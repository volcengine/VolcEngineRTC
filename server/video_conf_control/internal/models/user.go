package models

import (
	"context"
	"errors"
	"time"

	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/config"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/dal/db"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/dal/redis"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/pkg/record"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/pkg/response"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/pkg/token"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/rpc/frontier"
	"gorm.io/gorm"
)

const (
	Inactive = iota
	Active
	Reconnecting
)

type User struct {
	u *db.ConferenceUser
	r *Room
}

type joinMeetingReturn struct {
	Token string      `json:"token"`
	Info  MeetingInfo `json:"info"`
	Users []UserInfo  `json:"users"`
}

func GenDBUser(appID, userID, roomID, connID, deviceID string, isMicOn, isCameraOn bool) *db.ConferenceUser {
	return &db.ConferenceUser{
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

func NewUser(u *db.ConferenceUser, r *Room) *User {
	return &User{
		u: u,
		r: r,
	}
}

func GetUser(ctx context.Context, connID string) (*User, error) {
	u, err := db.GetUserByConnID(ctx, connID)
	if err != nil {
		logs.CtxError(ctx, "failed to get user in db, err: %v", err)
		return nil, InternalError(err)
	}

	r, err2 := GetRoom(ctx, u.RoomID)
	if err2 != nil {
		logs.CtxError(ctx, "failed to get room, err: %v", err2)
		return nil, err2
	}

	return &User{
		u: u,
		r: r,
	}, nil
}

func (u *User) Leave(ctx context.Context) error {
	if u.u.IsHost {
		return ErrHostNotAllowedLeave
	}

	shareInform := false
	if u.u.IsSharing {
		shareInform = true
		u.r.setShareUser(ctx, "")
	}

	u.u.IsSharing = false
	u.u.State = Inactive
	if err := db.UpdateUser(ctx, u.u); err != nil {
		logs.CtxError(ctx, "failed to update user in db, err: %v", err)
		return InternalError(err)
	}

	if shareInform {
		go u.r.Inform(ctx, ShareScreenStatusChanged, UserDeviceInfo{UserID: u.u.UserID, Status: false})
	}

	redis.DecreaseRoomUserCount(ctx, u.u.RoomID)
	go u.r.Inform(ctx, UserLeaveMeeting, UserIDInfo{UserID: u.u.UserID})
	go u.Inform(ctx, UserLeaveMeeting, UserIDInfo{UserID: u.u.UserID})

	return nil
}

func (u *User) Disconnect(ctx context.Context) error {
	u.u.State = Reconnecting
	go func() {
		time.Sleep(time.Duration(config.Config.ReconnectTimeout) * time.Second)
		if user, err := db.GetUserByDeviceID(ctx, u.u.RoomID, u.u.UserID, u.u.DeviceID); err == nil && user.State == Reconnecting {
			logs.CtxInfo(ctx, "clean user, err: %v", u.Clean(ctx, true))
		}
	}()

	if err := db.CreateOrUpdateUser(ctx, u.u); err != nil {
		logs.CtxError(ctx, "failed to update user in db, err: %v", err)
		return InternalError(err)
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
		logs.CtxError(ctx, "generate token error, err: %v", err)
		return "", ErrTokenGenerate
	}

	logs.CtxInfo(ctx, "generate token: %v", token)

	return token, nil
}

func (u *User) GenerateInformUserInfo() UserInfo {
	return UserInfo{
		UserID:     u.u.UserID,
		RoomID:     u.u.RoomID,
		IsHost:     u.u.IsHost,
		IsMicOn:    u.u.IsMicOn,
		IsCameraOn: u.u.IsCameraOn,
		IsSharing:  u.u.IsSharing,
		CreatedAt:  u.u.CreatedAt.UnixNano(),
	}
}

func (u *User) SetMicState(ctx context.Context, state bool) error {
	if err := u.checkRoomAndUserState(ctx, false); err != nil {
		return err
	}

	if u.u.IsMicOn == state {
		logs.CtxWarn(ctx, "user mic state is already %v", state)
		return ErrSameDeviceState
	}

	u.u.IsMicOn = state
	if err := db.UpdateUser(ctx, u.u); err != nil {
		logs.CtxError(ctx, "failed to update user mic state, err: %v", err)
		return InternalError(err)
	}
	go u.r.Inform(ctx, UserMicStatusChange, UserDeviceInfo{UserID: u.u.UserID, Status: state})
	return nil
}

func (u *User) SetCameraState(ctx context.Context, state bool) error {
	if err := u.checkRoomAndUserState(ctx, false); err != nil {
		return err
	}

	if u.u.IsCameraOn == state {
		logs.CtxWarn(ctx, "user camera state is already %v", state)
		return ErrSameDeviceState
	}

	u.u.IsCameraOn = state
	if err := db.UpdateUser(ctx, u.u); err != nil {
		logs.CtxError(ctx, "failed to update user camera state, err: %v", err)
		return InternalError(err)
	}
	go u.r.Inform(ctx, UserCameraStatusChange, UserDeviceInfo{UserID: u.u.UserID, Status: state})
	return nil
}

func (u *User) SetShareState(ctx context.Context, state bool) error {
	if err := u.checkRoomAndUserState(ctx, false); err != nil {
		return err
	}

	if state == true && u.r.shareUser != "" {
		logs.CtxWarn(ctx, "failed to share because %s is sharing, roomID: %s, userID: %s", u.r.shareUser, u.u.RoomID, u.u.UserID)
		return ErrUserIsSharing
	}

	if state == false && u.r.shareUser != u.u.UserID {
		logs.CtxWarn(ctx, "failed to stop share because %s is sharing, roomID: %s, userID: %s", u.r.shareUser, u.u.RoomID, u.u.UserID)
		return ErrUserIsSharing
	}

	if u.u.IsSharing == state {
		logs.CtxWarn(ctx, "user sharing state is already %v, no need to change, roomID: %s, userID: %s", state, u.u.RoomID, u.u.UserID)
		return ErrUserIsSharing
	}

	u.u.IsSharing = state
	if err := db.UpdateUser(ctx, u.u); err != nil {
		logs.CtxError(ctx, "failed to update user share state, err: %v", err)
		return InternalError(err)
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
		logs.CtxError(ctx, "failed to start record, err: %v", err)
		return InternalError(err)
	}
	u.r.setRecordTaskID(ctx, taskID)
	go u.r.Inform(ctx, Record, nil)
	return nil
}

func (u *User) UpdateRecord(ctx context.Context, users []string, screen string) error {
	if err := u.checkRoomAndUserState(ctx, true); err != nil {
		return err
	}
	if err := record.UpdateRecord(ctx, users, screen, u.u.AppID, u.u.RoomID, u.r.recordTaskID); err != nil {
		logs.CtxError(ctx, "failed to update record, err: %v", err)
		return InternalError(err)
	}
	return nil
}

func (u *User) MuteUser(ctx context.Context, userID string) error {
	if err := u.checkRoomAndUserState(ctx, true); err != nil {
		return err
	}

	if userID == "" {
		// if public.StringInSlice(u.r.room.RoomID, config.Config.MuteAllError) {
		// 	return ErrMuteAll
		// }

		return u.r.MuteAllWithoutHost(ctx)
	}

	user, err := db.GetActiveUserByRoomIDAndUserID(ctx, u.u.RoomID, userID)
	if err != nil {
		logs.CtxError(ctx, "failed to get user in db, err: %v", err)
		return InternalError(err)
	}
	go NewUser(user, nil).Inform(ctx, MuteUser, UserIDInfo{UserID: user.UserID})
	return nil
}

func (u *User) AskUserDeviceChange(ctx context.Context, userID string, event InformEvent) error {
	if err := u.checkRoomAndUserState(ctx, true); err != nil {
		return err
	}

	if userID == "" {
		return ErrUserIsInactive
	}

	user, err := db.GetActiveUserByRoomIDAndUserID(ctx, u.u.RoomID, userID)
	if err != nil {
		logs.CtxError(ctx, "failed to get user in db, err: %v", err)
		return InternalError(err)
	}
	go NewUser(user, nil).Inform(ctx, event, UserIDInfo{UserID: user.UserID})
	return nil
}

func (u *User) ChangeHost(ctx context.Context, userID string) error {
	if err := u.checkRoomAndUserState(ctx, true); err != nil {
		return err
	}

	user, err := db.GetActiveUserByRoomIDAndUserID(ctx, u.u.RoomID, userID)
	if err != nil {
		logs.CtxError(ctx, "failed to get user in db, err: %v", err)
		// error code 504 returned to the client in a unified manner
		return ErrChangeHost
	}

	u.u.IsHost = false
	user.IsHost = true
	if err := db.BatchUpdateUsers(ctx, u.u, user); err != nil {
		logs.CtxError(ctx, "failed to batch update users in db, err: %v", err)
		return ErrChangeHost
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
		return res, ErrInvalidAppID
	}

	token, err := u.GenerateToken(ctx)
	if err != nil {
		return res, err
	}

	ok, lt := u.r.Lock(ctx)
	if !ok {
		return res, ErrLockRedis
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

	return joinMeetingReturn{
		Token: token,
		Info:  u.r.GetRoomInfo(ctx),
		Users: users,
	}, nil
}

func (u *User) kickSameDeviceUser(ctx context.Context) error {
	user, err := db.GetReconnectingUser(ctx, u.u.DeviceID)
	if err == nil {
		r, err := GetRoom(ctx, user.RoomID)
		if err != nil {
			logs.CtxError(ctx, "failed to get room: %v", err)
			return err
		}
		return NewUser(user, r).Clean(ctx, false)
	}

	if errors.Is(err, gorm.ErrRecordNotFound) {
		logs.CtxInfo(ctx, "no same device user")
		return nil
	}
	return InternalError(err)
}

func (u *User) joinActiveMeeting(ctx context.Context) error {
	logs.CtxInfo(ctx, "join active meeting")
	user, err := db.GetActiveUserByRoomIDAndUserID(ctx, u.u.RoomID, u.u.UserID)
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
	return InternalError(err)
}

func (u *User) checkUserCount(ctx context.Context) error {
	if u.r.GetUserCount(ctx) >= config.Config.RoomUserLimit {
		logs.CtxError(ctx, "user exceed limit")
		return ErrUserExceedLimit
	}
	return nil
}

func (u *User) multiDeviceLogin(ctx context.Context, user *db.ConferenceUser) error {
	logs.CtxInfo(ctx, "multi device user login")
	cleanU, err := GetUser(ctx, user.ConnID)
	if err != nil {
		return InternalError(err)
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
	c, err := GetConnection(ctx, u.u.ConnID)
	if err != nil {
		logs.CtxError(ctx, "failed to get connection, err: %v", err)
		return
	}
	frontier.PushToClient(ctx, c.conn.ConnID, c.conn.Addr, c.conn.Addr6, string(event), response.NewInformToClient(string(event), data), -1)
}

func (u *User) Clean(ctx context.Context, withMeetingOver bool) error {
	if !u.u.IsHost {
		return u.r.KickNormalUser(ctx, u)
	}
	return u.r.KickHost(ctx, u, withMeetingOver)
}

func (u *User) checkRoomAndUserState(ctx context.Context, hostCheck bool) error {
	if u.r.room.State == false {
		logs.CtxWarn(ctx, "room is inactive")
		return ErrRoomIsInactive
	}

	if u.u.State != Active {
		logs.CtxWarn(ctx, "user state is not active")
		return ErrUserIsInactive
	}

	if hostCheck && u.u.IsHost == false {
		logs.CtxWarn(ctx, "user is not host")
		return ErrUserIsNotHost
	}

	return nil
}
