# ByteRTCRoomDelegate
```objectivec
@protocol ByteRTCRoomDelegate <NSObject>
```

房间事件回调接口


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **void** | [rtcRoom:onRoomStateChanged:withUid:state:extraInfo:](#ByteRTCRoomDelegate-rtcroom-onroomstatechanged-withuid-state-extrainfo) |
| **void** | [rtcRoom:onStreamStateChanged:withUid:state:extraInfo:](#ByteRTCRoomDelegate-rtcroom-onstreamstatechanged-withuid-state-extrainfo) |
| **void** | [rtcRoom:onLeaveRoomWithStats:](#ByteRTCRoomDelegate-rtcroom-onleaveroomwithstats) |
| **void** | [rtcRoom:onAVSyncStateChange:](#ByteRTCRoomDelegate-rtcroom-onavsyncstatechange) |
| **void** | [rtcRoom:onRoomStats:](#ByteRTCRoomDelegate-rtcroom-onroomstats) |
| **void** | [rtcRoom:onLocalStreamStats:](#ByteRTCRoomDelegate-rtcroom-onlocalstreamstats) |
| **void** | [rtcRoom:onRemoteStreamStats:](#ByteRTCRoomDelegate-rtcroom-onremotestreamstats) |
| **void** | [rtcRoom:onUserJoined:elapsed:](#ByteRTCRoomDelegate-rtcroom-onuserjoined-elapsed) |
| **void** | [rtcRoom:onUserLeave:reason:](#ByteRTCRoomDelegate-rtcroom-onuserleave-reason) |
| **void** | [onTokenWillExpire:](#ByteRTCRoomDelegate-ontokenwillexpire) |
| **void** | [rtcRoom:onUserPublishStream:type:](#ByteRTCRoomDelegate-rtcroom-onuserpublishstream-type) |
| **void** | [rtcRoom:onUserUnpublishStream:type:reason:](#ByteRTCRoomDelegate-rtcroom-onuserunpublishstream-type-reason) |
| **void** | [rtcRoom:onUserPublishScreen:type:](#ByteRTCRoomDelegate-rtcroom-onuserpublishscreen-type) |
| **void** | [rtcRoom:onUserUnpublishScreen:type:reason:](#ByteRTCRoomDelegate-rtcroom-onuserunpublishscreen-type-reason) |
| **void** | [rtcRoom:onStreamSubscribed:userId:subscribeConfig:](#ByteRTCRoomDelegate-rtcroom-onstreamsubscribed-userid-subscribeconfig) |
| **void** | [rtcRoom:onRoomMessageReceived:message:](#ByteRTCRoomDelegate-rtcroom-onroommessagereceived-message) |
| **void** | [rtcRoom:onRoomBinaryMessageReceived:message:](#ByteRTCRoomDelegate-rtcroom-onroombinarymessagereceived-message) |
| **void** | [rtcRoom:onUserMessageReceived:message:](#ByteRTCRoomDelegate-rtcroom-onusermessagereceived-message) |
| **void** | [rtcRoom:onUserBinaryMessageReceived:message:](#ByteRTCRoomDelegate-rtcroom-onuserbinarymessagereceived-message) |
| **void** | [rtcRoom:onUserMessageSendResult:error:](#ByteRTCRoomDelegate-rtcroom-onusermessagesendresult-error) |
| **void** | [rtcRoom:onRoomMessageSendResult:error:](#ByteRTCRoomDelegate-rtcroom-onroommessagesendresult-error) |
| **void** | [rtcRoom:onVideoStreamBanned:isBanned:](#ByteRTCRoomDelegate-rtcroom-onvideostreambanned-isbanned) |
| **void** | [rtcRoom:onAudioStreamBanned:isBanned:](#ByteRTCRoomDelegate-rtcroom-onaudiostreambanned-isbanned) |
| **void** | [rtcRoom:onForwardStreamStateChanged:](#ByteRTCRoomDelegate-rtcroom-onforwardstreamstatechanged) |
| **void** | [rtcRoom:onForwardStreamEvent:](#ByteRTCRoomDelegate-rtcroom-onforwardstreamevent) |
| **void** | [rtcRoom:onNetworkQuality:remoteQualities:](#ByteRTCRoomDelegate-rtcroom-onnetworkquality-remotequalities) |


## 函数说明
<span id="ByteRTCRoomDelegate-rtcroom-onroomstatechanged-withuid-state-extrainfo"></span>
### rtcRoom:onRoomStateChanged:withUid:state:extraInfo:
```objectivec

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onRoomStateChanged:(NSString *_Nonnull)roomId withUid:(nonnull NSString *)uid state:(NSInteger)state extraInfo:(NSString *_Nonnull)extraInfo;
```
房间状态改变回调，加入房间、异常退出房间、发生房间相关的警告或错误时会收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| roomId | **NSString*** | 房间 ID。 |
| uid | **NSString*** | 用户 ID。 |
| state | **NSInteger** | 房间状态码。  <br/>• 0: 成功。  <br/>• !0: 失败或异常退房。具体原因参看 [ByteRTCErrorCode](iOS-errorcode.md#bytertcerrorcode) 及 [ByteRTCWarningCode](iOS-errorcode.md#bytertcwarningcode)。异常退出房间，具体原因包括<br/>- -1004：相同 ID 用户在其他端进房； <br/>- -1006：用户被踢出当前房间。 |
| extraInfo | **NSString*** | 额外信息，如 `{"elapsed":1187,"join_type":0}`。<br/>`join_type` 表示加入房间的类型，`0`为首次进房，`1`为重连进房。<br/>`elapsed`表示加入房间耗时，即本地用户从调用 [joinRoomByToken:userInfo:roomConfig:](iOS-api.md#ByteRTCRoom-joinroombytoken-userinfo-roomconfig) 到加入房间成功所经历的时间间隔，单位为 ms。 |


<span id="ByteRTCRoomDelegate-rtcroom-onstreamstatechanged-withuid-state-extrainfo"></span>
### rtcRoom:onStreamStateChanged:withUid:state:extraInfo:
```objectivec

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onStreamStateChanged:(NSString *_Nonnull)roomId withUid:(nonnull NSString *)uid state:(NSInteger)state extraInfo:(NSString *_Nonnull)extraInfo;
```
流状态改变回调，发生流相关的警告或错误时会收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| roomId | **NSString*** | 房间 ID。 |
| uid | **NSString*** | 用户 ID。 |
| state | **NSInteger** | 流状态码，参看 [ByteRTCErrorCode](iOS-errorcode.md#bytertcerrorcode) 及 [ByteRTCWarningCode](iOS-errorcode.md#bytertcwarningcode)。 |
| extraInfo | **NSString*** | 附加信息，目前为空。 |


<span id="ByteRTCRoomDelegate-rtcroom-onleaveroomwithstats"></span>
### rtcRoom:onLeaveRoomWithStats:
```objectivec

- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onLeaveRoomWithStats:(ByteRTCRoomStats *_Nonnull)stats;
```
离开房间成功回调。  <br>
用户调用 [leaveRoom](iOS-api.md#ByteRTCRoom-leaveroom) 方法后，SDK 会停止所有的发布订阅流，并释放所有通话相关的音视频资源。SDK 完成所有的资源释放后通过此回调通知用户。  <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | **ByteRTCRoom*** | ByteRTCRoom 对象。 |
| stats | **ByteRTCRoomStats*** | 保留参数，目前为空。 |


**注意**

+ 用户调用 [leaveRoom](iOS-api.md#ByteRTCRoom-leaveroom) 方法离开房间后，如果立即调用 [destroyRTCVideo](iOS-api.md#ByteRTCVideo-destroyrtcvideo) 方法销毁 RTC 引擎，则将无法收到此回调事件。  
+ 离开房间结束通话后，如果 App 需要使用系统音视频设备，则建议在收到此回调后再初始化音视频设备，否则可能由于 SDK 占用了导致 App 初始化音视频设备失败。  


<span id="ByteRTCRoomDelegate-rtcroom-onavsyncstatechange"></span>
### rtcRoom:onAVSyncStateChange:
```objectivec

- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onAVSyncStateChange:(ByteRTCAVSyncState)state;
```
发布端调用 [setMultiDeviceAVSync:](iOS-api.md#ByteRTCRoom-setmultideviceavsync) 后音视频同步状态发生改变时，会收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | **ByteRTCRoom*** | ByteRTCRoom 实例 |
| state | **ByteRTCAVSyncState** | 音视频同步状态，参看 [ByteRTCAVSyncState](iOS-keytype.md#bytertcavsyncstate)。 |


<span id="ByteRTCRoomDelegate-rtcroom-onroomstats"></span>
### rtcRoom:onRoomStats:
```objectivec

- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onRoomStats:(ByteRTCRoomStats *_Nonnull)stats;
```
房间内通话统计信息回调。   <br>
用户进房开始通话后，每 2s 收到一次本回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | **ByteRTCRoom*** | ByteRTCRoom 对象。 |
| stats | **ByteRTCRoomStats*** | 当前 ByteRTCRoom 统计数据，详见：[ByteRTCRoomStats](iOS-keytype.md#bytertcroomstats) |


<span id="ByteRTCRoomDelegate-rtcroom-onlocalstreamstats"></span>
### rtcRoom:onLocalStreamStats:
```objectivec

- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onLocalStreamStats:(ByteRTCLocalStreamStats *_Nonnull)stats;
```
本地流数据统计以及网络质量回调。  <br>
本地用户发布流成功后，SDK 会周期性（2s）的通过此回调事件通知用户发布的流在此次统计周期内的质量统计信息。  <br>
统计信息通过 [ByteRTCLocalStreamStats](iOS-keytype.md#bytertclocalstreamstats) 类型的回调参数传递给用户，其中包括发送音视频比特率、发送帧率、编码帧率，网络质量等。  <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | **ByteRTCRoom*** | ByteRTCRoom 对象。 |
| stats | **ByteRTCLocalStreamStats*** | 当前房间本地流数据统计。详见：[ByteRTCLocalStreamStats](iOS-keytype.md#bytertclocalstreamstats) |


<span id="ByteRTCRoomDelegate-rtcroom-onremotestreamstats"></span>
### rtcRoom:onRemoteStreamStats:
```objectivec

- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onRemoteStreamStats:(ByteRTCRemoteStreamStats *_Nonnull)stats;
```
本地订阅的远端音/视频流数据统计以及网络质量回调。  <br>
本地用户订阅流成功后，SDK 会周期性（2s）的通过此回调事件通知用户订阅的流在此次统计周期内的质量统计信息，包括：发送音视频比特率、发送帧率、编码帧率，网络质量等。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | **ByteRTCRoom*** | ByteRTCRoom 对象。 |
| stats | **ByteRTCRemoteStreamStats*** | 当前房间本地流数据统计。 详见：[ByteRTCRemoteStreamStats](iOS-keytype.md#bytertcremotestreamstats) |


<span id="ByteRTCRoomDelegate-rtcroom-onuserjoined-elapsed"></span>
### rtcRoom:onUserJoined:elapsed:
```objectivec

- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onUserJoined:(ByteRTCUserInfo *_Nonnull)userInfo elapsed:(NSInteger)elapsed;
```
远端可见用户加入房间，或房内隐身用户切换为可见的回调。<br>
1. 远端用户调用 [setUserVisibility:](iOS-api.md#ByteRTCRoom-setuservisibility) 方法将自身设为可见后加入房间时，房间内其他用户将收到该事件。  <br>
2. 远端可见用户断网后重新连入房间时，房间内其他用户将收到该事件。  <br>
3. 房间内隐身远端用户调用 [setUserVisibility:](iOS-api.md#ByteRTCRoom-setuservisibility) 方法切换至可见时，房间内其他用户将收到该事件。  <br>
4. 新进房用户会收到进房前已在房内的主播角色用户的进房回调通知。  <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | **ByteRTCRoom*** | ByteRTCRoom 对象。 |
| userInfo | **ByteRTCUserInfo*** | 用户信息，参看 [ByteRTCUserInfo](iOS-keytype.md#bytertcuserinfo)。 |
| elapsed | **NSInteger** | 保留字段，无意义 |


<span id="ByteRTCRoomDelegate-rtcroom-onuserleave-reason"></span>
### rtcRoom:onUserLeave:reason:
```objectivec

- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onUserLeave:(NSString *_Nonnull)uid reason:(ByteRTCUserOfflineReason)reason;
```
远端用户离开房间，或切至不可见时，本地用户会收到此事件

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | **NSString*** | 离开房间，或切至不可见的的远端用户 ID。 |
| reason | **ByteRTCUserOfflineReason** | 用户离开房间的原因：  <br/>• 0: 远端用户调用 [leaveRoom](iOS-api.md#ByteRTCRoom-leaveroom) 主动退出房间。  <br/>• 1: 远端用户因 Token 过期或网络原因等掉线。详细信息请参看[连接状态提示](https://www.volcengine.com/docs/6348/95376) <br/>• 2: 远端用户调用 [setUserVisibility:](iOS-api.md#ByteRTCRoom-setuservisibility) 切换至不可见状态。 <br/>• 3: 服务端调用 OpenAPI 将远端用户踢出房间。 |


<span id="ByteRTCRoomDelegate-ontokenwillexpire"></span>
### onTokenWillExpire:
```objectivec

- (void)onTokenWillExpire:( ByteRTCRoom *_Nonnull)rtcRoom;
```
Token 过期前 30 秒将触发该回调。<br>
调用 [renewToken:](iOS-api.md#ByteRTCRoom-renewtoken) 更新 Token。否则 Token 过期后，用户将被移出房间无法继续进行音视频通话。


<span id="ByteRTCRoomDelegate-rtcroom-onuserpublishstream-type"></span>
### rtcRoom:onUserPublishStream:type:
```objectivec

- (void)rtcRoom:( ByteRTCRoom * _Nonnull)rtcRoom onUserPublishStream:(NSString *_Nonnull)userId type:(ByteRTCMediaStreamType)type;
```
房间内新增远端摄像头/麦克风采集的媒体流流的回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | **ByteRTCRoom*** | ByteRTCRoom 实例 |
| userId | **NSString*** | 远端流发布用户的用户 ID。 |
| type | **ByteRTCMediaStreamType** | 远端媒体流的类型，参看 [ByteRTCMediaStreamType](iOS-keytype.md#bytertcmediastreamtype)。 |


**注意**
当房间内的远端用户调用 [publishStream:](iOS-api.md#ByteRTCRoom-publishstream) 成功发布由摄像头/麦克风采集的媒体流时，本地用户会收到该回调，此时本地用户可以自行选择是否调用 [subscribeStream:mediaStreamType:](iOS-api.md#ByteRTCRoom-subscribestream-mediastreamtype) 订阅此流。

<span id="ByteRTCRoomDelegate-rtcroom-onuserunpublishstream-type-reason"></span>
### rtcRoom:onUserUnpublishStream:type:reason:
```objectivec

- (void)rtcRoom:( ByteRTCRoom * _Nonnull)rtcRoom onUserUnpublishStream:(NSString *_Nonnull)userId type:(ByteRTCMediaStreamType)type reason:(ByteRTCStreamRemoveReason)reason;
```
房间内远端摄像头/麦克风采集的媒体流移除的回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | **ByteRTCRoom*** | ByteRTCRoom 实例 |
| userId | **NSString*** | 移除的远端流发布用户的用户 ID。 |
| type | **ByteRTCMediaStreamType** | 移除的远端流类型，参看 [ByteRTCMediaStreamType](iOS-keytype.md#bytertcmediastreamtype)。 |
| reason | **ByteRTCStreamRemoveReason** | 远端流移除的原因，参看 [ByteRTCStreamRemoveReason](iOS-keytype.md#bytertcstreamremovereason)。 |


**注意**
收到该回调通知后，你可以自行选择是否调用 [unSubscribeStream:mediaStreamType:](iOS-api.md#ByteRTCRoom-unsubscribestream-mediastreamtype) 取消订阅此流。

<span id="ByteRTCRoomDelegate-rtcroom-onuserpublishscreen-type"></span>
### rtcRoom:onUserPublishScreen:type:
```objectivec

- (void)rtcRoom:( ByteRTCRoom * _Nonnull)rtcRoom onUserPublishScreen:(NSString *_Nonnull)userId type:(ByteRTCMediaStreamType)type;
```
房间内新增远端屏幕共享音视频流的回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | **ByteRTCRoom*** | ByteRTCRoom实例 |
| userId | **NSString*** | 远端流发布用户的用户 ID。 |
| type | **ByteRTCMediaStreamType** | 远端媒体流的类型，参看 [ByteRTCMediaStreamType](iOS-keytype.md#bytertcmediastreamtype)。 |


**注意**
当房间内的远端用户调用 [publishScreen:](iOS-api.md#ByteRTCRoom-publishscreen) 成功发布来自屏幕共享的音视频流时，本地用户会收到该回调，此时本地用户可以自行选择是否调用 [subscribeScreen:mediaStreamType:](iOS-api.md#ByteRTCRoom-subscribescreen-mediastreamtype) 订阅此流。

<span id="ByteRTCRoomDelegate-rtcroom-onuserunpublishscreen-type-reason"></span>
### rtcRoom:onUserUnpublishScreen:type:reason:
```objectivec

- (void)rtcRoom:( ByteRTCRoom * _Nonnull)rtcRoom onUserUnpublishScreen:(NSString *_Nonnull)userId type:(ByteRTCMediaStreamType)type reason:(ByteRTCStreamRemoveReason)reason;
```
房间内远端屏幕共享音视频流移除的回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | **ByteRTCRoom*** | ByteRTCRoom 实例 |
| userId | **NSString*** | 移除的远端流发布用户的用户 ID。 |
| type | **ByteRTCMediaStreamType** | 移除的远端流类型，参看 [ByteRTCMediaStreamType](iOS-keytype.md#bytertcmediastreamtype)。 |
| reason | **ByteRTCStreamRemoveReason** | 远端流移除的原因，参看 [ByteRTCStreamRemoveReason](iOS-keytype.md#bytertcstreamremovereason)。 |


**注意**
收到该回调通知后，你可以自行选择是否调用 [unSubscribeScreen:mediaStreamType:](iOS-api.md#ByteRTCRoom-unsubscribescreen-mediastreamtype) 取消订阅此流。

<span id="ByteRTCRoomDelegate-rtcroom-onstreamsubscribed-userid-subscribeconfig"></span>
### rtcRoom:onStreamSubscribed:userId:subscribeConfig:
```objectivec

- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onStreamSubscribed:(ByteRTCSubscribeState)state userId:(NSString *_Nonnull)userId subscribeConfig:(ByteRTCSubscribeConfig *_Nonnull)info;
```
关于订阅媒体流状态改变的回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | **ByteRTCRoom*** | ByteRTCRoom 对象 |
| state | **ByteRTCSubscribeState** | 订阅媒体流状态，参看 [ByteRTCSubscribeState](iOS-keytype.md#bytertcsubscribestate) |
| userId | **NSString*** | 流发布用户的用户 ID |
| info | **ByteRTCSubscribeConfig*** | 流的属性，参看 [ByteRTCSubscribeConfig](iOS-keytype.md#bytertcsubscribeconfig) |


**注意**
本地用户收到该回调的时机包括：  + 调用 [subscribeStream:mediaStreamType:](iOS-api.md#ByteRTCRoom-subscribestream-mediastreamtype) 或 [unSubscribeStream:mediaStreamType:](iOS-api.md#ByteRTCRoom-unsubscribestream-mediastreamtype) 订阅/取消订阅指定远端摄像头音视频流后；  

+ 调用 [subscribeScreen:mediaStreamType:](iOS-api.md#ByteRTCRoom-subscribescreen-mediastreamtype) 或 [unSubscribeScreen:mediaStreamType:](iOS-api.md#ByteRTCRoom-unsubscribescreen-mediastreamtype) 订阅/取消订阅指定远端屏幕共享流后。


<span id="ByteRTCRoomDelegate-rtcroom-onroommessagereceived-message"></span>
### rtcRoom:onRoomMessageReceived:message:
```objectivec

- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onRoomMessageReceived:(NSString *_Nonnull)uid message:(NSString *_Nonnull)message;
```
收到房间中调用 [sendRoomMessage:](iOS-api.md#ByteRTCRoom-sendroommessage) 发送的广播文本消息时，收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | **ByteRTCRoom*** | ByteRTCRoom 对象 |
| uid | **NSString*** | 消息发送者 ID 。 |
| message | **NSString*** | 收到的文本消息内容。 |


<span id="ByteRTCRoomDelegate-rtcroom-onroombinarymessagereceived-message"></span>
### rtcRoom:onRoomBinaryMessageReceived:message:
```objectivec

- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onRoomBinaryMessageReceived:(NSString *_Nonnull)uid message:(NSData *_Nonnull)message;
```
收到房间中调用 [sendRoomBinaryMessage:](iOS-api.md#ByteRTCRoom-sendroombinarymessage) 发送的广播二进制消息时，收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | **ByteRTCRoom*** | ByteRTCRoom 对象 |
| uid | **NSString*** | 消息发送者 ID 。 |
| message | **NSData*** | 收到的二进制消息内容。 |


<span id="ByteRTCRoomDelegate-rtcroom-onusermessagereceived-message"></span>
### rtcRoom:onUserMessageReceived:message:
```objectivec

- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onUserMessageReceived:(NSString *_Nonnull)uid message:(NSString *_Nonnull)message;
```
收到来自房间中其他用户通过 [sendUserMessage:message:config:](iOS-api.md#ByteRTCRoom-sendusermessage-message-config) 发来的文本消息时（P2P），会收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | **ByteRTCRoom*** | ByteRTCRoom 对象 |
| uid | **NSString*** | 消息发送者的用户 ID 。 |
| message | **NSString*** | 收到的文本消息内容。 |


<span id="ByteRTCRoomDelegate-rtcroom-onuserbinarymessagereceived-message"></span>
### rtcRoom:onUserBinaryMessageReceived:message:
```objectivec

- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onUserBinaryMessageReceived:(NSString *_Nonnull)uid message:(NSData *_Nonnull)message;
```
收到来自房间中其他用户通过 [sendUserBinaryMessage:message:config:](iOS-api.md#ByteRTCRoom-senduserbinarymessage-message-config) 发来的二进制消息时，会收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | **ByteRTCRoom*** | ByteRTCRoom 对象 |
| uid | **NSString*** | 消息发送者的用户 ID 。 |
| message | **NSData*** | 收到的二进制消息内容。 |


<span id="ByteRTCRoomDelegate-rtcroom-onusermessagesendresult-error"></span>
### rtcRoom:onUserMessageSendResult:error:
```objectivec

- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onUserMessageSendResult:(int64_t)msgid error:(ByteRTCUserMessageSendResult)error;
```
向房间内单个用户发送文本或二进制消息后（P2P），消息发送方会收到该消息发送结果回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | **ByteRTCRoom*** | ByteRTCRoom 对象。 |
| msgid | **int64_t** | 本条消息的 ID。 |
| error | **ByteRTCUserMessageSendResult** | 消息发送结果，详见 [ByteRTCUserMessageSendResult](iOS-keytype.md#bytertcusermessagesendresult) |


**注意**

+ 你应调用 [sendUserMessage:message:config:](iOS-api.md#ByteRTCRoom-sendusermessage-message-config) 向房间内单个用户发送文本消息 
+ 你应调用 [sendUserBinaryMessage:message:config:](iOS-api.md#ByteRTCRoom-senduserbinarymessage-message-config) 向房间内单个用户发送二进制消息


<span id="ByteRTCRoomDelegate-rtcroom-onroommessagesendresult-error"></span>
### rtcRoom:onRoomMessageSendResult:error:
```objectivec

- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onRoomMessageSendResult:(int64_t)msgid error:(ByteRTCRoomMessageSendResult)error;
```
向房间内所有用户群发文本或二进制消息后，消息发送方会收到该消息发送结果回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | **ByteRTCRoom*** | ByteRTCRoom 对象。 |
| msgid | **int64_t** | 本条消息的 ID。 |
| error | **ByteRTCRoomMessageSendResult** | 消息发送结果，详见 [ByteRTCRoomMessageSendResult](iOS-keytype.md#bytertcroommessagesendresult) |


**注意**

+ 你应调用 [sendRoomMessage:](iOS-api.md#ByteRTCRoom-sendroommessage) 向房间内群发文本消息 
+ 你应调用 [sendRoomBinaryMessage:](iOS-api.md#ByteRTCRoom-sendroombinarymessage) 向房间内群发二进制消息


<span id="ByteRTCRoomDelegate-rtcroom-onvideostreambanned-isbanned"></span>
### rtcRoom:onVideoStreamBanned:isBanned:
```objectivec

- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onVideoStreamBanned:(NSString *_Nonnull)uid isBanned:(BOOL)banned;
```
通过调用服务端 BanUserStream/UnbanUserStream 方法禁用/解禁指定房间内指定用户视频流的发送时，触发此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | **NSString*** | 被禁用/解禁的视频流用户 ID |
| banned | **BOOL** | 视频流发送状态 <br/>• true: 视频流发送被禁用 <br/>• false: 视频流发送被解禁 |


**注意**

+ 房间内指定用户被禁止/解禁视频流发送时，房间内所有用户都会收到该回调。  
+ 若被封禁用户断网或退房后再进房，则依然是封禁状态，且房间内所有人会再次收到该回调。  
+ 指定用户被封禁后，房间内其他用户退房后再进房，会再次收到该回调。  
+ 在控制台开启大会模式后，只有被封禁/解禁用户会收到该回调。
+ 同一房间解散后再次创建，房间内状态清空。


<span id="ByteRTCRoomDelegate-rtcroom-onaudiostreambanned-isbanned"></span>
### rtcRoom:onAudioStreamBanned:isBanned:
```objectivec

- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onAudioStreamBanned:(NSString *_Nonnull)uid isBanned:(BOOL)banned;
```
通过调用服务端 BanUserStream/UnbanUserStream 方法禁用/解禁指定房间内指定用户音频流的发送时，触发此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | **NSString*** | 被禁用/解禁的音频流用户 ID |
| banned | **BOOL** | 音频流发送状态 <br/>• true: 音频流发送被禁用 <br/>• false: 音频流发送被解禁 |


**注意**

+ 房间内指定用户被禁止/解禁音频流发送时，房间内所有用户都会收到该回调。  
+ 若被封禁用户断网或退房后再进房，则依然是封禁状态，且房间内所有人会再次收到该回调。  
+ 指定用户被封禁后，房间内其他用户退房后再进房，会再次收到该回调。  
+ 在控制台开启大会模式后，只有被封禁/解禁用户会收到该回调。
+ 同一房间解散后再次创建，房间内状态清空。


<span id="ByteRTCRoomDelegate-rtcroom-onforwardstreamstatechanged"></span>
### rtcRoom:onForwardStreamStateChanged:
```objectivec

- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onForwardStreamStateChanged:(NSArray<ForwardStreamStateInfo *> * _Nonnull)infos;
```
跨房间媒体流转发状态和错误回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | **ByteRTCRoom*** | ByteRTCRoom 对象 |
| infos | **NSArray<ForwardStreamStateInfo*>*** | 跨房间媒体流转发目标房间信息数组，详见 [ForwardStreamStateInfo](iOS-keytype.md#forwardstreamstateinfo) |


<span id="ByteRTCRoomDelegate-rtcroom-onforwardstreamevent"></span>
### rtcRoom:onForwardStreamEvent:
```objectivec

- (void)rtcRoom:( ByteRTCRoom * _Nonnull)rtcRoom onForwardStreamEvent:(NSArray<ForwardStreamEventInfo *> * _Nonnull)infos;
```
跨房间媒体流转发事件回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | **ByteRTCRoom*** | ByteRTCRoom 对象 |
| infos | **NSArray<ForwardStreamEventInfo*>*** | 跨房间媒体流转发目标房间事件数组，详见 [ForwardStreamEventInfo](iOS-keytype.md#forwardstreameventinfo) |


<span id="ByteRTCRoomDelegate-rtcroom-onnetworkquality-remotequalities"></span>
### rtcRoom:onNetworkQuality:remoteQualities:
```objectivec

- (void)rtcRoom:(ByteRTCRoom * _Nonnull)rtcRoom onNetworkQuality:(ByteRTCNetworkQualityStats *_Nonnull)localQuality remoteQualities:(NSArray<ByteRTCNetworkQualityStats*> *_Nonnull)remoteQualities;
```
加入房间并发布或订阅流后， 以每 2 秒一次的频率，报告本地用户和已订阅的远端用户的上下行网络质量信息。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | **ByteRTCRoom*** | ByteRTCRoom 对象 |
| localQuality | **ByteRTCNetworkQualityStats*** | 本端网络质量，详见 [ByteRTCNetworkQualityStats](iOS-keytype.md#bytertcnetworkqualitystats)。 |
| remoteQualities | **NSArray<ByteRTCNetworkQualityStats*>*** | 已订阅用户的网络质量，详见 [ByteRTCNetworkQualityStats](iOS-keytype.md#bytertcnetworkqualitystats)。<br/>@note 更多通话中的监测接口，详见[通话中质量监测](https://www.volcengine.com/docs/6348/106866) |


# ByteRTCVideoDelegate
```objectivec
@protocol ByteRTCVideoDelegate <NSObject>
```

ByteRTCVideoDelegate 协议包含了SDK提供的回调方法，SDK通过代理向应用程序上报一些运行时事件


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **void** | [rtcEngine:onWarning:](#ByteRTCVideoDelegate-rtcengine-onwarning) |
| **void** | [rtcEngine:onError:](#ByteRTCVideoDelegate-rtcengine-onerror) |
| **void** | [rtcEngine:onCreateRoomStateChanged:errorCode:](#ByteRTCVideoDelegate-rtcengine-oncreateroomstatechanged-errorcode) |
| **void** | [rtcEngine:connectionChangedToState:](#ByteRTCVideoDelegate-rtcengine-connectionchangedtostate) |
| **void** | [rtcEngine:networkTypeChangedToType:](#ByteRTCVideoDelegate-rtcengine-networktypechangedtotype) |
| **void** | [rtcEngine:onUserStartAudioCapture:uid:](#ByteRTCVideoDelegate-rtcengine-onuserstartaudiocapture-uid) |
| **void** | [rtcEngine:onUserStopAudioCapture:uid:](#ByteRTCVideoDelegate-rtcengine-onuserstopaudiocapture-uid) |
| **void** | [rtcEngine:onFirstRemoteAudioFrame:](#ByteRTCVideoDelegate-rtcengine-onfirstremoteaudioframe) |
| **void** | [rtcEngine:onLocalAudioPropertiesReport:](#ByteRTCVideoDelegate-rtcengine-onlocalaudiopropertiesreport) |
| **void** | [rtcEngine:onRemoteAudioPropertiesReport:totalRemoteVolume:](#ByteRTCVideoDelegate-rtcengine-onremoteaudiopropertiesreport-totalremotevolume) |
| **void** | [rtcEngine:onActiveSpeaker:uid:](#ByteRTCVideoDelegate-rtcengine-onactivespeaker-uid) |
| **void** | [rtcEngine:onUserStartVideoCapture:uid:](#ByteRTCVideoDelegate-rtcengine-onuserstartvideocapture-uid) |
| **void** | [rtcEngine:onUserStopVideoCapture:uid:](#ByteRTCVideoDelegate-rtcengine-onuserstopvideocapture-uid) |
| **void** | [rtcEngine:onFirstLocalVideoFrameCaptured:withFrameInfo:](#ByteRTCVideoDelegate-rtcengine-onfirstlocalvideoframecaptured-withframeinfo) |
| **void** | [rtcEngine:onFirstRemoteVideoFrameRendered:withFrameInfo:](#ByteRTCVideoDelegate-rtcengine-onfirstremotevideoframerendered-withframeinfo) |
| **void** | [rtcEngine:onFirstRemoteVideoFrameDecoded:withFrameInfo:](#ByteRTCVideoDelegate-rtcengine-onfirstremotevideoframedecoded-withframeinfo) |
| **void** | [rtcEngine:onRemoteVideoSizeChanged:withFrameInfo:](#ByteRTCVideoDelegate-rtcengine-onremotevideosizechanged-withframeinfo) |
| **void** | [rtcEngine:onLocalVideoSizeChanged:withFrameInfo:](#ByteRTCVideoDelegate-rtcengine-onlocalvideosizechanged-withframeinfo) |
| **void** | [rtcEngine:remoteVideoStateChangedOfUid:state:](#ByteRTCVideoDelegate-rtcengine-remotevideostatechangedofuid-state) |
| **void** | [rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:](#ByteRTCVideoDelegate-rtcengine-onaudiodevicestatechanged-device_type-device_state-device_error) |
| **void** | [rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:](#ByteRTCVideoDelegate-rtcengine-onvideodevicestatechanged-device_type-device_state-device_error) |
| **void** | [rtcEngine:onAudioDeviceWarning:deviceType:deviceWarning:](#ByteRTCVideoDelegate-rtcengine-onaudiodevicewarning-devicetype-devicewarning) |
| **void** | [rtcEngine:onVideoDeviceWarning:deviceType:deviceWarning:](#ByteRTCVideoDelegate-rtcengine-onvideodevicewarning-devicetype-devicewarning) |
| **void** | [rtcEngine:onAudioFrameSendStateChanged:rtcUser:state:](#ByteRTCVideoDelegate-rtcengine-onaudioframesendstatechanged-rtcuser-state) |
| **void** | [rtcEngine:onVideoFrameSendStateChanged:rtcUser:state:](#ByteRTCVideoDelegate-rtcengine-onvideoframesendstatechanged-rtcuser-state) |
| **void** | [rtcEngine:onScreenVideoFrameSendStateChanged:rtcUser:state:](#ByteRTCVideoDelegate-rtcengine-onscreenvideoframesendstatechanged-rtcuser-state) |
| **void** | [rtcEngine:onAudioFramePlayStateChanged:rtcUser:state:](#ByteRTCVideoDelegate-rtcengine-onaudioframeplaystatechanged-rtcuser-state) |
| **void** | [rtcEngine:onVideoFramePlayStateChanged:rtcUser:state:](#ByteRTCVideoDelegate-rtcengine-onvideoframeplaystatechanged-rtcuser-state) |
| **void** | [rtcEngine:onScreenVideoFramePlayStateChanged:rtcUser:state:](#ByteRTCVideoDelegate-rtcengine-onscreenvideoframeplaystatechanged-rtcuser-state) |
| **void** | [rtcEngine:onFirstLocalAudioFrame:](#ByteRTCVideoDelegate-rtcengine-onfirstlocalaudioframe) |
| **void** | [rtcEngine:onAudioRouteChanged:](#ByteRTCVideoDelegate-rtcengine-onaudioroutechanged) |
| **void** | [rtcEngine:onSEIMessageReceived:andMessage:](#ByteRTCVideoDelegate-rtcengine-onseimessagereceived-andmessage) |
| **void** | [rtcEngine:onStreamSyncInfoReceived:streamType:data:](#ByteRTCVideoDelegate-rtcengine-onstreamsyncinforeceived-streamtype-data) |
| **void** | [rtcEngine:reportSysStats:](#ByteRTCVideoDelegate-rtcengine-reportsysstats) |
| **void** | [rtcEngine:onLocalAudioStateChanged:error:](#ByteRTCVideoDelegate-rtcengine-onlocalaudiostatechanged-error) |
| **void** | [rtcEngine:onRemoteAudioStateChanged:state:reason:](#ByteRTCVideoDelegate-rtcengine-onremoteaudiostatechanged-state-reason) |
| **void** | [rtcEngine:onLocalVideoStateChanged:withStreamState:withStreamError:](#ByteRTCVideoDelegate-rtcengine-onlocalvideostatechanged-withstreamstate-withstreamerror) |
| **void** | [rtcEngine:onRemoteVideoStateChanged:withVideoState:withVideoStateReason:](#ByteRTCVideoDelegate-rtcengine-onremotevideostatechanged-withvideostate-withvideostatereason) |
| **void** | [rtcEngine:onLoginResult:errorCode:elapsed:](#ByteRTCVideoDelegate-rtcengine-onloginresult-errorcode-elapsed) |
| **void** | [rtcEngineOnLogout:](#ByteRTCVideoDelegate-rtcengineonlogout) |
| **void** | [rtcEngine:onServerParamsSetResult:](#ByteRTCVideoDelegate-rtcengine-onserverparamssetresult) |
| **void** | [rtcEngine:onGetPeerOnlineStatus:status:](#ByteRTCVideoDelegate-rtcengine-ongetpeeronlinestatus-status) |
| **void** | [rtcEngine:onUserMessageReceivedOutsideRoom:message:](#ByteRTCVideoDelegate-rtcengine-onusermessagereceivedoutsideroom-message) |
| **void** | [rtcEngine:onUserBinaryMessageReceivedOutsideRoom:message:](#ByteRTCVideoDelegate-rtcengine-onuserbinarymessagereceivedoutsideroom-message) |
| **void** | [rtcEngine:onUserMessageSendResultOutsideRoom:error:](#ByteRTCVideoDelegate-rtcengine-onusermessagesendresultoutsideroom-error) |
| **void** | [rtcEngine:onServerMessageSendResult:error:message:](#ByteRTCVideoDelegate-rtcengine-onservermessagesendresult-error-message) |
| **void** | [rtcEngine:onNetworkDetectionResult:quality:rtt:lostRate:bitrate:jitter:](#ByteRTCVideoDelegate-rtcengine-onnetworkdetectionresult-quality-rtt-lostrate-bitrate-jitter) |
| **void** | [rtcEngine:onNetworkDetectionStopped:](#ByteRTCVideoDelegate-rtcengine-onnetworkdetectionstopped) |
| **void** | [rtcEngine:onAudioMixingStateChanged:state:error:](#ByteRTCVideoDelegate-rtcengine-onaudiomixingstatechanged-state-error) |
| **void** | [rtcEngine:onAudioMixingPlayingProgress:progress:](#ByteRTCVideoDelegate-rtcengine-onaudiomixingplayingprogress-progress) |
| **void** | [rtcEngine:onPerformanceAlarmsWithMode:roomId:reason:sourceWantedData:](#ByteRTCVideoDelegate-rtcengine-onperformancealarmswithmode-roomid-reason-sourcewanteddata) |
| **void** | [rtcEngine:OnSimulcastSubscribeFallback:](#ByteRTCVideoDelegate-rtcengine-onsimulcastsubscribefallback) |
| **void** | [rtcEngine:onHttpProxyState:](#ByteRTCVideoDelegate-rtcengine-onhttpproxystate) |
| **void** | [rtcEngine:onHttpsProxyState:](#ByteRTCVideoDelegate-rtcengine-onhttpsproxystate) |
| **void** | [rtcEngine:onSocks5ProxyState:cmd:proxy_address:local_address:remote_address:](#ByteRTCVideoDelegate-rtcengine-onsocks5proxystate-cmd-proxy_address-local_address-remote_address) |
| **void** | [rtcEngine:onRecordingStateUpdate:state:error_code:recording_info:](#ByteRTCVideoDelegate-rtcengine-onrecordingstateupdate-state-error_code-recording_info) |
| **void** | [rtcEngine:onRecordingProgressUpdate:process:recording_info:](#ByteRTCVideoDelegate-rtcengine-onrecordingprogressupdate-process-recording_info) |
| **void** | [rtcEngine:onPushPublicStreamResult:publicStreamId:errorCode:](#ByteRTCVideoDelegate-rtcengine-onpushpublicstreamresult-publicstreamid-errorcode) |
| **void** | [rtcEngine:onPlayPublicStreamResult:errorCode:](#ByteRTCVideoDelegate-rtcengine-onplaypublicstreamresult-errorcode) |
| **void** | [rtcEngine:onPublicStreamSEIMessageReceived:andMessage:](#ByteRTCVideoDelegate-rtcengine-onpublicstreamseimessagereceived-andmessage) |
| **void** | [rtcEngine:onFirstPublicStreamVideoFrameDecoded:withFrameInfo:](#ByteRTCVideoDelegate-rtcengine-onfirstpublicstreamvideoframedecoded-withframeinfo) |
| **void** | [rtcEngine:onFirstPublicStreamAudioFrame:](#ByteRTCVideoDelegate-rtcengine-onfirstpublicstreamaudioframe) |
| **void** | [rtcEngine:onCloudProxyConnected:](#ByteRTCVideoDelegate-rtcengine-oncloudproxyconnected) |
| **void** | [rtcEngine:onEchoTestResult:](#ByteRTCVideoDelegate-rtcengine-onechotestresult) |


## 函数说明
<span id="ByteRTCVideoDelegate-rtcengine-onwarning"></span>
### rtcEngine:onWarning:
```objectivec

- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onWarning:(ByteRTCWarningCode)Code;
```
发生警告回调。  <br>
SDK 运行时出现了警告。SDK 通常会自动恢复，警告信息可以忽略。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象。 |
| Code | **ByteRTCWarningCode** | 警告代码，参看 [ByteRTCWarningCode](iOS-errorcode.md#bytertcwarningcode)。 |


<span id="ByteRTCVideoDelegate-rtcengine-onerror"></span>
### rtcEngine:onError:
```objectivec

- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onError:(ByteRTCErrorCode)errorCode;
```
发生错误回调。<br>
SDK 运行时出现了网络或媒体相关的错误，且无法自动恢复时触发此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象。 |
| errorCode | **ByteRTCErrorCode** | 错误代码，参看 [ByteRTCErrorCode](iOS-errorcode.md#bytertcerrorcode)。 |


<span id="ByteRTCVideoDelegate-rtcengine-oncreateroomstatechanged-errorcode"></span>
### rtcEngine:onCreateRoomStateChanged:errorCode:
```objectivec

- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onCreateRoomStateChanged:(NSString * _Nonnull)roomId errorCode:(NSInteger)errorCode;
```
创建房间失败回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| roomId | **NSString*** | 房间 ID。 |
| errorCode | **NSInteger** | 创建房间错误码，具体原因参看 [ByteRTCErrorCode](iOS-errorcode.md#bytertcerrorcode)。 |


<span id="ByteRTCVideoDelegate-rtcengine-connectionchangedtostate"></span>
### rtcEngine:connectionChangedToState:
```objectivec

- (void) rtcEngine:(ByteRTCVideo * _Nonnull)engine connectionChangedToState:(ByteRTCConnectionState) state;
```
SDK 与信令服务器连接状态改变回调。连接状态改变时触发。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象 |
| state | **ByteRTCConnectionState** | 当前 SDK 与信令服务器的连接状态，详见 [ByteRTCConnectionState](iOS-keytype.md#bytertcconnectionstate)。 |


**注意**
更多信息参见 [连接状态提示](https://www.volcengine.com/docs/6348/95376)。

<span id="ByteRTCVideoDelegate-rtcengine-networktypechangedtotype"></span>
### rtcEngine:networkTypeChangedToType:
```objectivec

- (void) rtcEngine:(ByteRTCVideo * _Nonnull)engine networkTypeChangedToType:(ByteRTCNetworkType) type;
```
SDK 当前网络连接类型改变回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象 |
| type | **ByteRTCNetworkType** | SDK 当前的网络连接类型，详见 [ByteRTCNetworkType](iOS-keytype.md#bytertcnetworktype) |


<span id="ByteRTCVideoDelegate-rtcengine-onuserstartaudiocapture-uid"></span>
### rtcEngine:onUserStartAudioCapture:uid:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onUserStartAudioCapture:(NSString* _Nonnull)roomId uid:(NSString *_Nonnull)userId;
```
房间内的可见用户调用 [startAudioCapture](iOS-api.md#ByteRTCVideo-startaudiocapture) 开启音频采集时，房间内其他用户会收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 实例 |
| roomId | **NSString*** | 开启音频采集的用户所在的房间 ID |
| userId | **NSString*** | 开启音频采集的远端用户 ID |


<span id="ByteRTCVideoDelegate-rtcengine-onuserstopaudiocapture-uid"></span>
### rtcEngine:onUserStopAudioCapture:uid:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onUserStopAudioCapture:(NSString* _Nonnull)roomId uid:(NSString *_Nonnull)userId;
```
房间内的可见用户调用 [stopAudioCapture](iOS-api.md#ByteRTCVideo-stopaudiocapture) 关闭音频采集时，房间内其他用户会收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 实例 |
| roomId | **NSString*** | 关闭音频采集的用户所在的房间 ID |
| userId | **NSString*** | 关闭音频采集的远端用户 ID |


<span id="ByteRTCVideoDelegate-rtcengine-onfirstremoteaudioframe"></span>
### rtcEngine:onFirstRemoteAudioFrame:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onFirstRemoteAudioFrame:(ByteRTCRemoteStreamKey * _Nonnull)key;
```
当收到远端流的第一帧音频的时候上报该事件

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象 |
| key | **ByteRTCRemoteStreamKey*** | 远端流信息, 详见 [ByteRTCRemoteStreamKey](iOS-keytype.md#bytertcremotestreamkey) |


**注意**
用户刚收到房间内每一路音频流时，都会收到该回调。

<span id="ByteRTCVideoDelegate-rtcengine-onlocalaudiopropertiesreport"></span>
### rtcEngine:onLocalAudioPropertiesReport:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onLocalAudioPropertiesReport:(NSArray<ByteRTCLocalAudioPropertiesInfo *> * _Nonnull)audioPropertiesInfos;
```
调用 [enableAudioPropertiesReport:](iOS-api.md#ByteRTCVideo-enableaudiopropertiesreport) 后，根据设置的 interval 值，你会周期性地收到此回调，了解本地音频的相关信息。  <br>
本地音频包括使用 RTC SDK 内部机制采集的麦克风音频和屏幕音频。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象 |
| audioPropertiesInfos | **NSArray<ByteRTCLocalAudioPropertiesInfo*>*** | 本地音频信息，详见 [ByteRTCLocalAudioPropertiesInfo](iOS-keytype.md#bytertclocalaudiopropertiesinfo) 。 |


<span id="ByteRTCVideoDelegate-rtcengine-onremoteaudiopropertiesreport-totalremotevolume"></span>
### rtcEngine:onRemoteAudioPropertiesReport:totalRemoteVolume:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onRemoteAudioPropertiesReport:(NSArray<ByteRTCRemoteAudioPropertiesInfo *> * _Nonnull)audioPropertiesInfos totalRemoteVolume:(NSInteger)totalRemoteVolume;
```
远端用户进房后，本地调用 [enableAudioPropertiesReport:](iOS-api.md#ByteRTCVideo-enableaudiopropertiesreport) ，根据设置的 interval 值，本地会周期性地收到此回调，了解订阅的远端用户的音频信息。<br>
远端用户的音频包括使用 RTC SDK 内部机制/自定义机制采集的麦克风音频和屏幕音频。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象 |
| audioPropertiesInfos | **NSArray<ByteRTCRemoteAudioPropertiesInfo*>*** | 远端音频信息，其中包含音频流属性、房间 ID、用户 ID ，详见 [ByteRTCRemoteAudioPropertiesInfo](iOS-keytype.md#bytertcremoteaudiopropertiesinfo)。 |
| totalRemoteVolume | **NSInteger** | 订阅的所有远端流的总音量，范围是 [0,255]。  <br/>• [0,25] 接近无声；  <br/>• [25,75] 为低音量；  <br/>• [76,204] 为中音量；  <br/>• [205,255] 为高音量。 |


<span id="ByteRTCVideoDelegate-rtcengine-onactivespeaker-uid"></span>
### rtcEngine:onActiveSpeaker:uid:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onActiveSpeaker:(NSString * _Nonnull)roomId uid:(NSString *_Nonnull)uid;
```
调用 [enableAudioPropertiesReport:](iOS-api.md#ByteRTCVideo-enableaudiopropertiesreport)  后，根据设置的 `config.interval`，你会周期性地收到此回调，获取房间内的最活跃用户信息。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| roomId | **NSString*** | 房间 ID |
| uid | **NSString*** | 最活跃用户（ActiveSpeaker）的用户 ID |


<span id="ByteRTCVideoDelegate-rtcengine-onuserstartvideocapture-uid"></span>
### rtcEngine:onUserStartVideoCapture:uid:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onUserStartVideoCapture:(NSString * _Nonnull)roomId uid:(NSString * _Nonnull)uid;
```
房间内的可见用户调用 [startVideoCapture](iOS-api.md#ByteRTCVideo-startvideocapture) 开启内部视频采集时，房间中其他用户会收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 实例 |
| roomId | **NSString*** | 开启视频采集的用户所在的房间 ID |
| uid | **NSString*** | 调用 [startVideoCapture](iOS-api.md#ByteRTCVideo-startvideocapture) 接口的远端用户 ID |


<span id="ByteRTCVideoDelegate-rtcengine-onuserstopvideocapture-uid"></span>
### rtcEngine:onUserStopVideoCapture:uid:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onUserStopVideoCapture:(NSString * _Nonnull)roomId uid:(NSString * _Nonnull)uid;
```
房间内的可见用户调用 [stopVideoCapture](iOS-api.md#ByteRTCVideo-stopvideocapture) 关闭内部视频采集时，房间内其他用户会收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 实例 |
| roomId | **NSString*** | 关闭视频采集的用户所在的房间 ID |
| uid | **NSString*** | 关闭视频采集的远端用户 ID |


<span id="ByteRTCVideoDelegate-rtcengine-onfirstlocalvideoframecaptured-withframeinfo"></span>
### rtcEngine:onFirstLocalVideoFrameCaptured:withFrameInfo:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onFirstLocalVideoFrameCaptured:(ByteRTCStreamIndex)streamIndex withFrameInfo:(ByteRTCVideoFrameInfo * _Nonnull)frameInfo;
```
第一帧本地采集的视频/屏幕共享画面在本地视图渲染完成时，收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象 |
| streamIndex | **ByteRTCStreamIndex** | 流属性，参看 [ByteRTCStreamIndex](iOS-keytype.md#bytertcstreamindex) |
| frameInfo | **ByteRTCVideoFrameInfo*** | 视频帧信息，参看 [ByteRTCVideoFrameInfo](iOS-keytype.md#bytertcvideoframeinfo) |


<span id="ByteRTCVideoDelegate-rtcengine-onfirstremotevideoframerendered-withframeinfo"></span>
### rtcEngine:onFirstRemoteVideoFrameRendered:withFrameInfo:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onFirstRemoteVideoFrameRendered:(ByteRTCRemoteStreamKey * _Nonnull)streamKey withFrameInfo:(ByteRTCVideoFrameInfo * _Nonnull)frameInfo;
```
SDK 内部渲染成功远端视频流首帧后，收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象 |
| streamKey | **ByteRTCRemoteStreamKey*** | 远端流信息，参看 [ByteRTCRemoteStreamKey](iOS-keytype.md#bytertcremotestreamkey) |
| frameInfo | **ByteRTCVideoFrameInfo*** | 视频帧信息，参看 [ByteRTCVideoFrameInfo](iOS-keytype.md#bytertcvideoframeinfo) |


<span id="ByteRTCVideoDelegate-rtcengine-onfirstremotevideoframedecoded-withframeinfo"></span>
### rtcEngine:onFirstRemoteVideoFrameDecoded:withFrameInfo:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onFirstRemoteVideoFrameDecoded:(ByteRTCRemoteStreamKey * _Nonnull)streamKey withFrameInfo:(ByteRTCVideoFrameInfo * _Nonnull)frameInfo;
```
SDK 接收并解码远端视频流首帧后，收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象 |
| streamKey | **ByteRTCRemoteStreamKey*** | 远端流信息，参看 [ByteRTCRemoteStreamKey](iOS-keytype.md#bytertcremotestreamkey) |
| frameInfo | **ByteRTCVideoFrameInfo*** | 视频帧信息，参看 [ByteRTCVideoFrameInfo](iOS-keytype.md#bytertcvideoframeinfo) |


<span id="ByteRTCVideoDelegate-rtcengine-onremotevideosizechanged-withframeinfo"></span>
### rtcEngine:onRemoteVideoSizeChanged:withFrameInfo:
```objectivec

- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onRemoteVideoSizeChanged:(ByteRTCRemoteStreamKey *_Nonnull)streamKey withFrameInfo:(ByteRTCVideoFrameInfo *_Nonnull)frameInfo;
```
远端视频大小或旋转信息发生变化时，房间内订阅此视频流的用户会收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象 |
| streamKey | **ByteRTCRemoteStreamKey*** | 流属性，参看 [ByteRTCRemoteStreamKey](iOS-keytype.md#bytertcremotestreamkey) |
| frameInfo | **ByteRTCVideoFrameInfo*** | 视频帧信息，参看 [ByteRTCVideoFrameInfo](iOS-keytype.md#bytertcvideoframeinfo) |


<span id="ByteRTCVideoDelegate-rtcengine-onlocalvideosizechanged-withframeinfo"></span>
### rtcEngine:onLocalVideoSizeChanged:withFrameInfo:
```objectivec

- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onLocalVideoSizeChanged:(ByteRTCStreamIndex)streamIndex withFrameInfo:(ByteRTCVideoFrameInfo *_Nonnull)frameInfo;
```
本地视频大小或旋转信息发生变化时，收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象 |
| streamIndex | **ByteRTCStreamIndex** | 流属性，参看 [ByteRTCStreamIndex](iOS-keytype.md#bytertcstreamindex) |
| frameInfo | **ByteRTCVideoFrameInfo*** | 视频帧信息，参看 [ByteRTCVideoFrameInfo](iOS-keytype.md#bytertcvideoframeinfo) |


<span id="ByteRTCVideoDelegate-rtcengine-remotevideostatechangedofuid-state"></span>
### rtcEngine:remoteVideoStateChangedOfUid:state:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine remoteVideoStateChangedOfUid:(NSString * _Nonnull)uid state:(ByteRTCRemoteVideoState)state;
```
远端视频流状态发生改变回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象，参考: [ByteRTCVideo](iOS-api.md#bytertcvideo) |
| uid | **NSString*** | 发生视频流状态改变的远端用户的用户ID |
| state | **ByteRTCRemoteVideoState** | 变更后的远端视频流状态，详见类型 [ByteRTCRemoteVideoState](iOS-keytype.md#bytertcremotevideostate) |


<span id="ByteRTCVideoDelegate-rtcengine-onaudiodevicestatechanged-device_type-device_state-device_error"></span>
### rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onAudioDeviceStateChanged:(NSString*_Nonnull)device_id device_type:(ByteRTCAudioDeviceType)device_type device_state:(ByteRTCMediaDeviceState)device_state device_error:(ByteRTCMediaDeviceError)device_error;
```
音频设备状态回调。提示音频采集、音频播放等设备的状态。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 实例 |
| device_id | **NSString*** | 设备 ID |
| device_type | **ByteRTCAudioDeviceType** | 设备类型，参看 [ByteRTCAudioDeviceType](iOS-keytype.md#bytertcaudiodevicetype)。 |
| device_state | **ByteRTCMediaDeviceState** | 设备状态，参看 [ByteRTCMediaDeviceState](iOS-keytype.md#bytertcmediadevicestate)。 |
| device_error | **ByteRTCMediaDeviceError** | 设备错误类型，参看 [ByteRTCMediaDeviceError](iOS-keytype.md#bytertcmediadeviceerror)。 |


<span id="ByteRTCVideoDelegate-rtcengine-onvideodevicestatechanged-device_type-device_state-device_error"></span>
### rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onVideoDeviceStateChanged:(NSString*_Nonnull)device_id device_type:(ByteRTCVideoDeviceType)device_type device_state:(ByteRTCMediaDeviceState)device_state device_error:(ByteRTCMediaDeviceError)device_error;
```
视频设备状态回调。提示摄像头视频采集、屏幕视频采集等设备的状态。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 实例 |
| device_id | **NSString*** | 设备 ID |
| device_type | **ByteRTCVideoDeviceType** | 设备类型，参看 [ByteRTCVideoDeviceType](iOS-keytype.md#bytertcvideodevicetype)。 |
| device_state | **ByteRTCMediaDeviceState** | 设备状态，参看 [ByteRTCMediaDeviceState](iOS-keytype.md#bytertcmediadevicestate)。 |
| device_error | **ByteRTCMediaDeviceError** | 设备错误类型，参看 [ByteRTCMediaDeviceError](iOS-keytype.md#bytertcmediadeviceerror)。 |


<span id="ByteRTCVideoDelegate-rtcengine-onaudiodevicewarning-devicetype-devicewarning"></span>
### rtcEngine:onAudioDeviceWarning:deviceType:deviceWarning:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onAudioDeviceWarning:(NSString*_Nonnull)deviceId deviceType:(ByteRTCAudioDeviceType)deviceType deviceWarning:(ByteRTCMediaDeviceWarning)deviceWarning;
```
音频设备警告回调。音频设备包括音频采集设备和音频渲染设备。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象 |
| deviceId | **NSString*** | 设备 ID |
| deviceType | **ByteRTCAudioDeviceType** | 参看 [ByteRTCAudioDeviceType](iOS-keytype.md#bytertcaudiodevicetype) |
| deviceWarning | **ByteRTCMediaDeviceWarning** | 参看 [ByteRTCMediaDeviceWarning](iOS-keytype.md#bytertcmediadevicewarning) |


<span id="ByteRTCVideoDelegate-rtcengine-onvideodevicewarning-devicetype-devicewarning"></span>
### rtcEngine:onVideoDeviceWarning:deviceType:deviceWarning:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onVideoDeviceWarning:(NSString*_Nonnull)deviceId deviceType:(ByteRTCVideoDeviceType)deviceType deviceWarning:(ByteRTCMediaDeviceWarning)deviceWarning;
```
视频设备警告回调。视频设备包括视频采集设备。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象 |
| deviceId | **NSString*** | 设备 ID |
| deviceType | **ByteRTCVideoDeviceType** | 参看 [ByteRTCVideoDeviceType](iOS-keytype.md#bytertcvideodevicetype) |
| deviceWarning | **ByteRTCMediaDeviceWarning** | 参看 [ByteRTCMediaDeviceWarning](iOS-keytype.md#bytertcmediadevicewarning) |


<span id="ByteRTCVideoDelegate-rtcengine-onaudioframesendstatechanged-rtcuser-state"></span>
### rtcEngine:onAudioFrameSendStateChanged:rtcUser:state:
```objectivec

- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onAudioFrameSendStateChanged:(NSString * _Nonnull)roomId rtcUser:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFrameSendState)state;
```
音频首帧发送状态改变时，收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象 |
| roomId | **NSString*** | 音频流发布用户所在的房间 ID |
| user | **ByteRTCUser*** | 本地用户信息，详见 [ByteRTCUser](iOS-keytype.md#bytertcuser) |
| state | **ByteRTCFirstFrameSendState** | 首帧发送状态，详见 [ByteRTCFirstFrameSendState](iOS-keytype.md#bytertcfirstframesendstate) |


<span id="ByteRTCVideoDelegate-rtcengine-onvideoframesendstatechanged-rtcuser-state"></span>
### rtcEngine:onVideoFrameSendStateChanged:rtcUser:state:
```objectivec

- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onVideoFrameSendStateChanged:(NSString * _Nonnull)roomId rtcUser:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFrameSendState)state;
```
视频首帧发送状态改变时，收到此回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象 |
| roomId | **NSString*** | 视频流发布用户所在的房间 ID |
| user | **ByteRTCUser*** | 本地用户信息，详见 [ByteRTCUser](iOS-keytype.md#bytertcuser) |
| state | **ByteRTCFirstFrameSendState** | 首帧发送状态，详见 [ByteRTCFirstFrameSendState](iOS-keytype.md#bytertcfirstframesendstate) |


<span id="ByteRTCVideoDelegate-rtcengine-onscreenvideoframesendstatechanged-rtcuser-state"></span>
### rtcEngine:onScreenVideoFrameSendStateChanged:rtcUser:state:
```objectivec

- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onScreenVideoFrameSendStateChanged:(NSString * _Nonnull)roomId rtcUser:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFrameSendState)state;
```
屏幕共享流视频首帧发送状态改变时，收到此回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象。 |
| roomId | **NSString*** | 屏幕流发布用户所在的房间 ID |
| user | **ByteRTCUser*** | 本地用户信息，参看 [ByteRTCUser](iOS-keytype.md#bytertcuser) |
| state | **ByteRTCFirstFrameSendState** | 首帧发送状态，参看 [ByteRTCFirstFrameSendState](iOS-keytype.md#bytertcfirstframesendstate) |


<span id="ByteRTCVideoDelegate-rtcengine-onaudioframeplaystatechanged-rtcuser-state"></span>
### rtcEngine:onAudioFramePlayStateChanged:rtcUser:state:
```objectivec

- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onAudioFramePlayStateChanged:(NSString * _Nonnull)roomId rtcUser:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFramePlayState)state;
```
音频首帧播放状态改变时，收到此回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象。 |
| roomId | **NSString*** | 音频流发布用户所在的房间 ID |
| user | **ByteRTCUser*** | 音频流来源的用户信息，参看 [ByteRTCUser](iOS-keytype.md#bytertcuser) |
| state | **ByteRTCFirstFramePlayState** | 首帧播放状态，参看 [ByteRTCFirstFramePlayState](iOS-keytype.md#bytertcfirstframeplaystate) |


<span id="ByteRTCVideoDelegate-rtcengine-onvideoframeplaystatechanged-rtcuser-state"></span>
### rtcEngine:onVideoFramePlayStateChanged:rtcUser:state:
```objectivec

- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onVideoFramePlayStateChanged:(NSString * _Nonnull)roomId rtcUser:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFramePlayState)state;
```
视频首帧播放状态改变时，收到此回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象。 |
| user | **ByteRTCUser*** | 视频流来源的用户信息，参看 [ByteRTCUser](iOS-keytype.md#bytertcuser) |
| roomId | **NSString*** | 视频流发布用户所在的房间 ID |
| state | **ByteRTCFirstFramePlayState** | 首帧播放状态，参看 [ByteRTCFirstFramePlayState](iOS-keytype.md#bytertcfirstframeplaystate) |


<span id="ByteRTCVideoDelegate-rtcengine-onscreenvideoframeplaystatechanged-rtcuser-state"></span>
### rtcEngine:onScreenVideoFramePlayStateChanged:rtcUser:state:
```objectivec

- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onScreenVideoFramePlayStateChanged:(NSString * _Nonnull)roomId rtcUser:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFramePlayState)state;
```
屏幕共享流视频首帧播放状态改变时，收到此回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象。 |
| roomId | **NSString*** | 屏幕流发布用户所在的房间 ID |
| user | **ByteRTCUser*** | 屏幕共享流来源的用户信息，参看 [ByteRTCUser](iOS-keytype.md#bytertcuser) |
| state | **ByteRTCFirstFramePlayState** | 首帧播放状态，参看 [ByteRTCFirstFramePlayState](iOS-keytype.md#bytertcfirstframeplaystate) |


<span id="ByteRTCVideoDelegate-rtcengine-onfirstlocalaudioframe"></span>
### rtcEngine:onFirstLocalAudioFrame:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onFirstLocalAudioFrame:(ByteRTCStreamIndex) streamIndex;
```
发布音频流时，采集到第一帧音频帧，收到该回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象 |
| streamIndex | **ByteRTCStreamIndex** | 音频流属性, 详见 [ByteRTCStreamIndex](iOS-keytype.md#bytertcstreamindex) |


**注意**
如果发布音频流时，未开启本地音频采集，SDK 会推送静音帧，也会收到此回调。

<span id="ByteRTCVideoDelegate-rtcengine-onaudioroutechanged"></span>
### rtcEngine:onAudioRouteChanged:
```objectivec

- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onAudioRouteChanged:(ByteRTCAudioRoute)device;
```
音频播放路由变化时，收到该回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| device | **ByteRTCAudioRoute** | 新的音频播放路由，详见 [ByteRTCAudioRoute](iOS-keytype.md#bytertcaudioroute) |


**注意**
插拔音频外设，或调用 [setAudioRoute:](iOS-api.md#ByteRTCVideo-setaudioroute) 都可能触发音频路由切换，详见[移动端设置音频路由](https://www.volcengine.com/docs/6348/117836) 。

<span id="ByteRTCVideoDelegate-rtcengine-onseimessagereceived-andmessage"></span>
### rtcEngine:onSEIMessageReceived:andMessage:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onSEIMessageReceived:(ByteRTCRemoteStreamKey* _Nonnull)remoteStreamKey andMessage:(NSData* _Nonnull)message;
```
收到通过调用 [sendSEIMessage:andMessage:andRepeatCount:](iOS-api.md#ByteRTCVideo-sendseimessage-andmessage-andrepeatcount) 带有 SEI 消息的视频帧时，收到此回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | 当前 ByteRTCVideo 实例。 |
| remoteStreamKey | **ByteRTCRemoteStreamKey*** | 包含 SEI 发送者的用户名，所在的房间名和媒体流，参看 [ByteRTCRemoteStreamKey](iOS-keytype.md#bytertcremotestreamkey) |
| message | **NSData*** | 收到的 SEI 消息内容 |


<span id="ByteRTCVideoDelegate-rtcengine-onstreamsyncinforeceived-streamtype-data"></span>
### rtcEngine:onStreamSyncInfoReceived:streamType:data:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onStreamSyncInfoReceived:(ByteRTCRemoteStreamKey* _Nonnull)remoteStreamKey streamType:(ByteRTCSyncInfoStreamType)streamType data:(NSData* _Nonnull)data;
```
音频流同步信息回调。可以通过此回调，在远端用户调用 [sendStreamSyncInfo:config:](iOS-api.md#ByteRTCVideo-sendstreamsyncinfo-config) 发送音频流同步消息后，收到远端发送的音频流同步信息。  <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | 当前 ByteRTCVideo 实例。 |
| remoteStreamKey | **ByteRTCRemoteStreamKey*** | 远端流信息，详见 [ByteRTCRemoteStreamKey](iOS-keytype.md#bytertcremotestreamkey) 。 |
| streamType | **ByteRTCSyncInfoStreamType** | 媒体流类型，详见 [ByteRTCSyncInfoStreamType](iOS-keytype.md#bytertcsyncinfostreamtype) 。 |
| data | **NSData*** | 消息内容。 |


<span id="ByteRTCVideoDelegate-rtcengine-reportsysstats"></span>
### rtcEngine:reportSysStats:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine reportSysStats:(const ByteRTCSysStats * _Nonnull)stats;
```
报告当前设备 cpu 与 memory 使用率，每 2s 触发一次。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象 |
| stats | **const ByteRTCSysStats*** | cpu 和 memory 使用率信息，详见 [ByteRTCSysStats](iOS-keytype.md#bytertcsysstats) 数据类型 |


<span id="ByteRTCVideoDelegate-rtcengine-onlocalaudiostatechanged-error"></span>
### rtcEngine:onLocalAudioStateChanged:error:
```objectivec

- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onLocalAudioStateChanged:(ByteRTCLocalAudioStreamState)state error:(ByteRTCLocalAudioStreamError)error;
```
本地音频流的状态发生改变时，收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象 |
| state | **ByteRTCLocalAudioStreamState** | 本地音频设备的当前状态，详见 [ByteRTCLocalAudioStreamState](iOS-keytype.md#bytertclocalaudiostreamstate) |
| error | **ByteRTCLocalAudioStreamError** | 本地音频流状态改变时的错误码，详见 [ByteRTCLocalAudioStreamError](iOS-keytype.md#bytertclocalaudiostreamerror) |


<span id="ByteRTCVideoDelegate-rtcengine-onremoteaudiostatechanged-state-reason"></span>
### rtcEngine:onRemoteAudioStateChanged:state:reason:
```objectivec

- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onRemoteAudioStateChanged:(ByteRTCRemoteStreamKey * _Nonnull)key state:(ByteRTCRemoteAudioState)state reason:(ByteRTCRemoteAudioStateChangeReason)reason;
```
订阅的远端音频流状态发生改变时，收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象 |
| key | **ByteRTCRemoteStreamKey*** | 远端流信息, 详见 [ByteRTCRemoteStreamKey](iOS-keytype.md#bytertcremotestreamkey) |
| state | **ByteRTCRemoteAudioState** | 远端音频流的当前状态，详见 [ByteRTCRemoteAudioState](iOS-keytype.md#bytertcremoteaudiostate) |
| reason | **ByteRTCRemoteAudioStateChangeReason** | 远端音频流状态改变的原因，详见 [ByteRTCRemoteAudioStateChangeReason](iOS-keytype.md#bytertcremoteaudiostatechangereason) |


<span id="ByteRTCVideoDelegate-rtcengine-onlocalvideostatechanged-withstreamstate-withstreamerror"></span>
### rtcEngine:onLocalVideoStateChanged:withStreamState:withStreamError:
```objectivec

- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onLocalVideoStateChanged:(ByteRTCStreamIndex)streamIndex withStreamState:(ByteRTCLocalVideoStreamState)state withStreamError:(ByteRTCLocalVideoStreamError)error;
```
本地视频流的状态发生改变时，收到该事件。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象 |
| streamIndex | **ByteRTCStreamIndex** | 流属性，参看 [ByteRTCStreamIndex](iOS-keytype.md#bytertcstreamindex) |
| state | **ByteRTCLocalVideoStreamState** | 本地视频流的当前状态，参看 [ByteRTCLocalVideoStreamState](iOS-keytype.md#bytertclocalvideostreamstate) |
| error | **ByteRTCLocalVideoStreamError** | 本地视频状态改变时的错误码，参看 [ByteRTCLocalVideoStreamError](iOS-keytype.md#bytertclocalvideostreamerror) |


<span id="ByteRTCVideoDelegate-rtcengine-onremotevideostatechanged-withvideostate-withvideostatereason"></span>
### rtcEngine:onRemoteVideoStateChanged:withVideoState:withVideoStateReason:
```objectivec

- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onRemoteVideoStateChanged:(ByteRTCRemoteStreamKey*_Nonnull)streamKey withVideoState:(ByteRTCRemoteVideoState)state withVideoStateReason:(ByteRTCRemoteVideoStateChangeReason)reason;
```
远端视频流的状态发生改变时，房间内订阅此流的用户会收到该事件。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象 |
| streamKey | **ByteRTCRemoteStreamKey*** | 远端视频流信息，房间、用户 ID、流属性等，参看 [ByteRTCRemoteStreamKey](iOS-keytype.md#bytertcremotestreamkey) |
| state | **ByteRTCRemoteVideoState** | 远端视频流的当前状态，参看 [ByteRTCRemoteVideoState](iOS-keytype.md#bytertcremotevideostate) |
| reason | **ByteRTCRemoteVideoStateChangeReason** | 远端视频流状态改变的原因，参看 [ByteRTCRemoteVideoStateChangeReason](iOS-keytype.md#bytertcremotevideostatechangereason) |


<span id="ByteRTCVideoDelegate-rtcengine-onloginresult-errorcode-elapsed"></span>
### rtcEngine:onLoginResult:errorCode:elapsed:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onLoginResult:(NSString * _Nonnull)uid errorCode:(ByteRTCLoginErrorCode)errorCode elapsed:(NSInteger)elapsed;
```
登录结果回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象 |
| uid | **NSString*** | 登录用户 ID |
| errorCode | **ByteRTCLoginErrorCode** | 登录结果  <br/>详见 [ByteRTCLoginErrorCode](iOS-errorcode.md#bytertcloginerrorcode)。 |
| elapsed | **NSInteger** | 从调用 [login:uid:](iOS-api.md#ByteRTCVideo-login-uid) 接口开始到返回结果所用时长。  <br/>单位为 ms。 |


**注意**
调用 [login:uid:](iOS-api.md#ByteRTCVideo-login-uid) 后，会收到此回调。

<span id="ByteRTCVideoDelegate-rtcengineonlogout"></span>
### rtcEngineOnLogout:
```objectivec

- (void)rtcEngineOnLogout:(ByteRTCVideo * _Nonnull)engine;
```
登出结果回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象 |


**注意**
调用 [logout](iOS-api.md#ByteRTCVideo-logout) 后，会收到此回调。

<span id="ByteRTCVideoDelegate-rtcengine-onserverparamssetresult"></span>
### rtcEngine:onServerParamsSetResult:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onServerParamsSetResult:(NSInteger)errorCode;
```
设置应用服务器参数的返回结果

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象 |
| errorCode | **NSInteger** | 设置结果  <br/>• 返回 200，设置成功  <br/>• 返回其他，设置失败，详见 [ByteRTCUserMessageSendResult](iOS-keytype.md#bytertcusermessagesendresult) |


**注意**
调用 [setServerParams:url:](iOS-api.md#ByteRTCVideo-setserverparams-url) 后，会收到此回调。

<span id="ByteRTCVideoDelegate-rtcengine-ongetpeeronlinestatus-status"></span>
### rtcEngine:onGetPeerOnlineStatus:status:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onGetPeerOnlineStatus:(NSString * _Nonnull)peerUserId status:(ByteRTCUserOnlineStatus)status;
```
查询对端或本端用户登录状态的返回结果

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象 |
| peerUserId | **NSString*** | 需要查询的用户 ID |
| status | **ByteRTCUserOnlineStatus** | 查询的用户登录状态  <br/>详见 [ByteRTCUserOnlineStatus](iOS-keytype.md#bytertcuseronlinestatus). |


**注意**
必须先调用 [getPeerOnlineStatus:](iOS-api.md#ByteRTCVideo-getpeeronlinestatus)，才能收到此回调。

<span id="ByteRTCVideoDelegate-rtcengine-onusermessagereceivedoutsideroom-message"></span>
### rtcEngine:onUserMessageReceivedOutsideRoom:message:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onUserMessageReceivedOutsideRoom:(NSString * _Nonnull)uid message:(NSString * _Nonnull)message;
```
收到房间外用户调用 [sendUserMessageOutsideRoom:message:config:](iOS-api.md#ByteRTCVideo-sendusermessageoutsideroom-message-config) 发来的文本消息时，会收到此回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象 |
| uid | **NSString*** | 消息发送者 ID |
| message | **NSString*** | 收到的文本消息内容 |


<span id="ByteRTCVideoDelegate-rtcengine-onuserbinarymessagereceivedoutsideroom-message"></span>
### rtcEngine:onUserBinaryMessageReceivedOutsideRoom:message:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onUserBinaryMessageReceivedOutsideRoom:(NSString * _Nonnull)uid message:(NSData * _Nonnull)message;
```
收到房间外用户调用 [sendUserBinaryMessageOutsideRoom:message:config:](iOS-api.md#ByteRTCVideo-senduserbinarymessageoutsideroom-message-config) 发来的二进制消息时，会收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象 |
| uid | **NSString*** | 消息发送者 ID |
| message | **NSData*** | 收到的二进制消息内容 |


<span id="ByteRTCVideoDelegate-rtcengine-onusermessagesendresultoutsideroom-error"></span>
### rtcEngine:onUserMessageSendResultOutsideRoom:error:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onUserMessageSendResultOutsideRoom:(int64_t)msgid error:(ByteRTCUserMessageSendResult)error;
```
给房间外指定的用户发送消息的回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象 |
| msgid | **int64_t** | 本条消息的 ID  <br/>所有的 P2P 和 P2Server 消息共用一个 ID 序列。 |
| error | **ByteRTCUserMessageSendResult** | 消息发送结果  <br/>详见 [ByteRTCUserMessageSendResult](iOS-keytype.md#bytertcusermessagesendresult)。 |


**注意**
当调用 [sendUserMessageOutsideRoom:message:config:](iOS-api.md#ByteRTCVideo-sendusermessageoutsideroom-message-config) 或 [sendUserBinaryMessageOutsideRoom:message:config:](iOS-api.md#ByteRTCVideo-senduserbinarymessageoutsideroom-message-config) 发送消息后，会收到此回调。

<span id="ByteRTCVideoDelegate-rtcengine-onservermessagesendresult-error-message"></span>
### rtcEngine:onServerMessageSendResult:error:message:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onServerMessageSendResult:(int64_t)msgid error:(ByteRTCUserMessageSendResult)error message:(NSData * _Nonnull)message;
```
给应用服务器发送消息的回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象。 |
| msgid | **int64_t** | 本条消息的 ID。<br/>所有的 P2P 和 P2Server 消息共用一个 ID 序列。 |
| error | **ByteRTCUserMessageSendResult** | 消息发送结果。详见 [ByteRTCUserMessageSendResult](iOS-keytype.md#bytertcusermessagesendresult)。 |
| message | **NSData*** | 应用服务器收到 HTTP 请求后，在 ACK 中返回的信息。消息不超过 64 KB。 |


**注意**
本回调为异步回调。当调用 [sendServerMessage:](iOS-api.md#ByteRTCVideo-sendservermessage) 或 [sendServerBinaryMessage:](iOS-api.md#ByteRTCVideo-sendserverbinarymessage) 接口发送消息后，会收到此回调。

<span id="ByteRTCVideoDelegate-rtcengine-onnetworkdetectionresult-quality-rtt-lostrate-bitrate-jitter"></span>
### rtcEngine:onNetworkDetectionResult:quality:rtt:lostRate:bitrate:jitter:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onNetworkDetectionResult:(ByteRTCNetworkDetectionLinkType)type quality:(ByteRTCNetworkQuality)quality rtt:(int)rtt lostRate:(double)lost_rate bitrate:(int)bitrate jitter:(int)jitter;
```
通话前网络探测结果。  <br>
成功调用 [startNetworkDetection:uplinkBandwidth:downlink:downlinkBandwidth:](iOS-api.md#ByteRTCVideo-startnetworkdetection-uplinkbandwidth-downlink-downlinkbandwidth) 接口开始探测后，会在 3s 内首次收到该回调，之后每 2s 收到一次该回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象 |
| type | **ByteRTCNetworkDetectionLinkType** | 探测网络类型为上行/下行 |
| quality | **ByteRTCNetworkQuality** | 探测网络的质量，参看 [ByteRTCNetworkQuality](iOS-keytype.md#bytertcnetworkquality)。 |
| rtt | **int** | 探测网络的 RTT，单位：ms |
| lost_rate | **double** | 探测网络的丢包率 |
| bitrate | **int** | 探测网络的带宽，单位：kbps |
| jitter | **int** | 探测网络的抖动,单位：ms |


<span id="ByteRTCVideoDelegate-rtcengine-onnetworkdetectionstopped"></span>
### rtcEngine:onNetworkDetectionStopped:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onNetworkDetectionStopped:(ByteRTCNetworkDetectionStopReason)err_code;
```
通话前网络探测结束  <br>
以下情况将停止探测并收到本一次本回调：<br>
1. 当调用 [stopNetworkDetection](iOS-api.md#ByteRTCVideo-stopnetworkdetection) 接口停止探测后，会收到一次该回调；
2. 当收到远端/本端音频首帧后，停止探测；
3. 当探测超过3分钟后，停止探测；
4. 当探测链路断开一定时间之后，停止探测。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象 |
| err_code | **ByteRTCNetworkDetectionStopReason** | 停止探测的原因类型,参考 [ByteRTCNetworkDetectionStopReason](iOS-keytype.md#bytertcnetworkdetectionstopreason) |


<span id="ByteRTCVideoDelegate-rtcengine-onaudiomixingstatechanged-state-error"></span>
### rtcEngine:onAudioMixingStateChanged:state:error:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onAudioMixingStateChanged:(NSInteger)mixId state:(ByteRTCAudioMixingState)state error:(ByteRTCAudioMixingError)error;
```
音频混音文件播放状态改变时回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | 当前 RTC SDK 对象 |
| mixId | **NSInteger** | 混音 ID  <br/>使用 [ByteRTCAudioMixingManager](iOS-api.md#bytertcaudiomixingmanager) 相关接口时传入的唯一 ID。 |
| state | **ByteRTCAudioMixingState** | 混音状态  <br/>其混音状态可参考：[ByteRTCAudioMixingState](iOS-keytype.md#bytertcaudiomixingstate)。 |
| error | **ByteRTCAudioMixingError** | 错误码  <br/>详见 [ByteRTCAudioMixingError](iOS-keytype.md#bytertcaudiomixingerror)。 |


**注意**
此回调会被触发的时机汇总如下：  

+ 当调用 [startAudioMixing:filePath:config:](iOS-api.md#ByteRTCAudioMixingManager-startaudiomixing-filepath-config) 方法成功后，会触发 state 值为 ByteRTCAudioMixingStatePlaying 回调；否则触发 state 值为 ByteRTCAudioMixingStateFailed 的回调。  
+ 当使用相同的 ID 重复调用 [startAudioMixing:filePath:config:](iOS-api.md#ByteRTCAudioMixingManager-startaudiomixing-filepath-config) 后，后一次会覆盖前一次，且本回调会以 ByteRTCAudioMixingStateStopped 通知前一次混音已停止。  
+ 当调用 [pauseAudioMixing:](iOS-api.md#ByteRTCAudioMixingManager-pauseaudiomixing) 方法暂停播放成功后，会触发 state 值为 ByteRTCAudioMixingStatePaused 回调；否则触发 state 值为 ByteRTCAudioMixingStateFailed 的回调。  
+ 当调用 [resumeAudioMixing:](iOS-api.md#ByteRTCAudioMixingManager-resumeaudiomixing) 方法恢复播放成功后，会触发 state 值为 ByteRTCAudioMixingStatePlaying 回调；否则触发 state 值为 ByteRTCAudioMixingStateFailed 的回调。  
+ 当调用 [stopAudioMixing:](iOS-api.md#ByteRTCAudioMixingManager-stopaudiomixing) 方法停止播放成功后，会触发 state 值为 ByteRTCAudioMixingStateStopped 回调；否则触发 state 值为 ByteRTCAudioMixingStateFailed 的回调。  
+ 播放结束会触发 state 值为 ByteRTCAudioMixingStateFinished 回调。


<span id="ByteRTCVideoDelegate-rtcengine-onaudiomixingplayingprogress-progress"></span>
### rtcEngine:onAudioMixingPlayingProgress:progress:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onAudioMixingPlayingProgress:(NSInteger)mixId progress:(int64_t) progress;
```
混音音频文件播放进度回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | 当前 RTC SDK 对象 |
| mixId | **NSInteger** | 混音 ID |
| progress | **int64_t** | 当前混音音频文件播放进度，单位毫秒 |


**注意**
调用 [setAudioMixingProgressInterval:interval:](iOS-api.md#ByteRTCAudioMixingManager-setaudiomixingprogressinterval-interval) 将时间间隔设为大于 0 的值后，或调用 [startAudioMixing:filePath:config:](iOS-api.md#ByteRTCAudioMixingManager-startaudiomixing-filepath-config) 将 [ByteRTCAudioMixingConfig](iOS-keytype.md#bytertcaudiomixingconfig) 中的时间间隔设为大于 0 的值后，SDK 会按照设置的时间间隔回调该事件。 

<span id="ByteRTCVideoDelegate-rtcengine-onperformancealarmswithmode-roomid-reason-sourcewanteddata"></span>
### rtcEngine:onPerformanceAlarmsWithMode:roomId:reason:sourceWantedData:
```objectivec

- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onPerformanceAlarmsWithMode:(ByteRTCPerformanceAlarmMode)mode roomId:(NSString *_Nonnull)roomId reason:(ByteRTCPerformanceAlarmReason)reason sourceWantedData:(ByteRTCSourceWantedData *_Nonnull)data;
```
本地未开启发布性能回退，检测到设备性能不足时，收到此回调。  <br>
本地开启发布性能回退，因设备性能/网络原因，造成发布性能回退/恢复时，收到此回调。  <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mode | **ByteRTCPerformanceAlarmMode** | 指示本地是否开启发布回退功能。参看 [ByteRTCPerformanceAlarmMode](iOS-keytype.md#bytertcperformancealarmmode)  <br/>• 当发布端未开启发布性能回退时，mode 值为 ByteRTCPerformanceAlarmModeNormal。  <br/>• 当发布端开启发布性能回退时，mode 值为 ByteRTCPerformanceAlarmModeSimulcast。 |
| roomId | **NSString*** | • 未开启发布性能回退时，roomId 为空  <br/>• 开启发布性能回退时，roomId 是告警影响的房间 ID。 |
| reason | **ByteRTCPerformanceAlarmReason** | 告警原因，参看 [ByteRTCPerformanceAlarmReason](iOS-keytype.md#bytertcperformancealarmreason) |
| data | **ByteRTCSourceWantedData*** | 性能回退相关数据，详见 [ByteRTCSourceWantedData](iOS-keytype.md#bytertcsourcewanteddata)。 |


<span id="ByteRTCVideoDelegate-rtcengine-onsimulcastsubscribefallback"></span>
### rtcEngine:OnSimulcastSubscribeFallback:
```objectivec

- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine OnSimulcastSubscribeFallback:(ByteRTCRemoteStreamSwitchEvent *_Nonnull)event;
```
音视频流因网络环境变化等原因发生回退，或从回退中恢复时，触发该回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | 当前 ByteRTCVideo 实例 |
| event | **ByteRTCRemoteStreamSwitchEvent*** | 流切换信息。详见 [ByteRTCRemoteStreamSwitchEvent](iOS-keytype.md#bytertcremotestreamswitchevent)。 |


<span id="ByteRTCVideoDelegate-rtcengine-onhttpproxystate"></span>
### rtcEngine:onHttpProxyState:
```objectivec

- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onHttpProxyState:(NSInteger)state;
```
HTTP 代理连接状态改变时，收到该回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象 |
| state | **NSInteger** | 当前 HTTP 代理连接状态 |


<span id="ByteRTCVideoDelegate-rtcengine-onhttpsproxystate"></span>
### rtcEngine:onHttpsProxyState:
```objectivec

- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onHttpsProxyState:(NSInteger)state;
```
HTTPS 代理连接状态改变时，收到该回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象 |
| state | **NSInteger** | 当前 HTTPS 代理连接状态 |


<span id="ByteRTCVideoDelegate-rtcengine-onsocks5proxystate-cmd-proxy_address-local_address-remote_address"></span>
### rtcEngine:onSocks5ProxyState:cmd:proxy_address:local_address:remote_address:
```objectivec

- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onSocks5ProxyState:(NSInteger)state cmd:(NSString *_Nonnull)cmd proxy_address:(NSString *_Nonnull)proxy_address local_address:(NSString *_Nonnull)local_address remote_address:(NSString *_Nonnull)remote_address;
```
SOCKS5 代理状态改变时，收到该回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象 |
| state | **NSInteger** | SOCKS5 代理连接状态 |
| cmd | **NSString*** | 代理连接的每一步操作命令 |
| proxy_address | **NSString*** | 代理地址信息 |
| local_address | **NSString*** | 当前连接使用的本地地址 |
| remote_address | **NSString*** | 远端的连接地址 |


<span id="ByteRTCVideoDelegate-rtcengine-onrecordingstateupdate-state-error_code-recording_info"></span>
### rtcEngine:onRecordingStateUpdate:state:error_code:recording_info:
```objectivec

- (void)rtcEngine:(ByteRTCVideo* _Nonnull)engine onRecordingStateUpdate:(ByteRTCStreamIndex)type state:(ByteRTCRecordingState)state error_code:(ByteRTCRecordingErrorCode)error_code recording_info:(ByteRTCRecordingInfo* _Nonnull)recording_info;
```
获取本地录制状态回调。  <br>
该回调由 [startFileRecording:withRecordingConfig:type:](iOS-api.md#ByteRTCVideo-startfilerecording-withrecordingconfig-type) 或 [stopFileRecording:](iOS-api.md#ByteRTCVideo-stopfilerecording) 触发。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象 |
| type | **ByteRTCStreamIndex** | 录制流的流属性，参看 [ByteRTCStreamIndex](iOS-keytype.md#bytertcstreamindex) |
| state | **ByteRTCRecordingState** | 录制状态，参看 [ByteRTCRecordingState](iOS-keytype.md#bytertcrecordingstate) |
| error_code | **ByteRTCRecordingErrorCode** | 录制错误码，参看 [ByteRTCRecordingErrorCode](iOS-keytype.md#bytertcrecordingerrorcode) |
| recording_info | **ByteRTCRecordingInfo*** | 录制文件的详细信息，参看 [ByteRTCRecordingInfo](iOS-keytype.md#bytertcrecordinginfo) |


<span id="ByteRTCVideoDelegate-rtcengine-onrecordingprogressupdate-process-recording_info"></span>
### rtcEngine:onRecordingProgressUpdate:process:recording_info:
```objectivec

- (void)rtcEngine:(ByteRTCVideo* _Nonnull)engine onRecordingProgressUpdate:(ByteRTCStreamIndex)type process:(ByteRTCRecordingProgress* _Nonnull)process recording_info:(ByteRTCRecordingInfo* _Nonnull)recording_info;
```
本地录制进度回调。  <br>
该回调由 [startFileRecording:withRecordingConfig:type:](iOS-api.md#ByteRTCVideo-startfilerecording-withrecordingconfig-type) 触发，录制状态正常时，系统每秒钟都会通过该回调提示录制进度。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象 |
| type | **ByteRTCStreamIndex** | 录制流的流属性，参看 [ByteRTCStreamIndex](iOS-keytype.md#bytertcstreamindex) |
| process | **ByteRTCRecordingProgress*** | 录制进度，参看 [ByteRTCRecordingProgress](iOS-keytype.md#bytertcrecordingprogress) |
| recording_info | **ByteRTCRecordingInfo*** | 录制文件的详细信息，参看 [ByteRTCRecordingInfo](iOS-keytype.md#bytertcrecordinginfo) |


<span id="ByteRTCVideoDelegate-rtcengine-onpushpublicstreamresult-publicstreamid-errorcode"></span>
### rtcEngine:onPushPublicStreamResult:publicStreamId:errorCode:
```objectivec

- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onPushPublicStreamResult:(NSString *_Nonnull)roomId publicStreamId:(NSString *_Nonnull)streamId errorCode:(ByteRTCTranscodingError)errorCode;
```
公共流发布结果回调。<br>
调用 [startPushPublicStream:withLayout:](iOS-api.md#ByteRTCVideo-startpushpublicstream-withlayout) <br>
接口或直接在服务端启动推公共流功能后，你会通过此回调收到启动结果和推流过程中的错误。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | engine 实例 |
| roomId | **NSString*** | 发布公共流的房间 ID |
| streamId | **NSString*** | 公共流ID。 |
| errorCode | **ByteRTCTranscodingError** | 公共流发布结果状态码。  <br/>`200`: 发布成功<br/>`1191`: 推流参数存在异常 <br/>`1192`: 当前状态异常，通常为无法发起任务<br/>`1193`: 服务端错误，不可恢复<br/>`1195`: 服务端调用发布接口返回失败<br/>`1196`: 超时无响应。推流请求发送后 10s 没有收到服务端的结果回调。客户端将每隔 10s 重试，3 次重试失败后停止。 |


<span id="ByteRTCVideoDelegate-rtcengine-onplaypublicstreamresult-errorcode"></span>
### rtcEngine:onPlayPublicStreamResult:errorCode:
```objectivec

- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onPlayPublicStreamResult:(NSString *_Nonnull)publicStreamId errorCode:(ByteRTCTranscodingError)errorCode;
```
订阅公共流的结果回调  <br>
调用 [startPlayPublicStream:](iOS-api.md#ByteRTCVideo-startplaypublicstream) 接口拉公共流后，你会通过此回调收到启动结果和拉流过程中的错误。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | engine 实例 |
| publicStreamId | **NSString*** | 公共流ID。 |
| errorCode | **ByteRTCTranscodingError** | 公共流订阅结果状态码。 <br/>`200`: 成功 |


<span id="ByteRTCVideoDelegate-rtcengine-onpublicstreamseimessagereceived-andmessage"></span>
### rtcEngine:onPublicStreamSEIMessageReceived:andMessage:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onPublicStreamSEIMessageReceived:(NSString* _Nonnull)publicStreamId andMessage:(NSData* _Nonnull)message;
```
回调公共流中包含的 SEI 信息<br>
通过 [startPlayPublicStream:](iOS-api.md#ByteRTCVideo-startplaypublicstream) 开始播放公共流后，可以通过本回调获取公共流中包含的 SEI 信息。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 实例。 |
| publicStreamId | **NSString*** | 公共流ID |
| message | **NSData*** | 收到的 SEI 消息内容 |


**注意**
当公共流中的多路视频流均包含有 SEI 信息时：SEI 不互相冲突时，将通过多次回调分别发送；
SEI 在同一帧有冲突时，则只有一条流中的 SEI 信息被透传并融合到公共流中。


<span id="ByteRTCVideoDelegate-rtcengine-onfirstpublicstreamvideoframedecoded-withframeinfo"></span>
### rtcEngine:onFirstPublicStreamVideoFrameDecoded:withFrameInfo:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onFirstPublicStreamVideoFrameDecoded:(NSString * _Nonnull)publicStreamId withFrameInfo:(ByteRTCVideoFrameInfo * _Nonnull)frameInfo;
```
公共流的首帧视频解码成功<br>
关于订阅公共流，详见 [startPlayPublicStream:](iOS-api.md#ByteRTCVideo-startplaypublicstream)。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象 |
| publicStreamId | **NSString*** | 公共流 ID |
| frameInfo | **ByteRTCVideoFrameInfo*** | 视频帧信息，参看 [ByteRTCVideoFrameInfo](iOS-keytype.md#bytertcvideoframeinfo) |


<span id="ByteRTCVideoDelegate-rtcengine-onfirstpublicstreamaudioframe"></span>
### rtcEngine:onFirstPublicStreamAudioFrame:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onFirstPublicStreamAudioFrame:(NSString * _Nonnull)publicStreamId;
```
公共流的音频首帧解码成功<br>
关于订阅公共流，详见 [startPlayPublicStream:](iOS-api.md#ByteRTCVideo-startplaypublicstream)。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象 |
| publicStreamId | **NSString*** | 公共流 ID |


<span id="ByteRTCVideoDelegate-rtcengine-oncloudproxyconnected"></span>
### rtcEngine:onCloudProxyConnected:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onCloudProxyConnected:(NSInteger)interval;
```
调用 [startCloudProxy:](iOS-api.md#ByteRTCVideo-startcloudproxy) 开启云代理，SDK 首次成功连接云代理服务器时，回调此事件。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| interval | **NSInteger** | 从开启云代理到连接成功经过的时间，单位为 ms |


<span id="ByteRTCVideoDelegate-rtcengine-onechotestresult"></span>
### rtcEngine:onEchoTestResult:
```objectivec

- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onEchoTestResult:(ByteRTCEchoTestResult)result;
```
关于音视频回路测试结果的回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| result | **ByteRTCEchoTestResult** | 测试结果，参看 [ByteRTCEchoTestResult](iOS-keytype.md#bytertcechotestresult)。 |


**注意**
该回调触发的时机包括： + 检测过程中采集设备发生错误时；  

+ 检测成功后；  
+ 非设备原因导致检测过程中未接收到音/视频回放，停止检测后。


# ByteRTCAudioFrameObserver
```objectivec
@protocol ByteRTCAudioFrameObserver <NSObject>
```

音频数据回调观察者


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **void** | [onRecordAudioFrame:](#ByteRTCAudioFrameObserver-onrecordaudioframe) |
| **void** | [onPlaybackAudioFrame:](#ByteRTCAudioFrameObserver-onplaybackaudioframe) |
| **void** | [onRemoteUserAudioFrame:audioFrame:](#ByteRTCAudioFrameObserver-onremoteuseraudioframe-audioframe) |
| **void** | [onMixedAudioFrame:](#ByteRTCAudioFrameObserver-onmixedaudioframe) |


## 函数说明
<span id="ByteRTCAudioFrameObserver-onrecordaudioframe"></span>
### onRecordAudioFrame:
```objectivec

- (void)onRecordAudioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;
```
返回麦克风录制的音频数据

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioFrame | **ByteRTCAudioFrame*** | 音频数据, 详见： [ByteRTCAudioFrame](iOS-keytype.md#bytertcaudioframe) |


<span id="ByteRTCAudioFrameObserver-onplaybackaudioframe"></span>
### onPlaybackAudioFrame:
```objectivec

- (void)onPlaybackAudioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;
```
返回订阅的所有远端用户混音后的音频数据

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioFrame | **ByteRTCAudioFrame*** | 音频数据, 详见： [ByteRTCAudioFrame](iOS-keytype.md#bytertcaudioframe) |


<span id="ByteRTCAudioFrameObserver-onremoteuseraudioframe-audioframe"></span>
### onRemoteUserAudioFrame:audioFrame:
```objectivec

- (void)onRemoteUserAudioFrame:(ByteRTCRemoteStreamKey * _Nonnull)streamKey audioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;
```
返回远端单个用户的音频数据

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamKey | **ByteRTCRemoteStreamKey*** | 远端流信息，参看 [ByteRTCRemoteStreamKey](iOS-keytype.md#bytertcremotestreamkey)。 |
| audioFrame | **ByteRTCAudioFrame*** | 音频数据，参看 [ByteRTCAudioFrame](iOS-keytype.md#bytertcaudioframe)。 |


**注意**
此回调在播放线程调用。不要在此回调中做任何耗时的事情，否则可能会影响整个音频播放链路。

<span id="ByteRTCAudioFrameObserver-onmixedaudioframe"></span>
### onMixedAudioFrame:
```objectivec

- (void)onMixedAudioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;
```
返回本地麦克风录制和订阅的所有远端用户混音后的音频数据

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioFrame | **ByteRTCAudioFrame*** | 音频数据, 详见： [ByteRTCAudioFrame](iOS-keytype.md#bytertcaudioframe) |


# ByteRTCAudioFrameProcessor
```objectivec
@protocol ByteRTCAudioFrameProcessor <NSObject>
```

自定义音频处理器。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **int** | [onProcessRecordAudioFrame:](#ByteRTCAudioFrameProcessor-onprocessrecordaudioframe) |
| **int** | [onProcessPlayBackAudioFrame:](#ByteRTCAudioFrameProcessor-onprocessplaybackaudioframe) |
| **int** | [onProcessRemoteUserAudioFrame:audioFrame:](#ByteRTCAudioFrameProcessor-onprocessremoteuseraudioframe-audioframe) |
| **int** | [onProcessEarMonitorAudioFrame:](#ByteRTCAudioFrameProcessor-onprocessearmonitoraudioframe) |
| **int** | [onProcessScreenAudioFrame:](#ByteRTCAudioFrameProcessor-onprocessscreenaudioframe) |


## 函数说明
<span id="ByteRTCAudioFrameProcessor-onprocessrecordaudioframe"></span>
### onProcessRecordAudioFrame:
```objectivec

- (int)onProcessRecordAudioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;
```
回调本地采集的音频帧地址，供自定义音频处理。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioFrame | **ByteRTCAudioFrame*** | 音频帧地址，参看 [ByteRTCAudioFrame](iOS-keytype.md#bytertcaudioframe)。 |


**注意**

+ 完成自定义音频处理后，SDK 会对处理后的音频帧进行编码，并传输到远端。
+ 调用 `enableAudioProcessor`，并在参数中选择本地采集的音频时，收到此回调。


<span id="ByteRTCAudioFrameProcessor-onprocessplaybackaudioframe"></span>
### onProcessPlayBackAudioFrame:
```objectivec

- (int)onProcessPlayBackAudioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;
```
回调远端音频混音的音频帧地址，供自定义音频处理。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioFrame | **ByteRTCAudioFrame*** | 音频帧地址，参看 [ByteRTCAudioFrame](iOS-keytype.md#bytertcaudioframe)。 |


**注意**
调用 `enableAudioProcessor`,并在参数中选择远端音频流的的混音音频时，收到此回调。

<span id="ByteRTCAudioFrameProcessor-onprocessremoteuseraudioframe-audioframe"></span>
### onProcessRemoteUserAudioFrame:audioFrame:
```objectivec

- (int)onProcessRemoteUserAudioFrame:(ByteRTCRemoteStreamKey * _Nonnull)stream_info audioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;
```
回调单个远端用户的音频帧地址，供自定义音频处理。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stream_info | **ByteRTCRemoteStreamKey*** | 音频流信息，参看 [ByteRTCRemoteStreamKey](iOS-keytype.md#bytertcremotestreamkey)。 |
| audioFrame | **ByteRTCAudioFrame*** | 音频帧地址，参看 [ByteRTCAudioFrame](iOS-keytype.md#bytertcaudioframe)。 |


**注意**
调用 `enableAudioProcessor`,并在参数中选择各个远端音频流时，收到此回调。

<span id="ByteRTCAudioFrameProcessor-onprocessearmonitoraudioframe"></span>
### onProcessEarMonitorAudioFrame:
```objectivec

- (int)onProcessEarMonitorAudioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;
```
软件耳返音频数据的回调。你可根据此回调自定义处理音频。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioFrame | **ByteRTCAudioFrame*** | 音频帧地址，参看 [ByteRTCAudioFrame](iOS-keytype.md#bytertcaudioframe)。 |


**注意**

+ 此数据处理只影响耳返音频数据。
+ 调用 [enableAudioProcessor:audioFormat:](iOS-api.md#ByteRTCVideo-enableaudioprocessor-audioformat) 把返回给音频处理器的音频类型设置为耳返音频后，你将收到此回调。


<span id="ByteRTCAudioFrameProcessor-onprocessscreenaudioframe"></span>
### onProcessScreenAudioFrame:
```objectivec

- (int)onProcessScreenAudioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;
```
回调屏幕共享的音频帧地址，供自定义音频处理。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioFrame | **ByteRTCAudioFrame*** | 音频帧地址，参看 [ByteRTCAudioFrame](iOS-keytype.md#bytertcaudioframe)。 |


**注意**
调用 `enableAudioProcessor:`，把返回给音频处理器的音频类型设置为屏幕共享音频后，你将收到此回调。

# ByteRTCEncryptHandler
```objectivec
@protocol ByteRTCEncryptHandler <NSObject>
```

自定义加密接口


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **NSData*** | [ByteRTCEncryptRawData:](#ByteRTCEncryptHandler-bytertcencryptrawdata) |
| **NSData*** | [ByteRTCDecryptRawData:](#ByteRTCEncryptHandler-bytertcdecryptrawdata) |


## 函数说明
<span id="ByteRTCEncryptHandler-bytertcencryptrawdata"></span>
### ByteRTCEncryptRawData:
```objectivec

- (NSData * _Nonnull) ByteRTCEncryptRawData:(NSData * _Nonnull)rawData;
```
自定义加密。  <br>
使用设定的自定义加密方式，对编码后传输前的音视频帧数据进行加密。暂不支持对原始音视频帧进行加密。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rawData | **NSData*** | 原始音视频帧数据 |

**返回值**
加密后的数据  

+ 非空，表示加密后的数据  
+ 为空，表示数据被丢弃


**注意**

+ 使用此接口进行自定义加密前，你必须先设置自定义加密方式，参看 `setCustomizeEncryptHandler:`。
+ 使用 [ByteRTCDecryptRawData:](#ByteRTCEncryptHandler-bytertcdecryptrawdata) 对已加密的音视频帧数据进行解密。
+ 返回的数据大小应控制在原始数据的 90% ~ 120% 范围以内，不然将被丢弃。


<span id="ByteRTCEncryptHandler-bytertcdecryptrawdata"></span>
### ByteRTCDecryptRawData:
```objectivec

- (NSData * _Nonnull) ByteRTCDecryptRawData:(NSData * _Nonnull)rawData;
```
自定义解密。  <br>
对自定义加密后的音视频帧数据进行解密。关于自定义加密，参看 [ByteRTCEncryptRawData:](#ByteRTCEncryptHandler-bytertcencryptrawdata)。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rawData | **NSData*** | 收到的已加密的音视频帧数据 |

**返回值**
解密后的数据  

+ 非空，表示解密后的数据  
+ 为空，表示丢弃该帧


**注意**

+ 使用此接口进行解密前，你必须先设定解密方式，参看 `setCustomizeEncryptHandler:`。
+ 返回的数据大小应控制在原始数据的 90% ~ 120% 范围以内，不然将被丢弃。


# ByteRTCKTVManagerDelegate
```objectivec
@protocol ByteRTCKTVManagerDelegate <NSObject>
```

KTV 事件回调接口。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **void** | [ktvManager:onMusicListResult:totalSize:musics:](#ByteRTCKTVManagerDelegate-ktvmanager-onmusiclistresult-totalsize-musics) |
| **void** | [ktvManager:onSearchMusicResult:totalSize:musics:](#ByteRTCKTVManagerDelegate-ktvmanager-onsearchmusicresult-totalsize-musics) |
| **void** | [ktvManager:onHotMusicResult:hotMusicInfos:](#ByteRTCKTVManagerDelegate-ktvmanager-onhotmusicresult-hotmusicinfos) |
| **void** | [ktvManager:onMusicDetailResult:music:](#ByteRTCKTVManagerDelegate-ktvmanager-onmusicdetailresult-music) |
| **void** | [ktvManager:onDownloadSuccess:downloadResult:](#ByteRTCKTVManagerDelegate-ktvmanager-ondownloadsuccess-downloadresult) |
| **void** | [ktvManager:onDownloadFail:errorCode:](#ByteRTCKTVManagerDelegate-ktvmanager-ondownloadfail-errorcode) |
| **void** | [ktvManager:onDownloadMusicProgress:progress:](#ByteRTCKTVManagerDelegate-ktvmanager-ondownloadmusicprogress-progress) |


## 函数说明
<span id="ByteRTCKTVManagerDelegate-ktvmanager-onmusiclistresult-totalsize-musics"></span>
### ktvManager:onMusicListResult:totalSize:musics:
```objectivec

- (void)ktvManager:(ByteRTCKTVManager *)ktvManager onMusicListResult:(ByteRTCKTVError)errorCode totalSize:(int)totalSize musics:(NSArray<ByteRTCKTVMusic *> * _Nullable)musics;
```
歌曲列表回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| errorCode | **ByteRTCKTVError** | 错误码，成功时返回 0，其余值参看 [ByteRTCKTVError](iOS-keytype.md#bytertcktverror)。 |
| totalSize | **int** | 数据条目总数。 |
| musics | **NSArray<ByteRTCKTVMusic*>*** | 歌曲数据数组，参看 [ByteRTCKTVMusic](iOS-keytype.md#bytertcktvmusic)。 |


<span id="ByteRTCKTVManagerDelegate-ktvmanager-onsearchmusicresult-totalsize-musics"></span>
### ktvManager:onSearchMusicResult:totalSize:musics:
```objectivec

- (void)ktvManager:(ByteRTCKTVManager *)ktvManager onSearchMusicResult:(ByteRTCKTVError)errorCode totalSize:(int)totalSize musics:(NSArray<ByteRTCKTVMusic *> * _Nullable)musics;
```
搜索歌曲结果回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| errorCode | **ByteRTCKTVError** | 错误码，成功时返回 0，其余值参看 [ByteRTCKTVError](iOS-keytype.md#bytertcktverror)。 |
| totalSize | **int** | 数据条目总数。 |
| musics | **NSArray<ByteRTCKTVMusic*>*** | 歌曲数据数组，参看 [ByteRTCKTVMusic](iOS-keytype.md#bytertcktvmusic)。 |


<span id="ByteRTCKTVManagerDelegate-ktvmanager-onhotmusicresult-hotmusicinfos"></span>
### ktvManager:onHotMusicResult:hotMusicInfos:
```objectivec

- (void)ktvManager:(ByteRTCKTVManager *)ktvManager onHotMusicResult:(ByteRTCKTVError)errorCode hotMusicInfos:(NSArray<ByteRTCKTVHotMusicInfo *> * _Nullable)hotMusicInfos;
```
热榜歌曲结果回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| errorCode | **ByteRTCKTVError** | 错误码，成功时返回 0，其余值参看 [ByteRTCKTVError](iOS-keytype.md#bytertcktverror)。 |
| hotMusicInfos | **NSArray<ByteRTCKTVHotMusicInfo*>*** | 热榜歌曲数据数组，参看 [ByteRTCKTVHotMusicInfo](iOS-keytype.md#bytertcktvhotmusicinfo)。 |


<span id="ByteRTCKTVManagerDelegate-ktvmanager-onmusicdetailresult-music"></span>
### ktvManager:onMusicDetailResult:music:
```objectivec

- (void)ktvManager:(ByteRTCKTVManager *)ktvManager onMusicDetailResult:(ByteRTCKTVError)errorCode music:(ByteRTCKTVMusic * _Nullable)music;
```
歌曲详细信息回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| errorCode | **ByteRTCKTVError** | 错误码，成功时返回 0，其余值参看 [ByteRTCKTVError](iOS-keytype.md#bytertcktverror)。 |
| music | **ByteRTCKTVMusic*** | 歌曲数据，参看 [ByteRTCKTVMusic](iOS-keytype.md#bytertcktvmusic)。 |


<span id="ByteRTCKTVManagerDelegate-ktvmanager-ondownloadsuccess-downloadresult"></span>
### ktvManager:onDownloadSuccess:downloadResult:
```objectivec

- (void)ktvManager:(ByteRTCKTVManager *)ktvManager onDownloadSuccess:(int)downloadId downloadResult:(ByteRTCKTVDownloadResult *)result;
```
下载成功回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| downloadId | **int** | 下载任务 ID。 |
| result | **ByteRTCKTVDownloadResult*** | 下载信息，参看 [ByteRTCKTVDownloadResult](iOS-keytype.md#bytertcktvdownloadresult)。 |


<span id="ByteRTCKTVManagerDelegate-ktvmanager-ondownloadfail-errorcode"></span>
### ktvManager:onDownloadFail:errorCode:
```objectivec

- (void)ktvManager:(ByteRTCKTVManager *)ktvManager onDownloadFail:(int)downloadId errorCode:(ByteRTCKTVError)errorCode;
```
下载失败回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| downloadId | **int** | 下载任务 ID。 |
| errorCode | **ByteRTCKTVError** | 错误码，参看 [ByteRTCKTVError](iOS-keytype.md#bytertcktverror)。 |


<span id="ByteRTCKTVManagerDelegate-ktvmanager-ondownloadmusicprogress-progress"></span>
### ktvManager:onDownloadMusicProgress:progress:
```objectivec

- (void)ktvManager:(ByteRTCKTVManager *)ktvManager onDownloadMusicProgress:(int)downloadId progress:(int)downloadPercentage;
```
歌曲文件下载进度回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| downloadId | **int** | 下载任务 ID。 |
| downloadPercentage | **int** | 下载进度百分比，取值范围 [0,100]。 |


# ByteRTCKTVPlayerDelegate
```objectivec
@protocol ByteRTCKTVPlayerDelegate <NSObject>
```

KTV 播放器回调接口。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **void** | [ktvPlayer:onPlayProgress:progress:](#ByteRTCKTVPlayerDelegate-ktvplayer-onplayprogress-progress) |
| **void** | [ktvPlayer:onPlayStateChange:state:error:](#ByteRTCKTVPlayerDelegate-ktvplayer-onplaystatechange-state-error) |


## 函数说明
<span id="ByteRTCKTVPlayerDelegate-ktvplayer-onplayprogress-progress"></span>
### ktvPlayer:onPlayProgress:progress:
```objectivec

- (void)ktvPlayer:(ByteRTCKTVPlayer *)ktvPlayer onPlayProgress:(NSString *)musicId progress:(int64_t)progress;
```
音乐播放进度回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| ktvPlayer | **ByteRTCKTVPlayer*** | 当前 ktvPlayer 对象，参看 [ByteRTCKTVPlayer](iOS-api.md#bytertcktvplayer)。 |
| musicId | **NSString*** | 音乐 ID。 |
| progress | **int64_t** | 音乐播放进度，单位为毫秒。 |


<span id="ByteRTCKTVPlayerDelegate-ktvplayer-onplaystatechange-state-error"></span>
### ktvPlayer:onPlayStateChange:state:error:
```objectivec

- (void)ktvPlayer:(ByteRTCKTVPlayer *)ktvPlayer onPlayStateChange:(NSString *)musicId state:(ByteRTCKTVPlayState)state error:(ByteRTCKTVPlayerError)error;
```
音乐播放状态改变回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| ktvPlayer | **ByteRTCKTVPlayer*** | 当前 ktvPlayer 对象，参看 [ByteRTCKTVPlayer](iOS-api.md#bytertcktvplayer)。 |
| musicId | **NSString*** | 音乐 ID。 |
| state | **ByteRTCKTVPlayState** | 音乐播放状态，参看 [ByteRTCKTVPlayState](iOS-keytype.md#bytertcktvplaystate)。 |
| error | **ByteRTCKTVPlayerError** | 错误码，参看 [ByteRTCKTVPlayerError](iOS-keytype.md#bytertcktvplayererror)。 |


**注意**
此回调被触发的时机汇总如下：

+ 调用 [playMusic:audioTrackType:audioPlayType:](iOS-api.md#ByteRTCKTVPlayer-playmusic-audiotracktype-audioplaytype) 成功后，会触发 playState 值为 ByteRTCKTVPlayStatePlaying 的回调；否则会触发 playState 值为 ByteRTCKTVPlayStateFailed 的回调。
+ 使用相同的音乐 ID 重复调用 [playMusic:audioTrackType:audioPlayType:](iOS-api.md#ByteRTCKTVPlayer-playmusic-audiotracktype-audioplaytype) 后，后一次播放会覆盖前一次，且会触发 playState 值为 ByteRTCKTVPlayStatePlaying 的回调，表示后一次音乐播放已开始。
+ 调用 [pauseMusic:](iOS-api.md#ByteRTCKTVPlayer-pausemusic) 方法暂停播放成功后，会触发 playState 值为 ByteRTCKTVPlayStatePaused 的回调；否则触发 playState 值为 ByteRTCKTVPlayStateFailed 的回调。
+ 调用 [resumeMusic:](iOS-api.md#ByteRTCKTVPlayer-resumemusic) 方法恢复播放成功后，会触发 playState 值为 ByteRTCKTVPlayStatePlaying 的回调；否则触发 playState 值为 ByteRTCKTVPlayStateFailed 的回调。
+ 调用 [stopMusic:](iOS-api.md#ByteRTCKTVPlayer-stopmusic) 方法停止播放成功后，会触发 playState 值为 ByteRTCKTVPlayStateStoped 的回调；否则触发 playState 值为 ByteRTCKTVPlayStateFailed 的回调。
+ 音乐播放结束会触发 playState 值为 ByteRTCKTVPlayStateFinished 的回调。


# ByteRTCRangeAudioObserver
```objectivec
@protocol ByteRTCRangeAudioObserver <NSObject>
```

范围语音衰减系数监测器


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **void** | [onRangeAudioInfo:](#ByteRTCRangeAudioObserver-onrangeaudioinfo) |


## 函数说明
<span id="ByteRTCRangeAudioObserver-onrangeaudioinfo"></span>
### onRangeAudioInfo:
```objectivec

- (void)onRangeAudioInfo:(NSArray<ByteRTCRangeAudioInfo *> * _Nonnull)rangeAudioInfo;
```
关于当前范围语音衰减系数的回调。  <br>
手动订阅的场景下，房间内任一用户调用 [updatePosition:](iOS-api.md#ByteRTCRangeAudio-updateposition) 更新自身位置或调用 [updateReceiveRange:](iOS-api.md#ByteRTCRangeAudio-updatereceiverange) 更新语音接收范围时，该用户与房间内其他用户的相对距离都会发生改变，据此计算的衰减系数也会发生改变，并通过该回调通知用户。 <br>
调用 [setAttenuationModel:coefficient:](iOS-api.md#ByteRTCRangeAudio-setattenuationmodel-coefficient) 更新音量衰减模式时，衰减系数将发生变化，通过该回调通知用户。<br>
你可以通过关注该回调中包含的远端用户的衰减系数决定是否订阅该远端用户的流。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rangeAudioInfo | **NSArray<ByteRTCRangeAudioInfo*>*** | 包含范围语音流信息的数组，参看 [ByteRTCRangeAudioInfo](iOS-keytype.md#bytertcrangeaudioinfo) |


**注意**
更新自身位置或语音接收范围后，并不会马上触发该回调。SDK 会每 500 ms 计算一次衰减系数，并且只在计算结果与上次不同，或结果相同但是距离上次计算已超过 3 秒的时候推送回调。

# ByteRTCSingScoringDelegate
```objectivec
@protocol ByteRTCSingScoringDelegate<NSObject>
```

K 歌评分事件回调类。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **void** | [onCurrentScoringInfo:](#ByteRTCSingScoringDelegate-oncurrentscoringinfo) |


## 函数说明
<span id="ByteRTCSingScoringDelegate-oncurrentscoringinfo"></span>
### onCurrentScoringInfo:
```objectivec

- (void)onCurrentScoringInfo:(ByteRTCSingScoringRealtimeInfo * _Nullable)info;
```
实时评分信息回调。调用 [startSingScoring:scoringInfoInterval:](iOS-api.md#ByteRTCSingScoringManager-startsingscoring-scoringinfointerval) 后，会收到该回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| Info | **ByteRTCSingScoringRealtime** | 实时评分信息。详见 [ByteRTCSingScoringRealtimeInfo](iOS-keytype.md#bytertcsingscoringrealtimeinfo)。 |


# ByteRTCVideoFrameObserver
```objectivec
@protocol ByteRTCVideoFrameObserver <NSObject>
```



## 成员函数

| 返回 | 名称 |
| --- | --- |
| **void** | [onLocalScreenFrame:](#ByteRTCVideoFrameObserver-onlocalscreenframe) |
| **void** | [onLocalVideoFrame:](#ByteRTCVideoFrameObserver-onlocalvideoframe) |
| **void** | [onRemoteScreenFrame:user:room:](#ByteRTCVideoFrameObserver-onremotescreenframe-user-room) |
| **void** | [onRemoteVideoFrame:user:room:](#ByteRTCVideoFrameObserver-onremotevideoframe-user-room) |


## 函数说明
<span id="ByteRTCVideoFrameObserver-onlocalscreenframe"></span>
### onLocalScreenFrame:
```objectivec

- (void)onLocalScreenFrame:(ByteRTCVideoFrame * _Nonnull)frame;
```
本地屏幕流的视频帧数据回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| frame | **ByteRTCVideoFrame*** | 本地屏幕视频帧数据，参考: [ByteRTCVideoFrame](iOS-keytype.md#bytertcvideoframe) |


<span id="ByteRTCVideoFrameObserver-onlocalvideoframe"></span>
### onLocalVideoFrame:
```objectivec

- (void)onLocalVideoFrame:(ByteRTCVideoFrame * _Nonnull)frame;
```
本地视频流的视频帧数据回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| frame | **ByteRTCVideoFrame*** | 本地视频流的视频帧数据，参考: [ByteRTCVideoFrame](iOS-keytype.md#bytertcvideoframe) |


<span id="ByteRTCVideoFrameObserver-onremotescreenframe-user-room"></span>
### onRemoteScreenFrame:user:room:
```objectivec

- (void)onRemoteScreenFrame:(ByteRTCVideoFrame * _Nonnull)frame user:(NSString * _Nullable)uid room:(NSString * _Nullable)room;
```
远端屏幕流的视频帧数据回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| frame | **ByteRTCVideoFrame*** | 远端屏幕的视频帧数据，参考: [ByteRTCVideoFrame](iOS-keytype.md#bytertcvideoframe) |
| uid | **NSString*** | 远端屏幕共享用户ID |
| room | **NSString*** | 对应流的房间 id |


<span id="ByteRTCVideoFrameObserver-onremotevideoframe-user-room"></span>
### onRemoteVideoFrame:user:room:
```objectivec

- (void)onRemoteVideoFrame:(ByteRTCVideoFrame * _Nonnull)frame user:(NSString * _Nullable)uid room:(NSString * _Nullable)room;
```
远端视频流的视频帧数据回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| frame | **ByteRTCVideoFrame*** | 远端视频流的视频帧数据，参考: [ByteRTCVideoFrame](iOS-keytype.md#bytertcvideoframe) |
| uid | **NSString*** | 远端屏幕共享用户ID |
| room | **NSString*** | 对应流的房间 id |


# ByteRTCVideoProcessorDelegate
```objectivec
@protocol ByteRTCVideoProcessorDelegate <NSObject>
```



## 成员函数

| 返回 | 名称 |
| --- | --- |
| **ByteRTCVideoFrame*** | [processVideoFrame:](#ByteRTCVideoProcessorDelegate-processvideoframe) |


## 函数说明
<span id="ByteRTCVideoProcessorDelegate-processvideoframe"></span>
### processVideoFrame:
```objectivec

- (ByteRTCVideoFrame* _Nullable) processVideoFrame:(ByteRTCVideoFrame* _Nonnull)src_frame;
```
获取 RTC SDK 采集得到的视频帧，根据 [registerLocalVideoProcessor:withConfig:](iOS-api.md#ByteRTCVideo-registerlocalvideoprocessor-withconfig) 设置的视频前处理器，进行视频前处理，最终将处理后的视频帧给到 RTC SDK 用于编码传输。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| src_frame | **ByteRTCVideoFrame*** | RTC SDK 采集得到的视频帧，参考: [ByteRTCVideoFrame](iOS-keytype.md#bytertcvideoframe) |

**返回值**
经过视频前处理后的视频帧，返回给 RTC SDK 供编码和传输，参考: [ByteRTCVideoFrame](iOS-keytype.md#bytertcvideoframe)


**注意**
如果需要取消视频前处理，可以将视频前处理器设置为 nullptr。

# ByteRTCLocalEncodedVideoFrameObserver
```objectivec
@protocol ByteRTCLocalEncodedVideoFrameObserver<NSObject>
```

本地视频帧监测器


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **void** | [onLocalEncodedVideoFrame:Frame:](#ByteRTCLocalEncodedVideoFrameObserver-onlocalencodedvideoframe-frame) |


## 函数说明
<span id="ByteRTCLocalEncodedVideoFrameObserver-onlocalencodedvideoframe-frame"></span>
### onLocalEncodedVideoFrame:Frame:
```objectivec

- (void)onLocalEncodedVideoFrame:(ByteRTCStreamIndex) streamIndex Frame:(ByteRTCEncodedVideoFrame * _Null_unspecified)frame;
```
调用 [registerLocalEncodedVideoFrameObserver:](iOS-api.md#ByteRTCVideo-registerlocalencodedvideoframeobserver) 后，SDK 每次使用内部采集，采集到一帧视频帧，或收到一帧外部视频帧时，都会回调该事件。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamIndex | **ByteRTCStreamIndex** | 本地视频帧类型，参看 [ByteRTCStreamIndex](iOS-keytype.md#bytertcstreamindex) |
| frame | **ByteRTCEncodedVideoFrame* _Null_unspecified** | 本地视频帧信息，参看 [ByteRTCEncodedVideoFrame](iOS-keytype.md#bytertcencodedvideoframe) |


# ByteRTCExternalVideoEncoderEventHandler
```objectivec
@protocol ByteRTCExternalVideoEncoderEventHandler<NSObject>
```

自定义编码帧回调类


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **void** | [onStart:](#ByteRTCExternalVideoEncoderEventHandler-onstart) |
| **void** | [onStop:](#ByteRTCExternalVideoEncoderEventHandler-onstop) |
| **void** | [onRateUpdate:withVideoIndex:withFps:withBitRate:](#ByteRTCExternalVideoEncoderEventHandler-onrateupdate-withvideoindex-withfps-withbitrate) |
| **void** | [onRequestKeyFrame:withVideoIndex:](#ByteRTCExternalVideoEncoderEventHandler-onrequestkeyframe-withvideoindex) |


## 函数说明
<span id="ByteRTCExternalVideoEncoderEventHandler-onstart"></span>
### onStart:
```objectivec

- (void)onStart:(ByteRTCStreamIndex)streamIndex;
```
提示自定义编码帧可以开始推送的回调。  <br>
收到该回调后，你即可调用 [pushExternalEncodedVideoFrame:withVideoIndex:withEncodedVideoFrame:](iOS-api.md#ByteRTCVideo-pushexternalencodedvideoframe-withvideoindex-withencodedvideoframe) 向 SDK 推送自定义编码视频帧

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamIndex | **ByteRTCStreamIndex** | 可以推送的编码流的属性，参看 [ByteRTCStreamIndex](iOS-keytype.md#bytertcstreamindex) |


<span id="ByteRTCExternalVideoEncoderEventHandler-onstop"></span>
### onStop:
```objectivec

- (void)onStop:(ByteRTCStreamIndex)streamIndex;
```
当收到该回调时，你需停止向 SDK 推送自定义编码视频帧

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamIndex | **ByteRTCStreamIndex** | 需停止推送的编码流的属性，参看 [ByteRTCStreamIndex](iOS-keytype.md#bytertcstreamindex) |


<span id="ByteRTCExternalVideoEncoderEventHandler-onrateupdate-withvideoindex-withfps-withbitrate"></span>
### onRateUpdate:withVideoIndex:withFps:withBitRate:
```objectivec

- (void)onRateUpdate:(ByteRTCStreamIndex)streamIndex withVideoIndex:(NSInteger)videoIndex withFps:(NSInteger)fps withBitRate:(NSInteger)bitRateKps;
```
当自定义编码流的帧率或码率发生变化时，触发该回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamIndex | **ByteRTCStreamIndex** | 发生变化的编码流的属性，参看 [ByteRTCStreamIndex](iOS-keytype.md#bytertcstreamindex) |
| videoIndex | **NSInteger** | 对应编码流的下标 |
| fps | **NSInteger** | 变化后的帧率，单位：fps |
| bitRateKps | **NSInteger** | 变化后的码率，单位：kbps |


<span id="ByteRTCExternalVideoEncoderEventHandler-onrequestkeyframe-withvideoindex"></span>
### onRequestKeyFrame:withVideoIndex:
```objectivec

- (void)onRequestKeyFrame:(ByteRTCStreamIndex)streamIndex withVideoIndex:(NSInteger)videoIndex;
```
提示流发布端需重新生成关键帧的回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamIndex | **ByteRTCStreamIndex** | 远端编码流的属性，参看 [ByteRTCStreamIndex](iOS-keytype.md#bytertcstreamindex) |
| videoIndex | **NSInteger** | 对应编码流的下标 |


# ByteRTCRemoteEncodedVideoFrameObserver
```objectivec
@protocol ByteRTCRemoteEncodedVideoFrameObserver<NSObject>
```

远端编码后视频数据监测器


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **void** | [onRemoteEncodedVideoFrame:withEncodedVideoFrame:](#ByteRTCRemoteEncodedVideoFrameObserver-onremoteencodedvideoframe-withencodedvideoframe) |


## 函数说明
<span id="ByteRTCRemoteEncodedVideoFrameObserver-onremoteencodedvideoframe-withencodedvideoframe"></span>
### onRemoteEncodedVideoFrame:withEncodedVideoFrame:
```objectivec

- (void)onRemoteEncodedVideoFrame:(ByteRTCRemoteStreamKey * _Nonnull)streamKey withEncodedVideoFrame:(ByteRTCEncodedVideoFrame* _Nonnull)videoFrame;
```
调用 [registerRemoteEncodedVideoFrameObserver:](iOS-api.md#ByteRTCVideo-registerremoteencodedvideoframeobserver) 后，SDK 监测到远端编码后视频数据时，触发该回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamKey | **ByteRTCRemoteStreamKey*** | 收到的远端流信息，参看 [ByteRTCRemoteStreamKey](iOS-keytype.md#bytertcremotestreamkey) |
| videoFrame | **ByteRTCEncodedVideoFrame*** | 收到的远端视频帧信息，参看 [ByteRTCEncodedVideoFrame](iOS-keytype.md#bytertcencodedvideoframe) |


# LiveTranscodingDelegate
```objectivec
@protocol LiveTranscodingDelegate <NSObject>
```

转推直播观察者。  <br>


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **BOOL** | [isSupportClientPushStream](#LiveTranscodingDelegate-issupportclientpushstream) |
| **void** | [onStreamMixingEvent:taskId:error:mixType:](#LiveTranscodingDelegate-onstreammixingevent-taskid-error-mixtype) |
| **void** | [onMixingAudioFrame:taskId:](#LiveTranscodingDelegate-onmixingaudioframe-taskid) |
| **void** | [onMixingVideoFrame:taskId:](#LiveTranscodingDelegate-onmixingvideoframe-taskid) |
| **void** | [onMixingDataFrame:taskId:](#LiveTranscodingDelegate-onmixingdataframe-taskid) |


## 函数说明
<span id="LiveTranscodingDelegate-issupportclientpushstream"></span>
### isSupportClientPushStream
```objectivec

- (BOOL)isSupportClientPushStream;
```
是否具有推流能力。  <br>

+ false：不具备推流能力（默认值）  <br>
+ true：具备推流能力


**注意**

+ 如果需要开启端云一体转推直播功能，你必须确保你的 App 包含 librtmp，具有推流能力。此时，设置该回调为 true。


<span id="LiveTranscodingDelegate-onstreammixingevent-taskid-error-mixtype"></span>
### onStreamMixingEvent:taskId:error:mixType:
```objectivec

- (void)onStreamMixingEvent:(ByteRTCStreamMixingEvent)event taskId:(NSString *_Nonnull)taskId error:(ByteRtcTranscoderErrorCode)Code mixType:(ByteRTCStreamMixingType)mixType;
```
转推直播状态回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| event | **ByteRTCStreamMixingEvent** | 转推直播任务状态，参看 [ByteRTCStreamMixingEvent](iOS-keytype.md#bytertcstreammixingevent)。 |
| taskId | **NSString*** | 转推直播任务 ID。 |
| Code | **ByteRtcTranscoderErrorCode** | 转推直播错误码，参看 [ByteRtcTranscoderErrorCode](iOS-errorcode.md#bytertctranscodererrorcode) 和 [ByteRTCTranscodingError](iOS-errorcode.md#bytertctranscodingerror)。 |
| mixType | **ByteRTCStreamMixingType** | 转推直播类型，参看 [ByteRTCStreamMixingType](iOS-keytype.md#bytertcstreammixingtype)。 |


<span id="LiveTranscodingDelegate-onmixingaudioframe-taskid"></span>
### onMixingAudioFrame:taskId:
```objectivec

- (void)onMixingAudioFrame:(ByteRTCAudioFrame *_Nonnull)audioFrame taskId:(NSString *_Nonnull)taskId;
```
端云一体合流音频 PCM 回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioFrame | **ByteRTCAudioFrame*** | PCM 编码的合流音频数据帧，参看 [ByteRTCAudioFrame](iOS-keytype.md#bytertcaudioframe)。 |
| taskId | **NSString*** | 转推直播任务 ID。 |


**注意**
收到该回调的周期为每 10 毫秒一次，并且每次的音频数据量为 10 毫秒数据量。

<span id="LiveTranscodingDelegate-onmixingvideoframe-taskid"></span>
### onMixingVideoFrame:taskId:
```objectivec

- (void)onMixingVideoFrame:(ByteRTCVideoFrame *_Nonnull)videoFrame taskId:(NSString *_Nonnull)taskId;
```
端云一体合流视频 YUV 回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| videoFrame | **ByteRTCVideoFrame*** | YUV 合流视频数据帧，参看 [ByteRTCVideoFrame](iOS-keytype.md#bytertcvideoframe)。 |
| taskId | **NSString*** | 转推直播任务 ID。 |


**注意**
收到该回调的周期取决于视频的帧率。

<span id="LiveTranscodingDelegate-onmixingdataframe-taskid"></span>
### onMixingDataFrame:taskId:
```objectivec

- (void)onMixingDataFrame:(ByteRTCFrameExtendedData *_Nonnull)dataFrame taskId:(NSString *_Nonnull)taskId;
```
端云一体合流视频 SEI 数据

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| dataFrame | **ByteRTCFrameExtendedData*** | SEI 数据，详见 [ByteRTCFrameExtendedData](iOS-keytype.md#bytertcframeextendeddata)。 |
| taskId | **NSString*** | 转推直播任务 ID。 |


# ByteRTCPushSingleStreamToCDNObserver
```objectivec
@protocol ByteRTCPushSingleStreamToCDNObserver <NSObject>
```

单流转推直播观察者。  <br>


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **void** | [onStreamPushEvent:taskId:error:](#ByteRTCPushSingleStreamToCDNObserver-onstreampushevent-taskid-error) |


## 函数说明
<span id="ByteRTCPushSingleStreamToCDNObserver-onstreampushevent-taskid-error"></span>
### onStreamPushEvent:taskId:error:
```objectivec

- (void)onStreamPushEvent:(ByteRTCSingleStreamPushEvent)event taskId:(NSString *_Nonnull)taskId error:(NSInteger)Code;
```
单流转推直播状态回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| event | **ByteRTCSingleStreamPushEvent** | 任务状态, 参看 [ByteRTCSingleStreamPushEvent](iOS-errorcode.md#bytertcsinglestreampushevent). |
| taskId | **NSString*** | 任务 ID |
| Code | **NSInteger** | 错误码，参看 [ByteRtcTranscoderErrorCode](iOS-errorcode.md#bytertctranscodererrorcode) 和 [ByteRTCTranscodingError](iOS-errorcode.md#bytertctranscodingerror)。 |


# ByteRTCFaceDetectionObserver
```objectivec
@protocol ByteRTCFaceDetectionObserver <NSObject>
```

人脸检测结果回调观察者


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **void** | [onFaceDetectionResult:](#ByteRTCFaceDetectionObserver-onfacedetectionresult) |


## 函数说明
<span id="ByteRTCFaceDetectionObserver-onfacedetectionresult"></span>
### onFaceDetectionResult:
```objectivec

- (void)onFaceDetectionResult:(ByteRTCFaceDetectionResult * _Nonnull)result;
```
特效 SDK 进行人脸检测结果的回调。 <br>
调用 [registerFaceDetectionObserver:withInterval:](iOS-api.md#ByteRTCVideo-registerfacedetectionobserver-withinterval) 注册了 [ByteRTCFaceDetectionObserver](#bytertcfacedetectionobserver) ，并使用 RTC SDK 中包含的特效 SDK 进行视频特效处理时，你会收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| result | **ByteRTCFaceDetectionResult*** | 人脸检测结果, 参看 [ByteRTCFaceDetectionResult](iOS-keytype.md#bytertcfacedetectionresult)。 |


# ByteRTCVideoSnapshotCallbackDelegate
```objectivec
@protocol ByteRTCVideoSnapshotCallbackDelegate <NSObject>
```



## 成员函数

| 返回 | 名称 |
| --- | --- |
| **void** | [onTakeLocalSnapshotResult:streamIndex:image:errorCode:](#ByteRTCVideoSnapshotCallbackDelegate-ontakelocalsnapshotresult-streamindex-image-errorcode) |
| **void** | [onTakeRemoteSnapshotResult:streamKey:image:errorCode:](#ByteRTCVideoSnapshotCallbackDelegate-ontakeremotesnapshotresult-streamkey-image-errorcode) |


## 函数说明
<span id="ByteRTCVideoSnapshotCallbackDelegate-ontakelocalsnapshotresult-streamindex-image-errorcode"></span>
### onTakeLocalSnapshotResult:streamIndex:image:errorCode:
```objectivec

- (void)onTakeLocalSnapshotResult:(NSInteger) taskId streamIndex:(ByteRTCStreamIndex)streamIndex image:(ByteRTCImage * _Nullable)image errorCode:(NSInteger)errorCode;
```
调用 [takeLocalSnapshot:callback:](iOS-api.md#ByteRTCVideo-takelocalsnapshot-callback) 截取视频画面时，收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| taskId | **NSInteger** | 本地截图任务的编号。和 [takeLocalSnapshot:callback:](iOS-api.md#ByteRTCVideo-takelocalsnapshot-callback) 的返回值一致。 |
| streamIndex | **ByteRTCStreamIndex** | 截图的视频流的属性，参看 [ByteRTCStreamIndex](iOS-keytype.md#bytertcstreamindex)。 |
| image | **ByteRTCImage*** | 截图。你可以保存为文件，或对其进行二次处理。截图失败时，为空。 |
| errorCode | **NSInteger** | 截图错误码：<br/>• 0: 成功 <br/>• -1: 截图错误。生成图片数据失败或 RGBA 编码失败 <br/>• -2: 截图错误。流无效。 |


<span id="ByteRTCVideoSnapshotCallbackDelegate-ontakeremotesnapshotresult-streamkey-image-errorcode"></span>
### onTakeRemoteSnapshotResult:streamKey:image:errorCode:
```objectivec

- (void)onTakeRemoteSnapshotResult:(NSInteger)taskId streamKey:(ByteRTCRemoteStreamKey * _Nonnull)streamKey image:(ByteRTCImage * _Nullable)image errorCode:(NSInteger)errorCode;
```
调用 [takeRemoteSnapshot:callback:](iOS-api.md#ByteRTCVideo-takeremotesnapshot-callback) 截取视频画面时，收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| taskId | **NSInteger** | 远端截图任务的编号。和 [takeRemoteSnapshot:callback:](iOS-api.md#ByteRTCVideo-takeremotesnapshot-callback) 的返回值一致。 |
| streamKey | **ByteRTCRemoteStreamKey*** | 截图的视频流，参看 [ByteRTCRemoteStreamKey](iOS-keytype.md#bytertcremotestreamkey)。 |
| image | **ByteRTCImage*** | 截图。你可以保存为文件，或对其进行二次处理。截图失败时，为空。 |
| errorCode | **NSInteger** | 截图错误码：<br/>• 0: 成功 <br/>• -1: 截图错误。生成图片数据失败或 RGBA 编码失败 <br/>• -2: 截图错误。流无效。 |