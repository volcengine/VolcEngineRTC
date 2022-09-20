#import "WindowController.h"
#import "LoginViewController.h"
#import "RoomViewController.h"
#import "Masonry.h"

@interface WindowController ()

@property (nonatomic, strong) RoomViewController *roomViewController;
@property (nonatomic, strong) LoginViewController *loginViewController;

@end

@implementation WindowController

- (void)windowDidLoad {
    [super windowDidLoad];
    
    self.window.styleMask = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable;
    
    LoginViewController *loginViewController = [[LoginViewController alloc]
                                           initWithNibName:@"LoginViewController"
                                                bundle:nil];
    [self.window.contentViewController addChildViewController:loginViewController];
    [self.window.contentView addSubview:loginViewController.view];
    [loginViewController.view mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(self.window.contentView);
    }];
    __weak __typeof(self) wself = self;
    loginViewController.joinRoomBlock = ^(NSString * _Nonnull roomID,
                                          NSString * _Nonnull userID) {
        [wself showRoom:roomID userID:userID];
    };
    _loginViewController = loginViewController;
}

- (void)showRoom:(NSString *)roomID userID:(NSString *)userID {
    _loginViewController.view.hidden = YES;
    RoomViewController *roomViewController = [[RoomViewController alloc]
                                              initWithNibName:@"RoomViewController"
                                              bundle:nil
                                              roomID:roomID
                                              uid:userID];
    [self.window.contentViewController addChildViewController:roomViewController];
    [self.window.contentView addSubview:roomViewController.view];
    [roomViewController.view mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(self.window.contentView);
    }];
    __weak __typeof(self) wself = self;
    roomViewController.clickBackBlock = ^{
        [wself closeRoom];
    };
    _roomViewController = roomViewController;
}

- (void)closeRoom {
    _loginViewController.view.hidden = NO;
    if (_roomViewController) {
        [_roomViewController.view removeFromSuperview];
        [_roomViewController removeFromParentViewController];
        _roomViewController = nil;
    }
}

- (NSSize)windowWillResize:(NSWindow *)sender toSize:(NSSize)frameSize {
    if((frameSize.width / frameSize.height) != 16.0/9.0) {
        frameSize.height = 9.0/16.0 *frameSize.width;
    }

    return frameSize;
}

@end
