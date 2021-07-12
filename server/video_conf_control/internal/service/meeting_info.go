package service

import (
	"context"
	"encoding/json"

	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/models"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/kitex_gen/vc_control"
)

type getMeetingUserInfoParam struct {
	UserID string `json:"user_id"`
}

func getMeetingUserInfo(ctx context.Context, param *vc_control.TEventParam) {
	var p getMeetingUserInfoParam
	if err := json.Unmarshal([]byte(param.Content), &p); err != nil {
		logs.CtxWarn(ctx, "input format error, err: %v", err)
		push2ClientWithoutReturn(ctx, param, models.ErrInput)
		return
	}

	user, err := models.GetUser(ctx, param.ConnId)
	if err != nil {
		logs.CtxError(ctx, "failed to get user, err: %v", err)
		push2ClientWithoutReturn(ctx, param, err)
		return
	}

	res, err := user.GetRoom().ListUsers(ctx)
	push2Client(ctx, param, err, res)
}

func getMeetingInfo(ctx context.Context, param *vc_control.TEventParam) {
	user, err := models.GetUser(ctx, param.ConnId)
	if err != nil {
		logs.CtxError(ctx, "failed to get user, err: %v", err)
		push2ClientWithoutReturn(ctx, param, err)
		return
	}

	push2Client(ctx, param, nil, user.GetRoom().GetRoomInfo(ctx))
}
