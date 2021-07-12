package db

import (
	"time"

	"gorm.io/gorm"
)

const (
	INACTIVE = iota
	ACTIVE
	RECONNECTING
)

var db *gorm.DB

// Open initializes db session based on db address and db name.
func Open(psm, name string) {
	var err error
	db, err = gorm.Open(
		bytedgorm.MySQL(psm, name), // Turn off read-write separation
		bytedgorm.WithDefaults(),
		bytedgorm.WithSingularTable(),
	)
	if err != nil {
		panic(err)
	}
}

// CleanDB only used in test env.
func CleanDB() {
	db.Where("1 = 1").Delete(&ConferenceUser{})
	db.Where("1 = 1").Delete(&ConferenceRoom{})
	db.Where("1 = 1").Delete(&ConferenceConnection{})
	db.Where("1 = 1").Delete(&ConferenceVideoRecord{})
}

type ConferenceConnection struct {
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

type ConferenceUser struct {
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

type ConferenceRoom struct {
	ID        int64     `gorm:"column:id" json:"id"`
	AppID     string    `gorm:"column:app_id" json:"app_id"`
	RoomID    string    `gorm:"column:room_id" json:"room_id"`
	State     bool      `gorm:"column:state" json:"state"`
	Record    bool      `gorm:"column:record" json:"record"`
	CreatedAt time.Time `gorm:"column:created_at" json:"created_at"`
	UpdatedAt time.Time `gorm:"column:updated_at" json:"updated_at"`
}

type ConferenceVideoRecord struct {
	ID        int64     `gorm:"column:id" json:"id"`
	AppID     string    `gorm:"column:app_id" json:"app_id"`
	RoomID    string    `gorm:"column:room_id" json:"room_id"`
	VID       string    `gorm:"column:vid" json:"vid"`
	CreatedAt time.Time `gorm:"column:created_at" json:"created_at"`
	UpdatedAt time.Time `gorm:"column:updated_at" json:"updated_at"`
}
