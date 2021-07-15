//
//  NavigationBarViewController.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/11.
//

#import <Cocoa/Cocoa.h>
#import "LoginModel.h"

static NSString * _Nullable const NoticeUpdateRoomExpandListName = @"NoticeUpdateRoomExpandListName";
static NSString * _Nullable const NoticeClickRoomExpandListName = @"NoticeClickRoomExpandListName";



typedef NS_ENUM(NSInteger, NavigationBarStatus) {
    NavigationBarStatusLogin,
    NavigationBarStatusRoom,
};

NS_ASSUME_NONNULL_BEGIN

@interface NavigationBarViewController : NSViewController

@property (nonatomic, strong) LoginModel *loginModel;

@property (nonatomic, assign) NSInteger meetingTime;

- (void)updateUIWithStatus:(NavigationBarStatus)status;

@end

NS_ASSUME_NONNULL_END
