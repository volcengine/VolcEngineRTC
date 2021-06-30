/*
 *  Copyright (c) 2020 The ByteRtc project authors. All Rights Reserved.
 *  @company ByteDance.Inc
 *  @brief Message Bus
 */

#include "byte_basic_message.h"
#include "byte_basic_weak_handler.h"
#include "byte_basic_item_dispatcher.h"

#pragma once

namespace bytertc {
namespace basic {

/**
 * @brief Basic Message Processing Function Prototype Definition
*/
typedef ItemDispatcher< Message, int >      MsgBusDispatcher;
typedef MsgBusDispatcher::SubscriberFunc    MessageHandler;

struct MessageBus {
    /**
     * @brief Append a traceable message
     * @param [in] msg_id: evet ID
     * @param [in] trace_id: evet tracking ID
     * @param [in] from: evet from
     * @param [in] args: parameter list
    */
    static void Publish(int msg_id, uint32_t trace_id, Message::FromType&& from, MessageArgList&& args);
    /**
     * @brief Append a message, using auto-incremental tracking ID
     * @param [in] msg_id: evet ID
     * @param [in] from: evet from
     * @param [in] args: parameter list
    */
    static void Publish(int msg_id, Message::FromType&& from, MessageArgList&& args);

    /**
     * @brief Append a message without any parameters
     * @param [in] msg_id: evet ID
     * @param [in] from: evet from
    */
    static void Publish(int msg_id, Message::FromType&& from);

    /**
     * @brief Bind a handler to receive a specific message,
     * The binding behavior is permanent until it is unbound using the incoming HKEY
    */
    static void Subscribe(int msg_id, MessageHandler handler, const std::string& hkey);

    /**
     * @brief Bind a handler to receive a specific message without setting a key
    */
    static void Subscribe(int msg_id, MessageHandler handler);

    /**
     * @brief Bind a Handler to receive a specific message,
     * The binding behavior is automatically unbound after a message is received
    */
    static void SubscribeOnce(int msg_id, MessageHandler handler, const std::string& hkey);

    /**
     * @brief Binding a Handler to receive a specific message will automatically unbind
     * after receiving a message without specifying a key
    */
    static void SubscribeOnce(int msg_id, MessageHandler handler);

    /**
     * @brief Unbind messages from handler pointed to by a specific HKEY
    */
    static void Unsubscribe(int msg_id, const std::string& hkey);

    /**
     * @brief Remove All handlers on msg_id
    */
    static void Unsubscribe(int msg_id);

    /**
     * @brief Start Message Channel for MessageBus
    */
    static void Initialize();

    /**
     * @brief Stop the message channel and notify all MessageQueues to release resources and exit all programs 
    */
    static void Destroy();
    /**
     * @brief No constructor
    */
    MessageBus() = delete;
};

template < typename ObjType > 
MessageHandler SafeSubscriber( ObjType* pobj, void (ObjType::*handler)(Message&) ) {
    auto _wobj = pobj->WeakThis();
    return MessageHandler([_wobj, handler]( Message& msg ) {
        if ( auto _sobj = _wobj.Lock() ) {
            ObjType* _p = static_cast<ObjType *>(&(*_sobj));
            (_p->*handler)(msg);
        }
    });
}

struct MessageBuilder {
    /**
     * @brief Add Arg without log string
    */
    MessageBuilder& AddArg( std::string&& key, MessageArgValue&& value );

    /**
     * @brief Publish Current Message
    */
    void Publish();

    /**
     * @brief Message Item
    */
    Message         msg;
};

/**
 * @brief Build a message builder
*/
MessageBuilder BuildMessageImpl(int msg_id, TraceLocation&& from);

/**
 * @brief Hide MSG_FROM_HERE
*/
#define BuildMessage(msg_id)    BuildMessageImpl(msg_id, MSG_FROM_HERE)

} // namespace basic
} // namespace bytertc

