#import "MeetingNavViewController.h"
#import "RoomVideoSession.h"
#import "UserListCell.h"

NS_ASSUME_NONNULL_BEGIN

@interface UserListViewController : MeetingNavViewController

@property (nonatomic, assign) BOOL isLoginHost;

@property (nonatomic, strong) RoomVideoSession *localVideoSession;

- (void)updateUserMicStatus:(BOOL)isOpen uid:(NSString *)uid;

- (void)updateUserCameraStatus:(BOOL)isOpen uid:(NSString *)uid;

- (void)updateUserHostStatusWithUid:(NSString *)uid;

- (void)loadDataWithGetMeetingUserInfo:(BOOL)isAlert;

- (void)updateUserMicStatus:(NSDictionary<NSString *,NSNumber *> *)speakUid;

@end

NS_ASSUME_NONNULL_END
