//
//  BottomView.m
//  RTCDemo


#import "BottomView.h"
#import "Masonry.h"
#import "NSColor+CorlorString.h"
#import "NSView+Snippet.h"

@interface BottomView ()

@property (nonatomic, strong) NSButton *micButton;
@property (nonatomic, strong) NSButton *cameraButton;
@property (nonatomic, strong) NSButton *cancelButton;
@property (nonatomic, strong) NSView *lineView;
@property (nonatomic, assign) BOOL isEnableMic;
@property (nonatomic, assign) BOOL isEnableCamera;

@end

@implementation BottomView

- (instancetype)init {
    self = [super init];
    if (self) {
        _isEnableMic = YES;
        _isEnableCamera = YES;
        
        [self addSubview:self.micButton];
        [self.micButton mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.mas_equalTo(70);
            make.centerY.equalTo(self);
            make.size.mas_equalTo(CGSizeMake(28, 28));
        }];
        
        [self addSubview:self.cameraButton];
        [self.cameraButton mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.mas_equalTo(162);
            make.centerY.equalTo(self);
            make.size.mas_equalTo(CGSizeMake(28, 28));
        }];
        
        [self addSubview:self.cancelButton];
        [self.cancelButton mas_makeConstraints:^(MASConstraintMaker *make) {
            make.right.mas_equalTo(-38);
            make.centerY.equalTo(self);
            make.size.mas_equalTo(CGSizeMake(32, 32));
        }];
        
        [self addSubview:self.lineView];
        [self.lineView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.right.mas_equalTo(-111);
            make.centerY.equalTo(self);
            make.size.mas_equalTo(CGSizeMake(2, 32));
        }];
        
    }
    return self;
}

- (void)micButtonAction {
    if (_isEnableMic) {
        _isEnableMic = NO;
        [_micButton setImage:[NSImage imageNamed:@"control_mic_disable"]];
    } else {
        _isEnableMic = YES;
        [_micButton setImage:[NSImage imageNamed:@"control_mic"]];
    }
    if (self.clickMicBlock) {
        self.clickMicBlock(_isEnableMic);
    }
}

- (void)cameraButtonAction {
    if (_isEnableCamera) {
        _isEnableCamera = NO;
        [_cameraButton setImage:[NSImage imageNamed:@"control_video_disable"]];
    } else {
        _isEnableCamera = YES;
        [_cameraButton setImage:[NSImage imageNamed:@"control_video"]];
    }
    if (self.clickCameraBlock) {
        self.clickCameraBlock(_isEnableCamera);
    }
}

- (void)cancelButtonAction {
    if (self.clickCancelBlock) {
        self.clickCancelBlock();
    }
}

#pragma mark - getter

- (NSView *)lineView {
    if (!_lineView) {
        _lineView = [[NSView alloc] init];
        [_lineView setBackgroundColor:[NSColor colorFromHexString:@"#FFFFFF"]];
    }
    return _lineView;
}

- (NSButton *)micButton {
    if (!_micButton) {
        _micButton = [[NSButton alloc] init];
        [_micButton setImage:[NSImage imageNamed:@"control_mic"]];
        [_micButton setTarget:self];
        [_micButton setAction:@selector(micButtonAction)];
    }
    return _micButton;
}

- (NSButton *)cameraButton {
    if (!_cameraButton) {
        _cameraButton = [[NSButton alloc] init];
        [_cameraButton setImage:[NSImage imageNamed:@"control_video"]];
        [_cameraButton setTarget:self];
        [_cameraButton setAction:@selector(cameraButtonAction)];
    }
    return _cameraButton;
}

- (NSButton *)cancelButton {
    if (!_cancelButton) {
        _cancelButton = [[NSButton alloc] init];
        [_cancelButton setImage:[NSImage imageNamed:@"control_hangup"]];
        [_cancelButton setTarget:self];
        [_cancelButton setAction:@selector(cancelButtonAction)];
    }
    return _cancelButton;
}

@end
