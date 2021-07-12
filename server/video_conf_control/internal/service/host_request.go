package service

import (
	"context"

	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/models"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/kitex_gen/vc_control"
)

func askMicOn(ctx context.Context, param *vc_control.TEventParam) {
	askDevice(ctx, param, models.AskingMicOn)
}

func askCameraOn(ctx context.Context, param *vc_control.TEventParam) {
	askDevice(ctx, param, models.AskingCameraOn)
}

func askDevice(ctx context.Context, param *vc_control.TEventParam, event models.InformEvent) {
	p, err := parseHostParam(ctx, param)
	if err != nil {
		logs.CtxError(ctx, "failed to parse host param: %v, err: %v", param, err)
		push2ClientWithoutReturn(ctx, param, models.ErrInput)
		return
	}

	user, err := models.GetUser(ctx, param.ConnId)
	if err != nil {
		logs.CtxError(ctx, "failed to get user, err: %v", err)
		push2ClientWithoutReturn(ctx, param, err)
		return
	}

	push2ClientWithoutReturn(ctx, param, user.AskUserDeviceChange(ctx, p.UserID, event))
}
