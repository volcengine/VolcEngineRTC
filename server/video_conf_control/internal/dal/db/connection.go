package db

import (
	"context"

	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/pkg/public"
)

// CreateConnection creates a record with the passed pointer of ConferenceConnection.
func CreateConnection(ctx context.Context, conn *ConferenceConnection) error {
	defer public.CheckPanic()

	if err := db.WithContext(ctx).Create(conn).Error; err != nil {
		return err
	}
	return nil
}

// CreateOrUpdateConnection updates matched record or creates a new one with given conditions.
func CreateOrUpdateConnection(ctx context.Context, conn *ConferenceConnection) error {
	defer public.CheckPanic()

	if err := db.WithContext(ctx).Where(ConferenceConnection{DeviceID: conn.DeviceID}).
		Assign(ConferenceConnection{ConnID: conn.ConnID, Addr: conn.Addr, Addr6: conn.Addr6}).
		FirstOrCreate(conn).Error; err != nil {
		return err
	}
	return nil
}

// UpdateConnection updates matched record with given conditions.
func UpdateConnection(ctx context.Context, conn *ConferenceConnection) error {
	defer public.CheckPanic()

	if err := db.WithContext(ctx).Table("terminal_connection").Where(ConferenceConnection{DeviceID: conn.DeviceID}).Updates(
		map[string]interface{}{
			"conn_id": conn.ConnID,
			"addr":    conn.Addr,
			"addr6":   conn.Addr6,
			"state":   conn.State,
		},
	).Error; err != nil {
		return err
	}
	return nil
}

// GetConnections returns a slice containing a point of ConferenceConnection for each matching connID passed to this process.
func GetConnections(ctx context.Context, connIDs []string) ([]*ConferenceConnection, error) {
	defer public.CheckPanic()
	var conns []*ConferenceConnection
	if err := db.WithContext(ctx).Where("conn_id IN ?", connIDs).Find(&conns).Error; err != nil {
		return nil, err
	}
	return conns, nil
}

// GetConnectionByConnID gets first matched record with passed connID.
func GetConnectionByConnID(ctx context.Context, connID string) (*ConferenceConnection, error) {
	defer public.CheckPanic()

	var conn ConferenceConnection
	if err := db.WithContext(ctx).Where(ConferenceConnection{ConnID: connID}).First(&conn).Error; err != nil {
		return nil, err
	}
	return &conn, nil
}

// GetConnectionByDeviceID get first matched record with passed deviceID.
func GetConnectionByDeviceID(ctx context.Context, deviceID string) (*ConferenceConnection, error) {
	defer public.CheckPanic()

	var conn *ConferenceConnection
	if err := db.WithContext(ctx).Where(ConferenceConnection{DeviceID: deviceID}).First(&conn).Error; err != nil {
		return nil, err
	}
	return conn, nil
}
