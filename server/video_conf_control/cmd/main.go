package main

import (
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/config"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/dal/db"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/dal/redis"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/pkg/record"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/pkg/video"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/rpc"
	vc_control "github.com/volcengine/VolcEngineRTC/server/video_conf_control/kitex_gen/vc_control/vccontrol"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/pkg/metrics"
)

func main() {
	metrics.InitMetrics(env.PSM(), true)

	config.ParseConfig()

	db.Open(config.Config.MysqlPSM, config.Config.MysqlDBName)

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
