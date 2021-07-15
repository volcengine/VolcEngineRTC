//
//  VoiceRoomViewController.h
//  veRTC_Demo
//
//  Created by  on 2021/5/18.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface VoiceRoomViewController : UIViewController

@property (nonatomic, copy) NSString *token;
@property (nonatomic, strong) VoiceControlRoomModel *roomModel;
@property (nonatomic, copy) NSArray<VoiceControlUserModel *> *userLists;

@property (nonatomic, strong) NSString *roomID;
@property (nonatomic, strong) NSString *userName;

- (void)addUser:(VoiceControlUserModel *)userModel;

- (void)removeUser:(VoiceControlUserModel *)userModel;

- (void)receivedRaiseHandWithUser:(NSString *)uid;

- (void)receivedRaiseHandInviteWithAudience;

- (void)receivedRaiseHandSucceedWithUser:(VoiceControlUserModel *)userModel;

- (void)receivedLowerHandSucceedWithUser:(NSString *)uid;

- (void)receivedMicChangeWithMute:(BOOL)isMute uid:(NSString *)uid;

- (void)receivedHostChangeWithNewHostUid:(VoiceControlUserModel *)hostUser;

- (void)hangUp;

@end

NS_ASSUME_NONNULL_END
