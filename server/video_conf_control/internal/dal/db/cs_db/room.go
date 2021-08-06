package cs_db

import (
	"context"
	"gorm.io/gorm"
	"time"

	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/dal/db"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/pkg/public"
)

func BatchCreateRoomUser(ctx context.Context, room *db.CsMeetingRoom, user *db.CsMeetingUser) error {
	defer public.CheckPanic()

	now := time.Now()

	if err := db.Client.Transaction(func(tx *gorm.DB) error {
		if err := tx.WithContext(ctx).Where(db.CsMeetingRoom{RoomID: room.RoomID}).
			Assign(db.CsMeetingRoom{
				AppID:     room.AppID,
				State:     true,
				RoomName:  room.RoomName,
				CreatedAt: now,
			}).FirstOrCreate(room).Error; err != nil {
			return err
		}

		if err := tx.WithContext(ctx).Where(db.CsMeetingUser{RoomID: user.RoomID, UserID: user.UserID, DeviceID: user.DeviceID}).
			Assign(map[string]interface{}{
				"app_id":         user.AppID,
				"user_name":      user.UserName,
				"user_status":    user.UserStatus,
				"is_host":        user.IsHost,
				"is_mic_on":      user.IsMicOn,
				"state":          user.State,
				"conn_id":        user.ConnID,
				"created_at":     now,
				"raise_hands_at": now,
			}).FirstOrCreate(user).Error; err != nil {
			return err
		}
		return nil
	}); err != nil {
		return err
	}
	return nil
}

func GetActiveRooms(ctx context.Context) ([]*db.CsMeetingRoom, error) {
	defer public.CheckPanic()

	var rs []*db.CsMeetingRoom
	if err := db.Client.WithContext(ctx).Where(db.CsMeetingRoom{State: true}).Find(&rs).Error; err != nil {
		return nil, err
	}
	return rs, nil
}

func GetRoom(ctx context.Context, roomID string) (*db.CsMeetingRoom, error) {
	defer public.CheckPanic()

	var r *db.CsMeetingRoom
	if err := db.Client.WithContext(ctx).Where(db.CsMeetingRoom{RoomID: roomID, State: true}).First(&r).Error; err != nil {
		return nil, err
	}
	return r, nil
}

func CreateRoom(ctx context.Context, room *db.CsMeetingRoom) error {
	defer public.CheckPanic()
	if err := db.Client.WithContext(ctx).Where(db.CsMeetingRoom{RoomID: room.RoomID, State: false}).
		Assign(db.CsMeetingRoom{AppID: room.AppID, State: true}).FirstOrCreate(room).Error; err != nil {
		return err
	}
	return nil
}

func DeleteRoom(ctx context.Context, roomID string) error {
	defer public.CheckPanic()

	if err := db.Client.WithContext(ctx).Table("cs_meeting_room").Where(db.CsMeetingRoom{RoomID: roomID}).Update("state", false).Error; err != nil {
		return err
	}
	return nil
}

func GetRoomUserCount(ctx context.Context, roomID string) (int, error) {
	defer public.CheckPanic()

	var count int64

	if err := db.Client.WithContext(ctx).Model(&db.CsMeetingUser{}).
		Where("room_id = ? AND state IN ?", roomID, []int{db.ACTIVE, db.RECONNECTING}).
		Count(&count).Error; err != nil {
		return int(count), err
	}

	return int(count), nil
}

func GetRoomUserOnMicrophone(ctx context.Context, roomID string) (int, error) {
	defer public.CheckPanic()

	var count int64

	if err := db.Client.WithContext(ctx).Model(&db.CsMeetingUser{}).
		Where("room_id = ? AND user_status = ? AND state IN ?", roomID, int(db.UserStatusOnMicrophone), []int{db.ACTIVE, db.RECONNECTING}).
		Count(&count).Error; err != nil {
		return int(count), err
	}

	return int(count), nil
}

func CleanRoom(ctx context.Context, roomID string) error {
	defer public.CheckPanic()

	if err := db.Client.Transaction(func(tx *gorm.DB) error {
		if err := tx.Table("cs_meeting_room").WithContext(ctx).Where("room_id = ? AND state = ?", roomID, db.ACTIVE).Update("state", db.INACTIVE).Error; err != nil {
			return err
		}
		if err := tx.Table("cs_meeting_user").WithContext(ctx).Where("room_id = ?", roomID).Updates(map[string]interface{}{
			"state": db.INACTIVE,
		}).Error; err != nil {
			return err
		}
		return nil
	}); err != nil {
		return err
	}
	return nil
}
