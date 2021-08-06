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

type askDeviceParam struct {
	LoginToken string `json:"login_token"`
	UserID     string `json:"user_id"`
}

func askMicOn(ctx context.Context, param *vc_control.TEventParam) {
	askDevice(ctx, param, vc_models.AskingMicOn)
}

func askCameraOn(ctx context.Context, param *vc_control.TEventParam) {
	askDevice(ctx, param, vc_models.AskingCameraOn)
}

func askDevice(ctx context.Context, param *vc_control.TEventParam, event vc_models.InformEvent) {
	var p askDeviceParam
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

	service_utils.Push2ClientWithoutReturn(ctx, param, user.AskUserDeviceChange(ctx, p.UserID, event))
}
