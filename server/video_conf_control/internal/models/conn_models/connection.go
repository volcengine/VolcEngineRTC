package conn_models

import (
	"context"

	logs "github.com/sirupsen/logrus"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/dal/db"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/dal/db/conn_db"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/models/custom_error"
)

type Connection struct {
	conn *db.MeetingConnection
}

func NewConnection(connID, addr, addr6, deviceID string) *Connection {
	return &Connection{
		conn: &db.MeetingConnection{
			ConnID:   connID,
			Addr:     addr,
			Addr6:    addr6,
			State:    db.ACTIVE,
			DeviceID: deviceID,
		},
	}
}

func GetConnection(ctx context.Context, connID string) (*Connection, error) {
	conn, err := conn_db.GetConnectionByConnID(ctx, connID)
	if err != nil {
		logs.Errorf("failed to get connection in db, err: %v", err)
		return nil, custom_error.InternalError(err)
	}
	return &Connection{conn: conn}, nil
}

func (c *Connection) Connect(ctx context.Context) error {
	err := conn_db.CreateOrUpdateConnection(ctx, c.conn)
	if err != nil {
		logs.Errorf("failed to create or update connection, err: %v", err)
		return err
	}
	logs.Infof("create or update connection: %v", c)
	return nil
}

func (c *Connection) GetConnID() string {
	return c.conn.ConnID
}

func (c *Connection) GetDeviceID() string {
	return c.conn.DeviceID
}

func (c *Connection) GetAddr() string {
	return c.conn.Addr
}

func (c *Connection) GetAddr6() string {
	return c.conn.Addr6
}
