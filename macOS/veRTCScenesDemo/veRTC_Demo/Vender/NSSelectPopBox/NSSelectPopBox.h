//
//  NSSelectPopBox.h
//  veRTC_Demo
//
//  Created by  on 2021/6/11.
//

#import <Cocoa/Cocoa.h>
#import <Foundation/Foundation.h>
@class NSSelectPopBox;
NS_ASSUME_NONNULL_BEGIN

@protocol NSSelectPopBoxDataSource <NSObject>

- (nullable id)selectPopBox:(NSSelectPopBox *)selectPopBox objectValueForItemAtIndex:(NSInteger)index;

- (NSInteger)selectPopBox:(NSSelectPopBox *)selectPopBox numberOfItemsInComboBox:(BOOL)isResult;

@end

@protocol NSSelectPopBoxDelegate <NSObject>

- (void)selectPopBox:(NSSelectPopBox *)selectPopBox boxSelectionDidChange:(NSString *)str;

- (void)selectPopBox:(NSSelectPopBox *)selectPopBox boxSelectionDidDelete:(NSString *)str;

@end

@interface NSSelectPopBox : NSView

@property (nonatomic, weak) id<NSSelectPopBoxDelegate> delegate;

@property (nonatomic, weak) id<NSSelectPopBoxDataSource> dataSource;

@property (nonatomic, copy) NSString *stringValue;

@property (nonatomic, assign) BOOL isDelete;

- (void)reloadData;

@end

NS_ASSUME_NONNULL_END
