//
//  AlertActionModel.h
//  quickstart

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

typedef void (^AlertModelClickBlock)(UIAlertAction * _Nonnull action);

NS_ASSUME_NONNULL_BEGIN

@interface AlertActionModel : NSObject

@property (nonatomic, copy) NSString *title;

@property (nonatomic, copy) AlertModelClickBlock alertModelClickBlock;

@end

NS_ASSUME_NONNULL_END
