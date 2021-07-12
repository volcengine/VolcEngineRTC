package service

import (
	"context"

	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/config"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/kitex_gen/vc_control"
)

func getAppID(ctx context.Context, param *vc_control.TEventParam) {
	push2Client(ctx, param, nil, map[string]string{"app_id": config.Config.AppID})
}
