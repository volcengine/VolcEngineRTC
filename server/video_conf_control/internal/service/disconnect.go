package service

import (
	"context"

	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/models"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/kitex_gen/vc_control"
)

func disconnect(ctx context.Context, param *vc_control.TEventParam) {
	u, err := models.GetUser(ctx, param.ConnId)
	if err != nil {
		logs.CtxError(ctx, "failed to get user, err: %v", err)
		return
	}

	logs.CtxInfo(ctx, "disconnect, err: %v", u.Disconnect(ctx))
}
