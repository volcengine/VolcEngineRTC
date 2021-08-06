package public

import (
	"errors"
	"os"
)

func StringInSlice(a string, list []string) bool {
	for _, b := range list {
		if b == a {
			return true
		}
	}
	return false
}

// GetInstanceIPV4 get instance ipv4 address
func GetInstanceIPV4() string {
	return GetEnvSeq("MY_HOST_IP")
}

// GetInstanceIPV6 get instance ipv6 address
func GetInstanceIPV6() string {
	return GetEnvSeq("MY_HOST_IPV6")
}

// IsDualStack env is dual-stack
func IsDualStack() bool {
	return GetInstanceIPV4() != "" && GetInstanceIPV6() != ""
}

// IsIPV4Only env is ipv4-only
func IsIPV4Only() bool {
	return GetInstanceIPV4() != "" && GetInstanceIPV6() == ""
}

// IsIPV6Only env is ipv6-only
func IsIPV6Only() bool {
	return GetInstanceIPV4() == "" && GetInstanceIPV6() != ""
}

// ChooseAddr dual-stack choose v6 first
func ChooseAddr(v4, v6 string) (string, error) {
	if IsIPV4Only() {
		if v4 != "" {

			return v4, nil
		}
		return "", errors.New("host is ipv4only, ipv4 addr not exist")
	}
	if IsIPV6Only() {
		if v6 != "" {
			return v6, nil
		}
		return "", errors.New("host is ipv6only, ipv6 addr not exist")
	}
	if v6 != "" {
		return v6, nil
	}
	if v4 != "" {
		return v4, nil
	}
	return "", errors.New("host is dual-stack, ipv4/ipv6 addr not exist")
}

func GetEnvSeq(keyArr ...string) string {
	for _, key := range keyArr {
		value := os.Getenv(key)
		if value != "" {
			return value
		}
	}
	return ""
}