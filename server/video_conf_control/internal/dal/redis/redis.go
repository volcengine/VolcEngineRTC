package redis

import (
	"time"
)

var (
	REDIS_DIAL_TIMEOUT  = 500 * time.Millisecond
	REDIS_READ_TIMEOUT  = 500 * time.Millisecond
	REDIS_WRITE_TIMEOUT = 500 * time.Millisecond
	REDIS_POOL_TIMEOUT  = 500 * time.Millisecond
	REDIS_IDLE_TIMEOUT  = 60 * time.Minute
	REDIS_LIVE_TIMEOUT  = 60 * time.Minute
)

var rc *goredis.Client

// NewRedis creates a new client with addr use the default timeout settings.
func NewRedis(addr string) {
	var err error
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
	rc, err = goredis.NewClientWithOption(addr, opt)
	if err != nil {
		panic(err)
	}
}
