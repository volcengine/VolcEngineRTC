package main

import (
	"context"
	"time"

	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/pkg/record"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/service"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/kitex_gen/base"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/kitex_gen/vc_control"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/pkg/metrics"
)

const (
	ConnID = "conn_id"
	Event  = "event"
)

// VCControlImpl implements the last service interface defined in the IDL.
type VCControlImpl struct{}

// NewVCControlImpl returns a new *VCControlImpl.
func NewVCControlImpl() *VCControlImpl {
	// upload metrics
	go func() {
		for range time.Tick(15 * time.Second) {
			service.Upload(context.Background())
		}
	}()
	return &VCControlImpl{}
}

// HandleMeetingEvent implements the VCControlImpl interface.
func (s *VCControlImpl) HandleMeetingEvent(ctx context.Context, param *vc_control.TEventParam) (resp *vc_control.TEventResp, err error) {
	resp = vc_control.NewTEventResp()
	resp.BaseResp = base.NewBaseResp()
	resp.BaseResp.StatusCode = 200

	ctx = logs.CtxAddKVs(ctx, ConnID, param.ConnId, Event, param.EventName)
	logs.CtxInfo(ctx, "handle event: %s, content: %s", param.EventName, param.Content)

	if eventHandler, ok := service.GetHandlerByEventName(param.EventName); ok {
		go func() {
			defer func(start time.Time) {
				eventTag := metrics.T{Name: "event", Value: param.EventName}
				metrics.EmitRateCounter(metrics.EventQPS, 1, eventTag)
				metrics.EmitTimer(metrics.EventLatency, start.UnixNano(), eventTag)
			}(time.Now())
			eventHandler(ctx, param)
		}()
	}
	return
}

// HandleRecordCallback implements the VCControlImpl interface.
func (s *VCControlImpl) HandleRecordCallback(ctx context.Context, param *vc_control.TRecordCallbackParam) (resp *vc_control.THTTPResp, err error) {
	logs.CtxInfo(ctx, "record call back return: %v", param)
	return record.HandleRecordCallback(ctx, param)
}
