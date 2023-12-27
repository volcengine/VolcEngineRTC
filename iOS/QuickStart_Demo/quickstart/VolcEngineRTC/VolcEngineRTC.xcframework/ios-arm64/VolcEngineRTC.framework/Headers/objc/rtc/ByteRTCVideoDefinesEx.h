#import "ByteRTCDefines.h"

typedef NS_ENUM(NSUInteger, ByteRTCVideoContentCategory) {
    ByteRTCVideoContentCategoryCamera = 0,
    ByteRTCVideoContentCategoryScreen = 1,
};

BYTERTC_APPLE_EXPORT @interface ByteRTCVideoSourceConfig : NSObject
@property (assign, nonatomic) ByteRTCVideoSourceType sourceType;
@property (assign, nonatomic) ByteRTCVideoContentCategory contentCategory;
@end

typedef NS_ENUM(NSUInteger, ByteRTCStreamPriority) {
    ByteRTCStreamPriorityLow = 0,
    ByteRTCStreamPriorityNormal = 1,
    ByteRTCStreamPriorityHigh = 2,
};

BYTERTC_APPLE_EXPORT @interface ByteRTCAudioContentTypeConfig : NSObject
@property(assign, nonatomic) BOOL hasMic;
@property(assign, nonatomic) BOOL hasScreenAudio;
@property(assign, nonatomic) BOOL hasMediaPlayer;
@end

BYTERTC_APPLE_EXPORT @interface ByteRTCAudioEncodeConfig : NSObject
@property(nonatomic, assign) NSInteger codecType;
@property(nonatomic, assign) NSInteger encMode;
@property(nonatomic, assign) NSInteger channelNum;
@property(nonatomic, assign) NSInteger encBitrate;
@property(nonatomic, assign) NSInteger useDtx;
@property(nonatomic, assign) NSInteger useInbandfec;
@property(nonatomic, assign) NSInteger sampleRate;
@property(nonatomic, assign) NSInteger packetSize;
@end

BYTERTC_APPLE_EXPORT @interface ByteRTCStreamKey : NSObject
@property(nonatomic, copy, nullable) NSString *userId;
@property(nonatomic, copy, nullable) NSString *roomId;
@property(nonatomic, assign) ByteRTCStreamIndex streamIndex;
@end
