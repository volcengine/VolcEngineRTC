//
//  SpeakerModeView.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/9.
//

#import <Cocoa/Cocoa.h>
#import "RoomUserModel.h"
#import "RoomAvatarRenderView.h"

@interface SpeakerModeView : NSView

@property (nonatomic, copy) NSArray<RoomUserModel *> *dataLists;

@property (nonatomic, copy) NSString *screenStreamsUid;

- (void)updateAvatarHidden:(BOOL)isHidden;

@end
