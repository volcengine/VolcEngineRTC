//
//  MeetingSelectComponents.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/9.
//

#import "MeetingSelectComponents.h"
#import "BaseComboBox.h"

@interface MeetingSelectComponents () <NSComboBoxDataSource, NSComboBoxDelegate>

@property (nonatomic, strong) BaseComboBox *comboBox;

@end

@implementation MeetingSelectComponents
@synthesize stringValue = _stringValue;

- (instancetype)init {
    self = [super init];
    if (self) {
        [self setBackgroundColor:[NSColor colorFromHexString:@"#F2F3F8"]];
        
        [self addSubview:self.comboBox];
        [self.comboBox mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.mas_equalTo(12);
            make.right.mas_equalTo(-12);
            make.top.mas_equalTo(6);
            make.bottom.mas_equalTo(-6);
        }];
    }
    return self;
}

- (void)setDataLists:(NSArray<NSString *> *)dataLists {
    _dataLists = dataLists;
    
    [self.comboBox reloadData];
}

- (void)setStringValue:(NSString *)stringValue {
    if (!stringValue) {
        stringValue = @"";
    }
    _stringValue = stringValue;
    self.comboBox.stringValue = stringValue;
}

- (NSString *)stringValue {
    return self.comboBox.stringValue;
}

#pragma mark - Publish Action

#pragma mark - NSComboBoxDataSource

- (NSInteger)numberOfItemsInComboBox:(NSComboBox *)comboBox {
    return self.dataLists.count;
}

- (nullable id)comboBox:(NSComboBox *)comboBox objectValueForItemAtIndex:(NSInteger)index {
    NSString *str = self.dataLists[index];
    return str;
}

#pragma mark - NSComboBoxDelegate

- (void)comboBoxSelectionDidChange:(NSNotification *)notification {
    NSComboBox *comboBox = (NSComboBox *)(notification.object);
    comboBox.stringValue = self.dataLists[comboBox.indexOfSelectedItem];;
    if (self.clickBlock) {
        self.clickBlock(comboBox.stringValue);
    }
}

#pragma mark - getter

- (BaseComboBox *)comboBox {
    if (!_comboBox) {
        _comboBox = [[BaseComboBox alloc] init];
        _comboBox.textColor = [NSColor colorFromHexString:@"#4F4F4F"];
        _comboBox.fontSize = 12;
        _comboBox.editable = NO;
        _comboBox.usesDataSource = YES;
        _comboBox.selectable = NO;
        _comboBox.buttonBordered = NO;
        _comboBox.delegate = self;
        _comboBox.dataSource = self;
        _comboBox.alignment = NSTextAlignmentLeft;
        _comboBox.font = [NSFont fontWithName:_comboBox.font.fontName size:12];
    }
    return _comboBox;
}

@end
