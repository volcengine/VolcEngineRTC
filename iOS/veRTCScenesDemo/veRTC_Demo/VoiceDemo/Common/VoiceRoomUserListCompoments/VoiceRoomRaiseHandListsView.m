//
//  VoiceRoomRaiseHandListsView.m
//  veRTC_Demo
//
//  Created by  on 2021/5/19.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import "VoiceRoomRaiseHandListsView.h"

@interface VoiceRoomRaiseHandListsView ()<UITableViewDelegate, UITableViewDataSource, VoiceRoomUserListtCellDelegate>

@property (nonatomic, strong) UITableView *roomTableView;

@end

@implementation VoiceRoomRaiseHandListsView

- (instancetype)init {
    self = [super init];
    if (self) {
        [self addSubview:self.roomTableView];
        [self.roomTableView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.edges.equalTo(self);
        }];
    }
    return self;
}

#pragma mark - Publish Action

- (void)setDataLists:(NSArray *)dataLists {
    _dataLists = dataLists;
    
    [self.roomTableView reloadData];
}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    VoiceRoomUserListtCell *cell = [tableView dequeueReusableCellWithIdentifier:@"VoiceRoomUserListtCellID" forIndexPath:indexPath];
    cell.selectionStyle = UITableViewCellSelectionStyleNone;
    cell.model = self.dataLists[indexPath.row];
    cell.delegate = self;
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [tableView deselectRowAtIndexPath:indexPath animated:NO];
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return 60;
}

#pragma mark - UITableViewDataSource

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.dataLists.count;
}

#pragma mark - VoiceRoomUserListtCellDelegate

- (void)voiceRoomUserListtCell:(VoiceRoomUserListtCell *)voiceRoomUserListtCell clickButton:(id)model {
    if ([self.delegate respondsToSelector:@selector(voiceRoomRaiseHandListsView:clickButton:)]) {
        [self.delegate voiceRoomRaiseHandListsView:self clickButton:model];
    }
}

#pragma mark - getter

- (UITableView *)roomTableView {
    if (!_roomTableView) {
        _roomTableView = [[UITableView alloc] init];
        _roomTableView.separatorStyle = UITableViewCellSeparatorStyleNone;
        _roomTableView.delegate = self;
        _roomTableView.dataSource = self;
        [_roomTableView registerClass:VoiceRoomUserListtCell.class forCellReuseIdentifier:@"VoiceRoomUserListtCellID"];
        _roomTableView.backgroundColor = [UIColor colorFromHexString:@"#272E3B"];
    }
    return _roomTableView;
}

- (void)dealloc {
    NSLog(@"dealloc %@",NSStringFromClass([self class]));
}

@end
