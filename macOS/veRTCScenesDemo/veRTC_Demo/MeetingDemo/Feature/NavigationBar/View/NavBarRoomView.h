//
//  NavBarRoomView.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/11.
//

#import <Cocoa/Cocoa.h>
#import "LoginModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface NavBarRoomView : NSView

@property (nonatomic, strong) LoginModel *loginModel;

@property (nonatomic, assign) BOOL isExpandList;

@property (nonatomic, assign) BOOL isRecord;

@property (nonatomic, assign) NSInteger meetingTime;

@end

NS_ASSUME_NONNULL_END
