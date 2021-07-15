//
//  VoiceSocketIOManager.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/16.
//

#import "VoiceSocketIOManager.h"
#import <CommonCrypto/CommonCrypto.h>
#import "GCDTimer.h"

@interface VoiceSocketIOManager ()

@property (nonatomic, strong) SocketManager *manager;

@property (nonatomic, strong) GCDTimer *timer;

@property (nonatomic, assign) NSInteger secondValue;

@end

@implementation VoiceSocketIOManager

+ (VoiceSocketIOManager *_Nullable)shareSocketManager {
    static VoiceSocketIOManager *shareSocketManager = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        shareSocketManager = [[self alloc] init];
    });
    return shareSocketManager;
}

- (instancetype)init {
    self = [super init];
    if (self) {
        self.connectStatus = VoiceConnectStatusNone;
        __weak __typeof(self) wself = self;
        [self.timer startTimerWithSpace:1 block:^(BOOL result) {
            [wself timerMethod];
        }];
        [self.timer suspend];
    }
    return self;
}

- (void)timerMethod {
    self.secondValue++;
    if (self.secondValue > 60) {
        self.secondValue = 0;
        self.connectStatus = VoiceConnectStatusNone;
        NSMutableDictionary *dic = [[NSMutableDictionary alloc] init];
        [dic setValue:@"exit" forKey:@"type"];
        [[NSNotificationCenter defaultCenter] postNotificationName:NotificationVoiceControlChange object:[dic copy]];
    }
}


#pragma mark - Publish Action

- (void)connectWithSdkVersion:(NSString *)sdkVersion block:(void (^)(BOOL relust))block {
    NSString *urlStr = @"wss://rtcio.bytedance.com";
    NSURL *url = [[NSURL alloc] initWithString:urlStr];
    
    NSString *deviceId = [self getDeviceId];
    NSString *uaStr = [NSString stringWithFormat:@"ios-%@", sdkVersion];
    NSMutableDictionary *dic = [[NSMutableDictionary alloc] init];
    [dic setValue:[self getWisd] forKey:@"wsid"];
    [dic setValue:@"veRTCDemox" forKey:@"appid"];
    [dic setValue:uaStr forKey:@"ua"];
    [dic setValue:deviceId forKey:@"did"];
    [dic setValue:@"websocket" forKey:@"transport"];

    self.manager = [[SocketManager alloc] initWithSocketURL:url
                                                     config:@{@"log" : @NO,
                                                              @"path" : @"/vc_control",
                                                              @"forcePolling" : @NO,
                                                              @"forceWebsockets" : @YES,
                                                              @"secure" : @YES,
                                                              @"forceNew" : @YES,
                                                              @"reconnectWait" : @1,
                                                              @"connectParams" : dic}];
    self.socket = self.manager.defaultSocket;
    [self.socket on:@"connect"
           callback:^(NSArray *data, SocketAckEmitter *ack) {
        dispatch_async(dispatch_get_main_queue(), ^{
            [self socketOnSuccess];
            if (block) {
                block(YES);
            }
        });
    }];
    
    [self.socket on:@"error"
           callback:^(NSArray *data, SocketAckEmitter *ack) {
        dispatch_async(dispatch_get_main_queue(), ^{
            [self socketOnFailure];
            if (block) {
                block(NO);
            }
        });
    }];
    
    [self.socket onAny:^(SocketAnyEvent * _Nonnull anyEvent) {
        if ([anyEvent.event isEqualToString:@"statusChange"]) {
            NSString *status = [NSString stringWithFormat:@"%@",anyEvent.items.firstObject];
            if (status && [status isKindOfClass:[NSString class]] && status.length > 0 &&
                ![status isEqualToString:@"connected"]) {
                if (self.connectStatus != VoiceConnectStatusNone) {
                    //禁止第一次请求
                    self.connectStatus = VoiceConnectStatusFailure;
                }
            }
        } else {
            
        }
    }];
    
    [self.socket connect];
}

- (void)setConnectStatus:(VoiceConnectStatus)connectStatus {
    _connectStatus = connectStatus;
    if (connectStatus == VoiceConnectStatusFailure) {
        [self.timer resume];
    } else {
        self.secondValue = 0;
        [self.timer suspend];
    }
}

- (void)disConnect {
    [self.timer suspend];
    [self.manager disconnect];
}

#pragma mark - Private Action

- (void)socketOnSuccess {
    if (self.connectStatus == VoiceConnectStatusFailure ||
        self.connectStatus == VoiceConnectStatusIng) {
        self.connectStatus = VoiceConnectStatusIng;
        __weak __typeof(self) wself = self;
        [VoiceControlCompoments reconnectWithBlock:^(VoiceControlRoomModel * _Nonnull roomModel, NSArray * _Nonnull users, VoiceControlAckModel * _Nonnull model) {
            NSString *type = @"";
            if (model.result) {
                type = @"resume";
                wself.connectStatus = VoiceConnectStatusSuccess;
            } else if (model.code == 404 || model.code == 422) {
                type = @"exit";
                wself.connectStatus = VoiceConnectStatusNone;
            } else {

            }
            if (NOEmptyStr(type) && roomModel && users) {
                NSMutableDictionary *dic = [[NSMutableDictionary alloc] init];
                [dic setValue:type forKey:@"type"];
                [dic setValue:roomModel forKey:@"roomModel"];
                [dic setValue:users forKey:@"users"];
                [[NSNotificationCenter defaultCenter] postNotificationName:NotificationVoiceControlChange object:[dic copy]];
            }
            [wself dismissToast];
        }];
    } else {
        self.connectStatus = VoiceConnectStatusSuccess;
        [self dismissToast];
    }
}

- (void)dismissToast {
    [[MeetingToastComponents shareMeetingToastComponents] dismiss];
}

- (void)socketOnFailure {
    UIViewController *windowVC = [DeviceInforTool topViewController];
    [[MeetingToastComponents shareMeetingToastComponents] showWithMessage:@"网络链接已断开，请检查设置" view:windowVC.view keep:YES block:^(BOOL result) {
        
    }];
}

#pragma mark - tool

- (NSString *)getWisd {
    NSString *timeStr = [NSString stringWithFormat:@"%.0f", ([[NSDate date] timeIntervalSince1970] * 1000)];
    NSString *arcStr = [NSString stringWithFormat:@"%ld", (long)arc4random()%10000];
    return [NSString stringWithFormat:@"%@%@", timeStr, arcStr];
}

- (NSString *)getDeviceId {
    NSString *wisd = [self getWisd];
    NSString *deviceId = [[NSUserDefaults standardUserDefaults] objectForKey:@"deviceId_key"];
    if (!deviceId || ![deviceId isKindOfClass:[NSString class]] || deviceId.length <= 0) {
        deviceId = [self MD5ForLower16Bate:wisd];
    }
    [[NSUserDefaults standardUserDefaults] setValue:deviceId forKey:@"deviceId_key"];
    [[NSUserDefaults standardUserDefaults] synchronize];
    return deviceId;
}

- (NSString *)MD5ForLower16Bate:(NSString *)str {
    NSString *md5Str = [self MD5ForLower32Bate:str];
    NSString *string;
    for (int i = 0; i < 24; i++) {
        string = [md5Str substringWithRange:NSMakeRange(8, 16)];
    }
    return string;
}

- (NSString *)MD5ForLower32Bate:(NSString *)str {
    const char *input = [str UTF8String];
    unsigned char result[CC_MD5_DIGEST_LENGTH];
    CC_MD5(input, (CC_LONG)strlen(input), result);
    NSMutableString *digest = [NSMutableString stringWithCapacity:CC_MD5_DIGEST_LENGTH * 2];
    for (NSInteger i = 0; i < CC_MD5_DIGEST_LENGTH; i++) {
        [digest appendFormat:@"%02x", result[i]];
    }
    return digest;
}

- (GCDTimer *)timer {
    if (!_timer) {
        _timer = [[GCDTimer alloc] init];
    }
    return _timer;
}

@end
