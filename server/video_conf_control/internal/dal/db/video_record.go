package db

import (
	"context"
	"time"

	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/config"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/pkg/public"
)

// GetVideoRecord returns a slice containing a point of ConferenceVideoRecord for each matching roomID
// ordered by create time with passed roomIDs to this process.
func GetVideoRecord(ctx context.Context, roomIDs []string) ([]*ConferenceVideoRecord, error) {
	var records []*ConferenceVideoRecord

	duration := time.Duration(config.Config.VideoDays)
	t := time.Now().Add(-duration * 24 * time.Hour).Format("2006-01-02 15:04:05")
	if err := db.WithContext(ctx).Where("room_id IN ? AND created_at >= ?", roomIDs, t).Order("created_at desc").Find(&records).Error; err != nil {
		logs.Warnf("failed to get video records, roomID: %s, err: %v", roomIDs, err)
		return nil, err
	}
	return records, nil
}

// CreateRecord creates a record with the passed pointer of ConferenceVideoRecord.
func CreateRecord(ctx context.Context, r *ConferenceVideoRecord) error {
	defer public.CheckPanic()

	if err := db.WithContext(ctx).Create(r).Error; err != nil {
		return err
	}
	return nil
}
