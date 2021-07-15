//
//  VoiceRoomView.h
//  veRTC_Demo
//
//  Created by  on 2021/5/21.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface VoiceRoomView : UIView

- (void)joinUser:(VoiceControlUserModel *)user;

- (void)leaveUser:(NSString *)user;

- (void)audienceRaisedHandsSuccess:(NSString *)uid;

- (void)hostLowerHandSuccess:(NSString *)uid;

- (void)updateAllUser:(NSArray<VoiceControlUserModel *> *)userLists roomModel:(VoiceControlRoomModel *)roomModel;

- (void)updateUserMic:(NSString *)uid isMute:(BOOL)isMute;

- (void)updateUserHand:(NSString *)uid isHand:(BOOL)isHand;

- (void)updateHostUser:(NSString *)uid;

- (void)updateHostVolume:(NSDictionary<NSString *, NSNumber *> *_Nonnull)volumeInfo;

- (void)reloadData;

- (NSInteger)hostNumber;

- (NSArray<VoiceControlUserModel *> *)allUserLists;

@end

NS_ASSUME_NONNULL_END
