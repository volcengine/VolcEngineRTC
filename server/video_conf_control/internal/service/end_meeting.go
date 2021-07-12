package service

import (
	"context"

	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/models"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/kitex_gen/vc_control"
)

func endMeeting(ctx context.Context, param *vc_control.TEventParam) {
	user, err := models.GetUser(ctx, param.ConnId)
	if err != nil {
		logs.CtxError(ctx, "failed to get user, err: %v", err)
		push2ClientWithoutReturn(ctx, param, err)
		return
	}

	push2ClientWithoutReturn(ctx, param, user.EndMeeting(ctx))
}
