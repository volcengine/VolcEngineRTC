package record

import (
	"context"
	"encoding/json"

	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/dal/db"
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
	r := &db.ConferenceVideoRecord{
		AppID:  p.AppID,
		RoomID: p.RoomID,
		VID:    p.RecordFileList[0].VID,
	}

	if err := db.CreateRecord(ctx, r); err != nil {
		logs.CtxWarn(ctx, "create meeting record error, err: %v", err)
	}
	return
}
