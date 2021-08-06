package vc_db

import (
	"context"
	"time"

	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/config"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/dal/db"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/pkg/public"
)

func GetVideoRecord(ctx context.Context, roomIDs []string) ([]*db.MeetingVideoRecord, error) {
	var records []*db.MeetingVideoRecord
	// only get 90 days record
	duration := time.Duration(config.Config.VideoDays)
	t := time.Now().Add(-duration * 24 * time.Hour).Format("2006-01-02 15:04:05")
	if err := db.Client.WithContext(ctx).Where("room_id IN ? AND created_at >= ? AND state = ?", roomIDs, t, db.ACTIVE).
		Order("created_at desc").Find(&records).Error; err != nil {
		return nil, err
	}
	return records, nil
}

func GetRecord(ctx context.Context, vid string) (*db.MeetingVideoRecord, error) {
	defer public.CheckPanic()

	var r *db.MeetingVideoRecord
	if err := db.Client.WithContext(ctx).Where(db.MeetingVideoRecord{
		VID:   vid,
		State: db.ACTIVE,
	}).First(&r).Error; err != nil {
		return nil, err
	}

	return r, nil
}

func CreateRecord(ctx context.Context, r *db.MeetingVideoRecord) error {
	defer public.CheckPanic()

	if err := db.Client.WithContext(ctx).Create(r).Error; err != nil {
		return err
	}
	return nil
}

func DeleteRecord(ctx context.Context, vid string) error {
	defer public.CheckPanic()

	if err := db.Client.WithContext(ctx).Table("meeting_video_record").Where(
		db.MeetingVideoRecord{
			VID: vid,
		}).Update("state", db.INACTIVE).Error; err != nil {
		return err
	}

	return nil
}
