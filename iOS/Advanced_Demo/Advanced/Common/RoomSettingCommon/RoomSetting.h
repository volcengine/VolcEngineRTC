//
//  RoomSetting.h
//  Advanced
//
//  Created by bytedance on 2021/12/8.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface RoomSetting : NSObject
@property (nonatomic, assign) CGSize resolution;
@property (nonatomic, assign) NSInteger fps;
@property (nonatomic, assign) NSInteger bitrate;

@property (nonatomic, assign) NSInteger localRenderMirror;

+ (instancetype)defaultSetting;
@end

NS_ASSUME_NONNULL_END
