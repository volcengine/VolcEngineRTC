//
//  RoomBottomBarModel.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/2.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, BottomBarStatus) {
    BottomBarStatusNone,
    BottomBarStatusMic,
    BottomBarStatusVideo,
    BottomBarStatusScreenShare,
    BottomBarStatusRecord,
    BottomBarStatusPeople,
    BottomBarStatusSeting,
    BottomBarStatusHangUp,
};

typedef NS_ENUM(NSInteger, RoomBottomBarStatus) {
    RoomBottomBarStatsuRoom,
    RoomBottomBarStatsuScreen,
};

NS_ASSUME_NONNULL_BEGIN

@interface RoomBottomBarModel : NSObject

@property (nonatomic, assign) BottomBarStatus status;

@end

NS_ASSUME_NONNULL_END
