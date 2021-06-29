//
//  ByteRtcRoomInternal.h
//  ByteRtcEngineKitSrc
//
//  Created by sakura on 2020/3/18.
//

#ifndef ByteRtcRoomInternal_h
#define ByteRtcRoomInternal_h

@interface ByteRtcRoom ()
- (instancetype _Nonnull)initWithRtcRoom:(bytertc::IRtcRoom *_Nonnull)rtcRoom roomId:(NSString *_Nonnull)roomId;

- (void)enableSubscribeSelf:(BOOL)enable;

- (void)destroyResourceInternal;

- (void)setByteRtcEngine:(id _Nullable)engine;

@end

#endif /* ByteRtcRoomInternal_h */
