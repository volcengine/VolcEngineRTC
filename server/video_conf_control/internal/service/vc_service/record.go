package vc_service

import (
	"context"
	"encoding/json"
	"errors"
	"gorm.io/gorm"

	logs "github.com/sirupsen/logrus"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/dal/db/vc_db"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/models/custom_error"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/models/vc_models"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/service/service_utils"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/kitex_gen/vc_control"
)

type getHistoryRecordParam struct {
	LoginToken string `json:"login_token"`
}

type recordParam struct {
	LoginToken string   `json:"login_token"`
	Users      []string `json:"users"`
	ScreenUID  string   `json:"screen_uid"`
}

type deleteRecordParam struct {
	LoginToken string `json:"login_token"`
	Vid        string `json:"vid"`
}

func getHistoryVideoRecord(ctx context.Context, param *vc_control.TEventParam) {
	var p getHistoryRecordParam
	if err := json.Unmarshal([]byte(param.Content), &p); err != nil {
		logs.Warnf("input format error, err: %v", err)
		service_utils.Push2ClientWithoutReturn(ctx, param, custom_error.ErrInput)
		return
	}

	userID := ""

	vr := vc_models.NewVCloudRecord()

	records, err := vr.GetVideoRecords(ctx, userID)
	if err != nil {
		logs.Errorf("failed to get video records, err: %v", err)
		service_utils.Push2ClientWithoutReturn(ctx, param, custom_error.InternalError(err))
		return
	}

	service_utils.Push2Client(ctx, param, err, records)
}

func deleteVideoRecord(ctx context.Context, param *vc_control.TEventParam) {
	var p deleteRecordParam
	if err := json.Unmarshal([]byte(param.Content), &p); err != nil {
		logs.Warnf("input format error, err: %v", err)
		service_utils.Push2ClientWithoutReturn(ctx, param, custom_error.ErrInput)
		return
	}

	if p.Vid == "" {
		logs.Warnf("input format error")
		service_utils.Push2ClientWithoutReturn(ctx, param, custom_error.ErrInput)
		return
	}


	userID := ""

	record, err := vc_db.GetRecord(ctx, p.Vid)
	if errors.Is(err, gorm.ErrRecordNotFound) {
		logs.Warnf("record not found, VID: %s", p.Vid)
		service_utils.Push2ClientWithoutReturn(ctx, param, nil)
		return
	}

	if err != nil {
		logs.Errorf("failed to get record, err: %v", err)
		service_utils.Push2ClientWithoutReturn(ctx, param, custom_error.InternalError(err))
		return
	}

	if userID != record.UserID {
		logs.Warnf("user is not record holder, userID: %s, record holder: %s", userID, record.UserID)
		service_utils.Push2ClientWithoutReturn(ctx, param, custom_error.ErrUserIsNotHost)
		return
	}

	vr := vc_models.NewVCloudRecord()

	err = vr.DeleteVideoRecord(ctx, p.Vid)
	if err != nil {
		logs.Errorf("failed to delete video record, err: %v", err)
		service_utils.Push2ClientWithoutReturn(ctx, param, custom_error.InternalError(err))
		return
	}

	err = vc_db.DeleteRecord(ctx, p.Vid)
	if err != nil {
		logs.Errorf("failed to delete video record, err: %v", err)
		service_utils.Push2ClientWithoutReturn(ctx, param, custom_error.InternalError(err))
		return
	}

	service_utils.Push2ClientWithoutReturn(ctx, param, nil)
}

func recordMeeting(ctx context.Context, param *vc_control.TEventParam) {
	p, err := parseRecordParam(ctx, param)
	if err != nil {
		logs.Errorf("failed to parse record param: %v, err: %v", param, err)
		service_utils.Push2ClientWithoutReturn(ctx, param, custom_error.ErrInput)
		return
	}

	user, err := vc_models.GetUser(ctx, param.ConnId)
	if err != nil {
		logs.Errorf("failed to get user, err: %v", err)
		service_utils.Push2ClientWithoutReturn(ctx, param, custom_error.InternalError(err))
		return
	}

	service_utils.Push2ClientWithoutReturn(ctx, param, user.StartRecord(ctx, p.Users, p.ScreenUID))
}

func updateRecordLayout(ctx context.Context, param *vc_control.TEventParam) {
	p, err := parseRecordParam(ctx, param)
	if err != nil {
		logs.Errorf("failed to parse record param: %v, err: %v", param, err)
		service_utils.Push2ClientWithoutReturn(ctx, param, custom_error.ErrInput)
		return
	}

	user, err := vc_models.GetUser(ctx, param.ConnId)
	if err != nil {
		logs.Errorf("failed to get user, err: %v", err)
		service_utils.Push2ClientWithoutReturn(ctx, param, custom_error.InternalError(err))
		return
	}

	service_utils.Push2ClientWithoutReturn(ctx, param, user.UpdateRecord(ctx, p.Users, p.ScreenUID))
}

func parseRecordParam(ctx context.Context, param *vc_control.TEventParam) (recordParam, error) {
	var p recordParam
	if err := json.Unmarshal([]byte(param.Content), &p); err != nil {
		logs.Infof("input format error, err: %v", err)
		return p, err
	}

	if p.ScreenUID == "" && len(p.Users) > 9 {
		logs.Infof("input user more than 9, users: %v", p.Users)
		p.Users = p.Users[:9]
		return p, nil
	} else if len(p.Users) > 8 {
		logs.Infof("input user and screen more than 9, users: %v, screen: %v", p.Users, p.ScreenUID)
		p.Users = p.Users[:8]
		return p, nil
	}

	return p, nil
}
