#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

@interface VideoDecoder : NSObject
@property(nonatomic,strong)AVAsset *asset;
@property(nonatomic,strong)AVAssetReader *assetReader;
@property(nonatomic,assign)BOOL autoDecode;
@property(nonatomic,assign)int height;
@property(nonatomic,assign)int width;
@property(nonatomic,assign)int fps;

@property (nonatomic, assign) int64_t dts;
@property (nonatomic, assign) int64_t pts;


- (id)initWithURL:(NSURL*)localURL;
- (NSData *)getKeyFrame;
- (NSData *)nextFrame:(bool *)is_key_frame;
- (int)height ;
- (int)width ;
- (int)getFramerate ;

@end
