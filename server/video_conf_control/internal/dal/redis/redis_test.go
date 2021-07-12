package redis

import (
	"context"
	"testing"

	. "github.com/agiledragon/gomonkey"
	"github.com/alicebob/miniredis/v2"
	. "github.com/smartystreets/goconvey/convey"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/pkg/metrics"
)

func TestNewRedis(t *testing.T) {
	Convey("TestNewRedis", t, func() {
		defer ApplyFunc(goredis.NewClientWithOption, func(_ string, _ *goredis.Option) (*goredis.Client, error) {
			return nil, nil
		}).Reset()
		NewRedis("testaddr")
	})
}

func TestRedisOp(t *testing.T) {
	metrics.InitMetrics("testpsm", false)

	s, err := miniredis.Run()
	if err != nil {
		t.Fatal("get redis connection failed!")
	}
	opt := goredis.NewOptionWithTimeout(
		REDIS_DIAL_TIMEOUT,
		REDIS_READ_TIMEOUT,
		REDIS_WRITE_TIMEOUT,
		REDIS_POOL_TIMEOUT,
		REDIS_IDLE_TIMEOUT,
		REDIS_LIVE_TIMEOUT,
		2000)
	opt.MaxRetries = 3
	opt.MinRetryBackoff = -1
	opt.MaxRetryBackoff = -1
	opt.PoolInitSize = 100
	rc, err = goredis.NewClientWithServers("", []string{s.Addr()}, opt)
	if err != nil {
		t.Fatal("get redis connection failed!")
	}

	Convey("TestRedisOp", t, func() {
		ctx := context.Background()
		roomID := "testroom"
		Convey("redis op", func() {
			InitRoomState(ctx, roomID, "")

			SetRoomHost(ctx, roomID, "testhost")
			So(GetRoomHost(ctx, roomID), ShouldEqual, "testhost")

			IncreaseRoomUserCount(ctx, roomID)
			So(GetRoomUserCount(ctx, roomID), ShouldEqual, 1)
			DecreaseRoomUserCount(ctx, roomID)
			So(GetRoomUserCount(ctx, roomID), ShouldEqual, 0)

			SetRoomShareUser(ctx, roomID, "testshare")
			So(GetRoomShareUser(ctx, roomID), ShouldEqual, "testshare")

			SetRoomTaskID(ctx, roomID, "testtaskid")
			So(GetRoomTaskID(ctx, roomID), ShouldEqual, "testtaskid")

			So(GetRoomLastActive(ctx, roomID), ShouldNotEqual, 0)
		})

		Convey("redis lock", func() {
			ok, lt := LockRoom(ctx, roomID)
			So(ok, ShouldEqual, true)

			err := UnLockRoom(ctx, roomID, lt)
			So(err, ShouldEqual, nil)
		})
	})
}
