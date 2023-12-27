//
//  FUMakeupView.m
//  FURTCDemo
//
//  Created by 项林平 on 2023/2/6.
//

#import "FUMakeupView.h"
#import "FUSlider.h"
#import "FUDefines.h"

static NSString * const kFUMakeupCellIdentifier = @"FUMakeupCell";

@interface FUMakeupView ()<UICollectionViewDataSource, UICollectionViewDelegate>

@property (nonatomic, strong) FUSlider *slider;

@property (nonatomic, strong) UICollectionView *collectionView;

@property (nonatomic, strong) FUMakeupViewModel *viewModel;

@end

@implementation FUMakeupView

#pragma mark - Initializer

- (instancetype)initWithFrame:(CGRect)frame {
    return [self initWithFrame:frame viewModel:[[FUMakeupViewModel alloc] init]];
}

- (instancetype)initWithFrame:(CGRect)frame viewModel:(FUMakeupViewModel *)viewModel {
    self = [super initWithFrame:frame];
    if (self) {
        self.viewModel = viewModel;
        [self configureUI];
    }
    return self;
}

#pragma mark - UI

- (void)configureUI {
    UIBlurEffect *effect = [UIBlurEffect effectWithStyle:UIBlurEffectStyleDark];
    UIVisualEffectView *effectView = [[UIVisualEffectView alloc] initWithEffect:effect];
    effectView.frame = CGRectMake(0, 0, CGRectGetWidth(self.frame), CGRectGetHeight(self.frame));
    [self addSubview:effectView];
    
    [self addSubview:self.slider];
    [self addSubview:self.collectionView];
    NSLayoutConstraint *bottom = [NSLayoutConstraint constraintWithItem:self.collectionView attribute:NSLayoutAttributeBottom relatedBy:NSLayoutRelationEqual toItem:self attribute:NSLayoutAttributeBottom multiplier:1 constant:0];
    NSLayoutConstraint *leading = [NSLayoutConstraint constraintWithItem:self.collectionView attribute:NSLayoutAttributeLeading relatedBy:NSLayoutRelationEqual toItem:self attribute:NSLayoutAttributeLeading multiplier:1 constant:0];
    NSLayoutConstraint *trailing = [NSLayoutConstraint constraintWithItem:self.collectionView attribute:NSLayoutAttributeTrailing relatedBy:NSLayoutRelationEqual toItem:self attribute:NSLayoutAttributeTrailing multiplier:1 constant:0];
    NSLayoutConstraint *height = [NSLayoutConstraint constraintWithItem:self.collectionView attribute:NSLayoutAttributeHeight relatedBy:NSLayoutRelationEqual toItem:nil attribute:NSLayoutAttributeNotAnAttribute multiplier:1 constant:98];
    [self addConstraints:@[bottom, leading, trailing]];
    [self.collectionView addConstraint:height];
    // 默认选中
    [self.collectionView selectItemAtIndexPath:[NSIndexPath indexPathForItem:self.viewModel.selectedIndex inSection:0] animated:YES scrollPosition:UICollectionViewScrollPositionCenteredHorizontally];
    self.slider.hidden = self.viewModel.selectedIndex < 1;
    if (!self.slider.hidden) {
        self.slider.value = self.viewModel.selectedMakeupValue;
    }
}

#pragma mark - Event response

- (void)sliderValueChanged {
    self.viewModel.selectedMakeupValue = self.slider.value;
}

#pragma mark - Collection view data source

- (NSInteger)collectionView:(UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section {
    return self.viewModel.combinationMakeups.count;
}

- (__kindof UICollectionViewCell *)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath {
    FUMakeupCell *cell = [collectionView dequeueReusableCellWithReuseIdentifier:kFUMakeupCellIdentifier forIndexPath:indexPath];
    cell.imageView.image = [self.viewModel combinationMakeupIconAtIndex:indexPath.item];
    cell.textLabel.text = [self.viewModel combinationMakeupNameAtIndex:indexPath.item];
    return cell;
}

#pragma mark - Collection view delegate

- (void)collectionView:(UICollectionView *)collectionView didSelectItemAtIndexPath:(NSIndexPath *)indexPath {
    if (self.viewModel.selectedIndex == indexPath.item) {
        return;
    }
    [self.viewModel selectCombinationMakeupAtIndex:indexPath.item];
    self.slider.hidden = indexPath.item < 1;
    if (!self.slider.hidden) {
        self.slider.value = self.viewModel.selectedMakeupValue;
    }
}

#pragma mark - Getters

- (FUSlider *)slider {
    if (!_slider) {
        _slider = [[FUSlider alloc] initWithFrame:CGRectMake(56, 15, CGRectGetWidth(self.frame) - 112, 30)];
        _slider.bidirection = NO;
        _slider.hidden = YES;
        [_slider addTarget:self action:@selector(sliderValueChanged) forControlEvents:UIControlEventValueChanged];
    }
    return _slider;
}

- (UICollectionView *)collectionView {
    if (!_collectionView) {
        UICollectionViewFlowLayout *layout = [[UICollectionViewFlowLayout alloc] init];
        layout.scrollDirection = UICollectionViewScrollDirectionHorizontal;
        layout.itemSize = CGSizeMake(54, 70);
        layout.minimumLineSpacing = 16;
        layout.minimumInteritemSpacing = 50;
        layout.sectionInset = UIEdgeInsetsMake(16, 18, 10, 18);
        _collectionView = [[UICollectionView alloc] initWithFrame:CGRectZero collectionViewLayout:layout];
        _collectionView.translatesAutoresizingMaskIntoConstraints = NO;
        _collectionView.backgroundColor = [UIColor clearColor];
        _collectionView.showsHorizontalScrollIndicator = NO;
        _collectionView.dataSource = self;
        _collectionView.delegate = self;
        [_collectionView registerClass:[FUMakeupCell class] forCellWithReuseIdentifier:kFUMakeupCellIdentifier];
    }
    return _collectionView;
}

- (FUMakeupViewModel *)viewModel {
    if (!_viewModel) {
        _viewModel = [[FUMakeupViewModel alloc] init];
    }
    return _viewModel;
}

@end

@interface FUMakeupCell ()

@property (nonatomic, strong) UIImageView *imageView;
@property (nonatomic, strong) UILabel *textLabel;

@end

@implementation FUMakeupCell

- (instancetype)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        [self.contentView addSubview:self.imageView];
        NSLayoutConstraint *imageTop = [NSLayoutConstraint constraintWithItem:self.imageView attribute:NSLayoutAttributeTop relatedBy:NSLayoutRelationEqual toItem:self.contentView attribute:NSLayoutAttributeTop multiplier:1 constant:0];
        NSLayoutConstraint *imageLeading = [NSLayoutConstraint constraintWithItem:self.imageView attribute:NSLayoutAttributeLeading relatedBy:NSLayoutRelationEqual toItem:self.contentView attribute:NSLayoutAttributeLeading multiplier:1 constant:0];
        NSLayoutConstraint *imageTrailing = [NSLayoutConstraint constraintWithItem:self.imageView attribute:NSLayoutAttributeTrailing relatedBy:NSLayoutRelationEqual toItem:self.contentView attribute:NSLayoutAttributeTrailing multiplier:1 constant:0];
        NSLayoutConstraint *imageHeight = [NSLayoutConstraint constraintWithItem:self.imageView attribute:NSLayoutAttributeHeight relatedBy:NSLayoutRelationEqual toItem:self.imageView attribute:NSLayoutAttributeWidth multiplier:1 constant:0];
        [self.contentView addConstraints:@[imageTop, imageLeading, imageTrailing]];
        [self.imageView addConstraint:imageHeight];
        
        [self.contentView addSubview:self.textLabel];
        NSLayoutConstraint *textTop = [NSLayoutConstraint constraintWithItem:self.textLabel attribute:NSLayoutAttributeTop relatedBy:NSLayoutRelationEqual toItem:self.imageView attribute:NSLayoutAttributeBottom multiplier:1 constant:2];
        NSLayoutConstraint *textLeading = [NSLayoutConstraint constraintWithItem:self.textLabel attribute:NSLayoutAttributeLeading relatedBy:NSLayoutRelationEqual toItem:self.contentView attribute:NSLayoutAttributeLeading multiplier:1 constant:0];
        NSLayoutConstraint *textTrailing = [NSLayoutConstraint constraintWithItem:self.textLabel attribute:NSLayoutAttributeTrailing relatedBy:NSLayoutRelationEqual toItem:self.contentView attribute:NSLayoutAttributeTrailing multiplier:1 constant:0];
        [self.contentView addConstraints:@[textTop, textLeading, textTrailing]];
    }
    return self;
}

- (void)setSelected:(BOOL)selected {
    [super setSelected:selected];
    self.imageView.layer.borderWidth = selected ? 2 : 0;
    self.imageView.layer.borderColor = selected ? [UIColor colorWithRed:94/255.0 green:199/255.0 blue:254/255.0 alpha:1].CGColor : [UIColor clearColor].CGColor;
    self.textLabel.textColor = selected ? [UIColor colorWithRed:94/255.0 green:199/255.0 blue:254/255.0 alpha:1] : [UIColor whiteColor];
}

- (UIImageView *)imageView {
    if (!_imageView) {
        _imageView = [[UIImageView alloc] init];
        _imageView.translatesAutoresizingMaskIntoConstraints = NO;
        _imageView.layer.masksToBounds = YES;
        _imageView.layer.cornerRadius = 3.f;
    }
    return _imageView;
}

- (UILabel *)textLabel {
    if (!_textLabel) {
        _textLabel = [[UILabel alloc] init];
        _textLabel.textColor = [UIColor whiteColor];
        _textLabel.font = [UIFont systemFontOfSize:10];
        _textLabel.textAlignment = NSTextAlignmentCenter;
        _textLabel.translatesAutoresizingMaskIntoConstraints = NO;
    }
    return _textLabel;
}

@end
