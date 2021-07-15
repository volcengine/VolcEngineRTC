//
//  VoiceRoomAudienceView.m
//  veRTC_Demo
//
//  Created by  on 2021/5/18.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import "VoiceRoomAudienceView.h"
#import "BaseCollectionLayout.h"

@interface VoiceRoomAudienceView () <UICollectionViewDelegate,UICollectionViewDataSource>

@property (nonatomic, strong) UICollectionView *collectionView;


@end

@implementation VoiceRoomAudienceView


- (instancetype)init
{
    self = [super init];
    if (self) {

        [self addSubview:self.collectionView];
        [self.collectionView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.top.equalTo(self);
            make.left.right.bottom.equalTo(self);
        }];
    }
    return self;
}

- (void)layoutSubviews {
    [super layoutSubviews];
    
}

- (void)setDataLists:(NSArray *)dataLists {
    _dataLists = dataLists;
    
    [self.collectionView reloadData];
}

#pragma mark - collectionView delegate

- (NSInteger)numberOfSectionsInCollectionView:(UICollectionView *)collectionView {
    return 1;
}

- (UIEdgeInsets)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout *)collectionViewLayout insetForSectionAtIndex:(NSInteger)section {
    UIEdgeInsets top = {0,0,0,0};
    return top;
}

- (NSInteger)collectionView:(UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section {
    return self.dataLists.count;
}

-(UICollectionViewCell *)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath {
    
    VoiceUserAvatarCell *cell = (VoiceUserAvatarCell *)[collectionView dequeueReusableCellWithReuseIdentifier:@"VoiceUserAvatarCellID" forIndexPath:indexPath];
    cell.status = AvatarCellStatusAudience;
    cell.model = self.dataLists[indexPath.row];
    return cell;
}

- (CGFloat)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout*)collectionViewLayout minimumInteritemSpacingForSectionAtIndex:(NSInteger)section {
    return 10;
}

- (CGFloat)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout*)collectionViewLayout minimumLineSpacingForSectionAtIndex:(NSInteger)section {
    
    return 10;
}

-(CGSize)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout *)collectionViewLayout sizeForItemAtIndexPath:(NSIndexPath *)indexPath {
    return CGSizeMake(155 / 2, 128 / 2);
}

- (void)collectionView:(UICollectionView *)collectionView didSelectItemAtIndexPath:(NSIndexPath *)indexPath {

}

#pragma mark - getter

- (UICollectionView *)collectionView {
    if (_collectionView == nil) {
        BaseCollectionLayout *flowLayout =[[BaseCollectionLayout alloc] init];
        _collectionView = [[UICollectionView alloc] initWithFrame:CGRectMake(0, 0, 0, 0) collectionViewLayout:flowLayout];
        [_collectionView registerClass:[VoiceUserAvatarCell class]forCellWithReuseIdentifier:@"VoiceUserAvatarCellID"];
        _collectionView.delegate = self;
        _collectionView.dataSource = self;
        _collectionView.showsHorizontalScrollIndicator = NO;
        _collectionView.showsVerticalScrollIndicator = NO;
        _collectionView.backgroundColor = [UIColor clearColor];
    }
    return _collectionView;
}

@end
