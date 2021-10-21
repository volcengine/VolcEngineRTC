//
//  BottomView.h
//  RTCDemo


#import <Cocoa/Cocoa.h>

NS_ASSUME_NONNULL_BEGIN

@interface BottomView : NSView

@property (nonatomic, copy) void (^clickCancelBlock)(void);

@property (nonatomic, copy) void (^clickCameraBlock)(BOOL enable);

@property (nonatomic, copy) void (^clickMicBlock)(BOOL enable);

@end

NS_ASSUME_NONNULL_END
