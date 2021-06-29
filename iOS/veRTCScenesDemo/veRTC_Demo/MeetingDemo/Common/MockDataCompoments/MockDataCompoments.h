//
//  MockDataCompoments.h
//  quickstart
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface MockDataCompoments : NSObject

@property (nonatomic, assign, readonly) NSRange bitRateRang;

@property (nonatomic, copy) NSArray *frameRateLists;

@property (nonatomic, copy, readonly) NSArray<NSArray *> *resolutionLists;

/*
 * Get the corresponding bit rate by selecting the resolution
 * @param The position of the resolution in the array
 * @return Corresponding bit rate
 */
- (NSRange)selectBitRateRangWithRow:(NSInteger)row;

@end

NS_ASSUME_NONNULL_END
