//
//  FeedbackViewController.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/12.
//

#import "FeedbackViewController.h"
#import "FeedbackView.h"
#import "FeedbackInfoView.h"

@interface FeedbackViewController () <FeedbackViewDeleagte>

@property (nonatomic, strong) FeedbackView *feedbackView;
@property (nonatomic, strong) FeedbackInfoView *feedbackInfoView;

@end

@implementation FeedbackViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self.view setBackgroundColorWithHexString:@"000000" andAlpha:0.5 * 255];
    
    [self.view addSubview:self.feedbackView];
    [self.feedbackView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(320, 126));
        make.centerX.equalTo(self.view);
        make.centerY.equalTo(self.view).offset(-80);
    }];
    
    [self.view addSubview:self.feedbackInfoView];
    [self.feedbackInfoView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(480, 306));
        make.center.equalTo(self.feedbackView);
    }];
}


#pragma mark - FeedbackViewDeleagte

- (void)feedbackView:(FeedbackView *)feedbackView clickButton:(NSInteger)type {
    if (type == 1) {
        //good
        [self cancel];
    } else if (type == 2) {
        //bad
        self.feedbackInfoView.hidden = NO;
        __weak __typeof(self) wself = self;
        self.feedbackInfoView.clickInfoCancelBlock = ^{
            [wself cancel];
        };
        self.feedbackInfoView.clickInfoSubmitBlock = ^{
            //Submit to SDK
            
        };
    } else {
        //cancel
        [self cancel];
    }
}

#pragma mark - Private Action

- (void)cancel {
    if (self.clickCancelBlock) {
        self.clickCancelBlock();
    }
}

#pragma mark - getter

- (FeedbackView *)feedbackView {
    if (!_feedbackView) {
        _feedbackView = [[FeedbackView alloc] init];
        [_feedbackView setBackgroundColor:[NSColor whiteColor]];
        _feedbackView.deleagte = self;
    }
    return _feedbackView;
}

- (FeedbackInfoView *)feedbackInfoView {
    if (!_feedbackInfoView) {
        _feedbackInfoView = [[FeedbackInfoView alloc] init];
        [_feedbackInfoView setBackgroundColor:[NSColor whiteColor]];
        _feedbackInfoView.hidden = YES;
    }
    return _feedbackInfoView;
}

@end
