//
//  MeetingSocketIOManager.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/16.
//

#import "MeetingSocketIOManager.h"
#import <CommonCrypto/CommonCrypto.h>
#import "GCDTimer.h"

//会控状态的链接，并不是socket的链接状态
//The link of the conference control state is not the link state of the socket
typedef NS_ENUM(NSInteger, MeetingConnectStatus) {
    MeetingConnectStatusNone = 0,
    MeetingConnectStatusSuccess,
    MeetingConnectStatusFailure,
    MeetingConnectStatusIng,
};

@interface MeetingSocketIOManager ()

@property (nonatomic, strong) SocketManager *manager;

@property (nonatomic, assign) MeetingConnectStatus connectStatus;

@property (nonatomic, strong) GCDTimer *timer;

@property (nonatomic, assign) NSInteger secondValue;

@end

@implementation MeetingSocketIOManager

+ (MeetingSocketIOManager *_Nullable)shareSocketManager {
    static MeetingSocketIOManager *shareSocketManager = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        shareSocketManager = [[self alloc] init];
    });
    return shareSocketManager;
}

- (instancetype)init {
    self = [super init];
    if (self) {
        self.connectStatus = MeetingConnectStatusNone;
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
        self.connectStatus = MeetingConnectStatusNone;
        [[NSNotificationCenter defaultCenter] postNotificationName:NotificationMeetingControlChange object:@"exit"];
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
        [self socketOnSuccess];
        dispatch_async(dispatch_get_main_queue(), ^{
            if (block) {
                block(YES);
            }
        });
    }];
    
    [self.socket on:@"error"
           callback:^(NSArray *data, SocketAckEmitter *ack) {
        [self socketOnFailure];
        dispatch_async(dispatch_get_main_queue(), ^{
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
                if (self.connectStatus != MeetingConnectStatusNone) {
                    //禁止第一次请求
                    self.connectStatus = MeetingConnectStatusFailure;
                }
            }
        } else {
            
        }
    }];
    
    [self.socket connect];
}

- (void)setConnectStatus:(MeetingConnectStatus)connectStatus {
    _connectStatus = connectStatus;
    if (connectStatus == MeetingConnectStatusFailure) {
        [self.timer resume];
    } else {
        self.secondValue = 0;
        [self.timer suspend];
    }
}

- (void)connect {
    [self.socket connect];
}

- (void)disConnect {
    [self.timer suspend];
    [self.manager disconnect];
}

#pragma mark - Private Action

- (void)socketOnSuccess {
    if (self.connectStatus == MeetingConnectStatusFailure ||
        self.connectStatus == MeetingConnectStatusIng) {
        self.connectStatus = MeetingConnectStatusIng;
        __weak __typeof(self) wself = self;
        [MeetingControlCompoments reconnectWithBlock:^(MeetingControlAckModel * _Nonnull model) {
            NSString *type = @"";
            if (model.result) {
                type = @"resume";
                wself.connectStatus = MeetingConnectStatusSuccess;
            } else if (model.code == 404 || model.code == 422) {
                type = @"exit";
                wself.connectStatus = MeetingConnectStatusNone;
            } else {
                
            }
            if (type.length > 0) {
                [[NSNotificationCenter defaultCenter] postNotificationName:NotificationMeetingControlChange object:type];
                [wself showSocketConnectStatus:YES];
            }
        }];
    } else {
        self.connectStatus = MeetingConnectStatusSuccess;
        [self showSocketConnectStatus:YES];
    }
}

- (void)socketOnFailure {
    [self showSocketConnectStatus:NO];
}

- (void)showSocketConnectStatus:(BOOL)isConnect {
    dispatch_async(dispatch_get_main_queue(), ^{
        UIViewController *topVC = [DeviceInforTool topViewController];
        if ([NSStringFromClass([topVC class]) isEqualToString:@"MeetingLoginViewController"]) {
            //login show alert
            if (!isConnect) {
                [[NSNotificationCenter defaultCenter] postNotificationName:NotificationSocketStatusChange object:@"faile"];
            }
            return;
        }
        if (isConnect) {
            [[MeetingToastComponents shareMeetingToastComponents] dismiss];
        } else {
            [[NSNotificationCenter defaultCenter] postNotificationName:NotificationSocketStatusChange object:@"faile"];
        }
    });
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
