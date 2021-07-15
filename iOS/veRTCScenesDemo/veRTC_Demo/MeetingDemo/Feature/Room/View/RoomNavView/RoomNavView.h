//
//  RoomNavView.h
//  quickstart
//
//  Created by  on 2021/3/23.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import <UIKit/UIKit.h>
@class RoomNavView;

typedef NS_ENUM(NSInteger, RoomNavStatus) {
    RoomNavStatusSwitchCamera,
    RoomNavStatusHangeup
};

NS_ASSUME_NONNULL_BEGIN

@protocol RoomNavViewDelegate <NSObject>

- (void)roomNavView:(RoomNavView *)roomNavView didSelectStatus:(RoomNavStatus)status;

@end

@interface RoomNavView : UIView

@property (nonatomic, strong) RoomVideoSession *localVideoSession;

@property (nonatomic, weak) id<RoomNavViewDelegate> delegate;

@property (nonatomic, assign) NSInteger meetingTime;

@end

NS_ASSUME_NONNULL_END
