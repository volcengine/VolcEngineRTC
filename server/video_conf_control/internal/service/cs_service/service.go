package cs_service

import (
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/service/service_utils"
)

var eventHandler = map[string]service_utils.EventHandlerFunc{
	"csUserReconnect": reconnect,
	"csGetAppID":      getAppID,
	"csGetMeetings":   getMeetings,
	"csCreateMeeting": createMeeting,
	"csJoinMeeting":   joinMeeting,
	"csLeaveMeeting":  leaveMeeting,
	"csGetRaiseHands": getRaiseHands,
	"csGetAudiences":  getAudiences,
	"csInviteMic":     inviteMic,
	"csConfirmMic":    confirmMic,
	"csRaiseHandsMic": raiseHandsMic,
	"csAgreeMic":      agreeMic,
	"csOffSelfMic":    offSelfMic,
	"csOffMic":        offMic,
	"csMuteMic":       muteMic,
	"csUnmuteMic":     unMuteMic,
}

func GetHandlerByEventName(event string) (service_utils.EventHandlerFunc, bool) {
	h, ok := eventHandler[event]
	return h, ok
}
