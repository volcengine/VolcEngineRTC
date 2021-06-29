//
//  SystemAuthority.m
//  quickstart
//

#import "SystemAuthority.h"
#import <AVFoundation/AVFoundation.h>

@implementation SystemAuthority

+ (void)authorCamera:(void (^ __nullable)(BOOL granted))completion {
    dispatch_block_t workBlock;
    if (@available(macOS 10.14, *)) {
        AVAuthorizationStatus authStatus = [AVCaptureDevice authorizationStatusForMediaType:AVMediaTypeVideo];
        if(authStatus == AVAuthorizationStatusAuthorized) {
            workBlock = ^{
                if (completion) completion(YES);
            };
            // do your logic
        } else if(authStatus == AVAuthorizationStatusDenied || authStatus == AVAuthorizationStatusRestricted){
            workBlock = ^{
                if (completion) completion(NO);
            };
            // denied
        } else if(authStatus == AVAuthorizationStatusNotDetermined){
            // not determined?!
            [AVCaptureDevice requestAccessForMediaType:AVMediaTypeVideo completionHandler:^(BOOL granted) {
                if (completion) {
                    completion(granted);
                }
            }];
            return;
        } else {
            // impossible, unknown authorization status
            workBlock = ^{
                if (completion) completion(NO);
            };
        }
    } else {
        workBlock = ^{
            if (completion) completion(YES);
        };
    }
    dispatch_async(dispatch_get_main_queue(), workBlock);
}

+ (void)authorMicphone:(void (^ __nullable)(BOOL granted))completion {
    dispatch_block_t workBlock;
    if (@available(macOS 10.14, *)) {
        AVAuthorizationStatus authStatus = [AVCaptureDevice authorizationStatusForMediaType:AVMediaTypeAudio];
        if(authStatus == AVAuthorizationStatusAuthorized) {
            workBlock = ^{
                if (completion) completion(YES);
            };
            // do your logic
        } else if(authStatus == AVAuthorizationStatusDenied || authStatus == AVAuthorizationStatusRestricted){
            workBlock = ^{
                if (completion) completion(NO);
            };
            // denied
        } else if(authStatus == AVAuthorizationStatusNotDetermined){
            // not determined?!
            [AVCaptureDevice requestAccessForMediaType:AVMediaTypeAudio completionHandler:^(BOOL granted) {
                if (completion) {
                    completion(granted);
                }
            }];
            return;
        } else {
            // impossible, unknown authorization status
            workBlock = ^{
                if (completion) completion(NO);
            };
        }
    } else {
        workBlock = ^{
            if (completion) completion(YES);
        };
    }
    dispatch_async(dispatch_get_main_queue(), workBlock);
}


+ (BOOL)canRecordScreen {
    if (@available(macOS 10.15, *)) {
        CFArrayRef windowList = CGWindowListCopyWindowInfo(kCGWindowListOptionOnScreenOnly, kCGNullWindowID);
        NSUInteger numberOfWindows = CFArrayGetCount(windowList);
        NSUInteger numberOfWindowsWithName = 0;
        for (int idx = 0; idx < numberOfWindows; idx++) {
            NSDictionary *windowInfo = (NSDictionary *)CFArrayGetValueAtIndex(windowList, idx);
            NSString *windowName = windowInfo[(id)kCGWindowName];
            if (windowName) {
                numberOfWindowsWithName++;
            } else {
                //no kCGWindowName detected -> not enabled
                break; //breaking early, numberOfWindowsWithName not increased
            }

        }
        CFRelease(windowList);
        return numberOfWindows == numberOfWindowsWithName;
    } else {
        return YES;
    }
}
@end
