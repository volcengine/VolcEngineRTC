package lock

import (
	"context"
	"time"

	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/dal/redis"
)

const (
	lockTimeout      = 1000 // milliseconds
	tryPeriod        = 10 * time.Millisecond
	csLockExpiration = 2 * time.Second
)

const (
	csRoomAssignKey        = "cs:vccontrol:room:assign"
	csRoomLockKeyPrefix    = "cs:vccontrol:room:lock:"
	csLocalUserIDAssignKey = "cs:vccontrol:local:userid:assign"
)

func getDistributedLockKey(roomID string) string {
	return "c:vccontrol:roomlock:" + roomID
}

func LockRoom(ctx context.Context, roomID string) (bool, int64) {
	return mustGetLock(getDistributedLockKey(roomID), 2*time.Second)
}

func UnLockRoom(ctx context.Context, roomID string, lt int64) error {
	return freeLock(getDistributedLockKey(roomID), lt)
}

func LockCsRoom(_ context.Context, roomID string) (bool, int64) {
	return mustGetLock(csRoomLockKeyPrefix+roomID, 2*time.Second)
}

func UnLockCsRoom(_ context.Context, roomID string, lt int64) error {
	return freeLock(csRoomLockKeyPrefix+roomID, lt)
}

func LockCsRoomIDAssign(_ context.Context) (bool, int64) {
	return mustGetLock(csRoomAssignKey, csLockExpiration)
}

func UnLockCsRoomIDAssign(_ context.Context, lt int64) error {
	return freeLock(csRoomAssignKey, lt)
}

func LockLocalUserIDAssign(_ context.Context) (bool, int64) {
	return mustGetLock(csLocalUserIDAssignKey, csLockExpiration)
}

func UnLockLocalUserIDAssign(_ context.Context, lt int64) error {
	return freeLock(csLocalUserIDAssignKey, lt)
}

// getLock attemps to get and locking a lock. It returns whether the lock is free and the expiring time of the lock.
func getLock(key string) (bool, int64) {
	// lt timestamp microsecond
	lt := time.Now().Add(lockTimeout*time.Millisecond).UnixNano() / 1000
	lock, _ := redis.Client.SetNX(context.Background(), key, lt, lockTimeout*time.Millisecond).Result()
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
			return l, t
		}
		time.Sleep(tryPeriod)
	}
	return false, 0
}

// freeLock checks whether the lock is expiring. If not, let it be free.
func freeLock(key string, lt int64) error {
	if lt > time.Now().UnixNano()/1000 {
		return redis.Client.Del(context.Background(), key).Err()
	}
	return nil
}
