//
//  GalleryModeLineView.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/14.
//

#import <UIKit/UIKit.h>
#import "RoomAvatarRenderView.h"

NS_ASSUME_NONNULL_BEGIN

@interface GalleryModeLineView : UIView

@property (nonatomic, strong, readonly) NSArray <RoomAvatarRenderView *> *avatarViewLists;

@end

NS_ASSUME_NONNULL_END
