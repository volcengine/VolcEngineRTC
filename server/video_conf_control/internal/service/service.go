package service

import (
	"context"

	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/kitex_gen/vc_control"
)

type eventHandlerFunc func(ctx context.Context, param *vc_control.TEventParam)

var eventHandler = map[string]eventHandlerFunc{
	"connection":            connection,
	"disconnect":            disconnect,
	"disconnection":         disconnect,
	"userReconnect":         reconnect,
	"getAppID":              getAppID,
	"joinMeeting":           joinMeeting,
	"leaveMeeting":          leaveMeeting,
	"turnOnMic":             turnOnMic,
	"turnOffMic":            turnOffMic,
	"turnOnCamera":          turnOnCamera,
	"turnOffCamera":         turnOffCamera,
	"getMeetingUserInfo":    getMeetingUserInfo,
	"getMeetingInfo":        getMeetingInfo,
	"changeHost":            changeHost,
	"muteUser":              muteUser,
	"askMicOn":              askMicOn,
	"askCameraOn":           askCameraOn,
	"endMeeting":            endMeeting,
	"startShareScreen":      startShareScreen,
	"endShareScreen":        endShareScreen,
	"recordMeeting":         recordMeeting,
	"getHistoryVideoRecord": getHistoryVideoRecord,
	"updateRecordLayout":    updateRecordLayout,
}

func GetHandlerByEventName(event string) (eventHandlerFunc, bool) {
	h, ok := eventHandler[event]
	return h, ok
}
