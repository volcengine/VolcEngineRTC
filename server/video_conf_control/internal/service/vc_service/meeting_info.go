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

type getMeetingUserInfoParam struct {
	LoginToken string `json:"login_token"`
	UserID     string `json:"user_id"`
}

func getMeetingUserInfo(ctx context.Context, param *vc_control.TEventParam) {
	var p getMeetingUserInfoParam
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

	res, err := user.GetRoom().ListUsers(ctx)
	service_utils.Push2Client(ctx, param, err, res)
}

type getMeetingInfoParam struct {
	LoginToken string `json:"login_token"`
}

func getMeetingInfo(ctx context.Context, param *vc_control.TEventParam) {
	var p getMeetingInfoParam
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

	service_utils.Push2Client(ctx, param, nil, user.GetRoom().GetRoomInfo(ctx))
}
