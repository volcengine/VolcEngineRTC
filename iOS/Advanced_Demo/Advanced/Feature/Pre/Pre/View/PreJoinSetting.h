//
//  PreJoinSetting.h
//  Advanced
//
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, RenderMode) {
    RenderMode_Hidden,
    RenderMode_Fit,
    RenderMode_Stretch
};

typedef NS_ENUM(NSUInteger, EffectsMode) {
    EffectsMode_Volc = 0,
    EffectsMode_None,
};

@interface PreJoinSetting : NSObject
@property (nonatomic, assign) BOOL useCustomCapture;
@property (nonatomic, assign) BOOL useCustomRender;

@property (nonatomic, assign) RenderMode localRenderMode;
@property (nonatomic, assign) RenderMode remoteRenderMode;

@property (nonatomic, assign) EffectsMode effectsMode;

@property (nonatomic, assign) BOOL isScreenShare;

@end

NS_ASSUME_NONNULL_END
