package cs_service

import (
	"context"
	"encoding/json"
	"errors"
	"sort"

	logs "github.com/sirupsen/logrus"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/config"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/models/conn_models"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/models/cs_models"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/models/custom_error"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/service/service_utils"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/kitex_gen/vc_control"
)

type getMeetingsParam struct {
	LoginToken string `json:"login_token"`
}

type getMeetingsReturn struct {
	Infos []*cs_models.RoomInfo `json:"infos"`
}

func getMeetings(ctx context.Context, param *vc_control.TEventParam) {
	var p getMeetingsParam
	if err := json.Unmarshal([]byte(param.Content), &p); err != nil {
		logs.Warnf("input format error, err: %v", err)
		service_utils.Push2ClientWithoutReturn(ctx, param, custom_error.ErrInput)
		return
	}

	_, err := conn_models.GetConnection(ctx, param.ConnId)
	if err != nil {
		logs.Errorf("failed to get connection, err: %v", err)
		service_utils.Push2ClientWithoutReturn(ctx, param, err)
		return
	}

	res := make(cs_models.RoomInfoSlice, 0)

	rooms, err := cs_models.GetActiveRooms(ctx)
	if errors.Is(err, custom_error.ErrRoomNotExist) {
		logs.Warnf("no active rooms in db")
		service_utils.Push2Client(ctx, param, nil, &getMeetingsReturn{Infos: res})
		return
	}

	if err != nil {
		logs.Errorf("failed to get rooms in db, err: %v", err)
		service_utils.Push2ClientWithoutReturn(ctx, param, err)
		return
	}

	for _, room := range rooms {
		res = append(res, cs_models.NewRoom(config.Config.AppID, room.RoomID, room.RoomName).GenerateInformRoomInfo(ctx))
	}

	sort.Sort(res)
	service_utils.Push2Client(ctx, param, err, &getMeetingsReturn{Infos: res})
}
