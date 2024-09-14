<span id="IRTCRoomEventHandler"></span>
# IRTCRoomEventHandler
```java
public abstract class com.ss.bytertc.engine.handler.IRTCRoomEventHandler
```
房间事件回调接口

注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| void | [onLeaveRoom](#IRTCRoomEventHandler-onleaveroom) |
| void | [onRoomStateChanged](#IRTCRoomEventHandler-onroomstatechanged) |
| void | [onStreamStateChanged](#IRTCRoomEventHandler-onstreamstatechanged) |
| void | [onAVSyncStateChange](#IRTCRoomEventHandler-onavsyncstatechange) |
| void | [onRoomStats](#IRTCRoomEventHandler-onroomstats) |
| void | [onUserJoined](#IRTCRoomEventHandler-onuserjoined) |
| void | [onUserLeave](#IRTCRoomEventHandler-onuserleave) |
| void | [onTokenWillExpire](#IRTCRoomEventHandler-ontokenwillexpire) |
| void | [onPublishPrivilegeTokenWillExpire](#IRTCRoomEventHandler-onpublishprivilegetokenwillexpire) |
| void | [onSubscribePrivilegeTokenWillExpire](#IRTCRoomEventHandler-onsubscribeprivilegetokenwillexpire) |
| void | [onUserPublishStream](#IRTCRoomEventHandler-onuserpublishstream) |
| void | [onUserUnpublishStream](#IRTCRoomEventHandler-onuserunpublishstream) |
| void | [onUserPublishScreen](#IRTCRoomEventHandler-onuserpublishscreen) |
| void | [onUserUnpublishScreen](#IRTCRoomEventHandler-onuserunpublishscreen) |
| void | [onLocalStreamStats](#IRTCRoomEventHandler-onlocalstreamstats) |
| void | [onRemoteStreamStats](#IRTCRoomEventHandler-onremotestreamstats) |
| void | [onStreamSubscribed](#IRTCRoomEventHandler-onstreamsubscribed) |
| void | [onRoomMessageReceived](#IRTCRoomEventHandler-onroommessagereceived) |
| void | [onRoomBinaryMessageReceived](#IRTCRoomEventHandler-onroombinarymessagereceived) |
| void | [onUserMessageReceived](#IRTCRoomEventHandler-onusermessagereceived) |
| void | [onUserBinaryMessageReceived](#IRTCRoomEventHandler-onuserbinarymessagereceived) |
| void | [onUserMessageSendResult](#IRTCRoomEventHandler-onusermessagesendresult) |
| void | [onRoomMessageSendResult](#IRTCRoomEventHandler-onroommessagesendresult) |
| void | [onVideoStreamBanned](#IRTCRoomEventHandler-onvideostreambanned) |
| void | [onAudioStreamBanned](#IRTCRoomEventHandler-onaudiostreambanned) |
| void | [onForwardStreamStateChanged](#IRTCRoomEventHandler-onforwardstreamstatechanged) |
| void | [onForwardStreamEvent](#IRTCRoomEventHandler-onforwardstreamevent) |
| void | [onNetworkQuality](#IRTCRoomEventHandler-onnetworkquality) |
| void | [onSetRoomExtraInfoResult](#IRTCRoomEventHandler-onsetroomextrainforesult) |
| void | [onRoomExtraInfoUpdate](#IRTCRoomEventHandler-onroomextrainfoupdate) |
| void | [onUserVisibilityChanged](#IRTCRoomEventHandler-onuservisibilitychanged) |
| void | [onSubtitleStateChanged](#IRTCRoomEventHandler-onsubtitlestatechanged) |
| void | [onSubtitleMessageReceived](#IRTCRoomEventHandler-onsubtitlemessagereceived) |
| void | [deprecated] [onRoomWarning](#IRTCRoomEventHandler-onroomwarning) |
| void | [deprecated] [onRoomError](#IRTCRoomEventHandler-onroomerror) |
| void | [deprecated] [onStreamRemove](#IRTCRoomEventHandler-onstreamremove) |
| void | [deprecated] [onStreamAdd](#IRTCRoomEventHandler-onstreamadd) |


## 函数说明
<span id="IRTCRoomEventHandler-onleaveroom"></span>
### onLeaveRoom
```java
void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onLeaveRoom(RTCRoomStats stats)
```
离开房间成功回调。

用户调用 [leaveRoom](Android-api.md#RTCRoom-leaveroom) 方法后，SDK 会停止所有的发布订阅流，并在释放所有通话相关的音视频资源后，通过此回调通知用户离开房间成功。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stats | RTCRoomStats | 保留参数，目前为空。 |



**注意**

- 用户调用 [leaveRoom](Android-api.md#RTCRoom-leaveroom) 方法离开房间后，如果立即调用 [destroy](Android-api.md#RTCRoom-destroy) 销毁房间实例或 [destroyRTCVideo](Android-api.md#RTCVideo-destroyrtcvideo) 方法销毁 RTC 引擎，则将无法收到此回调事件。
- 离开房间后，如果 App 需要使用系统音视频设备，则建议在收到此回调后再初始化音视频设备，否则可能由于 SDK 占用音视频设备导致初始化失败。

<span id="IRTCRoomEventHandler-onroomstatechanged"></span>
### onRoomStateChanged
```java
void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onRoomStateChanged(
    String roomId,
    String uid,
    int state,
    String extraInfo
)
```
房间状态改变回调，加入房间、异常退出房间、发生房间相关的警告或错误时会收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| roomId | String | 房间 ID。 |
| uid | String | 用户 ID。 |
| state | int | 房间状态码。<br><ul><li>0: 加入房间成功。</li><li>!0: 加入房间失败、异常退房、发生房间相关的警告或错误。具体原因参看 [ErrorCode](Android-errorcode.md#ErrorCode) 及 [WarningCode](Android-errorcode.md#WarningCode)。</li></ul> |
| extraInfo | String | 额外信息，如 `{"elapsed":1187,"join_type":0}`。<br>`join_type` 表示加入房间的类型，`0`为首次进房，`1`为重连进房。<br>`elapsed` 表示加入房间耗时，即本地用户从调用 [joinRoom](Android-api.md#RTCRoom-joinroom) 到加入房间成功所经历的时间间隔，单位为 ms。 |



<span id="IRTCRoomEventHandler-onstreamstatechanged"></span>
### onStreamStateChanged
```java
void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onStreamStateChanged(
    String roomId,
    String uid,
    int state,
    String extraInfo
)
```
流状态改变回调，发生流相关的警告或错误时会收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| roomId | String | 房间 ID。 |
| uid | String | 用户 ID。 |
| state | int | 流状态码，参看 [ErrorCode](Android-errorcode.md#ErrorCode) 及 [WarningCode](Android-errorcode.md#WarningCode)。 |
| extraInfo | String | 附加信息，目前为空。 |



<span id="IRTCRoomEventHandler-onavsyncstatechange"></span>
### onAVSyncStateChange
```java
void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onAVSyncStateChange(AVSyncState state)
```
发布端调用 [setMultiDeviceAVSync](Android-api.md#RTCRoom-setmultideviceavsync) 后音视频同步状态发生改变时，会收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| state | AVSyncState | 音视频同步状态，参看 [AVSyncState](Android-keytype.md#AVSyncState)。 |



<span id="IRTCRoomEventHandler-onroomstats"></span>
### onRoomStats
```java
void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onRoomStats(RTCRoomStats stats)
```
房间内通话统计信息回调。

用户进房开始通话后，每 2s 收到一次本回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stats | RTCRoomStats | 房间内的汇总统计数据。详见 [RTCRoomStats](Android-keytype.md#RTCRoomStats)。 |



<span id="IRTCRoomEventHandler-onuserjoined"></span>
### onUserJoined
```java
void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onUserJoined(
    UserInfo userInfo,
    int elapsed
)
```
远端可见用户加入房间，或房内不可见用户切换为可见的回调。

1.远端用户调用 [setUserVisibility](Android-api.md#RTCRoom-setuservisibility) 方法将自身设为可见后加入房间时，房间内其他用户将收到该事件。

2.远端可见用户断网后重新连入房间时，房间内其他用户将收到该事件。

3.房间内隐身远端用户调用 [setUserVisibility](Android-api.md#RTCRoom-setuservisibility) 方法切换至可见时，房间内其他用户将收到该事件。

4.新进房用户也会收到进房前已在房内的可见用户的进房回调通知。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| userInfo | UserInfo | 用户信息。参看 [UserInfo](Android-keytype.md#UserInfo)。 |
| elapsed | int | 保留字段，无意义。 |



<span id="IRTCRoomEventHandler-onuserleave"></span>
### onUserLeave
```java
void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onUserLeave(
    String uid,
    int reason
)
```
远端用户离开房间，或切至不可见时，房间内其他用户会收到此事件


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | String | 离开房间，或切至不可见的的远端用户 ID。 |
| reason | int | 用户离开房间的原因：<br><ul><li>0: 远端用户调用 [leaveRoom](Android-api.md#RTCRoom-leaveroom) 主动退出房间。</li><li>1: 远端用户因 Token 过期或网络原因等掉线。详细信息请参看[连接状态提示](https://www.volcengine.com/docs/6348/95376)</li><li>2: 远端用户调用 [setUserVisibility](Android-api.md#RTCRoom-setuservisibility) 切换至不可见状态。</li><li>3: 服务端调用 OpenAPI 将该远端用户踢出房间。</li></ul> |



<span id="IRTCRoomEventHandler-ontokenwillexpire"></span>
### onTokenWillExpire
```java
void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onTokenWillExpire()
```
当 SDK 检测到 Token 的进房权限将在 30 秒内过期时，触发该回调。

收到该回调后，你需调用 [updateToken](Android-api.md#RTCRoom-updatetoken) 更新 Token 进房权限。


**注意**

若 Token 进房权限过期且未及时更新：

- 用户此时尝试进房会收到 [onRoomStateChanged](#IRTCRoomEventHandler-onroomstatechanged) 回调，提示错误码为 `-1000` Token 无效；
- 用户已在房间内则会被移出房间，本地用户会收到 [onRoomStateChanged](#IRTCRoomEventHandler-onroomstatechanged) 回调，提示错误码为 `-1009` Token 无效，同时远端用户会收到 [onUserLeave](#IRTCRoomEventHandler-onuserleave) 回调，提示原因为 `1` Token 进房权限过期。

<span id="IRTCRoomEventHandler-onpublishprivilegetokenwillexpire"></span>
### onPublishPrivilegeTokenWillExpire
```java
void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onPublishPrivilegeTokenWillExpire()
```
Token 发布权限过期前 30 秒将触发该回调。

收到该回调后，你需调用 [updateToken](Android-api.md#RTCRoom-updatetoken) 更新 Token 发布权限。


**注意**

若收到该回调后未及时更新 Token，Token 发布权限过期后：

- 此时尝试发布流会收到 [onStreamStateChanged](#IRTCRoomEventHandler-onstreamstatechanged) 回调，提示错误码为 `-1002` 没有发布权限；
- 已在发布中的流会停止发布，发布端会收到 [onStreamStateChanged](#IRTCRoomEventHandler-onstreamstatechanged) 回调，提示错误码为 `-1002` 没有发布权限，同时远端用户会收到 [onUserUnpublishStream](#IRTCRoomEventHandler-onuserunpublishstream)/ [onUserUnpublishScreen](#IRTCRoomEventHandler-onuserunpublishscreen) 回调，提示原因为 `6` 发流端发布权限过期。

<span id="IRTCRoomEventHandler-onsubscribeprivilegetokenwillexpire"></span>
### onSubscribePrivilegeTokenWillExpire
```java
void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onSubscribePrivilegeTokenWillExpire()
```
Token 订阅权限过期前 30 秒将触发该回调。

收到该回调后，你需调用 [updateToken](Android-api.md#RTCRoom-updatetoken) 更新 Token 订阅权限有效期。


**注意**

若收到该回调后未及时更新 Token，Token 订阅权限过期后，尝试新订阅流会失败，已订阅的流会取消订阅，并且会收到 [onStreamStateChanged](#IRTCRoomEventHandler-onstreamstatechanged) 回调，提示错误码为 `-1003` 没有订阅权限。

<span id="IRTCRoomEventHandler-onuserpublishstream"></span>
### onUserPublishStream
```java
void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onUserPublishStream(
    String uid,
    MediaStreamType type
)
```
房间内新增远端摄像头/麦克风采集的媒体流的回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | String | 远端流发布用户的用户 ID。 |
| type | MediaStreamType | 远端媒体流的类型，参看 [MediaStreamType](Android-keytype.md#MediaStreamType)。 |



**注意**

当房间内的远端用户调用 [publishStream](Android-api.md#RTCRoom-publishstream) 成功发布由摄像头/麦克风采集的媒体流时，本地用户会收到该回调，此时本地用户可以自行选择是否调用 [subscribeStream](Android-api.md#RTCRoom-subscribestream) 订阅此流。

<span id="IRTCRoomEventHandler-onuserunpublishstream"></span>
### onUserUnpublishStream
```java
void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onUserUnpublishStream(
    String uid,
    MediaStreamType type,
    StreamRemoveReason reason
)
```
房间内远端摄像头/麦克风采集的媒体流移除的回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | String | 移除的远端流发布用户的用户 ID。 |
| type | MediaStreamType | 移除的远端流类型，参看 [MediaStreamType](Android-keytype.md#MediaStreamType)。 |
| reason | StreamRemoveReason | 远端流移除的原因，参看 [StreamRemoveReason](Android-keytype.md#StreamRemoveReason)。 |



**注意**

收到该回调通知后，你可以自行选择是否调用 [unsubscribeStream](Android-api.md#RTCRoom-unsubscribestream) 取消订阅此流。

<span id="IRTCRoomEventHandler-onuserpublishscreen"></span>
### onUserPublishScreen
```java
void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onUserPublishScreen(
    String uid,
    MediaStreamType type
)
```
房间内新增远端屏幕共享音视频流的回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | String | 远端流发布用户的用户 ID。 |
| type | MediaStreamType | 远端媒体流的类型，参看 [MediaStreamType](Android-keytype.md#MediaStreamType)。 |



**注意**

当房间内的远端用户调用 [publishScreen](Android-api.md#RTCRoom-publishscreen) 成功发布来自屏幕共享的音视频流时，本地用户会收到该回调，此时本地用户可以自行选择是否调用 [subscribeScreen](Android-api.md#RTCRoom-subscribescreen) 订阅此流。

<span id="IRTCRoomEventHandler-onuserunpublishscreen"></span>
### onUserUnpublishScreen
```java
void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onUserUnpublishScreen(
    String uid,
    MediaStreamType type,
    StreamRemoveReason reason
)
```
房间内远端屏幕共享音视频流移除的回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | String | 移除的远端流发布用户的用户 ID。 |
| type | MediaStreamType | 移除的远端流类型，参看 [MediaStreamType](Android-keytype.md#MediaStreamType)。 |
| reason | StreamRemoveReason | 远端流移除的原因，参看 [StreamRemoveReason](Android-keytype.md#StreamRemoveReason)。 |



**注意**

收到该回调通知后，你可以自行选择是否调用 [unsubscribeScreen](Android-api.md#RTCRoom-unsubscribescreen) 取消订阅此流。

<span id="IRTCRoomEventHandler-onlocalstreamstats"></span>
### onLocalStreamStats
```java
void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onLocalStreamStats(LocalStreamStats stats)
```
本地流数据统计以及网络质量回调。

本地用户发布流成功后，SDK 会周期性（2s）的通过此回调事件通知用户发布的流在此次统计周期内的质量统计信息。

统计信息通过 [LocalStreamStats](Android-keytype.md#LocalStreamStats) 类型的回调参数传递给用户，其中包括发送音视频比特率、发送帧率、编码帧率，网络质量等。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stats | LocalStreamStats | 音视频流以及网络状况统计信息。参见 [LocalStreamStats](Android-keytype.md#LocalStreamStats)。 |



<span id="IRTCRoomEventHandler-onremotestreamstats"></span>
### onRemoteStreamStats
```java
void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onRemoteStreamStats(RemoteStreamStats stats)
```
本地订阅的远端音/视频流数据统计以及网络质量回调。

本地用户订阅流成功后，SDK 会周期性（2s）的通过此回调事件通知用户订阅的流在此次统计周期内的质量统计信息，包括：发送音视频比特率、发送帧率、编码帧率，网络质量等。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stats | RemoteStreamStats | 音视频流以及网络状况统计信息。参见 [RemoteStreamStats](Android-keytype.md#RemoteStreamStats)。 |



<span id="IRTCRoomEventHandler-onstreamsubscribed"></span>
### onStreamSubscribed
```java
void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onStreamSubscribed(
    int stateCode,
    String userId,
    SubscribeConfig info
)
```
关于订阅媒体流状态改变的回调


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stateCode | int | 订阅媒体流状态，参看 [SubscribeState](Android-keytype.md#SubscribeState) |
| userId | String | 流发布用户的用户 ID |
| info | SubscribeConfig | 流的属性，参看 [SubscribeConfig](Android-keytype.md#SubscribeConfig) |



**注意**

本地用户收到该回调的时机包括：

- 调用 [subscribeStream](Android-api.md#RTCRoom-subscribestream) 或 [unsubscribeStream](Android-api.md#RTCRoom-unsubscribestream) 订阅/取消订阅指定远端摄像头音视频流后；
- 调用 [subscribeScreen](Android-api.md#RTCRoom-subscribescreen) 或 [unsubscribeScreen](Android-api.md#RTCRoom-unsubscribescreen) 订阅/取消订阅指定远端屏幕共享流后。

<span id="IRTCRoomEventHandler-onroommessagereceived"></span>
### onRoomMessageReceived
```java
void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onRoomMessageReceived(
    String uid,
    String message
)
```
接收到房间内广播消息的回调。

房间内其他用户调用 [sendRoomMessage](Android-api.md#RTCRoom-sendroommessage) 发送广播消息时，收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | String | 消息发送者 ID |
| message | String | 收到的消息内容 |



<span id="IRTCRoomEventHandler-onroombinarymessagereceived"></span>
### onRoomBinaryMessageReceived
```java
void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onRoomBinaryMessageReceived(
    String uid,
    ByteBuffer message
)
```
收到房间内广播二进制消息的回调。

房间内其他用户调用 [sendRoomBinaryMessage](Android-api.md#RTCRoom-sendroombinarymessage) 发送广播二进制消息时，收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | String | 消息发送者 ID |
| message | ByteBuffer | 收到的二进制消息内容 |



<span id="IRTCRoomEventHandler-onusermessagereceived"></span>
### onUserMessageReceived
```java
void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onUserMessageReceived(
    String uid,
    String message
)
```
收到来自房间中其他用户通过 [sendUserMessage](Android-api.md#RTCRoom-sendusermessage) 发来的点对点文本消息时，会收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | String | 消息发送者的用户 ID 。 |
| message | String | 收到的文本消息内容。 |



<span id="IRTCRoomEventHandler-onuserbinarymessagereceived"></span>
### onUserBinaryMessageReceived
```java
void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onUserBinaryMessageReceived(
    String uid,
    ByteBuffer message
)
```
收到来自房间中其他用户通过 [sendUserBinaryMessage](Android-api.md#RTCRoom-senduserbinarymessage) 发来的点对点二进制消息时，会收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | String | 消息发送者的用户 ID 。 |
| message | ByteBuffer | 收到的二进制消息内容。 |



<span id="IRTCRoomEventHandler-onusermessagesendresult"></span>
### onUserMessageSendResult
```java
void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onUserMessageSendResult(
    long msgid,
    int error
)
```
向房间内单个用户发送文本或二进制消息后（P2P），消息发送方会收到该消息发送结果回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| msgid | long | 本条消息的 ID。 |
| error | int | 文本或二进制消息发送结果，详见 [UserMessageSendResult](Android-errorcode.md#UserMessageSendResult) |



**注意**

调用 [sendUserMessage](Android-api.md#RTCRoom-sendusermessage) 或 [sendUserBinaryMessage](Android-api.md#RTCRoom-senduserbinarymessage) 接口，才能收到此回调。

<span id="IRTCRoomEventHandler-onroommessagesendresult"></span>
### onRoomMessageSendResult
```java
void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onRoomMessageSendResult(
    long msgid,
    int error
)
```
调用 [sendRoomMessage](Android-api.md#RTCRoom-sendroommessage) 或 [sendRoomBinaryMessage](Android-api.md#RTCRoom-sendroombinarymessage) 向房间内群发文本或二进制消息后，消息发送方会收到该消息发送结果回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| msgid | long | 本条消息的 ID。 |
| error | int | 消息发送结果，详见 [RoomMessageSendResult](Android-errorcode.md#RoomMessageSendResult) |



<span id="IRTCRoomEventHandler-onvideostreambanned"></span>
### onVideoStreamBanned
```java
void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onVideoStreamBanned(
    String uid,
    boolean banned
)
```
通过调用服务端 BanUserStream/UnbanUserStream 方法禁用/解禁指定房间内指定用户视频流的发送时，触发此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | String | 被禁用/解禁的视频流用户 ID |
| banned | boolean | 视频流发送状态<br><ul><li>true: 视频流发送被禁用</li><li>false: 视频流发送被解禁</li></ul> |



**注意**

- 房间内指定用户被禁止/解禁视频流发送时，房间内所有用户都会收到该回调。
- 若被封禁用户断网或退房后再进房，则依然是封禁状态，且房间内所有人会再次收到该回调。
- 指定用户被封禁后，房间内其他用户退房后再进房，会再次收到该回调。
- 同一房间解散后再次创建，房间内状态清空。

<span id="IRTCRoomEventHandler-onaudiostreambanned"></span>
### onAudioStreamBanned
```java
void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onAudioStreamBanned(
    String uid,
    boolean banned
)
```
通过调用服务端 BanUserStream/UnbanUserStream 方法禁用/解禁指定房间内指定用户音频流的发送时，触发此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | String | 被禁用/解禁的音频流用户 ID |
| banned | boolean | 音频流发送状态<br><ul><li>true: 音频流发送被禁用</li><li>false: 音频流发送被解禁</li></ul> |



**注意**

- 房间内指定用户被禁止/解禁音频流发送时，房间内所有用户都会收到该回调。
- 若被封禁用户断网或退房后再进房，则依然是封禁状态，且房间内所有人会再次收到该回调。
- 指定用户被封禁后，房间内其他用户退房后再进房，会再次收到该回调。
- 在控制台开启音频选路后，只有被封禁/解禁用户会收到该回调。
- 同一房间解散后再次创建，房间内状态清空。

<span id="IRTCRoomEventHandler-onforwardstreamstatechanged"></span>
### onForwardStreamStateChanged
```java
void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onForwardStreamStateChanged(ForwardStreamStateInfo[] stateInfos)
```
跨房间媒体流转发状态和错误回调


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stateInfos | ForwardStreamStateInfo[] | 跨房间媒体流转发目标房间信息数组，详见 [ForwardStreamStateInfo](Android-keytype.md#ForwardStreamStateInfo) |



<span id="IRTCRoomEventHandler-onforwardstreamevent"></span>
### onForwardStreamEvent
```java
void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onForwardStreamEvent(ForwardStreamEventInfo[] eventInfos)
```
跨房间媒体流转发事件回调


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| eventInfos | ForwardStreamEventInfo[] | 跨房间媒体流转发目标房间事件数组，详见 [ForwardStreamEventInfo](Android-keytype.md#ForwardStreamEventInfo) |



<span id="IRTCRoomEventHandler-onnetworkquality"></span>
### onNetworkQuality
```java
void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onNetworkQuality(
    NetworkQualityStats localQuality,
    NetworkQualityStats[] remoteQualities
)
```
加入房间并发布或订阅流后， 以每 2 秒一次的频率，报告本地用户和已订阅的远端用户的上下行网络质量信息。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| localQuality | NetworkQualityStats | 本地网络质量，详见 [NetworkQualityStats](Android-keytype.md#NetworkQualityStats)。 |
| remoteQualities | NetworkQualityStats[] | 已订阅用户的网络质量，详见 [NetworkQualityStats](Android-keytype.md#NetworkQualityStats)。 |



**注意**

更多通话中的监测接口，详见[通话中质量监测](https://www.volcengine.com/docs/6348/106866)。

<span id="IRTCRoomEventHandler-onsetroomextrainforesult"></span>
### onSetRoomExtraInfoResult
```java
void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onSetRoomExtraInfoResult(
    long taskId,
    SetRoomExtraInfoResult error
)
```
> Available since 3.52

调用 [setRoomExtraInfo](Android-api.md#RTCRoom-setroomextrainfo) 设置房间附加信息结果的回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| taskId | long | 调用 setRoomExtraInfo 的任务编号。 |
| error | SetRoomExtraInfoResult | 设置房间附加信息的结果，详见 [SetRoomExtraInfoResult](Android-keytype.md#SetRoomExtraInfoResult) |



<span id="IRTCRoomEventHandler-onroomextrainfoupdate"></span>
### onRoomExtraInfoUpdate
```java
void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onRoomExtraInfoUpdate(
    String key,
    String value,
    String lastUpdateUserId,
    long lastUpdateTimeMs
)
```
> Available since 3.52

接收同一房间内，其他用户调用 [setRoomExtraInfo](Android-api.md#RTCRoom-setroomextrainfo) 设置的房间附加信息的回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| key | String | 房间附加信息的键值 |
| value | String | 房间附加信息的内容 |
| lastUpdateUserId | String | 最后更新本条信息的用户 ID。 |
| lastUpdateTimeMs | long | 最后更新本条信息的 Unix 时间，单位：毫秒。 |



**注意**

新进房的用户会收到进房前房间内已有的全部附加信息通知。

<span id="IRTCRoomEventHandler-onuservisibilitychanged"></span>
### onUserVisibilityChanged
```java
void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onUserVisibilityChanged(
    boolean currentUserVisibility,
    UserVisibilityChangeError errorCode
)
```
> Available since 3.54

用户调用 [setUserVisibility](Android-api.md#RTCRoom-setuservisibility) 设置用户可见性的回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| currentUserVisibility | boolean | 当前用户的可见性。<br><ul><li>true: 可见，用户可以在房间内发布音视频流，房间中的其他用户将收到用户的行为通知，例如进房、开启视频采集和退房。</li><li>false: 不可见，用户不可以在房间内发布音视频流，房间中的其他用户不会收到用户的行为通知，例如进房、开启视频采集和退房。</li></ul> |
| errorCode | UserVisibilityChangeError | 设置用户可见性错误码，参看 [UserVisibilityChangeError](Android-keytype.md#UserVisibilityChangeError)。 |



<span id="IRTCRoomEventHandler-onsubtitlestatechanged"></span>
### onSubtitleStateChanged
```java
void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onSubtitleStateChanged(
    SubtitleState state,
    SubtitleErrorCode errorCode,
    String errorMessage
)
```
字幕状态发生改变回调。

当用户调用 [startSubtitle](Android-api.md#RTCRoom-startsubtitle) 和 [stopSubtitle](Android-api.md#RTCRoom-stopsubtitle) 使字幕状态发生改变或字幕任务出现错误时，触发该回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| state | SubtitleState | 字幕状态。参看 [SubtitleState](Android-keytype.md#SubtitleState)。 |
| errorCode | SubtitleErrorCode | 字幕任务错误码。参看 [SubtitleErrorCode](Android-errorcode.md#SubtitleErrorCode)。 |
| errorMessage | String | 与第三方服务有关的错误信息。 |



<span id="IRTCRoomEventHandler-onsubtitlemessagereceived"></span>
### onSubtitleMessageReceived
```java
void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onSubtitleMessageReceived(SubtitleMessage[] subtitles)
```
字幕相关内容回调。

当用户成功调用 [startSubtitle](Android-api.md#RTCRoom-startsubtitle) 后会收到此回调，通知字幕的相关信息。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| subtitles | SubtitleMessage[] | 字幕消息内容。参看 [SubtitleMessage](Android-keytype.md#SubtitleMessage)。 |



<span id="IRTCRoomEventHandler-onroomwarning"></span>
### onRoomWarning
```java
void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onRoomWarning(int warn)
```
> Deprecated since 3.41 and will be deleted in 3.51, use [onRoomStateChanged](#IRTCRoomEventHandler-onroomstatechanged) and [onStreamStateChanged](#IRTCRoomEventHandler-onstreamstatechanged) instead.

发生警告回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| warn | int | 警告代码，参见 [WarningCode](Android-errorcode.md#WarningCode) |



**注意**

SDK 运行时出现了（网络或媒体相关的）警告。SDK 通常会自动恢复，警告信息可以忽略。

<span id="IRTCRoomEventHandler-onroomerror"></span>
### onRoomError
```java
void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onRoomError(int err)
```
> Deprecated since 3.41 and will be deleted in 3.51, use [onRoomStateChanged](#IRTCRoomEventHandler-onroomstatechanged) and [onStreamStateChanged](#IRTCRoomEventHandler-onstreamstatechanged) instead.

发生错误回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| err | int | 错误代码，详情定义见: [ErrorCode](Android-errorcode.md#ErrorCode) |



**注意**

SDK 运行时出现了（网络或媒体相关的）错误。SDK 通常无法自动恢复，你可能需要干预。

<span id="IRTCRoomEventHandler-onstreamremove"></span>
### onStreamRemove
```java
void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onStreamRemove(
    RTCStream stream,
    StreamRemoveReason reason
)
```
> Deprecated since 3.36 and will be deleted in 3.51, use [onUserUnpublishStream](#IRTCRoomEventHandler-onuserunpublishstream) and [onUserUnpublishScreen](#IRTCRoomEventHandler-onuserunpublishscreen) instead.

房间内远端流移除回调。

房间内的远端用户停止发布音视频流时，本地用户会收到此回调通知。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stream | RTCStream | 流的属性，参看 [RTCStream](Android-keytype.md#RTCStream)。 |
| reason | StreamRemoveReason | 远端流移除的原因，参看 [StreamRemoveReason](Android-keytype.md#StreamRemoveReason)。 |



<span id="IRTCRoomEventHandler-onstreamadd"></span>
### onStreamAdd
```java
void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onStreamAdd(RTCStream stream)
```
> Deprecated since 3.36 and will be deleted in 3.51, use [onUserPublishStream](#IRTCRoomEventHandler-onuserpublishstream) and [onUserPublishScreen](#IRTCRoomEventHandler-onuserpublishscreen) instead.

房间内新流发布回调。

房间内的远端用户发布新的音视频流时，本地用户会收到此回调通知。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stream | RTCStream | 流的属性，详见 [RTCStream](Android-keytype.md#RTCStream) 数据类型。 |



<span id="IKTVPlayerEventHandler"></span>
# IKTVPlayerEventHandler
```java
public abstract class com.ss.bytertc.ktv.IKTVPlayerEventHandler
```
KTV 播放器回调接口。

注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| abstract void | [onPlayProgress](#IKTVPlayerEventHandler-onplayprogress) |
| abstract void | [onPlayStateChanged](#IKTVPlayerEventHandler-onplaystatechanged) |


## 函数说明
<span id="IKTVPlayerEventHandler-onplayprogress"></span>
### onPlayProgress
```java
abstract void com.ss.bytertc.ktv.IKTVPlayerEventHandler.onPlayProgress(
    @NonNull String musicId,
    long progress
)
```
音乐播放进度回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| musicId | @NonNull String | 音乐 ID。 |
| progress | long | 音乐播放进度，单位为毫秒。 |



<span id="IKTVPlayerEventHandler-onplaystatechanged"></span>
### onPlayStateChanged
```java
abstract void com.ss.bytertc.ktv.IKTVPlayerEventHandler.onPlayStateChanged(
    @NonNull String musicId,
    @NonNull PlayState playState,
    KTVPlayerErrorCode errorCode
)
```
音乐播放状态改变回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| musicId | @NonNull String | 音乐 ID。 |
| playState | @NonNull PlayState | 音乐播放状态，参看 [PlayState](Android-keytype.md#PlayState)。 |
| errorCode | KTVPlayerErrorCode | 错误码，参看 [KTVPlayerErrorCode](Android-keytype.md#KTVPlayerErrorCode)。 |



**注意**

此回调被触发的时机汇总如下：

- 调用 [playMusic](Android-api.md#IKTVPlayer-playmusic) 成功后，会触发 playState 值为 PLAY_STATE_PLAYING 的回调；否则会触发 playState 值为 PLAY_STATE_FAILED 的回调。
- 使用相同的音乐 ID 重复调用 [playMusic](Android-api.md#IKTVPlayer-playmusic) 后，后一次播放会覆盖前一次，且会触发 playState 值为 PLAY_STATE_PLAYING 的回调，表示后一次音乐播放已开始。
- 调用 [pauseMusic](Android-api.md#IKTVPlayer-pausemusic) 方法暂停播放成功后，会触发 playState 值为 PLAY_STATE_PAUSED 的回调；否则触发 playState 值为 PLAY_STATE_FAILED 的回调。
- 调用 [resumeMusic](Android-api.md#IKTVPlayer-resumemusic) 方法恢复播放成功后，会触发 playState 值为 PLAY_STATE_PLAYING 的回调；否则触发 playState 值为 PLAY_STATE_FAILED 的回调。
- 调用 [stopMusic](Android-api.md#IKTVPlayer-stopmusic) 方法停止播放成功后，会触发 playState 值为 PLAY_STATE_STOPPED 的回调；否则触发 playState 值为 PLAY_STATE_FAILED 的回调。
- 音乐播放结束会触发 playState 值为 PLAY_STATE_FINISHED 的回调。

<span id="IAudioEffectPlayerEventHandler"></span>
# IAudioEffectPlayerEventHandler
```java
public interface com.ss.bytertc.engine.IAudioEffectPlayerEventHandler
```
[IAudioEffectPlayer](Android-api.md#IAudioEffectPlayer) 对应的回调句柄。你必须调用 [setEventHandler](Android-api.md#IAudioEffectPlayer-seteventhandler) 完成设置后，才能收到对应回调。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| void | [onAudioEffectPlayerStateChanged](#IAudioEffectPlayerEventHandler-onaudioeffectplayerstatechanged) |


## 函数说明
<span id="IAudioEffectPlayerEventHandler-onaudioeffectplayerstatechanged"></span>
### onAudioEffectPlayerStateChanged
```java
void com.ss.bytertc.engine.IAudioEffectPlayerEventHandler.onAudioEffectPlayerStateChanged(
    int effectId,
    PlayerState state,
    PlayerError error
)
```
播放状态改变时回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| effectId | int | [IAudioEffectPlayer](Android-api.md#IAudioEffectPlayer) 的 ID。通过 [getAudioEffectPlayer](Android-api.md#RTCVideo-getaudioeffectplayer) 设置。 |
| state | PlayerState | 混音状态。参考 [PlayerState](Android-keytype.md#PlayerState)。 |
| error | PlayerError | 错误码。参考 [PlayerError](Android-keytype.md#PlayerError)。 |



<span id="IPushSingleStreamToCDNObserver"></span>
# IPushSingleStreamToCDNObserver
```java
public interface com.ss.bytertc.engine.live.IPushSingleStreamToCDNObserver
```
单流转推直播观察者。

注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| void | [onStreamPushEvent](#IPushSingleStreamToCDNObserver-onstreampushevent) |


## 函数说明
<span id="IPushSingleStreamToCDNObserver-onstreampushevent"></span>
### onStreamPushEvent
```java
void com.ss.bytertc.engine.live.IPushSingleStreamToCDNObserver.onStreamPushEvent(
    ByteRTCStreamSinglePushEvent eventType,
    String taskId,
    int error
)
```
单流转推直播状态回调


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| eventType | ByteRTCStreamSinglePushEvent | 任务状态, 参看 [ByteRTCStreamSinglePushEvent](Android-errorcode.md#ByteRTCStreamSinglePushEvent) |
| taskId | String | 任务 ID |
| error | int | 错误码，参看 [ByteRTCTranscoderErrorCode](Android-errorcode.md#ByteRTCTranscoderErrorCode) |



<span id="IRemoteEncodedVideoFrameObserver"></span>
# IRemoteEncodedVideoFrameObserver
```java
public abstract class com.ss.bytertc.engine.mediaio.IRemoteEncodedVideoFrameObserver
```
远端编码后视频数据监测器

注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| abstract void | [onRemoteEncodedVideoFrame](#IRemoteEncodedVideoFrameObserver-onremoteencodedvideoframe) |


## 函数说明
<span id="IRemoteEncodedVideoFrameObserver-onremoteencodedvideoframe"></span>
### onRemoteEncodedVideoFrame
```java
abstract void com.ss.bytertc.engine.mediaio.IRemoteEncodedVideoFrameObserver.onRemoteEncodedVideoFrame(
    RemoteStreamKey streamKey,
    RTCEncodedVideoFrame encodedVideoFrame
)
```
调用 [registerRemoteEncodedVideoFrameObserver](Android-api.md#RTCVideo-registerremoteencodedvideoframeobserver) 后，SDK 监测到远端编码后视频数据时，触发该回调


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamKey | RemoteStreamKey | 收到的远端流信息，参看 [RemoteStreamKey](Android-keytype.md#RemoteStreamKey) |
| encodedVideoFrame | RTCEncodedVideoFrame | 收到的远端视频帧信息，参看 [RTCEncodedVideoFrame](Android-keytype.md#RTCEncodedVideoFrame) |



**注意**

encodedVideoFrame 只在回调函数作用域内有效，不要存储该参数并在其它函数内访问该参数的内存数据

<span id="IKTVManagerEventHandler"></span>
# IKTVManagerEventHandler
```java
public abstract class com.ss.bytertc.ktv.IKTVManagerEventHandler
```
KTV 事件回调接口。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| abstract void | [onMusicListResult](#IKTVManagerEventHandler-onmusiclistresult) |
| abstract void | [onSearchMusicResult](#IKTVManagerEventHandler-onsearchmusicresult) |
| abstract void | [onHotMusicResult](#IKTVManagerEventHandler-onhotmusicresult) |
| abstract void | [onMusicDetailResult](#IKTVManagerEventHandler-onmusicdetailresult) |
| abstract void | [onDownloadSuccess](#IKTVManagerEventHandler-ondownloadsuccess) |
| abstract void | [onDownloadFailed](#IKTVManagerEventHandler-ondownloadfailed) |
| abstract void | [onDownloadMusicProgress](#IKTVManagerEventHandler-ondownloadmusicprogress) |
| abstract void | [onClearCacheResult](#IKTVManagerEventHandler-onclearcacheresult) |


## 函数说明
<span id="IKTVManagerEventHandler-onmusiclistresult"></span>
### onMusicListResult
```java
abstract void com.ss.bytertc.ktv.IKTVManagerEventHandler.onMusicListResult(
    MusicInfo[] musicInfos,
    int totalSize,
    KTVErrorCode errorCode
)
```
歌曲列表回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| musicInfos | MusicInfo[] | 歌曲数据数组，参看 [MusicInfo](Android-keytype.md#MusicInfo)。 |
| totalSize | int | 数据条目总数。 |
| errorCode | KTVErrorCode | 错误码，成功时返回 0，其余值参看 [KTVErrorCode](Android-errorcode.md#KTVErrorCode)。 |



<span id="IKTVManagerEventHandler-onsearchmusicresult"></span>
### onSearchMusicResult
```java
abstract void com.ss.bytertc.ktv.IKTVManagerEventHandler.onSearchMusicResult(
    MusicInfo[] musicInfos,
    int totalSize,
    KTVErrorCode errorCode
)
```
搜索歌曲结果回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| musicInfos | MusicInfo[] | 歌曲数据数组，参看 [MusicInfo](Android-keytype.md#MusicInfo)。 |
| totalSize | int | 数据条目总数。 |
| errorCode | KTVErrorCode | 错误码，成功时返回 0，其余值参看 [KTVErrorCode](Android-errorcode.md#KTVErrorCode)。 |



<span id="IKTVManagerEventHandler-onhotmusicresult"></span>
### onHotMusicResult
```java
abstract void com.ss.bytertc.ktv.IKTVManagerEventHandler.onHotMusicResult(
    HotMusicInfo[] hotMusics,
    KTVErrorCode errorCode
)
```
热榜歌曲结果回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| hotMusics | HotMusicInfo[] | 热榜歌曲数据数组，参看 [HotMusicInfo](Android-keytype.md#HotMusicInfo)。 |
| errorCode | KTVErrorCode | 错误码，成功时返回 0，其余值参看 [KTVErrorCode](Android-errorcode.md#KTVErrorCode)。 |



<span id="IKTVManagerEventHandler-onmusicdetailresult"></span>
### onMusicDetailResult
```java
abstract void com.ss.bytertc.ktv.IKTVManagerEventHandler.onMusicDetailResult(
    MusicInfo musicInfo,
    KTVErrorCode errorCode
)
```
歌曲详细信息回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| musicInfo | MusicInfo | 歌曲数据，参看 [MusicInfo](Android-keytype.md#MusicInfo)。 |
| errorCode | KTVErrorCode | 错误码，成功时返回 0，其余值参看 [KTVErrorCode](Android-errorcode.md#KTVErrorCode)。 |



<span id="IKTVManagerEventHandler-ondownloadsuccess"></span>
### onDownloadSuccess
```java
abstract void com.ss.bytertc.ktv.IKTVManagerEventHandler.onDownloadSuccess(
    int downloadId,
    DownloadResult result
)
```
下载成功回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| downloadId | int | 下载任务 ID。 |
| result | DownloadResult | 下载信息，参看 [DownloadResult](Android-keytype.md#DownloadResult)。 |



<span id="IKTVManagerEventHandler-ondownloadfailed"></span>
### onDownloadFailed
```java
abstract void com.ss.bytertc.ktv.IKTVManagerEventHandler.onDownloadFailed(
    int downloadId,
    KTVErrorCode errorCode
)
```
下载失败回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| downloadId | int | 下载任务 ID。 |
| errorCode | KTVErrorCode | 错误码，成功时返回 0，其余值参看 [KTVErrorCode](Android-errorcode.md#KTVErrorCode)。 |



<span id="IKTVManagerEventHandler-ondownloadmusicprogress"></span>
### onDownloadMusicProgress
```java
abstract void com.ss.bytertc.ktv.IKTVManagerEventHandler.onDownloadMusicProgress(
    int downloadId,
    int downloadProgress
)
```
歌曲文件下载进度回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| downloadId | int | 下载任务 ID。 |
| downloadProgress | int | 下载进度百分比，取值范围 [0,100]。 |



<span id="IKTVManagerEventHandler-onclearcacheresult"></span>
### onClearCacheResult
```java
abstract void com.ss.bytertc.ktv.IKTVManagerEventHandler.onClearCacheResult(KTVErrorCode errorCode)
```
清理文件缓存结果回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| errorCode | KTVErrorCode | 错误码，非 0 为失败，参看 [KTVErrorCode](Android-errorcode.md#KTVErrorCode)。 |



<span id="ISingScoringEventHandler"></span>
# ISingScoringEventHandler
```java
public interface com.ss.bytertc.engine.ISingScoringEventHandler
```
K 歌评分事件回调类。

注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| void | [onCurrentScoringInfo](#ISingScoringEventHandler-oncurrentscoringinfo) |


## 函数说明
<span id="ISingScoringEventHandler-oncurrentscoringinfo"></span>
### onCurrentScoringInfo
```java
void com.ss.bytertc.engine.ISingScoringEventHandler.onCurrentScoringInfo(SingScoringRealtimeInfo info)
```
实时评分信息回调。调用 [startSingScoring](Android-api.md#ISingScoringManager-startsingscoring) 后，会收到该回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| info | SingScoringRealtimeInfo | 实时评分信息。详见 [SingScoringRealtimeInfo](Android-keytype.md#SingScoringRealtimeInfo)。 |



<span id="IFaceDetectionObserver"></span>
# IFaceDetectionObserver
```java
public interface com.ss.bytertc.engine.video.IFaceDetectionObserver
```
人脸检测结果回调观察者

注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| void | [onFaceDetectResult](#IFaceDetectionObserver-onfacedetectresult) |


## 函数说明
<span id="IFaceDetectionObserver-onfacedetectresult"></span>
### onFaceDetectResult
```java
void com.ss.bytertc.engine.video.IFaceDetectionObserver.onFaceDetectResult(FaceDetectionResult result)
```
特效 SDK 进行人脸检测结果的回调。

调用 [enableFaceDetection](Android-api.md#IVideoEffect-enablefacedetection) 注册了 [IFaceDetectionObserver](#IFaceDetectionObserver)，并使用 RTC SDK 中包含的特效 SDK 进行视频特效处理时，你会收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| result | FaceDetectionResult | 人脸检测结果, 参看 [FaceDetectionResult](Android-keytype.md#FaceDetectionResult)。 |



<span id="IMixedStreamObserver"></span>
# IMixedStreamObserver
```java
public interface com.ss.bytertc.engine.live.IMixedStreamObserver
```
转推直播观察者。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| boolean | [isSupportClientPushStream](#IMixedStreamObserver-issupportclientpushstream) |
| void | [onMixingEvent](#IMixedStreamObserver-onmixingevent) |
| void | [onMixingAudioFrame](#IMixedStreamObserver-onmixingaudioframe) |
| void | [onMixingVideoFrame](#IMixedStreamObserver-onmixingvideoframe) |
| void | [onMixingDataFrame](#IMixedStreamObserver-onmixingdataframe) |


## 函数说明
<span id="IMixedStreamObserver-issupportclientpushstream"></span>
### isSupportClientPushStream
```java
boolean com.ss.bytertc.engine.live.IMixedStreamObserver.isSupportClientPushStream()
```
是否具有推流能力。

- false：不具备推流能力（默认值）
- true：具备推流能力


**注意**

- 如果需要开启端云一体转推直播功能，你必须确保你的 App 包含 librtmp，具有推流能力。此时，设置该回调为 true。

<span id="IMixedStreamObserver-onmixingevent"></span>
### onMixingEvent
```java
void com.ss.bytertc.engine.live.IMixedStreamObserver.onMixingEvent(
    ByteRTCStreamMixingEvent eventType,
    String taskId,
    ByteRTCTranscoderErrorCode error,
    MixedStreamType mixType
)
```
转推直播状态回调


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| eventType | ByteRTCStreamMixingEvent | 转推直播任务状态, 参看 [ByteRTCStreamMixingEvent](Android-keytype.md#ByteRTCStreamMixingEvent) |
| taskId | String | 转推直播任务 ID |
| error | ByteRTCTranscoderErrorCode | 转推直播错误码，参看 [ByteRTCTranscoderErrorCode](Android-errorcode.md#ByteRTCTranscoderErrorCode) |
| mixType | MixedStreamType | 转推直播类型，参看 [MixedStreamType](Android-keytype.md#MixedStreamType) |



<span id="IMixedStreamObserver-onmixingaudioframe"></span>
### onMixingAudioFrame
```java
void com.ss.bytertc.engine.live.IMixedStreamObserver.onMixingAudioFrame(
    String taskId,
    byte[] audioFrame,
    int frameNum,
    long timeStampMs
)
```
端云一体合流音频 PCM 回调


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| taskId | String | 转推直播任务 ID |
| audioFrame | byte[] | PCM 编码的合流音频数据帧 |
| frameNum | int | PCM 编码的音频数据帧数 |
| timeStampMs | long | 时间戳，单位毫秒 |



**注意**

收到该回调的周期为每 10 毫秒一次，并且每次的音频数据量为 10 毫秒数据量。

<span id="IMixedStreamObserver-onmixingvideoframe"></span>
### onMixingVideoFrame
```java
void com.ss.bytertc.engine.live.IMixedStreamObserver.onMixingVideoFrame(
    String taskId,
    VideoFrame videoFrame
)
```
端云一体合流视频 YUV 回调


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| taskId | String | 转推直播任务 ID |
| videoFrame | VideoFrame | YUV 合流视频数据帧，参看 [VideoFrame](Android-keytype.md#VideoFrame) |



**注意**

- 收到该回调的周期与视频的帧间隔一致。
- 为避免内存泄露，你应在回调中手动释放视频帧： ``` public void onMixingVideoFrame(String taskId, VideoFrame videoFrame){ videoFrame.release() } ```

<span id="IMixedStreamObserver-onmixingdataframe"></span>
### onMixingDataFrame
```java
void com.ss.bytertc.engine.live.IMixedStreamObserver.onMixingDataFrame(
    String taskId,
    byte[] dataFrame,
    long time
)
```
端云一体合流视频 SEI 数据回调


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| taskId | String | 转推直播任务 ID |
| dataFrame | byte[] | SEI 数据 |
| time | long | 时间信息 |



<span id="IMediaPlayerAudioFrameObserver"></span>
# IMediaPlayerAudioFrameObserver
```java
public interface com.ss.bytertc.engine.IMediaPlayerAudioFrameObserver
```
本地音频文件混音的音频帧观察者。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| void | [onFrame](#IMediaPlayerAudioFrameObserver-onframe) |


## 函数说明
<span id="IMediaPlayerAudioFrameObserver-onframe"></span>
### onFrame
```java
void com.ss.bytertc.engine.IMediaPlayerAudioFrameObserver.onFrame(
    int playerId,
    IAudioFrame frame
)
```
当本地音频文件混音时，回调播放的音频帧。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| playerId | int | - |
| frame | IAudioFrame | 参看 [IAudioFrame](Android-keytype.md#IAudioFrame)。 |



<span id="IAudioFileFrameObserver"></span>
# IAudioFileFrameObserver
```java
public interface com.ss.bytertc.engine.IAudioFileFrameObserver
```
本地音频文件混音的音频帧观察者。

注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| void | [onAudioFileFrame](#IAudioFileFrameObserver-onaudiofileframe) |


## 函数说明
<span id="IAudioFileFrameObserver-onaudiofileframe"></span>
### onAudioFileFrame
```java
void com.ss.bytertc.engine.IAudioFileFrameObserver.onAudioFileFrame(
    int mixID,
    IAudioFrame audioFrame
)
```
当本地音频文件混音时，回调播放的音频帧。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mixID | int | 混音 ID。 |
| audioFrame | IAudioFrame | 参看 [IAudioFrame](Android-keytype.md#IAudioFrame)。 |



<span id="ILiveTranscodingObserver"></span>
# ILiveTranscodingObserver
```java
public interface com.ss.bytertc.engine.live.ILiveTranscodingObserver
```
转推直播观察者。

注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| boolean | [isSupportClientPushStream](#ILiveTranscodingObserver-issupportclientpushstream) |
| void | [onStreamMixingEvent](#ILiveTranscodingObserver-onstreammixingevent) |
| void | [onMixingAudioFrame](#ILiveTranscodingObserver-onmixingaudioframe) |
| void | [onMixingVideoFrame](#ILiveTranscodingObserver-onmixingvideoframe) |
| void | [onMixingDataFrame](#ILiveTranscodingObserver-onmixingdataframe) |


## 函数说明
<span id="ILiveTranscodingObserver-issupportclientpushstream"></span>
### isSupportClientPushStream
```java
boolean com.ss.bytertc.engine.live.ILiveTranscodingObserver.isSupportClientPushStream()
```
是否具有推流能力。

- false：不具备推流能力（默认值）
- true：具备推流能力


**注意**

如果需要开启端云一体转推直播功能，你必须确保你的 App 包含 librtmp，具有推流能力。此时，设置该回调为 true。

<span id="ILiveTranscodingObserver-onstreammixingevent"></span>
### onStreamMixingEvent
```java
void com.ss.bytertc.engine.live.ILiveTranscodingObserver.onStreamMixingEvent(
    ByteRTCStreamMixingEvent eventType,
    String taskId,
    ByteRTCTranscoderErrorCode error,
    ByteRTCStreamMixingType mixType
)
```
转推直播状态回调


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| eventType | ByteRTCStreamMixingEvent | 转推直播任务状态, 参看 [ByteRTCStreamMixingEvent](Android-keytype.md#ByteRTCStreamMixingEvent) |
| taskId | String | 转推直播任务 ID |
| error | ByteRTCTranscoderErrorCode | 转推直播错误码，参看 [ByteRTCTranscoderErrorCode](Android-errorcode.md#ByteRTCTranscoderErrorCode) |
| mixType | ByteRTCStreamMixingType | 转推直播类型，参看 [ByteRTCStreamMixingType](Android-keytype.md#ByteRTCStreamMixingType) |



<span id="ILiveTranscodingObserver-onmixingaudioframe"></span>
### onMixingAudioFrame
```java
void com.ss.bytertc.engine.live.ILiveTranscodingObserver.onMixingAudioFrame(
    String taskId,
    byte[] audioFrame,
    int frameNum,
    long timeStampMs
)
```
端云一体合流音频 PCM 回调


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| taskId | String | 转推直播任务 ID |
| audioFrame | byte[] | PCM 编码的合流音频数据帧 |
| frameNum | int | PCM 编码的音频数据帧数 |
| timeStampMs | long | 时间戳，单位毫秒 |



**注意**

收到该回调的周期为每 10 毫秒一次，并且每次的音频数据量为 10 毫秒数据量。

<span id="ILiveTranscodingObserver-onmixingvideoframe"></span>
### onMixingVideoFrame
```java
void com.ss.bytertc.engine.live.ILiveTranscodingObserver.onMixingVideoFrame(
    String taskId,
    VideoFrame videoFrame
)
```
端云一体合流视频 YUV 回调


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| taskId | String | 转推直播任务 ID |
| videoFrame | VideoFrame | YUV 合流视频数据帧，参看 [VideoFrame](Android-keytype.md#VideoFrame) |



**注意**

- 收到该回调的周期与视频的帧间隔一致。
- 为避免内存泄露，你应在回调中手动释放视频帧： ``` public void onMixingVideoFrame(String taskId, VideoFrame videoFrame){ videoFrame.release() } ```

<span id="ILiveTranscodingObserver-onmixingdataframe"></span>
### onMixingDataFrame
```java
void com.ss.bytertc.engine.live.ILiveTranscodingObserver.onMixingDataFrame(
    String taskId,
    byte[] dataFrame,
    long time
)
```
端云一体合流视频 SEI 数据回调


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| taskId | String | 转推直播任务 ID |
| dataFrame | byte[] | SEI 数据 |
| time | long | 时间信息 |



<span id="IRTCASREngineEventHandler"></span>
# IRTCASREngineEventHandler
```java
public interface com.ss.bytertc.engine.handler.IRTCASREngineEventHandler
```
语音识别服务使用状态回调

注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| void | [onSuccess](#IRTCASREngineEventHandler-onsuccess) |
| void | [onMessage](#IRTCASREngineEventHandler-onmessage) |
| void | [onError](#IRTCASREngineEventHandler-onerror) |


## 函数说明
<span id="IRTCASREngineEventHandler-onsuccess"></span>
### onSuccess
```java
void com.ss.bytertc.engine.handler.IRTCASREngineEventHandler.onSuccess()
```
语音识别服务开启成功回调


<span id="IRTCASREngineEventHandler-onmessage"></span>
### onMessage
```java
void com.ss.bytertc.engine.handler.IRTCASREngineEventHandler.onMessage(String message)
```
语音转文字成功后回调，该回调返回识别后的全量消息。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| message | String | 识别完成后得到的文字消息 |



**注意**

若识别过程中发生了网络连接中断，则重连后回调的信息中只包含重连后识别的文字消息，不再包含上一次连接后识别的消息。

<span id="IRTCASREngineEventHandler-onerror"></span>
### onError
```java
void com.ss.bytertc.engine.handler.IRTCASREngineEventHandler.onError(
    int errorCode,
    String errorMessage
)
```
当语音识别服务内部发生错误事件时触发该回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| errorCode | int | 错误码<br><ul><li>< 0: 参数错误或 API 调用顺序错误，参看 [RTCASRErrorCode](Android-keytype.md#RTCASRErrorCode)；</li><li>>0: 参看 [语音识别服务错误码](https://www.volcengine.com/docs/6561/80818#_3-3-%E9%94%99%E8%AF%AF%E7%A0%81)</li></ul> |
| errorMessage | String | 错误原因说明。 |



<span id="ILocalEncodedVideoFrameObserver"></span>
# ILocalEncodedVideoFrameObserver
```java
public interface com.ss.bytertc.engine.mediaio.ILocalEncodedVideoFrameObserver
```
本地视频帧监测器

注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| void | [onLocalEncodedVideoFrame](#ILocalEncodedVideoFrameObserver-onlocalencodedvideoframe) |


## 函数说明
<span id="ILocalEncodedVideoFrameObserver-onlocalencodedvideoframe"></span>
### onLocalEncodedVideoFrame
```java
void com.ss.bytertc.engine.mediaio.ILocalEncodedVideoFrameObserver.onLocalEncodedVideoFrame(
    StreamIndex streamIndex,
    RTCEncodedVideoFrame encodedVideoFrame
)
```
调用 [registerLocalEncodedVideoFrameObserver](Android-api.md#RTCVideo-registerlocalencodedvideoframeobserver) 后，SDK 每次使用内部采集，采集到一帧视频帧，或收到一帧外部视频帧时，都会回调该事件。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamIndex | StreamIndex | 本地视频帧类型，参看 [StreamIndex](Android-keytype.md#StreamIndex-2) |
| encodedVideoFrame | RTCEncodedVideoFrame | 本地视频帧信息，参看 [RTCEncodedVideoFrame](Android-keytype.md#RTCEncodedVideoFrame) |



**注意**

encodedVideoFrame 只在回调函数作用域内有效，不要存储该参数并在其它函数内访问该参数的内存数据

<span id="IExternalVideoEncoderEventHandler"></span>
# IExternalVideoEncoderEventHandler
```java
public abstract class com.ss.bytertc.engine.handler.IExternalVideoEncoderEventHandler
```
自定义编码帧回调类

注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| abstract void | [onStart](#IExternalVideoEncoderEventHandler-onstart) |
| abstract void | [onStop](#IExternalVideoEncoderEventHandler-onstop) |
| abstract void | [onRateUpdate](#IExternalVideoEncoderEventHandler-onrateupdate) |
| abstract void | [onRequestKeyFrame](#IExternalVideoEncoderEventHandler-onrequestkeyframe) |
| abstract void | [onActiveVideoLayer](#IExternalVideoEncoderEventHandler-onactivevideolayer) |


## 函数说明
<span id="IExternalVideoEncoderEventHandler-onstart"></span>
### onStart
```java
abstract void com.ss.bytertc.engine.handler.IExternalVideoEncoderEventHandler.onStart(StreamIndex index)
```
提示自定义编码帧可以开始推送的回调。

收到该回调后，你即可调用 [pushExternalEncodedVideoFrame](Android-api.md#RTCVideo-pushexternalencodedvideoframe) 向 SDK 推送自定义编码视频帧


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| index | StreamIndex | 可以推送的编码流的属性，参看 [StreamIndex](Android-keytype.md#streamindex-2) |



<span id="IExternalVideoEncoderEventHandler-onstop"></span>
### onStop
```java
abstract void com.ss.bytertc.engine.handler.IExternalVideoEncoderEventHandler.onStop(StreamIndex index)
```
当收到该回调时，你需停止向 SDK 推送自定义编码视频帧


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| index | StreamIndex | 需停止推送的编码流的属性，参看 [StreamIndex](Android-keytype.md#streamindex-2) |



<span id="IExternalVideoEncoderEventHandler-onrateupdate"></span>
### onRateUpdate
```java
abstract void com.ss.bytertc.engine.handler.IExternalVideoEncoderEventHandler.onRateUpdate(
    StreamIndex streamIndex,
    int videoIndex,
    int fps,
    int bitrateKbps
)
```
当自定义编码流的帧率或码率发生变化时，触发该回调


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamIndex | StreamIndex | 发生变化的编码流的属性，参看 [StreamIndex](Android-keytype.md#streamindex-2) |
| videoIndex | int | 对应编码流的下标 |
| fps | int | 变化后的帧率，单位：fps |
| bitrateKbps | int | 变化后的码率，单位：kbps |



<span id="IExternalVideoEncoderEventHandler-onrequestkeyframe"></span>
### onRequestKeyFrame
```java
abstract void com.ss.bytertc.engine.handler.IExternalVideoEncoderEventHandler.onRequestKeyFrame(
    StreamIndex streamIndex,
    int videoIndex
)
```
提示流发布端需重新生成关键帧的回调


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamIndex | StreamIndex | 远端编码流的属性，参看 [StreamIndex](Android-keytype.md#streamindex-2) |
| videoIndex | int | 对应编码流的下标 |



<span id="IExternalVideoEncoderEventHandler-onactivevideolayer"></span>
### onActiveVideoLayer
```java
abstract void com.ss.bytertc.engine.handler.IExternalVideoEncoderEventHandler.onActiveVideoLayer(
    StreamIndex streamIndex,
    int videoIndex,
    boolean active
)
```
> Available since 3.56

作为自定义编码视频流的发送端，你会在视频流可发送状态发生变化时，收到此回调。

你可以根据此回调的提示，仅对可发送的视频流进行编码，以降低本端视频编码性能消耗。此回调会根据多个因素综合判断触发，包括：本端设备性能和本端网络性能，以及按需订阅场景下，远端用户是否订阅。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamIndex | StreamIndex | 远端编码流的属性，参看 [StreamIndex](Android-keytype.md#streamindex-2) |
| videoIndex | int | 对应编码流的下标 |
| active | boolean | 该路流可发送状态 |



**注意**

要收到此回调，必须调用 [setVideoSourceType](Android-api.md#RTCVideo-setvideosourcetype) 设置视频源是自定义编码，且通过 [setExternalVideoEncoderEventHandler](Android-api.md#RTCVideo-setexternalvideoencodereventhandler) 设置了回调句柄。

<span id="IMediaPlayerEventHandler"></span>
# IMediaPlayerEventHandler
```java
public interface com.ss.bytertc.engine.IMediaPlayerEventHandler
```
[IMediaPlayer](Android-api.md#IMediaPlayer) 对应的回调句柄。你必须调用 [setEventHandler](Android-api.md#IMediaPlayer-seteventhandler) 完成设置后，才能收到对应回调。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| void | [onMediaPlayerStateChanged](#IMediaPlayerEventHandler-onmediaplayerstatechanged) |
| void | [onMediaPlayerPlayingProgress](#IMediaPlayerEventHandler-onmediaplayerplayingprogress) |


## 函数说明
<span id="IMediaPlayerEventHandler-onmediaplayerstatechanged"></span>
### onMediaPlayerStateChanged
```java
void com.ss.bytertc.engine.IMediaPlayerEventHandler.onMediaPlayerStateChanged(
    int playerId,
    PlayerState state,
    PlayerError error
)
```
播放状态改变时回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| playerId | int | [IMediaPlayer](Android-api.md#IMediaPlayer) 的 ID。通过 [getMediaPlayer](Android-api.md#RTCVideo-getmediaplayer) 设置。 |
| state | PlayerState | 混音状态。参考 [PlayerState](Android-keytype.md#PlayerState)。 |
| error | PlayerError | 错误码。参考 [PlayerError](Android-keytype.md#PlayerError)。 |



<span id="IMediaPlayerEventHandler-onmediaplayerplayingprogress"></span>
### onMediaPlayerPlayingProgress
```java
void com.ss.bytertc.engine.IMediaPlayerEventHandler.onMediaPlayerPlayingProgress(
    int playerId,
    long progress
)
```
播放进度周期性回调。回调周期通过 [setProgressInterval](Android-api.md#IMediaPlayer-setprogressinterval) 设置。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| playerId | int | [IMediaPlayer](Android-api.md#IMediaPlayer) 的 ID。通过 [getMediaPlayer](Android-api.md#RTCVideo-getmediaplayer) 设置。 |
| progress | long | 进度。单位 ms。 |



<span id="IAudioFrameObserver"></span>
# IAudioFrameObserver
```java
public interface com.ss.bytertc.engine.IAudioFrameObserver
```
音频数据回调观察者

注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。

本接口类中的单个回调的数据量为 20 ms 的数据量。回调周期在 20 ms 上下浮动。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| void | [onRecordAudioFrame](#IAudioFrameObserver-onrecordaudioframe) |
| void | [onPlaybackAudioFrame](#IAudioFrameObserver-onplaybackaudioframe) |
| void | [onRemoteUserAudioFrame](#IAudioFrameObserver-onremoteuseraudioframe) |
| void | [onMixedAudioFrame](#IAudioFrameObserver-onmixedaudioframe) |


## 函数说明
<span id="IAudioFrameObserver-onrecordaudioframe"></span>
### onRecordAudioFrame
```java
void com.ss.bytertc.engine.IAudioFrameObserver.onRecordAudioFrame(IAudioFrame audioFrame)
```
返回麦克风录制的音频数据


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioFrame | IAudioFrame | 音频数据, 参看 [IAudioFrame](Android-keytype.md#IAudioFrame)。 |



<span id="IAudioFrameObserver-onplaybackaudioframe"></span>
### onPlaybackAudioFrame
```java
void com.ss.bytertc.engine.IAudioFrameObserver.onPlaybackAudioFrame(IAudioFrame audioFrame)
```
返回订阅的所有远端用户混音后的音频数据。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioFrame | IAudioFrame | 音频数据, 参看 [IAudioFrame](Android-keytype.md#IAudioFrame)。 |



<span id="IAudioFrameObserver-onremoteuseraudioframe"></span>
### onRemoteUserAudioFrame
```java
void com.ss.bytertc.engine.IAudioFrameObserver.onRemoteUserAudioFrame(
    RemoteStreamKey streamKey,
    IAudioFrame audioFrame
)
```
返回远端单个用户的音频数据


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamKey | RemoteStreamKey | 远端流信息，参看 [RemoteStreamKey](Android-keytype.md#RemoteStreamKey)。 |
| audioFrame | IAudioFrame | 音频数据，参看 [IAudioFrame](Android-keytype.md#IAudioFrame)。 |



**注意**

此回调在播放线程调用。不要在此回调中做任何耗时的事情，否则可能会影响整个音频播放链路。

<span id="IAudioFrameObserver-onmixedaudioframe"></span>
### onMixedAudioFrame
```java
void com.ss.bytertc.engine.IAudioFrameObserver.onMixedAudioFrame(IAudioFrame audioFrame)
```
返回本地麦克风录制和订阅的所有远端用户混音后的音频数据


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioFrame | IAudioFrame | 音频数据, 参看 [IAudioFrame](Android-keytype.md#IAudioFrame)。 |



<span id="IRTCEncryptionHandler"></span>
# IRTCEncryptionHandler
```java
public interface com.ss.bytertc.engine.handler.IRTCEncryptionHandler
```
加密事件回调接口

注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| byte[] | [onEncryptData](#IRTCEncryptionHandler-onencryptdata) |
| byte[] | [onDecryptData](#IRTCEncryptionHandler-ondecryptdata) |


## 函数说明
<span id="IRTCEncryptionHandler-onencryptdata"></span>
### onEncryptData
```java
byte[] com.ss.bytertc.engine.handler.IRTCEncryptionHandler.onEncryptData(byte[] data)
```
自定义加密。

使用设定的自定义加密方式，对编码后传输前的音视频帧数据进行加密。

暂不支持对原始音视频帧进行加密。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| data | byte[] | 未加密的数据。 |



**返回值**

加密后的数据


<span id="IRTCEncryptionHandler-ondecryptdata"></span>
### onDecryptData
```java
byte[] com.ss.bytertc.engine.handler.IRTCEncryptionHandler.onDecryptData(byte[] data)
```
自定义解密。

对自定义加密后的音视频帧数据进行解密。关于自定义加密，参看 [onEncryptData](#IRTCEncryptionHandler-onencryptdata)。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| data | byte[] | 加密过的数据。 |



**返回值**

解密后的数据


<span id="IMediaPlayerCustomSourceProvider"></span>
# IMediaPlayerCustomSourceProvider
```java
public interface com.ss.bytertc.engine.IMediaPlayerCustomSourceProvider
```
内存播放数据源回调


## 成员函数

| 返回 | 名称 |
| --- | --- |
| int | [onReadData](#IMediaPlayerCustomSourceProvider-onreaddata) |
| long | [onSeek](#IMediaPlayerCustomSourceProvider-onseek) |


## 函数说明
<span id="IMediaPlayerCustomSourceProvider-onreaddata"></span>
### onReadData
```java
int com.ss.bytertc.engine.IMediaPlayerCustomSourceProvider.onReadData(
    ByteBuffer buffer,
    int bufferSize
)
```
> Available since 3.53

调用 [openWithCustomSource](Android-api.md#IMediaPlayer-openwithcustomsource) 接口播放用户传入的内存音频数据时，会触发此回调，用户需要写入音频数据。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| buffer | ByteBuffer | 内存地址。在该地址中写入音频数据，写入音频数据的大小不超过 bufferSize 中填入的数值。支持的音频数据格式有: mp3，aac，m4a，3gp，wav。 |
| bufferSize | int | 音频数据大小，单位为字节。如果你想停止播放内存音频数据，可在 bufferSize 中填入小于或等于 0 的数，此时 SDK 会停止调用此接口。 |



**返回值**

返回实际读取的音频数据大小。


**注意**

若 [openWithCustomSource](Android-api.md#IMediaPlayer-openwithcustomsource) 接口调用失败，请在 buffer 和 bufferSize 两个参数中填入 0。 此时 SDK 会停止调用此接口。

<span id="IMediaPlayerCustomSourceProvider-onseek"></span>
### onSeek
```java
long com.ss.bytertc.engine.IMediaPlayerCustomSourceProvider.onSeek(
    long offset,
    MediaPlayerCustomSourceSeekWhence whence
)
```
> Available since 3.53

根据设置好的内存音频数据的读取位置和读取偏移量对音频数据进行偏移，以便 SDK 读取和分析音频数据。

在调用 [openWithCustomSource](Android-api.md#IMediaPlayer-openwithcustomsource) 接口传入内存音频数据，或者调用 [setPosition](Android-api.md#IMediaPlayer-setposition) 设置了音频数据的起始播放位置后，SDK 会对音频数据进行读取和分析，此时会触发该回调，你需要根据参数中设置的起始读取位置和偏移量进行操作。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| offset | long | 音频数据读取偏移量，单位为字节，取值可正可负。 |
| whence | MediaPlayerCustomSourceSeekWhence | 音频数据的起始读取位置。参看 [MediaPlayerCustomSourceSeekWhence](Android-keytype.md#MediaPlayerCustomSourceSeekWhence) |



**返回值**

定位成功，返回偏移后的位置信息，或返回音频数据的大小。

定位失败，返回 -1。


<span id="IRTCVideoEventHandler"></span>
# IRTCVideoEventHandler
```java
public abstract class com.ss.bytertc.engine.handler.IRTCVideoEventHandler
```
音视频引擎事件回调接口

注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| void | [onWarning](#IRTCVideoEventHandler-onwarning) |
| void | [onError](#IRTCVideoEventHandler-onerror) |
| void | [onDeadLockError](#IRTCVideoEventHandler-ondeadlockerror) |
| void | [onExtensionAccessError](#IRTCVideoEventHandler-onextensionaccesserror) |
| void | [onSysStats](#IRTCVideoEventHandler-onsysstats) |
| void | [onNetworkTypeChanged](#IRTCVideoEventHandler-onnetworktypechanged) |
| void | [onUserStartVideoCapture](#IRTCVideoEventHandler-onuserstartvideocapture) |
| void | [onUserStopVideoCapture](#IRTCVideoEventHandler-onuserstopvideocapture) |
| void | [onCreateRoomStateChanged](#IRTCVideoEventHandler-oncreateroomstatechanged) |
| void | [onUserStartAudioCapture](#IRTCVideoEventHandler-onuserstartaudiocapture) |
| void | [onUserStopAudioCapture](#IRTCVideoEventHandler-onuserstopaudiocapture) |
| void | [onLocalAudioStateChanged](#IRTCVideoEventHandler-onlocalaudiostatechanged) |
| void | [onRemoteAudioStateChanged](#IRTCVideoEventHandler-onremoteaudiostatechanged) |
| void | [onLocalVideoStateChanged](#IRTCVideoEventHandler-onlocalvideostatechanged) |
| void | [onRemoteVideoStateChanged](#IRTCVideoEventHandler-onremotevideostatechanged) |
| void | [onFirstRemoteVideoFrameRendered](#IRTCVideoEventHandler-onfirstremotevideoframerendered) |
| void | [onFirstRemoteVideoFrameDecoded](#IRTCVideoEventHandler-onfirstremotevideoframedecoded) |
| void | [onFirstLocalVideoFrameCaptured](#IRTCVideoEventHandler-onfirstlocalvideoframecaptured) |
| void | [onLocalVideoSizeChanged](#IRTCVideoEventHandler-onlocalvideosizechanged) |
| void | [onRemoteVideoSizeChanged](#IRTCVideoEventHandler-onremotevideosizechanged) |
| void | [onConnectionStateChanged](#IRTCVideoEventHandler-onconnectionstatechanged) |
| void | [onAudioRouteChanged](#IRTCVideoEventHandler-onaudioroutechanged) |
| void | [onFirstLocalAudioFrame](#IRTCVideoEventHandler-onfirstlocalaudioframe) |
| void | [onFirstRemoteAudioFrame](#IRTCVideoEventHandler-onfirstremoteaudioframe) |
| void | [onLogReport](#IRTCVideoEventHandler-onlogreport) |
| void | [onSEIMessageReceived](#IRTCVideoEventHandler-onseimessagereceived) |
| void | [onSEIStreamUpdate](#IRTCVideoEventHandler-onseistreamupdate) |
| void | [onLoginResult](#IRTCVideoEventHandler-onloginresult) |
| void | [onLogout](#IRTCVideoEventHandler-onlogout) |
| void | [onServerParamsSetResult](#IRTCVideoEventHandler-onserverparamssetresult) |
| void | [onGetPeerOnlineStatus](#IRTCVideoEventHandler-ongetpeeronlinestatus) |
| void | [onUserMessageReceivedOutsideRoom](#IRTCVideoEventHandler-onusermessagereceivedoutsideroom) |
| void | [onUserBinaryMessageReceivedOutsideRoom](#IRTCVideoEventHandler-onuserbinarymessagereceivedoutsideroom) |
| void | [onUserMessageSendResultOutsideRoom](#IRTCVideoEventHandler-onusermessagesendresultoutsideroom) |
| void | [onServerMessageSendResult](#IRTCVideoEventHandler-onservermessagesendresult) |
| void | [onNetworkDetectionResult](#IRTCVideoEventHandler-onnetworkdetectionresult) |
| void | [onNetworkDetectionStopped](#IRTCVideoEventHandler-onnetworkdetectionstopped) |
| void | [onSimulcastSubscribeFallback](#IRTCVideoEventHandler-onsimulcastsubscribefallback) |
| void | [onPerformanceAlarms](#IRTCVideoEventHandler-onperformancealarms) |
| void | [onAudioFrameSendStateChanged](#IRTCVideoEventHandler-onaudioframesendstatechanged) |
| void | [onVideoFrameSendStateChanged](#IRTCVideoEventHandler-onvideoframesendstatechanged) |
| void | [onScreenVideoFrameSendStateChanged](#IRTCVideoEventHandler-onscreenvideoframesendstatechanged) |
| void | [onAudioFramePlayStateChanged](#IRTCVideoEventHandler-onaudioframeplaystatechanged) |
| void | [onVideoFramePlayStateChanged](#IRTCVideoEventHandler-onvideoframeplaystatechanged) |
| void | [onScreenVideoFramePlayStateChanged](#IRTCVideoEventHandler-onscreenvideoframeplaystatechanged) |
| void | [onAudioDeviceStateChanged](#IRTCVideoEventHandler-onaudiodevicestatechanged) |
| void | [onVideoDeviceStateChanged](#IRTCVideoEventHandler-onvideodevicestatechanged) |
| void | [onAudioDeviceWarning](#IRTCVideoEventHandler-onaudiodevicewarning) |
| void | [onVideoDeviceWarning](#IRTCVideoEventHandler-onvideodevicewarning) |
| void | [onRecordingStateUpdate](#IRTCVideoEventHandler-onrecordingstateupdate) |
| void | [onRecordingProgressUpdate](#IRTCVideoEventHandler-onrecordingprogressupdate) |
| void | [onAudioRecordingStateUpdate](#IRTCVideoEventHandler-onaudiorecordingstateupdate) |
| void | [onAudioMixingPlayingProgress](#IRTCVideoEventHandler-onaudiomixingplayingprogress) |
| void | [onLocalAudioPropertiesReport](#IRTCVideoEventHandler-onlocalaudiopropertiesreport) |
| void | [onAudioPlaybackDeviceTestVolume](#IRTCVideoEventHandler-onaudioplaybackdevicetestvolume) |
| void | [onRemoteAudioPropertiesReport](#IRTCVideoEventHandler-onremoteaudiopropertiesreport) |
| void | [onActiveSpeaker](#IRTCVideoEventHandler-onactivespeaker) |
| void | [onStreamSyncInfoReceived](#IRTCVideoEventHandler-onstreamsyncinforeceived) |
| void | [onPushPublicStreamResult](#IRTCVideoEventHandler-onpushpublicstreamresult) |
| void | [onPlayPublicStreamResult](#IRTCVideoEventHandler-onplaypublicstreamresult) |
| void | [onPublicStreamSEIMessageReceived](#IRTCVideoEventHandler-onpublicstreamseimessagereceived) |
| void | [onPublicStreamDataMessageReceived](#IRTCVideoEventHandler-onpublicstreamdatamessagereceived) |
| void | [onFirstPublicStreamVideoFrameDecoded](#IRTCVideoEventHandler-onfirstpublicstreamvideoframedecoded) |
| void | [onFirstPublicStreamAudioFrame](#IRTCVideoEventHandler-onfirstpublicstreamaudioframe) |
| void | [onEchoTestResult](#IRTCVideoEventHandler-onechotestresult) |
| void | [onCloudProxyConnected](#IRTCVideoEventHandler-oncloudproxyconnected) |
| void | [onNetworkTimeSynchronized](#IRTCVideoEventHandler-onnetworktimesynchronized) |
| void | [onHardwareEchoDetectionResult](#IRTCVideoEventHandler-onhardwareechodetectionresult) |
| void | [onLocalProxyStateChanged](#IRTCVideoEventHandler-onlocalproxystatechanged) |
| void | [onExternalScreenFrameUpdate](#IRTCVideoEventHandler-onexternalscreenframeupdate) |
| void | [deprecated] [onUserMuteAudio](#IRTCVideoEventHandler-onusermuteaudio) |
| void | [deprecated] [onUserMuteVideo](#IRTCVideoEventHandler-onusermutevideo) |
| void | [deprecated] [onAudioPlaybackDeviceChanged](#IRTCVideoEventHandler-onaudioplaybackdevicechanged) |
| void | [deprecated] [onMediaDeviceStateChanged](#IRTCVideoEventHandler-onmediadevicestatechanged) |
| void | [deprecated] [onMediaDeviceWarning](#IRTCVideoEventHandler-onmediadevicewarning) |
| void | [deprecated] [onHttpProxyState](#IRTCVideoEventHandler-onhttpproxystate) |
| void | [deprecated] [onHttpsProxyState](#IRTCVideoEventHandler-onhttpsproxystate) |
| void | [deprecated] [onSocks5ProxyState](#IRTCVideoEventHandler-onsocks5proxystate) |
| void | [deprecated] [onAudioMixingStateChanged](#IRTCVideoEventHandler-onaudiomixingstatechanged) |


## 函数说明
<span id="IRTCVideoEventHandler-onwarning"></span>
### onWarning
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onWarning(int warn)
```
发生警告回调。

SDK 运行时出现了警告。SDK 通常会自动恢复，警告信息可以忽略。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| warn | int | 警告代码，参见 [WarningCode](Android-errorcode.md#WarningCode) |



<span id="IRTCVideoEventHandler-onerror"></span>
### onError
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onError(int err)
```
发生错误回调。

SDK 运行时出现了网络或媒体相关的错误，且无法自动恢复时触发此回调。

你可能需要干预.


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| err | int | 错误代码，详情定义见: [ErrorCode](Android-errorcode.md#ErrorCode) |



<span id="IRTCVideoEventHandler-ondeadlockerror"></span>
### onDeadLockError
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onDeadLockError(DeadLockMsg deadLockMsg)
```
当 RTC 内部线程发生 block 时，会触发回调。线程名与持续次数


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| deadLockMsg | DeadLockMsg | 错误消息 |



<span id="IRTCVideoEventHandler-onextensionaccesserror"></span>
### onExtensionAccessError
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onExtensionAccessError(
    String extensionName,
    String msg
)
```
> Available since 3.52

当访问插件失败时，收到此回调。

RTC SDK 将一些功能封装成插件。当使用这些功能时，如果插件不存在，功能将无法使用。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| extensionName | String | 插件名字 |
| msg | String | 失败说明 |



<span id="IRTCVideoEventHandler-onsysstats"></span>
### onSysStats
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onSysStats(SysStats stats)
```
每 2 秒发生回调，通知当前 cpu，内存使用的信息。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stats | SysStats | cpu，内存信息。详见 [SysStats](Android-keytype.md#SysStats) 数据类型。 |



<span id="IRTCVideoEventHandler-onnetworktypechanged"></span>
### onNetworkTypeChanged
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onNetworkTypeChanged(int type)
```
SDK 当前网络连接类型改变回调。当 SDK 的当前网络连接类型发生改变时回调该事件。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| type | int | <br>网络类型。<br><ul><li>-1： 网络连接类型未知。</li><li>0： 网络连接已断开。</li><li>1： LAN</li><li>2： Wi-Fi,包含热点</li><li>3： 2G 移动网络</li><li>4： 3G 移动网络</li><li>5： 4G 移动网络</li><li>6： 5G 移动网络</li></ul> |



<span id="IRTCVideoEventHandler-onuserstartvideocapture"></span>
### onUserStartVideoCapture
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onUserStartVideoCapture(
    String roomId,
    String uid
)
```
房间内的可见用户调用 [startVideoCapture](Android-api.md#RTCVideo-startvideocapture) 开启内部视频采集时，房间内其他用户会收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| roomId | String | 开启视频采集的远端用户所在的房间 ID |
| uid | String | 开启视频采集的远端用户 ID |



<span id="IRTCVideoEventHandler-onuserstopvideocapture"></span>
### onUserStopVideoCapture
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onUserStopVideoCapture(
    String roomId,
    String uid
)
```
房间内的可见用户调用 [stopVideoCapture](Android-api.md#RTCVideo-stopvideocapture) 关闭内部视频采集时，房间内其他用户会收到此回调。

若发布视频数据前未开启采集，房间内所有可见用户会收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| roomId | String | 关闭视频采集的远端用户所在的房间 ID |
| uid | String | 关闭视频采集的远端用户 ID |



<span id="IRTCVideoEventHandler-oncreateroomstatechanged"></span>
### onCreateRoomStateChanged
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onCreateRoomStateChanged(
    String roomId,
    int errorCode
)
```
创建房间失败回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| roomId | String | 房间 ID。 |
| errorCode | int | 创建房间错误码，具体原因参看 [ErrorCode](Android-errorcode.md#ErrorCode)。 |



<span id="IRTCVideoEventHandler-onuserstartaudiocapture"></span>
### onUserStartAudioCapture
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onUserStartAudioCapture(
    String roomId,
    String uid
)
```
房间内的用户调用 [startAudioCapture](Android-api.md#RTCVideo-startaudiocapture) 开启音频采集时，房间内其他用户会收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| roomId | String | 开启音频采集的远端用户所在的房间 ID |
| uid | String | 开启音频采集的远端用户 ID |



<span id="IRTCVideoEventHandler-onuserstopaudiocapture"></span>
### onUserStopAudioCapture
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onUserStopAudioCapture(
    String roomId,
    String uid
)
```
房间内的用户调用 [stopAudioCapture](Android-api.md#RTCVideo-stopaudiocapture) 关闭音频采集时，房间内其他用户会收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| roomId | String | 关闭音频采集的远端用户所在的房间 ID |
| uid | String | 关闭音频采集的远端用户 ID |



<span id="IRTCVideoEventHandler-onlocalaudiostatechanged"></span>
### onLocalAudioStateChanged
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onLocalAudioStateChanged(
    LocalAudioStreamState state,
    LocalAudioStreamError error
)
```
本地音频流的状态发生改变时，收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| state | LocalAudioStreamState | 本地音频设备的状态，详见 [LocalAudioStreamState](Android-keytype.md#LocalAudioStreamState) |
| error | LocalAudioStreamError | 本地音频流状态改变时的错误码，详见 [LocalAudioStreamError](Android-keytype.md#LocalAudioStreamError) |



<span id="IRTCVideoEventHandler-onremoteaudiostatechanged"></span>
### onRemoteAudioStateChanged
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onRemoteAudioStateChanged(
    RemoteStreamKey key,
    RemoteAudioState state,
    RemoteAudioStateChangeReason reason
)
```
用户订阅来自远端的音频流状态发生改变时，会收到此回调，了解当前的远端音频流状态。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| key | RemoteStreamKey | 远端流信息, 详见 [RemoteStreamKey](Android-keytype.md#RemoteStreamKey) |
| state | RemoteAudioState | 远端音频流状态，详见 [RemoteAudioState](Android-keytype.md#RemoteAudioState) |
| reason | RemoteAudioStateChangeReason | 远端音频流状态改变的原因，详见 [RemoteAudioStateChangeReason](Android-keytype.md#RemoteAudioStateChangeReason) |



<span id="IRTCVideoEventHandler-onlocalvideostatechanged"></span>
### onLocalVideoStateChanged
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onLocalVideoStateChanged(
    StreamIndex streamIndex,
    LocalVideoStreamState state,
    LocalVideoStreamError error
)
```
本地视频流的状态发生改变时，收到该事件。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamIndex | StreamIndex | 流属性，参看 [StreamIndex](Android-keytype.md#streamindex-2) |
| state | LocalVideoStreamState | 本地视频流状态，参看 [LocalVideoStreamState](Android-keytype.md#LocalVideoStreamState) |
| error | LocalVideoStreamError | 本地视频状态改变时的错误码，参看 [LocalVideoStreamError](Android-keytype.md#LocalVideoStreamError) |



<span id="IRTCVideoEventHandler-onremotevideostatechanged"></span>
### onRemoteVideoStateChanged
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onRemoteVideoStateChanged(
    RemoteStreamKey streamKey,
    RemoteVideoState videoState,
    RemoteVideoStateChangeReason videoStateReason
)
```
远端视频流的状态发生改变时，房间内订阅此流的用户会收到该事件。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamKey | RemoteStreamKey | 远端视频流信息，房间、用户 ID、流属性等，参看 [RemoteStreamKey](Android-keytype.md#RemoteStreamKey) |
| videoState | RemoteVideoState | 远端视频流状态，参看 [RemoteVideoState](Android-keytype.md#RemoteVideoState) |
| videoStateReason | RemoteVideoStateChangeReason | 远端视频流状态改变原因，参看 [RemoteVideoStateChangeReason](Android-keytype.md#RemoteVideoStateChangeReason) |



**注意**

本回调仅适用于主流，不适用于屏幕流。

<span id="IRTCVideoEventHandler-onfirstremotevideoframerendered"></span>
### onFirstRemoteVideoFrameRendered
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onFirstRemoteVideoFrameRendered(
    RemoteStreamKey remoteStreamKey,
    VideoFrameInfo frameInfo
)
```
SDK 内部渲染成功远端视频流首帧后，收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| remoteStreamKey | RemoteStreamKey | 远端流信息，参看 [RemoteStreamKey](Android-keytype.md#RemoteStreamKey) |
| frameInfo | VideoFrameInfo | 视频帧信息，参看 [VideoFrameInfo](Android-keytype.md#VideoFrameInfo) |



<span id="IRTCVideoEventHandler-onfirstremotevideoframedecoded"></span>
### onFirstRemoteVideoFrameDecoded
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onFirstRemoteVideoFrameDecoded(
    RemoteStreamKey remoteStreamKey,
    VideoFrameInfo frameInfo
)
```
SDK 接收并解码远端视频流首帧后，收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| remoteStreamKey | RemoteStreamKey | 远端流信息，参看 [RemoteStreamKey](Android-keytype.md#RemoteStreamKey) |
| frameInfo | VideoFrameInfo | 视频帧信息，参看 [VideoFrameInfo](Android-keytype.md#VideoFrameInfo) |



**注意**

- 对于主流，进入房间后，仅在发布端第一次发布的时候，订阅端会收到该回调，此后不受重新发布的影响，只要不重新加入房间，就不会再收到该回调。
- 对于屏幕流，用户每次重新发布屏幕视频流在订阅端都会重新触发一次该回调。

<span id="IRTCVideoEventHandler-onfirstlocalvideoframecaptured"></span>
### onFirstLocalVideoFrameCaptured
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onFirstLocalVideoFrameCaptured(
    StreamIndex streamIndex,
    VideoFrameInfo frameInfo
)
```
RTC SDK 在本地完成第一帧视频帧或屏幕视频帧采集时，收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamIndex | StreamIndex | 流属性，参看 [StreamIndex](Android-keytype.md#streamindex-2) |
| frameInfo | VideoFrameInfo | 视频信息，参看 [VideoFrameInfo](Android-keytype.md#VideoFrameInfo) |



**注意**

对于采集到的本地视频帧，你可以调用 [setLocalVideoCanvas](Android-api.md#RTCVideo-setlocalvideocanvas) 或 [setLocalVideoSink](Android-api.md#RTCVideo-setlocalvideosink) 在本地渲染。

<span id="IRTCVideoEventHandler-onlocalvideosizechanged"></span>
### onLocalVideoSizeChanged
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onLocalVideoSizeChanged(
    StreamIndex streamIndex,
    VideoFrameInfo frameInfo
)
```
本地预览视频大小或旋转信息发生改变时，收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamIndex | StreamIndex | 流属性，参看 [StreamIndex](Android-keytype.md#streamindex-2) |
| frameInfo | VideoFrameInfo | 视频帧信息，参看 [VideoFrameInfo](Android-keytype.md#VideoFrameInfo) |



<span id="IRTCVideoEventHandler-onremotevideosizechanged"></span>
### onRemoteVideoSizeChanged
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onRemoteVideoSizeChanged(
    RemoteStreamKey remoteStreamKey,
    VideoFrameInfo frameInfo
)
```
远端视频大小或旋转信息发生改变时，房间内订阅此视频流的用户会收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| remoteStreamKey | RemoteStreamKey | 远端流信息，参看 [RemoteStreamKey](Android-keytype.md#RemoteStreamKey)。 |
| frameInfo | VideoFrameInfo | 视频帧信息，参看 [VideoFrameInfo](Android-keytype.md#VideoFrameInfo) |



<span id="IRTCVideoEventHandler-onconnectionstatechanged"></span>
### onConnectionStateChanged
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onConnectionStateChanged(
    int state,
    int reason
)
```
回调 SDK 与信令服务器连接状态相关事件。当 SDK 与信令服务器的网络连接状态改变时回调该事件。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| state | int | <br>当前 SDK 与信令服务器连接状态。 详细定义参见 [ConnectionState](Android-keytype.md#ConnectionState) |
| reason | int | <br>引起信令服务器连接状态发生改变的原因，目前未启用固定为 -1 。 |



**注意**

更多信息参见 [连接状态提示](https://www.volcengine.com/docs/6348/95376)。

<span id="IRTCVideoEventHandler-onaudioroutechanged"></span>
### onAudioRouteChanged
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onAudioRouteChanged(AudioRoute route)
```
音频播放路由变化时，收到该回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| route | AudioRoute | 新的音频播放路由，详见 [AudioRoute](Android-keytype.md#AudioRoute) |



**注意**

插拔音频外设，或调用 [setAudioRoute](Android-api.md#RTCVideo-setaudioroute) 都可能触发音频路由切换，详见[移动端设置音频路由](https://www.volcengine.com/docs/6348/117836) 。

<span id="IRTCVideoEventHandler-onfirstlocalaudioframe"></span>
### onFirstLocalAudioFrame
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onFirstLocalAudioFrame(StreamIndex streamIndex)
```
发布音频流时，采集到第一帧音频帧，收到该回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamIndex | StreamIndex | 音频流属性, 详见 [StreamIndex](Android-keytype.md#streamindex-2) |



**注意**

如果发布音频流时，未开启本地音频采集，SDK 会推送静音帧，也会收到此回调。

<span id="IRTCVideoEventHandler-onfirstremoteaudioframe"></span>
### onFirstRemoteAudioFrame
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onFirstRemoteAudioFrame(RemoteStreamKey remoteStreamKey)
```
接收到来自远端某音频流的第一帧时，收到该回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| remoteStreamKey | RemoteStreamKey | 远端音频流信息, 详见 [RemoteStreamKey](Android-keytype.md#RemoteStreamKey) |



**注意**

用户刚收到房间内订阅的每一路音频流时，都会收到该回调。

<span id="IRTCVideoEventHandler-onlogreport"></span>
### onLogReport
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onLogReport(
    String logType,
    JSONObject logContent
)
```
上报日志时回调该事件。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| logType | String | <br>日志类型。 |
| logContent | JSONObject | <br>日志内容。 |



<span id="IRTCVideoEventHandler-onseimessagereceived"></span>
### onSEIMessageReceived
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onSEIMessageReceived(
    RemoteStreamKey remoteStreamKey,
    ByteBuffer message
)
```
收到通过调用 [sendSEIMessage](Android-api.md#RTCVideo-sendseimessage) 发送带有 SEI 消息的视频帧时，收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| remoteStreamKey | RemoteStreamKey | 包含 SEI 发送者的用户名，所在的房间名和媒体流，详见 [RemoteStreamKey](Android-keytype.md#RemoteStreamKey) |
| message | ByteBuffer | 收到的 SEI 消息内容 |



<span id="IRTCVideoEventHandler-onseistreamupdate"></span>
### onSEIStreamUpdate
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onSEIStreamUpdate(
    RemoteStreamKey remoteStreamKey,
    SEIStreamUpdateEvent event
)
```
黑帧视频流发布状态回调。

在语音通话场景下，本地用户调用 [sendSEIMessage](Android-api.md#RTCVideo-sendseimessage) 通过黑帧视频流发送 SEI 数据时，流的发送状态会通过该回调通知远端用户。

你可以通过此回调判断携带 SEI 数据的视频帧为黑帧，从而不对该视频帧进行渲染。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| remoteStreamKey | RemoteStreamKey | 远端流信息，参看 [RemoteStreamKey](Android-keytype.md#RemoteStreamKey)。 |
| event | SEIStreamUpdateEvent | 黑帧视频流状态，参看 [SEIStreamUpdateEvent](Android-keytype.md#SEIStreamUpdateEvent) |



<span id="IRTCVideoEventHandler-onloginresult"></span>
### onLoginResult
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onLoginResult(
    String uid,
    int errorCode,
    int elapsed
)
```
登录结果回调


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | String | <br>登录用户 ID |
| errorCode | int | <br>登录结果<br>详见 [LoginErrorCode](Android-errorcode.md#LoginErrorCode)。 |
| elapsed | int | <br>从调用 [login](Android-api.md#RTCVideo-login) 接口开始到返回结果所用时长。<br>单位为 ms。 |



**注意**

调用 [login](Android-api.md#RTCVideo-login) 后，会收到此回调。

<span id="IRTCVideoEventHandler-onlogout"></span>
### onLogout
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onLogout(int reason)
```
登出结果回调


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| reason | int | 用户登出的原因，参看 [LogoutReason](Android-keytype.md#LogoutReason) |



**注意**

在以下两种情况下会收到此回调：调用 [logout](Android-api.md#RTCVideo-logout) 接口主动退出；或其他用户以相同 UserId 进行 `login` 导致本地用户被动登出。

<span id="IRTCVideoEventHandler-onserverparamssetresult"></span>
### onServerParamsSetResult
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onServerParamsSetResult(int error)
```
设置应用服务器参数的返回结果


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| error | int | <br>设置结果<br><ul><li>返回 200，设置成功</li><li>返回其他，设置失败，详见 [UserMessageSendResult](Android-errorcode.md#UserMessageSendResult) </li></ul> |



**注意**

调用 [setServerParams](Android-api.md#RTCVideo-setserverparams) 后，会收到此回调。

<span id="IRTCVideoEventHandler-ongetpeeronlinestatus"></span>
### onGetPeerOnlineStatus
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onGetPeerOnlineStatus(
    String peerUserId,
    int status
)
```
查询对端或本端用户登录状态的返回结果


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| peerUserId | String | <br>需要查询的用户 ID |
| status | int | <br>查询的用户登录状态<br>详见 [UserOnlineStatus](Android-keytype.md#UserOnlineStatus). |



**注意**

必须先调用 [getPeerOnlineStatus](Android-api.md#RTCVideo-getpeeronlinestatus)，才能收到此回调。

<span id="IRTCVideoEventHandler-onusermessagereceivedoutsideroom"></span>
### onUserMessageReceivedOutsideRoom
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onUserMessageReceivedOutsideRoom(
    String uid,
    String message
)
```
收到房间外用户调用 [sendUserMessageOutsideRoom](Android-api.md#RTCVideo-sendusermessageoutsideroom) 发来的文本消息时，会收到此回调


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | String | <br>消息发送者 ID |
| message | String | <br>收到的文本消息内容 |



<span id="IRTCVideoEventHandler-onuserbinarymessagereceivedoutsideroom"></span>
### onUserBinaryMessageReceivedOutsideRoom
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onUserBinaryMessageReceivedOutsideRoom(
    String uid,
    ByteBuffer message
)
```
收到房间外用户调用 [sendUserBinaryMessageOutsideRoom](Android-api.md#RTCVideo-senduserbinarymessageoutsideroom) 发来的二进制消息时，会收到此回调


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | String | <br>消息发送者 ID |
| message | ByteBuffer | <br>收到的二进制消息内容 |



<span id="IRTCVideoEventHandler-onusermessagesendresultoutsideroom"></span>
### onUserMessageSendResultOutsideRoom
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onUserMessageSendResultOutsideRoom(
    long msgid,
    int error
)
```
给房间外指定的用户发送消息的回调


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| msgid | long | <br>本条消息的 ID<br>所有的 P2P 和 P2Server 消息共用一个 ID 序列。 |
| error | int | <br>消息发送结果<br>详见 [UserMessageSendResult](Android-errorcode.md#UserMessageSendResult)。 |



**注意**

当调用 [sendUserMessageOutsideRoom](Android-api.md#RTCVideo-sendusermessageoutsideroom) 或 [sendUserBinaryMessageOutsideRoom](Android-api.md#RTCVideo-senduserbinarymessageoutsideroom) 发送消息后，会收到此回调。

<span id="IRTCVideoEventHandler-onservermessagesendresult"></span>
### onServerMessageSendResult
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onServerMessageSendResult(
    long msgid,
    int error,
    ByteBuffer message
)
```
给应用服务器发送消息的回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| msgid | long | 本条消息的 ID<br>所有的 P2P 和 P2Server 消息共用一个 ID 序列。 |
| error | int | 消息发送结果，详见 [UserMessageSendResult](Android-errorcode.md#UserMessageSendResult)。 |
| message | ByteBuffer | 应用服务器收到 HTTP 请求后，在 ACK 中返回的信息。消息不超过 64 KB。 |



**注意**

本回调为异步回调。当调用 [sendServerMessage](Android-api.md#RTCVideo-sendservermessage) 或 [sendServerBinaryMessage](Android-api.md#RTCVideo-sendserverbinarymessage) 接口发送消息后，会收到此回调。

<span id="IRTCVideoEventHandler-onnetworkdetectionresult"></span>
### onNetworkDetectionResult
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onNetworkDetectionResult(
    NetworkDetectionLinkType type,
    int quality,
    int rtt,
    double lostRate,
    int bitrate,
    int jitter
)
```
通话前网络探测结果。

成功调用 [startNetworkDetection](Android-api.md#RTCVideo-startnetworkdetection) 接口开始探测后，会在 3s 内首次收到该回调，之后每 2s 收到一次该回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| type | NetworkDetectionLinkType | 探测网络类型为上行/下行 |
| quality | int | 探测网络的质量，参看 [NetworkQuality](Android-keytype.md#NetworkQuality)。 |
| rtt | int | 探测网络的 RTT，单位：ms |
| lostRate | double | 探测网络的丢包率 |
| bitrate | int | 探测网络的带宽，单位：kbps |
| jitter | int | 探测网络的抖动,单位：ms |



<span id="IRTCVideoEventHandler-onnetworkdetectionstopped"></span>
### onNetworkDetectionStopped
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onNetworkDetectionStopped(NetworkDetectionStopReason reason)
```
通话前网络探测结束

以下情况将停止探测并收到本一次本回调：

1. 当调用 [stopNetworkDetection](Android-api.md#RTCVideo-stopnetworkdetection) 接口停止探测后，会收到一次该回调；

2. 当收到远端/本端音频首帧后，停止探测；

3. 当探测超过 3 分钟后，停止探测；

4. 当探测链路断开一定时间之后，停止探测。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| reason | NetworkDetectionStopReason | <br>停止探测的原因类型,参考 [NetworkDetectionStopReason](Android-keytype.md#NetworkDetectionStopReason) |



<span id="IRTCVideoEventHandler-onsimulcastsubscribefallback"></span>
### onSimulcastSubscribeFallback
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onSimulcastSubscribeFallback(RemoteStreamSwitch event)
```
音视频流因网络环境变化等原因发生回退，或从回退中恢复时，触发该回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| event | RemoteStreamSwitch | 音视频流发生变化的信息。参看 [RemoteStreamSwitch](Android-keytype.md#RemoteStreamSwitch)。 |



<span id="IRTCVideoEventHandler-onperformancealarms"></span>
### onPerformanceAlarms
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onPerformanceAlarms(
    PerformanceAlarmMode mode,
    String roomId,
    PerformanceAlarmReason reason,
    SourceWantedData data
)
```
本地未通过 [setPublishFallbackOption](Android-api.md#RTCVideo-setpublishfallbackoption) 开启发布性能回退，检测到设备性能不足时，收到此回调。

本地通过 [setPublishFallbackOption](Android-api.md#RTCVideo-setpublishfallbackoption) 开启发布性能回退，因设备性能/网络原因，造成发布性能回退/恢复时，收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mode | PerformanceAlarmMode | 指示本地是否开启发布回退功能。参看 [PerformanceAlarmMode](Android-keytype.md#PerformanceAlarmMode)<br><ul><li>当发布端未开启发布性能回退时，mode 值为 NORMAL。</li><li>当发布端开启发布性能回退时，mode 值为 SIMULCAST。</li></ul> |
| roomId | String | <ul><li>未开启发布性能回退时，roomId 为空</li><li>开启发布性能回退时，roomId 是告警影响的房间 ID。</li></ul> |
| reason | PerformanceAlarmReason | 告警原因，参看 [PerformanceAlarmReason](Android-keytype.md#PerformanceAlarmReason) |
| data | SourceWantedData | 性能回退相关数据，详见 [SourceWantedData](Android-keytype.md#SourceWantedData)。 |



<span id="IRTCVideoEventHandler-onaudioframesendstatechanged"></span>
### onAudioFrameSendStateChanged
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onAudioFrameSendStateChanged(
    String roomId,
    RtcUser user,
    FirstFrameSendState state
)
```
本地音频首帧发送状态发生改变时，收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| roomId | String | 音频发布用户所在的房间 ID |
| user | RtcUser | 本地用户信息，详见 [RtcUser](Android-keytype.md#RtcUser) |
| state | FirstFrameSendState | 首帧发送状态，详见 [FirstFrameSendState](Android-keytype.md#FirstFrameSendState) |



<span id="IRTCVideoEventHandler-onvideoframesendstatechanged"></span>
### onVideoFrameSendStateChanged
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onVideoFrameSendStateChanged(
    String roomId,
    RtcUser user,
    FirstFrameSendState state
)
```
本地视频首帧发送状态发生改变时，收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| roomId | String | 视频发布用户所在的房间 ID |
| user | RtcUser | 本地用户信息，详见 [RtcUser](Android-keytype.md#RtcUser) |
| state | FirstFrameSendState | 首帧发送状态，详见 [FirstFrameSendState](Android-keytype.md#FirstFrameSendState) |



<span id="IRTCVideoEventHandler-onscreenvideoframesendstatechanged"></span>
### onScreenVideoFrameSendStateChanged
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onScreenVideoFrameSendStateChanged(
    String roomId,
    RtcUser user,
    FirstFrameSendState state
)
```
屏幕共享流的视频首帧发送状态发生改变时，收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| roomId | String | 屏幕视频发布用户所在的房间 ID |
| user | RtcUser | 本地用户信息，详见 [RtcUser](Android-keytype.md#RtcUser) |
| state | FirstFrameSendState | 首帧发送状态，详见 [FirstFrameSendState](Android-keytype.md#FirstFrameSendState) |



<span id="IRTCVideoEventHandler-onaudioframeplaystatechanged"></span>
### onAudioFramePlayStateChanged
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onAudioFramePlayStateChanged(
    String roomId,
    RtcUser user,
    FirstFramePlayState state
)
```
音频首帧播放状态发生改变时，收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| roomId | String | 音频发布用户所在的房间 ID |
| user | RtcUser | 远端用户信息，详见 [RtcUser](Android-keytype.md#RtcUser) |
| state | FirstFramePlayState | 首帧播放状态，详见 [FirstFramePlayState](Android-keytype.md#FirstFramePlayState) |



<span id="IRTCVideoEventHandler-onvideoframeplaystatechanged"></span>
### onVideoFramePlayStateChanged
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onVideoFramePlayStateChanged(
    String roomId,
    RtcUser user,
    FirstFramePlayState state
)
```
视频首帧播放状态发生改变时，收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| roomId | String | 视频发布用户所在的房间 ID |
| user | RtcUser | 远端用户信息，详见 [RtcUser](Android-keytype.md#RtcUser) |
| state | FirstFramePlayState | 首帧播放状态，详见 [FirstFramePlayState](Android-keytype.md#FirstFramePlayState) |



<span id="IRTCVideoEventHandler-onscreenvideoframeplaystatechanged"></span>
### onScreenVideoFramePlayStateChanged
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onScreenVideoFramePlayStateChanged(
    String roomId,
    RtcUser user,
    FirstFramePlayState state
)
```
屏幕共享流视频首帧播放状态发生改变时，收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| roomId | String | 屏幕视频发布用户所在的房间 ID |
| user | RtcUser | 远端用户信息，详见 [RtcUser](Android-keytype.md#RtcUser) |
| state | FirstFramePlayState | 首帧播放状态，详见 [FirstFramePlayState](Android-keytype.md#FirstFramePlayState) |



<span id="IRTCVideoEventHandler-onaudiodevicestatechanged"></span>
### onAudioDeviceStateChanged
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onAudioDeviceStateChanged(
    String deviceID,
    AudioDeviceType deviceType,
    int deviceState,
    int deviceError
)
```
音频设备状态回调。提示音频采集、音频播放等媒体设备的状态。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| deviceID | String | 设备 ID |
| deviceType | AudioDeviceType | 设备类型，详见 [AudioDeviceType](Android-keytype.md#AudioDeviceType)。 |
| deviceState | int | 设备状态，详见 [MediaDeviceState](Android-keytype.md#MediaDeviceState)。 |
| deviceError | int | 设备错误类型，详见 [MediaDeviceError](Android-keytype.md#MediaDeviceError)。 |



<span id="IRTCVideoEventHandler-onvideodevicestatechanged"></span>
### onVideoDeviceStateChanged
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onVideoDeviceStateChanged(
    String deviceID,
    VideoDeviceType deviceType,
    int deviceState,
    int deviceError
)
```
视频设备状态回调。提示摄像头视频采集、屏幕视频采集等媒体设备的状态。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| deviceID | String | 设备 ID |
| deviceType | VideoDeviceType | 设备类型，详见 [VideoDeviceType](Android-keytype.md#VideoDeviceType)。 |
| deviceState | int | 设备状态，详见 [MediaDeviceState](Android-keytype.md#MediaDeviceState)。 |
| deviceError | int | 设备错误类型，详见 [MediaDeviceError](Android-keytype.md#MediaDeviceError)。 |



<span id="IRTCVideoEventHandler-onaudiodevicewarning"></span>
### onAudioDeviceWarning
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onAudioDeviceWarning(
    String deviceID,
    AudioDeviceType deviceType,
    int deviceWarning
)
```
音频设备警告回调。音频设备包括音频采集设备、音频渲染设备等。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| deviceID | String | 设备 ID |
| deviceType | AudioDeviceType | 参看 [AudioDeviceType](Android-keytype.md#AudioDeviceType) |
| deviceWarning | int | 参看 [MediaDeviceWarning](Android-keytype.md#MediaDeviceWarning) |



<span id="IRTCVideoEventHandler-onvideodevicewarning"></span>
### onVideoDeviceWarning
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onVideoDeviceWarning(
    String deviceID,
    VideoDeviceType deviceType,
    int deviceWarning
)
```
视频设备警告回调，包括视频采集等设备。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| deviceID | String | 设备 ID |
| deviceType | VideoDeviceType | 参看 [VideoDeviceType](Android-keytype.md#VideoDeviceType) |
| deviceWarning | int | 参看 [MediaDeviceWarning](Android-keytype.md#MediaDeviceWarning) |



<span id="IRTCVideoEventHandler-onrecordingstateupdate"></span>
### onRecordingStateUpdate
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onRecordingStateUpdate(
    StreamIndex type,
    RecordingState state,
    RecordingErrorCode errorCode,
    RecordingInfo info
)
```
获取本地录制状态回调。

该回调由 [startFileRecording](Android-api.md#RTCVideo-startfilerecording) 或 [stopFileRecording](Android-api.md#RTCVideo-stopfilerecording) 触发。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| type | StreamIndex | 录制流的流属性，参看 [StreamIndex](Android-keytype.md#streamindex-2) |
| state | RecordingState | 录制状态，参看 [RecordingState](Android-keytype.md#RecordingState) |
| errorCode | RecordingErrorCode | 录制错误码，参看 [RecordingErrorCode](Android-keytype.md#RecordingErrorCode) |
| info | RecordingInfo | 录制文件的详细信息，参看 [RecordingInfo](Android-keytype.md#RecordingInfo) |



<span id="IRTCVideoEventHandler-onrecordingprogressupdate"></span>
### onRecordingProgressUpdate
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onRecordingProgressUpdate(
    StreamIndex type,
    RecordingProgress progress,
    RecordingInfo info
)
```
本地录制进度回调。

该回调由 [startFileRecording](Android-api.md#RTCVideo-startfilerecording) 触发，录制状态正常时，系统每秒钟都会通过该回调提示录制进度。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| type | StreamIndex | 录制流的流属性，参看 [StreamIndex](Android-keytype.md#streamindex-2) |
| progress | RecordingProgress | 录制进度，参看 [RecordingProgress](Android-keytype.md#RecordingProgress) |
| info | RecordingInfo | 录制文件的详细信息，参看 [RecordingInfo](Android-keytype.md#RecordingInfo) |



<span id="IRTCVideoEventHandler-onaudiorecordingstateupdate"></span>
### onAudioRecordingStateUpdate
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onAudioRecordingStateUpdate(
    AudioRecordingState state,
    AudioRecordingErrorCode errorCode
)
```
调用 [startAudioRecording](Android-api.md#RTCVideo-startaudiorecording) 或 [stopAudioRecording](Android-api.md#RTCVideo-stopaudiorecording) 改变音频文件录制状态时，收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| state | AudioRecordingState | 录制状态，参看 [AudioRecordingState](Android-keytype.md#AudioRecordingState) |
| errorCode | AudioRecordingErrorCode | 录制错误码，参看 [AudioRecordingErrorCode](Android-errorcode.md#AudioRecordingErrorCode) |



<span id="IRTCVideoEventHandler-onaudiomixingplayingprogress"></span>
### onAudioMixingPlayingProgress
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onAudioMixingPlayingProgress(
    int mixId,
    long progress
)
```
混音音频文件播放进度回调


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mixId | int | 混音 ID |
| progress | long | 当前混音音频文件播放进度，单位毫秒 |



**注意**

调用 [setAudioMixingProgressInterval](Android-api#IAudioMixingManager-setaudiomixingprogressinterval) 将时间间隔设为大于 0 的值后，或调用 [startAudioMixing](Android-api#IAudioMixingManager-startaudiomixing) 将 [AudioMixingConfig](Android-keytype.md#AudioMixingConfig) 中的时间间隔设为大于 0 的值后，SDK 会按照设置的时间间隔回调该事件。

<span id="IRTCVideoEventHandler-onlocalaudiopropertiesreport"></span>
### onLocalAudioPropertiesReport
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onLocalAudioPropertiesReport(LocalAudioPropertiesInfo[] audioPropertiesInfos)
```
调用 [enableAudioPropertiesReport](Android-api.md#RTCVideo-enableaudiopropertiesreport) 后，你会周期性地收到此回调，了解本地音频的相关信息。

本地音频包括使用 RTC SDK 内部机制采集的麦克风音频，屏幕音频和本地混音音频信息。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioPropertiesInfos | LocalAudioPropertiesInfo[] | 本地音频信息，详见 [LocalAudioPropertiesInfo](Android-keytype.md#LocalAudioPropertiesInfo)。 |



<span id="IRTCVideoEventHandler-onaudioplaybackdevicetestvolume"></span>
### onAudioPlaybackDeviceTestVolume
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onAudioPlaybackDeviceTestVolume(int volume)
```
回调音频设备测试时的播放音量


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| volume | int | 音频设备测试播放音量。取值范围：[0,255] |



**注意**

调用 [startAudioPlaybackDeviceTest](Android-api.md#IRTCAudioDeviceManager-startaudioplaybackdevicetest) 或 [startAudioDeviceRecordTest](Android-api.md#IRTCAudioDeviceManager-startaudiodevicerecordtest)，开始播放音频文件或录音时，将开启该回调。本回调为周期性回调，回调周期由上述接口的 `interval` 参数指定。

<span id="IRTCVideoEventHandler-onremoteaudiopropertiesreport"></span>
### onRemoteAudioPropertiesReport
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onRemoteAudioPropertiesReport(
    RemoteAudioPropertiesInfo[] audioPropertiesInfos,
    int totalRemoteVolume
)
```
远端用户进房后，本地调用 [enableAudioPropertiesReport](Android-api.md#RTCVideo-enableaudiopropertiesreport) ，根据设置的 interval 值，本地会周期性地收到此回调，了解订阅的远端用户的瞬时音频信息。

远端用户的音频包括使用 RTC SDK 内部机制/自定义机制采集的麦克风音频和屏幕音频。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioPropertiesInfos | RemoteAudioPropertiesInfo[] | 远端音频信息，其中包含音频流属性、房间 ID、用户 ID ，详见 [RemoteAudioPropertiesInfo](Android-keytype.md#RemoteAudioPropertiesInfo)。 |
| totalRemoteVolume | int | 订阅的所有远端流混音后的总音量，范围是 [0,255]。<br><ul><li>[0,25] 接近无声；</li><li>[25,75] 为低音量；</li><li>[76,204] 为中音量；</li><li>[205,255] 为高音量。</li></ul> |



<span id="IRTCVideoEventHandler-onactivespeaker"></span>
### onActiveSpeaker
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onActiveSpeaker(
    String roomId,
    String uid
)
```
调用 [enableAudioPropertiesReport](Android-api.md#RTCVideo-enableaudiopropertiesreport) 后，根据设置的 `AudioPropertiesConfig.interval`，你会周期性地收到此回调，获取房间内的最活跃用户信息。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| roomId | String | 房间 ID |
| uid | String | 最活跃用户（ActiveSpeaker）的用户 ID |



<span id="IRTCVideoEventHandler-onstreamsyncinforeceived"></span>
### onStreamSyncInfoReceived
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onStreamSyncInfoReceived(
    RemoteStreamKey streamKey,
    StreamSycnInfoConfig.SyncInfoStreamType streamType,
    ByteBuffer data
)
```
音频流同步信息回调。可以通过此回调，在远端用户调用 [sendStreamSyncInfo](Android-api.md#RTCVideo-sendstreamsyncinfo) 发送音频流同步消息后，收到远端发送的音频流同步信息。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamKey | RemoteStreamKey | 远端流信息，详见 [RemoteStreamKey](Android-keytype.md#RemoteStreamKey)。 |
| streamType | StreamSycnInfoConfig.SyncInfoStreamType | 媒体流类型，详见 [SyncInfoStreamType](Android-keytype.md#SyncInfoStreamType)。 |
| data | ByteBuffer | 消息内容。 |



<span id="IRTCVideoEventHandler-onpushpublicstreamresult"></span>
### onPushPublicStreamResult
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onPushPublicStreamResult(
    String roomId,
    String publicStreamId,
    PublicStreamErrorCode error
)
```
公共流发布结果回调。

调用 [startPushPublicStream](Android-api.md#RTCVideo-startpushpublicstream) 接口发布公共流后，启动结果通过此回调方法通知用户。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| roomId | String | 发布公共流的房间 ID |
| publicStreamId | String | 公共流 ID |
| error | PublicStreamErrorCode | 公共流发布结果状态码。详见 [PublicStreamErrorCode](Android-errorcode.md#PublicStreamErrorCode)。 |



<span id="IRTCVideoEventHandler-onplaypublicstreamresult"></span>
### onPlayPublicStreamResult
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onPlayPublicStreamResult(
    String publicStreamId,
    PublicStreamErrorCode error
)
```
订阅公共流的结果回调

调用 [startPlayPublicStream](Android-api.md#RTCVideo-startplaypublicstream) 接口启动拉公共流功能后，通过此回调收到启动结果和拉流过程中的错误。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| publicStreamId | String | 公共流 ID。 |
| error | PublicStreamErrorCode | 公共流订阅结果状态码。详见 [PublicStreamErrorCode](Android-errorcode.md#PublicStreamErrorCode)。 |



<span id="IRTCVideoEventHandler-onpublicstreamseimessagereceived"></span>
### onPublicStreamSEIMessageReceived
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onPublicStreamSEIMessageReceived(
    String publicStreamId,
    ByteBuffer message,
    DataMessageSourceType sourceType
)
```
回调公共流中包含的 SEI 信息。

调用 [startPlayPublicStream](Android-api.md#RTCVideo-startplaypublicstream) 接口启动拉公共流功能后，通过此回调收到公共流中的 SEI 消息。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| publicStreamId | String | 公共流 ID。 |
| message | ByteBuffer | 收到的 SEI 消息内容。<br>通过调用客户端 [sendSEIMessage](Android-api.md#RTCVideo-sendseimessage-2) 插入的 SEI 信息。<br>当公共流中的多路视频流均包含有 SEI 信息：SEI 不互相冲突时，将通过多次回调分别发送；SEI 在同一帧有冲突时，则只有一条流中的 SEI 信息被透传并融合到公共流中。 |
| sourceType | DataMessageSourceType | SEI 消息类型，自 3.52.1 版本后固定为 `0`，自定义消息。参看 [DataMessageSourceType](Android-keytype.md#DataMessageSourceType)。 |



**注意**

通过 Open API 插入的自定义信息，应通过回调 [onPublicStreamDataMessageReceived](#IRTCVideoEventHandler-onpublicstreamdatamessagereceived) 获取。

<span id="IRTCVideoEventHandler-onpublicstreamdatamessagereceived"></span>
### onPublicStreamDataMessageReceived
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onPublicStreamDataMessageReceived(
    String publicStreamId,
    ByteBuffer message,
    DataMessageSourceType sourceType
)
```
> Available since 3.52

回调公共流中包含的数据信息。

调用 [startPlayPublicStream](Android-api.md#RTCVideo-startplaypublicstream) 订阅公共流后，通过监听本回调获取公共流中的数据消息，包括调用 Open API 发送的 SEI 消息和音量回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| publicStreamId | String | 公共流 ID。 |
| message | ByteBuffer | 收到的数据消息内容，如下：<br><ul><li>调用公共流 OpenAPI 发送的自定义消息。</li><li>媒体流音量变化，需要通过公共流 OpenAPI 开启回调。JSON 格式说明如下： {<br>"Type":"VolumeIndication", //具体业务类型<br>"VolumeInfos"[// 业务类型对应信息<br>{<br>"RoomId":"1000001", // 房间 ID<br>"UserId":"1000001", // 用户 ID<br>"StreamType":0, // 0:摄像头流；1:屏幕流<br>"LinearVolume":1 // 线性音量大小<br>}<br>]<br>}</li></ul> |
| sourceType | DataMessageSourceType | 数据消息来源，参看 [DataMessageSourceType](Android-keytype.md#DataMessageSourceType)。 |



**注意**

通过调用客户端 API 插入的 SEI 信息，应通过回调 [onPublicStreamSEIMessageReceived](#IRTCVideoEventHandler-onpublicstreamseimessagereceived) 获取。

<span id="IRTCVideoEventHandler-onfirstpublicstreamvideoframedecoded"></span>
### onFirstPublicStreamVideoFrameDecoded
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onFirstPublicStreamVideoFrameDecoded(
    String publicStreamId,
    VideoFrameInfo videoFrameInfo
)
```
公共流的首帧视频解码成功

关于订阅公共流，详见 [startPlayPublicStream](Android-api.md#RTCVideo-startplaypublicstream)。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| publicStreamId | String | 公共流 ID |
| videoFrameInfo | VideoFrameInfo | 视频帧信息，参看 [VideoFrameInfo](Android-keytype.md#VideoFrameInfo) |



<span id="IRTCVideoEventHandler-onfirstpublicstreamaudioframe"></span>
### onFirstPublicStreamAudioFrame
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onFirstPublicStreamAudioFrame(String publicStreamId)
```
公共流的音频首帧解码成功

关于订阅公共流，详见 [startPlayPublicStream](Android-api.md#RTCVideo-startplaypublicstream)。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| publicStreamId | String | 公共流 ID |



<span id="IRTCVideoEventHandler-onechotestresult"></span>
### onEchoTestResult
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onEchoTestResult(EchoTestResult result)
```
关于音视频回路测试结果的回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| result | EchoTestResult | 测试结果，参看 [EchoTestResult](Android-keytype.md#EchoTestResult) |



**注意**

该回调触发的时机包括：

- 检测过程中采集设备发生错误时；
- 检测成功后；
- 非设备原因导致检测过程中未接收到音/视频回放，停止检测后。

<span id="IRTCVideoEventHandler-oncloudproxyconnected"></span>
### onCloudProxyConnected
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onCloudProxyConnected(int interval)
```
调用 [startCloudProxy](Android-api.md#RTCVideo-startcloudproxy) 开启云代理，SDK 首次成功连接云代理服务器时，回调此事件。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| interval | int | 从开启云代理到连接成功经过的时间，单位为 ms |



<span id="IRTCVideoEventHandler-onnetworktimesynchronized"></span>
### onNetworkTimeSynchronized
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onNetworkTimeSynchronized()
```
首次调用 [getNetworkTimeInfo](Android-api.md#RTCVideo-getnetworktimeinfo) 后，SDK 内部启动网络时间同步，同步完成时会触发此回调。


<span id="IRTCVideoEventHandler-onhardwareechodetectionresult"></span>
### onHardwareEchoDetectionResult
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onHardwareEchoDetectionResult(HardwareEchoDetectionResult hardwareEchoDetectionResult)
```
通话前回声检测结果回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| hardwareEchoDetectionResult | HardwareEchoDetectionResult | 参见 [HardwareEchoDetectionResult](Android-keytype.md#HardwareEchoDetectionResult) |



**注意**

- 通话前调用 [startHardwareEchoDetection](Android-api.md#RTCVideo-starthardwareechodetection) 后，将触发本回调返回检测结果。
- 建议在收到检测结果后，调用 [stopHardwareEchoDetection](Android-api.md#RTCVideo-stophardwareechodetection) 停止检测，释放对音频设备的占用。
- 如果 SDK 在通话中检测到回声，将通过 [onAudioDeviceWarning](#IRTCVideoEventHandler-onaudiodevicewarning) 回调 `MEDIA_DEVICE_WARNING_DETECT_LEAK_ECHO`。

<span id="IRTCVideoEventHandler-onlocalproxystatechanged"></span>
### onLocalProxyStateChanged
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onLocalProxyStateChanged(
    LocalProxyType localProxyType,
    LocalProxyState localProxyState,
    LocalProxyError localProxyError
)
```
本地代理状态发生改变回调。调用 [setLocalProxy](Android-api.md#RTCVideo-setlocalproxy) 设置本地代理后，SDK 会触发此回调，通知代理连接的状态。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| localProxyType | LocalProxyType | 本地代理类型。参看 [LocalProxyType](Android-keytype.md#LocalProxyType)。 |
| localProxyState | LocalProxyState | 本地代理状态。参看 [LocalProxyState](Android-keytype.md#LocalProxyState)。 |
| localProxyError | LocalProxyError | 本地代理错误。参看 [LocalProxyError](Android-keytype.md#LocalProxyError)。 |



<span id="IRTCVideoEventHandler-onexternalscreenframeupdate"></span>
### onExternalScreenFrameUpdate
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onExternalScreenFrameUpdate(FrameUpdateInfo info)
```
外部采集时，调用 setOriginalScreenVideoInfo 设置屏幕或窗口大小改变前的分辨率后，若屏幕采集模式为智能模式，你将收到此回调，根据 RTC 智能决策合适的帧率和分辨率积（宽*高）重新采集。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| info | FrameUpdateInfo | RTC 智能决策后合适的帧率和分辨率积（宽*高）。参看 [FrameUpdateInfo](Android-keytype.md#FrameUpdateInfo)。 |



<span id="IRTCVideoEventHandler-onusermuteaudio"></span>
### onUserMuteAudio
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onUserMuteAudio(
    String roomId,
    String uid,
    MuteState muteState
)
```
> Deprecated since 3.36 and will be deleted in 3.51, use [onUserPublishStream](#IRTCRoomEventHandler-onuserpublishstream), [onUserPublishScreen](#IRTCRoomEventHandler-onuserpublishscreen), [onUserUnpublishStream](#IRTCRoomEventHandler-onuserunpublishstream) and [onUserUnpublishScreen](#IRTCRoomEventHandler-onuserunpublishscreen) instead.

房间内用户暂停/恢复发送音频流时，房间内其他用户会收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| roomId | String | 房间 ID |
| uid | String | 改变本地音频发送状态的用户 ID |
| muteState | MuteState | 发送状态，参看 [MuteState](Android-keytype.md#MuteState) |



<span id="IRTCVideoEventHandler-onusermutevideo"></span>
### onUserMuteVideo
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onUserMuteVideo(
    String roomId,
    String uid,
    MuteState muteState
)
```
> Deprecated since 3.36 and will be deleted in 3.51, use [onUserPublishStream](#IRTCRoomEventHandler-onuserpublishstream), [onUserPublishScreen](#IRTCRoomEventHandler-onuserpublishscreen), [onUserUnpublishStream](#IRTCRoomEventHandler-onuserunpublishstream) and [onUserUnpublishScreen](#IRTCRoomEventHandler-onuserunpublishscreen) instead.

房间内用户暂停/恢复发送视频流时，房间内其他用户会收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| roomId | String | 房间 ID |
| uid | String | 暂停/恢复发送视频流的用户 ID。 |
| muteState | MuteState | 视频流的发送状态。参看 [MuteState](Android-keytype.md#MuteState)。 |



<span id="IRTCVideoEventHandler-onaudioplaybackdevicechanged"></span>
### onAudioPlaybackDeviceChanged
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onAudioPlaybackDeviceChanged(AudioPlaybackDevice device)
```
> Deprecated since 3.38 and will be deleted in 3.51, use [onAudioRouteChanged](#IRTCVideoEventHandler-onaudioroutechanged) instead.

音频播放设备变化时，收到该回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| device | AudioPlaybackDevice | 新的音频设备，详见 [AudioPlaybackDevice](Android-keytype.md#AudioPlaybackDevice) |



**注意**

音频设备设置与音频路由策略，详见 [setAudioPlaybackDevice](Android-api.md#RTCVideo-setaudioplaybackdevice)

<span id="IRTCVideoEventHandler-onmediadevicestatechanged"></span>
### onMediaDeviceStateChanged
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onMediaDeviceStateChanged(
    String deviceID,
    int deviceType,
    int deviceState,
    int deviceError
)
```
> Deprecated since 3.37 and will be deleted in 3.51, using [onAudioDeviceStateChanged](#IRTCVideoEventHandler-onaudiodevicestatechanged) and [onVideoDeviceStateChanged](#IRTCVideoEventHandler-onvideodevicestatechanged) instead.

媒体设备状态回调。提示音频采集、音频播放、摄像头视频采集、屏幕视频采集四种媒体设备的状态。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| deviceID | String | 设备 ID |
| deviceType | int | 设备类型，详见 [MediaDeviceType](Android-keytype.md#MediaDeviceType)。 |
| deviceState | int | 设备状态，详见 [MediaDeviceState](Android-keytype.md#MediaDeviceState)。 |
| deviceError | int | 设备错误类型，详见 [MediaDeviceError](Android-keytype.md#MediaDeviceError)。 |



<span id="IRTCVideoEventHandler-onmediadevicewarning"></span>
### onMediaDeviceWarning
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onMediaDeviceWarning(
    String deviceID,
    int deviceType,
    int deviceWarning
)
```
> Deprecated since 3.37 and will be deleted in 3.51, using [onAudioDeviceWarning](#IRTCVideoEventHandler-onaudiodevicewarning) and [onVideoDeviceWarning](#IRTCVideoEventHandler-onvideodevicewarning) instead.

媒体设备警告回调。媒体设备包括：音频采集设备、音频渲染设备、和视频采集设备。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| deviceID | String | 设备 ID |
| deviceType | int | 参看 [MediaDeviceType](Android-keytype.md#MediaDeviceType) |
| deviceWarning | int | 参看 [MediaDeviceWarning](Android-keytype.md#MediaDeviceWarning) |



<span id="IRTCVideoEventHandler-onhttpproxystate"></span>
### onHttpProxyState
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onHttpProxyState(int state)
```
> Deprecated since 3.52, will be deleted at 3.57, use [onLocalProxyStateChanged](#IRTCVideoEventHandler-onlocalproxystatechanged) instead

HTTP 代理连接状态改变时，收到该回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| state | int | 当前 HTTP 代理连接状态 |



<span id="IRTCVideoEventHandler-onhttpsproxystate"></span>
### onHttpsProxyState
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onHttpsProxyState(int state)
```
> Deprecated since 3.52, will be deleted at 3.57, use [onLocalProxyStateChanged](#IRTCVideoEventHandler-onlocalproxystatechanged) instead

HTTPS 代理连接状态改变时，收到该回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| state | int | 当前 HTTPS 代理连接状态 |



<span id="IRTCVideoEventHandler-onsocks5proxystate"></span>
### onSocks5ProxyState
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onSocks5ProxyState(
    int state,
    String cmd,
    String proxyAddress,
    String localAddress,
    String remoteAddress
)
```
> Deprecated since 3.52, will be deleted at 3.57, use [onLocalProxyStateChanged](#IRTCVideoEventHandler-onlocalproxystatechanged) instead

SOCKS5 代理状态改变时，收到该回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| state | int | SOCKS5 代理连接状态 |
| cmd | String | 代理连接的每一步操作命令 |
| proxyAddress | String | 代理地址信息 |
| localAddress | String | 当前连接使用的本地地址 |
| remoteAddress | String | 远端的连接地址 |



<span id="IRTCVideoEventHandler-onaudiomixingstatechanged"></span>
### onAudioMixingStateChanged
```java
void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onAudioMixingStateChanged(
    int mixId,
    AudioMixingState state,
    AudioMixingError error
)
```
> Deprecated since 353. Use [IMediaPlayerEventHandler](#IMediaPlayerEventHandler) and [IAudioEffectPlayerEventHandler](#IAudioEffectPlayerEventHandler) instead.

音频混音文件播放状态改变时回调


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mixId | int | <br>混音 ID<br>使用 [IAudioMixingManager](Android-api.md#IAudioMixingManager) 相关接口时传入的唯一 ID。 |
| state | AudioMixingState | <br>混音状态<br>其混音状态可参考： [AudioMixingState](Android-keytype.md#AudioMixingState)。 |
| error | AudioMixingError | <br>错误码<br>详见 [AudioMixingError](Android-keytype.md#AudioMixingError)。 |



**注意**

此回调会被触发的时机汇总如下：

- 当调用 [startAudioMixing](Android-api.md#IAudioMixingManager-startaudiomixing) 方法成功后，会触发 state 值为 AUDIO_MIXING_STATE_PLAYING 回调；否则触发 state 值为 AUDIO_MIXING_STATE_FAILED 的回调。
- 当使用相同的 ID 重复调用 [startAudioMixing](Android-api.md#IAudioMixingManager-startaudiomixing) 后，后一次会覆盖前一次，且本回调会以 AUDIO_MIXING_STATE_STOPPED 通知前一次混音已停止。
- 当调用 [pauseAudioMixing](Android-api.md#IAudioMixingManager-pauseaudiomixing) 方法暂停播放成功后， 会触发 state 值为 AUDIO_MIXING_STATE_PAUSED 回调；否则触发 state 值为 AUDIO_MIXING_STATE_FAILED 的回调。
- 当调用 [resumeAudioMixing](Android-api.md#IAudioMixingManager-resumeaudiomixing) 方法恢复播放成功后，会触发 state 值为 AUDIO_MIXING_STATE_PLAYING 回调；否则触发 state 值为 AUDIO_MIXING_STATE_FAILED 的回调。
- 当调用 [stopAudioMixing](Android-api.md#IAudioMixingManager-stopaudiomixing) 方法暂停止播放成功后， 会触发 state 值为 AUDIO_MIXING_STATE_STOPPED 回调；否则触发 state 值为 AUDIO_MIXING_STATE_FAILED 的回调。
- 播放结束会触发 state 值为 AUDIO_MIXING_STATE_FINISHED 回调。

<span id="ISnapshotResultCallback"></span>
# ISnapshotResultCallback
```java
public interface com.ss.bytertc.engine.video.ISnapshotResultCallback
```
截图的回调。

注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| void | [onTakeLocalSnapshotResult](#ISnapshotResultCallback-ontakelocalsnapshotresult) |
| void | [onTakeRemoteSnapshotResult](#ISnapshotResultCallback-ontakeremotesnapshotresult) |


## 函数说明
<span id="ISnapshotResultCallback-ontakelocalsnapshotresult"></span>
### onTakeLocalSnapshotResult
```java
void com.ss.bytertc.engine.video.ISnapshotResultCallback.onTakeLocalSnapshotResult(
    long taskId,
    StreamIndex streamIndex,
    Bitmap image,
    int errorCode
)
```
调用 [takeLocalSnapshot](Android-api.md#RTCVideo-takelocalsnapshot) 截取视频画面时，收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| taskId | long | 本地截图任务的编号。和 [takeLocalSnapshot](Android-api.md#RTCVideo-takelocalsnapshot) 的返回值一致。 |
| streamIndex | StreamIndex | 截图的视频流的属性，参看 [StreamIndex](Android-keytype.md#StreamIndex)。 |
| image | Bitmap | 截图。你可以保存为文件，或对其进行二次处理。截图失败时，为空。 |
| errorCode | int | 截图错误码：<br><ul><li>0: 成功</li><li>-1: 截图错误。生成图片数据失败或 RGBA 编码失败</li><li>-2: 截图错误。流无效。</li><li>-3: 截图错误。截图超时,超时时间 1 秒。</li></ul> |



<span id="ISnapshotResultCallback-ontakeremotesnapshotresult"></span>
### onTakeRemoteSnapshotResult
```java
void com.ss.bytertc.engine.video.ISnapshotResultCallback.onTakeRemoteSnapshotResult(
    long taskId,
    RemoteStreamKey streamKey,
    Bitmap image,
    int errorCode
)
```
调用 [takeRemoteSnapshot](Android-api.md#RTCVideo-takeremotesnapshot) 截取视频画面时，收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| taskId | long | 远端截图任务的编号。和 [takeRemoteSnapshot](Android-api.md#RTCVideo-takeremotesnapshot) 的返回值一致。 |
| streamKey | RemoteStreamKey | 截图的视频流，参看 [RemoteStreamKey](Android-keytype.md#RemoteStreamKey)。 |
| image | Bitmap | 截图。你可以保存为文件，或对其进行二次处理。截图失败时，为空。 |
| errorCode | int | 截图错误码：<br><ul><li>0: 成功</li><li>-1: 截图错误。生成图片数据失败或 RGBA 编码失败</li><li>-2: 截图错误。流无效。</li><li>-3: 截图错误。截图超时,超时时间 1 秒。</li></ul> |



<span id="IAudioFrameProcessor"></span>
# IAudioFrameProcessor
```java
public interface com.ss.bytertc.engine.IAudioFrameProcessor
```
自定义音频处理器。

注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| int | [onProcessRecordAudioFrame](#IAudioFrameProcessor-onprocessrecordaudioframe) |
| int | [onProcessPlayBackAudioFrame](#IAudioFrameProcessor-onprocessplaybackaudioframe) |
| int | [onProcessRemoteUserAudioFrame](#IAudioFrameProcessor-onprocessremoteuseraudioframe) |
| int | [onProcessEarMonitorAudioFrame](#IAudioFrameProcessor-onprocessearmonitoraudioframe) |
| int | [onProcessScreenAudioFrame](#IAudioFrameProcessor-onprocessscreenaudioframe) |


## 函数说明
<span id="IAudioFrameProcessor-onprocessrecordaudioframe"></span>
### onProcessRecordAudioFrame
```java
int com.ss.bytertc.engine.IAudioFrameProcessor.onProcessRecordAudioFrame(IAudioFrame audioFrame)
```
回调本地采集的音频帧地址，供自定义音频处理。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioFrame | IAudioFrame | 音频帧地址，参看 [IAudioFrame](Android-keytype.md#IAudioFrame)。 |



**返回值**

- 0： 成功。
- < 0： 失败。


**注意**

- 完成自定义音频处理后，SDK 会对处理后的音频帧进行编码，并传输到远端。此音频处理不会影响软件耳返音频数据。
- 要启用此回调，必须调用 `enableAudioProcessor`，并在参数中选择本地采集的音频，每 10 ms 收到此回调。

<span id="IAudioFrameProcessor-onprocessplaybackaudioframe"></span>
### onProcessPlayBackAudioFrame
```java
int com.ss.bytertc.engine.IAudioFrameProcessor.onProcessPlayBackAudioFrame(IAudioFrame audioFrame)
```
回调远端音频混音的音频帧地址，供自定义音频处理。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioFrame | IAudioFrame | 音频帧地址，参看 [IAudioFrame](Android-keytype.md#IAudioFrame) |



**注意**

调用 `enableAudioProcessor`，并在参数中选择远端音频流的的混音音频时，每 10 ms 收到此回调。

<span id="IAudioFrameProcessor-onprocessremoteuseraudioframe"></span>
### onProcessRemoteUserAudioFrame
```java
int com.ss.bytertc.engine.IAudioFrameProcessor.onProcessRemoteUserAudioFrame(
    RemoteStreamKey streamKey,
    IAudioFrame audioFrame
)
```
回调单个远端用户的音频帧地址，供自定义音频处理。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamKey | RemoteStreamKey | 音频流信息，参看 [RemoteStreamKey](Android-keytype.md#RemoteStreamKey) |
| audioFrame | IAudioFrame | 音频帧地址，参看 [IAudioFrame](Android-keytype.md#IAudioFrame) |



**注意**

调用 `enableAudioProcessor`，并在参数中选择各个远端音频流时，，每 10 ms 收到此回调。

<span id="IAudioFrameProcessor-onprocessearmonitoraudioframe"></span>
### onProcessEarMonitorAudioFrame
```java
int com.ss.bytertc.engine.IAudioFrameProcessor.onProcessEarMonitorAudioFrame(IAudioFrame audioFrame)
```
> Available since 3.50

软件耳返音频数据的回调。你可根据此回调自定义处理音频。

软件耳返音频中包含通过调用 `setVoiceReverbType` 和 `setVoiceChangerType` 设置的音频特效。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioFrame | IAudioFrame | 音频帧地址。参看 [IAudioFrame](Android-keytype.md#IAudioFrame)。 |



**返回值**

- 0： 成功。
- < 0： 失败。


**注意**

- 此数据处理只影响软件耳返音频数据。
- 要启用此回调，必须调用 `enableAudioProcessor`，并选择软件耳返音频，每 10 ms 收到此回调。

<span id="IAudioFrameProcessor-onprocessscreenaudioframe"></span>
### onProcessScreenAudioFrame
```java
int com.ss.bytertc.engine.IAudioFrameProcessor.onProcessScreenAudioFrame(IAudioFrame audioFrame)
```
屏幕共享的音频帧地址回调。你可根据此回调自定义处理音频。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioFrame | IAudioFrame | 音频帧地址，参看 [IAudioFrame](Android-keytype.md#IAudioFrame)。 |



**注意**

调用 `enableAudioProcessor`，把返回给音频处理器的音频类型设置为屏幕共享音频后，每 10 ms 收到此回调。