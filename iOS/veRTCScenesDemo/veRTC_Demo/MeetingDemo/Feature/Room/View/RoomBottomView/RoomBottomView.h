//
//  RoomBottomView.h
//  quickstart
//
//  Created by on 2021/3/23.
//  Copyright © 2021. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "RoomItemButton.h"
@class RoomBottomView;

typedef NS_ENUM(NSInteger, RoomBottomStatus) {
    RoomBottomStatusMic = 0,
    RoomBottomStatusCamera,
    RoomBottomStatusScreen,
    RoomBottomStatusPar,
    RoomBottomStatusMore,
    RoomBottomStatusAudio,
    RoomBottomStatusSet,
    RoomBottomStatusTest,
    RoomBottomStatusRecord,
};

@protocol RoomBottomViewDelegate <NSObject>

- (void)roomBottomView:(RoomBottomView *_Nonnull)roomBottomView itemButton:(RoomItemButton *_Nullable)itemButton didSelectStatus:(RoomBottomStatus)status;

@end

NS_ASSUME_NONNULL_BEGIN

@interface RoomBottomView : UIView

@property (nonatomic, weak) id<RoomBottomViewDelegate> delegate;

- (void)updateButtonStatus:(RoomBottomStatus)status close:(BOOL)isClose;

- (ButtonStatus)getButtonStatus:(RoomBottomStatus)status;

- (void)dismissMoreView;

@end

NS_ASSUME_NONNULL_END
