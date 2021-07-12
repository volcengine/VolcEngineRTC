package redis

import (
	"context"
	"strconv"
	"time"
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

// InitRoomState creates a new key holding a hash with passed roomID and hostID.
func InitRoomState(ctx context.Context, roomID, hostID string) {
	logs.CtxInfo(ctx, "redis init roomID: %s", roomID)
	key := redisKeyRoom(roomID)
	rc.Expire(key, 24*time.Hour) // The expiration time is set to 24h

	rc.HSet(key, count, 0)
	rc.HSet(key, host, hostID)
	rc.HSet(key, shareUser, "")
	rc.HSet(key, recordTaskID, "")
	rc.HSet(key, lastActive, time.Now().UnixNano())
}

func GetRoomLastActive(ctx context.Context, roomID string) int64 {
	r := rc.HGet(redisKeyRoom(roomID), lastActive).Val()
	logs.CtxInfo(ctx, "get room record last active, roomID: %s, res: %s", roomID, r)

	res, _ := strconv.ParseInt(r, 10, 64)

	return res
}

func SetRoomLastActive(ctx context.Context, roomID string, start int64) {
	logs.CtxInfo(ctx, "set room record last active, roomID: %s, start: %v", roomID, start)
	rc.HSet(redisKeyRoom(roomID), lastActive, start)
}

// GetRoomUserCount returns user count with passed roomID.
func GetRoomUserCount(ctx context.Context, roomID string) int {
	r := rc.HGet(redisKeyRoom(roomID), count).Val()
	logs.CtxInfo(ctx, "get room use count, roomID: %s, res: %s", roomID, r)
	res, _ := strconv.Atoi(r)
	return res
}

func IncreaseRoomUserCount(ctx context.Context, roomID string) {
	logs.CtxInfo(ctx, "redis increase user, roomID: %s", roomID)
	rc.HIncrBy(redisKeyRoom(roomID), count, 1)
}

func DecreaseRoomUserCount(ctx context.Context, roomID string) {
	logs.CtxInfo(ctx, "redis decrease user, roomID: %s", roomID)
	rc.HIncrBy(redisKeyRoom(roomID), count, -1)
}

func SetRoomUserCount(ctx context.Context, roomID string, num int) {
	logs.CtxInfo(ctx, "redis set user count, roomID: %s, count: %v", roomID, num)
	rc.HSet(redisKeyRoom(roomID), count, num)
}

// GetRoomShareUser returns share userID with passed roomID.
func GetRoomShareUser(ctx context.Context, roomID string) string {
	r := rc.HGet(redisKeyRoom(roomID), shareUser).Val()
	logs.CtxInfo(ctx, "get room share userID, roomID: %s, res: %s", roomID, r)

	return r
}

func SetRoomShareUser(ctx context.Context, roomID, userID string) {
	logs.CtxInfo(ctx, "redis set room share userID, roomID: %s, userID: %s", roomID, userID)
	rc.HSet(redisKeyRoom(roomID), shareUser, userID)
}

// GetRoomHost returns hostID with passed roomID.
func GetRoomHost(ctx context.Context, roomID string) string {
	r := rc.HGet(redisKeyRoom(roomID), host).Val()

	logs.CtxInfo(ctx, "get room host, roomID: %s, res: %s", roomID, r)
	return r
}

func SetRoomHost(ctx context.Context, roomID, hostID string) {
	logs.CtxInfo(ctx, "redis set host, roomID: %s, hostID: %s", roomID, hostID)
	rc.HSet(redisKeyRoom(roomID), host, hostID)
}

// GetRoomTaskID returns record taskID with passed roomID.
func GetRoomTaskID(ctx context.Context, roomID string) string {
	r := rc.HGet(redisKeyRoom(roomID), recordTaskID).Val()
	logs.CtxInfo(ctx, "get room record taskID, roomID: %s, res: %s", roomID, r)

	return r
}

func SetRoomTaskID(ctx context.Context, roomID, taskID string) {
	logs.CtxInfo(ctx, "set room record taskID, roomID: %s, taskID: %s", roomID, taskID)
	rc.HSet(redisKeyRoom(roomID), recordTaskID, taskID)
}
