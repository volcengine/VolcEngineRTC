package record

import "github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/config"

func genLayout(users []string, screen string) layout {
	switch {
	case screen != "":
		return layout{
			LayoutMode:   2,
			CustomLayout: screenLayout(users, screen),
		}
	case len(users) == 1:
		return layout{
			LayoutMode:   2,
			CustomLayout: userLayout1(users[0]),
		}
	case len(users) == 2:
		return layout{
			LayoutMode:   2,
			CustomLayout: userLayout2(users),
		}
	case len(users) <= 4:
		return layout{
			LayoutMode:   2,
			CustomLayout: userLayout4(users),
		}
	case len(users) <= 9:
		return layout{
			LayoutMode:   2,
			CustomLayout: userLayout9(users),
		}
	default:
		return layout{}
	}
}

// Screen sharing flow layout
func screenLayout(users []string, screen string) customLayout {
	r := make([]region, 0)

	// User layout
	for idx := range users {
		r = append(r, region{
			StreamIndex:      idx,
			LocationX:        float32(idx) / 8,
			LocationY:        0,
			WidthProportion:  0.125,
			HeightProportion: 0.125,
			RenderMode:       2,
		})
	}

	// Screen flow layout
	r = append(r, region{
		StreamIndex:      len(users),
		LocationX:        0,
		LocationY:        0.125,
		WidthProportion:  1,
		HeightProportion: 0.875,
		RenderMode:       2,
	})

	return customLayout{
		Regions: r,
		Canvas:  customCanvas(),
	}
}

// Layout when the number of users is 1
func userLayout1(user string) customLayout {
	r := make([]region, 0)

	r = append(r, region{
		StreamIndex:      0,
		LocationX:        0,
		LocationY:        0,
		WidthProportion:  1,
		HeightProportion: 1,
		RenderMode:       2,
	})

	return customLayout{
		Regions: r,
		Canvas:  customCanvas(),
	}
}

// Layout when the number of users is 2
func userLayout2(users []string) customLayout {
	r := make([]region, 0)

	for idx := range users {
		r = append(r, region{
			StreamIndex:      idx,
			LocationX:        float32(idx) / 2,
			LocationY:        0,
			WidthProportion:  0.5,
			HeightProportion: 1,
			RenderMode:       2,
		})
	}

	return customLayout{
		Regions: r,
		Canvas:  customCanvas(),
	}
}

// Layout when the number of users is less than or equal to 4
func userLayout4(users []string) customLayout {
	r := make([]region, 0)

	for idx := range users {
		row := idx / 2
		col := idx % 2
		r = append(r, region{
			StreamIndex:      idx,
			LocationX:        float32(col) / 2,
			LocationY:        float32(row) / 2,
			WidthProportion:  0.5,
			HeightProportion: 0.5,
			RenderMode:       2,
		})
	}

	return customLayout{
		Regions: r,
		Canvas:  customCanvas(),
	}
}

// Layout when the number of users is less than or equal to 9
func userLayout9(users []string) customLayout {
	r := make([]region, 0)

	for idx := range users {
		row := idx / 3
		col := idx % 3
		r = append(r, region{
			StreamIndex:      idx,
			LocationX:        float32(col) / 3,
			LocationY:        float32(row) / 3,
			WidthProportion:  float32(1) / float32(3),
			HeightProportion: float32(1) / float32(3),
			RenderMode:       2,
		})
	}

	return customLayout{
		Regions: r,
		Canvas:  customCanvas(),
	}
}

func customCanvas() canvas {
	switch config.Config.Resolution {
	case "480":
		return canvas{
			Width:      640,
			Height:     480,
			Background: "#000000",
		}
	case "720":
		return canvas{
			Width:      960,
			Height:     720,
			Background: "#000000",
		}
	case "1080":
		return canvas{
			Width:      1440,
			Height:     1080,
			Background: "#000000",
		}
	default:
		return canvas{
			Width:      640,
			Height:     480,
			Background: "#000000",
		}
	}
}
