//
//  VoiceRoomItemButton.h
//  quickstart
//
//  Created by  on 2021/3/24.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import "BaseButton.h"

NS_ASSUME_NONNULL_BEGIN

@interface VoiceRoomItemButton : BaseButton

@property (nonatomic, copy) NSString *desTitle;

@property (nonatomic, assign) BOOL isAction;

@property (nonatomic, assign) NSInteger tagNum;

@end

NS_ASSUME_NONNULL_END
