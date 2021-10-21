#import <Cocoa/Cocoa.h>

NS_ASSUME_NONNULL_BEGIN

@interface LoginView : NSView

@property (nonatomic, copy) void (^clickBlock)(NSString *roomID, NSString *userID);

@end

NS_ASSUME_NONNULL_END
