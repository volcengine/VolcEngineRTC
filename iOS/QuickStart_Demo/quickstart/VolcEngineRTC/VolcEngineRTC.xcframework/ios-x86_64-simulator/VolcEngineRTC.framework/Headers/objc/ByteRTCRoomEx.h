#import "ByteRTCRoom.h"
#import "rtc/ByteRTCVideoDefinesEx.h"

@class ByteRTCRoomEx;

@protocol ByteRTCRoomDelegateEx <NSObject>
@optional
- (void)rtcRoom:(ByteRTCRoom* _Nonnull)rtcRoom
        onUserPublishStream:(ByteRTCRemoteStreamKey* _Nonnull)streamKey
                   isScreen:(BOOL)isScreen
            mediaStreamType:(ByteRTCMediaStreamType)type;

- (void)rtcRoom:(ByteRTCRoom* _Nonnull)rtcRoom
        onUserUnpublishStream:(ByteRTCRemoteStreamKey* _Nonnull)streamKey
              mediaStreamType:(ByteRTCMediaStreamType)type
                       reason:(ByteRTCStreamRemoveReason)reason;

- (void)rtcRoom:(ByteRTCRoom* _Nonnull)rtcRoom
        onStreamStateChanged:(ByteRTCStreamKey* _Nonnull)streamKey
                       state:(NSInteger)state
                   extraInfo:(NSString* _Nonnull)extraInfo;
@end

BYTERTC_APPLE_EXPORT @interface ByteRTCRoomEx : ByteRTCRoom

@property(nonatomic, weak) id<ByteRTCRoomDelegateEx> _Nullable delegateEx;

- (int)publishStream:(ByteRTCStreamIndex)streamIndex mediaStreamType:(ByteRTCMediaStreamType)type;

- (int)unpublishStream:(ByteRTCStreamIndex)streamIndex mediaStreamType:(ByteRTCMediaStreamType)type;

- (int)subscribeStream:(NSString* _Nonnull)userId
            streamIndex:(ByteRTCStreamIndex)streamIndex
        mediaStreamType:(ByteRTCMediaStreamType)mediaStreamType;

- (int)unsubscribeStream:(NSString* _Nonnull)userId
             streamIndex:(ByteRTCStreamIndex)streamIndex
         mediaStreamType:(ByteRTCMediaStreamType)mediaStreamType;

- (int)setRTCRoomDelegateEx:(id<ByteRTCRoomDelegateEx> _Nullable)roomDelegate;

@end
