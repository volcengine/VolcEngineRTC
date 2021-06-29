//
//  ByteSocketIO.h
//  ByteSocketIO
//
//  Created by xiewei on 2019/1/6.
//  Copyright © 2019 xiewei. All rights reserved.
//

#pragma once
#import <UIKit/UIKit.h>
#include <functional>
#include <map>
#import "ByteRtcEngineKitDefines.h"

#ifdef BYTERTC_IOS
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnullability-completeness"
#endif

typedef void(^ByteSocketIOCallbackFn)(NSArray* _Nullable data);
@interface ByteSignalMessageHandler : NSObject
@property (strong) NSString* _Nullable msgType;
@property (strong) ByteSocketIOCallbackFn _Nullable handler;
@end


namespace sio {
    class client;
}

namespace bytesio {
class BYTE_RTC_EXPORT ByteSocketIO {
public:
    typedef std::function<void(NSArray* _Nonnull data)> event_listener;
    
    ByteSocketIO();
    ~ByteSocketIO();
    ByteSocketIO(ByteSocketIO& client) = delete;
    void on(std::string const& event_name, event_listener const& callback);
    void emit(std::string const& name, NSDictionary* _Nonnull data, ByteSocketIOCallbackFn _Nullable callback);
    
       
    enum close_reason
    {
        close_reason_normal,
        close_reason_drop
    };

     enum WebSocket_API_Type
    {
        WSPP = 0,
        TTNET
    };
    
    enum transport_status_ext : int
    {
        ws_dns_resolved_ext     =    0,
        ws_transport_conn_ext         ,
        ws_proxy_tls_conn_ext         ,
        ws_connected_cmpl_ext         ,
        ws_reconnect_cmpl_ext         ,
        ws_disconnec_cmpl_ext         ,
        ws_connect_metric_ext   =   16,
        ws_disconn_metric_ext   =   17,
        websocket_loginfo_ext   =   18,
        websocket_reserve_max   =  100,
        ttnet_conn_metric_ext   =  101,//transport vendor ext 101--1024
        transport_max_ext       = 1024
    };
        
    //TCP or UDP
    typedef std::function<void(int const& ,const std::string&)> transport_ext_listener;

    typedef std::function<void(void)> con_listener;

    typedef std::function<void(close_reason const& reason)> close_listener;

    typedef std::function<void(unsigned, unsigned)> reconnect_listener;

    typedef std::function<void(std::string const& nsp)> socket_listener;
    
    //set listeners and event bindings.
    void set_transport_ext_listener(transport_ext_listener const& l);

    void set_open_listener(con_listener const& l);

    void set_fail_listener(con_listener const& l);
    
    void set_reconnecting_listener(con_listener const& l);

    void set_reconnect_listener(reconnect_listener const& l);

    void set_close_listener(close_listener const& l);

    void set_socket_open_listener(socket_listener const& l);

    void set_socket_close_listener(socket_listener const& l);
    
    void clear_con_listeners();

    void clear_socket_listeners();
        
    void connect(const std::string& uri, const char *path = NULL);

    void connect(const std::string& uri, const std::map<std::string,std::string>& query);

    void connect(const std::string& uri, const char *path, const std::map<std::string,std::string>& query,
            const std::map<std::string,std::string>& http_extra_headers);

    void set_reconnect_attempts(int attempts);

    void set_reconnect_delay(unsigned millis);

    void set_reconnect_delay_max(unsigned millis);
    
    // Closes the connection
    void close();

    void sync_close();

    bool opened() const;

    std::string const& get_sessionid() const;
        
protected:
    sio::client* mClient = nullptr;
};
}

#ifdef BYTERTC_IOS
#pragma clang diagnostic pop
#endif
