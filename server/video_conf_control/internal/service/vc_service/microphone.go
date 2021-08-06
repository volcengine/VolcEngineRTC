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

type changeMicStateParam struct {
	LoginToken string `json:"login_token"`
}

func turnOnMic(ctx context.Context, param *vc_control.TEventParam) {
	changeMicState(ctx, param, true)
}

func turnOffMic(ctx context.Context, param *vc_control.TEventParam) {
	changeMicState(ctx, param, false)
}

func changeMicState(ctx context.Context, param *vc_control.TEventParam, state bool) {
	var p changeMicStateParam
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

	service_utils.Push2ClientWithoutReturn(ctx, param, user.SetMicState(ctx, state))
}
