package service

import (
	"context"

	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/dal/db"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/pkg/metrics"
)

func Upload(ctx context.Context) {
	rooms, err := db.GetActiveRooms(ctx)
	if err != nil {
		logs.CtxWarn(ctx, "failed to get rooms in db, err: %v", err)
		return
	}

	dirtyRoomCount := 0
	for _, room := range rooms {
		tags := []metrics.T{
			{Name: "room_id", Value: room.RoomID},
		}

		if count, err := db.GetRoomUserCount(ctx, room.RoomID); err == nil {
			if count == 0 {
				db.DeleteRoom(ctx, room.RoomID)
				dirtyRoomCount++
				continue
			}

			logs.CtxInfo(ctx, "room %v has %v users", room.RoomID, count)
			metrics.EmitStore(metrics.UserCount, count, tags...)
		}
	}

	metrics.EmitStore(metrics.RoomCount, len(rooms)-dirtyRoomCount)
}
