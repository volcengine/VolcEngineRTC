package vc_service

import (
	"context"
	"encoding/json"

	logs "github.com/sirupsen/logrus"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/models/custom_error"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/models/vc_models"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/service/service_utils"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/kitex_gen/vc_control"
)

type changeCameraStateParam struct {
	LoginToken string `json:"login_token"`
}

func turnOnCamera(ctx context.Context, param *vc_control.TEventParam) {
	changeCameraState(ctx, param, true)
}

func turnOffCamera(ctx context.Context, param *vc_control.TEventParam) {
	changeCameraState(ctx, param, false)
}

func changeCameraState(ctx context.Context, param *vc_control.TEventParam, state bool) {
	var p changeCameraStateParam
	if err := json.Unmarshal([]byte(param.Content), &p); err != nil {
		logs.Warnf("input format error, err: %v", err)
		service_utils.Push2ClientWithoutReturn(ctx, param, custom_error.ErrInput)
		return
	}

	user, err := vc_models.GetUser(ctx, param.ConnId)
	if err != nil {
		logs.Errorf("failed to get user, err: %v", err)
		service_utils.Push2ClientWithoutReturn(ctx, param, err)
		return
	}

	service_utils.Push2ClientWithoutReturn(ctx, param, user.SetCameraState(ctx, state))
}
