package record

import (
	"testing"

	. "github.com/agiledragon/gomonkey"
	. "github.com/smartystreets/goconvey/convey"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/config"
)

func TestGenLayout(t *testing.T) {
	Convey("TestGenLayout", t, func() {
		defer ApplyGlobalVar(&config.Config,
			config.Configuration{
				Resolution: "480p",
			}).Reset()

		users := []string{"1"}
		screen := ""

		res := genLayout(users, screen)

		expect := layout{
			LayoutMode: 2,
			CustomLayout: customLayout{
				Canvas: canvas{
					Width:      640,
					Height:     480,
					Background: "#000000",
				},
				Regions: []region{
					{
						StreamIndex:      0,
						LocationX:        0,
						LocationY:        0,
						WidthProportion:  1,
						HeightProportion: 1,
						RenderMode:       2,
					},
				},
			},
		}
		So(res, ShouldResemble, expect)

		users = []string{"1", "2"}
		res = genLayout(users, screen)
		expect = layout{
			LayoutMode: 2,
			CustomLayout: customLayout{
				Canvas: canvas{
					Width:      640,
					Height:     480,
					Background: "#000000",
				},
				Regions: []region{
					{
						StreamIndex:      0,
						LocationX:        0,
						LocationY:        0,
						WidthProportion:  0.5,
						HeightProportion: 1,
						RenderMode:       2,
					},
					{
						StreamIndex:      1,
						LocationX:        0.5,
						LocationY:        0,
						WidthProportion:  0.5,
						HeightProportion: 1,
						RenderMode:       2,
					},
				},
			},
		}
		So(res, ShouldResemble, expect)

		users = []string{"1", "2", "3", "4"}
		res = genLayout(users, screen)
		expect = layout{
			LayoutMode: 2,
			CustomLayout: customLayout{
				Canvas: canvas{
					Width:      640,
					Height:     480,
					Background: "#000000",
				},
				Regions: []region{
					{
						StreamIndex:      0,
						LocationX:        0,
						LocationY:        0,
						WidthProportion:  0.5,
						HeightProportion: 0.5,
						RenderMode:       2,
					},
					{
						StreamIndex:      1,
						LocationX:        0.5,
						LocationY:        0,
						WidthProportion:  0.5,
						HeightProportion: 0.5,
						RenderMode:       2,
					},
					{
						StreamIndex:      2,
						LocationX:        0,
						LocationY:        0.5,
						WidthProportion:  0.5,
						HeightProportion: 0.5,
						RenderMode:       2,
					},
					{
						StreamIndex:      3,
						LocationX:        0.5,
						LocationY:        0.5,
						WidthProportion:  0.5,
						HeightProportion: 0.5,
						RenderMode:       2,
					},
				},
			},
		}
		So(res, ShouldResemble, expect)

		users = []string{"1", "2", "3", "4", "5"}
		res = genLayout(users, screen)
		expect = layout{
			LayoutMode: 2,
			CustomLayout: customLayout{
				Canvas: canvas{
					Width:      640,
					Height:     480,
					Background: "#000000",
				},
				Regions: []region{
					{
						StreamIndex:      0,
						LocationX:        0,
						LocationY:        0,
						WidthProportion:  float32(1) / float32(3),
						HeightProportion: float32(1) / float32(3),
						RenderMode:       2,
					},
					{
						StreamIndex:      1,
						LocationX:        float32(1) / float32(3),
						LocationY:        0,
						WidthProportion:  float32(1) / float32(3),
						HeightProportion: float32(1) / float32(3),
						RenderMode:       2,
					},
					{
						StreamIndex:      2,
						LocationX:        float32(2) / float32(3),
						LocationY:        0,
						WidthProportion:  float32(1) / float32(3),
						HeightProportion: float32(1) / float32(3),
						RenderMode:       2,
					},
					{
						StreamIndex:      3,
						LocationX:        0,
						LocationY:        float32(1) / float32(3),
						WidthProportion:  float32(1) / float32(3),
						HeightProportion: float32(1) / float32(3),
						RenderMode:       2,
					},
					{
						StreamIndex:      4,
						LocationX:        float32(1) / float32(3),
						LocationY:        float32(1) / float32(3),
						WidthProportion:  float32(1) / float32(3),
						HeightProportion: float32(1) / float32(3),
						RenderMode:       2,
					},
				},
			},
		}
		So(res, ShouldResemble, expect)

		users = []string{"1", "2", "3"}
		screen = "1"
		res = genLayout(users, screen)
		expect = layout{
			LayoutMode: 2,
			CustomLayout: customLayout{
				Canvas: canvas{
					Width:      640,
					Height:     480,
					Background: "#000000",
				},
				Regions: []region{
					{
						StreamIndex:      0,
						LocationX:        0,
						LocationY:        0,
						WidthProportion:  0.125,
						HeightProportion: 0.125,
						RenderMode:       2,
					},
					{
						StreamIndex:      1,
						LocationX:        0.125,
						LocationY:        0,
						WidthProportion:  0.125,
						HeightProportion: 0.125,
						RenderMode:       2,
					},
					{
						StreamIndex:      2,
						LocationX:        0.25,
						LocationY:        0,
						WidthProportion:  0.125,
						HeightProportion: 0.125,
						RenderMode:       2,
					},
					{
						StreamIndex:      3,
						LocationX:        0,
						LocationY:        0.125,
						WidthProportion:  1,
						HeightProportion: 0.875,
						RenderMode:       2,
					},
				},
			},
		}
		So(res, ShouldResemble, expect)
	})
}
