package token

import (
	"bytes"
	"crypto/hmac"
	"crypto/sha256"
	"encoding/base64"
	"encoding/binary"
	"io"
	"math/rand"
	"sort"
	"time"
)

const (
	Version = "001"
)

type Privilege uint16

const (
	PrivPublishStream Privilege = iota
	privPublishAudioStream
	privPublishVideoStream
	privPublishDataStream
	PrivSubscribeStream
	PrivSwitchRTCProvider
)

type Token struct {
	AppID      string
	AppKey     string
	RoomID     string
	UserID     string
	IssuedAt   uint32
	ExpireAt   uint32
	Nonce      uint32
	Privileges map[uint16]uint32
	Signature  string
}

type GenerateParam struct {
	AppID        string
	AppKey       string
	RoomID       string
	UserID       string
	ExpireAt     int64
	CanPublish   bool
	CanSubscribe bool
	CanSwitch    bool
}

func init() {
	rand.Seed(time.Now().UnixNano())
}

func random(min int, max int) int {
	return rand.Intn(max-min) + min
}

func New(appID, appKey, roomID, userID string) *Token {
	return &Token{
		AppID:      appID,
		AppKey:     appKey,
		RoomID:     roomID,
		UserID:     userID,
		IssuedAt:   uint32(time.Now().Unix()),
		Nonce:      uint32(random(1, 99999999)),
		Privileges: make(map[uint16]uint32),
	}
}

func (t *Token) ExpireTime(et time.Time) {
	if !et.IsZero() {
		t.ExpireAt = uint32(et.Unix())
	}
}

func (t *Token) AddPrivilege(p Privilege, expireAt time.Time) {
	if t.Privileges == nil {
		t.Privileges = make(map[uint16]uint32)
	}
	expire := uint32(expireAt.Unix())
	if expireAt.IsZero() {
		expire = 0
	}
	t.Privileges[uint16(p)] = expire
	// add separated publish privileges for now
	if p == PrivPublishStream {
		t.Privileges[uint16(privPublishVideoStream)] = expire
		t.Privileges[uint16(privPublishAudioStream)] = expire
		t.Privileges[uint16(privPublishDataStream)] = expire
	}
}

func packUint16(w io.Writer, n uint16) error {
	return binary.Write(w, binary.LittleEndian, n)
}

func packUint32(w io.Writer, n uint32) error {
	return binary.Write(w, binary.LittleEndian, n)
}

func packString(w io.Writer, s string) error {
	err := packUint16(w, uint16(len(s)))
	if err != nil {
		return err
	}
	_, err = w.Write([]byte(s))
	return err
}

func packMapUint32(w io.Writer, extra map[uint16]uint32) error {
	var keys []int
	if err := packUint16(w, uint16(len(extra))); err != nil {
		return err
	}
	for k := range extra {
		keys = append(keys, int(k))
	}
	//should sorted keys
	sort.Ints(keys)

	for _, k := range keys {
		v := extra[uint16(k)]
		if err := packUint16(w, uint16(k)); err != nil {
			return err
		}
		if err := packUint32(w, v); err != nil {
			return err
		}
	}
	return nil
}

func (t *Token) pack() (string, string, error) {
	bufM := new(bytes.Buffer)
	if err := packUint32(bufM, t.Nonce); err != nil {
		return "", "", err
	}
	if err := packUint32(bufM, t.IssuedAt); err != nil {
		return "", "", err
	}
	if err := packUint32(bufM, t.ExpireAt); err != nil {
		return "", "", err
	}
	if err := packString(bufM, t.RoomID); err != nil {
		return "", "", err
	}
	if err := packString(bufM, t.UserID); err != nil {
		return "", "", err
	}
	if err := packMapUint32(bufM, t.Privileges); err != nil {
		return "", "", err
	}
	bytesM := bufM.Bytes()

	bufSign := hmac.New(sha256.New, []byte(t.AppKey))
	bufSign.Write(bytesM)
	bytesSign := bufSign.Sum(nil)

	return string(bytesM[:]), string(bytesSign[:]), nil
}

func (t *Token) Serialize() (string, error) {
	msg, sign, err := t.pack()
	if err != nil {
		return "", err
	}

	bufContent := new(bytes.Buffer)
	if err := packString(bufContent, msg); err != nil {
		return "", err
	}

	if err := packString(bufContent, sign); err != nil {
		return "", err
	}

	bytesContent := bufContent.Bytes()

	return Version + t.AppID + base64.StdEncoding.EncodeToString(bytesContent), nil
}

func GenerateToken(param *GenerateParam) (string, error) {
	if param.AppKey == "" {
		return "", nil
	}

	expiredAt := param.ExpireAt
	if expiredAt < 1609500000 {
		expiredAt = time.Now().Unix() + param.ExpireAt
	}

	token := New(param.AppID, param.AppKey, param.RoomID, param.UserID)

	token.ExpireTime(time.Unix(expiredAt, 0))

	if param.CanPublish {
		token.AddPrivilege(PrivPublishStream, time.Unix(expiredAt, 0))
	}

	if param.CanSubscribe {
		token.AddPrivilege(PrivSubscribeStream, time.Unix(expiredAt, 0))
	}

	if param.CanSwitch {
		token.AddPrivilege(PrivSwitchRTCProvider, time.Unix(expiredAt, 0))
	}

	return token.Serialize()
}
