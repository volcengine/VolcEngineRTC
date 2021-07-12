package response

import (
	"encoding/json"
	"time"
)

type CommonResponse struct {
	Code      int         `json:"code"`
	Message   string      `json:"message"`
	Timestamp int64       `json:"timestamp"`
	Response  interface{} `json:"response"`
}

func NewCommonResponse(code int, message string, response interface{}) string {
	c := &CommonResponse{
		Code:      code,
		Message:   message,
		Timestamp: time.Now().UnixNano(),
		Response:  response,
	}
	resByte, err := json.Marshal(c)
	if err != nil {
		logs.Warnf("json marshal error, err: %v", err)
	}
	return string(resByte)
}
