package cs_service

import (
	"context"
	"encoding/json"
	"math"
	"net/url"
	"strconv"
	"time"

	logs "github.com/sirupsen/logrus"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/config"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/models/conn_models"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/models/cs_models"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/models/custom_error"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/service/service_utils"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/kitex_gen/vc_control"
)

const (
	maxUserNameLen = 64
	maxRoomNameLen = 128
	retryDelay     = 8 * time.Millisecond
	maxRetryDelay  = 128 * time.Millisecond
	maxRetryNum    = 10
)

type createMeetingParam struct {
	LoginToken string `json:"login_token"`
	UserName   string `json:"user_name"`
	RoomName   string `json:"room_name"`
}

func createMeeting(ctx context.Context, param *vc_control.TEventParam) {
	var p createMeetingParam
	if err := json.Unmarshal([]byte(param.Content), &p); err != nil {
		logs.Warnf("input format error, err: %v", err)
		service_utils.Push2ClientWithoutReturn(ctx, param, custom_error.ErrInput)
		return
	}

	if p.UserName == "" || p.RoomName == "" {
		logs.Warnf("input format error, params: %v", p)
		service_utils.Push2ClientWithoutReturn(ctx, param, custom_error.ErrInput)
		return
	}

	roomName, err := url.QueryUnescape(p.RoomName)
	if err != nil {
		logs.Warnf("input format error, err: %v", err)
		service_utils.Push2ClientWithoutReturn(ctx, param, custom_error.ErrInput)
		return
	}

	if len(p.UserName) > maxUserNameLen || len(roomName) > maxRoomNameLen {
		logs.Warnf("input format error, params: %v", p)
		service_utils.Push2ClientWithoutReturn(ctx, param, custom_error.ErrInput)
		return
	}

	c, err := conn_models.GetConnection(ctx, param.ConnId)
	if err != nil {
		logs.Errorf("failed to get connection, err: %v", err)
		service_utils.Push2ClientWithoutReturn(ctx, param, custom_error.InternalError(err))
		return
	}

	roomID, err := cs_models.GenerateRoomID(ctx)
	for i := 0; roomID == 0 && i <= maxRetryNum; i++ {
		backOff := time.Duration(int64(math.Pow(2, float64(i)))) * retryDelay
		if backOff > maxRetryDelay {
			backOff = maxRetryDelay
		}

		time.Sleep(backOff)

		roomID, err = cs_models.GenerateRoomID(ctx)
	}

	if roomID == 0 {
		logs.Errorf("failed to generate roomID, err: %v", err)
		service_utils.Push2ClientWithoutReturn(ctx, param, custom_error.InternalError(err))
		return
	}

	userID := c.GetDeviceID()
	strRoomID := strconv.FormatInt(roomID, 10)
	appID := config.Config.AppID

	user := cs_models.NewUser(
		cs_models.GenDBUser(appID, userID, p.UserName, strRoomID, c.GetConnID(), c.GetDeviceID()),
		cs_models.NewRoom(appID, strRoomID, roomName),
	)

	user.CleanUserResidual(ctx, strRoomID)

	res, err := user.CreateMeeting(ctx)
	if err != nil {
		logs.Errorf("failed to create meeting, err: %v", err)
		service_utils.Push2ClientWithoutReturn(ctx, param, custom_error.InternalError(err))
		return
	}

	service_utils.Push2Client(ctx, param, err, res)
}
