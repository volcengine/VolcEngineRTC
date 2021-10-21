//
//  UserRenderView.h
//  RTCDemo


#import <Cocoa/Cocoa.h>

NS_ASSUME_NONNULL_BEGIN

@interface UserRenderView : NSView

@property (nonatomic, copy) NSString *uid;

@property (nonatomic, strong) NSView *videoView;

@end

NS_ASSUME_NONNULL_END
