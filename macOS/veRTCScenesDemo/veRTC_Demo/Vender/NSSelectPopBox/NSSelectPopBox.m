//
//  NSSelectPopBox.m
//  veRTC_Demo
//
//  Created by  on 2021/6/11.
//

#import "NSSelectPopBox.h"
#import "NSSelectPopTableRowView.h"
#import "NSSelectPopCell.h"

@interface NSSelectPopBox () <NSTableViewDelegate, NSTableViewDataSource>

@property (nonatomic, strong) NSButton *enterButton;
@property (nonatomic, strong) NSLabel *enterLabel;

@property (nonatomic, strong) NSButton *maskButton;
@property (nonatomic, strong) NSView *popView;
@property (nonatomic, strong) NSScrollView *scrollView;
@property (nonatomic, strong) NSTableView *tableView;

@end

@implementation NSSelectPopBox


- (instancetype)init {
    self = [super init];
    if (self) {
        [self setBackgroundColorWithHexString:@"#F2F3F8"];
        
        [self addSubview:self.enterLabel];
        [self.enterLabel mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.mas_equalTo(0);
            make.centerY.equalTo(self);
        }];
        
        [self addSubview:self.enterButton];
        [self.enterButton mas_makeConstraints:^(MASConstraintMaker *make) {
            make.edges.equalTo(self);
        }];
    }
    return self;
}

- (void)enterButtonButtonAction {
    AppDelegate *appDelegate = (AppDelegate *)[NSApplication sharedApplication].delegate;
    NSWindow *window = appDelegate.windowManager.currentWindowController.window;

    CGRect rect = [window.contentView convertRect:self.frame fromView:self];
    
    [window.contentView addSubview:self.maskButton];
    [self.maskButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(window.contentView);
    }];
    
    [self.maskButton addSubview:self.popView];
    [self.popView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(320, 224));
        make.top.mas_equalTo(rect.origin.y + rect.size.height + 12 + 4);
        make.left.mas_equalTo(rect.origin.x - 24);
    }];
    
    [self.popView addSubview:self.scrollView];
    [self.scrollView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(self.popView);
    }];
    
    self.scrollView.contentView.documentView = self.tableView;
    [self.tableView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.left.right.mas_equalTo(self.scrollView);
    }];
}


- (void)maskButtonAction:(NSButton *)sender {
    [sender removeAllSubView];
    [sender removeFromSuperview];
    sender = nil;
}

#pragma mark - Publish Action

- (void)reloadData {
    [self.tableView reloadData];
}

- (void)setStringValue:(NSString *)stringValue {
    _stringValue = stringValue;
    
    self.enterLabel.text = stringValue;
}

#pragma mark - NSTableViewDataSource

- (NSView *)tableView:(NSTableView *)tableView viewForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row {
    return nil;
}

- (NSTableRowView *)tableView:(NSTableView *)tableView rowViewForRow:(NSInteger)row {
    NSString *message = @"";
    if ([self.dataSource respondsToSelector:@selector(selectPopBox:objectValueForItemAtIndex:)]) {
        message = [self.dataSource selectPopBox:self objectValueForItemAtIndex:row];
    }
    
    NSSelectPopTableRowView *rowView = [tableView makeViewWithIdentifier:@"NSSelectPopTableRowViewID" owner:self];
    NSSelectPopCell *cellView = [tableView makeViewWithIdentifier:@"NSSelectPopCellID" owner:nil];
    cellView.isDelete = self.isDelete;
    cellView.messageStr = message;
    __weak __typeof(self) wself = self;
    cellView.clickBlock = ^(NSString * _Nonnull str) {
        if ([wself.delegate respondsToSelector:@selector(selectPopBox:boxSelectionDidChange:)]) {
            [wself.delegate selectPopBox:self boxSelectionDidChange:str];
        }
        [wself maskButtonAction:wself.maskButton];
    };
    cellView.clickDeleteBlock = ^(NSString * _Nonnull str) {
        if ([wself.delegate respondsToSelector:@selector(selectPopBox:boxSelectionDidDelete:)]) {
            [wself.delegate selectPopBox:self boxSelectionDidDelete:str];
        }
    };
    [rowView removeAllSubView];
    [rowView addSubview:cellView];
    return rowView;
}

- (NSInteger)numberOfRowsInTableView:(NSTableView *)tableView {
    NSInteger num = 0;
    if ([self.dataSource respondsToSelector:@selector(selectPopBox:numberOfItemsInComboBox:)]) {
        num = [self.dataSource selectPopBox:self numberOfItemsInComboBox:YES];
    }
    return num;
}

- (CGFloat)tableView:(NSTableView *)tableView heightOfRow:(NSInteger)row {
    return 36;
}

#pragma mark - getter

- (NSTableView *)tableView {
    if (!_tableView) {
        _tableView = [[NSTableView alloc] init];
        if (@available(macOS 11.0, *)) {
            _tableView.style = NSTableViewStylePlain;
        }
        NSTableColumn *tableColumn = [[NSTableColumn alloc] init];
        [_tableView addTableColumn:tableColumn];
        [_tableView setHeaderView:nil];
        _tableView.backgroundColor = [NSColor colorFromHexString:@"#FFFFFF"];
        _tableView.selectionHighlightStyle = NSTableViewSelectionHighlightStyleNone;
        _tableView.delegate = self;
        _tableView.dataSource = self;
        
        NSNib *nib = [[NSNib alloc] initWithNibNamed:@"NSSelectPopCell" bundle:nil];
        [_tableView registerNib:nib forIdentifier:@"NSSelectPopCellID"];
        
        NSNib *rowNib = [[NSNib alloc] initWithNibNamed:@"NSSelectPopTableRowView" bundle:nil];
        [_tableView registerNib:rowNib forIdentifier:@"NSSelectPopTableRowViewID"];
    }
    return _tableView;
}

- (NSScrollView *)scrollView {
    if (!_scrollView) {
        _scrollView = [[NSScrollView alloc] init];
        _scrollView.backgroundColor = [NSColor clearColor];
        [_scrollView.contentView setBackgroundColor:[NSColor clearColor]];
        _scrollView.hasVerticalRuler = YES;
    }
    return _scrollView;
}

- (NSButton *)enterButton {
    if (!_enterButton) {
        _enterButton = [[NSButton alloc] init];
        [_enterButton setTarget:self];
        [_enterButton setAction:@selector(enterButtonButtonAction)];
    }
    return _enterButton;
}

- (NSButton *)maskButton {
    if (!_maskButton) {
        _maskButton = [[NSButton alloc] init];
        [_maskButton setBackgroundColor:[NSColor clearColor]];
        
        [_maskButton setTarget:self];
        [_maskButton setAction:@selector(maskButtonAction:)];
    }
    return _maskButton;
}

- (NSView *)popView {
    if (!_popView) {
        _popView = [[NSView alloc] init];
        
        _popView.wantsLayer = YES;
        _popView.layer.borderWidth = 2;
        _popView.layer.borderColor = [NSColor colorFromHexString:@"#E5E6EB"].CGColor;
        _popView.layer.cornerRadius = 2;
        _popView.layer.masksToBounds = YES;
    }
    return _popView;
}

- (NSLabel *)enterLabel {
    if (!_enterLabel) {
        _enterLabel = [[NSLabel alloc] init];
        _enterLabel.textColor = [NSColor colorFromHexString:@"#86909C"];
        _enterLabel.font = [NSFont systemFontOfSize:12 weight:NSFontWeightRegular];
        _enterLabel.enabled = NO;
    }
    return _enterLabel;
}

@end
