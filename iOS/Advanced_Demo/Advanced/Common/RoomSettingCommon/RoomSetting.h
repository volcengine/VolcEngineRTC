//
//  RoomSetting.h
//  Advanced
//
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface RoomSetting : NSObject
@property (nonatomic, assign) CGSize resolution;
@property (nonatomic, assign) NSInteger fps;
@property (nonatomic, assign) NSInteger bitrate;

@property (nonatomic, assign) NSInteger localRenderMirror;

+ (instancetype)defaultSetting;
@end

NS_ASSUME_NONNULL_END
