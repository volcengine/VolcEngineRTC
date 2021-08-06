package vc_models

type InformEvent string

const (
	UserMicStatusChange      InformEvent = "onUserMicStatusChange"
	UserCameraStatusChange   InformEvent = "onUserCameraStatusChange"
	HostChange               InformEvent = "onHostChange"
	UserJoinMeeting          InformEvent = "onUserJoinMeeting"
	UserLeaveMeeting         InformEvent = "onUserLeaveMeeting"
	ShareScreenStatusChanged InformEvent = "onShareScreenStatusChanged"
	Record                   InformEvent = "onRecord"
	MeetingEnd               InformEvent = "onMeetingEnd"
	MuteAll                  InformEvent = "onMuteAll"
	AskingMicOn              InformEvent = "onAskingMicOn"
	AskingCameraOn           InformEvent = "onAskingCameraOn"
	UserKickedOff            InformEvent = "onUserKickedOff"
	MuteUser                 InformEvent = "onMuteUser"
)

type UserInfo struct {
	UserID          string `json:"user_id"`
	UserName        string `json:"user_name"`
	UserUniformName string `json:"user_uniform_name"`
	RoomID          string `json:"room_id"`
	IsHost          bool   `json:"is_host"`
	IsMicOn         bool   `json:"is_mic_on"`
	IsCameraOn      bool   `json:"is_camera_on"`
	IsSharing       bool   `json:"is_sharing"`
	CreatedAt       int64  `json:"created_at"`
}

type UserIDInfo struct {
	UserID string `json:"user_id"`
}

type UserDeviceInfo struct {
	UserID string `json:"user_id"`
	Status bool   `json:"status"`
}

type HostInfo struct {
	FormerHostID string `json:"former_host_id"`
	HostID       string `json:"host_id"`
}

type UserInfoSlice []UserInfo

func (us UserInfoSlice) Len() int {
	return len(us)
}

func (us UserInfoSlice) Swap(i, j int) {
	us[i], us[j] = us[j], us[i]
}

func (us UserInfoSlice) Less(i, j int) bool {
	// 字典序排序
	// 但是字母开头有大小写不同的要排在一起，大写排在小写字母的前面
	// A a B b ...

	return compareStrLess(us[i].UserUniformName, us[j].UserUniformName)
}

func compareStrLess(s1, s2 string) bool {
	if len(s2) == 0 {
		return false
	}

	if len(s1) == 0 {
		return true
	}

	r1 := []rune(s1)[0]
	r2 := []rune(s2)[0]

	if r1 == r2 {
		return compareStrLess(s1[1:], s2[1:])
	}

	switch {
	case isLower(r1) && isUpper(r2):
		return r1-('a'-'A') < r2
	case isUpper(r1) && isLower(r2):
		return r1+('a'-'A') <= r2
	default:
		return r1 < r2
	}
}

func isLower(r rune) bool {
	if r >= 'a' && r <= 'z' {
		return true
	}
	return false
}
func isUpper(r rune) bool {
	if r >= 'A' && r <= 'Z' {
		return true
	}
	return false
}
