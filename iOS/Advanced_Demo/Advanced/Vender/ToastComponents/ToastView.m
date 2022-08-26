//
//  ToastView.m
//  veRTC_Demo
//
//

#import "ToastView.h"
#import "Masonry.h"

#define SCREEN_WIDTH  ([UIScreen mainScreen].bounds.size.width)
#define SCREEN_HEIGHT ([UIScreen mainScreen].bounds.size.height)
#define XH_1PX_WIDTH (1 / [UIScreen mainScreen].scale)

@interface ToastView ()

@property (nonatomic, strong) UIView *bgView;

@end


@implementation ToastView

- (instancetype)initWithMeeage:(NSString *)message {
    self = [super init];
    if (self) {
        CGFloat minScreen = MIN(SCREEN_WIDTH, SCREEN_HEIGHT);
        CGFloat scale = (minScreen / 375);
        self.bgView = [[UIView alloc] init];
        self.bgView.backgroundColor = [UIColor colorWithWhite:0.1 alpha:0.8];
        self.bgView.layer.cornerRadius = 4;
        self.bgView.layer.masksToBounds = YES;
        
        UILabel *titleLabel = [[UILabel alloc] init];
        titleLabel.numberOfLines = 0;
        titleLabel.textColor = [UIColor whiteColor];
        titleLabel.textAlignment = NSTextAlignmentCenter;
        titleLabel.font = [UIFont systemFontOfSize:16.0 * scale weight:UIFontWeightRegular];
        titleLabel.text = message;
        
        [self addSubview:self.bgView];
        [self.bgView addSubview:titleLabel];
        
        [titleLabel mas_makeConstraints:^(MASConstraintMaker *make) {
            make.center.equalTo(self.bgView);
            make.width.mas_lessThanOrEqualTo(SCREEN_WIDTH - 24 * 2);
        }];
        
        [self.bgView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.equalTo(titleLabel).offset(-12);
            make.right.equalTo(titleLabel).offset(12);
            make.top.equalTo(titleLabel).offset(-12);;
            make.bottom.equalTo(titleLabel).offset(12);;
        }];
        
        [self mas_updateConstraints:^(MASConstraintMaker *make) {
            make.size.equalTo(self.bgView);
        }];
    }
    return self;
}

@end
