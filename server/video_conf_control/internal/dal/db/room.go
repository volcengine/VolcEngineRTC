package db

import (
	"context"

	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/pkg/public"
	"gorm.io/gorm"
)

// BatchCreateRoomUser creates or updates ConferenceRoom and ConferenceUser records within a transaction.
func BatchCreateRoomUser(ctx context.Context, room *ConferenceRoom, user *ConferenceUser) error {
	defer public.CheckPanic()

	if err := db.Transaction(func(tx *gorm.DB) error {
		if err := tx.WithContext(ctx).Where(ConferenceRoom{RoomID: room.RoomID}).
			Assign(ConferenceRoom{AppID: room.AppID, State: true}).FirstOrCreate(room).Error; err != nil {
			return err
		}
		if err := tx.WithContext(ctx).Where(ConferenceUser{RoomID: user.RoomID, UserID: user.UserID, DeviceID: user.DeviceID}).
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

// GetActiveRooms returns a slice containing a point of ConferenceConnection for each active state room.
func GetActiveRooms(ctx context.Context) ([]*ConferenceRoom, error) {
	defer public.CheckPanic()

	var rs []*ConferenceRoom
	if err := db.WithContext(ctx).Where(ConferenceRoom{State: true}).Find(&rs).Error; err != nil {
		return nil, err
	}
	return rs, nil
}

// GetRoom gets first matched record with passed roomID.
func GetRoom(ctx context.Context, roomID string) (*ConferenceRoom, error) {
	defer public.CheckPanic()

	var r *ConferenceRoom
	if err := db.WithContext(ctx).Where(ConferenceRoom{RoomID: roomID, State: true}).First(&r).Error; err != nil {
		return nil, err
	}
	return r, nil
}

// CreateRoom updates matched record or creates a new one with given conditions *ConferenceRoom.
func CreateRoom(ctx context.Context, room *ConferenceRoom) error {
	defer public.CheckPanic()
	if err := db.WithContext(ctx).Where(ConferenceRoom{RoomID: room.RoomID, State: false}).
		Assign(ConferenceRoom{AppID: room.AppID, State: true, Record: room.Record}).FirstOrCreate(room).Error; err != nil {
		return err
	}
	return nil
}

// DeleteRoom updates room state to false with passed roomID.
func DeleteRoom(ctx context.Context, roomID string) error {
	defer public.CheckPanic()

	if err := db.WithContext(ctx).Table("conference_room").Where(ConferenceRoom{RoomID: roomID}).Update("state", false).Error; err != nil {
		return err
	}
	return nil
}

// GetRoomUserCount returns the number of users with passed roomID.
func GetRoomUserCount(ctx context.Context, roomID string) (int, error) {
	defer public.CheckPanic()
	var count int64
	if err := db.WithContext(ctx).Model(&ConferenceUser{}).Where("room_id = ? AND state IN ?", roomID, []int{ACTIVE, RECONNECTING}).Count(&count).Error; err != nil {
		return int(count), err
	}
	return int(count), nil
}

// CleanRoom updates ConferenceRoom and ConferenceUser state to inactive with passed roomID within a transaction.
func CleanRoom(ctx context.Context, roomID string) error {
	defer public.CheckPanic()

	if err := db.Transaction(func(tx *gorm.DB) error {
		if err := tx.Table("conference_room").WithContext(ctx).Where("room_id = ? AND state = ?", roomID, ACTIVE).Update("state", INACTIVE).Error; err != nil {
			return err
		}
		if err := tx.Table("conference_user").WithContext(ctx).Where("room_id = ?", roomID).Updates(map[string]interface{}{
			"state":        INACTIVE,
			"is_sharing":   INACTIVE,
			"is_mic_on":    INACTIVE,
			"is_camera_on": INACTIVE,
		}).Error; err != nil {
			return err
		}
		return nil
	}); err != nil {
		return err
	}
	return nil
}
