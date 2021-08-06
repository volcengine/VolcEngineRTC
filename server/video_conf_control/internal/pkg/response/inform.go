package response

import (
	"encoding/json"
	"log"
	"time"
)

type inform struct {
	Event     string      `json:"event"`
	Timestamp int64       `json:"timestamp"`
	Data      interface{} `json:"data"`
}

func NewInformToClient(event string, data interface{}) string {
	info := inform{
		Event:     event,
		Timestamp: time.Now().UnixNano(),
		Data:      data,
	}

	infoByte, err := json.Marshal(info)
	if err != nil {
		log.Printf("json marshal error, input: %v, err: %v", info, err)
	}

	return string(infoByte)
}
