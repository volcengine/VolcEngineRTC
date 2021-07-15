//
//  RoomBottomBarView.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/9.
//

#import <Cocoa/Cocoa.h>
#import "RoomBottomBarModel.h"

@class RoomBottomBarView;

@protocol RoomBottomBarViewDelegate <NSObject>

- (void)roomBottomBarView:(RoomBottomBarView *)roomBottomBarView didSelectItemsAtButton:(RoomBottomBarModel *)roomBottomBarModel button:(TrackButton *)button; 

@end

@interface RoomBottomBarView : NSView

@property (nonatomic, assign) BOOL isDragged;

@property (nonatomic, weak) id<RoomBottomBarViewDelegate> delegate;

- (instancetype)initWithStatus:(RoomBottomBarStatus)status;

- (void)updateButtonStatus:(BottomBarStatus)status close:(BOOL)isClose;

//Simulate clicking the button
- (void)clickButtonStatus:(BottomBarStatus)status;

@end
