//
//  VoiceRoomTableView.m
//  veRTC_Demo
//
//  Created by  on 2021/5/18.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import "VoiceRoomTableView.h"

@interface VoiceRoomTableView () <UITableViewDelegate, UITableViewDataSource>

@property (nonatomic, strong) UITableView *roomTableView;

@end


@implementation VoiceRoomTableView

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
    VoiceRoomCell *cell = [tableView dequeueReusableCellWithIdentifier:@"VoiceRoomCellID" forIndexPath:indexPath];
    cell.selectionStyle = UITableViewCellSelectionStyleNone;
    cell.model = self.dataLists[indexPath.row];
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [tableView deselectRowAtIndexPath:indexPath animated:NO];

    if ([self.delegate respondsToSelector:@selector(voiceRoomTableView:didSelectRowAtIndexPath:)]) {
        [self.delegate voiceRoomTableView:self didSelectRowAtIndexPath:self.dataLists[indexPath.row]];
    }
}

#pragma mark - UITableViewDataSource

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.dataLists.count;
}


#pragma mark - getter


- (UITableView *)roomTableView {
    if (!_roomTableView) {
        _roomTableView = [[UITableView alloc] init];
        _roomTableView.separatorStyle = UITableViewCellSeparatorStyleNone;
        _roomTableView.delegate = self;
        _roomTableView.dataSource = self;
        [_roomTableView registerClass:VoiceRoomCell.class forCellReuseIdentifier:@"VoiceRoomCellID"];
        _roomTableView.backgroundColor = [UIColor clearColor];
        _roomTableView.rowHeight = UITableViewAutomaticDimension;
        _roomTableView.estimatedRowHeight = 149 + 20;
    }
    return _roomTableView;
}

@end
