package vc_service

import (
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/service/service_utils"
)

var eventHandler = map[string]service_utils.EventHandlerFunc{
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
	"deleteVideoRecord":     deleteVideoRecord,
}

func GetHandlerByEventName(event string) (service_utils.EventHandlerFunc, bool) {
	h, ok := eventHandler[event]
	return h, ok
}
