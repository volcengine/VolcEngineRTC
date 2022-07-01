///
///  RoomViewController.h
///  advanced
///

#import <UIKit/UIKit.h>
#import "PreJoinSetting.h"


NS_ASSUME_NONNULL_BEGIN

@interface RoomViewController : UIViewController
@property (nonatomic, copy) NSString *roomID;
@property (nonatomic, copy) NSString *userID;
@property (nonatomic, strong) PreJoinSetting *preJoinSetting;
@end

NS_ASSUME_NONNULL_END
