include "base.thrift"
namespace go frontier

/**
 * Exceptions
 */
enum ErrorCode {
    SOCKET_NOT_FOUND = 1,
}

exception UserException {
    1: required ErrorCode error_code,
    2: required string message
}

exception UnknownException {
    1: required ErrorCode error_code,
    2: required string message
}

/*
Push is divided into two situations:
1. Active push
2. As the return value of the function, delay sending

Proactively push packet_id to pass -1;
When used as a function return value, packet_id is the packet_id brought by the client request, event is an empty string
*/
struct TPushParam {
    1: required string conn_id
    2: required string event_name
    3: required i32 packet_id
    4: required string content

    255: optional base.Base Base
}

struct TPushResp {
    1: required i32 code
    2: optional string err_msg

    255: optional base.BaseResp BaseResp
}

struct TBroadCastParam {
    1: list<string> conn_ids
    2: string event_name
    3: i32 packet_id
    4: string content

    255: base.Base Base
}

struct TBroadCastResp {
    1: i32 code
    2: string err_msg
    3: list<string> conn_ids

    255: base.BaseResp BaseResp
}

service Frontier {
    TPushResp push_to_client(1: TPushParam param)
        throws (1: UserException user_exception,
                2: UnknownException unknown_exception),

    TBroadCastResp broadcast_to_client(1: TBroadCastParam param),
}
