/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngine Room Internal API
*/

@interface ByteRTCRoom ()

- (instancetype _Nonnull)initWithRtcRoom:(bytertc::IRtcRoom *_Nonnull)rtcRoom roomId:(NSString *_Nonnull)roomId;

- (void)enableSubscribeSelf:(BOOL)enable;

- (void)destroyResourceInternal;

- (void)setEngine:(id _Nullable)engine;

@end
