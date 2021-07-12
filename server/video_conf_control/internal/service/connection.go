package service

import (
	"context"
	"encoding/json"

	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/models"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/kitex_gen/vc_control"
)

type connectionParam struct {
	DeviceID string `json:"did"`
}

func connection(ctx context.Context, param *vc_control.TEventParam) {
	var p connectionParam
	if err := json.Unmarshal([]byte(param.Content), &p); err != nil || p.DeviceID == "" || p.DeviceID == "unknown" {
		logs.CtxWarn(ctx, "input param format error, deviceID: %v", p.DeviceID)
		return
	}

	c := models.NewConnection(param.ConnId, param.Addr, param.Addr6, p.DeviceID)

	logs.CtxInfo(ctx, "connect err: %v", c.Connect(ctx))
}
