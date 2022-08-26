/*
 * Copyright 2021 @bytedance
 *
 *  Created on: Mar 14, 2021
 */

#pragma once

#import <Foundation/Foundation.h>
#import <CoreVideo/CoreVideo.h>
#import <ReplayKit/ReplayKit.h>

NS_ASSUME_NONNULL_BEGIN
#define BYTE_RTC_EXPORT __attribute__((visibility("default")))
/** 
 * @type keytype
 * @brief 屏幕采集相关扩展协议，仅适用于 SDK 内部采集。  <br>
 *        用户创建 extesion 后生成的 SampleHandler 需继承此协议以实现屏幕共享相关能力。
 */
BYTE_RTC_EXPORT @protocol ByteRtcScreenCapturerExtDelegate <NSObject>
/** 
 * @type api
 * @region 视频管理
 * @brief 通知 Broadcast Upload Extension 停止采集屏幕并退出。
 * @notes 用户调用 stopScreenCapture{@link #ByteRTCVideo#stopScreenCapture} 后，会触发该方法通知 extension 端的 SDK 停止屏幕采集。
 */
- (void)onQuitFromApp;
/** 
 * @type api
 * @region 视频管理
 * @brief Socket 收到 App 侧发来的信息时，触发该回调
 * @param message App 侧发送的消息
 */
- (void)onReceiveMessageFromApp:(NSData *)message;
/** 
 * @type api
 * @region 视频管理
 * @brief Socket 连接断开时触发此回调
 */
- (void)onSocketDisconnect;
/** 
 * @type api
 * @region 视频管理
 * @brief Socket 连接成功时触发此回调
 */
- (void)onSocketConnect;
/** 
 * @type api
 * @region 视频管理
 * @brief 检测到 App 正在进行音视频通话时触发此回调。
 */
- (void)onNotifyAppRunning;
@end

/** 
 * @type keytype
 * @brief 屏幕采集相关扩展实例，仅适用于 SDK 内部采集。  <br>
 *        用户创建 extesion 后生成的 SampleHandler 需通过此实例实现屏幕共享相关能力。
 */
BYTE_RTC_EXPORT @interface ByteRtcScreenCapturerExt : NSObject
/**
 * @hidden
 */
@property (readonly, class) ByteRtcScreenCapturerExt *shared; // NOLINT
/**
 * @hidden
 */
@property (nonatomic, weak, nullable) NSObject<ByteRtcScreenCapturerExtDelegate> *delegate; // NOLINT
/** 
 * @type api
 * @region 视频管理
 * @brief 开始屏幕采集  <br>
 *        Extension 启动后，系统将自动调用该方法开启屏幕采集。
 * @param delegate 回调代理，参看 ByteRtcScreenCapturerExtDelegate{@link #ByteRtcScreenCapturerExtDelegate}
 * @param groupId App groups 中配置的 group ID
 */
- (void)startWithDelegate:(NSObject<ByteRtcScreenCapturerExtDelegate> *)delegate groupId:(NSString *)groupId;
/** 
 * @type api
 * @region 视频管理
 * @brief 结束屏幕采集  <br>
 *        Extension 关闭后，系统将自动调用该方法停止屏幕采集。
 */
- (void)stop;
/** 
 * @type api
 * @region 视频管理
 * @brief 推送 Extension 采集的数据
 * @param sampleBuffer 采集到的数据
 * @param sampleBufferType 数据类型
 */
- (void)processSampleBuffer:(CMSampleBufferRef)sampleBuffer withType:(RPSampleBufferType)sampleBufferType API_AVAILABLE(ios(10));
@end

NS_ASSUME_NONNULL_END
