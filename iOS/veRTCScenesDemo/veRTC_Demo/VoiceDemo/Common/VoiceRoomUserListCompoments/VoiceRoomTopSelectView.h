//
//  VoiceRoomTopSelectView.h
//  veRTC_Demo
//
//  Created by  on 2021/5/24.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import <UIKit/UIKit.h>
@class VoiceRoomTopSelectView;

NS_ASSUME_NONNULL_BEGIN

@protocol VoiceRoomTopSelectViewDelegate <NSObject>

- (void)voiceRoomTopSelectView:(VoiceRoomTopSelectView *)voiceRoomTopSelectView clickCancelAction:(id)model;

- (void)voiceRoomTopSelectView:(VoiceRoomTopSelectView *)voiceRoomTopSelectView clickSwitchItem:(BOOL)isAudience;

@end

@interface VoiceRoomTopSelectView : UIView

@property (nonatomic, weak) id<VoiceRoomTopSelectViewDelegate> delegate;

@property (nonatomic, copy) NSString *titleStr;

@end

NS_ASSUME_NONNULL_END
