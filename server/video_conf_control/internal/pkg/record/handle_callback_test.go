package record

import (
	"context"
	"testing"

	. "github.com/agiledragon/gomonkey"
	. "github.com/smartystreets/goconvey/convey"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/dal/db"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/kitex_gen/vc_control"
)

func TestHandleRecordCallback(t *testing.T) {
	Convey("TestHandleRecordCallback", t, func() {
		defer ApplyFunc(db.CreateRecord, func(_ context.Context, _ *db.ConferenceVideoRecord) error {
			return nil
		}).Reset()

		ctx := context.Background()

		param := &vc_control.TRecordCallbackParam{
			EventData: "123",
		}
		HandleRecordCallback(ctx, param)

		param = &vc_control.TRecordCallbackParam{
			EventData: `{"AppId":"123", "RoomId":"1234", "RecordFileList": ["Vid": "12345"]}`,
		}
		HandleRecordCallback(ctx, param)
	})
}
