//
//  CustomCameraCapture.m


#import <AVFoundation/AVFoundation.h>
#import <UIKit/UIKit.h>
#import "CustomCameraCapture.h"

@interface CustomCameraCapture () <AVCaptureVideoDataOutputSampleBufferDelegate>

@property (nonatomic, strong) AVCaptureSession *captureSession;
@property (nonatomic, strong) AVCaptureConnection *captureConnection;
@property (nonatomic, strong) AVCaptureDevice *currentDevice;
@property (nonatomic, strong) NSCondition *captureChangeCondition;

@property (nonatomic, strong) NSLock *orientationLock;
@property (nonatomic, assign) UIInterfaceOrientation orientation;
@property (nonatomic, assign) BOOL captureIsChanging;
@property (nonatomic, assign) BOOL captureStarted;

@property (nonatomic, assign) BOOL mirror;

@property (nonatomic, strong) dispatch_queue_t capture_queue;

@end

@implementation CustomCameraCapture

- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    [self stopCamera];
}

- (instancetype)init {
    self = [super init];
    if (self) {
        _captureSession = [[AVCaptureSession alloc] init];
        _captureSession.usesApplicationAudioSession = NO;
        _captureSession.sessionPreset = AVCaptureSessionPresetInputPriority;
        _captureIsChanging = NO;
        _captureChangeCondition = [[NSCondition alloc] init];
        _mirror = YES;

        if (!_captureSession || !_captureChangeCondition) {
            return nil;
        }

        AVCaptureVideoDataOutput *capture_output = [[AVCaptureVideoDataOutput alloc] init];
        NSString *key = (NSString *)kCVPixelBufferPixelFormatTypeKey;
        NSNumber *value = [NSNumber numberWithUnsignedInt:kCVPixelFormatType_32BGRA];

        NSDictionary *video_settings = [NSDictionary dictionaryWithObject:value forKey:key];
        capture_output.videoSettings = video_settings;

        if ([_captureSession canAddOutput:capture_output]) {
            [_captureSession addOutput:capture_output];
        }

        _capture_queue = dispatch_queue_create("VideoCaptureObjC", DISPATCH_QUEUE_SERIAL);

        _orientationLock = [[NSLock alloc] init];
        _orientation = UIInterfaceOrientationPortrait;

        dispatch_async(dispatch_get_main_queue(), ^{
            [[UIDevice currentDevice] beginGeneratingDeviceOrientationNotifications];
        });
        NSNotificationCenter *notify = [NSNotificationCenter defaultCenter];
        [notify addObserver:self
                   selector:@selector(onVideoError:)
                       name:AVCaptureSessionRuntimeErrorNotification
                     object:_captureSession];
        [notify addObserver:self
                   selector:@selector(handleStatusbarOrientationChange:)
                       name:UIApplicationDidChangeStatusBarOrientationNotification
                     object:nil];
        dispatch_async(_capture_queue, ^{
            [self updateStatusbarOrientation];
        });
    }
    return self;
}

#pragma mark - Publish Action

- (BOOL)startCamera {
    [self waitCaptureChange];

    if (!_captureSession) {
        NSLog(@"capture session is NULL!");
        return NO;
    }

    OSType format = kCVPixelFormatType_32BGRA;

    // Get capture session current output, first output as default output.
    AVCaptureVideoDataOutput *current_output = [[_captureSession outputs] firstObject];
    if (!current_output) {
        NSLog(@"capture session have not AVCaptureVideoDataOutput!");
        return NO;
    }

    // set pixel format
    NSDictionary *outputSettings = [NSDictionary dictionaryWithObjectsAndKeys:[NSNumber numberWithInt:format],
                                                                              (id)kCVPixelBufferPixelFormatTypeKey,
                                                                              nil];
    [current_output setVideoSettings:outputSettings];

    // Register delegate to capture session output.
    // When was capture frame arrived, delegate't captureOutput will be called.
    [current_output setSampleBufferDelegate:self queue:_capture_queue];

    _captureStarted = YES;
    dispatch_async(_capture_queue, ^{
        [self startCaptureWithOutputBackground:current_output];
    });
    return YES;
}

- (BOOL)stopCamera {
    dispatch_async(dispatch_get_main_queue(), ^{
        [[UIDevice currentDevice] endGeneratingDeviceOrientationNotifications];
    });

    [self waitCaptureChange];

    [[[_captureSession outputs] firstObject] setSampleBufferDelegate:nil queue:NULL];

    if (!_captureConnection) {
        NSLog(@"stop camera failed, capture session is NULL!");
        return NO;
    }

    @synchronized(self) {
        _captureStarted = NO;
    }

    dispatch_async(_capture_queue, ^(void) {
        [self stopCaptureBackground];
    });
    return YES;
}

- (BOOL)switchCameraIsFront:(BOOL)isFront {
    [self waitCaptureChange];

    NSArray *current_outputs = [_captureSession inputs];
    // Remove current input
    if ([current_outputs count] > 0) {
        AVCaptureInput *input = (AVCaptureInput *)[current_outputs objectAtIndex:0];
        [_captureSession removeInput:input];
    }

    AVCaptureDevice *target_device = nil;

    if (isFront) {
        target_device = [self cameraWithPosition:AVCaptureDevicePositionFront];
    }else {
        target_device = [self cameraWithPosition:AVCaptureDevicePositionBack];
    }

    if (!target_device) {
        NSLog(@"cant not find target camera width unique id: ");
        return NO;
    }

    _currentDevice = target_device;

    // Now create capture session input with AVCaptureDevice
    NSError *device_error = nil;
    AVCaptureDeviceInput *new_capture_input =
        [AVCaptureDeviceInput deviceInputWithDevice:target_device
                                              error:&device_error];

    if (!new_capture_input) {
        const char *err_msg = [[device_error localizedDescription] UTF8String];
        NSLog(@"deviceInputWithDevice error:%s", err_msg);
        return NO;
    }

    // Try to add our new capture input to the capture session
    [_captureSession beginConfiguration];

    BOOL addedCaptureInput = NO;
    if ([_captureSession canAddInput:new_capture_input]) {
        [_captureSession addInput:new_capture_input];
        addedCaptureInput = YES;
    } else {
        addedCaptureInput = NO;
    }

    AVCaptureVideoDataOutput *current_output = [[_captureSession outputs] firstObject];
    _captureConnection = [current_output connectionWithMediaType:AVMediaTypeVideo];
    _captureConnection.videoOrientation = AVCaptureVideoOrientationPortrait;
    _captureConnection.videoMirrored = self.mirror;
    
    [_captureSession commitConfiguration];

    // Release lock
    [self signalCaptureChange];

    return addedCaptureInput;
}

- (AVCaptureDevice *)cameraWithPosition:(AVCaptureDevicePosition)position{
    NSArray *devices = [AVCaptureDevice devicesWithMediaType:AVMediaTypeVideo];
    for ( AVCaptureDevice *device in devices )
        if ( device.position == position ){
            return device;
        }
    return nil;
}

#pragma mark - AVCaptureVideoDataOutputSampleBufferDelegate

- (void)captureOutput:(AVCaptureOutput*)capture_output
    didOutputSampleBuffer:(CMSampleBufferRef)sample_buffer
           fromConnection:(AVCaptureConnection*)connection {
    @synchronized(self) {
        if (!_captureStarted) {
            NSLog(@"capture output, but owner is NULL!");
            return;
        }

        CVImageBufferRef video_frame = CMSampleBufferGetImageBuffer(sample_buffer);
        CMTime time = CMSampleBufferGetPresentationTimeStamp(sample_buffer);
        
        if ([self.captureDelegate respondsToSelector:@selector(customCameraCapture:didOutputBuffer:time:)]) {
            [self.captureDelegate customCameraCapture:self didOutputBuffer:video_frame time:time];
        }
    }
}

#pragma mark - Notification

- (void)handleStatusbarOrientationChange:(NSNotification *)notification {
    [self updateStatusbarOrientation];
}

- (void)onVideoError:(NSNotification*)notification {
    // TODO(sjlee): make the specific error handling with this notification.
    NSLog(@"[AVCaptureSession startRunning] error.");
}

#pragma mark - Private Action

// This method SHOULD be called by async in background.
- (void)startCaptureWithOutputBackground:(AVCaptureVideoDataOutput*)current_output {
    if ([_currentDevice lockForConfiguration:NULL] != YES) {
        return;
    }
    
    // Ready to configure AVCaptureSession
    [_captureSession beginConfiguration];

    //
    _captureConnection = [current_output connectionWithMediaType:AVMediaTypeVideo];
    _captureConnection.videoOrientation = AVCaptureVideoOrientationPortrait;
    _captureConnection.videoMirrored = _mirror;

    // Set frame rate
    [self configCaptureFormat];

    // Configuring finished , commit settings to AVCaptureSession.
    [_captureSession commitConfiguration];

    [_currentDevice unlockForConfiguration];

    // Start running
    [_captureSession startRunning];
    NSLog(@"capture has started!");

    // Release lock
    [self signalCaptureChange];
}

- (void)stopCaptureBackground {
    [_captureSession stopRunning];
    [self signalCaptureChange];
}

- (void)updateStatusbarOrientation {
    if ([NSThread isMainThread]) {
        [_orientationLock lock];
        _orientation = [[UIApplication sharedApplication] statusBarOrientation];
        [_orientationLock unlock];
    } else {
        dispatch_sync(dispatch_get_main_queue(), ^{
            [_orientationLock lock];
            _orientation = [[UIApplication sharedApplication] statusBarOrientation];
            [_orientationLock unlock];
        });
    }
}

- (void)configCaptureFormat {
    // set resolution
    // Find the format closest to what you are looking for
    //  this is just one way of finding it
    AVCaptureDeviceFormat *best_format;
    
    for (AVCaptureDeviceFormat* format in [_currentDevice formats]) {
        best_format = format;
    }

    [_currentDevice setActiveFormat:best_format];

    // set framerate
    AVCaptureDeviceFormat* current_format = [_currentDevice activeFormat];
    AVFrameRateRange* range;
    int32_t max_fps_supported = 0, min_fps_supported = 0;
    for (range in current_format.videoSupportedFrameRateRanges) {
        if (range.maxFrameRate > max_fps_supported) {
            max_fps_supported = range.maxFrameRate;
        }
        
        if (range.minFrameRate < min_fps_supported || !min_fps_supported) {
            min_fps_supported = range.minFrameRate;
        }
    }
}

- (void)signalCaptureChange {
    [_captureChangeCondition lock];

    _captureIsChanging = NO;

    [_captureChangeCondition signal];
    [_captureChangeCondition unlock];
}

- (void)waitCaptureChange {
    [_captureChangeCondition lock];

    while (_captureIsChanging) {
        NSLog(@"waiting other change completed!");
        [_captureChangeCondition wait];
    }
    _captureIsChanging = YES;

    [_captureChangeCondition unlock];
}

- (AVCaptureVideoOrientation) videoOrientationFromCurrentDeviceOrientation {
    switch (_orientation) {
        case UIInterfaceOrientationPortrait: {
            return AVCaptureVideoOrientationPortrait;
        }
        case UIInterfaceOrientationLandscapeLeft: {
            return AVCaptureVideoOrientationLandscapeLeft;
        }
        case UIInterfaceOrientationLandscapeRight: {
            return AVCaptureVideoOrientationLandscapeRight;
        }
        case UIInterfaceOrientationPortraitUpsideDown: {
            return AVCaptureVideoOrientationPortraitUpsideDown;
        }
        default:
        return AVCaptureVideoOrientationPortrait;
    }
}

@end
