//
//  SetingModel.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/15.
//

#import <Foundation/Foundation.h>
@class SetingDeviceModel;
NS_ASSUME_NONNULL_BEGIN

@interface SetingModel : NSObject <NSCoding>

@property (nonatomic, assign) NSSize resolutionSize;

@property (nonatomic, assign) NSInteger frameRate;

@property (nonatomic, assign) NSInteger bitRate;

@property (nonatomic, assign) NSSize screenResolutionSize;

@property (nonatomic, assign) NSInteger screenFrameRate;

@property (nonatomic, assign) NSInteger screenBitRate;

@property (nonatomic, assign) NSInteger isOpenParam;

@property (nonatomic, strong) SetingDeviceModel *micInputDevice;

@property (nonatomic, strong) SetingDeviceModel *cameraInputDevice;

@end

NS_ASSUME_NONNULL_END
