//
//  VoiceRoomMicCell.m
//  veRTC_Demo
//
//  Created by  on 2021/5/21.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import "VoiceRoomMicCell.h"
#import "VoiceRoomMicUserView.h"

@interface VoiceRoomMicCell ()

@property (nonatomic, strong) VoiceRoomMicUserView *micUserView;

@property (nonatomic, strong) UIView *micLineView;

@end

@implementation VoiceRoomMicCell

- (instancetype)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier {
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {
        self.backgroundColor = [UIColor clearColor];
        self.contentView.backgroundColor = [UIColor clearColor];
        
        [self.contentView addSubview:self.micUserView];
        [self.micUserView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.top.equalTo(self.contentView);
            make.left.equalTo(self.contentView).offset(20);
            make.right.equalTo(self.contentView).offset(-20);
            make.height.mas_equalTo(100);
            make.bottom.equalTo(self.contentView).offset(-30);
        }];
        
        [self.contentView addSubview:self.micLineView];
        [self.micLineView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.height.mas_equalTo(XH_1PX_WIDTH);
            make.left.equalTo(self.contentView).offset(20);
            make.right.equalTo(self.contentView).offset(-20);
            make.bottom.equalTo(self.contentView).offset(-1);
        }];
    }
    return self;
}

- (void)setDataLists:(NSArray *)dataLists {
    _dataLists = dataLists;
    
    self.micUserView.dataLists = dataLists;
    NSInteger row = (dataLists.count / 3);
    NSInteger rowNumber = ((dataLists.count % 3) == 0) ? row : row + 1;
    [self.micUserView mas_updateConstraints:^(MASConstraintMaker *make) {
        make.height.mas_equalTo(100 * rowNumber);
    }];
}

#pragma mark - getter

- (UIView *)micLineView {
    if (!_micLineView) {
        _micLineView = [[UIView alloc] init];
        _micLineView.backgroundColor = [UIColor colorFromRGBHexString:@"#FFFFFF" andAlpha:255 * 0.1];
    }
    return _micLineView;
}

- (VoiceRoomMicUserView *)micUserView {
    if (!_micUserView) {
        _micUserView = [[VoiceRoomMicUserView alloc] init];
        _micUserView.backgroundColor = [UIColor clearColor];
    }
    return _micUserView;
}

@end
