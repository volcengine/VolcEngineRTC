//
//  SettingView.m
//  Advanced
//
//

#import "SettingView.h"

@interface SettingView () <UITableViewDelegate, UITableViewDataSource>
@property (nonatomic, strong) UILabel *titleLabel;
@property (nonatomic, strong) UITableView *tableView;
@end

@implementation SettingView

- (instancetype)initWithFrame:(CGRect)frame {
    if (self = [super initWithFrame:frame]) {
        [self addSubview:self.titleLabel];
        [self.titleLabel mas_makeConstraints:^(MASConstraintMaker *make) {
          make.top.equalTo(self);
          make.left.mas_equalTo(10);
          make.right.mas_equalTo(-10);
        }];

        [self addSubview:self.tableView];
        [self.tableView mas_makeConstraints:^(MASConstraintMaker *make) {
          make.top.equalTo(self.titleLabel.mas_bottom).offset(10);
          make.left.right.bottom.equalTo(self);
        }];
    }
    return self;
}

- (void)setTitle:(NSString *)title {
    _title = [title copy];

    self.titleLabel.text = title;
}

- (void)setDataArray:(NSArray *)dataArray {
    _dataArray = [dataArray copy];

    [self.tableView reloadData];
}

- (void)reloadData {
    [self.tableView reloadData];
}

#pragma mark - tableView delegate

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.dataArray.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    NSString *identifier = @"SettingTableViewCell_Identifier";
    SettingTableViewCell *cell = [self.tableView dequeueReusableCellWithIdentifier:identifier];
    if (cell == nil) {
        cell = [[SettingTableViewCell alloc] initWithStyle:UITableViewCellStyleValue1 reuseIdentifier:identifier];
    }
    SettingBaseModel *model = self.dataArray[indexPath.row];
    cell.model = model;
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    SettingTableViewCell *cell = [self.tableView cellForRowAtIndexPath:indexPath];

    if (cell.model.cellType == SettingTableViewCellType_OptionArray) {
        SettingOptionArrayModel *optionModel = (SettingOptionArrayModel *)cell.model;

        [self showActionSheetWithOptionModel:optionModel cellView:cell];
    } else if (cell.model.cellType == SettingTableViewCellType_Button) {
        SettingButtonModel *model = (SettingButtonModel *)cell.model;
        if (model.clickBlock) {
            model.clickBlock();
        }
    } else if (cell.model.cellType == SettingTableViewCellType_TextField) {
        [self showActionTextFieldWithModel:(SettingTextFieldModel *)cell.model];
    }
}

- (void)showActionTextFieldWithModel:(SettingTextFieldModel *)model {
    UIAlertController *alertController = [UIAlertController alertControllerWithTitle:model.alertTitle message:model.alertMessage preferredStyle:UIAlertControllerStyleAlert];
    for (int i = 0; i < model.placeholders.count; i++) {
        [alertController addTextFieldWithConfigurationHandler:^(UITextField *_Nonnull textField) {
          textField.text = model.describe;
          textField.placeholder = model.placeholders[i];
          textField.keyboardType = UIKeyboardTypeDefault;
        }];
    }

    __weak __typeof(self) wself = self;
    UIAlertAction *okAction = [UIAlertAction actionWithTitle:@"确定"
                                                       style:UIAlertActionStyleDefault
                                                     handler:^(UIAlertAction *action) {
                                                       for (int i = 0; i < model.placeholders.count; i++) {
                                                           UITextField *textField = alertController.textFields[i];
                                                           if (model.inputBlock) {
                                                               model.inputBlock(i, textField.text);
                                                           }
                                                       }
                                                       [wself.tableView reloadData];
                                                     }];

    UIAlertAction *cancelAction = [UIAlertAction actionWithTitle:@"取消" style:UIAlertActionStyleCancel handler:nil];

    [alertController addAction:okAction];
    [alertController addAction:cancelAction];

    UIViewController *currentVC = [UIApplication sharedApplication].keyWindow.rootViewController;
    if ([currentVC isKindOfClass:[UINavigationController class]]) {
        UINavigationController *navVC = (UINavigationController *)currentVC;
        UIViewController *topVC = navVC.visibleViewController;
        [topVC presentViewController:alertController animated:YES completion:nil];
    } else {
        [currentVC presentViewController:alertController animated:YES completion:nil];
    }
}

- (void)showActionSheetWithOptionModel:(SettingOptionArrayModel *)optionModel cellView:(SettingTableViewCell *)cellView {
    NSString *titleStr = (optionModel.describe.length > 0) ? optionModel.describe : optionModel.title;
    UIAlertController *alerVC = [UIAlertController alertControllerWithTitle:titleStr message:@"" preferredStyle:UIAlertControllerStyleActionSheet];

    __weak typeof(self) weakSelf = self;

    for (int i = 0; i < optionModel.optionArray.count; i++) {
        NSString *title = optionModel.optionArray[i];

        UIAlertAction *alertAction = [UIAlertAction actionWithTitle:title
                                                              style:UIAlertActionStyleDefault
                                                            handler:^(UIAlertAction *_Nonnull action) {
                                                              if (optionModel.currentIndex != -1) {
                                                                  // -1 不需要刷新 detailTextLabel
                                                                  optionModel.currentIndex = i;
                                                              }

                                                              if (optionModel.didSelectedIndex) {
                                                                  optionModel.didSelectedIndex(i, title);
                                                              }

                                                              [weakSelf.tableView reloadData];
                                                            }];
        [alerVC addAction:alertAction];
    }

    UIAlertAction *cancelAction = [UIAlertAction actionWithTitle:@"取消" style:UIAlertActionStyleCancel handler:nil];
    [alerVC addAction:cancelAction];

    UIPopoverPresentationController *popoverCtl = nil;
    NSString *deviceType = [UIDevice currentDevice].model;
    if ([deviceType isEqualToString:@"iPad"]) {
        popoverCtl = [alerVC popoverPresentationController];
    }

    UIViewController *currentVC = [UIApplication sharedApplication].keyWindow.rootViewController;
    if ([currentVC isKindOfClass:[UINavigationController class]]) {
        UINavigationController *navVC = (UINavigationController *)currentVC;
        UIViewController *topVC = navVC.visibleViewController;
        if (popoverCtl) {
            popoverCtl.sourceView = cellView;
            popoverCtl.sourceRect = cellView.bounds;
        }
        [topVC presentViewController:alerVC animated:YES completion:nil];
    } else {
        if (popoverCtl) {
            popoverCtl.sourceView = cellView;
            popoverCtl.sourceRect = cellView.bounds;
        }
        [currentVC presentViewController:alerVC animated:YES completion:nil];
    }
}

#pragma mark - delegate

- (UILabel *)titleLabel {
    if (!_titleLabel) {
        _titleLabel = [[UILabel alloc] init];
        _titleLabel.font = [UIFont systemFontOfSize:25];
    }
    return _titleLabel;
}

- (UITableView *)tableView {
    if (!_tableView) {
        _tableView = [[UITableView alloc] init];
        _tableView.delegate = self;
        _tableView.dataSource = self;
        _tableView.tableFooterView = [[UIView alloc] init];
        _tableView.scrollEnabled = NO;
    }
    return _tableView;
}

@end
