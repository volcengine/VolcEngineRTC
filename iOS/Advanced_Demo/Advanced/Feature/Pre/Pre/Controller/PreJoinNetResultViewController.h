//
//  PreJoinNetResultViewController.h
//  Advanced
//
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
