package metrics

import (
	"testing"
	"time"

	"github.com/stretchr/testify/assert"
)

func TestInitMetrics(t *testing.T) {
	init := InitMetrics("bytertc.server.vc_control", true)
	assert.Equal(t, init, true)
}

func TestEmit(t *testing.T) {
	EmitCounter("ok", 1)
	EmitCounterNoErr("ok1", 1)
	EmitTimer("ok2", time.Now().UnixNano())
	EmitStore("ok3", "fei")
}
