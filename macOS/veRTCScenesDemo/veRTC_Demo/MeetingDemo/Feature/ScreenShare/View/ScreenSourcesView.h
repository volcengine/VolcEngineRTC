//
//  ScreenSourcesView.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/3.
//

#import <Cocoa/Cocoa.h>
#import "MeetingControlRoomModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface ScreenSourcesView : NSView

@property (nonatomic, strong) LoginModel *loginModel;

@property (nonatomic, strong) MeetingControlRoomModel *roomModel;

@property (copy, nonatomic) void(^clickCancelBLock)(void);

- (void)updateThumbnailWithDataLists:(NSArray *)dataLists;

@end

NS_ASSUME_NONNULL_END
