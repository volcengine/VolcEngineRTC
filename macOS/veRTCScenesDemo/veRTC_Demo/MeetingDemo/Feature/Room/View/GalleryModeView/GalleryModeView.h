//
//  GalleryModeView.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/9.
//

#import <Cocoa/Cocoa.h>
#import "RoomUserModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface GalleryModeView : NSView

@property (nonatomic, copy) NSArray<RoomUserModel *> *dataLists;

@end

NS_ASSUME_NONNULL_END
