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

type changeScreenParam struct {
	LoginToken string `json:"login_token"`
}

func startShareScreen(ctx context.Context, param *vc_control.TEventParam) {
	changeScreenState(ctx, param, true)
}

func endShareScreen(ctx context.Context, param *vc_control.TEventParam) {
	changeScreenState(ctx, param, false)
}

func changeScreenState(ctx context.Context, param *vc_control.TEventParam, state bool) {
	var p changeScreenParam
	if err := json.Unmarshal([]byte(param.Content), &p); err != nil {
		logs.Warnf("input format error, err: %v", err)
		service_utils.Push2ClientWithoutReturn(ctx, param, custom_error.ErrInput)
		return
	}

	user, err := vc_models.GetUser(ctx, param.ConnId)
	if err != nil {
		logs.Errorf("failed to get user, err: %v", err)
		service_utils.Push2ClientWithoutReturn(ctx, param, custom_error.InternalError(err))
		return
	}
	service_utils.Push2ClientWithoutReturn(ctx, param, user.SetShareState(ctx, state))
}
