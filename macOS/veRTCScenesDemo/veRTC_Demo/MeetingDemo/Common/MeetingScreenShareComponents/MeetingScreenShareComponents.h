//
//  MeetingScreenShareComponents.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/2.
//

#import <Foundation/Foundation.h>
#import "MeetingScreenShareModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface MeetingScreenShareComponents : NSObject

- (NSArray<MeetingScreenShareModel *> *)screenCaptureSourcesWithThumbnailSize:(NSSize)thumbnailSize;

@end

NS_ASSUME_NONNULL_END
