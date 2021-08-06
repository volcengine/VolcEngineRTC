package cs_service

import (
	"context"

	logs "github.com/sirupsen/logrus"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/models/cs_models"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/kitex_gen/vc_control"
)

func Disconnect(ctx context.Context, param *vc_control.TEventParam) {
	u, err := cs_models.GetUser(ctx, param.ConnId)
	if err != nil {
		logs.Errorf("failed to get user, err: %v", err)
		return
	}

	logs.Infof("disconnect, err: %v", u.Disconnect(ctx))
}
