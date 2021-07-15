//
//  ScreenShareViewController.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/10.
//

#import "ScreenShareViewController.h"
#import "ScreenSourcesView.h"
#import "MeetingScreenShareComponents.h"

@interface ScreenShareViewController ()

@property (nonatomic, strong) NSButton *maskView;
@property (nonatomic, strong) ScreenSourcesView *screenSourcesView;
@property (nonatomic, strong) MeetingScreenShareComponents *screenShareComponents;

@end

@implementation ScreenShareViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    [self.view setBackgroundColor:[NSColor clearColor]];
    
    [self.view addSubview:self.maskView];
    [self.maskView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(self.view);
    }];
    
    [self.view addSubview:self.screenSourcesView];
    [self.screenSourcesView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(800, 504));
        make.centerX.equalTo(self.view);
        make.bottom.mas_equalTo(-76);
    }];
    
    dispatch_async(dispatch_get_main_queue(), ^{
        NSArray *lists = [self.screenShareComponents screenCaptureSourcesWithThumbnailSize:CGSizeMake(160, 90)];
        [self.screenSourcesView updateThumbnailWithDataLists:lists];
    });
    
    __weak __typeof(self) wself = self;
    self.screenSourcesView.clickCancelBLock = ^{
        if (wself.clickCancelBlock) {
            wself.clickCancelBlock();
        }
    };
}

- (void)setLoginModel:(LoginModel *)loginModel {
    _loginModel = loginModel;
    
    self.screenSourcesView.loginModel = loginModel;
}

- (void)setRoomModel:(MeetingControlRoomModel *)roomModel {
    _roomModel = roomModel;
    self.screenSourcesView.roomModel = roomModel;
}

- (void)maskViewButtonAction {
    if (self.clickCancelBlock) {
        self.clickCancelBlock();
    }
}

#pragma mark - getter

- (ScreenSourcesView *)screenSourcesView {
    if (!_screenSourcesView) {
        _screenSourcesView = [[ScreenSourcesView alloc] init];
    }
    return _screenSourcesView;
}


- (MeetingScreenShareComponents *)screenShareComponents {
    if (!_screenShareComponents) {
        _screenShareComponents = [[MeetingScreenShareComponents alloc] init];
    }
    return _screenShareComponents;
}

- (NSButton *)maskView {
    if (!_maskView) {
        _maskView = [[NSButton alloc] init];
        [_maskView setBackgroundColorWithHexString:@"#000000" andAlpha:0.5 * 255];
        
        [_maskView setTarget:self];
        [_maskView setAction:@selector(maskViewButtonAction)];
        
    }
    return _maskView;
}

- (void)dealloc {
    NSLog(@"[dealloc]%@",self.className);
}

@end
