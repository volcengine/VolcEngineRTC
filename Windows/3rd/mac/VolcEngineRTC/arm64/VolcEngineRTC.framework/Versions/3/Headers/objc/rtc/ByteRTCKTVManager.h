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
 * 注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。
 */
@protocol ByteRTCKTVManagerDelegate <NSObject>
@optional

/** 
 * @type callback
 * @brief 歌曲列表回调。
 * @param musics 歌曲数据数组，参看 ByteRTCMusicInfo{@link #ByteRTCMusicInfo}。
 * @param totalSize 数据条目总数。
 * @param errorCode 错误码，成功时返回 0，其余值参看 ByteRTCKTVErrorCode{@link #ByteRTCKTVErrorCode}。
 */
- (void)ktvManager:(ByteRTCKTVManager *)ktvManager onMusicListResult:(NSArray<ByteRTCMusicInfo *> * _Nullable)musics totalSize:(int)totalSize errorCode:(ByteRTCKTVErrorCode)errorCode;

/** 
 * @type callback
 * @brief 搜索歌曲结果回调。
 * @param musics 歌曲数据数组，参看 ByteRTCMusicInfo{@link #ByteRTCMusicInfo}。
 * @param totalSize 数据条目总数。
 * @param errorCode 错误码，成功时返回 0，其余值参看 ByteRTCKTVErrorCode{@link #ByteRTCKTVErrorCode}。
 */
- (void)ktvManager:(ByteRTCKTVManager *)ktvManager onSearchMusicResult:(NSArray<ByteRTCMusicInfo *> * _Nullable)musics totalSize:(int)totalSize errorCode:(ByteRTCKTVErrorCode)errorCode;

/** 
 * @type callback
 * @brief 热榜歌曲结果回调。
 * @param hotMusicInfos 热榜歌曲数据数组，参看 ByteRTCHotMusicInfo{@link #ByteRTCHotMusicInfo}。
 * @param errorCode 错误码，成功时返回 0，其余值参看 ByteRTCKTVErrorCode{@link #ByteRTCKTVErrorCode}。
 */
- (void)ktvManager:(ByteRTCKTVManager *)ktvManager onHotMusicResult:(NSArray<ByteRTCHotMusicInfo *> * _Nullable)hotMusicInfos errorCode:(ByteRTCKTVErrorCode)errorCode;

/** 
 * @type callback
 * @brief 歌曲详细信息回调。
 * @param music 歌曲数据，参看 ByteRTCMusicInfo{@link #ByteRTCMusicInfo}。
 * @param errorCode 错误码，成功时返回 0，其余值参看 ByteRTCKTVErrorCode{@link #ByteRTCKTVErrorCode}。
 */
- (void)ktvManager:(ByteRTCKTVManager *)ktvManager onMusicDetailResult:(ByteRTCMusicInfo * _Nullable)music errorCode:(ByteRTCKTVErrorCode)errorCode;

/** 
 * @type callback
 * @brief 下载成功回调。
 * @param downloadId 下载任务 ID。
 * @param result 下载信息，参看 ByteRTCDownloadResult{@link #ByteRTCDownloadResult}。
 */
- (void)ktvManager:(ByteRTCKTVManager *)ktvManager onDownloadSuccess:(int)downloadId downloadResult:(ByteRTCDownloadResult *)result;

/** 
 * @type callback
 * @brief 下载失败回调。
 * @param downloadId 下载任务 ID。
 * @param errorCode 错误码，参看 ByteRTCKTVErrorCode{@link #ByteRTCKTVErrorCode}。
 */
- (void)ktvManager:(ByteRTCKTVManager *)ktvManager onDownloadFailed:(int)downloadId errorCode:(ByteRTCKTVErrorCode)errorCode;

/** 
 * @type callback
 * @brief 歌曲文件下载进度回调。
 * @param downloadId 下载任务 ID。
 * @param downloadPercentage 下载进度百分比，取值范围 [0,100]。
 */
- (void)ktvManager:(ByteRTCKTVManager *)ktvManager onDownloadMusicProgress:(int)downloadId progress:(int)downloadPercentage;

/** 
 * @type callback
 * @brief 清理文件缓存结果回调。
 * @param errorCode 错误码，非0为失败，参看 ByteRTCKTVErrorCode{@link #ByteRTCKTVErrorCode}。
 */
- (void)ktvManager:(ByteRTCKTVManager *)ktvManager onClearCacheResult:(ByteRTCKTVErrorCode)errorCode;
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
 * @param filterType 歌曲过滤方式，参看 ByteRTCMusicFilterType{@link #ByteRTCMusicFilterType}。多个过滤方式可以按位或组合。
 * @notes 调用接口后，你会收到 ktvManager:onMusicListResult:totalSize:errorCode:{@link #ByteRTCKTVManagerDelegate#ktvManager:onMusicListResult:totalSize:errorCode:} 回调歌曲列表。
 */
- (void)getMusicList:(int)pageNumber pageSize:(int)pageSize filterType:(ByteRTCMusicFilterType)filterType;

/** 
 * @type api
 * @brief 根据关键词搜索歌曲。
 * @param keyWord 关键词，字符串长度最大为 20 个字符。
 * @param pageNumber 页码，默认从 1 开始。
 * @param pageSize 每页显示歌曲的最大数量，取值范围 [1,99]。
 * @param filterType 歌曲过滤方式，参看 ByteRTCMusicFilterType{@link #ByteRTCMusicFilterType}。多个过滤方式可以按位或组合。
 * @notes 调用接口后，你会收到 ktvManager:onSearchMusicResult:totalSize:errorCode:{@link #ByteRTCKTVManagerDelegate#ktvManager:onSearchMusicResult:totalSize:errorCode:} 回调歌曲列表。
 */
- (void)searchMusic:(NSString * _Nonnull)keyWord pageNumber:(int)pageNumber pageSize:(int)pageSize filterType:(ByteRTCMusicFilterType)filterType;

/** 
 * @type api
 * @brief 根据热榜获取每个榜单的歌曲列表。
 * @param hotType 热榜类别，参看 ByteRTCMusicHotType{@link #ByteRTCMusicHotType}。多个热榜类别可以按位或组合。
 * @param filterType 歌曲过滤方式，参看 ByteRTCMusicFilterType{@link #ByteRTCMusicFilterType}。多个过滤方式可以按位或组合。
 * @notes 调用接口后，你会收到 ktvManager:onHotMusicResult:errorCode:{@link #ByteRTCKTVManagerDelegate#ktvManager:onHotMusicResult:errorCode:} 回调歌曲列表。
 */
- (void)getHotMusic:(ByteRTCMusicHotType)hotType filterType:(ByteRTCMusicFilterType)filterType;

/** 
 * @type api
 * @brief 获取音乐详细信息。
 * @param musicId 音乐 ID。
 * @notes 调用接口后，你会收到 ktvManager:onMusicDetailResult:errorCode:{@link #ByteRTCKTVManagerDelegate#ktvManager:onMusicDetailResult:errorCode:} 回调。
 */
- (void)getMusicDetail:(NSString * _Nonnull)musicId;

/** 
 * @type api
 * @brief 下载音乐。
 * @param musicId 音乐 ID。
 * @return 下载任务 ID。
 * @notes  <br>
 *       + 若音乐下载成功，你会收到 ktvManager:onDownloadSuccess:downloadResult:{@link #ByteRTCKTVManagerDelegate#ktvManager:onDownloadSuccess:downloadResult:} 回调。
 *       + 若音乐下载失败，你会收到 ktvManager:onDownloadFailed:errorCode:{@link #ByteRTCKTVManagerDelegate#ktvManager:onDownloadFailed:errorCode:} 回调。
 *       + 音乐下载进度更新时，你会收到 ktvManager:onDownloadMusicProgress:progress:{@link #ByteRTCKTVManagerDelegate#ktvManager:onDownloadMusicProgress:progress:} 回调。
 */
- (int)downloadMusic:(NSString * _Nonnull)musicId;

/** 
 * @type api
 * @brief 下载歌词。
 * @param musicId 音乐 ID。
 * @param lyricType 歌词文件类型，参看 ByteRTCDownloadLyricType{@link #ByteRTCDownloadLyricType}。
 * @return 下载任务 ID。
 * @notes  <br>
 *       + 若歌词下载成功，你会收到 ktvManager:onDownloadSuccess:downloadResult:{@link #ByteRTCKTVManagerDelegate#ktvManager:onDownloadSuccess:downloadResult:} 回调。
 *       + 若歌词下载失败，你会收到 ktvManager:onDownloadFailed:errorCode:{@link #ByteRTCKTVManagerDelegate#ktvManager:onDownloadFailed:errorCode:} 回调。
 */
- (int)downloadLyric:(NSString * _Nonnull)musicId lyricType:(ByteRTCDownloadLyricType)lyricType;

/** 
 * @type api
 * @brief 下载 MIDI 文件。
 * @param musicId 音乐 ID。
 * @return 下载任务 ID。
 * @notes  <br>
 *       + 若文件下载成功，你会收到 ktvManager:onDownloadSuccess:downloadResult:{@link #ByteRTCKTVManagerDelegate#ktvManager:onDownloadSuccess:downloadResult:} 回调。
 *       + 若文件下载失败，你会收到 ktvManager:onDownloadFailed:errorCode:{@link #ByteRTCKTVManagerDelegate#ktvManager:onDownloadFailed:errorCode:} 回调。
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
