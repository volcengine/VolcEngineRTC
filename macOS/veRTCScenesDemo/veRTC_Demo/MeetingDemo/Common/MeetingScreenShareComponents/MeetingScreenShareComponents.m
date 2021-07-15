//
//  MeetingScreenShareComponents.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/2.
//

#import "MeetingScreenShareComponents.h"

@interface MeetingScreenShareComponents ()

@end

@implementation MeetingScreenShareComponents

#pragma mark - Publish Action

- (NSArray<MeetingScreenShareModel *> *)screenCaptureSourcesWithThumbnailSize:(NSSize)thumbnailSize {
    NSArray *lists = [[MeetingRTCManager shareMeetingRTCManager] getScreenCaptureSourceList];
    NSMutableArray *modelLists = [[NSMutableArray alloc] init];
    NSInteger screentIndex = 0;
    for (int i = 0; i < lists.count; i++) {
        ByteRtcScreenCaptureSourceInfo *rtcSourceInfo = lists[i];
        
        MeetingScreenShareModel *model = [[MeetingScreenShareModel alloc] init];
        model.sourceName = rtcSourceInfo.sourceName;
        model.isScreen = (rtcSourceInfo.sourceType == ByteScreenCaptureSourceTypeScreen) ? YES : NO;
        if (model.isScreen) {
            screentIndex++;
            NSString *numStr = [[self class] chineseWithArabString:[NSString stringWithFormat:@"%ld",(long)(screentIndex)]];
            model.sourceName = [NSString stringWithFormat:@"桌面%@",numStr];
        }
        model.sourceType = rtcSourceInfo.sourceType;
        model.sourceId = (int)rtcSourceInfo.sourceId;
        [modelLists addObject:model];
    }
    return [modelLists copy];
}

#pragma mark - tool

+ (NSString *)chineseWithArabString:(NSString *)arabStr {
    NSArray *arab_numbers = @[@"1",@"2",@"3",@"4",@"5",@"6",@"7",@"8",@"9",@"0"];
    NSArray *chinese_strs = @[@"一",@"二",@"三",@"四",@"五",@"六",@"七",@"八",@"九",@"〇"];
    NSArray *digits = @[@"", @"十",@"百",@"千",@"万",@"十",@"百",@"千",@"亿",@"十",@"百",@"千",@"兆"];
    NSDictionary *tranDict = [NSDictionary dictionaryWithObjects:chinese_strs forKeys:arab_numbers];
    NSString *chineseStr = @"";
    NSMutableArray *sums = [NSMutableArray array];
    for (int i = 0; i < arabStr.length; i++) {
        NSString *subStr = [arabStr substringWithRange:NSMakeRange(i, 1)];
        NSString *a = [tranDict objectForKey:subStr];
        NSString *b = digits[arabStr.length - i - 1];
        NSString *sum = [a stringByAppendingString:b];
        if ([a isEqualToString:chinese_strs[9]]) {
            if ([b isEqualToString:digits[4]] || [b isEqualToString:digits[8]]) {
                sum = b;
                if ([[sums lastObject] isEqualToString:chinese_strs[9]]) {
                    [sums removeLastObject];
                }
            } else {
                sum = chinese_strs[9];
            }

            if ([[sums lastObject] isEqualToString:sum]) {
                continue;
            }
        }
        [sums addObject:sum];
    }
    chineseStr = [sums componentsJoinedByString:@""];

    return chineseStr;
}

#pragma mark - getter




@end
