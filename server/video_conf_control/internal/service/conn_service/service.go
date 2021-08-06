package conn_service

import (
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/service/service_utils"
)

var eventHandler = map[string]service_utils.EventHandlerFunc{
	"connection":    connection,
	"disconnect":    disconnect,
	"disconnection": disconnect,
}

func GetHandlerByEventName(event string) (service_utils.EventHandlerFunc, bool) {
	h, ok := eventHandler[event]
	return h, ok
}
