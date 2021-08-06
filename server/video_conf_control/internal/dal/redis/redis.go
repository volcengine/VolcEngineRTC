package redis

import (
	"time"

	goredis "github.com/go-redis/redis/v8"
)

var (
	DialTimeout     = 500 * time.Millisecond
	ReadTimeout     = 500 * time.Millisecond
	WriteTimeout    = 500 * time.Millisecond
	PoolTimeout     = 500 * time.Millisecond
	IdleTimeout     = 60 * time.Minute
	MinRetryBackoff = 8 * time.Millisecond
	MaxRetryBackoff = 128 * time.Millisecond
)

var Client *goredis.Client

func NewRedis(addr string) {
	Client = goredis.NewClient(&goredis.Options{
		Addr:            addr,
		MaxRetries:      3,
		MinRetryBackoff: MinRetryBackoff,
		MaxRetryBackoff: MaxRetryBackoff,
		PoolSize:        100,
		DialTimeout:     DialTimeout,
		ReadTimeout:     ReadTimeout,
		WriteTimeout:    WriteTimeout,
		PoolTimeout:     PoolTimeout,
		IdleTimeout:     IdleTimeout,
	})
}
