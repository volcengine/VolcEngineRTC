package cs_models

import (
	"context"
	"errors"
	"gorm.io/gorm"
	"math"
	"sort"
	"strconv"
	"strings"
	"time"

	goredis "github.com/go-redis/redis/v8"
	logs "github.com/sirupsen/logrus"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/dal/db"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/dal/db/conn_db"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/dal/db/cs_db"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/dal/redis/cs_redis"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/dal/redis/lock"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/models/custom_error"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/pkg/response"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/rpc/frontier"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/pkg/public"
)

const (
	roomLength = 8
)

type Room struct {
	room *db.CsMeetingRoom
}

func NewRoom(appID, roomID, roomName string) *Room {
	return &Room{
		room: &db.CsMeetingRoom{
			AppID:     appID,
			RoomID:    roomID,
			RoomName:  roomName,
			State:     true,
			CreatedAt: time.Now(),
		},
	}
}

func GetRoom(ctx context.Context, roomID string) (*Room, error) {
	r, err := cs_db.GetRoom(ctx, roomID)
	if errors.Is(err, gorm.ErrRecordNotFound) {
		logs.Warnf("room not exist")
		return nil, custom_error.ErrRoomNotExist
	}

	if err != nil {
		logs.Errorf("failed to get room in db, err: %v", err)
		return nil, custom_error.InternalError(err)
	}

	return &Room{
		room: r,
	}, nil
}

func GetActiveRooms(ctx context.Context) ([]*db.CsMeetingRoom, error) {
	rooms, err := cs_db.GetActiveRooms(ctx)
	if err != nil && !errors.Is(err, gorm.ErrRecordNotFound) {
		logs.Errorf("failed to get rooms in db, err: %v", err)
		return nil, custom_error.InternalError(err)
	}

	if errors.Is(err, gorm.ErrRecordNotFound) {
		logs.Warn("room not exist")
		return nil, custom_error.ErrRoomNotExist
	}

	cleanedRoomIDs := make([]string, 0)
	activeRooms := make([]*db.CsMeetingRoom, 0)

	for _, room := range rooms {
		if time.Now().Sub(room.CreatedAt) > cs_redis.RoomExpiration {
			cleanedRoomIDs = append(cleanedRoomIDs, room.RoomID)
			continue
		}

		activeRooms = append(activeRooms, room)
	}

	if len(cleanedRoomIDs) > 0 {
		go func() {
			defer public.CheckPanic()

			for _, roomID := range cleanedRoomIDs {
				err := cs_db.CleanRoom(ctx, roomID)
				if err != nil {
					logs.Warnf("failed to clean room in db, err: %v", err)
				}
			}
		}()
	}

	if len(activeRooms) == 0 {
		logs.Warnf("active room not exist")
		return nil, custom_error.ErrRoomNotExist
	}

	return activeRooms, nil
}

func GenerateRoomID(ctx context.Context) (int64, error) {
	ok, lt := lock.LockCsRoomIDAssign(ctx)
	if !ok {
		return 0, custom_error.ErrLockRedis
	}

	defer lock.UnLockCsRoomIDAssign(ctx, lt)

	roomID, err := cs_redis.GetAssignedRoomID()
	if err != nil && !errors.Is(err, goredis.Nil) {
		return 0, custom_error.InternalError(err)
	}

	baseline := int64(math.Pow10(roomLength))
	minRoomID := int64(math.Pow10(roomLength - 1))

	if roomID == 0 {
		roomID = time.Now().Unix() % baseline
	} else {
		roomID = (roomID + 1) % baseline
	}

	if roomID < minRoomID {
		roomID += minRoomID
	}

	cs_redis.SetAssignedRoomID(roomID)

	_, err = cs_db.GetRoom(ctx, strconv.FormatInt(roomID, 10))
	if errors.Is(err, gorm.ErrRecordNotFound) {
		return roomID, nil
	}

	if err != nil {
		return 0, custom_error.InternalError(err)
	}

	return 0, custom_error.ErrRoomAlreadyExist
}

func RoomExist(ctx context.Context, roomID string) (bool, error) {
	_, err := cs_db.GetRoom(ctx, roomID)
	if err == nil {
		return true, nil
	}

	if errors.Is(err, gorm.ErrRecordNotFound) {
		return false, nil
	}

	return false, custom_error.InternalError(err)
}

func (r *Room) Lock(ctx context.Context) (bool, int64) {
	return lock.LockCsRoom(ctx, r.room.RoomID)
}

func (r *Room) UnLock(ctx context.Context, lt int64) error {
	return lock.UnLockCsRoom(ctx, r.room.RoomID, lt)
}

func (r *Room) GenerateInformRoomInfo(ctx context.Context) *RoomInfo {
	roomID := r.room.RoomID

	userCounts := cs_redis.GetRoomUserCount(ctx, roomID)
	if userCounts <= 0 {
		userCounts, _ = cs_db.GetRoomUserCount(ctx, roomID)
		cs_redis.SetRoomUserCount(ctx, roomID, userCounts)
	}

	miconCounts := cs_redis.GetRoomUserOnMicrophone(ctx, roomID)
	if miconCounts <= 0 {
		miconCounts, _ = cs_db.GetRoomUserOnMicrophone(ctx, roomID)
		cs_redis.SetRoomUserOnMicrophone(ctx, roomID, miconCounts)
	}

	return &RoomInfo{
		RoomID:      roomID,
		RoomName:    r.room.RoomName,
		HostID:      cs_redis.GetRoomHostID(ctx, roomID),
		HostName:    cs_redis.GetRoomHostName(ctx, roomID),
		UserCounts:  userCounts,
		MiconCounts: miconCounts,
		CreatedAt:   cs_redis.GetRoomLastActive(ctx, roomID),
		Now:         time.Now().UnixNano(),
	}
}

func (r *Room) ListUsers(ctx context.Context) ([]*UserInfo, error) {
	users, err := cs_db.GetUsersByRoomID(ctx, r.room.RoomID, db.ACTIVE, db.RECONNECTING)
	if err != nil {
		logs.Infof("failed to get users in room, roomID: %s, err: %v", r.room.RoomID, err)
		return nil, custom_error.InternalError(err)
	}

	var res UserInfoSlice
	var host *UserInfo

	for _, u := range users {
		uinfo := NewUser(u, r).GenerateInformUserInfo()
		if u.IsHost {
			host = uinfo
			continue
		}
		res = append(res, uinfo)
	}
	sort.Sort(res)
	return append([]*UserInfo{host}, res...), nil
}

func (r *Room) ListUsersWithJoinMeetingTime(ctx context.Context) ([]*UserInfo, error) {
	users, err := cs_db.GetUsersByRoomID(ctx, r.room.RoomID, db.ACTIVE, db.RECONNECTING)
	if err != nil && !errors.Is(err, gorm.ErrRecordNotFound) {
		logs.Infof("failed to get users in room, roomID: %s, err: %v", r.room.RoomID, err)
		return nil, custom_error.InternalError(err)
	}

	if errors.Is(err, gorm.ErrRecordNotFound) {
		logs.Warnf("no users in room, roomID: %s, err: %v", r.room.RoomID, err)
		return make([]*UserInfo, 0), nil
	}

	var res UserInfoJoinMeetingSlice
	var host *UserInfo

	for _, u := range users {
		uinfo := NewUser(u, r).GenerateInformUserInfo()
		if u.IsHost {
			host = uinfo
			continue
		}
		res = append(res, uinfo)
	}
	sort.Sort(res)
	return append([]*UserInfo{host}, res...), nil
}

func (r *Room) ListRaiseHandsUsers(ctx context.Context) ([]*UserInfo, error) {
	users, err := cs_db.GetRaiseHandsUsersByRoomID(ctx, r.room.RoomID, db.ACTIVE, db.RECONNECTING)
	if err != nil && !errors.Is(err, gorm.ErrRecordNotFound) {
		logs.Infof("failed to get raise hands users in room, roomID: %s, err: %v", r.room.RoomID, err)
		return nil, custom_error.InternalError(err)
	}

	res := make(UserInfoRaiseHandsSlice, 0)
	if errors.Is(err, gorm.ErrRecordNotFound) {
		return res, nil
	}

	for _, u := range users {
		uinfo := NewUser(u, r).GenerateInformUserInfo()
		res = append(res, uinfo)
	}
	sort.Sort(res)
	return res, nil
}

func (r *Room) ListAudiences(ctx context.Context) ([]*UserInfo, error) {
	users, err := cs_db.GetAudiencesByRoomID(ctx, r.room.RoomID, db.ACTIVE, db.RECONNECTING)
	if err != nil && !errors.Is(err, gorm.ErrRecordNotFound) {
		logs.Infof("failed to get audiences in room, roomID: %s, err: %v", r.room.RoomID, err)
		return nil, custom_error.InternalError(err)
	}

	res := make(UserInfoSlice, 0)
	if errors.Is(err, gorm.ErrRecordNotFound) {
		return res, nil
	}

	for _, u := range users {
		uinfo := NewUser(u, r).GenerateInformUserInfo()
		res = append(res, uinfo)
	}

	sort.Sort(res)
	return res, nil
}

func (r *Room) GetUserCount(ctx context.Context) int {
	return cs_redis.GetRoomUserCount(ctx, r.room.RoomID)
}

func (r *Room) setUserCount(ctx context.Context, count int) {
	cs_redis.SetRoomUserCount(ctx, r.room.RoomID, count)
}

func (r *Room) IncreaseUserCount(ctx context.Context) {
	cs_redis.IncreaseRoomUserCount(ctx, r.room.RoomID)
}

func (r *Room) DecreaseUserCount(ctx context.Context) {
	cs_redis.DecreaseRoomUserCount(ctx, r.room.RoomID)
}

func (r *Room) exist(ctx context.Context) (bool, error) {
	_, err := cs_db.GetRoom(ctx, r.room.RoomID)
	if err == nil {
		return true, nil
	}
	if errors.Is(err, gorm.ErrRecordNotFound) {
		return false, custom_error.ErrRoomNotExist
	}
	return false, custom_error.InternalError(err)
}

func (r *Room) create(ctx context.Context, user *User) error {
	user.u.IsHost = true
	user.u.UserStatus = int(db.UserStatusOnMicrophone)
	user.u.IsMicOn = true

	if err := cs_db.BatchCreateRoomUser(ctx, r.room, user.u); err != nil {
		return custom_error.InternalError(err)
	}

	cs_redis.InitRoomState(ctx, r.room.RoomID, user.u.UserID, user.u.UserName)

	return nil
}

func (r *Room) AddUser(ctx context.Context, user *User) error {
	user.u.IsHost = false
	user.u.UserStatus = int(db.UserStatusAudience)
	user.u.IsMicOn = false

	if err := cs_db.CreateOrUpdateUser(ctx, user.u); err != nil {
		return custom_error.InternalError(err)
	}

	cs_redis.IncreaseRoomUserCount(ctx, r.room.RoomID)

	return nil
}

func (r *Room) Inform(ctx context.Context, event InformEvent, data interface{}) {
	connIDMap := make(map[string][]string) // addr-addr6: []connIDs
	users, err := cs_db.GetUsersByRoomID(ctx, r.room.RoomID, db.ACTIVE)
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
