//
//  MeetingNavViewController.h
//  quickstart
//
//  Created by  on 2021/3/22.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface MeetingNavViewController : UIViewController

@property (nonatomic, copy) NSString *navTitle;

@property (nonatomic, strong) UIView *navView;

@end

NS_ASSUME_NONNULL_END
