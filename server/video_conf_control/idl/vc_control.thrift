include "base.thrift"
namespace go vc_control

struct TEventParam {
    1: string conn_id,
    2: string event_name,
    3: string content,
    4: string addr,
    5: string addr6,
    6: i32 packet_id,
    
    255: base.Base Base
}

struct TEventResp {
    255: base.BaseResp BaseResp
}

struct TRecordCallbackParam {
	1: string event_type (api.body='EventType')
	2: string event_data (api.body='EventData')
	3: string event_time (api.body='EventTime')
	4: string event_id (api.body='EventId')
	5: string app_id (api.body='AppId')
	6: string version (api.body='Version')
	7: string signature (api.body='Signature')
	8: string noce (api.body='Noce')
    
    255: base.Base Base
}

struct THTTPResp {
    255: base.BaseResp BaseResp
}

service VCControl {
    TEventResp handle_meeting_event(1: TEventParam param)
    
    THTTPResp handle_record_callback(1: TRecordCallbackParam param) (api.post='/vc_control/callback')
}
