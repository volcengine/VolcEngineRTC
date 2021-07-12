package record

import (
	"context"
	"encoding/json"
	"errors"
	"net/http"
	"net/url"
	"strings"
	"time"

	"github.com/TTvcloud/vcloud-sdk-golang/base"
	uuid "github.com/satori/go.uuid"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/config"
)

var client *base.Client

const (
	startRecord  = "StartRecord"
	updateRecord = "UpdateRecord"
	stopRecord   = "StopRecord"
	version      = "2020-12-01"
)

func Init() {
	serviceInfo := &base.ServiceInfo{
		Timeout:     5 * time.Second,
		Host:        config.Config.PostProcessingURL,
		Header:      getHTTPHeader(),
		Credentials: base.Credentials{Region: base.RegionCnNorth1, Service: "rtc"},
	}

	apiInfoList := map[string]*base.ApiInfo{
		startRecord: {
			Method: http.MethodPost,
			Path:   getActionPath("start"),
			Query: url.Values{
				"Action":  []string{startRecord},
				"Version": []string{version},
			},
		},
		updateRecord: {
			Method: http.MethodPost,
			Path:   getActionPath("update"),
			Query: url.Values{
				"Action":  []string{updateRecord},
				"Version": []string{version},
			},
		},
		stopRecord: {
			Method: http.MethodPost,
			Path:   getActionPath("stop"),
			Query: url.Values{
				"Action":  []string{stopRecord},
				"Version": []string{version},
			},
		},
	}

	client = base.NewClient(serviceInfo, apiInfoList)
	client.SetAccessKey(config.Config.PostProcessingAK)
	client.SetSecretKey(config.Config.PostProcessingSK)
}

func getActionPath(action string) string {
	if strings.Contains(env.PSM(), "_test") {
		return "/media_adapter/openapi/v20201201/record/" + action
	}
	return "/"
}

func getHTTPHeader() http.Header {
	if strings.Contains(env.PSM(), "_test") {
		return http.Header{
			"Accept": []string{"application/json"},
			// For testing use only
			"X-Top-Account-Id": []string{"test"},
			"X-Top-Request-Id": []string{"test"},
			"X-Top-Service":    []string{"test"},
			"X-Top-Region":     []string{"test"},
		}
	}
	return http.Header{
		"Accept": []string{"application/json"},
	}
}

func StartRecord(ctx context.Context, users []string, screen, appID, roomID string) (string, error) {
	taskID := getUUID()
	param := genStartParam(users, screen, appID, roomID, taskID)
	logs.CtxInfo(ctx, "roomID: %s StartRecord, param: %s", roomID, param)
	res, code, err := client.Json(startRecord, nil, param)

	if err != nil || code != 200 {
		logs.CtxInfo(ctx, "start record error, roomID: %s, taskID: %s, res: %s", roomID, taskID, string(res))
		return "", err
	}

	var r response
	if err := json.Unmarshal(res, &r); err != nil {
		logs.CtxInfo(ctx, "parse start record response error, err: %v, res: %v", err, string(res))
		return "", err
	}

	logs.CtxInfo(ctx, "StartRecord response: %v", r)
	// Post-processing return, whether it is successful without code flag
	// A result field will be returned when successful, so result is not empty to express a successful request
	if r.Result == nil {
		return "", errors.New(r.Error.Message)
	}

	return taskID, nil
}

func UpdateRecord(ctx context.Context, users []string, screen, appID, roomID, taskID string) error {
	if taskID == "" {
		logs.CtxWarn(ctx, "record not started yet, roomID: %s", roomID)
		return errors.New("record not started yet")
	}

	param := genUpdateParam(users, screen, appID, roomID, taskID)
	logs.CtxInfo(ctx, "roomID: %s UpdateRecord, param: %s", roomID, param)
	res, code, err := client.Json(updateRecord, nil, param)

	if err != nil || code != 200 {
		logs.CtxInfo(ctx, "update record error, roomID: %s, taskID: %s, res: %s", roomID, taskID, string(res))
		return err
	}

	var r response
	if err := json.Unmarshal(res, &r); err != nil {
		logs.CtxInfo(ctx, "parse update record response error, err: %v, res: %v", err, res)
		return err
	}

	logs.CtxInfo(ctx, "UpdateRecord response: %v", r)
	// Post-processing return, whether it is successful without code flag
	// A result field will be returned when successful, so result is not empty to express a successful request
	if r.Result == nil {
		return errors.New(r.Error.Message)
	}
	return nil
}

func StopRecord(ctx context.Context, appID, roomID, taskID string) error {
	if taskID == "" {
		logs.CtxWarn(ctx, "record not started yet, roomID: %s", roomID)
		return errors.New("record not started yet")
	}

	param := genStopParam(appID, roomID, taskID)
	logs.CtxInfo(ctx, "roomID: %s StopRecord, param: %s", roomID, param)
	res, code, err := client.Json(stopRecord, nil, param)

	if err != nil || code != 200 {
		logs.CtxInfo(ctx, "stop record error, roomID: %s, taskID: %s, res: %s", roomID, taskID, string(res))
		return err
	}

	var r response
	if err := json.Unmarshal(res, &r); err != nil {
		logs.CtxInfo(ctx, "parse stop record response error, err: %v, res: %v", err, res)
	}

	logs.CtxInfo(ctx, "StopRecord response: %v", r)
	// Post-processing return, whether it is successful without code flag
	// A result field will be returned when successful, so result is not empty to express a successful request
	if r.Result == nil {
		return errors.New(r.Error.Message)
	}
	return nil
}

func getUUID() string {
	return uuid.Must(uuid.NewV4(), nil).String()
}

func genStartParam(users []string, screen, appID, roomID, taskID string) string {
	p := startRecordParam{
		AppID:         appID,
		RoomID:        roomID,
		TaskID:        taskID,
		RecordMode:    0, // Mixed stream recording
		TargetStreams: genTargetStreams(users, screen),
		Layout:        genLayout(users, screen),
	}

	if r, err := json.Marshal(p); err == nil {
		return string(r)
	}
	return ""
}

func genUpdateParam(users []string, screen, appID, roomID, taskID string) string {
	p := updateRecordParam{
		AppID:         appID,
		RoomID:        roomID,
		TaskID:        taskID,
		TargetStreams: genTargetStreams(users, screen),
		Layout:        genLayout(users, screen),
	}

	if r, err := json.Marshal(p); err == nil {
		return string(r)
	}
	return ""
}

func genStopParam(appID, roomID, taskID string) string {
	p := stopRecordParam{
		AppID:  appID,
		RoomID: roomID,
		TaskID: taskID,
	}

	if r, err := json.Marshal(p); err == nil {
		return string(r)
	}
	return ""
}
