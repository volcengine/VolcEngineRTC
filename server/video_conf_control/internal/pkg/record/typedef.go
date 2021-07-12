package record

type startRecordParam struct {
	AppID         string     `json:"AppId"`
	BussinessID   string     `json:"BussinessId,omitempty"`
	RoomID        string     `json:"RoomId"`
	TaskID        string     `json:"TaskId"`
	RecordMode    int        `json:"RecordMode"`
	TargetStreams streamList `json:"TargetStreams"`
	Layout        layout     `json:"Layout"`
	Encode        encode     `json:"Encode,omitempty"`
	Control       control    `json:"Control,omitempty"`
}

type updateRecordParam struct {
	AppID         string     `json:"AppId"`
	BussinessID   string     `json:"BussinessId,omitempty"`
	RoomID        string     `json:"RoomId"`
	TaskID        string     `json:"TaskId"`
	TargetStreams streamList `json:"TargetStreams"`
	Layout        layout     `json:"Layout"`
}

type stopRecordParam struct {
	AppID       string `json:"AppId"`
	BussinessID string `json:"BussinessId,omitempty"`
	RoomID      string `json:"RoomId"`
	TaskID      string `json:"TaskId"`
}

type streamList struct {
	StreamList []stream `json:"StreamList"`
}

type stream struct {
	Index      int    `json:"Index"`
	UserID     string `json:"UserId"`
	StreamType int    `json:"StreamType,omitempty"` // The default is normal flow, 1 means screen flow
}

type layout struct {
	LayoutMode           int          `json:"LayoutMode"`                     // Fixed here as 2, custom layout
	MainVideoStreamIndex int          `json:"MainVideoStreamIndex,omitempty"` // The parameter is not effective here and should not be set
	CustomLayout         customLayout `json:"CustomLayout"`
}

type customLayout struct {
	Canvas  canvas   `json:"Canvas,omitempty"`
	Regions []region `json:"Regions"`
}

type canvas struct {
	Width      int    `json:"Width,omitempty"`
	Height     int    `json:"Height,omitempty"`
	Background string `json:"Background,omitempty"`
}

type region struct {
	StreamIndex      int     `json:"StreamIndex"`
	LocationX        float32 `json:"LocationX"`
	LocationY        float32 `json:"LocationY"`
	WidthProportion  float32 `json:"WidthProportion"`
	HeightProportion float32 `json:"HeightProportion"`
	ZOrder           int     `json:"ZOrder,omitempty"`
	Alpha            float32 `json:"Alpha,omitempty"`
	RenderMode       int     `json:"RenderMode,omitempty"`
}

type encode struct {
	VideoCodec      int `json:"VideoCodec,omitempty"`
	VideoBitrate    int `json:"VideoBitrate,omitempty"`
	VideoWidth      int `json:"VideoWidth,omitempty"`
	VideoHeight     int `json:"VideoHeight,omitempty"`
	VideoFps        int `json:"VideoFps,omitempty"`
	VideoGop        int `json:"VideoGop,omitempty"`
	AudioCodec      int `json:"AudioCodec,omitempty"`
	AudioProfile    int `json:"AudioProfile,omitempty"`
	AudioBitrate    int `json:"AudioBitrate,omitempty"`
	AudioSampleRate int `json:"AudioSampleRate,omitempty"`
	AudioChannels   int `json:"AudioChannels,omitempty"`
}

type control struct {
	MediaType              int32 `json:"MediaType,omitempty"`
	FrameInterpolationMode int32 `json:"FrameInterpolationMode,omitempty"`
}

type response struct {
	Service   string      `json:"Service"`
	Region    string      `json:"Region"`
	RequestID string      `json:"RequestId"`
	Action    string      `json:"Action"`
	Version   string      `json:"Version"`
	Result    interface{} `json:"Result,omitempty"`
	Error     commonError `json:"Error,omitempty"`
}

type commonError struct {
	Code    string `json:"Code"`
	Message string `json:"Message"`
}

type recordFile struct {
	VID        string   `json:"Vid"`
	Duration   int64    `json:"Duration"`  // Unit ms
	Size       int64    `json:"Size"`      // Unit ms
	StartTime  int64    `json:"StartTime"` // Unit ms
	StreamList []stream `json:"StreamList"`
}
