//
//  LoginBottonBarView.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/8.
//

#import <Cocoa/Cocoa.h>
#import "LoginModel.h"

@class LoginBottonBarView;

typedef NS_ENUM(NSInteger, ButtonStatus) {
    ButtonStatusMic,
    ButtonStatusVideo,
    ButtonStatusSet,
    ButtonStatusStart,
};

NS_ASSUME_NONNULL_BEGIN

@protocol LoginBottonBarViewDelegate <NSObject>

- (void)loginBottonBarView:(LoginBottonBarView *)loginBottonBarView didSelectItemsAtStatus:(ButtonStatus)status clickButton:(TrackButton *)button;

@end

@interface LoginBottonBarView : NSView

- (void)updateUserNameTextFile:(NSString *)text;

- (void)updateBottomBar:(LoginModel *)loginModel;

@property (nonatomic, weak) id<LoginBottonBarViewDelegate> delegate;

@property (nonatomic, strong, readonly) LoginModel *loginModel;

@property (nonatomic, copy, readonly) NSString *roomId;

@property (nonatomic, copy, readonly) NSString *userName;

@property (nonatomic, assign, readonly) BOOL isEnableVideo;

@property (nonatomic, assign, readonly) BOOL isEnableAudio;

@end

NS_ASSUME_NONNULL_END
