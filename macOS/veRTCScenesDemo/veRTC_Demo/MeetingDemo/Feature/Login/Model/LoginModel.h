//
//  LoginModel.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/15.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface LoginModel : NSObject

@property (nonatomic, copy) NSString *appid;

@property (nonatomic, copy) NSString *token;

@property (nonatomic, copy) NSString *uid;

@property (nonatomic, copy) NSString *name;

@property (nonatomic, copy) NSString *roomId;

@property (nonatomic, assign) BOOL isEnableVideo;

@property (nonatomic, assign) BOOL isEnableAudio;

@end

NS_ASSUME_NONNULL_END
