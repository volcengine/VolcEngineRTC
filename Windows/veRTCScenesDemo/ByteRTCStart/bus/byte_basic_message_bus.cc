/*
 *  Copyright (c) 2020 The ByteRtc project authors. All Rights Reserved.
 *  @company ByteDance.Inc
 *  @brief Message Bus
 */

#include "byte_basic_message_bus.h"
#include <iostream>
#include <atomic>

namespace bytertc {
namespace basic {

/**
 * @brief Get the current time
*/
inline Message::Time_t TimeNow() {
    return std::chrono::high_resolution_clock::now();
}

// Impl of Message Bus Handler Storage
// The Impl is just an static storage, contains the safe mutex and the map
struct MsgBusImpl {
    typedef WeakWrapper<MsgBusDispatcher>   WeakableDispatcher;
    static WeakPtr<WeakableDispatcher> Dispatcher() {
        static StaticWrapper<WeakableDispatcher> s_dispatcher;
        return s_dispatcher.SafeGet();
    }

    static uint32_t ValidateTraceId( uint32_t* p_trace ) {
        static std::atomic<uint32_t> s_trace_id(0);

        uint32_t _tid = INVALIDATE_TRACEID;
        if ( p_trace != NULL ) _tid = *p_trace;
        if ( _tid == INVALIDATE_TRACEID ) _tid = s_trace_id++;
        if ( p_trace != NULL ) *p_trace = _tid;

        return _tid;
    }
};

/**
 * @brief Append a traceable message
 * @param [in] msg_id: event ID
 * @param [in] trace_id: event trace ID
 * @param [in] from: Message from
 * @param [in] args: parameter list
*/
void MessageBus::Publish(int msg_id, uint32_t trace_id, Message::FromType&& from, MessageArgList&& args) {
    // Create a msg
    Message _msg{msg_id, MsgBusImpl::ValidateTraceId(&trace_id), 
            std::move(from), Message::Time_t(), std::move(args), nullptr};
    auto weak_dispatcher = MsgBusImpl::Dispatcher();
    if ( auto strong_dispatcher = weak_dispatcher.Lock() ) {
        strong_dispatcher->GetItem().Publish( msg_id, _msg );
    }
}
/**
 * @brief Append a message, using auto-incremental tracking ID
 * @param [in] msg_id: event ID
 * @param [in] from: event from
 * @param [in] args: parameter list
*/
void MessageBus::Publish(int msg_id, Message::FromType&& from, MessageArgList&& args) {
    MessageBus::Publish(msg_id, INVALIDATE_TRACEID, std::move(from), std::move(args));
}

/**
 * @brief Append a message without any parameters
 * @param [in] msg_id: event ID
 * @param [in] from: Message from
*/
void MessageBus::Publish(int msg_id, Message::FromType&& from) {
    MessageBus::Publish(msg_id, INVALIDATE_TRACEID, std::move(from), {});
}

/**
 * @brief Bind a handler to receive a specific message,
 * The binding behavior is permanent until it is unbound using the incoming HKEY
*/
void MessageBus::Subscribe(int msg_id, MessageHandler handler, const std::string& hkey) {
    auto weak_dispatcher = MsgBusImpl::Dispatcher();
    if ( auto strong_dispatcher = weak_dispatcher.Lock() ) {
        strong_dispatcher->GetItem().Subscribe(msg_id, handler, false, hkey);
    }
}
/**
 * @brief Bind a handler to receive a specific message without setting a key
*/
void MessageBus::Subscribe(int msg_id, MessageHandler handler) {
    static std::string kEmptyKey("");
    auto weak_dispatcher = MsgBusImpl::Dispatcher();
    if ( auto strong_dispatcher = weak_dispatcher.Lock() ) {
        strong_dispatcher->GetItem().Subscribe(msg_id, handler, false, kEmptyKey);
    }
}

/**
 * @brief Bind a Handler to receive a specific message,
 * The binding behavior is automatically unbound after a message is received
*/
void MessageBus::SubscribeOnce(int msg_id, MessageHandler handler, const std::string& hkey) {
    auto weak_dispatcher = MsgBusImpl::Dispatcher();
    if ( auto strong_dispatcher = weak_dispatcher.Lock() ) {
        strong_dispatcher->GetItem().Subscribe(msg_id, handler, true, hkey);
    }
}
/**
 * @brief Binding a Handler to receive a specific message will automatically unbind
 * after receiving a message without specifying a key
*/
void MessageBus::SubscribeOnce(int msg_id, MessageHandler handler) {
    static std::string kEmptyKey("");
    auto weak_dispatcher = MsgBusImpl::Dispatcher();
    if ( auto strong_dispatcher = weak_dispatcher.Lock() ) {
        strong_dispatcher->GetItem().Subscribe(msg_id, handler, true, kEmptyKey);
    }
}

/**
 * @brief Unbind messages from handler pointed to by a specific HKEY
*/
void MessageBus::Unsubscribe(int msg_id, const std::string& hkey) {
    auto weak_dispatcher = MsgBusImpl::Dispatcher();
    if ( auto strong_dispatcher = weak_dispatcher.Lock() ) {
        strong_dispatcher->GetItem().Unsubscribe(msg_id, hkey);
    }
}
/**
 * @brief Remove All handlers on msg_id
*/
void MessageBus::Unsubscribe(int msg_id) {
    static std::string kEmptyKey("");
    auto weak_dispatcher = MsgBusImpl::Dispatcher();
    if ( auto strong_dispatcher = weak_dispatcher.Lock() ) {
        strong_dispatcher->GetItem().Unsubscribe(msg_id, kEmptyKey);
    }
}

/**
 * @brief Start Message Channel for MessageBus
*/
void MessageBus::Initialize() {
    auto weak_dispatcher = MsgBusImpl::Dispatcher();
    if ( auto strong_dispatcher = weak_dispatcher.Lock() ) {
        strong_dispatcher->GetItem().Enable(true);
    }
}

/**
 * @brief Stop the message channel and notify all MessageQueues to release resources and exit all programs
*/
void MessageBus::Destroy() {
    auto weak_dispatcher = MsgBusImpl::Dispatcher();
    if ( auto strong_dispatcher = weak_dispatcher.Lock() ) {
        strong_dispatcher->GetItem().Enable(false);
        strong_dispatcher->GetItem().UnsubscribeAll();
    }
}

/**
 * @brief Add Arg without log string
*/
MessageBuilder& MessageBuilder::AddArg( std::string&& key, MessageArgValue&& value ) {
    msg.msg_args.emplace_back(
        std::make_pair<std::string, MessageArgValue>(
            std::forward<std::string>(key),
            std::forward<MessageArgValue>(value)
            )
        );
    return *this;
}

/**
 * @brief Publish Current Message
*/
void MessageBuilder::Publish() {
    auto weak_dispatcher = MsgBusImpl::Dispatcher();
    if ( auto strong_dispatcher = weak_dispatcher.Lock() ) {
        strong_dispatcher->GetItem().Publish( msg.msg_id, msg );
    }
}

/**
 * @brief Build a message builder
*/
MessageBuilder BuildMessageImpl(int msg_id, TraceLocation&& from) {
    MessageBuilder mb;
    mb.msg.msg_id = msg_id;
    mb.msg.msg_from = std::move(from);
    mb.msg.msg_trace_id = MsgBusImpl::ValidateTraceId(NULL);
    mb.msg.msg_create_time = Message::Time_t();
    return mb;
}

} // namespace basic
} // namespace bytertc 
