//
//  ParamView.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/14.
//

#import <Cocoa/Cocoa.h>
#import "ParamModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface ParamView : NSView

@property (nonatomic, strong) ParamModel *paramModel;

@end

NS_ASSUME_NONNULL_END
