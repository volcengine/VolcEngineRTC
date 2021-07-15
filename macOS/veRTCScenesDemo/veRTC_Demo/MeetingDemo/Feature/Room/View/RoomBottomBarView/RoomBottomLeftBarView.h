//
//  RoomBottomLeftBarView.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/2.
//

#import <Cocoa/Cocoa.h>
#import "RoomBottomBarModel.h"
@class RoomBottomLeftBarView;

NS_ASSUME_NONNULL_BEGIN

@protocol RoomBottomLeftBarViewDelegate <NSObject>

- (void)roomBottomLeftBarView:(RoomBottomLeftBarView *)roomBottomLeftBarView didSelectItemsAtButton:(RoomBottomBarModel *)roomBottomBarModel button:(TrackButton *)button;

@end

@interface RoomBottomLeftBarView : NSView

@property (nonatomic, weak) id<RoomBottomLeftBarViewDelegate> delegate;

- (instancetype)initWithStatus:(RoomBottomBarStatus)status;

- (void)updateButtonStatus:(BottomBarStatus)status close:(BOOL)isClose;

//Simulate clicking the button
- (void)clickButtonStatus:(BottomBarStatus)status;

@end

NS_ASSUME_NONNULL_END
