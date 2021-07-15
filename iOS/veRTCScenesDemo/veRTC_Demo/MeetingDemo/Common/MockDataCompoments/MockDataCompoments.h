//
//  MockDataCompoments.h
//  quickstart
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface MockDataCompoments : NSObject

@property (nonatomic, assign, readonly) NSRange bitRateRang;

@property (nonatomic, assign, readonly) NSRange bitScreenRateRang;

@property (nonatomic, copy) NSArray *frameRateLists;

@property (nonatomic, copy, readonly) NSArray<NSArray *> *resolutionLists;

/*
 * Get the corresponding bit rate by selecting the resolution
 * @param The position of the resolution in the array
 * @return Corresponding bit rate
 */
- (NSRange)selectBitRateRangWithRow:(NSInteger)row;

/*
 * Get the corresponding bit rate by selecting the screen resolution
 * @param The position of the resolution in the array
 * @return Corresponding bit rate
 */
- (NSRange)selectScreenBitRateRangWithRow:(NSInteger)row isDefault:(BOOL)isDefault;

@end

NS_ASSUME_NONNULL_END
