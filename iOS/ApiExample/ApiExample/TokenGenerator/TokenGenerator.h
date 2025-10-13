//
//  TokenGenerator.h
//  ApiExample
//
//  Created by bytedance on 2023/10/7.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <VolcEngineRTC/VolcEngineRTC.h>


NS_ASSUME_NONNULL_BEGIN

@interface TokenGenerator : NSObject
+ (NSString *)tokenWithAppID:(NSString *)appId appKey:(NSString *)appKey roomId:(NSString *)roomId uid:(NSString *)userId;
@end

NS_ASSUME_NONNULL_END
