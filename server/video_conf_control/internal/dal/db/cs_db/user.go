package cs_db

import (
	"context"
	"gorm.io/gorm"

	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/dal/db"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/pkg/public"
)

// 根据RoomID UserID DeviceID 唯一的确定一个用户
func CreateOrUpdateUser(ctx context.Context, user *db.CsMeetingUser) error {
	defer public.CheckPanic()

	if err := db.Client.WithContext(ctx).Where(db.CsMeetingUser{RoomID: user.RoomID, UserID: user.UserID, DeviceID: user.DeviceID}).
		Assign(map[string]interface{}{
			"app_id":      user.AppID,
			"user_name":   user.UserName,
			"user_status": user.UserStatus,
			"is_host":     user.IsHost,
			"is_mic_on":   user.IsMicOn,
			"state":       user.State,
			"conn_id":     user.ConnID,
		}).FirstOrCreate(user).Error; err != nil {
		return err
	}
	return nil
}

func UpdateUser(ctx context.Context, user *db.CsMeetingUser) error {
	defer public.CheckPanic()

	if err := db.Client.WithContext(ctx).Where(db.CsMeetingUser{ConnID: user.ConnID, State: db.ACTIVE}).Save(user).Error; err != nil {
		return err
	}
	return nil
}

func BatchUpdateUsers(ctx context.Context, users ...*db.CsMeetingUser) error {
	defer public.CheckPanic()

	if err := db.Client.Transaction(func(tx *gorm.DB) error {
		for _, user := range users {
			if err := tx.WithContext(ctx).Where(db.CsMeetingUser{ConnID: user.ConnID}).Save(user).Error; err != nil {
				return err
			}
		}
		return nil
	}); err != nil {
		return err
	}
	return nil
}

func GetUsersByRoomID(ctx context.Context, roomID string, userType ...int) ([]*db.CsMeetingUser, error) {
	defer public.CheckPanic()

	var users []*db.CsMeetingUser

	if err := db.Client.WithContext(ctx).Where("room_id = ? AND state IN ?", roomID, userType).Find(&users).Error; err != nil {
		return nil, err
	}
	return users, nil
}

func GetRaiseHandsUsersByRoomID(ctx context.Context, roomID string, userType ...int) ([]*db.CsMeetingUser, error) {
	defer public.CheckPanic()

	var users []*db.CsMeetingUser

	if err := db.Client.WithContext(ctx).Where(map[string]interface{}{
		"room_id":     roomID,
		"is_host":     false,
		"user_status": []int{int(db.UserStatusRaiseHands), int(db.UserStatusOnMicrophone)},
		"state":       userType,
	}).Find(&users).Error; err != nil {
		return nil, err
	}

	return users, nil
}

func GetAudiencesByRoomID(ctx context.Context, roomID string, userType ...int) ([]*db.CsMeetingUser, error) {
	defer public.CheckPanic()

	var users []*db.CsMeetingUser

	if err := db.Client.WithContext(ctx).Where(map[string]interface{}{
		"room_id":     roomID,
		"is_host":     false,
		"user_status": int(db.UserStatusAudience),
		"state":       userType,
	}).Find(&users).Error; err != nil {
		return nil, err
	}

	return users, nil
}

func GetActiveUserByRoomIDAndUserID(ctx context.Context, roomID, userID string) (*db.CsMeetingUser, error) {
	defer public.CheckPanic()

	var user *db.CsMeetingUser
	if err := db.Client.WithContext(ctx).Where(db.CsMeetingUser{UserID: userID, RoomID: roomID, State: db.ACTIVE}).First(&user).Error; err != nil {
		return nil, err
	}

	return user, nil
}

func GetHostByRoomID(ctx context.Context, roomID string) (*db.CsMeetingUser, error) {
	defer public.CheckPanic()

	var user *db.CsMeetingUser
	if err := db.Client.WithContext(ctx).Where(db.CsMeetingUser{RoomID: roomID, State: db.ACTIVE, IsHost: true}).First(&user).Error; err != nil {
		return nil, err
	}
	return user, nil
}

func GetNextHost(ctx context.Context, u *db.CsMeetingUser) (*db.CsMeetingUser, error) {
	defer public.CheckPanic()

	var user *db.CsMeetingUser
	if err := db.Client.WithContext(ctx).Where("room_id = ? AND state = ? AND id <> ? AND user_status = ?",
		u.RoomID, db.ACTIVE, u.ID, db.UserStatusOnMicrophone).Order("raise_hands_at asc").First(&user).Error; err != nil {
		return nil, err
	}
	return user, nil
}

func GetActiveUserByConnID(ctx context.Context, connID string) (*db.CsMeetingUser, error) {
	defer public.CheckPanic()

	var user *db.CsMeetingUser
	if err := db.Client.WithContext(ctx).Where(db.CsMeetingUser{ConnID: connID, State: db.ACTIVE}).First(&user).Error; err != nil {
		return nil, err
	}
	return user, nil
}

func GetReconnectingUserByConnID(ctx context.Context, connID string) (*db.CsMeetingUser, error) {
	defer public.CheckPanic()

	var user *db.CsMeetingUser
	if err := db.Client.WithContext(ctx).Where(db.CsMeetingUser{ConnID: connID, State: db.RECONNECTING}).First(&user).Error; err != nil {
		return nil, err
	}
	return user, nil
}

func GetReconnectingOrActiveUserByRoomIDAndDeviceID(ctx context.Context, roomID, userID, deviceID string) (*db.CsMeetingUser, error) {
	defer public.CheckPanic()

	var user *db.CsMeetingUser
	if err := db.Client.WithContext(ctx).Where(map[string]interface{}{
		"device_id": deviceID,
		"room_id":   roomID,
		"user_id":   userID,
		"state":     []int{int(db.RECONNECTING), int(db.ACTIVE)},
	}).First(&user).Error; err != nil {
		return nil, err
	}

	return user, nil
}

func GetReconnectingOrActiveUserByDeviceID(ctx context.Context, deviceID string) (*db.CsMeetingUser, error) {
	defer public.CheckPanic()

	var user *db.CsMeetingUser
	if err := db.Client.WithContext(ctx).Where("device_id = ? AND state IN ?", deviceID, []int{db.RECONNECTING, db.ACTIVE}).Last(&user).Error; err != nil {
		return nil, err
	}
	return user, nil
}

func GetActiveUsersByDeviceID(ctx context.Context, deviceID string) ([]*db.CsMeetingUser, error) {
	defer public.CheckPanic()

	var users []*db.CsMeetingUser
	if err := db.Client.WithContext(ctx).Where(db.CsMeetingUser{DeviceID: deviceID, State: db.ACTIVE}).Find(&users).Error; err != nil {
		return nil, err
	}
	return users, nil
}
