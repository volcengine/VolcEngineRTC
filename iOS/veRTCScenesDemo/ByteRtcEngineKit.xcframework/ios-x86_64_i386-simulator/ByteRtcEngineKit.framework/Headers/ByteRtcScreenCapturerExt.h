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
 * @type api
 * @brief 建议 SampleHandler 继承此协议。
 */
BYTE_RTC_EXPORT @protocol ByteRtcScreenCapturerExtDelegate <NSObject>

/**
 * @type api
 * @region 视频管理
 * @brief 通知 Broadcast Upload Extension 停止采集并退出。
 * @notes
 *        1.屏幕采集分为内部采集和外部采集，本方法属于内部采集。
 *        2.用于 App 通知 Extension 停止采集并关闭，收到此方法后调用 finishBroadcastWithError: 停止采集并推出。
 */
- (void)quit;

@end

/**
 * @type api
 * @brief 建议 SampleHandler 实例持有 ByteRtcScreenCapturerExt 实例。
 */
BYTE_RTC_EXPORT @interface ByteRtcScreenCapturerExt : NSObject


@property (readonly, class) ByteRtcScreenCapturerExt *shared; // NOLINT

@property (nonatomic, weak, nullable) NSObject<ByteRtcScreenCapturerExtDelegate> *delegate; // NOLINT

/**
 * @type api
 * @region 视频管理
 * @brief 开始采集和编码
 * @param delegate 回调代理，参考 ByteRtcScreenCapturerExtDelegate{@link #ByteRtcScreenCapturerExtDelegate}
 * @notes
 *        屏幕采集分为内部采集和外部采集，本方法属于内部采集。
 */
- (void)startWithDelegate:(NSObject<ByteRtcScreenCapturerExtDelegate> *)delegate groupId:(NSString *)groupId;


/**
 * @type api
 * @region 视频管理
 * @brief 结束屏幕分享
 * @notes
 *        屏幕采集分为内部采集和外部采集，本方法属于内部采集。
 */
- (void)stop;

/**
 * @type api
 * @region 视频管理
 * @brief 推送 Extension 采集的数据
 * @param sampleBuffer 采集到的数据
 * @param sampleBufferType 数据类型
 * @notes
 *        屏幕采集分为内部采集和外部采集，本方法属于内部采集。
 */
- (void)processSampleBuffer:(CMSampleBufferRef)sampleBuffer withType:(RPSampleBufferType)sampleBufferType;

@end

NS_ASSUME_NONNULL_END
