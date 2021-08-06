package vc_db

import (
	"context"
	"gorm.io/gorm"

	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/dal/db"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/pkg/public"
)

func BatchCreateRoomUser(ctx context.Context, room *db.MeetingRoom, user *db.MeetingUser) error {
	defer public.CheckPanic()

	if err := db.Client.Transaction(func(tx *gorm.DB) error {
		if err := tx.WithContext(ctx).Where(db.MeetingRoom{RoomID: room.RoomID}).
			Assign(db.MeetingRoom{AppID: room.AppID, State: true}).FirstOrCreate(room).Error; err != nil {
			return err
		}
		if err := tx.WithContext(ctx).Where(db.MeetingUser{RoomID: user.RoomID, UserID: user.UserID, DeviceID: user.DeviceID}).
			Assign(map[string]interface{}{
				"app_id":       user.AppID,
				"is_host":      user.IsHost,
				"is_mic_on":    user.IsMicOn,
				"is_camera_on": user.IsCameraOn,
				"state":        user.State,
				"is_sharing":   user.IsSharing,
				"conn_id":      user.ConnID,
				"created_at":   user.CreatedAt,
			}).FirstOrCreate(user).Error; err != nil {
			return err
		}
		return nil
	}); err != nil {
		return err
	}
	return nil
}

func GetActiveRooms(ctx context.Context) ([]*db.MeetingRoom, error) {
	defer public.CheckPanic()

	var rs []*db.MeetingRoom
	if err := db.Client.WithContext(ctx).Where(db.MeetingRoom{State: true}).Find(&rs).Error; err != nil {
		return nil, err
	}
	return rs, nil
}

func GetRoom(ctx context.Context, roomID string) (*db.MeetingRoom, error) {
	defer public.CheckPanic()

	var r *db.MeetingRoom
	if err := db.Client.WithContext(ctx).Where(db.MeetingRoom{RoomID: roomID, State: true}).First(&r).Error; err != nil {
		return nil, err
	}
	return r, nil
}

func CreateRoom(ctx context.Context, room *db.MeetingRoom) error {
	defer public.CheckPanic()
	if err := db.Client.WithContext(ctx).Where(db.MeetingRoom{RoomID: room.RoomID, State: false}).
		Assign(db.MeetingRoom{AppID: room.AppID, State: true, Record: room.Record}).FirstOrCreate(room).Error; err != nil {
		return err
	}
	return nil
}

func DeleteRoom(ctx context.Context, roomID string) error {
	defer public.CheckPanic()

	if err := db.Client.WithContext(ctx).Table("meeting_room").Where(db.MeetingRoom{RoomID: roomID}).Update("state", false).Error; err != nil {
		return err
	}
	return nil
}

func GetRoomUserCount(ctx context.Context, roomID string) (int, error) {
	defer public.CheckPanic()
	var count int64
	if err := db.Client.WithContext(ctx).Model(&db.MeetingUser{}).Where("room_id = ? AND state IN ?", roomID, []int{db.ACTIVE, db.RECONNECTING}).Count(&count).Error; err != nil {
		return int(count), err
	}
	return int(count), nil
}

func CleanRoom(ctx context.Context, roomID string) error {
	defer public.CheckPanic()

	if err := db.Client.Transaction(func(tx *gorm.DB) error {
		if err := tx.Table("meeting_room").WithContext(ctx).Where("room_id = ? AND state = ?", roomID, db.ACTIVE).Update("state", db.INACTIVE).Error; err != nil {
			return err
		}
		if err := tx.Table("meeting_user").WithContext(ctx).Where("room_id = ?", roomID).Updates(map[string]interface{}{
			"state":        db.INACTIVE,
			"is_sharing":   db.INACTIVE,
			"is_mic_on":    db.INACTIVE,
			"is_camera_on": db.INACTIVE,
		}).Error; err != nil {
			return err
		}
		return nil
	}); err != nil {
		return err
	}
	return nil
}
