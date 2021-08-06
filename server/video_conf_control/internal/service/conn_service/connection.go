package conn_service

import (
	"context"
	"encoding/json"

	logs "github.com/sirupsen/logrus"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/models/conn_models"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/kitex_gen/vc_control"
)

type connectionParam struct {
	DeviceID string `json:"did"`
}

func connection(ctx context.Context, param *vc_control.TEventParam) {
	var p connectionParam
	if err := json.Unmarshal([]byte(param.Content), &p); err != nil || p.DeviceID == "" || p.DeviceID == "unknown" {
		logs.Warnf("input param format error, deviceID: %v", p.DeviceID)
		return
	}

	c := conn_models.NewConnection(param.ConnId, param.Addr, param.Addr6, p.DeviceID)

	logs.Infof("connect err: %v", c.Connect(ctx))
}
