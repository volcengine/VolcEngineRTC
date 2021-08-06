package vc_models

import (
	"context"
	"errors"
	"gorm.io/gorm"
	"time"

	logs "github.com/sirupsen/logrus"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/config"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/dal/db"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/dal/db/vc_db"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/dal/redis/vc_redis"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/models/conn_models"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/models/custom_error"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/pkg/record"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/pkg/response"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/pkg/token"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/rpc/frontier"
)

const MaxReconnectRetry = 5

const (
	Inactive = iota
	Active
	Reconnecting
)

type User struct {
	u *db.MeetingUser
	r *Room
}

type joinMeetingReturn struct {
	Token string      `json:"token"`
	Info  MeetingInfo `json:"info"`
	Users []UserInfo  `json:"users"`
}

func GenDBUser(appID, userID, roomID, connID, deviceID string, isMicOn, isCameraOn bool) *db.MeetingUser {
	return &db.MeetingUser{
		AppID:      appID,
		UserID:     userID,
		RoomID:     roomID,
		ConnID:     connID,
		IsMicOn:    isMicOn,
		IsCameraOn: isCameraOn,
		State:      db.ACTIVE,
		DeviceID:   deviceID,
		CreatedAt:  time.Now(),
	}
}

func NewUser(u *db.MeetingUser, r *Room) *User {
	return &User{
		u: u,
		r: r,
	}
}

func GetUser(ctx context.Context, connID string) (*User, error) {
	u, err := vc_db.GetUserByConnID(ctx, connID)
	if err != nil {
		logs.Errorf("failed to get user in db, err: %v", err)
		return nil, custom_error.InternalError(err)
	}

	r, err2 := GetRoom(ctx, u.RoomID)
	if err2 != nil {
		logs.Errorf("failed to get room, err: %v", err2)
		return nil, err2
	}

	return &User{
		u: u,
		r: r,
	}, nil
}

func (u *User) Leave(ctx context.Context) error {
	if u.u.IsHost {
		return custom_error.ErrHostNotAllowedLeave
	}

	shareInform := false
	if u.u.IsSharing {
		shareInform = true
		u.r.setShareUser(ctx, "")
	}

	u.u.IsSharing = false
	u.u.State = Inactive
	if err := vc_db.UpdateUser(ctx, u.u); err != nil {
		logs.Errorf("failed to update user in db, err: %v", err)
		return custom_error.InternalError(err)
	}

	if shareInform {
		go u.r.Inform(ctx, ShareScreenStatusChanged, UserDeviceInfo{UserID: u.u.UserID, Status: false})
	}

	vc_redis.DecreaseRoomUserCount(ctx, u.u.RoomID)
	go u.r.Inform(ctx, UserLeaveMeeting, UserIDInfo{UserID: u.u.UserID})
	go u.Inform(ctx, UserLeaveMeeting, UserIDInfo{UserID: u.u.UserID})

	return nil
}

func (u *User) Disconnect(ctx context.Context) error {
	u.u.State = Reconnecting
	go func() {
		time.Sleep(time.Duration(config.Config.ReconnectTimeout) * time.Second)
		if user, err := vc_db.GetUserByDeviceID(ctx, u.u.RoomID, u.u.UserID, u.u.DeviceID); err == nil && user.State == Reconnecting {
			logs.Infof("clean user, err: %v", u.Clean(ctx, true))
		}
	}()

	if err := vc_db.CreateOrUpdateUser(ctx, u.u); err != nil {
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

func (u *User) GetShareState() bool {
	return u.u.IsSharing
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

func (u *User) GetCameraState() bool {
	return u.u.IsCameraOn
}

func (u *User) CheckAppID(appID string) bool {
	return appID == config.Config.AppID
}

func (u *User) GenerateToken(ctx context.Context) (string, error) {
	// hack for qa test
	// if public.StringInSlice(u.r.room.RoomID, tcc.Settings().TokenError) {
	// 	return "", ErrTokenGenerate
	// }

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

func (u *User) GenerateInformUserInfo() UserInfo {
	return UserInfo{
		UserID:          u.u.UserID,
		RoomID:          u.u.RoomID,
		IsHost:          u.u.IsHost,
		IsMicOn:         u.u.IsMicOn,
		IsCameraOn:      u.u.IsCameraOn,
		IsSharing:       u.u.IsSharing,
		CreatedAt:       u.u.CreatedAt.UnixNano(),
	}
}

func (u *User) SetMicState(ctx context.Context, state bool) error {
	if err := u.checkRoomAndUserState(ctx, false); err != nil {
		return err
	}

	if u.u.IsMicOn == state {
		logs.Warnf("user mic state is already %v", state)
		return custom_error.ErrSameDeviceState
	}

	u.u.IsMicOn = state
	if err := vc_db.UpdateUser(ctx, u.u); err != nil {
		logs.Errorf("failed to update user mic state, err: %v", err)
		return custom_error.InternalError(err)
	}
	go u.r.Inform(ctx, UserMicStatusChange, UserDeviceInfo{UserID: u.u.UserID, Status: state})
	return nil
}

func (u *User) SetCameraState(ctx context.Context, state bool) error {
	if err := u.checkRoomAndUserState(ctx, false); err != nil {
		return err
	}

	if u.u.IsCameraOn == state {
		logs.Warnf("user camera state is already %v", state)
		return custom_error.ErrSameDeviceState
	}

	u.u.IsCameraOn = state
	if err := vc_db.UpdateUser(ctx, u.u); err != nil {
		logs.Errorf("failed to update user camera state, err: %v", err)
		return custom_error.InternalError(err)
	}
	go u.r.Inform(ctx, UserCameraStatusChange, UserDeviceInfo{UserID: u.u.UserID, Status: state})
	return nil
}

func (u *User) SetShareState(ctx context.Context, state bool) error {
	if err := u.checkRoomAndUserState(ctx, false); err != nil {
		return err
	}

	if state == true && u.r.shareUser != "" {
		logs.Warnf("failed to share because %s is sharing, roomID: %s, userID: %s", u.r.shareUser, u.u.RoomID, u.u.UserID)
		return custom_error.ErrUserIsSharing
	}

	if state == false && u.r.shareUser != u.u.UserID {
		logs.Warnf("failed to stop share because %s is sharing, roomID: %s, userID: %s", u.r.shareUser, u.u.RoomID, u.u.UserID)
		return custom_error.ErrUserIsSharing
	}

	if u.u.IsSharing == state {
		logs.Warnf("user sharing state is already %v, no need to change, roomID: %s, userID: %s", state, u.u.RoomID, u.u.UserID)
		return custom_error.ErrUserIsSharing
	}

	u.u.IsSharing = state
	if err := vc_db.UpdateUser(ctx, u.u); err != nil {
		logs.Errorf("failed to update user share state, err: %v", err)
		return custom_error.InternalError(err)
	}

	if state {
		u.r.setShareUser(ctx, u.u.UserID)
	} else {
		u.r.setShareUser(ctx, "")
	}
	go u.r.Inform(ctx, ShareScreenStatusChanged, UserDeviceInfo{UserID: u.u.UserID, Status: state})
	return nil
}

func (u *User) StartRecord(ctx context.Context, users []string, screen string) error {
	if err := u.checkRoomAndUserState(ctx, true); err != nil {
		return err
	}
	taskID, err := record.StartRecord(ctx, users, screen, u.u.AppID, u.u.RoomID)
	if err != nil {
		logs.Errorf("failed to start record, err: %v", err)
		return custom_error.InternalError(err)
	}
	u.r.setRecordTaskID(ctx, taskID)

	// set pair <TaskID: UserID>
	vc_redis.SetTaskIDWithUserID(ctx, taskID, u.u.UserID)

	go u.r.Inform(ctx, Record, nil)
	return nil
}

func (u *User) UpdateRecord(ctx context.Context, users []string, screen string) error {
	if err := u.checkRoomAndUserState(ctx, true); err != nil {
		return err
	}
	if err := record.UpdateRecord(ctx, users, screen, u.u.AppID, u.u.RoomID, u.r.recordTaskID); err != nil {
		logs.Errorf("failed to update record, err: %v", err)
		return custom_error.InternalError(err)
	}
	return nil
}

func (u *User) MuteUser(ctx context.Context, userID string) error {
	if err := u.checkRoomAndUserState(ctx, true); err != nil {
		return err
	}

	if userID == "" {
		// if public.StringInSlice(u.r.room.RoomID, tcc.Settings().MuteAllError) {
		// 	return ErrMuteAll
		// }

		return u.r.MuteAllWithoutHost(ctx)
	}

	user, err := vc_db.GetActiveUserByRoomIDAndUserID(ctx, u.u.RoomID, userID)
	if err != nil {
		logs.Errorf("failed to get user in db, err: %v", err)
		return custom_error.InternalError(err)
	}
	go NewUser(user, nil).Inform(ctx, MuteUser, UserIDInfo{UserID: user.UserID})
	return nil
}

func (u *User) AskUserDeviceChange(ctx context.Context, userID string, event InformEvent) error {
	if err := u.checkRoomAndUserState(ctx, true); err != nil {
		return err
	}

	if userID == "" {
		return custom_error.ErrUserIsInactive
	}

	user, err := vc_db.GetActiveUserByRoomIDAndUserID(ctx, u.u.RoomID, userID)
	if err != nil {
		logs.Errorf("failed to get user in db, err: %v", err)
		return custom_error.InternalError(err)
	}
	go NewUser(user, nil).Inform(ctx, event, UserIDInfo{UserID: user.UserID})
	return nil
}

func (u *User) ChangeHost(ctx context.Context, userID string) error {
	// if public.StringInSlice(u.r.room.RoomID, tcc.Settings().ChangeHostError) {
	// 	return ErrChangeHost
	// }

	if err := u.checkRoomAndUserState(ctx, true); err != nil {
		return err
	}

	user, err := vc_db.GetActiveUserByRoomIDAndUserID(ctx, u.u.RoomID, userID)
	if err != nil {
		logs.Errorf("failed to get user in db, err: %v", err)
		// 统一返回给客户端503的错误码
		return custom_error.ErrChangeHost
	}

	u.u.IsHost = false
	user.IsHost = true
	if err := vc_db.BatchUpdateUsers(ctx, u.u, user); err != nil {
		logs.Errorf("failed to batch update users in db, err: %v", err)
		return custom_error.ErrChangeHost
	}

	u.r.setHost(ctx, user.UserID)
	go u.r.Inform(ctx, HostChange, HostInfo{FormerHostID: u.u.UserID, HostID: user.UserID})
	return nil
}

func (u *User) EndMeeting(ctx context.Context) error {
	if err := u.checkRoomAndUserState(ctx, true); err != nil {
		return err
	}
	return u.r.End(ctx)
}

func (u *User) JoinMeeting(ctx context.Context) (joinMeetingReturn, error) {
	res := joinMeetingReturn{}

	if !u.CheckAppID(u.u.AppID) {
		return res, custom_error.ErrInvalidAppID
	}

	token, err := u.GenerateToken(ctx)
	if err != nil {
		return res, err
	}

	ok, lt := u.r.Lock(ctx)
	if !ok {
		return res, custom_error.ErrLockRedis
	}
	defer u.r.UnLock(ctx, lt)

	ok, err = u.r.exist(ctx)
	if err != nil {
		return res, err
	}

	if !ok {
		if err := u.r.create(ctx, u); err != nil {
			return res, err
		}

		return u.joinRoomRes(ctx, token)
	}

	if err := u.checkUserCount(ctx); err != nil {
		return res, err
	}

	if err := u.kickSameDeviceUser(ctx); err != nil {
		return res, err
	}

	if err := u.joinActiveMeeting(ctx); err != nil {
		return res, err
	}

	return u.joinRoomRes(ctx, token)
}

func (u *User) joinRoomRes(ctx context.Context, token string) (joinMeetingReturn, error) {
	users, err := u.r.ListUsers(ctx)
	if err != nil {
		return joinMeetingReturn{}, err
	}

	// if len(users) > 10 {
	// 	users = users[:10]
	// }

	return joinMeetingReturn{
		Token: token,
		Info:  u.r.GetRoomInfo(ctx),
		Users: users,
	}, nil
}

func (u *User) kickSameDeviceUser(ctx context.Context) error {
	user, err := vc_db.GetReconnectingUser(ctx, u.u.DeviceID)
	if err == nil {
		r, err := GetRoom(ctx, user.RoomID)
		if err != nil {
			logs.Errorf("failed to get room: %v", err)
			return err
		}
		return NewUser(user, r).Clean(ctx, false)
	}

	if errors.Is(err, gorm.ErrRecordNotFound) {
		logs.Infof("no same device user")
		return nil
	}
	return custom_error.InternalError(err)
}

func (u *User) joinActiveMeeting(ctx context.Context) error {
	logs.Infof("join active meeting")
	user, err := vc_db.GetActiveUserByRoomIDAndUserID(ctx, u.u.RoomID, u.u.UserID)
	if err == nil {
		return u.multiDeviceLogin(ctx, user)
	}
	if errors.Is(err, gorm.ErrRecordNotFound) {
		if u.r.GetUserCount(ctx) == 0 {
			u.r.setHost(ctx, u.u.UserID)
			u.u.IsHost = true
		}
		return u.r.AddUser(ctx, u)
	}
	return custom_error.InternalError(err)
}

func (u *User) checkUserCount(ctx context.Context) error {
	if u.r.GetUserCount(ctx) >= config.Config.RoomUserLimit {
		logs.Errorf("user exceed limit")
		return custom_error.ErrUserExceedLimit
	}
	return nil
}

func (u *User) multiDeviceLogin(ctx context.Context, user *db.MeetingUser) error {
	logs.Infof("multi device user login")
	cleanU, err := GetUser(ctx, user.ConnID)
	if err != nil {
		return custom_error.InternalError(err)
	}

	if err := cleanU.Clean(ctx, false); err != nil {
		return err
	}

	if u.r.GetUserCount(ctx) == 0 {
		u.r.setHost(ctx, u.u.UserID)
		u.u.IsHost = true
	}

	if err := u.r.AddUser(ctx, u); err != nil {
		return err
	}

	return nil
}

func (u *User) Inform(ctx context.Context, event InformEvent, data interface{}) {
	c, err := conn_models.GetConnection(ctx, u.u.ConnID)
	if err != nil {
		logs.Errorf("failed to get connection, err: %v", err)
		return
	}
	frontier.PushToClient(ctx, c.GetConnID(), c.GetAddr(), c.GetAddr6(), string(event), response.NewInformToClient(string(event), data), -1)
}

func (u *User) Clean(ctx context.Context, withMeetingOver bool) error {
	if !u.u.IsHost {
		return u.r.KickNormalUser(ctx, u)
	}
	return u.r.KickHost(ctx, u, withMeetingOver)
}

func (u *User) checkRoomAndUserState(ctx context.Context, hostCheck bool) error {
	if u.r.room.State == false {
		logs.Warnf("room is inactive")
		return custom_error.ErrRoomIsInactive
	}

	if u.u.State != Active {
		logs.Warnf("user state is not active")
		return custom_error.ErrUserIsInactive
	}

	if hostCheck && u.u.IsHost == false {
		logs.Warnf("user is not host")
		return custom_error.ErrUserIsNotHost
	}

	return nil
}

func (u *User) CleanDirtyUser(ctx context.Context, selfuserID string) {
	users, err := vc_db.GetActiveUsersByDeviceID(ctx, u.u.DeviceID)
	if err != nil {
		logs.Warnf("failed to get users from db, err: %v", err)
		return
	}

	us := make(map[string][]*db.MeetingUser)

	for _, u := range users {
		if u.UserID == selfuserID {
			continue
		}
		u.State = Inactive
		us[u.RoomID] = append(us[u.RoomID], u)
	}

	for roomID, user := range us {
		if err := vc_db.BatchUpdateUsers(ctx, user...); err != nil {
			logs.Warnf("failed to clean dirty user, err: %v", err)
		}
		if count, err := vc_db.GetRoomUserCount(ctx, roomID); err == nil && count == 0 {
			logs.Infof("delete room, err: %v", vc_db.DeleteRoom(ctx, roomID))
			vc_redis.InitRoomState(ctx, roomID, "")
		}
	}
}

func retryGetConnectingUser(ctx context.Context, c *conn_models.Connection) (user *db.MeetingUser, err error) {
	for i := 0; i < MaxReconnectRetry; i++ {
		if user, err = vc_db.GetReconnectingUser(ctx, c.GetDeviceID()); err == nil {
			return user, nil
		}
		logs.Infof("cannot find reconnecting user, wait 10ms")
		time.Sleep(10 * time.Millisecond)
	}
	return nil, err
}

func Reconnect(ctx context.Context, c *conn_models.Connection) error {
	user, err := retryGetConnectingUser(ctx, c)
	if errors.Is(err, gorm.ErrRecordNotFound) {
		logs.Infof("no need to reconnect")
		return custom_error.ErrUserIsInactive
	}

	if err != nil {
		logs.Errorf("db error: %v", err)
		return custom_error.InternalError(err)
	}

	user.State = Active
	user.ConnID = c.GetConnID()
	if err := vc_db.CreateOrUpdateUser(ctx, user); err != nil {
		logs.Warnf("failed to update user in db, err: %v", err)
		return custom_error.InternalError(err)
	}

	return nil
}
