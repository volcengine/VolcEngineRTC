//
//  VoiceUserAvatarCell.h
//  veRTC_Demo
//
//  Created by  on 2021/5/19.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, AvatarCellStatus) {
    AvatarCellStatusMic,
    AvatarCellStatusAudience,
};

@interface VoiceUserAvatarCell : UICollectionViewCell

@property (nonatomic, strong) VoiceControlUserModel *model;

@property (nonatomic, assign) AvatarCellStatus status;

@end

NS_ASSUME_NONNULL_END
