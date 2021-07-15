//
//  VoiceRoomView.m
//  veRTC_Demo
//
//  Created by  on 2021/5/21.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import "VoiceRoomView.h"
#import "VoiceRoomTitleCell.h"
#import "VoiceRoomMicCell.h"
#import "VoiceRoomAudienceCell.h"
#import "VoiceRoomSubTitleCell.h"

@interface VoiceRoomView ()<UITableViewDelegate, UITableViewDataSource>

@property (nonatomic, strong) NSMutableArray<VoiceControlUserModel *> *hostLists;

@property (nonatomic, strong) NSMutableArray<VoiceControlUserModel *> *audienceLists;

@property (nonatomic, strong) UITableView *roomTableView;

@property (nonatomic, strong) NSMutableArray *roomDataLists;

@property (nonatomic, strong) VoiceControlRoomModel *roomModel;

@end


@implementation VoiceRoomView

- (instancetype)init
{
    self = [super init];
    if (self) {
        self.backgroundColor = [UIColor clearColor];
        
        [self addSubview:self.roomTableView];
        [self.roomTableView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.edges.equalTo(self);
        }];
    }
    return self;
}


#pragma mark - Publish Action

- (void)updateAllUser:(NSArray<VoiceControlUserModel *> *)userLists roomModel:(VoiceControlRoomModel *)roomModel {
    self.roomModel = roomModel;
    [self.hostLists removeAllObjects];
    [self.audienceLists removeAllObjects];
    if (userLists && userLists.count > 0) {
        for (VoiceControlUserModel *userModel in userLists) {
            if (userModel.is_host || userModel.user_status == 2) {
                [self.hostLists addObject:userModel];
            } else {
                [self.audienceLists addObject:userModel];
            }
        }
    }
    [self updateRoomDataLists];
}

- (void)joinUser:(VoiceControlUserModel *)user {
    NSMutableArray *dataLists = user.is_host ? self.hostLists : self.audienceLists;
    BOOL isRepeat = NO;
    for (VoiceControlUserModel *currentUser in dataLists) {
        if ([currentUser.user_id isEqualToString:user.user_id]) {
            isRepeat = YES;
            break;;
        }
    }
    if (!isRepeat && self.roomModel) {
        [dataLists insertObject:user atIndex:0];
        [self updateRoomDataLists];
    }
}

- (void)leaveUser:(NSString *)user {
    VoiceControlUserModel *leaveUserModel = nil;
    for (VoiceControlUserModel *model in self.hostLists) {
        if ([model.user_id isEqualToString:user]) {
            leaveUserModel = model;
        }
    }
    if (leaveUserModel) {
        [self.hostLists removeObject:leaveUserModel];
        [self updateRoomDataLists];
        leaveUserModel = nil;
    }
    for (VoiceControlUserModel *model in self.audienceLists) {
        if ([model.user_id isEqualToString:user]) {
            leaveUserModel = model;
        }
    }
    if (leaveUserModel) {
        [self.audienceLists removeObject:leaveUserModel];
        [self updateRoomDataLists];
    }
}

- (void)audienceRaisedHandsSuccess:(NSString *)uid {
    VoiceControlUserModel *newHostUser = nil;
    for (VoiceControlUserModel *model in self.audienceLists) {
        if ([model.user_id isEqualToString:uid]) {
            newHostUser = model; break;
        }
    }
    if (newHostUser) {
        [self.audienceLists removeObject:newHostUser];
        [self.hostLists addObject:newHostUser];
        [self updateRoomDataLists];
    }
}

- (void)hostLowerHandSuccess:(NSString *)uid {
    VoiceControlUserModel *newAudienceUser = nil;
    for (VoiceControlUserModel *model in self.hostLists) {
        if ([model.user_id isEqualToString:uid]) {
            newAudienceUser = model;
            newAudienceUser.user_status = 0;
        }
    }
    if (newAudienceUser) {
        [self.hostLists removeObject:newAudienceUser];
        [self.audienceLists insertObject:newAudienceUser atIndex:0];
        [self updateRoomDataLists];
    }
}

- (void)updateHostVolume:(NSDictionary<NSString *, NSNumber *> *_Nonnull)volumeInfo {
    for (VoiceControlUserModel *model in self.hostLists) {
        NSNumber *volume = [volumeInfo objectForKey:model.user_id];
        model.volume = [volume integerValue];
    }
    dispatch_async(dispatch_get_main_queue(), ^{
        [self reloadData];
    });
}

- (void)updateHostUser:(NSString *)uid {
    for (VoiceControlUserModel *model in self.hostLists) {
        if ([model.user_id isEqualToString:uid]) {
            model.is_host = YES;
        } else {
            model.is_host = NO;
        }
    }
}

- (void)updateUserHand:(NSString *)uid isHand:(BOOL)isHand {
    for (VoiceControlUserModel *model in self.audienceLists) {
        if ([model.user_id isEqualToString:uid]) {
            model.user_status = isHand ? 1 : 0;
            break;
        }
    }
}

- (void)updateUserMic:(NSString *)uid isMute:(BOOL)isMute {
    for (VoiceControlUserModel *model in self.hostLists) {
        if ([model.user_id isEqualToString:uid]) {
            model.is_mic_on = !isMute;
            break;
        }
    }
}

- (NSArray<VoiceControlUserModel *> *)allUserLists {
    NSMutableArray *lists = [[NSMutableArray alloc] init];
    [lists addObjectsFromArray:self.hostLists];
    [lists addObjectsFromArray:self.audienceLists];
    return [lists copy];
}

#pragma mark - Private Action

- (void)updateRoomDataLists {
    [self.roomDataLists removeAllObjects];
    //title
    if (self.roomModel && NOEmptyStr(self.roomModel.room_name)) {
        [self.roomDataLists addObject:self.roomModel.room_name];
    } else {
        [self.roomDataLists addObject:@""];
    }
    //host
    [self.roomDataLists addObject:[self.hostLists copy]];
    //sub title
    [self.roomDataLists addObject:[NSString stringWithFormat:@"其他听众%ld人", (long)self.audienceLists.count]];
    //audience
    [self.roomDataLists addObject:[self.audienceLists copy]];
    [self reloadData];
}

- (void)reloadData {
    [self.roomTableView reloadData];
}

- (NSInteger)hostNumber {
    return self.hostLists.count;
}

#pragma mark - UITableViewDelegate

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [UITableViewCell new];
    switch (indexPath.row) {
        case 0:
            cell = [tableView dequeueReusableCellWithIdentifier:@"VoiceRoomTitleCellID" forIndexPath:indexPath];
            ((VoiceRoomTitleCell *)cell).titleStr = self.roomDataLists[indexPath.row];
            break;
        case 1:
            cell = [tableView dequeueReusableCellWithIdentifier:@"VoiceRoomMicCellID" forIndexPath:indexPath];
            ((VoiceRoomMicCell *)cell).dataLists = self.roomDataLists[indexPath.row];
            break;
        case 2:
            cell = [tableView dequeueReusableCellWithIdentifier:@"VoiceRoomSubTitleCellID" forIndexPath:indexPath];
            ((VoiceRoomSubTitleCell *)cell).titleStr = self.roomDataLists[indexPath.row];
            break;
        case 3:
            cell = [tableView dequeueReusableCellWithIdentifier:@"VoiceRoomAudienceCellID" forIndexPath:indexPath];
            ((VoiceRoomAudienceCell *)cell).dataLists = self.roomDataLists[indexPath.row];
            break;
        default:
            break;
    }
    cell.selectionStyle = UITableViewCellSelectionStyleNone;
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [tableView deselectRowAtIndexPath:indexPath animated:NO];
}

#pragma mark - UITableViewDataSource

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.roomDataLists.count;
}


#pragma mark - getter


- (UITableView *)roomTableView {
    if (!_roomTableView) {
        _roomTableView = [[UITableView alloc] init];
        _roomTableView.separatorStyle = UITableViewCellSeparatorStyleNone;
        _roomTableView.delegate = self;
        _roomTableView.dataSource = self;
        [_roomTableView registerClass:VoiceRoomTitleCell.class forCellReuseIdentifier:@"VoiceRoomTitleCellID"];
        [_roomTableView registerClass:VoiceRoomMicCell.class forCellReuseIdentifier:@"VoiceRoomMicCellID"];
        [_roomTableView registerClass:VoiceRoomSubTitleCell.class forCellReuseIdentifier:@"VoiceRoomSubTitleCellID"];
        [_roomTableView registerClass:VoiceRoomAudienceCell.class forCellReuseIdentifier:@"VoiceRoomAudienceCellID"];
        _roomTableView.backgroundColor = [UIColor clearColor];
        _roomTableView.rowHeight = UITableViewAutomaticDimension;
        _roomTableView.estimatedRowHeight = 36;
        _roomTableView.estimatedSectionFooterHeight = 0;
        _roomTableView.estimatedSectionHeaderHeight = 0;
    }
    return _roomTableView;
}

- (NSMutableArray *)roomDataLists {
    if (!_roomDataLists) {
        _roomDataLists = [[NSMutableArray alloc] init];
    }
    return _roomDataLists;
}

- (NSMutableArray<VoiceControlUserModel *> *)hostLists {
    if (!_hostLists) {
        _hostLists = [[NSMutableArray alloc] init];
    }
    return _hostLists;
}

- (NSMutableArray<VoiceControlUserModel *> *)audienceLists {
    if (!_audienceLists) {
        _audienceLists = [[NSMutableArray alloc] init];
    }
    return _audienceLists;
}



@end
