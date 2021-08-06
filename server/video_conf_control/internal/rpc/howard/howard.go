package howard

import (
	"context"
	"errors"
	"time"

	kc "github.com/cloudwego/kitex/client"
	"github.com/cloudwego/kitex/pkg/connpool"
	"github.com/cloudwego/kitex/transport"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/config"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/kitex_gen/base"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/kitex_gen/howard"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/kitex_gen/howard/howardservice"
)

const (
	statusCodeSuccess                       = 0
	statusCodeVidNotExistInRecords          = 1020
)

const cleanVideoTimeout = 1000 * time.Millisecond

var (
	client    howardservice.Client
)

func Init() {
	var err error

	client, err = howardservice.NewClient(
		config.Config.HowardConfig.PSM,
		kc.WithLongConnection(connpool.IdleConfig{
			MaxIdlePerAddress: 100,
			MaxIdleGlobal:     100,
			MaxIdleTimeout:    600 * time.Second,
		}),
		kc.WithTransportProtocol(transport.TTHeaderFramed),
	)

	if err != nil {
		panic(err)
	}

}

func DeleteRecord(ctx context.Context, vid string) (bool, error) {
	if client == nil {
		return false, errors.New("howard client not init")
	}

	req := &howard.CleanVideoRequest{
		Vid:          vid,
		IdentityInfo: "",
		Base: &base.Base{
			Caller: config.Config.PSM,
		},
	}

	ctxTimeout, cancel := context.WithTimeout(ctx, cleanVideoTimeout)
	defer cancel()

	rsp, err := client.CleanVideo(ctxTimeout, req)
	if err != nil {
		return false, err
	}

	baseRsp := rsp.BaseResp

	switch baseRsp.StatusCode {
	case statusCodeSuccess:
		return true, nil
	case statusCodeVidNotExistInRecords:
		return true, nil
	default:
		return false, errors.New(baseRsp.StatusMessage)
	}
}
