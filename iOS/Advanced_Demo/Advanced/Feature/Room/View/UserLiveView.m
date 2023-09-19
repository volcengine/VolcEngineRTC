//
//  LiveView.m
//  advanced
//

#import "Masonry.h"
#import "UserLiveView.h"

@interface UserLiveView ()
@property (nonatomic, strong) UILabel *label;
@end

@implementation UserLiveView
- (void)dealloc {
    NSLog(@"%@,%s", [NSThread currentThread], __func__);
}

- (instancetype)initWithFrame:(CGRect)frame {
    if (self = [super initWithFrame:frame]) {
        self.uid = @"";

        [self addSubview:self.label];
        [self.label mas_makeConstraints:^(MASConstraintMaker *make) {
          make.left.bottom.right.equalTo(self);
          make.height.mas_equalTo(30);
        }];
    }
    return self;
}

- (void)setUseCustomRender:(BOOL)useCustomRender {
    _useCustomRender = useCustomRender;

    if (useCustomRender) {
        [_liveView removeFromSuperview];

        [self addSubview:self.customRenderView];
        [self.customRenderView mas_makeConstraints:^(MASConstraintMaker *make) {
          make.left.top.right.equalTo(self);
          make.height.equalTo(self).offset(-30);
        }];
    } else {
        [_customRenderView removeFromSuperview];

        [self addSubview:self.liveView];
        [self.liveView mas_makeConstraints:^(MASConstraintMaker *make) {
          make.left.top.right.equalTo(self);
          make.height.equalTo(self).offset(-30);
        }];
    }
}

- (void)setUid:(NSString *)uid {
    _uid = uid;
    if (uid.length > 0) {
        self.label.text = [@"UserID：" stringByAppendingString:uid];
    } else {
        self.label.text = @"";
        [self.liveView removeFromSuperview];
        [self.customRenderView removeFromSuperview];
    }
}

- (UIView *)liveView {
    if (!_liveView) {
        _liveView = [[UIView alloc] init];
    }
    return _liveView;
}

- (CustomVideoRenderView *)customRenderView {
    if (!_customRenderView) {
        _customRenderView = [[CustomVideoRenderView alloc] init];
    }
    return _customRenderView;
}

- (UILabel *)label {
    if (!_label) {
        _label = [[UILabel alloc] init];
        _label.textAlignment = NSTextAlignmentCenter;
    }
    return _label;
}
@end
