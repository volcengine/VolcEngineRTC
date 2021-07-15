//
//  MeetingScreenShareModel.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/5.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface MeetingScreenShareModel : NSObject

@property (nonatomic, copy) NSString *sourceName;

@property (nonatomic, assign) BOOL isScreen;

@property (nonatomic, assign) int sourceId;

@property (nonatomic, assign) NSInteger sourceType;

@end

NS_ASSUME_NONNULL_END
