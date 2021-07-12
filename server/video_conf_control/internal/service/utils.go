package service

import (
	"context"
	"encoding/json"

	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/models"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/pkg/response"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/rpc/frontier"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/kitex_gen/vc_control"
)

type hostParam struct {
	UserID string `json:"user_id"`
}

func parseHostParam(ctx context.Context, param *vc_control.TEventParam) (hostParam, error) {
	var p hostParam
	if err := json.Unmarshal([]byte(param.Content), &p); err != nil {
		logs.CtxError(ctx, "input format error, err: %v", err)
		return p, err
	}
	return p, nil
}

func push2Client(ctx context.Context, param *vc_control.TEventParam, err error, noErrRes interface{}) {
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

	if cerr, ok := err.(*models.CustomError); ok {
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

func push2ClientWithoutReturn(ctx context.Context, param *vc_control.TEventParam, err error) {
	push2Client(ctx, param, err, nil)
}
