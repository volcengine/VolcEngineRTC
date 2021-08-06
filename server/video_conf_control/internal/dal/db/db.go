package db

import (
	"gorm.io/driver/mysql"
	"gorm.io/gorm"
	"time"
)

const (
	INACTIVE = iota
	ACTIVE
	RECONNECTING
)

type UserStatusType int

const (
	UserStatusAudience UserStatusType = iota
	UserStatusRaiseHands
	UserStatusOnMicrophone
)

var Client *gorm.DB

func Open(dsn string) {
	var err error
	Client, err = gorm.Open(mysql.Open(dsn))
	if err != nil {
		panic(err)
	}
}

type MeetingConnection struct {
	ID        int64     `gorm:"column:id" json:"id"`
	AppID     string    `gorm:"column:app_id" json:"app_id"`
	ConnID    string    `gorm:"column:conn_id" json:"conn_id"`
	Addr      string    `gorm:"column:addr" json:"addr"`
	Addr6     string    `gorm:"column:addr6" json:"addr6"`
	State     int       `gorm:"column:state" json:"state"`
	DeviceID  string    `gorm:"column:device_id" json:"device_id"`
	CreatedAt time.Time `gorm:"column:created_at" json:"created_at"`
	UpdatedAt time.Time `gorm:"column:updated_at" json:"updated_at"`
}

type MeetingUser struct {
	ID         int64     `gorm:"column:id" json:"id"`
	AppID      string    `gorm:"column:app_id" json:"app_id"`
	UserID     string    `gorm:"column:user_id" json:"user_id"`
	RoomID     string    `gorm:"column:room_id" json:"room_id"`
	ConnID     string    `gorm:"column:conn_id" json:"conn_id"`
	State      int       `gorm:"column:state" json:"state"`
	IsHost     bool      `gorm:"column:is_host" json:"is_host"`
	IsMicOn    bool      `gorm:"column:is_mic_on" json:"is_mic_on"`
	IsCameraOn bool      `gorm:"column:is_camera_on" json:"is_camera_on"`
	IsSharing  bool      `gorm:"column:is_sharing" json:"is_sharing"`
	DeviceID   string    `gorm:"column:device_id" json:"device_id"`
	CreatedAt  time.Time `gorm:"column:created_at" json:"created_at"`
	UpdatedAt  time.Time `gorm:"column:updated_at" json:"updated_at"`
}

type MeetingRoom struct {
	ID        int64     `gorm:"column:id" json:"id"`
	AppID     string    `gorm:"column:app_id" json:"app_id"`
	RoomID    string    `gorm:"column:room_id" json:"room_id"`
	State     bool      `gorm:"column:state" json:"state"`
	Record    bool      `gorm:"column:record" json:"record"`
	CreatedAt time.Time `gorm:"column:created_at" json:"created_at"`
	UpdatedAt time.Time `gorm:"column:updated_at" json:"updated_at"`
}

type MeetingVideoRecord struct {
	ID        int64     `gorm:"column:id" json:"id"`
	AppID     string    `gorm:"column:app_id" json:"app_id"`
	RoomID    string    `gorm:"column:room_id" json:"room_id"`
	VID       string    `gorm:"column:vid" json:"vid"`
	State     int       `gorm:"column:state" json:"state"`
	UserID    string    `gorm:"column:user_id" json:"user_id"`
	CreatedAt time.Time `gorm:"column:created_at" json:"created_at"`
	UpdatedAt time.Time `gorm:"column:updated_at" json:"updated_at"`
}

type CsMeetingUser struct {
	ID           int64     `gorm:"column:id" json:"id"`
	AppID        string    `gorm:"column:app_id" json:"app_id"`
	UserID       string    `gorm:"column:user_id" json:"user_id"`
	UserName     string    `gorm:"column:user_name" json:"user_name"`
	UserStatus   int       `gorm:"column:user_status" json:"user_status"`
	RoomID       string    `gorm:"column:room_id" json:"room_id"`
	ConnID       string    `gorm:"column:conn_id" json:"conn_id"`
	State        int       `gorm:"column:state" json:"state"`
	IsHost       bool      `gorm:"column:is_host" json:"is_host"`
	IsMicOn      bool      `gorm:"column:is_mic_on" json:"is_mic_on"`
	DeviceID     string    `gorm:"column:device_id" json:"device_id"`
	RaiseHandsAt time.Time `gorm:"column:raise_hands_at" json:"raise_hands_at"`
	CreatedAt    time.Time `gorm:"column:created_at" json:"created_at"`
	UpdatedAt    time.Time `gorm:"column:updated_at" json:"updated_at"`
}

type CsMeetingRoom struct {
	ID        int64     `gorm:"column:id" json:"id"`
	AppID     string    `gorm:"column:app_id" json:"app_id"`
	RoomID    string    `gorm:"column:room_id" json:"room_id"`
	RoomName  string    `gorm:"column:room_name" json:"room_name"`
	State     bool      `gorm:"column:state" json:"state"`
	CreatedAt time.Time `gorm:"column:created_at" json:"created_at"`
	UpdatedAt time.Time `gorm:"column:updated_at" json:"updated_at"`
}

type UserProfile struct {
	ID        int64     `gorm:"column:id" json:"id"`
	UserID    string    `gorm:"column:user_id" json:"user_id"`
	UserName  string    `gorm:"column:user_name" json:"user_name"`
	CreatedAt time.Time `gorm:"column:created_at" json:"created_at"`
	UpdatedAt time.Time `gorm:"column:updated_at" json:"updated_at"`
}
