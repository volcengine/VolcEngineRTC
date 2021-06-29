//
//  ParticipantListsView.h
//  SceneRTCDemo
//
//  Created by on 2021/3/10.
//

#import <Cocoa/Cocoa.h>
#import "ParticipantModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface ParticipantListsView : NSView

@property (nonatomic, assign) BOOL isLoginHost;

@property (nonatomic, copy) NSArray<ParticipantModel *> *dataLists;

@end

NS_ASSUME_NONNULL_END
