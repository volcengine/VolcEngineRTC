/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC Room Internal API
*/

@interface RTSRoom ()

- (instancetype _Nonnull)initWithRtsRoom:(bytertc::IRTSRoom *_Nonnull)rtsRoom roomId:(NSString *_Nonnull)roomId;

@end
