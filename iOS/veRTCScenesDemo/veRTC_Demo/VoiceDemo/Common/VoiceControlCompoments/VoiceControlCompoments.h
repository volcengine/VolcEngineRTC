//
//  VoiceControlCompoments.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/16.
//

#import <Foundation/Foundation.h>
#import "VoiceControlUserModel.h"
#import "VoiceControlRoomModel.h"
#import "VoiceControlRecordModel.h"
#import "VoiceControlAckModel.h"
#import "RoomVideoSession.h"
#import "VoiceSocketIOManager.h"
#import "MenuUpgradeModel.h"
#import "BaseUserModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface VoiceControlCompoments : NSObject

#pragma mark - Get Voice data

/*
 * Reconnect
 * @param block Callback
 */
+ (void)reconnectWithBlock:(void (^)(VoiceControlRoomModel *roomModel, NSArray *users, VoiceControlAckModel *model))block;

/*
 * Issue appID
 * @param uid User ID
 * @param roomId Room ID
 * @param block Callback
 */
+ (void)getAppIDWithUid:(NSString *)uid
                 roomId:(NSString *)roomId
                  block:(void (^)(NSString *appID, VoiceControlAckModel *model))block;

//csGetMeetings
+ (void)getMeetingsWithBlock:(void (^)(NSArray *lists, VoiceControlAckModel *model))block;

+ (void)createMeeting:(NSString *)roomName
             userName:(NSString *)userName
                block:(void (^)(NSString *token,
                                VoiceControlRoomModel *roomModel,
                                NSArray<VoiceControlUserModel *> *lists,
                                VoiceControlAckModel *model))block;

/*
 * Join the Voice
 * @param loginModel Login user data
 * @param block Callback
 */
+ (void)joinVoice:(NSString *)roomID
         userName:(NSString *)userName
            block:(void (^)(NSString *token,
                            VoiceControlRoomModel *roomModel,
                            NSArray<VoiceControlUserModel *> *lists,
                            VoiceControlAckModel *model))block;

/*
 * Leave Voice
 */
+ (void)leaveVoice;

/*
 * Get the participant list/participant status
 * @param userId User ID
 * @param block Callback
 */
+ (void)getRaiseHandsWithBlock:(void (^)(NSArray<VoiceControlUserModel *> *userLists, VoiceControlAckModel *model))block;


+ (void)getAudiencesWithBlock:(void (^)(NSArray<VoiceControlUserModel *> *userLists, VoiceControlAckModel *model))block;

#pragma mark - Control Voice status

/*
 * Invite Mic
 * @param userId Host ID to be handed over
 * @param block Callback
 */
+ (void)inviteMic:(NSString *)userId block:(void (^)(VoiceControlAckModel *model))block;

/*
 * Confirmation
 * @param userId Users who want to mute, do not pass means to mute all users
 * @param block Callback
 */
+ (void)confirmMicWithBlock:(void (^)(VoiceControlAckModel *model))block;

/*
 * Raise your hand in wheat
 * @param userId ID of the user who requested to turn on the microphone
 * @param block Callback
 */
+ (void)raiseHandsMicWithBlock:(void (^)(VoiceControlAckModel *model))block;

/*
 * Agree to serve
 * @param userId ID of the user who requested to turn on the microphone
 * @param block Callback
 */
+ (void)agreeMic:(NSString *)userId block:(void (^)(VoiceControlAckModel *model))block;

// Download (user)
+ (void)offSelfMicWithBlock:(void (^)(VoiceControlAckModel *model))block;

// Switch to normal user (host)
+ (void)offMic:(NSString *)userId block:(void (^)(VoiceControlAckModel *model))block;

/*
 * Turn On Mic
 */
+ (void)muteMic;

/*
 * Turn Off Mic
 */
+ (void)unmuteMic;


#pragma mark - Notification message

/*
 * User join Notification
 * @param block Callback
 */
+ (void)onJoinMeetingWithBlock:(void (^)(VoiceControlUserModel *userModel))block;

/*
 * User leave Notification
 * @param block Callback
 */
+ (void)onLeaveMeetingWithBlock:(void (^)(VoiceControlUserModel *userModel))block;

/*
 * User raises hand Notification
 * @param block Callback
 */
+ (void)onRaiseHandsMicWithBlock:(void (^)(NSString *uid))block;

/*
 * Audience receives the invitation to the microphone Notification
 * @param block Callback
 */
+ (void)onInviteMicWithBlock:(void (^)(NSString *uid))block;

/*
 * Successful user registration Notification
 * @param block Callback
 */
+ (void)onMicOnWithBlock:(void (^)(VoiceControlUserModel *userModel))block;

/*
 * Successful user download Notification
 * @param block Callback
 */
+ (void)onMicOffWithBlock:(void (^)(NSString *uid))block;

/*
 * User silent notification Notification
 * @param block Callback
 */
+ (void)onMuteMicWithBlock:(void (^)(NSString *uid))block;

/*
 * User unmute notification Notification
 * @param block Callback
 */
+ (void)onUnmuteMic:(void (^)(NSString * _Nonnull uid))block;

/*
 * Is over Notification
 * @param block Callback
 */
+ (void)onMeetingEnd:(void (^)(BOOL result))block;

/*
 * Handover host Notification
 * @param block Callback
 */
+ (void)onHostChange:(void (^)(NSString *formerHostID, VoiceControlUserModel *hostUser))block;

#pragma mark - Upgrade

/*
 * Get updates
 * @param block Callback
 */
+ (void)getAuditStateAppVersion:(NSString *)version block:(void (^)(MenuUpgradeModel *upgradeModel, VoiceControlAckModel *ackModel))block;

#pragma mark - Login

/*
 * login
 * @param name User Name

 * @param block Callback
 */
+ (void)login:(NSString *)name block:(void (^)(BaseUserModel *userModel, VoiceControlAckModel *ackModel))block;

/*
 * Change User Name
 * Change User Name
 * @param block Callback
 */
+ (void)changeUserName:(BaseUserModel *)userModel block:(void (^)(VoiceControlAckModel *ackModel))block;

/*
 * Verify login token
 */
+ (void)verifyLoginToken;


@end

NS_ASSUME_NONNULL_END
