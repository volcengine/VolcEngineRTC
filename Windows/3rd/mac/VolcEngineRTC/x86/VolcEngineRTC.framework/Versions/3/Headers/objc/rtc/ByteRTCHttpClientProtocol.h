/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC HTTP Client Protocol
*/

#import <Foundation/Foundation.h>

/**
 * @locale zh
 * @hidden for internal use only
 * @type api
 * @region 引擎管理
 */
/**
 * @locale en
 * @hidden for internal use only
 * @type api
 * @region Engine Management
 */
@protocol ByteRTCHttpClientProtocol <NSObject>

@required

/**
 * @locale zh
 * @type api
 * @region 引擎管理
 * @brief 需要实现的 HTTP 异步 GET 接口。
 * @param url GET 请求地址。
 * @param timeout 超时时间。
 * @param callback GET 请求结果回调函数。
 */
/**
 * @locale en
 * @type api
 * @region Engine Management
 * @brief The HTTP asynchronous GET interface to be implemented
 * @param url GET request address
 * @param timeout Timeout period
 * @param callback GET request result callback function
 */
- (void)getAsync:(NSString * _Nonnull)url timeoutMillisecond:(int)timeout
    withCallback:(void(^ _Nullable)(int code, NSString* _Nullable data))callback;

/**
 * @locale zh
 * @type api
 * @region 引擎管理
 * @brief 需要实现的 HTTP 异步 POST 接口。
 * @param url  POST 请求地址。
 * @param content POST 请求的内容。
 * @param timeout 超时时间。
 * @param callback  POST 请求结果回调函数。
 */
/**
 * @locale en
 * @type api
 * @region Engine Management
 * @brief The HTTP asynchronous POST interface to be implemented
 * @param url POST request address
 * @param content The content of the POST request
 * @param timeout Timeout period
 * @param callback POST request result callback function
 */
- (void)postAsync:(NSString * _Nonnull)url content:(NSString * _Nullable)content timeoutMillisecond:(int)timeout
    withCallback:(void(^ _Nullable)(int code, NSString* _Nullable data))callback;
@end
