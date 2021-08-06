package cs_service

import (
	"context"
	"encoding/json"

	logs "github.com/sirupsen/logrus"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/models/cs_models"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/models/custom_error"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/service/service_utils"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/kitex_gen/vc_control"
)

type offMicParam struct {
	LoginToken string `json:"login_token"`
	UserID     string `json:"user_id"`
}

func offMic(ctx context.Context, param *vc_control.TEventParam) {
	var p offMicParam
	if err := json.Unmarshal([]byte(param.Content), &p); err != nil {
		logs.Warnf("input format error, err: %v", err)
		service_utils.Push2ClientWithoutReturn(ctx, param, custom_error.ErrInput)
		return
	}

	if p.UserID == "" {
		logs.Warnf("input format error, params: %v", p)
		service_utils.Push2ClientWithoutReturn(ctx, param, custom_error.ErrInput)
		return
	}

	user, err := cs_models.GetUser(ctx, param.ConnId)
	if err != nil {
		logs.Errorf("failed to get user, err %v", err)
		service_utils.Push2ClientWithoutReturn(ctx, param, err)
		return
	}

	offUser, err := user.OffMic(ctx, p.UserID)
	if err != nil {
		logs.Errorf("failed to off mic, err %v", err)
		service_utils.Push2ClientWithoutReturn(ctx, param, err)
		return
	}

	service_utils.Push2ClientWithoutReturn(ctx, param, nil)

	user.GetRoom().Inform(ctx, cs_models.OnCsMicOff, offUser.GenerateInformUserInfo())
}
