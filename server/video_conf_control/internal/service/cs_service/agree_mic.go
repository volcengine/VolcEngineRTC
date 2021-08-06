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

type agreeMicParam struct {
	LoginToken string `json:"login_token"`
	UserID     string `json:"user_id"`
}

func agreeMic(ctx context.Context, param *vc_control.TEventParam) {
	var p agreeMicParam
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

	agreedUser, err := user.AgreeMic(ctx, p.UserID)
	if err != nil {
		logs.Errorf("failed to agree mic, err %v", err)
		service_utils.Push2ClientWithoutReturn(ctx, param, err)
		return
	}

	service_utils.Push2ClientWithoutReturn(ctx, param, nil)

	user.GetRoom().Inform(ctx, cs_models.OnCsMicOn, agreedUser.GenerateInformUserInfo())
}
