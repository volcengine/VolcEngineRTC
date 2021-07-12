package models

import (
	"context"
	"errors"
	"time"

	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/dal/db"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/dal/redis"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/pkg/video"
	"gorm.io/gorm"
)

type Connection struct {
	conn *db.ConferenceConnection
}

const MaxReconnectRetry = 5

// NewConnection returns a new *Connection.
func NewConnection(connID, addr, addr6, deviceID string) *Connection {
	return &Connection{
		conn: &db.ConferenceConnection{
			ConnID:   connID,
			Addr:     addr,
			Addr6:    addr6,
			State:    db.ACTIVE,
			DeviceID: deviceID,
		},
	}
}

// GetConnection tries to get a *Connection with passed connID.
func GetConnection(ctx context.Context, connID string) (*Connection, error) {
	conn, err := db.GetConnectionByConnID(ctx, connID)
	if err != nil {
		logs.CtxError(ctx, "failed to get connection in db, err: %v", err)
		return nil, InternalError(err)
	}
	return &Connection{conn: conn}, nil
}

// CleanDirtyUser updates the other user's state to inactive with the same deviceID,
// if the room user count is zero, then updates the room state to false.
func (c *Connection) CleanDirtyUser(ctx context.Context, selfuserID string) {
	users, err := db.GetActiveUsersByDeviceID(ctx, c.conn.DeviceID)
	if err != nil {
		logs.CtxWarn(ctx, "failed to get users from db, err: %v", err)
		return
	}

	us := make(map[string][]*db.ConferenceUser)

	for _, u := range users {
		if u.UserID == selfuserID {
			continue
		}
		u.State = Inactive
		us[u.RoomID] = append(us[u.RoomID], u)
	}

	for roomID, user := range us {
		if err := db.BatchUpdateUsers(ctx, user...); err != nil {
			logs.CtxWarn(ctx, "failed to clean dirty user, err: %v", err)
		}
		if count, err := db.GetRoomUserCount(ctx, roomID); err == nil && count == 0 {
			logs.CtxInfo(ctx, "delete room, err: %v", db.DeleteRoom(ctx, roomID))
			redis.InitRoomState(ctx, roomID, "")
		}
	}
}

// Connect updates or creates a connection.
func (c *Connection) Connect(ctx context.Context) error {
	err := db.CreateOrUpdateConnection(ctx, c.conn)
	if err != nil {
		logs.CtxError(ctx, "failed to create or update connection, err: %v", err)
		return err
	}
	logs.CtxInfo(ctx, "create or update connection: %v", c)
	return nil
}

func (c *Connection) retryGetConnectingUser(ctx context.Context) (user *db.ConferenceUser, err error) {
	for i := 0; i < MaxReconnectRetry; i++ {
		if user, err = db.GetReconnectingUser(ctx, c.conn.DeviceID); err == nil {
			return user, nil
		}
		logs.CtxInfo(ctx, "cannot find reconnecting user, wait 10ms")
		time.Sleep(10 * time.Millisecond)
	}
	return nil, err
}

// Reconnect updates user's state to active if user's state is reconnecting.
func (c *Connection) Reconnect(ctx context.Context) error {
	user, err := c.retryGetConnectingUser(ctx)
	if errors.Is(err, gorm.ErrRecordNotFound) {
		logs.CtxInfo(ctx, "no need to reconnect")
		return ErrUserIsInactive
	}

	if err != nil {
		logs.CtxError(ctx, "db error: %v", err)
		return InternalError(err)
	}

	user.State = Active
	user.ConnID = c.conn.ConnID
	if err := db.CreateOrUpdateUser(ctx, user); err != nil {
		logs.CtxWarn(ctx, "failed to update user in db, err: %v", err)
		return InternalError(err)
	}

	return nil
}

func (c *Connection) GetConnID() string {
	return c.conn.ConnID
}

func (c *Connection) GetDeviceID() string {
	return c.conn.DeviceID
}

// GetVideoRecords returns a slice containing a *recordInfo for each roomID with the same deviceID.
func (c *Connection) GetVideoRecords(ctx context.Context) ([]*recordInfo, error) {
	users, err := db.GetAllUserByDeviceID(ctx, c.conn.DeviceID)
	if err != nil {
		logs.CtxError(ctx, "failed to get users in db, deviceID: %s, err: %v", c.conn.DeviceID, err)
		return nil, InternalError(err)
	}

	roomIDs := make([]string, 0)
	for _, u := range users {
		roomIDs = append(roomIDs, u.RoomID)
	}

	records, err := db.GetVideoRecord(ctx, roomIDs)
	if err != nil {
		logs.CtxError(ctx, "failed to get video records, deviceID: %s, roomIDs: %v, err: %v", c.conn.DeviceID, roomIDs, err)
		return nil, InternalError(err)
	}

	return getVideoRecords(ctx, records), nil
}

type recordInfo struct {
	RoomID      string `json:"room_id"`
	CreatedAt   int64  `json:"created_at"`
	DownloadURL string `json:"download_url"`
}

func getVideoRecords(ctx context.Context, records []*db.ConferenceVideoRecord) (res []*recordInfo) {
	recordMap := make(map[string]*recordInfo) // key: vid
	for _, rec := range records {
		recordMap[rec.VID] = &recordInfo{
			RoomID:    rec.RoomID,
			CreatedAt: rec.CreatedAt.UnixNano(),
		}
	}

	vids := make([]string, 0)
	for _, record := range records {
		vids = append(vids, record.VID)
	}

	durl := video.GetVideoURL(ctx, vids)

	logs.CtxInfo(ctx, "vids: %v, downloadurl: %v", vids, durl)

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
