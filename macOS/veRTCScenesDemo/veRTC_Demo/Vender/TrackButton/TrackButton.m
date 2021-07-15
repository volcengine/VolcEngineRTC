//
//  TrackButton.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/11.
//

#import "TrackButton.h"
#import "TrackTipView.h"

@interface TrackButton ()

@property (nonatomic, strong) NSMutableDictionary *colorDic;

@property (nonatomic, strong) NSMutableDictionary *imageDic;

@property (nonatomic, strong) NSMutableDictionary *imageInfoDic;

@property (nonatomic, strong) TrackTipView *tipImageView;

@end

@implementation TrackButton

- (instancetype)init {
    self = [super init];
    if (self) {
        _currentStatus = TrackButtonStatusDefault;
        _isClose = NO;
        
        [self updateUIWithStatus];
    }
    return self;
}

- (void)updateTrackingAreas {
    NSArray * trackingAreas = [self trackingAreas];
    for (NSTrackingArea *area in trackingAreas) {
        [self removeTrackingArea:area];
    }
    
    NSTrackingArea *trackingArea = [[NSTrackingArea alloc] initWithRect:self.bounds
                                                                options:(NSTrackingMouseEnteredAndExited |
                                                                         NSTrackingMouseMoved |
                                                                         NSTrackingActiveInActiveApp |
                                                                         NSTrackingInVisibleRect |
                                                                         NSTrackingAssumeInside |
                                                                         NSTrackingCursorUpdate)
                                                                  owner:self
                                                               userInfo:nil];
    [self addTrackingArea:trackingArea];
}

#pragma mark - Publish Action

- (void)setCurrentStatus:(TrackButtonStatus)currentStatus {
    _currentStatus = currentStatus;
    [self updateUIWithStatus];
}

- (void)setTipTitle:(NSString *)tipTitle {
    _tipTitle = tipTitle;
    self.tipImageView.title = tipTitle;
}

- (void)setIsClose:(BOOL)isClose {
    if (_isClose != isClose) {
        _isClose = isClose;
        
        if ([NSThread mainThread]) {
            NSString *key = [NSString stringWithFormat:@"%ld",(long)isClose];
            NSImage *image = self.imageInfoDic[key];
            if (image && [image isKindOfClass:[NSImage class]]) {
                [self setImage:image];
            }
        } else {
            dispatch_async(dispatch_get_main_queue(), ^{
                NSString *key = [NSString stringWithFormat:@"%ld",(long)isClose];
                NSImage *image = self.imageInfoDic[key];
                if (image && [image isKindOfClass:[NSImage class]]) {
                    [self setImage:image];
                }
            });
        }
    }
}

- (void)bingBackColorWithStatus:(TrackButtonStatus)status color:(NSColor *)color {
    if (color && [color isKindOfClass:[NSColor class]]) {
        NSString *key = [NSString stringWithFormat:@"%ld",(long)status];
        [self.colorDic setValue:color forKey:key];
        
        if (status == TrackButtonStatusDefault) {
            [self updateUIWithStatus];
        }
    }
}

- (void)bingImageWithStatus:(TrackButtonStatus)status image:(NSImage *)image {
    if (image && [image isKindOfClass:[NSImage class]]) {
        NSString *key = [NSString stringWithFormat:@"%ld",(long)status];
        [self.imageDic setValue:image forKey:key];
        
        if (status == TrackButtonStatusDefault) {
            [self updateUIWithStatus];
        }
    }
}

- (void)bingImageWithType:(BOOL)isClose image:(NSImage *)image {
    if (image && [image isKindOfClass:[NSImage class]]) {
        NSString *key = [NSString stringWithFormat:@"%ld",(long)isClose];
        [self.imageInfoDic setValue:image forKey:key];
        
        if (!isClose) {
            [self setImage:image];
        }
    }
}

- (void)setHidden:(BOOL)hidden {
    [super setHidden:hidden];
    if (hidden) {
        [self removeTip];
    }
}

#pragma mark - Private Action

- (void)showTip {
    if (self.tipTitle.length > 0) {
        AppDelegate *appDelegate = (AppDelegate *)[NSApplication sharedApplication].delegate;
        NSView *windowView = appDelegate.windowManager.currentWindowController.window.contentView;
        
        if (windowView && [windowView isKindOfClass:[NSView class]]) {
            self.tipImageView.title = self.tipTitle;
            self.tipImageView.offsetX = self.offsetX;
            [windowView addSubview:self.tipImageView];
            [self.tipImageView mas_makeConstraints:^(MASConstraintMaker *make) {
                make.bottom.equalTo(self.mas_top).offset(-6);
                make.height.mas_equalTo(28);
                make.centerX.equalTo(self).offset(self.offsetX);
            }];
        }
    }
}

- (void)removeTip {
    if (self.tipImageView && self.tipImageView.superview) {
        [self.tipImageView removeAllSubView];
        [self.tipImageView removeAllAutoLayout];
        [self.tipImageView removeFromSuperview];
        self.tipImageView = nil;
    }
}

- (void)updateUIWithStatus {
    NSString *key = [NSString stringWithFormat:@"%ld",(long)_currentStatus];
    NSColor *color = self.colorDic[key];
    if (color && [color isKindOfClass:[NSColor class]]) {
        [self setBackgroundColor:color];
    }
    
    NSImage *image = self.imageDic[key];
    if (image && [image isKindOfClass:[NSImage class]]) {
        [self setImage:image];
    }
    
    if (self.changeStatus) {
        self.changeStatus(_currentStatus);
    }
}

- (void)mouseEntered:(NSEvent *)event {
    if (_currentStatus == TrackButtonStatusDisabled) {
        return;
    }
    
    _currentStatus = TrackButtonStatusHover;
    [self updateUIWithStatus];
    
    [self showTip];
}

- (void)mouseExited:(NSEvent *)event {
    if (_currentStatus == TrackButtonStatusDisabled) {
        return;
    }
    
    _currentStatus = TrackButtonStatusDefault;
    [self updateUIWithStatus];
    
    [self removeTip];
}

- (void)mouseDown:(NSEvent *)event {
    if (_currentStatus == TrackButtonStatusDisabled) {
        return;
    }
    
    //dowm
    _currentStatus = TrackButtonStatusActive;
    [self updateUIWithStatus];
    
    [super mouseDown:event];
    
    //up
    _currentStatus = TrackButtonStatusHover;
    [self updateUIWithStatus];
}

- (void)otherMouseUp:(NSEvent *)event {
    [super otherMouseUp:event];
    NSLog(@"asdf");
}

- (void)moveUpAndModifySelection:(id)sender {
    [super moveUpAndModifySelection:sender];
    NSLog(@"asdf");
}

- (void)scrollWheel:(NSEvent *)event {
    if (_currentStatus == TrackButtonStatusDisabled) {
        return;
    }
    
    [super scrollWheel:event];
    _currentStatus = TrackButtonStatusDefault;
    [self updateUIWithStatus];
}

#pragma mark - getter

- (NSMutableDictionary *)colorDic {
    if (!_colorDic) {
        _colorDic = [[NSMutableDictionary alloc] init];
    }
    return _colorDic;
}

- (NSMutableDictionary *)imageDic {
    if (!_imageDic) {
        _imageDic = [[NSMutableDictionary alloc] init];
    }
    return _imageDic;
}

- (NSMutableDictionary *)imageInfoDic {
    if (!_imageInfoDic) {
        _imageInfoDic = [[NSMutableDictionary alloc] init];
    }
    return _imageInfoDic;
}

- (TrackTipView *)tipImageView {
    if (!_tipImageView) {
        _tipImageView = [[TrackTipView alloc] init];
    }
    return _tipImageView;
}

- (void)dealloc {
    [self removeTip];
}


@end
