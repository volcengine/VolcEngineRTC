# IExternalVideoEncoderEventHandler
```java
public abstract class com.ss.bytertc.engine.handler.IExternalVideoEncoderEventHandler
```

自定义编码帧回调类


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **abstract void** | [onStart](#IExternalVideoEncoderEventHandler-onstart) |
| **abstract void** | [onStop](#IExternalVideoEncoderEventHandler-onstop) |
| **abstract void** | [onRateUpdate](#IExternalVideoEncoderEventHandler-onrateupdate) |
| **abstract void** | [onRequestKeyFrame](#IExternalVideoEncoderEventHandler-onrequestkeyframe) |


## 函数说明
<span id="IExternalVideoEncoderEventHandler-onstart"></span>
### onStart
```java
public abstract void com.ss.bytertc.engine.handler.IExternalVideoEncoderEventHandler.onStart(
    StreamIndex index)
```
提示自定义编码帧可以开始推送的回调。  <br>
收到该回调后，你即可调用 [pushExternalEncodedVideoFrame](Android-api.md#RTCVideo-pushexternalencodedvideoframe) 向 SDK 推送自定义编码视频帧

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| index | **StreamIndex** | 可以推送的编码流的属性，参看 [StreamIndex](Android-keytype.md#streamindex-2) |


<span id="IExternalVideoEncoderEventHandler-onstop"></span>
### onStop
```java
public abstract void com.ss.bytertc.engine.handler.IExternalVideoEncoderEventHandler.onStop(
    StreamIndex index)
```
当收到该回调时，你需停止向 SDK 推送自定义编码视频帧

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| index | **StreamIndex** | 需停止推送的编码流的属性，参看 [StreamIndex](Android-keytype.md#streamindex-2) |


<span id="IExternalVideoEncoderEventHandler-onrateupdate"></span>
### onRateUpdate
```java
public abstract void com.ss.bytertc.engine.handler.IExternalVideoEncoderEventHandler.onRateUpdate(
    StreamIndex stream_index,
    int video_index,
    int fps,
    int bitrateKbps)
```
当自定义编码流的帧率或码率发生变化时，触发该回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stream_index | **StreamIndex** | 发生变化的编码流的属性，参看 [StreamIndex](Android-keytype.md#streamindex-2) |
| video_index | **int** | 对应编码流的下标 |
| fps | **int** | 变化后的帧率，单位：fps |
| bitrateKbps | **int** | 变化后的码率，单位：kbps |


<span id="IExternalVideoEncoderEventHandler-onrequestkeyframe"></span>
### onRequestKeyFrame
```java
public abstract void com.ss.bytertc.engine.handler.IExternalVideoEncoderEventHandler.onRequestKeyFrame(
    StreamIndex stream_index,
    int video_index)
```
提示流发布端需重新生成关键帧的回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stream_index | **StreamIndex** | 远端编码流的属性，参看 [StreamIndex](Android-keytype.md#streamindex-2) |
| video_index | **int** | 对应编码流的下标 |


# IRTCASREngineEventHandler
```java
public interface com.ss.bytertc.engine.handler.IRTCASREngineEventHandler
```

语音识别服务使用状态回调


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **void** | [onSuccess](#IRTCASREngineEventHandler-onsuccess) |
| **void** | [onMessage](#IRTCASREngineEventHandler-onmessage) |
| **void** | [onError](#IRTCASREngineEventHandler-onerror) |


## 函数说明
<span id="IRTCASREngineEventHandler-onsuccess"></span>
### onSuccess
```java
public void com.ss.bytertc.engine.handler.IRTCASREngineEventHandler.onSuccess()
```
语音识别服务开启成功回调


<span id="IRTCASREngineEventHandler-onmessage"></span>
### onMessage
```java
public void com.ss.bytertc.engine.handler.IRTCASREngineEventHandler.onMessage(
    String message)
```
语音转文字成功后回调，该回调返回识别后的全量消息。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| message | **String** | 识别完成后得到的文字消息 |


**注意**
若识别过程中发生了网络连接中断，则重连后回调的信息中只包含重连后识别的文字消息，不再包含上一次连接后识别的消息。

<span id="IRTCASREngineEventHandler-onerror"></span>
### onError
```java
public void com.ss.bytertc.engine.handler.IRTCASREngineEventHandler.onError(
    int errorCode,
    String errorMessage)
```
当语音识别服务内部发生错误事件时触发该回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| errorCode | **int** | 错误码  <br/>• < 0: 参数错误或 API 调用顺序错误，参看 [RTCASRErrorCode](Android-keytype.md#rtcasrerrorcode)；  <br/>• >0: 参看 [语音识别服务错误码](https://www.volcengine.com/docs/6561/80818#_3-3-%E9%94%99%E8%AF%AF%E7%A0%81) |
| errorMessage | **String** | 错误原因说明。 |


# IRTCEncryptionHandler
```java
public interface com.ss.bytertc.engine.handler.IRTCEncryptionHandler
```

加密事件回调接口


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **byte[]** | [onEncryptData](#IRTCEncryptionHandler-onencryptdata) |
| **byte[]** | [onDecryptData](#IRTCEncryptionHandler-ondecryptdata) |


## 函数说明
<span id="IRTCEncryptionHandler-onencryptdata"></span>
### onEncryptData
```java
public byte[] com.ss.bytertc.engine.handler.IRTCEncryptionHandler.onEncryptData(
    byte[] data)
```
自定义加密。  <br>
使用设定的自定义加密方式，对编码后传输前的音视频帧数据进行加密。<br>
暂不支持对原始音视频帧进行加密。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| data | **byte[]** | 未加密的数据。 |

**返回值**
加密后的数据   


<span id="IRTCEncryptionHandler-ondecryptdata"></span>
### onDecryptData
```java
public byte[] com.ss.bytertc.engine.handler.IRTCEncryptionHandler.onDecryptData(
    byte[] data)
```
自定义解密。  <br>
对自定义加密后的音视频帧数据进行解密。关于自定义加密，参看 [onEncryptData](#IRTCEncryptionHandler-onencryptdata)。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| data | **byte[]** | 加密过的数据。 |

**返回值**
解密后的数据   


# IRTCRoomEventHandler
```java
public abstract class com.ss.bytertc.engine.handler.IRTCRoomEventHandler
```

房间事件回调接口


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **void** | [onLeaveRoom](#IRTCRoomEventHandler-onleaveroom) |
| **void** | [onRoomStateChanged](#IRTCRoomEventHandler-onroomstatechanged) |
| **void** | [onStreamStateChanged](#IRTCRoomEventHandler-onstreamstatechanged) |
| **void** | [onAVSyncStateChange](#IRTCRoomEventHandler-onavsyncstatechange) |
| **void** | [onRoomStats](#IRTCRoomEventHandler-onroomstats) |
| **void** | [onUserJoined](#IRTCRoomEventHandler-onuserjoined) |
| **void** | [onUserLeave](#IRTCRoomEventHandler-onuserleave) |
| **void** | [onTokenWillExpire](#IRTCRoomEventHandler-ontokenwillexpire) |
| **void** | [onPublishPrivilegeTokenWillExpire](#IRTCRoomEventHandler-onpublishprivilegetokenwillexpire) |
| **void** | [onSubscribePrivilegeTokenWillExpire](#IRTCRoomEventHandler-onsubscribeprivilegetokenwillexpire) |
| **void** | [onUserPublishStream](#IRTCRoomEventHandler-onuserpublishstream) |
| **void** | [onUserUnpublishStream](#IRTCRoomEventHandler-onuserunpublishstream) |
| **void** | [onUserPublishScreen](#IRTCRoomEventHandler-onuserpublishscreen) |
| **void** | [onUserUnpublishScreen](#IRTCRoomEventHandler-onuserunpublishscreen) |
| **void** | [onLocalStreamStats](#IRTCRoomEventHandler-onlocalstreamstats) |
| **void** | [onRemoteStreamStats](#IRTCRoomEventHandler-onremotestreamstats) |
| **void** | [onStreamSubscribed](#IRTCRoomEventHandler-onstreamsubscribed) |
| **void** | [onRoomMessageReceived](#IRTCRoomEventHandler-onroommessagereceived) |
| **void** | [onRoomBinaryMessageReceived](#IRTCRoomEventHandler-onroombinarymessagereceived) |
| **void** | [onUserMessageReceived](#IRTCRoomEventHandler-onusermessagereceived) |
| **void** | [onUserBinaryMessageReceived](#IRTCRoomEventHandler-onuserbinarymessagereceived) |
| **void** | [onUserMessageSendResult](#IRTCRoomEventHandler-onusermessagesendresult) |
| **void** | [onRoomMessageSendResult](#IRTCRoomEventHandler-onroommessagesendresult) |
| **void** | [onVideoStreamBanned](#IRTCRoomEventHandler-onvideostreambanned) |
| **void** | [onAudioStreamBanned](#IRTCRoomEventHandler-onaudiostreambanned) |
| **void** | [onForwardStreamStateChanged](#IRTCRoomEventHandler-onforwardstreamstatechanged) |
| **void** | [onForwardStreamEvent](#IRTCRoomEventHandler-onforwardstreamevent) |
| **void** | [onNetworkQuality](#IRTCRoomEventHandler-onnetworkquality) |
| **void** | [[deprecated] onRoomWarning](#IRTCRoomEventHandler-onroomwarning) |
| **void** | [[deprecated] onRoomError](#IRTCRoomEventHandler-onroomerror) |
| **void** | [[deprecated] onStreamRemove](#IRTCRoomEventHandler-onstreamremove) |
| **void** | [[deprecated] onStreamAdd](#IRTCRoomEventHandler-onstreamadd) |


## 函数说明
<span id="IRTCRoomEventHandler-onleaveroom"></span>
### onLeaveRoom
```java
public void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onLeaveRoom(
    RTCRoomStats stats)
```
离开房间成功回调。  <br>
用户调用 [leaveRoom](Android-api.md#RTCRoom-leaveroom) 方法后，SDK 会停止所有的发布订阅流，并在释放所有通话相关的音视频资源后，通过此回调通知用户离开房间成功。  <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stats | **RTCRoomStats** | 保留参数，目前为空。 |


**注意**

+ 用户调用 [leaveRoom](Android-api.md#RTCRoom-leaveroom) 方法离开房间后，如果立即调用 [destroyRTCVideo](Android-api.md#RTCVideo-destroyrtcvideo) 方法销毁 RTC 引擎，则将无法收到此回调事件。  
+ 离开房间后，如果 App 需要使用系统音视频设备，则建议在收到此回调后再初始化音视频设备，否则可能由于 SDK 占用音视频设备导致初始化失败。  


<span id="IRTCRoomEventHandler-onroomstatechanged"></span>
### onRoomStateChanged
```java
public void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onRoomStateChanged(
    String roomId,
    String uid,
    int state,
    String extraInfo)
```
房间状态改变回调，加入房间、异常退出房间、发生房间相关的警告或错误时会收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| roomId | **String** | 房间 ID。 |
| uid | **String** | 用户 ID。 |
| state | **int** | 房间状态码。  <br/>• 0: 加入房间成功。  <br/>• !0: 加入房间失败、异常退房、发生房间相关的警告或错误。具体原因参看 [ErrorCode](Android-errorcode.md#errorcode) 及 [WarningCode](Android-errorcode.md#warningcode)。 |
| extraInfo | **String** | 额外信息，如 `{"elapsed":1187,"join_type":0}`。<br/>`join_type` 表示加入房间的类型，`0`为首次进房，`1`为重连进房。<br/>`elapsed` 表示加入房间耗时，即本地用户从调用 [joinRoom](Android-api.md#RTCRoom-joinroom) 到加入房间成功所经历的时间间隔，单位为 ms。 |


<span id="IRTCRoomEventHandler-onstreamstatechanged"></span>
### onStreamStateChanged
```java
public void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onStreamStateChanged(
    String roomId,
    String uid,
    int state,
    String extraInfo)
```
流状态改变回调，发生流相关的警告或错误时会收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| roomId | **String** | 房间 ID。 |
| uid | **String** | 用户 ID。 |
| state | **int** | 流状态码，参看 [ErrorCode](Android-errorcode.md#errorcode) 及 [WarningCode](Android-errorcode.md#warningcode)。 |
| extraInfo | **String** | 附加信息，目前为空。 |


<span id="IRTCRoomEventHandler-onroomwarning"></span>
### onRoomWarning
```java
public void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onRoomWarning(
    int warn)
```
> Deprecated  since 3.41 and will be deleted in 3.51, use [onRoomStateChanged](#IRTCRoomEventHandler-onroomstatechanged) and [onStreamStateChanged](#IRTCRoomEventHandler-onstreamstatechanged) instead.

发生警告回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| warn | **int** | 警告代码，参见 [WarningCode](Android-errorcode.md#warningcode) |


**注意**
SDK 运行时出现了（网络或媒体相关的）警告。SDK 通常会自动恢复，警告信息可以忽略。

<span id="IRTCRoomEventHandler-onroomerror"></span>
### onRoomError
```java
public void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onRoomError(
    int err)
```
> Deprecated  since 3.41 and will be deleted in 3.51, use [onRoomStateChanged](#IRTCRoomEventHandler-onroomstatechanged) and [onStreamStateChanged](#IRTCRoomEventHandler-onstreamstatechanged) instead.

发生错误回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| err | **int** | 错误代码，详情定义见: [ErrorCode](Android-errorcode.md#errorcode) |


**注意**
SDK 运行时出现了（网络或媒体相关的）错误。SDK 通常无法自动恢复，你可能需要干预。

<span id="IRTCRoomEventHandler-onavsyncstatechange"></span>
### onAVSyncStateChange
```java
public void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onAVSyncStateChange(
    AVSyncState state)
```
发布端调用 [setMultiDeviceAVSync](Android-api.md#RTCRoom-setmultideviceavsync) 后音视频同步状态发生改变时，会收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| state | **AVSyncState** | 音视频同步状态，参看 [AVSyncState](Android-keytype.md#avsyncstate)。 |


<span id="IRTCRoomEventHandler-onroomstats"></span>
### onRoomStats
```java
public void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onRoomStats(
    RTCRoomStats stats)
```
房间内通话统计信息回调。  <br>
用户进房开始通话后，每 2s 收到一次本回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stats | **RTCRoomStats** | 房间内的汇总统计数据。详见 [RTCRoomStats](Android-keytype.md#rtcroomstats)。 |


<span id="IRTCRoomEventHandler-onuserjoined"></span>
### onUserJoined
```java
public void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onUserJoined(
    UserInfo userInfo,
    int elapsed)
```
远端可见用户加入房间，或房内隐身用户切换为可见的回调。<br>
1.远端用户调用 [setUserVisibility](Android-api.md#RTCRoom-setuservisibility) 方法将自身设为可见后加入房间时，房间内其他用户将收到该事件。  <br>
2.远端可见用户断网后重新连入房间时，房间内其他用户将收到该事件。  <br>
3.房间内隐身远端用户调用 [setUserVisibility](Android-api.md#RTCRoom-setuservisibility) 方法切换至可见时，房间内其他用户将收到该事件。  <br>
4.新进房用户也会收到进房前已在房内的可见用户的进房回调通知。  <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| userInfo | **UserInfo** | 用户信息。参看 [UserInfo](Android-keytype.md#userinfo)。 |
| elapsed | **int** | 保留字段，无意义。 |


<span id="IRTCRoomEventHandler-onuserleave"></span>
### onUserLeave
```java
public void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onUserLeave(
    String uid,
    int reason)
```
远端用户离开房间，或切至不可见时，房间内其他用户会收到此事件

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | **String** | 离开房间，或切至不可见的的远端用户 ID。 |
| reason | **int** | 用户离开房间的原因：  <br/>• 0: 远端用户调用 [leaveRoom](Android-api.md#RTCRoom-leaveroom) 主动退出房间。 <br/>• 1: 远端用户因 Token 过期或网络原因等掉线。详细信息请参看[连接状态提示](https://www.volcengine.com/docs/6348/95376) <br/>• 2: 远端用户调用 [setUserVisibility](Android-api.md#RTCRoom-setuservisibility) 切换至不可见状态。 <br/>• 3: 服务端调用 OpenAPI 将该远端用户踢出房间。 |


<span id="IRTCRoomEventHandler-ontokenwillexpire"></span>
### onTokenWillExpire
```java
public void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onTokenWillExpire()
```
Token 进房权限过期前 30 秒将触发该回调。<br>
收到该回调后，你需调用 [updateToken](Android-api.md#RTCRoom-updatetoken) 更新 Token 进房权限。


**注意**
若 Token 进房权限过期且未及时更新： + 用户此时尝试进房会收到 [onRoomStateChanged](#IRTCRoomEventHandler-onroomstatechanged) 回调，提示错误码为 `-1000` Token 无效； 

+ 用户已在房间内则会被移出房间，本地用户会收到 [onRoomStateChanged](#IRTCRoomEventHandler-onroomstatechanged) 回调，提示错误码为 `-1009` Token 无效，同时远端用户会收到 [onUserLeave](#IRTCRoomEventHandler-onuserleave) 回调，提示原因为 `2` Token 进房权限过期。


<span id="IRTCRoomEventHandler-onpublishprivilegetokenwillexpire"></span>
### onPublishPrivilegeTokenWillExpire
```java
public void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onPublishPrivilegeTokenWillExpire()
```
Token 发布权限过期前 30 秒将触发该回调。<br>
收到该回调后，你需调用 [updateToken](Android-api.md#RTCRoom-updatetoken) 更新 Token 发布权限。


**注意**
若收到该回调后未及时更新 Token，Token 发布权限过期后： + 此时尝试发布流会收到 [onStreamStateChanged](#IRTCRoomEventHandler-onstreamstatechanged) 回调，提示错误码为 `-1002` 没有发布权限； 

+ 已在发布中的流会停止发布，发布端会收到 [onStreamStateChanged](#IRTCRoomEventHandler-onstreamstatechanged) 回调，提示错误码为 `-1002` 没有发布权限，同时远端用户会收到 [onUserUnpublishStream](#IRTCRoomEventHandler-onuserunpublishstream)/[onUserUnpublishScreen](#IRTCRoomEventHandler-onuserunpublishscreen) 回调，提示原因为 `6` 发流端发布权限过期。


<span id="IRTCRoomEventHandler-onsubscribeprivilegetokenwillexpire"></span>
### onSubscribePrivilegeTokenWillExpire
```java
public void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onSubscribePrivilegeTokenWillExpire()
```
Token 订阅权限过期前 30 秒将触发该回调。<br>
收到该回调后，你需调用 [updateToken](Android-api.md#RTCRoom-updatetoken) 更新 Token 订阅权限有效期。


**注意**
若收到该回调后未及时更新 Token，Token 订阅权限过期后，尝试新订阅流会失败，已订阅的流会取消订阅，并且会收到 [onStreamStateChanged](#IRTCRoomEventHandler-onstreamstatechanged) 回调，提示错误码为 `-1003` 没有订阅权限。

<span id="IRTCRoomEventHandler-onuserpublishstream"></span>
### onUserPublishStream
```java
public void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onUserPublishStream(
    String uid,
    MediaStreamType type)
```
房间内新增远端摄像头/麦克风采集的媒体流的回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | **String** | 远端流发布用户的用户 ID。 |
| type | **MediaStreamType** | 远端媒体流的类型，参看 [MediaStreamType](Android-keytype.md#mediastreamtype)。 |


**注意**
当房间内的远端用户调用 [publishStream](Android-api.md#RTCRoom-publishstream) 成功发布由摄像头/麦克风采集的媒体流时，本地用户会收到该回调，此时本地用户可以自行选择是否调用 [subscribeStream](Android-api.md#RTCRoom-subscribestream) 订阅此流。

<span id="IRTCRoomEventHandler-onuserunpublishstream"></span>
### onUserUnpublishStream
```java
public void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onUserUnpublishStream(
    String uid,
    MediaStreamType type,
    StreamRemoveReason reason)
```
房间内远端摄像头/麦克风采集的媒体流移除的回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | **String** | 移除的远端流发布用户的用户 ID。 |
| type | **MediaStreamType** | 移除的远端流类型，参看 [MediaStreamType](Android-keytype.md#mediastreamtype)。 |
| reason | **StreamRemoveReason** | 远端流移除的原因，参看 [StreamRemoveReason](Android-keytype.md#streamremovereason)。 |


**注意**
收到该回调通知后，你可以自行选择是否调用 [unsubscribeStream](Android-api.md#RTCRoom-unsubscribestream) 取消订阅此流。

<span id="IRTCRoomEventHandler-onuserpublishscreen"></span>
### onUserPublishScreen
```java
public void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onUserPublishScreen(
    String uid,
    MediaStreamType type)
```
房间内新增远端屏幕共享音视频流的回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | **String** | 远端流发布用户的用户 ID。 |
| type | **MediaStreamType** | 远端媒体流的类型，参看 [MediaStreamType](Android-keytype.md#mediastreamtype)。 |


**注意**
当房间内的远端用户调用 [publishScreen](Android-api.md#RTCRoom-publishscreen) 成功发布来自屏幕共享的音视频流时，本地用户会收到该回调，此时本地用户可以自行选择是否调用 [subscribeScreen](Android-api.md#RTCRoom-subscribescreen) 订阅此流。

<span id="IRTCRoomEventHandler-onuserunpublishscreen"></span>
### onUserUnpublishScreen
```java
public void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onUserUnpublishScreen(
    String uid,
    MediaStreamType type,
    StreamRemoveReason reason)
```
房间内远端屏幕共享音视频流移除的回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | **String** | 移除的远端流发布用户的用户 ID。 |
| type | **MediaStreamType** | 移除的远端流类型，参看 [MediaStreamType](Android-keytype.md#mediastreamtype)。 |
| reason | **StreamRemoveReason** | 远端流移除的原因，参看 [StreamRemoveReason](Android-keytype.md#streamremovereason)。 |


**注意**
收到该回调通知后，你可以自行选择是否调用 [unsubscribeScreen](Android-api.md#RTCRoom-unsubscribescreen) 取消订阅此流。

<span id="IRTCRoomEventHandler-onlocalstreamstats"></span>
### onLocalStreamStats
```java
public void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onLocalStreamStats(
    LocalStreamStats stats)
```
本地流数据统计以及网络质量回调。  <br>
本地用户发布流成功后，SDK 会周期性（2s）的通过此回调事件通知用户发布的流在此次统计周期内的质量统计信息。  <br>
统计信息通过 [LocalStreamStats](Android-keytype.md#localstreamstats) 类型的回调参数传递给用户，其中包括发送音视频比特率、发送帧率、编码帧率，网络质量等。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stats | **LocalStreamStats** | 音视频流以及网络状况统计信息。参见 [LocalStreamStats](Android-keytype.md#localstreamstats)。 |


<span id="IRTCRoomEventHandler-onremotestreamstats"></span>
### onRemoteStreamStats
```java
public void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onRemoteStreamStats(
    RemoteStreamStats stats)
```
本地订阅的远端音/视频流数据统计以及网络质量回调。  <br>
本地用户订阅流成功后，SDK 会周期性（2s）的通过此回调事件通知用户订阅的流在此次统计周期内的质量统计信息，包括：发送音视频比特率、发送帧率、编码帧率，网络质量等。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stats | **RemoteStreamStats** | 音视频流以及网络状况统计信息。参见 [RemoteStreamStats](Android-keytype.md#remotestreamstats)。 |


<span id="IRTCRoomEventHandler-onstreamremove"></span>
### onStreamRemove
```java
public void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onStreamRemove(
    RTCStream stream,
    StreamRemoveReason reason)
```
> Deprecated  since 3.36 and will be deleted in 3.51, use [onUserUnpublishStream](#IRTCRoomEventHandler-onuserunpublishstream) and [onUserUnpublishScreen](#IRTCRoomEventHandler-onuserunpublishscreen) instead.

房间内远端流移除回调。  <br>
房间内的远端用户停止发布音视频流时，本地用户会收到此回调通知。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stream | **RTCStream** | 流的属性，参看 [RTCStream](Android-keytype.md#rtcstream)。 |
| reason | **StreamRemoveReason** | 远端流移除的原因，参看 [StreamRemoveReason](Android-keytype.md#streamremovereason)。 |


<span id="IRTCRoomEventHandler-onstreamadd"></span>
### onStreamAdd
```java
public void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onStreamAdd(
    RTCStream stream)
```
> Deprecated  since 3.36 and will be deleted in 3.51, use [onUserPublishStream](#IRTCRoomEventHandler-onuserpublishstream) and [onUserPublishScreen](#IRTCRoomEventHandler-onuserpublishscreen) instead.

房间内新流发布回调。  <br>
房间内的远端用户发布新的音视频流时，本地用户会收到此回调通知。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stream | **RTCStream** | 流的属性，详见 [RTCStream](Android-keytype.md#rtcstream) 数据类型。 |


<span id="IRTCRoomEventHandler-onstreamsubscribed"></span>
### onStreamSubscribed
```java
public void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onStreamSubscribed(
    int stateCode,
    String userId,
    SubscribeConfig info)
```
关于订阅媒体流状态改变的回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stateCode | **int** | 订阅媒体流状态，参看 [SubscribeState](Android-keytype.md#subscribestate) |
| userId | **String** | 流发布用户的用户 ID |
| info | **SubscribeConfig** | 流的属性，参看 [SubscribeConfig](Android-keytype.md#subscribeconfig) |


**注意**
本地用户收到该回调的时机包括：  

+ 调用 [subscribeStream](Android-api.md#RTCRoom-subscribestream) 或 [unsubscribeStream](Android-api.md#RTCRoom-unsubscribestream) 订阅/取消订阅指定远端摄像头音视频流后；  
+ 调用 [subscribeScreen](Android-api.md#RTCRoom-subscribescreen) 或 [unsubscribeScreen](Android-api.md#RTCRoom-unsubscribescreen) 订阅/取消订阅指定远端屏幕共享流后。


<span id="IRTCRoomEventHandler-onroommessagereceived"></span>
### onRoomMessageReceived
```java
public void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onRoomMessageReceived(
    String uid,
    String message)
```
接收到房间内广播消息的回调。<br>
房间内其他用户调用 [sendRoomMessage](Android-api.md#RTCRoom-sendroommessage) 发送广播消息时，收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | **String** | 消息发送者 ID |
| message | **String** | 收到的消息内容 |


<span id="IRTCRoomEventHandler-onroombinarymessagereceived"></span>
### onRoomBinaryMessageReceived
```java
public void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onRoomBinaryMessageReceived(
    String uid,
    ByteBuffer message)
```
收到房间内广播二进制消息的回调。<br>
房间内其他用户调用 [sendRoomBinaryMessage](Android-api.md#RTCRoom-sendroombinarymessage) 发送广播二进制消息时，收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | **String** | 消息发送者 ID |
| message | **ByteBuffer** | 收到的二进制消息内容 |


<span id="IRTCRoomEventHandler-onusermessagereceived"></span>
### onUserMessageReceived
```java
public void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onUserMessageReceived(
    String uid,
    String message)
```
收到来自房间中其他用户通过 [sendUserMessage](Android-api.md#RTCRoom-sendusermessage) 发来的点对点文本消息时，会收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | **String** | 消息发送者的用户 ID 。 |
| message | **String** | 收到的文本消息内容。 |


<span id="IRTCRoomEventHandler-onuserbinarymessagereceived"></span>
### onUserBinaryMessageReceived
```java
public void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onUserBinaryMessageReceived(
    String uid,
    ByteBuffer message)
```
收到来自房间中其他用户通过 [sendUserBinaryMessage](Android-api.md#RTCRoom-senduserbinarymessage) 发来的点对点二进制消息时，会收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | **String** | 消息发送者的用户 ID 。 |
| message | **ByteBuffer** | 收到的二进制消息内容。 |


<span id="IRTCRoomEventHandler-onusermessagesendresult"></span>
### onUserMessageSendResult
```java
public void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onUserMessageSendResult(
    long msgid,
    int error)
```
向房间内单个用户发送文本或二进制消息后（P2P），消息发送方会收到该消息发送结果回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| msgid | **long** | 本条消息的 ID。 |
| error | **int** | 文本或二进制消息发送结果，详见 [UserMessageSendResult](Android-errorcode.md#usermessagesendresult) |


**注意**
调用 [sendUserMessage](Android-api.md#RTCRoom-sendusermessage) 或 [sendUserBinaryMessage](Android-api.md#RTCRoom-senduserbinarymessage) 接口，才能收到此回调。

<span id="IRTCRoomEventHandler-onroommessagesendresult"></span>
### onRoomMessageSendResult
```java
public void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onRoomMessageSendResult(
    long msgid,
    int error)
```
调用 [sendRoomMessage](Android-api.md#RTCRoom-sendroommessage) 或 [sendRoomBinaryMessage](Android-api.md#RTCRoom-sendroombinarymessage) 向房间内群发文本或二进制消息后，消息发送方会收到该消息发送结果回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| msgid | **long** | 本条消息的 ID。 |
| error | **int** | 消息发送结果，详见 [RoomMessageSendResult](Android-errorcode.md#roommessagesendresult) |


<span id="IRTCRoomEventHandler-onvideostreambanned"></span>
### onVideoStreamBanned
```java
public void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onVideoStreamBanned(
    String uid,
    boolean banned)
```
通过调用服务端 BanUserStream/UnbanUserStream 方法禁用/解禁指定房间内指定用户视频流的发送时，触发此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | **String** | 被禁用/解禁的视频流用户 ID |
| banned | **boolean** | 视频流发送状态 <br/>• true: 视频流发送被禁用 <br/>• false: 视频流发送被解禁 |


**注意**

+ 房间内指定用户被禁止/解禁视频流发送时，房间内所有用户都会收到该回调。  
+ 若被封禁用户断网或退房后再进房，则依然是封禁状态，且房间内所有人会再次收到该回调。  
+ 指定用户被封禁后，房间内其他用户退房后再进房，会再次收到该回调。  
+ 同一房间解散后再次创建，房间内状态清空。


<span id="IRTCRoomEventHandler-onaudiostreambanned"></span>
### onAudioStreamBanned
```java
public void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onAudioStreamBanned(
    String uid,
    boolean banned)
```
通过调用服务端 BanUserStream/UnbanUserStream 方法禁用/解禁指定房间内指定用户音频流的发送时，触发此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | **String** | 被禁用/解禁的音频流用户 ID |
| banned | **boolean** | 音频流发送状态 <br/>• true: 音频流发送被禁用 <br/>• false: 音频流发送被解禁 |


**注意**

+ 房间内指定用户被禁止/解禁音频流发送时，房间内所有用户都会收到该回调。  
+ 若被封禁用户断网或退房后再进房，则依然是封禁状态，且房间内所有人会再次收到该回调。  
+ 指定用户被封禁后，房间内其他用户退房后再进房，会再次收到该回调。  
+ 在控制台开启大会模式后，只有被封禁/解禁用户会收到该回调。
+ 同一房间解散后再次创建，房间内状态清空。


<span id="IRTCRoomEventHandler-onforwardstreamstatechanged"></span>
### onForwardStreamStateChanged
```java
public void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onForwardStreamStateChanged(
    ForwardStreamStateInfo[] stateInfos)
```
跨房间媒体流转发状态和错误回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stateInfos | **ForwardStreamStateInfo[]** | 跨房间媒体流转发目标房间信息数组，详见 [ForwardStreamStateInfo](Android-keytype.md#forwardstreamstateinfo) |


<span id="IRTCRoomEventHandler-onforwardstreamevent"></span>
### onForwardStreamEvent
```java
public void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onForwardStreamEvent(
    ForwardStreamEventInfo[] eventInfos)
```
跨房间媒体流转发事件回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| eventInfos | **ForwardStreamEventInfo[]** | 跨房间媒体流转发目标房间事件数组，详见 [ForwardStreamEventInfo](Android-keytype.md#forwardstreameventinfo) |


<span id="IRTCRoomEventHandler-onnetworkquality"></span>
### onNetworkQuality
```java
public void com.ss.bytertc.engine.handler.IRTCRoomEventHandler.onNetworkQuality(
    NetworkQualityStats localQuality,
    NetworkQualityStats[] remoteQualities)
```
加入房间并发布或订阅流后， 以每 2 秒一次的频率，报告本地用户和已订阅的远端用户的上下行网络质量信息。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| localQuality | **NetworkQualityStats** | 本地网络质量，详见 [NetworkQualityStats](Android-keytype.md#networkqualitystats)。 |
| remoteQualities | **NetworkQualityStats[]** | 已订阅用户的网络质量，详见 [NetworkQualityStats](Android-keytype.md#networkqualitystats)。 |


**注意**
更多通话中的监测接口，详见[通话中质量监测](https://www.volcengine.com/docs/6348/106866)。

# IRTCVideoEventHandler
```java
public abstract class com.ss.bytertc.engine.handler.IRTCVideoEventHandler
```

音视频引擎事件回调接口


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **void** | [onWarning](#IRTCVideoEventHandler-onwarning) |
| **void** | [onError](#IRTCVideoEventHandler-onerror) |
| **void** | [onSysStats](#IRTCVideoEventHandler-onsysstats) |
| **void** | [onNetworkTypeChanged](#IRTCVideoEventHandler-onnetworktypechanged) |
| **void** | [onUserStartVideoCapture](#IRTCVideoEventHandler-onuserstartvideocapture) |
| **void** | [onUserStopVideoCapture](#IRTCVideoEventHandler-onuserstopvideocapture) |
| **void** | [onCreateRoomStateChanged](#IRTCVideoEventHandler-oncreateroomstatechanged) |
| **void** | [onUserStartAudioCapture](#IRTCVideoEventHandler-onuserstartaudiocapture) |
| **void** | [onUserStopAudioCapture](#IRTCVideoEventHandler-onuserstopaudiocapture) |
| **void** | [onRemoteAudioStateChanged](#IRTCVideoEventHandler-onremoteaudiostatechanged) |
| **void** | [onRemoteVideoStateChanged](#IRTCVideoEventHandler-onremotevideostatechanged) |
| **void** | [onFirstRemoteVideoFrameRendered](#IRTCVideoEventHandler-onfirstremotevideoframerendered) |
| **void** | [onFirstRemoteVideoFrameDecoded](#IRTCVideoEventHandler-onfirstremotevideoframedecoded) |
| **void** | [onFirstLocalVideoFrameCaptured](#IRTCVideoEventHandler-onfirstlocalvideoframecaptured) |
| **void** | [onLocalVideoSizeChanged](#IRTCVideoEventHandler-onlocalvideosizechanged) |
| **void** | [onRemoteVideoSizeChanged](#IRTCVideoEventHandler-onremotevideosizechanged) |
| **void** | [onConnectionStateChanged](#IRTCVideoEventHandler-onconnectionstatechanged) |
| **void** | [onAudioRouteChanged](#IRTCVideoEventHandler-onaudioroutechanged) |
| **void** | [onFirstLocalAudioFrame](#IRTCVideoEventHandler-onfirstlocalaudioframe) |
| **void** | [onFirstRemoteAudioFrame](#IRTCVideoEventHandler-onfirstremoteaudioframe) |
| **void** | [onLogReport](#IRTCVideoEventHandler-onlogreport) |
| **void** | [onSEIMessageReceived](#IRTCVideoEventHandler-onseimessagereceived) |
| **void** | [onSEIStreamUpdate](#IRTCVideoEventHandler-onseistreamupdate) |
| **void** | [onLoginResult](#IRTCVideoEventHandler-onloginresult) |
| **void** | [onLogout](#IRTCVideoEventHandler-onlogout) |
| **void** | [onServerParamsSetResult](#IRTCVideoEventHandler-onserverparamssetresult) |
| **void** | [onGetPeerOnlineStatus](#IRTCVideoEventHandler-ongetpeeronlinestatus) |
| **void** | [onUserMessageReceivedOutsideRoom](#IRTCVideoEventHandler-onusermessagereceivedoutsideroom) |
| **void** | [onUserBinaryMessageReceivedOutsideRoom](#IRTCVideoEventHandler-onuserbinarymessagereceivedoutsideroom) |
| **void** | [onUserMessageSendResultOutsideRoom](#IRTCVideoEventHandler-onusermessagesendresultoutsideroom) |
| **void** | [onServerMessageSendResult](#IRTCVideoEventHandler-onservermessagesendresult) |
| **void** | [onNetworkDetectionResult](#IRTCVideoEventHandler-onnetworkdetectionresult) |
| **void** | [onNetworkDetectionStopped](#IRTCVideoEventHandler-onnetworkdetectionstopped) |
| **void** | [onSimulcastSubscribeFallback](#IRTCVideoEventHandler-onsimulcastsubscribefallback) |
| **void** | [onPerformanceAlarms](#IRTCVideoEventHandler-onperformancealarms) |
| **void** | [onAudioFrameSendStateChanged](#IRTCVideoEventHandler-onaudioframesendstatechanged) |
| **void** | [onVideoFrameSendStateChanged](#IRTCVideoEventHandler-onvideoframesendstatechanged) |
| **void** | [onScreenVideoFrameSendStateChanged](#IRTCVideoEventHandler-onscreenvideoframesendstatechanged) |
| **void** | [onAudioFramePlayStateChanged](#IRTCVideoEventHandler-onaudioframeplaystatechanged) |
| **void** | [onVideoFramePlayStateChanged](#IRTCVideoEventHandler-onvideoframeplaystatechanged) |
| **void** | [onScreenVideoFramePlayStateChanged](#IRTCVideoEventHandler-onscreenvideoframeplaystatechanged) |
| **void** | [onAudioDeviceStateChanged](#IRTCVideoEventHandler-onaudiodevicestatechanged) |
| **void** | [onVideoDeviceStateChanged](#IRTCVideoEventHandler-onvideodevicestatechanged) |
| **void** | [onAudioDeviceWarning](#IRTCVideoEventHandler-onaudiodevicewarning) |
| **void** | [onVideoDeviceWarning](#IRTCVideoEventHandler-onvideodevicewarning) |
| **void** | [onHttpProxyState](#IRTCVideoEventHandler-onhttpproxystate) |
| **void** | [onHttpsProxyState](#IRTCVideoEventHandler-onhttpsproxystate) |
| **void** | [onSocks5ProxyState](#IRTCVideoEventHandler-onsocks5proxystate) |
| **void** | [onRecordingStateUpdate](#IRTCVideoEventHandler-onrecordingstateupdate) |
| **void** | [onRecordingProgressUpdate](#IRTCVideoEventHandler-onrecordingprogressupdate) |
| **void** | [onAudioRecordingStateUpdate](#IRTCVideoEventHandler-onaudiorecordingstateupdate) |
| **void** | [onAudioMixingStateChanged](#IRTCVideoEventHandler-onaudiomixingstatechanged) |
| **void** | [onAudioMixingPlayingProgress](#IRTCVideoEventHandler-onaudiomixingplayingprogress) |
| **void** | [onLocalAudioPropertiesReport](#IRTCVideoEventHandler-onlocalaudiopropertiesreport) |
| **void** | [onAudioPlaybackDeviceTestVolume](#IRTCVideoEventHandler-onaudioplaybackdevicetestvolume) |
| **void** | [onRemoteAudioPropertiesReport](#IRTCVideoEventHandler-onremoteaudiopropertiesreport) |
| **void** | [onActiveSpeaker](#IRTCVideoEventHandler-onactivespeaker) |
| **void** | [onStreamSyncInfoReceived](#IRTCVideoEventHandler-onstreamsyncinforeceived) |
| **void** | [onPushPublicStreamResult](#IRTCVideoEventHandler-onpushpublicstreamresult) |
| **void** | [onPlayPublicStreamResult](#IRTCVideoEventHandler-onplaypublicstreamresult) |
| **void** | [onPublicStreamSEIMessageReceived](#IRTCVideoEventHandler-onpublicstreamseimessagereceived) |
| **void** | [onFirstPublicStreamVideoFrameDecoded](#IRTCVideoEventHandler-onfirstpublicstreamvideoframedecoded) |
| **void** | [onFirstPublicStreamAudioFrame](#IRTCVideoEventHandler-onfirstpublicstreamaudioframe) |
| **void** | [onEchoTestResult](#IRTCVideoEventHandler-onechotestresult) |
| **void** | [onCloudProxyConnected](#IRTCVideoEventHandler-oncloudproxyconnected) |
| **void** | [onNetworkTimeSynchronized](#IRTCVideoEventHandler-onnetworktimesynchronized) |
| **void** | [onLicenseWillExpire](#IRTCVideoEventHandler-onlicensewillexpire) |
| **void** | [[deprecated] onUserMuteAudio](#IRTCVideoEventHandler-onusermuteaudio) |
| **void** | [[deprecated] onUserMuteVideo](#IRTCVideoEventHandler-onusermutevideo) |
| **void** | [[deprecated] onLocalAudioStateChanged](#IRTCVideoEventHandler-onlocalaudiostatechanged) |
| **void** | [[deprecated] onLocalVideoStateChanged](#IRTCVideoEventHandler-onlocalvideostatechanged) |
| **void** | [[deprecated] onAudioPlaybackDeviceChanged](#IRTCVideoEventHandler-onaudioplaybackdevicechanged) |
| **void** | [[deprecated] onMediaDeviceStateChanged](#IRTCVideoEventHandler-onmediadevicestatechanged) |
| **void** | [[deprecated] onMediaDeviceWarning](#IRTCVideoEventHandler-onmediadevicewarning) |


## 函数说明
<span id="IRTCVideoEventHandler-onwarning"></span>
### onWarning
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onWarning(
    int warn)
```
发生警告回调。  <br>
SDK 运行时出现了警告。SDK 通常会自动恢复，警告信息可以忽略。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| warn | **int** | 警告代码，参见 [WarningCode](Android-errorcode.md#warningcode) |


<span id="IRTCVideoEventHandler-onerror"></span>
### onError
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onError(
    int err)
```
发生错误回调。<br>
SDK 运行时出现了网络或媒体相关的错误，且无法自动恢复时触发此回调。<br>
你可能需要干预.

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| err | **int** | 错误代码，详情定义见: [ErrorCode](Android-errorcode.md#errorcode) |


<span id="IRTCVideoEventHandler-onsysstats"></span>
### onSysStats
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onSysStats(
    SysStats stats)
```
每2秒发生回调，通知当前cpu，内存使用的信息。  <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stats | **SysStats** | cpu，内存信息。详见 [SysStats](Android-keytype.md#sysstats) 数据类型。 |


<span id="IRTCVideoEventHandler-onnetworktypechanged"></span>
### onNetworkTypeChanged
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onNetworkTypeChanged(
    int type)
```
SDK 当前网络连接类型改变回调。当 SDK 的当前网络连接类型发生改变时回调该事件。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| type | **int** | 网络类型。  <br/>• -1： 网络连接类型未知。  <br/>• 0： 网络连接已断开。  <br/>• 1： LAN  <br/>• 2： Wi-Fi,包含热点  <br/>• 3： 2G 移动网络  <br/>• 4： 3G 移动网络  <br/>• 5： 4G 移动网络  <br/>• 6： 5G 移动网络 |


<span id="IRTCVideoEventHandler-onusermuteaudio"></span>
### onUserMuteAudio
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onUserMuteAudio(
    String room_id,
    String uid,
    MuteState muteState)
```
> Deprecated  since 3.36 and will be deleted in 3.51, use [onUserPublishStream](#IRTCRoomEventHandler-onuserpublishstream), [onUserPublishScreen](#IRTCRoomEventHandler-onuserpublishscreen), [onUserUnpublishStream](#IRTCRoomEventHandler-onuserunpublishstream) and [onUserUnpublishScreen](#IRTCRoomEventHandler-onuserunpublishscreen) instead.

房间内用户暂停/恢复发送音频流时，房间内其他用户会收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | **String** | 改变本地音频发送状态的用户 ID |
| muteState | **MuteState** | 发送状态，参看 [MuteState](Android-keytype.md#mutestate) |


<span id="IRTCVideoEventHandler-onusermutevideo"></span>
### onUserMuteVideo
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onUserMuteVideo(
    String roomId,
    String uid,
    MuteState muteState)
```
> Deprecated  since 3.36 and will be deleted in 3.51, use [onUserPublishStream](#IRTCRoomEventHandler-onuserpublishstream), [onUserPublishScreen](#IRTCRoomEventHandler-onuserpublishscreen), [onUserUnpublishStream](#IRTCRoomEventHandler-onuserunpublishstream) and [onUserUnpublishScreen](#IRTCRoomEventHandler-onuserunpublishscreen) instead.

房间内用户暂停/恢复发送视频流时，房间内其他用户会收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | **String** | 暂停/恢复发送视频流的用户 ID。 |
| muteState | **MuteState** | 视频流的发送状态。参看 [MuteState](Android-keytype.md#mutestate)。 |


<span id="IRTCVideoEventHandler-onuserstartvideocapture"></span>
### onUserStartVideoCapture
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onUserStartVideoCapture(
    String roomId,
    String uid)
```
房间内的可见用户调用 [startVideoCapture](Android-api.md#RTCVideo-startvideocapture) 开启内部视频采集时，房间内其他用户会收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| roomId | **String** | 开启视频采集的远端用户所在的房间 ID |
| uid | **String** | 开启视频采集的远端用户 ID |


<span id="IRTCVideoEventHandler-onuserstopvideocapture"></span>
### onUserStopVideoCapture
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onUserStopVideoCapture(
    String roomId,
    String uid)
```
房间内的可见用户调用 [stopVideoCapture](Android-api.md#RTCVideo-stopvideocapture) 关闭内部视频采集时，房间内其他用户会收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| roomId | **String** | 关闭视频采集的远端用户所在的房间 ID |
| uid | **String** | 关闭视频采集的远端用户 ID |


<span id="IRTCVideoEventHandler-oncreateroomstatechanged"></span>
### onCreateRoomStateChanged
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onCreateRoomStateChanged(
    String roomId,
    int errorCode)
```
创建房间失败回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| roomId | **String** | 房间 ID。 |
| errorCode | **int** | 创建房间错误码，具体原因参看 [ErrorCode](Android-errorcode.md#errorcode)。 |


<span id="IRTCVideoEventHandler-onuserstartaudiocapture"></span>
### onUserStartAudioCapture
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onUserStartAudioCapture(
    String roomId,
    String uid)
```
房间内的用户调用 [startAudioCapture](Android-api.md#RTCVideo-startaudiocapture) 开启音频采集时，房间内其他用户会收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| roomId | **String** | 开启音频采集的远端用户所在的房间 ID |
| uid | **String** | 开启音频采集的远端用户 ID |


<span id="IRTCVideoEventHandler-onuserstopaudiocapture"></span>
### onUserStopAudioCapture
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onUserStopAudioCapture(
    String roomId,
    String uid)
```
房间内的用户调用 [stopAudioCapture](Android-api.md#RTCVideo-stopaudiocapture) 关闭音频采集时，房间内其他用户会收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| roomId | **String** | 关闭音频采集的远端用户所在的房间 ID |
| uid | **String** | 关闭音频采集的远端用户 ID |


<span id="IRTCVideoEventHandler-onlocalaudiostatechanged"></span>
### onLocalAudioStateChanged
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onLocalAudioStateChanged(
    LocalAudioStreamState state,
    LocalAudioStreamError error)
```
> Deprecated  since 3.50 and will be deleted in 3.55. Use [onAudioDeviceStateChanged](#IRTCVideoEventHandler-onaudiodevicestatechanged) instead.

本地音频流的状态发生改变时，收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| state | **LocalAudioStreamState** | 本地音频设备的状态，详见 [LocalAudioStreamState](Android-keytype.md#localaudiostreamstate) |
| error | **LocalAudioStreamError** | 本地音频流状态改变时的错误码，详见 [LocalAudioStreamError](Android-keytype.md#localaudiostreamerror) |


<span id="IRTCVideoEventHandler-onremoteaudiostatechanged"></span>
### onRemoteAudioStateChanged
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onRemoteAudioStateChanged(
    RemoteStreamKey key,
    RemoteAudioState state,
    RemoteAudioStateChangeReason reason)
```
用户订阅来自远端的音频流状态发生改变时，会收到此回调，了解当前的远端音频流状态。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| key | **RemoteStreamKey** | 远端流信息, 详见 [RemoteStreamKey](Android-keytype.md#remotestreamkey) |
| state | **RemoteAudioState** | 远端音频流状态，详见 [RemoteAudioState](Android-keytype.md#remoteaudiostate) |
| reason | **RemoteAudioStateChangeReason** | 远端音频流状态改变的原因，详见 [RemoteAudioStateChangeReason](Android-keytype.md#remoteaudiostatechangereason) |


<span id="IRTCVideoEventHandler-onlocalvideostatechanged"></span>
### onLocalVideoStateChanged
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onLocalVideoStateChanged(
    StreamIndex streamIndex,
    LocalVideoStreamState state,
    LocalVideoStreamError error)
```
> Deprecated  since 3.50 and will be deleted in 3.55. Use [onVideoDeviceStateChanged](#IRTCVideoEventHandler-onvideodevicestatechanged) instead.

本地视频流的状态发生改变时，收到该事件。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamIndex | **StreamIndex** | 流属性，参看 [StreamIndex](Android-keytype.md#streamindex-2) |
| state | **LocalVideoStreamState** | 本地视频流状态，参看 [LocalVideoStreamState](Android-keytype.md#localvideostreamstate) |
| error | **LocalVideoStreamError** | 本地视频状态改变时的错误码，参看 [LocalVideoStreamError](Android-keytype.md#localvideostreamerror) |


<span id="IRTCVideoEventHandler-onremotevideostatechanged"></span>
### onRemoteVideoStateChanged
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onRemoteVideoStateChanged(
    RemoteStreamKey streamKey,
    RemoteVideoState videoState,
    RemoteVideoStateChangeReason videoStateReason)
```
远端视频流的状态发生改变时，房间内订阅此流的用户会收到该事件。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamKey | **RemoteStreamKey** | 远端视频流信息，房间、用户 ID、流属性等，参看 [RemoteStreamKey](Android-keytype.md#remotestreamkey) |
| videoState | **RemoteVideoState** | 远端视频流状态，参看 [RemoteVideoState](Android-keytype.md#remotevideostate) |
| videoStateReason | **RemoteVideoStateChangeReason** | 远端视频流状态改变原因，参看 [RemoteVideoStateChangeReason](Android-keytype.md#remotevideostatechangereason) |


<span id="IRTCVideoEventHandler-onfirstremotevideoframerendered"></span>
### onFirstRemoteVideoFrameRendered
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onFirstRemoteVideoFrameRendered(
    RemoteStreamKey remoteStreamKey,
    VideoFrameInfo frameInfo)
```
SDK 内部渲染成功远端视频流首帧后，收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| remoteStreamKey | **RemoteStreamKey** | 远端流信息，参看 [RemoteStreamKey](Android-keytype.md#remotestreamkey) |
| frameInfo | **VideoFrameInfo** | 视频帧信息，参看 [VideoFrameInfo](Android-keytype.md#videoframeinfo) |


<span id="IRTCVideoEventHandler-onfirstremotevideoframedecoded"></span>
### onFirstRemoteVideoFrameDecoded
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onFirstRemoteVideoFrameDecoded(
    RemoteStreamKey remoteStreamKey,
    VideoFrameInfo frameInfo)
```
SDK 接收并解码远端视频流首帧后，收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| remoteStreamKey | **RemoteStreamKey** | 远端流信息，参看 [RemoteStreamKey](Android-keytype.md#remotestreamkey) |
| frameInfo | **VideoFrameInfo** | 视频帧信息，参看 [VideoFrameInfo](Android-keytype.md#videoframeinfo) |


**注意**

 + 对于主流，进入房间后，仅在发布端第一次发布的时候，订阅端会收到该回调，此后不受重新发布的影响，只要不重新加入房间，就不会再收到该回调。
 + 对于屏幕流，用户每次重新发布屏幕视频流在订阅端都会重新触发一次该回调。

<span id="IRTCVideoEventHandler-onfirstlocalvideoframecaptured"></span>
### onFirstLocalVideoFrameCaptured
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onFirstLocalVideoFrameCaptured(
    StreamIndex streamIndex,
    VideoFrameInfo frameInfo)
```
RTC SDK 在本地完成第一帧视频帧或屏幕视频帧采集时，收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamIndex | **StreamIndex** | 流属性，参看 [StreamIndex](Android-keytype.md#streamindex-2) |
| frameInfo | **VideoFrameInfo** | 视频信息，参看 [VideoFrameInfo](Android-keytype.md#videoframeinfo) |


**注意**
对于采集到的本地视频帧，你可以调用 [setLocalVideoCanvas](Android-api.md#RTCVideo-setlocalvideocanvas) 或 [setLocalVideoSink](Android-api.md#RTCVideo-setlocalvideosink) 在本地渲染。

<span id="IRTCVideoEventHandler-onlocalvideosizechanged"></span>
### onLocalVideoSizeChanged
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onLocalVideoSizeChanged(
    StreamIndex streamIndex,
    VideoFrameInfo frameInfo)
```
本地预览视频大小或旋转信息发生改变时，收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamIndex | **StreamIndex** | 流属性，参看 [StreamIndex](Android-keytype.md#streamindex-2) |
| frameInfo | **VideoFrameInfo** | 视频帧信息，参看 [VideoFrameInfo](Android-keytype.md#videoframeinfo) |


<span id="IRTCVideoEventHandler-onremotevideosizechanged"></span>
### onRemoteVideoSizeChanged
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onRemoteVideoSizeChanged(
    RemoteStreamKey remoteStreamKey,
    VideoFrameInfo frameInfo)
```
远端视频大小或旋转信息发生改变时，房间内订阅此视频流的用户会收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| remoteStreamKey | **RemoteStreamKey** | 远端流信息，参看 [StreamIndex](Android-keytype.md#streamindex-2) |
| frameInfo | **VideoFrameInfo** | 视频帧信息，参看 [VideoFrameInfo](Android-keytype.md#videoframeinfo) |


<span id="IRTCVideoEventHandler-onconnectionstatechanged"></span>
### onConnectionStateChanged
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onConnectionStateChanged(
    int state,
    int reason)
```
回调 SDK 与信令服务器连接状态相关事件。当 SDK 与信令服务器的网络连接状态改变时回调该事件。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| state | **int** | 当前 SDK 与信令服务器连接状态。 详细定义参见 [ConnectionState](Android-keytype.md#connectionstate) |
| reason | **int** | 引起信令服务器连接状态发生改变的原因，目前未启用固定为 -1 。 |


**注意**
更多信息参见 [连接状态提示](https://www.volcengine.com/docs/6348/95376)。

<span id="IRTCVideoEventHandler-onaudioplaybackdevicechanged"></span>
### onAudioPlaybackDeviceChanged
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onAudioPlaybackDeviceChanged(
    AudioPlaybackDevice device)
```
> Deprecated  since 3.38 and will be deleted in 3.51, use [onAudioRouteChanged](#IRTCVideoEventHandler-onaudioroutechanged) instead.

音频播放设备变化时，收到该回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| device | **AudioPlaybackDevice** | 新的音频设备，详见 [AudioPlaybackDevice](Android-keytype.md#audioplaybackdevice) |


**注意**
音频设备设置与音频路由策略，详见 [setAudioPlaybackDevice](Android-api.md#RTCVideo-setaudioplaybackdevice)

<span id="IRTCVideoEventHandler-onaudioroutechanged"></span>
### onAudioRouteChanged
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onAudioRouteChanged(
    AudioRoute route)
```
音频播放路由变化时，收到该回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| route | **AudioRoute** | 新的音频播放路由，详见 [AudioRoute](Android-keytype.md#audioroute) |


**注意**
插拔音频外设，或调用 [setAudioRoute](Android-api.md#RTCVideo-setaudioroute) 都可能触发音频路由切换，详见[移动端设置音频路由](https://www.volcengine.com/docs/6348/117836) 。

<span id="IRTCVideoEventHandler-onfirstlocalaudioframe"></span>
### onFirstLocalAudioFrame
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onFirstLocalAudioFrame(
    StreamIndex streamIndex)
```
发布音频流时，采集到第一帧音频帧，收到该回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamIndex | **StreamIndex** | 音频流属性, 详见 [StreamIndex](Android-keytype.md#streamindex-2) |


**注意**
如果发布音频流时，未开启本地音频采集，SDK 会推送静音帧，也会收到此回调。

<span id="IRTCVideoEventHandler-onfirstremoteaudioframe"></span>
### onFirstRemoteAudioFrame
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onFirstRemoteAudioFrame(
    RemoteStreamKey remoteStreamKey)
```
接收到来自远端某音频流的第一帧时，收到该回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| remoteStreamKey | **RemoteStreamKey** | 远端音频流信息, 详见 [RemoteStreamKey](Android-keytype.md#remotestreamkey) |


**注意**
用户刚收到房间内订阅的每一路音频流时，都会收到该回调。

<span id="IRTCVideoEventHandler-onlogreport"></span>
### onLogReport
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onLogReport(
    String logType,
    JSONObject logContent)
```
上报日志时回调该事件。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| logType | **String** | 日志类型。 |
| logContent | **JSONObject** | 日志内容。 |


<span id="IRTCVideoEventHandler-onseimessagereceived"></span>
### onSEIMessageReceived
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onSEIMessageReceived(
    RemoteStreamKey remoteStreamKey,
    ByteBuffer message)
```
收到通过调用 [sendSEIMessage](Android-api.md#RTCVideo-sendseimessage) 发送带有 SEI 消息的视频帧时，收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| remoteStreamKey | **RemoteStreamKey** | 包含 SEI 发送者的用户名，所在的房间名和媒体流，详见 [RemoteStreamKey](Android-keytype.md#remotestreamkey) |
| message | **ByteBuffer** | 收到的 SEI 消息内容 |


<span id="IRTCVideoEventHandler-onseistreamupdate"></span>
### onSEIStreamUpdate
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onSEIStreamUpdate(
    RemoteStreamKey remoteStreamKey,
    SEIStreamUpdateEvent event)
```
黑帧视频流发布状态回调。  <br>
在语音通话场景下，本地用户调用 [sendSEIMessage](Android-api.md#RTCVideo-sendseimessage) 通过黑帧视频流发送 SEI 数据时，流的发送状态会通过该回调通知远端用户。  <br>
你可以通过此回调判断携带 SEI 数据的视频帧为黑帧，从而不对该视频帧进行渲染。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| remoteStreamKey | **RemoteStreamKey** | 远端流信息，参看 [RemoteStreamKey](Android-keytype.md#remotestreamkey)。 |
| event | **SEIStreamUpdateEvent** | 黑帧视频流状态，参看 [SEIStreamUpdateEvent](Android-keytype.md#seistreamupdateevent) |


<span id="IRTCVideoEventHandler-onloginresult"></span>
### onLoginResult
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onLoginResult(
    String uid,
    int error_code,
    int elapsed)
```
登录结果回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | **String** | 登录用户 ID |
| error_code | **int** | 登录结果  <br/>详见 [LoginErrorCode](Android-errorcode.md#loginerrorcode)。 |
| elapsed | **int** | 从调用 [login](Android-api.md#RTCVideo-login) 接口开始到返回结果所用时长。  <br/>单位为 ms。 |


**注意**
调用 [login](Android-api.md#RTCVideo-login) 后，会收到此回调。

<span id="IRTCVideoEventHandler-onlogout"></span>
### onLogout
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onLogout()
```
登出结果回调


**注意**
调用 [logout](Android-api.md#RTCVideo-logout) 后，会收到此回调。

<span id="IRTCVideoEventHandler-onserverparamssetresult"></span>
### onServerParamsSetResult
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onServerParamsSetResult(
    int error)
```
设置应用服务器参数的返回结果

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| error | **int** | 设置结果  <br/>• 返回 200，设置成功  <br/>• 返回其他，设置失败，详见 [UserMessageSendResult](Android-errorcode.md#usermessagesendresult) |


**注意**
调用 [setServerParams](Android-api.md#RTCVideo-setserverparams) 后，会收到此回调。

<span id="IRTCVideoEventHandler-ongetpeeronlinestatus"></span>
### onGetPeerOnlineStatus
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onGetPeerOnlineStatus(
    String peerUserId,
    int status)
```
查询对端或本端用户登录状态的返回结果

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| peerUserId | **String** | 需要查询的用户 ID |
| status | **int** | 查询的用户登录状态  <br/>详见 [UserOnlineStatus](Android-keytype.md#useronlinestatus). |


**注意**
必须先调用 [getPeerOnlineStatus](Android-api.md#RTCVideo-getpeeronlinestatus)，才能收到此回调。

<span id="IRTCVideoEventHandler-onusermessagereceivedoutsideroom"></span>
### onUserMessageReceivedOutsideRoom
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onUserMessageReceivedOutsideRoom(
    String uid,
    String message)
```
收到房间外用户调用 [sendUserMessageOutsideRoom](Android-api.md#RTCVideo-sendusermessageoutsideroom) 发来的文本消息时，会收到此回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | **String** | 消息发送者 ID |
| message | **String** | 收到的文本消息内容 |


<span id="IRTCVideoEventHandler-onuserbinarymessagereceivedoutsideroom"></span>
### onUserBinaryMessageReceivedOutsideRoom
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onUserBinaryMessageReceivedOutsideRoom(
    String uid,
    ByteBuffer message)
```
收到房间外用户调用 [sendUserBinaryMessageOutsideRoom](Android-api.md#RTCVideo-senduserbinarymessageoutsideroom) 发来的二进制消息时，会收到此回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | **String** | 消息发送者 ID |
| message | **ByteBuffer** | 收到的二进制消息内容 |


<span id="IRTCVideoEventHandler-onusermessagesendresultoutsideroom"></span>
### onUserMessageSendResultOutsideRoom
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onUserMessageSendResultOutsideRoom(
    long msgid,
    int error)
```
给房间外指定的用户发送消息的回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| msgid | **long** | 本条消息的 ID  <br/>所有的 P2P 和 P2Server 消息共用一个 ID 序列。 |
| error | **int** | 消息发送结果  <br/>详见 [UserMessageSendResult](Android-errorcode.md#usermessagesendresult)。 |


**注意**
当调用 [sendUserMessageOutsideRoom](Android-api.md#RTCVideo-sendusermessageoutsideroom) 或 [sendUserBinaryMessageOutsideRoom](Android-api.md#RTCVideo-senduserbinarymessageoutsideroom) 发送消息后，会收到此回调。

<span id="IRTCVideoEventHandler-onservermessagesendresult"></span>
### onServerMessageSendResult
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onServerMessageSendResult(
    long msgid,
    int error,
    ByteBuffer message)
```
给应用服务器发送消息的回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| msgid | **long** | 本条消息的 ID  <br/>所有的 P2P 和 P2Server 消息共用一个 ID 序列。 |
| error | **int** | 消息发送结果，详见 [UserMessageSendResult](Android-errorcode.md#usermessagesendresult)。 |
| message | **ByteBuffer** | 应用服务器收到 HTTP 请求后，在 ACK 中返回的信息。消息不超过 64 KB。 |


**注意**
本回调为异步回调。当调用 [sendServerMessage](Android-api.md#RTCVideo-sendservermessage) 或 [sendServerBinaryMessage](Android-api.md#RTCVideo-sendserverbinarymessage) 接口发送消息后，会收到此回调。

<span id="IRTCVideoEventHandler-onnetworkdetectionresult"></span>
### onNetworkDetectionResult
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onNetworkDetectionResult(
    NetworkDetectionLinkType type,
    int quality,
    int rtt,
    double lost_rate,
    int bitrate,
    int jitter)
```
通话前网络探测结果。  <br>
成功调用 [startNetworkDetection](Android-api.md#RTCVideo-startnetworkdetection) 接口开始探测后，会在 3s 内首次收到该回调，之后每 2s 收到一次该回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| type | **NetworkDetectionLinkType** | 探测网络类型为上行/下行 |
| quality | **int** | 探测网络的质量，参看 [NetworkQuality](Android-keytype.md#networkquality)。 |
| rtt | **int** | 探测网络的 RTT，单位：ms |
| lost_rate | **double** | 探测网络的丢包率 |
| bitrate | **int** | 探测网络的带宽，单位：kbps |
| jitter | **int** | 探测网络的抖动,单位：ms |


<span id="IRTCVideoEventHandler-onnetworkdetectionstopped"></span>
### onNetworkDetectionStopped
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onNetworkDetectionStopped(
    NetworkDetectionStopReason reason)
```
通话前网络探测结束
以下情况将停止探测并收到本一次本回调：<br>
1. 当调用 [stopNetworkDetection](Android-api.md#RTCVideo-stopnetworkdetection) 接口停止探测后，会收到一次该回调；
2. 当收到远端/本端音频首帧后，停止探测；
3. 当探测超过3分钟后，停止探测；
4. 当探测链路断开一定时间之后，停止探测。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| reason | **NetworkDetectionStopReason** | 停止探测的原因类型,参考 [NetworkDetectionStopReason](Android-keytype.md#networkdetectionstopreason) |


<span id="IRTCVideoEventHandler-onsimulcastsubscribefallback"></span>
### onSimulcastSubscribeFallback
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onSimulcastSubscribeFallback(
    RemoteStreamSwitch event)
```
音视频流因网络环境变化等原因发生回退，或从回退中恢复时，触发该回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| event | **RemoteStreamSwitch** | 音视频流发生变化的信息。参看 [RemoteStreamSwitch](Android-keytype.md#remotestreamswitch)。 |


<span id="IRTCVideoEventHandler-onperformancealarms"></span>
### onPerformanceAlarms
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onPerformanceAlarms(
    PerformanceAlarmMode mode,
    String roomId,
    PerformanceAlarmReason reason,
    SourceWantedData data)
```
本地未开启发布性能回退，检测到设备性能不足时，收到此回调。  <br>
本地开启发布性能回退，因设备性能/网络原因，造成发布性能回退/恢复时，收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mode | **PerformanceAlarmMode** | 指示本地是否开启发布回退功能。参看 [PerformanceAlarmMode](Android-keytype.md#performancealarmmode)  <br/>• 当发布端未开启发布性能回退时，mode 值为 PERFORMANCE_ALARM_MODE_NORMAL。  <br/>• 当发布端开启发布性能回退时，mode 值为 PERFORMANCE_ALARM_MODE_SIMULCAST。 |
| roomId | **String** | • 未开启发布性能回退时，roomId 为空 <br/>• 开启发布性能回退时，roomId 是告警影响的房间 ID。 |
| reason | **PerformanceAlarmReason** | 告警原因，参看 [PerformanceAlarmReason](Android-keytype.md#performancealarmreason) |
| data | **SourceWantedData** | 性能回退相关数据，详见 [SourceWantedData](Android-keytype.md#sourcewanteddata)。 |


<span id="IRTCVideoEventHandler-onaudioframesendstatechanged"></span>
### onAudioFrameSendStateChanged
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onAudioFrameSendStateChanged(
    String roomId,
    RtcUser user,
    FirstFrameSendState state)
```
本地音频首帧发送状态发生改变时，收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| roomId | **String** | 音频发布用户所在的房间 ID |
| user | **RtcUser** | 本地用户信息，详见 [RtcUser](Android-keytype.md#rtcuser) |
| state | **FirstFrameSendState** | 首帧发送状态，详见 [FirstFrameSendState](Android-keytype.md#firstframesendstate) |


<span id="IRTCVideoEventHandler-onvideoframesendstatechanged"></span>
### onVideoFrameSendStateChanged
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onVideoFrameSendStateChanged(
    String roomId,
    RtcUser user,
    FirstFrameSendState state)
```
本地视频首帧发送状态发生改变时，收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| roomId | **String** | 视频发布用户所在的房间 ID |
| user | **RtcUser** | 本地用户信息，详见 [RtcUser](Android-keytype.md#rtcuser) |
| state | **FirstFrameSendState** | 首帧发送状态，详见 [FirstFrameSendState](Android-keytype.md#firstframesendstate) |


<span id="IRTCVideoEventHandler-onscreenvideoframesendstatechanged"></span>
### onScreenVideoFrameSendStateChanged
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onScreenVideoFrameSendStateChanged(
    String roomId,
    RtcUser user,
    FirstFrameSendState state)
```
屏幕共享流的视频首帧发送状态发生改变时，收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| roomId | **String** | 屏幕视频发布用户所在的房间 ID |
| user | **RtcUser** | 本地用户信息，详见 [RtcUser](Android-keytype.md#rtcuser) |
| state | **FirstFrameSendState** | 首帧发送状态，详见 [FirstFrameSendState](Android-keytype.md#firstframesendstate) |


<span id="IRTCVideoEventHandler-onaudioframeplaystatechanged"></span>
### onAudioFramePlayStateChanged
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onAudioFramePlayStateChanged(
    String roomId,
    RtcUser user,
    FirstFramePlayState state)
```
音频首帧播放状态发生改变时，收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| roomId | **String** | 音频发布用户所在的房间 ID |
| user | **RtcUser** | 远端用户信息，详见 [RtcUser](Android-keytype.md#rtcuser) |
| state | **FirstFramePlayState** | 首帧播放状态，详见 [FirstFramePlayState](Android-keytype.md#firstframeplaystate) |


<span id="IRTCVideoEventHandler-onvideoframeplaystatechanged"></span>
### onVideoFramePlayStateChanged
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onVideoFramePlayStateChanged(
    String roomId,
    RtcUser user,
    FirstFramePlayState state)
```
视频首帧播放状态发生改变时，收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| roomId | **String** | 视频发布用户所在的房间 ID |
| user | **RtcUser** | 远端用户信息，详见 [RtcUser](Android-keytype.md#rtcuser) |
| state | **FirstFramePlayState** | 首帧播放状态，详见 [FirstFramePlayState](Android-keytype.md#firstframeplaystate) |


<span id="IRTCVideoEventHandler-onscreenvideoframeplaystatechanged"></span>
### onScreenVideoFramePlayStateChanged
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onScreenVideoFramePlayStateChanged(
    String roomId,
    RtcUser user,
    FirstFramePlayState state)
```
屏幕共享流视频首帧播放状态发生改变时，收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| roomId | **String** | 屏幕视频发布用户所在的房间 ID |
| user | **RtcUser** | 远端用户信息，详见 [RtcUser](Android-keytype.md#rtcuser) |
| state | **FirstFramePlayState** | 首帧播放状态，详见 [FirstFramePlayState](Android-keytype.md#firstframeplaystate) |


<span id="IRTCVideoEventHandler-onmediadevicestatechanged"></span>
### onMediaDeviceStateChanged
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onMediaDeviceStateChanged(
    String device_id,
    int device_type,
    int device_state,
    int device_error)
```
> Deprecated  since 3.37 and will be deleted in 3.51, using [onAudioDeviceStateChanged](#IRTCVideoEventHandler-onaudiodevicestatechanged) and [onVideoDeviceStateChanged](#IRTCVideoEventHandler-onvideodevicestatechanged) instead.

媒体设备状态回调。提示音频采集、音频播放、摄像头视频采集、屏幕视频采集四种媒体设备的状态。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| device_id | **String** | 设备 ID |
| device_type | **int** | 设备类型，详见 [MediaDeviceType](Android-keytype.md#mediadevicetype)。 |
| device_state | **int** | 设备状态，详见 [MediaDeviceState](Android-keytype.md#mediadevicestate)。 |
| device_error | **int** | 设备错误类型，详见 [MediaDeviceError](Android-keytype.md#mediadeviceerror)。 |


<span id="IRTCVideoEventHandler-onaudiodevicestatechanged"></span>
### onAudioDeviceStateChanged
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onAudioDeviceStateChanged(
    String device_id,
    AudioDeviceType device_type,
    int device_state,
    int device_error)
```
音频设备状态回调。提示音频采集、音频播放等媒体设备的状态。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| device_id | **String** | 设备 ID |
| device_type | **AudioDeviceType** | 设备类型，详见 [AudioDeviceType](Android-keytype.md#audiodevicetype)。 |
| device_state | **int** | 设备状态，详见 [MediaDeviceState](Android-keytype.md#mediadevicestate)。 |
| device_error | **int** | 设备错误类型，详见 [MediaDeviceError](Android-keytype.md#mediadeviceerror)。 |


<span id="IRTCVideoEventHandler-onvideodevicestatechanged"></span>
### onVideoDeviceStateChanged
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onVideoDeviceStateChanged(
    String device_id,
    VideoDeviceType device_type,
    int device_state,
    int device_error)
```
视频设备状态回调。提示摄像头视频采集、屏幕视频采集等媒体设备的状态。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| device_id | **String** | 设备 ID |
| device_type | **VideoDeviceType** | 设备类型，详见 [VideoDeviceType](Android-keytype.md#videodevicetype)。 |
| device_state | **int** | 设备状态，详见 [MediaDeviceState](Android-keytype.md#mediadevicestate)。 |
| device_error | **int** | 设备错误类型，详见 [MediaDeviceError](Android-keytype.md#mediadeviceerror)。 |


<span id="IRTCVideoEventHandler-onmediadevicewarning"></span>
### onMediaDeviceWarning
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onMediaDeviceWarning(
    String device_id,
    int device_type,
    int device_warning)
```
> Deprecated  since 3.37 and will be deleted in 3.51, using [onAudioDeviceWarning](#IRTCVideoEventHandler-onaudiodevicewarning) and [onVideoDeviceWarning](#IRTCVideoEventHandler-onvideodevicewarning) instead.

媒体设备警告回调。媒体设备包括：音频采集设备、音频渲染设备、和视频采集设备。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| device_id | **String** | 设备 ID |
| device_type | **int** | 参看 [MediaDeviceType](Android-keytype.md#mediadevicetype) |
| device_warning | **int** | 参看 [MediaDeviceWarning](Android-keytype.md#mediadevicewarning) |


<span id="IRTCVideoEventHandler-onaudiodevicewarning"></span>
### onAudioDeviceWarning
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onAudioDeviceWarning(
    String device_id,
    AudioDeviceType device_type,
    int device_warning)
```
音频设备警告回调。音频设备包括音频采集设备、音频渲染设备等。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| device_id | **String** | 设备 ID |
| device_type | **AudioDeviceType** | 参看 [AudioDeviceType](Android-keytype.md#audiodevicetype) |
| device_warning | **int** | 参看 [MediaDeviceWarning](Android-keytype.md#mediadevicewarning) |


<span id="IRTCVideoEventHandler-onvideodevicewarning"></span>
### onVideoDeviceWarning
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onVideoDeviceWarning(
    String device_id,
    VideoDeviceType device_type,
    int device_warning)
```
视频设备警告回调，包括视频采集等设备。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| device_id | **String** | 设备 ID |
| device_type | **VideoDeviceType** | 参看 [VideoDeviceType](Android-keytype.md#videodevicetype) |
| device_warning | **int** | 参看 [MediaDeviceWarning](Android-keytype.md#mediadevicewarning) |


<span id="IRTCVideoEventHandler-onhttpproxystate"></span>
### onHttpProxyState
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onHttpProxyState(
    int state)
```
HTTP 代理连接状态改变时，收到该回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| state | **int** | 当前 HTTP 代理连接状态 |


<span id="IRTCVideoEventHandler-onhttpsproxystate"></span>
### onHttpsProxyState
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onHttpsProxyState(
    int state)
```
HTTPS 代理连接状态改变时，收到该回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| state | **int** | 当前 HTTPS 代理连接状态 |


<span id="IRTCVideoEventHandler-onsocks5proxystate"></span>
### onSocks5ProxyState
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onSocks5ProxyState(
    int state,
    String cmd,
    String proxy_address,
    String local_address,
    String remote_address)
```
SOCKS5 代理状态改变时，收到该回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| state | **int** | SOCKS5 代理连接状态 |
| cmd | **String** | 代理连接的每一步操作命令 |
| proxy_address | **String** | 代理地址信息 |
| local_address | **String** | 当前连接使用的本地地址 |
| remote_address | **String** | 远端的连接地址 |


<span id="IRTCVideoEventHandler-onrecordingstateupdate"></span>
### onRecordingStateUpdate
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onRecordingStateUpdate(
    StreamIndex type,
    RecordingState state,
    RecordingErrorCode errorCode,
    RecordingInfo info)
```
获取本地录制状态回调。  <br>
该回调由 [startFileRecording](Android-api.md#RTCVideo-startfilerecording) 或 [stopFileRecording](Android-api.md#RTCVideo-stopfilerecording) 触发。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| type | **StreamIndex** | 录制流的流属性，参看 [StreamIndex](Android-keytype.md#streamindex-2) |
| state | **RecordingState** | 录制状态，参看 [RecordingState](Android-keytype.md#recordingstate) |
| errorCode | **RecordingErrorCode** | 录制错误码，参看 [RecordingErrorCode](Android-keytype.md#recordingerrorcode) |
| info | **RecordingInfo** | 录制文件的详细信息，参看 [RecordingInfo](Android-keytype.md#recordinginfo) |


<span id="IRTCVideoEventHandler-onrecordingprogressupdate"></span>
### onRecordingProgressUpdate
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onRecordingProgressUpdate(
    StreamIndex type,
    RecordingProgress progress,
    RecordingInfo info)
```
本地录制进度回调。  <br>
该回调由 [startFileRecording](Android-api.md#RTCVideo-startfilerecording) 触发，录制状态正常时，系统每秒钟都会通过该回调提示录制进度。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| type | **StreamIndex** | 录制流的流属性，参看 [StreamIndex](Android-keytype.md#streamindex-2) |
| progress | **RecordingProgress** | 录制进度，参看 [RecordingProgress](Android-keytype.md#recordingprogress) |
| info | **RecordingInfo** | 录制文件的详细信息，参看 [RecordingInfo](Android-keytype.md#recordinginfo) |


<span id="IRTCVideoEventHandler-onaudiorecordingstateupdate"></span>
### onAudioRecordingStateUpdate
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onAudioRecordingStateUpdate(
    AudioRecordingState state,
    AudioRecordingErrorCode errorCode)
```
调用 [startAudioRecording](Android-api.md#RTCVideo-startaudiorecording) 或 [stopAudioRecording](Android-api.md#RTCVideo-stopaudiorecording) 改变音频文件录制状态时，收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| state | **AudioRecordingState** | 录制状态，参看 [AudioRecordingState](Android-keytype.md#audiorecordingstate) |
| errorCode | **AudioRecordingErrorCode** | 录制错误码，参看 [AudioRecordingErrorCode](Android-errorcode.md#audiorecordingerrorcode) |


<span id="IRTCVideoEventHandler-onaudiomixingstatechanged"></span>
### onAudioMixingStateChanged
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onAudioMixingStateChanged(
    int mixId,
    AudioMixingState state,
    AudioMixingError error)
```
音频混音文件播放状态改变时回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mixId | **int** | 混音 ID  <br/>使用 [IAudioMixingManager](Android-api.md#iaudiomixingmanager) 相关接口时传入的唯一 ID。 |
| state | **AudioMixingState** | 混音状态  <br/>其混音状态可参考：[AudioMixingState](Android-keytype.md#audiomixingstate)。 |
| error | **AudioMixingError** | 错误码  <br/>详见 [AudioMixingError](Android-keytype.md#audiomixingerror)。 |


**注意**
此回调会被触发的时机汇总如下：  

+ 当调用 [startAudioMixing](Android-api.md#IAudioMixingManager-startaudiomixing) 方法成功后，会触发 state 值为 AUDIO_MIXING_STATE_PLAYING 回调；否则触发 state 值为 AUDIO_MIXING_STATE_FAILED 的回调。  
+ 当使用相同的 ID 重复调用 [startAudioMixing](Android-api.md#IAudioMixingManager-startaudiomixing) 后，后一次会覆盖前一次，且本回调会以 AUDIO_MIXING_STATE_STOPPED 通知前一次混音已停止。  
+ 当调用 [pauseAudioMixing](Android-api.md#IAudioMixingManager-pauseaudiomixing) 方法暂停播放成功后， 会触发 state 值为 AUDIO_MIXING_STATE_PAUSED 回调；否则触发 state 值为 AUDIO_MIXING_STATE_FAILED 的回调。  
+ 当调用 [resumeAudioMixing](Android-api.md#IAudioMixingManager-resumeaudiomixing) 方法恢复播放成功后，会触发 state 值为 AUDIO_MIXING_STATE_PLAYING 回调；否则触发 state 值为 AUDIO_MIXING_STATE_FAILED 的回调。  
+ 当调用 [stopAudioMixing](Android-api.md#IAudioMixingManager-stopaudiomixing) 方法暂停止播放成功后， 会触发 state 值为 AUDIO_MIXING_STATE_STOPPED 回调；否则触发 state 值为 AUDIO_MIXING_STATE_FAILED 的回调。  
+ 播放结束会触发 state 值为 AUDIO_MIXING_STATE_FINISHED 回调。


<span id="IRTCVideoEventHandler-onaudiomixingplayingprogress"></span>
### onAudioMixingPlayingProgress
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onAudioMixingPlayingProgress(
    int mixId,
    long progress)
```
混音音频文件播放进度回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mixId | **int** | 混音 ID |
| progress | **long** | 当前混音音频文件播放进度，单位毫秒 |


**注意**
调用 [setAudioMixingProgressInterval](Android-api#IAudioMixingManager-setaudiomixingprogressinterval) 将时间间隔设为大于 0 的值后，或调用 [startAudioMixing](Android-api#IAudioMixingManager-startaudiomixing) 将 [AudioMixingConfig](Android-keytype.md#audiomixingconfig) 中的时间间隔设为大于 0 的值后，SDK 会按照设置的时间间隔回调该事件。 

<span id="IRTCVideoEventHandler-onlocalaudiopropertiesreport"></span>
### onLocalAudioPropertiesReport
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onLocalAudioPropertiesReport(
    LocalAudioPropertiesInfo[] audioPropertiesInfos)
```
调用 [enableAudioPropertiesReport](Android-api.md#RTCVideo-enableaudiopropertiesreport) 后，你会周期性地收到此回调，了解本地音频的相关信息。  <br>
本地音频包括使用 RTC SDK 内部机制采集的麦克风音频，屏幕音频和本地混音音频信息。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioPropertiesInfos | **LocalAudioPropertiesInfo[]** | 本地音频信息，详见 [LocalAudioPropertiesInfo](Android-keytype.md#localaudiopropertiesinfo) 。 |


<span id="IRTCVideoEventHandler-onaudioplaybackdevicetestvolume"></span>
### onAudioPlaybackDeviceTestVolume
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onAudioPlaybackDeviceTestVolume(
    int volume)
```
回调音频设备测试时的播放音量

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| volume | **int** | 音频设备测试播放音量。单位：毫秒。推荐设置为 200 ms。范围：[0,255] |


**注意**
调用 [startAudioPlaybackDeviceTest](Android-api.md#IRTCAudioDeviceManager-startaudioplaybackdevicetest) 或 [startAudioDeviceRecordTest](Android-api.md#IRTCAudioDeviceManager-startaudiodevicerecordtest)，开始播放音频文件或录音时，将开启该回调。本回调为周期性回调，回调周期由上述接口的 `interval` 参数指定。

<span id="IRTCVideoEventHandler-onremoteaudiopropertiesreport"></span>
### onRemoteAudioPropertiesReport
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onRemoteAudioPropertiesReport(
    RemoteAudioPropertiesInfo[] audioPropertiesInfos,
    int totalRemoteVolume)
```
远端用户进房后，本地调用 [enableAudioPropertiesReport](Android-api.md#RTCVideo-enableaudiopropertiesreport) ，根据设置的 interval 值，本地会周期性地收到此回调，了解订阅的远端用户的音频信息。<br>
远端用户的音频包括使用 RTC SDK 内部机制/自定义机制采集的麦克风音频和屏幕音频。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioPropertiesInfos | **RemoteAudioPropertiesInfo[]** | 远端音频信息，其中包含音频流属性、房间 ID、用户 ID ，详见 [RemoteAudioPropertiesInfo](Android-keytype.md#remoteaudiopropertiesinfo)。 |
| totalRemoteVolume | **int** | 订阅的所有远端流的总音量。 |


<span id="IRTCVideoEventHandler-onactivespeaker"></span>
### onActiveSpeaker
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onActiveSpeaker(
    String roomId,
    String uid)
```
调用 [enableAudioPropertiesReport](Android-api.md#RTCVideo-enableaudiopropertiesreport) 后，根据设置的 `AudioPropertiesConfig.interval`，你会周期性地收到此回调，获取房间内的最活跃用户信息。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| roomId | **String** | 房间 ID |
| uid | **String** | 最活跃用户（ActiveSpeaker）的用户 ID |


<span id="IRTCVideoEventHandler-onstreamsyncinforeceived"></span>
### onStreamSyncInfoReceived
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onStreamSyncInfoReceived(
    RemoteStreamKey streamKey,
    StreamSycnInfoConfig.SyncInfoStreamType streamType,
    ByteBuffer data)
```
音频流同步信息回调。可以通过此回调，在远端用户调用 [sendStreamSyncInfo](Android-api.md#RTCVideo-sendstreamsyncinfo) 发送音频流同步消息后，收到远端发送的音频流同步信息。  <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamKey | **RemoteStreamKey** | 远端流信息，详见 [RemoteStreamKey](Android-keytype.md#remotestreamkey) 。 |
| streamType | **StreamSycnInfoConfig.SyncInfoStreamType** | 媒体流类型，详见 [SyncInfoStreamType](Android-keytype.md#syncinfostreamtype) 。 |
| data | **ByteBuffer** | 消息内容。 |


<span id="IRTCVideoEventHandler-onpushpublicstreamresult"></span>
### onPushPublicStreamResult
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onPushPublicStreamResult(
    String roomId,
    String publicStreamId,
    PublicStreamErrorCode error)
```
公共流发布结果回调。<br>
调用 [startPushPublicStream](Android-api.md#RTCVideo-startpushpublicstream) 接口发布公共流后，启动结果通过此回调方法通知用户。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| roomId | **String** | 发布公共流的房间 ID |
| publicStreamId | **String** | 公共流 ID |
| error | **PublicStreamErrorCode** | 公共流发布结果状态码。详见 [PublicStreamErrorCode](Android-errorcode.md#publicstreamerrorcode)。 |


<span id="IRTCVideoEventHandler-onplaypublicstreamresult"></span>
### onPlayPublicStreamResult
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onPlayPublicStreamResult(
    String publicStreamId,
    PublicStreamErrorCode error)
```
订阅公共流的结果回调  <br>
调用 [startPlayPublicStream](Android-api.md#RTCVideo-startplaypublicstream) 接口启动拉公共流功能后，通过此回调收到启动结果和拉流过程中的错误。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| publicStreamId | **String** | 公共流ID。 |
| error | **PublicStreamErrorCode** | 公共流订阅结果状态码。详见 [PublicStreamErrorCode](Android-errorcode.md#publicstreamerrorcode)。 |


<span id="IRTCVideoEventHandler-onpublicstreamseimessagereceived"></span>
### onPublicStreamSEIMessageReceived
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onPublicStreamSEIMessageReceived(
    String publicStreamId,
    ByteBuffer message,
    SEIMessageSourceType sourceType)
```
回调公共流中包含的 SEI 信息。
调用 [startPlayPublicStream](Android-api.md#RTCVideo-startplaypublicstream) 接口启动拉公共流功能后，通过此回调收到公共流中的 SEI 消息。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| publicStreamId | **String** | 公共流 ID。 |
| message | **ByteBuffer** | 收到的 SEI 消息内容。 |
| sourceType | **SEIMessageSourceType** | SEI 消息类型，参看 [SEIMessageSourceType](Android-keytype.md#seimessagesourcetype)。 |


**注意**
当公共流中的多路视频流均包含有 SEI 信息：SEI 不互相冲突时，将通过多次回调分别发送；SEI 在同一帧有冲突时，则只有一条流中的 SEI 信息被透传并融合到公共流中。

<span id="IRTCVideoEventHandler-onfirstpublicstreamvideoframedecoded"></span>
### onFirstPublicStreamVideoFrameDecoded
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onFirstPublicStreamVideoFrameDecoded(
    String publicStreamId,
    VideoFrameInfo videoFrameInfo)
```
公共流的首帧视频解码成功<br>
关于订阅公共流，详见 [startPlayPublicStream](Android-api.md#RTCVideo-startplaypublicstream)。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| publicStreamId | **String** | 公共流 ID |
| videoFrameInfo | **VideoFrameInfo** | 视频帧信息，参看 [VideoFrameInfo](Android-keytype.md#videoframeinfo) |


<span id="IRTCVideoEventHandler-onfirstpublicstreamaudioframe"></span>
### onFirstPublicStreamAudioFrame
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onFirstPublicStreamAudioFrame(
    String publicStreamId)
```
公共流的音频首帧解码成功<br>
关于订阅公共流，详见 [startPlayPublicStream](Android-api.md#RTCVideo-startplaypublicstream)。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| publicStreamId | **String** | 公共流 ID |


<span id="IRTCVideoEventHandler-onechotestresult"></span>
### onEchoTestResult
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onEchoTestResult(
    EchoTestResult result)
```
关于音视频回路测试结果的回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| result | **EchoTestResult** | 测试结果，参看 [EchoTestResult](Android-keytype.md#echotestresult) |


**注意**
该回调触发的时机包括： + 检测过程中采集设备发生错误时；  

+ 检测成功后；  
+ 非设备原因导致检测过程中未接收到音/视频回放，停止检测后。


<span id="IRTCVideoEventHandler-oncloudproxyconnected"></span>
### onCloudProxyConnected
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onCloudProxyConnected(
    int interval)
```
调用 [startCloudProxy](Android-api.md#RTCVideo-startcloudproxy) 开启云代理，SDK 首次成功连接云代理服务器时，回调此事件。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| interval | **int** | 从开启云代理到连接成功经过的时间，单位为 ms |


<span id="IRTCVideoEventHandler-onnetworktimesynchronized"></span>
### onNetworkTimeSynchronized
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onNetworkTimeSynchronized()
```
首次调用 [getNetworkTimeInfo](Android-api.md#RTCVideo-getnetworktimeinfo) 后，SDK内部启动网络时间同步，同步完成时会触发此回调。


<span id="IRTCVideoEventHandler-onlicensewillexpire"></span>
### onLicenseWillExpire
```java
public void com.ss.bytertc.engine.handler.IRTCVideoEventHandler.onLicenseWillExpire(
    int days)
```
license 过期时间提醒

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| days | **int** | 即将过期剩余天数 |



# ILiveTranscodingObserver
```java
public interface com.ss.bytertc.engine.live.ILiveTranscodingObserver
```

转推直播观察者。  <br>


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **boolean** | [isSupportClientPushStream](#ILiveTranscodingObserver-issupportclientpushstream) |
| **void** | [onStreamMixingEvent](#ILiveTranscodingObserver-onstreammixingevent) |
| **void** | [onMixingAudioFrame](#ILiveTranscodingObserver-onmixingaudioframe) |
| **void** | [onMixingVideoFrame](#ILiveTranscodingObserver-onmixingvideoframe) |
| **void** | [onMixingDataFrame](#ILiveTranscodingObserver-onmixingdataframe) |


## 函数说明
<span id="ILiveTranscodingObserver-issupportclientpushstream"></span>
### isSupportClientPushStream
```java
boolean com.ss.bytertc.engine.live.ILiveTranscodingObserver.isSupportClientPushStream()
```
是否具有推流能力。  <br>

+ false：不具备推流能力（默认值）  <br>
+ true：具备推流能力


**注意**
如果需要开启端云一体转推直播功能，你必须确保你的 App 包含 librtmp，具有推流能力。此时，设置该回调为 true。

<span id="ILiveTranscodingObserver-onstreammixingevent"></span>
### onStreamMixingEvent
```java
void com.ss.bytertc.engine.live.ILiveTranscodingObserver.onStreamMixingEvent(
    ByteRTCStreamMixingEvent eventType,
    String taskId,
    ByteRTCTranscoderErrorCode error,
    ByteRTCStreamMixingType mixType)
```
转推直播状态回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| eventType | **ByteRTCStreamMixingEvent** | 转推直播任务状态, 参看 [ByteRTCStreamMixingEvent](Android-keytype.md#bytertcstreammixingevent) |
| taskId | **String** | 转推直播任务 ID |
| error | **ByteRTCTranscoderErrorCode** | 转推直播错误码，参看 [ByteRTCTranscoderErrorCode](Android-errorcode.md#bytertctranscodererrorcode) |
| mixType | **ByteRTCStreamMixingType** | 转推直播类型，参看 [ByteRTCStreamMixingType](Android-keytype.md#bytertcstreammixingtype) |


<span id="ILiveTranscodingObserver-onmixingaudioframe"></span>
### onMixingAudioFrame
```java
void com.ss.bytertc.engine.live.ILiveTranscodingObserver.onMixingAudioFrame(
    String taskId,
    byte[] audioFrame,
    int frameNum,
    long timeStampMs)
```
端云一体合流音频 PCM 回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| taskId | **String** | 转推直播任务 ID |
| audioFrame | **byte[]** | PCM 编码的合流音频数据帧 |
| frameNum | **int** | PCM 编码的音频数据帧数 |
| timeStampMs | **long** | 时间戳，单位毫秒 |


**注意**
收到该回调的周期为每 10 毫秒一次，并且每次的音频数据量为 10 毫秒数据量。

<span id="ILiveTranscodingObserver-onmixingvideoframe"></span>
### onMixingVideoFrame
```java
void com.ss.bytertc.engine.live.ILiveTranscodingObserver.onMixingVideoFrame(
    String taskId,
    VideoFrame videoFrame)
```
端云一体合流视频 YUV 回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| taskId | **String** | 转推直播任务 ID |
| videoFrame | **VideoFrame** | YUV 合流视频数据帧，参看 [VideoFrame](Android-keytype.md#videoframe) |


**注意**

+ 收到该回调的周期与视频的帧间隔一致。
+ 为避免内存泄露，你应在回调中手动释放视频帧：
```
public void onMixingVideoFrame(String taskId, VideoFrame videoFrame){
videoFrame.release()
}
```


<span id="ILiveTranscodingObserver-onmixingdataframe"></span>
### onMixingDataFrame
```java
void com.ss.bytertc.engine.live.ILiveTranscodingObserver.onMixingDataFrame(
    String taskId,
    byte[] dataFrame,
    long time)
```
端云一体合流视频 SEI 数据回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| taskId | **String** | 转推直播任务 ID |
| dataFrame | **byte[]** | SEI 数据 |
| time | **long** | 时间信息 |


# IPushSingleStreamToCDNObserver
```java
public interface com.ss.bytertc.engine.live.IPushSingleStreamToCDNObserver
```

单流转推直播观察者。  <br>


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **void** | [onStreamPushEvent](#IPushSingleStreamToCDNObserver-onstreampushevent) |


## 函数说明
<span id="IPushSingleStreamToCDNObserver-onstreampushevent"></span>
### onStreamPushEvent
```java
void com.ss.bytertc.engine.live.IPushSingleStreamToCDNObserver.onStreamPushEvent(
    ByteRTCStreamSinglePushEvent eventType,
    String taskId,
    int error)
```
单流转推直播状态回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| eventType | **ByteRTCStreamSinglePushEvent** | 任务状态, 参看 [ByteRTCStreamSinglePushEvent](Android-errorcode.md#bytertcstreamsinglepushevent) |
| taskId | **String** | 任务 ID |
| error | **int** | 错误码，参看 [ByteRTCTranscoderErrorCode](Android-errorcode.md#bytertctranscodererrorcode) |


# IFaceDetectionObserver
```java
public interface com.ss.bytertc.engine.video.IFaceDetectionObserver
```

人脸检测结果回调观察者


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **void** | [onFaceDetectResult](#IFaceDetectionObserver-onfacedetectresult) |


## 函数说明
<span id="IFaceDetectionObserver-onfacedetectresult"></span>
### onFaceDetectResult
```java
public void com.ss.bytertc.engine.video.IFaceDetectionObserver.onFaceDetectResult(
    FaceDetectionResult result)
```
特效 SDK 进行人脸检测结果的回调。 <br>
调用 [enableFaceDetection](Android-api.md#IVideoEffect-enablefacedetection) 注册了 [IFaceDetectionObserver](#ifacedetectionobserver)，并使用 RTC SDK 中包含的特效 SDK 进行视频特效处理时，你会收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| result | **FaceDetectionResult** | 人脸检测结果, 参看 [FaceDetectionResult](Android-keytype.md#facedetectionresult)。 |


# ISingScoringEventHandler
```java
public interface com.ss.bytertc.engine.ISingScoringEventHandler
```

K 歌评分事件回调类。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **void** | [onCurrentScoringInfo](#ISingScoringEventHandler-oncurrentscoringinfo) |


## 函数说明
<span id="ISingScoringEventHandler-oncurrentscoringinfo"></span>
### onCurrentScoringInfo
```java
void com.ss.bytertc.engine.ISingScoringEventHandler.onCurrentScoringInfo(
    SingScoringRealtimeInfo info)
```
实时评分信息回调。调用 [startSingScoring](Android-api.md#ISingScoringManager-startsingscoring) 后，会收到该回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| Info | **SingScoringRealtime** | 实时评分信息。详见 [SingScoringRealtimeInfo](Android-keytype.md#singscoringrealtimeinfo)。 |


# ILocalEncodedVideoFrameObserver
```java
public interface com.ss.bytertc.engine.mediaio.ILocalEncodedVideoFrameObserver
```

本地视频帧监测器


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **void** | [onLocalEncodedVideoFrame](#ILocalEncodedVideoFrameObserver-onlocalencodedvideoframe) |


## 函数说明
<span id="ILocalEncodedVideoFrameObserver-onlocalencodedvideoframe"></span>
### onLocalEncodedVideoFrame
```java
void com.ss.bytertc.engine.mediaio.ILocalEncodedVideoFrameObserver.onLocalEncodedVideoFrame(
    StreamIndex streamIndex,
    RTCEncodedVideoFrame encodedVideoFrame)
```
调用 [registerLocalEncodedVideoFrameObserver](Android-api.md#RTCVideo-registerlocalencodedvideoframeobserver) 后，SDK 每次使用内部采集，采集到一帧视频帧，或收到一帧外部视频帧时，都会回调该事件。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamIndex | **StreamIndex** | 本地视频帧类型，参看 [StreamIndex](Android-keytype.md#StreamIndex-2) |
| encodedVideoFrame | **RTCEncodedVideoFrame** | 本地视频帧信息，参看 [RTCEncodedVideoFrame](Android-keytype.md#rtcencodedvideoframe) |


**注意**
encodedVideoFrame 只在回调函数作用域内有效，不要存储该参数并在其它函数内访问该参数的内存数据

# IRemoteEncodedVideoFrameObserver
```java
public abstract class com.ss.bytertc.engine.mediaio.IRemoteEncodedVideoFrameObserver
```

远端编码后视频数据监测器


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **abstract void** | [onRemoteEncodedVideoFrame](#IRemoteEncodedVideoFrameObserver-onremoteencodedvideoframe) |


## 函数说明
<span id="IRemoteEncodedVideoFrameObserver-onremoteencodedvideoframe"></span>
### onRemoteEncodedVideoFrame
```java
public abstract void com.ss.bytertc.engine.mediaio.IRemoteEncodedVideoFrameObserver.onRemoteEncodedVideoFrame(
    RemoteStreamKey stream_info,
    RTCEncodedVideoFrame video_stream)
```
调用 [registerRemoteEncodedVideoFrameObserver](Android-api.md#RTCVideo-registerremoteencodedvideoframeobserver) 后，SDK 监测到远端编码后视频数据时，触发该回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stream_info | **RemoteStreamKey** | 收到的远端流信息，参看 [RemoteStreamKey](Android-keytype.md#remotestreamkey) |
| video_stream | **RTCEncodedVideoFrame** | 收到的远端视频帧信息，参看 [RTCEncodedVideoFrame](Android-keytype.md#rtcencodedvideoframe) |


**注意**
encodedVideoFrame 只在回调函数作用域内有效，不要存储该参数并在其它函数内访问该参数的内存数据

# ISnapshotResultCallback
```java
public interface com.ss.bytertc.engine.video.ISnapshotResultCallback
```

截图的回调。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **void** | [onTakeLocalSnapshotResult](#ISnapshotResultCallback-ontakelocalsnapshotresult) |
| **void** | [onTakeRemoteSnapshotResult](#ISnapshotResultCallback-ontakeremotesnapshotresult) |


## 函数说明
<span id="ISnapshotResultCallback-ontakelocalsnapshotresult"></span>
### onTakeLocalSnapshotResult
```java
void com.ss.bytertc.engine.video.ISnapshotResultCallback.onTakeLocalSnapshotResult(
    long taskId,
    StreamIndex streamIndex,
    Bitmap image,
    int errorCode)
```
调用 [takeLocalSnapshot](Android-api.md#RTCVideo-takelocalsnapshot) 截取视频画面时，收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| taskId | **long** | 本地截图任务的编号。和 [takeLocalSnapshot](Android-api.md#RTCVideo-takelocalsnapshot) 的返回值一致。 |
| streamIndex | **StreamIndex** | 截图的视频流的属性，参看 [StreamIndex](Android-keytype.md#streamindex)。 |
| image | **Bitmap** | 截图。你可以保存为文件，或对其进行二次处理。截图失败时，为空。 |
| errorCode | **int** | 截图错误码：<br/>• 0: 成功 <br/>• -1: 截图错误。生成图片数据失败或 RGBA 编码失败 <br/>• -2: 截图错误。流无效。 |


<span id="ISnapshotResultCallback-ontakeremotesnapshotresult"></span>
### onTakeRemoteSnapshotResult
```java
void com.ss.bytertc.engine.video.ISnapshotResultCallback.onTakeRemoteSnapshotResult(
    long taskId,
    RemoteStreamKey streamKey,
    Bitmap image,
    int errorCode)
```
调用 [takeRemoteSnapshot](Android-api.md#RTCVideo-takeremotesnapshot) 截取视频画面时，收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| taskId | **long** | 远端截图任务的编号。和 [takeRemoteSnapshot](Android-api.md#RTCVideo-takeremotesnapshot) 的返回值一致。 |
| streamKey | **RemoteStreamKey** | 截图的视频流，参看 [RemoteStreamKey](Android-keytype.md#remotestreamkey)。 |
| image | **Bitmap** | 截图。你可以保存为文件，或对其进行二次处理。截图失败时，为空。 |
| errorCode | **int** | 截图错误码：<br/>• 0: 成功 <br/>• -1: 截图错误。生成图片数据失败或 RGBA 编码失败 <br/>• -2: 截图错误。流无效。 |


# IAudioFileFrameObserver
```java
public interface com.ss.bytertc.engine.IAudioFileFrameObserver
```

本地音频文件混音的音频帧观察者。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **void** | [onAudioFileFrame](#IAudioFileFrameObserver-onaudiofileframe) |


## 函数说明
<span id="IAudioFileFrameObserver-onaudiofileframe"></span>
### onAudioFileFrame
```java
void com.ss.bytertc.engine.IAudioFileFrameObserver.onAudioFileFrame(
    int mix_id,
    IAudioFrame audio_frame)
```
当本地音频文件混音时，回调播放的音频帧。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mix_id | **int** | 混音 ID。 |
| audio_frame | **IAudioFrame** | 参看 [IAudioFrame](Android-keytype.md#iaudioframe)。 |


# IAudioFrameObserver
```java
public interface com.ss.bytertc.engine.IAudioFrameObserver
```

音频数据回调观察者
注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。
本接口类中的回调周期均为 20 ms。

## 成员函数

| 返回 | 名称 |
| --- | --- |
| **void** | [onRecordAudioFrame](#IAudioFrameObserver-onrecordaudioframe) |
| **void** | [onPlaybackAudioFrame](#IAudioFrameObserver-onplaybackaudioframe) |
| **void** | [onRemoteUserAudioFrame](#IAudioFrameObserver-onremoteuseraudioframe) |
| **void** | [onMixedAudioFrame](#IAudioFrameObserver-onmixedaudioframe) |


## 函数说明
<span id="IAudioFrameObserver-onrecordaudioframe"></span>
### onRecordAudioFrame
```java
void com.ss.bytertc.engine.IAudioFrameObserver.onRecordAudioFrame(
    IAudioFrame audioFrame)
```
返回麦克风录制的音频数据

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioFrame | **IAudioFrame** | 音频数据, 参看 [IAudioFrame](Android-keytype.md#iaudioframe)。 |


<span id="IAudioFrameObserver-onplaybackaudioframe"></span>
### onPlaybackAudioFrame
```java
void com.ss.bytertc.engine.IAudioFrameObserver.onPlaybackAudioFrame(
    IAudioFrame audioFrame)
```
返回订阅的所有远端用户混音后的音频数据。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioFrame | **IAudioFrame** | 音频数据, 参看 [IAudioFrame](Android-keytype.md#iaudioframe)。 |


<span id="IAudioFrameObserver-onremoteuseraudioframe"></span>
### onRemoteUserAudioFrame
```java
void com.ss.bytertc.engine.IAudioFrameObserver.onRemoteUserAudioFrame(
    RemoteStreamKey stream_info,
    IAudioFrame audioFrame)
```
返回远端单个用户的音频数据

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stream_info | **RemoteStreamKey** | 远端流信息，参看 [RemoteStreamKey](Android-keytype.md#remotestreamkey)。 |
| audioFrame | **IAudioFrame** | 音频数据，参看 [IAudioFrame](Android-keytype.md#iaudioframe)。 |


**注意**
此回调在播放线程调用。不要在此回调中做任何耗时的事情，否则可能会影响整个音频播放链路。

<span id="IAudioFrameObserver-onmixedaudioframe"></span>
### onMixedAudioFrame
```java
void com.ss.bytertc.engine.IAudioFrameObserver.onMixedAudioFrame(
    IAudioFrame audioFrame)
```
返回本地麦克风录制和订阅的所有远端用户混音后的音频数据

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioFrame | **IAudioFrame** | 音频数据, 参看 [IAudioFrame](Android-keytype.md#iaudioframe)。 |


# IAudioFrameProcessor
```java
public interface com.ss.bytertc.engine.IAudioFrameProcessor
```

自定义音频处理器。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **int** | [onProcessRecordAudioFrame](#IAudioFrameProcessor-onprocessrecordaudioframe) |
| **int** | [onProcessPlayBackAudioFrame](#IAudioFrameProcessor-onprocessplaybackaudioframe) |
| **int** | [onProcessRemoteUserAudioFrame](#IAudioFrameProcessor-onprocessremoteuseraudioframe) |
| **int** | [onProcessEarMonitorAudioFrame](#IAudioFrameProcessor-onprocessearmonitoraudioframe) |
| **int** | [onProcessScreenAudioFrame](#IAudioFrameProcessor-onprocessscreenaudioframe) |


## 函数说明
<span id="IAudioFrameProcessor-onprocessrecordaudioframe"></span>
### onProcessRecordAudioFrame
```java
int com.ss.bytertc.engine.IAudioFrameProcessor.onProcessRecordAudioFrame(
    IAudioFrame audioFrame)
```
回调本地采集的音频帧地址，供自定义音频处理。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioFrame | **IAudioFrame** | 音频帧地址，参看 [IAudioFrame](Android-keytype.md#iaudioframe)。 |


**注意**

+ 完成自定义音频处理后，SDK 会对处理后的音频帧进行编码，并传输到远端。  
+ 调用 `enableAudioProcessor`，并在参数中选择本地采集的音频时，收到此回调。


<span id="IAudioFrameProcessor-onprocessplaybackaudioframe"></span>
### onProcessPlayBackAudioFrame
```java
int com.ss.bytertc.engine.IAudioFrameProcessor.onProcessPlayBackAudioFrame(
    IAudioFrame audioFrame)
```
回调远端音频混音的音频帧地址，供自定义音频处理。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioFrame | **IAudioFrame** | 音频帧地址，参看 [IAudioFrame](Android-keytype.md#iaudioframe) |


**注意**
调用 `enableAudioProcessor`，并在参数中选择远端音频流的的混音音频时，每 10ms 收到此回调。

<span id="IAudioFrameProcessor-onprocessremoteuseraudioframe"></span>
### onProcessRemoteUserAudioFrame
```java
int com.ss.bytertc.engine.IAudioFrameProcessor.onProcessRemoteUserAudioFrame(
    RemoteStreamKey stream_info,
    IAudioFrame audioFrame)
```
回调单个远端用户的音频帧地址，供自定义音频处理。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stream_info | **RemoteStreamKey** | 音频流信息，参看 [RemoteStreamKey](Android-keytype.md#remotestreamkey) |
| audioFrame | **IAudioFrame** | 音频帧地址，参看 [IAudioFrame](Android-keytype.md#iaudioframe) |


**注意**
调用 `enableAudioProcessor`，并在参数中选择各个远端音频流时，收到此回调。

<span id="IAudioFrameProcessor-onprocessearmonitoraudioframe"></span>
### onProcessEarMonitorAudioFrame
```java
int com.ss.bytertc.engine.IAudioFrameProcessor.onProcessEarMonitorAudioFrame(
    IAudioFrame audioFrame)
```
软件耳返音频数据的回调。你可根据此回调自定义处理音频。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioFrame | **IAudioFrame** | 音频帧地址。参看 [IAudioFrame](Android-keytype.md#iaudioframe)。 |


**注意**

+ 此数据处理只影响耳返音频数据。  
+ 调用 [enableAudioProcessor](Android-api.md#RTCVideo-enableaudioprocessor)，把返回给音频处理器的音频类型设置为耳返音频后，你将收到此回调。


<span id="IAudioFrameProcessor-onprocessscreenaudioframe"></span>
### onProcessScreenAudioFrame
```java
int com.ss.bytertc.engine.IAudioFrameProcessor.onProcessScreenAudioFrame(
    IAudioFrame audioFrame)
```
屏幕共享的音频帧地址回调。你可根据此回调自定义处理音频。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioFrame | **IAudioFrame** | 音频帧地址，参看 [IAudioFrame](Android-keytype.md#iaudioframe)。 |


**注意**
调用 `enableAudioProcessor`，把返回给音频处理器的音频类型设置为屏幕共享音频后，你将收到此回调。

# IKTVEventHandler
```java
public abstract class com.ss.bytertc.ktv.IKTVEventHandler
```

KTV 事件回调接口。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **abstract void** | [onMusicListResult](#IKTVEventHandler-onmusiclistresult) |
| **abstract void** | [onSearchMusicResult](#IKTVEventHandler-onsearchmusicresult) |
| **abstract void** | [onHotMusicResult](#IKTVEventHandler-onhotmusicresult) |
| **abstract void** | [onMusicDetailResult](#IKTVEventHandler-onmusicdetailresult) |
| **abstract void** | [onDownloadSuccess](#IKTVEventHandler-ondownloadsuccess) |
| **abstract void** | [onDownloadFail](#IKTVEventHandler-ondownloadfail) |
| **abstract void** | [onDownloadMusicProgress](#IKTVEventHandler-ondownloadmusicprogress) |


## 函数说明
<span id="IKTVEventHandler-onmusiclistresult"></span>
### onMusicListResult
```java
public abstract void com.ss.bytertc.ktv.IKTVEventHandler.onMusicListResult(
    int errorCode,
    int totalSize,
    Music[] musics)
```
歌曲列表回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| errorCode | **int** | 错误码，成功时返回 0。 |
| totalSize | **int** | 数据条目总数。 |
| musics | **Music[]** | 歌曲数据数组，参看 [Music](Android-keytype.md#music)。 |


<span id="IKTVEventHandler-onsearchmusicresult"></span>
### onSearchMusicResult
```java
public abstract void com.ss.bytertc.ktv.IKTVEventHandler.onSearchMusicResult(
    int errorCode,
    int totalSize,
    Music[] musics)
```
搜索歌曲结果回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| errorCode | **int** | 错误码，成功时返回 0。 |
| totalSize | **int** | 数据条目总数。 |
| musics | **Music[]** | 歌曲数据数组，参看 [Music](Android-keytype.md#music)。 |


<span id="IKTVEventHandler-onhotmusicresult"></span>
### onHotMusicResult
```java
public abstract void com.ss.bytertc.ktv.IKTVEventHandler.onHotMusicResult(
    int errorCode,
    HotMusicInfo[] hotMusics)
```
热榜歌曲结果回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| errorCode | **int** | 错误码，成功时返回 0。 |
| hotMusics | **HotMusicInfo[]** | 热榜歌曲数据数组，参看 [HotMusicInfo](Android-keytype.md#hotmusicinfo)。 |


<span id="IKTVEventHandler-onmusicdetailresult"></span>
### onMusicDetailResult
```java
public abstract void com.ss.bytertc.ktv.IKTVEventHandler.onMusicDetailResult(
    int errorCode,
    Music music)
```
歌曲详细信息回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| errorCode | **int** | 错误码，成功时返回 0。 |
| music | **Music** | 歌曲数据，参看 [Music](Android-keytype.md#music)。 |


<span id="IKTVEventHandler-ondownloadsuccess"></span>
### onDownloadSuccess
```java
public abstract void com.ss.bytertc.ktv.IKTVEventHandler.onDownloadSuccess(
    int downloadId,
    DownloadResult result)
```
下载成功回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| downloadId | **int** | 下载任务 ID。 |
| result | **DownloadResult** | 下载信息，参看 [DownloadResult](Android-keytype.md#downloadresult)。 |


<span id="IKTVEventHandler-ondownloadfail"></span>
### onDownloadFail
```java
public abstract void com.ss.bytertc.ktv.IKTVEventHandler.onDownloadFail(
    int downloadId,
    int errorCode)
```
下载失败回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| downloadId | **int** | 下载任务 ID。 |
| errorCode | **int** | 错误码。 |


<span id="IKTVEventHandler-ondownloadmusicprogress"></span>
### onDownloadMusicProgress
```java
public abstract void com.ss.bytertc.ktv.IKTVEventHandler.onDownloadMusicProgress(
    int downloadId,
    int downloadProgress)
```
歌曲文件下载进度回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| downloadId | **int** | 下载任务 ID。 |
| downloadProgress | **int** | 下载进度百分比，取值范围 [0,100]。 |


# IKTVPlayerEventHandler
```java
public abstract class com.ss.bytertc.ktv.IKTVPlayerEventHandler
```

KTV 播放器回调接口。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **abstract void** | [onPlayProgress](#IKTVPlayerEventHandler-onplayprogress) |
| **abstract void** | [onPlayStateChange](#IKTVPlayerEventHandler-onplaystatechange) |


## 函数说明
<span id="IKTVPlayerEventHandler-onplayprogress"></span>
### onPlayProgress
```java
public abstract void com.ss.bytertc.ktv.IKTVPlayerEventHandler.onPlayProgress(
    @NonNull String musicId,
    long progress)
```
音乐播放进度回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| musicId | **@NonNull String** | 音乐 ID。 |
| progress | **long** | 音乐播放进度，单位为毫秒。 |


<span id="IKTVPlayerEventHandler-onplaystatechange"></span>
### onPlayStateChange
```java
public abstract void com.ss.bytertc.ktv.IKTVPlayerEventHandler.onPlayStateChange(
    int errorCode,
    @NonNull String musicId,
    @NonNull PlayState playState)
```
音乐播放状态改变回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| errorCode | **int** | 错误码。 |
| musicId | **@NonNull String** | 音乐 ID。 |
| playState | **@NonNull PlayState** | 音乐播放状态，参看 [PlayState](Android-keytype.md#playstate)。 |


**注意**
此回调被触发的时机汇总如下：

+ 调用 [playMusic](Android-api.md#KTVPlayer-playmusic) 成功后，会触发 playState 值为 PLAY_STATE_PLAYING 的回调；否则会触发 playState 值为 PLAY_STATE_FAILED 的回调。
+ 使用相同的音乐 ID 重复调用 [playMusic](Android-api.md#KTVPlayer-playmusic) 后，后一次播放会覆盖前一次，且会触发 playState 值为 PLAY_STATE_PLAYING 的回调，表示后一次音乐播放已开始。
+ 调用 [pauseMusic](Android-api.md#KTVPlayer-pausemusic) 方法暂停播放成功后，会触发 playState 值为 PLAY_STATE_PAUSED 的回调；否则触发 playState 值为 PLAY_STATE_FAILED 的回调。
+ 调用 [resumeMusic](Android-api.md#KTVPlayer-resumemusic) 方法恢复播放成功后，会触发 playState 值为 PLAY_STATE_PLAYING 的回调；否则触发 playState 值为 PLAY_STATE_FAILED 的回调。
+ 调用 [stopMusic](Android-api.md#KTVPlayer-stopmusic) 方法停止播放成功后，会触发 playState 值为 PLAY_STATE_STOPPED 的回调；否则触发 playState 值为 PLAY_STATE_FAILED 的回调。
+ 音乐播放结束会触发 playState 值为 PLAY_STATE_FINISHED 的回调。


# IAudioProcessor
```java
public interface com.ss.bytertc.engine.IAudioProcessor
```

自定义音频处理器


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **int** | [processAudioFrame](#IAudioProcessor-processaudioframe) |


## 函数说明
<span id="IAudioProcessor-processaudioframe"></span>
### processAudioFrame
```java
int com.ss.bytertc.engine.IAudioProcessor.processAudioFrame(
    IAudioFrame audioFrame)
```
获取 RTC SDK 采集得到的音频帧，并进行自定义处理，最终将处理后的音频帧给到 RTC SDK 用于编码传输。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioFrame | **IAudioFrame** | RTC SDK 采集到的音频帧，自定义处理可直接对音频 buffer 进行修改。参看 [IAudioFrame](Android-keytype.md#iaudioframe)。 |

**返回值**

0: 未处理  
\>0: 处理成功  
< 0: 处理失败


**注意**
在进行音频自定义处理前，你需要调用 `registerLocalAudioProcessor` 设置音频自定义处理器。