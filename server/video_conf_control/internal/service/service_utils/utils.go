package service_utils

import (
	"context"
	"encoding/json"

	logs "github.com/sirupsen/logrus"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/models/custom_error"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/pkg/response"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/rpc/frontier"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/kitex_gen/vc_control"
)

type EventHandlerFunc func(ctx context.Context, param *vc_control.TEventParam)

type hostParam struct {
	UserID string `json:"user_id"`
}

func ParseHostParam(ctx context.Context, param *vc_control.TEventParam) (hostParam, error) {
	var p hostParam
	if err := json.Unmarshal([]byte(param.Content), &p); err != nil {
		logs.Errorf("input format error, err: %v", err)
		return p, err
	}
	return p, nil
}

func Push2Client(ctx context.Context, param *vc_control.TEventParam, err error, noErrRes interface{}) {
	if err == nil {
		frontier.PushToClient(ctx,
			param.ConnId,
			param.Addr,
			param.Addr6,
			param.EventName,
			response.NewCommonResponse(200, "ok", noErrRes),
			param.PacketId,
		)
	}

	if cerr, ok := err.(*custom_error.CustomError); ok {
		frontier.PushToClient(ctx,
			param.ConnId,
			param.Addr,
			param.Addr6,
			param.EventName,
			response.NewCommonResponse(cerr.Code(), cerr.Error(), nil),
			param.PacketId,
		)
	}
}

func Push2ClientWithoutReturn(ctx context.Context, param *vc_control.TEventParam, err error) {
	Push2Client(ctx, param, err, nil)
}
