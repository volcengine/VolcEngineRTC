package metrics

import (
	"os"
	"strconv"
	"time"
)

type T = metrics.T

const (
	EventQPS     = "event_qps"
	EventLatency = "event_lantency"

	ChooseAddrError     = "choose_addr_error"
	ChooseFrontierIPQPS = "choose_frontier_ip_qps"

	LockSuccessQps = "lock_success_qps"
	LockFailedQps  = "lock_failed_qps"

	RoomCount = "room_count"
	UserCount = "user_count"
)

var Emitter *metrics.MetricsClientV2
var Psm string
var EnableMetrics = true

func InitMetrics(psm string, enableMetrics bool) bool {
	Psm = psm
	if !enableMetrics {
		EnableMetrics = false
	}
	metrics.AddGlobalTag("pid", strconv.Itoa(os.Getpid()))
	Emitter = metrics.NewDefaultMetricsClientV2(Psm, EnableMetrics)
	return true
}

func EmitStore(name string, value interface{}, tags ...T) {
	err := Emitter.EmitStore(name, value, tags...)
	if err != nil {
		logs.Warnf("metrics error: %v", err)
	}
}

func EmitCounter(name string, value interface{}, tags ...T) {
	err := Emitter.EmitCounter(name, value, tags...)
	if err != nil {
		logs.Warnf("metrics error: %v", err)
	}
}

func EmitRateCounter(name string, value interface{}, tags ...T) {
	err := Emitter.EmitRateCounter(name, value, tags...)
	if err != nil {
		logs.Warnf("metrics error: %v", err)
	}
}

func EmitTimer(name string, start interface{}, tags ...T) {
	s, ok := start.(int64)
	if !ok {
		s = start.(time.Time).UnixNano()
	}

	err := Emitter.EmitTimer(name, time.Now().UnixNano()-s, tags...)
	if err != nil {
		logs.Warnf("metrics error: %v", err)
	}
}

func EmitCounterNoErr(name string, value interface{}, tags ...T) {
	err := Emitter.EmitCounter(name, value, tags...)
	if err != nil {
		logs.Warnf("metrics counter error: %s", err)
	}
}
