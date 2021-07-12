package public

import (
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/config"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/pkg/metrics"
)

func ChooseAddr(addr, addr6 string) (string, error) {
	useAddr := addr
	var err error
	if config.Config.EnableIPv6 {
		useAddr, err = tce_utils.ChooseAddr(addr, addr6)
		if err != nil {
			logs.Errorf("choose address error:%s, addr:%s, addr6:%s", err, addr, addr6)
			metrics.EmitRateCounter(metrics.ChooseAddrError, 1)
			return "", err
		}
	}
	if useAddr == addr {
		metrics.EmitRateCounter(metrics.ChooseFrontierIPQPS, 1, metrics.T{Name: "ip", Value: "ipv4"})
	} else {
		metrics.EmitRateCounter(metrics.ChooseFrontierIPQPS, 1, metrics.T{Name: "ip", Value: "ipv6"})
	}
	return useAddr, nil
}

func StringInSlice(a string, list []string) bool {
	for _, b := range list {
		if b == a {
			return true
		}
	}
	return false
}
