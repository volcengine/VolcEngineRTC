//
//  RoomAvatarRenderTagView.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/14.
//

#import <Cocoa/Cocoa.h>
#import "RoomUserModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface RoomAvatarRenderTagView : NSView

@property (nonatomic, strong) RoomUserModel *userModel;

@property (nonatomic, strong) NSFont *font;

@property (nonatomic, strong) NSColor *textColor;

@end

NS_ASSUME_NONNULL_END
