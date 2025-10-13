#import "VideoDecoder.h"
#import <CoreFoundation/CoreFoundation.h>

@interface VideoDecoder()
{
@public
    dispatch_semaphore_t _decodeSemaphore;
    NSLock *_lock;
}
@property(nonatomic,strong)NSMutableData *result;
@property(nonatomic,strong)NSMutableData *keyframeResult;


@property(nonatomic,strong)NSURL *url;
@property(nonatomic,assign) CMSampleBufferRef videoSamplebuffer;
@property(nonatomic,strong) AVAssetReaderOutput *videoTrackout;
@end

@implementation VideoDecoder

- (NSMutableData *)result {
    
    if (_result == nil) {
        _result = [NSMutableData data];
    }
    
    return _result;
}

- (NSMutableData *)keyframeResult {
    if (_keyframeResult == nil) {
        _keyframeResult = [NSMutableData data];
    }
    
    return _keyframeResult;
}

- (id)initWithURL:(NSURL*)localURL
{
    NSLog(@"initWithURL ----------------- begin");
    if (!(self = [super init])) {
        return  nil;
    }
    self->_decodeSemaphore = dispatch_semaphore_create(0);
    dispatch_semaphore_signal(self->_decodeSemaphore);
    self.url = localURL;
    self.autoDecode = NO;
    self.videoSamplebuffer = NULL;
    [self loadVideoFile];
    NSLog(@"initWithURL ----------------- end");
    return self;
}

- (void)loadVideoFile
{
    NSLog(@"-------start loadVideoFile");
    if (dispatch_semaphore_wait(self->_decodeSemaphore, DISPATCH_TIME_NOW) != 0) {
        return;
    }

    NSDictionary *inputOptions = @{
        AVURLAssetPreferPreciseDurationAndTimingKey:@(YES)
    };
    self.asset = [[AVURLAsset alloc] initWithURL:self.url options:inputOptions];
   
    __block  VideoDecoder *blockSelf  = self;
    CFAbsoluteTime startTime = CFAbsoluteTimeGetCurrent();
    [self.asset loadValuesAsynchronouslyForKeys:@[@"tracks",@"duration"] completionHandler:^{
        NSError *error = nil;
        AVKeyValueStatus status = [blockSelf.asset statusOfValueForKey:@"tracks" error:&error];
        if (status != AVKeyValueStatusLoaded) {
            NSLog(@"------------error %@",error);
            dispatch_semaphore_signal(blockSelf->_decodeSemaphore);
            return;
        }

        blockSelf.assetReader = [blockSelf createAssetReader];
        for (AVAssetReaderOutput *output in blockSelf.assetReader.outputs) {
            if ([output.mediaType isEqualToString:AVMediaTypeVideo]) {
                blockSelf.videoTrackout = output;
            }
        }

        if ([blockSelf.assetReader startReading] == NO) {
            NSLog(@"start reading failer");
            dispatch_semaphore_signal(blockSelf->_decodeSemaphore);
            return;
        }
        NSLog(@"----------time %f s",CFAbsoluteTimeGetCurrent() - startTime);

        dispatch_semaphore_signal(blockSelf->_decodeSemaphore);
        NSLog(@"-------reading start");
    }];
    dispatch_semaphore_wait(self->_decodeSemaphore, DISPATCH_TIME_FOREVER);
    NSLog(@"-------stop loadVideoFile");
}

- (NSData *)nextFrame:(bool *)is_key_frame
{
    while (self.assetReader.status == AVAssetReaderStatusReading ) {
        if (!self.videoTrackout ) {
           NSLog(@"track is nil-----------");
           continue;
        }
        self.videoSamplebuffer = [self.videoTrackout copyNextSampleBuffer];
        if (!self.videoSamplebuffer) {
            NSLog(@"buffer is nil-----------");
            break;
        }
        [self ReadAvccCovertAnnexb:self.videoSamplebuffer keyflag:is_key_frame];
        CMSampleBufferInvalidate(self.videoSamplebuffer);
        CFRelease(self.videoSamplebuffer);
        break;
    }

    return self.result;
}

- (AVAssetReader *)createAssetReader
{
    NSError *error = nil;

    AVAssetReader *assetReader = [AVAssetReader assetReaderWithAsset:self.asset error:&error];
    NSMutableDictionary *videoOutputSettings = [NSMutableDictionary dictionary];
    [videoOutputSettings setObject:@(kCVPixelFormatType_420YpCbCr8BiPlanarFullRange) forKey:(__bridge NSString*)kCVPixelBufferPixelFormatTypeKey];

    AVAssetTrack *videoTrack = [[self.asset tracksWithMediaType:AVMediaTypeVideo] objectAtIndex:0];
    if (!self.autoDecode) {
        videoOutputSettings = nil;
    }
    self.videoTrackout = [AVAssetReaderTrackOutput assetReaderTrackOutputWithTrack:videoTrack outputSettings:videoOutputSettings];
    self.videoTrackout.alwaysCopiesSampleData = NO;
    [assetReader addOutput:self.videoTrackout];
    return  assetReader;
}

- (void)dealloc{
    [self stopProcess];
}

- (void)stopProcess
{
    if (self.assetReader.status == AVAssetReaderStatusCompleted) {
        [self.assetReader cancelReading];
        self.assetReader = nil;
    }
    self.videoTrackout = nil;
    self.videoSamplebuffer = nil;
}

- (NSData *) ReadAvccCovertAnnexb:(CMSampleBufferRef)sampleBuffer keyflag:(bool *)is_key_frame{
    
    // Assume we have a CMSampleBufferRef named sampleBuffer
    CMTime presentationTimeStamp = CMSampleBufferGetPresentationTimeStamp(sampleBuffer);
    CMTime decodeTimeStamp = CMSampleBufferGetDecodeTimeStamp(sampleBuffer);

    // Convert CMTime to microseconds
    int64_t ptsMicroseconds = (int64_t)(CMTimeGetSeconds(presentationTimeStamp) * 1e6);
    int64_t dtsMicroseconds = (int64_t)(CMTimeGetSeconds(decodeTimeStamp) * 1e6);

//    NSLog(@"PTS in microseconds: %lld", ptsMicroseconds);
//    NSLog(@"DTS in microseconds: %lld", dtsMicroseconds);
    self.dts = dtsMicroseconds;
    self.pts = ptsMicroseconds;
    
    static uint8_t start_code[4] = { 0x00, 0x00, 0x00, 0x01 };
    if (!CMSampleBufferDataIsReady(sampleBuffer)) {
        NSLog(@"didCompressH264 data is not ready ");
        return self.result;
    }

    bool keyframe = false;
    int frame_len = 0;
    [self.result setLength:0];
  
    CFArrayRef attachmentsArray = CMSampleBufferGetSampleAttachmentsArray(sampleBuffer, 0);
    CFIndex  len;
    len = !attachmentsArray ? 0 : CFArrayGetCount(attachmentsArray);

    if(!len){
        keyframe = true;
        *is_key_frame = true;
    }else{
        CFBooleanRef notSync;
        CFDictionaryRef dict = (CFDictionaryRef)CFArrayGetValueAtIndex(attachmentsArray, 0);
        if(CFDictionaryGetValueIfPresent(dict,kCMSampleAttachmentKey_NotSync,(const void **)&notSync)){
            keyframe = !CFBooleanGetValue(notSync);
        }else{
            keyframe = true;
            *is_key_frame = true;
        }
    }

        CMFormatDescriptionRef format = CMSampleBufferGetFormatDescription(sampleBuffer);
        size_t sps_size, sps_cnt;
        const uint8_t *sparameterSet;
        OSStatus statusCode = CMVideoFormatDescriptionGetH264ParameterSetAtIndex(format, 0, &sparameterSet, &sps_size, &sps_cnt, 0 );
        if (statusCode == noErr) {
            size_t pps_size, pps_cnt;
            const uint8_t *pparameterSet;
            OSStatus statusCode = CMVideoFormatDescriptionGetH264ParameterSetAtIndex(format, 1, &pparameterSet, &pps_size, &pps_cnt, 0 );
            if (statusCode == noErr) {
                // Found pps
                NSData *sps = [NSData dataWithBytes:sparameterSet length:sps_size];
                NSData *pps = [NSData dataWithBytes:pparameterSet length:pps_size];
        
                uint8_t *data = (unsigned char *)[sps bytes];
                
                [self.result appendBytes:start_code length:4];
                [self.result appendBytes:data length:sps_size];

                data = (unsigned char *)[pps bytes];
                [self.result appendBytes:start_code length:4];
                [self.result appendBytes:data length:pps_size];

                frame_len = sps_size + 4 + pps_size + 4;
            }
        }

    CMBlockBufferRef data_buffer = CMSampleBufferGetDataBuffer(sampleBuffer);
    size_t length, total_len;
    char *data_pointer;
    OSStatus statusCodeRet = CMBlockBufferGetDataPointer(data_buffer, 0, &length, &total_len, &data_pointer);
    if (statusCodeRet == noErr) {
        size_t buffer_offset = 0;
        static const int avcc_h_len = 4;
        
        while (buffer_offset < total_len - avcc_h_len) {
            uint32_t nal_len = 0;
            memcpy(&nal_len, data_pointer + buffer_offset, avcc_h_len);
            nal_len = CFSwapInt32BigToHost(nal_len);
            NSData* data = [[NSData alloc] initWithBytes:(data_pointer + buffer_offset + avcc_h_len) length:nal_len];
         
            buffer_offset += avcc_h_len + nal_len;
            frame_len += buffer_offset;

            uint8_t *nal_data = (unsigned char *)[data bytes];
            int nal_type = (nal_data[0] & 0x1f);
            if (0x07 != nal_type && nal_type != 0x08) {
                [self.result appendBytes:start_code length:4];
                [self.result appendBytes:nal_data length:nal_len];
            }
        }
    }

    if(keyframe){
        *is_key_frame = true;
        [_lock lock];
        [self.keyframeResult setLength:0];
        [self.keyframeResult appendData:self.result];
        [_lock unlock];
        NSLog(@"-------------key frame");
    }
    return self->_result;
}

- (NSData *)getKeyFrame {
    [_lock lock];
    NSData *keyFrameData = self.keyframeResult;
    [_lock unlock];
    return keyFrameData;
}

- (int)height {
    return self.height;
}

- (int)width {
    return self.width;
}

- (int)getFramerate {
    return self.fps;
}
@end

