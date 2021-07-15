//
//  ParticipantListsView.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/10.
//

#import "ParticipantListsView.h"
#import "ParticipantCell.h"
#import "ParticipantTableRowView.h"

@interface ParticipantListsView () <NSTableViewDelegate, NSTableViewDataSource>

@property (nonatomic, strong) NSScrollView *scrollView;
@property (nonatomic, strong) NSTableView *tableView;

@end

@implementation ParticipantListsView

- (instancetype)init {
    self = [super init];
    if (self) {
        [self addSubview:self.scrollView];
        [self.scrollView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.edges.equalTo(self);
        }];
        
        self.scrollView.contentView.documentView = self.tableView;
        [self.tableView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.top.left.right.mas_equalTo(self.scrollView);
        }];
    }
    return self;
}

- (void)setDataLists:(NSArray *)dataLists {
    _dataLists = dataLists;
    
    [self.tableView reloadData];
}


#pragma mark - Private Action

- (void)changeHost:(NSString *)uid {
    [MeetingControlCompoments changeHost:uid block:^(BOOL result, MeetingControlAckModel * _Nonnull model) {
        if (!model.result) {
            [[MeetingToastComponents shareMeetingToastComponents] showWithMessage:model.message];
        }
    }];
}

- (void)showAlert:(NSString *)uid name:(NSString *)name {
    NSString *message = [NSString stringWithFormat:@"是否将主持人移交给：%@", name];
    __weak __typeof(self) wself = self;
    [[MeetingAlertCompoments share] showWithTitle:message clickBlock:^(BOOL result) {
        if (result) {
            [wself changeHost:uid];
        }
    }];
}

#pragma mark - NSTableViewDataSource

- (NSView *)tableView:(NSTableView *)tableView viewForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row {
    ParticipantCell *cellView = [tableView makeViewWithIdentifier:@"ParticipantCellID" owner:nil];
    cellView.isLoginHost = self.isLoginHost;
    if (row < self.dataLists.count) {
        cellView.roomUserModel = self.dataLists[row];
    } else {
        cellView.roomUserModel = nil;
    }

    __weak __typeof(self) wself = self;
    cellView.clickChangeHost = ^(NSString *uid, NSString *name) {
        [wself showAlert:uid name:name];
    };
    cellView.moveTrackBlock = ^(NSString *uid) {
        [wself trackUid:uid];
    };
    return cellView;
    
}

- (NSTableRowView *)tableView:(NSTableView *)tableView rowViewForRow:(NSInteger)row {
    ParticipantTableRowView *rowView = [tableView makeViewWithIdentifier:@"ParticipantTableRowViewID" owner:self];
    return rowView;
}

- (NSInteger)numberOfRowsInTableView:(NSTableView *)tableView {
    return self.dataLists.count;
}

- (CGFloat)tableView:(NSTableView *)tableView heightOfRow:(NSInteger)row {
    return 48;
}

#pragma mark - Private Action

- (void)trackUid:(NSString *)uid {
    for (RoomUserModel *model in self.dataLists) {
        if ([model.uid isEqualToString:uid]) {
            model.isTrack = YES;
        } else {
            model.isTrack = NO;
        }
    }
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
        _tableView.backgroundColor = [NSColor colorFromHexString:@"#101319"];
        _tableView.selectionHighlightStyle = NSTableViewSelectionHighlightStyleNone;
        _tableView.delegate = self;
        _tableView.dataSource = self;
        
        NSNib *nib = [[NSNib alloc] initWithNibNamed:@"ParticipantCell" bundle:nil];
        [_tableView registerNib:nib forIdentifier:@"ParticipantCellID"];
        
        NSNib *rowNib = [[NSNib alloc] initWithNibNamed:@"ParticipantTableRowView" bundle:nil];
        [_tableView registerNib:rowNib forIdentifier:@"ParticipantTableRowViewID"];
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

@end
