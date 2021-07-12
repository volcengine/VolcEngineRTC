package response

import (
	"testing"

	. "github.com/smartystreets/goconvey/convey"
)

func TestNewInformToClient(t *testing.T) {
	Convey("TestNewInformToClient", t, func() {
		NewInformToClient("testevent", nil)
	})
}
