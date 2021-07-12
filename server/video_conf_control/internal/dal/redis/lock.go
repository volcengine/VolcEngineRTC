package redis

import (
	"context"
	"time"

	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/pkg/metrics"
)

const (
	lockTimeout = 1000 // milliseconds
	tryPeriod   = 10 * time.Millisecond
)

func getDistributedLockKey(roomID string) string {
	return "c:vccontrol:roomlock:" + roomID
}

func LockRoom(ctx context.Context, roomID string) (bool, int64) {
	logs.CtxInfo(ctx, "roomID: %s try to lock", roomID)
	return mustGetLock(getDistributedLockKey(roomID), 2*time.Second)
}

func UnLockRoom(ctx context.Context, roomID string, lt int64) error {
	logs.CtxInfo(ctx, "roomID: %s try to unlock", roomID)
	return freeLock(getDistributedLockKey(roomID), lt)
}

// getLock attemps to get and locking a lock. It returns whether the lock is free and the expiring time of the lock.
func getLock(key string) (bool, int64) {
	// lt timestamp microsecond
	lt := time.Now().Add(lockTimeout*time.Millisecond).UnixNano() / 1000
	lock, _ := rc.SetNX(key, lt, lockTimeout*time.Millisecond).Result()
	if lock {
		return true, lt
	}
	return false, 0
}

// mustGetLock tries to get the lock every 10 ms util obtaining the lock or util timeout.
func mustGetLock(key string, timeout time.Duration) (bool, int64) {
	tryTime := timeout / tryPeriod
	for i := 0; i < int(tryTime); i++ {
		l, t := getLock(key)
		if l {
			metrics.EmitCounter(metrics.LockSuccessQps, 1)
			return l, t
		}
		time.Sleep(tryPeriod)
	}
	metrics.EmitCounter(metrics.LockFailedQps, 1)
	return false, 0
}

// freeLock checks whether the lock is expiring. If not, let it be free.
func freeLock(key string, lt int64) error {
	if lt > time.Now().UnixNano()/1000 {
		return rc.Del(key).Err()
	}
	return nil
}
