package vc_models

import (
	"context"
	"errors"
	"sort"
	"strings"
	"time"

	logs "github.com/sirupsen/logrus"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/config"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/dal/db"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/dal/db/conn_db"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/dal/db/vc_db"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/dal/redis/lock"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/dal/redis/vc_redis"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/models/custom_error"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/pkg/record"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/pkg/response"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/rpc/frontier"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/pkg/public"
	"gorm.io/gorm"
)

type Room struct {
	room         *db.MeetingRoom
	shareUser    string
	host         string
	recordTaskID string
	start        int64
}

type MeetingInfo struct {
	RoomID          string `json:"room_id"`
	HostID          string `json:"host_id"`
	Record          bool   `json:"record"`
	ScreenSharedUID string `json:"screen_shared_uid"`
	CreatedAt       int64  `json:"created_at"`
	Now             int64  `json:"now"`
}

func NewRoom(appID, roomID string) *Room {
	return &Room{
		room: &db.MeetingRoom{
			AppID:  appID,
			RoomID: roomID,
			State:  true,
		},
	}
}

func GetRoom(ctx context.Context, roomID string) (*Room, error) {
	r, err := vc_db.GetRoom(ctx, roomID)
	if err != nil {
		logs.Errorf("failed to get room in db, err: %v", err)
		return nil, custom_error.InternalError(err)
	}

	return &Room{
		room:         r,
		shareUser:    vc_redis.GetRoomShareUser(ctx, roomID),
		host:         vc_redis.GetRoomHost(ctx, roomID),
		recordTaskID: vc_redis.GetRoomTaskID(ctx, roomID),
		start:        vc_redis.GetRoomLastActive(ctx, roomID),
	}, nil
}

func (r *Room) Lock(ctx context.Context) (bool, int64) {
	return lock.LockRoom(ctx, r.room.RoomID)
}

func (r *Room) UnLock(ctx context.Context, lt int64) error {
	return lock.UnLockRoom(ctx, r.room.RoomID, lt)
}

func (r *Room) setShareUser(ctx context.Context, userID string) {
	r.shareUser = userID
	vc_redis.SetRoomShareUser(ctx, r.room.RoomID, userID)
}

func (r *Room) setHost(ctx context.Context, host string) {
	r.host = host
	vc_redis.SetRoomHost(ctx, r.room.RoomID, host)
}

func (r *Room) setRecordTaskID(ctx context.Context, taskID string) {
	r.recordTaskID = taskID
	vc_redis.SetRoomTaskID(ctx, r.room.RoomID, taskID)
}

func (r *Room) setStartTime(ctx context.Context) {
	r.start = time.Now().UnixNano()
	vc_redis.SetRoomLastActive(ctx, r.room.RoomID, r.start)
}

func (r *Room) GetRoomInfo(ctx context.Context) MeetingInfo {
	rid := r.room.RoomID
	return MeetingInfo{
		RoomID:          rid,
		HostID:          vc_redis.GetRoomHost(ctx, rid),
		Record:          vc_redis.GetRoomTaskID(ctx, rid) != "",
		ScreenSharedUID: vc_redis.GetRoomShareUser(ctx, rid),
		CreatedAt:       vc_redis.GetRoomLastActive(ctx, rid),
		Now:             time.Now().UnixNano(),
	}
}

func (r *Room) ListUsers(ctx context.Context) ([]UserInfo, error) {
	users, err := vc_db.GetUsersByRoomID(ctx, r.room.RoomID, Active, Reconnecting)
	if err != nil {
		logs.Infof("failed to get users in room, roomID: %s, err: %v", r.room.RoomID, err)
		return nil, custom_error.InternalError(err)
	}

	var res UserInfoSlice
	var host UserInfo

	for _, u := range users {
		uinfo := NewUser(u, r).GenerateInformUserInfo()
		if u.IsHost {
			host = uinfo
			continue
		}
		res = append(res, uinfo)
	}
	sort.Sort(res)
	return append([]UserInfo{host}, res...), nil
}

func (r *Room) stopRecord(ctx context.Context) error {
	if err := record.StopRecord(ctx, r.room.AppID, r.room.RoomID, r.recordTaskID); err != nil {
		logs.Errorf("failed to stop record, err: %v", err)
		return custom_error.InternalError(err)
	}
	r.setRecordTaskID(ctx, "")
	return nil
}

func (r *Room) MuteAllWithoutHost(ctx context.Context) error {
	if err := vc_db.MuteAllUsersWithoutHost(ctx, r.room.RoomID); err != nil {
		logs.Errorf("failed to mute all users, err: %v", err)
		// 静音全体失败返回给客户端特殊的错误码
		return custom_error.ErrMuteAll
	}

	go r.Inform(ctx, MuteAll, nil)
	return nil
}

func (r *Room) GetUserCount(ctx context.Context) int {
	return vc_redis.GetRoomUserCount(ctx, r.room.RoomID)
}

func (r *Room) setUserCount(ctx context.Context, count int) {
	vc_redis.SetRoomUserCount(ctx, r.room.RoomID, count)
}

func (r *Room) IncreaseUserCount(ctx context.Context) {
	vc_redis.IncreaseRoomUserCount(ctx, r.room.RoomID)
}

func (r *Room) DecreaseUserCount(ctx context.Context) {
	vc_redis.DecreaseRoomUserCount(ctx, r.room.RoomID)
}

func (r *Room) End(ctx context.Context) error {
	r.Inform(ctx, MeetingEnd, nil)
	if err := vc_db.CleanRoom(ctx, r.room.RoomID); err != nil {
		logs.Errorf("failed to clean room, err: %v", err)
		return custom_error.InternalError(err)
	}
	if r.recordTaskID != "" {
		go func() {
			logs.Infof("try to stop record, err: %v", r.stopRecord(ctx))
		}()
	}
	vc_redis.InitRoomState(ctx, r.room.RoomID, "")
	return nil
}

func (r *Room) exist(ctx context.Context) (bool, error) {
	_, err := vc_db.GetRoom(ctx, r.room.RoomID)
	if err == nil {
		return true, nil
	}
	if errors.Is(err, gorm.ErrRecordNotFound) {
		return false, nil
	}
	return false, custom_error.InternalError(err)
}

func (r *Room) create(ctx context.Context, user *User) error {
	user.u.IsHost = true
	if err := vc_db.BatchCreateRoomUser(ctx, r.room, user.u); err != nil {
		return custom_error.InternalError(err)
	}
	vc_redis.InitRoomState(ctx, r.room.RoomID, user.u.UserID)
	vc_redis.IncreaseRoomUserCount(ctx, r.room.RoomID)
	if !public.StringInSlice(r.room.RoomID, config.Config.RoomWhiteList) {
		go func() {
			time.Sleep(time.Duration(config.Config.RoomDurationMinute) * time.Minute)
			if _, err := vc_db.GetRoom(ctx, r.room.RoomID); err == nil {
				r.End(ctx)
			}
		}()
	}
	return nil
}

func (r *Room) AddUser(ctx context.Context, user *User) error {
	if err := vc_db.CreateOrUpdateUser(ctx, user.u); err != nil {
		return custom_error.InternalError(err)
	}

	vc_redis.IncreaseRoomUserCount(ctx, r.room.RoomID)
	return nil
}

func (r *Room) Inform(ctx context.Context, event InformEvent, data interface{}) {
	connIDMap := make(map[string][]string) // addr-addr6: []connIDs
	users, err := vc_db.GetUsersByRoomID(ctx, r.room.RoomID, Active)
	if err != nil {
		logs.Infof("failed to get users in room, roomID: %s, err: %v", r.room.RoomID, err)
		return
	}

	connIDs := make([]string, 0)
	for _, user := range users {
		connIDs = append(connIDs, user.ConnID)
	}

	conns, err := conn_db.GetConnections(ctx, connIDs)
	if err != nil {
		logs.Infof("failed to get conns, connIDs: %v, err: %v", connIDs, err)
		return
	}

	for _, conn := range conns {
		address := strings.Join([]string{conn.Addr, conn.Addr6}, "-")
		connIDMap[address] = append(connIDMap[address], conn.ConnID)
	}

	for address, connIDList := range connIDMap {
		addr := strings.Split(address, "-")
		go frontier.BroadcastToClient(ctx, connIDList, addr[0], addr[1], string(event), response.NewInformToClient(string(event), data), -1)
	}
}

func (r *Room) KickNormalUser(ctx context.Context, u *User) error {
	u.u.State = Inactive
	shareInform := u.u.IsSharing == true
	if u.u.IsSharing {
		u.u.IsSharing = false
		u.r.setShareUser(ctx, "")
	}
	if err := vc_db.BatchUpdateUsers(ctx, u.u); err != nil {
		return custom_error.InternalError(err)
	}

	if shareInform {
		go r.Inform(ctx, ShareScreenStatusChanged, UserDeviceInfo{UserID: u.u.UserID, Status: false})
	}

	go r.Inform(ctx, UserLeaveMeeting, UserIDInfo{UserID: u.u.UserID})
	go u.Inform(ctx, UserKickedOff, nil)

	vc_redis.DecreaseRoomUserCount(ctx, u.u.RoomID)
	return nil
}

func (r *Room) KickHost(ctx context.Context, u *User, withMeetingOver bool) error {
	nextHost, err := vc_db.GetNextHost(ctx, u.u)
	if err == nil {
		u.u.State = Inactive
		u.u.IsHost = false
		nextHost.IsHost = true

		shareInform := u.u.IsSharing == true
		if u.u.IsSharing {
			r.setShareUser(ctx, "")
			u.u.IsSharing = false
		}

		if err := vc_db.BatchUpdateUsers(ctx, u.u, nextHost); err != nil {
			return custom_error.InternalError(err)
		}

		if shareInform {
			go r.Inform(ctx, ShareScreenStatusChanged, UserDeviceInfo{UserID: u.u.UserID, Status: false})
		}

		go func() {
			r.Inform(ctx, UserLeaveMeeting, UserIDInfo{UserID: u.u.UserID})
			u.Inform(ctx, UserKickedOff, nil)
			r.Inform(ctx, HostChange, HostInfo{FormerHostID: u.u.UserID, HostID: nextHost.UserID})
		}()

		vc_redis.DecreaseRoomUserCount(ctx, u.u.RoomID)
		r.setHost(ctx, nextHost.UserID)
		return nil
	}

	// 没有下一个主持人的时候，意味着该用户是房间内最后一个用户
	if errors.Is(err, gorm.ErrRecordNotFound) {
		if withMeetingOver {
			return u.r.End(ctx)
		}
		u.u.IsHost = false
		r.setHost(ctx, "")
		return r.KickNormalUser(ctx, u)
	}

	return custom_error.InternalError(err)
}
