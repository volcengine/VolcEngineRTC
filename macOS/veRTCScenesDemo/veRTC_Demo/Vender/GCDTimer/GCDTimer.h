//
//  GCDTimer.h
//
//

#import <Foundation/Foundation.h>

@interface GCDTimer : NSObject

/**
 Initialization plus start

 @param timeNum Cycle Time
 @param block Loop method
 */
- (void)startTimerWithSpace:(float)timeNum block:(void(^)(BOOL result))block;


/**
 restore
 */
- (void)resume;

/**
 pause
 */
- (void)suspend;


/**
 close
 */
- (void)stopTimer;

@end
