package cs_service

import (
	"context"
	"encoding/json"

	logs "github.com/sirupsen/logrus"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/models/conn_models"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/models/cs_models"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/models/custom_error"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/service/service_utils"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/kitex_gen/vc_control"
)

type reconnectParam struct {
	LoginToken string `json:"login_token"`
}

func reconnect(ctx context.Context, param *vc_control.TEventParam) {
	var p reconnectParam
	if err := json.Unmarshal([]byte(param.Content), &p); err != nil {
		logs.Warnf("input format error, err: %v", err)
		service_utils.Push2ClientWithoutReturn(ctx, param, custom_error.ErrInput)
		return
	}

	c, err := conn_models.GetConnection(ctx, param.ConnId)
	if err != nil {
		logs.Errorf("failed to get user, err %v", err)
		service_utils.Push2ClientWithoutReturn(ctx, param, err)
		return
	}

	res, err := cs_models.Reconnect(ctx, c)
	if err != nil {
		logs.Errorf("failed to reconnect, err %v", err)
		service_utils.Push2ClientWithoutReturn(ctx, param, err)
		return
	}

	service_utils.Push2Client(ctx, param, err, res)
}
