package vc_redis

import (
	"context"
	"time"

	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/dal/redis"
)

const (
	TaskIDKeyPrefix = "c:vccontrol:taskid:"

	taskIDKeyExpire = 24 * time.Hour
)

func GetUserIDByTaskID(ctx context.Context, taskID string) string {
	userID := redis.Client.Get(ctx, TaskIDKeyPrefix + taskID).Val()
	return userID
}

func SetTaskIDWithUserID(ctx context.Context, taskID, userID string) {
	redis.Client.Set(ctx, TaskIDKeyPrefix+taskID, userID, taskIDKeyExpire)
}
