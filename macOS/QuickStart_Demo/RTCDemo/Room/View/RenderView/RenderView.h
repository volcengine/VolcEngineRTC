//
//  RenderView.h
//  RTCDemo


#import <Cocoa/Cocoa.h>
#import <VolcEngineRTC/VolcEngineRTC.h>

NS_ASSUME_NONNULL_BEGIN

@interface RenderView : NSView

- (instancetype)initWithRTC:(ByteRTCVideo *)videoEngine localUid:(NSString *)uid;

- (void)addUser:(NSString *)uid roomid:(NSString *)roomId;

- (void)removeUser:(NSString *)uid roomid:(NSString *)roomId;

@property (nonatomic, copy) NSString *currentUid;

@end

NS_ASSUME_NONNULL_END
