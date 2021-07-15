//
//  NavBarVersionView.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/11.
//

#import "NavBarVersionView.h"

@interface NavBarVersionView ()

@property (nonatomic, strong) NSLabel *verLabel;

@end


@implementation NavBarVersionView

- (instancetype)init {
    self = [super init];
    if (self) {
        [self addSubview:self.verLabel];
        [self.verLabel mas_makeConstraints:^(MASConstraintMaker *make) {
            make.centerY.equalTo(self);
            make.right.mas_equalTo(self).offset(-24);
        }];
        
        NSString *sdkVer = [[MeetingRTCManager shareMeetingRTCManager] getSdkVersion];
        NSString *appVer = [[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleShortVersionString"];
        self.verLabel.text = [NSString stringWithFormat:@"Demo版本 v%@ / SDK版本 v%@", appVer, sdkVer];
    }
    return self;
}

- (NSLabel *)verLabel {
    if (!_verLabel) {
        _verLabel = [[NSLabel alloc] init];
        _verLabel.textColor = [NSColor colorFromHexString:@"#86909C"];
        _verLabel.font = [NSFont systemFontOfSize:12 weight:NSFontWeightRegular];
    }
    return _verLabel;
}

- (void)dealloc {
    NSLog(@"[dealloc]%@",self.className);
}

@end
