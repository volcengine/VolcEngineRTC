// Code generated by Kitex v1.4.3. DO NOT EDIT.

package vccontrol

import (
	"github.com/volcengine/VolcEngineRTC/server/video_conf_control/kitex_gen/vc_control"
)

// NewInvoker creates a server.Invoker with the given handler and options.
func NewInvoker(handler vc_control.VCControl, opts ...server.Option) server.Invoker {
	var options []server.Option
	options = append(options, byted.InvokeSuite(serviceInfo()))
	options = append(options, opts...)

	s := server.NewInvoker(options...)
	if err := s.RegisterService(serviceInfo(), handler); err != nil {
		panic(err)
	}
	if err := s.Init(); err != nil {
		panic(err)
	}
	return s
}

// NewInvokerWithBytedConfig creates a server.Invoker with the given handler and options.
func NewInvokerWithBytedConfig(handler vc_control.VCControl, config *byted.ServerConfig, opts ...server.Option) server.Invoker {
	var options []server.Option
	options = append(options, byted.InvokeSuiteWithConfig(serviceInfo(), config))
	options = append(options, opts...)

	s := server.NewInvoker(options...)
	if err := s.RegisterService(serviceInfo(), handler); err != nil {
		panic(err)
	}
	if err := s.Init(); err != nil {
		panic(err)
	}
	return s
}