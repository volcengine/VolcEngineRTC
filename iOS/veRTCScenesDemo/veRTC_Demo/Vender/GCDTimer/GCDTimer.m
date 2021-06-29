//
//  GCDTimer.m
//
//

#import "GCDTimer.h"

typedef NS_ENUM(NSInteger,YUTimerStatus) {
    YUTimerStatusIng,
    YUTimerStatusSuspend,
    YUTimerStatusStop,
};

@interface GCDTimer ()

@property (nonatomic, strong) dispatch_source_t timer;

@property (nonatomic, strong) dispatch_semaphore_t lock;

@property (nonatomic, assign) BOOL onFire;

@property (nonatomic, assign) YUTimerStatus timerStatus;

@end

@implementation GCDTimer

- (instancetype)init
{
    self = [super init];
    if (self) {
        _timerStatus = YUTimerStatusStop;
    }
    return self;
}

- (void)startTimerWithSpace:(float)timeNum block:(void (^)(BOOL))block {
    if (_timerStatus != YUTimerStatusStop) {
        NSLog(@"%@-start error%ld", [self class], (long)_timerStatus);
        if (block) {
            block(NO);
        }
        return;
    }
    dispatch_time_t start = dispatch_walltime(NULL, (int64_t)(0.0 * NSEC_PER_SEC));
    uint64_t interval = (uint64_t)(timeNum * NSEC_PER_SEC);
    dispatch_source_set_timer(self.timer, start, interval, 0);
    dispatch_source_set_event_handler(self.timer, ^{
        dispatch_async(dispatch_get_main_queue(), ^{
            if (block) {
                block(YES);
            }
        });
    });
    [self resumeTime];
}

- (void)resume {
    if (_timerStatus != YUTimerStatusSuspend) {
        NSLog(@"%@-resume error%ld",[self class],_timerStatus);
        return;
    }
    [self resumeTime];
}

- (void)resumeTime {
    dispatch_semaphore_wait(self.lock, DISPATCH_TIME_FOREVER);
    if (self.timer) {
        dispatch_resume(self.timer);
        _onFire = YES;
        _timerStatus = YUTimerStatusIng;
    }
    dispatch_semaphore_signal(self.lock);
}

- (void)suspend {
    if (_timerStatus != YUTimerStatusIng) {
        NSLog(@"%@-suspend error%ld",[self class],_timerStatus);
        return;
    }
    dispatch_semaphore_wait(self.lock, DISPATCH_TIME_FOREVER);
    if (self.timer) {
        dispatch_suspend(self.timer);
        _onFire = NO;
        _timerStatus = YUTimerStatusSuspend;
    }
    dispatch_semaphore_signal(self.lock);
}

- (void)stopTimer {
    if (_timerStatus != YUTimerStatusIng) {
        NSLog(@"%@-stop error%ld",[self class],_timerStatus);
        return;
    }
    dispatch_semaphore_wait(self.lock, DISPATCH_TIME_FOREVER);
    if (self.timer) {
        dispatch_source_cancel(self.timer);
        _timerStatus = YUTimerStatusStop;
        _onFire = NO;
        self.timer = NULL;
    }
    dispatch_semaphore_signal(self.lock);
}


- (void)dealloc {
    if (self.timer) {
        if (_onFire == NO) {
            dispatch_resume(self.timer);
        }
    }
    [self stopTimer];
}


#pragma mark - getter

- (dispatch_source_t)timer {
    if (_timer == nil) {
        dispatch_queue_t queue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT,0);
        _timer = dispatch_source_create(DISPATCH_SOURCE_TYPE_TIMER, 0, 0, queue);
    }
    return _timer;
}

- (dispatch_semaphore_t)lock {
    if (_lock == nil) {
        _lock = dispatch_semaphore_create(1);
    }
    return _lock;
}






@end
