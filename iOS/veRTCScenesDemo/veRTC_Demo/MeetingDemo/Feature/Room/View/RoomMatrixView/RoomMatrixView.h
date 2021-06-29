#import <UIKit/UIKit.h>
#import "RoomVideoSession.h"

@interface RoomMatrixView : UIView

- (void)bindVideoSessions:(NSArray<RoomVideoSession *> *)videoSessions;

@end
