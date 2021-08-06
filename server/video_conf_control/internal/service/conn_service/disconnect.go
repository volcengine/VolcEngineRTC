package conn_service

import (
	"context"

	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/dal/db/cs_db"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/dal/db/vc_db"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/service/cs_service"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/service/vc_service"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/kitex_gen/vc_control"
)

func disconnect(ctx context.Context, param *vc_control.TEventParam) {
	_, err := vc_db.GetUserByConnID(ctx, param.ConnId)
	if err == nil {
		vc_service.Disconnect(ctx, param)

		return
	}

	_, err = cs_db.GetActiveUserByConnID(ctx, param.ConnId)
	if err == nil {
		cs_service.Disconnect(ctx, param)

		return
	}
}
