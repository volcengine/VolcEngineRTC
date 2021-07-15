//
//  MeetingScreenComponents.h
//  quickstart
//
//  Created by  on 2021/4/6.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MeetingScreenComponents : NSObject

@property (nonatomic, assign, readonly) BOOL isSharing;

@property (nonatomic, assign) BOOL isTurnOffCamera;

- (void)start:(void (^)(void))block;

- (void)stop;

@end
