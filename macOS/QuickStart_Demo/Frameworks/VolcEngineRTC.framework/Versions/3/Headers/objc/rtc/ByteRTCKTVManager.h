/*
 * Copyright (c) 2022 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief ByteRTCKTVManager
*/

#import <Foundation/Foundation.h>
#import "ByteRTCKTVDefines.h"
@class ByteRTCKTVManager;
@class ByteRTCKTVPlayer;

NS_ASSUME_NONNULL_BEGIN

/** 
 * @type callback
 * @brief KTV 事件回调接口。
 */
@protocol ByteRTCKTVManagerDelegate <NSObject>
@optional

/** 
 * @type callback
 * @brief 歌曲列表回调。
 * @param errorCode 错误码，成功时返回 0，其余值参看 ByteRTCKTVError{@link #ByteRTCKTVError}。
 * @param totalSize 数据条目总数。
 * @param musics 歌曲数据数组，参看 ByteRTCKTVMusic{@link #ByteRTCKTVMusic}。
 */
- (void)ktvManager:(ByteRTCKTVManager *)ktvManager onMusicListResult:(ByteRTCKTVError)errorCode totalSize:(int)totalSize musics:(NSArray<ByteRTCKTVMusic *> * _Nullable)musics;

/** 
 * @type callback
 * @brief 搜索歌曲结果回调。
 * @param errorCode 错误码，成功时返回 0，其余值参看 ByteRTCKTVError{@link #ByteRTCKTVError}。
 * @param totalSize 数据条目总数。
 * @param musics 歌曲数据数组，参看 ByteRTCKTVMusic{@link #ByteRTCKTVMusic}。
 */
- (void)ktvManager:(ByteRTCKTVManager *)ktvManager onSearchMusicResult:(ByteRTCKTVError)errorCode totalSize:(int)totalSize musics:(NSArray<ByteRTCKTVMusic *> * _Nullable)musics;

/** 
 * @type callback
 * @brief 热榜歌曲结果回调。
 * @param errorCode 错误码，成功时返回 0，其余值参看 ByteRTCKTVError{@link #ByteRTCKTVError}。
 * @param hotMusicInfos 热榜歌曲数据数组，参看 ByteRTCKTVHotMusicInfo{@link #ByteRTCKTVHotMusicInfo}。
 */
- (void)ktvManager:(ByteRTCKTVManager *)ktvManager onHotMusicResult:(ByteRTCKTVError)errorCode hotMusicInfos:(NSArray<ByteRTCKTVHotMusicInfo *> * _Nullable)hotMusicInfos;

/** 
 * @type callback
 * @brief 歌曲详细信息回调。
 * @param errorCode 错误码，成功时返回 0，其余值参看 ByteRTCKTVError{@link #ByteRTCKTVError}。
 * @param music 歌曲数据，参看 ByteRTCKTVMusic{@link #ByteRTCKTVMusic}。
 */
- (void)ktvManager:(ByteRTCKTVManager *)ktvManager onMusicDetailResult:(ByteRTCKTVError)errorCode music:(ByteRTCKTVMusic * _Nullable)music;

/** 
 * @type callback
 * @brief 下载成功回调。
 * @param downloadId 下载任务 ID。
 * @param result 下载信息，参看 ByteRTCKTVDownloadResult{@link #ByteRTCKTVDownloadResult}。
 */
- (void)ktvManager:(ByteRTCKTVManager *)ktvManager onDownloadSuccess:(int)downloadId downloadResult:(ByteRTCKTVDownloadResult *)result;

/** 
 * @type callback
 * @brief 下载失败回调。
 * @param downloadId 下载任务 ID。
 * @param errorCode 错误码，参看 ByteRTCKTVError{@link #ByteRTCKTVError}。
 */
- (void)ktvManager:(ByteRTCKTVManager *)ktvManager onDownloadFail:(int)downloadId errorCode:(ByteRTCKTVError)errorCode;

/** 
 * @type callback
 * @brief 歌曲文件下载进度回调。
 * @param downloadId 下载任务 ID。
 * @param downloadPercentage 下载进度百分比，取值范围 [0,100]。
 */
- (void)ktvManager:(ByteRTCKTVManager *)ktvManager onDownloadMusicProgress:(int)downloadId progress:(int)downloadPercentage;
@end

/** 
 * @type api
 * @brief KTV 管理接口。
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCKTVManager : NSObject

@property(nonatomic, weak) id<ByteRTCKTVManagerDelegate> delegate;

#pragma mark - Core Methods

/** 
 * @type api
 * @brief 获取歌曲列表。
 * @param pageNumber 页码，默认从 1 开始。
 * @param pageSize 每页显示歌曲的最大数量，取值范围 [1,99]。
 * @param filterType 歌曲过滤方式，参看 ByteRTCKTVMusicFilterType{@link #ByteRTCKTVMusicFilterType}。多个过滤方式可以按位或组合。
 * @notes 调用接口后，你会收到 ktvManager:onMusicListResult:totalSize:musics:{@link #ByteRTCKTVManagerDelegate#ktvManager:onMusicListResult:totalSize:musics:} 回调歌曲列表。
 */
- (void)getMusicList:(int)pageNumber pageSize:(int)pageSize filterType:(ByteRTCKTVMusicFilterType)filterType;

/** 
 * @type api
 * @brief 根据关键词搜索歌曲。
 * @param keyWord 关键词，字符串长度最大为 20 个字符。
 * @param pageNumber 页码，默认从 1 开始。
 * @param pageSize 每页显示歌曲的最大数量，取值范围 [1,99]。
 * @param filterType 歌曲过滤方式，参看 ByteRTCKTVMusicFilterType{@link #ByteRTCKTVMusicFilterType}。多个过滤方式可以按位或组合。
 * @notes 调用接口后，你会收到 ktvManager:onSearchMusicResult:totalSize:musics:{@link #ByteRTCKTVManagerDelegate#ktvManager:onSearchMusicResult:totalSize:musics:} 回调歌曲列表。
 */
- (void)searchMusic:(NSString * _Nonnull)keyWord pageNumber:(int)pageNumber pageSize:(int)pageSize filterType:(ByteRTCKTVMusicFilterType)filterType;

/** 
 * @type api
 * @brief 根据热榜获取每个榜单的歌曲列表。
 * @param hotType 热榜类别，参看 ByteRTCKTVMusicHotType{@link #ByteRTCKTVMusicHotType}。多个热榜类别可以按位或组合。
 * @param filterType 歌曲过滤方式，参看 ByteRTCKTVMusicFilterType{@link #ByteRTCKTVMusicFilterType}。多个过滤方式可以按位或组合。
 * @notes 调用接口后，你会收到 ktvManager:onHotMusicResult:hotMusicInfos:{@link #ByteRTCKTVManagerDelegate#ktvManager:onHotMusicResult:hotMusicInfos:} 回调歌曲列表。
 */
- (void)getHotMusic:(ByteRTCKTVMusicHotType)hotType filterType:(ByteRTCKTVMusicFilterType)filterType;

/** 
 * @type api
 * @brief 获取音乐详细信息。
 * @param musicId 音乐 ID。
 * @notes 调用接口后，你会收到 ktvManager:onMusicDetailResult:music:{@link #ByteRTCKTVManagerDelegate#ktvManager:onMusicDetailResult:music:} 回调。
 */
- (void)getMusicDetail:(NSString * _Nonnull)musicId;

/** 
 * @type api
 * @brief 下载音乐。
 * @param musicId 音乐 ID。
 * @return 下载任务 ID。
 * @notes  <br>
 *       + 若音乐下载成功，你会收到 ktvManager:onDownloadSuccess:downloadResult:{@link #ByteRTCKTVManagerDelegate#ktvManager:onDownloadSuccess:downloadResult:} 回调。
 *       + 若音乐下载失败，你会收到 ktvManager:onDownloadFail:errorCode:{@link #ByteRTCKTVManagerDelegate#ktvManager:onDownloadFail:errorCode:} 回调。
 *       + 音乐下载进度更新时，你会收到 ktvManager:onDownloadMusicProgress:progress:{@link #ByteRTCKTVManagerDelegate#ktvManager:onDownloadMusicProgress:progress:} 回调。
 */
- (int)downloadMusic:(NSString * _Nonnull)musicId;

/** 
 * @type api
 * @brief 下载歌词。
 * @param musicId 音乐 ID。
 * @param lyricType 歌词文件类型，参看 ByteRTCKTVDownloadLyricType{@link #ByteRTCKTVDownloadLyricType}。
 * @return 下载任务 ID。
 * @notes  <br>
 *       + 若歌词下载成功，你会收到 ktvManager:onDownloadSuccess:downloadResult:{@link #ByteRTCKTVManagerDelegate#ktvManager:onDownloadSuccess:downloadResult:} 回调。
 *       + 若歌词下载失败，你会收到 ktvManager:onDownloadFail:errorCode:{@link #ByteRTCKTVManagerDelegate#ktvManager:onDownloadFail:errorCode:} 回调。
 */
- (int)downloadLyric:(NSString * _Nonnull)musicId lyricType:(ByteRTCKTVDownloadLyricType)lyricType;

/** 
 * @type api
 * @brief 下载 MIDI 文件。
 * @param musicId 音乐 ID。
 * @return 下载任务 ID。
 * @notes  <br>
 *       + 若文件下载成功，你会收到 ktvManager:onDownloadSuccess:downloadResult:{@link #ByteRTCKTVManagerDelegate#ktvManager:onDownloadSuccess:downloadResult:} 回调。
 *       + 若文件下载失败，你会收到 ktvManager:onDownloadFail:errorCode:{@link #ByteRTCKTVManagerDelegate#ktvManager:onDownloadFail:errorCode:} 回调。
 */
- (int)downloadMidi:(NSString * _Nonnull)musicId;

/** 
 * @type api
 * @brief 取消下载任务。
 * @param downloadId 下载任务 ID。
 */
- (void)cancelDownload:(int)downloadId;

/** 
 * @type api
 * @brief 清除当前音乐缓存文件，包括音乐音频和歌词。
 */
- (void)clearCache;

/** 
 * @type api
 * @brief 设置歌曲文件最大占用的本地缓存。
 * @param maxCacheSizeMB 本地缓存，单位 MB。
 *        设置值小于等于 0 时，使用默认值 1024 MB。
 */
- (void)setMaxCacheSize:(int)maxCacheSizeMB;

/** 
 * @type api
 * @brief 获取 KTV 播放器。
 * @return KTV 播放器接口，参看 ByteRTCKTVPlayer{@link #ByteRTCKTVPlayer}。
 */
- (ByteRTCKTVPlayer * _Nullable)getKTVPlayer;


@end

NS_ASSUME_NONNULL_END
