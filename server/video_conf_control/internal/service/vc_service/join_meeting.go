package vc_service

import (
	"context"
	"encoding/json"

	logs "github.com/sirupsen/logrus"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/models/conn_models"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/models/custom_error"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/models/vc_models"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/service/service_utils"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/kitex_gen/vc_control"
)

type joinMeetingParam struct {
	AppID      string `json:"app_id"`
	UserID     string `json:"user_id"`
	RoomID     string `json:"room_id"`
	Mic        bool   `json:"mic"`
	Camera     bool   `json:"camera"`
	LoginToken string `json:"login_token"`
	UserName   string `json:"user_name"`
}

func joinMeeting(ctx context.Context, param *vc_control.TEventParam) {
	var p joinMeetingParam
	if err := json.Unmarshal([]byte(param.Content), &p); err != nil {
		logs.Warnf("input format error, err: %v", err)
		service_utils.Push2ClientWithoutReturn(ctx, param, custom_error.ErrInput)
		return
	}

	c, err := conn_models.GetConnection(ctx, param.ConnId)
	if err != nil {
		logs.Errorf("failed to get connection, err: %v", err)
		service_utils.Push2ClientWithoutReturn(ctx, param, err)
		return
	}

	user := vc_models.NewUser(
		vc_models.GenDBUser(p.AppID, p.UserID, p.RoomID, c.GetConnID(), c.GetDeviceID(), p.Mic, p.Camera),
		vc_models.NewRoom(p.AppID, p.RoomID),
	)

	user.CleanDirtyUser(ctx, p.UserID)
	res, err := user.JoinMeeting(ctx)
	service_utils.Push2Client(ctx, param, err, res)

	if err == nil {
		user.GetRoom().Inform(ctx, vc_models.UserJoinMeeting, user.GenerateInformUserInfo())
	}
}
