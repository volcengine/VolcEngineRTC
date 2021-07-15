//
//  PhoneLoginWindowController.m
//  veRTC_Demo
//
//  Created by  on 2021/6/7.
//

#import "PhoneLoginWindowController.h"
#import "PhoneLoginViewController.h"

@interface PhoneLoginWindowController ()

@property (nonatomic, strong) PhoneLoginViewController *loginViewController;

@end

@implementation PhoneLoginWindowController

- (void)windowDidLoad {
    [super windowDidLoad];
    
    [self.window.contentViewController addChildViewController:self.loginViewController];
    [self.window.contentView addSubview:self.loginViewController.view];
    [self.loginViewController.view mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(self.window.contentView);
    }];
}

- (void)setLoginBlock:(void (^)(void))loginBlock {
    _loginBlock = loginBlock;
    self.loginViewController.loginBlock = self.loginBlock;
}

#pragma mark - getter

- (PhoneLoginViewController *)loginViewController {
    if (!_loginViewController) {
        _loginViewController = [[PhoneLoginViewController alloc] init];
    }
    return _loginViewController;
}

@end
