//
//  RoomViewController.h
//  RTCDemo


#import <Cocoa/Cocoa.h>

@interface RoomViewController : NSViewController

- (instancetype)initWithNibName:(NSNibName)nibNameOrNil
                         bundle:(NSBundle *)nibBundleOrNil
                         roomID:(NSString *)roomid
                            uid:(NSString *)uid;

@property (nonatomic, copy) void (^clickBackBlock)(void);

@end
