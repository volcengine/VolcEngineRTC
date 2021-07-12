package service

import (
	"context"

	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/models"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/kitex_gen/vc_control"
)

func reconnect(ctx context.Context, param *vc_control.TEventParam) {
	c, err := models.GetConnection(ctx, param.ConnId)
	if err != nil {
		push2ClientWithoutReturn(ctx, param, err)
		return
	}

	push2ClientWithoutReturn(ctx, param, c.Reconnect(ctx))
}
