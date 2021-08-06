package main

import (
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/config"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/dal/db"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/dal/redis"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/pkg/record"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/pkg/video"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/rpc"
	vc_control "github.com/volcengine/VolcEngineRTC/server/video_conf_control/kitex_gen/vc_control/vccontrol"
)

func main() {
	config.ParseConfig()
	db.Open(config.Config.MysqlDSN)
	redis.NewRedis(config.Config.RedisAddr)
	rpc.Init()
	record.Init()
	video.Init()

	svr := vc_control.NewServer(NewVCControlImpl())
	err := svr.Run()
	if err != nil {
		panic(err)
	}
}
