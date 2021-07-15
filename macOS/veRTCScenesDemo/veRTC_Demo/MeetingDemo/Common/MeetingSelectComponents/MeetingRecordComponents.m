//
//  MeetingRecordComponents.m
//  veRTC_Demo
//
//  Created by  on 2021/6/11.
//

#import "MeetingRecordComponents.h"
#import "NSSelectPopBox.h"

@interface MeetingRecordComponents () <NSSelectPopBoxDelegate, NSSelectPopBoxDataSource>

@property (nonatomic, strong) NSSelectPopBox *selectPopBox;

@end

@implementation MeetingRecordComponents

@synthesize stringValue = _stringValue;

- (instancetype)init {
    self = [super init];
    if (self) {
        [self setBackgroundColor:[NSColor colorFromHexString:@"#F2F3F8"]];
        
        [self addSubview:self.selectPopBox];
        [self.selectPopBox mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.mas_equalTo(12);
            make.right.mas_equalTo(-12);
            make.top.mas_equalTo(6);
            make.bottom.mas_equalTo(-6);
        }];
    }
    return self;
}

- (void)setIsDelete:(BOOL)isDelete {
    _isDelete = isDelete;
    
    self.selectPopBox.isDelete = isDelete;
}

- (void)setDataLists:(NSArray<NSString *> *)dataLists {
    _dataLists = dataLists;
    
    [self.selectPopBox reloadData];
}

- (void)setStringValue:(NSString *)stringValue {
    if (!stringValue) {
        stringValue = @"";
    }
    _stringValue = stringValue;
    self.selectPopBox.stringValue = stringValue;
}

- (NSString *)stringValue {
    return self.selectPopBox.stringValue;
}

#pragma mark - Publish Action

#pragma mark - NSComboBoxDataSource

- (NSInteger)selectPopBox:(NSSelectPopBox *)selectPopBox numberOfItemsInComboBox:(BOOL)isResult {
    return self.dataLists.count;
}

- (nullable id)selectPopBox:(NSSelectPopBox *)selectPopBox objectValueForItemAtIndex:(NSInteger)index {
    NSString *str = self.dataLists[index];
    return str;
}

#pragma mark - NSComboBoxDelegate

- (void)selectPopBox:(NSSelectPopBox *)selectPopBox boxSelectionDidChange:(nonnull NSString *)str {
    if (self.clickBlock) {
        self.clickBlock(str);
    }
}

- (void)selectPopBox:(NSSelectPopBox *)selectPopBox boxSelectionDidDelete:(nonnull NSString *)str {
    if (self.deleteBlock) {
        self.deleteBlock(str);
    }
}

#pragma mark - getter

- (NSSelectPopBox *)selectPopBox {
    if (!_selectPopBox) {
        _selectPopBox = [[NSSelectPopBox alloc] init];
        _selectPopBox.delegate = self;
        _selectPopBox.dataSource = self;
    }
    return _selectPopBox;
}

@end
