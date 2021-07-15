#import "MeetingNavViewController.h"
#import "RoomVideoSession.h"
#import "UserListCell.h"

NS_ASSUME_NONNULL_BEGIN

@interface UserListViewController : MeetingNavViewController

@property (nonatomic, assign) BOOL isLoginHost;

@property (nonatomic, strong) RoomVideoSession *localVideoSession;

@property (nonatomic, strong) NSMutableArray<RoomVideoSession *> *videoSessions;

@end

NS_ASSUME_NONNULL_END
