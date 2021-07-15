//
//  SetingView.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/8.
//

#import <Cocoa/Cocoa.h>
#import "SetingDeviceModel.h"
#import "MeetingControlRecordModel.h"
@class SetingView;

NS_ASSUME_NONNULL_BEGIN

@protocol SetingViewDelegate <NSObject>

- (void)setingView:(SetingView *)setingView cancelAction:(BOOL)isCancel;

- (void)setingView:(SetingView *)setingView confirmAction:(BOOL)isConfirm;

- (void)setingView:(SetingView *)setingView changeParam:(SetingModel *)setingModel;

@end

@interface SetingView : NSView

@property (nonatomic, weak) id<SetingViewDelegate> delegate;

@property (nonatomic, strong) SetingModel *setingModel;

@property (nonatomic, copy) NSArray<SetingDeviceModel *> *micInputDeviceLists;

@property (nonatomic, copy) NSArray<SetingDeviceModel *> *cameraInputDeviceLists;

@property (nonatomic, copy) NSArray<MeetingControlRecordModel *> *historyVideoRecordLists;

@property (nonatomic, copy) NSArray<MeetingControlRecordModel *> *historyHostVideoRecordLists;

@end

NS_ASSUME_NONNULL_END
