//
//  FeedbackManager.m
//  quickstart

#import "FeedbackManager.h"
#import "FeedbackInputView.h"
#import "MeetingRTCManager.h"

@interface FeedbackManager ()

@property (nonatomic, strong) UIView *maskView;
@property (nonatomic, strong) UIView *feedbackContainerView;
@property (nonatomic, strong) UIView *lineView;
@property (nonatomic, strong) UILabel *feedbackTitleLabel;
@property (nonatomic, strong) UIButton *feedbackCloseBtn;
@property (nonatomic, strong) UIButton *feedbackGoodBtn;
@property (nonatomic, strong) UIButton *feedbackBadBtn;

@property (nonatomic, strong) UIView *collectContainerView;
@property (nonatomic, strong) UILabel *collectTitleLabel;
@property (nonatomic, strong) UIButton *collectCloseBtn;
@property (nonatomic, strong) UIButton *collectOpinionsBtn1;
@property (nonatomic, strong) UIButton *collectOpinionsBtn2;
@property (nonatomic, strong) UIButton *collectOpinionsBtn3;
@property (nonatomic, strong) UIButton *collectOpinionsBtn4;
@property (nonatomic, strong) FeedbackInputView *collectOpinionsTextField;
@property (nonatomic, strong) UIButton *collectConfirmBtn;

@property (nonatomic, assign) BOOL isSelectBtn1;
@property (nonatomic, assign) BOOL isSelectBtn2;
@property (nonatomic, assign) BOOL isSelectBtn3;
@property (nonatomic, assign) BOOL isSelectBtn4;

@end


@implementation FeedbackManager

- (instancetype)init {
    self = [super init];
    if (self) {
        [self initFeedBackUIComponents];
        [self dataRestoration];
        
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector (keyboardDidShowNotification:) name:UIKeyboardWillShowNotification object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyboardDidHideNotification:) name:UIKeyboardWillHideNotification object:nil];
    }
    return self;
}

- (void)keyboardDidShowNotification:(NSNotification *)notification {
    UIView *keyView = [UIApplication sharedApplication].keyWindow.rootViewController.view;
    [UIView animateWithDuration:0.25 animations:^{
        [self.collectContainerView mas_updateConstraints:^(MASConstraintMaker *make) {
            make.centerY.equalTo(keyView).offset(-100);
        }];
        [self.collectContainerView.superview layoutIfNeeded];
    }];
}

- (void)keyboardDidHideNotification:(NSNotification *)notification {
    UIView *keyView = [UIApplication sharedApplication].keyWindow.rootViewController.view;
    [UIView animateWithDuration:0.2 animations:^{
        [self.collectContainerView mas_updateConstraints:^(MASConstraintMaker *make) {
            make.centerY.equalTo(keyView).offset(0);
        }];
        [self.collectContainerView.superview layoutIfNeeded];
    }];
}

#pragma mark - Publish Action

- (void)show {
    self.maskView.hidden = NO;
}

- (void)textFieldResignFirstResponder {
    [self.collectOpinionsTextField resignFirstResponder];
}

#pragma mark - Click Action

- (void)onClickBtn:(id)sender {
    if (sender == self.feedbackGoodBtn) {
        [self dismiss];
    } else if (sender == self.feedbackBadBtn) {
        self.collectContainerView.hidden = NO;
    } else if (sender == self.feedbackCloseBtn || sender == self.collectCloseBtn) {
        [self dismiss];
    } else if (sender == self.collectOpinionsBtn1) {
        _isSelectBtn1 = !_isSelectBtn1;
        [self updateCollectOpinionsBtn:self.collectOpinionsBtn1 isSelect:_isSelectBtn1];
    } else if (sender == self.collectOpinionsBtn2) {
        _isSelectBtn2 = !_isSelectBtn2;
        [self updateCollectOpinionsBtn:self.collectOpinionsBtn2 isSelect:_isSelectBtn2];
        
    } else if (sender == self.collectOpinionsBtn3) {
        _isSelectBtn3 = !_isSelectBtn3;
        [self updateCollectOpinionsBtn:self.collectOpinionsBtn3 isSelect:_isSelectBtn3];
        
    } else if (sender == self.collectOpinionsBtn4) {
        _isSelectBtn4 = !_isSelectBtn4;
        [self updateCollectOpinionsBtn:self.collectOpinionsBtn4 isSelect:_isSelectBtn4];
        
    } else if (sender == self.collectConfirmBtn) {
        [self loadDataWithFeedBack];
        [self dismiss];
    } else {
        
    }
}

- (void)dismiss {
    [self textFieldResignFirstResponder];
    [self.maskView removeAllSubviews];
    [self.maskView removeFromSuperview];
    [self.collectContainerView removeAllSubviews];
    [self.collectContainerView removeFromSuperview];
    self.maskView = nil;
    self.collectContainerView = nil;
    if (self.clickCancelBlock) {
        self.clickCancelBlock();
    }
}

#pragma mark - Network

- (void)loadDataWithFeedBack {
    NSInteger type = PROBLEM_NONE;
    if (_isSelectBtn1) {
        type = type | PROBLEM_VIDEO_LAGGING;
    }
    if (_isSelectBtn2) {
        type = type | PROBLEM_NONE;
    }
    if (_isSelectBtn3) {
        type = type | PROBLEM_AUDIO_LAGGING;
    }
    if (_isSelectBtn4) {
        type = type | PROBLEM_OTHER_MSG;
    }
//    [ByteRtcEngineKit feedbackGrade:1 type:type desc:self.collectOpinionsTextField.text];
}

#pragma mark - Private Action

- (void)updateCollectOpinionsBtn:(UIButton *)button isSelect:(BOOL)isSelect {
    if (isSelect) {
        button.backgroundColor = [UIColor colorFromHexString:@"#4080FF"];
    } else {
        button.backgroundColor = [UIColor colorFromRGBHexString:@"#FFFFFF" andAlpha:0.1 * 255];
    }
}

- (void)dataRestoration {
    _isSelectBtn1 = NO;
    _isSelectBtn2 = NO;
    _isSelectBtn3 = NO;
    _isSelectBtn4 = NO;
    
    [self updateCollectOpinionsBtn:self.collectOpinionsBtn1 isSelect:_isSelectBtn1];
    [self updateCollectOpinionsBtn:self.collectOpinionsBtn2 isSelect:_isSelectBtn2];
    [self updateCollectOpinionsBtn:self.collectOpinionsBtn3 isSelect:_isSelectBtn3];
    [self updateCollectOpinionsBtn:self.collectOpinionsBtn4 isSelect:_isSelectBtn4];
    
    self.collectOpinionsTextField.text = @"";
}

- (void)maskAction {
    [self.collectOpinionsTextField resignFirstResponder];
}

- (void)initFeedBackUIComponents {
    UIView *keyView = [UIApplication sharedApplication].keyWindow.rootViewController.view;
    
    self.maskView = [[UIView alloc] init];
    self.maskView.backgroundColor = [UIColor colorFromRGBHexString:@"000000" andAlpha:0.5 * 255];
    [keyView addSubview:self.maskView];
    [self.maskView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(keyView);
    }];
    self.maskView.userInteractionEnabled = YES;
    UITapGestureRecognizer *tap = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(maskAction)];
    [self.maskView addGestureRecognizer:tap];
    
    self.feedbackContainerView = [[UIView alloc] init];
    [self.maskView addSubview:self.feedbackContainerView];
    [self.feedbackContainerView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.center.equalTo(keyView);
        make.width.mas_equalTo(590/2);
        make.height.mas_equalTo(372/2);
    }];
    [self.feedbackContainerView setBackgroundColor:[UIColor colorFromHexString:@"#272E3B"]];
    self.feedbackContainerView.layer.cornerRadius = 4.f;
    self.feedbackContainerView.layer.masksToBounds = YES;
    self.maskView.hidden = YES;
    
    self.feedbackTitleLabel = [[UILabel alloc] init];
    [self.feedbackContainerView addSubview:self.feedbackTitleLabel];
    [self.feedbackTitleLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerX.equalTo(self.feedbackContainerView);
        make.top.equalTo(self.feedbackContainerView).mas_offset(30);
    }];
    self.feedbackTitleLabel.adjustsFontSizeToFitWidth = YES;
    self.feedbackTitleLabel.text = @"本次通话体验如何？";
    self.feedbackTitleLabel.textColor = [UIColor whiteColor];

    [self.feedbackContainerView addSubview:self.lineView];
    [self.lineView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerX.equalTo(self.feedbackContainerView);
        make.bottom.mas_equalTo(-124/2);
        make.width.mas_equalTo(XH_1PX_WIDTH);
        make.height.mas_equalTo(32);
    }];
    
    self.feedbackGoodBtn = [[UIButton alloc] init];
    [self.feedbackContainerView addSubview:self.feedbackGoodBtn];
    [self.feedbackGoodBtn mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerY.equalTo(self.lineView);
        make.right.equalTo(self.lineView.mas_left).mas_offset(-55);
        make.height.width.mas_equalTo(40);
    }];
    [self.feedbackGoodBtn setImage:[UIImage imageNamed:@"meeting_feed_good"] forState:UIControlStateNormal];
    [self.feedbackGoodBtn addTarget:self action:@selector(onClickBtn:) forControlEvents:UIControlEventTouchUpInside];
    UILabel *goodLabel = [[UILabel alloc] init];
    goodLabel.text = @"好";
    goodLabel.textColor = [UIColor colorFromHexString:@"#86909C"];
    goodLabel.font = [UIFont systemFontOfSize:12];
    [self.feedbackContainerView addSubview:goodLabel];
    [goodLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerX.equalTo(self.feedbackGoodBtn);
        make.top.equalTo(self.feedbackGoodBtn.mas_bottom).offset(12);
    }];
    
    
    self.feedbackBadBtn = [[UIButton alloc] init];
    [self.feedbackContainerView addSubview:self.feedbackBadBtn];
    [self.feedbackBadBtn mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerY.equalTo(self.lineView);
        make.left.equalTo(self.lineView.mas_right).mas_offset(55);
        make.height.width.mas_equalTo(40);
    }];
    [self.feedbackBadBtn setImage:[UIImage imageNamed:@"meeting_feed_bad"] forState:UIControlStateNormal];
    [self.feedbackBadBtn addTarget:self action:@selector(onClickBtn:) forControlEvents:UIControlEventTouchUpInside];
    UILabel *badLabel = [[UILabel alloc] init];
    badLabel.text = @"差";
    badLabel.textColor = [UIColor colorFromHexString:@"#86909C"];
    badLabel.font = [UIFont systemFontOfSize:12];
    [self.feedbackContainerView addSubview:badLabel];
    [badLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerX.equalTo(self.feedbackBadBtn);
        make.top.equalTo(self.feedbackBadBtn.mas_bottom).offset(12);
    }];
    
    
    self.feedbackCloseBtn = [[UIButton alloc] init];
    [self.maskView addSubview:self.feedbackCloseBtn];
    [self.feedbackCloseBtn mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self.feedbackContainerView.mas_bottom).mas_offset(40);
        make.centerX.equalTo(self.feedbackContainerView);
        make.height.width.mas_equalTo(30);
    }];
    [self.feedbackCloseBtn setImage:[UIImage imageNamed:@"meeting_feed_cancel"] forState:UIControlStateNormal];
    [self.feedbackCloseBtn addTarget:self action:@selector(onClickBtn:) forControlEvents:UIControlEventTouchUpInside];

    //collect opinions view
    self.collectContainerView = [[UIView alloc] init];
    [keyView addSubview:self.collectContainerView];
    [self.collectContainerView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerX.equalTo(keyView);
        make.centerY.equalTo(keyView).offset(0);
        make.width.mas_equalTo(590/2);
        make.height.mas_equalTo(704/2);
    }];
    [self.collectContainerView setBackgroundColor:[UIColor colorFromHexString:@"#272E3B"]];
    self.collectContainerView.layer.cornerRadius = 4;
    self.collectContainerView.layer.masksToBounds = YES;
    self.collectContainerView.hidden = YES;

    self.collectTitleLabel = [[UILabel alloc] init];
    [self.collectContainerView addSubview:self.collectTitleLabel];
    [self.collectTitleLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.equalTo(self.collectContainerView).mas_offset(20);
        make.top.equalTo(self.collectContainerView).mas_offset(20);
    }];
    self.collectTitleLabel.text = @"具体问题反馈";
    self.collectTitleLabel.textColor = [UIColor whiteColor];
    self.collectTitleLabel.font = [UIFont systemFontOfSize:32/2];


    self.collectOpinionsBtn1 = [[UIButton alloc] init];
    [self.collectContainerView addSubview:self.collectOpinionsBtn1];
    [self.collectOpinionsBtn1 mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.equalTo(self.collectContainerView).mas_offset(20.f);
        make.top.equalTo(self.collectContainerView).mas_offset(55.f);
        make.width.mas_equalTo(122.5f);
        make.height.mas_equalTo(44.f);
    }];
    [self updateButtonStyle:self.collectOpinionsBtn1];
    [self.collectOpinionsBtn1 setTitle:@"视频卡顿" forState:UIControlStateNormal];
    
    self.collectOpinionsBtn2 = [[UIButton alloc] init];
    [self.collectContainerView addSubview:self.collectOpinionsBtn2];
    [self.collectOpinionsBtn2 mas_makeConstraints:^(MASConstraintMaker *make) {
        make.right.equalTo(self.collectContainerView).mas_offset(-20.f);
        make.top.equalTo(self.collectContainerView).mas_offset(55.f);
        make.width.mas_equalTo(122.5f);
        make.height.mas_equalTo(44.f);
    }];
    [self.collectOpinionsBtn2 setTitle:@"共享内容故障" forState:UIControlStateNormal];
    [self updateButtonStyle:self.collectOpinionsBtn2];

    self.collectOpinionsBtn3 = [[UIButton alloc] init];
    [self.collectContainerView addSubview:self.collectOpinionsBtn3];
    [self.collectOpinionsBtn3 mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.equalTo(self.collectContainerView).mas_offset(20.f);
        make.top.equalTo(self.collectOpinionsBtn2.mas_bottom).mas_offset(10.f);
        make.width.mas_equalTo(122.5f);
        make.height.mas_equalTo(44.f);
    }];
    [self.collectOpinionsBtn3 setTitle:@"音频卡顿" forState:UIControlStateNormal];
    [self updateButtonStyle:self.collectOpinionsBtn3];

    self.collectOpinionsBtn4 = [[UIButton alloc] init];
    [self.collectContainerView addSubview:self.collectOpinionsBtn4];
    [self.collectOpinionsBtn4 mas_makeConstraints:^(MASConstraintMaker *make) {
        make.right.equalTo(self.collectContainerView).mas_offset(-20.f);
        make.top.equalTo(self.collectOpinionsBtn2.mas_bottom).mas_offset(10.f);
        make.width.mas_equalTo(122.5f);
        make.height.mas_equalTo(44.f);
    }];
    [self.collectOpinionsBtn4 setTitle:@"其他问题" forState:UIControlStateNormal];
    [self updateButtonStyle:self.collectOpinionsBtn4];

    UILabel *subTitleLabel = [[UILabel alloc] init];
    subTitleLabel.text = @"其他反馈问题";
    subTitleLabel.textColor = [UIColor whiteColor];
    subTitleLabel.font = [UIFont systemFontOfSize:32/2];
    [self.collectContainerView addSubview:subTitleLabel];
    [subTitleLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.equalTo(self.collectContainerView).mas_offset(20.f);
        make.top.equalTo(self.collectOpinionsBtn4.mas_bottom).mas_offset(20);
    }];
    
    self.collectOpinionsTextField = [[FeedbackInputView alloc] init];
    [self.collectContainerView addSubview:self.collectOpinionsTextField];
    [self.collectOpinionsTextField mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerX.equalTo(self.collectContainerView);
        make.bottom.equalTo(self.collectContainerView).mas_offset(-128/2);
        make.width.mas_equalTo(510/2);
        make.height.mas_equalTo(160/2);
    }];
    self.collectOpinionsTextField.backgroundColor = [UIColor colorFromHexString:@"#1D2129"];
    self.collectOpinionsTextField.layer.cornerRadius = 4.f;
    self.collectOpinionsTextField.layer.masksToBounds = YES;
    self.collectOpinionsTextField.font = [UIFont systemFontOfSize:32/2];
    self.collectOpinionsTextField.textColor = [UIColor whiteColor];

    
    self.collectCloseBtn = [[UIButton alloc] init];
    [self.collectContainerView addSubview:self.collectCloseBtn];
    [self.collectCloseBtn mas_makeConstraints:^(MASConstraintMaker *make) {
        make.bottom.left.equalTo(self.collectContainerView);
        make.width.equalTo(self.collectContainerView.mas_width).multipliedBy(0.5);
        make.height.mas_equalTo(87/2);
    }];
    [self.collectCloseBtn setTitle:@"取消" forState:UIControlStateNormal];
    [self.collectCloseBtn addTarget:self action:@selector(onClickBtn:) forControlEvents:UIControlEventTouchUpInside];
    self.collectCloseBtn.titleLabel.font = [UIFont systemFontOfSize:32/2];
    [self.collectCloseBtn setTitleColor:[UIColor colorFromHexString:@"#C9CDD4"] forState:UIControlStateNormal];

    self.collectConfirmBtn = [[UIButton alloc] init];
    [self.collectContainerView addSubview:self.collectConfirmBtn];
    [self.collectConfirmBtn mas_makeConstraints:^(MASConstraintMaker *make) {
        make.bottom.right.equalTo(self.collectContainerView);
        make.width.equalTo(self.collectContainerView).multipliedBy(0.5);
        make.height.mas_equalTo(87/2);
    }];
    [self.collectConfirmBtn setTitle:@"提交" forState:UIControlStateNormal];
    [self.collectConfirmBtn addTarget:self action:@selector(onClickBtn:) forControlEvents:UIControlEventTouchUpInside];
    self.collectConfirmBtn.titleLabel.font = [UIFont systemFontOfSize:32/2];
    [self.collectConfirmBtn setTitleColor:[UIColor colorFromHexString:@"#4080FF"] forState:UIControlStateNormal];
    
    UIView *line1View = [[UIView alloc] init];
    line1View.backgroundColor = [UIColor colorFromHexString:@"#101319"];
    [self.collectContainerView addSubview:line1View];
    [line1View mas_makeConstraints:^(MASConstraintMaker *make) {
        make.bottom.equalTo(self.collectConfirmBtn.mas_top);
        make.left.right.equalTo(self.collectContainerView);
        make.height.mas_equalTo(XH_1PX_WIDTH);
    }];
    
    UIView *line2View = [[UIView alloc] init];
    line2View.backgroundColor = [UIColor colorFromHexString:@"#101319"];
    [self.collectContainerView addSubview:line2View];
    [line2View mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerX.equalTo(self.collectContainerView);
        make.top.bottom.equalTo(self.collectConfirmBtn);
        make.width.mas_equalTo(XH_1PX_WIDTH);
    }];
}

- (void)updateButtonStyle:(UIButton *)button {
    button.layer.cornerRadius = 4.f;
    button.layer.masksToBounds = YES;
    [button.titleLabel setFont:[UIFont systemFontOfSize:32/2]];
    [button setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    [button addTarget:self action:@selector(onClickBtn:) forControlEvents:UIControlEventTouchUpInside];
}

#pragma mark - getter

- (UIView *)lineView {
    if (!_lineView) {
        _lineView = [[UIView alloc] init];
        _lineView.backgroundColor = [UIColor colorFromHexString:@"#86909C"];
    }
    return _lineView;
}

- (void)dealloc {
    NSLog(@"dealloc %@",NSStringFromClass([self class]));
}

@end
