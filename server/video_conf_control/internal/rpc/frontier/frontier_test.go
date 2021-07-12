package frontier

import (
	"context"
	"errors"
	"testing"

	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/config"
	mock "github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/rpc/mock/frontiermock"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/kitex_gen/rtc_frontier"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/pkg/metrics"

	. "github.com/agiledragon/gomonkey"
	"github.com/golang/mock/gomock"
	"github.com/prashantv/gostub"
	. "github.com/smartystreets/goconvey/convey"
)

func TestToFrontier(t *testing.T) {
	Convey("TestToFrontier", t, func() {
		metrics.InitMetrics("testpsm", false)
		defer ApplyGlobalVar(&config.Config,
			config.Configuration{
				FrontierPSM: "rtc.frontier.psm",
				EnableIPv6:  false,
			}).Reset()
		Init()

		ctl := gomock.NewController(t)
		defer ctl.Finish()
		mockClient := mock.NewMockClient(ctl)
		defer gostub.Stub(&client, mockClient).Reset()

		Convey("PushToClient", func() {
			mockClient.EXPECT().PushToClient(gomock.Any(), gomock.Any(), gomock.Any()).Return(nil, nil)
			PushToClient(context.Background(), "", "addr", "addr6", "testevent", "testcontent", -1)
			mockClient.EXPECT().PushToClient(gomock.Any(), gomock.Any(), gomock.Any()).Return(nil, errors.New("test error"))
			PushToClient(context.Background(), "", "addr", "addr6", "testevent", "testcontent", -1)
		})

		Convey("BroadcastToClient", func() {
			resp := &rtc_frontier.TBroadCastResp{
				ConnIds: []string{"test1"},
			}
			mockClient.EXPECT().BroadcastToClient(gomock.Any(), gomock.Any(), gomock.Any()).Return(resp, nil)
			BroadcastToClient(context.Background(), nil, "addr", "addr6", "testevent", "testcontent", -1)
			mockClient.EXPECT().BroadcastToClient(gomock.Any(), gomock.Any(), gomock.Any()).Return(nil, errors.New("test error"))
			BroadcastToClient(context.Background(), nil, "addr", "addr6", "testevent", "testcontent", -1)
		})
	})
}
