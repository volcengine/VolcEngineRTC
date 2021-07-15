#import "RoomMatrixView.h"
#import "UserListViewController.h"
#import <UIKit/UIKit.h>
#import "RoomVideoSession.h"
#import "RoomBottomView.h"

typedef NS_ENUM(NSInteger, RoomModeStatus) {
    //Jiugongge
    RoomModeStatusGallery,
    //Speaker
    RoomModeStatusSpaker,
};

@interface RoomViewController : UIViewController

@property (nonatomic, strong) RoomBottomView *bottomView;

@property (nonatomic, strong) RoomVideoSession *localVideoSession;

@property (nonatomic, strong) MeetingControlRoomModel *currentRoomModel;

//只做添加，删除，更新，不能直接使用。
@property (nonatomic, strong) NSMutableArray<RoomVideoSession *> *userDataPool;

@property (nonatomic, weak) RoomVideoSession *maxVolumeUserModel;

@property (nonatomic, copy) void (^closeRoomBlock)(BOOL isEnableAudio, BOOL isEnableVideo);

- (instancetype)initWithVideoSession:(RoomVideoSession *)loginModel
                           userLists:(NSArray<RoomVideoSession *> *)userLists;

- (void)hangUp;

- (void)updateRenderModeViewWithCameraStatus:(NSString *)uid enableCamera:(BOOL)isEnable;

- (void)updateRenderModeViewWithMicStatus:(NSString *)uid enableMic:(BOOL)isEnable;

- (void)updateRenderModeViewWithHost:(NSString *)hostID;

- (void)updateRenderModeViewWithScreenStatus:(NSString *)uid enableScreen:(BOOL)isShare;

- (void)addUser:(RoomVideoSession *)roomUserModel;

- (void)removeUser:(NSString *)uid;

- (void)updateRecordTipStatusWithHidden:(BOOL)isHidden;

- (void)updateModeWithStatus:(RoomModeStatus)roomModeStatus;

- (void)restoreScreenOrientation;

@end
