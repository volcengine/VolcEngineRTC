//
//  MeetingControlTool.m
//  SceneRTCDemo
//
//  Created by on 2021/3/17.
//

#import "MeetingControlTool.h"

@implementation MeetingControlTool

+ (NSString *)convertToJsonData:(NSDictionary *)dict {
    if (!dict) {
        return @"";
    }
    NSError *error;
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:dict options:NSJSONWritingPrettyPrinted error:&error];
    NSString *jsonString;
    if (!jsonData) {
        NSLog(@"%@", error);
    } else {
        jsonString = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
    }
    NSMutableString *mutStr = [NSMutableString stringWithString:jsonString];
    NSRange range = {0, jsonString.length};
    [mutStr replaceOccurrencesOfString:@" " withString:@"" options:NSLiteralSearch range:range];
    NSRange range2 = {0, mutStr.length};
    [mutStr replaceOccurrencesOfString:@"\n" withString:@"" options:NSLiteralSearch range:range2];
    return mutStr;
}

+ (MeetingControlAckModel *)dataToAckModel:(NSArray *)dataList {
    MeetingControlAckModel *model = nil;
    if (dataList && [dataList isKindOfClass:[NSArray class]] && dataList.count > 0) {
        model = [[MeetingControlAckModel alloc] init];
        NSDictionary *dic = dataList.firstObject;
        if (dic && [dic isKindOfClass:[NSDictionary class]] && dic.count > 0) {
            model = [[MeetingControlAckModel alloc] init];
            model.code = [dic[@"code"] integerValue];
            model.response = dic[@"response"];
            NSString *message = [MeetingControlTool messageToRequestCode:model.code];
            if (!message || ![message isKindOfClass:[NSString class]] || message.length <= 0) {
                message = dic[@"message"];
            }
            model.message = message;
        }
    }
    return model;
}

+ (NSString *)messageToRequestCode:(NSInteger)code {
    NSString *message = @"";
    switch (code) {
        case 406:
            message = @"会议房间已满员";
            break;
        case 412:
            message = @"屏幕共享发起失败，请提示前一位参会者结束共享";
            break;
        case 503:
            message = @"全体静音失败，请重试";
            break;
        case 504:
            message = @"移交主持人失败，请重试";
            break;
        case 702:
            message = @"服务端Token生成失败，请重试";
            break;
        default:
            break;
    }
    return message;
}

+ (MeetingControlNoticeModel *)dataToNoticeModel:(NSArray *)dataList {
    MeetingControlNoticeModel *model = nil;
    if (dataList && [dataList isKindOfClass:[NSArray class]] && dataList.count > 0) {
        NSDictionary *dic = dataList.firstObject;
        if (dic && [dic isKindOfClass:[NSDictionary class]] && dic.count > 0) {
            model = [[MeetingControlNoticeModel alloc] init];
            model.data = dic[@"data"];
        }
    }
    return model;
}


@end
