package response

import (
	"testing"

	. "github.com/smartystreets/goconvey/convey"
)

func TestResponse(t *testing.T) {
	Convey("TestResponse", t, func() {
		NewCommonResponse(200, "ok", nil)
	})
}
