package conn_db

import (
	"context"

	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/dal/db"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/pkg/public"
)

func CreateConnection(ctx context.Context, conn *db.MeetingConnection) error {
	defer public.CheckPanic()

	if err := db.Client.WithContext(ctx).Create(conn).Error; err != nil {
		return err
	}
	return nil
}

func CreateOrUpdateConnection(ctx context.Context, conn *db.MeetingConnection) error {
	defer public.CheckPanic()

	if err := db.Client.WithContext(ctx).Where(db.MeetingConnection{DeviceID: conn.DeviceID}).
		Assign(db.MeetingConnection{ConnID: conn.ConnID, Addr: conn.Addr, Addr6: conn.Addr6}).
		FirstOrCreate(conn).Error; err != nil {
		return err
	}
	return nil
}

func UpdateConnection(ctx context.Context, conn *db.MeetingConnection) error {
	defer public.CheckPanic()

	if err := db.Client.WithContext(ctx).Table("meeting_connection").Where(db.MeetingConnection{DeviceID: conn.DeviceID}).Updates(
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

func GetConnections(ctx context.Context, connIDs []string) ([]*db.MeetingConnection, error) {
	defer public.CheckPanic()
	var conns []*db.MeetingConnection
	if err := db.Client.WithContext(ctx).Where("conn_id IN ?", connIDs).Find(&conns).Error; err != nil {
		return nil, err
	}
	return conns, nil
}

func GetConnectionByConnID(ctx context.Context, connID string) (*db.MeetingConnection, error) {
	defer public.CheckPanic()

	var conn db.MeetingConnection
	if err := db.Client.WithContext(ctx).Where(db.MeetingConnection{ConnID: connID}).First(&conn).Error; err != nil {
		return nil, err
	}
	return &conn, nil
}

func GetConnectionByDeviceID(ctx context.Context, deviceID string) (*db.MeetingConnection, error) {
	defer public.CheckPanic()

	var conn *db.MeetingConnection
	if err := db.Client.WithContext(ctx).Where(db.MeetingConnection{DeviceID: deviceID}).First(&conn).Error; err != nil {
		return nil, err
	}
	return conn, nil
}
