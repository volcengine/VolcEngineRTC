//
//  TrackButton.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/11.
//

#import <Cocoa/Cocoa.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, TrackButtonStatus) {
    TrackButtonStatusDefault = 0,
    TrackButtonStatusHover,
    TrackButtonStatusActive,
    TrackButtonStatusDisabled,
};

@interface TrackButton : NSButton

@property (nonatomic, assign) BOOL isClose;

@property (nonatomic, copy) NSString *tipTitle;

@property (nonatomic, assign) CGFloat offsetX;

@property (nonatomic, assign) BOOL simulation;

@property (nonatomic, assign) TrackButtonStatus currentStatus;

@property (nonatomic, copy) void (^changeStatus)(TrackButtonStatus status);

- (void)bingBackColorWithStatus:(TrackButtonStatus)status color:(NSColor *)color;

- (void)bingImageWithStatus:(TrackButtonStatus)status image:(NSImage *)image;

- (void)bingImageWithType:(BOOL)isClose image:(NSImage *)image;

- (void)removeTip;

@end

NS_ASSUME_NONNULL_END
