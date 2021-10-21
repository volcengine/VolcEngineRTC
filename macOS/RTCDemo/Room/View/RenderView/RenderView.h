//
//  RenderView.h
//  RTCDemo


#import <Cocoa/Cocoa.h>
#import <VolcEngineRTC/objc/rtc/ByteRTCEngineKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface RenderView : NSView

- (instancetype)initWithRTC:(ByteRTCEngineKit *)rtcEngineKit localUid:(NSString *)uid;

- (void)addUser:(NSString *)uid;

- (void)removeUser:(NSString *)uid;

@property (nonatomic, copy) NSString *currentUid;

@end

NS_ASSUME_NONNULL_END
