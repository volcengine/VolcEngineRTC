//
//  CaptureSourceCollectionItem.m
//  TXLiteAVMacDemo
//
//  Created by  on 2021/3/4.
//

#import "CaptureSourceCollectionItem.h"

@interface CaptureSourceCollectionItem ()

@property (nonatomic, strong) NSView *bgView;
@property (nonatomic, strong) NSImageView *iconImageView;
@property (nonatomic, strong) NSLabel *titleLabel;
@property (nonatomic, strong) TrackButton *maskButton;

@end

@implementation CaptureSourceCollectionItem

- (void)viewDidLoad {
    [super viewDidLoad];
    [self.view setBackgroundColor:[NSColor clearColor]];
    [self.view addSubview:self.bgView];
    [self.bgView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(168, 98));
        make.centerX.top.equalTo(self.view);
    }];
    
    [self.view addSubview:self.iconImageView];
    [self.iconImageView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(160, 90));
        make.center.equalTo(self.bgView);
    }];
    
    [self.view addSubview:self.titleLabel];
    [self.titleLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerX.equalTo(self.view);
        make.top.equalTo(self.iconImageView.mas_bottom).offset(8);
    }];
    
    [self.view addSubview:self.maskButton];
    [self.maskButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(self.iconImageView);
    }];
    
    __weak __typeof(self) wself = self;
    self.maskButton.changeStatus = ^(TrackButtonStatus status) {
        if (status == TrackButtonStatusHover) {
            [wself.maskButton setTitleColor:@"#FFFFFF" title:@"点击开始共享"];
        } else {
            [wself.maskButton setTitleColor:@"#FFFFFF" title:@""];
        }
    };
}

- (void)setSource:(MeetingScreenShareModel *)source {
    if (_source == source) return;
    _source = source;
    
    dispatch_async(dispatch_get_global_queue(0, 0), ^{
        NSImage *image = [[MeetingRTCManager shareMeetingRTCManager]
                          getScreenCaptureSourceThumbnail:source.sourceType
                          sourceId:source.sourceId
                          maxWidth:160 * 2
                          maxHeight:90 * 2];
        dispatch_async(dispatch_get_main_queue(), ^{
            self.iconImageView.image = image;
            self.titleLabel.text = [self substringToIndex:11 string:source.sourceName];
            if (source.isScreen) {
                self.titleLabel.textColor = [NSColor colorFromHexString:@"#4080FF"];
            } else {
                self.titleLabel.textColor = [NSColor colorFromHexString:@"#FFFFFF"];
            }
        });
    });
}

- (NSString *)substringToIndex:(NSInteger)num string:(NSString *)string {
    NSString *tmp = string;
    if (tmp.length > num) {
        tmp = [tmp substringToIndex:num];
        tmp = [tmp stringByAppendingString:@"..."];
    }
    return tmp;
}

#pragma mark - Private Action

- (void)maskButtonClick {
    //Start shareScreen socket api
    [MeetingControlCompoments startShareScreen];
    //show
    AppDelegate *appDelegate = (AppDelegate *)[NSApplication sharedApplication].delegate;
    WindowManager *manager = (WindowManager *)(appDelegate.windowManager);
    [manager showScreenBottomWindowController:self.loginModel
                                    roomModel:self.roomModel];
    
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.5 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        if (self.source.isScreen) {
            [[MeetingRTCManager shareMeetingRTCManager] startScreenCaptureByDisplayId:self.source.sourceId];
        } else {
            [[MeetingRTCManager shareMeetingRTCManager] startScreenCaptureByWindowId:self.source.sourceId];
        }
    });
    
    if ([self.delegate respondsToSelector:@selector(captureSourceCollectionItem:didSelectItem:)]) {
        [self.delegate captureSourceCollectionItem:self didSelectItem:self.source];
    }
}

#pragma mark - getter

- (NSView *)bgView {
    if (!_bgView) {
        _bgView = [[NSView alloc] init];
        [_bgView setBackgroundColor:[NSColor whiteColor]];
    }
    return _bgView;
}

- (NSImageView *)iconImageView {
    if (!_iconImageView) {
        _iconImageView = [[NSImageView alloc] init];
    }
    return _iconImageView;
}

- (NSLabel *)titleLabel {
    if (!_titleLabel) {
        _titleLabel = [[NSLabel alloc] init];
        _titleLabel.font = [NSFont systemFontOfSize:14 weight:NSFontWeightRegular];
        _titleLabel.oneLine = YES;
    }
    return _titleLabel;
}

- (TrackButton *)maskButton {
    if (!_maskButton) {
        _maskButton = [[TrackButton alloc] init];
        _maskButton.font = [NSFont systemFontOfSize:14 weight:NSFontWeightRegular];
        [_maskButton setTarget:self];
        [_maskButton setAction:@selector(maskButtonClick)];
        
        [_maskButton bingBackColorWithStatus:TrackButtonStatusDefault color:[NSColor clearColor]];
        [_maskButton bingBackColorWithStatus:TrackButtonStatusHover color:[NSColor colorFromRGBHexString:@"#000000" andAlpha:255 * 0.5]];
    }
    return _maskButton;
}

@end
