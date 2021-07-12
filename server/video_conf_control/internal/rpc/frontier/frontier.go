package frontier

import (
	"context"
	"time"

	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/internal/config"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/kitex_gen/rtc_frontier"
	frontierCli "github.com/volcengine/VolcEngineRTC/server/video_conf_control/kitex_gen/rtc_frontier/frontier"
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/pkg/public"
)

var client frontierCli.Client

func Init() {
	var err error

	opts := make([]kc.Option, 0)
	opts = append(opts,
		kc.WithCluster(env.Cluster()),
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
	address, err := public.ChooseAddr(addr, addr6)
	if err != nil {
		logs.CtxWarn(ctx, "choose addr error: %v", err)
	}
	event := &rtc_frontier.TPushParam{
		ConnId:    connID,
		EventName: eventName,
		Content:   content,
		PacketId:  packetID,
	}

	_, err = client.PushToClient(ctx, event, callopt.WithHostPort(address))
	if err != nil {
		logs.CtxWarn(ctx, "push to client error, addr: %s, content: %s, err: %v", address, content, err)
		return
	}

	logs.CtxInfo(ctx, "push to client, addr: %s, content: %s, err: %v", address, content, err)
}

// BroadcastToClient sends the same message with connIDs to the frontier.
func BroadcastToClient(ctx context.Context, connIDs []string, addr, addr6, eventName, content string, packetID int32) {
	address, err := public.ChooseAddr(addr, addr6)
	if err != nil {
		logs.CtxWarn(ctx, "choose addr error: %v", err)
	}

	event := &rtc_frontier.TBroadCastParam{
		ConnIds:   connIDs,
		EventName: eventName,
		Content:   content,
		PacketId:  packetID,
	}

	resp, err := client.BroadcastToClient(ctx, event, callopt.WithHostPort(address))
	if err != nil {
		logs.CtxWarn(ctx, "broadcast to client error, addr: %s, content: %s, err: %v", address, content, err)
		return
	}

	logs.CtxInfo(ctx, "broadcast to client, failed connIDs: %v, connIDs: %v, addr: %v, content: %v", resp.ConnIds, connIDs, address, content)
}
