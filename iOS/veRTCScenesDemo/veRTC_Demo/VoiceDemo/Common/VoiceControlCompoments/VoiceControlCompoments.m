//
//  VoiceControlCompoments.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/16.
//

#import "VoiceControlCompoments.h"
#import "VoiceControlTool.h"

static const CGFloat DefaultTimeout = 3;

@implementation VoiceControlCompoments

#pragma mark - Get Voice data

+ (void)reconnectWithBlock:(void (^)(VoiceControlRoomModel *roomModel, NSArray *users, VoiceControlAckModel *model))block {
    NSDictionary *dic = [VoiceControlTool addToken:nil];
    
    OnAckCallback *callback = [[VoiceSocketIOManager shareSocketManager].socket emitWithAck:@"csUserReconnect" with:@[dic]];
    [callback timingOutAfter:DefaultTimeout callback:^(NSArray * _Nonnull dataLists) {
        VoiceControlAckModel *ackModel = [VoiceControlTool dataToAckModel:dataLists];
        VoiceControlRoomModel *roomModel = nil;
        NSMutableArray *userLists = [[NSMutableArray alloc] init];
        if ([ackModel.response isKindOfClass:[NSDictionary class]]) {
            roomModel = [VoiceControlRoomModel yy_modelWithJSON:ackModel.response[@"info"]];
            NSArray *infos = ackModel.response[@"users"];
            for (int i = 0; i < infos.count; i++) {
                VoiceControlUserModel *model = [VoiceControlUserModel yy_modelWithJSON:infos[i]];
                if (model) {
                    [userLists addObject:model];
                }
            }
        }
        dispatch_async(dispatch_get_main_queue(), ^{
            if (block) {
                block(roomModel, [userLists copy], ackModel);
            }
        });
        NSLog(@"[%@]-reconnectWithBlock %@", [self class], dataLists);
    }];
}

+ (void)getAppIDWithUid:(NSString *)uid roomId:(NSString *)roomId block:(void (^)(NSString *appID, VoiceControlAckModel *model))block {
    NSDictionary *dic = @{};
    if (uid && roomId && uid.length > 0 && roomId.length > 0) {
        dic = @{@"user_id" : uid,
                @"room_id" : roomId};
    }
    dic = [VoiceControlTool addToken:dic];
    
    OnAckCallback *callback = [[VoiceSocketIOManager shareSocketManager].socket emitWithAck:@"getAppID" with:@[dic]];
    [callback timingOutAfter:DefaultTimeout callback:^(NSArray * _Nonnull dataLists) {
        VoiceControlAckModel *ackModel = [VoiceControlTool dataToAckModel:dataLists];
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

+ (void)getMeetingsWithBlock:(void (^)(NSArray *lists, VoiceControlAckModel *model))block {
    NSDictionary *dic = [VoiceControlTool addToken:nil];
    OnAckCallback *callback = [[VoiceSocketIOManager shareSocketManager].socket emitWithAck:@"csGetMeetings" with:@[dic]];
    
    [callback timingOutAfter:DefaultTimeout callback:^(NSArray * _Nonnull dataLists) {
        VoiceControlAckModel *ackModel = [VoiceControlTool dataToAckModel:dataLists];
        NSMutableArray *modelLsts = [[NSMutableArray alloc] init];
        if ([ackModel.response isKindOfClass:[NSDictionary class]]) {
            NSArray *infos = ackModel.response[@"infos"];
            for (int i = 0; i < infos.count; i++) {
                VoiceControlRoomModel *roomMdoel = [VoiceControlRoomModel yy_modelWithJSON:infos[i]];
                [modelLsts addObject:roomMdoel];
            }
        }
        dispatch_async(dispatch_get_main_queue(), ^{
            if (block) {
                block([modelLsts copy], ackModel);
            }
        });
        NSLog(@"[%@]-getMeetingsWithBlock %@", [self class], dataLists);
    }];
}

+ (void)createMeeting:(NSString *)roomName
             userName:(NSString *)userName
                block:(void (^)(NSString *token,
                                VoiceControlRoomModel *roomModel,
                                NSArray<VoiceControlUserModel *> *lists,
                                VoiceControlAckModel *model))block {
    NSString *encodedString = (NSString *)CFBridgingRelease(CFURLCreateStringByAddingPercentEscapes(kCFAllocatorDefault,(CFStringRef)roomName,NULL,NULL,kCFStringEncodingUTF8));
    NSDictionary *dic = @{@"room_name" : encodedString,
                          @"user_name" : userName};
    dic = [VoiceControlTool addToken:dic];
    
    OnAckCallback *callback = [[VoiceSocketIOManager shareSocketManager].socket emitWithAck:@"csCreateMeeting" with:@[dic]];
    [callback timingOutAfter:DefaultTimeout callback:^(NSArray * _Nonnull dataLists) {
        VoiceControlAckModel *ackModel = [VoiceControlTool dataToAckModel:dataLists];
        NSString *token = @"";
        VoiceControlRoomModel *roomModel = nil;
        NSMutableArray *modelLsts = [[NSMutableArray alloc] init];
        if ([ackModel.response isKindOfClass:[NSDictionary class]]) {
            token = ackModel.response[@"token"];
            roomModel = [VoiceControlRoomModel yy_modelWithJSON:ackModel.response[@"info"]];
            NSArray *infos = ackModel.response[@"users"];
            for (int i = 0; i < infos.count; i++) {
                VoiceControlUserModel *model = [VoiceControlUserModel yy_modelWithJSON:infos[i]];
                [modelLsts addObject:model];
            }
        }
        dispatch_async(dispatch_get_main_queue(), ^{
            if (block) {
                block(token, roomModel, [modelLsts copy], ackModel);
            }
        });
        NSLog(@"[%@]-createMeeting %@", [self class], dataLists);
    }];
}


+ (void)joinVoice:(NSString *)roomID
         userName:(NSString *)userName
            block:(void (^)(NSString *token,
                            VoiceControlRoomModel *roomModel,
                            NSArray<VoiceControlUserModel *> *lists,
                            VoiceControlAckModel *model))block {
    NSDictionary *dic = @{};
    if (NOEmptyStr(roomID) && NOEmptyStr(userName)) {
        dic = @{@"room_id" : roomID,
                @"user_name" : userName};
    }
    dic = [VoiceControlTool addToken:dic];
    
    OnAckCallback *callback = [[VoiceSocketIOManager shareSocketManager].socket emitWithAck:@"csJoinMeeting" with:@[dic]];
    [callback timingOutAfter:DefaultTimeout callback:^(NSArray * _Nonnull dataLists) {
        VoiceControlAckModel *ackModel = [VoiceControlTool dataToAckModel:dataLists];
        NSString *token = @"";
        VoiceControlRoomModel *roomModel = nil;
        NSMutableArray *modelLsts = [[NSMutableArray alloc] init];
        if ([ackModel.response isKindOfClass:[NSDictionary class]]) {
            token = ackModel.response[@"token"];
            roomModel = [VoiceControlRoomModel yy_modelWithJSON:ackModel.response[@"info"]];
            NSArray *infos = ackModel.response[@"users"];
            for (int i = 0; i < infos.count; i++) {
                VoiceControlUserModel *model = [VoiceControlUserModel yy_modelWithJSON:infos[i]];
                if (model) {
                    [modelLsts addObject:model];
                }
            }
        }
        dispatch_async(dispatch_get_main_queue(), ^{
            if (block) {
                block(token, roomModel, [modelLsts copy], ackModel);
            }
        });
        NSLog(@"[%@]-createMeeting %@", [self class], dataLists);
    }];

}

+ (void)leaveVoice {
    NSDictionary *dic = [VoiceControlTool addToken:nil];
    [[VoiceSocketIOManager shareSocketManager].socket emit:@"csLeaveMeeting" with:@[dic]];
}

+ (void)getRaiseHandsWithBlock:(void (^)(NSArray<VoiceControlUserModel *> *userLists, VoiceControlAckModel *model))block {
    NSDictionary *dic = [VoiceControlTool addToken:nil];
    OnAckCallback *callback = [[VoiceSocketIOManager shareSocketManager].socket emitWithAck:@"csGetRaiseHands" with:@[dic]];
    [callback timingOutAfter:DefaultTimeout callback:^(NSArray * _Nonnull dataLists) {
        VoiceControlAckModel *ackModel = [VoiceControlTool dataToAckModel:dataLists];
        NSMutableArray *modelLsts = [[NSMutableArray alloc] init];
        NSArray *data = (NSArray *)ackModel.response[@"users"];
        if (data && [data isKindOfClass:[NSArray class]]) {
            for (int i = 0; i < data.count; i++) {
                VoiceControlUserModel *userModel = [VoiceControlUserModel yy_modelWithJSON:data[i]];
                [modelLsts addObject:userModel];
            }
        }
        dispatch_async(dispatch_get_main_queue(), ^{
            if (block) {
                block([modelLsts copy], ackModel);
            }
        });
        NSLog(@"[%@]-getRaiseHandsWithBlock %@", [self class], dataLists);
    }];
}

+ (void)getAudiencesWithBlock:(void (^)(NSArray<VoiceControlUserModel *> *userLists, VoiceControlAckModel *model))block {
    NSDictionary *dic = [VoiceControlTool addToken:nil];
    OnAckCallback *callback = [[VoiceSocketIOManager shareSocketManager].socket emitWithAck:@"csGetAudiences" with:@[dic]];
    [callback timingOutAfter:DefaultTimeout callback:^(NSArray * _Nonnull dataLists) {
        VoiceControlAckModel *ackModel = [VoiceControlTool dataToAckModel:dataLists];
        NSMutableArray *modelLsts = [[NSMutableArray alloc] init];
        NSArray *data = (NSArray *)ackModel.response[@"users"];
        if (data && [data isKindOfClass:[NSArray class]]) {
            for (int i = 0; i < data.count; i++) {
                VoiceControlUserModel *userModel = [VoiceControlUserModel yy_modelWithJSON:data[i]];
                [modelLsts addObject:userModel];
            }
        }
        dispatch_async(dispatch_get_main_queue(), ^{
            if (block) {
                block([modelLsts copy], ackModel);
            }
        });
        NSLog(@"[%@]-getAudiencesWithBlock %@", [self class], dataLists);
    }];
}

#pragma mark - Control Voice status

+ (void)inviteMic:(NSString *)userId block:(void (^)(VoiceControlAckModel *model))block {
    NSDictionary *dic = @{};
    if (NOEmptyStr(userId)) {
        dic = @{@"user_id" : userId};
    }
    dic = [VoiceControlTool addToken:dic];
    OnAckCallback *callback = [[VoiceSocketIOManager shareSocketManager].socket emitWithAck:@"csInviteMic" with:@[dic]];
    [callback timingOutAfter:DefaultTimeout callback:^(NSArray * _Nonnull dataLists) {
        VoiceControlAckModel *ackModel = [VoiceControlTool dataToAckModel:dataLists];
        dispatch_async(dispatch_get_main_queue(), ^{
            if (block) {
                block(ackModel);
            }
        });
        NSLog(@"[%@]-inviteMic %@", [self class], dataLists);
    }];
}

+ (void)confirmMicWithBlock:(void (^)(VoiceControlAckModel *model))block {
    NSDictionary *dic = [VoiceControlTool addToken:nil];
    OnAckCallback *callback = [[VoiceSocketIOManager shareSocketManager].socket emitWithAck:@"csConfirmMic" with:@[dic]];
    [callback timingOutAfter:DefaultTimeout callback:^(NSArray * _Nonnull dataLists) {
        VoiceControlAckModel *ackModel = [VoiceControlTool dataToAckModel:dataLists];
        NSMutableArray *modelLsts = [[NSMutableArray alloc] init];
        NSArray *data = (NSArray *)ackModel.response;
        if (data && [data isKindOfClass:[NSArray class]]) {
            for (int i = 0; i < data.count; i++) {
                VoiceControlRecordModel *model = [VoiceControlRecordModel yy_modelWithJSON:data[i]];
                [modelLsts addObject:model];
            }
        }
        dispatch_async(dispatch_get_main_queue(), ^{
            if (block) {
                block(ackModel);
            }
        });
        NSLog(@"[%@]-confirmMicWithBlock %@", [self class], dataLists);
    }];
}

+ (void)raiseHandsMicWithBlock:(void (^)(VoiceControlAckModel *model))block {
    NSDictionary *dic = [VoiceControlTool addToken:nil];
    OnAckCallback *callback = [[VoiceSocketIOManager shareSocketManager].socket emitWithAck:@"csRaiseHandsMic" with:@[dic]];
    [callback timingOutAfter:DefaultTimeout callback:^(NSArray * _Nonnull dataLists) {
        VoiceControlAckModel *ackModel = [VoiceControlTool dataToAckModel:dataLists];
        dispatch_async(dispatch_get_main_queue(), ^{
            if (block) {
                block(ackModel);
            }
        });
        NSLog(@"[%@]-raiseHandsMicWithBlock %@", [self class], dataLists);
    }];
}

+ (void)agreeMic:(NSString *)userId block:(void (^)(VoiceControlAckModel *model))block {
    NSDictionary *dic = @{};
    if (NOEmptyStr(userId)) {
        dic = @{@"user_id" : userId};
    }
    dic = [VoiceControlTool addToken:dic];
    OnAckCallback *callback = [[VoiceSocketIOManager shareSocketManager].socket emitWithAck:@"csAgreeMic" with:@[dic]];
    [callback timingOutAfter:DefaultTimeout callback:^(NSArray * _Nonnull dataLists) {
        VoiceControlAckModel *ackModel = [VoiceControlTool dataToAckModel:dataLists];
        dispatch_async(dispatch_get_main_queue(), ^{
            if (block) {
                block(ackModel);
            }
        });
        NSLog(@"[%@]-agreeMic %@", [self class], dataLists);
    }];
}

+ (void)offSelfMicWithBlock:(void (^)(VoiceControlAckModel *model))block {
    NSDictionary *dic = [VoiceControlTool addToken:nil];
    OnAckCallback *callback = [[VoiceSocketIOManager shareSocketManager].socket emitWithAck:@"csOffSelfMic" with:@[dic]];
    [callback timingOutAfter:DefaultTimeout callback:^(NSArray * _Nonnull dataLists) {
        VoiceControlAckModel *ackModel = [VoiceControlTool dataToAckModel:dataLists];
        dispatch_async(dispatch_get_main_queue(), ^{
            if (block) {
                block(ackModel);
            }
        });
        NSLog(@"[%@]-reconnectWithBlock %@", [self class], dataLists);
    }];
}

+ (void)offMic:(NSString *)userId block:(void (^)(VoiceControlAckModel *model))block {
    NSDictionary *dic = @{};
    if (NOEmptyStr(userId)) {
        dic = @{@"user_id" : userId};
    }
    dic = [VoiceControlTool addToken:dic];
    OnAckCallback *callback = [[VoiceSocketIOManager shareSocketManager].socket emitWithAck:@"csOffMic" with:@[dic]];
    [callback timingOutAfter:DefaultTimeout callback:^(NSArray * _Nonnull dataLists) {
        VoiceControlAckModel *ackModel = [VoiceControlTool dataToAckModel:dataLists];
        NSString *appid = @"";
        if ([ackModel.response isKindOfClass:[NSDictionary class]]) {
            appid = ackModel.response[@"app_id"];
        }
        dispatch_async(dispatch_get_main_queue(), ^{
            if (block) {
                block(ackModel);
            }
        });
        NSLog(@"[%@]-createMeeting %@", [self class], dataLists);
    }];
}
                                                                      
+ (void)muteMic {
    NSDictionary *dic = [VoiceControlTool addToken:nil];
    [[VoiceSocketIOManager shareSocketManager].socket emit:@"csMuteMic" with:@[dic]];
}

+ (void)unmuteMic {
    NSDictionary *dic = [VoiceControlTool addToken:nil];
    [[VoiceSocketIOManager shareSocketManager].socket emit:@"csUnmuteMic" with:@[dic]];
}

#pragma mark - Notification message

+ (void)onJoinMeetingWithBlock:(void (^)(VoiceControlUserModel *userModel))block {
    [[VoiceSocketIOManager shareSocketManager].socket on:@"onCsJoinMeeting" callback:^(NSArray * _Nonnull lists, SocketAckEmitter * _Nonnull socketAckEmitter) {
        VoiceControlNoticeModel *noticeModel = [VoiceControlTool dataToNoticeModel:lists];
        VoiceControlUserModel *model = nil;
        if (noticeModel.data && [noticeModel.data isKindOfClass:[NSDictionary class]]) {
            model = [VoiceControlUserModel yy_modelWithJSON:noticeModel.data];
        }
        if (block) {
            block(model);
        }
    }];
}

+ (void)onLeaveMeetingWithBlock:(void (^)(VoiceControlUserModel *userModel))block {
    [[VoiceSocketIOManager shareSocketManager].socket on:@"onCsLeaveMeeting" callback:^(NSArray * _Nonnull lists, SocketAckEmitter * _Nonnull socketAckEmitter) {
        VoiceControlNoticeModel *noticeModel = [VoiceControlTool dataToNoticeModel:lists];
        VoiceControlUserModel *model = nil;
        if (noticeModel.data && [noticeModel.data isKindOfClass:[NSDictionary class]]) {
            model = [VoiceControlUserModel yy_modelWithJSON:noticeModel.data];
        }
        if (block) {
            block(model);
        }
    }];
}

+ (void)onRaiseHandsMicWithBlock:(void (^)(NSString *uid))block {
    [[VoiceSocketIOManager shareSocketManager].socket on:@"onCsRaiseHandsMic" callback:^(NSArray * _Nonnull lists, SocketAckEmitter * _Nonnull socketAckEmitter) {
        VoiceControlNoticeModel *noticeModel = [VoiceControlTool dataToNoticeModel:lists];
        NSString *uid = @"";
        if (noticeModel.data && [noticeModel.data isKindOfClass:[NSDictionary class]]) {
            uid = noticeModel.data[@"user_id"];
        }
        if (block) {
            block(uid);
        }
    }];
}

+ (void)onInviteMicWithBlock:(void (^)(NSString *uid))block {
    [[VoiceSocketIOManager shareSocketManager].socket on:@"onCsInviteMic" callback:^(NSArray * _Nonnull lists, SocketAckEmitter * _Nonnull socketAckEmitter) {
        VoiceControlNoticeModel *noticeModel = [VoiceControlTool dataToNoticeModel:lists];
        NSString *uid = @"";
        if (noticeModel.data && [noticeModel.data isKindOfClass:[NSDictionary class]]) {
            uid = noticeModel.data[@"user_id"];
        }
        if (block) {
            block(uid);
        }
    }];
}

+ (void)onMicOnWithBlock:(void (^)(VoiceControlUserModel *userModel))block {
    [[VoiceSocketIOManager shareSocketManager].socket on:@"onCsMicOn" callback:^(NSArray * _Nonnull lists, SocketAckEmitter * _Nonnull socketAckEmitter) {
        VoiceControlNoticeModel *noticeModel = [VoiceControlTool dataToNoticeModel:lists];
        VoiceControlUserModel *model = nil;
        if (noticeModel.data && [noticeModel.data isKindOfClass:[NSDictionary class]]) {
            model = [VoiceControlUserModel yy_modelWithJSON:noticeModel.data];
        }
        if (block) {
            block(model);
        }
    }];
}

+ (void)onMicOffWithBlock:(void (^)(NSString *uid))block {
    [[VoiceSocketIOManager shareSocketManager].socket on:@"onCsMicOff" callback:^(NSArray * _Nonnull lists, SocketAckEmitter * _Nonnull socketAckEmitter) {
        VoiceControlNoticeModel *noticeModel = [VoiceControlTool dataToNoticeModel:lists];
        NSString *uid = @"";
        if (noticeModel.data && [noticeModel.data isKindOfClass:[NSDictionary class]]) {
            uid = noticeModel.data[@"user_id"];
        }
        if (block) {
            block(uid);
        }
    }];
}

+ (void)onMuteMicWithBlock:(void (^)(NSString *uid))block {
    [[VoiceSocketIOManager shareSocketManager].socket on:@"onCsMuteMic" callback:^(NSArray * _Nonnull lists, SocketAckEmitter * _Nonnull socketAckEmitter) {
        VoiceControlNoticeModel *noticeModel = [VoiceControlTool dataToNoticeModel:lists];
        NSString *uid = @"";
        if (noticeModel.data && [noticeModel.data isKindOfClass:[NSDictionary class]]) {
            uid = noticeModel.data[@"user_id"];
        }
        if (block) {
            block(uid);
        }
    }];
}

+ (void)onUnmuteMic:(void (^)(NSString * _Nonnull uid))block {
    [[VoiceSocketIOManager shareSocketManager].socket on:@"onCsUnmuteMic" callback:^(NSArray * _Nonnull lists, SocketAckEmitter * _Nonnull socketAckEmitter) {
        VoiceControlNoticeModel *noticeModel = [VoiceControlTool dataToNoticeModel:lists];
        NSString *uid = @"";
        if (noticeModel.data && [noticeModel.data isKindOfClass:[NSDictionary class]]) {
            uid = noticeModel.data[@"user_id"];
        }
        if (block) {
            block(uid);
        }
    }];
}

+ (void)onMeetingEnd:(void (^)(BOOL result))block {
    [[VoiceSocketIOManager shareSocketManager].socket on:@"onCsMeetingEnd" callback:^(NSArray * _Nonnull lists, SocketAckEmitter * _Nonnull socketAckEmitter) {
        VoiceControlNoticeModel *noticeModel = [VoiceControlTool dataToNoticeModel:lists];
        NSString *uid = @"";
        if (noticeModel.data && [noticeModel.data isKindOfClass:[NSDictionary class]]) {
            uid = noticeModel.data[@"room_id"];
        }
        if (block) {
            block(uid);
        }
    }];
}

+ (void)onHostChange:(void (^)(NSString *formerHostID, VoiceControlUserModel *hostUser))block {
    [[VoiceSocketIOManager shareSocketManager].socket on:@"onCsHostChange" callback:^(NSArray * _Nonnull lists, SocketAckEmitter * _Nonnull socketAckEmitter) {
        NSString *forUid = @"";
        VoiceControlUserModel *model = nil;
        VoiceControlNoticeModel *noticeModel = [VoiceControlTool dataToNoticeModel:lists];
        if (noticeModel.data && [noticeModel.data isKindOfClass:[NSDictionary class]]) {
            forUid = noticeModel.data[@"former_host_id"];
            model = [VoiceControlUserModel yy_modelWithJSON:noticeModel.data[@"host_info"]];
        }
        if (block) {
            block(forUid, model);
        }
    }];
}

#pragma mark - App

+ (void)getAuditStateAppVersion:(NSString *)version block:(void (^)(MenuUpgradeModel *upgradeModel, VoiceControlAckModel *ackModel))block {
    NSDictionary *dic = @{@"device_type" : @"ios",
                          @"app_version" : version};
    
    OnAckCallback *callback = [[VoiceSocketIOManager shareSocketManager].socket emitWithAck:@"getAuditState"
                                                                                       with:@[dic]];
    [callback timingOutAfter:DefaultTimeout callback:^(NSArray * _Nonnull dataLists) {
        VoiceControlAckModel *ackModel = [VoiceControlTool dataToAckModel:dataLists];
        MenuUpgradeModel *model = [MenuUpgradeModel yy_modelWithJSON:ackModel.response];
        dispatch_async(dispatch_get_main_queue(), ^{
            if (block) {
                block(model, ackModel);
            }
        });
        NSLog(@"[%@]-getAuditState %@", [self class], dataLists);
    }];
}

+ (void)verifyLoginToken {
    NSDictionary *dic = [VoiceControlTool addToken:nil];
    
    OnAckCallback *callback = [[MeetingSocketIOManager shareSocketManager].socket emitWithAck:@"verifyLoginToken"
                                                                                       with:@[dic]];
    [callback timingOutAfter:DefaultTimeout callback:^(NSArray * _Nonnull dataLists) {
        [VoiceControlTool dataToAckModel:dataLists];
        NSLog(@"[%@]-verifyLoginToken %@", [self class], dataLists);
    }];
}

#pragma mark - User

+ (void)changeUserName:(BaseUserModel *)userModel block:(void (^)(VoiceControlAckModel *ackModel))block {
    NSDictionary *dic = @{@"user_name" : userModel.name};
    dic = [VoiceControlTool addToken:dic];
    
    OnAckCallback *callback = [[VoiceSocketIOManager shareSocketManager].socket emitWithAck:@"changeUserName"
                                                                                       with:@[dic]];
    [callback timingOutAfter:DefaultTimeout callback:^(NSArray * _Nonnull dataLists) {
        VoiceControlAckModel *ackModel = [VoiceControlTool dataToAckModel:dataLists];
        dispatch_async(dispatch_get_main_queue(), ^{
            if (block) {
                block(ackModel);
            }
        });
        NSLog(@"[%@]-getAuditState %@", [self class], dataLists);
    }];
}

#pragma mark - Login

+ (void)login:(NSString *)name block:(void (^)(BaseUserModel *userModel, VoiceControlAckModel *ackModel))block {
    NSDictionary *dic = @{@"user_name" : name};
    
    OnAckCallback *callback = [[VoiceSocketIOManager shareSocketManager].socket emitWithAck:@"passwordFreeLogin"
                                                                                       with:@[dic]];
    [callback timingOutAfter:DefaultTimeout callback:^(NSArray * _Nonnull dataLists) {
        VoiceControlAckModel *ackModel = [VoiceControlTool dataToAckModel:dataLists];
        BaseUserModel *model = [BaseUserModel yy_modelWithJSON:ackModel.response];
        if ([ackModel.response isKindOfClass:[NSDictionary class]]) {
            [MenuTokenCompoments updateToken:ackModel.response[@"login_token"]];
        }
        dispatch_async(dispatch_get_main_queue(), ^{
            if (block) {
                block(model, ackModel);
            }
        });
        NSLog(@"[%@]-passwordFreeLogin %@", [self class], dataLists);
    }];
}

@end
