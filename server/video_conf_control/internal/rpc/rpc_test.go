package rpc

import (
	"testing"

	. "github.com/agiledragon/gomonkey"
	. "github.com/smartystreets/goconvey/convey"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/config"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/pkg/metrics"
)

func TestInit(t *testing.T) {
	Convey("TestInit", t, func() {
		metrics.InitMetrics("testpsm", false)
		defer ApplyGlobalVar(&config.Config,
			config.Configuration{
				FrontierPSM: "rtc.frontier.psm",
				VCloudAK:    "vcloudak",
				VCloudSK:    "vcloudsk",
			}).Reset()
		Init()
	})
}
