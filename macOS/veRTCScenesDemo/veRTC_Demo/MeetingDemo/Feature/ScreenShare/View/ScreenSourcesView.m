//
//  ScreenSourcesView.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/3.
//

#import "ScreenSourcesView.h"
#import "CaptureSourceCollectionItem.h"

@interface ScreenSourcesView () <NSCollectionViewDelegate, NSCollectionViewDataSource, CaptureSourceCollectionItemDelegate>

@property (nonatomic, strong) NSLabel *titleLabel;
@property (nonatomic, strong) NSButton *cancelButton;

@property (nonatomic, strong) NSScrollView *scrollView;
@property (nonatomic, strong) NSClipView *clipView;
@property (nonatomic, strong) NSCollectionView *collectionView;

@property (nonatomic, strong) NSMutableArray<NSArray *> *sections;

@end

@implementation ScreenSourcesView

- (instancetype)init {
    self = [super init];
    if (self) {
        [self setBackgroundColorWithHexString:@"#1D2129"];
        self.wantsLayer = YES;
        self.layer.masksToBounds = YES;
        self.layer.cornerRadius = 2;
        
        self.clipView.documentView = self.collectionView;
        self.scrollView.contentView = self.clipView;
        [self addSubview:self.scrollView];
        [self.scrollView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.top.mas_equalTo(72);
            make.left.mas_equalTo(32);
            make.right.mas_equalTo(-12);
            make.bottom.equalTo(self);
        }];
        
        [self.collectionView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.right.top.equalTo(self.scrollView);
            make.left.equalTo(self.scrollView).offset(20);
        }];
        
        [self addSubview:self.titleLabel];
        [self.titleLabel mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.mas_equalTo(32);
            make.top.mas_equalTo(24);
        }];
        
        [self addSubview:self.cancelButton];
        [self.cancelButton mas_makeConstraints:^(MASConstraintMaker *make) {
            make.top.mas_equalTo(24);
            make.right.mas_equalTo(-32);
            make.height.width.mas_equalTo(20);
        }];
    }
    return self;
}

- (void)layout {
    [super layout];
    
    self.clipView.frame = self.bounds;
}

- (void)setLoginModel:(LoginModel *)loginModel {
    _loginModel = loginModel;
}

- (void)setRoomModel:(MeetingControlRoomModel *)roomModel {
    _roomModel = roomModel;
}

- (void)buttonAction {
    if (self.clickCancelBLock) {
        self.clickCancelBLock();
    }
}

- (void)updateThumbnailWithDataLists:(NSArray *)dataLists {
    NSArray *windowList = [dataLists filteredArrayUsingPredicate:[NSPredicate predicateWithBlock:^BOOL(id  _Nullable evaluatedObject, NSDictionary<NSString *,id> * _Nullable bindings) {
        MeetingScreenShareModel *model = (MeetingScreenShareModel *)evaluatedObject;
        return !model.isScreen;
    }]];
    NSArray *screenList = [dataLists filteredArrayUsingPredicate:[NSPredicate predicateWithBlock:^BOOL(id  _Nullable evaluatedObject, NSDictionary<NSString *,id> * _Nullable bindings) {
        MeetingScreenShareModel *model = (MeetingScreenShareModel *)evaluatedObject;
        return model.isScreen;
    }]];
    [self.sections addObject:screenList];
    [self.sections addObject:windowList];
    [self.collectionView reloadData];
}

#pragma mark - CaptureSourceCollectionItemDelegate

- (void)captureSourceCollectionItem:(CaptureSourceCollectionItem *)captureSourceCollectionItem didSelectItem:(MeetingScreenShareModel *)model {
    [self buttonAction];
}

#pragma mark - NSCollectionViewDataSource

- (NSInteger)numberOfSectionsInCollectionView:(NSCollectionView *)collectionView {
    return self.sections.count;
}

- (NSInteger)collectionView:(NSCollectionView *)collectionView numberOfItemsInSection:(NSInteger)section {
    return self.sections[section].count;
}

- (NSCollectionViewItem *)collectionView:(NSCollectionView *)collectionView itemForRepresentedObjectAtIndexPath:(NSIndexPath *)indexPath {
    CaptureSourceCollectionItem *item = [collectionView makeItemWithIdentifier:@"CaptureSourceCollectionItem" forIndexPath:indexPath];
    item.delegate = self;
    item.roomModel = self.roomModel;
    item.loginModel = self.loginModel;
    item.source = self.sections[indexPath.section][indexPath.item];
    return item;
}

- (void)collectionView:(NSCollectionView *)collectionView didSelectItemsAtIndexPaths:(NSSet<NSIndexPath *> *)indexPaths {

}

#pragma mark - NSTableViewDelegate

- (CGFloat)tableView:(NSTableView *)tableView heightOfRow:(NSInteger)row {
    return 150;
}

#pragma mark - getter

- (NSButton *)cancelButton {
    if (!_cancelButton) {
        _cancelButton = [[NSButton alloc] init];
        [_cancelButton setImage:[NSImage imageNamed:@"meeting_partner_cancel"]];
        [_cancelButton setBackgroundColor:[NSColor clearColor]];
        [_cancelButton setTarget:self];
        [_cancelButton setAction:@selector(buttonAction)];
    }
    return _cancelButton;
}

- (NSCollectionView *)collectionView {
    if (!_collectionView) {
        _collectionView = [[NSCollectionView alloc] init];
        [_collectionView registerClass:[CaptureSourceCollectionItem class] forItemWithIdentifier:@"CaptureSourceCollectionItem"];
        _collectionView.delegate = self;
        _collectionView.dataSource = self;
        [_collectionView setBackgroundColor:[NSColor clearColor]];
        _collectionView.backgroundColors = @[[NSColor clearColor]];
        _collectionView.enclosingScrollView.drawsBackground = NO;
        
        NSCollectionViewFlowLayout *layout = [[NSCollectionViewFlowLayout alloc] init];
        layout.itemSize = NSMakeSize(168, 98 + 30);
        layout.sectionInset = NSEdgeInsetsMake(0, 0, 24, 20);
        layout.minimumInteritemSpacing = 12;
        layout.minimumLineSpacing = 24;
        if (@available(macOS 10.12, *)) {
            layout.sectionHeadersPinToVisibleBounds = YES;
        }
        _collectionView.collectionViewLayout = layout;
    }
    return _collectionView;
}

- (NSMutableArray *)sections {
    if (!_sections) {
        _sections = [[NSMutableArray alloc] init];
    }
    return _sections;
}

- (NSScrollView *)scrollView {
    if (!_scrollView) {
        _scrollView = [[NSScrollView alloc] init];
    }
    return _scrollView;
}

- (NSClipView *)clipView {
    if (!_clipView) {
        _clipView = [[NSClipView alloc] init];
    }
    return _clipView;
}

- (NSLabel *)titleLabel {
    if (!_titleLabel) {
        _titleLabel = [[NSLabel alloc] init];
        _titleLabel.textColor = [NSColor colorFromHexString:@"#FFFFFF"];
        _titleLabel.font = [NSFont systemFontOfSize:16 weight:NSFontWeightMedium];
        _titleLabel.text = @"选择共享内容";
    }
    return _titleLabel;
}

@end
