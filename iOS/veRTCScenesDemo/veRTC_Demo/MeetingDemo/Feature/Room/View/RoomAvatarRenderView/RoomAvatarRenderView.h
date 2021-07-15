//
//  RoomAvatarRenderView.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/12.
//

#import <UIKit/UIKit.h>

typedef NS_ENUM(NSInteger, RoomAvatarStatus) {
    //Normal Jiugongge
    RoomAvatarStatusGalleryNone,
    //One person nine squares
    RoomAvatarStatusGalleryOne,
    //Full Jiugongge
    RoomAvatarStatusGalleryFull,
    //Speaker
    RoomAvatarStatusSpaker,
};

@interface RoomAvatarRenderView : UIView

@property (nonatomic, assign) RoomAvatarStatus avatarStatus;

@property (nonatomic, strong) RoomVideoSession *userModel;

@end
