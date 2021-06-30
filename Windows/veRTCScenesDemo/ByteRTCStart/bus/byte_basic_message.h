/*
 *  Copyright (c) 2020 The ByteRtc project authors. All Rights Reserved.
 *  @company ByteDance.Inc
 *  @brief Message definition
 */

#include <iostream>
#include <memory>
#include <vector>
#include <chrono>
#include <functional>
#include <thread>
#include <cassert>
#include <cstdint>

#include "byte_basic_string_util.h"
#include "byte_basic_location_type.h"

#pragma once
namespace bytertc {
namespace basic {

/**
 * @brief Message type
*/
typedef struct {
    std::shared_ptr< void >             value;
    std::shared_ptr< std::string >      str;
} MessageInnerValue;
/**
 * @brief Reference count, For parameter transfer
*/
typedef std::shared_ptr< void >                                     MessageArgValue;
typedef std::pair<std::string, MessageArgValue>                     MessagePairValue;
/**
 * @brief Parameter list definition
*/
typedef std::vector< MessagePairValue >                             MessageArgList;

/**
 * @brief Basic message class
*/
class Message {
public:
    typedef TraceLocation                                   FromType;
    typedef std::chrono::high_resolution_clock              HighResolutionTime;
    typedef std::chrono::time_point< HighResolutionTime >   Time_t;
    /**
     * @brief Message EventID
    */
    int                 msg_id;
    /**
     * @brief Message trace ID
    */
    uint32_t            msg_trace_id;
    /**
     * @brief Message from
    */
    FromType            msg_from;
    /**
     * @brief Message create time
     */
    Time_t  msg_create_time;
    /**
     * @brief Message args
     */
    MessageArgList      msg_args;

    /**
     * @brief Message custom data
    */
    MessageArgValue     msg_data;

#ifdef RTC_SDK_UNITTEST
    /**
     * @brief test only
     */
    MessageArgValue     msg_user_data;
#endif
};

#define INVALIDATE_TRACEID      (uint32_t)-1
#define MSG_FROM_HERE           CODE_FROM_HERE
#define MSG_FROM_ANYWHERE       CODE_FROM_ANYWHERE

#if _MSC_VER && !__INTEL_COMPILER
inline MessageInnerValue __MSG_INNER_INIT(std::shared_ptr<void>&& pv, std::shared_ptr<std::string>& ps) {
    MessageInnerValue _iv;
    _iv.value = pv;
    _iv.str = ps;
    return _iv;
}
#else
#define __MSG_INNER_INIT(pv, ps)    (MessageInnerValue){pv, ps}
#endif

/**
 * @brief Create srgument universal reference object
*/
template < typename ArgType, typename std::enable_if< std::is_pointer<ArgType>::value, int >::type = 0 >
inline std::shared_ptr< void > CreateArg( ArgType arg ) {
    return std::static_pointer_cast<void>(std::make_shared<MessageInnerValue>(__MSG_INNER_INIT(
        std::static_pointer_cast<void>( std::make_shared< ArgType >(arg)),
        std::make_shared<std::string>(ptr_str((const void*)arg))
    )));
}
/**
 * @brief Create srgument universal reference object
*/
template < typename ArgType, typename std::enable_if< !std::is_pointer<ArgType>::value, int >::type = 0 >
inline std::shared_ptr< void > CreateArg( ArgType&& arg ) {
    std::shared_ptr<std::string> _pstr = std::make_shared<std::string>(as_string(arg));
    return std::static_pointer_cast<void>(std::make_shared<MessageInnerValue>(__MSG_INNER_INIT(
        std::static_pointer_cast<void>( std::make_shared< ArgType >(std::move(arg))),
        _pstr
    )));
}
/**
 * @brief Create srgument universal reference object
*/
template < typename ArgType, typename std::enable_if< !std::is_pointer<ArgType>::value, int >::type = 0 >
inline std::shared_ptr< void > CreateArg( const ArgType& arg ) {
    return std::static_pointer_cast<void>(std::make_shared<MessageInnerValue>(__MSG_INNER_INIT(
        std::static_pointer_cast<void>( std::make_shared< ArgType >(arg)),
        std::make_shared<std::string>(as_string(arg))
    )));
}
/**
 * @brief Create string parameter template specialization
*/
template< >
inline std::shared_ptr< void > CreateArg<std::string>( std::string&& arg ) {
    std::shared_ptr< std::string > _ptr = std::make_shared<std::string>(std::move(arg));
    return std::static_pointer_cast<void>(std::make_shared<MessageInnerValue>(__MSG_INNER_INIT(
        std::static_pointer_cast<void>( _ptr ), _ptr
    )));
}
template< >
inline std::shared_ptr< void > CreateArg<std::string>( const std::string& arg ) {
    std::shared_ptr< std::string > _ptr = std::make_shared<std::string>(arg);
    return std::static_pointer_cast<void>(std::make_shared<MessageInnerValue>(__MSG_INNER_INIT(
        std::static_pointer_cast<void>( _ptr ), _ptr
    )));
}

template < typename ValueType >
inline std::shared_ptr< void > SetArg( std::shared_ptr< ValueType > arg ) {
    return std::static_pointer_cast<void>(std::make_shared<MessageInnerValue>(__MSG_INNER_INIT(
        std::static_pointer_cast<void>(arg), std::make_shared<std::string>("Obj"))));
}

#define MK_ARG(t, v)    bytertc::basic::CreateArg<t>(v)

/**
 * @brief Restoring original parameters from generic reference objects
*/
template < typename ArgType >
inline std::shared_ptr< ArgType > GetArg(const MessageArgValue& arg) {
    return std::static_pointer_cast<ArgType>(std::static_pointer_cast< MessageInnerValue >(arg)->value);
}

/**
 * @brief Gets the string corresponding to the message parameter
*/
inline const std::string& GetArgString(const MessageArgValue& arg) {
    return *(std::static_pointer_cast< MessageInnerValue >(arg)->str);
}

template < typename T >
inline std::shared_ptr<T> SearchArg(const Message& msg, const std::string& name) {
    for ( const auto& a : msg.msg_args ) {
        if ( a.first != name ) continue;
        return GetArg<T>(a.second);
    }
    return nullptr;
}

#define G_MSG_ARG_NAME(m, i)    (((m).msg_args[i]).first)
#define G_MSG_ARG(m, t, i)      (*bytertc::basic::GetArg<t>((m).msg_args[i].second))
#define G_ARG_NAME(i)           G_MSG_ARG_NAME(msg, i)
#define G_ARG(t, i)             G_MSG_ARG(msg, t, i)

#define G_MSG_ARG_BY_NAME(m, t, n)  *(bytertc::basic::SearchArg<t>((m), (n)))
#define G_ARG_BY_NAME(t, n)         G_MSG_ARG_BY_NAME(msg, t, n)

#define G_MSG_ARG_STR(m, i)     (bytertc::basic::GetArgString((m).msg_args[i].second))
#define G_ARG_STR(i)            G_MSG_ARG_STR(msg, i)

/**
 * @brief Directly Dump the arg value
*/
template < >
inline std::string as_string(const MessagePairValue& arg) {
    return arg.first + ": " + GetArgString(arg.second);
}

} // namespace basic
} // namespace bytertc
