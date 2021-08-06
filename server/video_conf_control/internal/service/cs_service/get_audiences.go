package cs_service

import (
	"context"
	"encoding/json"

	logs "github.com/sirupsen/logrus"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/models/cs_models"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/models/custom_error"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/service/service_utils"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/kitex_gen/vc_control"
)

type getAudiencesParam struct {
	LoginToken string `json:"login_token"`
}

func getAudiences(ctx context.Context, param *vc_control.TEventParam) {
	var p getAudiencesParam
	if err := json.Unmarshal([]byte(param.Content), &p); err != nil {
		logs.Warnf("input format error, err: %v", err)
		service_utils.Push2ClientWithoutReturn(ctx, param, custom_error.ErrInput)
		return
	}

	user, err := cs_models.GetUser(ctx, param.ConnId)
	if err != nil {
		logs.Errorf("failed to get user, err: %v", err)
		service_utils.Push2ClientWithoutReturn(ctx, param, err)
		return
	}

	res, err := user.GetAudiences(ctx)
	if err != nil {
		logs.Errorf("failed to get audiences, err: %v", err)
		service_utils.Push2ClientWithoutReturn(ctx, param, err)
		return
	}

	service_utils.Push2Client(ctx, param, err, res)
}
