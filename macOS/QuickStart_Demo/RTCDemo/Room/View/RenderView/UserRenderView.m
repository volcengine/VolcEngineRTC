//
//  UserRenderView.m
//  RTCDemo


#import "UserRenderView.h"
#import "Masonry.h"
#import "NSColor+CorlorString.h"
#import "NSView+Snippet.h"
#import "NSLabel.h"

@interface UserRenderView ()

@property (nonatomic, strong) NSLabel *uidLabel;

@end

@implementation UserRenderView

- (instancetype)init {
    self = [super init];
    if (self) {
        [self addSubview:self.videoView];
        [self.videoView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.edges.equalTo(self);
        }];
        
        [self addSubview:self.uidLabel];
        [self.uidLabel mas_makeConstraints:^(MASConstraintMaker *make) {
            make.right.bottom.equalTo(self);
        }];
    }
    return self;
}

- (void)setUid:(NSString *)uid {
    _uid = uid;
    dispatch_async(dispatch_get_main_queue(), ^{
        self.uidLabel.text = uid;
    });
}

- (NSLabel *)uidLabel {
    if (!_uidLabel) {
        _uidLabel = [[NSLabel alloc] init];
        _uidLabel.textColor = [NSColor whiteColor];
        _uidLabel.font = [NSFont systemFontOfSize:14];
    }
    return _uidLabel;
}

- (NSView *)videoView {
    if (!_videoView) {
        _videoView = [[NSView alloc] init];
    }
    return _videoView;
}

@end
