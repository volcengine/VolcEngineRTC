//
//  MeetingControlTool.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/17.
//

#import <Foundation/Foundation.h>
#import "MeetingControlAckModel.h"
#import "MeetingControlNoticeModel.h"

@interface MeetingControlTool : NSObject

+ (MeetingControlAckModel *)dataToAckModel:(NSArray *)dataList;

+ (MeetingControlNoticeModel *)dataToNoticeModel:(NSArray *)dataList;

+ (NSDictionary *)addToken:(NSDictionary *)dic;

@end
