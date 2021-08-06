//
//  ByteRtcEngineKitInternal.h
//  ByteRtcEngineKit
//
//  Created by yanchangqing on 2018/7/26.
//  Copyright © 2018年 bytedance. All rights reserved.
//

#pragma once

#if TARGET_OS_IPHONE || TARGET_OS_SIMULATOR
#import <UIKit/UIKit.h>
#elif TARGET_OS_OSX
#import <AppKit/AppKit.h>
#endif

#import "ByteRtcEngineKitDefines.h"
@class ByteRtcEngineKit;

@protocol ByteEngineInternalEventDelegate <NSObject>
@optional

#pragma mark SDK common delegate

/**
 *  The warning occurred in SDK. The APP could igonre the warning, and the SDK could try to resume automically.
 *
 *  @param engine      The engine kit
 *  @param muxed      iceMux is or not used
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine iceMux:(bool)muxed;

- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine preIce:(bool)preIce;

@end

/**
 *@brief 内部事件注册
 */
@interface ByteRtcEngineKit()
- (void)registerInternaEventHandler:(id<ByteEngineInternalEventDelegate> _Nullable)handler;
@end
