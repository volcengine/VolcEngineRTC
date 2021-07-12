package service

import (
	"context"

	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/models"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/kitex_gen/vc_control"
)

func turnOnMic(ctx context.Context, param *vc_control.TEventParam) {
	changeMicState(ctx, param, true)
}

func turnOffMic(ctx context.Context, param *vc_control.TEventParam) {
	changeMicState(ctx, param, false)
}

func changeMicState(ctx context.Context, param *vc_control.TEventParam, state bool) {
	user, err := models.GetUser(ctx, param.ConnId)
	if err != nil {
		logs.CtxError(ctx, "failed to get user, err: %v", err)
		push2ClientWithoutReturn(ctx, param, err)
		return
	}

	push2ClientWithoutReturn(ctx, param, user.SetMicState(ctx, state))
}
