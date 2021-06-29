//
//  SystemAuthority.h
//  quickstart
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface SystemAuthority : NSObject

/*
 * Obtain system camera authorization status
 * @param completion State callback
 */
+ (void)authorCamera:(void (^ __nullable)(BOOL granted))completion;

/*
 * Obtain system microphone authorization status
 * @param completion State callback
 */
+ (void)authorMicphone:(void (^ __nullable)(BOOL granted))completion;


+ (BOOL)canRecordScreen;

@end

NS_ASSUME_NONNULL_END
