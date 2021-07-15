//
//  RoomAvatarRenderView.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/12.
//

#import <Cocoa/Cocoa.h>
#import "RoomUserModel.h"

static const NSInteger MaxAvatarNumber = 9;

typedef NS_ENUM(NSInteger, RoomAvatarStatus) {
    RoomAvatarStatusGalleryOne,
    RoomAvatarStatusGalleryTwo,
    RoomAvatarStatusGalleryFour,
    RoomAvatarStatusGalleryNine,
    RoomAvatarStatusSpaker,
};

@interface RoomAvatarRenderView : NSView

@property (nonatomic, assign) RoomAvatarStatus avatarStatus;

@property (nonatomic, strong) RoomUserModel *userModel;

@end
