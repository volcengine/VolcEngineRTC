
#import <UIKit/UIKit.h>

@interface SettingsSwitchCell : UITableViewCell

@property (nonatomic, strong, readonly) UILabel *settingsLabel;

- (void)setSwitchOn:(BOOL)on;
- (void)switchValueChangeCallback:(void (^)(BOOL on))callback;
- (void)setSwitchAccessibilityIdentifier:(NSString *)accessId;

@end
