/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC Internal API
*/

#pragma once

#if TARGET_OS_IPHONE || TARGET_OS_SIMULATOR
#import <UIKit/UIKit.h>
#elif TARGET_OS_OSX
#import <AppKit/AppKit.h>
#endif

#import "ByteRTCDefines.h"
@class ByteRTCEngineKit;

@protocol ByteRTCEngineInternalEventDelegate <NSObject>
@optional

#pragma mark SDK common delegate

/**
 *  The warning occurred in SDK. The APP could igonre the warning, and the SDK could try to resume automically.
 *
 *  @param engine      The engine kit
 *  @param muxed      iceMux is or not used
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine iceMux:(bool)muxed;

- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine preIce:(bool)preIce;

@end

/**
 *@brief 内部事件注册
 */
@interface ByteRTCEngineKit()

- (void)registerInternaEventHandler:(id<ByteRTCEngineInternalEventDelegate> _Nullable)handler;

@end
