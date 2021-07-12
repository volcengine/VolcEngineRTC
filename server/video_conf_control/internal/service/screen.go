package service

import (
	"context"

	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/models"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/kitex_gen/vc_control"
)

func startShareScreen(ctx context.Context, param *vc_control.TEventParam) {
	changeScreenState(ctx, param, true)
}

func endShareScreen(ctx context.Context, param *vc_control.TEventParam) {
	changeScreenState(ctx, param, false)
}

func changeScreenState(ctx context.Context, param *vc_control.TEventParam, state bool) {
	user, err := models.GetUser(ctx, param.ConnId)
	if err != nil {
		logs.CtxError(ctx, "failed to get user, err: %v", err)
		push2ClientWithoutReturn(ctx, param, models.InternalError(err))
		return
	}
	push2ClientWithoutReturn(ctx, param, user.SetShareState(ctx, state))
}
