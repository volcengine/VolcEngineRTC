//
//  MockDataCompoments.m
//  quickstart
//

#import "MockDataCompoments.h"
#import "SettingsService.h"

@interface MockDataCompoments ()

@property (nonatomic, copy) NSArray *bitRatelists;

@end

@implementation MockDataCompoments

- (instancetype)init {
    self = [super init];
    if (self) {
        NSString *plistPath = [[NSBundle mainBundle] pathForResource:@"mockData" ofType:@"plist"];
        NSDictionary *mockDataDic = [[NSDictionary alloc] initWithContentsOfFile:plistPath];
        
        _resolutionLists = [self resolutionListsWithMockData:mockDataDic];
        _bitRatelists = [self bitRateListsWithMockData:mockDataDic];
    }
    return self;
}

#pragma mark - Publish Action

- (NSRange)selectBitRateRangWithRow:(NSInteger)row {
    //根据分辨率选择对应的码率
    //Select the corresponding bit rate according to the resolution
    NSValue *value = self.bitRatelists[row];
    _bitRateRang = [value rangeValue];

    NSInteger bitRate = [SettingsService getKBitRate];
    if (bitRate < _bitRateRang.location) {
        bitRate = _bitRateRang.location;
    }
    if (bitRate > _bitRateRang.location + _bitRateRang.length) {
        bitRate = _bitRateRang.location + _bitRateRang.length;
    }
    [SettingsService setKBitRate:(int)bitRate];

    return _bitRateRang;
}

- (NSRange)selectScreenBitRateRangWithRow:(NSInteger)row isDefault:(BOOL)isDefault {
    //根据分辨率选择对应的码率
    //Select the corresponding bit rate according to the resolution
    NSValue *value = self.bitRatelists[row];
    _bitScreenRateRang = [value rangeValue];

    NSInteger bitRate = [SettingsService getKBitRate];
    if (bitRate < _bitScreenRateRang.location) {
        bitRate = _bitScreenRateRang.location;
    }
    if (bitRate > _bitScreenRateRang.location + _bitScreenRateRang.length) {
        bitRate = _bitScreenRateRang.location + _bitScreenRateRang.length;
    }
    if (!isDefault) {
        [SettingsService setScreenKBitRate:(int)bitRate];
    }

    return _bitScreenRateRang;
}

#pragma mark - Private Action

- (NSArray *)resolutionListsWithMockData:(NSDictionary *)mockDataDic {
    //通过plist配置文件解析分辨率数据
    //Analyze the resolution data through the plist configuration file
    NSMutableArray *mutableLists = [[NSMutableArray alloc] init];
    NSArray *resolutionLists = mockDataDic[@"ResolutionLists"];
    for (int i = 0; i < resolutionLists.count; i++) {
        NSDictionary *dic = resolutionLists[i];
        NSMutableArray *lists = [[NSMutableArray alloc] init];
        [lists addObject:dic[@"width"]];
        [lists addObject:dic[@"height"]];
        
        [mutableLists addObject:lists];
    }
    return [mutableLists copy];
}

- (NSArray *)bitRateListsWithMockData:(NSDictionary *)mockDataDic {
    //通过plist配置文件解析码率数据
    //Analyze the code rate data through the plist configuration file
    NSMutableArray *mutableLists = [[NSMutableArray alloc] init];
    NSArray *bitRatelists = mockDataDic[@"BitRatelists"];
    for (int i = 0; i < bitRatelists.count; i++) {
        NSDictionary *dic = bitRatelists[i];
        NSNumber *minValue = dic[@"min"];
        NSNumber *maxValue = dic[@"max"];
        NSValue *range = [NSValue valueWithRange:NSMakeRange([minValue integerValue], [maxValue integerValue] - [minValue integerValue])];
        [mutableLists addObject:range];
    }
    return [mutableLists copy];
}

- (NSArray *)frameRateLists {
    if (!_frameRateLists) {
        _frameRateLists = @[@(15),@(20),@(24)];
    }
    return _frameRateLists;
}

@end
