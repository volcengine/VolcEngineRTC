package vc_models

import (
	"context"
	"errors"
	"gorm.io/gorm"

	logs "github.com/sirupsen/logrus"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/dal/db"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/dal/db/vc_db"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/models/custom_error"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/pkg/video"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/rpc/howard"
)

type VCloudRecord struct {
}

type recordInfo struct {
	RoomID      string `json:"room_id"`
	CreatedAt   int64  `json:"created_at"`
	DownloadURL string `json:"download_url"`
	VID         string `json:"vid"`
	VideoHolder bool   `json:"video_holder"`
}

func NewVCloudRecord() *VCloudRecord {
	return &VCloudRecord{}
}

func (vr *VCloudRecord) GetVideoRecords(ctx context.Context, userID string) ([]*recordInfo, error) {
	users, err := vc_db.GetAllUserByUserID(ctx, userID)
	if errors.Is(err, gorm.ErrRecordNotFound) {
		logs.Warnf("users not found, userID: %s", userID)
		return nil, nil
	}

	if err != nil {
		logs.Errorf("failed to get users in db, userID: %s, err: %v", userID, err)
		return nil, custom_error.InternalError(err)
	}

	roomIDs := make([]string, 0)
	for _, u := range users {
		roomIDs = append(roomIDs, u.RoomID)
	}

	records, err := vc_db.GetVideoRecord(ctx, roomIDs)
	if errors.Is(err, gorm.ErrRecordNotFound) {
		logs.Warnf("video record not found, roomIDs: %v", roomIDs)
		return nil, nil
	}

	if err != nil {
		logs.Errorf("failed to get video records, userID: %s, roomIDs: %v, err: %v", userID, roomIDs, err)
		return nil, custom_error.InternalError(err)
	}

	return getVideoRecords(ctx, userID, records), nil
}

func getVideoRecords(ctx context.Context, userID string, records []*db.MeetingVideoRecord) (res []*recordInfo) {
	recordMap := make(map[string]*recordInfo) // key: vid
	for _, rec := range records {
		recordMap[rec.VID] = &recordInfo{
			RoomID:      rec.RoomID,
			CreatedAt:   rec.CreatedAt.UnixNano(),
			VID:         rec.VID,
			VideoHolder: userID == rec.UserID,
		}

		logs.Infof("VID: %v, userID: %v, rec.userID: %v", rec.VID, userID, rec.UserID)
	}

	vids := make([]string, 0)
	for _, record := range records {
		vids = append(vids, record.VID)
	}

	durl := video.GetVideoURL(ctx, vids)

	logs.Infof("vids: %v, downloadurl: %v", vids, durl)

	for vid, record := range recordMap {
		record.DownloadURL = durl[vid]
	}

	for _, record := range records {
		if recordMap[record.VID].DownloadURL != "" {
			res = append(res, recordMap[record.VID])
		}
	}

	return res
}

func (vr *VCloudRecord) DeleteVideoRecord(ctx context.Context, vid string) error {
	_, err := howard.DeleteRecord(ctx, vid)
	if err != nil {
		return custom_error.InternalError(err)
	}

	return nil
}
