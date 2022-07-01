//
//  PreJoinNetResultViewController.h
//  Advanced
//
//  Created by bytedance on 2022/3/16.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface PreJoinNetResultViewController : UIViewController

@property (nonatomic, assign) BOOL isUplink;
@property (nonatomic, assign) BOOL isDownlink;
@property (nonatomic, assign) NSInteger uplinkBandwidth;
@property (nonatomic, assign) NSInteger downlinkBandwidth;

@end

NS_ASSUME_NONNULL_END
