package service

import (
	"context"

	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/models"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/kitex_gen/vc_control"
)

func turnOnCamera(ctx context.Context, param *vc_control.TEventParam) {
	changeCameraState(ctx, param, true)
}

func turnOffCamera(ctx context.Context, param *vc_control.TEventParam) {
	changeCameraState(ctx, param, false)
}

func changeCameraState(ctx context.Context, param *vc_control.TEventParam, state bool) {
	user, err := models.GetUser(ctx, param.ConnId)
	if err != nil {
		logs.CtxError(ctx, "failed to get user, err: %v", err)
		push2ClientWithoutReturn(ctx, param, err)
		return
	}

	push2ClientWithoutReturn(ctx, param, user.SetCameraState(ctx, state))
}
