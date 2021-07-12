package record

import (
	"testing"

	. "github.com/smartystreets/goconvey/convey"
)

func TestGenTargetStreams(t *testing.T) {
	Convey("TestGenTargetStreams", t, func() {
		users := []string{"1", "2", "3"}
		screen := "1"

		res := genTargetStreams(users, screen)

		expect := streamList{
			StreamList: []stream{
				{
					Index:  0,
					UserID: "1",
				},
				{
					Index:  1,
					UserID: "2",
				},
				{
					Index:  2,
					UserID: "3",
				},
				{
					Index:      3,
					UserID:     "1",
					StreamType: 1,
				},
			},
		}

		So(res, ShouldResemble, expect)
	})
}
