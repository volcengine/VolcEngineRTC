//
//  PhoneLoginViewController.h
//  veRTC_Demo
//
//  Created by  on 2021/6/7.
//

#import <Cocoa/Cocoa.h>

NS_ASSUME_NONNULL_BEGIN

@interface PhoneLoginViewController : NSViewController

@property (nonatomic, copy) void (^loginBlock)(void);

@end

NS_ASSUME_NONNULL_END
