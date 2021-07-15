//
//  VoiceRoomUserListtCell.h
//  veRTC_Demo
//
//  Created by  on 2021/5/19.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import <UIKit/UIKit.h>
@class VoiceRoomUserListtCell;

NS_ASSUME_NONNULL_BEGIN

@protocol VoiceRoomUserListtCellDelegate <NSObject>

- (void)voiceRoomUserListtCell:(VoiceRoomUserListtCell *)voiceRoomUserListtCell clickButton:(id)model;

@end

@interface VoiceRoomUserListtCell : UITableViewCell

@property (nonatomic, strong) VoiceControlUserModel *model;

@property (nonatomic, weak) id<VoiceRoomUserListtCellDelegate> delegate;

@end

NS_ASSUME_NONNULL_END
