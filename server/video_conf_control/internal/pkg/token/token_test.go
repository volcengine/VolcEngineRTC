package token

import (
	"testing"
)

func TestGenerateToken(t *testing.T) {
	param := &GenerateParam{
		AppID:        "60542343fb27800c6a382d1",
		AppKey:       "abcedf3fe21dd74aa0a2345653a8a345678",
		RoomID:       "789234",
		UserID:       "demouser",
		ExpireAt:     7 * 24 * 3600,
		CanPublish:   true,
		CanSubscribe: true,
		CanSwitch:    true,
	}

	s, err := GenerateToken(param)
	if err != nil {
		t.Errorf("generate token error: %v", err)
	}

	t.Logf("generate token: %s", s)
}
