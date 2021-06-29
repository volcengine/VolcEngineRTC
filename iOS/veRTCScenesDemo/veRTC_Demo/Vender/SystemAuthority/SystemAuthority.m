//
//  SystemAuthority.m
//  quickstart
//

#import "SystemAuthority.h"
#import <AVFoundation/AVFoundation.h>
#import <UIKit/UIKit.h>

@implementation SystemAuthority

+ (void)authorizationStatusWithType:(AuthorizationType)type block:(void (^)(BOOL isAuthorize))block {
    AVAuthorizationStatus authStatus = [[self class] getAuthStatusWithType:type];
    if (authStatus == AVAuthorizationStatusNotDetermined) {
        [[AVAudioSession sharedInstance] requestRecordPermission:^(BOOL granted) {
          // CALL YOUR METHOD HERE - as this assumes being called only once from user interacting with permission alert!
          dispatch_async(dispatch_get_main_queue(), ^{
            if (block) {
                block(granted);
            }
          });
        }];
    } else if (authStatus == AVAuthorizationStatusRestricted ||
               authStatus == AVAuthorizationStatusDenied) {
        // unauthorized
        if (block) {
            block(NO);
        }
    } else if (authStatus == AVAuthorizationStatusAuthorized) {
        // authorized
        if (block) {
            block(YES);
        }
    } else {
        // unknown type
        if (block) {
            block(NO);
        }
    }
}

+ (void)autoJumpWithAuthorizationStatusWithType:(AuthorizationType)type {
    [[self class] authorizationStatusWithType:type block:^(BOOL isAuthorize) {
        if (!isAuthorize) {
            // jump to setting
            NSURL *url = [NSURL URLWithString:UIApplicationOpenSettingsURLString];
            if ([[UIApplication sharedApplication] canOpenURL:url]) {
                if (@available(iOS 10.0, *)) {
                    [[UIApplication sharedApplication] openURL:url options:@{} completionHandler:^(BOOL success) {
                        
                    }];
                } else {
                    [[UIApplication sharedApplication] openURL:url];
                }
            }
        }
    }];
}

#pragma mark - Private Action

+ (AVAuthorizationStatus)getAuthStatusWithType:(AuthorizationType)type {
    AVAuthorizationStatus authStatus = AVAuthorizationStatusNotDetermined;
    if (type == AuthorizationTypeAudio) {
        authStatus = [AVCaptureDevice authorizationStatusForMediaType:AVMediaTypeAudio];
    } else if (type == AuthorizationTypeCamera) {
        authStatus = [AVCaptureDevice authorizationStatusForMediaType:AVMediaTypeVideo];
    }
    return authStatus;
}

@end
