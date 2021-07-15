//
//  AppDelegate.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/2.
//

#import "AppDelegate.h"

@interface AppDelegate ()

@end

@implementation AppDelegate

- (instancetype)init {
    self = [super init];
    if (self) {
        NSArray *apps = [NSRunningApplication runningApplicationsWithBundleIdentifier:[[NSBundle mainBundle] bundleIdentifier]];
        if ([apps count] > 1) {
            NSRunningApplication *curApp = [NSRunningApplication currentApplication];
            for (NSRunningApplication *app in apps) {
                if(app != curApp) {
                    [app activateWithOptions:NSApplicationActivateAllWindows | NSApplicationActivateIgnoringOtherApps];
                    break;
                }
            }
            [self showAlert];
            [NSApp terminate:nil];
            return nil;
        }
    }
    return self;
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    self.windowManager = [[WindowManager alloc] init];
    [self.windowManager start];
}

- (BOOL)applicationShouldHandleReopen:(NSApplication *)sender hasVisibleWindows:(BOOL)flag {
    return YES;
}

- (void)applicationWillTerminate:(NSNotification *)aNotification {
    
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender {
    
    return YES;
}

#pragma mark - Private Action

- (void)showAlert {
    NSAlert *alert = [NSAlert new];
    [alert addButtonWithTitle:@"确定"];
    [alert setMessageText:@"同时只能打开一个APP"];
    [alert setInformativeText:@"请关闭当前激活的APP，再重试。"];
    [alert setAlertStyle:NSWarningAlertStyle];
    [alert runModal];
}

@end
