package db

import (
	"context"

	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/pkg/public"
	"gorm.io/gorm"
)

// CreateOrUpdateUser updates matched record or creates a new one with given conditions *ConferenceUser
// Uniquely determine a user based on RoomID UserID DeviceID.
func CreateOrUpdateUser(ctx context.Context, user *ConferenceUser) error {
	defer public.CheckPanic()

	if err := db.WithContext(ctx).Where(ConferenceUser{RoomID: user.RoomID, UserID: user.UserID, DeviceID: user.DeviceID}).
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

// MuteAllUsersWithoutHost updates the is_mic_on status of all users except the host to inactive with passed roomID.
func MuteAllUsersWithoutHost(ctx context.Context, roomID string) error {
	defer public.CheckPanic()
	if err := db.Table("conference_user").WithContext(ctx).Where("room_id = ? AND state = ? AND is_host = ?", roomID, ACTIVE, false).Update("is_mic_on", INACTIVE).Error; err != nil {
		return err
	}
	return nil
}

// UpdateUser saves all fields of user with given conditions *ConferenceUser.
func UpdateUser(ctx context.Context, user *ConferenceUser) error {
	defer public.CheckPanic()

	if err := db.WithContext(ctx).Where(ConferenceUser{ConnID: user.ConnID, State: ACTIVE}).Save(user).Error; err != nil {
		return err
	}
	return nil
}

// GetReconnectingUser gets first matched record with passed deviceID.
func GetReconnectingUser(ctx context.Context, deviceID string) (*ConferenceUser, error) {
	defer public.CheckPanic()

	var user *ConferenceUser

	if err := db.WithContext(ctx).Where("device_id = ? AND state IN ?", deviceID, []int{RECONNECTING, ACTIVE}).First(&user).Error; err != nil {
		return nil, err
	}
	return user, nil
}

// BatchUpdateUsers saves user's fields for each *ConferenceUser passed to this process within a transaction.
func BatchUpdateUsers(ctx context.Context, users ...*ConferenceUser) error {
	defer public.CheckPanic()

	if err := db.Transaction(func(tx *gorm.DB) error {
		for _, user := range users {
			if err := tx.WithContext(ctx).Where(ConferenceUser{ConnID: user.ConnID}).Save(user).Error; err != nil {
				return err
			}
		}
		return nil
	}); err != nil {
		return err
	}
	return nil
}

// GetUsersByRoomID returns a slice containing a *ConferenceUser for each user with passed roomID and userTypes.
func GetUsersByRoomID(ctx context.Context, roomID string, userType ...int) ([]*ConferenceUser, error) {
	defer public.CheckPanic()

	var users []*ConferenceUser

	if err := db.WithContext(ctx).Where("room_id = ? AND state IN ?", roomID, userType).Find(&users).Error; err != nil {
		return nil, err
	}
	return users, nil
}

// GetAllUserByDeviceID returns a slice containing a *ConferenceUser for each user ordered by create time with passed deviceID.
func GetAllUserByDeviceID(ctx context.Context, deviceID string) ([]*ConferenceUser, error) {
	defer public.CheckPanic()

	var users []*ConferenceUser
	if err := db.WithContext(ctx).Where(ConferenceUser{DeviceID: deviceID}).Distinct("room_id").Order("created_at asc").Find(&users).Error; err != nil {
		return nil, err
	}
	return users, nil
}

// GetActiveUserByRoomIDAndUserID gets first matched record with passed roomID and userID.
func GetActiveUserByRoomIDAndUserID(ctx context.Context, roomID, userID string) (*ConferenceUser, error) {
	defer public.CheckPanic()

	var user *ConferenceUser
	if err := db.WithContext(ctx).Where(ConferenceUser{UserID: userID, RoomID: roomID, State: ACTIVE}).First(&user).Error; err != nil {
		return nil, err
	}

	return user, nil
}

// GetNextHost gets first matched record with given conditions *ConferenceUser.
func GetNextHost(ctx context.Context, u *ConferenceUser) (*ConferenceUser, error) {
	defer public.CheckPanic()

	var user *ConferenceUser
	if err := db.WithContext(ctx).Where("room_id = ? AND state = ? AND id <> ?", u.RoomID, ACTIVE, u.ID).Order("created_at asc").First(&user).Error; err != nil {
		return nil, err
	}
	return user, nil
}

// GetUserByConnID gets first matched record with passed connID.
func GetUserByConnID(ctx context.Context, connID string) (*ConferenceUser, error) {
	defer public.CheckPanic()

	var user *ConferenceUser
	if err := db.WithContext(ctx).Where(ConferenceUser{ConnID: connID, State: ACTIVE}).First(&user).Error; err != nil {
		return nil, err
	}
	return user, nil
}

// GetUserByDeviceID gets first matched record with passed roomID, userID and deviceID.
func GetUserByDeviceID(ctx context.Context, roomID, userID, deviceID string) (*ConferenceUser, error) {
	defer public.CheckPanic()

	var user *ConferenceUser
	if err := db.WithContext(ctx).Where(ConferenceUser{DeviceID: deviceID, RoomID: roomID, UserID: userID}).First(&user).Error; err != nil {
		return nil, err
	}
	return user, nil
}

// GetActiveUsersByDeviceID returns a slice containing a *ConferenceUser for each active user with passed deviceID.
func GetActiveUsersByDeviceID(ctx context.Context, deviceID string) ([]*ConferenceUser, error) {
	defer public.CheckPanic()

	var users []*ConferenceUser
	if err := db.WithContext(ctx).Where(ConferenceUser{DeviceID: deviceID, State: ACTIVE}).Find(&users).Error; err != nil {
		return nil, err
	}
	return users, nil
}
