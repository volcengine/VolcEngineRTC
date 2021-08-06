package cs_models

import (
	"context"
	"errors"
	"gorm.io/gorm"
	"time"

	logs "github.com/sirupsen/logrus"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/config"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/dal/db"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/dal/db/cs_db"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/dal/redis/cs_redis"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/models/conn_models"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/models/custom_error"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/pkg/response"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/pkg/token"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/rpc/frontier"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/pkg/public"
)

const MaxReconnectRetry = 5

type User struct {
	u *db.CsMeetingUser
	r *Room
}

type joinMeetingReturn struct {
	Token string      `json:"token"`
	Info  *RoomInfo   `json:"info"`
	Users []*UserInfo `json:"users"`
}

type getRaiseHandsReturn struct {
	Users []*UserInfo `json:"users"`
}

type getAudiencesReturn struct {
	Users []*UserInfo `json:"users"`
}

type reconnectReturn struct {
	Info  *RoomInfo   `json:"info"`
	Users []*UserInfo `json:"users"`
}

func GenDBUser(appID, userID, userName, roomID, connID, deviceID string) *db.CsMeetingUser {
	return &db.CsMeetingUser{
		AppID:    appID,
		UserID:   userID,
		UserName: userName,
		RoomID:   roomID,
		ConnID:   connID,
		State:    db.ACTIVE,
		DeviceID: deviceID,
	}
}

func NewUser(u *db.CsMeetingUser, r *Room) *User {
	return &User{
		u: u,
		r: r,
	}
}

func GetUser(ctx context.Context, connID string) (*User, error) {
	u, err := cs_db.GetActiveUserByConnID(ctx, connID)
	if err != nil && !errors.Is(err, gorm.ErrRecordNotFound) {
		logs.Errorf("failed to get user in db, err: %v", err)
		return nil, custom_error.InternalError(err)
	}

	if errors.Is(err, gorm.ErrRecordNotFound) {
		logs.Warn(ctx, "user is inactive")
		return nil, custom_error.ErrUserIsInactive
	}

	r, err := GetRoom(ctx, u.RoomID)
	if err != nil && !errors.Is(err, custom_error.ErrRoomNotExist) {
		logs.Errorf("failed to get room, err: %v", err)
		return nil, err
	}

	if errors.Is(err, custom_error.ErrRoomNotExist) {
		logs.Warn(ctx, "room not exist")
		return nil, err
	}

	return &User{
		u: u,
		r: r,
	}, nil
}

func GetReconnectingUser(ctx context.Context, connID string) (*User, error) {
	u, err := cs_db.GetReconnectingUserByConnID(ctx, connID)
	if err != nil && !errors.Is(err, gorm.ErrRecordNotFound) {
		logs.Errorf("failed to get user in db, err: %v", err)
		return nil, custom_error.InternalError(err)
	}

	if errors.Is(err, gorm.ErrRecordNotFound) {
		logs.Warn(ctx, "user is inactive")
		return nil, custom_error.ErrUserIsInactive
	}

	r, err := GetRoom(ctx, u.RoomID)
	if err != nil && !errors.Is(err, custom_error.ErrRoomNotExist) {
		logs.Errorf("failed to get room, err: %v", err)
		return nil, err
	}

	if errors.Is(err, custom_error.ErrRoomNotExist) {
		logs.Warn(ctx, "room not exist")
		return nil, err
	}

	return &User{
		u: u,
		r: r,
	}, nil
}

func (u *User) LeaveMeeting(ctx context.Context) error {
	logs.Infof("leave meeting")

	if u.u.IsHost {
		host, err := cs_db.GetNextHost(ctx, u.u)
		if err != nil && !errors.Is(err, gorm.ErrRecordNotFound) {
			logs.Errorf("failed to get next host, err: %v", err)
			return custom_error.InternalError(err)
		}

		if errors.Is(err, gorm.ErrRecordNotFound) {
			logs.Infof("no user on microphone")
			return u.MeetingEnd(ctx)
		}

		return u.HostChange(ctx, host)
	}

	return u.NormalUserLeaveMeeting(ctx)
}

func (u *User) MeetingEnd(ctx context.Context) error {
	u.GetRoom().Inform(ctx, OnCsMeetingEnd, RoomIDInfo{RoomID: u.u.RoomID})

	if err := cs_db.CleanRoom(ctx, u.u.RoomID); err != nil {
		logs.Errorf("failed to clean room, err: %v", err)
		return custom_error.InternalError(err)
	}

	cs_redis.DeleteRoomState(ctx, u.u.RoomID)

	return nil
}

func (u *User) HostChange(ctx context.Context, host *db.CsMeetingUser) error {
	logs.Infof("host change, pre host: %s, next host: %s", u.u.UserID, host.UserID)

	u.u.IsHost = false
	u.u.UserStatus = int(db.UserStatusAudience)
	u.u.State = db.INACTIVE
	host.IsHost = true

	if err := cs_db.BatchUpdateUsers(ctx, u.u, host); err != nil {
		logs.Errorf("failed to batch update users in db, err: %v", err)
		return custom_error.ErrChangeHost
	}

	cs_redis.SetRoomHostID(ctx, host.RoomID, host.UserID)
	cs_redis.SetRoomHostName(ctx, host.RoomID, host.UserName)
	cs_redis.DecreaseRoomUserOnMicrophone(ctx, host.RoomID)
	cs_redis.DecreaseRoomUserCount(ctx, host.RoomID)

	go func() {
		defer public.CheckPanic()

		hoster := NewUser(host, u.r)

		u.r.Inform(ctx, OnCsHostChange, HostInfo{
			FormerHostID: u.u.UserID,
			HostInfo:     hoster.GenerateInformUserInfo(),
		})

		u.r.Inform(ctx, OnCsLeaveMeeting, u.GenerateInformUserInfo())
	}()

	return nil
}

func (u *User) NormalUserLeaveMeeting(ctx context.Context) error {
	logs.Infof("normal user leave meeting, user: %s", u.u.UserID)

	var isOnMic bool

	if u.u.UserStatus == int(db.UserStatusOnMicrophone) {
		isOnMic = true
	}

	u.u.UserStatus = int(db.UserStatusAudience)
	u.u.State = db.INACTIVE

	if err := cs_db.UpdateUser(ctx, u.u); err != nil {
		logs.Errorf("failed to update user in db, err: %v", err)
		return custom_error.InternalError(err)
	}

	cs_redis.DecreaseRoomUserCount(ctx, u.u.RoomID)

	if isOnMic {
		cs_redis.DecreaseRoomUserOnMicrophone(ctx, u.u.RoomID)
	}

	go u.r.Inform(ctx, OnCsLeaveMeeting, u.GenerateInformUserInfo())

	return nil
}

func (u *User) Disconnect(ctx context.Context) error {
	u.u.State = db.RECONNECTING

	go func() {
		time.Sleep(time.Duration(config.Config.ReconnectTimeout) * time.Second)

		user, err := GetReconnectingUser(ctx, u.u.ConnID)
		if err != nil {
			logs.Infof("not get reconnecting user, err: %v", err)
			return
		}

		_ = user.LeaveMeeting(ctx)
	}()

	if err := cs_db.CreateOrUpdateUser(ctx, u.u); err != nil {
		logs.Errorf("failed to update user in db, err: %v", err)
		return custom_error.InternalError(err)
	}
	return nil
}

func (u *User) GetRoomID() string {
	return u.u.RoomID
}

func (u *User) GetUserID() string {
	return u.u.UserID
}

func (u *User) GetAppID() string {
	return u.u.AppID
}

func (u *User) GetRoom() *Room {
	return u.r
}

func (u *User) GetState() int {
	return u.u.State
}

func (u *User) GetCreateAt() int64 {
	return u.u.CreatedAt.UnixNano()
}

func (u *User) GetHostState() bool {
	return u.u.IsHost
}

func (u *User) GetMicState() bool {
	return u.u.IsMicOn
}

func (u *User) CheckAppID(appID string) bool {
	return appID == config.Config.AppID
}

func (u *User) GenerateToken(ctx context.Context) (string, error) {
	param := &token.GenerateParam{
		AppID:        u.u.AppID,
		AppKey:       config.Config.AppKey,
		RoomID:       u.u.RoomID,
		UserID:       u.u.UserID,
		ExpireAt:     7 * 24 * 3600,
		CanPublish:   true,
		CanSubscribe: true,
		CanSwitch:    true,
	}

	token, err := token.GenerateToken(param)
	if err != nil {
		logs.Errorf("generate token error, err: %v", err)
		return "", custom_error.ErrTokenGenerate
	}

	logs.Infof("generate token: %v", token)

	return token, nil
}

func (u *User) GenerateInformUserInfo() *UserInfo {
	return &UserInfo{
		UserID:       u.u.UserID,
		UserName:     u.u.UserName,
		IsHost:       u.u.IsHost,
		UserStatus:   u.u.UserStatus,
		IsMicOn:      u.u.IsMicOn,
		CreatedAt:    u.u.CreatedAt.UnixNano(),
		RaiseHandsAt: u.u.RaiseHandsAt.UnixNano(),
	}
}

func (u *User) CreateMeeting(ctx context.Context) (*joinMeetingReturn, error) {
	token, err := u.GenerateToken(ctx)
	if err != nil {
		return nil, err
	}

	if err := u.r.create(ctx, u); err != nil {
		return nil, err
	}

	return &joinMeetingReturn{
		Token: token,
		Info: &RoomInfo{
			RoomID:      u.r.room.RoomID,
			RoomName:    u.r.room.RoomName,
			HostID:      u.u.UserID,
			HostName:    u.u.UserName,
			UserCounts:  1,
			MiconCounts: 1,
			CreatedAt:   u.r.room.CreatedAt.UnixNano(),
			Now:         time.Now().UnixNano(),
		},
		Users: []*UserInfo{u.GenerateInformUserInfo()},
	}, nil
}

func (u *User) JoinMeeting(ctx context.Context) (*joinMeetingReturn, error) {
	token, err := u.GenerateToken(ctx)
	if err != nil {
		return nil, err
	}

	ok, lt := u.r.Lock(ctx)
	if !ok {
		return nil, custom_error.ErrLockRedis
	}
	defer u.r.UnLock(ctx, lt)

	ok, err = u.r.exist(ctx)
	if err != nil {
		return nil, err
	}

	ok, err = u.updateSameDeviceUser(ctx)
	if err != nil {
		return nil, err
	}

	if ok {
		return u.joinRoomRes(ctx, token)
	}

	err = u.checkUserCount(ctx)
	if err != nil {
		return nil, err
	}

	err = u.joinActiveMeeting(ctx)
	if err != nil {
		return nil, err
	}

	return u.joinRoomRes(ctx, token)
}

func (u *User) joinRoomRes(ctx context.Context, token string) (*joinMeetingReturn, error) {
	users, err := u.r.ListUsersWithJoinMeetingTime(ctx)
	if err != nil {
		return nil, err
	}

	return &joinMeetingReturn{
		Token: token,
		Info:  u.r.GenerateInformRoomInfo(ctx),
		Users: users,
	}, nil
}

func (u *User) CleanUserResidual(ctx context.Context, roomID string) {
	meetingUsers, err := cs_db.GetActiveUsersByDeviceID(ctx, u.u.DeviceID)
	if errors.Is(err, gorm.ErrRecordNotFound) {
		return
	}

	if err != nil {
		logs.Errorf("failed to get active users, err: %v", err)
		return
	}

	for _, meetingUser := range meetingUsers {
		if meetingUser.RoomID == roomID {
			continue
		}

		r, err := GetRoom(ctx, meetingUser.RoomID)
		if err != nil {
			logs.Errorf("failed to get room, err: %v", err)
			continue
		}

		user := NewUser(meetingUser, r)

		logs.Infof("clean user residual")

		_ = user.LeaveMeeting(ctx)
	}
}

func (u *User) updateSameDeviceUser(ctx context.Context) (bool, error) {
	meetingUser, err := cs_db.GetReconnectingOrActiveUserByRoomIDAndDeviceID(ctx, u.u.RoomID, u.u.UserID, u.u.DeviceID)
	if err != nil && !errors.Is(err, gorm.ErrRecordNotFound) {
		return false, custom_error.InternalError(err)
	}

	if errors.Is(err, gorm.ErrRecordNotFound) {
		return false, nil
	}

	meetingUser.UserName = u.u.UserName
	meetingUser.ConnID = u.u.ConnID
	meetingUser.State = db.ACTIVE

	u.u = meetingUser

	err = cs_db.CreateOrUpdateUser(ctx, meetingUser)
	if err != nil {
		return false, custom_error.InternalError(err)
	}

	if meetingUser.IsHost {
		cs_redis.SetRoomHostName(ctx, meetingUser.RoomID, meetingUser.UserName)
	}

	return true, nil
}

func (u *User) joinActiveMeeting(ctx context.Context) error {
	logs.Infof("join active meeting")
	return u.r.AddUser(ctx, u)
}

func (u *User) checkUserCount(ctx context.Context) error {
	if u.r.GetUserCount(ctx) >= config.Config.RoomUserLimit {
		logs.Errorf("user exceed limit")
		return custom_error.ErrUserExceedLimit
	}
	return nil
}

func (u *User) Inform(ctx context.Context, event InformEvent, data interface{}) {
	defer public.CheckPanic()

	c, err := conn_models.GetConnection(ctx, u.u.ConnID)
	if err != nil {
		logs.Errorf("failed to get connection, err: %v", err)
		return
	}
	frontier.PushToClient(ctx, c.GetConnID(), c.GetAddr(), c.GetAddr6(), string(event), response.NewInformToClient(string(event), data), -1)
}

func (u *User) checkRoomAndUserState(ctx context.Context, hostCheck bool) error {
	if u.r.room.State == false {
		logs.Warn(ctx, "room is inactive")
		return custom_error.ErrRoomIsInactive
	}

	if u.u.State != db.ACTIVE {
		logs.Warn(ctx, "user state is not active")
		return custom_error.ErrUserIsInactive
	}

	if hostCheck && u.u.IsHost == false {
		logs.Warn(ctx, "user is not host")
		return custom_error.ErrUserIsNotHost
	}

	return nil
}

func (u *User) GetRaiseHands(ctx context.Context) (*getRaiseHandsReturn, error) {
	if err := u.checkRoomAndUserState(ctx, true); err != nil {
		return nil, err
	}

	users, err := u.r.ListRaiseHandsUsers(ctx)
	if err != nil {
		return nil, err
	}

	return &getRaiseHandsReturn{
		Users: users,
	}, nil
}

func (u *User) GetAudiences(ctx context.Context) (*getAudiencesReturn, error) {
	if err := u.checkRoomAndUserState(ctx, true); err != nil {
		return nil, err
	}

	users, err := u.r.ListAudiences(ctx)
	if err != nil {
		return nil, err
	}

	return &getAudiencesReturn{
		Users: users,
	}, nil
}

func (u *User) InviteMic(ctx context.Context, userID string) (*User, error) {
	if err := u.checkRoomAndUserState(ctx, true); err != nil {
		return nil, err
	}

	meetingUser, err := cs_db.GetActiveUserByRoomIDAndUserID(ctx, u.r.room.RoomID, userID)
	if errors.Is(err, gorm.ErrRecordNotFound) {
		logs.Warn(ctx, "user is not active")
		return nil, custom_error.ErrUserIsInactive
	}

	if err != nil {
		logs.Errorf("failed to get user, err: %v", err)
		return nil, custom_error.InternalError(err)
	}

	return NewUser(meetingUser, u.r), nil
}

func (u *User) ConfirmMic(ctx context.Context) error {
	if err := u.checkRoomAndUserState(ctx, false); err != nil {
		return err
	}

	if u.u.UserStatus == int(db.UserStatusOnMicrophone) {
		logs.Warn(ctx, "user already on microphone")
		return nil
	}

	u.u.UserStatus = int(db.UserStatusOnMicrophone)
	u.u.RaiseHandsAt = time.Now()
	if err := cs_db.UpdateUser(ctx, u.u); err != nil {
		logs.Errorf("failed to update user status, err: %v", err)
		return custom_error.InternalError(err)
	}

	cs_redis.IncreaseRoomUserOnMicrophone(ctx, u.u.RoomID)

	return nil
}

func (u *User) RaiseHandsMic(ctx context.Context) error {
	if err := u.checkRoomAndUserState(ctx, false); err != nil {
		return err
	}

	// support raising hands repeatedly
	u.u.UserStatus = int(db.UserStatusRaiseHands)
	u.u.RaiseHandsAt = time.Now()
	if err := cs_db.UpdateUser(ctx, u.u); err != nil {
		logs.Errorf("failed to update user status, err: %v", err)
		return custom_error.InternalError(err)
	}

	return nil
}

func (u *User) AgreeMic(ctx context.Context, userID string) (*User, error) {
	if err := u.checkRoomAndUserState(ctx, true); err != nil {
		return nil, err
	}

	meetingUser, err := cs_db.GetActiveUserByRoomIDAndUserID(ctx, u.r.room.RoomID, userID)
	if err != nil {
		return nil, custom_error.InternalError(err)
	}

	agreedUser := NewUser(meetingUser, u.r)

	if agreedUser.u.UserStatus == int(db.UserStatusOnMicrophone) {
		logs.Warn(ctx, "user already on microphone")
		return agreedUser, nil
	}

	agreedUser.u.UserStatus = int(db.UserStatusOnMicrophone)
	agreedUser.u.RaiseHandsAt = time.Now()

	if err := cs_db.UpdateUser(ctx, agreedUser.u); err != nil {
		logs.Errorf("failed to update user status, err: %v", err)
		return nil, custom_error.InternalError(err)
	}

	cs_redis.IncreaseRoomUserOnMicrophone(ctx, agreedUser.u.RoomID)

	return agreedUser, nil
}

func (u *User) OffSelfMic(ctx context.Context) error {
	if err := u.checkRoomAndUserState(ctx, false); err != nil {
		return err
	}

	if u.u.UserStatus == int(db.UserStatusAudience) {
		logs.Warn(ctx, "user already off microphone")
		return nil
	}

	u.u.UserStatus = int(db.UserStatusAudience)

	if err := cs_db.UpdateUser(ctx, u.u); err != nil {
		logs.Errorf("failed to update user status, err: %v", err)
		return custom_error.InternalError(err)
	}

	cs_redis.DecreaseRoomUserOnMicrophone(ctx, u.u.RoomID)

	return nil
}

func (u *User) OffMic(ctx context.Context, userID string) (*User, error) {
	if err := u.checkRoomAndUserState(ctx, true); err != nil {
		return nil, err
	}

	meetingUser, err := cs_db.GetActiveUserByRoomIDAndUserID(ctx, u.r.room.RoomID, userID)
	if errors.Is(err, gorm.ErrRecordNotFound) {
		logs.Warn(ctx, "user is inactive")
		return nil, custom_error.ErrUserIsInactive
	}

	if err != nil {
		logs.Errorf("failed to get user, err: %v", err)
		return nil, custom_error.InternalError(err)
	}

	offUser := NewUser(meetingUser, u.r)

	if offUser.u.UserStatus == int(db.UserStatusAudience) {
		logs.Warn(ctx, "user already off microphone")
		return offUser, nil
	}

	offUser.u.UserStatus = int(db.UserStatusAudience)
	if err := cs_db.UpdateUser(ctx, offUser.u); err != nil {
		logs.Errorf("failed to update user status, err: %v", err)
		return nil, custom_error.InternalError(err)
	}

	cs_redis.DecreaseRoomUserOnMicrophone(ctx, offUser.u.RoomID)

	return offUser, nil
}

func (u *User) MuteMic(ctx context.Context) error {
	if err := u.checkRoomAndUserState(ctx, false); err != nil {
		return err
	}

	if u.u.IsMicOn == false {
		logs.Warn(ctx, "user already mute mic")
		return nil
	}

	u.u.IsMicOn = false
	if err := cs_db.UpdateUser(ctx, u.u); err != nil {
		logs.Errorf("failed to update user mic status, err: %v", err)
		return custom_error.InternalError(err)
	}

	return nil
}

func (u *User) UnmuteMic(ctx context.Context) error {
	if err := u.checkRoomAndUserState(ctx, false); err != nil {
		return err
	}

	if u.u.IsMicOn == true {
		logs.Warn(ctx, "user already unmute mic")
		return nil
	}

	u.u.IsMicOn = true
	if err := cs_db.UpdateUser(ctx, u.u); err != nil {
		logs.Errorf("failed to update user mic status, err: %v", err)
		return custom_error.InternalError(err)
	}

	return nil
}

func getReconnectingUser(ctx context.Context, c *conn_models.Connection) (user *db.CsMeetingUser, err error) {
	for i := 0; i < MaxReconnectRetry; i++ {
		if user, err = cs_db.GetReconnectingOrActiveUserByDeviceID(ctx, c.GetDeviceID()); err == nil {
			return user, nil
		}
		logs.Infof("cannot find reconnecting user, wait 10ms")
		time.Sleep(10 * time.Millisecond)
	}

	return nil, err
}

func Reconnect(ctx context.Context, c *conn_models.Connection) (*reconnectReturn, error) {
	meetingUser, err := getReconnectingUser(ctx, c)
	if errors.Is(err, gorm.ErrRecordNotFound) {
		logs.Infof("no need to reconnect")
		return nil, custom_error.ErrCanNotReconnect
	}

	if err != nil {
		logs.Errorf("db error: %v", err)
		return nil, custom_error.InternalError(err)
	}

	meetingUser.State = db.ACTIVE
	meetingUser.ConnID = c.GetConnID()
	if err := cs_db.CreateOrUpdateUser(ctx, meetingUser); err != nil {
		logs.Warn(ctx, "failed to update user in db, err: %v", err)
		return nil, custom_error.InternalError(err)
	}

	user, err := GetUser(ctx, meetingUser.ConnID)
	if err != nil {
		logs.Errorf("failed to get user, err %v", err)
		return nil, err
	}

	users, err := user.r.ListUsersWithJoinMeetingTime(ctx)
	if err != nil {
		logs.Errorf("failed to get user list, err %v", err)
		return nil, err
	}

	return &reconnectReturn{
		Info:  user.r.GenerateInformRoomInfo(ctx),
		Users: users,
	}, nil
}
