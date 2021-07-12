package record

import (
	"context"
	"encoding/json"
	"errors"
	"net/url"
	"reflect"
	"testing"

	"github.com/TTvcloud/vcloud-sdk-golang/base"
	. "github.com/agiledragon/gomonkey"
	. "github.com/smartystreets/goconvey/convey"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/config"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/dal/redis"
)

func TestInit(t *testing.T) {
	Convey("TestInit", t, func() {
		defer ApplyGlobalVar(&config.Config,
			config.Configuration{
				PostProcessingURL: "ppurl",
				PostProcessingAK:  "ppak",
				PostProcessingSK:  "ppsk",
			}).Reset()

		Convey("test env", func() {
			defer ApplyFunc(env.PSM, func() string {
				return "p.s.m_test"
			}).Reset()
			Init()
		})

		Convey("prod env", func() {
			defer ApplyFunc(env.PSM, func() string {
				return "p.s.m"
			}).Reset()
			Init()
		})
	})
}

func TestStartRecord(t *testing.T) {
	Convey("TestStartRecord", t, func() {
		users := []string{"1"}
		screen := "1"
		ctx := context.Background()
		appID := "testappid"
		roomID := "testroomid"

		Convey("query failed", func() {
			defer ApplyMethod(reflect.TypeOf(client), "Json", func(_ *base.Client, _ string, _ url.Values, _ string) ([]byte, int, error) {
				return nil, 400, errors.New("error")
			}).Reset()

			_, err := StartRecord(ctx, users, screen, appID, roomID)
			So(err, ShouldResemble, errors.New("error"))
		})

		Convey("query success", func() {
			Convey("invaild json", func() {
				defer ApplyMethod(reflect.TypeOf(client), "Json", func(_ *base.Client, _ string, _ url.Values, _ string) ([]byte, int, error) {
					res := "123"
					b, _ := json.Marshal(res)
					return b, 200, nil
				}).Reset()
				_, err := StartRecord(ctx, users, screen, appID, roomID)
				So(err, ShouldNotEqual, nil)
			})

			Convey("error return", func() {
				defer ApplyMethod(reflect.TypeOf(client), "Json", func(_ *base.Client, _ string, _ url.Values, _ string) ([]byte, int, error) {
					res := `{"Service": "test", "Error":{"Code": "400", "Message": "testerr"}}`
					return []byte(res), 200, nil
				}).Reset()
				_, err := StartRecord(ctx, users, screen, appID, roomID)
				So(err, ShouldResemble, errors.New("testerr"))
			})

			Convey("success return", func() {
				defer ApplyMethod(reflect.TypeOf(client), "Json", func(_ *base.Client, _ string, _ url.Values, _ string) ([]byte, int, error) {
					res := `{"Service": "test", "Result": "ok"}`
					return []byte(res), 200, nil
				}).Reset()
				defer ApplyFunc(redis.SetRoomTaskID, func(_ context.Context, _, _ string) {
					return
				}).Reset()
				_, err := StartRecord(ctx, users, screen, appID, roomID)
				So(err, ShouldResemble, nil)
			})
		})
	})
}

func TestUpdateRecord(t *testing.T) {
	Convey("TestUpdateRecord", t, func() {
		ctx := context.Background()
		users := []string{"1"}
		screen := "1"
		appID := "testappid"
		roomID := "testroomid"

		Convey("taskid is null", func() {
			err := UpdateRecord(ctx, users, screen, appID, roomID, "")
			So(err, ShouldResemble, errors.New("record not started yet"))
		})

		Convey("taskid is not null", func() {
			Convey("query failed", func() {
				defer ApplyMethod(reflect.TypeOf(client), "Json", func(_ *base.Client, _ string, _ url.Values, _ string) ([]byte, int, error) {
					return nil, 400, errors.New("error")
				}).Reset()

				err := UpdateRecord(ctx, users, screen, appID, roomID, "xxx")
				So(err, ShouldResemble, errors.New("error"))
			})

			Convey("query success", func() {
				Convey("invaild json", func() {
					defer ApplyMethod(reflect.TypeOf(client), "Json", func(_ *base.Client, _ string, _ url.Values, _ string) ([]byte, int, error) {
						res := "123"
						return []byte(res), 200, nil
					}).Reset()
					err := UpdateRecord(ctx, users, screen, appID, roomID, "xxx")
					So(err, ShouldNotEqual, nil)
				})

				Convey("error return", func() {
					defer ApplyMethod(reflect.TypeOf(client), "Json", func(_ *base.Client, _ string, _ url.Values, _ string) ([]byte, int, error) {
						res := `{"Service": "test", "Error":{"Code": "400", "Message": "testerr"}}`
						return []byte(res), 200, nil
					}).Reset()
					err := UpdateRecord(ctx, users, screen, appID, roomID, "xxx")
					So(err, ShouldResemble, errors.New("testerr"))
				})

				Convey("success return", func() {
					defer ApplyMethod(reflect.TypeOf(client), "Json", func(_ *base.Client, _ string, _ url.Values, _ string) ([]byte, int, error) {
						res := `{"Service": "test", "Result": "ok"}`
						return []byte(res), 200, nil
					}).Reset()
					err := UpdateRecord(ctx, users, screen, appID, roomID, "xxx")
					So(err, ShouldResemble, nil)
				})
			})
		})
	})
}

func TestStopRecord(t *testing.T) {
	Convey("TestStopRecord", t, func() {
		ctx := context.Background()
		appID := "testappid"
		roomID := "testroomid"

		Convey("taskid is null", func() {
			err := StopRecord(ctx, appID, roomID, "")
			So(err, ShouldResemble, errors.New("record not started yet"))
		})

		Convey("taskid is not null", func() {
			Convey("query failed", func() {
				defer ApplyMethod(reflect.TypeOf(client), "Json", func(_ *base.Client, _ string, _ url.Values, _ string) ([]byte, int, error) {
					return nil, 400, errors.New("error")
				}).Reset()

				err := StopRecord(ctx, appID, roomID, "xxx")
				So(err, ShouldResemble, errors.New("error"))
			})

			Convey("query success", func() {
				Convey("invaild json", func() {
					defer ApplyMethod(reflect.TypeOf(client), "Json", func(_ *base.Client, _ string, _ url.Values, _ string) ([]byte, int, error) {
						res := "123"
						return []byte(res), 200, nil
					}).Reset()
					err := StopRecord(ctx, appID, roomID, "xxx")
					So(err, ShouldNotEqual, nil)
				})

				Convey("error return", func() {
					defer ApplyMethod(reflect.TypeOf(client), "Json", func(_ *base.Client, _ string, _ url.Values, _ string) ([]byte, int, error) {
						res := `{"Service": "test", "Error":{"Code": "400", "Message": "testerr"}}`
						return []byte(res), 200, nil
					}).Reset()
					err := StopRecord(ctx, appID, roomID, "xxx")
					So(err, ShouldResemble, errors.New("testerr"))
				})

				Convey("success return", func() {
					defer ApplyMethod(reflect.TypeOf(client), "Json", func(_ *base.Client, _ string, _ url.Values, _ string) ([]byte, int, error) {
						res := `{"Service": "test", "Result": "ok"}`
						return []byte(res), 200, nil
					}).Reset()
					err := StopRecord(ctx, appID, roomID, "xxx")
					So(err, ShouldResemble, nil)
				})
			})
		})
	})
}
