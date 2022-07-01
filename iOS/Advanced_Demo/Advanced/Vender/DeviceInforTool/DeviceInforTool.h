//
//  DeviceInforTool.h
//  quickstart
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface DeviceInforTool : NSObject

/*
 * Get whether it is an iPad device
 * @return YES: It means that the current device is iPad;
            NO: Indicates that the current device is not an iPad
 */
+ (BOOL)isIpad;

/*
 * Get the height of the status bar
 * @return The height of the current device status bar
 */
+ (CGFloat)getStatusBarHight;

/*
 * Get the height of the bottom safe area
 * @return The height of the safe area at the bottom of the current device
 */
+ (CGFloat)getVirtualHomeHeight;

/*
 * Get the value of safe area
 * @return The the safe area
 */
+ (UIEdgeInsets)getSafeAreaInsets;

+ (UIViewController *)topViewController;

@end

NS_ASSUME_NONNULL_END
