//
//  MeetingRTCManager.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/3.
//

#import <Foundation/Foundation.h>
#import <MacByteRtcEngineKit/byte_rtc_engine_kit.h>
#import <MacByteRtcEngineKit/byte_rtc_engine_kit_internal.h>
#import <MacByteRtcEngineKit/byte_rtc_engine_kit_advance.h>
#import <MacByteRtcEngineKit/ByteRtcEngineKitDefines.h>
#import <MacByteRtcEngineKit/ByteRtcRoom.h>

#import "LoginModel.h"
#import "SetingModel.h"
#import "ParamModel.h"

@class MeetingRTCManager;

@protocol MeetingRTCManagerDelegate <NSObject>

- (void)rtcManager:(MeetingRTCManager * _Nonnull)rtcManager didStreamAdded:(NSString *_Nullable)streamsUid;

- (void)rtcManager:(MeetingRTCManager * _Nonnull)rtcManager didScreenStreamAdded:(NSString *_Nullable)screenStreamsUid;

- (void)rtcManager:(MeetingRTCManager *_Nonnull)rtcManager didStreamRemoved:(NSString *_Nullable)streamsUid;

- (void)rtcManager:(MeetingRTCManager *_Nonnull)rtcManager didScreenStreamRemoved:(NSString *_Nonnull)screenStreamsUid;

- (void)rtcManager:(MeetingRTCManager *_Nonnull)rtcManager reportRtcParamModel:(ParamModel *_Nonnull)paramModel;

- (void)rtcManager:(MeetingRTCManager *_Nonnull)rtcManager reportAudioVolume:(NSDictionary<NSString *, ByteRtcAudioVolumeInfo *> *_Nonnull)volumeInfo;

@end

@interface MeetingRTCManager : NSObject

@property (nonatomic, weak) id<MeetingRTCManagerDelegate> _Nullable delegate;

#pragma mark - Basic Method

/*
 * RTC Manager Singleton
 */
+ (MeetingRTCManager *_Nullable)shareMeetingRTCManager;

/*
 * Create RTC engine
 */
- (void)createEngine:(NSString *_Nullable)appID;

/*
 * Set a set of video attributes to be released, and each attribute corresponds to a set of video parameters, such as resolution, frame rate, bit rate, etc.
 */
- (void)setVideoProfiles:(SetingModel *_Nullable)setingModel;

/*
 * Open preview screen (do not push stream)
 * @param view Preview screen
 */
- (void)startPreview:(NSView *_Nullable)view;

/*
 * Close the preview screen
 */
- (void)stopPreview;

/*
 * Turn on/off speaker volume alert
 * @param interval Specify the time interval for the volume alert
 * @param smooth The sensitivity of the volume prompt, the sensitivity range is [0,10]. The larger the number, the more sensitive the fluctuation; the smaller the number, the smoother the fluctuation
 */
- (int)enableAudioVolumeIndication:(NSInteger)interval
                            smooth:(NSInteger)smooth;

/*
 * Get the current version number of the SDK
 */
- (NSString *_Nullable)getSdkVersion;

/*
 * Join room
 * @param uid User ID
 * @param roomId room number
 * @param token token
 */
- (void)joinChannelWithUser:(LoginModel *_Nullable)loginModel;

/*
 * Leave Channel
 * @param block Callback
 */
- (void)leaveChannel:(void(^ _Nullable)(BOOL result))block;

/*
 * Bind the display window of the local video stream
 * @param videoCanvas Video attributes
 */
- (void)setupLocalVideo:(ByteRtcVideoCanvas *_Nullable)videoCanvas;

/*
 * Bind remote users and display views
 * @param videoCanvas Video attributes
 */
- (void)setupRemoteVideo:(ByteRtcVideoCanvas *_Nullable)videoCanvas;

/*
 * Turn on or turn off local video capture
 * @param isEnableVideo Enable local audio capture (default); NO: disable local audio capture
 */
- (void)enableLocalVideo:(BOOL)isEnableVideo;

/*
 * Turn on/off local audio capture.
 * @param isEnableVideo Enable local audio capture (default); NO: disable local audio capture
 */
- (void)enableLocalAudio:(BOOL)isEnableAudio;

#pragma mark - Device Method
/*
 * Set up audio capture device
 * @param deviceID Device ID
 */
- (int)setMicDevice:(NSString *_Nullable)deviceID;

/*
 * Set the current video capture device
 * @param deviceID Device ID
 */
- (int)setCameraDevice:(NSString *_Nullable)deviceID;

/*
 * Create a collection of audio capture devices
 * @return Audio Device list
 */
- (ByteRtcAudioDeviceCollection * _Nullable)getRecordingDevices;

/*
 * Get the current system video device list
 * @return Video Device list
 */
- (ByteRtcVideoDeviceCollection * _Nullable)getVideoDeviceDevices;

/*
 * Get the current audio capture device id
 * @return Device id
 */
- (NSString *_Nullable)getMicDeviceID;

/*
 * Get the current video capture device id
 * @return Device id
 */
- (NSString *_Nullable)getCameraDeviceID;

#pragma mark - Subscribe Stream
/*
 * Subscribe to the remote audio and video stream in the specified room.
 * @param uid User ID
 */
- (void)subscribeStream:(NSString *_Nullable)uid;

/*
 * Subscribe to the remote audio and screen stream in the specified room.
 * @param uid User ID
 */
- (void)subscribeScreenStream:(NSString * _Nullable)uid;

/*
 * Stop subscribing to the remote audio and video stream specified in the room.
 * @param uid User ID
 */
- (void)unsubscribe:(NSString *_Nullable)uid;

/*
 * Stop subscribing to the remote audio and screen stream specified in the room.
 * @param uid User ID
 */
- (void)unsubscribeScreen:(NSString * _Nullable)uid;

/*
 * Get current subscription Uid
 * @return subscription Uid
 */
- (NSDictionary *_Nullable)getSubscribeUidDic;

#pragma mark - Screen Method

/*
 * Share screen by screen id, share a screen or part of the screen. The user needs to specify the id of the screen they want to share in this method.
 * @param displayId Specify the id of the screen to be shared.
 */
- (void)startScreenCaptureByDisplayId:(int)displayId;

/*
 * This method shares a window or part of the window. Users need to specify the id of the window they want to share in this method.
 * @param displayId Specify the id of the window to be shared.
 */
- (void)startScreenCaptureByWindowId:(int)displayId;

/*
 * Stop screen or window sharing.
 */
- (void)stopScreenCapture;

/*
 * Binds the remote screen view,
 * @param view View
 * @param uid User ID
 */
- (void)setupRemoteScreen:(NSView * _Nullable)view uid:(NSString * _Nullable)uid;

/*
 * Remove all remote screens.
 */
- (void)removeAllRemoteScreen;

/*
 * Get a list of shared objects (application windows and desktops)
 * @return Data lists
 */
- (NSArray<ByteRtcScreenCaptureSourceInfo *> *_Nonnull)getScreenCaptureSourceList;

/*
 * Get a thumbnail of the shared object
 * @param sourceType Source Type
 * @param sourceId Source ID
 * @param maxWidth Max Width
 * @param maxHeight Max Height
 * @return Thumbnail image
 */
- (NSImage *_Nonnull)getScreenCaptureSourceThumbnail:(ByteScreenCaptureSourceType)sourceType sourceId:(intptr_t)sourceId maxWidth:(int)maxWidth maxHeight:(int)maxHeight;

/*
 * Update the encoding parameter configuration of screen sharing.
 */
- (void)updateScreenParameters;

@end
