package vc_db

import (
	"context"
	"gorm.io/gorm"

	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/dal/db"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/pkg/public"
)

// 根据RoomID UserID DeviceID 唯一的确定一个用户
func CreateOrUpdateUser(ctx context.Context, user *db.MeetingUser) error {
	defer public.CheckPanic()

	if err := db.Client.WithContext(ctx).Where(db.MeetingUser{RoomID: user.RoomID, UserID: user.UserID, DeviceID: user.DeviceID}).
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
}

func MuteAllUsersWithoutHost(ctx context.Context, roomID string) error {
	defer public.CheckPanic()
	if err := db.Client.Table("meeting_user").WithContext(ctx).Where("room_id = ? AND state = ? AND is_host = ?", roomID, db.ACTIVE, false).Update("is_mic_on", db.INACTIVE).Error; err != nil {
		return err
	}
	return nil
}

func UpdateUser(ctx context.Context, user *db.MeetingUser) error {
	defer public.CheckPanic()

	if err := db.Client.WithContext(ctx).Where(db.MeetingUser{ConnID: user.ConnID, State: db.ACTIVE}).Save(user).Error; err != nil {
		return err
	}
	return nil
}

func GetReconnectingUser(ctx context.Context, deviceID string) (*db.MeetingUser, error) {
	defer public.CheckPanic()

	var user *db.MeetingUser

	if err := db.Client.WithContext(ctx).Where("device_id = ? AND state IN ?", deviceID, []int{db.RECONNECTING, db.ACTIVE}).First(&user).Error; err != nil {
		return nil, err
	}
	return user, nil
}

func BatchUpdateUsers(ctx context.Context, users ...*db.MeetingUser) error {
	defer public.CheckPanic()

	if err := db.Client.Transaction(func(tx *gorm.DB) error {
		for _, user := range users {
			if err := tx.WithContext(ctx).Where(db.MeetingUser{ConnID: user.ConnID}).Save(user).Error; err != nil {
				return err
			}
		}
		return nil
	}); err != nil {
		return err
	}
	return nil
}

func GetUsersByRoomID(ctx context.Context, roomID string, userType ...int) ([]*db.MeetingUser, error) {
	defer public.CheckPanic()

	var users []*db.MeetingUser

	if err := db.Client.WithContext(ctx).Where("room_id = ? AND state IN ?", roomID, userType).Find(&users).Error; err != nil {
		return nil, err
	}
	return users, nil
}

func GetAllUserByDeviceID(ctx context.Context, deviceID string) ([]*db.MeetingUser, error) {
	defer public.CheckPanic()

	var users []*db.MeetingUser
	if err := db.Client.WithContext(ctx).Where(db.MeetingUser{DeviceID: deviceID}).Distinct("room_id").Order("created_at asc").Find(&users).Error; err != nil {
		return nil, err
	}
	return users, nil
}

func GetAllUserByUserID(ctx context.Context, userID string) ([]*db.MeetingUser, error) {
	defer public.CheckPanic()

	var users []*db.MeetingUser
	if err := db.Client.WithContext(ctx).Where(db.MeetingUser{UserID: userID}).Distinct("room_id").Order("created_at asc").Find(&users).Error; err != nil {
		return nil, err
	}
	return users, nil
}

func GetActiveUserByRoomIDAndUserID(ctx context.Context, roomID, userID string) (*db.MeetingUser, error) {
	defer public.CheckPanic()

	var user *db.MeetingUser
	if err := db.Client.WithContext(ctx).Where(db.MeetingUser{UserID: userID, RoomID: roomID, State: db.ACTIVE}).First(&user).Error; err != nil {
		return nil, err
	}

	return user, nil
}

func GetNextHost(ctx context.Context, u *db.MeetingUser) (*db.MeetingUser, error) {
	defer public.CheckPanic()

	var user *db.MeetingUser
	if err := db.Client.WithContext(ctx).Where("room_id = ? AND state = ? AND id <> ?", u.RoomID, db.ACTIVE, u.ID).Order("created_at asc").First(&user).Error; err != nil {
		return nil, err
	}
	return user, nil
}

func GetUserByConnID(ctx context.Context, connID string) (*db.MeetingUser, error) {
	defer public.CheckPanic()

	var user *db.MeetingUser
	if err := db.Client.WithContext(ctx).Where(db.MeetingUser{ConnID: connID, State: db.ACTIVE}).First(&user).Error; err != nil {
		return nil, err
	}
	return user, nil
}

func GetUserByDeviceID(ctx context.Context, roomID, userID, deviceID string) (*db.MeetingUser, error) {
	defer public.CheckPanic()

	var user *db.MeetingUser
	if err := db.Client.WithContext(ctx).Where(db.MeetingUser{DeviceID: deviceID, RoomID: roomID, UserID: userID}).First(&user).Error; err != nil {
		return nil, err
	}
	return user, nil
}

func GetActiveUsersByDeviceID(ctx context.Context, deviceID string) ([]*db.MeetingUser, error) {
	defer public.CheckPanic()

	var users []*db.MeetingUser
	if err := db.Client.WithContext(ctx).Where(db.MeetingUser{DeviceID: deviceID, State: db.ACTIVE}).Find(&users).Error; err != nil {
		return nil, err
	}
	return users, nil
}
