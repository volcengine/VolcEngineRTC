package cs_redis

import (
	"context"
	"strconv"
	"time"

	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/dal/redis"
)

const (
	fieldCount        = "count"
	fieldOnMicrophone = "on_microphone"
	fieldHostID       = "host_id"
	fieldHostName     = "host_name"
	fieldLastActive   = "last_active"
	keyAssignedRoomID = "cs:vccontrol:assigned:roomid"
	RoomExpiration    = 24 * time.Hour
)

func redisKeyRoom(roomID string) string {
	return "cs:vccontrol:" + roomID
}

func InitRoomState(ctx context.Context, roomID, hostID, hostName string) {
	key := redisKeyRoom(roomID)

	redis.Client.Expire(ctx, key, RoomExpiration)
	redis.Client.HSet(ctx,key, fieldCount, 1)
	redis.Client.HSet(ctx,key, fieldOnMicrophone, 1)
	redis.Client.HSet(ctx,key, fieldHostID, hostID)
	redis.Client.HSet(ctx,key, fieldHostName, hostName)
	redis.Client.HSet(ctx,key, fieldLastActive, time.Now().UnixNano())
}

func DeleteRoomState(ctx context.Context, roomID string) {
	key := redisKeyRoom(roomID)
	redis.Client.Del(ctx, key)
}

func GetRoomLastActive(ctx context.Context, roomID string) int64 {
	r := redis.Client.HGet(ctx,redisKeyRoom(roomID), fieldLastActive).Val()

	res, _ := strconv.ParseInt(r, 10, 64)

	return res
}

func SetRoomLastActive(ctx context.Context, roomID string, start int64) {
	redis.Client.HSet(ctx,redisKeyRoom(roomID), fieldLastActive, start)
}

func GetRoomUserCount(ctx context.Context, roomID string) int {
	r := redis.Client.HGet(ctx,redisKeyRoom(roomID), fieldCount).Val()
	res, _ := strconv.Atoi(r)
	return res
}

func IncreaseRoomUserCount(ctx context.Context, roomID string) {
	redis.Client.HIncrBy(ctx,redisKeyRoom(roomID), fieldCount, 1)
}

func DecreaseRoomUserCount(ctx context.Context, roomID string) {
	redis.Client.HIncrBy(ctx,redisKeyRoom(roomID), fieldCount, -1)
}

func SetRoomUserCount(ctx context.Context, roomID string, num int) {
	redis.Client.HSet(ctx,redisKeyRoom(roomID), fieldCount, num)
}

func GetRoomUserOnMicrophone(ctx context.Context, roomID string) int {
	r := redis.Client.HGet(ctx,redisKeyRoom(roomID), fieldOnMicrophone).Val()
	res, _ := strconv.Atoi(r)
	return res
}

func IncreaseRoomUserOnMicrophone(ctx context.Context, roomID string) {
	redis.Client.HIncrBy(ctx,redisKeyRoom(roomID), fieldOnMicrophone, 1)
}

func DecreaseRoomUserOnMicrophone(ctx context.Context, roomID string) {
	redis.Client.HIncrBy(ctx,redisKeyRoom(roomID), fieldOnMicrophone, -1)
}

func SetRoomUserOnMicrophone(ctx context.Context, roomID string, num int) {
	redis.Client.HSet(ctx,redisKeyRoom(roomID), fieldOnMicrophone, num)
}

func GetRoomHostID(ctx context.Context, roomID string) string {
	r := redis.Client.HGet(ctx,redisKeyRoom(roomID), fieldHostID).Val()
	return r
}

func SetRoomHostID(ctx context.Context, roomID, hostID string) {
	redis.Client.HSet(ctx,redisKeyRoom(roomID), fieldHostID, hostID)
}

func SetRoomHostName(ctx context.Context, roomID, hostName string) {
	redis.Client.HSet(ctx,redisKeyRoom(roomID), fieldHostName, hostName)
}

func GetRoomHostName(ctx context.Context, roomID string) string {
	r := redis.Client.HGet(ctx,redisKeyRoom(roomID), fieldHostName).Val()
	return r
}

func SetAssignedRoomID(roomID int64) {
	ctx := context.Background()
	redis.Client.Set(ctx,keyAssignedRoomID, roomID, 0)
}

func DelAssignedRoomID() {
	ctx := context.Background()
	redis.Client.Del(ctx,keyAssignedRoomID)
}

func GetAssignedRoomID() (int64, error) {
	ctx := context.Background()
	return redis.Client.Get(ctx, keyAssignedRoomID).Int64()
}
