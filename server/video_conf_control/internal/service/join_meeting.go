package service

import (
	"context"
	"encoding/json"

	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/models"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/kitex_gen/vc_control"
)

type joinMeetingParam struct {
	AppID  string `json:"app_id"`
	UserID string `json:"user_id"`
	RoomID string `json:"room_id"`
	Mic    bool   `json:"mic"`
	Camera bool   `json:"camera"`
}

func joinMeeting(ctx context.Context, param *vc_control.TEventParam) {
	var p joinMeetingParam
	if err := json.Unmarshal([]byte(param.Content), &p); err != nil {
		logs.CtxWarn(ctx, "input format error, err: %v", err)
		push2ClientWithoutReturn(ctx, param, models.ErrInput)
		return
	}

	c, err := models.GetConnection(ctx, param.ConnId)
	if err != nil {
		logs.CtxError(ctx, "failed to get connection, err: %v", err)
		push2ClientWithoutReturn(ctx, param, err)
		return
	}

	user := models.NewUser(
		models.GenDBUser(p.AppID, p.UserID, p.RoomID, c.GetConnID(), c.GetDeviceID(), p.Mic, p.Camera),
		models.NewRoom(p.AppID, p.RoomID),
	)

	c.CleanDirtyUser(ctx, p.UserID)
	res, err := user.JoinMeeting(ctx)
	push2Client(ctx, param, err, res)

	if err == nil {
		user.GetRoom().Inform(ctx, models.UserJoinMeeting, user.GenerateInformUserInfo())
	}
}
