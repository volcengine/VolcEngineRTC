//
//  VoiceControlTool.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/17.
//

#import <Foundation/Foundation.h>
#import "VoiceControlAckModel.h"
#import "VoiceControlNoticeModel.h"

@interface VoiceControlTool : NSObject

+ (VoiceControlAckModel *)dataToAckModel:(NSArray *)dataList;

+ (VoiceControlNoticeModel *)dataToNoticeModel:(NSArray *)dataList;

+ (NSDictionary *)addToken:(NSDictionary *)dic;

@end
