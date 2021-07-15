//
//  CaptureSourceCollectionItem.h
//  TXLiteAVMacDemo
//
//  Created by  on 2021/3/4.
//

#import <Cocoa/Cocoa.h>
#import "MeetingScreenShareModel.h"
@class CaptureSourceCollectionItem;

NS_ASSUME_NONNULL_BEGIN

@protocol CaptureSourceCollectionItemDelegate <NSObject>

- (void)captureSourceCollectionItem:(CaptureSourceCollectionItem *)captureSourceCollectionItem didSelectItem:(MeetingScreenShareModel *)model;

@end

@interface CaptureSourceCollectionItem : NSCollectionViewItem

@property (strong, nonatomic) MeetingScreenShareModel *source;

@property (nonatomic, strong) MeetingControlRoomModel *roomModel;

@property (nonatomic, strong) LoginModel *loginModel;

@property (nonatomic, weak) id<CaptureSourceCollectionItemDelegate> delegate;

@end

NS_ASSUME_NONNULL_END
