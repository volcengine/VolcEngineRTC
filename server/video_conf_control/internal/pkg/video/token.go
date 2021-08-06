package video

import (
	"encoding/base64"
	"encoding/json"
	"net/url"
	"sync"
	"time"

	"github.com/TTvcloud/vcloud-sdk-golang/base"
	"github.com/TTvcloud/vcloud-sdk-golang/service/vod"
	logs "github.com/sirupsen/logrus"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/config"
)

type token struct {
	tokenURL string
	sync.RWMutex
}

var t = &token{}
var vodClient *vod.Vod

func Init() {
	// file in machine updates every 3 mins, so update interval should be less than 3 mins
	vodClient = vod.NewInstance()
	logs.Infof("ak/sk: %v, %v", config.Config.PostProcessingAK, config.Config.PostProcessingSK)
	vodClient.SetCredential(base.Credentials{
		AccessKeyID:     config.Config.PostProcessingAK,
		SecretAccessKey: config.Config.PostProcessingSK,
		Service:         "vod",
		Region:          base.RegionCnNorth1,
	})

	go func() {
		ticker := time.NewTicker(30 * time.Minute)
		for ; true; <-ticker.C {
			t.update()
		}
	}()
}

func (t *token) get() string {
	t.RLock()
	defer t.RUnlock()

	return t.tokenURL
}

func (t *token) update() {
	qss := url.Values{}
	// 240p,360p,480p,540p,720p,1080p
	qss.Set("definition", "0")
	// Set the signature expiration time, unit: second. 3600 seconds by default
	qss.Set("X-Amz-Expires", "3600")

	ret, _ := vodClient.GetPlayAuthToken(qss)
	resp, _ := base64.StdEncoding.DecodeString(ret)
	var playAuthToken map[string]string
	json.Unmarshal(resp, &playAuthToken)

	t.Lock()
	t.tokenURL = playAuthToken["GetPlayInfoToken"]
	t.Unlock()
}
