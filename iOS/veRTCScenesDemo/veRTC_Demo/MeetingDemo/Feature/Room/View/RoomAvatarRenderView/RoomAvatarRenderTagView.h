//
//  RoomAvatarRenderTagView.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/14.
//

#import <UIKit/UIKit.h>
#import "RoomVideoSession.h"

NS_ASSUME_NONNULL_BEGIN

@interface RoomAvatarRenderTagView : UIView

@property (nonatomic, strong) RoomVideoSession *userModel;

@property (nonatomic, assign) BOOL hiddenBG;

@property (nonatomic, strong) UIFont *font;

@property (nonatomic, strong) UIColor *textColor;

@end

NS_ASSUME_NONNULL_END
