package main

import (
	"context"

	logs "github.com/sirupsen/logrus"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/pkg/record"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/service/conn_service"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/service/cs_service"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/service/vc_service"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/kitex_gen/base"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/kitex_gen/vc_control"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/pkg/public"
)

const (
	ConnID = "conn_id"
	Event  = "event"
)

// VCControlImpl implements the last service interface defined in the IDL.
type VCControlImpl struct{}

func NewVCControlImpl() *VCControlImpl {
	return &VCControlImpl{}
}

// HandleMeetingEvent implements the VCControlImpl interface.
func (s *VCControlImpl) HandleMeetingEvent(ctx context.Context, param *vc_control.TEventParam) (resp *vc_control.TEventResp, err error) {
	resp = vc_control.NewTEventResp()
	resp.BaseResp = base.NewBaseResp()
	resp.BaseResp.StatusCode = 200

	logs.Infof("handle event: %s, content: %s", param.EventName, param.Content)

	if eventHandler, ok := conn_service.GetHandlerByEventName(param.EventName); ok {
		go func() {
			defer public.CheckPanic()
			eventHandler(ctx, param)
		}()

		return
	}

	if eventHandler, ok := vc_service.GetHandlerByEventName(param.EventName); ok {
		go func() {
			defer public.CheckPanic()
			eventHandler(ctx, param)
		}()

		return
	}

	if eventHandler, ok := cs_service.GetHandlerByEventName(param.EventName); ok {
		go func() {
			defer public.CheckPanic()
			eventHandler(ctx, param)
		}()

		return
	}

	return
}

// HandleRecordCallback implements the VCControlImpl interface.
func (s *VCControlImpl) HandleRecordCallback(ctx context.Context, param *vc_control.TRecordCallbackParam) (resp *vc_control.THTTPResp, err error) {
	logs.Infof("record call back return: %v", param)
	return record.HandleRecordCallback(ctx, param)
}
