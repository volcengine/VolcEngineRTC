module github.com/volcengine/VolcEngineRTC/server/video_conf_control

go 1.14

replace github.com/apache/thrift => github.com/apache/thrift v0.13.0

require (
	github.com/TTvcloud/vcloud-sdk-golang v1.0.29
	github.com/apache/thrift v0.13.0
	github.com/cloudwego/kitex v0.0.3
	github.com/go-redis/redis/v8 v8.11.1
	github.com/jinzhu/configor v1.2.1
	github.com/kr/pretty v0.1.0 // indirect
	github.com/mozillazg/go-pinyin v0.18.0
	github.com/satori/go.uuid v1.2.0
	github.com/sirupsen/logrus v1.8.1
	github.com/valyala/fasthttp v1.28.0
	gopkg.in/check.v1 v1.0.0-20180628173108-788fd7840127 // indirect
	gorm.io/driver/mysql v1.1.1
	gorm.io/gorm v1.21.12
)
