package vc_redis

import (
	"context"
	"strconv"
	"time"

	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/dal/redis"
)

const (
	count        = "count"
	host         = "host"
	shareUser    = "share_user"
	lastActive   = "last_active"
	recordTaskID = "record_task_id"
	roomStatus   = "room_status"
)

func redisKeyRoom(roomID string) string {
	return "c:vccontrol:" + roomID
}

func InitRoomState(ctx context.Context, roomID, hostID string) {
	key := redisKeyRoom(roomID)
	redis.Client.Expire(ctx, key, 24*time.Hour) // 过期时间设置为24h

	redis.Client.HSet(ctx, key, count, 0)
	redis.Client.HSet(ctx, key, host, hostID)
	redis.Client.HSet(ctx, key, shareUser, "")
	redis.Client.HSet(ctx, key, recordTaskID, "")
	redis.Client.HSet(ctx, key, lastActive, time.Now().UnixNano())
}

func GetRoomLastActive(ctx context.Context, roomID string) int64 {
	r := redis.Client.HGet(ctx, redisKeyRoom(roomID), lastActive).Val()
	res, _ := strconv.ParseInt(r, 10, 64)
	return res
}

func SetRoomLastActive(ctx context.Context, roomID string, start int64) {
	redis.Client.HSet(ctx, redisKeyRoom(roomID), lastActive, start)
}

// user count
func GetRoomUserCount(ctx context.Context, roomID string) int {
	r := redis.Client.HGet(ctx, redisKeyRoom(roomID), count).Val()
	res, _ := strconv.Atoi(r)
	return res
}

func IncreaseRoomUserCount(ctx context.Context, roomID string) {
	redis.Client.HIncrBy(ctx, redisKeyRoom(roomID), count, 1)
}

func DecreaseRoomUserCount(ctx context.Context, roomID string) {
	redis.Client.HIncrBy(ctx, redisKeyRoom(roomID), count, -1)
}

func SetRoomUserCount(ctx context.Context, roomID string, num int) {
	redis.Client.HSet(ctx, redisKeyRoom(roomID), count, num)
}

// share
func GetRoomShareUser(ctx context.Context, roomID string) string {
	r := redis.Client.HGet(ctx, redisKeyRoom(roomID), shareUser).Val()
	return r
}

func SetRoomShareUser(ctx context.Context, roomID, userID string) {
	redis.Client.HSet(ctx, redisKeyRoom(roomID), shareUser, userID)
}

// host
func GetRoomHost(ctx context.Context, roomID string) string {
	r := redis.Client.HGet(ctx, redisKeyRoom(roomID), host).Val()
	return r
}

func SetRoomHost(ctx context.Context, roomID, hostID string) {
	redis.Client.HSet(ctx, redisKeyRoom(roomID), host, hostID)
}

// record
func GetRoomTaskID(ctx context.Context, roomID string) string {
	r := redis.Client.HGet(ctx, redisKeyRoom(roomID), recordTaskID).Val()
	return r
}

func SetRoomTaskID(ctx context.Context, roomID, taskID string) {
	redis.Client.HSet(ctx, redisKeyRoom(roomID), recordTaskID, taskID)
}
