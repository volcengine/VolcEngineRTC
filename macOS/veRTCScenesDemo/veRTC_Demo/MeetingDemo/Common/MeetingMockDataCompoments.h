//
//  MeetingMockDataCompoments.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/15.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface MeetingMockDataCompoments : NSObject

+ (instancetype)sharedInstance;

@property(nonatomic, strong, readonly)NSArray<NSDictionary *> *resolutionData;
@property(nonatomic, strong, readonly)NSArray *framerateData;
@property(nonatomic, strong, readonly)NSArray *micInputDeviceData;
@property(nonatomic, strong, readonly)NSArray *micOutputDeviceData;
@property(nonatomic, strong, readonly)NSArray *cameraDeviceData;

@property(nonatomic, strong, readonly)NSArray<NSDictionary *> *screenResolutionData;
@property(nonatomic, strong, readonly)NSArray *screenFramerateData;

@end

NS_ASSUME_NONNULL_END
