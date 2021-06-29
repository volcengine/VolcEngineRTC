
#ifndef ByteRtcHttpClient_h
#define ByteRtcHttpClient_h

#import <Foundation/Foundation.h>

/**
 * @hidden
 * @region 引擎管理
 * @type api
 */
@protocol ByteRtcHttpClientProtocol <NSObject>

@required

/**
 * @hidden
 * @type api
 * @region 引擎管理
 * @brief 需要实现的 HTTP 异步 GET 接口。
 * @param url  <br>
 *        GET 请求地址。
 * @param timeout  <br>
 *        超时时间。
 * @param callback  <br>
 *        GET 请求结果回调函数。
 */
- (void)getAsync:(NSString * _Nonnull)url timeoutMillisecond:(int)timeout
    withCallback:(void(^ _Nullable)(int code, NSString* _Nullable data))callback;

/**
 * @hidden
 * @type api
 * @region 引擎管理
 * @brief 需要实现的 HTTP 异步 POST 接口。
 * @param url  <br>
 *        POST 请求地址。
 * @param content  <br>
 *        POST 请求的内容。
 * @param timeout  <br>
 *        超时时间。
 * @param callback  <br>
 *        POST 请求结果回调函数。
 */
- (void)postAsync:(NSString * _Nonnull)url content:(NSString * _Nullable)content timeoutMillisecond:(int)timeout
    withCallback:(void(^ _Nullable)(int code, NSString* _Nullable data))callback;

@end

#endif
