///
///  LoginViewController.h
///  RTCDemo


#import <Cocoa/Cocoa.h>

NS_ASSUME_NONNULL_BEGIN

@interface LoginViewController : NSViewController

@property (nonatomic, copy) void (^joinRoomBlock)(NSString *roomID, NSString *userID);

@end

NS_ASSUME_NONNULL_END
