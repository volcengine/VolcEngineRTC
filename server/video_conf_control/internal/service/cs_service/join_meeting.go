package cs_service

import (
	"context"
	"encoding/json"
	"errors"

	logs "github.com/sirupsen/logrus"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/config"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/models/conn_models"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/models/cs_models"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/models/custom_error"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/service/service_utils"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/kitex_gen/vc_control"
)

type joinMeetingParam struct {
	LoginToken string `json:"login_token"`
	UserName   string `json:"user_name"`
	RoomID     string `json:"room_id"`
}

func joinMeeting(ctx context.Context, param *vc_control.TEventParam) {
	var p joinMeetingParam
	if err := json.Unmarshal([]byte(param.Content), &p); err != nil {
		logs.Warnf("input format error, err: %v", err)
		service_utils.Push2ClientWithoutReturn(ctx, param, custom_error.ErrInput)
		return
	}

	if p.UserName == "" || p.RoomID == "" {
		logs.Warnf("input format error, params: %v", p)
		service_utils.Push2ClientWithoutReturn(ctx, param, custom_error.ErrInput)
		return
	}

	if len(p.UserName) > maxUserNameLen {
		logs.Warnf("input format error, params: %v", p)
		service_utils.Push2ClientWithoutReturn(ctx, param, custom_error.ErrInput)
		return
	}

	room, err := cs_models.GetRoom(ctx, p.RoomID)
	if errors.Is(err, custom_error.ErrRoomNotExist) {
		logs.Warnf("room not exist")
		service_utils.Push2ClientWithoutReturn(ctx, param, err)
		return
	}

	if err != nil {
		logs.Errorf("failed to get room, err: %v", err)
		service_utils.Push2ClientWithoutReturn(ctx, param, err)
		return
	}

	c, err := conn_models.GetConnection(ctx, param.ConnId)
	if err != nil {
		logs.Errorf("failed to get connection, err: %v", err)
		service_utils.Push2ClientWithoutReturn(ctx, param, err)
		return
	}

	userID := c.GetDeviceID()
	appID := config.Config.AppID

	user := cs_models.NewUser(
		cs_models.GenDBUser(appID, userID, p.UserName, p.RoomID, c.GetConnID(), c.GetDeviceID()),
		room,
	)

	user.CleanUserResidual(ctx, p.RoomID)

	res, err := user.JoinMeeting(ctx)
	if err != nil {
		logs.Errorf("failed to join meeting, err: %v", err)
		service_utils.Push2ClientWithoutReturn(ctx, param, err)
		return
	}

	service_utils.Push2Client(ctx, param, err, res)

	user.GetRoom().Inform(ctx, cs_models.OnCsJoinMeeting, user.GenerateInformUserInfo())
}
