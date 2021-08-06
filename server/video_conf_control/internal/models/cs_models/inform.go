package cs_models

type InformEvent string

const (
	OnCsJoinMeeting   InformEvent = "onCsJoinMeeting"
	OnCsLeaveMeeting  InformEvent = "onCsLeaveMeeting"
	OnCsRaiseHandsMic InformEvent = "onCsRaiseHandsMic"
	OnCsInviteMic     InformEvent = "onCsInviteMic"
	OnCsMicOn         InformEvent = "onCsMicOn"
	OnCsMicOff        InformEvent = "onCsMicOff"
	OnCsMuteMic       InformEvent = "onCsMuteMic"
	OnCsUnmuteMic     InformEvent = "onCsUnmuteMic"
	OnCsMeetingEnd    InformEvent = "onCsMeetingEnd"
	OnCsHostChange    InformEvent = "onCsHostChange"
)

type UserInfo struct {
	UserID       string `json:"user_id"`
	UserName     string `json:"user_name"`
	IsHost       bool   `json:"is_host"`
	UserStatus   int    `json:"user_status"`
	IsMicOn      bool   `json:"is_mic_on"`
	CreatedAt    int64  `json:"created_at"`
	RaiseHandsAt int64  `json:"raise_hands_at"`
}

type UserIDInfo struct {
	UserID string `json:"user_id"`
}

type UserDeviceInfo struct {
	UserID string `json:"user_id"`
	Status bool   `json:"status"`
}

type HostInfo struct {
	FormerHostID string    `json:"former_host_id"`
	HostInfo     *UserInfo `json:"host_info"`
}

type UserInfoSlice []*UserInfo

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

	return compareStrLess(us[i].UserName, us[j].UserName)
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

type UserInfoJoinMeetingSlice []*UserInfo

func (us UserInfoJoinMeetingSlice) Len() int {
	return len(us)
}

func (us UserInfoJoinMeetingSlice) Swap(i, j int) {
	us[i], us[j] = us[j], us[i]
}

func (us UserInfoJoinMeetingSlice) Less(i, j int) bool {
	return us[i].CreatedAt < us[j].CreatedAt
}

type UserInfoRaiseHandsSlice []*UserInfo

func (us UserInfoRaiseHandsSlice) Len() int {
	return len(us)
}

func (us UserInfoRaiseHandsSlice) Swap(i, j int) {
	us[i], us[j] = us[j], us[i]
}

func (us UserInfoRaiseHandsSlice) Less(i, j int) bool {
	return us[i].RaiseHandsAt > us[j].RaiseHandsAt
}

type RoomIDInfo struct {
	RoomID string `json:"room_id,omitempty"`
}

type RoomInfo struct {
	RoomID      string `json:"room_id"`
	RoomName    string `json:"room_name"`
	HostID      string `json:"host_id"`
	HostName    string `json:"host_name"`
	UserCounts  int    `json:"user_counts"`
	MiconCounts int    `json:"micon_counts"`
	CreatedAt   int64  `json:"created_at"`
	Now         int64  `json:"now"`
}

type RoomInfoSlice []*RoomInfo

func (ms RoomInfoSlice) Len() int {
	return len(ms)
}

func (ms RoomInfoSlice) Swap(i, j int) {
	ms[i], ms[j] = ms[j], ms[i]
}

func (ms RoomInfoSlice) Less(i, j int) bool {
	return ms[i].CreatedAt > ms[j].CreatedAt
}
