//
//  VoiceIMView.m
//  veRTC_Demo
//
//  Created by  on 2021/5/23.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import "VoiceIMView.h"

@interface VoiceIMView ()<UITableViewDelegate, UITableViewDataSource>

@property (nonatomic, strong) UITableView *roomTableView;

@end

@implementation VoiceIMView


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
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.1 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        [self scrollToBottom:YES tableView:self.roomTableView];
    });
}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    VoiceIMCell *cell = [tableView dequeueReusableCellWithIdentifier:@"VoiceIMCellID" forIndexPath:indexPath];
    cell.selectionStyle = UITableViewCellSelectionStyleNone;
    cell.model = self.dataLists[indexPath.row];
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [tableView deselectRowAtIndexPath:indexPath animated:NO];
}

#pragma mark - UITableViewDataSource

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.dataLists.count;
}

#pragma mark - Private Action

- (void)scrollToBottom:(BOOL)animated tableView:(UITableView *)tableView {
    NSUInteger sectionCount = [tableView numberOfSections];
    NSUInteger rowCount = 0;
    while (sectionCount != 0) {
        rowCount = [tableView numberOfRowsInSection:sectionCount-1];
        if(rowCount != 0)
            break;
        sectionCount--;
    }
    
    if (sectionCount && rowCount) {
        NSUInteger ii[2] = {sectionCount-1, rowCount-1};
        NSIndexPath* indexPath = [NSIndexPath indexPathWithIndexes:ii length:2];
        [tableView scrollToRowAtIndexPath:indexPath atScrollPosition:UITableViewScrollPositionBottom
                            animated:animated];
    }
}

#pragma mark - getter


- (UITableView *)roomTableView {
    if (!_roomTableView) {
        _roomTableView = [[UITableView alloc] init];
        _roomTableView.separatorStyle = UITableViewCellSeparatorStyleNone;
        _roomTableView.delegate = self;
        _roomTableView.dataSource = self;
        [_roomTableView registerClass:VoiceIMCell.class forCellReuseIdentifier:@"VoiceIMCellID"];
        _roomTableView.backgroundColor = [UIColor clearColor];
        _roomTableView.rowHeight = UITableViewAutomaticDimension;
        _roomTableView.estimatedRowHeight = 30;
        _roomTableView.showsVerticalScrollIndicator = NO;
        _roomTableView.showsHorizontalScrollIndicator = NO;
    }
    return _roomTableView;
}


@end
