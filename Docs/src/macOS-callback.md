# ByteRTCRoomDelegate
```objectivec
@protocol ByteRTCRoomDelegate <NSObject>
```

房间事件回调接口
注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **void** | [rtcRoom:onRoomStateChanged:withUid:state:extraInfo:](#ByteRTCRoomDelegate-rtcroom-onroomstatechanged-withuid-state-extrainfo) |
| **void** | [rtcRoom:onStreamStateChanged:withUid:state:extraInfo:](#ByteRTCRoomDelegate-rtcroom-onstreamstatechanged-withuid-state-extrainfo) |
| **void** | [rtcRoom:onLeaveRoom:](#ByteRTCRoomDelegate-rtcroom-onleaveroom) |
| **void** | [rtcRoom:onAVSyncStateChange:](#ByteRTCRoomDelegate-rtcroom-onavsyncstatechange) |
| **void** | [rtcRoom:onRoomStats:](#ByteRTCRoomDelegate-rtcroom-onroomstats) |
| **void** | [rtcRoom:onLocalStreamStats:](#ByteRTCRoomDelegate-rtcroom-onlocalstreamstats) |
| **void** | [rtcRoom:onRemoteStreamStats:](#ByteRTCRoomDelegate-rtcroom-onremotestreamstats) |
| **void** | [rtcRoom:onUserJoined:elapsed:](#ByteRTCRoomDelegate-rtcroom-onuserjoined-elapsed) |
| **void** | [rtcRoom:onUserLeave:reason:](#ByteRTCRoomDelegate-rtcroom-onuserleave-reason) |
| **void** | [onTokenWillExpire:](#ByteRTCRoomDelegate-ontokenwillexpire) |
| **void** | [onPublishPrivilegeTokenWillExpire:](#ByteRTCRoomDelegate-onpublishprivilegetokenwillexpire) |
| **void** | [onSubscribePrivilegeTokenWillExpire:](#ByteRTCRoomDelegate-onsubscribeprivilegetokenwillexpire) |
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
| **void** | [rtcRoom:onSetRoomExtraInfoResult:error:](#ByteRTCRoomDelegate-rtcroom-onsetroomextrainforesult-error) |
| **void** | [rtcRoom:onRoomExtraInfoUpdate:value:lastUpdateUserId:lastUpdateTimeMs:](#ByteRTCRoomDelegate-rtcroom-onroomextrainfoupdate-value-lastupdateuserid-lastupdatetimems) |
| **void** | [rtcRoom:onVideoStreamBanned:isBanned:](#ByteRTCRoomDelegate-rtcroom-onvideostreambanned-isbanned) |
| **void** | [rtcRoom:onAudioStreamBanned:isBanned:](#ByteRTCRoomDelegate-rtcroom-onaudiostreambanned-isbanned) |
| **void** | [rtcRoom:onForwardStreamStateChanged:](#ByteRTCRoomDelegate-rtcroom-onforwardstreamstatechanged) |
| **void** | [rtcRoom:onForwardStreamEvent:](#ByteRTCRoomDelegate-rtcroom-onforwardstreamevent) |
| **void** | [rtcRoom:onNetworkQuality:remoteQualities:](#ByteRTCRoomDelegate-rtcroom-onnetworkquality-remotequalities) |
| **void** | [rtcRoom:onSubtitleStateChanged:errorCode:errorMessage:](#ByteRTCRoomDelegate-rtcroom-onsubtitlestatechanged-errorcode-errormessage) |
| **void** | [rtcRoom:onSubtitleMessageReceived:](#ByteRTCRoomDelegate-rtcroom-onsubtitlemessagereceived) |
| **void** | [[deprecated] rtcRoom:onRoomWarning:](#ByteRTCRoomDelegate-rtcroom-onroomwarning) |
| **void** | [[deprecated] rtcRoom:onRoomError:](#ByteRTCRoomDelegate-rtcroom-onroomerror) |
| **void** | [[deprecated] rtcRoom:onStreamAdd:](#ByteRTCRoomDelegate-rtcroom-onstreamadd) |
| **void** | [[deprecated] rtcRoom:onStreamRemove:stream:reason:](#ByteRTCRoomDelegate-rtcroom-onstreamremove-stream-reason) |


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
| rtcRoom | **ByteRTCRoom*** | ByteRTCAudioRoom 实例 |
| roomId | **NSString*** | 房间 ID。 |
| uid | **NSString*** | 用户 ID。 |
| state | **NSInteger** | 房间状态码。  <br/>• 0: 加入房间成功。  <br/>• !0: 加入房间失败、异常退房、发生房间相关的警告或错误。具体原因参看 [ByteRTCErrorCode](macOS-errorcode.md#bytertcerrorcode) 及 [ByteRTCWarningCode](macOS-errorcode.md#bytertcwarningcode)。 |
| extraInfo | **NSString*** | 额外信息，如 `{"elapsed":1187,"join_type":0}`。<br/>`join_type`表示加入房间的类型，`0`为首次进房，`1`为重连进房。<br/>`elapsed`表示加入房间耗时，即本地用户从调用 [joinRoom:userInfo:roomConfig:](macOS-api.md#ByteRTCRoom-joinroom-userinfo-roomconfig) 到加入房间成功所经历的时间间隔，单位为 ms。 |


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
| state | **NSInteger** | 流状态码，参看 [ByteRTCErrorCode](macOS-errorcode.md#bytertcerrorcode) 及 [ByteRTCWarningCode](macOS-errorcode.md#bytertcwarningcode)。 |
| extraInfo | **NSString*** | 附加信息，目前为空。 |


<span id="ByteRTCRoomDelegate-rtcroom-onleaveroom"></span>
### rtcRoom:onLeaveRoom:
```objectivec

- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onLeaveRoom:(ByteRTCRoomStats *_Nonnull)stats;
```
离开房间成功回调。  <br>
用户调用 [leaveRoom](macOS-api.md#ByteRTCRoom-leaveroom) 方法后，SDK 会停止所有的发布订阅流，并释放所有通话相关的音视频资源。SDK 完成所有的资源释放后通过此回调通知用户。  <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | **ByteRTCRoom*** | ByteRTCRoom 对象。 |
| stats | **ByteRTCRoomStats*** | 保留参数，目前为空。 |


**注意**

+ 用户调用 [leaveRoom](macOS-api.md#ByteRTCRoom-leaveroom) 方法离开房间后，如果立即调用 [destroyRTCVideo](macOS-api.md#ByteRTCVideo-destroyrtcvideo) 方法销毁 RTC 引擎，则将无法收到此回调事件。  
+ 离开房间结束通话后，如果 App 需要使用系统音视频设备，则建议在收到此回调后再初始化音视频设备，否则可能由于 SDK 占用了导致 App 初始化音视频设备失败。  


<span id="ByteRTCRoomDelegate-rtcroom-onroomwarning"></span>
### rtcRoom:onRoomWarning:
```objectivec

- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onRoomWarning:(ByteRTCWarningCode)warningCode __deprecated_msg("Will be removed in new version");
```
> Deprecated  since 3.41 and will be deleted in 3.51, use [rtcRoom:onRoomStateChanged:withUid:state:extraInfo:](#ByteRTCRoomDelegate-rtcroom-onroomstatechanged-withuid-state-extrainfo) and [rtcRoom:onStreamStateChanged:withUid:state:extraInfo:](#ByteRTCRoomDelegate-rtcroom-onstreamstatechanged-withuid-state-extrainfo) instead.

发生警告回调。  <br>
SDK 运行时出现了警告。SDK 通常会自动恢复，警告信息可以忽略。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | **ByteRTCRoom*** | ByteRTCRoom 对象。 |
| warningCode | **ByteRTCWarningCode** | 警告码，详见枚举类型 [ByteRTCWarningCode](macOS-errorcode.md#bytertcwarningcode) 。 |


<span id="ByteRTCRoomDelegate-rtcroom-onroomerror"></span>
### rtcRoom:onRoomError:
```objectivec

- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onRoomError:(ByteRTCErrorCode)errorCode __deprecated_msg("Will be removed in new version");
```
> Deprecated  since 3.41 and will be deleted in 3.51, use [rtcRoom:onRoomStateChanged:withUid:state:extraInfo:](#ByteRTCRoomDelegate-rtcroom-onroomstatechanged-withuid-state-extrainfo) and [rtcRoom:onStreamStateChanged:withUid:state:extraInfo:](#ByteRTCRoomDelegate-rtcroom-onstreamstatechanged-withuid-state-extrainfo) instead.

发生错误回调。  <br>
SDK 运行时出现了错误。SDK 通常无法自动恢复，应用需要采取行动。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | **ByteRTCRoom*** | ByteRTCRoom 对象。 |
| errorCode | **ByteRTCErrorCode** | 错误码，详见枚举类型 [ByteRTCErrorCode](macOS-errorcode.md#bytertcerrorcode) 。 |


<span id="ByteRTCRoomDelegate-rtcroom-onavsyncstatechange"></span>
### rtcRoom:onAVSyncStateChange:
```objectivec

- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onAVSyncStateChange:(ByteRTCAVSyncState)state;
```
发布端调用 [setMultiDeviceAVSync:](macOS-api.md#ByteRTCRoom-setmultideviceavsync) 后音视频同步状态发生改变时，会收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | **ByteRTCRoom*** | ByteRTCRoom 实例 |
| state | **ByteRTCAVSyncState** | 音视频同步状态，参看 [ByteRTCAVSyncState](macOS-keytype.md#bytertcavsyncstate)。 |


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
| stats | **ByteRTCRoomStats*** | 当前 ByteRTCRoom 统计数据，详见：[ByteRTCRoomStats](macOS-keytype.md#bytertcroomstats) |


<span id="ByteRTCRoomDelegate-rtcroom-onlocalstreamstats"></span>
### rtcRoom:onLocalStreamStats:
```objectivec

- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onLocalStreamStats:(ByteRTCLocalStreamStats *_Nonnull)stats;
```
本地流数据统计以及网络质量回调。  <br>
本地用户发布流成功后，SDK 会周期性（2s）的通过此回调事件通知用户发布的流在此次统计周期内的质量统计信息。  <br>
统计信息通过 [ByteRTCLocalStreamStats](macOS-keytype.md#bytertclocalstreamstats) 类型的回调参数传递给用户，其中包括发送音视频比特率、发送帧率、编码帧率，网络质量等。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | **ByteRTCRoom*** | ByteRTCRoom 对象。 |
| stats | **ByteRTCLocalStreamStats*** | 当前房间本地流数据统计。详见：[ByteRTCLocalStreamStats](macOS-keytype.md#bytertclocalstreamstats) |


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
| stats | **ByteRTCRemoteStreamStats*** | 当前房间本地流数据统计。 详见：[ByteRTCRemoteStreamStats](macOS-keytype.md#bytertcremotestreamstats) |


<span id="ByteRTCRoomDelegate-rtcroom-onuserjoined-elapsed"></span>
### rtcRoom:onUserJoined:elapsed:
```objectivec

- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onUserJoined:(ByteRTCUserInfo *_Nonnull)userInfo elapsed:(NSInteger)elapsed;
```
远端可见用户加入房间，或房内隐身用户切换为可见的回调。<br>
1. 远端用户调用 [setUserVisibility:](macOS-api.md#ByteRTCRoom-setuservisibility) 方法将自身设为可见后加入房间时，房间内其他用户将收到该事件。  <br>
2. 远端可见用户断网后重新连入房间时，房间内其他用户将收到该事件。  <br>
3. 房间内隐身远端用户调用 [setUserVisibility:](macOS-api.md#ByteRTCRoom-setuservisibility) 方法切换至可见时，房间内其他用户将收到该事件。  <br>
4. 新进房用户会收到进房前已在房内的可见用户的进房回调通知。  <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | **ByteRTCRoom*** | ByteRTCRoom 对象。 |
| userInfo | **ByteRTCUserInfo*** | 用户信息，参看 [ByteRTCUserInfo](macOS-keytype.md#bytertcuserinfo)。 |
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
| reason | **ByteRTCUserOfflineReason** | 用户离开房间的原因：  <br/>• 0: 远端用户调用 [leaveRoom](macOS-api.md#ByteRTCRoom-leaveroom) 主动退出房间。  <br/>• 1: 远端用户因 Token 过期或网络原因等掉线。详细信息请参看[连接状态提示](https://www.volcengine.com/docs/6348/95376) <br/>• 2: 远端用户调用 [setUserVisibility:](macOS-api.md#ByteRTCRoom-setuservisibility) 切换至不可见状态。 <br/>• 3: 服务端调用 OpenAPI 将远端用户踢出房间。 |


<span id="ByteRTCRoomDelegate-ontokenwillexpire"></span>
### onTokenWillExpire:
```objectivec

- (void)onTokenWillExpire:( ByteRTCRoom *_Nonnull)rtcRoom;
```
Token 进房权限过期前 30 秒将触发该回调。<br>
收到该回调后，你需调用 [updateToken:](macOS-api.md#ByteRTCRoom-updatetoken) 更新 Token 进房权限。


**注意**
若 Token 进房权限过期且未及时更新： + 用户此时尝试进房会收到 [rtcRoom:onRoomStateChanged:withUid:state:extraInfo:](#ByteRTCRoomDelegate-rtcroom-onroomstatechanged-withuid-state-extrainfo) 回调，提示错误码为 `-1000` Token 无效； 

+ 用户已在房间内则会被移出房间，本地用户会收到 [rtcRoom:onRoomStateChanged:withUid:state:extraInfo:](#ByteRTCRoomDelegate-rtcroom-onroomstatechanged-withuid-state-extrainfo) 回调，提示错误码为 `-1009` Token 过期，同时远端用户会收到 [rtcRoom:onUserLeave:reason:](#ByteRTCRoomDelegate-rtcroom-onuserleave-reason) 回调，提示原因为 `2` Token 进房权限过期。


<span id="ByteRTCRoomDelegate-onpublishprivilegetokenwillexpire"></span>
### onPublishPrivilegeTokenWillExpire:
```objectivec

- (void)onPublishPrivilegeTokenWillExpire:( ByteRTCRoom *_Nonnull)rtcRoom;
```
Token 发布权限过期前 30 秒将触发该回调。<br>
收到该回调后，你需调用 [updateToken:](macOS-api.md#ByteRTCRoom-updatetoken) 更新 Token 发布权限。


**注意**
若收到该回调后未及时更新 Token，Token 发布权限过期后： + 此时尝试发布流会收到 [rtcRoom:onStreamStateChanged:withUid:state:extraInfo:](#ByteRTCRoomDelegate-rtcroom-onstreamstatechanged-withuid-state-extrainfo) 回调，提示错误码为 `-1002` 没有发布权限； 

+ 已在发布中的流会停止发布，发布端会收到 [rtcRoom:onStreamStateChanged:withUid:state:extraInfo:](#ByteRTCRoomDelegate-rtcroom-onstreamstatechanged-withuid-state-extrainfo) 回调，提示错误码为 `-1002` 没有发布权限，同时远端用户会收到 [rtcRoom:onUserUnpublishStream:type:reason:](#ByteRTCRoomDelegate-rtcroom-onuserunpublishstream-type-reason)/[rtcRoom:onUserUnpublishScreen:type:reason:](#ByteRTCRoomDelegate-rtcroom-onuserunpublishscreen-type-reason) 回调，提示原因为 `6` 发流端发布权限过期。


<span id="ByteRTCRoomDelegate-onsubscribeprivilegetokenwillexpire"></span>
### onSubscribePrivilegeTokenWillExpire:
```objectivec

- (void)onSubscribePrivilegeTokenWillExpire:( ByteRTCRoom *_Nonnull)rtcRoom;
```
Token 订阅权限过期前 30 秒将触发该回调。<br>
收到该回调后，你需调用 [updateToken:](macOS-api.md#ByteRTCRoom-updatetoken) 更新 Token 订阅权限有效期。


**注意**
若收到该回调后未及时更新 Token，Token 订阅权限过期后，尝试新订阅流会失败，已订阅的流会取消订阅，并且会收到 [rtcRoom:onStreamStateChanged:withUid:state:extraInfo:](#ByteRTCRoomDelegate-rtcroom-onstreamstatechanged-withuid-state-extrainfo) 回调，提示错误码为 `-1003` 没有订阅权限。

<span id="ByteRTCRoomDelegate-rtcroom-onstreamadd"></span>
### rtcRoom:onStreamAdd:
```objectivec

- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onStreamAdd:(id<ByteRTCStream> _Nonnull)stream __deprecated_msg("Will be removed in new version");
```
> Deprecated  since 3.36 and will be deleted in 3.51, use [rtcRoom:onUserPublishStream:type:](#ByteRTCRoomDelegate-rtcroom-onuserpublishstream-type) and [rtcRoom:onUserPublishScreen:type:](#ByteRTCRoomDelegate-rtcroom-onuserpublishscreen-type) instead.

以下情况会触发此回调：<br>

+ 房间内的用户发布新的音视频流时，房间内的其他用户会收到此回调通知。  <br>
+ 房间内的用户原音视频流被移出后，又重新发布音视频流时，房间内的其他用户会收到此回调通知。  <br>
+ 用户刚加入房间时，会收到此回调，包含房间中所有已发布的流。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | **ByteRTCRoom*** | ByteRTCRoom 对象。 |
| stream | **id<ByteRTCStream>** | 流属性，参看 [ByteRTCStream](macOS-keytype.md#bytertcstream) 。 |


<span id="ByteRTCRoomDelegate-rtcroom-onstreamremove-stream-reason"></span>
### rtcRoom:onStreamRemove:stream:reason:
```objectivec

- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onStreamRemove:(NSString *_Nonnull)uid stream:(id<ByteRTCStream> _Nonnull)stream reason:(ByteRTCStreamRemoveReason)reason;
```
> Deprecated  since 3.36 and will be deleted in 3.51, use [rtcRoom:onUserUnpublishStream:type:reason:](#ByteRTCRoomDelegate-rtcroom-onuserunpublishstream-type-reason) and [rtcRoom:onUserUnpublishScreen:type:reason:](#ByteRTCRoomDelegate-rtcroom-onuserunpublishscreen-type-reason) instead.

房间内的远端用户停止发布音视频流时，本地用户会收到此回调通知。  <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | **ByteRTCRoom*** | ByteRTCRoom 对象 |
| uid | **NSString*** | 远端流来源的用户 ID 。 |
| stream | **id<ByteRTCStream>** | 流的属性，参看 [ByteRTCStream](macOS-keytype.md#bytertcstream)。 |
| reason | **ByteRTCStreamRemoveReason** | 远端流移除的原因，参看 [ByteRTCStreamRemoveReason](macOS-keytype.md#bytertcstreamremovereason) 。 |


<span id="ByteRTCRoomDelegate-rtcroom-onuserpublishstream-type"></span>
### rtcRoom:onUserPublishStream:type:
```objectivec

- (void)rtcRoom:( ByteRTCRoom * _Nonnull)rtcRoom onUserPublishStream:(NSString *_Nonnull)userId type:(ByteRTCMediaStreamType)type;
```
房间内新增远端摄像头/麦克风采集的媒体流的回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | **ByteRTCRoom*** | ByteRTCRoom 实例 |
| userId | **NSString*** | 远端流发布用户的用户 ID。 |
| type | **ByteRTCMediaStreamType** | 远端媒体流的类型，参看 [ByteRTCMediaStreamType](macOS-keytype.md#bytertcmediastreamtype)。 |


**注意**
当房间内的远端用户调用 [publishStream:](macOS-api.md#ByteRTCRoom-publishstream) 成功发布由摄像头/麦克风采集的媒体流时，本地用户会收到该回调，此时本地用户可以自行选择是否调用 [subscribeStream:mediaStreamType:](macOS-api.md#ByteRTCRoom-subscribestream-mediastreamtype) 订阅此流。

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
| type | **ByteRTCMediaStreamType** | 移除的远端流类型，参看 [ByteRTCMediaStreamType](macOS-keytype.md#bytertcmediastreamtype)。 |
| reason | **ByteRTCStreamRemoveReason** | 远端流移除的原因，参看 [ByteRTCStreamRemoveReason](macOS-keytype.md#bytertcstreamremovereason)。 |


**注意**
收到该回调通知后，你可以自行选择是否调用 [unsubscribeStream:mediaStreamType:](macOS-api.md#ByteRTCRoom-unsubscribestream-mediastreamtype) 取消订阅此流。

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
| type | **ByteRTCMediaStreamType** | 远端媒体流的类型，参看 [ByteRTCMediaStreamType](macOS-keytype.md#bytertcmediastreamtype)。 |


**注意**
当房间内的远端用户调用 [publishScreen:](macOS-api.md#ByteRTCRoom-publishscreen) 成功发布来自屏幕共享的音视频流时，本地用户会收到该回调，此时本地用户可以自行选择是否调用 [subscribeScreen:mediaStreamType:](macOS-api.md#ByteRTCRoom-subscribescreen-mediastreamtype) 订阅此流。

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
| type | **ByteRTCMediaStreamType** | 移除的远端流类型，参看 [ByteRTCMediaStreamType](macOS-keytype.md#bytertcmediastreamtype)。 |
| reason | **ByteRTCStreamRemoveReason** | 远端流移除的原因，参看 [ByteRTCStreamRemoveReason](macOS-keytype.md#bytertcstreamremovereason)。 |


**注意**
收到该回调通知后，你可以自行选择是否调用 [unsubscribeScreen:mediaStreamType:](macOS-api.md#ByteRTCRoom-unsubscribescreen-mediastreamtype) 取消订阅此流。

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
| state | **ByteRTCSubscribeState** | 订阅媒体流状态，参看 [ByteRTCSubscribeState](macOS-keytype.md#bytertcsubscribestate) |
| userId | **NSString*** | 流发布用户的用户 ID |
| info | **ByteRTCSubscribeConfig*** | 流的属性，参看 [ByteRTCSubscribeConfig](macOS-keytype.md#bytertcsubscribeconfig) |


**注意**
本地用户收到该回调的时机包括：  + 调用 [subscribeStream:mediaStreamType:](macOS-api.md#ByteRTCRoom-subscribestream-mediastreamtype) 或 [unsubscribeStream:mediaStreamType:](macOS-api.md#ByteRTCRoom-unsubscribestream-mediastreamtype) 订阅/取消订阅指定远端摄像头音视频流后；  

+ 调用 [subscribeScreen:mediaStreamType:](macOS-api.md#ByteRTCRoom-subscribescreen-mediastreamtype) 或 [unsubscribeScreen:mediaStreamType:](macOS-api.md#ByteRTCRoom-unsubscribescreen-mediastreamtype) 订阅/取消订阅指定远端屏幕共享流后。


<span id="ByteRTCRoomDelegate-rtcroom-onroommessagereceived-message"></span>
### rtcRoom:onRoomMessageReceived:message:
```objectivec

- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onRoomMessageReceived:(NSString *_Nonnull)uid message:(NSString *_Nonnull)message;
```
收到房间中调用 [sendRoomMessage:](macOS-api.md#ByteRTCRoom-sendroommessage) 发送的广播文本消息时，收到此回调。

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
收到房间内广播二进制消息的回调。<br>
房间内其他用户调用 [sendRoomBinaryMessage:](macOS-api.md#ByteRTCRoom-sendroombinarymessage) 发送的广播二进制消息时，收到此回调。

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
收到来自房间中其他用户通过 [sendUserMessage:message:config:](macOS-api.md#ByteRTCRoom-sendusermessage-message-config) 发来的点对点文本消息时，会收到此回调。

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
收到来自房间中其他用户通过 [sendUserBinaryMessage:message:config:](macOS-api.md#ByteRTCRoom-senduserbinarymessage-message-config) 发来的点对点二进制消息时，会收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | **ByteRTCRoom*** | ByteRTCRoom 对象 |
| uid | **NSString*** | 消息发送者的用户 ID 。 |
| message | **NSData*** | 收到的二进制消息内容。 |


<span id="ByteRTCRoomDelegate-rtcroom-onusermessagesendresult-error"></span>
### rtcRoom:onUserMessageSendResult:error:
```objectivec

- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onUserMessageSendResult:(NSInteger)msgid error:(ByteRTCUserMessageSendResult)error;
```
向房间内单个用户发送文本或二进制消息后（P2P），消息发送方会收到该消息发送结果回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | **ByteRTCRoom*** | ByteRTCRoom 对象。 |
| msgid | **NSInteger** | 本条消息的 ID。 |
| error | **ByteRTCUserMessageSendResult** | 消息发送结果，详见 [ByteRTCUserMessageSendResult](macOS-errorcode.md#bytertcusermessagesendresult) |


**注意**

+ 你应调用 [sendUserMessage:message:config:](macOS-api.md#ByteRTCRoom-sendusermessage-message-config) 向房间内单个用户发送文本消息 
+ 你应调用 [sendUserBinaryMessage:message:config:](macOS-api.md#ByteRTCRoom-senduserbinarymessage-message-config) 向房间内单个用户发送二进制消息


<span id="ByteRTCRoomDelegate-rtcroom-onroommessagesendresult-error"></span>
### rtcRoom:onRoomMessageSendResult:error:
```objectivec

- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onRoomMessageSendResult:(NSInteger)msgid error:(ByteRTCRoomMessageSendResult)error;
```
调用 [sendRoomMessage:](macOS-api.md#ByteRTCRoom-sendroommessage) 或 [sendRoomBinaryMessage:](macOS-api.md#ByteRTCRoom-sendroombinarymessage) 向房间内群发文本或二进制消息后，消息发送方会收到该消息发送结果回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | **ByteRTCRoom*** | ByteRTCRoom 对象。 |
| msgid | **NSInteger** | 本条消息的 ID。 |
| error | **ByteRTCRoomMessageSendResult** | 消息发送结果，详见 [ByteRTCRoomMessageSendResult](macOS-errorcode.md#bytertcroommessagesendresult) |


<span id="ByteRTCRoomDelegate-rtcroom-onsetroomextrainforesult-error"></span>
### rtcRoom:onSetRoomExtraInfoResult:error:
```objectivec

- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onSetRoomExtraInfoResult:(NSInteger)taskId error:(ByteRTCSetRoomExtraInfoResult)error;
```
> Available since 3.52.

调用 [setRoomExtraInfo:value:](macOS-api.md#ByteRTCRoom-setroomextrainfo-value) 结果回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | **ByteRTCRoom*** | ByteRTCRoom 对象。 |
| taskId | **NSInteger** | 本次调用的任务编号。 |
| error | **ByteRTCSetRoomExtraInfoResult** | 设置房间附加信息结果，详见 [ByteRTCSetRoomExtraInfoResult](macOS-keytype.md#bytertcsetroomextrainforesult) |


<span id="ByteRTCRoomDelegate-rtcroom-onroomextrainfoupdate-value-lastupdateuserid-lastupdatetimems"></span>
### rtcRoom:onRoomExtraInfoUpdate:value:lastUpdateUserId:lastUpdateTimeMs:
```objectivec

- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onRoomExtraInfoUpdate:(NSString *_Nonnull)key value:(NSString *_Nonnull)value lastUpdateUserId:(NSString *_Nonnull)lastUpdateUserId lastUpdateTimeMs:(NSInteger)lastUpdateTimeMs;
```
> Available since 3.52.

接收到房间附加信息的回调。<br>
房间内其他用户调用 [setRoomExtraInfo:value:](macOS-api.md#ByteRTCRoom-setroomextrainfo-value) 设置房间附加信息，收到此回调。<br>
另外用户加入房间成功后会收到这个房间全量附加信息

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | **ByteRTCRoom*** | ByteRTCRoom 对象。 |
| key | **NSString*** | 附加信息的键值 |
| value | **NSString*** | 附加信息的内容 |
| lastUpdateUserId | **NSString*** | 最后更新这条附加信息的用户编号 |
| lastUpdateTimeMs | **NSInteger** | 最后更新这条附加信息的Unix时间，时间精度是毫秒 |


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
+ 在控制台开启音频选路后，只有被封禁/解禁用户会收到该回调。
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
| infos | **NSArray<ForwardStreamStateInfo*>*** | 跨房间媒体流转发目标房间信息数组，详见 [ForwardStreamStateInfo](macOS-keytype.md#forwardstreamstateinfo) |


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
| infos | **NSArray<ForwardStreamEventInfo*>*** | 跨房间媒体流转发目标房间事件数组，详见 [ForwardStreamEventInfo](macOS-keytype.md#forwardstreameventinfo) |


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
| localQuality | **ByteRTCNetworkQualityStats*** | 本端网络质量，详见 [ByteRTCNetworkQualityStats](macOS-keytype.md#bytertcnetworkqualitystats)。 |
| remoteQualities | **NSArray<ByteRTCNetworkQualityStats*>*** | 已订阅用户的网络质量，详见 [ByteRTCNetworkQualityStats](macOS-keytype.md#bytertcnetworkqualitystats)。 |


**注意**
更多通话中的监测接口，详见[通话中质量监测](https://www.volcengine.com/docs/6348/106866)。

<span id="ByteRTCRoomDelegate-rtcroom-onsubtitlestatechanged-errorcode-errormessage"></span>
### rtcRoom:onSubtitleStateChanged:errorCode:errorMessage:
```objectivec

- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onSubtitleStateChanged:(ByteRTCSubtitleState)state errorCode:(ByteRTCSubtitleErrorCode)errorCode errorMessage:(NSString *_Nonnull)errorMessage;
```
字幕状态发生改变回调。 <br>
当用户调用 [startSubtitle:](macOS-api.md#ByteRTCRoom-startsubtitle) 和 [stopSubtitle](macOS-api.md#ByteRTCRoom-stopsubtitle) 使字幕状态发生改变或出现错误时，触发该回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | **ByteRTCRoom*** | ByteRTCRoom 实例。 |
| state | **ByteRTCSubtitleState** | 字幕状态。参看 [ByteRTCSubtitleState](macOS-keytype.md#bytertcsubtitlestate)。 |
| errorCode | **ByteRTCSubtitleErrorCode** | 字幕任务错误码。参看 [ByteRTCSubtitleErrorCode](macOS-keytype.md#bytertcsubtitleerrorcode)。 |
| errorMessage | **NSString*** | 第三方服务出现的错误。当因第三方服务出现错误，导致字幕状态改变时，用户可通过此参数获取具体的错误信息。如果不是因为第三方服务导致字幕状态改变，该字段为空。 |


<span id="ByteRTCRoomDelegate-rtcroom-onsubtitlemessagereceived"></span>
### rtcRoom:onSubtitleMessageReceived:
```objectivec

- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onSubtitleMessageReceived:(NSArray<ByteRTCSubtitleMessage*> * _Nonnull)subtitles;
```
字幕相关内容回调。 <br>
当用户调用 [startSubtitle:](macOS-api.md#ByteRTCRoom-startsubtitle) 后会收到此回调，通知字幕的相关信息。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | **ByteRTCRoom*** | ByteRTCRoom 实例。 |
| subtitles | **NSArray<ByteRTCSubtitleMessage*>*** | 字幕消息内容。参看 [ByteRTCSubtitleMessage](macOS-keytype.md#bytertcsubtitlemessage)。 |


# ByteRTCVideoDelegate
```objectivec
@protocol ByteRTCVideoDelegate <NSObject>
```

ByteRTCVideoDelegate 协议包含了SDK提供的回调方法，SDK通过代理向应用程序上报一些运行时事件
注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **void** | [rtcEngine:onWarning:](#ByteRTCVideoDelegate-rtcengine-onwarning) |
| **void** | [rtcEngine:onError:](#ByteRTCVideoDelegate-rtcengine-onerror) |
| **void** | [rtcEngine:onExtensionAccessError:msg:](#ByteRTCVideoDelegate-rtcengine-onextensionaccesserror-msg) |
| **void** | [rtcEngine:onCreateRoomStateChanged:errorCode:](#ByteRTCVideoDelegate-rtcengine-oncreateroomstatechanged-errorcode) |
| **void** | [rtcEngine:onConnectionStateChanged:](#ByteRTCVideoDelegate-rtcengine-onconnectionstatechanged) |
| **void** | [rtcEngine:onNetworkTypeChanged:](#ByteRTCVideoDelegate-rtcengine-onnetworktypechanged) |
| **void** | [rtcEngine:onUserStartAudioCapture:uid:](#ByteRTCVideoDelegate-rtcengine-onuserstartaudiocapture-uid) |
| **void** | [rtcEngine:onUserStopAudioCapture:uid:](#ByteRTCVideoDelegate-rtcengine-onuserstopaudiocapture-uid) |
| **void** | [rtcEngine:onFirstRemoteAudioFrame:](#ByteRTCVideoDelegate-rtcengine-onfirstremoteaudioframe) |
| **void** | [rtcEngine:onLocalAudioPropertiesReport:](#ByteRTCVideoDelegate-rtcengine-onlocalaudiopropertiesreport) |
| **void** | [rtcEngine:onAudioPlaybackDeviceTestVolume:](#ByteRTCVideoDelegate-rtcengine-onaudioplaybackdevicetestvolume) |
| **void** | [rtcEngine:onAudioDeviceVolumeChanged:volume:muted:](#ByteRTCVideoDelegate-rtcengine-onaudiodevicevolumechanged-volume-muted) |
| **void** | [rtcEngine:onRemoteAudioPropertiesReport:totalRemoteVolume:](#ByteRTCVideoDelegate-rtcengine-onremoteaudiopropertiesreport-totalremotevolume) |
| **void** | [rtcEngine:onActiveSpeaker:uid:](#ByteRTCVideoDelegate-rtcengine-onactivespeaker-uid) |
| **void** | [rtcEngine:onUserStartVideoCapture:uid:](#ByteRTCVideoDelegate-rtcengine-onuserstartvideocapture-uid) |
| **void** | [rtcEngine:onUserStopVideoCapture:uid:](#ByteRTCVideoDelegate-rtcengine-onuserstopvideocapture-uid) |
| **void** | [rtcEngine:onFirstLocalVideoFrameCaptured:withFrameInfo:](#ByteRTCVideoDelegate-rtcengine-onfirstlocalvideoframecaptured-withframeinfo) |
| **void** | [rtcEngine:onFirstRemoteVideoFrameRendered:withFrameInfo:](#ByteRTCVideoDelegate-rtcengine-onfirstremotevideoframerendered-withframeinfo) |
| **void** | [rtcEngine:onFirstRemoteVideoFrameDecoded:withFrameInfo:](#ByteRTCVideoDelegate-rtcengine-onfirstremotevideoframedecoded-withframeinfo) |
| **void** | [rtcEngine:onRemoteVideoSizeChanged:withFrameInfo:](#ByteRTCVideoDelegate-rtcengine-onremotevideosizechanged-withframeinfo) |
| **void** | [rtcEngine:onLocalVideoSizeChanged:withFrameInfo:](#ByteRTCVideoDelegate-rtcengine-onlocalvideosizechanged-withframeinfo) |
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
| **void** | [rtcEngine:onSEIMessageReceived:andMessage:](#ByteRTCVideoDelegate-rtcengine-onseimessagereceived-andmessage) |
| **void** | [rtcEngine:onSEIStreamUpdate:eventType:](#ByteRTCVideoDelegate-rtcengine-onseistreamupdate-eventtype) |
| **void** | [rtcEngine:onStreamSyncInfoReceived:streamType:data:](#ByteRTCVideoDelegate-rtcengine-onstreamsyncinforeceived-streamtype-data) |
| **void** | [rtcEngine:onSysStats:](#ByteRTCVideoDelegate-rtcengine-onsysstats) |
| **void** | [rtcEngine:onRemoteAudioStateChanged:state:reason:](#ByteRTCVideoDelegate-rtcengine-onremoteaudiostatechanged-state-reason) |
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
| **void** | [rtcEngine:onPerformanceAlarms:roomId:reason:sourceWantedData:](#ByteRTCVideoDelegate-rtcengine-onperformancealarms-roomid-reason-sourcewanteddata) |
| **void** | [rtcEngine:onSimulcastSubscribeFallback:](#ByteRTCVideoDelegate-rtcengine-onsimulcastsubscribefallback) |
| **void** | [rtcEngine:onExternalScreenFrameUpdate:](#ByteRTCVideoDelegate-rtcengine-onexternalscreenframeupdate) |
| **void** | [rtcEngine:onRecordingStateUpdate:state:error_code:recording_info:](#ByteRTCVideoDelegate-rtcengine-onrecordingstateupdate-state-error_code-recording_info) |
| **void** | [rtcEngine:onRecordingProgressUpdate:process:recording_info:](#ByteRTCVideoDelegate-rtcengine-onrecordingprogressupdate-process-recording_info) |
| **void** | [rtcEngine:onAudioRecordingStateUpdate:error_code:](#ByteRTCVideoDelegate-rtcengine-onaudiorecordingstateupdate-error_code) |
| **void** | [rtcEngine:onPushPublicStreamResult:publicStreamId:errorCode:](#ByteRTCVideoDelegate-rtcengine-onpushpublicstreamresult-publicstreamid-errorcode) |
| **void** | [rtcEngine:onPlayPublicStreamResult:errorCode:](#ByteRTCVideoDelegate-rtcengine-onplaypublicstreamresult-errorcode) |
| **void** | [rtcEngine:onPublicStreamSEIMessageReceived:andMessage:andSourceType:](#ByteRTCVideoDelegate-rtcengine-onpublicstreamseimessagereceived-andmessage-andsourcetype) |
| **void** | [rtcEngine:onPublicStreamDataMessageReceived:andMessage:andSourceType:](#ByteRTCVideoDelegate-rtcengine-onpublicstreamdatamessagereceived-andmessage-andsourcetype) |
| **void** | [rtcEngine:onFirstPublicStreamVideoFrameDecoded:withFrameInfo:](#ByteRTCVideoDelegate-rtcengine-onfirstpublicstreamvideoframedecoded-withframeinfo) |
| **void** | [rtcEngine:onFirstPublicStreamAudioFrame:](#ByteRTCVideoDelegate-rtcengine-onfirstpublicstreamaudioframe) |
| **void** | [rtcEngine:onCloudProxyConnected:](#ByteRTCVideoDelegate-rtcengine-oncloudproxyconnected) |
| **void** | [rtcEngine:onEchoTestResult:](#ByteRTCVideoDelegate-rtcengine-onechotestresult) |
| **void** | [rtcEngineOnNetworkTimeSynchronized:](#ByteRTCVideoDelegate-rtcengineonnetworktimesynchronized) |
| **void** | [rtcEngine:onLicenseWillExpire:](#ByteRTCVideoDelegate-rtcengine-onlicensewillexpire) |
| **void** | [rtcEngine:onHardwareEchoDetectionResult:](#ByteRTCVideoDelegate-rtcengine-onhardwareechodetectionresult) |
| **void** | [rtcEngine:onLocalProxyStateChanged:withProxyState:withProxyError:](#ByteRTCVideoDelegate-rtcengine-onlocalproxystatechanged-withproxystate-withproxyerror) |
| **void** | [[deprecated] rtcEngine:onUserMuteAudio:uid:muteState:](#ByteRTCVideoDelegate-rtcengine-onusermuteaudio-uid-mutestate) |
| **void** | [[deprecated] rtcEngine:onUserMuteVideo:uid:withMuteState:](#ByteRTCVideoDelegate-rtcengine-onusermutevideo-uid-withmutestate) |
| **void** | [[deprecated] rtcEngine:onMediaDeviceStateChanged:device_type:device_state:device_error:](#ByteRTCVideoDelegate-rtcengine-onmediadevicestatechanged-device_type-device_state-device_error) |
| **void** | [[deprecated] rtcEngine:onMediaDeviceWarning:deviceType:deviceWarning:](#ByteRTCVideoDelegate-rtcengine-onmediadevicewarning-devicetype-devicewarning) |
| **void** | [[deprecated] rtcEngine:onLocalAudioStateChanged:error:](#ByteRTCVideoDelegate-rtcengine-onlocalaudiostatechanged-error) |
| **void** | [[deprecated] rtcEngine:onLocalVideoStateChanged:withStreamState:withStreamError:](#ByteRTCVideoDelegate-rtcengine-onlocalvideostatechanged-withstreamstate-withstreamerror) |
| **void** | [[deprecated] rtcEngine:log:](#ByteRTCVideoDelegate-rtcengine-log) |
| **void** | [[deprecated] rtcEngine:onHttpProxyState:](#ByteRTCVideoDelegate-rtcengine-onhttpproxystate) |
| **void** | [[deprecated] rtcEngine:onHttpsProxyState:](#ByteRTCVideoDelegate-rtcengine-onhttpsproxystate) |
| **void** | [[deprecated] rtcEngine:onSocks5ProxyState:cmd:proxy_address:local_address:remote_address:](#ByteRTCVideoDelegate-rtcengine-onsocks5proxystate-cmd-proxy_address-local_address-remote_address) |


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
| Code | **ByteRTCWarningCode** | 警告代码，参看 [ByteRTCWarningCode](macOS-errorcode.md#bytertcwarningcode)。 |


<span id="ByteRTCVideoDelegate-rtcengine-onerror"></span>
### rtcEngine:onError:
```objectivec

- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onError:(ByteRTCErrorCode)errorCode;
```
发生错误回调。<br>
SDK 运行时出现了网络或媒体相关的错误，且无法自动恢复时触发此回调。<br>
你可能需要干预.

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象。 |
| errorCode | **ByteRTCErrorCode** | 错误代码，参看 [ByteRTCErrorCode](macOS-errorcode.md#bytertcerrorcode)。 |


<span id="ByteRTCVideoDelegate-rtcengine-onextensionaccesserror-msg"></span>
### rtcEngine:onExtensionAccessError:msg:
```objectivec

- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onExtensionAccessError:(NSString * _Nonnull)extensionName msg:(NSString * _Nonnull)msg;
```
> Available since 3.52

当访问插件失败时，收到此回调。
RTC SDK 将一些功能封装成插件。当使用这些功能时，如果插件不存在，功能将无法使用。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| extensionName | **NSString*** | 插件名字 |
| msg | **NSString*** | 失败说明 |


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
| errorCode | **NSInteger** | 创建房间错误码，具体原因参看 [ByteRTCErrorCode](macOS-errorcode.md#bytertcerrorcode)。 |


<span id="ByteRTCVideoDelegate-rtcengine-onconnectionstatechanged"></span>
### rtcEngine:onConnectionStateChanged:
```objectivec

- (void) rtcEngine:(ByteRTCVideo * _Nonnull)engine onConnectionStateChanged:(ByteRTCConnectionState) state;
```
SDK 与信令服务器连接状态改变回调。连接状态改变时触发。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象 |
| state | **ByteRTCConnectionState** | 当前 SDK 与信令服务器的连接状态，详见 [ByteRTCConnectionState](macOS-keytype.md#bytertcconnectionstate)。 |


**注意**
更多信息参见 [连接状态提示](https://www.volcengine.com/docs/6348/95376)。

<span id="ByteRTCVideoDelegate-rtcengine-onnetworktypechanged"></span>
### rtcEngine:onNetworkTypeChanged:
```objectivec

- (void) rtcEngine:(ByteRTCVideo * _Nonnull)engine onNetworkTypeChanged:(ByteRTCNetworkType) type;
```
SDK 当前网络连接类型改变回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象 |
| type | **ByteRTCNetworkType** | SDK 当前的网络连接类型，详见 [ByteRTCNetworkType](macOS-keytype.md#bytertcnetworktype) |


<span id="ByteRTCVideoDelegate-rtcengine-onusermuteaudio-uid-mutestate"></span>
### rtcEngine:onUserMuteAudio:uid:muteState:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onUserMuteAudio:(NSString * _Nonnull)roomId uid:(NSString * _Nonnull)uid muteState:(ByteRTCMuteState)muteState __deprecated_msg("Will be removed in new version");
```
> Deprecated  since 3.36 and will be deleted in 3.51, use [rtcRoom:onUserPublishStream:type:](#ByteRTCRoomDelegate-rtcroom-onuserpublishstream-type), [rtcRoom:onUserPublishScreen:type:](#ByteRTCRoomDelegate-rtcroom-onuserpublishscreen-type), [rtcRoom:onUserUnpublishStream:type:reason:](#ByteRTCRoomDelegate-rtcroom-onuserunpublishstream-type-reason) and [rtcRoom:onUserUnpublishScreen:type:reason:](#ByteRTCRoomDelegate-rtcroom-onuserunpublishscreen-type-reason) instead.

房间内用户暂停/恢复发送音频流时，房间内其他用户会收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 实例 |
| uid | **NSString*** | 改变本地音频发送状态的用户 ID |
| muteState | **ByteRTCMuteState** | 发送状态，参看 [ByteRTCMuteState](macOS-keytype.md#bytertcmutestate) |


<span id="ByteRTCVideoDelegate-rtcengine-onuserstartaudiocapture-uid"></span>
### rtcEngine:onUserStartAudioCapture:uid:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onUserStartAudioCapture:(NSString* _Nonnull)roomId uid:(NSString *_Nonnull)userId;
```
房间内的可见用户调用 [startAudioCapture](macOS-api.md#ByteRTCVideo-startaudiocapture) 开启音频采集时，房间内其他用户会收到此回调。

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
房间内的可见用户调用 [stopAudioCapture](macOS-api.md#ByteRTCVideo-stopaudiocapture) 关闭音频采集时，房间内其他用户会收到此回调。

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
| key | **ByteRTCRemoteStreamKey*** | 远端流信息, 详见 [ByteRTCRemoteStreamKey](macOS-keytype.md#bytertcremotestreamkey) |


**注意**
用户刚收到房间内每一路音频流时，都会收到该回调。

<span id="ByteRTCVideoDelegate-rtcengine-onlocalaudiopropertiesreport"></span>
### rtcEngine:onLocalAudioPropertiesReport:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onLocalAudioPropertiesReport:(NSArray<ByteRTCLocalAudioPropertiesInfo *> * _Nonnull)audioPropertiesInfos;
```
调用 [enableAudioPropertiesReport:](macOS-api.md#ByteRTCVideo-enableaudiopropertiesreport) 后，根据设置的 interval 值，你会周期性地收到此回调，了解本地音频的相关信息。  <br>
本地音频包括使用 RTC SDK 内部机制采集的麦克风音频，屏幕音频和本地混音音频信息。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象 |
| audioPropertiesInfos | **NSArray<ByteRTCLocalAudioPropertiesInfo*>*** | 本地音频信息，详见 [ByteRTCLocalAudioPropertiesInfo](macOS-keytype.md#bytertclocalaudiopropertiesinfo) 。 |


<span id="ByteRTCVideoDelegate-rtcengine-onaudioplaybackdevicetestvolume"></span>
### rtcEngine:onAudioPlaybackDeviceTestVolume:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onAudioPlaybackDeviceTestVolume:(int)volume;
```
回调音频设备测试时的播放音量

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| volume | **int** | 音频设备测试播放音量。单位：毫秒。推荐设置为 200 ms。范围：[0,255] |


**注意**
调用 [startAudioPlaybackDeviceTest:interval:](macOS-api.md#ByteRTCAudioDeviceManager-startaudioplaybackdevicetest-interval) 或 [startAudioDeviceRecordTest:](macOS-api.md#ByteRTCAudioDeviceManager-startaudiodevicerecordtest)，开始播放音频文件或录音时，将开启该回调。本回调为周期性回调，回调周期由上述接口的 `interval` 参数指定。

<span id="ByteRTCVideoDelegate-rtcengine-onaudiodevicevolumechanged-volume-muted"></span>
### rtcEngine:onAudioDeviceVolumeChanged:volume:muted:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onAudioDeviceVolumeChanged:(ByteRTCAudioDeviceType)device_type volume:(int)volume muted:(bool)muted;
```
音频设备音量改变回调。当通过系统设置，改变音频设备音量或静音状态时，触发本回调。本回调无需手动开启。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| device_type | **ByteRTCAudioDeviceType** | 设备类型，包括麦克风和扬声器，参阅 [ByteRTCAudioDeviceType](macOS-keytype.md#bytertcaudiodevicetype)。 |
| volume | **int** | 音量值，[0, 255]。当 volume 变为 0 时，muted 会转为 True。 |
| muted | **bool** | 是否禁音状态。扬声器被设置为禁音时，muted 为 True，但 volume 保持不变。 |


<span id="ByteRTCVideoDelegate-rtcengine-onremoteaudiopropertiesreport-totalremotevolume"></span>
### rtcEngine:onRemoteAudioPropertiesReport:totalRemoteVolume:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onRemoteAudioPropertiesReport:(NSArray<ByteRTCRemoteAudioPropertiesInfo *> * _Nonnull)audioPropertiesInfos totalRemoteVolume:(NSInteger)totalRemoteVolume;
```
远端用户进房后，本地调用 [enableAudioPropertiesReport:](macOS-api.md#ByteRTCVideo-enableaudiopropertiesreport) ，根据设置的 interval 值，本地会周期性地收到此回调，了解订阅的远端用户的音频信息。<br>
远端用户的音频包括使用 RTC SDK 内部机制/自定义机制采集的麦克风音频和屏幕音频。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象 |
| audioPropertiesInfos | **NSArray<ByteRTCRemoteAudioPropertiesInfo*>*** | 远端音频信息，其中包含音频流属性、房间 ID、用户 ID ，详见 [ByteRTCRemoteAudioPropertiesInfo](macOS-keytype.md#bytertcremoteaudiopropertiesinfo)。 |
| totalRemoteVolume | **NSInteger** | 订阅的所有远端流的总音量，范围是 [0,255]。  <br/>• [0,25] 接近无声；  <br/>• [25,75] 为低音量；  <br/>• [76,204] 为中音量；  <br/>• [205,255] 为高音量。 |


<span id="ByteRTCVideoDelegate-rtcengine-onactivespeaker-uid"></span>
### rtcEngine:onActiveSpeaker:uid:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onActiveSpeaker:(NSString * _Nonnull)roomId uid:(NSString *_Nonnull)uid;
```
调用 [enableAudioPropertiesReport:](macOS-api.md#ByteRTCVideo-enableaudiopropertiesreport)  后，根据设置的 `config.interval`，你会周期性地收到此回调，获取房间内的最活跃用户信息。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| roomId | **NSString*** | 房间 ID |
| uid | **NSString*** | 最活跃用户（ActiveSpeaker）的用户 ID |


<span id="ByteRTCVideoDelegate-rtcengine-onusermutevideo-uid-withmutestate"></span>
### rtcEngine:onUserMuteVideo:uid:withMuteState:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onUserMuteVideo:(NSString * _Nonnull)roomId uid:(NSString * _Nonnull)uid withMuteState:(ByteRTCMuteState)muteState ;
```
> Deprecated  since 3.36 and will be deleted in 3.51, use [rtcRoom:onUserPublishStream:type:](#ByteRTCRoomDelegate-rtcroom-onuserpublishstream-type), [rtcRoom:onUserPublishScreen:type:](#ByteRTCRoomDelegate-rtcroom-onuserpublishscreen-type), [rtcRoom:onUserUnpublishStream:type:reason:](#ByteRTCRoomDelegate-rtcroom-onuserunpublishstream-type-reason) and [rtcRoom:onUserUnpublishScreen:type:reason:](#ByteRTCRoomDelegate-rtcroom-onuserunpublishscreen-type-reason) instead.

房间内用户暂停/恢复发送视频流时，房间内其他用户会收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 实例 |
| uid | **NSString*** | 暂停/恢复发送视频流的用户 ID。 |
| muteState | **ByteRTCMuteState** | 视频流的发送状态。参看 [ByteRTCMuteState](macOS-keytype.md#bytertcmutestate)。 |


<span id="ByteRTCVideoDelegate-rtcengine-onuserstartvideocapture-uid"></span>
### rtcEngine:onUserStartVideoCapture:uid:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onUserStartVideoCapture:(NSString * _Nonnull)roomId uid:(NSString * _Nonnull)uid;
```
房间内的可见用户调用 [startVideoCapture](macOS-api.md#ByteRTCVideo-startvideocapture) 开启内部视频采集时，房间中其他用户会收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 实例 |
| roomId | **NSString*** | 开启视频采集的用户所在的房间 ID |
| uid | **NSString*** | 调用 [startVideoCapture](macOS-api.md#ByteRTCVideo-startvideocapture) 接口的远端用户 ID |


<span id="ByteRTCVideoDelegate-rtcengine-onuserstopvideocapture-uid"></span>
### rtcEngine:onUserStopVideoCapture:uid:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onUserStopVideoCapture:(NSString * _Nonnull)roomId uid:(NSString * _Nonnull)uid;
```
房间内的可见用户调用 [stopVideoCapture](macOS-api.md#ByteRTCVideo-stopvideocapture) 关闭内部视频采集时，房间内其他用户会收到此回调。

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
| streamIndex | **ByteRTCStreamIndex** | 流属性，参看 [ByteRTCStreamIndex](macOS-keytype.md#bytertcstreamindex) |
| frameInfo | **ByteRTCVideoFrameInfo*** | 视频帧信息，参看 [ByteRTCVideoFrameInfo](macOS-keytype.md#bytertcvideoframeinfo) |


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
| streamKey | **ByteRTCRemoteStreamKey*** | 远端流信息，参看 [ByteRTCRemoteStreamKey](macOS-keytype.md#bytertcremotestreamkey) |
| frameInfo | **ByteRTCVideoFrameInfo*** | 视频帧信息，参看 [ByteRTCVideoFrameInfo](macOS-keytype.md#bytertcvideoframeinfo) |


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
| streamKey | **ByteRTCRemoteStreamKey*** | 远端流信息，参看 [ByteRTCRemoteStreamKey](macOS-keytype.md#bytertcremotestreamkey) |
| frameInfo | **ByteRTCVideoFrameInfo*** | 视频帧信息，参看 [ByteRTCVideoFrameInfo](macOS-keytype.md#bytertcvideoframeinfo) |


**注意**

+ 对于主流，进入房间后，仅在发布端第一次发布的时候，订阅端会收到该回调，此后不受重新发布的影响，只要不重新加入房间，就不会再收到该回调。
+ 对于屏幕流，用户每次重新发布屏幕视频流在订阅端都会重新触发一次该回调。


<span id="ByteRTCVideoDelegate-rtcengine-onremotevideosizechanged-withframeinfo"></span>
### rtcEngine:onRemoteVideoSizeChanged:withFrameInfo:
```objectivec

- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onRemoteVideoSizeChanged:(ByteRTCRemoteStreamKey *_Nonnull)streamKey withFrameInfo:(ByteRTCVideoFrameInfo *_Nonnull)frameInfo;
```
远端视频大小或旋转信息发生改变时，房间内订阅此视频流的用户会收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象 |
| streamKey | **ByteRTCRemoteStreamKey*** | 流属性，参看 [ByteRTCRemoteStreamKey](macOS-keytype.md#bytertcremotestreamkey) |
| frameInfo | **ByteRTCVideoFrameInfo*** | 视频帧信息，参看 [ByteRTCVideoFrameInfo](macOS-keytype.md#bytertcvideoframeinfo) |


<span id="ByteRTCVideoDelegate-rtcengine-onlocalvideosizechanged-withframeinfo"></span>
### rtcEngine:onLocalVideoSizeChanged:withFrameInfo:
```objectivec

- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onLocalVideoSizeChanged:(ByteRTCStreamIndex)streamIndex withFrameInfo:(ByteRTCVideoFrameInfo *_Nonnull)frameInfo;
```
本地视频大小或旋转信息发生改变时，收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象 |
| streamIndex | **ByteRTCStreamIndex** | 流属性，参看 [ByteRTCStreamIndex](macOS-keytype.md#bytertcstreamindex) |
| frameInfo | **ByteRTCVideoFrameInfo*** | 视频帧信息，参看 [ByteRTCVideoFrameInfo](macOS-keytype.md#bytertcvideoframeinfo) |


<span id="ByteRTCVideoDelegate-rtcengine-onmediadevicestatechanged-device_type-device_state-device_error"></span>
### rtcEngine:onMediaDeviceStateChanged:device_type:device_state:device_error:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onMediaDeviceStateChanged:(NSString*_Nonnull)device_id device_type:(ByteRTCMediaDeviceType)device_type device_state:(ByteRTCMediaDeviceState)device_state device_error:(ByteRTCMediaDeviceError)device_error;
```
> Deprecated  since 3.37 and will be deleted in 3.51, use [rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:](#ByteRTCVideoDelegate-rtcengine-onaudiodevicestatechanged-device_type-device_state-device_error) and [rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:](#ByteRTCVideoDelegate-rtcengine-onvideodevicestatechanged-device_type-device_state-device_error) instead.

媒体设备状态回调。提示音频采集、音频播放、摄像头视频采集、屏幕视频采集四种媒体设备的状态。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 实例 |
| device_id | **NSString*** | 设备 ID |
| device_type | **ByteRTCMediaDeviceType** | 设备类型，参看 [ByteRTCMediaDeviceType](macOS-keytype.md#bytertcmediadevicetype)。 |
| device_state | **ByteRTCMediaDeviceState** | 设备状态，参看 [ByteRTCMediaDeviceState](macOS-keytype.md#bytertcmediadevicestate)。 |
| device_error | **ByteRTCMediaDeviceError** | 设备错误类型，参看 [ByteRTCMediaDeviceError](macOS-keytype.md#bytertcmediadeviceerror)。 |


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
| device_type | **ByteRTCAudioDeviceType** | 设备类型，参看 [ByteRTCAudioDeviceType](macOS-keytype.md#bytertcaudiodevicetype)。 |
| device_state | **ByteRTCMediaDeviceState** | 设备状态，参看 [ByteRTCMediaDeviceState](macOS-keytype.md#bytertcmediadevicestate)。 |
| device_error | **ByteRTCMediaDeviceError** | 设备错误类型，参看 [ByteRTCMediaDeviceError](macOS-keytype.md#bytertcmediadeviceerror)。 |


<span id="ByteRTCVideoDelegate-rtcengine-onvideodevicestatechanged-device_type-device_state-device_error"></span>
### rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onVideoDeviceStateChanged:(NSString*_Nonnull)device_id device_type:(ByteRTCVideoDeviceType)device_type device_state:(ByteRTCMediaDeviceState)device_state device_error:(ByteRTCMediaDeviceError)device_error;
```
视频设备状态发生改变回调。当设备的视频状态发生改变时，SDK 会触发该回调，提示摄像头视频采集、屏幕视频采集等设备的状态。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| device_id | **NSString*** | 设备 ID |
| device_type | **ByteRTCVideoDeviceType** | 设备类型，参看 [ByteRTCVideoDeviceType](macOS-keytype.md#bytertcvideodevicetype)。 |
| device_state | **ByteRTCMediaDeviceState** | 设备状态，参看 [ByteRTCMediaDeviceState](macOS-keytype.md#bytertcmediadevicestate)。 |
| device_error | **ByteRTCMediaDeviceError** | 设备错误类型，参看 [ByteRTCMediaDeviceError](macOS-keytype.md#bytertcmediadeviceerror)。 |


<span id="ByteRTCVideoDelegate-rtcengine-onmediadevicewarning-devicetype-devicewarning"></span>
### rtcEngine:onMediaDeviceWarning:deviceType:deviceWarning:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onMediaDeviceWarning:(NSString*_Nonnull)deviceId deviceType:(ByteRTCMediaDeviceType)deviceType deviceWarning:(ByteRTCMediaDeviceWarning)deviceWarning;
```
> Deprecated  since 3.37 and will be deleted in 3.51, use [rtcEngine:onAudioDeviceWarning:deviceType:deviceWarning:](#ByteRTCVideoDelegate-rtcengine-onaudiodevicewarning-devicetype-devicewarning) and [rtcEngine:onVideoDeviceWarning:deviceType:deviceWarning:](#ByteRTCVideoDelegate-rtcengine-onvideodevicewarning-devicetype-devicewarning) instead.

媒体设备警告回调。媒体设备包括：音频采集设备、音频渲染设备、和视频采集设备。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象 |
| deviceId | **NSString*** | 设备 ID |
| deviceType | **ByteRTCMediaDeviceType** | 参看 [ByteRTCMediaDeviceType](macOS-keytype.md#bytertcmediadevicetype) |
| deviceWarning | **ByteRTCMediaDeviceWarning** | 参看 [ByteRTCMediaDeviceWarning](macOS-keytype.md#bytertcmediadevicewarning) |


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
| deviceType | **ByteRTCAudioDeviceType** | 参看 [ByteRTCAudioDeviceType](macOS-keytype.md#bytertcaudiodevicetype) |
| deviceWarning | **ByteRTCMediaDeviceWarning** | 参看 [ByteRTCMediaDeviceWarning](macOS-keytype.md#bytertcmediadevicewarning) |


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
| deviceType | **ByteRTCVideoDeviceType** | 参看 [ByteRTCVideoDeviceType](macOS-keytype.md#bytertcvideodevicetype) |
| deviceWarning | **ByteRTCMediaDeviceWarning** | 参看 [ByteRTCMediaDeviceWarning](macOS-keytype.md#bytertcmediadevicewarning) |


<span id="ByteRTCVideoDelegate-rtcengine-onaudioframesendstatechanged-rtcuser-state"></span>
### rtcEngine:onAudioFrameSendStateChanged:rtcUser:state:
```objectivec

- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onAudioFrameSendStateChanged:(NSString * _Nonnull)roomId rtcUser:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFrameSendState)state;
```
本地音频首帧发送状态发生改变时，收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象 |
| roomId | **NSString*** | 音频流发布用户所在的房间 ID |
| user | **ByteRTCUser*** | 本地用户信息，详见 [ByteRTCUser](macOS-keytype.md#bytertcuser) |
| state | **ByteRTCFirstFrameSendState** | 首帧发送状态，详见 [ByteRTCFirstFrameSendState](macOS-keytype.md#bytertcfirstframesendstate) |


<span id="ByteRTCVideoDelegate-rtcengine-onvideoframesendstatechanged-rtcuser-state"></span>
### rtcEngine:onVideoFrameSendStateChanged:rtcUser:state:
```objectivec

- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onVideoFrameSendStateChanged:(NSString * _Nonnull)roomId rtcUser:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFrameSendState)state;
```
本地视频首帧发送状态发生改变时，收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象 |
| roomId | **NSString*** | 视频流发布用户所在的房间 ID |
| user | **ByteRTCUser*** | 本地用户信息，详见 [ByteRTCUser](macOS-keytype.md#bytertcuser) |
| state | **ByteRTCFirstFrameSendState** | 首帧发送状态，详见 [ByteRTCFirstFrameSendState](macOS-keytype.md#bytertcfirstframesendstate) |


<span id="ByteRTCVideoDelegate-rtcengine-onscreenvideoframesendstatechanged-rtcuser-state"></span>
### rtcEngine:onScreenVideoFrameSendStateChanged:rtcUser:state:
```objectivec

- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onScreenVideoFrameSendStateChanged:(NSString * _Nonnull)roomId rtcUser:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFrameSendState)state;
```
屏幕共享流的视频首帧发送状态发生改变时，收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象。 |
| roomId | **NSString*** | 屏幕流发布用户所在的房间 ID |
| user | **ByteRTCUser*** | 本地用户信息，参看 [ByteRTCUser](macOS-keytype.md#bytertcuser) |
| state | **ByteRTCFirstFrameSendState** | 首帧发送状态，参看 [ByteRTCFirstFrameSendState](macOS-keytype.md#bytertcfirstframesendstate) |


<span id="ByteRTCVideoDelegate-rtcengine-onaudioframeplaystatechanged-rtcuser-state"></span>
### rtcEngine:onAudioFramePlayStateChanged:rtcUser:state:
```objectivec

- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onAudioFramePlayStateChanged:(NSString * _Nonnull)roomId rtcUser:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFramePlayState)state;
```
音频首帧播放状态发生改变时，收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象。 |
| roomId | **NSString*** | 音频流发布用户所在的房间 ID |
| user | **ByteRTCUser*** | 音频流来源的用户信息，参看 [ByteRTCUser](macOS-keytype.md#bytertcuser) |
| state | **ByteRTCFirstFramePlayState** | 首帧播放状态，参看 [ByteRTCFirstFramePlayState](macOS-keytype.md#bytertcfirstframeplaystate) |


<span id="ByteRTCVideoDelegate-rtcengine-onvideoframeplaystatechanged-rtcuser-state"></span>
### rtcEngine:onVideoFramePlayStateChanged:rtcUser:state:
```objectivec

- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onVideoFramePlayStateChanged:(NSString * _Nonnull)roomId rtcUser:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFramePlayState)state;
```
视频首帧播放状态发生改变时，收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象。 |
| user | **ByteRTCUser*** | 视频流来源的用户信息，参看 [ByteRTCUser](macOS-keytype.md#bytertcuser) |
| roomId | **NSString*** | 视频流发布用户所在的房间 ID |
| state | **ByteRTCFirstFramePlayState** | 首帧播放状态，参看 [ByteRTCFirstFramePlayState](macOS-keytype.md#bytertcfirstframeplaystate) |


<span id="ByteRTCVideoDelegate-rtcengine-onscreenvideoframeplaystatechanged-rtcuser-state"></span>
### rtcEngine:onScreenVideoFramePlayStateChanged:rtcUser:state:
```objectivec

- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onScreenVideoFramePlayStateChanged:(NSString * _Nonnull)roomId rtcUser:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFramePlayState)state;
```
屏幕共享流视频首帧播放状态发生改变时，收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象。 |
| roomId | **NSString*** | 屏幕流发布用户所在的房间 ID |
| user | **ByteRTCUser*** | 屏幕共享流来源的用户信息，参看 [ByteRTCUser](macOS-keytype.md#bytertcuser) |
| state | **ByteRTCFirstFramePlayState** | 首帧播放状态，参看 [ByteRTCFirstFramePlayState](macOS-keytype.md#bytertcfirstframeplaystate) |


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
| streamIndex | **ByteRTCStreamIndex** | 音频流属性, 详见 [ByteRTCStreamIndex](macOS-keytype.md#bytertcstreamindex) |


**注意**
如果发布音频流时，未开启本地音频采集，SDK 会推送静音帧，也会收到此回调。

<span id="ByteRTCVideoDelegate-rtcengine-onseimessagereceived-andmessage"></span>
### rtcEngine:onSEIMessageReceived:andMessage:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onSEIMessageReceived:(ByteRTCRemoteStreamKey* _Nonnull)remoteStreamKey andMessage:(NSData* _Nonnull)message;
```
收到通过调用 [sendSEIMessage:andMessage:andRepeatCount:andCountPerFrame:](macOS-api.md#ByteRTCVideo-sendseimessage-andmessage-andrepeatcount-andcountperframe) 发送带有 SEI 消息的视频帧时，收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | 当前 ByteRTCVideo 实例。 |
| remoteStreamKey | **ByteRTCRemoteStreamKey*** | 包含 SEI 发送者的用户名，所在的房间名和媒体流，参看 [ByteRTCRemoteStreamKey](macOS-keytype.md#bytertcremotestreamkey) |
| message | **NSData*** | 收到的 SEI 消息内容 |


<span id="ByteRTCVideoDelegate-rtcengine-onseistreamupdate-eventtype"></span>
### rtcEngine:onSEIStreamUpdate:eventType:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onSEIStreamUpdate:(ByteRTCRemoteStreamKey* _Nonnull)remoteStreamKey eventType:(ByteSEIStreamEventType)eventType;
```
黑帧视频流发布状态回调。  <br>
在语音通话场景下，本地用户调用 [sendSEIMessage:andMessage:andRepeatCount:andCountPerFrame:](macOS-api.md#ByteRTCVideo-sendseimessage-andmessage-andrepeatcount-andcountperframe) 通过黑帧视频流发送 SEI 数据时，流的发送状态会通过该回调通知远端用户。  <br>
你可以通过此回调判断携带 SEI 数据的视频帧为黑帧，从而不对该视频帧进行渲染。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | 当前 ByteRTCVideo 实例。 |
| remoteStreamKey | **ByteRTCRemoteStreamKey*** | 远端流信息，参看 [ByteRTCRemoteStreamKey](macOS-keytype.md#bytertcremotestreamkey)。 |
| eventType | **ByteSEIStreamEventType** | 黑帧视频流状态，参看 [ByteSEIStreamEventType](macOS-keytype.md#byteseistreameventtype) |


<span id="ByteRTCVideoDelegate-rtcengine-onstreamsyncinforeceived-streamtype-data"></span>
### rtcEngine:onStreamSyncInfoReceived:streamType:data:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onStreamSyncInfoReceived:(ByteRTCRemoteStreamKey* _Nonnull)remoteStreamKey streamType:(ByteRTCSyncInfoStreamType)streamType data:(NSData* _Nonnull)data;
```
音频流同步信息回调。可以通过此回调，在远端用户调用 [sendStreamSyncInfo:config:](macOS-api.md#ByteRTCVideo-sendstreamsyncinfo-config) 发送音频流同步消息后，收到远端发送的音频流同步信息。  <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | 当前 ByteRTCVideo 实例。 |
| remoteStreamKey | **ByteRTCRemoteStreamKey*** | 远端流信息，详见 [ByteRTCRemoteStreamKey](macOS-keytype.md#bytertcremotestreamkey) 。 |
| streamType | **ByteRTCSyncInfoStreamType** | 媒体流类型，详见 [ByteRTCSyncInfoStreamType](macOS-keytype.md#bytertcsyncinfostreamtype) 。 |
| data | **NSData*** | 消息内容。 |


<span id="ByteRTCVideoDelegate-rtcengine-onsysstats"></span>
### rtcEngine:onSysStats:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onSysStats:(const ByteRTCSysStats * _Nonnull)stats;
```
报告当前设备 cpu 与 memory 使用率，每 2s 触发一次。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象 |
| stats | **const ByteRTCSysStats*** | cpu 和 memory 使用率信息，详见 [ByteRTCSysStats](macOS-keytype.md#bytertcsysstats) 数据类型 |


<span id="ByteRTCVideoDelegate-rtcengine-onlocalaudiostatechanged-error"></span>
### rtcEngine:onLocalAudioStateChanged:error:
```objectivec

- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onLocalAudioStateChanged:(ByteRTCLocalAudioStreamState)state error:(ByteRTCLocalAudioStreamError)error;
```
> Deprecated  since 3.50 and will be deleted in 3.55. Use [rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:](#ByteRTCVideoDelegate-rtcengine-onaudiodevicestatechanged-device_type-device_state-device_error) instead.

本地音频流的状态发生改变时，收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象 |
| state | **ByteRTCLocalAudioStreamState** | 本地音频设备的当前状态，详见 [ByteRTCLocalAudioStreamState](macOS-keytype.md#bytertclocalaudiostreamstate) |
| error | **ByteRTCLocalAudioStreamError** | 本地音频流状态改变时的错误码，详见 [ByteRTCLocalAudioStreamError](macOS-keytype.md#bytertclocalaudiostreamerror) |


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
| key | **ByteRTCRemoteStreamKey*** | 远端流信息, 详见 [ByteRTCRemoteStreamKey](macOS-keytype.md#bytertcremotestreamkey) |
| state | **ByteRTCRemoteAudioState** | 远端音频流的当前状态，详见 [ByteRTCRemoteAudioState](macOS-keytype.md#bytertcremoteaudiostate) |
| reason | **ByteRTCRemoteAudioStateChangeReason** | 远端音频流状态改变的原因，详见 [ByteRTCRemoteAudioStateChangeReason](macOS-keytype.md#bytertcremoteaudiostatechangereason) |


<span id="ByteRTCVideoDelegate-rtcengine-onlocalvideostatechanged-withstreamstate-withstreamerror"></span>
### rtcEngine:onLocalVideoStateChanged:withStreamState:withStreamError:
```objectivec

- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onLocalVideoStateChanged:(ByteRTCStreamIndex)streamIndex withStreamState:(ByteRTCLocalVideoStreamState)state withStreamError:(ByteRTCLocalVideoStreamError)error;
```
> Deprecated  since 3.50 and will be deleted in 3.55. Use [rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:](#ByteRTCVideoDelegate-rtcengine-onvideodevicestatechanged-device_type-device_state-device_error) instead.

本地视频流的状态发生改变时，收到该事件。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象 |
| streamIndex | **ByteRTCStreamIndex** | 流属性，参看 [ByteRTCStreamIndex](macOS-keytype.md#bytertcstreamindex) |
| state | **ByteRTCLocalVideoStreamState** | 本地视频流的当前状态，参看 [ByteRTCLocalVideoStreamState](macOS-keytype.md#bytertclocalvideostreamstate) |
| error | **ByteRTCLocalVideoStreamError** | 本地视频状态改变时的错误码，参看 [ByteRTCLocalVideoStreamError](macOS-keytype.md#bytertclocalvideostreamerror) |


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
| streamKey | **ByteRTCRemoteStreamKey*** | 远端视频流信息，房间、用户 ID、流属性等，参看 [ByteRTCRemoteStreamKey](macOS-keytype.md#bytertcremotestreamkey) |
| state | **ByteRTCRemoteVideoState** | 远端视频流的当前状态，参看 [ByteRTCRemoteVideoState](macOS-keytype.md#bytertcremotevideostate) |
| reason | **ByteRTCRemoteVideoStateChangeReason** | 远端视频流状态改变的原因，参看 [ByteRTCRemoteVideoStateChangeReason](macOS-keytype.md#bytertcremotevideostatechangereason) |


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
| errorCode | **ByteRTCLoginErrorCode** | 登录结果  <br/>详见 [ByteRTCLoginErrorCode](macOS-errorcode.md#bytertcloginerrorcode)。 |
| elapsed | **NSInteger** | 从调用 [login:uid:](macOS-api.md#ByteRTCVideo-login-uid) 接口开始到返回结果所用时长。  <br/>单位为 ms。 |


**注意**
调用 [login:uid:](macOS-api.md#ByteRTCVideo-login-uid) 后，会收到此回调。

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
调用 [logout](macOS-api.md#ByteRTCVideo-logout) 后，会收到此回调。

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
| errorCode | **NSInteger** | 设置结果  <br/>• 返回 200，设置成功  <br/>• 返回其他，设置失败，详见 [ByteRTCUserMessageSendResult](macOS-errorcode.md#bytertcusermessagesendresult) |


**注意**
调用 [setServerParams:url:](macOS-api.md#ByteRTCVideo-setserverparams-url) 后，会收到此回调。

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
| status | **ByteRTCUserOnlineStatus** | 查询的用户登录状态  <br/>详见 [ByteRTCUserOnlineStatus](macOS-keytype.md#bytertcuseronlinestatus). |


**注意**
必须先调用 [getPeerOnlineStatus:](macOS-api.md#ByteRTCVideo-getpeeronlinestatus)，才能收到此回调。

<span id="ByteRTCVideoDelegate-rtcengine-onusermessagereceivedoutsideroom-message"></span>
### rtcEngine:onUserMessageReceivedOutsideRoom:message:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onUserMessageReceivedOutsideRoom:(NSString * _Nonnull)uid message:(NSString * _Nonnull)message;
```
收到房间外用户调用 [sendUserMessageOutsideRoom:message:config:](macOS-api.md#ByteRTCVideo-sendusermessageoutsideroom-message-config) 发来的文本消息时，会收到此回调

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
收到房间外用户调用 [sendUserBinaryMessageOutsideRoom:message:config:](macOS-api.md#ByteRTCVideo-senduserbinarymessageoutsideroom-message-config) 发来的二进制消息时，会收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象 |
| uid | **NSString*** | 消息发送者 ID |
| message | **NSData*** | 收到的二进制消息内容 |


<span id="ByteRTCVideoDelegate-rtcengine-onusermessagesendresultoutsideroom-error"></span>
### rtcEngine:onUserMessageSendResultOutsideRoom:error:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onUserMessageSendResultOutsideRoom:(NSInteger)msgid error:(ByteRTCUserMessageSendResult)error;
```
给房间外指定的用户发送消息的回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象 |
| msgid | **NSInteger** | 本条消息的 ID  <br/>所有的 P2P 和 P2Server 消息共用一个 ID 序列。 |
| error | **ByteRTCUserMessageSendResult** | 消息发送结果  <br/>详见 [ByteRTCUserMessageSendResult](macOS-errorcode.md#bytertcusermessagesendresult)。 |


**注意**
当调用 [sendUserMessageOutsideRoom:message:config:](macOS-api.md#ByteRTCVideo-sendusermessageoutsideroom-message-config) 或 [sendUserBinaryMessageOutsideRoom:message:config:](macOS-api.md#ByteRTCVideo-senduserbinarymessageoutsideroom-message-config) 发送消息后，会收到此回调。

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
| error | **ByteRTCUserMessageSendResult** | 消息发送结果。详见 [ByteRTCUserMessageSendResult](macOS-errorcode.md#bytertcusermessagesendresult)。 |
| message | **NSData*** | 应用服务器收到 HTTP 请求后，在 ACK 中返回的信息。消息不超过 64 KB。 |


**注意**
本回调为异步回调。当调用 [sendServerMessage:](macOS-api.md#ByteRTCVideo-sendservermessage) 或 [sendServerBinaryMessage:](macOS-api.md#ByteRTCVideo-sendserverbinarymessage) 接口发送消息后，会收到此回调。

<span id="ByteRTCVideoDelegate-rtcengine-onnetworkdetectionresult-quality-rtt-lostrate-bitrate-jitter"></span>
### rtcEngine:onNetworkDetectionResult:quality:rtt:lostRate:bitrate:jitter:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onNetworkDetectionResult:(ByteRTCNetworkDetectionLinkType)type quality:(ByteRTCNetworkQuality)quality rtt:(int)rtt lostRate:(double)lost_rate bitrate:(int)bitrate jitter:(int)jitter;
```
通话前网络探测结果的回调。  <br>
成功调用 [startNetworkDetection:uplinkBandwidth:downlink:downlinkBandwidth:](macOS-api.md#ByteRTCVideo-startnetworkdetection-uplinkbandwidth-downlink-downlinkbandwidth) 接口开始探测后，会在 3s 内首次收到该回调，之后每 2s 收到一次该回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象 |
| type | **ByteRTCNetworkDetectionLinkType** | 探测网络类型为上行/下行 |
| quality | **ByteRTCNetworkQuality** | 探测网络的质量，参看 [ByteRTCNetworkQuality](macOS-keytype.md#bytertcnetworkquality)。 |
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
以下情况将停止探测并收到一次本回调：<br>
1. 当调用 [stopNetworkDetection](macOS-api.md#ByteRTCVideo-stopnetworkdetection) 接口停止探测后，会收到一次该回调；
2. 当收到远端/本端音频首帧后，停止探测；
3. 当探测超过3分钟后，停止探测；
4. 当探测链路断开一定时间之后，停止探测。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象 |
| err_code | **ByteRTCNetworkDetectionStopReason** | 停止探测的原因类型,参考 [ByteRTCNetworkDetectionStopReason](macOS-keytype.md#bytertcnetworkdetectionstopreason) |


<span id="ByteRTCVideoDelegate-rtcengine-log"></span>
### rtcEngine:log:
```objectivec

- (void)rtcEngine:(ByteRTCVideo* _Nonnull)engine log:(NSDictionary* _Nonnull)dict;
```
> Deprecated  since 3.45 and will be deleted in 3.51.

SDK 内部日志回调。  <br>
SDK 内部运行时，会把日志回调给业务方，方便排查问题。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象。 |
| dict | **NSDictionary*** | 日志内容。 |


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
| mixId | **NSInteger** | 混音 ID  <br/>使用 [ByteRTCAudioMixingManager](macOS-api.md#bytertcaudiomixingmanager) 相关接口时传入的唯一 ID。 |
| state | **ByteRTCAudioMixingState** | 混音状态  <br/>其混音状态可参考：[ByteRTCAudioMixingState](macOS-keytype.md#bytertcaudiomixingstate)。 |
| error | **ByteRTCAudioMixingError** | 错误码  <br/>详见 [ByteRTCAudioMixingError](macOS-keytype.md#bytertcaudiomixingerror)。 |


**注意**
此回调会被触发的时机汇总如下：  

+ 当调用 [startAudioMixing:filePath:config:](macOS-api.md#ByteRTCAudioMixingManager-startaudiomixing-filepath-config) 方法成功后，会触发 state 值为 ByteRTCAudioMixingStatePlaying 回调；否则触发 state 值为 ByteRTCAudioMixingStateFailed 的回调。  
+ 当使用相同的 ID 重复调用 [startAudioMixing:filePath:config:](macOS-api.md#ByteRTCAudioMixingManager-startaudiomixing-filepath-config) 后，后一次会覆盖前一次，且本回调会以 ByteRTCAudioMixingStateStopped 通知前一次混音已停止。  
+ 当调用 [pauseAudioMixing:](macOS-api.md#ByteRTCAudioMixingManager-pauseaudiomixing) 方法暂停播放成功后，会触发 state 值为 ByteRTCAudioMixingStatePaused 回调；否则触发 state 值为 ByteRTCAudioMixingStateFailed 的回调。  
+ 当调用 [resumeAudioMixing:](macOS-api.md#ByteRTCAudioMixingManager-resumeaudiomixing) 方法恢复播放成功后，会触发 state 值为 ByteRTCAudioMixingStatePlaying 回调；否则触发 state 值为 ByteRTCAudioMixingStateFailed 的回调。  
+ 当调用 [stopAudioMixing:](macOS-api.md#ByteRTCAudioMixingManager-stopaudiomixing) 方法停止播放成功后，会触发 state 值为 ByteRTCAudioMixingStateStopped 回调；否则触发 state 值为 ByteRTCAudioMixingStateFailed 的回调。  
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
调用 [setAudioMixingProgressInterval:interval:](macOS-api#ByteRTCAudioMixingManager-setaudiomixingprogressinterval-interval) 将时间间隔设为大于 0 的值后，或调用 [startAudioMixing:filePath:config:](macOS-api#ByteRTCAudioMixingManager-startaudiomixing-filepath-config) 将 [ByteRTCAudioMixingConfig](macOS-keytype.md#bytertcaudiomixingconfig) 中的时间间隔设为大于 0 的值后，SDK 会按照设置的时间间隔回调该事件。 

<span id="ByteRTCVideoDelegate-rtcengine-onperformancealarms-roomid-reason-sourcewanteddata"></span>
### rtcEngine:onPerformanceAlarms:roomId:reason:sourceWantedData:
```objectivec

- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onPerformanceAlarms:(ByteRTCPerformanceAlarmMode)mode roomId:(NSString *_Nonnull)roomId reason:(ByteRTCPerformanceAlarmReason)reason sourceWantedData:(ByteRTCSourceWantedData *_Nonnull)data;
```
本地未开启发布性能回退，检测到设备性能不足时，收到此回调。  <br>
本地开启发布性能回退，因设备性能/网络原因，造成发布性能回退/恢复时，收到此回调。  <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mode | **ByteRTCPerformanceAlarmMode** | 指示本地是否开启发布回退功能。参看 [ByteRTCPerformanceAlarmMode](macOS-keytype.md#bytertcperformancealarmmode)  <br/>• 当发布端未开启发布性能回退时，mode 值为 ByteRTCPerformanceAlarmModeNormal。  <br/>• 当发布端开启发布性能回退时，mode 值为 ByteRTCPerformanceAlarmModeSimulcast。 |
| roomId | **NSString*** | • 未开启发布性能回退时，roomId 为空  <br/>• 开启发布性能回退时，roomId 是告警影响的房间 ID。 |
| reason | **ByteRTCPerformanceAlarmReason** | 告警原因，参看 [ByteRTCPerformanceAlarmReason](macOS-keytype.md#bytertcperformancealarmreason) |
| data | **ByteRTCSourceWantedData*** | 性能回退相关数据，详见 [ByteRTCSourceWantedData](macOS-keytype.md#bytertcsourcewanteddata)。 |


<span id="ByteRTCVideoDelegate-rtcengine-onsimulcastsubscribefallback"></span>
### rtcEngine:onSimulcastSubscribeFallback:
```objectivec

- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onSimulcastSubscribeFallback:(ByteRTCRemoteStreamSwitchEvent *_Nonnull)event;
```
音视频流因网络环境变化等原因发生回退，或从回退中恢复时，触发该回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | 当前 ByteRTCVideo 实例 |
| event | **ByteRTCRemoteStreamSwitchEvent*** | 流切换信息。详见 [ByteRTCRemoteStreamSwitchEvent](macOS-keytype.md#bytertcremotestreamswitchevent)。 |


<span id="ByteRTCVideoDelegate-rtcengine-onexternalscreenframeupdate"></span>
### rtcEngine:onExternalScreenFrameUpdate:
```objectivec

- (void)rtcEngine: (ByteRTCVideo* _Nonnull)engine onExternalScreenFrameUpdate: (ByteRTCFrameUpdateInfo* _Nullable)frameUpdateInfo;
```
外部采集时，调用 [setOriginalScreenVideoInfo:withOriginalCaptureHeight:](macOS-api.md#ByteRTCVideo-setoriginalscreenvideoinfo-withoriginalcaptureheight) 设置屏幕或窗口大小改变前的分辨率后，若屏幕采集模式为智能模式，你将收到此回调，根据 RTC 智能决策合适的帧率和分辨率积（宽*高）重新采集。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| frameUpdateInfo | **ByteRTCFrameUpdateInfo*** | RTC 智能决策后合适的帧率和分辨率积（宽*高）。参看 [ByteRTCFrameUpdateInfo](macOS-keytype.md#bytertcframeupdateinfo)。 |


<span id="ByteRTCVideoDelegate-rtcengine-onhttpproxystate"></span>
### rtcEngine:onHttpProxyState:
```objectivec

- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onHttpProxyState:(NSInteger)state;
```
> Deprecated  在3.52及之后废弃，将在3.57删除，使用 [rtcEngine:onLocalProxyStateChanged:withProxyState:withProxyError:](#ByteRTCVideoDelegate-rtcengine-onlocalproxystatechanged-withproxystate-withproxyerror) 替换

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
> Deprecated  在3.52及之后废弃，将在3.57删除，使用 [rtcEngine:onLocalProxyStateChanged:withProxyState:withProxyError:](#ByteRTCVideoDelegate-rtcengine-onlocalproxystatechanged-withproxystate-withproxyerror) 替换

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
> Deprecated  在3.52及之后废弃，将在3.57删除，使用 [rtcEngine:onLocalProxyStateChanged:withProxyState:withProxyError:](#ByteRTCVideoDelegate-rtcengine-onlocalproxystatechanged-withproxystate-withproxyerror) 替换

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
该回调由 [startFileRecording:withRecordingConfig:type:](macOS-api.md#ByteRTCVideo-startfilerecording-withrecordingconfig-type) 或 [stopFileRecording:](macOS-api.md#ByteRTCVideo-stopfilerecording) 触发。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象 |
| type | **ByteRTCStreamIndex** | 录制流的流属性，参看 [ByteRTCStreamIndex](macOS-keytype.md#bytertcstreamindex) |
| state | **ByteRTCRecordingState** | 录制状态，参看 [ByteRTCRecordingState](macOS-keytype.md#bytertcrecordingstate) |
| error_code | **ByteRTCRecordingErrorCode** | 录制错误码，参看 [ByteRTCRecordingErrorCode](macOS-keytype.md#bytertcrecordingerrorcode) |
| recording_info | **ByteRTCRecordingInfo*** | 录制文件的详细信息，参看 [ByteRTCRecordingInfo](macOS-keytype.md#bytertcrecordinginfo) |


<span id="ByteRTCVideoDelegate-rtcengine-onrecordingprogressupdate-process-recording_info"></span>
### rtcEngine:onRecordingProgressUpdate:process:recording_info:
```objectivec

- (void)rtcEngine:(ByteRTCVideo* _Nonnull)engine onRecordingProgressUpdate:(ByteRTCStreamIndex)type process:(ByteRTCRecordingProgress* _Nonnull)process recording_info:(ByteRTCRecordingInfo* _Nonnull)recording_info;
```
本地录制进度回调。  <br>
该回调由 [startFileRecording:withRecordingConfig:type:](macOS-api.md#ByteRTCVideo-startfilerecording-withrecordingconfig-type) 触发，录制状态正常时，系统每秒钟都会通过该回调提示录制进度。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象 |
| type | **ByteRTCStreamIndex** | 录制流的流属性，参看 [ByteRTCStreamIndex](macOS-keytype.md#bytertcstreamindex) |
| process | **ByteRTCRecordingProgress*** | 录制进度，参看 [ByteRTCRecordingProgress](macOS-keytype.md#bytertcrecordingprogress) |
| recording_info | **ByteRTCRecordingInfo*** | 录制文件的详细信息，参看 [ByteRTCRecordingInfo](macOS-keytype.md#bytertcrecordinginfo) |


<span id="ByteRTCVideoDelegate-rtcengine-onaudiorecordingstateupdate-error_code"></span>
### rtcEngine:onAudioRecordingStateUpdate:error_code:
```objectivec

- (void)rtcEngine:(ByteRTCVideo* _Nonnull)engine onAudioRecordingStateUpdate:(ByteRTCAudioRecordingState)state error_code:(ByteRTCAudioRecordingErrorCode)error_code;
```
调用 [startAudioRecording:](macOS-api.md#ByteRTCVideo-startaudiorecording) 或者 [stopAudioRecording](macOS-api.md#ByteRTCVideo-stopaudiorecording) 改变音频文件录制状态时，收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| state | **ByteRTCAudioRecordingState** | 录制状态，参看 [ByteRTCAudioRecordingState](macOS-keytype.md#bytertcaudiorecordingstate) |
| error_code | **ByteRTCAudioRecordingErrorCode** | 录制错误码，参看 [ByteRTCAudioRecordingErrorCode](macOS-errorcode.md#bytertcaudiorecordingerrorcode) |


<span id="ByteRTCVideoDelegate-rtcengine-onpushpublicstreamresult-publicstreamid-errorcode"></span>
### rtcEngine:onPushPublicStreamResult:publicStreamId:errorCode:
```objectivec

- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onPushPublicStreamResult:(NSString *_Nonnull)roomId publicStreamId:(NSString *_Nonnull)streamId errorCode:(ByteRTCPublicStreamErrorCode)errorCode;
```
公共流发布结果回调。<br>
调用 [startPushPublicStream:withLayout:](macOS-api.md#ByteRTCVideo-startpushpublicstream-withlayout) <br>
接口或直接在服务端启动推公共流功能后，你会通过此回调收到启动结果和推流过程中的错误。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | engine 实例 |
| roomId | **NSString*** | 发布公共流的房间 ID |
| streamId | **NSString*** | 公共流ID。 |
| errorCode | **ByteRTCPublicStreamErrorCode** | 公共流发布结果状态码。 详见 [ByteRTCPublicStreamErrorCode](macOS-errorcode.md#bytertcpublicstreamerrorcode)。 |


<span id="ByteRTCVideoDelegate-rtcengine-onplaypublicstreamresult-errorcode"></span>
### rtcEngine:onPlayPublicStreamResult:errorCode:
```objectivec

- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onPlayPublicStreamResult:(NSString *_Nonnull)publicStreamId errorCode:(ByteRTCPublicStreamErrorCode)errorCode;
```
订阅公共流的结果回调  <br>
调用 [startPlayPublicStream:](macOS-api.md#ByteRTCVideo-startplaypublicstream) 接口拉公共流后，你会通过此回调收到启动结果和拉流过程中的错误。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | engine 实例 |
| publicStreamId | **NSString*** | 公共流ID。 |
| errorCode | **ByteRTCPublicStreamErrorCode** | 公共流订阅结果状态码。 详见 [ByteRTCPublicStreamErrorCode](macOS-errorcode.md#bytertcpublicstreamerrorcode)。 |


<span id="ByteRTCVideoDelegate-rtcengine-onpublicstreamseimessagereceived-andmessage-andsourcetype"></span>
### rtcEngine:onPublicStreamSEIMessageReceived:andMessage:andSourceType:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onPublicStreamSEIMessageReceived:(NSString* _Nonnull)publicStreamId andMessage:(NSData* _Nonnull)message andSourceType:(ByteRTCDataMessageSourceType)sourceType;
```
回调公共流中包含的 SEI 信息。
调用 [startPlayPublicStream:](macOS-api.md#ByteRTCVideo-startplaypublicstream) 接口启动拉公共流功能后，通过此回调收到公共流中的 SEI 消息。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 实例。 |
| publicStreamId | **NSString*** | 公共流 ID。 |
| message | **NSData*** | 收到的 SEI 消息内容。<br/>本回调可以获取通过调用客户端 [sendSEIMessage:andMessage:andRepeatCount:andCountPerFrame:](macOS-api.md#ByteRTCVideo-sendseimessage-andmessage-andrepeatcount-andcountperframe) 插入的 SEI 信息。<br/>当公共流中的多路视频流均包含有 SEI 信息：SEI 不互相冲突时，将通过多次回调分别发送；SEI 在同一帧有冲突时，则只有一条流中的 SEI 信息被透传并融合到公共流中。 |
| sourceType | **ByteRTCDataMessageSourceType** | SEI 消息类型，自 3.52.1 版本后固定为 `0`，自定义消息。参看 [ByteRTCDataMessageSourceType](macOS-keytype.md#bytertcdatamessagesourcetype)。 |


**注意**
通过 Open API 插入的 SEI 信息，应通过回调 [rtcEngine:onPublicStreamDataMessageReceived:andMessage:andSourceType:](#ByteRTCVideoDelegate-rtcengine-onpublicstreamdatamessagereceived-andmessage-andsourcetype) 获取。

<span id="ByteRTCVideoDelegate-rtcengine-onpublicstreamdatamessagereceived-andmessage-andsourcetype"></span>
### rtcEngine:onPublicStreamDataMessageReceived:andMessage:andSourceType:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onPublicStreamDataMessageReceived:(NSString* _Nonnull)publicStreamId andMessage:(NSData* _Nonnull)message andSourceType:(ByteRTCDataMessageSourceType)sourceType;
```
> Available since 3.52

回调公共流中包含的数据信息。<br>
通过 [startPlayPublicStream:](macOS-api.md#ByteRTCVideo-startplaypublicstream) 开始播放公共流后，可以通过本回调获取发送端发送的非SEI消息。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 实例。 |
| publicStreamId | **NSString*** | 公共流 ID |
| message | **NSData*** | 收到的数据消息内容，如下：<br/>• 调用公共流 OpenAPI 发送的 SEI 消息。当公共流中的多路视频流均包含有 SEI 信息：SEI 不互相冲突时，将通过多次回调分别发送；SEI 在同一帧有冲突时，则只有一条流中的 SEI 信息被透传并融合到公共流中。<br/>• 媒体流音量变化，需要通过公共流 OpenAPI 开启回调。 |
| sourceType | **ByteRTCDataMessageSourceType** | 数据消息来源，参看 [ByteRTCDataMessageSourceType](macOS-keytype.md#bytertcdatamessagesourcetype)。 |


**注意**
通过调用客户端 API 插入的 SEI 信息，应通过回调 [rtcEngine:onPublicStreamSEIMessageReceived:andMessage:andSourceType:](#ByteRTCVideoDelegate-rtcengine-onpublicstreamseimessagereceived-andmessage-andsourcetype) 获取。

<span id="ByteRTCVideoDelegate-rtcengine-onfirstpublicstreamvideoframedecoded-withframeinfo"></span>
### rtcEngine:onFirstPublicStreamVideoFrameDecoded:withFrameInfo:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onFirstPublicStreamVideoFrameDecoded:(NSString * _Nonnull)publicStreamId withFrameInfo:(ByteRTCVideoFrameInfo * _Nonnull)frameInfo;
```
公共流的首帧视频解码成功<br>
关于订阅公共流，详见 [startPlayPublicStream:](macOS-api.md#ByteRTCVideo-startplaypublicstream)。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | ByteRTCVideo 对象 |
| publicStreamId | **NSString*** | 公共流 ID |
| frameInfo | **ByteRTCVideoFrameInfo*** | 视频帧信息，参看 [ByteRTCVideoFrameInfo](macOS-keytype.md#bytertcvideoframeinfo) |


<span id="ByteRTCVideoDelegate-rtcengine-onfirstpublicstreamaudioframe"></span>
### rtcEngine:onFirstPublicStreamAudioFrame:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onFirstPublicStreamAudioFrame:(NSString * _Nonnull)publicStreamId;
```
公共流的音频首帧解码成功<br>
关于订阅公共流，详见 [startPlayPublicStream:](macOS-api.md#ByteRTCVideo-startplaypublicstream)。

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
调用 [startCloudProxy:](macOS-api.md#ByteRTCVideo-startcloudproxy) 开启云代理，SDK 首次成功连接云代理服务器时，回调此事件。

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
| result | **ByteRTCEchoTestResult** | 测试结果，参看 [ByteRTCEchoTestResult](macOS-keytype.md#bytertcechotestresult)。 |


**注意**
该回调触发的时机包括： + 检测过程中采集设备发生错误时；  

+ 检测成功后；  
+ 非设备原因导致检测过程中未接收到音/视频回放，停止检测后。


<span id="ByteRTCVideoDelegate-rtcengineonnetworktimesynchronized"></span>
### rtcEngineOnNetworkTimeSynchronized:
```objectivec

- (void)rtcEngineOnNetworkTimeSynchronized:(ByteRTCVideo *_Nonnull)engine;
```
首次调用 [getNetworkTimeInfo](macOS-api.md#ByteRTCVideo-getnetworktimeinfo) 后，SDK 内部启动网络时间同步，同步完成时会触发此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | [ByteRTCVideo](macOS-api.md#bytertcvideo) 对象 |


<span id="ByteRTCVideoDelegate-rtcengine-onlicensewillexpire"></span>
### rtcEngine:onLicenseWillExpire:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onLicenseWillExpire:(NSInteger)days;
```
license过期时间提醒

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **ByteRTCVideo*** | [ByteRTCVideo](macOS-api.md#bytertcvideo) 对象 |
| days | **NSInteger** | 过期时间天数 |


<span id="ByteRTCVideoDelegate-rtcengine-onhardwareechodetectionresult"></span>
### rtcEngine:onHardwareEchoDetectionResult:
```objectivec

- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onHardwareEchoDetectionResult:(ByteRTCHardwareEchoDetectionResult)result;
```
通话前回声检测结果回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| result | **ByteRTCHardwareEchoDetectionResult** | 参见 [ByteRTCHardwareEchoDetectionResult](macOS-keytype.md#bytertchardwareechodetectionresult)。 |


**注意**

+ 通话前调用 [startHardwareEchoDetection:](macOS-api.md#ByteRTCVideo-starthardwareechodetection) 后，将触发本回调返回检测结果。
+ 建议在收到检测结果后，调用 [stopHardwareEchoDetection](macOS-api.md#ByteRTCVideo-stophardwareechodetection) 停止检测，释放对音频设备的占用。
+ 如果 SDK 在通话中检测到回声，将通过 [rtcEngine:onAudioDeviceWarning:deviceType:deviceWarning:](#ByteRTCVideoDelegate-rtcengine-onaudiodevicewarning-devicetype-devicewarning) 回调 `kMediaDeviceWarningLeakEchoDetected`。


<span id="ByteRTCVideoDelegate-rtcengine-onlocalproxystatechanged-withproxystate-withproxyerror"></span>
### rtcEngine:onLocalProxyStateChanged:withProxyState:withProxyError:
```objectivec

- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onLocalProxyStateChanged:(ByteRTCLocalProxyType)type withProxyState:(ByteRTCLocalProxyState)state withProxyError:(ByteRTCLocalProxyError)error;
```
本地代理状态发生改变回调。调用 [setLocalProxy:](macOS-api.md#ByteRTCVideo-setlocalproxy) 设置本地代理后，SDK 会触发此回调，返回代理连接的状态。  <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| type | **ByteRTCLocalProxyType** | 本地代理类型。参看 [ByteRTCLocalProxyType](macOS-keytype.md#bytertclocalproxytype) 。 |
| state | **ByteRTCLocalProxyState** | 本地代理状态。参看 [ByteRTCLocalProxyState](macOS-keytype.md#bytertclocalproxystate)。 |
| error | **ByteRTCLocalProxyError** | 本地代理错误。参看 [ByteRTCLocalProxyError](macOS-keytype.md#bytertclocalproxyerror)。 |


# ByteRTCAudioFrameObserver
```objectivec
@protocol ByteRTCAudioFrameObserver <NSObject>
```

音频数据回调观察者
注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。
本接口类中的回调周期均为 20 ms。


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
| audioFrame | **ByteRTCAudioFrame*** | 音频数据, 详见： [ByteRTCAudioFrame](macOS-keytype.md#bytertcaudioframe) |


<span id="ByteRTCAudioFrameObserver-onplaybackaudioframe"></span>
### onPlaybackAudioFrame:
```objectivec

- (void)onPlaybackAudioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;
```
返回订阅的所有远端用户混音后的音频数据。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioFrame | **ByteRTCAudioFrame*** | 音频数据, 详见： [ByteRTCAudioFrame](macOS-keytype.md#bytertcaudioframe) |


<span id="ByteRTCAudioFrameObserver-onremoteuseraudioframe-audioframe"></span>
### onRemoteUserAudioFrame:audioFrame:
```objectivec

- (void)onRemoteUserAudioFrame:(ByteRTCRemoteStreamKey * _Nonnull)streamKey audioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;
```
返回远端单个用户的音频数据

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamKey | **ByteRTCRemoteStreamKey*** | 远端流信息，参看 [ByteRTCRemoteStreamKey](macOS-keytype.md#bytertcremotestreamkey)。 |
| audioFrame | **ByteRTCAudioFrame*** | 音频数据，参看 [ByteRTCAudioFrame](macOS-keytype.md#bytertcaudioframe)。 |


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
| audioFrame | **ByteRTCAudioFrame*** | 音频数据, 详见： [ByteRTCAudioFrame](macOS-keytype.md#bytertcaudioframe) |


# ByteRTCAudioProcessor
```objectivec
@protocol ByteRTCAudioProcessor <NSObject>
```

自定义音频处理器
注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **int** | [processAudioFrame:](#ByteRTCAudioProcessor-processaudioframe) |


## 函数说明
<span id="ByteRTCAudioProcessor-processaudioframe"></span>
### processAudioFrame:
```objectivec

- (int)processAudioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;
```
获取 RTC SDK 采集得到的音频帧，并进行自定义处理，最终将处理后的音频帧给到 RTC SDK 用于编码传输。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioFrame | **ByteRTCAudioFrame*** | RTC SDK 采集到的音频帧，自定义处理可直接对音频 buffer 中的数据进行修改。参看 [ByteRTCAudioFrame](macOS-keytype.md#bytertcaudioframe)。 |

**返回值**

0: 未处理  
\>0: 处理成功  
< 0: 处理失败


**注意**
在进行音频自定义处理前，你需要调用 `registerLocalAudioProcessor` 设置音频自定义处理器。

# ByteRTCAudioFrameProcessor
```objectivec
@protocol ByteRTCAudioFrameProcessor <NSObject>
```

自定义音频处理器
注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **int** | [onProcessRecordAudioFrame:](#ByteRTCAudioFrameProcessor-onprocessrecordaudioframe) |
| **int** | [onProcessPlayBackAudioFrame:](#ByteRTCAudioFrameProcessor-onprocessplaybackaudioframe) |
| **int** | [onProcessRemoteUserAudioFrame:audioFrame:](#ByteRTCAudioFrameProcessor-onprocessremoteuseraudioframe-audioframe) |
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
| audioFrame | **ByteRTCAudioFrame*** | 音频帧地址，参看 [ByteRTCAudioFrame](macOS-keytype.md#bytertcaudioframe)。 |

**返回值**

+ 0： 成功。  
+ < 0： 失败。  


**注意**

+ 完成自定义音频处理后，SDK 会对处理后的音频帧进行编码，并传输到远端。此音频处理不会影响软件耳返音频数据。
+ 要启用此回调，必须调用 `enableAudioProcessor`，并在参数中选择本地采集的音频，每 10 ms 收到此回调。


<span id="ByteRTCAudioFrameProcessor-onprocessplaybackaudioframe"></span>
### onProcessPlayBackAudioFrame:
```objectivec

- (int)onProcessPlayBackAudioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;
```
回调远端音频混音的音频帧地址，供自定义音频处理。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioFrame | **ByteRTCAudioFrame*** | 音频帧地址，参看 [ByteRTCAudioFrame](macOS-keytype.md#bytertcaudioframe) |


**注意**
调用 `enableAudioProcessor`,并在参数中选择远端音频流的的混音音频时，每 10 ms 收到此回调。

<span id="ByteRTCAudioFrameProcessor-onprocessremoteuseraudioframe-audioframe"></span>
### onProcessRemoteUserAudioFrame:audioFrame:
```objectivec

- (int)onProcessRemoteUserAudioFrame:(ByteRTCRemoteStreamKey * _Nonnull)stream_info audioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;
```
回调单个远端用户的音频帧地址，供自定义音频处理。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stream_info | **ByteRTCRemoteStreamKey*** | 音频流信息，参看 [ByteRTCRemoteStreamKey](macOS-keytype.md#bytertcremotestreamkey) |
| audioFrame | **ByteRTCAudioFrame*** | 音频帧地址，参看 [ByteRTCAudioFrame](macOS-keytype.md#bytertcaudioframe) |


**注意**
调用 `enableAudioProcessor`,并在参数中选择各个远端音频流时，每 10 ms 收到此回调。

<span id="ByteRTCAudioFrameProcessor-onprocessscreenaudioframe"></span>
### onProcessScreenAudioFrame:
```objectivec

- (int)onProcessScreenAudioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;
```
回调屏幕共享的音频帧地址，供自定义音频处理。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioFrame | **ByteRTCAudioFrame*** | 音频帧地址，参看 [ByteRTCAudioFrame](macOS-keytype.md#bytertcaudioframe)。 |


**注意**
调用 `enableAudioProcessor:`，把返回给音频处理器的音频类型设置为屏幕共享音频后，每 10 ms 收到此回调。

# ByteRTCAudioFileFrameObserver
```objectivec
@protocol ByteRTCAudioFileFrameObserver <NSObject>
```

本地音频文件混音的音频帧观察者。
注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **void** | [onAudioFileFrame:audioFrame:](#ByteRTCAudioFileFrameObserver-onaudiofileframe-audioframe) |


## 函数说明
<span id="ByteRTCAudioFileFrameObserver-onaudiofileframe-audioframe"></span>
### onAudioFileFrame:audioFrame:
```objectivec

- (void)onAudioFileFrame:(int)mix_id audioFrame:(ByteRTCAudioFrame * _Nonnull)audio_frame;
```
当本地音频文件混音时，回调播放的音频帧。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mix_id | **int** | 混音 ID。 |
| audio_frame | **ByteRTCAudioFrame*** | 参看 [ByteRTCAudioFrame](macOS-keytype.md#bytertcaudioframe)。 |


# ByteRTCEncryptHandler
```objectivec
@protocol ByteRTCEncryptHandler <NSObject>
```

自定义加密接口
注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **NSData*** | [onEncryptData:](#ByteRTCEncryptHandler-onencryptdata) |
| **NSData*** | [onDecryptData:](#ByteRTCEncryptHandler-ondecryptdata) |


## 函数说明
<span id="ByteRTCEncryptHandler-onencryptdata"></span>
### onEncryptData:
```objectivec

- (NSData * _Nonnull) onEncryptData:(NSData * _Nonnull)rawData;
```
自定义加密。  <br>
使用设定的自定义加密方式，对编码后传输前的音视频帧数据进行加密。<br>
暂不支持对原始音视频帧进行加密。

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
+ 使用 [onDecryptData:](#ByteRTCEncryptHandler-ondecryptdata) 对已加密的音视频帧数据进行解密。
+ 返回的数据大小应控制在原始数据的 90% ~ 120% 范围以内，不然将被丢弃。


<span id="ByteRTCEncryptHandler-ondecryptdata"></span>
### onDecryptData:
```objectivec

- (NSData * _Nonnull) onDecryptData:(NSData * _Nonnull)rawData;
```
自定义解密。  <br>
对自定义加密后的音视频帧数据进行解密。关于自定义加密，参看 [onEncryptData:](#ByteRTCEncryptHandler-onencryptdata)。

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


# ByteRtcScreenCapturerExtDelegate
```objectivec
@protocol ByteRtcScreenCapturerExtDelegate <NSObject>
```

屏幕采集相关扩展协议，仅适用于 SDK 内部采集。  <br>
用户创建 extension 后生成的 SampleHandler 需继承此协议以实现屏幕共享相关能力。
注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **void** | [onQuitFromApp](#ByteRtcScreenCapturerExtDelegate-onquitfromapp) |
| **void** | [onReceiveMessageFromApp:](#ByteRtcScreenCapturerExtDelegate-onreceivemessagefromapp) |
| **void** | [onSocketDisconnect](#ByteRtcScreenCapturerExtDelegate-onsocketdisconnect) |
| **void** | [onSocketConnect](#ByteRtcScreenCapturerExtDelegate-onsocketconnect) |
| **void** | [onNotifyAppRunning](#ByteRtcScreenCapturerExtDelegate-onnotifyapprunning) |


## 函数说明
<span id="ByteRtcScreenCapturerExtDelegate-onquitfromapp"></span>
### onQuitFromApp
```objectivec

- (void)onQuitFromApp;
```
通知 Broadcast Upload Extension 停止采集屏幕并退出。


**注意**
用户调用 [stopScreenCapture](#stopscreencapture) 后，会触发该方法通知 extension 端的 SDK 停止屏幕采集。

<span id="ByteRtcScreenCapturerExtDelegate-onreceivemessagefromapp"></span>
### onReceiveMessageFromApp:
```objectivec

- (void)onReceiveMessageFromApp:(NSData *)message;
```
Socket 收到 App 侧发来的信息时，触发该回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| message | **NSData*** | App 侧发送的消息 |


<span id="ByteRtcScreenCapturerExtDelegate-onsocketdisconnect"></span>
### onSocketDisconnect
```objectivec

- (void)onSocketDisconnect;
```
Socket 连接断开时触发此回调


<span id="ByteRtcScreenCapturerExtDelegate-onsocketconnect"></span>
### onSocketConnect
```objectivec

- (void)onSocketConnect;
```
Socket 连接成功时触发此回调


<span id="ByteRtcScreenCapturerExtDelegate-onnotifyapprunning"></span>
### onNotifyAppRunning
```objectivec

- (void)onNotifyAppRunning;
```
检测到 App 正在进行音视频通话时触发此回调。


# ByteRTCSingScoringDelegate
```objectivec
@protocol ByteRTCSingScoringDelegate<NSObject>
```

K 歌评分事件回调类。
注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。


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
实时评分信息回调。调用 [startSingScoring:scoringInfoInterval:](macOS-api.md#ByteRTCSingScoringManager-startsingscoring-scoringinfointerval) 后，会收到该回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| Info | **ByteRTCSingScoringRealtime** | 实时评分信息。详见 [ByteRTCSingScoringRealtimeInfo](macOS-keytype.md#bytertcsingscoringrealtimeinfo)。 |


# ByteRTCVideoProcessorDelegate
```objectivec
@protocol ByteRTCVideoProcessorDelegate <NSObject>
```

视频处理回调接口类
注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **ByteRTCVideoFrame*** | [processVideoFrame:](#ByteRTCVideoProcessorDelegate-processvideoframe) |


## 函数说明
<span id="ByteRTCVideoProcessorDelegate-processvideoframe"></span>
### processVideoFrame:
```objectivec

- (ByteRTCVideoFrame* _Nullable)processVideoFrame:(ByteRTCVideoFrame* _Nonnull)src_frame;
```
获取 RTC SDK 采集得到的视频帧，根据 [registerLocalVideoProcessor:withConfig:](macOS-api.md#ByteRTCVideo-registerlocalvideoprocessor-withconfig) 设置的视频前处理器，进行视频前处理，最终将处理后的视频帧给到 RTC SDK 用于编码传输。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| src_frame | **ByteRTCVideoFrame*** | RTC SDK 采集得到的视频帧，参考: [ByteRTCVideoFrame](macOS-keytype.md#bytertcvideoframe) |

**返回值**
经过视频前处理后的视频帧，返回给 RTC SDK 供编码和传输，参考: [ByteRTCVideoFrame](macOS-keytype.md#bytertcvideoframe)


**注意**
如果需要取消视频前处理，可以将视频前处理器设置为 nullptr。

# ByteRTCLocalEncodedVideoFrameObserver
```objectivec
@protocol ByteRTCLocalEncodedVideoFrameObserver<NSObject>
```

本地视频帧监测器
注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。


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
调用 [registerLocalEncodedVideoFrameObserver:](macOS-api.md#ByteRTCVideo-registerlocalencodedvideoframeobserver) 后，SDK 每次使用内部采集，采集到一帧视频帧，或收到一帧外部视频帧时，都会回调该事件。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamIndex | **ByteRTCStreamIndex** | 本地视频帧类型，参看 [ByteRTCStreamIndex](macOS-keytype.md#bytertcstreamindex) |
| frame | **ByteRTCEncodedVideoFrame* _Null_unspecified** | 本地视频帧信息，参看 [ByteRTCEncodedVideoFrame](macOS-keytype.md#bytertcencodedvideoframe) |


# ByteRTCExternalVideoEncoderEventHandler
```objectivec
@protocol ByteRTCExternalVideoEncoderEventHandler<NSObject>
```

自定义编码帧回调类
注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。


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
收到该回调后，你即可调用 [pushExternalEncodedVideoFrame:withVideoIndex:withEncodedVideoFrame:](macOS-api.md#ByteRTCVideo-pushexternalencodedvideoframe-withvideoindex-withencodedvideoframe) 向 SDK 推送自定义编码视频帧

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamIndex | **ByteRTCStreamIndex** | 可以推送的编码流的属性，参看 [ByteRTCStreamIndex](macOS-keytype.md#bytertcstreamindex) |


<span id="ByteRTCExternalVideoEncoderEventHandler-onstop"></span>
### onStop:
```objectivec

- (void)onStop:(ByteRTCStreamIndex)streamIndex;
```
当收到该回调时，你需停止向 SDK 推送自定义编码视频帧

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamIndex | **ByteRTCStreamIndex** | 需停止推送的编码流的属性，参看 [ByteRTCStreamIndex](macOS-keytype.md#bytertcstreamindex) |


<span id="ByteRTCExternalVideoEncoderEventHandler-onrateupdate-withvideoindex-withfps-withbitrate"></span>
### onRateUpdate:withVideoIndex:withFps:withBitRate:
```objectivec

- (void)onRateUpdate:(ByteRTCStreamIndex)streamIndex withVideoIndex:(NSInteger)videoIndex withFps:(NSInteger)fps withBitRate:(NSInteger)bitRateKps;
```
当自定义编码流的帧率或码率发生变化时，触发该回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamIndex | **ByteRTCStreamIndex** | 发生变化的编码流的属性，参看 [ByteRTCStreamIndex](macOS-keytype.md#bytertcstreamindex) |
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
| streamIndex | **ByteRTCStreamIndex** | 远端编码流的属性，参看 [ByteRTCStreamIndex](macOS-keytype.md#bytertcstreamindex) |
| videoIndex | **NSInteger** | 对应编码流的下标 |


# ByteRTCRemoteEncodedVideoFrameObserver
```objectivec
@protocol ByteRTCRemoteEncodedVideoFrameObserver<NSObject>
```

远端编码后视频数据监测器
注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。


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
调用 [registerRemoteEncodedVideoFrameObserver:](macOS-api.md#ByteRTCVideo-registerremoteencodedvideoframeobserver) 后，SDK 监测到远端编码后视频数据时，触发该回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamKey | **ByteRTCRemoteStreamKey*** | 收到的远端流信息，参看 [ByteRTCRemoteStreamKey](macOS-keytype.md#bytertcremotestreamkey) |
| videoFrame | **ByteRTCEncodedVideoFrame*** | 收到的远端视频帧信息，参看 [ByteRTCEncodedVideoFrame](macOS-keytype.md#bytertcencodedvideoframe) |


# LiveTranscodingDelegate
```objectivec
@protocol LiveTranscodingDelegate <NSObject>
```

转推直播观察者。  <br>
注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **BOOL** | [isSupportClientPushStream](#LiveTranscodingDelegate-issupportclientpushstream) |
| **void** | [onStreamMixingEvent:taskId:error:mixType:](#LiveTranscodingDelegate-onstreammixingevent-taskid-error-mixtype) |
| **void** | [onMixingAudioFrame:timestamp:taskId:](#LiveTranscodingDelegate-onmixingaudioframe-timestamp-taskid) |
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
如果需要开启端云一体转推直播功能，你必须确保你的 App 包含 librtmp，具有推流能力。此时，设置该回调为 true。

<span id="LiveTranscodingDelegate-onstreammixingevent-taskid-error-mixtype"></span>
### onStreamMixingEvent:taskId:error:mixType:
```objectivec

- (void)onStreamMixingEvent:(ByteRTCStreamMixingEvent)event taskId:(NSString *_Nonnull)taskId error:(ByteRtcTranscoderErrorCode)Code mixType:(ByteRTCStreamMixingType)mixType;
```
转推直播状态回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| event | **ByteRTCStreamMixingEvent** | 转推直播任务状态，参看 [ByteRTCStreamMixingEvent](macOS-keytype.md#bytertcstreammixingevent)。 |
| taskId | **NSString*** | 转推直播任务 ID。 |
| Code | **ByteRtcTranscoderErrorCode** | 转推直播错误码，参看 [ByteRtcTranscoderErrorCode](macOS-errorcode.md#bytertctranscodererrorcode) 和 [ByteRTCTranscodingError](macOS-errorcode.md#bytertctranscodingerror)。 |
| mixType | **ByteRTCStreamMixingType** | 转推直播类型，参看 [ByteRTCStreamMixingType](macOS-keytype.md#bytertcstreammixingtype)。 |


<span id="LiveTranscodingDelegate-onmixingaudioframe-timestamp-taskid"></span>
### onMixingAudioFrame:timestamp:taskId:
```objectivec

- (void)onMixingAudioFrame:(ByteRTCAudioFrame *_Nonnull)audioFrame timestamp:(int64_t)timeStamp taskId:(NSString *_Nonnull)taskId;
```
端云一体合流音频 PCM 回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioFrame | **ByteRTCAudioFrame*** | PCM 编码的合流音频数据帧，参看 [ByteRTCAudioFrame](macOS-keytype.md#bytertcaudioframe)。 |
| timeStamp | **int64_t** | 时间戳，单位毫秒。 |
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
| videoFrame | **ByteRTCVideoFrame*** | YUV 合流视频数据帧，参看 [ByteRTCVideoFrame](macOS-keytype.md#bytertcvideoframe)。 |
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
| dataFrame | **ByteRTCFrameExtendedData*** | SEI 数据，详见 [ByteRTCFrameExtendedData](macOS-keytype.md#bytertcframeextendeddata)。 |
| taskId | **NSString*** | 转推直播任务 ID。 |


# ByteRTCMixedStreamObserver
```objectivec
@protocol ByteRTCMixedStreamObserver <NSObject>
```

转推直播观察者。(Valid from 352.1)
注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **BOOL** | [isSupportClientPushStream](#ByteRTCMixedStreamObserver-issupportclientpushstream) |
| **void** | [onMixingEvent:taskId:error:mixType:](#ByteRTCMixedStreamObserver-onmixingevent-taskid-error-mixtype) |
| **void** | [onMixingAudioFrame:timestamp:taskId:](#ByteRTCMixedStreamObserver-onmixingaudioframe-timestamp-taskid) |
| **void** | [onMixingVideoFrame:taskId:](#ByteRTCMixedStreamObserver-onmixingvideoframe-taskid) |
| **void** | [onMixingDataFrame:taskId:](#ByteRTCMixedStreamObserver-onmixingdataframe-taskid) |


## 函数说明
<span id="ByteRTCMixedStreamObserver-issupportclientpushstream"></span>
### isSupportClientPushStream
```objectivec

- (BOOL)isSupportClientPushStream;
```
是否具有推流能力。  <br>

+ false：不具备推流能力（默认值）  <br>
+ true：具备推流能力


**注意**

+ 如果需要开启端云一体转推直播功能，你必须确保你的 App 包含 librtmp，具有推流能力。此时，设置该回调为 true。


<span id="ByteRTCMixedStreamObserver-onmixingevent-taskid-error-mixtype"></span>
### onMixingEvent:taskId:error:mixType:
```objectivec

- (void)onMixingEvent:(ByteRTCStreamMixingEvent)event taskId:(NSString *_Nonnull)taskId error:(ByteRTCStreamMixingErrorCode)Code mixType:(ByteRTCMixedStreamType)mixType;
```
转推直播状态回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| event | **ByteRTCStreamMixingEvent** | 转推直播任务状态，参看 [ByteRTCStreamMixingEvent](macOS-keytype.md#bytertcstreammixingevent)。 |
| taskId | **NSString*** | 转推直播任务 ID。 |
| Code | **ByteRTCStreamMixingErrorCode** | 转推直播错误码，参看 [ByteRTCStreamMixingErrorCode](macOS-errorcode.md#bytertcstreammixingerrorcode) 和 [ByteRTCStreamMixingErrorCode](macOS-errorcode.md#bytertcstreammixingerrorcode)。 |
| mixType | **ByteRTCMixedStreamType** | 转推直播类型，参看 [ByteRTCMixedStreamType](macOS-keytype.md#bytertcmixedstreamtype)。 |


<span id="ByteRTCMixedStreamObserver-onmixingaudioframe-timestamp-taskid"></span>
### onMixingAudioFrame:timestamp:taskId:
```objectivec

- (void)onMixingAudioFrame:(ByteRTCAudioFrame *_Nonnull)audioFrame timestamp:(int64_t)timeStamp taskId:(NSString *_Nonnull)taskId;
```
端云一体合流音频 PCM 回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioFrame | **ByteRTCAudioFrame*** | PCM 编码的合流音频数据帧，参看 [ByteRTCAudioFrame](macOS-keytype.md#bytertcaudioframe)。 |
| timeStamp | **int64_t** | 时间戳，单位毫秒。 |
| taskId | **NSString*** | 转推直播任务 ID。 |


**注意**
收到该回调的周期为每 10 毫秒一次，并且每次的音频数据量为 10 毫秒数据量。

<span id="ByteRTCMixedStreamObserver-onmixingvideoframe-taskid"></span>
### onMixingVideoFrame:taskId:
```objectivec

- (void)onMixingVideoFrame:(ByteRTCVideoFrame *_Nonnull)videoFrame taskId:(NSString *_Nonnull)taskId;
```
端云一体合流视频 YUV 回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| videoFrame | **ByteRTCVideoFrame*** | YUV 合流视频数据帧，参看 [ByteRTCVideoFrame](macOS-keytype.md#bytertcvideoframe)。 |
| taskId | **NSString*** | 转推直播任务 ID。 |


**注意**
收到该回调的周期取决于视频的帧率。

<span id="ByteRTCMixedStreamObserver-onmixingdataframe-taskid"></span>
### onMixingDataFrame:taskId:
```objectivec

- (void)onMixingDataFrame:(ByteRTCFrameExtendedData *_Nonnull)dataFrame taskId:(NSString *_Nonnull)taskId;
```
端云一体合流视频 SEI 数据

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| dataFrame | **ByteRTCFrameExtendedData*** | SEI 数据，详见 [ByteRTCFrameExtendedData](macOS-keytype.md#bytertcframeextendeddata)。 |
| taskId | **NSString*** | 转推直播任务 ID。 |


# ByteRTCPushSingleStreamToCDNObserver
```objectivec
@protocol ByteRTCPushSingleStreamToCDNObserver <NSObject>
```

单流转推直播观察者。  <br>
注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。


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
| event | **ByteRTCSingleStreamPushEvent** | 任务状态, 参看 [ByteRTCSingleStreamPushEvent](macOS-errorcode.md#bytertcsinglestreampushevent). |
| taskId | **NSString*** | 任务 ID |
| Code | **NSInteger** | 错误码，参看 [ByteRtcTranscoderErrorCode](macOS-errorcode.md#bytertctranscodererrorcode)。 |


# ByteRTCFaceDetectionObserver
```objectivec
@protocol ByteRTCFaceDetectionObserver <NSObject>
```

人脸检测结果回调观察者
注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **void** | [onFaceDetectResult:](#ByteRTCFaceDetectionObserver-onfacedetectresult) |


## 函数说明
<span id="ByteRTCFaceDetectionObserver-onfacedetectresult"></span>
### onFaceDetectResult:
```objectivec

- (void)onFaceDetectResult:(ByteRTCFaceDetectionResult * _Nonnull)result;
```
特效 SDK 进行人脸检测结果的回调。 <br>
调用 [enableFaceDetection:withInterval:withModelPath:](macOS-api.md#ByteRTCVideoEffect-enablefacedetection-withinterval-withmodelpath) 注册了 [ByteRTCFaceDetectionObserver](#bytertcfacedetectionobserver) ，并使用 RTC SDK 中包含的特效 SDK 进行视频特效处理时，你会收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| result | **ByteRTCFaceDetectionResult*** | 人脸检测结果, 参看 [ByteRTCFaceDetectionResult](macOS-keytype.md#bytertcfacedetectionresult)。 |


# ByteRTCVideoSnapshotCallbackDelegate
```objectivec
@protocol ByteRTCVideoSnapshotCallbackDelegate <NSObject>
```

截取视频画面回调类
注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。


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
调用 [takeLocalSnapshot:callback:](macOS-api.md#ByteRTCVideo-takelocalsnapshot-callback) 截取视频画面时，收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| taskId | **NSInteger** | 本地截图任务的编号。和 [takeLocalSnapshot:callback:](macOS-api.md#ByteRTCVideo-takelocalsnapshot-callback) 的返回值一致。 |
| streamIndex | **ByteRTCStreamIndex** | 截图的视频流的属性，参看 [ByteRTCStreamIndex](macOS-keytype.md#bytertcstreamindex)。 |
| image | **ByteRTCImage*** | 截图。你可以保存为文件，或对其进行二次处理。截图失败时，为空。 |
| errorCode | **NSInteger** | 截图错误码：<br/>• 0: 成功 <br/>• -1: 截图错误。生成图片数据失败或 RGBA 编码失败 <br/>• -2: 截图错误。流无效。 |


<span id="ByteRTCVideoSnapshotCallbackDelegate-ontakeremotesnapshotresult-streamkey-image-errorcode"></span>
### onTakeRemoteSnapshotResult:streamKey:image:errorCode:
```objectivec

- (void)onTakeRemoteSnapshotResult:(NSInteger)taskId streamKey:(ByteRTCRemoteStreamKey * _Nonnull)streamKey image:(ByteRTCImage * _Nullable)image errorCode:(NSInteger)errorCode;
```
调用 [takeRemoteSnapshot:callback:](macOS-api.md#ByteRTCVideo-takeremotesnapshot-callback) 截取视频画面时，收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| taskId | **NSInteger** | 远端截图任务的编号。和 [takeRemoteSnapshot:callback:](macOS-api.md#ByteRTCVideo-takeremotesnapshot-callback) 的返回值一致。 |
| streamKey | **ByteRTCRemoteStreamKey*** | 截图的视频流，参看 [ByteRTCRemoteStreamKey](macOS-keytype.md#bytertcremotestreamkey)。 |
| image | **ByteRTCImage*** | 截图。你可以保存为文件，或对其进行二次处理。截图失败时，为空。 |
| errorCode | **NSInteger** | 截图错误码：<br/>• 0: 成功 <br/>• -1: 截图错误。生成图片数据失败或 RGBA 编码失败 <br/>• -2: 截图错误。流无效。 |