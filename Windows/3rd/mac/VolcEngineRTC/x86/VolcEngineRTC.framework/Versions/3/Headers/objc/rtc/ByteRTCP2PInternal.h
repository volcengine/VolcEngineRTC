/*
 * Copyright (c) 2023 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC Internal
*/

#import "../ByteRTCVideo.h"

@protocol ByteRTCVideoP2PEventDelegate <NSObject>

@optional
- (void) onP2PConnectionStatusUpdated:(int)state;
- (void) onP2PSignalingStatusUpdated:(int)state;

@end

@interface ByteRTCVideo(ByteRTCVideoP2PEventDelegate)

/** {zh}
 * @hidden
 * @brief 设置P2P内部事件回调
 * @param delegate 当前app应用的P2P内部事件回调句柄
 * @notes  必须在joinChannel之前调用
 */
- (void)setP2PEventDelegate:(id<ByteRTCVideoP2PEventDelegate>_Nullable)delegate;

/** {zh}
 * @hidden
 * @brief 开启P2P
 * @param roomId 需要开启P2P的房间号
 * @param onlyLan 是否只开启局域网P2P
 * @notes  必须在joinChannel之前调用
 */
- (int)enableP2P:(NSString *_Nonnull)roomId onlyLan:(bool)onlyLan;

@end
