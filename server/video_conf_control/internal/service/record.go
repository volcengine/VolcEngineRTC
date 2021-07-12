package service

import (
	"context"
	"encoding/json"

	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/models"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/kitex_gen/vc_control"
)

type recordParam struct {
	Users     []string `json:"users"`
	ScreenUID string   `json:"screen_uid"`
}

func getHistoryVideoRecord(ctx context.Context, param *vc_control.TEventParam) {
	c, err := models.GetConnection(ctx, param.ConnId)
	if err != nil {
		logs.CtxError(ctx, "failed to get connection, err: %v", err)
		push2ClientWithoutReturn(ctx, param, models.InternalError(err))
		return
	}

	records, err := c.GetVideoRecords(ctx)
	push2Client(ctx, param, err, records)
}

func recordMeeting(ctx context.Context, param *vc_control.TEventParam) {
	p, err := parseRecordParam(ctx, param)
	if err != nil {
		logs.CtxError(ctx, "failed to parse record param: %v, err: %v", param, err)
		push2ClientWithoutReturn(ctx, param, models.ErrInput)
		return
	}

	user, err := models.GetUser(ctx, param.ConnId)
	if err != nil {
		logs.CtxError(ctx, "failed to get user, err: %v", err)
		push2ClientWithoutReturn(ctx, param, models.InternalError(err))
		return
	}

	push2ClientWithoutReturn(ctx, param, user.StartRecord(ctx, p.Users, p.ScreenUID))
}

func updateRecordLayout(ctx context.Context, param *vc_control.TEventParam) {
	p, err := parseRecordParam(ctx, param)
	if err != nil {
		logs.CtxError(ctx, "failed to parse record param: %v, err: %v", param, err)
		push2ClientWithoutReturn(ctx, param, models.ErrInput)
		return
	}

	user, err := models.GetUser(ctx, param.ConnId)
	if err != nil {
		logs.CtxError(ctx, "failed to get user, err: %v", err)
		push2ClientWithoutReturn(ctx, param, models.InternalError(err))
		return
	}

	push2ClientWithoutReturn(ctx, param, user.UpdateRecord(ctx, p.Users, p.ScreenUID))
}

func parseRecordParam(ctx context.Context, param *vc_control.TEventParam) (recordParam, error) {
	var p recordParam
	if err := json.Unmarshal([]byte(param.Content), &p); err != nil {
		logs.CtxInfo(ctx, "input format error, err: %v", err)
		return p, err
	}

	if p.ScreenUID == "" && len(p.Users) > 9 {
		logs.CtxInfo(ctx, "input user more than 9, users: %v", p.Users)
		p.Users = p.Users[:9]
		return p, nil
	} else if len(p.Users) > 8 {
		logs.CtxInfo(ctx, "input user and screen more than 9, users: %v, screen: %v", p.Users, p.ScreenUID)
		p.Users = p.Users[:8]
		return p, nil
	}

	return p, nil
}
