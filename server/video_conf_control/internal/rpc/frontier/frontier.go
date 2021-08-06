package frontier

import (
	"context"
	"time"

	kc "github.com/cloudwego/kitex/client"
	"github.com/cloudwego/kitex/client/callopt"
	"github.com/cloudwego/kitex/pkg/connpool"
	"github.com/cloudwego/kitex/transport"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/config"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/kitex_gen/frontier"
	frontierCli "github.com/volcengine/VolcEngineRTC/server/video_conf_control/kitex_gen/frontier/frontier"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/pkg/public"
)

var client frontierCli.Client

func Init() {
	var err error

	opts := make([]kc.Option, 0)
	opts = append(opts,
		kc.WithLongConnection(connpool.IdleConfig{
			MaxIdlePerAddress: 100,
			MaxIdleGlobal:     100,
			MaxIdleTimeout:    600 * time.Second,
		}),
		kc.WithTransportProtocol(transport.TTHeaderFramed),
	)

	client, err = frontierCli.NewClient(config.Config.FrontierPSM, opts...)

	if err != nil {
		panic("init frontier client error")
	}
}

// PushToClient sends message with specific connID to the frontier.
func PushToClient(ctx context.Context, connID, addr, addr6, eventName, content string, packetID int32) {
	address, _ := public.ChooseAddr(addr, addr6)
	event := &frontier.TPushParam{
		ConnId:    connID,
		EventName: eventName,
		Content:   content,
		PacketId:  packetID,
	}

	client.PushToClient(ctx, event, callopt.WithHostPort(address))
}

// BroadcastToClient sends the same message with connIDs to the frontier.
func BroadcastToClient(ctx context.Context, connIDs []string, addr, addr6, eventName, content string, packetID int32) {
	address, _ := public.ChooseAddr(addr, addr6)

	event := &frontier.TBroadCastParam{
		ConnIds:   connIDs,
		EventName: eventName,
		Content:   content,
		PacketId:  packetID,
	}

	client.BroadcastToClient(ctx, event, callopt.WithHostPort(address))
}
