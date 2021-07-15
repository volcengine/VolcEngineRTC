//
//  MeetingControlCompoments.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/16.
//

#import "MeetingControlCompoments.h"
#import "MeetingControlTool.h"

static const CGFloat DefaultTimeout = 3;

@implementation MeetingControlCompoments

#pragma mark - Get meeting data

+ (void)getAppIDWithUid:(NSString *)uid roomId:(NSString *)roomId block:(void (^)(NSString *appID, MeetingControlAckModel *model))block {
    NSDictionary *dic = @{};
    if (uid && roomId && uid.length > 0 && roomId.length > 0) {
        dic = @{@"user_id" : uid,
                @"room_id" : roomId};
    }
    dic = [MeetingControlTool addToken:dic];
    
    OnAckCallback *callback = [[MeetingSocketIOManager shareSocketManager].socket emitWithAck:@"getAppID" with:@[dic]];
    [callback timingOutAfter:1 callback:^(NSArray * _Nonnull dataLists) {
        MeetingControlAckModel *ackModel = [MeetingControlTool dataToAckModel:dataLists];
        NSString *appid = @"";
        if ([ackModel.response isKindOfClass:[NSDictionary class]]) {
            appid = ackModel.response[@"app_id"];
        }
        dispatch_async(dispatch_get_main_queue(), ^{
            if (block) {
                block(appid, ackModel);
            }
        });
        NSLog(@"[%@]-getAppIDWithUid %@", [self class], dataLists);
    }];

}

+ (void)joinMeeting:(LoginModel *)loginModel block:(void (^)(NSString *token, NSArray<RoomUserModel *> *userLists, MeetingControlAckModel *model))block {
    NSMutableDictionary *dic = [[NSMutableDictionary alloc] init];
    [dic setValue:loginModel.appid forKey:@"app_id"];
    [dic setValue:loginModel.uid forKey:@"user_id"];
    [dic setValue:loginModel.name forKey:@"user_name"];
    [dic setValue:loginModel.roomId forKey:@"room_id"];
    [dic setValue:@(loginModel.isEnableAudio) forKey:@"mic"];
    [dic setValue:@(loginModel.isEnableVideo) forKey:@"camera"];
    
    NSDictionary *dicData = [MeetingControlTool addToken:[dic copy]];
    
    OnAckCallback *callback = [[MeetingSocketIOManager shareSocketManager].socket emitWithAck:@"joinMeeting" with:@[dicData]];
    [callback timingOutAfter:DefaultTimeout callback:^(NSArray * _Nonnull dataLists) {
        MeetingControlAckModel *ackModel = [MeetingControlTool dataToAckModel:dataLists];
        NSString *token = @"";
        NSMutableArray *userLists = [[NSMutableArray alloc] init];
        if ([ackModel.response isKindOfClass:[NSDictionary class]]) {
            token = ackModel.response[@"token"];
            NSArray *lists = ackModel.response[@"users"];
            for (int i = 0; i < lists.count; i++) {
                MeetingControlUserModel *meetingUserModel = [MeetingControlUserModel yy_modelWithJSON:lists[i]];
                RoomUserModel *userModel = [RoomUserModel roomUserModelToMeetingControlUserModel:meetingUserModel];
                [userLists addObject:userModel];
            }
            BaseUserModel *localUser = [LocalUserCompoments userModel];
            localUser.name = loginModel.name;
            [LocalUserCompoments updateLocalUserModel:localUser];
        }
        dispatch_async(dispatch_get_main_queue(), ^{
            if (block) {
                block(token, [userLists copy], ackModel);
            }
        });
        NSLog(@"[%@]-joinMeeting %@", [self class], dataLists);
    }];

}

+ (void)leaveMeeting {
    NSDictionary *dic = [MeetingControlTool addToken:nil];
    [[MeetingSocketIOManager shareSocketManager].socket emit:@"leaveMeeting" with:@[dic]];
}

+ (void)turnOnMic {
    NSDictionary *dic = [MeetingControlTool addToken:nil];
    [[MeetingSocketIOManager shareSocketManager].socket emit:@"turnOnMic" with:@[dic]];
}

+ (void)turnOffMic {
    NSDictionary *dic = [MeetingControlTool addToken:nil];
    [[MeetingSocketIOManager shareSocketManager].socket emit:@"turnOffMic" with:@[dic]];
}

+ (void)turnOnCamera {
    NSDictionary *dic = [MeetingControlTool addToken:nil];
    [[MeetingSocketIOManager shareSocketManager].socket emit:@"turnOnCamera" with:@[dic]];
}

+ (void)turnOffCamera {
    NSDictionary *dic = [MeetingControlTool addToken:nil];
    [[MeetingSocketIOManager shareSocketManager].socket emit:@"turnOffCamera" with:@[dic]];
}

+ (void)getMeetingUserInfo:(NSString *)userId block:(void (^)(NSArray<MeetingControlUserModel *> *userLists, MeetingControlAckModel *model))block {
    NSDictionary *dic = @{@"user_id" : userId};
    dic = [MeetingControlTool addToken:dic];
    
    OnAckCallback *callback = [[MeetingSocketIOManager shareSocketManager].socket emitWithAck:@"getMeetingUserInfo" with:@[dic]];
    [callback timingOutAfter:DefaultTimeout callback:^(NSArray * _Nonnull dataLists) {
        MeetingControlAckModel *ackModel = [MeetingControlTool dataToAckModel:dataLists];
        NSMutableArray *modelLsts = [[NSMutableArray alloc] init];
        NSArray *data = (NSArray *)ackModel.response;
        if (data && [data isKindOfClass:[NSArray class]]) {
            for (int i = 0; i < data.count; i++) {
                MeetingControlUserModel *userModel = [MeetingControlUserModel yy_modelWithJSON:data[i]];
                [modelLsts addObject:userModel];
            }
        }
        if (block) {
            block([modelLsts copy], ackModel);
        }
        NSLog(@"[%@]-getMeetingUserInfo %@", [self class], dataLists);
    }];

}

+ (void)getMeetingInfoWithBlock:(void (^)(MeetingControlRoomModel *roomModel, MeetingControlAckModel *model))block {
    NSDictionary *dic = [MeetingControlTool addToken:nil];
    OnAckCallback *callback = [[MeetingSocketIOManager shareSocketManager].socket emitWithAck:@"getMeetingInfo" with:@[dic]];
    [callback timingOutAfter:DefaultTimeout callback:^(NSArray * _Nonnull dataLists) {
        MeetingControlAckModel *ackModel = [MeetingControlTool dataToAckModel:dataLists];
        MeetingControlRoomModel *roomModel = [MeetingControlRoomModel yy_modelWithJSON:ackModel.response];
        dispatch_async(dispatch_get_main_queue(), ^{
            if (block) {
                block(roomModel, ackModel);
            }
        });
        NSLog(@"[%@]-getMeetingInfoWithBlock %@", [self class], dataLists);
    }];
}

+ (void)getHistoryVideoRecordWithBlock:(void (^)(NSArray<MeetingControlRecordModel *> *recordLists, MeetingControlAckModel *model))block {
    NSDictionary *dic = [MeetingControlTool addToken:nil];
    OnAckCallback *callback = [[MeetingSocketIOManager shareSocketManager].socket emitWithAck:@"getHistoryVideoRecord" with:@[dic]];
    [callback timingOutAfter:DefaultTimeout callback:^(NSArray * _Nonnull dataLists) {
        MeetingControlAckModel *ackModel = [MeetingControlTool dataToAckModel:dataLists];
        NSMutableArray *modelLsts = [[NSMutableArray alloc] init];
        NSArray *data = (NSArray *)ackModel.response;
        if (data && [data isKindOfClass:[NSArray class]]) {
            for (int i = 0; i < data.count; i++) {
                MeetingControlRecordModel *model = [MeetingControlRecordModel yy_modelWithJSON:data[i]];
                [modelLsts addObject:model];
            }
        }
        dispatch_async(dispatch_get_main_queue(), ^{
            if (block) {
                block([modelLsts copy], ackModel);
            }
        });
        NSLog(@"[%@]-getHistoryVideoRecordWithBlock %@", [self class], dataLists);
    }];
}

+ (void)reconnectWithBlock:(void (^)(MeetingControlAckModel *model))block {
    NSDictionary *dic = [MeetingControlTool addToken:nil];
    OnAckCallback *callback = [[MeetingSocketIOManager shareSocketManager].socket emitWithAck:@"userReconnect" with:@[dic]];
    [callback timingOutAfter:5 callback:^(NSArray * _Nonnull dataLists) {
        MeetingControlAckModel *ackModel = [MeetingControlTool dataToAckModel:dataLists];
        dispatch_async(dispatch_get_main_queue(), ^{
            if (block) {
                block(ackModel);
            }
        });
        NSLog(@"[%@]-reconnectWithBlock %@", [self class], dataLists);
    }];
}

+ (void)deleteVideoRecord:(NSString *)vid block:(void (^)(MeetingControlAckModel *ackModel))block {
    NSDictionary *dic = @{@"vid" : vid};
    dic = [MeetingControlTool addToken:dic];
    
    OnAckCallback *callback = [[MeetingSocketIOManager shareSocketManager].socket emitWithAck:@"deleteVideoRecord" with:@[dic]];
    [callback timingOutAfter:DefaultTimeout callback:^(NSArray * _Nonnull dataLists) {
        MeetingControlAckModel *ackModel = [MeetingControlTool dataToAckModel:dataLists];
        dispatch_async(dispatch_get_main_queue(), ^{
            if (block) {
                block(ackModel);
            }
        });
        NSLog(@"[%@]-deleteVideoRecord %@", [self class], dataLists);
    }];
}


#pragma mark - Control meeting status

+ (void)changeHost:(NSString *)userId block:(void (^)(BOOL result, MeetingControlAckModel *model))block {
    NSDictionary *dic = @{};
    if (userId.length > 0) {
        dic = @{@"user_id" : userId};
    }
    dic = [MeetingControlTool addToken:dic];
    
    OnAckCallback *callback = [[MeetingSocketIOManager shareSocketManager].socket emitWithAck:@"changeHost" with:@[dic]];
    [callback timingOutAfter:DefaultTimeout callback:^(NSArray * _Nonnull dataLists) {
        MeetingControlAckModel *ackModel = [MeetingControlTool dataToAckModel:dataLists];
        dispatch_async(dispatch_get_main_queue(), ^{
            if (block) {
                block(NO, ackModel);
            }
        });
    }];
}

+ (void)muteUser:(NSString *)userId block:(void (^)(BOOL result, MeetingControlAckModel *model))block {
    NSDictionary *dic = @{};
    if (userId.length > 0) {
        dic = @{@"user_id" : userId};
    }
    dic = [MeetingControlTool addToken:dic];
    
    OnAckCallback *callback = [[MeetingSocketIOManager shareSocketManager].socket emitWithAck:@"muteUser" with:@[dic]];
    [callback timingOutAfter:DefaultTimeout callback:^(NSArray * _Nonnull dataLists) {
        MeetingControlAckModel *ackModel = [MeetingControlTool dataToAckModel:dataLists];
        dispatch_async(dispatch_get_main_queue(), ^{
            if (block) {
                block(NO, ackModel);
            }
        });
    }];
}

+ (void)askMicOn:(NSString *)userId block:(void (^)(BOOL result))block {
    NSDictionary *dic = @{};
    if (userId.length > 0) {
        dic = @{@"user_id" : userId};
    }
    dic = [MeetingControlTool addToken:dic];
    
    [[MeetingSocketIOManager shareSocketManager].socket emit:@"askMicOn" with:@[dic] completion:^{
        if (block) {
            block(NO);
        }
    }];
}

+ (void)askCameraOn:(NSString *)userId block:(void (^)(BOOL result))block {
    NSDictionary *dic = @{};
    if (userId.length > 0) {
        dic = @{@"user_id" : userId};
    }
    dic = [MeetingControlTool addToken:dic];
    
    [[MeetingSocketIOManager shareSocketManager].socket emit:@"askCameraOn" with:@[dic] completion:^{
        if (block) {
            block(NO);
        }
    }];
}

+ (void)endMeeting {
    NSDictionary *dic = [MeetingControlTool addToken:nil];
    [[MeetingSocketIOManager shareSocketManager].socket emit:@"endMeeting" with:@[dic]];
}

+ (void)startShareScreen {
    NSDictionary *dic = [MeetingControlTool addToken:nil];
    [[MeetingSocketIOManager shareSocketManager].socket emit:@"startShareScreen" with:@[dic]];
}

+ (void)endShareScreen {
    NSDictionary *dic = [MeetingControlTool addToken:nil];
    [[MeetingSocketIOManager shareSocketManager].socket emit:@"endShareScreen" with:@[dic]];
}

+ (void)recordMeeting:(NSArray *)uids screenId:(NSString *)screenId {
    NSMutableDictionary *dic = [[NSMutableDictionary alloc] init];
    if (uids && [uids isKindOfClass:[NSArray class]]) {
        [dic setValue:uids forKey:@"users"];
    }
    if (screenId.length > 0) {
        [dic setValue:screenId forKey:@"screen_uid"];
    }
    NSDictionary *dicData = [MeetingControlTool addToken:[dic copy]];
    [[MeetingSocketIOManager shareSocketManager].socket emit:@"recordMeeting" with:@[dicData]];
}

+ (void)updateRecordLayout:(NSArray *)uids screenId:(NSString *)screenId {
    NSMutableDictionary *dic = [[NSMutableDictionary alloc] init];
    if (uids && [uids isKindOfClass:[NSArray class]]) {
        [dic setValue:uids forKey:@"users"];
    }
    if (screenId.length > 0) {
        [dic setValue:screenId forKey:@"screen_uid"];
    }
    NSDictionary *dicData = [MeetingControlTool addToken:[dic copy]];
    [[MeetingSocketIOManager shareSocketManager].socket emit:@"updateRecordLayout" with:@[dicData]];
}


#pragma mark - Notification message

+ (void)onUserMicStatusChangeWithBlock:(void (^)(NSString *uid, BOOL result))block {
    [[MeetingSocketIOManager shareSocketManager].socket on:@"onUserMicStatusChange" callback:^(NSArray * _Nonnull lists, SocketAckEmitter * _Nonnull socketAckEmitter) {
        MeetingControlNoticeModel *noticeModel = [MeetingControlTool dataToNoticeModel:lists];
        NSString *uid = @"";
        BOOL status = NO;
        if (noticeModel.data && [noticeModel.data isKindOfClass:[NSDictionary class]]) {
            uid = noticeModel.data[@"user_id"];
            status = [noticeModel.data[@"status"] boolValue];
        }
        if (block) {
            block(uid, status);
        }
    }];
}

+ (void)onUserCameraStatusChangeWithBlock:(void (^)(NSString *uid, BOOL result))block {
    [[MeetingSocketIOManager shareSocketManager].socket on:@"onUserCameraStatusChange" callback:^(NSArray * _Nonnull lists, SocketAckEmitter * _Nonnull socketAckEmitter) {
        MeetingControlNoticeModel *noticeModel = [MeetingControlTool dataToNoticeModel:lists];
        NSString *uid = @"";
        BOOL status = NO;
        if (noticeModel.data && [noticeModel.data isKindOfClass:[NSDictionary class]]) {
            uid = noticeModel.data[@"user_id"];
            status = [noticeModel.data[@"status"] boolValue];
        }
        if (block) {
            block(uid, status);
        }
    }];
}

+ (void)onHostChangeWithBlock:(void (^)(NSString *formerHostUid, NSString *hostUid))block {
    [[MeetingSocketIOManager shareSocketManager].socket on:@"onHostChange" callback:^(NSArray * _Nonnull lists, SocketAckEmitter * _Nonnull socketAckEmitter) {
        MeetingControlNoticeModel *noticeModel = [MeetingControlTool dataToNoticeModel:lists];
        NSString *aboveUid = @"";
        NSString *hostUid = @"";
        if (noticeModel.data && [noticeModel.data isKindOfClass:[NSDictionary class]]) {
            aboveUid = noticeModel.data[@"former_host_id"];
            hostUid = noticeModel.data[@"host_id"];
        }
        if (block) {
            block(aboveUid, hostUid);
        }
    }];
}

+ (void)onUserJoinMeetingWithBlock:(void (^)(MeetingControlUserModel *model))block {
    [[MeetingSocketIOManager shareSocketManager].socket on:@"onUserJoinMeeting" callback:^(NSArray * _Nonnull lists, SocketAckEmitter * _Nonnull socketAckEmitter) {
        MeetingControlNoticeModel *noticeModel = [MeetingControlTool dataToNoticeModel:lists];
        MeetingControlUserModel *model = [MeetingControlUserModel yy_modelWithJSON:noticeModel.data];
        if (block) {
            block(model);
        }
    }];
}

+ (void)onUserLeaveMeetingWithBlock:(void (^)(NSString *uid))block {
    [[MeetingSocketIOManager shareSocketManager].socket on:@"onUserLeaveMeeting" callback:^(NSArray * _Nonnull lists, SocketAckEmitter * _Nonnull socketAckEmitter) {
        NSString *uid = @"";
        MeetingControlNoticeModel *noticeModel = [MeetingControlTool dataToNoticeModel:lists];
        if (noticeModel.data && [noticeModel.data isKindOfClass:[NSDictionary class]]) {
            uid = noticeModel.data[@"user_id"];
        }
        if (block) {
            block(uid);
        }
    }];
}

+ (void)onUserKickedOffWithBlock:(void (^)(BOOL result))block {
    [[MeetingSocketIOManager shareSocketManager].socket on:@"onUserKickedOff" callback:^(NSArray * _Nonnull lists, SocketAckEmitter * _Nonnull socketAckEmitter) {
        if (block) {
            block(YES);
        }
    }];
}

+ (void)onShareScreenStatusChangedWithBlock:(void (^)(NSString *uid, BOOL result))block {
    [[MeetingSocketIOManager shareSocketManager].socket on:@"onShareScreenStatusChanged" callback:^(NSArray * _Nonnull lists, SocketAckEmitter * _Nonnull socketAckEmitter) {
        NSString *uid = @"";
        BOOL status = NO;
        MeetingControlNoticeModel *noticeModel = [MeetingControlTool dataToNoticeModel:lists];
        if (noticeModel.data && [noticeModel.data isKindOfClass:[NSDictionary class]]) {
            uid = noticeModel.data[@"user_id"];
            status = [noticeModel.data[@"status"] boolValue];
        }
        if (block) {
            block(uid ,status);
        }
    }];
}

+ (void)onRecordWithBlock:(void (^)(BOOL result))block {
    [[MeetingSocketIOManager shareSocketManager].socket on:@"onRecord" callback:^(NSArray * _Nonnull lists, SocketAckEmitter * _Nonnull socketAckEmitter) {
        if (block) {
            block(YES);
        }
    }];
}

+ (void)onMeetingEndWithBlock:(void (^)(BOOL result))block {
    [[MeetingSocketIOManager shareSocketManager].socket on:@"onMeetingEnd" callback:^(NSArray * _Nonnull lists, SocketAckEmitter * _Nonnull socketAckEmitter) {
        if (block) {
            block(YES);
        }
    }];
}

+ (void)onMuteAllWithBlock:(void (^)(BOOL result))block {
    [[MeetingSocketIOManager shareSocketManager].socket on:@"onMuteAll" callback:^(NSArray * _Nonnull lists, SocketAckEmitter * _Nonnull socketAckEmitter) {
        if (block) {
            block(YES);
        }
    }];
}

+ (void)onMuteUserWithBlock:(void (^)(NSString *uid))block {
    [[MeetingSocketIOManager shareSocketManager].socket on:@"onMuteUser" callback:^(NSArray * _Nonnull lists, SocketAckEmitter * _Nonnull socketAckEmitter) {
        NSString *uid = @"";
        MeetingControlNoticeModel *noticeModel = [MeetingControlTool dataToNoticeModel:lists];
        if (noticeModel.data && [noticeModel.data isKindOfClass:[NSDictionary class]]) {
            uid = noticeModel.data[@"user_id"];
        }
        if (block) {
            block(uid);
        }
    }];
}

+ (void)onRecordFinishedWithBlock:(void (^)(BOOL result))block {
    [[MeetingSocketIOManager shareSocketManager].socket on:@"onRecordFinished" callback:^(NSArray * _Nonnull lists, SocketAckEmitter * _Nonnull socketAckEmitter) {
        if (block) {
            block(NO);
        }
    }];
}

+ (void)onAskingMicOnWithBlock:(void (^)(NSString *uid))block {
    [[MeetingSocketIOManager shareSocketManager].socket on:@"onAskingMicOn" callback:^(NSArray * _Nonnull lists, SocketAckEmitter * _Nonnull socketAckEmitter) {
        NSString *uid = @"";
        MeetingControlNoticeModel *noticeModel = [MeetingControlTool dataToNoticeModel:lists];
        if (noticeModel.data && [noticeModel.data isKindOfClass:[NSDictionary class]]) {
            uid = noticeModel.data[@"user_id"];
        }
        if (block) {
            block(uid);
        }
    }];
}

+ (void)onAskingCameraOnWithBlock:(void (^)(NSString *uid))block {
    [[MeetingSocketIOManager shareSocketManager].socket on:@"onAskingCameraOn" callback:^(NSArray * _Nonnull lists, SocketAckEmitter * _Nonnull socketAckEmitter) {
        if (block) {
            block(nil);
        }
    }];
}

#pragma mark - Upgrade

+ (void)getAuditState:(void (^)(MenuUpgradeModel *upgradeModel, MeetingControlAckModel *ackModel))block {
    NSDictionary *dic = @{@"device_type" : @"ios"};
    
    OnAckCallback *callback = [[MeetingSocketIOManager shareSocketManager].socket emitWithAck:@"getAuditState"
                                                                                       with:@[dic]];
    [callback timingOutAfter:DefaultTimeout callback:^(NSArray * _Nonnull dataLists) {
        MeetingControlAckModel *ackModel = [MeetingControlTool dataToAckModel:dataLists];
        MenuUpgradeModel *model = [MenuUpgradeModel yy_modelWithJSON:ackModel.response];
        dispatch_async(dispatch_get_main_queue(), ^{
            if (block) {
                block(model, ackModel);
            }
        });
        NSLog(@"[%@]-getAuditState %@", [self class], dataLists);
    }];
}

#pragma mark - Login

+ (void)login:(NSString *)name block:(void (^)(BaseUserModel *userModel, MeetingControlAckModel *ackModel))block {
    NSDictionary *dic = @{@"user_name" : name};
    
    OnAckCallback *callback = [[MeetingSocketIOManager shareSocketManager].socket emitWithAck:@"passwordFreeLogin"
                                                                                       with:@[dic]];
    [callback timingOutAfter:DefaultTimeout callback:^(NSArray * _Nonnull dataLists) {
        MeetingControlAckModel *ackModel = [MeetingControlTool dataToAckModel:dataLists];
        BaseUserModel *model = [BaseUserModel yy_modelWithJSON:ackModel.response];
        if ([ackModel.response isKindOfClass:[NSDictionary class]]) {
            [MenuTokenCompoments updateToken:ackModel.response[@"login_token"]];
        }
        dispatch_async(dispatch_get_main_queue(), ^{
            if (block) {
                block(model, ackModel);
            }
        });
        NSLog(@"[%@]-getAuditState %@", [self class], dataLists);
    }];
}

+ (void)changeUserName:(BaseUserModel *)userModel block:(void (^)(MeetingControlAckModel *ackModel))block {
    NSDictionary *dic = @{@"user_id" : userModel.uid,
                          @"user_name" : userModel.name};
    dic = [MeetingControlTool addToken:dic];
    
    OnAckCallback *callback = [[MeetingSocketIOManager shareSocketManager].socket emitWithAck:@"changeUserName"
                                                                                       with:@[dic]];
    [callback timingOutAfter:DefaultTimeout callback:^(NSArray * _Nonnull dataLists) {
        MeetingControlAckModel *ackModel = [MeetingControlTool dataToAckModel:dataLists];
        dispatch_async(dispatch_get_main_queue(), ^{
            if (block) {
                block(ackModel);
            }
        });
        NSLog(@"[%@]-getAuditState %@", [self class], dataLists);
    }];
}

+ (void)verifyLoginToken {
    NSDictionary *dic = [MeetingControlTool addToken:nil];
    
    OnAckCallback *callback = [[MeetingSocketIOManager shareSocketManager].socket emitWithAck:@"verifyLoginToken"
                                                                                       with:@[dic]];
    [callback timingOutAfter:DefaultTimeout callback:^(NSArray * _Nonnull dataLists) {
        [MeetingControlTool dataToAckModel:dataLists];
        NSLog(@"[%@]-verifyLoginToken %@", [self class], dataLists);
    }];
}

@end
