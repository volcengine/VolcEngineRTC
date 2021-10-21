//
//  LiveView.m
//  quickstart
//

#import "UserLiveView.h"
#import "Masonry.h"

@interface UserLiveView ()
@property (nonatomic, strong) UILabel *label;
@end

@implementation UserLiveView
- (void)dealloc{
    NSLog(@"%@,%s",[NSThread currentThread],__func__);
}

- (instancetype)initWithFrame:(CGRect)frame{
    if (self = [super initWithFrame:frame]) {
        
        self.uid = @"";
        
        [self addSubview:self.liveView];
        [self.liveView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.top.right.equalTo(self);
            make.height.equalTo(self).offset(-30);
        }];
        
        [self addSubview:self.label];
        [self.label mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.bottom.right.equalTo(self);
            make.height.mas_equalTo(30);
        }];
    }
    return self;
}

- (void)setUid:(NSString *)uid{
    _uid = uid;
    self.label.text = uid;
}

- (UIView *)liveView{
    if(!_liveView){
        _liveView = [[UIView alloc] init];
    }
    return _liveView;
}

- (UILabel *)label{
    if(!_label){
        _label = [[UILabel alloc] init];
        _label.textAlignment = NSTextAlignmentCenter;
    }
    return _label;
}
@end
