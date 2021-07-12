package public

import (
	"errors"
	"testing"

	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/pkg/metrics"

	. "github.com/agiledragon/gomonkey"
	. "github.com/smartystreets/goconvey/convey"

	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/config"
)

func TestChooseAddr(t *testing.T) {
	Convey("TestChooseAddr", t, func() {
		metrics.InitMetrics("test", false)
		Convey("EnableIPv6", func() {
			defer ApplyGlobalVar(&config.Config,
				config.Configuration{
					EnableIPv6: true,
				}).Reset()

			patch1 := ApplyFunc(tce_utils.ChooseAddr, func(v4 string, v6 string) (string, error) {
				return v4, nil
			})

			addr, addr6 := "test1", "test2"
			ret, err := ChooseAddr(addr, addr6)
			So(ret, ShouldEqual, "test1")
			So(err, ShouldEqual, nil)

			patch1 = ApplyFunc(tce_utils.ChooseAddr, func(v4 string, v6 string) (string, error) {
				return "", errors.New("")
			})

			ret, err = ChooseAddr(addr, addr6)
			So(ret, ShouldEqual, "")
			So(err, ShouldResemble, errors.New(""))
			defer patch1.Reset()
		})

		Convey("DisableIPv6", func() {
			defer ApplyGlobalVar(&config.Config,
				config.Configuration{
					EnableIPv6: false,
				}).Reset()

			addr, addr6 := "test1", "test2"
			ret, err := ChooseAddr(addr, addr6)
			So(ret, ShouldEqual, "test1")
			So(err, ShouldEqual, nil)
		})
	})
}
