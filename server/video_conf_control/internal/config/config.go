package config

import (
	"fmt"
	"os"
	"path"

	"github.com/jinzhu/configor"
)

// Predefined env variables and default configurations.
const (
	EnvConfDir  = "CONF_DIR"
	EnvConfFile = "CONF_FILE"

	DefaultConfDir  = "conf"
	DefaultConfFile = "config.yaml"
)

type HowardConfig struct {
	PSM       string `json:"psm" default:""`
	AccessKey string `json:"access_key" default:""`
	SecretKey string `json:"secret_key" default:""`
}

type Configuration struct {
	PSM 			   string   `yaml:"PSM"`
	MysqlDSN           string   `yaml:"MysqlDSN"`
	RedisAddr          string   `yaml:"RedisAddr"`
	FrontierPSM        string   `yaml:"FrontierPSM"`
	AppID              string   `yaml:"AppID"`
	AppKey             string   `yaml:"AppKey"`
	EnableIPv6         bool     `yaml:"EnableIPv6"`
	ReconnectTimeout   int      `yaml:"ReconnectTimeout"`
	RoomUserLimit      int      `yaml:"RoomUserLimit"`
	VCloudAK           string   `yaml:"VCloudAK"`
	VCloudSK           string   `yaml:"VCloudSK"`
	PostProcessingURL  string   `yaml:"PostProcessingURL"`
	PostProcessingAK   string   `yaml:"PostProcessingAK"`
	PostProcessingSK   string   `yaml:"PostProcessingSK"`
	Resolution         string   `yaml:"Resolution"`
	VideoDays          int      `yaml:"VideoDays"`
	RoomDurationMinute int      `yaml:"RoomDurationMinute"`
	RoomWhiteList      []string `yaml:"RoomWhiteList"`
	VideoObtainingURL  string   `yaml:"VideoObtainingURL"`
	HowardConfig       HowardConfig `yaml:"howard_config"`
}

var Config Configuration

// ParseConfig parses config file.
func ParseConfig() {
	file := GetConfFile()

	if err := configor.Load(&Config, file); err != nil {
		fmt.Fprintf(os.Stderr, "ParseConfig failed: err=%v\n", err)
		os.Exit(1)
	}
}

// GetConfDir gets dir of config file.
func GetConfDir() string {
	if confDir := os.Getenv(EnvConfDir); confDir != "" {
		return confDir
	}
	return DefaultConfDir
}

// GetConfFile gets config file path.
func GetConfFile() string {
	file := DefaultConfFile
	if confFile := os.Getenv(EnvConfFile); confFile != "" {
		file = confFile
	}
	return path.Join(GetConfDir(), file)
}
