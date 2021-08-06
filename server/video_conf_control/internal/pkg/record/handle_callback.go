package record

import (
	"context"
	"encoding/json"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/dal/db"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/dal/db/vc_db"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/dal/redis/vc_redis"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/kitex_gen/vc_control"
)

type PostProcessingCallBack struct {
	AppID          string       `json:"AppId"`
	BussinessID    string       `json:"BusinessId"`
	RoomID         string       `json:"RoomId"`
	TaskID         string       `json:"TaskId"`
	Code           int          `json:"code"`
	ErrorMessage   string       `json:"ErrorMessage"`
	RecordFileList []recordFile `json:"RecordFileList"`
}

func HandleRecordCallback(ctx context.Context, param *vc_control.TRecordCallbackParam) (resp *vc_control.THTTPResp, err error) {
	resp = vc_control.NewTHTTPResp()

	// Only handle the callback when the recording is complete
	var p PostProcessingCallBack
	if err2 := json.Unmarshal([]byte(param.EventData), &p); err2 != nil {
		return
	}

	// For scenes that only need to be mixed stream recording, just take the first one of the return values
	userID := vc_redis.GetUserIDByTaskID(ctx, p.TaskID)

	// 对于只需要混流录制的场景，取返回值的第一个就可以
	r := &db.MeetingVideoRecord{
		AppID:  p.AppID,
		RoomID: p.RoomID,
		VID:    p.RecordFileList[0].VID,
		UserID: userID,
		State:  db.ACTIVE,
	}
	vc_db.CreateRecord(ctx, r)
	return
}
