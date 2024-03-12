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
 * @locale zh
 * @type callback
 * @brief KTV 事件回调接口。<br>
 * 注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。
 */
/**
 * @locale en
 * @hidden currently not available
 * @type callback
 * @brief KTV manager event handler.<br>
 * Note: Callback functions are thrown synchronously in a non-UI thread within the SDK. Therefore, you must not perform any time-consuming operations or direct UI operations within the callback function, as this may cause the app to crash.
 */
@protocol ByteRTCKTVManagerDelegate <NSObject>
@optional

/**
 * @locale zh
 * @type callback
 * @brief 歌曲列表回调。
 * @param musics 歌曲数据数组，参看 ByteRTCMusicInfo{@link #ByteRTCMusicInfo}。
 * @param totalSize 数据条目总数。
 * @param errorCode 错误码，成功时返回 0，其余值参看 ByteRTCKTVErrorCode{@link #ByteRTCKTVErrorCode}。
 */
/**
 * @locale en
 * @type callback
 * @brief The music list callback.
 * @param musics Array of the music information. See ByteRTCMusicInfo{@link #ByteRTCMusicInfo}.
 * @param totalSize The total size of the music list.
 * @param errorCode Error code. The value 0 indicates success. For the indications of other values, see ByteRTCKTVErrorCode{@link #ByteRTCKTVErrorCode}.
 */
- (void)ktvManager:(ByteRTCKTVManager *)ktvManager onMusicListResult:(NSArray<ByteRTCMusicInfo *> * _Nullable)musics totalSize:(int)totalSize errorCode:(ByteRTCKTVErrorCode)errorCode;

/**
 * @locale zh
 * @type callback
 * @brief 搜索歌曲结果回调。
 * @param musics 歌曲数据数组，参看 ByteRTCMusicInfo{@link #ByteRTCMusicInfo}。
 * @param totalSize 数据条目总数。
 * @param errorCode 错误码，成功时返回 0，其余值参看 ByteRTCKTVErrorCode{@link #ByteRTCKTVErrorCode}。
 */
/**
 * @locale en
 * @type callback
 * @brief The search music callback.
 * @param musics Array of the music information. See ByteRTCMusicInfo{@link #ByteRTCMusicInfo}.
 * @param totalSize The total size of the music list.
 * @param errorCode Error code. The value 0 indicates success. For the indications of other values, see ByteRTCKTVErrorCode{@link #ByteRTCKTVErrorCode}.
 */
- (void)ktvManager:(ByteRTCKTVManager *)ktvManager onSearchMusicResult:(NSArray<ByteRTCMusicInfo *> * _Nullable)musics totalSize:(int)totalSize errorCode:(ByteRTCKTVErrorCode)errorCode;

/**
 * @locale zh
 * @type callback
 * @brief 热榜歌曲结果回调。
 * @param hotMusicInfos 热榜歌曲数据数组，参看 ByteRTCHotMusicInfo{@link #ByteRTCHotMusicInfo}。
 * @param errorCode 错误码，成功时返回 0，其余值参看 ByteRTCKTVErrorCode{@link #ByteRTCKTVErrorCode}。
 */
/**
 * @locale en
 * @type callback
 * @brief The hot music callback.
 * @param hotMusicInfos Array of the hot music information. See ByteRTCHotMusicInfo{@link #ByteRTCHotMusicInfo}.
 * @param errorCode Error code. The value 0 indicates success. For the indications of other values, see ByteRTCKTVErrorCode{@link #ByteRTCKTVErrorCode}.
 */
- (void)ktvManager:(ByteRTCKTVManager *)ktvManager onHotMusicResult:(NSArray<ByteRTCHotMusicInfo *> * _Nullable)hotMusicInfos errorCode:(ByteRTCKTVErrorCode)errorCode;

/**
 * @locale zh
 * @type callback
 * @brief 歌曲详细信息回调。
 * @param music 歌曲数据，参看 ByteRTCMusicInfo{@link #ByteRTCMusicInfo}。
 * @param errorCode 错误码，成功时返回 0，其余值参看 ByteRTCKTVErrorCode{@link #ByteRTCKTVErrorCode}。
 */
/**
 * @locale en
 * @type callback
 * @brief The music detail callback.
 * @param music Music information. See ByteRTCMusicInfo{@link #ByteRTCMusicInfo}.
 * @param errorCode Error code. The value 0 indicates success. For the indications of other values, see ByteRTCKTVErrorCode{@link #ByteRTCKTVErrorCode}.
 */
- (void)ktvManager:(ByteRTCKTVManager *)ktvManager onMusicDetailResult:(ByteRTCMusicInfo * _Nullable)music errorCode:(ByteRTCKTVErrorCode)errorCode;

/**
 * @locale zh
 * @type callback
 * @brief 下载成功回调。
 * @param downloadId 下载任务 ID。
 * @param result 下载信息，参看 ByteRTCDownloadResult{@link #ByteRTCDownloadResult}。
 */
/**
 * @locale en
 * @type callback
 * @brief Download success callback.
 * @param downloadId Download task ID.
 * @param result Download result. See ByteRTCDownloadResult{@link #ByteRTCDownloadResult}.
 */
- (void)ktvManager:(ByteRTCKTVManager *)ktvManager onDownloadSuccess:(int)downloadId downloadResult:(ByteRTCDownloadResult *)result;

/**
 * @locale zh
 * @type callback
 * @brief 下载失败回调。
 * @param downloadId 下载任务 ID。
 * @param errorCode 错误码，参看 ByteRTCKTVErrorCode{@link #ByteRTCKTVErrorCode}。
 */
/**
 * @locale en
 * @type callback
 * @brief Download failure callback.
 * @param downloadId Download task ID.
 * @param errorCode Error code. See ByteRTCKTVErrorCode{@link #ByteRTCKTVErrorCode}.
 */
- (void)ktvManager:(ByteRTCKTVManager *)ktvManager onDownloadFailed:(int)downloadId errorCode:(ByteRTCKTVErrorCode)errorCode;

/**
 * @locale zh
 * @type callback
 * @brief 歌曲文件下载进度回调。
 * @param downloadId 下载任务 ID。
 * @param downloadPercentage 下载进度百分比，取值范围 [0,100]。
 */
/**
 * @locale en
 * @type callback
 * @brief Music file download progress callback.
 * @param downloadId Download task ID.
 * @param downloadPercentage The percentage of download progress, in the range of [0,100].
 */
- (void)ktvManager:(ByteRTCKTVManager *)ktvManager onDownloadMusicProgress:(int)downloadId progress:(int)downloadPercentage;

/**
 * @locale zh
 * @type callback
 * @brief 清理文件缓存结果回调。
 * @param errorCode 错误码，非0为失败，参看 ByteRTCKTVErrorCode{@link #ByteRTCKTVErrorCode}。
 */
/**
 * @locale en
 * @type callback
 * @brief Clear Cache result callback.
 * @param errorCode  Error code. See ByteRTCKTVErrorCode{@link #ByteRTCKTVErrorCode}.
 */
- (void)ktvManager:(ByteRTCKTVManager *)ktvManager onClearCacheResult:(ByteRTCKTVErrorCode)errorCode;
@end

/**
 * @locale zh
 * @type api
 * @brief KTV 管理接口。
 */
/**
 * @locale en
 * @hidden currently not available
 * @type api
 * @brief KTV manager interfaces.
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCKTVManager : NSObject

@property(nonatomic, weak) id<ByteRTCKTVManagerDelegate> delegate;

#pragma mark - Core Methods

/**
 * @locale zh
 * @type api
 * @brief 获取歌曲列表。
 * @param pageNumber 页码，默认从 1 开始。
 * @param pageSize 每页显示歌曲的最大数量，取值范围 [1,99]。
 * @param filterType 歌曲过滤方式，参看 ByteRTCMusicFilterType{@link #ByteRTCMusicFilterType}。多个过滤方式可以按位或组合。
 * @note 调用接口后，你会收到 ktvManager:onMusicListResult:totalSize:errorCode:{@link #ByteRTCKTVManagerDelegate#ktvManager:onMusicListResult:totalSize:errorCode:} 回调歌曲列表。
 */
/**
 * @locale en
 * @type api
 * @brief Gets the music list.
 * @param pageNumber Page number. The default value is 1.
 * @param pageSize The number of the music that displays on one page.
 * @param filterType The filter type of the music list. See ByteRTCMusicFilterType{@link #ByteRTCMusicFilterType}. Multiple filters can be combined by the bitwise-or operator.
 * @note After calling this API, you will receive the music list through ktvManager:onMusicListResult:totalSize:errorCode:{@link #ByteRTCKTVManagerDelegate#ktvManager:onMusicListResult:totalSize:errorCode:} callback.
 */
- (void)getMusicList:(int)pageNumber pageSize:(int)pageSize filterType:(ByteRTCMusicFilterType)filterType;

/**
 * @locale zh
 * @type api
 * @brief 根据关键词搜索歌曲。
 * @param keyWord 关键词，字符串长度最大为 20 个字符。
 * @param pageNumber 页码，默认从 1 开始。
 * @param pageSize 每页显示歌曲的最大数量，取值范围 [1,99]。
 * @param filterType 歌曲过滤方式，参看 ByteRTCMusicFilterType{@link #ByteRTCMusicFilterType}。多个过滤方式可以按位或组合。
 * @note 调用接口后，你会收到 ktvManager:onSearchMusicResult:totalSize:errorCode:{@link #ByteRTCKTVManagerDelegate#ktvManager:onSearchMusicResult:totalSize:errorCode:} 回调歌曲列表。
 */
/**
 * @locale en
 * @type api
 * @brief Search music by keywords.
 * @param keyWord Keyword. The string should be no more than 20 characters.
 * @param pageNumber Page number. The default value is 1.
 * @param pageSize The number of the music that displays on one page.
 * @param filterType The filter type of the music list. See ByteRTCMusicFilterType{@link #ByteRTCMusicFilterType}. Multiple filters can be combined by the bitwise-or operator.
 * @note After calling this API, you will receive the music list through ktvManager:onSearchMusicResult:totalSize:errorCode:{@link #ByteRTCKTVManagerDelegate#ktvManager:onSearchMusicResult:totalSize:errorCode:} callback.
 */
- (void)searchMusic:(NSString * _Nonnull)keyWord pageNumber:(int)pageNumber pageSize:(int)pageSize filterType:(ByteRTCMusicFilterType)filterType;

/**
 * @locale zh
 * @type api
 * @brief 根据热榜获取每个榜单的歌曲列表。
 * @param hotType 热榜类别，参看 ByteRTCMusicHotType{@link #ByteRTCMusicHotType}。多个热榜类别可以按位或组合。
 * @param filterType 歌曲过滤方式，参看 ByteRTCMusicFilterType{@link #ByteRTCMusicFilterType}。多个过滤方式可以按位或组合。
 * @note 调用接口后，你会收到 ktvManager:onHotMusicResult:errorCode:{@link #ByteRTCKTVManagerDelegate#ktvManager:onHotMusicResult:errorCode:} 回调歌曲列表。
 */
/**
 * @locale en
 * @type api
 * @brief Gets hot music according to music types.
 * @param hotType Hot music type. See ByteRTCMusicHotType{@link #ByteRTCMusicHotType}. Multiple hot music types can be combined by the bitwise-or operator.
 * @param filterType The filter type of the music list. See ByteRTCMusicFilterType{@link #ByteRTCMusicFilterType}. Multiple filters can be combined by the bitwise-or operator.
 * @note After calling this API, you will receive the music list through ktvManager:onHotMusicResult:errorCode:{@link #ByteRTCKTVManagerDelegate#ktvManager:onHotMusicResult:errorCode:} callback.
 */
- (void)getHotMusic:(ByteRTCMusicHotType)hotType filterType:(ByteRTCMusicFilterType)filterType;

/**
 * @locale zh
 * @type api
 * @brief 获取音乐详细信息。
 * @param musicId 音乐 ID。
 * @note 调用接口后，你会收到 ktvManager:onMusicDetailResult:errorCode:{@link #ByteRTCKTVManagerDelegate#ktvManager:onMusicDetailResult:errorCode:} 回调。
 */
/**
 * @locale en
 * @type api
 * @brief Gets music detail.
 * @param musicId Music ID.
 * @note After calling this API, you will receive the music detail through ktvManager:onMusicDetailResult:errorCode:{@link #ByteRTCKTVManagerDelegate#ktvManager:onMusicDetailResult:errorCode:} callback.
 */
- (void)getMusicDetail:(NSString * _Nonnull)musicId;

/**
 * @locale zh
 * @type api
 * @brief 下载音乐。
 * @param musicId 音乐 ID。
 * @return 下载任务 ID。
 * @note  
 *       + 若音乐下载成功，你会收到 ktvManager:onDownloadSuccess:downloadResult:{@link #ByteRTCKTVManagerDelegate#ktvManager:onDownloadSuccess:downloadResult:} 回调。<br>
 *       + 若音乐下载失败，你会收到 ktvManager:onDownloadFailed:errorCode:{@link #ByteRTCKTVManagerDelegate#ktvManager:onDownloadFailed:errorCode:} 回调。<br>
 *       + 音乐下载进度更新时，你会收到 ktvManager:onDownloadMusicProgress:progress:{@link #ByteRTCKTVManagerDelegate#ktvManager:onDownloadMusicProgress:progress:} 回调。
 */
/**
 * @locale en
 * @type api
 * @brief Download music.
 * @param musicId Music ID.
 * @return Download task ID.
 * @note  
 *       + If the music is successfully downloaded, you will receive ktvManager:onDownloadSuccess:downloadResult:{@link #ByteRTCKTVManagerDelegate#ktvManager:onDownloadSuccess:downloadResult:}.<br>
 *       + If the music fails to download, you will receive ktvManager:onDownloadFailed:errorCode:{@link #ByteRTCKTVManagerDelegate#ktvManager:onDownloadFailed:errorCode:}.<br>
 *       + When the music download progress is updated, you will receive ktvManager:onDownloadMusicProgress:progress:{@link #ByteRTCKTVManagerDelegate#ktvManager:onDownloadMusicProgress:progress:}.
 */
- (int)downloadMusic:(NSString * _Nonnull)musicId;

/**
 * @locale zh
 * @type api
 * @brief 下载歌词。
 * @param musicId 音乐 ID。
 * @param lyricType 歌词文件类型，参看 ByteRTCDownloadLyricType{@link #ByteRTCDownloadLyricType}。
 * @return 下载任务 ID。
 * @note  
 *       + 若歌词下载成功，你会收到 ktvManager:onDownloadSuccess:downloadResult:{@link #ByteRTCKTVManagerDelegate#ktvManager:onDownloadSuccess:downloadResult:} 回调。<br>
 *       + 若歌词下载失败，你会收到 ktvManager:onDownloadFailed:errorCode:{@link #ByteRTCKTVManagerDelegate#ktvManager:onDownloadFailed:errorCode:} 回调。
 */
/**
 * @locale en
 * @type api
 * @brief Download lyrics.
 * @param musicId Music ID.
 * @param lyricType The lyrics file's format. See ByteRTCDownloadLyricType{@link #ByteRTCDownloadLyricType}.
 * @return Download task ID.
 * @note  
 *       + If the lyrics are successfully downloaded, you will receive ktvManager:onDownloadSuccess:downloadResult:{@link #ByteRTCKTVManagerDelegate#ktvManager:onDownloadSuccess:downloadResult:}.<br>
 *       + If the lyrics fail to download, you will receive ktvManager:onDownloadFailed:errorCode:{@link #ByteRTCKTVManagerDelegate#ktvManager:onDownloadFailed:errorCode:}.
 */
- (int)downloadLyric:(NSString * _Nonnull)musicId lyricType:(ByteRTCDownloadLyricType)lyricType;

/**
 * @locale zh
 * @type api
 * @brief 下载 MIDI 文件。
 * @param musicId 音乐 ID。
 * @return 下载任务 ID。
 * @note  
 *       + 若文件下载成功，你会收到 ktvManager:onDownloadSuccess:downloadResult:{@link #ByteRTCKTVManagerDelegate#ktvManager:onDownloadSuccess:downloadResult:} 回调。<br>
 *       + 若文件下载失败，你会收到 ktvManager:onDownloadFailed:errorCode:{@link #ByteRTCKTVManagerDelegate#ktvManager:onDownloadFailed:errorCode:} 回调。
 */
/**
 * @locale en
 * @type api
 * @brief Download MIDI files.
 * @param musicId Music ID.
 * @return Download task ID.
 * @note  
 *       + If the file is successfully downloaded, you will receive ktvManager:onDownloadSuccess:downloadResult:{@link #ByteRTCKTVManagerDelegate#ktvManager:onDownloadSuccess:downloadResult:}.<br>
 *       + If the file fails to download, you will receive ktvManager:onDownloadFailed:errorCode:{@link #ByteRTCKTVManagerDelegate#ktvManager:onDownloadFailed:errorCode:}.
 */
- (int)downloadMidi:(NSString * _Nonnull)musicId;

/**
 * @locale zh
 * @type api
 * @brief 取消下载任务。
 * @param downloadId 下载任务 ID。
 */
/**
 * @locale en
 * @type api
 * @brief Cancels download task.
 * @param downloadId Download task ID.
 */
- (void)cancelDownload:(int)downloadId;

/**
 * @locale zh
 * @type api
 * @brief 清除当前音乐缓存文件，包括音乐音频和歌词。
 */
/**
 * @locale en
 * @type api
 * @brief Clear music cache, including music and lyrics.
 */
- (void)clearCache;

/**
 * @locale zh
 * @type api
 * @brief 设置歌曲文件最大占用的本地缓存。
 * @param maxCacheSizeMB 本地缓存，单位 MB。<br>
 *        设置值小于等于 0 时，使用默认值 1024 MB。
 */
/**
 * @locale en
 * @type api
 * @brief Sets the maximum cache for storing music files.
 * @param maxCacheSizeMB The maximum cache to be set in MB.<br>
 *        If the setting value is less than or equal to 0, it will be adjusted to 1,024 MB.
 */
- (void)setMaxCacheSize:(int)maxCacheSizeMB;

/**
 * @locale zh
 * @type api
 * @brief 获取 KTV 播放器。
 * @return KTV 播放器接口，参看 ByteRTCKTVPlayer{@link #ByteRTCKTVPlayer}。
 */
/**
 * @locale en
 * @type api
 * @brief Gets the KTV player.
 * @return KTV player interfaces. See ByteRTCKTVPlayer{@link #ByteRTCKTVPlayer}.
 */
- (ByteRTCKTVPlayer * _Nullable)getKTVPlayer;


@end

NS_ASSUME_NONNULL_END
