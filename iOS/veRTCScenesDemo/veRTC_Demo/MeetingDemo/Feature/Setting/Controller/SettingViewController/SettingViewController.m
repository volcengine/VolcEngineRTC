#import "MockDataCompoments.h"
#import "SettingsRightLabelCell.h"
#import "SettingsService.h"
#import "SettingsSwitchCell.h"
#import "SettingViewController.h"
#import "MeetingPickerCompoments.h"
#import "SettingsSliderView.h"
#import "HistoryViewController.h"

static NSString *const kSettingsBaseCellIdentifier = @"kSettingsBaseCellIdentifier";
static NSString *const kSettingsRightLabelCellIdentifier = @"kSettingsRightLabelCellIdentifier";
static NSString *const kSettingsSwitchCellIdentifier = @"kSettingsSwitchCellIdentifier";

typedef NS_ENUM(NSInteger, SettingsGroupType) {
    SettingsGroupTypeResolution,        // Resolution configuration
    SettingsGroupTypeFrameRate,         // Frame rate configuration
    SettingsGroupTypeBitRate,           // Bit rate configuration
    SettingsGroupTypeScreenResolution,  // Screen Resolution configuration
    SettingsGroupTypeScreenFrameRate,   // Screen Frame rate configuration
    SettingsGroupTypeScreenBitRate,     // Screen Bit rate configuration
    SettingsGroupTypeShowVideoParam,    // View real-time parameter configuration
    SettingsGroupTypeHistory,           // Historical meeting
    SettingsGroupTypeSelfHistory,       // Self Historical meeting
};

@interface SettingViewController () <UITableViewDelegate, UITableViewDataSource>
@property (nonatomic, strong) UITableView *settingsTableView;
@property (nonatomic, strong) NSArray *groupTypes;
@property (nonatomic, strong) MockDataCompoments *localDataModel;

@property (nonatomic, strong) MeetingPickerCompoments *resolutionPicker;
@property (nonatomic, strong) MeetingPickerCompoments *frameRatePicker;

@property (nonatomic, copy) NSArray *currentResolutionItem;
@property (nonatomic, strong) NSNumber *currentFrameRate;
@property (nonatomic, strong) NSNumber *currentBitRate;

@property (nonatomic, copy) NSArray *currentScreenResolutionItem;
@property (nonatomic, strong) NSNumber *currentScreenFrameRate;
@property (nonatomic, strong) NSNumber *currentScreenBitRate;

@property (nonatomic, assign) BOOL isShowVideoParam;

@end

@implementation SettingViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor clearColor];
    self.groupTypes = @[@"分辨率", @"帧率", @"码率",
                        @"屏幕共享分辨率", @"屏幕共享帧率", @"屏幕共享码率",
                        @"实时视频参数", @"查看历史会议", @"我的云录制"];

    [self createUIComponents];
    [self defaultSelectBitRateRang];
    [self defaultSelectScreenBitRateRang];
    [self.settingsTableView reloadData];
    
    self.currentResolutionItem = [SettingsService getResolutionArray];
    self.currentFrameRate = @([SettingsService getFrameRate]);
    self.currentBitRate = @([SettingsService getKBitRate]);
    self.currentScreenResolutionItem = [SettingsService getScreenResolutionArray];
    self.currentScreenFrameRate = @([SettingsService getScreenFrameRate]);
    self.currentScreenBitRate = @([SettingsService getScreenKBitRate]);
    self.isShowVideoParam = [SettingsService getOpenParam];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];

    self.navTitle = @"会议设置";
}

- (void)createUIComponents {
    [self.view addSubview:self.settingsTableView];
    [self.settingsTableView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self.navView.mas_bottom);
        make.left.right.bottom.equalTo(self.view);
    }];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [UITableViewCell new];
    switch (indexPath.row) {
        case SettingsGroupTypeResolution: {
            cell = [tableView dequeueReusableCellWithIdentifier:kSettingsRightLabelCellIdentifier forIndexPath:indexPath];
            [(SettingsRightLabelCell *)cell settingsLabel].text = self.groupTypes[indexPath.row];
            [(SettingsRightLabelCell *)cell settingsRightLabel].text = [NSString stringWithFormat:@"%d*%d", (int)[SettingsService getResolution].width, (int)[SettingsService getResolution].height];
        } break;
        case SettingsGroupTypeFrameRate: {
            cell = [tableView dequeueReusableCellWithIdentifier:kSettingsRightLabelCellIdentifier forIndexPath:indexPath];
            [(SettingsRightLabelCell *)cell settingsLabel].text = self.groupTypes[indexPath.row];
            [(SettingsRightLabelCell *)cell settingsRightLabel].text = [NSString stringWithFormat:@"%dfps", [SettingsService getFrameRate]];
        } break;
        case SettingsGroupTypeBitRate: {
            cell = [tableView dequeueReusableCellWithIdentifier:kSettingsRightLabelCellIdentifier forIndexPath:indexPath];
            [(SettingsRightLabelCell *)cell settingsLabel].text = self.groupTypes[indexPath.row];
            [(SettingsRightLabelCell *)cell settingsRightLabel].text = [NSString stringWithFormat:@"%dkbps", [SettingsService getKBitRate]];
        } break;
            
        case SettingsGroupTypeScreenResolution: {
            cell = [tableView dequeueReusableCellWithIdentifier:kSettingsRightLabelCellIdentifier forIndexPath:indexPath];
            [(SettingsRightLabelCell *)cell settingsLabel].text = self.groupTypes[indexPath.row];
            [(SettingsRightLabelCell *)cell settingsRightLabel].text = [NSString stringWithFormat:@"%d*%d", (int)[SettingsService getScreenResolution].width, (int)[SettingsService getScreenResolution].height];
        } break;
        case SettingsGroupTypeScreenFrameRate: {
            cell = [tableView dequeueReusableCellWithIdentifier:kSettingsRightLabelCellIdentifier forIndexPath:indexPath];
            [(SettingsRightLabelCell *)cell settingsLabel].text = self.groupTypes[indexPath.row];
            [(SettingsRightLabelCell *)cell settingsRightLabel].text = [NSString stringWithFormat:@"%dfps", [SettingsService getScreenFrameRate]];
        } break;
        case SettingsGroupTypeScreenBitRate: {
            cell = [tableView dequeueReusableCellWithIdentifier:kSettingsRightLabelCellIdentifier forIndexPath:indexPath];
            [(SettingsRightLabelCell *)cell settingsLabel].text = self.groupTypes[indexPath.row];
            [(SettingsRightLabelCell *)cell settingsRightLabel].text = [NSString stringWithFormat:@"%dkbps", [SettingsService getScreenKBitRate]];
        } break;
            
        case SettingsGroupTypeShowVideoParam: {
            cell = [tableView dequeueReusableCellWithIdentifier:kSettingsSwitchCellIdentifier forIndexPath:indexPath];
            [(SettingsRightLabelCell *)cell settingsLabel].text = self.groupTypes[indexPath.row];
            [(SettingsSwitchCell *)cell setSwitchOn:self.isShowVideoParam];
            __weak typeof(self) weakSelf = self;
            [(SettingsSwitchCell *)cell switchValueChangeCallback:^(BOOL on) {
                [SettingsService setOpenParam:on];
              if (weakSelf.switchValueChangeBlock) {
                  weakSelf.switchValueChangeBlock(on);
              }
            }];
        } break;
        case SettingsGroupTypeHistory: {
            cell = [tableView dequeueReusableCellWithIdentifier:kSettingsRightLabelCellIdentifier forIndexPath:indexPath];
            [(SettingsRightLabelCell *)cell settingsLabel].text = self.groupTypes[indexPath.row];
        } break;
        case SettingsGroupTypeSelfHistory: {
            cell = [tableView dequeueReusableCellWithIdentifier:kSettingsRightLabelCellIdentifier forIndexPath:indexPath];
            [(SettingsRightLabelCell *)cell settingsLabel].text = self.groupTypes[indexPath.row];
        } break;
        default:
            break;
    }
    if (cell) {
        cell.selectionStyle = UITableViewCellSelectionStyleNone;
    }
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [tableView deselectRowAtIndexPath:indexPath animated:NO];
    switch (indexPath.row) {
        case SettingsGroupTypeResolution: {
            [self.resolutionPicker show:self.localDataModel.resolutionLists
                             selectItem:self.currentResolutionItem];
            __weak __typeof(self) wself = self;
            self.resolutionPicker.clickDismissBlock = ^(BOOL isCancel, id selectItem, NSInteger row) {
                if (!isCancel) {
                    wself.currentResolutionItem = selectItem;
                    [SettingsService setResolutions:selectItem];
                    [wself.localDataModel selectBitRateRangWithRow:row];
                    [wself.settingsTableView reloadData];
                }
                wself.resolutionPicker = nil;
            };
        } break;
        case SettingsGroupTypeFrameRate: {
            [self.frameRatePicker show:self.localDataModel.frameRateLists
                             selectItem:self.currentFrameRate];
            __weak __typeof(self) wself = self;
            self.frameRatePicker.clickDismissBlock = ^(BOOL isCancel, id selectItem, NSInteger row) {
                if (!isCancel) {
                    wself.currentFrameRate = selectItem;
                    int frameRate = ((NSNumber *)selectItem).intValue;
                    [SettingsService setFrameRate:frameRate];
                    [wself.settingsTableView reloadData];
                }
                wself.frameRatePicker = nil;
            };
        } break;
        case SettingsGroupTypeBitRate: {
            __block SettingsSliderView *view = [[SettingsSliderView alloc] init];
            NSRange bitRateRang = self.localDataModel.bitRateRang;
            [view show:bitRateRang.location
              maxValue:(bitRateRang.location + bitRateRang.length)
                 value:[SettingsService getKBitRate]];
            [self.view addSubview:view];
            [view mas_makeConstraints:^(MASConstraintMaker *make) {
                make.edges.equalTo(self.view);
            }];
            __weak __typeof(self) wself = self;
            view.clickDismissBlock = ^(BOOL isCancel, id  _Nonnull selectItem) {
                if (!isCancel) {
                    NSNumber *valueNumber = (NSNumber *)selectItem;
                    wself.currentBitRate = valueNumber;
                    [SettingsService setKBitRate:valueNumber.intValue];
                    [wself.settingsTableView reloadData];
                }
                view = nil;
            };
        } break;
            
        case SettingsGroupTypeScreenResolution: {
            [self.resolutionPicker show:self.localDataModel.resolutionLists
                             selectItem:self.currentScreenResolutionItem];
            __weak __typeof(self) wself = self;
            self.resolutionPicker.clickDismissBlock = ^(BOOL isCancel, id selectItem, NSInteger row) {
                if (!isCancel) {
                    wself.currentScreenResolutionItem = selectItem;
                    [SettingsService setScreenResolutions:selectItem];
                    [wself.localDataModel selectScreenBitRateRangWithRow:row isDefault:NO];
                    [wself.settingsTableView reloadData];
                }
                wself.resolutionPicker = nil;
            };
        } break;
        case SettingsGroupTypeScreenFrameRate: {
            [self.frameRatePicker show:self.localDataModel.frameRateLists
                             selectItem:self.currentScreenFrameRate];
            __weak __typeof(self) wself = self;
            self.frameRatePicker.clickDismissBlock = ^(BOOL isCancel, id selectItem, NSInteger row) {
                if (!isCancel) {
                    wself.currentScreenFrameRate = selectItem;
                    int frameRate = ((NSNumber *)selectItem).intValue;
                    [SettingsService setScreenFrameRate:frameRate];
                    [wself.settingsTableView reloadData];
                }
                wself.frameRatePicker = nil;
            };
        } break;
        case SettingsGroupTypeScreenBitRate: {
            __block SettingsSliderView *view = [[SettingsSliderView alloc] init];
            NSRange bitRateRang = self.localDataModel.bitScreenRateRang;
            [view show:bitRateRang.location
              maxValue:(bitRateRang.location + bitRateRang.length)
                 value:[SettingsService getScreenKBitRate]];
            [self.view addSubview:view];
            [view mas_makeConstraints:^(MASConstraintMaker *make) {
                make.edges.equalTo(self.view);
            }];
            __weak __typeof(self) wself = self;
            view.clickDismissBlock = ^(BOOL isCancel, id  _Nonnull selectItem) {
                if (!isCancel) {
                    NSNumber *valueNumber = (NSNumber *)selectItem;
                    wself.currentScreenBitRate = valueNumber;
                    [SettingsService setScreenKBitRate:valueNumber.intValue];
                    [wself.settingsTableView reloadData];
                }
                view = nil;
            };
        } break;
            
            
        case SettingsGroupTypeHistory: {
            HistoryViewController *next = [[HistoryViewController alloc] init];
            next.isDelete = NO;
            [self.navigationController pushViewController:next animated:YES];
        } break;
        case SettingsGroupTypeSelfHistory: {
            HistoryViewController *next = [[HistoryViewController alloc] init];
            next.isDelete = YES;
            [self.navigationController pushViewController:next animated:YES];
        } break;
        default:
            break;
    }
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return 119/2;
}

#pragma mark - UITableViewDataSource

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.groupTypes.count;
}

#pragma mark - Private Action

- (void)defaultSelectBitRateRang {
    CGSize resolution = [SettingsService getResolution];
    NSInteger defaultRow = 0;
    NSString *resolutionString = [NSString stringWithFormat:@"%ld*%ld", (long)resolution.width, (long)resolution.height];
    for (int i = 0; i < self.localDataModel.resolutionLists.count; i++) {
        NSArray *resolutions = self.localDataModel.resolutionLists[i];
        NSString *titleString = [NSString stringWithFormat:@"%@*%@", resolutions[0], resolutions[1]];
        if ([titleString isEqualToString:resolutionString]) {
            defaultRow = i;
            break;
        }
    }

    [self.localDataModel selectBitRateRangWithRow:defaultRow];
}

- (void)defaultSelectScreenBitRateRang {
    CGSize resolution = [SettingsService getScreenResolution];
    NSInteger defaultRow = 0;
    NSString *resolutionString = [NSString stringWithFormat:@"%ld*%ld", (long)resolution.width, (long)resolution.height];
    for (int i = 0; i < self.localDataModel.resolutionLists.count; i++) {
        NSArray *resolutions = self.localDataModel.resolutionLists[i];
        NSString *titleString = [NSString stringWithFormat:@"%@*%@", resolutions[0], resolutions[1]];
        if ([titleString isEqualToString:resolutionString]) {
            defaultRow = i;
            break;
        }
    }

    [self.localDataModel selectScreenBitRateRangWithRow:defaultRow isDefault:YES];
}

#pragma mark - getter

- (UITableView *)settingsTableView {
    if (!_settingsTableView) {
        _settingsTableView = [[UITableView alloc] init];
        _settingsTableView.separatorStyle = UITableViewCellSeparatorStyleNone;
        _settingsTableView.delegate = self;
        _settingsTableView.dataSource = self;
        [_settingsTableView registerClass:SettingsRightLabelCell.class forCellReuseIdentifier:kSettingsRightLabelCellIdentifier];
        [_settingsTableView registerClass:SettingsSwitchCell.class forCellReuseIdentifier:kSettingsSwitchCellIdentifier];
        _settingsTableView.backgroundColor = [UIColor colorFromHexString:@"#1D2129"];
    }
    return _settingsTableView;
}

- (MockDataCompoments *)localDataModel {
    if (!_localDataModel) {
        _localDataModel = [[MockDataCompoments alloc] init];
    }
    return _localDataModel;
}

- (MeetingPickerCompoments *)resolutionPicker {
    if (!_resolutionPicker) {
        _resolutionPicker = [[MeetingPickerCompoments alloc] initWithHeight:566/2 superView:self.view];
        _resolutionPicker.titleStr = @"分辨率";
    }
    return _resolutionPicker;
}

- (MeetingPickerCompoments *)frameRatePicker {
    if (!_frameRatePicker) {
        _frameRatePicker = [[MeetingPickerCompoments alloc] initWithHeight:195 superView:self.view];
        _frameRatePicker.titleStr = @"帧率";
    }
    return _frameRatePicker;
}

#pragma mark - tool

@end
