# RTCRoom
```java
public abstract class com.ss.bytertc.engine.RTCRoom
```



## 成员函数

| 返回 | 名称 |
| --- | --- |
| **abstract void** | [destroy](#RTCRoom-destroy) |
| **abstract int** | [joinRoom](#RTCRoom-joinroom) |
| **abstract void** | [setRTCRoomEventHandler](#RTCRoom-setrtcroomeventhandler) |
| **abstract void** | [leaveRoom](#RTCRoom-leaveroom) |
| **abstract void** | [setUserVisibility](#RTCRoom-setuservisibility) |
| **abstract int** | [updateToken](#RTCRoom-updatetoken) |
| **abstract long** | [sendUserMessage](#RTCRoom-sendusermessage) |
| **abstract long** | [sendUserBinaryMessage](#RTCRoom-senduserbinarymessage) |
| **abstract long** | [sendRoomMessage](#RTCRoom-sendroommessage) |
| **abstract long** | [sendRoomBinaryMessage](#RTCRoom-sendroombinarymessage) |
| **abstract void** | [setMultiDeviceAVSync](#RTCRoom-setmultideviceavsync) |
| **abstract int** | [setRemoteVideoConfig](#RTCRoom-setremotevideoconfig) |
| **abstract void** | [publishStream](#RTCRoom-publishstream) |
| **abstract void** | [unpublishStream](#RTCRoom-unpublishstream) |
| **abstract void** | [publishScreen](#RTCRoom-publishscreen) |
| **abstract void** | [unpublishScreen](#RTCRoom-unpublishscreen) |
| **abstract int** | [subscribeStream](#RTCRoom-subscribestream) |
| **abstract int** | [subscribeAllStreams](#RTCRoom-subscribeallstreams) |
| **abstract int** | [unsubscribeStream](#RTCRoom-unsubscribestream) |
| **abstract int** | [unsubscribeAllStreams](#RTCRoom-unsubscribeallstreams) |
| **abstract int** | [subscribeScreen](#RTCRoom-subscribescreen) |
| **abstract int** | [unsubscribeScreen](#RTCRoom-unsubscribescreen) |
| **abstract void** | [pauseAllSubscribedStream](#RTCRoom-pauseallsubscribedstream) |
| **abstract void** | [resumeAllSubscribedStream](#RTCRoom-resumeallsubscribedstream) |
| **abstract int** | [startForwardStreamToRooms](#RTCRoom-startforwardstreamtorooms) |
| **abstract int** | [updateForwardStreamToRooms](#RTCRoom-updateforwardstreamtorooms) |
| **abstract void** | [stopForwardStreamToRooms](#RTCRoom-stopforwardstreamtorooms) |
| **abstract void** | [pauseForwardStreamToAllRooms](#RTCRoom-pauseforwardstreamtoallrooms) |
| **abstract void** | [resumeForwardStreamToAllRooms](#RTCRoom-resumeforwardstreamtoallrooms) |
| **abstract IRangeAudio** | [getRangeAudio](#RTCRoom-getrangeaudio) |
| **abstract ISpatialAudio** | [getSpatialAudio](#RTCRoom-getspatialaudio) |
| **abstract void** | [setRemoteRoomAudioPlaybackVolume](#RTCRoom-setremoteroomaudioplaybackvolume) |
| **abstract int** | [setAudioSelectionConfig](#RTCRoom-setaudioselectionconfig) |
| **abstract long** | [setRoomExtraInfo](#RTCRoom-setroomextrainfo) |
| **abstract int** | [startSubtitle](#RTCRoom-startsubtitle) |
| **abstract int** | [stopSubtitle](#RTCRoom-stopsubtitle) |
| **abstract int** | [[deprecated] subscribeUserStream](#RTCRoom-subscribeuserstream) |


## 函数说明
<span id="RTCRoom-destroy"></span>
### destroy
```java
public abstract void com.ss.bytertc.engine.RTCRoom.destroy()
```
退出并销毁调用 [createRTCRoom](#RTCVideo-creatertcroom) 所创建的房间实例。


<span id="RTCRoom-joinroom"></span>
### joinRoom
```java
public abstract int com.ss.bytertc.engine.RTCRoom.joinRoom(
    String token,
    UserInfo userInfo,
    RTCRoomConfig roomConfig)
```
加入房间。<br>
多房间场景下，调用 [createRTCRoom](#RTCVideo-creatertcroom) 创建房间后，调用此方法加入房间，同房间内其他用户进行音视频通话。  <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| token | **String** | 动态密钥。用于对进房用户进行鉴权验证。  <br/>进入房间需要携带 Token。测试时可使用控制台生成临时 Token，正式上线需要使用密钥 SDK 在你的服务端生成并下发 Token。Token 有效期及生成方式参看[使用 Token 完成鉴权](70121)。  <br/>使用不同 AppID 的 App 是不能互通的。  <br/>请务必保证生成 Token 使用的 AppID 和创建引擎时使用的 AppID 相同，否则会导致加入房间失败。具体失败原因会通过 [onRoomStateChanged](Android-callback.md#IRTCRoomEventHandler-onroomstatechanged) 回调告知。 |
| userInfo | **UserInfo** | 用户信息。参看 [UserInfo](Android-keytype.md#userinfo)。 |
| roomConfig | **RTCRoomConfig** | 房间参数配置，设置房间模式以及是否自动发布或订阅流。具体配置模式参看 [RTCRoomConfig](Android-keytype.md#rtcroomconfig)。 |

**返回值**

+ 0：方法调用成功。  
+ -1：roomID / userInfo.uid 包含了无效的参数。  
+ -2：已经在房间内。接口调用成功后，只要收到返回值为 0 ，且未调用 [leaveRoom](#RTCRoom-leaveroom) 成功，则再次调用进房接口时，无论填写的房间 ID 和用户 ID 是否重复，均触发此返回值。  
+ -3：room 为空。  


**注意**

+ 同一个 App ID 的同一个房间内，每个用户的用户 ID 必须是唯一的。如果两个用户的用户 ID 相同，则后进房的用户会将先进房的用户踢出房间，并且先进房的用户会收到 [onRoomStateChanged](Android-callback#IRTCRoomEventHandler-onroomstatechanged) 回调通知，错误类型详见 [ERROR_CODE_DUPLICATE_LOGIN](Android-errorcode.md#ErrorCode-error_code_duplicate_login)。  
+ 本地用户调用此方法加入房间成功后，会收到 [onRoomStateChanged](Android-callback.md#IRTCRoomEventHandler-onroomstatechanged) 回调通知。若本地用户同时为可见用户，加入房间时远端用户会收到 [onUserJoined](Android-callback.md#IRTCRoomEventHandler-onuserjoined) 回调通知。关于可见性设置参看 [setUserVisibility](#RTCRoom-setuservisibility)。  
+ 用户加入房间成功后，在本地网络状况不佳的情况下，SDK 可能会与服务器失去连接，并触发 [onConnectionStateChanged](Android-callback.md#IRTCVideoEventHandler-onconnectionstatechanged) 回调。此时 SDK 会自动重试，直到成功重连。重连成功后，本地会收到 [onRoomStateChanged](Android-callback.md#IRTCRoomEventHandler-onroomstatechanged) 回调通知；如果加入房间的用户是可见用户，远端用户会收到 [onUserJoined](Android-callback.md#IRTCRoomEventHandler-onuserjoined) 回调通知。  


<span id="RTCRoom-setrtcroomeventhandler"></span>
### setRTCRoomEventHandler
```java
public abstract void com.ss.bytertc.engine.RTCRoom.setRTCRoomEventHandler(
    IRTCRoomEventHandler rtcRoomEventHandler)
```
通过设置 [RTCRoom](#rtcroom) 对象的事件句柄，监听此对象对应的回调事件。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoomEventHandler | **IRTCRoomEventHandler** | 参看 [IRTCRoomEventHandler](Android-callback.md#irtcroomeventhandler) |


<span id="RTCRoom-leaveroom"></span>
### leaveRoom
```java
public abstract void com.ss.bytertc.engine.RTCRoom.leaveRoom()
```
离开房间。  <br>
用户调用此方法离开房间，结束通话过程，释放所有通话相关的资源。  <br>
此方法是异步操作，调用返回时并没有真正退出房间。真正退出房间后，本地会收到 [onLeaveRoom](Android-callback.md#IRTCRoomEventHandler-onleaveroom) 回调通知。  <br>


**注意**

+ 调用 [setUserVisibility](#RTCRoom-setuservisibility) 将自身设为可见的用户离开房间后，房间内其他用户会收到 [onUserLeave](Android-callback.md#IRTCRoomEventHandler-onuserleave) 回调通知。  
+ 如果调用此方法后立即销毁引擎，SDK 将无法触发 [onLeaveRoom](Android-callback.md#IRTCRoomEventHandler-onleaveroom) 回调。  


<span id="RTCRoom-setuservisibility"></span>
### setUserVisibility
```java
public abstract void com.ss.bytertc.engine.RTCRoom.setUserVisibility(
    boolean enable)
```
设置用户可见性。未调用该接口前，本地用户默认对他人可见。<br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| enable | **boolean** | 设置用户是否对房间内其他用户可见：  <br/>• true: 可以在房间内发布音视频流，房间中的其他用户将收到用户的行为通知，例如进房、开启视频采集和退房。  <br/>• false: 不可以在房间内发布音视频流，房间中的其他用户不会收到用户的行为通知，例如进房、开启视频采集和退房。 |


**注意**

+ 在加入房间前后，用户均可调用此方法设置用户可见性。 
+ 在房间内，调用此方法成功切换用户可见性后，房间内其他用户会收到相应的回调通知：
- 从可见换至不可见时，房间内其他用户会收到 [onUserLeave](Android-callback.md#IRTCRoomEventHandler-onuserleave)；  
- 从不可见切换至可见时，房间内其他用户会收到 [onUserJoined](Android-callback.md#IRTCRoomEventHandler-onuserjoined) 。
+ 若调用该方法将可见性设为 false，此时尝试发布流会收到 `WARNING_CODE_PUBLISH_STREAM_FORBIDEN` 警告。


<span id="RTCRoom-updatetoken"></span>
### updateToken
```java
public abstract int com.ss.bytertc.engine.RTCRoom.updateToken(
    String token)
```
更新 Token。
Token 中同时包含进房、发布和订阅权限，各权限有一定的有效期，并且到期前 30 秒会触发回调，提示用户更新 Token 相关权限。此时需要重新获取 Token，并调用此方法更新 Token，以保证通话的正常进行。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| token | **String** | 重新获取的有效 Token。<br/>如果传入的 Token 无效，回调错误码为 [ErrorCode](Android-errorcode.md#errorcode) 中的 `-1010` 提示传入的 Token 无效。 |

**返回值**
方法调用结果：

+ 0：成功；
+ <0：失败。具体失败原因参看 [ReturnStatus](Android-keytype.md#returnstatus)。


**注意**

+ 3.50（不含）以前的版本中，Token 中的发布和订阅权限为保留参数，无实际控制权限；3.50 及以后版本开放 Token 发布订阅控制权限，如需通过 Token 控制连麦权限，请联系技术支持团队开通白名单后支持。
+ 请勿同时调用 [updateToken](#RTCRoom-updatetoken) 和 [joinRoom](#RTCRoom-joinroom) 方法更新 Token。若因 Token 过期或无效导致加入房间失败或已被移出房间，你应该在获取新的有效 Token 后调用 [joinRoom](#RTCRoom-joinroom) 重新加入房间。


<span id="RTCRoom-sendusermessage"></span>
### sendUserMessage
```java
public abstract long com.ss.bytertc.engine.RTCRoom.sendUserMessage(
    String userId,
    String messageStr,
    MessageConfig config)
```
给房间内指定的用户发送点对点文本消息（P2P）。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| userId | **String** | 消息接收用户的 ID |
| messageStr | **String** | 发送的文本消息内容。消息不超过 64 KB。 |
| config | **MessageConfig** | 消息发送的可靠/有序类型，参看 [MessageConfig](Android-keytype.md#messageconfig) |

**返回值**

+ \>0：发送成功，返回这次发送消息的编号，从 1 开始递增  
+ -1：发送失败，RTCRoom 实例未创建  
+ -2：发送失败，uid 为空


**注意**

+ 在发送房间内文本消息前，必须先调用 [joinRoom](#RTCRoom-joinroom) 加入房间。  
+ 调用后，会收到 [onUserMessageSendResult](Android-callback.md#IRTCRoomEventHandler-onusermessagesendresult) 回调，通知消息发送成功或失败；  
+ 若消息发送成功，则 userId 所指定的用户会收到 [onUserMessageReceived](Android-callback.md#IRTCRoomEventHandler-onusermessagereceived) 回调。


<span id="RTCRoom-senduserbinarymessage"></span>
### sendUserBinaryMessage
```java
public abstract long com.ss.bytertc.engine.RTCRoom.sendUserBinaryMessage(
    String userId,
    byte[] buffer,
    MessageConfig config)
```
给房间内指定的用户发送点对点二进制消息（P2P）。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| userId | **String** | 消息接收用户的 ID |
| buffer | **byte[]** | 发送的二进制消息内容。消息不超过 46KB。 |
| config | **MessageConfig** | 消息发送的可靠/有序类型，参看 [MessageConfig](Android-keytype.md#messageconfig)。 |


**注意**

+ 在发送房间内二进制消息前，必须先调用 [joinRoom](#RTCRoom-joinroom) 加入房间。  
+ 调用后，会收到 [onUserMessageSendResult](Android-callback.md#IRTCRoomEventHandler-onusermessagesendresult) 回调，通知消息发送成功或失败；  
+ 若消息发送成功，则 userId 所指定的用户会收到 [onUserBinaryMessageReceived](Android-callback.md#IRTCRoomEventHandler-onuserbinarymessagereceived) 回调。


<span id="RTCRoom-sendroommessage"></span>
### sendRoomMessage
```java
public abstract long com.ss.bytertc.engine.RTCRoom.sendRoomMessage(
    String messageStr)
```
给房间内的所有其他用户群发文本消息。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| messageStr | **String** | 发送的文本消息内容，消息不超过 64 KB。 |


**注意**

+ 在房间内广播文本消息前，必须先调用 [joinRoom](#RTCRoom-joinroom) 加入房间。  
+ 调用后，会收到 [onRoomMessageSendResult](Android-callback.md#IRTCRoomEventHandler-onroommessagesendresult) 回调；
+ 同一房间内的其他用户会收到 [onRoomMessageReceived](Android-callback.md#IRTCRoomEventHandler-onroommessagereceived) 回调。


<span id="RTCRoom-sendroombinarymessage"></span>
### sendRoomBinaryMessage
```java
public abstract long com.ss.bytertc.engine.RTCRoom.sendRoomBinaryMessage(
    byte[] buffer)
```
给房间内的所有其他用户群发二进制消息。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| buffer | **byte[]** | 发送的二进制消息内容，消息不超过 46KB。 |


**注意**

+ 在房间内广播二进制消息前，必须先调用 [joinRoom](#RTCRoom-joinroom) 加入房间。  
+ 调用后，会收到 [onRoomMessageSendResult](Android-callback.md#IRTCRoomEventHandler-onroommessagesendresult) 回调；
+ 同一房间内的其他用户会收到 [onRoomBinaryMessageReceived](Android-callback.md#IRTCRoomEventHandler-onroombinarymessagereceived) 回调。


<span id="RTCRoom-setmultideviceavsync"></span>
### setMultiDeviceAVSync
```java
public abstract void com.ss.bytertc.engine.RTCRoom.setMultiDeviceAVSync(
    String audioUserId)
```
设置发流端音画同步。  <br>
当同一用户同时使用两个通话设备分别采集发送音频和视频时，有可能会因两个设备所处的网络环境不一致而导致发布的流不同步，此时你可以在视频发送端调用该接口，SDK 会根据音频流的时间戳自动校准视频流，以保证接收端听到音频和看到视频在时间上的同步性。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioUserId | **String** | 音频发送端的用户 ID，将该参数设为空则可解除当前音视频的同步关系。 |


**注意**

+ 该方法在进房前后均可调用。  
+ 进行音画同步的音频发布用户 ID 和视频发布用户 ID 须在同一个 RTC 房间内。  
+ 调用该接口后音画同步状态发生改变时，你会收到 [onAVSyncStateChange](Android-callback.md#IRTCRoomEventHandler-onavsyncstatechange) 回调。  
+ 同一 RTC 房间内允许存在多个音视频同步关系，但需注意单个音频源不支持与多个视频源同时同步。  
+ 如需更换同步音频源，再次调用该接口传入新的 `audioUserId` 即可；如需更换同步视频源，需先解除当前的同步关系，后在新视频源端开启同步。


<span id="RTCRoom-setremotevideoconfig"></span>
### setRemoteVideoConfig
```java
public abstract int com.ss.bytertc.engine.RTCRoom.setRemoteVideoConfig(
    String userId,
    RemoteVideoConfig remoteVideoConfig)
```
设置期望订阅的远端视频流的参数。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| userId | **String** | 期望配置订阅参数的远端视频流发布用户的 ID。 |
| remoteVideoConfig | **RemoteVideoConfig** | 期望配置的远端视频流参数，参看 [RemoteVideoConfig](Android-keytype.md#remotevideoconfig)。 |

**返回值**
方法调用结果：

+ 0：成功；
+ <0：失败。具体失败原因参看 [ReturnStatus](Android-keytype.md#returnstatus)。


**注意**

+ 若使用 342 及以前版本的 SDK，调用该方法前请联系技术支持人员开启按需订阅功能。  
+ 该方法仅在发布端调用 [enableSimulcastMode](#RTCVideo-enablesimulcastmode) 开启了发送多路视频流的情况下生效，此时订阅端将收到来自发布端与期望设置的参数最相近的一路流；否则订阅端只会收到一路参数为分辨率 640px × 360px、帧率 15fps 的视频流。  
+ 若发布端开启了推送多路流功能，但订阅端不对流参数进行设置，则默认接受发送端设置的分辨率最大的一路视频流。  
+ 该方法需在进房后调用，若想进房前设置，你需调用 [joinRoom](#RTCRoom-joinroom)，并对 `roomConfig` 中的 `remoteVideoConfig` 进行设置。  
+ SDK 会根据发布端和所有订阅端的设置灵活调整视频流的参数，具体调整策略详见[推送多路流](https://www.volcengine.com/docs/6348/70139)文档。


<span id="RTCRoom-publishstream"></span>
### publishStream
```java
public abstract void com.ss.bytertc.engine.RTCRoom.publishStream(
    MediaStreamType type)
```
在当前所在房间内发布本地通过摄像头/麦克风采集的媒体流

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| type | **MediaStreamType** | 媒体流类型，用于指定发布音频/视频，参看 [MediaStreamType](Android-keytype.md#mediastreamtype) |


**注意**

+ 如果你已经在用户进房时通过调用 [joinRoom](#RTCRoom-joinroom) 成功选择了自动发布，则无需再调用本接口。
+ 调用 [setUserVisibility](#RTCRoom-setuservisibility) 方法将自身设置为不可见后无法调用该方法，需将自身切换至可见后方可调用该方法发布摄像头音视频流。 
+ 如果你需要发布屏幕共享流，调用 [publishScreen](#RTCRoom-publishscreen)。
+ 如果你需要向多个房间发布流，调用 [startForwardStreamToRooms](#RTCRoom-startforwardstreamtorooms)。  
+ 调用此方法后，房间中的所有远端用户会收到 [onUserPublishStream](Android-callback.md#IRTCRoomEventHandler-onuserpublishstream) 回调通知，其中成功收到了音频流的远端用户会收到 [onFirstRemoteAudioFrame](Android-callback.md#IRTCVideoEventHandler-onfirstremoteaudioframe) 回调，订阅了视频流的远端用户会收到 [onFirstRemoteVideoFrameDecoded](Android-callback.md#IRTCVideoEventHandler-onfirstremotevideoframedecoded) 回调。
+ 调用 [unpublishStream](#RTCRoom-unpublishstream) 取消发布。


<span id="RTCRoom-unpublishstream"></span>
### unpublishStream
```java
public abstract void com.ss.bytertc.engine.RTCRoom.unpublishStream(
    MediaStreamType type)
```
停止将本地摄像头/麦克风采集的媒体流发布到当前所在房间中

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| type | **MediaStreamType** | 媒体流类型，用于指定停止发布音频/视频，参看 [MediaStreamType](Android-keytype.md#mediastreamtype) |


**注意**

+ 调用 [publishStream](#RTCRoom-publishstream) 手动发布摄像头音视频流后，你需调用此接口停止发布。
+ 调用此方法停止发布音视频流后，房间中的其他用户将会收到 [onUserUnpublishStream](Android-callback.md#IRTCRoomEventHandler-onuserunpublishstream) 回调通知。


<span id="RTCRoom-publishscreen"></span>
### publishScreen
```java
public abstract void com.ss.bytertc.engine.RTCRoom.publishScreen(
    MediaStreamType type)
```
在当前所在房间内发布本地屏幕共享音视频流

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| type | **MediaStreamType** | 媒体流类型，用于指定发布屏幕音频/视频，参看 [MediaStreamType](Android-keytype.md#mediastreamtype)。 |


**注意**

+ 即使你已经在用户进房时通过调用 [joinRoom](#RTCRoom-joinroom) 成功选择了自动发布，也需要调用本接口发布屏幕流。
+ 调用 [setUserVisibility](#RTCRoom-setuservisibility) 方法将自身设置为不可见后无法调用该方法，需将自身切换至可见后方可调用该方法发布屏幕流。 
+ 调用该方法后，房间中的所有远端用户会收到 [onUserPublishScreen](Android-callback.md#IRTCRoomEventHandler-onuserpublishscreen) 回调，其中成功收到音频流的远端用户会收到 [onFirstRemoteAudioFrame](Android-callback.md#IRTCVideoEventHandler-onfirstremoteaudioframe) 回调，订阅了视频流的远端用户会收到 [onFirstRemoteVideoFrameDecoded](Android-callback.md#IRTCVideoEventHandler-onfirstremotevideoframedecoded) 回调。
+ 调用该方法后，本地用户会收到 [onScreenVideoFrameSendStateChanged](Android-callback.md#IRTCVideoEventHandler-onscreenvideoframesendstatechanged)。
+ 如果你需要向多个房间发布流，调用 [startForwardStreamToRooms](#RTCRoom-startforwardstreamtorooms)。  
+ 调用 [unpublishScreen](#RTCRoom-unpublishscreen) 取消发布。
+ 查看 [Android 端屏幕共享](https://www.volcengine.com/docs/6348/124176)，获取更多信息。


<span id="RTCRoom-unpublishscreen"></span>
### unpublishScreen
```java
public abstract void com.ss.bytertc.engine.RTCRoom.unpublishScreen(
    MediaStreamType type)
```
停止将本地屏幕共享音视频流发布到当前所在房间中

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| type | **MediaStreamType** | 媒体流类型，用于指定停止发布屏幕音频/视频，参看 [MediaStreamType](Android-keytype.md#mediastreamtype) |


**注意**

+ 调用 [publishScreen](#RTCRoom-publishscreen) 发布屏幕流后，你需调用此接口停止发布。 
+ 调用此方法停止发布屏幕音视频流后，房间中的其他用户将会收到 [onUserUnpublishScreen](Android-callback.md#IRTCRoomEventHandler-onuserunpublishscreen) 回调。


<span id="RTCRoom-subscribeuserstream"></span>
### subscribeUserStream
```java
public abstract int com.ss.bytertc.engine.RTCRoom.subscribeUserStream(
    String uid,
    StreamIndex streamType,
    SubscribeMediaType mediaType,
    SubscribeVideoConfig subscribeVideoConfig)
```
> Deprecated  since 3.36 and will be deleted in 3.51, use [subscribeStream](#RTCRoom-subscribestream), [unsubscribeStream](#RTCRoom-unsubscribestream), [subscribeScreen](#RTCRoom-subscribescreen) and [unsubscribeScreen](#RTCRoom-unsubscribescreen) instead.

订阅房间内指定的远端音视频流。  <br>
无论自动订阅还是手动订阅模式，用户都可以调用此方法按需订阅房间中的音视频流。  <br>
该方法也可用于更新已经订阅的流的属性、媒体类型等配置。 <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | **String** | 指定订阅的远端发布音视频流的用户 ID。 |
| streamType | **StreamIndex** | 流属性，用于指定订阅主流/屏幕流，参看 [StreamIndex](Android-keytype.md#streamindex-2)。 |
| mediaType | **SubscribeMediaType** | 媒体类型，用于指定订阅音/视频，参看 [SubscribeMediaType](Android-keytype.md#subscribemediatype)。 |
| subscribeVideoConfig | **SubscribeVideoConfig** | 视频订阅配置，参看 [SubscribeVideoConfig](Android-keytype.md#subscribevideoconfig) 。 |


**注意**

+ 你必须通过 [onStreamAdd](Android-callback.md#IRTCRoomEventHandler-onstreamadd) 和 [onStreamRemove](Android-callback.md#IRTCRoomEventHandler-onstreamremove) 两个回调获取当前房间里的音视频流信息，并调用本方法按需订阅流或修改订阅配置。  
+ 若订阅失败，你会收到 [onStreamStateChanged](Android-callback#IRTCRoomEventHandler-onstreamstatechanged) 回调通知，具体失败原因参看 [ErrorCode](Android-errorcode.md#errorcode)。
+ 若调用 [pauseAllSubscribedStream](#RTCRoom-pauseallsubscribedstream) 暂停接收远端音视频流，此时仍可使用该方法对暂停接收的流进行设置，你会在调用 [resumeAllSubscribedStream](#RTCRoom-resumeallsubscribedstream) 恢复接收流后收到修改设置后的流。  


<span id="RTCRoom-subscribestream"></span>
### subscribeStream
```java
public abstract int com.ss.bytertc.engine.RTCRoom.subscribeStream(
    String uid,
    MediaStreamType type)
```
订阅房间内指定的通过摄像头/麦克风采集的媒体流，或更新对指定远端用户的订阅选项

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | **String** | 指定订阅的远端发布音视频流的用户 ID。 |
| type | **MediaStreamType** | 媒体流类型，用于指定订阅音频/视频。参看 [MediaStreamType](Android-keytype.md#mediastreamtype)。 |

**返回值**
方法调用结果：

+ 0：成功；
+ <0：失败。具体失败原因参看 [ReturnStatus](Android-keytype.md#returnstatus)。


**注意**

+ 当调用本接口时，当前用户已经订阅该远端用户，不论是通过手动订阅还是自动订阅，都将根据本次传入的参数，更新订阅配置。
+ 你必须先通过 [onUserPublishStream](Android-callback.md#IRTCRoomEventHandler-onuserpublishstream) 回调获取当前房间里的远端摄像头音视频流信息，然后调用本方法按需订阅。  
+ 调用该方法后，你会收到 [onStreamSubscribed](Android-callback.md#IRTCRoomEventHandler-onstreamsubscribed) 通知方法调用结果。  
+ 成功订阅远端用户的媒体流后，订阅关系将持续到调用 [unsubscribeStream](#RTCRoom-unsubscribestream) 取消订阅或本端用户退房。 
+ 关于其他调用异常，你会收到 [onStreamStateChanged](Android-callback#IRTCRoomEventHandler-onstreamstatechanged) 回调通知，具体异常原因参看 [ErrorCode](Android-errorcode.md#errorcode)。


<span id="RTCRoom-subscribeallstreams"></span>
### subscribeAllStreams
```java
public abstract int com.ss.bytertc.engine.RTCRoom.subscribeAllStreams(
    MediaStreamType type)
```
订阅房间内所有通过摄像头/麦克风采集的媒体流，或更新订阅选项。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| type | **MediaStreamType** | 媒体流类型，用于指定订阅音频/视频。参看 [MediaStreamType](Android-keytype.md#mediastreamtype)。 |

**返回值**

+ 0: 方法调用成功  
+ !0: 方法调用失败  


**注意**

+ 多次调用订阅接口时，将根据末次调用接口和传入的参数，更新订阅配置。
+ 开启音频选路后，如果房间内的媒体流超过上限，建议通过调用 [subscribeStream](#RTCRoom-subscribestream) 逐一指定需要订阅的媒体流。
+ 调用该方法后，你会收到 [onStreamSubscribed](Android-callback.md#IRTCRoomEventHandler-onstreamsubscribed) 通知方法调用结果。  
+ 成功订阅远端用户的媒体流后，订阅关系将持续到调用 [unsubscribeStream](#RTCRoom-unsubscribestream) 取消订阅或本端用户退房。 
+ 关于其他调用异常，你会收到 [onStreamStateChanged](Android-callback#IRTCRoomEventHandler-onstreamstatechanged) 回调通知，具体异常原因参看 [ErrorCode](Android-errorcode.md#errorcode)。


<span id="RTCRoom-unsubscribestream"></span>
### unsubscribeStream
```java
public abstract int com.ss.bytertc.engine.RTCRoom.unsubscribeStream(
    String uid,
    MediaStreamType type)
```
取消订阅房间内指定的通过摄像头/麦克风采集的媒体流。  <br>
该方法对自动订阅和手动订阅模式均适用。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | **String** | 指定取消订阅的远端发布音视频流的用户 ID。 |
| type | **MediaStreamType** | 媒体流类型，用于指定取消订阅音频/视频。参看 [MediaStreamType](Android-keytype.md#mediastreamtype)。 |

**返回值**
方法调用结果：

+ 0：成功；
+ <0：失败。具体失败原因参看 [ReturnStatus](Android-keytype.md#returnstatus)。


**注意**

+ 调用该方法后，你会收到 [onStreamSubscribed](Android-callback.md#IRTCRoomEventHandler-onstreamsubscribed) 通知方法调用结果。  
+ 关于其他调用异常，你会收到 [onStreamStateChanged](Android-callback#IRTCRoomEventHandler-onstreamstatechanged) 回调通知，具体失败原因参看 [ErrorCode](Android-errorcode.md#errorcode)。


<span id="RTCRoom-unsubscribeallstreams"></span>
### unsubscribeAllStreams
```java
public abstract int com.ss.bytertc.engine.RTCRoom.unsubscribeAllStreams(
    MediaStreamType type)
```
取消订阅房间内所有的通过摄像头/麦克风采集的媒体流。  <br>
自动订阅和手动订阅的流都可以通过本方法取消订阅。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| type | **MediaStreamType** | 媒体流类型，用于指定取消订阅音频/视频。参看 [MediaStreamType](Android-keytype.md#mediastreamtype)。 |

**返回值**
方法调用结果：  

+ 0：成功  
+ !0：失败


**注意**

+ 调用该方法后，你会收到 [onStreamSubscribed](Android-callback.md#IRTCRoomEventHandler-onstreamsubscribed) 通知方法调用结果。  
+ 关于其他调用异常，你会收到 [onStreamStateChanged](Android-callback#IRTCRoomEventHandler-onstreamstatechanged) 回调通知，具体失败原因参看 [ErrorCode](Android-errorcode.md#errorcode)。


<span id="RTCRoom-subscribescreen"></span>
### subscribeScreen
```java
public abstract int com.ss.bytertc.engine.RTCRoom.subscribeScreen(
    String uid,
    MediaStreamType type)
```
订阅房间内指定的远端屏幕共享音视频流，或更新对指定远端用户的订阅选项

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | **String** | 指定订阅的远端发布屏幕流的用户 ID。 |
| type | **MediaStreamType** | 媒体流类型，用于指定订阅音频/视频。参看 [MediaStreamType](Android-keytype.md#mediastreamtype)。 |

**返回值**
方法调用结果：

+ 0：成功；
+ <0：失败。具体失败原因参看 [ReturnStatus](Android-keytype.md#returnstatus)。


**注意**

+ 当调用本接口时，当前用户已经订阅该远端用户，不论是通过手动订阅还是自动订阅，都将根据本次传入的参数，更新订阅配置。
+ 你必须先通过 [onUserPublishScreen](Android-callback.md#IRTCRoomEventHandler-onuserpublishscreen) 回调获取当前房间里的远端屏幕流信息，然后调用本方法按需订阅。  
+ 调用该方法后，你会收到 [onStreamSubscribed](Android-callback.md#IRTCRoomEventHandler-onstreamsubscribed) 通知方法调用结果。  
+ 成功订阅远端用户的媒体流后，订阅关系将持续到调用 [unsubscribeScreen](#RTCRoom-unsubscribescreen) 取消订阅或本端用户退房。 
+ 关于其他调用异常，你会收到 [onStreamStateChanged](Android-callback#IRTCRoomEventHandler-onstreamstatechanged) 回调通知，具体异常原因参看 [ErrorCode](Android-errorcode.md#errorcode)。


<span id="RTCRoom-unsubscribescreen"></span>
### unsubscribeScreen
```java
public abstract int com.ss.bytertc.engine.RTCRoom.unsubscribeScreen(
    String uid,
    MediaStreamType type)
```
取消订阅房间内指定的远端屏幕共享音视频流。  <br>
该方法对自动订阅和手动订阅模式均适用。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | **String** | 指定取消订阅的远端发布屏幕流的用户 ID。 |
| type | **MediaStreamType** | 媒体流类型，用于指定取消订阅音频/视频。参看 [MediaStreamType](Android-keytype.md#mediastreamtype)。 |

**返回值**
方法调用结果：

+ 0：成功；
+ <0：失败。具体失败原因参看 [ReturnStatus](Android-keytype.md#returnstatus)。


**注意**

+ 调用该方法后，你会收到 [onStreamSubscribed](Android-callback.md#IRTCRoomEventHandler-onstreamsubscribed) 通知流的退订结果。  
+ 关于其他调用异常，你会收到 [onStreamStateChanged](Android-callback#IRTCRoomEventHandler-onstreamstatechanged) 回调通知，具体失败原因参看 [ErrorCode](Android-errorcode.md#errorcode)。


<span id="RTCRoom-pauseallsubscribedstream"></span>
### pauseAllSubscribedStream
```java
public abstract void com.ss.bytertc.engine.RTCRoom.pauseAllSubscribedStream(
    PauseResumeControlMediaType mediaType)
```
暂停接收来自远端的媒体流。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mediaType | **PauseResumeControlMediaType** | 媒体流类型，指定需要暂停接收音频还是视频流，参看 [PauseResumeControlMediaType](Android-keytype.md#pauseresumecontrolmediatype)。 |


**注意**

+ 该方法仅暂停远端流的接收，并不影响远端流的采集和发送；  
+ 该方法不改变用户的订阅状态以及订阅流的属性。  
+ 若想恢复接收远端流，需调用 [resumeAllSubscribedStream](#RTCRoom-resumeallsubscribedstream)。 
+ 多房间场景下，仅暂停接收发布在当前所在房间的流。


<span id="RTCRoom-resumeallsubscribedstream"></span>
### resumeAllSubscribedStream
```java
public abstract void com.ss.bytertc.engine.RTCRoom.resumeAllSubscribedStream(
    PauseResumeControlMediaType mediaType)
```
恢复接收来自远端的媒体流

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mediaType | **PauseResumeControlMediaType** | 媒体流类型，指定需要暂停接收音频还是视频流，参看 [PauseResumeControlMediaType](Android-keytype.md#pauseresumecontrolmediatype) |


**注意**

+ 该方法仅恢复远端流的接收，并不影响远端流的采集和发送；  
+ 该方法不改变用户的订阅状态以及订阅流的属性。


<span id="RTCRoom-startforwardstreamtorooms"></span>
### startForwardStreamToRooms
```java
public abstract int com.ss.bytertc.engine.RTCRoom.startForwardStreamToRooms(
    List<ForwardStreamInfo> forwardStreamInfos)
```
开始跨房间转发媒体流。
在调用 [joinRoom](#RTCRoom-joinroom) 后调用本接口，实现向多个房间转发媒体流，适用于跨房间连麦等场景。<br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| forwardStreamInfos | **List<ForwardStreamInfo>** | 跨房间媒体流转发指定房间的信息。参看 [ForwardStreamInfo](Android-keytype.md#forwardstreaminfo)。 |

**返回值**

0: 方法调用成功  
<0: 方法调用失败  


**注意**

+ 调用本方法后，将在本端触发 [onForwardStreamStateChanged](Android-callback.md#IRTCRoomEventHandler-onforwardstreamstatechanged) 回调。
+ 调用本方法后，你可以通过监听 [onForwardStreamEvent](Android-callback.md#IRTCRoomEventHandler-onforwardstreamevent) 回调来获取各个目标房间在转发媒体流过程中的相关事件。
+ 开始转发后，目标房间中的用户将接收到本地用户进房 [onUserJoined](Android-callback.md#IRTCRoomEventHandler-onuserjoined) 和发流 [onUserPublishStream](Android-callback.md#IRTCRoomEventHandler-onuserpublishstream)/[onUserPublishScreen](Android-callback.md#IRTCRoomEventHandler-onuserpublishscreen) 的回调。
+ 调用本方法后，可以调用 [updateForwardStreamToRooms](#RTCRoom-updateforwardstreamtorooms) 更新目标房间信息，例如，增加或减少目标房间等。
+ 调用本方法后，可以调用 [stopForwardStreamToRooms](#RTCRoom-stopforwardstreamtorooms) 停止向所有房间转发媒体流。
+ 调用本方法后，可以调用 [pauseForwardStreamToAllRooms](#RTCRoom-pauseforwardstreamtoallrooms) 暂停向所有房间转发媒体流。


<span id="RTCRoom-updateforwardstreamtorooms"></span>
### updateForwardStreamToRooms
```java
public abstract int com.ss.bytertc.engine.RTCRoom.updateForwardStreamToRooms(
    List<ForwardStreamInfo> forwardStreamInfos)
```
更新跨房间媒体流转发信息。<br>
通过 [startForwardStreamToRooms](#RTCRoom-startforwardstreamtorooms) 发起媒体流转发后，可调用本方法增加或者减少目标房间，或更新房间密钥。
调用本方法增加或删减房间后，将在本端触发 [onForwardStreamStateChanged](Android-callback.md#IRTCRoomEventHandler-onforwardstreamstatechanged) 回调，包含发生了变动的目标房间中媒体流转发状态。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| forwardStreamInfos | **List<ForwardStreamInfo>** | 跨房间媒体流转发目标房间信息。参看 [ForwardStreamInfo](Android-keytype.md#forwardstreaminfo)。 |

**返回值**

+ 0: 方法调用成功  
+ <0: 方法调用失败


**注意**

+ 增加目标房间后，新增目标房间中的用户将接收到本地用户进房 [onUserJoined](Android-callback.md#IRTCRoomEventHandler-onuserjoined) 和发布 [onUserPublishStream](Android-callback.md#IRTCRoomEventHandler-onuserpublishstream)/[onUserPublishScreen](Android-callback.md#IRTCRoomEventHandler-onuserpublishscreen) 的回调。
+ 删减目标房间后，原目标房间中的用户将接收到本地用户停止发布 [onUserUnpublishStream](Android-callback.md#IRTCRoomEventHandler-onuserunpublishstream)/[onUserUnpublishScreen](Android-callback.md#IRTCRoomEventHandler-onuserunpublishscreen) 和退房 [onUserLeave](Android-callback.md#IRTCRoomEventHandler-onuserleave) 的回调。


<span id="RTCRoom-stopforwardstreamtorooms"></span>
### stopForwardStreamToRooms
```java
public abstract void com.ss.bytertc.engine.RTCRoom.stopForwardStreamToRooms()
```
停止跨房间媒体流转发。
通过 [startForwardStreamToRooms](#RTCRoom-startforwardstreamtorooms) 发起媒体流转发后，可调用本方法停止向所有目标房间转发媒体流。


**注意**

+ 调用本方法后，将在本端触发 [onForwardStreamStateChanged](Android-callback.md#IRTCRoomEventHandler-onforwardstreamstatechanged) 回调。
+ 调用本方法后，原目标房间中的用户将接收到本地用户停止发布 [onUserUnpublishStream](Android-callback.md#IRTCRoomEventHandler-onuserunpublishstream)/[onUserUnpublishScreen](Android-callback.md#IRTCRoomEventHandler-onuserunpublishscreen) 和退房 [onUserLeave](Android-callback.md#IRTCRoomEventHandler-onuserleave) 的回调。
+ 如果需要停止向指定的房间转发媒体流，请调用 [updateForwardStreamToRooms](#RTCRoom-updateforwardstreamtorooms) 更新房间信息。
+ 如果需要暂停转发，请调用 [pauseForwardStreamToAllRooms](#RTCRoom-pauseforwardstreamtoallrooms)，并在之后随时调用 [resumeForwardStreamToAllRooms](#RTCRoom-resumeforwardstreamtoallrooms) 快速恢复转发。


<span id="RTCRoom-pauseforwardstreamtoallrooms"></span>
### pauseForwardStreamToAllRooms
```java
public abstract void com.ss.bytertc.engine.RTCRoom.pauseForwardStreamToAllRooms()
```
暂停跨房间媒体流转发。
通过 [startForwardStreamToRooms](#RTCRoom-startforwardstreamtorooms) 发起媒体流转发后，可调用本方法暂停向所有目标房间转发媒体流。
调用本方法暂停向所有目标房间转发后，你可以随时调用 [resumeForwardStreamToAllRooms](#RTCRoom-resumeforwardstreamtoallrooms) 快速恢复转发。


**注意**
调用本方法后，目标房间中的用户将接收到本地用户停止发布 [onUserUnpublishStream](Android-callback.md#IRTCRoomEventHandler-onuserunpublishstream)/[onUserUnpublishScreen](Android-callback.md#IRTCRoomEventHandler-onuserunpublishscreen) 和退房 [onUserLeave](Android-callback.md#IRTCRoomEventHandler-onuserleave) 的回调。

<span id="RTCRoom-resumeforwardstreamtoallrooms"></span>
### resumeForwardStreamToAllRooms
```java
public abstract void com.ss.bytertc.engine.RTCRoom.resumeForwardStreamToAllRooms()
```
恢复跨房间媒体流转发。
调用 [pauseForwardStreamToAllRooms](#RTCRoom-pauseforwardstreamtoallrooms) 暂停转发之后，调用本方法恢复向所有目标房间转发媒体流。


**注意**
目标房间中的用户将接收到本地用户进房 [onUserJoined](Android-callback.md#IRTCRoomEventHandler-onuserjoined) 和发布 [onUserPublishStream](Android-callback.md#IRTCRoomEventHandler-onuserpublishstream)/[onUserPublishScreen](Android-callback.md#IRTCRoomEventHandler-onuserpublishscreen) 的回调。

<span id="RTCRoom-getrangeaudio"></span>
### getRangeAudio
```java
public abstract IRangeAudio com.ss.bytertc.engine.RTCRoom.getRangeAudio()
```
获取范围语音接口实例。

**返回值**
方法调用结果： 

+ IRangeAudio：成功，返回一个 [IRangeAudio](#irangeaudio) 实例。  
+ null：失败，当前 SDK 不支持范围语音功能。


**注意**
首次调用该方法须在创建房间后、加入房间前。范围语音相关 API 和调用时序详见[范围语音](https://www.volcengine.com/docs/6348/114727)。

<span id="RTCRoom-getspatialaudio"></span>
### getSpatialAudio
```java
public abstract ISpatialAudio com.ss.bytertc.engine.RTCRoom.getSpatialAudio()
```
获取空间音频接口实例。

**返回值**
空间音频管理接口实例。如果返回 NULL，则表示不支持空间音频，详见 [ISpatialAudio](#ispatialaudio) 。


**注意**

+ 首次调用该方法须在创建房间后、加入房间前。空间音频相关 API 和调用时序详见[空间音频](https://www.volcengine.com/docs/6348/93903)。 
+ 只有在使用支持真双声道播放的设备时，才能开启空间音频效果；  
+ 在网络状况不佳的情况下，即使开启了这一功能，也不会产生空间音频效果；  
+ 机型性能不足可能会导致音频卡顿，使用低端机时，不建议开启空间音频效果；  
+ 空间音频效果在启用服务端选路功能时，不生效。  


<span id="RTCRoom-setremoteroomaudioplaybackvolume"></span>
### setRemoteRoomAudioPlaybackVolume
```java
public abstract void com.ss.bytertc.engine.RTCRoom.setRemoteRoomAudioPlaybackVolume(
    int volume)
```
调节某个房间内所有远端用户的音频播放音量。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| volume | **int** | 音频播放音量和原始音量的比值，范围是 [0, 400]，单位为 %，自带溢出保护。<br/>为保证更好的通话质量，建议将 volume 值设为 [0,100]。 <br/>• 0: 静音  <br/>• 100: 原始音量，默认值  <br/>• 400: 最大可为原始音量的 4 倍(自带溢出保护) |


**注意**
假设某远端用户 A 始终在被调节的目标用户范围内，+ 当该方法与 [setRemoteAudioPlaybackVolume](#RTCVideo-setremoteaudioplaybackvolume) 共同使用时，本地收听用户 A 的音量为后调用的方法设置的音量；

+ 当该方法与 [setPlaybackVolume](#RTCVideo-setplaybackvolume) 方法共同使用时，本地收听用户 A 的音量将为两次设置的音量效果的叠加。


<span id="RTCRoom-setaudioselectionconfig"></span>
### setAudioSelectionConfig
```java
public abstract int com.ss.bytertc.engine.RTCRoom.setAudioSelectionConfig(
    AudioSelectionPriority audioSelectionPriority)
```
> Available since 3.52

设置本端发布流在音频选路中的优先级。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioSelectionPriority | **AudioSelectionPriority** | 本端发布流在音频选路中的优先级，默认正常参与音频选路。参见 [AudioSelectionPriority](Android-keytype.md#audioselectionpriority)。 |


**注意**
在控制台上为本 appId 开启音频选路后，调用本接口才会生效。进房前后调用均可生效。更多信息参见[音频选路](https://www.volcengine.com/docs/6348/113547)。
如果本端用户同时加入不同房间，使用本接口进行的设置相互独立。



<span id="RTCRoom-setroomextrainfo"></span>
### setRoomExtraInfo
```java
public abstract long com.ss.bytertc.engine.RTCRoom.setRoomExtraInfo(
    String key,
    String value)
```
> Available since 3.52

设置/更新房间附加信息，可用于标识房间状态或属性，或灵活实现各种业务逻辑。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| key | **String** | 房间附加信息键值，长度小于 10 字节。<br/>同一房间内最多可存在 5 个 key，超出则会从第一个 key 起进行替换。 |
| value | **String** | 房间附加信息内容，长度小于 128 字节。 |

**返回值**

+ 0: 方法调用成功，返回本次调用的任务编号； 
+ <0: 方法调用失败，具体原因详见 [SetRoomExtraInfoResult](Android-keytype.md#setroomextrainforesult)。


**注意**

+ 在设置房间附加信息前，必须先调用 [joinRoom](#RTCRoom-joinroom) 加入房间。  
+ 调用该方法后，会收到一次 [onSetRoomExtraInfoResult](Android-callback.md#IRTCRoomEventHandler-onsetroomextrainforesult) 回调，提示设置结果。  
+ 调用该方法成功设置附加信息后，同一房间内的其他用户会收到关于该信息的回调 [onRoomExtraInfoUpdate](Android-callback.md#IRTCRoomEventHandler-onroomextrainfoupdate)。
+ 新进房的用户会收到进房前房间内已有的全部附加信息通知。


<span id="RTCRoom-startsubtitle"></span>
### startSubtitle
```java
public abstract int com.ss.bytertc.engine.RTCRoom.startSubtitle(
    SubtitleConfig subtitleConfig)
```
> Available since 3.52.

识别或翻译房间内所有用户的语音，形成字幕。<br>
语音识别或翻译的结果会通过 [onSubtitleMessageReceived](Android-callback.md#IRTCRoomEventHandler-onsubtitlemessagereceived) 事件回调给你。<br>
调用该方法后，你会收到 [onSubtitleStateChanged](Android-callback.md#IRTCRoomEventHandler-onsubtitlestatechanged) 回调，通知字幕是否开启。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| subtitleConfig | **SubtitleConfig** | 字幕配置信息。参看 [SubtitleConfig](Android-keytype.md#subtitleconfig)。 |

**返回值**

+  0: 调用成功。  
+ !0: 调用失败。


**注意**
此方法需要在进房后调用。  
如果想要指定源语言，你需要在调用 `joinRoom` 接口进房时，通过 `extraInfo` 参数传入 `"source_language": "zh"` JSON 字符串，设置源语言为中文；传入 `"source_language": "en"`JSON 字符串，设置源语言为英文；传入 `"source_language": "ja"` JSON 字符串，设置源语言为日文。如果你未指定源语言，SDK 会将系统语种设定为源语言。如果你的系统语种不是中文、英文和日文，此时 SDK 会自动将中文设为源语言。  
使用字幕功能前，你需要[开通机器翻译服务](https://www.volcengine.com/docs/4640/130262)，并前往 [RTC 控制台](https://console.volcengine.com/rtc/cloudRTC?tab=subtitle)，在功能配置页面开启字幕功能。


<span id="RTCRoom-stopsubtitle"></span>
### stopSubtitle
```java
public abstract int com.ss.bytertc.engine.RTCRoom.stopSubtitle()
```
> Available since 3.52.

关闭字幕。 <br>
调用该方法后，用户会收到 [onSubtitleStateChanged](Android-callback.md#IRTCRoomEventHandler-onsubtitlestatechanged) 回调，通知字幕是否关闭。

**返回值**

+  0: 调用成功。  
+ !0: 调用失败。


# RTCVideo
```java
public abstract class com.ss.bytertc.engine.RTCVideo
```

RTCVideo Class


## 静态函数

| 返回 | 名称 |
| --- | --- |
| **static synchronized RTCVideo** | [createRTCVideo](#RTCVideo-creatertcvideo) |
| **static synchronized void** | [destroyRTCVideo](#RTCVideo-destroyrtcvideo) |
| **static String** | [getSDKVersion](#RTCVideo-getsdkversion) |
| **static String** | [getErrorDescription](#RTCVideo-geterrordescription) |
| **static int** | [[deprecated] setDeviceId](#RTCVideo-setdeviceid) |
| **static int** | [[deprecated] setEnv](#RTCVideo-setenv) |


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **abstract void** | [setRtcVideoEventHandler](#RTCVideo-setrtcvideoeventhandler) |
| **abstract IRTCAudioDeviceManager** | [getAudioDeviceManager](#RTCVideo-getaudiodevicemanager) |
| **abstract void** | [startVideoCapture](#RTCVideo-startvideocapture) |
| **abstract void** | [stopVideoCapture](#RTCVideo-stopvideocapture) |
| **abstract void** | [startAudioCapture](#RTCVideo-startaudiocapture) |
| **abstract void** | [stopAudioCapture](#RTCVideo-stopaudiocapture) |
| **abstract void** | [setAudioScenario](#RTCVideo-setaudioscenario) |
| **abstract void** | [setAudioProfile](#RTCVideo-setaudioprofile) |
| **abstract void** | [setAnsMode](#RTCVideo-setansmode) |
| **abstract int** | [setVoiceChangerType](#RTCVideo-setvoicechangertype) |
| **abstract int** | [setVoiceReverbType](#RTCVideo-setvoicereverbtype) |
| **abstract int** | [setLocalVoiceEqualization](#RTCVideo-setlocalvoiceequalization) |
| **abstract int** | [setLocalVoiceReverbParam](#RTCVideo-setlocalvoicereverbparam) |
| **abstract int** | [enableLocalVoiceReverb](#RTCVideo-enablelocalvoicereverb) |
| **abstract int** | [setLocalVideoCanvas](#RTCVideo-setlocalvideocanvas) |
| **abstract void** | [updateLocalVideoCanvas](#RTCVideo-updatelocalvideocanvas) |
| **abstract void** | [setLocalVideoSink](#RTCVideo-setlocalvideosink) |
| **abstract void** | [setRemoteVideoSink](#RTCVideo-setremotevideosink) |
| **abstract void** | [updateRemoteStreamVideoCanvas](#RTCVideo-updateremotestreamvideocanvas) |
| **abstract void** | [setRemoteVideoCanvas](#RTCVideo-setremotevideocanvas) |
| **abstract void** | [setLocalVideoMirrorType](#RTCVideo-setlocalvideomirrortype) |
| **abstract void** | [setVideoRotationMode](#RTCVideo-setvideorotationmode) |
| **abstract void** | [switchCamera](#RTCVideo-switchcamera) |
| **abstract void** | [setAudioRoute](#RTCVideo-setaudioroute) |
| **abstract AudioRoute** | [getAudioRoute](#RTCVideo-getaudioroute) |
| **abstract int** | [setDefaultAudioRoute](#RTCVideo-setdefaultaudioroute) |
| **abstract void** | [enableExternalSoundCard](#RTCVideo-enableexternalsoundcard) |
| **abstract void** | [setCaptureVolume](#RTCVideo-setcapturevolume) |
| **abstract void** | [setPlaybackVolume](#RTCVideo-setplaybackvolume) |
| **abstract void** | [setLocalVoicePitch](#RTCVideo-setlocalvoicepitch) |
| **abstract void** | [enableVocalInstrumentBalance](#RTCVideo-enablevocalinstrumentbalance) |
| **abstract void** | [enablePlaybackDucking](#RTCVideo-enableplaybackducking) |
| **abstract long** | [login](#RTCVideo-login) |
| **abstract void** | [logout](#RTCVideo-logout) |
| **abstract void** | [updateLoginToken](#RTCVideo-updatelogintoken) |
| **abstract void** | [setServerParams](#RTCVideo-setserverparams) |
| **abstract void** | [getPeerOnlineStatus](#RTCVideo-getpeeronlinestatus) |
| **abstract long** | [sendUserMessageOutsideRoom](#RTCVideo-sendusermessageoutsideroom) |
| **abstract long** | [sendUserBinaryMessageOutsideRoom](#RTCVideo-senduserbinarymessageoutsideroom) |
| **abstract long** | [sendServerMessage](#RTCVideo-sendservermessage) |
| **abstract long** | [sendServerBinaryMessage](#RTCVideo-sendserverbinarymessage) |
| **abstract NetworkDetectionStartReturn** | [startNetworkDetection](#RTCVideo-startnetworkdetection) |
| **abstract void** | [stopNetworkDetection](#RTCVideo-stopnetworkdetection) |
| **abstract void** | [enableAudioFrameCallback](#RTCVideo-enableaudioframecallback) |
| **abstract void** | [disableAudioFrameCallback](#RTCVideo-disableaudioframecallback) |
| **abstract void** | [registerAudioFrameObserver](#RTCVideo-registeraudioframeobserver) |
| **abstract void** | [registerAudioProcessor](#RTCVideo-registeraudioprocessor) |
| **abstract void** | [enableAudioProcessor](#RTCVideo-enableaudioprocessor) |
| **abstract void** | [disableAudioProcessor](#RTCVideo-disableaudioprocessor) |
| **abstract int** | [registerLocalVideoProcessor](#RTCVideo-registerlocalvideoprocessor) |
| **abstract void** | [setVideoDigitalZoomConfig](#RTCVideo-setvideodigitalzoomconfig) |
| **abstract void** | [setVideoDigitalZoomControl](#RTCVideo-setvideodigitalzoomcontrol) |
| **abstract void** | [startVideoDigitalZoomControl](#RTCVideo-startvideodigitalzoomcontrol) |
| **abstract void** | [stopVideoDigitalZoomControl](#RTCVideo-stopvideodigitalzoomcontrol) |
| **abstract void** | [registerLocalEncodedVideoFrameObserver](#RTCVideo-registerlocalencodedvideoframeobserver) |
| **abstract void** | [registerRemoteEncodedVideoFrameObserver](#RTCVideo-registerremoteencodedvideoframeobserver) |
| **abstract void** | [setVideoSourceType](#RTCVideo-setvideosourcetype) |
| **abstract int** | [pushExternalVideoFrame](#RTCVideo-pushexternalvideoframe) |
| **abstract int** | [startPushMixedStreamToCDN](#RTCVideo-startpushmixedstreamtocdn) |
| **abstract int** | [updatePushMixedStreamToCDN](#RTCVideo-updatepushmixedstreamtocdn) |
| **abstract void** | [startPushSingleStreamToCDN](#RTCVideo-startpushsinglestreamtocdn) |
| **abstract void** | [stopPushStreamToCDN](#RTCVideo-stoppushstreamtocdn) |
| **abstract int** | [setVideoCaptureConfig](#RTCVideo-setvideocaptureconfig) |
| **abstract void** | [enableSimulcastMode](#RTCVideo-enablesimulcastmode) |
| **abstract int** | [setVideoEncoderConfig](#RTCVideo-setvideoencoderconfig) |
| **abstract int** | [setVideoEncoderConfig](#RTCVideo-setvideoencoderconfig) |
| **abstract int** | [setScreenVideoEncoderConfig](#RTCVideo-setscreenvideoencoderconfig) |
| **abstract int** | [setAudioSourceType](#RTCVideo-setaudiosourcetype) |
| **abstract int** | [setAudioRenderType](#RTCVideo-setaudiorendertype) |
| **abstract int** | [pushExternalAudioFrame](#RTCVideo-pushexternalaudioframe) |
| **abstract int** | [pullExternalAudioFrame](#RTCVideo-pullexternalaudioframe) |
| **abstract int** | [pushScreenVideoFrame](#RTCVideo-pushscreenvideoframe) |
| **abstract int** | [setRemoteAudioPlaybackVolume](#RTCVideo-setremoteaudioplaybackvolume) |
| **abstract void** | [setAudioAlignmentProperty](#RTCVideo-setaudioalignmentproperty) |
| **abstract RTCRoom** | [createRTCRoom](#RTCVideo-creatertcroom) |
| **abstract void** | [setPublishFallbackOption](#RTCVideo-setpublishfallbackoption) |
| **abstract void** | [setSubscribeFallbackOption](#RTCVideo-setsubscribefallbackoption) |
| **abstract int** | [setRemoteUserPriority](#RTCVideo-setremoteuserpriority) |
| **abstract int** | [sendSEIMessage](#RTCVideo-sendseimessage) |
| **abstract int** | [setBusinessId](#RTCVideo-setbusinessid) |
| **abstract void** | [setEncryptInfo](#RTCVideo-setencryptinfo) |
| **abstract void** | [setCustomizeEncryptHandler](#RTCVideo-setcustomizeencrypthandler) |
| **abstract IVideoEffect** | [getVideoEffectInterface](#RTCVideo-getvideoeffectinterface) |
| **abstract int** | [enableEffectBeauty](#RTCVideo-enableeffectbeauty) |
| **abstract int** | [setBeautyIntensity](#RTCVideo-setbeautyintensity) |
| **abstract void** | [setVideoOrientation](#RTCVideo-setvideoorientation) |
| **abstract void** | [setRuntimeParameters](#RTCVideo-setruntimeparameters) |
| **abstract int** | [feedback](#RTCVideo-feedback) |
| **abstract void** | [startASR](#RTCVideo-startasr) |
| **abstract void** | [stopASR](#RTCVideo-stopasr) |
| **abstract int** | [startFileRecording](#RTCVideo-startfilerecording) |
| **abstract void** | [stopFileRecording](#RTCVideo-stopfilerecording) |
| **abstract int** | [startAudioRecording](#RTCVideo-startaudiorecording) |
| **abstract int** | [stopAudioRecording](#RTCVideo-stopaudiorecording) |
| **abstract IAudioMixingManager** | [getAudioMixingManager](#RTCVideo-getaudiomixingmanager) |
| **abstract void** | [setScreenAudioSourceType](#RTCVideo-setscreenaudiosourcetype) |
| **abstract void** | [setScreenAudioStreamIndex](#RTCVideo-setscreenaudiostreamindex) |
| **abstract int** | [pushScreenAudioFrame](#RTCVideo-pushscreenaudioframe) |
| **abstract void** | [startScreenCapture](#RTCVideo-startscreencapture) |
| **abstract void** | [updateScreenCapture](#RTCVideo-updatescreencapture) |
| **abstract void** | [stopScreenCapture](#RTCVideo-stopscreencapture) |
| **abstract void** | [setExternalVideoEncoderEventHandler](#RTCVideo-setexternalvideoencodereventhandler) |
| **abstract int** | [pushExternalEncodedVideoFrame](#RTCVideo-pushexternalencodedvideoframe) |
| **abstract void** | [setVideoDecoderConfig](#RTCVideo-setvideodecoderconfig) |
| **abstract void** | [requestRemoteVideoKeyFrame](#RTCVideo-requestremotevideokeyframe) |
| **abstract void** | [setEarMonitorMode](#RTCVideo-setearmonitormode) |
| **abstract void** | [setEarMonitorVolume](#RTCVideo-setearmonitorvolume) |
| **abstract void** | [enableAudioPropertiesReport](#RTCVideo-enableaudiopropertiesreport) |
| **abstract int** | [sendStreamSyncInfo](#RTCVideo-sendstreamsyncinfo) |
| **abstract boolean** | [isCameraTorchSupported](#RTCVideo-iscameratorchsupported) |
| **abstract boolean** | [isCameraZoomSupported](#RTCVideo-iscamerazoomsupported) |
| **abstract int** | [setCameraZoomRatio](#RTCVideo-setcamerazoomratio) |
| **abstract float** | [getCameraZoomMaxRatio](#RTCVideo-getcamerazoommaxratio) |
| **abstract int** | [setCameraTorch](#RTCVideo-setcameratorch) |
| **abstract boolean** | [isCameraFocusPositionSupported](#RTCVideo-iscamerafocuspositionsupported) |
| **abstract int** | [setCameraFocusPosition](#RTCVideo-setcamerafocusposition) |
| **abstract boolean** | [isCameraExposurePositionSupported](#RTCVideo-iscameraexposurepositionsupported) |
| **abstract int** | [setCameraExposurePosition](#RTCVideo-setcameraexposureposition) |
| **abstract int** | [setCameraExposureCompensation](#RTCVideo-setcameraexposurecompensation) |
| **abstract int** | [startPushPublicStream](#RTCVideo-startpushpublicstream) |
| **abstract int** | [stopPushPublicStream](#RTCVideo-stoppushpublicstream) |
| **abstract int** | [updatePublicStreamParam](#RTCVideo-updatepublicstreamparam) |
| **abstract int** | [startPlayPublicStream](#RTCVideo-startplaypublicstream) |
| **abstract int** | [stopPlayPublicStream](#RTCVideo-stopplaypublicstream) |
| **abstract int** | [setPublicStreamVideoCanvas](#RTCVideo-setpublicstreamvideocanvas) |
| **abstract int** | [setPublicStreamVideoSink](#RTCVideo-setpublicstreamvideosink) |
| **abstract int** | [setPublicStreamAudioPlaybackVolume](#RTCVideo-setpublicstreamaudioplaybackvolume) |
| **abstract int** | [startEchoTest](#RTCVideo-startechotest) |
| **abstract int** | [stopEchoTest](#RTCVideo-stopechotest) |
| **abstract void** | [setVideoWatermark](#RTCVideo-setvideowatermark) |
| **abstract void** | [clearVideoWatermark](#RTCVideo-clearvideowatermark) |
| **abstract int** | [setDummyCaptureImagePath](#RTCVideo-setdummycaptureimagepath) |
| **abstract long** | [takeLocalSnapshot](#RTCVideo-takelocalsnapshot) |
| **abstract long** | [takeRemoteSnapshot](#RTCVideo-takeremotesnapshot) |
| **abstract void** | [startCloudProxy](#RTCVideo-startcloudproxy) |
| **abstract void** | [stopCloudProxy](#RTCVideo-stopcloudproxy) |
| **abstract ISingScoringManager** | [getSingScoringManager](#RTCVideo-getsingscoringmanager) |
| **abstract NetworkTimeInfo** | [getNetworkTimeInfo](#RTCVideo-getnetworktimeinfo) |
| **abstract KTVManager** | [getKTVManager](#RTCVideo-getktvmanager) |
| **abstract int** | [startHardwareEchoDetection](#RTCVideo-starthardwareechodetection) |
| **abstract int** | [stopHardwareEchoDetection](#RTCVideo-stophardwareechodetection) |
| **abstract void** | [setCellularEnhancement](#RTCVideo-setcellularenhancement) |
| **abstract int** | [setLocalProxy](#RTCVideo-setlocalproxy) |
| **abstract void** | [[deprecated] setInternalEventHandler](#RTCVideo-setinternaleventhandler) |
| **abstract int** | [[deprecated] replaceBackground](#RTCVideo-replacebackground) |
| **abstract int** | [[deprecated] setAudioPlaybackDevice](#RTCVideo-setaudioplaybackdevice) |
| **abstract void** | [[deprecated] registerLocalAudioProcessor](#RTCVideo-registerlocalaudioprocessor) |
| **abstract void** | [[deprecated] startLiveTranscoding](#RTCVideo-startlivetranscoding) |
| **abstract void** | [[deprecated] stopLiveTranscoding](#RTCVideo-stoplivetranscoding) |
| **abstract void** | [[deprecated] updateLiveTranscoding](#RTCVideo-updatelivetranscoding) |
| **abstract int** | [[deprecated] setVideoEncoderConfig](#RTCVideo-setvideoencoderconfig) |
| **abstract int** | [[deprecated] setVideoEncoderConfig](#RTCVideo-setvideoencoderconfig) |
| **abstract void** | [[deprecated] setOnDestroyCompletedCallback](#RTCVideo-setondestroycompletedcallback) |
| **abstract int** | [[deprecated] sendSEIMessage](#RTCVideo-sendseimessage) |
| **abstract int** | [[deprecated] checkVideoEffectLicense](#RTCVideo-checkvideoeffectlicense) |
| **abstract void** | [[deprecated] setVideoEffectAlgoModelPath](#RTCVideo-setvideoeffectalgomodelpath) |
| **abstract int** | [[deprecated] enableVideoEffect](#RTCVideo-enablevideoeffect) |
| **abstract int** | [[deprecated] setVideoEffectNodes](#RTCVideo-setvideoeffectnodes) |
| **abstract int** | [[deprecated] updateVideoEffectNode](#RTCVideo-updatevideoeffectnode) |
| **abstract int** | [[deprecated] setBackgroundSticker](#RTCVideo-setbackgroundsticker) |
| **abstract int** | [[deprecated] setVideoEffectColorFilter](#RTCVideo-setvideoeffectcolorfilter) |
| **abstract int** | [[deprecated] setVideoEffectColorFilterIntensity](#RTCVideo-setvideoeffectcolorfilterintensity) |
| **abstract int** | [[deprecated] registerFaceDetectionObserver](#RTCVideo-registerfacedetectionobserver) |
| **abstract void** | [[deprecated] muteAudioPlayback](#RTCVideo-muteaudioplayback) |


## 函数说明
<span id="RTCVideo-creatertcvideo"></span>
### createRTCVideo
```java
public static synchronized RTCVideo com.ss.bytertc.engine.RTCVideo.createRTCVideo(
    Context context,
    String appId,
    IRTCVideoEventHandler handler,
    Object eglContext,
    JSONObject parameters)
```
创建引擎对象  <br>
如果当前进程中未创建引擎实例，那么你必须先使用此方法，以使用 RTC 提供的各种音视频能力。  <br>
如果当前进程中已创建了引擎实例，再次调用此方法时，会返回已创建的引擎实例。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| context | **Context** | Android Application Context |
| appId | **String** | 每个应用的唯一标识符，由 RTC 控制台随机生成的。不同的 AppId 生成的实例在 RTC 中进行音视频通话完全独立，无法互通。 |
| handler | **IRTCVideoEventHandler** | SDK 回调给应用层的 Handler，详见 [IRTCVideoEventHandler](Android-callback.md#irtcvideoeventhandler) |
| eglContext | **Object** | 如果需要支持外部纹理硬编码，则需要以 `JObject` 方式传入 `eglContext`。 |
| parameters | **JSONObject** | 私有参数。如需使用请联系技术支持人员。 |

**返回值**

+ RTCVideo：创建成功。返回一个可用的 [RTCVideo](#rtcvideo) 实例  
+ Null：.so 文件加载失败，创建失败。


**注意**
你应注意保持 handler 的生命周期必须大于 [RTCVideo](#rtcvideo) 的生命周期，即 handler 必须在调用 [destroyRTCVideo](#RTCVideo-destroyrtcvideo) 之后销毁。

<span id="RTCVideo-destroyrtcvideo"></span>
### destroyRTCVideo
```java
public static synchronized void com.ss.bytertc.engine.RTCVideo.destroyRTCVideo()
```
销毁由 [createRTCVideo](#RTCVideo-creatertcvideo) 所创建的引擎实例，并释放所有相关资源。<br>


**注意**

+ 请确保和需要销毁的 [RTCVideo](#rtcvideo) 实例相关的业务场景全部结束后，才调用此方法  
+ 该方法在调用之后，会销毁所有和此 [RTCVideo](#rtcvideo) 实例相关的内存，并且停止与媒体服务器的任何交互  
+ 调用本方法会启动 SDK 退出逻辑。引擎线程会保留，直到退出逻辑完成。因此，不要在回调线程中直接调用此 API，也不要在回调中等待主线程的执行，并同时在主线程调用本方法。不然会造成死锁。


<span id="RTCVideo-getsdkversion"></span>
### getSDKVersion
```java
public static String com.ss.bytertc.engine.RTCVideo.getSDKVersion()
```
获取 SDK 当前的版本号。

**返回值**
SDK 当前的版本号。


<span id="RTCVideo-geterrordescription"></span>
### getErrorDescription
```java
public static String com.ss.bytertc.engine.RTCVideo.getErrorDescription(
    int code)
```
获取 SDK 内各种错误码、警告码的描述文字。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| code | **int** | 通过 [onWarning](Android-callback#IRTCVideoEventHandler-onwarning) 和 [onError](Android-callback#IRTCVideoEventHandler-onerror) 回调获得的值，<br/>具体可以参考 [ErrorCode](Android-errorcode.md#errorcode) 和 [WarningCode](Android-errorcode.md#warningcode) |

**返回值**
String 描述文字


<span id="RTCVideo-setdeviceid"></span>
### setDeviceId
```java
public static int com.ss.bytertc.engine.RTCVideo.setDeviceId(
    String deviceId)
```
> Deprecated  since 3.45 and will be deleted in 3.51.

设置设备 ID 。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| deviceId | **String** | 设备 ID 。 |

**返回值**

+ 0： 成功。  
+ < 0： 失败。  
+ -1： deviceId 为空。


<span id="RTCVideo-setenv"></span>
### setEnv
```java
public static int com.ss.bytertc.engine.RTCVideo.setEnv(
    RTCEngine.Env env)
```
> Deprecated  since 3.45 and will be deleted in 3.51.

设置 SDK 当前使用的服务器环境。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| env | **RTCEngine.Env** | SDK 使用的环境参数。 |

**返回值**

+ 0： 成功。  
+ < 0： 失败。  
+ -1： native library 未加载。


**注意**

+ 本函数是可选函数，默认使用正式环境。  
+ 本函数必须在创建引擎前调用。  


<span id="RTCVideo-setinternaleventhandler"></span>
### setInternalEventHandler
```java
public abstract void com.ss.bytertc.engine.RTCVideo.setInternalEventHandler(
    IRTCEngineInternalEventHandler handler)
```
> Deprecated  since 3.45 and will be deleted in 3.51.

设置内部事件回调 Handler  <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| handler | **IRTCEngineInternalEventHandler** | 内部事件回调 handler，详见[IRTCEngineInternalEventHandler](#irtcengineinternaleventhandler) |


<span id="RTCVideo-setrtcvideoeventhandler"></span>
### setRtcVideoEventHandler
```java
public abstract void com.ss.bytertc.engine.RTCVideo.setRtcVideoEventHandler(
    IRTCVideoEventHandler engineEventHandler)
```
设置引擎事件回调的接收类，必须继承自 [IRTCVideoEventHandler](Android-callback.md#irtcvideoeventhandler) 。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engineEventHandler | **IRTCVideoEventHandler** | 事件处理器接口类，详见 [IRTCVideoEventHandler](Android-callback.md#irtcvideoeventhandler) 。 |


**注意**

+ 调用方需要自行实现一个继承自 [IRTCVideoEventHandler](Android-callback.md#irtcvideoeventhandler) 的类，并重载其中需要关注的事件。
+ 该回调为异步回调  
+ 所有的事件回调均会在独立的回调线程内触发，请接收回调事件时注意所有与线程运行环境有关的操作，如需要在 UI 线程内执行的操作等，
请勿直接在回调函数的实现中直接进行操作。


<span id="RTCVideo-getaudiodevicemanager"></span>
### getAudioDeviceManager
```java
public abstract IRTCAudioDeviceManager com.ss.bytertc.engine.RTCVideo.getAudioDeviceManager()
```
获取音频设备管理接口

**返回值**
音频设备管理接口 IRTCAudioDeviceManager


<span id="RTCVideo-startvideocapture"></span>
### startVideoCapture
```java
public abstract void com.ss.bytertc.engine.RTCVideo.startVideoCapture()
```
立即开启内部视频采集。默认为关闭状态。  <br>
内部视频采集指：使用 RTC SDK 内置视频采集模块，进行采集。<br>
调用该方法后，本地用户会收到 [onVideoDeviceStateChanged](Android-callback.md#IRTCVideoEventHandler-onvideodevicestatechanged) 的回调。  <br>
本地用户在非隐身状态下调用该方法后，房间中的其他用户会收到 [onUserStartVideoCapture](Android-callback.md#IRTCVideoEventHandler-onuserstartvideocapture) 的回调。


**注意**

+ 自 v3.37.0 版本，使用本接口需要在 Gradle 里引入 Kotlin。
+ 调用 [stopVideoCapture](#RTCVideo-stopvideocapture) 可以停止内部视频采集。否则，只有当销毁引擎实例时，内部视频采集才会停止。  
+ 创建引擎后，无论是否发布视频数据，你都可以调用该方法开启内部视频采集。只有当（内部或外部）视频采集开始以后视频流才会发布。  
+ 如果需要从自定义视频采集切换为内部视频采集，你必须先停止发布流，关闭自定义采集，再调用此方法手动开启内部采集。
+ 内部视频采集使用的摄像头由 [switchCamera](#RTCVideo-switchcamera) 接口指定。
+ 你还可以联系技术支持人员，帮助你在服务端配置采集格式并下发到 Android 端。


<span id="RTCVideo-stopvideocapture"></span>
### stopVideoCapture
```java
public abstract void com.ss.bytertc.engine.RTCVideo.stopVideoCapture()
```
立即关闭内部视频采集。默认为关闭状态。  <br>
内部视频采集指：使用 RTC SDK 内置视频采集模块，进行采集。
调用该方法，本地用户会收到 [onVideoDeviceStateChanged](Android-callback.md#IRTCVideoEventHandler-onvideodevicestatechanged) 的回调。  <br>
非隐身用户进房后调用该方法，房间中的其他用户会收到 [onUserStopVideoCapture](Android-callback.md#IRTCVideoEventHandler-onuserstopvideocapture) 的回调。


**注意**

+ 调用 [startVideoCapture](#RTCVideo-startvideocapture) 可以开启内部视频采集。  
+ 如果不调用本方法停止内部视频采集，则只有当销毁引擎实例时，内部视频采集才会停止。   


<span id="RTCVideo-startaudiocapture"></span>
### startAudioCapture
```java
public abstract void com.ss.bytertc.engine.RTCVideo.startAudioCapture()
```
开启内部音频采集。默认为关闭状态。  <br>
内部采集是指：使用 RTC SDK 内置的音频采集机制进行音频采集。
调用该方法开启后，本地用户会收到 [onAudioDeviceStateChanged](Android-callback.md#IRTCVideoEventHandler-onaudiodevicestatechanged) 的回调。  <br>
非隐身用户进房后调用该方法，房间中的其他用户会收到 [onUserStartAudioCapture](Android-callback.md#IRTCVideoEventHandler-onuserstartaudiocapture) 的回调。


**注意**

+ 若未取得当前设备的麦克风权限，调用该方法后会触发 [onWarning](Android-callback.md#IRTCVideoEventHandler-onwarning) 回调。  
+ 调用 [stopAudioCapture](#RTCVideo-stopaudiocapture) 可以关闭音频采集设备，否则，SDK 只会在销毁引擎的时候自动关闭设备。  
+ 由于不同硬件设备初始化响应时间不同，频繁调用 [stopAudioCapture](#RTCVideo-stopaudiocapture) 和本接口闭麦/开麦可能出现短暂无声问题，建议使用 [publishStream](#RTCRoom-publishstream)/[unpublishStream](#RTCRoom-unpublishstream) 实现临时闭麦和重新开麦。
+ 创建引擎后，无论是否发布音频数据，你都可以调用该方法开启音频采集，并且调用后方可发布音频。  
+ 如果需要从自定义音频采集切换为内部音频采集，你必须先停止发布流，调用 [setAudioSourceType](#RTCVideo-setaudiosourcetype) 关闭自定义采集，再调用此方法手动开启内部采集。


<span id="RTCVideo-stopaudiocapture"></span>
### stopAudioCapture
```java
public abstract void com.ss.bytertc.engine.RTCVideo.stopAudioCapture()
```
立即关闭内部音频采集。默认为关闭状态。  <br>
内部采集是指：使用 RTC SDK 内置的音频采集机制进行音频采集。
调用该方法，本地用户会收到 [onAudioDeviceStateChanged](Android-callback.md#IRTCVideoEventHandler-onaudiodevicestatechanged) 的回调。  <br>
非隐身用户进房后调用该方法，房间中的其他用户会收到 [onUserStopAudioCapture](Android-callback.md#IRTCVideoEventHandler-onuserstopaudiocapture) 的回调。


**注意**

+ 调用 [startAudioCapture](#RTCVideo-startaudiocapture) 可以开启内部音频采集设备。  
+ 如果不调用本方法停止内部音频采集，则只有当销毁引擎实例时，内部音频采集才会停止。


<span id="RTCVideo-setaudioscenario"></span>
### setAudioScenario
```java
public abstract void com.ss.bytertc.engine.RTCVideo.setAudioScenario(
    AudioScenarioType audioScenario)
```
设置音频场景类型。
你可以根据你的应用所在场景，选择合适的音频场景类型。
选择音频场景后，SDK 会自动根据客户端音频采集播放设备和状态，适用通话音量/媒体音量。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioScenario | **AudioScenarioType** | 音频场景类型，参看 [AudioScenarioType](Android-keytype.md#audioscenariotype)。 |


**注意**

+ 建议在加入房间和调用音频相关接口之前，调用此接口设置音频场景类型。如果在此之后调用此接口，可能会引入音频卡顿。
+ 通话音量更适合通话、会议等对信息准确度更高的场景。通话音量会激活系统硬件信号处理，使通话声音更清晰。同时，音量无法降低到 0。
+ 媒体音量更适合娱乐场景，因其声音的表现力会更强。媒体音量下，最低音量可以为 0。


<span id="RTCVideo-setaudioprofile"></span>
### setAudioProfile
```java
public abstract void com.ss.bytertc.engine.RTCVideo.setAudioProfile(
    AudioProfileType audioProfile)
```
设置音质档位。<br>
当所选的 [ChannelProfile](Android-keytype.md#channelprofile) 中的音频参数无法满足你的场景需求时，调用本接口切换的音质档位。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioProfile | **AudioProfileType** | 音质档位，参看 [AudioProfileType](Android-keytype.md#audioprofiletype) |


**注意**

+ 该方法在进房前后均可调用；  
+ 支持通话过程中动态切换音质档位。


<span id="RTCVideo-setansmode"></span>
### setAnsMode
```java
public abstract void com.ss.bytertc.engine.RTCVideo.setAnsMode(
    AnsMode ansMode)
```
支持根据业务场景，设置通话中的音频降噪模式。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| ansMode | **AnsMode** | 降噪模式。具体参见 [AnsMode](Android-keytype.md#ansmode)。 |


**注意**
该接口进房前后均可调用，可重复调用，仅最后一次调用生效。

<span id="RTCVideo-setvoicechangertype"></span>
### setVoiceChangerType
```java
public abstract int com.ss.bytertc.engine.RTCVideo.setVoiceChangerType(
    VoiceChangerType voiceChanger)
```
> Available since 3.32

设置变声特效类型

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| voiceChanger | **VoiceChangerType** | 变声特效类型，参看 [VoiceChangerType](Android-keytype.md#voicechangertype) |

**返回值**
方法调用结果：

+ 0：成功；
+ <0：失败。具体失败原因参看 [ReturnStatus](Android-keytype.md#returnstatus)。


**注意**

+ 在进房前后都可设置。  
+ 对 RTC SDK 内部采集的音频和自定义采集的音频都生效。 
+ 只对单声道音频生效。
+ 与 [setVoiceReverbType](#RTCVideo-setvoicereverbtype) 互斥，后设置的特效会覆盖先设置的特效。 


<span id="RTCVideo-setvoicereverbtype"></span>
### setVoiceReverbType
```java
public abstract int com.ss.bytertc.engine.RTCVideo.setVoiceReverbType(
    VoiceReverbType voiceReverb)
```
> Available since 3.32

设置混响特效类型

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| voiceReverb | **VoiceReverbType** | 混响特效类型，参看 [VoiceReverbType](Android-keytype.md#voicereverbtype) |

**返回值**
方法调用结果：

+ 0：成功；
+ <0：失败。具体失败原因参看 [ReturnStatus](Android-keytype.md#returnstatus)。


**注意**

+ 在进房前后都可设置。  
+ 对 RTC SDK 内部采集的音频和自定义采集的音频都生效。 
+ 只对单声道音频生效。
+ 与 [setVoiceChangerType](#RTCVideo-setvoicechangertype) 互斥，后设置的特效会覆盖先设置的特效。 
+ 使用本接口前，请联系 RTC 技术支持了解更多详情。


<span id="RTCVideo-setlocalvoiceequalization"></span>
### setLocalVoiceEqualization
```java
public abstract int com.ss.bytertc.engine.RTCVideo.setLocalVoiceEqualization(
    VoiceEqualizationConfig voiceEqualizationConfig)
```
设置本地采集语音的均衡效果。包含内部采集和外部采集，但不包含混音音频文件。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| voiceEqualizationConfig | **VoiceEqualizationConfig** | 语音均衡效果，参看 [VoiceEqualizationConfig](Android-keytype.md#voiceequalizationconfig) |

**返回值**

+ 0： 成功。  
+ < 0： 失败。


**注意**
根据奈奎斯特采样率，音频采样率必须大于等于设置的中心频率的两倍，否则，设置不生效。

<span id="RTCVideo-setlocalvoicereverbparam"></span>
### setLocalVoiceReverbParam
```java
public abstract int com.ss.bytertc.engine.RTCVideo.setLocalVoiceReverbParam(
    VoiceReverbConfig config)
```
设置本地采集音频的混响效果。包含内部采集和外部采集，但不包含混音音频文件。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| config | **VoiceReverbConfig** | 混响效果，参看 [VoiceReverbConfig](Android-keytype.md#voicereverbconfig) |

**返回值**

+ 0： 成功。  
+ < 0： 失败。


**注意**
调用 [enableLocalVoiceReverb](#RTCVideo-enablelocalvoicereverb) 开启混响效果。

<span id="RTCVideo-enablelocalvoicereverb"></span>
### enableLocalVoiceReverb
```java
public abstract int com.ss.bytertc.engine.RTCVideo.enableLocalVoiceReverb(
    boolean enable)
```
开启本地音效混响效果

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| enable | **boolean** | 是否开启 |

**返回值**

+ 0： 成功。  
+ < 0： 失败。


**注意**
调用 [setLocalVoiceReverbParam](#RTCVideo-setlocalvoicereverbparam) 设置混响效果。

<span id="RTCVideo-setlocalvideocanvas"></span>
### setLocalVideoCanvas
```java
public abstract int com.ss.bytertc.engine.RTCVideo.setLocalVideoCanvas(
    StreamIndex streamIndex,
    VideoCanvas videoCanvas)
```
设置本地视频渲染时使用的视图，并设置渲染模式。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamIndex | **StreamIndex** | 视频流属性, 参看 [StreamIndex](Android-keytype.md#streamindex-2) |
| videoCanvas | **VideoCanvas** | 视图信息和渲染模式, 参看 [VideoCanvas](Android-keytype.md#videocanvas) |

**返回值**

+ 0: 成功  
+ -1: videoCanvas 为空  


**注意**

+ 你应在加入房间前，绑定本地视图。退出房间后，此设置仍然有效。  
+ 如果需要解除绑定，你可以调用本方法传入空视图。


<span id="RTCVideo-updatelocalvideocanvas"></span>
### updateLocalVideoCanvas
```java
public abstract void com.ss.bytertc.engine.RTCVideo.updateLocalVideoCanvas(
    StreamIndex streamIndex,
    int renderMode,
    int background_color)
```
修改本地视频渲染模式和背景色。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamIndex | **StreamIndex** | 视频流属性。参看 [StreamIndex](Android-keytype.md#streamindex-2) |
| renderMode | **int** | 渲染模式。参看 [VideoCanvas](Android-keytype.md#videocanvas).renderMode |
| background_color | **int** | 背景颜色。参看 [VideoCanvas](Android-keytype.md#videocanvas).background_color |


**注意**
你可以在本地视频渲染过程中，调用此接口。调用结果会实时生效。

<span id="RTCVideo-setlocalvideosink"></span>
### setLocalVideoSink
```java
public abstract void com.ss.bytertc.engine.RTCVideo.setLocalVideoSink(
    StreamIndex index,
    IVideoSink videoSink,
    @IVideoSink.PixelFormat int requiredFormat)
```
将本地视频流与自定义渲染器绑定。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| index | **StreamIndex** | 视频流属性。采集的视频流/屏幕视频流，参看 [StreamIndex](Android-keytype.md#streamindex-2) |
| videoSink | **IVideoSink** | 自定义视频渲染器，参看 [IVideoSink](Android-keytype.md#ivideosink) |
| requiredFormat | **@IVideoSink.PixelFormat int** | videoSink 适用的视频帧编码格式，参看 [PixelFormat](Android-keytype.md#pixelformat) |


**注意**

+ RTC SDK 默认使用自带的渲染器（内部渲染器）进行视频渲染。 
+ 退房时将清除绑定状态。 
+ 如果需要解除绑定，你必须将 videoSink 设置为 null。
+ 一般在收到 [onFirstLocalVideoFrameCaptured](Android-callback.md#IRTCVideoEventHandler-onfirstlocalvideoframecaptured) 回调通知完成本地视频首帧采集后，调用此方法为视频流绑定自定义渲染器；然后加入房间。


<span id="RTCVideo-setremotevideosink"></span>
### setRemoteVideoSink
```java
public abstract void com.ss.bytertc.engine.RTCVideo.setRemoteVideoSink(
    RemoteStreamKey streamKey,
    IVideoSink videoSink,
    @IVideoSink.PixelFormat int requiredFormat)
```
将远端视频流与自定义渲染器绑定。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamKey | **RemoteStreamKey** | 远端流信息，用于指定需要渲染的视频流来源及属性，参看 [RemoteStreamKey](Android-keytype.md#remotestreamkey) |
| videoSink | **IVideoSink** | 自定义视频渲染器，参看 [IVideoSink](Android-keytype.md#ivideosink) |
| requiredFormat | **@IVideoSink.PixelFormat int** | videoSink 适用的视频帧编码格式，参看 [PixelFormat](Android-keytype.md#pixelformat) |


**注意**

+ RTC SDK 默认使用 RTC SDK 自带的渲染器（内部渲染器）进行视频渲染。
+ 该方法进房前后均可以调用。若想在进房前调用，你需要在加入房间前获取远端流信息；若无法预先获取远端流信息，你可以在加入房间并通过 [onUserPublishStream](Android-callback.md#IRTCRoomEventHandler-onuserpublishstream) 回调获取到远端流信息之后，再调用该方法。
+ 如果需要解除绑定，你必须将 videoSink 设置为 null。退房时将清除绑定状态。


<span id="RTCVideo-updateremotestreamvideocanvas"></span>
### updateRemoteStreamVideoCanvas
```java
public abstract void com.ss.bytertc.engine.RTCVideo.updateRemoteStreamVideoCanvas(
    RemoteStreamKey stream_key,
    int renderMode,
    int background_color)
```
修改远端视频渲染模式和背景色。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stream_key | **RemoteStreamKey** | 远端流信息。参看 [RemoteStreamKey](Android-keytype.md#remotestreamkey) |
| renderMode | **int** | 渲染模式，参看 [VideoCanvas](Android-keytype.md#videocanvas).renderMode |
| background_color | **int** | 背景颜色，参看 [VideoCanvas](Android-keytype.md#videocanvas).background_color |


**注意**
你可以在远端视频渲染过程中，调用此接口。调用结果会实时生效。

<span id="RTCVideo-setremotevideocanvas"></span>
### setRemoteVideoCanvas
```java
public abstract void com.ss.bytertc.engine.RTCVideo.setRemoteVideoCanvas(
    RemoteStreamKey stream_key,
    VideoCanvas videoCanvas)
```
渲染来自指定远端用户的视频流时，设置使用的视图和渲染模式。<br>
要解除绑定，将 `videoCanvas` 设置为空。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stream_key | **RemoteStreamKey** | 远端流信息。参看 [RemoteStreamKey](Android-keytype.md#remotestreamkey) |
| videoCanvas | **VideoCanvas** | 视图信息和渲染模式，参看 [VideoCanvas](Android-keytype.md#videocanvas) |


**注意**
本地用户离开房间时，会解除调用此 API 建立的绑定关系；远端用户离开房间则不会影响。

<span id="RTCVideo-setlocalvideomirrortype"></span>
### setLocalVideoMirrorType
```java
public abstract void com.ss.bytertc.engine.RTCVideo.setLocalVideoMirrorType(
    MirrorType mirrorType)
```
为采集到的视频流开启镜像

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mirrorType | **MirrorType** | 镜像类型，参看 [MirrorType](Android-keytype.md#mirrortype) |


**注意**

+ 切换视频源不影响镜像设置。
+ 屏幕视频流始终不受镜像设置影响。
+ 使用外部渲染器时，`mirrorType` 支持设置为 `0`（无镜像）和 `3`（本地预览和编码传输镜像），不支持设置为 `1`（本地预览镜像）。
+ 该接口调用前，各视频源的初始状态如下：
<table>
<tr><th></th><th>前置摄像头</th><th>后置摄像头</th><th>自定义采集视频源</th> <th>桌面端摄像头</th> </tr>
<tr><td>移动端</td><td>本地预览镜像，编码传输不镜像</td><td> 本地预览不镜像，编码传输不镜像 </td><td> 本地预览不镜像，编码传输不镜像 </td><td>/</td></tr>
<tr><td>桌面端</td><td>/</td><td>/</td><td> 本地预览不镜像，编码传输不镜像 </td><td> 本地预览镜像，编码传输不镜像 </td></tr> 
</table>


<span id="RTCVideo-setvideorotationmode"></span>
### setVideoRotationMode
```java
public abstract void com.ss.bytertc.engine.RTCVideo.setVideoRotationMode(
    VideoRotationMode rotationMode)
```
设置采集视频的旋转模式。默认以 App 方向为旋转参考系。<br>
接收端渲染视频时，将按照和发送端相同的方式进行旋转。<br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rotationMode | **VideoRotationMode** | 视频旋转参考系为 App 方向或重力方向，参看 [VideoRotationMode](Android-keytype.md#videorotationmode)。 |


**注意**

+ 旋转仅对内部视频采集生效，不适用于外部视频源和屏幕源。
+ 调用该接口时已开启视频采集，将立即生效；调用该接口时未开启视频采集，则将在采集开启后生效。
+ 更多信息请参考[视频采集方向](https://www.volcengine.com/docs/6348/106458)。


<span id="RTCVideo-switchcamera"></span>
### switchCamera
```java
public abstract void com.ss.bytertc.engine.RTCVideo.switchCamera(
    CameraId cameraId)
```
切换视频内部采集时使用的前置/后置摄像头 <br>
调用此接口后，在本地会触发 [onVideoDeviceStateChanged](Android-callback.md#IRTCVideoEventHandler-onvideodevicestatechanged) 回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| cameraId | **CameraId** | 摄像头 ID，参看 [CameraId](Android-keytype.md#cameraid) |

**返回值**

+ 0：方法调用成功  
+ < 0：方法调用失败  


**注意**

+ 默认使用前置摄像头。
+ 如果你正在使用相机进行视频采集，切换操作当即生效；如果相机未启动，后续开启内部采集时，会打开设定的摄像头。


<span id="RTCVideo-replacebackground"></span>
### replaceBackground
```java
public abstract int com.ss.bytertc.engine.RTCVideo.replaceBackground(
    BackgroundMode mode,
    DivideModel divide_model)
```
> Deprecated  since 3.45 and will be deleted in 3.51.

视频图像分割，替换背景

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mode | **BackgroundMode** | 背景模式，用于设置预置背景，是否虚化等 详见 [BackgroundMode](Android-keytype.md#backgroundmode) |
| divide_model | **DivideModel** | 选择使用哪种分割模型，@return  <br/>分割模型类型详见 [DivideModel](Android-keytype.md#dividemodel)<br/>• 0: 方法调用成功；  <br/>• < 0: 方法调用失败； |


<span id="RTCVideo-setaudioplaybackdevice"></span>
### setAudioPlaybackDevice
```java
public abstract int com.ss.bytertc.engine.RTCVideo.setAudioPlaybackDevice(
    AudioPlaybackDevice audioPlaybackDevice)
```
> Deprecated  since 3.38 and will be deleted in 3.51, use [setAudioRoute](#RTCVideo-setaudioroute) instead.

设置音频播放设备为扬声器或者听筒，默认使用扬声器。  <br>
音频播放设备发生变化时，会收到 [onAudioPlaybackDeviceChanged](Android-callback.md#IRTCVideoEventHandler-onaudioplaybackdevicechanged) 回调。  <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioPlaybackDevice | **AudioPlaybackDevice** | 音频播放设备（扬声器或者听筒），详见 [AudioPlaybackDevice](Android-keytype.md#audioplaybackdevice) |

**返回值**

+ 0: 方法调用成功  
+ < 0: 方法调用失败  


**注意**

+ 该方法适用于手机等移动设备。  
+ 听筒和扬声器为移动设备自带的音频播放设备。听筒一般用于通话，扬声器一般用于外放。  
+ 连接有线或者蓝牙音频播放设备后，音频路由将切换至有线耳机或者蓝牙耳机。不同音频场景中，音频路由和发布订阅状态到音量类型的映射关系详见 [AudioScenarioType](Android-keytype.md#audioscenariotype) 。  
+ 进房前和进房后，均可调用此方法设置音频播放设备。


<span id="RTCVideo-setaudioroute"></span>
### setAudioRoute
```java
public abstract void com.ss.bytertc.engine.RTCVideo.setAudioRoute(
    AudioRoute audioRoute)
```
强制切换当前的音频播放路由。默认使用 [setDefaultAudioRoute](#RTCVideo-setdefaultaudioroute) 中设置的音频路由。
音频播放路由发生变化时，会收到 [onAudioRouteChanged](Android-callback.md#IRTCVideoEventHandler-onaudioroutechanged) 回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioRoute | **AudioRoute** | 音频播放路由，参见 [AudioRoute](Android-keytype.md#audioroute)。<br/>对 Android 设备，不同的音频设备连接状态下，可切换的音频设备情况不同。参见[移动端设置音频路由](https://www.volcengine.com/docs/6348/117836)。 |


**注意**

+ 对于绝大多数音频场景，使用 [setDefaultAudioRoute](#RTCVideo-setdefaultaudioroute) 设置默认音频路由，并借助 RTC SDK 的音频路由自动切换逻辑即可完成。切换逻辑参见[移动端设置音频路由](https://www.volcengine.com/docs/6348/117836)。你应仅在例外的场景下，使用此接口，比如在接入外接音频设备时，手动切换音频路由。
+ 本接口仅支持在 `AUDIO_SCENARIO_COMMUNICATION` 音频场景下使用。你可以通过调用 [setAudioScenario](#RTCVideo-setaudioscenario) 切换音频场景。
+ 不同音频场景中，音频路由和发布订阅状态到音量类型的映射关系详见 [AudioScenarioType](Android-keytype.md#audioscenariotype) 。


<span id="RTCVideo-getaudioroute"></span>
### getAudioRoute
```java
public abstract AudioRoute com.ss.bytertc.engine.RTCVideo.getAudioRoute()
```
获取当前使用的音频播放路由。  <br>

**返回值**
详见 [AudioRoute](Android-keytype.md#audioroute)


**注意**
要设置音频路由，详见 [setAudioRoute](#RTCVideo-setaudioroute)。

<span id="RTCVideo-setdefaultaudioroute"></span>
### setDefaultAudioRoute
```java
public abstract int com.ss.bytertc.engine.RTCVideo.setDefaultAudioRoute(
    AudioRoute route)
```
将默认的音频播放设备设置为听筒或扬声器。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| route | **AudioRoute** | 音频播放设备。参看 [AudioRoute](Android-keytype.md#audioroute)。仅支持听筒或扬声器。 |

**返回值**

+ 0: 方法调用成功。
+ < 0: 方法调用失败。


**注意**
对于音频路由切换逻辑，参见[移动端设置音频路由](https://www.volcengine.com/docs/6348/117836)。

<span id="RTCVideo-enableexternalsoundcard"></span>
### enableExternalSoundCard
```java
public abstract void com.ss.bytertc.engine.RTCVideo.enableExternalSoundCard(
    boolean enable)
```
启用匹配外置声卡的音频处理模式

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| enable | **boolean** | • true: 开启 <br/>• false: 不开启(默认) |


**注意**

+ 当采用外接声卡进行音频采集时，建议开启此模式，以获得更好的音质。
+ 开启此模式时，仅支持耳机播放。如果需要使用扬声器或者外置音箱播放，关闭此模式。


<span id="RTCVideo-setcapturevolume"></span>
### setCaptureVolume
```java
public abstract void com.ss.bytertc.engine.RTCVideo.setCaptureVolume(
    StreamIndex index,
    int volume)
```
调节音频采集音量

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| index | **StreamIndex** | 流索引，指定调节主流还是调节屏幕流的音量，参看 [StreamIndex](Android-keytype.md#streamindex-2) |
| volume | **int** | 采集的音量值和原始音量的比值，范围是 [0, 400]，单位为 %，自带溢出保护。<br/>只改变音频数据的音量信息，不涉及本端硬件的音量调节。<br/>为保证更好的通话质量，建议将 volume 值设为 [0,100]。<br/>• 0：静音  <br/>• 100：原始音量  <br/>• 400: 最大可为原始音量的 4 倍(自带溢出保护) |


**注意**
在开启音频采集前后，你都可以使用此接口设定采集音量。

<span id="RTCVideo-setplaybackvolume"></span>
### setPlaybackVolume
```java
public abstract void com.ss.bytertc.engine.RTCVideo.setPlaybackVolume(
    int volume)
```
调节本地播放的所有远端用户混音后的音量。<br>
播放音频前或播放音频时，你都可以使用此接口设定播放音量。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| volume | **int** | 音频播放音量值和原始音量的比值，范围是 [0, 400]，单位为 %，自带溢出保护。  <br/>为保证更好的通话质量，建议将 volume 值设为 [0,100]。  <br/>• 0：静音  <br/>• 100：原始音量  <br/>• 400: 最大可为原始音量的 4 倍(自带溢出保护) |


**注意**
假设某远端用户 A 始终在被调节的目标用户范围内，当该方法与 [setRemoteAudioPlaybackVolume](#RTCVideo-setremoteaudioplaybackvolume) 或 [setRemoteRoomAudioPlaybackVolume](#RTCRoom-setremoteroomaudioplaybackvolume) 共同使用时，本地收听用户 A 的音量将为两次设置的音量效果的叠加。

<span id="RTCVideo-setlocalvoicepitch"></span>
### setLocalVoicePitch
```java
public abstract void com.ss.bytertc.engine.RTCVideo.setLocalVoicePitch(
    int pitch)
```
开启本地语音变调功能，多用于 K 歌场景。  <br>
使用该方法，你可以对本地语音的音调进行升调或降调等调整。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| pitch | **int** | 相对于语音原始音调的升高/降低值，取值范围[-12，12]，默认值为 0，即不做调整。  <br/>取值范围内每相邻两个值的音高距离相差半音，正值表示升调，负值表示降调，设置的绝对值越大表示音调升高或降低越多。  <br/>超出取值范围则设置失败，并且会触发 [onWarning](Android-callback#IRTCVideoEventHandler-onwarning) 回调，提示 [WarningCode](Android-errorcode.md#warningcode) 错误码为 `WARNING_CODE_SET_SCREEN_STREAM_INVALID_VOICE_PITCH` 设置语音音调不合法 |


<span id="RTCVideo-enablevocalinstrumentbalance"></span>
### enableVocalInstrumentBalance
```java
public abstract void com.ss.bytertc.engine.RTCVideo.enableVocalInstrumentBalance(
    boolean enable)
```
开启/关闭音量均衡功能。  <br>
开启音量均衡功能后，人声的响度会调整为 -16lufs。如果已调用 [setAudioMixingLoudness](#IAudioMixingManager-setaudiomixingloudness) 传入了混音音乐的原始响度，此音乐播放时，响度会调整为 -20lufs。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| enable | **boolean** | 是否开启音量均衡功能：  <br/>• true: 是  <br/>• false: 否 |


**注意**
该接口须在调用 [startAudioMixing](#IAudioMixingManager-startaudiomixing) 开始播放音频文件之前调用。

<span id="RTCVideo-enableplaybackducking"></span>
### enablePlaybackDucking
```java
public abstract void com.ss.bytertc.engine.RTCVideo.enablePlaybackDucking(
    boolean enable)
```
打开/关闭音量闪避功能，适用于在 RTC 通话过程中会同时播放短视频或音乐的场景，如“一起看”、“在线 KTV”等。  <br>
开启该功能后，当检测到远端人声时，本地的媒体播放音量会自动减弱，从而保证远端人声的清晰可辨；当远端人声消失时，本地媒体音量会恢复到闪避前的音量水平。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| enable | **boolean** | 是否开启音量闪避：  <br/>• true: 是  <br/>• false: 否 |


<span id="RTCVideo-login"></span>
### login
```java
public abstract long com.ss.bytertc.engine.RTCVideo.login(
    String token,
    String uid)
```
必须先登录，才能调用 [sendUserMessageOutsideRoom](#RTCVideo-sendusermessageoutsideroom) 和 [sendServerMessage](#RTCVideo-sendservermessage) 发送房间外点对点消息和向应用服务器发送消息 <br>
在调用本接口登录后，如果想要登出，需要调用 [logout](#RTCVideo-logout)。  <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| token | **String** | 用户登录必须携带的 Token，用于鉴权验证。<br/>测试时可使用[控制台](https://console.volcengine.com/rtc/listRTC)生成临时 Token，`roomId` 填任意值。<br/>正式上线需要使用密钥 SDK 在你的服务端生成并下发 Token，`roomId` 置空，Token 有效期及生成方式参看[使用 Token 完成鉴权](70121)。 |
| uid | **String** | 用户 ID  <br/>用户 ID 在 appid的维度下是唯一的。 |

**返回值**

+ 0：成功；
+ <0：失败。具体失败原因参看 [ReturnStatus](Android-keytype.md#returnstatus)。


**注意**
本地用户调用此方法登录成功后，会收到 [onLoginResult](Android-callback.md#IRTCVideoEventHandler-onloginresult) 回调通登录结果，远端用户不会收到通知。

<span id="RTCVideo-logout"></span>
### logout
```java
public abstract void com.ss.bytertc.engine.RTCVideo.logout()
```
调用本接口登出后，无法调用房间外消息以及端到服务器消息相关的方法或收到相关回调。


**注意**

+ 调用本接口登出后，必须先调用 [login](#RTCVideo-login) 登录。  
+ 本地用户调用此方法登出后，会收到 [onLogout](Android-callback.md#IRTCVideoEventHandler-onlogout) 回调通知结果，远端用户不会收到通知。


<span id="RTCVideo-updatelogintoken"></span>
### updateLoginToken
```java
public abstract void com.ss.bytertc.engine.RTCVideo.updateLoginToken(
    String token)
```
更新用户用于登录的 Token  <br>
Token 有一定的有效期，当 Token 过期时，需调用此方法更新登录的 Token 信息。  <br>
调用 [login](#RTCVideo-login) 方法登录时，如果使用了过期的 Token 将导致登录失败，并会收到 [onLoginResult](Android-callback.md#IRTCVideoEventHandler-onloginresult) 回调通知，错误码为 `LOGIN_ERROR_CODE_INVALID_TOKEN`。此时需要重新获取 Token，并调用此方法更新 Token。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| token | **String** | 更新的动态密钥 |


**注意**

+ 如果 Token 无效导致登录失败，则调用此方法更新 Token 后，SDK 会自动重新登录，而用户不需要自己调用 [login](#RTCVideo-login) 方法。  
+ Token 过期时，如果已经成功登录，则不会受到影响。Token 过期的错误会在下一次使用过期 Token 登录时，或因本地网络状况不佳导致断网重新登录时通知给用户。


<span id="RTCVideo-setserverparams"></span>
### setServerParams
```java
public abstract void com.ss.bytertc.engine.RTCVideo.setServerParams(
    String signature,
    String url)
```
设置应用服务器参数  <br>
客户端调用 [sendServerMessage](#RTCVideo-sendservermessage) 或 [sendServerBinaryMessage](#RTCVideo-sendserverbinarymessage) 发送消息给应用服务器之前，必须需要设置有效签名和应用服务器地址。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| signature | **String** | 动态签名  <br/>应用服务器会使用该签名对请求进行鉴权验证。 |
| url | **String** | 应用服务器的地址 |


**注意**

+ 用户必须调用 [login](#RTCVideo-login) 登录后，才能调用本接口。  
+ 调用本接口后，SDK 会使用 [onServerParamsSetResult](Android-callback.md#IRTCVideoEventHandler-onserverparamssetresult) 返回相应结果。


<span id="RTCVideo-getpeeronlinestatus"></span>
### getPeerOnlineStatus
```java
public abstract void com.ss.bytertc.engine.RTCVideo.getPeerOnlineStatus(
    String peer_user_id)
```
查询对端用户或本端用户的登录状态

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| peer_user_id | **String** | 需要查询的用户 ID |


**注意**

+ 必须调用 [login](#RTCVideo-login) 登录后，才能调用本接口。 
+ 调用本接口后，SDK 会使用 [onGetPeerOnlineStatus](Android-callback.md#IRTCVideoEventHandler-ongetpeeronlinestatus) 回调通知查询结果。  
+ 在发送房间外消息之前，用户可以通过本接口了解对端用户是否登录，从而决定是否发送消息。也可以通过本接口查询自己查看自己的登录状态。


<span id="RTCVideo-sendusermessageoutsideroom"></span>
### sendUserMessageOutsideRoom
```java
public abstract long com.ss.bytertc.engine.RTCVideo.sendUserMessageOutsideRoom(
    String uid,
    String message,
    MessageConfig config)
```
给房间外指定的用户发送文本消息（P2P）

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | **String** | 消息接收用户的 ID |
| message | **String** | 发送的文本消息内容。  <br/>消息不超过 64 KB。 |
| config | **MessageConfig** | 消息类型，参看 [MessageConfig](Android-keytype.md#messageconfig)。 |

**返回值**

+ \>0：发送成功，返回这次发送消息的编号，从 1 开始递增  
+ -1：发送失败，RTCVideo 实例未创建  
+ -2：发送失败，uid 为空


**注意**

+ 在发送房间外文本消息前，必须先调用 [login](#RTCVideo-login) 完成登录。  
+ 用户调用本接口发送文本信息后，会收到一次 [onUserMessageSendResultOutsideRoom](Android-callback.md#IRTCVideoEventHandler-onusermessagesendresultoutsideroom) 回调，得知消息是否成功发送。  
+ 若文本消息发送成功，则 uid 所指定的用户会通过 [onUserMessageReceivedOutsideRoom](Android-callback.md#IRTCVideoEventHandler-onusermessagereceivedoutsideroom) 回调收到该消息。


<span id="RTCVideo-senduserbinarymessageoutsideroom"></span>
### sendUserBinaryMessageOutsideRoom
```java
public abstract long com.ss.bytertc.engine.RTCVideo.sendUserBinaryMessageOutsideRoom(
    String uid,
    byte[] buffer,
    MessageConfig config)
```
给房间外指定的用户发送二进制消息（P2P）

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | **String** | 消息接收用户的 ID |
| buffer | **byte[]** | 发送的二进制消息内容  <br/>消息不超过 46KB。 |
| config | **MessageConfig** | 消息类型，参看 [MessageConfig](Android-keytype.md#messageconfig)。 |

**返回值**

+ \>0：发送成功，返回这次发送消息的编号，从 1 开始递增  
+ -1：发送失败，RTCVideo 实例未创建  
+ -2：发送失败，uid 为空


**注意**

+ 在发送房间外二进制消息前，必须先调用 [login](#RTCVideo-login) 完成登录。  
+ 用户调用本接口发送二进制消息后，会收到一次 [onUserMessageSendResultOutsideRoom](Android-callback.md#IRTCVideoEventHandler-onusermessagesendresultoutsideroom) 回调，通知消息是否发送成功；  
+ 若二进制消息发送成功，则 uid 所指定的用户会通过 [onUserBinaryMessageReceivedOutsideRoom](Android-callback.md#IRTCVideoEventHandler-onuserbinarymessagereceivedoutsideroom) 回调收到该条消息。


<span id="RTCVideo-sendservermessage"></span>
### sendServerMessage
```java
public abstract long com.ss.bytertc.engine.RTCVideo.sendServerMessage(
    String message)
```
客户端给应用服务器发送文本消息（P2Server）

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| message | **String** | 发送的文本消息内容  <br/>消息不超过 64 KB。 |

**返回值**

+ \>0：发送成功，返回这次发送消息的编号，从 1 开始递增  
+ -1：发送失败，RTCVideo 实例未创建


**注意**

+ 在向应用服务器发送文本消息前，必须先调用 [login](#RTCVideo-login) 完成登录，随后调用 [setServerParams](#RTCVideo-setserverparams) 设置应用服务器。  
+ 调用本接口后会收到一次 [onServerMessageSendResult](Android-callback.md#IRTCVideoEventHandler-onservermessagesendresult) 回调，通知消息发送方是否发送成功。  
+ 若文本消息发送成功，则之前调用 [setServerParams](#RTCVideo-setserverparams) 设置的应用服务器会收到该条消息。


<span id="RTCVideo-sendserverbinarymessage"></span>
### sendServerBinaryMessage
```java
public abstract long com.ss.bytertc.engine.RTCVideo.sendServerBinaryMessage(
    byte[] buffer)
```
客户端给应用服务器发送二进制消息（P2Server）

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| buffer | **byte[]** | 发送的二进制消息内容  <br/>消息不超过 46KB。 |

**返回值**

+ \>0：发送成功，返回这次发送消息的编号，从 1 开始递增  
+ -1：发送失败，RTCVideo 实例未创建


**注意**

+ 在向应用服务器发送二进制消息前，必须先调用 [login](#RTCVideo-login) 完成登录，随后调用 [setServerParams](#RTCVideo-setserverparams) 设置应用服务器。  
+ 调用本接口后，会收到一次 [onServerMessageSendResult](Android-callback.md#IRTCVideoEventHandler-onservermessagesendresult) 回调，通知消息发送方发送成功或失败；  
+ 若二进制消息发送成功，则之前调用 [setServerParams](#RTCVideo-setserverparams) 设置的应用服务器会收到该条消息。


<span id="RTCVideo-startnetworkdetection"></span>
### startNetworkDetection
```java
public abstract NetworkDetectionStartReturn com.ss.bytertc.engine.RTCVideo.startNetworkDetection(
    boolean isTestUplink,
    int expectedUplinkBitrate,
    boolean isTestDownlink,
    int expectedDownlinkBitrate)
```
开启通话前网络探测

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| isTestUplink | **boolean** | 是否探测上行带宽 |
| expectedUplinkBitrate | **int** | 期望上行带宽，单位：kbps范围为 `{0, [100-10000]}`，其中， `0` 表示由 SDK 指定最高码率。 |
| isTestDownlink | **boolean** | 是否探测下行带宽 |
| expectedDownlinkBitrate | **int** | 期望下行带宽，单位：kbps范围为 `{0, [100-10000]}`，其中， `0` 表示由 SDK 指定最高码率。 |

**返回值**
开启通话前网络探测结果，详见 [NetworkDetectionStartReturn](Android-errorcode.md#networkdetectionstartreturn)


**注意**

+ 成功调用本接口后，会在 3s 内收到一次 [onNetworkDetectionResult](Android-callback.md#IRTCVideoEventHandler-onnetworkdetectionresult) 回调，此后每 2s 收到一次该回调，通知探测结果；  
+ 若探测停止，则会收到一次 [onNetworkDetectionStopped](Android-callback.md#IRTCVideoEventHandler-onnetworkdetectionstopped) 通知探测停止。


<span id="RTCVideo-stopnetworkdetection"></span>
### stopNetworkDetection
```java
public abstract void com.ss.bytertc.engine.RTCVideo.stopNetworkDetection()
```
停止通话前网络探测


**注意**

+ 调用本接口后，会收到一次 [onNetworkDetectionStopped](Android-callback.md#IRTCVideoEventHandler-onnetworkdetectionstopped) 回调通知探测停止。


<span id="RTCVideo-enableaudioframecallback"></span>
### enableAudioFrameCallback
```java
public abstract void com.ss.bytertc.engine.RTCVideo.enableAudioFrameCallback(
    AudioFrameCallbackMethod method,
    AudioFormat format)
```
设置并开启指定的音频数据帧回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| method | **AudioFrameCallbackMethod** | 音频回调方法，参看 [AudioFrameCallbackMethod](Android-keytype.md#audioframecallbackmethod)。  <br/>当音频回调方法设置为 `AUDIO_FRAME_CALLBACK_RECORD(0)`、`AUDIO_FRAME_CALLBACK_PLAYBACK(1)`、`AUDIO_FRAME_CALLBACK_MIXED(2)`时，你需要在参数 `format` 中指定准确的采样率和声道，暂不支持设置为自动。  <br/>当音频回调方法设置为 `AUDIO_FRAME_CALLBACK_REMOTE_USER(3)`时，暂不支持音频参数格式中设置准确的采样率和声道，你需要设置为自动。 |
| format | **AudioFormat** | 音频参数格式，参看 [AudioFormat](Android-keytype.md#audioformat)。 |


**注意**
开启音频回调并调用 [registerAudioFrameObserver](#RTCVideo-registeraudioframeobserver) 后，[IAudioFrameObserver](Android-callback.md#iaudioframeobserver) 会收到对应的音频回调。两者调用顺序没有限制且相互独立。  

<span id="RTCVideo-disableaudioframecallback"></span>
### disableAudioFrameCallback
```java
public abstract void com.ss.bytertc.engine.RTCVideo.disableAudioFrameCallback(
    AudioFrameCallbackMethod method)
```
关闭音频回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| method | **AudioFrameCallbackMethod** | 音频回调方法，参看 [AudioFrameCallbackMethod](Android-keytype.md#audioframecallbackmethod)。 |


**注意**
该方法需要在调用 [enableAudioFrameCallback](#RTCVideo-enableaudioframecallback) 之后调用。

<span id="RTCVideo-registeraudioframeobserver"></span>
### registerAudioFrameObserver
```java
public abstract void com.ss.bytertc.engine.RTCVideo.registerAudioFrameObserver(
    IAudioFrameObserver observer)
```
注册音频数据回调观察者。  <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| observer | **IAudioFrameObserver** | 音频数据观察者，参看 [IAudioFrameObserver](Android-callback.md#iaudioframeobserver)。如果传入 null，则取消注册。 |


**注意**
注册音频数据回调观察者并调用 [enableAudioFrameCallback](#RTCVideo-enableaudioframecallback) 后，[IAudioFrameObserver](Android-callback.md#iaudioframeobserver) 会收到对应的音频回调。对回调中收到的音频数据进行处理，不会影响 RTC 的编码发送或渲染。

<span id="RTCVideo-registerlocalaudioprocessor"></span>
### registerLocalAudioProcessor
```java
public abstract void com.ss.bytertc.engine.RTCVideo.registerLocalAudioProcessor(
    IAudioProcessor audioProcessor,
    AudioFormat audioFormat)
```
> Deprecated  since 3.42 and will be deleted in 3.51, use [registerAudioProcessor](#RTCVideo-registeraudioprocessor) instead.

设置自定义音频处理器。  <br>
使用该处理器，你可以调用 [processAudioFrame](Android-callback.md#IAudioProcessor-processaudioframe) 对 RTC SDK 采集得到的音频帧进行自定义处理，并将处理后的音频帧用于 RTC 音视频通信。  <br>
SDK 只持有 processor 的弱引用，你应保证其生命周期。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioProcessor | **IAudioProcessor** | 自定义音频处理器，参看 [IAudioProcessor](Android-callback.md#iaudioprocessor)。如果传入null，则不对 RTC SDK 采集得到的音频帧进行自定义处理。 |
| audioFormat | **AudioFormat** | 自定义音频参数格式，参看 [AudioFormat](Android-keytype.md#audioformat)，SDK 将按指定设置给出音频帧。 |


**注意**
重复调用此接口时，仅最后一次调用生效。效果不会叠加。

<span id="RTCVideo-registeraudioprocessor"></span>
### registerAudioProcessor
```java
public abstract void com.ss.bytertc.engine.RTCVideo.registerAudioProcessor(
    IAudioFrameProcessor processor)
```
注册自定义音频处理器。<br>
注册完成后，你可以调用 [enableAudioProcessor](#RTCVideo-enableaudioprocessor)，对本地采集到的音频进行处理，RTC SDK 将对处理后的音频进行编码和发送。也可以对接收到的远端音频进行自定义处理，RTC SDK 将对处理后的音频进行渲染。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| processor | **IAudioFrameProcessor** | 自定义音频处理器，详见 [IAudioFrameProcessor](Android-callback.md#iaudioframeprocessor)。<br/>SDK 只持有 processor 的弱引用，你应保证其生命周期。 |


**注意**

- 重复调用此接口时，仅最后一次调用生效。
- 更多相关信息，详见[音频自定义处理](https://www.volcengine.com/docs/6348/80635)。

<span id="RTCVideo-enableaudioprocessor"></span>
### enableAudioProcessor
```java
public abstract void com.ss.bytertc.engine.RTCVideo.enableAudioProcessor(
    AudioProcessorMethod method,
    AudioFormat format)
```
设置并开启指定的音频帧回调，进行自定义处理。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| method | **AudioProcessorMethod** | 音频帧类型，参看 [AudioProcessorMethod](Android-keytype#audioprocessormethod)。可多次调用此接口，处理不同类型的音频帧。  <br/>选择不同类型的音频帧将收到对应的回调：<br/>• 选择本地采集的音频时，会收到 [onProcessRecordAudioFrame](Android-callback.md#IAudioFrameProcessor-onprocessrecordaudioframe)。  <br/>• 选择远端音频流的混音音频时，会收到 [onProcessPlayBackAudioFrame](Android-callback.md#IAudioFrameProcessor-onprocessplaybackaudioframe)。  <br/>• 选择远端音频流时，会收到 [onProcessRemoteUserAudioFrame](Android-callback.md#IAudioFrameProcessor-onprocessremoteuseraudioframe)。  <br/>• 选择软件耳返音频时，会收到 [onProcessEarMonitorAudioFrame](Android-callback.md#IAudioFrameProcessor-onprocessearmonitoraudioframe)。  <br/>• 选择屏幕共享音频流时，会收到 [onProcessScreenAudioFrame](Android-callback.md#IAudioFrameProcessor-onprocessscreenaudioframe)。 |
| format | **AudioFormat** | 设定自定义处理时获取的音频帧格式，参看 [AudioFormat](Android-keytype.md#audioformat)。 |


**注意**

+ 在调用此接口前，你需要调用 [registerAudioProcessor](#RTCVideo-registeraudioprocessor) 注册自定义音频处理器。
+ 要关闭音频自定义处理，调用 [disableAudioProcessor](#RTCVideo-disableaudioprocessor)。


<span id="RTCVideo-disableaudioprocessor"></span>
### disableAudioProcessor
```java
public abstract void com.ss.bytertc.engine.RTCVideo.disableAudioProcessor(
    AudioProcessorMethod method)
```
关闭自定义音频处理。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| method | **AudioProcessorMethod** | 音频帧类型，参看 [AudioProcessorMethod](Android-keytype.md#audioprocessormethod)。 |


<span id="RTCVideo-registerlocalvideoprocessor"></span>
### registerLocalVideoProcessor
```java
public abstract int com.ss.bytertc.engine.RTCVideo.registerLocalVideoProcessor(
    IVideoProcessor processor,
    VideoPreprocessorConfig config)
```
设置自定义视频前处理器。<br>
使用这个视频前处理器，你能够调用 [processVideoFrame](#IVideoProcessor-processvideoframe) 对 RTC SDK 采集得到的视频帧进行前处理，并将处理后的视频帧用于 RTC 音视频通信。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| processor | **IVideoProcessor** | 自定义视频处理器，详见 [IVideoProcessor](#ivideoprocessor)。如果传入 null，则不对 RTC SDK 采集得到的视频帧进行前处理。<br/>SDK 只持有 processor 的弱引用，你应保证其生命周期。 |
| config | **VideoPreprocessorConfig** | 自定义视频前处理器适用的设置，详见 [VideoPreprocessorConfig](Android-keytype.md#videopreprocessorconfig)。<br/>当前，`config` 中的 `required_pixel_format` 仅支持：`I420`、`TEXTURE_2D` 和 `UNKNOWN`：<br/>• 设置为 `UNKNOWN` 时，RTC SDK 给出供 processor 处理的视频帧格式即采集的格式。<br/>你可以通过 [getPixelFormat](Android-keytype.md#VideoFrame-getpixelformat) 获取实际采集的视频帧格式，支持的格式为：`kVideoPixelFormatI420`、 `kVideoPixelFormatTexture2D` 和 `kVideoPixelFormatTextureOES`<br/>• 设置为 `I420` 或 `TEXTURE_2D` 时，RTC SDK 会将采集得到的视频转变为对应的格式，供前处理使用。<br/>• 设置为其他值时，此方法调用失败。 |

**返回值**

+ 0：方法调用成功 
+ !0：方法调用失败 


**注意**
经前处理后，返回给 RTC SDK 的视频帧格式仅支持 `I420` 和 `TEXTURE_2D`。

<span id="RTCVideo-setvideodigitalzoomconfig"></span>
### setVideoDigitalZoomConfig
```java
public abstract void com.ss.bytertc.engine.RTCVideo.setVideoDigitalZoomConfig(
    ZoomConfigType type,
    float size)
```
> Available since 3.51

设置本地摄像头数码变焦参数，包括缩放倍数，移动步长。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| type | **ZoomConfigType** | 数码变焦参数类型，缩放系数或移动步长。参看 [ZoomConfigType](Android-keytype.md#zoomconfigtype)。必填。 |
| size | **float** | 缩放系数或移动步长，保留到小数点后三位。默认值为 0。必填。<br/>选择不同 `type` 时有不同的取值范围。当计算后的结果超过缩放和移动边界时，取临界值。<br/>• `ZOOM_FOCUS_OFFSET(0)`：缩放系数增量，范围为 [0, 7]。例如，设置为 0.5 时，如果调用 [setVideoDigitalZoomControl](#RTCVideo-setvideodigitalzoomcontrol) 选择 Zoom in，则缩放系数增加 0.5。缩放系数范围 [1，8]，默认为 `1`，原始大小。<br/>• `ZOOM_MOVE_OFFSET(1)`：移动百分比，范围为 [0, 0.5]，默认为 0，不移动。如果调用 [setVideoDigitalZoomControl](#RTCVideo-setvideodigitalzoomcontrol) 选择的是左右移动，则移动距离为 size x 原始视频宽度；如果选择的是上下移动，则移动距离为 size x 原始视频高度。例如，视频帧边长为 1080 px，设置为 0.5 时，实际移动距离为 0.5 x 1080 px = 540 px。 |


**注意**

+ 每次调用本接口只能设置一种参数。如果缩放系数和移动步长都需要设置，分别调用本接口传入相应参数。
+ 由于移动步长的默认值为 `0` ，在调用 [setVideoDigitalZoomControl](#RTCVideo-setvideodigitalzoomcontrol) 或 [startVideoDigitalZoomControl](#RTCVideo-startvideodigitalzoomcontrol) 进行数码变焦操作前，应先调用本接口。


<span id="RTCVideo-setvideodigitalzoomcontrol"></span>
### setVideoDigitalZoomControl
```java
public abstract void com.ss.bytertc.engine.RTCVideo.setVideoDigitalZoomControl(
    ZoomDirectionType direction)
```
> Available since 3.51

控制本地摄像头数码变焦，缩放或移动一次。设置对本地预览画面和发布到远端的视频都生效。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| direction | **ZoomDirectionType** | 数码变焦操作类型，参看 [ZoomDirectionType](Android-keytype.md#zoomdirectiontype)。 |


**注意**

+ 由于默认步长为 `0`，调用该方法前需通过 [setVideoDigitalZoomConfig](#RTCVideo-setvideodigitalzoomconfig) 设置参数。
+ 调用该方法进行移动前，应先使用本方法或 [startVideoDigitalZoomControl](#RTCVideo-startvideodigitalzoomcontrol) 进行放大，否则无法移动。
+ 当数码变焦操作超出范围时，将置为临界值。例如，移动到了图片边界、放大到了 8 倍、缩小到原图大小。
+ 如果你希望实现持续数码变焦操作，调用 [startVideoDigitalZoomControl](#RTCVideo-startvideodigitalzoomcontrol)。
+ 如果你需要对摄像头进行光学变焦控制，参看 [setCameraZoomRatio](#RTCVideo-setcamerazoomratio)。


<span id="RTCVideo-startvideodigitalzoomcontrol"></span>
### startVideoDigitalZoomControl
```java
public abstract void com.ss.bytertc.engine.RTCVideo.startVideoDigitalZoomControl(
    ZoomDirectionType direction)
```
> Available since 3.51

开启本地摄像头持续数码变焦，缩放或移动。设置对本地预览画面和发布到远端的视频都生效。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| direction | **ZoomDirectionType** | 数码变焦操作类型，参看 [ZoomDirectionType](Android-keytype.md#zoomdirectiontype)。 |


**注意**

+ 由于默认步长为 `0`，调用该方法前需通过 [setVideoDigitalZoomConfig](#RTCVideo-setvideodigitalzoomconfig) 设置参数。
+ 调用该方法进行移动前，应先使用本方法或 [setVideoDigitalZoomControl](#RTCVideo-setvideodigitalzoomcontrol) 进行放大，否则无法移动。
+ 当数码变焦操作超出范围时，将置为临界值并停止操作。例如，移动到了图片边界、放大到了 8 倍、缩小到原图大小。
+ 你也可以调用 [stopVideoDigitalZoomControl](#RTCVideo-stopvideodigitalzoomcontrol) 手动停止控制。
+ 如果你希望实现单次数码变焦操作，调用 [setVideoDigitalZoomControl](#RTCVideo-setvideodigitalzoomcontrol)。
+ 如果你需要对摄像头进行光学变焦控制，参看 [setCameraZoomRatio](#RTCVideo-setcamerazoomratio)。


<span id="RTCVideo-stopvideodigitalzoomcontrol"></span>
### stopVideoDigitalZoomControl
```java
public abstract void com.ss.bytertc.engine.RTCVideo.stopVideoDigitalZoomControl()
```
> Available since 3.51

停止本地摄像头持续数码变焦。


**注意**
关于开始数码变焦，参看 [startVideoDigitalZoomControl](#RTCVideo-startvideodigitalzoomcontrol)。

<span id="RTCVideo-registerlocalencodedvideoframeobserver"></span>
### registerLocalEncodedVideoFrameObserver
```java
public abstract void com.ss.bytertc.engine.RTCVideo.registerLocalEncodedVideoFrameObserver(
    ILocalEncodedVideoFrameObserver observer)
```
注册本地视频帧监测器。  <br>
无论使用内部采集还是自定义采集，调用该方法后，SDK 每监测到一帧本地视频帧时，都会将视频帧信息通过 [onLocalEncodedVideoFrame](Android-callback.md#ILocalEncodedVideoFrameObserver-onlocalencodedvideoframe) 回调给用户。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| observer | **ILocalEncodedVideoFrameObserver** | 本地频帧监测器，参看 [ILocalEncodedVideoFrameObserver](Android-callback.md#ilocalencodedvideoframeobserver) 。将参数设置为 null 则取消注册。 |


**注意**
该方法可在进房前后的任意时间调用，在进房前调用可保证尽可能早地监测视频帧并触发回调

<span id="RTCVideo-registerremoteencodedvideoframeobserver"></span>
### registerRemoteEncodedVideoFrameObserver
```java
public abstract void com.ss.bytertc.engine.RTCVideo.registerRemoteEncodedVideoFrameObserver(
    IRemoteEncodedVideoFrameObserver observer)
```
注册远端编码后视频数据回調。  <br>
完成注册后，当 SDK 监测到远端编码后视频帧时，会触发 [onRemoteEncodedVideoFrame](Android-callback.md#IRemoteEncodedVideoFrameObserver-onremoteencodedvideoframe) 回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| observer | **IRemoteEncodedVideoFrameObserver** | 远端编码后视频数据监测器，参看 [IRemoteEncodedVideoFrameObserver](Android-callback.md#iremoteencodedvideoframeobserver) |


**注意**

+ 更多自定义解码功能说明参看 [自定义视频编解码](https://www.volcengine.com/docs/6348/82921#%E8%87%AA%E5%AE%9A%E4%B9%89%E8%A7%86%E9%A2%91%E8%A7%A3%E7%A0%81)。
+ 该方法适用于手动订阅，并且进房前后均可调用，建议在进房前调用。 
+ 引擎销毁前需取消注册，调用该方法将参数设置为 "null" 即可。


<span id="RTCVideo-setvideosourcetype"></span>
### setVideoSourceType
```java
public abstract void com.ss.bytertc.engine.RTCVideo.setVideoSourceType(
    StreamIndex index,
    VideoSourceType type)
```
设置向 SDK 输入的视频源，包括屏幕流
默认使用内部采集。内部采集指：使用 RTC SDK 内置的视频采集机制进行视频采集。 <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| index | **StreamIndex** | 视频流的属性，参看 [StreamIndex](Android-keytype.md#streamindex-2) |
| type | **VideoSourceType** | 视频输入源类型，参看 [VideoSourceType](Android-keytype.md#videosourcetype) |


**注意**

+ 该方法进房前后均可调用。  
+ 当你已调用 [startVideoCapture](#RTCVideo-startvideocapture) 开启内部采集后，再调用此方法切换至自定义采集时，SDK 会自动关闭内部采集。  
+ 当你调用此方法开启自定义采集后，想要切换至内部采集，你必须先调用此方法关闭自定义采集，然后调用 [startVideoCapture](#RTCVideo-startvideocapture) 手动开启内部采集。
+ 当你需要向 SDK 推送自定义编码后的视频帧，你需调用该方法将视频源切换至自定义编码视频源。


<span id="RTCVideo-pushexternalvideoframe"></span>
### pushExternalVideoFrame
```java
public abstract int com.ss.bytertc.engine.RTCVideo.pushExternalVideoFrame(
    VideoFrame frame)
```
推送外部视频帧。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| frame | **VideoFrame** | 视频帧的数据信息 |

**返回值**
方法调用结果：

+ 0：成功；
+ <0：失败。具体失败原因参看 [ReturnStatus](Android-keytype.md#returnstatus)。


**注意**

+ 该方法主动将视频帧数据用 [VideoFrame](Android-keytype.md#videoframe) 类封装后传递给 SDK。  
+ 请确保在你调用本方法前已调用 [setVideoSourceType](#RTCVideo-setvideosourcetype) 设置为自定义视频采集。 
+ 当使用纹理数据时， 确保 [createRTCVideo](#RTCVideo-creatertcvideo) 中的 `eglContext`与 `frame` 中的 `eglContext` 为 `sharedContext` 或者相同，否则会无法编码。
+ 支持的格式：Raw： I420, NV12, RGBA；纹理： Texture2D, TextureOES。


<span id="RTCVideo-startlivetranscoding"></span>
### startLiveTranscoding
```java
public abstract void com.ss.bytertc.engine.RTCVideo.startLiveTranscoding(
    String taskId,
    LiveTranscoding liveTranscode,
    ILiveTranscodingObserver observer)
```
> Deprecated  since 3.52, will be deleted in 3.58, use [startPushMixedStreamToCDN](#RTCVideo-startpushmixedstreamtocdn) instead.

新增转推直播任务，并设置合流的图片、视频视图布局和音频属性。  <br>
同一个任务中转推多路直播流时，SDK 会先将多路流合成一路流，然后再进行转推。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| taskId | **String** | 转推直播任务 ID，长度不超过 126 字节。<br/>你可以在同一房间内发起多个转推直播任务，并用不同的任务 ID 加以区分。当你需要发起多个转推直播任务时，应使用多个 ID；当你仅需发起一个转推直播任务时，建议使用空字符串。 |
| liveTranscode | **LiveTranscoding** | 转推直播配置参数。详见 [LiveTranscoding](Android-keytype.md#livetranscoding)。 |
| observer | **ILiveTranscodingObserver** | 端云一体转推直播观察者。详见 [ILiveTranscodingObserver](Android-callback.md#ilivetranscodingobserver)。  <br/>通过注册 observer 接收转推直播相关的回调。 |


**注意**

+ 在调用该接口前，你需要在[控制台](https://console.volcengine.com/rtc/workplaceRTC)开启转推直播功能。
+ 调用该方法后，关于启动结果和推流过程中的错误，会收到 [onStreamMixingEvent](Android-callback.md#ILiveTranscodingObserver-onstreammixingevent) 回调。
+ 调用 [stopLiveTranscoding](#RTCVideo-stoplivetranscoding) 停止转推直播。


<span id="RTCVideo-stoplivetranscoding"></span>
### stopLiveTranscoding
```java
public abstract void com.ss.bytertc.engine.RTCVideo.stopLiveTranscoding(
    String taskId)
```
> Deprecated  since 3.52, will be deleted in 3.58, use [stopPushStreamToCDN](#RTCVideo-stoppushstreamtocdn) instead.

停止转推直播，会收到 [onStreamMixingEvent](Android-callback.md#ILiveTranscodingObserver-onstreammixingevent) 回调。<br>
关于启动转推直播，参看 [startLiveTranscoding](#RTCVideo-startlivetranscoding)。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| taskId | **String** | 转推直播任务 ID。可以指定想要停止的转推直播任务。 |


<span id="RTCVideo-updatelivetranscoding"></span>
### updateLiveTranscoding
```java
public abstract void com.ss.bytertc.engine.RTCVideo.updateLiveTranscoding(
    String taskId,
    LiveTranscoding transcoding)
```
> Deprecated  since 3.52, will be deleted in 3.58, use [updatePushMixedStreamToCDN](#RTCVideo-updatepushmixedstreamtocdn) instead.

更新转推直播参数，会收到 [onStreamMixingEvent](Android-callback.md#ILiveTranscodingObserver-onstreammixingevent) 回调。
使用 [startLiveTranscoding](#RTCVideo-startlivetranscoding) 启用转推直播功能后，使用此方法更新功能配置参数。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| taskId | **String** | 转推直播任务 ID。指定想要更新参数设置的转推直播任务。 |
| transcoding | **LiveTranscoding** | 转推直播配置参数，参看 [LiveTranscoding](Android-keytype.md#livetranscoding)。除特殊说明外，均支持过程中更新。<br/>调用时，结构体中没有传入值的属性，会被更新为默认值。 |


<span id="RTCVideo-startpushmixedstreamtocdn"></span>
### startPushMixedStreamToCDN
```java
public abstract int com.ss.bytertc.engine.RTCVideo.startPushMixedStreamToCDN(
    String taskId,
    MixedStreamConfig mixedConfig,
    IMixedStreamObserver observer)
```
> Available since 3.52

新增合流转推直播任务，并设置合流的图片、视频视图布局和音频属性。  <br>
同一个任务中转推多路直播流时，SDK 会先将多路流合成一路流，然后再进行转推。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| taskId | **String** | 转推直播任务 ID，长度不超过 126 字节。<br/>你可以在同一房间内发起多个转推直播任务，并用不同的任务 ID 加以区分。当你需要发起多个转推直播任务时，应使用多个 ID；当你仅需发起一个转推直播任务时，建议使用空字符串。 |
| mixedConfig | **MixedStreamConfig** | 转推直播配置参数。详见 [MixedStreamConfig](Android-keytype.md#mixedstreamconfig)。 |
| observer | **IMixedStreamObserver** | 端云一体转推直播观察者。详见 [IMixedStreamObserver](Android-callback.md#imixedstreamobserver)。  <br/>通过注册 observer 接收转推直播相关的回调。 |

**返回值**
方法调用结果： 

+ 0：成功；
+ !0：失败。


**注意**

+ 在调用该接口前，你需要在[控制台](https://console.volcengine.com/rtc/workplaceRTC)开启转推直播功能。
+ 调用该方法后，关于启动结果和推流过程中的错误，会收到 [onMixingEvent](Android-callback.md#IMixedStreamObserver-onmixingevent) 回调。
+ 如果你在[控制台](https://console.volcengine.com/rtc/cloudRTC?tab=callback)配置了转推直播的服务端回调，调用本接口会收到 [TranscodeStarted](https://www.volcengine.com/docs/6348/75125#transcodestarted)。重复调用该接口时，第二次调用会同时触发 [TranscodeStarted](https://www.volcengine.com/docs/6348/75125#transcodestarted) 和 [TranscodeUpdated](https://www.volcengine.com/docs/6348/75125#transcodeupdated)。
+ 调用 [stopPushStreamToCDN](#RTCVideo-stoppushstreamtocdn) 停止转推直播。


<span id="RTCVideo-updatepushmixedstreamtocdn"></span>
### updatePushMixedStreamToCDN
```java
public abstract int com.ss.bytertc.engine.RTCVideo.updatePushMixedStreamToCDN(
    String taskId,
    MixedStreamConfig mixedConfig)
```
> Available since 3.52

更新合流转推直播参数，会收到 [onMixingEvent](Android-callback.md#IMixedStreamObserver-onmixingevent) 回调。  <br>
使用 [startPushMixedStreamToCDN](#RTCVideo-startpushmixedstreamtocdn) 启用转推直播功能后，使用此方法更新功能配置参数。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| taskId | **String** | 转推直播任务 ID。指定想要更新参数设置的转推直播任务。 |
| mixedConfig | **MixedStreamConfig** | 转推直播配置参数，详见 [MixedStreamConfig](Android-keytype.md#mixedstreamconfig)。除特殊说明外，均支持过程中更新。<br/>调用时，结构体中没有传入值的属性，会被更新为默认值。 |

**返回值**
方法调用结果： 

+ 0：成功；
+ !0：失败。


<span id="RTCVideo-startpushsinglestreamtocdn"></span>
### startPushSingleStreamToCDN
```java
public abstract void com.ss.bytertc.engine.RTCVideo.startPushSingleStreamToCDN(
    String taskId,
    PushSingleStreamParam param,
    IPushSingleStreamToCDNObserver observer)
```
新增单流转推直播任务。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| taskId | **String** | 任务 ID。<br/>你可以发起多个转推直播任务，并用不同的任务 ID 加以区分。当你需要发起多个转推直播任务时，应使用多个 ID；当你仅需发起一个转推直播任务时，建议使用空字符串。 |
| param | **PushSingleStreamParam** | 转推直播配置参数。详见 [PushSingleStreamParam](Android-keytype.md#pushsinglestreamparam)。 |
| observer | **IPushSingleStreamToCDNObserver** | 单流转推直播观察者。详见 [IPushSingleStreamToCDNObserver](Android-callback.md#ipushsinglestreamtocdnobserver)。  <br/>通过注册 observer 接收单流转推直播相关的回调。 |


**注意**

+ 在调用该接口前，你需要在[控制台](https://console.volcengine.com/rtc/workplaceRTC)开启转推直播功能。
+ 调用该方法后，关于启动结果和推流过程中的错误，会收到 [onStreamPushEvent](Android-callback.md#IPushSingleStreamToCDNObserver-onstreampushevent) 回调。
+ 调用 [stopPushStreamToCDN](#RTCVideo-stoppushstreamtocdn) 停止任务。
+ 由于本功能不进行编解码，所以推到 RTMP 的视频流会根据推流端的分辨率、编码方式、关闭摄像头等变化而变化。


<span id="RTCVideo-stoppushstreamtocdn"></span>
### stopPushStreamToCDN
```java
public abstract void com.ss.bytertc.engine.RTCVideo.stopPushStreamToCDN(
    String taskId)
```
停止转推直播。<br>
该方法可用于停止单流转推直播或停止合流转推直播，通过 taskId 区分需要停止的任务。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| taskId | **String** | 任务 ID。可以指定想要停止的单流转推直播或合流转推直播任务。 |


**注意**

+ 关于启动单流转推直播，参看 [startPushSingleStreamToCDN](#RTCVideo-startpushsinglestreamtocdn)。
+ 关于启动合流转推直播，参看 [startPushMixedStreamToCDN](#RTCVideo-startpushmixedstreamtocdn)。


<span id="RTCVideo-setvideocaptureconfig"></span>
### setVideoCaptureConfig
```java
public abstract int com.ss.bytertc.engine.RTCVideo.setVideoCaptureConfig(
    VideoCaptureConfig videoCaptureConfig)
```
设置 RTC SDK 内部采集时的视频采集参数。<br>
如果你的项目使用了 SDK 内部采集模块，可以通过本接口指定视频采集参数包括模式、分辨率、帧率。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| videoCaptureConfig | **VideoCaptureConfig** | 视频采集参数。参看: [VideoCaptureConfig](Android-keytype.md#videocaptureconfig)。 |

**返回值**

+ 0: 成功  
+ < 0: 失败  


**注意**

+ 本接口在引擎创建后即可调用，建议在调用 [startVideoCapture](#RTCVideo-startvideocapture) 前调用本接口。
+ 建议同一设备上的不同引擎使用相同的视频采集参数。
+ 如果调用本接口前使用内部模块开始视频采集，采集参数默认为 Auto 模式。


<span id="RTCVideo-enablesimulcastmode"></span>
### enableSimulcastMode
```java
public abstract void com.ss.bytertc.engine.RTCVideo.enableSimulcastMode(
    boolean enabled)
```
该方法设置视频流发布端是否开启发布多路编码参数不同的视频流的模式。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| enabled | **boolean** | 是否开启推送多路视频流模式： <br/>• true：开启 <br/>• false：关闭（默认） |


**注意**

+ 你应在进房前或进房后但未发布流时，调用此方法。  
+ 开启推送多路流后，不能动态关闭，也不能更新多路流的路数和编码参数。 
+ 开启推送多路视频流模式后，你可以调用 [setVideoEncoderConfig](#RTCVideo-setvideoencoderconfig-1) 为多路视频流分别设置编码参数。 
+ 该功能关闭时，或该功能开启但未设置多路流参数时，默认只发一路视频流，该流的编码参数为：分辨率 640px × 360px，帧率 15fps。


<span id="RTCVideo-setvideoencoderconfig"></span>
### setVideoEncoderConfig
```java
public abstract int com.ss.bytertc.engine.RTCVideo.setVideoEncoderConfig(
    List<VideoStreamDescription> videoStreamDescriptions,
    VideoEncoderConfiguration.OrientationMode orientationMode)
```
> Deprecated  since 3.37 and will be deleted in 3.51, use [setVideoEncoderConfig](#RTCVideo-setvideoencoderconfig-2) instead.

设置推送多路流时的各路视频参数，以及视频旋转角度。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| videoStreamDescriptions | **List<VideoStreamDescription>** | 要推送的多路视频流参数，参看 [VideoStreamDescription](Android-keytype.md#videostreamdescription) |
| orientationMode | **VideoEncoderConfiguration.OrientationMode** | 视频编码的方向模式，参看 [OrientationMode](Android-keytype.md#orientationmode) |

**返回值**

+ 0: 成功；  
+ < 0: 失败；  


**注意**

+ orientationMode 这个参数没有实现
+ 该接口已废弃，请使用同名新接口代替；若仍需使用该旧接口，请注意无需先调用 `enableSimulcastMode` 开启推送多路流模式。


<span id="RTCVideo-setvideoencoderconfig"></span>
### setVideoEncoderConfig
```java
public abstract int com.ss.bytertc.engine.RTCVideo.setVideoEncoderConfig(
    StreamIndex streamIndex,
    List<VideoStreamDescription> videoStreamDescriptions)
```
> Deprecated  since 3.37 and will be deleted in 3.51, use [setVideoEncoderConfig](#RTCVideo-setvideoencoderconfig-2) instead.

设置推送多路流时的各路视频参数，以及视频旋转角度。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamIndex | **StreamIndex** | 视频流属性。采集的视频流/屏幕视频流，参看 [StreamIndex](Android-keytype.md#streamindex-2) |
| videoStreamDescriptions | **List<VideoStreamDescription>** | 要推送的多路视频流参数，参看 [VideoStreamDescription](Android-keytype.md#videostreamdescription) |

**返回值**

+ 0: 成功；  
+ < 0: 失败；  


**注意**
该接口已经废弃，请使用同名新接口代替；若仍需使用该旧接口，请注意无需先调用 `enableSimulcastMode` 开启推送多路流模式。

<span id="RTCVideo-setvideoencoderconfig"></span>
### setVideoEncoderConfig
```java
public abstract int com.ss.bytertc.engine.RTCVideo.setVideoEncoderConfig(
    VideoEncoderConfig max_solution)
```
<span id="RTCVideo-setvideoencoderconfig-1"></span>视频发布端设置期望发布的最大分辨率视频流参数，包括分辨率、帧率、码率、网络不佳时的回退策略等。  <br>
该接口支持设置一路视频流参数，设置多路参数请使用重载 API：[setVideoEncoderConfig](#RTCVideo-setvideoencoderconfig-2)

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| max_solution | **VideoEncoderConfig** | 期望发布的最大分辨率视频流参数。参看 [VideoEncoderConfig](Android-keytype.md#videoencoderconfig)。 |

**返回值**
方法调用结果： 

+ 0：成功  
+ !0：失败  


**注意**

+ 你可以同时使用 [enableSimulcastMode](#RTCVideo-enablesimulcastmode) 方法来发布多路分辨率不同的流。具体而言，若期望发布多路不同分辨率的流，你需要在发布流之前调用本方法以及 [enableSimulcastMode](#RTCVideo-enablesimulcastmode) 方法开启多路流模式，SDK 会根据订阅端的设置智能调整发布的流数（最多发布 4 条）以及各路流的参数。其中，调用本方法设置的分辨率为各路流中的最大分辨率。具体规则参看[推送多路流](70139)文档。
+ 调用该方法前，SDK 默认仅发布一条分辨率为 640px × 360px，帧率为 15fps 的视频流。  
+ 使用自定义采集时，必须调用该方法设置编码参数，以保证远端收到画面的完整性。
+ 该方法适用于摄像头采集的视频流，设置屏幕共享视频流参数参看 [setScreenVideoEncoderConfig](#RTCVideo-setscreenvideoencoderconfig)。


<span id="RTCVideo-setvideoencoderconfig"></span>
### setVideoEncoderConfig
```java
public abstract int com.ss.bytertc.engine.RTCVideo.setVideoEncoderConfig(
    VideoEncoderConfig[] channel_solutions)
```
<span id="RTCVideo-setvideoencoderconfig-2"></span>视频发布端设置推送多路流时各路流的参数，包括分辨率、帧率、码率、网络不佳时的回退策略等。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| channel_solutions | **VideoEncoderConfig[]** | 要推送的多路视频流的参数，最多支持设置 3 路参数，超过 3 路时默认取前 3 路的值。  <br/>当设置了多路参数时，分辨率和帧率必须是从大到小排列。需注意，所设置的分辨率是各路流的最大分辨率。参看 [VideoEncoderConfig](Android-keytype.md#videoencoderconfig)。 |

**返回值**
方法调用结果： 

+ 0：成功  
+ !0：失败  


**注意**

+ 该方法设置的多路参数是否均生效，取决于是否同时调用了 [enableSimulcastMode](#RTCVideo-enablesimulcastmode) 开启发布多路参数不同的视频流模式。若未开启推送多路流模式，但调用本方法设置了多个分辨率，SDK 则默认发布设置的第一条流，多个分辨率的设置会在开启推送多路流模式之后生效。  
+ 若期望推送多路不同分辨率的流，你需要在发布流之前调用本方法以及[enableSimulcastMode](#RTCVideo-enablesimulcastmode) 方法。
+ 开启推送多路流后，不能动态关闭，也不能更新多路流的路数和编码参数。  
+ 调用该方法设置多路视频流参数前，SDK 默认仅发布一条分辨率为 640px × 360px，帧率为 15fps 的视频流。  
+ 调用该方法设置分辨率不同的多条流后，SDK 会根据订阅端设置的期望订阅参数自动匹配发送的流，具体规则参看[推送多路流](https://www.volcengine.com/docs/6348/70139)文档。  
+ 该方法适用于摄像头采集的视频流，设置屏幕共享视频流参数参看 [setScreenVideoEncoderConfig](#RTCVideo-setscreenvideoencoderconfig)。


<span id="RTCVideo-setscreenvideoencoderconfig"></span>
### setScreenVideoEncoderConfig
```java
public abstract int com.ss.bytertc.engine.RTCVideo.setScreenVideoEncoderConfig(
    ScreenVideoEncoderConfig screen_solution)
```
为发布的屏幕共享视频流设置期望的编码参数，包括分辨率、帧率、码率、网络不佳时的回退策略等。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| screen_solution | **ScreenVideoEncoderConfig** | 屏幕共享视频流参数。参看 [ScreenVideoEncoderConfig](Android-keytype.md#screenvideoencoderconfig)。 |

**返回值**

+ 0：成功。  
+ !0：失败。


**注意**
建议在采集视频前设置编码参数。若采集前未设置编码参数，则使用默认编码参数: 分辨率 1920px × 1080px，帧率 15fps。

<span id="RTCVideo-setaudiosourcetype"></span>
### setAudioSourceType
```java
public abstract int com.ss.bytertc.engine.RTCVideo.setAudioSourceType (
    AudioSourceType type)
```
切换音频采集方式

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| type | **AudioSourceType** | 音频数据源，详见 [AudioSourceType](Android-keytype.md#audiosourcetype)。<br/>默认使用内部音频采集。音频采集和渲染方式无需对应。 |

**返回值**
方法调用结果：  

+ \>0: 切换成功。
+ -1：切换失败。


**注意**

+ 进房前后调用此方法均有效。
+ 如果你调用此方法由内部采集切换至自定义采集，SDK 会自动关闭内部采集。然后，调用 [pushExternalAudioFrame](#RTCVideo-pushexternalaudioframe) 推送自定义采集的音频数据到 RTC SDK 用于传输。 
+ 如果你调用此方法由自定义采集切换至内部采集，你必须再调用 [startAudioCapture](#RTCVideo-startaudiocapture) 手动开启内部采集。 


<span id="RTCVideo-setaudiorendertype"></span>
### setAudioRenderType
```java
public abstract int com.ss.bytertc.engine.RTCVideo.setAudioRenderType (
    AudioRenderType type)
```
切换音频渲染方式

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| type | **AudioRenderType** | 音频输出类型，详见 [AudioRenderType](Android-keytype.md#audiorendertype) <br/>默认使用内部音频渲染。音频采集和渲染方式无需对应。 |

**返回值**
方法调用结果：  

+ \>0: 切换成功。
+ -1：切换失败。


**注意**

+ 进房前后调用此方法均有效。
+ 如果你调用此方法切换至自定义渲染，调用 [pullExternalAudioFrame](#RTCVideo-pullexternalaudioframe) 获取音频数据。 


<span id="RTCVideo-pushexternalaudioframe"></span>
### pushExternalAudioFrame
```java
public abstract int com.ss.bytertc.engine.RTCVideo.pushExternalAudioFrame(
    AudioFrame audioFrame)
```
推送自定义采集的音频数据到 RTC SDK。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioFrame | **AudioFrame** | 音频数据帧，详见 [AudioFrame](Android-keytype.md#audioframe) |

**返回值**
方法调用结果  

+ 0: 设置成功  
+ < 0: 设置失败  


**注意**

+ 推送自定义采集的音频数据前，必须先调用 [setAudioSourceType](#RTCVideo-setaudiosourcetype) 开启自定义采集。
+ 你必须每隔 10 毫秒推送一次外部采集的音频数据。单次推送的 samples (音频采样点个数）应该为 audioFrame.sampleRate / 100。比如设置采样率为 48000 时， 每次应该推送 480 个采样点。  
+ 音频采样格式必须为 S16。音频缓冲区内的数据格式必须为 PCM，其容量大小应该为 audioFrame.samples × audioFrame.channel × 2。


<span id="RTCVideo-pullexternalaudioframe"></span>
### pullExternalAudioFrame
```java
public abstract int com.ss.bytertc.engine.RTCVideo.pullExternalAudioFrame(
    AudioFrame audioFrame)
```
拉取远端音频数据。<br>
可用于自定义音频渲染。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioFrame | **AudioFrame** | 音频数据帧，详见 [AudioFrame](Android-keytype.md#audioframe) |

**返回值**
方法调用结果  

+ 0: 设置成功  
+ < 0: 设置失败  


**注意**

+ 拉取外部音频数据前，必须先调用 [setAudioRenderType](#RTCVideo-setaudiorendertype) 启用自定义音频渲染。
+ 由于 RTC SDK 的帧长为 10 毫秒，你应当每隔 10 毫秒拉取一次音频数据。确保音频采样点数（sample）x 拉取频率等于 audioFrame 的采样率 （sampleRate）。如设置采样率为 48000 时，每 10 毫秒调用本接口拉取数据，每次应拉取 480 个采样点。  
+ 音频采样格式为 S16。音频缓冲区内的数据格式为 PCM 数据，其容量大小为 audioFrame.samples × audioFrame.channel × 2。  


<span id="RTCVideo-pushscreenvideoframe"></span>
### pushScreenVideoFrame
```java
public abstract int com.ss.bytertc.engine.RTCVideo.pushScreenVideoFrame(
    VideoFrame videoFrame)
```
推送屏幕视频帧

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| videoFrame | **VideoFrame** | 视频帧 [VideoFrame](Android-keytype.md#videoframe) |

**返回值**
方法调用结果：

+ 0：成功；
+ <0：失败。具体失败原因参看 [ReturnStatus](Android-keytype.md#returnstatus)。


<span id="RTCVideo-setondestroycompletedcallback"></span>
### setOnDestroyCompletedCallback
```java
public abstract void com.ss.bytertc.engine.RTCVideo.setOnDestroyCompletedCallback(
    Runnable callback)
```
> Deprecated  since 3.45 and will be deleted in 3.51.

设置引擎销毁后通知 App 的回调函数。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| callback | **Runnable** | App 接收引擎销毁的回调函数。 |


<span id="RTCVideo-setremoteaudioplaybackvolume"></span>
### setRemoteAudioPlaybackVolume
```java
public abstract int com.ss.bytertc.engine.RTCVideo.setRemoteAudioPlaybackVolume(
    String roomId,
    String uid,
    int volume)
```
调节来自指定远端用户的音频播放音量。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| roomId | **String** | 远端用户所属的房间 ID |
| uid | **String** | 音频来源的远端用户 ID |
| volume | **int** | 音频播放音量值和原始音量的比值，范围是 [0, 400]，单位为 %，自带溢出保护。  <br/>只改变音频数据的音量信息，不涉及本端硬件的音量调节。<br/>为保证更好的通话质量，建议将 volume 值设为 [0,100]。  <br/>• 0: 静音  <br/>• 100: 原始音量，默认值  <br/>• 400: 最大可为原始音量的 4 倍(自带溢出保护) |

**返回值**
方法调用结果：

+ 0：成功；
+ <0：失败。具体失败原因参看 [ReturnStatus](Android-keytype.md#returnstatus)。


**注意**
假设某远端用户 A 始终在被调节的目标用户范围内，+ 当该方法与 [setRemoteRoomAudioPlaybackVolume](#RTCRoom-setremoteroomaudioplaybackvolume) 共同使用时，本地收听用户 A 的音量为后调用的方法设置的音量；

+ 当该方法与 [setPlaybackVolume](#RTCVideo-setplaybackvolume) 方法共同使用时，本地收听用户 A 的音量将为两次设置的音量效果的叠加。


<span id="RTCVideo-setaudioalignmentproperty"></span>
### setAudioAlignmentProperty
```java
public abstract void com.ss.bytertc.engine.RTCVideo.setAudioAlignmentProperty(
    RemoteStreamKey streamKey,
    AudioAlignmentMode mode)
```
在听众端，设置订阅的所有远端音频流精准对齐后播放。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamKey | **RemoteStreamKey** | 作为对齐基准的远端音频流。参看 [RemoteStreamKey](Android-keytype#remotestreamkey)。<br/>一般选择主唱的音频流。<br/>你必须在收到 [onUserPublishStream](Android-callback.md#IRTCRoomEventHandler-onuserpublishstream), 确认此音频流已发布后，调用此 API。 |
| mode | **AudioAlignmentMode** | 是否对齐，默认不对齐。参看 [AudioAlignmentMode](Android-keytype.md#audioalignmentmode)。 |


**注意**

+ 你必须在实时合唱场景下使用此功能。在加入房间时，所有人应设置 [ChannelProfile](Android-keytype.md#channelprofile) 为 `CHANNEL_PROFILE_CHORUS`。
+ 订阅的所有远端流必须通过 [startAudioMixing](#IAudioMixingManager-startaudiomixing) 开启了背景音乐混音，并将 [AudioMixingConfig](Android-keytype.md#audiomixingconfig) 中的 `syncProgressToRecordFrame` 设置为 `true`。
+ 如果订阅的某个音频流延迟过大，可能无法实现精准对齐。
+ 合唱的参与者不应调用此 API，因为调用此 API 会增加延迟。如果希望从听众变为合唱参与者，应关闭对齐功能。


<span id="RTCVideo-creatertcroom"></span>
### createRTCRoom
```java
public abstract RTCRoom com.ss.bytertc.engine.RTCVideo.createRTCRoom(
    String roomId)
```
创建房间实例。
调用此方法仅返回一个房间实例，你仍需调用 [joinRoom](#RTCRoom-joinroom) 才能真正地创建/加入房间。
多次调用此方法以创建多个 [RTCRoom](#rtcroom) 实例。分别调用各 RTCRoom 实例中的 [joinRoom](#RTCRoom-joinroom) 方法，同时加入多个房间。
多房间模式下，用户可以同时订阅各房间的音视频流。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| roomId | **String** | 标识通话房间的房间 ID。该字符串符合正则表达式：`[a-zA-Z0-9_@\-\.]{1,128}`。 |

**返回值**
创建的 [RTCRoom](#rtcroom) 房间实例。


**注意**

+ 如果需要加入的房间已存在，你仍需先调用本方法来获取 RTCRoom 实例，再调用 [joinRoom](#RTCRoom-joinroom) 加入房间。
+ 请勿使用同样的 roomId 创建多个房间，否则后创建的房间实例会替换先创建的房间实例。
+ 如果你需要在多个房间发布音视频流，无须创建多房间，直接调用 [startForwardStreamToRooms](#RTCRoom-startforwardstreamtorooms) 开始跨房间转发媒体流。


<span id="RTCVideo-setpublishfallbackoption"></span>
### setPublishFallbackOption
```java
public abstract void com.ss.bytertc.engine.RTCVideo.setPublishFallbackOption(
    PublishFallbackOption option)
```
设置发布的音视频流的回退选项。  <br>
你可以调用该接口设置网络不佳或设备性能不足时从大流起进行降级处理，以保证通话质量。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| option | **PublishFallbackOption** | 本地发布的音视频流回退选项，参看 [PublishFallbackOption](Android-keytype.md#publishfallbackoption)。 |


**注意**

+ 该方法仅在调用 [enableSimulcastMode](#RTCVideo-enablesimulcastmode) 开启了发送多路视频流的情况下生效。  
+ 该方法必须在进房前设置，进房后设置或更改设置无效。  
+ 设置回退后，本地发布的音视频流发生回退或从回退中恢复时，远端会收到 [onSimulcastSubscribeFallback](Android-callback.md#IRTCVideoEventHandler-onsimulcastsubscribefallback) 回调通知。  
+ 你可以调用客户端 API 或者在服务端下发策略设置回退。当使用服务端下发配置实现时，下发配置优先级高于在客户端使用 API 设定的配置。


<span id="RTCVideo-setsubscribefallbackoption"></span>
### setSubscribeFallbackOption
```java
public abstract void com.ss.bytertc.engine.RTCVideo.setSubscribeFallbackOption(
    SubscribeFallbackOptions option)
```
设置订阅的音视频流的回退选项。 <br>
你可调用该接口设置网络不佳或设备性能不足时允许订阅流进行降级或只订阅音频流，以保证通话流畅。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| option | **SubscribeFallbackOptions** | 订阅的音视频流回退选项，参看 [SubscribeFallbackOptions](Android-keytype.md#subscribefallbackoptions)。 |


**注意**

+ 你必须在进房前设置，进房后设置或更改设置无效。  
+ 设置回退选项后，订阅的音视频流发生回退或从回退中恢复时，会收到 [onSimulcastSubscribeFallback](Android-callback.md#IRTCVideoEventHandler-onsimulcastsubscribefallback) 和 [onRemoteVideoSizeChanged](Android-callback.md#IRTCVideoEventHandler-onremotevideosizechanged) 回调通知。  
+ 你可以调用 API 或者在服务端下发策略设置回退。当使用服务端下发配置实现时，下发配置优先级高于在客户端使用 API 设定的配置。


<span id="RTCVideo-setremoteuserpriority"></span>
### setRemoteUserPriority
```java
public abstract int com.ss.bytertc.engine.RTCVideo.setRemoteUserPriority(
    String roomid,
    String uid,
    RemoteUserPriority priority)
```
设置用户优先级。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| roomid | **String** | 房间 ID |
| uid | **String** | 远端用户的 ID 。 |
| priority | **RemoteUserPriority** | 远端用户的优先级，详见枚举类型 [RemoteUserPriority](Android-keytype.md#remoteuserpriority) 。 |

**返回值**

+ 0： 成功。  
+ < 0： 失败。


**注意**

+ 该方法与 SubscribeFallbackOption[setSubscribeFallbackOption](#setsubscribefallbackoption) 搭配使用。  
+ 如果开启了订阅流回退选项，弱网或性能不足时会优先保证收到的高优先级用户的流的质量。  
+ 该方法在进房前后都可以使用，可以修改远端用户的优先级。


<span id="RTCVideo-sendseimessage"></span>
### sendSEIMessage
```java
public abstract int com.ss.bytertc.engine.RTCVideo.sendSEIMessage(
    StreamIndex streamIndex,
    byte[] message,
    int repeatCount)
```
> Deprecated  since 3.50 and will be deleted in 3.55, use [sendSEIMessage](#RTCVideo-sendseimessage-2) instead.

<span id="RTCVideo-sendseimessage-1"></span>通过视频帧发送 SEI 数据。
在视频通话场景下，SEI 数据会随视频帧发送；在语音通话场景下，SDK 会自动生成一路 16px × 16px 的黑帧视频流用来发送 SEI 数据。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamIndex | **StreamIndex** | 指定携带 SEI 数据的媒体流类型，参看 [StreamIndex](Android-keytype.md#streamindex-2)。  <br/>语音通话场景下，该值需设为 `STREAM_INDEX_MAIN`，否则 SEI 数据会被丢弃从而无法送达远端。 |
| message | **byte[]** | SEI 消息。长度不超过 4KB。 |
| repeatCount | **int** | 消息发送重复次数。取值范围是 [0, 30]。<br/>调用此接口后，SEI 数据会添加到从当前视频帧开始的连续 `repeatCount+1` 个视频帧中。 |

**返回值**

+ \>=0: 将被添加到视频帧中的 SEI 的数量  
+ <0: 发送失败


**注意**

+ 语音通话场景中，仅支持在内部采集模式下调用该接口发送 SEI 数据，且调用频率需为 15/repeat_count FPS。  
+ 视频帧仅携带前后 2s 内收到的 SEI 数据；语音通话场景下，若调用此接口后 1min 内未有 SEI 数据发送，则 SDK 会自动取消发布视频黑帧。  
+ 消息发送成功后，远端会收到 [onSEIMessageReceived](Android-callback.md#IRTCVideoEventHandler-onseimessagereceived) 回调。  
+ 语音通话切换至视频通话时，会停止使用黑帧发送 SEI 数据，自动转为用采集到的正常视频帧发送 SEI 数据。


<span id="RTCVideo-sendseimessage"></span>
### sendSEIMessage
```java
public abstract int com.ss.bytertc.engine.RTCVideo.sendSEIMessage(
    StreamIndex streamIndex,
    byte[] message,
    int repeatCount,
    SEICountPerFrame mode)
```
<span id="RTCVideo-sendseimessage-2"></span>通过视频帧发送 SEI 数据。
在视频通话场景下，SEI 数据会随视频帧发送；在语音通话场景下，SDK 会自动生成一路 16px × 16px 的黑帧视频流用来发送 SEI 数据。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamIndex | **StreamIndex** | 指定携带 SEI 数据的媒体流类型，参看 [StreamIndex](Android-keytype.md#streamindex-2)。<br/>语音通话场景下，该值需设为 `STREAM_INDEX_MAIN`，否则 SEI 数据会被丢弃从而无法送达远端。 |
| message | **byte[]** | SEI 消息，建议每帧 SEI 数据总长度不超过 4 KB。超过长度限制的消息会被丢弃。 |
| repeatCount | **int** | 消息发送重复次数。取值范围是 [0, max{29, %{视频帧率}-1}]。推荐范围 [2,4]。<br/>调用此接口后，这些 SEI 数据会添加到从当前视频帧开始的连续 `%{repeatCount+1}` 个视频帧中。 |
| mode | **SEICountPerFrame** | SEI 发送模式，参看 [SEICountPerFrame](Android-keytype.md#seicountperframe)。 |

**返回值**

+ \>= 0: 将被添加到视频帧中的 SEI 的数量。
+ < 0: 发送失败。


**注意**

+ 每秒发送的 SEI 消息数量建议不超过当前的视频帧率。在语音通话场景下，黑帧帧率为 15 fps。
+ 语音通话场景中，仅支持在内部采集模式下调用该接口发送 SEI 数据。
+ 视频通话场景中，使用自定义采集并通过 [pushExternalVideoFrame](#RTCVideo-pushexternalvideoframe) 推送至 SDK 的视频帧，若本身未携带 SEI 数据，也可通过本接口发送 SEI 数据；若原视频帧中已添加了 SEI 数据，则调用此方法不生效。
+ 视频帧仅携带前后 2s 内收到的 SEI 数据；语音通话场景下，若调用此接口后 1min 内未有 SEI 数据发送，则 SDK 会自动取消发布视频黑帧。
+ 消息发送成功后，远端会收到 [onSEIMessageReceived](Android-callback.md#IRTCVideoEventHandler-onseimessagereceived) 回调。
+ 语音通话切换至视频通话时，会停止使用黑帧发送 SEI 数据，自动转为用采集到的正常视频帧发送 SEI 数据。


<span id="RTCVideo-setbusinessid"></span>
### setBusinessId
```java
public abstract int com.ss.bytertc.engine.RTCVideo.setBusinessId(
    String businessId)
```
设置业务标识参数  <br>
可通过 businessId 区分不同的业务场景。businessId 由客户自定义，相当于一个“标签”，可以分担和细化现在 AppId 的逻辑划分的功能，但不需要鉴权。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| businessId | **String** | 用户设置的自己的 businessId 值<br/>businessId 只是一个标签，颗粒度需要用户自定义。 |

**返回值**

+ 0： 成功  
+ < 0： 失败  
+ -6001： 用户已经在房间中。  
+ -6002： 输入非法，合法字符包括所有小写字母、大写字母和数字，除此外还包括四个独立字符，分别是：英文句号，短横线，下划线和 @ 。


**注意**

+ 需要在进房前调用，进房后调用该方法无效。


<span id="RTCVideo-setencryptinfo"></span>
### setEncryptInfo
```java
public abstract void com.ss.bytertc.engine.RTCVideo.setEncryptInfo(
    int aesType,
    String key)
```
设置传输时使用内置加密的方式。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| aesType | **int** | 加密类型。可选参数为 0、1、2、3、4。代表的含义如下：<br/>0. 不加密 <br/>1. AES-128-CBC  <br/>2. AES-256-CBC  <br/>3. AES-128-ECB  <br/>4. AES-256-ECB |
| key | **String** | 加密密钥。长度限制为36位，超出部分将会被截断。 |


**注意**

+ 该方法与 [setCustomizeEncryptHandler](#RTCVideo-setcustomizeencrypthandler) 为互斥关系，即按照调用顺序，最后一个调用的方法为最终生效的版本。  
+ 该方法必须在调用 [joinRoom](#RTCRoom-joinroom) 之前调用，可重复调用，以最后调用的参数作为生效参数  


<span id="RTCVideo-setcustomizeencrypthandler"></span>
### setCustomizeEncryptHandler
```java
public abstract void com.ss.bytertc.engine.RTCVideo.setCustomizeEncryptHandler(
    RTCEncryptHandler handler)
```
设置自定义加密和解密方式。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| handler | **RTCEncryptHandler** | 自定义加密handler，需要实现里面的加密和解密方法。参看 [IRTCEncryptionHandler](Android-callback.md#irtcencryptionhandler)。 |


**注意**

+ 该方法与 [setEncryptInfo](#RTCVideo-setencryptinfo) 为互斥关系，即按照调用顺序，最后一个调用的方法为最终生效的版本  
+ 该方法必须在进房前调用，可重复调用，以最后调用的参数作为生效参数  
+ 无论加密或者解密，其对原始数据的长度修改，需要控制在90%-120%之间，即如果输入数据为100字节，则处理完成后的数据必须在 90 至 120 字节之间，如果加密或解密结果超出该长度限制，则该音视频帧会被丢弃  
+ 数据加密/解密为串行执行，因而视实现方式不同，可能会影响到最终渲染效率，是否使用该方法，需要由使用方谨慎评估  


<span id="RTCVideo-getvideoeffectinterface"></span>
### getVideoEffectInterface
```java
public abstract IVideoEffect com.ss.bytertc.engine.RTCVideo.getVideoEffectInterface()
```
获取视频特效接口。

**返回值**
视频特效接口，参看 [IVideoEffect](#ivideoeffect)。


<span id="RTCVideo-checkvideoeffectlicense"></span>
### checkVideoEffectLicense
```java
public abstract int com.ss.bytertc.engine.RTCVideo.checkVideoEffectLicense(
    Context context,
    String licenseFile)
```
> Deprecated  since 3.50 and will be deleted in 3.55, use [initCVResource](#IVideoEffect-initcvresource) instead.

视频特效许可证检查

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| context | **Context** | Android Context 对象 |
| licenseFile | **String** | 许可证文件绝对路径 |

**返回值**

+ 0: 许可证验证成功  
+ 1000: 未集成特效 SDK。  
+  1001: 特效 SDK 不支持该功能。  
+ <0: 其他错误，具体参看[错误码表](https://www.volcengine.com/docs/6705/102042)


**注意**
调用 [enableVideoEffect](#RTCVideo-enablevideoeffect) 开始使用视频特效前，需要先调用这个方法进行许可证验证

<span id="RTCVideo-setvideoeffectalgomodelpath"></span>
### setVideoEffectAlgoModelPath
```java
public abstract void com.ss.bytertc.engine.RTCVideo.setVideoEffectAlgoModelPath(
    String modelPath)
```
> Deprecated  since 3.50 and will be deleted in 3.55, use [initCVResource](#IVideoEffect-initcvresource) instead.

设置视频特效算法模型路径

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| modelPath | **String** | 模型路径 |


<span id="RTCVideo-enablevideoeffect"></span>
### enableVideoEffect
```java
public abstract int com.ss.bytertc.engine.RTCVideo.enableVideoEffect(
    boolean enable)
```
> Deprecated  since 3.50 and will be deleted in 3.55, use [enableVideoEffect](#IVideoEffect-enablevideoeffect) instead.

创建/销毁视频特效引擎

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| enable | **boolean** | 是否创建视频特效引擎  <br/>• true: 创建  <br/>• false: 销毁 |

**返回值**

+ 0: 成功  
+ 1000: 未集成特效 SDK。  
+  1001: 特效 SDK 不支持该功能。  
+ <0: 其他错误，具体参看[错误码表](https://www.volcengine.com/docs/6705/102042)


**注意**

+ 该方法须在调用 [checkVideoEffectLicense](#RTCVideo-checkvideoeffectlicense) 和 [setVideoEffectAlgoModelPath](#RTCVideo-setvideoeffectalgomodelpath) 后调用。  
+ 该方法不直接开启/关闭视频特效，你须在调用该方法后，调用 [setVideoEffectNodes](#RTCVideo-setvideoeffectnodes) 开启视频特效。  
+ 通用场景下，特效引擎会随 RTC 引擎销毁而销毁。当你对性能有较高要求时，可在不使用特效相关功能时调用该方法中 false 单独销毁特效引擎。


<span id="RTCVideo-setvideoeffectnodes"></span>
### setVideoEffectNodes
```java
public abstract int com.ss.bytertc.engine.RTCVideo.setVideoEffectNodes(
    List<String> effectNodes)
```
> Deprecated  since 3.50 and will be deleted in 3.55, use [setEffectNodes](#IVideoEffect-seteffectnodes) instead.

设置视频特效素材包

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| effectNodes | **List<String>** | 特效素材包路径数组 <br/>要取消当前视频特效，将此参数设置为 null。 |

**返回值**

+ 0: 调用成功。  
+ 1000: 未集成特效 SDK。  
+ 1001: 特效 SDK 不支持该功能。  
+ < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。  


**注意**
你须在调用 [enableVideoEffect](#RTCVideo-enablevideoeffect) 后调用该方法。

<span id="RTCVideo-updatevideoeffectnode"></span>
### updateVideoEffectNode
```java
public abstract int com.ss.bytertc.engine.RTCVideo.updateVideoEffectNode(
    String effectNode,
    String key,
    float value)
```
> Deprecated  since 3.50 and will be deleted in 3.55, use [updateEffectNode](#IVideoEffect-updateeffectnode) instead.

设置特效强度

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| effectNode | **String** | 特效素材包路径 |
| key | **String** | 需要设置的素材 key 名称，参看 [素材key对应说明](https://www.volcengine.com/docs/6705/102041)。 |
| value | **float** | 需要设置的强度值，取值范围为 [0,1]，超出该范围设置无效。 |

**返回值**

+ 0: 调用成功。  
+ 1000: 未集成特效 SDK。  
+ 1001: 特效 SDK 不支持该功能。  
+ < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。  


**注意**
该接口仅适用于同时含有上述三个参数的特效资源，对于如大部分贴纸类等没有强度参数的特效，该接口调用无效。

<span id="RTCVideo-setbackgroundsticker"></span>
### setBackgroundSticker
```java
public abstract int com.ss.bytertc.engine.RTCVideo.setBackgroundSticker(
    String modelPath,
    VirtualBackgroundSource source)
```
> Deprecated  since 3.50 and will be deleted in 3.55, use [enableVirtualBackground](#IVideoEffect-enablevirtualbackground) instead.

将摄像头采集画面中的人像背景替换为指定图片或纯色背景。
若要取消背景特效，将背景贴纸特效素材路径设置为null。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| modelPath | **String** | 传入背景贴纸特效素材路径。 |
| source | **VirtualBackgroundSource** | 设置背景特效图片的本地路径。参看 [VirtualBackgroundSource](Android-keytype.md#virtualbackgroundsource)。 |

**返回值**

+ 0：调用成功。  
+ 1000：未集成特效 SDK。  
+ 1001：特效 SDK 不支持该功能。  
+ < 0：调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。


**注意**
调用此接口前需依次调用以下接口：1、检查视频特效许可证 [checkVideoEffectLicense](#RTCVideo-checkvideoeffectlicense)；2、设置视频特效算法模型路径 [setVideoEffectAlgoModelPath](#RTCVideo-setvideoeffectalgomodelpath)；3、开启视频特效 [enableVideoEffect](#RTCVideo-enablevideoeffect)。


<span id="RTCVideo-setvideoeffectcolorfilter"></span>
### setVideoEffectColorFilter
```java
public abstract int com.ss.bytertc.engine.RTCVideo.setVideoEffectColorFilter(
    String resFile)
```
> Deprecated  since 3.50 and will be deleted in 3.55, use [setColorFilter](#IVideoEffect-setcolorfilter) instead.

设置颜色滤镜

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| resFile | **String** | 滤镜资源包绝对路径 |

**返回值**

+ 0: 调用成功。  
+ 1000: 未集成特效 SDK。  
+ 1001: 特效 SDK 不支持该功能。  
+ < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。  


<span id="RTCVideo-setvideoeffectcolorfilterintensity"></span>
### setVideoEffectColorFilterIntensity
```java
public abstract int com.ss.bytertc.engine.RTCVideo.setVideoEffectColorFilterIntensity(
    float intensity)
```
> Deprecated  since 3.50 and will be deleted in 3.55, use [setColorFilterIntensity](#IVideoEffect-setcolorfilterintensity) instead.

设置已启用的颜色滤镜强度

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| intensity | **float** | 滤镜强度，取值范围 [0,1]，超出范围时设置无效。 |

**返回值**

+ 0: 调用成功。  
+ 1000: 未集成特效 SDK。  
+ 1001: 特效 SDK 不支持该功能。  
+ < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。  


<span id="RTCVideo-registerfacedetectionobserver"></span>
### registerFaceDetectionObserver
```java
public abstract int com.ss.bytertc.engine.RTCVideo.registerFaceDetectionObserver(
    IFaceDetectionObserver observer,
    int interval)
```
> Deprecated  since 3.50 and will be deleted in 3.55, use [registerFaceDetectionObserver](#IVideoEffect-registerfacedetectionobserver) instead.

注册人脸检测结果回调观察者 <br>
注册此观察者后，你会周期性收到 [onFaceDetectResult](Android-callback.md#IFaceDetectionObserver-onfacedetectresult) 回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| observer | **IFaceDetectionObserver** | 人脸检测结果回调观察者，参看 [IFaceDetectionObserver](Android-callback.md#ifacedetectionobserver)。 |
| interval | **int** | 时间间隔，必须大于 0。单位：ms。实际收到回调的时间间隔大于 `interval`，小于 `interval • 视频采集帧间隔`。 |

**返回值**

+ 0：方法调用成功  
+ < 0：方法调用失败  


<span id="RTCVideo-enableeffectbeauty"></span>
### enableEffectBeauty
```java
public abstract int com.ss.bytertc.engine.RTCVideo.enableEffectBeauty(
    boolean enable)
```
开启/关闭基础美颜

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| enable | **boolean** | 基础美颜开关 <br/>• true: 开启基础美颜 <br/>• false: 关闭基础美颜（默认） |

**返回值**

+ 0: 调用成功。
+ –1000: 未集成特效 SDK。
+ –1001: RTC SDK 版本不支持此功能。
+ –1002: 特效 SDK 当前版本不支持此功能，建议使用特效 SDK V4.3.1 版本。
+ –1003: 联系技术支持人员。
+ –1004: 正在下载相关资源，下载完成后生效。
+ <0: 调用失败，特效 SDK 内部错误，具体错误码请参考[错误码表](https://www.volcengine.com/docs/6705/102042)。


**注意**

+ 本方法不能与高级视频特效接口共用。如已购买高级视频特效，建议调用 [enableVideoEffect](#IVideoEffect-enablevideoeffect) 使用高级特效、贴纸功能等。 
+ 使用此功能需要[集成](https://www.volcengine.com/docs/6348/114717)特效 SDK，建议使用特效 SDK V4.3.1+ 版本。 
+ 调用 [setBeautyIntensity](#RTCVideo-setbeautyintensity) 设置基础美颜强度。若在调用本方法前没有设置美颜强度，则初始美白、磨皮、锐化强度均为 0.5。 
+ 本方法仅适用于视频源，不适用于屏幕源。 


<span id="RTCVideo-setbeautyintensity"></span>
### setBeautyIntensity
```java
public abstract int com.ss.bytertc.engine.RTCVideo.setBeautyIntensity(
    EffectBeautyMode beautyMode,
    float intensity)
```
调整基础美颜强度

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| beautyMode | **EffectBeautyMode** | 基础美颜模式，参看 [EffectBeautyMode](Android-keytype.md#effectbeautymode)。 |
| intensity | **float** | 美颜强度，取值范围为 [0,1]。强度为 0 表示关闭，默认强度为 0.5。 |

**返回值**

+ 0: 调用成功。
+ –1000: 未集成特效 SDK。
+ –1001: RTC SDK 版本不支持此功能。
+ <0: 调用失败，特效 SDK 内部错误，具体错误码请参考[错误码表](https://www.volcengine.com/docs/6705/102042)。


**注意**

+ 若在调用 [enableEffectBeauty](#RTCVideo-enableeffectbeauty) 前设置美颜强度，则对应美颜功能的强度初始值会根据设置更新。
+ 销毁引擎后，美颜功能强度恢复默认值。


<span id="RTCVideo-setvideoorientation"></span>
### setVideoOrientation
```java
public abstract void com.ss.bytertc.engine.RTCVideo.setVideoOrientation(
    VideoOrientation orientation)
```
在自定义视频前处理及编码前，设置 RTC 链路中的视频帧朝向，默认为 Adaptive 模式。
移动端开启视频特效贴纸，或使用自定义视频前处理时，建议固定视频帧朝向为 Portrait 模式。单流转推场景下，建议根据业务需要固定视频帧朝向为 Portrait 或 Landscape 模式。不同模式的具体显示效果参看[视频帧朝向](https://www.volcengine.com/docs/6348/128787)。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| orientation | **VideoOrientation** | 视频帧朝向，参看 [VideoOrientation](Android-keytype.md#videoorientation)。 |


**注意**

+ 设置视频帧朝向仅对内部视频采集生效，不适用于外部视频源和屏幕源。  
+ 编码分辨率的更新与视频帧处理是异步操作，进房后切换视频帧朝向可能导致画面出现短暂的裁切异常，因此建议在进房前设置视频帧朝向，且不在进房后进行切换。


<span id="RTCVideo-setruntimeparameters"></span>
### setRuntimeParameters
```java
public abstract void com.ss.bytertc.engine.RTCVideo.setRuntimeParameters(
    JSONObject params)
```
设置运行时的参数

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| params | **JSONObject** | 保留参数 |


**注意**
该接口需在 [joinRoom](#RTCRoom-joinroom) 和 [startAudioCapture](#RTCVideo-startaudiocapture) 之前调用。

<span id="RTCVideo-feedback"></span>
### feedback
```java
public abstract int com.ss.bytertc.engine.RTCVideo.feedback(
    List<ProblemFeedbackOption> types,
    ProblemFeedbackInfo info)
```
将用户反馈的问题上报到 RTC

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| types | **List<ProblemFeedbackOption>** | 预设问题列表，参看 [ProblemFeedbackOption](Android-keytype.md#problemfeedbackoption) |
| info | **ProblemFeedbackInfo** | 预设问题以外的其他问题的具体描述、房间信息，参看 [ProblemFeedbackInfo](Android-keytype.md#problemfeedbackinfo) |

**返回值**

+ 0: 上报成功  
+ -1: 上报失败，还没加入过房间 
+ -2: 上报失败，数据解析错误  
+ -3: 上报失败，字段缺失  


**注意**
如果用户上报时在房间内，那么问题会定位到用户当前所在的一个或多个房间；如果用户上报时不在房间内，那么问题会定位到引擎此前退出的房间。


<span id="RTCVideo-startasr"></span>
### startASR
```java
public abstract void com.ss.bytertc.engine.RTCVideo.startASR(
    RTCASRConfig asrConfig,
    IRTCASREngineEventHandler handler)
```
开启自动语音识别服务。<br>
该方法将识别后的用户语音转化成文字，并通过 [onMessage](Android-callback.md#IRTCASREngineEventHandler-onmessage) 事件回调给用户。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| asrConfig | **RTCASRConfig** | 校验信息，参看 [RTCASRConfig](Android-keytype.md#rtcasrconfig) |
| handler | **IRTCASREngineEventHandler** | 语音识别服务使用状态回调，参看 [IRTCASREngineEventHandler](Android-callback.md#irtcasrengineeventhandler)。 |


<span id="RTCVideo-stopasr"></span>
### stopASR
```java
public abstract void com.ss.bytertc.engine.RTCVideo.stopASR()
```
关闭语音识别服务


<span id="RTCVideo-startfilerecording"></span>
### startFileRecording
```java
public abstract int com.ss.bytertc.engine.RTCVideo.startFileRecording(
    StreamIndex type,
    RecordingConfig config,
    RecordingType recordingType)
```
该方法将通话过程中的音视频数据录制到本地的文件中。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| type | **StreamIndex** | 流属性，指定录制主流还是屏幕流，参看 [StreamIndex](Android-keytype.md#streamindex-2) |
| config | **RecordingConfig** | 本地录制参数配置，参看 [RecordingConfig](Android-keytype.md#recordingconfig) |
| recordingType | **RecordingType** | 本地录制的媒体类型，参看 [RecordingType](Android-keytype.md#recordingtype) |

**返回值**
0: 正常
-1: 参数设置异常
-2: 当前版本 SDK 不支持该特性，请联系技术支持人员


**注意**

+ 调用该方法后，你会收到 [onRecordingStateUpdate](Android-callback.md#IRTCVideoEventHandler-onrecordingstateupdate) 回调。  
+ 如果录制正常，系统每秒钟会通过 [onRecordingProgressUpdate](Android-callback.md#IRTCVideoEventHandler-onrecordingprogressupdate) 回调通知录制进度。


<span id="RTCVideo-stopfilerecording"></span>
### stopFileRecording
```java
public abstract void com.ss.bytertc.engine.RTCVideo.stopFileRecording(
    StreamIndex type)
```
停止本地录制

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| type | **StreamIndex** | 流属性，指定停止主流或者屏幕流录制，参看 [StreamIndex](Android-keytype.md#streamindex-2) |


**注意**

+ 调用 [startFileRecording](#RTCVideo-startfilerecording) 开启本地录制后，你必须调用该方法停止录制。  
+ 调用该方法后，你会收到 [onRecordingStateUpdate](Android-callback.md#IRTCVideoEventHandler-onrecordingstateupdate) 回调提示录制结果。


<span id="RTCVideo-startaudiorecording"></span>
### startAudioRecording
```java
public abstract int com.ss.bytertc.engine.RTCVideo.startAudioRecording(
    AudioRecordingConfig config)
```
开启录制语音通话，生成本地文件。 <br>
在进房前后开启录制，如果未打开麦克风采集，录制任务正常进行，只是不会将数据写入生成的本地文件；只有调用 [startAudioCapture](#RTCVideo-startaudiocapture) 接口打开麦克风采集后，才会将录制数据写入本地文件。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| config | **AudioRecordingConfig** | 参看 [AudioRecordingConfig](Android-keytype.md#audiorecordingconfig) |

**返回值**

+ 0: 正常 
+ -2: 参数设置异常 
+ -3: 当前版本 SDK 不支持该特性，请联系技术支持人员


**注意**

+ 录制包含各种音频效果。但不包含混音的背景音乐。
+ 加入房间前后均可调用。在进房前调用该方法，退房之后，录制任务不会自动停止，需调用[stopAudioRecording](#RTCVideo-stopaudiorecording) 关闭录制。在进房后调用该方法，退房之后，录制任务会自动被停止。如果加入了多个房间，录制的文件中会包含各个房间的音频。
+ 调用该方法后，你会收到 [onAudioRecordingStateUpdate](Android-callback.md#IRTCVideoEventHandler-onaudiorecordingstateupdate) 回调。  


<span id="RTCVideo-stopaudiorecording"></span>
### stopAudioRecording
```java
public abstract int com.ss.bytertc.engine.RTCVideo.stopAudioRecording()
```
停止音频文件录制

**返回值**

+ 0: 正常 
+ -3: 当前版本 SDK 不支持该特性，请联系技术支持人员


**注意**
调用 [startAudioRecording](#RTCVideo-startaudiorecording) 开启本地录制后，你必须调用该方法停止录制。

<span id="RTCVideo-getaudiomixingmanager"></span>
### getAudioMixingManager
```java
public abstract IAudioMixingManager com.ss.bytertc.engine.RTCVideo.getAudioMixingManager()
```
混音管理接口创建

**返回值**
混音管理实例，详见[IAudioMixingManager](#iaudiomixingmanager)


<span id="RTCVideo-setscreenaudiosourcetype"></span>
### setScreenAudioSourceType
```java
public abstract void com.ss.bytertc.engine.RTCVideo.setScreenAudioSourceType(
    AudioSourceType sourceType)
```
在屏幕共享时，设置屏幕音频的采集方式（内部采集/自定义采集）

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| sourceType | **AudioSourceType** | 屏幕音频输入源类型, 参看 [AudioSourceType](Android-keytype.md#audiosourcetype)。 |


**注意**

+ 默认采集方式是 RTC SDK 内部采集。
+ 你应该在 [publishScreen](#RTCRoom-publishscreen) 前，调用此方法。否则，你将收到 [onWarning](Android-callback.md#IRTCVideoEventHandler-onwarning) 的报错：`WARNING_CODE_SET_SCREEN_AUDIO_SOURCE_TYPE_FAILED`。 
+ 如果设定为内部采集，你必须再调用 [startScreenCapture](#RTCVideo-startscreencapture) 开始采集。开启后，可以再次本接口切换为外部采集，此时内部采集将自动停止。
+ 如果设定为自定义采集，你必须再调用 [pushScreenAudioFrame](#RTCVideo-pushscreenaudioframe) 将自定义采集到的屏幕音频帧推送到 RTC SDK。
+ 无论是内部采集还是自定义采集，你都必须调用 [publishScreen](#RTCRoom-publishscreen) 发布采集到的屏幕音频流。


<span id="RTCVideo-setscreenaudiostreamindex"></span>
### setScreenAudioStreamIndex
```java
public abstract void com.ss.bytertc.engine.RTCVideo.setScreenAudioStreamIndex(
    StreamIndex index)
```
在屏幕共享时，设置屏幕音频流和麦克风采集到的音频流的混流方式

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| index | **StreamIndex** | 混流方式，参看 [StreamIndex](Android-keytype.md#streamindex-2) <br/>• `STREAM_INDEX_MAIN`: 将屏幕音频流和麦克风采集到的音频流混流 <br/>• `STREAM_INDEX_SCREEN`: 默认值，将屏幕音频流和麦克风采集到的音频流分为两路音频流 |


**注意**
你应该在 [publishScreen](#RTCRoom-publishscreen) 之前，调用此方法。否则，你将收到 [onWarning](Android-callback.md#IRTCVideoEventHandler-onwarning) 的报错：`WARNING_CODE_SET_SCREEN_STREAM_INDEX_FAILED`

<span id="RTCVideo-pushscreenaudioframe"></span>
### pushScreenAudioFrame
```java
public abstract int com.ss.bytertc.engine.RTCVideo.pushScreenAudioFrame(
    AudioFrame audioFrame)
```
使用自定义采集方式，采集屏幕共享时的屏幕音频时，将音频帧推送至 RTC SDK 处进行编码等处理。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioFrame | **AudioFrame** | 音频数据帧，参见 [AudioFrame](Android-keytype.md#audioframe) |

**返回值**
方法调用结果  

+ 0: 设置成功  
+ < 0: 设置失败  


**注意**

+ 调用此接口推送屏幕共享时的自定义采集的音频数据前，必须调用 [setScreenAudioSourceType](#RTCVideo-setscreenaudiosourcetype) 开启屏幕音频自定义采集。  
+ 你应每隔 10 毫秒，调用一次此方法推送一次自定义采集的音频帧。一次推送的音频帧中应包含 frame.sample_rate / 100 个音频采样点。比如，假如采样率为 48000Hz，则每次应该推送 480 个采样点。  
+ 音频采样格式为 S16。音频缓冲区内的数据格式必须为 PCM 数据，其容量大小应该为 samples × frame.channel × 2。  
+ 调用此接口将自定义采集的音频帧推送到 RTC SDK 后，你必须调用 [publishScreen](#RTCRoom-publishscreen) 将采集到的屏幕音频推送到远端。在调用 [publishScreen](#RTCRoom-publishscreen) 前，推送到 RTC SDK 的音频帧信息会丢失。


<span id="RTCVideo-startscreencapture"></span>
### startScreenCapture
```java
public abstract void com.ss.bytertc.engine.RTCVideo.startScreenCapture(
    ScreenMediaType type,
    Intent mediaProjectionResultData)
```
使用 RTC SDK 内部采集模块开始采集屏幕音频流和（或）视频流。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| type | **ScreenMediaType** | 媒体类型，参看 [ScreenMediaType](Android-keytype.md#screenmediatype)。 |
| mediaProjectionResultData | **Intent** | 向 Android 设备申请屏幕共享权限后，拿到的 Intent 数据，参看 [getMediaProjection](https://developer.android.com/reference/android/media/projection/MediaProjectionManager#getMediaProjection(int,%20android.content.Intent))。 |


**注意**

+ 调用本接口时，采集模式应为内部模式。在外部采集模式下调用无效，并将触发 [onVideoDeviceWarning](Android-callback.md#IRTCVideoEventHandler-onvideodevicewarning) 或 [onAudioDeviceWarning](Android-callback.md#IRTCVideoEventHandler-onaudiodevicewarning) 回调。
+ 采集后，你还需要调用 [publishScreen](#RTCRoom-publishscreen) 发布采集到的屏幕音视频。
+ 开启屏幕音频/视频采集成功后，本地用户会收到 [onVideoDeviceStateChanged](Android-callback.md#IRTCVideoEventHandler-onvideodevicestatechanged) 和 [onAudioDeviceStateChanged](Android-callback.md#IRTCVideoEventHandler-onaudiodevicestatechanged) 的回调。
+ 要关闭屏幕音视频内部采集，调用 [stopScreenCapture](#RTCVideo-stopscreencapture)。


<span id="RTCVideo-updatescreencapture"></span>
### updateScreenCapture
```java
public abstract void com.ss.bytertc.engine.RTCVideo.updateScreenCapture(
    ScreenMediaType type)
```
使用 RTC SDK 内部屏幕采集后，更新采集的媒体类型。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| type | **ScreenMediaType** | 媒体类型，指定屏幕采集媒体类型，参看 [ScreenMediaType](Android-keytype.md#screenmediatype)。 |

**返回值**

+ 0: 成功  
+ -1: 失败  


**注意**
在 [startScreenCapture](#RTCVideo-startscreencapture) 后调用该方法。

<span id="RTCVideo-stopscreencapture"></span>
### stopScreenCapture
```java
public abstract void com.ss.bytertc.engine.RTCVideo.stopScreenCapture()
```
在屏幕共享时，停止使用 RTC SDK 内部采集方式采集屏幕音视频。


**注意**

+ 调用本接口时，采集模式应为内部模式。在外部采集模式下调用无效，并将触发 [onVideoDeviceWarning](Android-callback.md#IRTCVideoEventHandler-onvideodevicewarning) 或 [onAudioDeviceWarning](Android-callback.md#IRTCVideoEventHandler-onaudiodevicewarning) 回调。
+ 要开始屏幕音视频内部采集，调用 [startScreenCapture](#RTCVideo-startscreencapture)。


<span id="RTCVideo-setexternalvideoencodereventhandler"></span>
### setExternalVideoEncoderEventHandler
```java
public abstract void com.ss.bytertc.engine.RTCVideo.setExternalVideoEncoderEventHandler(
    IExternalVideoEncoderEventHandler encoder_handler)
```
注册自定义编码帧推送事件回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| encoder_handler | **IExternalVideoEncoderEventHandler** | 自定义编码帧回调类，参看 [IExternalVideoEncoderEventHandler](Android-callback.md#iexternalvideoencodereventhandler) |


**注意**

+ 该方法需在进房前调用。 
+ 引擎销毁前需取消注册，调用该方法将参数设置为 "null" 即可。


<span id="RTCVideo-pushexternalencodedvideoframe"></span>
### pushExternalEncodedVideoFrame
```java
public abstract int com.ss.bytertc.engine.RTCVideo.pushExternalEncodedVideoFrame(
    StreamIndex index,
    int video_index,
    RTCEncodedVideoFrame video_stream)
```
推送自定义编码后的视频流

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| index | **StreamIndex** | 需要推送的编码流的属性，参看 [StreamIndex](Android-keytype.md#streamindex-2) |
| video_index | **int** | 对应的编码流下标，从 0 开始，如果调用 [setVideoEncoderConfig](#RTCVideo-setvideoencoderconfig) 设置了多路流，此处数量须与之保持一致 |
| video_stream | **RTCEncodedVideoFrame** | 编码流视频帧信息，参看 [RTCEncodedVideoFrame](Android-keytype.md#rtcencodedvideoframe)。 |

**返回值**
方法调用结果：

+ 0：成功；
+ <0：失败。具体失败原因参看 [ReturnStatus](Android-keytype.md#returnstatus)。


**注意**

+ 目前仅支持推送 H264 和 ByteVC1 格式的视频帧，且视频流协议格式须为 Annex B 格式。  
+ 该函数运行在用户调用线程内  
+ 推送自定义编码视频帧前，必须调用 [setVideoSourceType](#RTCVideo-setvideosourcetype) 将视频输入源切换至自定义编码视频源。


<span id="RTCVideo-setvideodecoderconfig"></span>
### setVideoDecoderConfig
```java
public abstract void com.ss.bytertc.engine.RTCVideo.setVideoDecoderConfig(
    RemoteStreamKey key,
    VideoDecoderConfig config)
```
在订阅远端视频流之前，设置远端视频数据解码方式

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| key | **RemoteStreamKey** | 远端流信息，指定对哪一路视频流进行解码方式设置，参看 [RemoteStreamKey](Android-keytype.md#remotestreamkey)。 |
| config | **VideoDecoderConfig** | 视频解码方式，参看 [VideoDecoderConfig](Android-keytype.md#videodecoderconfig)。 |


**注意**

+ 该方法仅适用于手动订阅模式，并且在订阅远端流之前使用。  
+ 当你想要对远端流进行自定义解码时，你需要先调用 [registerRemoteEncodedVideoFrameObserver](#RTCVideo-registerremoteencodedvideoframeobserver) 注册远端视频流监测器，然后再调用该接口将解码方式设置为自定义解码。监测到的视频数据会通过 [onRemoteEncodedVideoFrame](Android-callback.md#IRemoteEncodedVideoFrameObserver-onremoteencodedvideoframe) 回调出来。


<span id="RTCVideo-requestremotevideokeyframe"></span>
### requestRemoteVideoKeyFrame
```java
public abstract void com.ss.bytertc.engine.RTCVideo.requestRemoteVideoKeyFrame(
    RemoteStreamKey stream_info)
```
在订阅远端视频流之后，向远端请求关键帧

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stream_info | **RemoteStreamKey** | 远端流信息，参看 [RemoteStreamKey](Android-keytype.md#remotestreamkey)。 |


**注意**

+ 该方法仅适用于手动订阅模式，并且在成功订阅远端流之后使用。  
+ 该方法适用于调用 [setVideoDecoderConfig](#RTCVideo-setvideodecoderconfig) 开启自定义解码功能后，并且自定义解码失败的情况下使用


<span id="RTCVideo-setearmonitormode"></span>
### setEarMonitorMode
```java
public abstract void com.ss.bytertc.engine.RTCVideo.setEarMonitorMode(
    EarMonitorMode mode)
```
打开/关闭耳返功能。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mode | **EarMonitorMode** | 耳返功能是否开启，详见 [EarMonitorMode](Android-keytype.md#earmonitormode)。 |


**注意**

+ 耳返功能仅适用于由 RTC SDK 内部采集的音频。  
+ 使用耳返功能必须佩戴耳机。为保证低延时耳返最佳体验，建议佩戴有线耳机。蓝牙耳机不支持硬件耳返。 
+ RTC SDK 支持硬件耳返和软件耳返。一般来说，硬件耳返延时低且音质好。如果 App 在手机厂商的硬件耳返白名单内，且运行环境存在支持硬件耳返的 SDK，RTC SDK 默认启用硬件耳返。使用华为手机硬件耳返功能时，请添加[华为硬件耳返的依赖配置](https://www.volcengine.com/docs/6348/113523)。


<span id="RTCVideo-setearmonitorvolume"></span>
### setEarMonitorVolume
```java
public abstract void com.ss.bytertc.engine.RTCVideo.setEarMonitorVolume(
    int volume)
```
设置耳返音量。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| volume | **int** | 耳返音量，调节范围：[0,100]，单位：% |


**注意**

+ 设置耳返音量前，你必须先调用 [setEarMonitorMode](#RTCVideo-setearmonitormode) 打开耳返功能。  


<span id="RTCVideo-enableaudiopropertiesreport"></span>
### enableAudioPropertiesReport
```java
public abstract void com.ss.bytertc.engine.RTCVideo.enableAudioPropertiesReport(
    AudioPropertiesConfig config)
```
启用音频信息提示。开启提示后，你可以收到 [onLocalAudioPropertiesReport](Android-callback.md#IRTCVideoEventHandler-onlocalaudiopropertiesreport)，[onRemoteAudioPropertiesReport](Android-callback.md#IRTCVideoEventHandler-onremoteaudiopropertiesreport) 和 [onActiveSpeaker](Android-callback.md#IRTCVideoEventHandler-onactivespeaker)。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| config | **AudioPropertiesConfig** | 详见 [AudioPropertiesConfig](Android-keytype.md#audiopropertiesconfig) |


<span id="RTCVideo-sendstreamsyncinfo"></span>
### sendStreamSyncInfo
```java
public abstract int com.ss.bytertc.engine.RTCVideo.sendStreamSyncInfo(
    byte[] data,
    StreamSycnInfoConfig config)
```
发送音频流同步信息。将消息通过音频流发送到远端，并实现与音频流同步，该接口调用成功后，远端用户会收到 [onStreamSyncInfoReceived](Android-callback.md#IRTCVideoEventHandler-onstreamsyncinforeceived) 回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| data | **byte[]** | 消息内容。 |
| config | **StreamSycnInfoConfig** | 音频流同步信息的相关配置。详见 [StreamSycnInfoConfig](Android-keytype.md#streamsycninfoconfig) 。 |

**返回值**

+ \>=0: 消息发送成功。返回成功发送的次数。  
+ -1: 消息发送失败。消息长度大于 255 字节。  
+ -2: 消息发送失败。传入的消息内容为空。  
+ -3: 消息发送失败。通过屏幕流进行消息同步时，此屏幕流还未发布。  
+ -4: 消息发送失败。通过用麦克风或自定义设备采集到的音频流进行消息同步时，此音频流还未发布，详见错误码 [ErrorCode](Android-errorcode.md#errorcode)。  


**注意**

+ 调用本接口的频率建议不超过 50 次每秒。
+ 在 `CHANNEL_PROFILE_INTERACTIVE_PODCAST` 房间模式下，此消息一定会送达。在其他房间模式下，如果本地用户未说话，此消息不一定会送达。


<span id="RTCVideo-iscameratorchsupported"></span>
### isCameraTorchSupported
```java
public abstract boolean com.ss.bytertc.engine.RTCVideo.isCameraTorchSupported()
```
检测当前使用的摄像头（前置/后置），是否支持闪光灯。

**返回值**

+ true: 支持 
+ false: 不支持


**注意**
必须已调用 [startVideoCapture](#RTCVideo-startvideocapture) 使用 SDK 内部采集模块进行视频采集时，才能检测闪光能力。

<span id="RTCVideo-iscamerazoomsupported"></span>
### isCameraZoomSupported
```java
public abstract boolean com.ss.bytertc.engine.RTCVideo.isCameraZoomSupported()
```
检测当前使用的摄像头（前置/后置），是否支持变焦（数码/光学变焦）。

**返回值**

+ true: 支持 
+ false: 不支持


**注意**
必须已调用 [startVideoCapture](#RTCVideo-startvideocapture) 使用 SDK 内部采集模块进行视频采集时，才能检测摄像头变焦能力。

<span id="RTCVideo-setcamerazoomratio"></span>
### setCameraZoomRatio
```java
public abstract int com.ss.bytertc.engine.RTCVideo.setCameraZoomRatio(
    float zoom)
```
设置当前使用的摄像头（前置/后置）的光学变焦倍数

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| zoom | **float** | 变焦倍数。取值范围是 [1, <最大变焦倍数>]。<br/>最大变焦倍数可以通过调用 [getCameraZoomMaxRatio](#RTCVideo-getcamerazoommaxratio) 获取。 |

**返回值**

+ 0： 成功。 
+ < 0： 失败。


**注意**

+ 必须已调用 [startVideoCapture](#RTCVideo-startvideocapture) 使用 SDK 内部采集模块进行视频采集时，才能设置摄像头变焦倍数。
+ 设置结果在调用 [stopVideoCapture](#RTCVideo-stopvideocapture) 关闭内部采集后失效。
+ 你可以调用 [setVideoDigitalZoomConfig](#RTCVideo-setvideodigitalzoomconfig) 设置数码变焦参数， 调用 [setVideoDigitalZoomControl](#RTCVideo-setvideodigitalzoomcontrol) 进行数码变焦。


<span id="RTCVideo-getcamerazoommaxratio"></span>
### getCameraZoomMaxRatio
```java
public abstract float com.ss.bytertc.engine.RTCVideo.getCameraZoomMaxRatio()
```
获取当前使用的摄像头（前置/后置）的最大变焦倍数

**返回值**
最大变焦倍数


**注意**
必须已调用 [startVideoCapture](#RTCVideo-startvideocapture) 使用 SDK 内部采集模块进行视频采集时，才能检测摄像头最大变焦倍数。

<span id="RTCVideo-setcameratorch"></span>
### setCameraTorch
```java
public abstract int com.ss.bytertc.engine.RTCVideo.setCameraTorch(
    TorchState torch_state)
```
打开/关闭当前使用的摄像头（前置/后置）的闪光灯

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| torch_state | **TorchState** | 闪光灯状态。参考 [TorchState](Android-keytype.md#torchstate) |

**返回值**

+ 0： 成功。
+ < 0： 失败。


**注意**

+ 必须已调用 [startVideoCapture](#RTCVideo-startvideocapture) 使用 SDK 内部采集模块进行视频采集时，才能设置闪光灯。
+ 设置结果在调用 [stopVideoCapture](#RTCVideo-stopvideocapture) 关闭内部采集后失效。


<span id="RTCVideo-iscamerafocuspositionsupported"></span>
### isCameraFocusPositionSupported
```java
public abstract boolean com.ss.bytertc.engine.RTCVideo.isCameraFocusPositionSupported()
```
检查当前使用的摄像头是否支持手动对焦。

**返回值**

+ true: 支持。 
+ false: 不支持。


**注意**
必须已调用 [startVideoCapture](#RTCVideo-startvideocapture) 使用 SDK 内部采集模块进行视频采集，才能检查摄像头是否支持手动对焦。

<span id="RTCVideo-setcamerafocusposition"></span>
### setCameraFocusPosition
```java
public abstract int com.ss.bytertc.engine.RTCVideo.setCameraFocusPosition(
    float x,
    float y)
```
设置当前使用的摄像头的对焦点。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| x | **float** | 对焦点水平方向归一化坐标。以本地预览画布的左上为原点，取值范围为 [0, 1]，0 表示最左边，1 表示最右边。 |
| y | **float** | 对焦点垂直方向归一化坐标。以本地预览画布的左上为原点，取值范围为 [0, 1]，0 表示最上边，1 表示最下边。 |

**返回值**

+ 0: 成功。 
+ < 0: 失败。


**注意**

+ 必须已调用 [startVideoCapture](#RTCVideo-startvideocapture) 使用 SDK 内部采集模块进行视频采集，并且使用 SDK 内部渲染时，才能设置对焦点。  
+ 移动设备时，自动取消对焦点设置。  
+ 调用 [stopVideoCapture](#RTCVideo-stopvideocapture) 关闭内部采集后，设置的对焦点失效。


<span id="RTCVideo-iscameraexposurepositionsupported"></span>
### isCameraExposurePositionSupported
```java
public abstract boolean com.ss.bytertc.engine.RTCVideo.isCameraExposurePositionSupported()
```
检查当前使用的摄像头是否支持手动设置曝光点。

**返回值**

+ true: 支持。 
+ false: 不支持。


**注意**
必须已调用 [startVideoCapture](#RTCVideo-startvideocapture) 使用 SDK 内部采集模块进行视频采集时，才能检查曝光点设置能力。

<span id="RTCVideo-setcameraexposureposition"></span>
### setCameraExposurePosition
```java
public abstract int com.ss.bytertc.engine.RTCVideo.setCameraExposurePosition(
    float x,
    float y)
```
设置当前使用的摄像头的曝光点

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| x | **float** | 曝光点水平方向归一化坐标。以本地预览画布的左上为原点，取值范围为 [0, 1]，0 表示最左边，1 表示最右边。 |
| y | **float** | 曝光点垂直方向归一化坐标。以本地预览画布的左上为原点，取值范围为 [0, 1]，0 表示最上边，1 表示最下边。 |

**返回值**

+ 0: 成功。 
+ < 0: 失败。


**注意**

+ 必须已调用 [startVideoCapture](#RTCVideo-startvideocapture) 使用 SDK 内部采集模块进行视频采集，并且使用SDK内部渲染时，才能设置曝光点。 
+ 移动设备时，自动取消曝光点设置。  
+ 调用 [stopVideoCapture](#RTCVideo-stopvideocapture) 关闭内部采集后，设置的曝光点失效。


<span id="RTCVideo-setcameraexposurecompensation"></span>
### setCameraExposureCompensation
```java
public abstract int com.ss.bytertc.engine.RTCVideo.setCameraExposureCompensation(
    float val)
```
设置当前使用的摄像头的曝光补偿。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| val | **float** | 曝光补偿值，取值范围 [-1, 1]，0 为系统默认值(没有曝光补偿)。 |

**返回值**

+ 0: 成功。 
+ < 0: 失败。


**注意**

+ 必须已调用 [startVideoCapture](#RTCVideo-startvideocapture) 使用 SDK 内部采集模块进行视频采集时，才能设置曝光补偿。  
+ 调用 [stopVideoCapture](#RTCVideo-stopvideocapture) 关闭内部采集后，设置的曝光补偿失效。


<span id="RTCVideo-muteaudioplayback"></span>
### muteAudioPlayback
```java
public abstract void com.ss.bytertc.engine.RTCVideo.muteAudioPlayback(
    MuteState muteState)
```
> Deprecated  since 3.45 and will be deleted in 3.51, use [setPlaybackVolume](#RTCVideo-setplaybackvolume) instead.

控制本地音频流播放状态：播放/不播放  <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| muteState | **MuteState** | 播放状态，标识是否播放本地音频流，详见：[MuteState](Android-keytype.md#mutestate) |


**注意**
本方法仅控制本地收到音频流的播放状态，并不影响本地音频播放设备。

<span id="RTCVideo-startpushpublicstream"></span>
### startPushPublicStream
```java
public abstract int com.ss.bytertc.engine.RTCVideo.startPushPublicStream(
    String publicStreamId,
    PublicStreaming publicStream)
```
发布一路公共流<br>
用户可以指定房间内多个用户发布的媒体流合成一路公共流。使用同一 `appID` 的用户，可以调用 [startPlayPublicStream](#RTCVideo-startplaypublicstream) 获取和播放指定的公共流。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| publicStreamId | **String** | 公共流ID |
| publicStream | **PublicStreaming** | 公共流参数。详见 [PublicStreaming](Android-keytype.md#publicstreaming)。<br/>一路公共流可以包含多路房间内的媒体流，按照指定的布局方式进行聚合。<br/>如果指定的媒体流还未发布，则公共流将在指定流开始发布后实时更新。 |

**返回值**
0: 成功。同时将收到 [onPushPublicStreamResult](Android-callback.md#IRTCVideoEventHandler-onpushpublicstreamresult) 回调。

+ !0: 失败。当参数不合法或参数为空，调用失败。


**注意**

+ 同一用户使用同一公共流 ID 多次调用本接口无效。如果你希望更新公共流参数，调用 [updatePublicStreamParam](#RTCVideo-updatepublicstreamparam) 接口。
+ 不同用户使用同一公共流 ID 多次调用本接口时，RTC 将使用最后一次调用时传入的参数更新公共流。
+ 使用不同的 ID 多次调用本接口可以发布多路公共流。
+ 调用 [stopPushPublicStream](#RTCVideo-stoppushpublicstream) 停止推公共流。
+ 关于公共流功能的介绍，详见[发布和订阅公共流](https://www.volcengine.com/docs/6348/108930)


<span id="RTCVideo-stoppushpublicstream"></span>
### stopPushPublicStream
```java
public abstract int com.ss.bytertc.engine.RTCVideo.stopPushPublicStream(
    String publicStreamId)
```
停止发布当前用户发布的公共流<br>
关于发布公共流，查看 [startPushPublicStream](#RTCVideo-startpushpublicstream)

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| publicStreamId | **String** | 公共流 ID  <br/>指定的流必须为当前用户所发布。 |

**返回值**

+ 0: 成功
+ !0: 失败


<span id="RTCVideo-updatepublicstreamparam"></span>
### updatePublicStreamParam
```java
public abstract int com.ss.bytertc.engine.RTCVideo.updatePublicStreamParam(
    String publicStreamId,
    PublicStreaming transcoding)
```
更新公共流参数<br>
关于发布公共流，查看 [startPushPublicStream](#RTCVideo-startpushpublicstream)。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| publicStreamId | **String** | 公共流 ID  <br/>指定的流必须为当前用户所发布。 |
| transcoding | **PublicStreaming** | 配置参数，详见 [PublicStreaming](Android-keytype.md#publicstreaming)。 |

**返回值**

+ 0: 成功
+ !0: 失败


**注意**
调用本接口前需要通过 [onPushPublicStreamResult](Android-callback.md#IRTCVideoEventHandler-onpushpublicstreamresult) 确认公共流是否已经成功启动。

<span id="RTCVideo-startplaypublicstream"></span>
### startPlayPublicStream
```java
public abstract int com.ss.bytertc.engine.RTCVideo.startPlayPublicStream(
    String publicStreamId)
```
订阅指定公共流<br>
无论用户是否在房间内，都可以调用本接口获取和播放指定的公共流。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| publicStreamId | **String** | 公共流ID，如果指定流暂未发布，则本地客户端将在其开始发布后接收到流数据。 |

**返回值**

+ 0: 成功。同时将收到 [onPlayPublicStreamResult](Android-callback.md#IRTCVideoEventHandler-onplaypublicstreamresult) 回调。
+ !0: 失败。当参数不合法或参数为空，调用失败。


**注意**

+ 在调用本接口之前，建议先绑定渲染视图。
- 调用 [setPublicStreamVideoCanvas](#RTCVideo-setpublicstreamvideocanvas) 绑定内部渲染视图：
- 调用 [setPublicStreamVideoSink](#RTCVideo-setpublicstreamvideosink) 绑定自定义渲染视图：
+ 调用本接口后，可以通过 [onFirstPublicStreamVideoFrameDecoded](Android-callback.md#IRTCVideoEventHandler-onfirstpublicstreamvideoframedecoded) 和 [onFirstPublicStreamAudioFrame](Android-callback.md#IRTCVideoEventHandler-onfirstpublicstreamaudioframe) 回调公共流的视频和音频首帧解码情况。
+ 调用本接口后，可以通过 [onPublicStreamSEIMessageReceived](Android-callback.md#IRTCVideoEventHandler-onpublicstreamseimessagereceived) 回调公共流中包含的 SEI 信息。
+ 调用 [stopPlayPublicStream](#RTCVideo-stopplaypublicstream) 取消订阅公共流。


<span id="RTCVideo-stopplaypublicstream"></span>
### stopPlayPublicStream
```java
public abstract int com.ss.bytertc.engine.RTCVideo.stopPlayPublicStream(
    String publicStreamId)
```
取消订阅指定公共流<br>
关于订阅公共流，查看 [startPlayPublicStream](#RTCVideo-startplaypublicstream)。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| publicStreamId | **String** | 公共流ID |

**返回值**

+ 0：成功  
+ !0：失败  


<span id="RTCVideo-setpublicstreamvideocanvas"></span>
### setPublicStreamVideoCanvas
```java
public abstract int com.ss.bytertc.engine.RTCVideo.setPublicStreamVideoCanvas(
    String publicStreamId,
    VideoCanvas canvas)
```
为指定公共流绑定内部渲染视图。  <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| publicStreamId | **String** | 公共流ID |
| canvas | **VideoCanvas** | 内部渲染视图，如果需要解除视频的绑定视图，把 videoCanvas 设置为空。详见 [VideoCanvas](Android-keytype.md#videocanvas) |

**返回值**

+ 0：成功  
+ <0：失败  


<span id="RTCVideo-setpublicstreamvideosink"></span>
### setPublicStreamVideoSink
```java
public abstract int com.ss.bytertc.engine.RTCVideo.setPublicStreamVideoSink(
    String publicStreamId,
    IVideoSink videoSink,
    @IVideoSink.PixelFormat int requiredFormat)
```
为指定公共流绑定自定义渲染器。详见[自定义视频渲染](https://www.volcengine.com/docs/6348/81201)。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| publicStreamId | **String** | 公共流ID |
| videoSink | **IVideoSink** | 自定义视频渲染器，需要释放渲染器资源时，将 videoSink 设置为 `null`。参看 [IVideoSink](Android-keytype.md#ivideosink) |
| requiredFormat | **@IVideoSink.PixelFormat int** | videoSink 适用的视频帧编码格式，参看 [PixelFormat](Android-keytype.md#pixelformat) |

**返回值**
方法调用结果：

+ 0：成功；
+ <0：失败。具体失败原因参看 [ReturnStatus](Android-keytype.md#returnstatus)。


<span id="RTCVideo-setpublicstreamaudioplaybackvolume"></span>
### setPublicStreamAudioPlaybackVolume
```java
public abstract int com.ss.bytertc.engine.RTCVideo.setPublicStreamAudioPlaybackVolume(
    String publicStreamId,
    int volume)
```
> Available since 3.51

调节公共流的音频播放音量。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| publicStreamId | **String** | 公共流 ID |
| volume | **int** | 音频播放音量值和原始音量值的比值，该比值的范围是 `[0, 400]`，单位为 %，且自带溢出保护。为保证更好的音频质量，建议设定在 `[0, 100]` 之间，其中 100 为系统默认值。 |

**返回值**

+ 0: 成功调用。
+ -2: 参数错误。


<span id="RTCVideo-startechotest"></span>
### startEchoTest
```java
public abstract int com.ss.bytertc.engine.RTCVideo.startEchoTest(
    EchoTestConfig config,
    int delayTime)
```
开启音视频回路测试。  <br>
在进房前，用户可调用该接口对音视频通话全链路进行检测，包括对音视频设备以及用户上下行网络的检测，从而帮助用户判断是否可以正常发布和接收音视频流。  <br>
开始检测后，SDK 会录制你声音或视频。如果你在设置的延时范围内收到了回放，则视为音视频回路测试正常。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| config | **EchoTestConfig** | 回路测试参数设置，参看 [EchoTestConfig](Android-keytype.md#echotestconfig)。 |
| delayTime | **int** | 音视频延迟播放的时间间隔，用于指定在开始检测多长时间后期望收到回放。取值范围为 [2,10]，单位为秒，默认为 2 秒。 |

**返回值**
方法调用结果：  

+ 0：成功  
+ -1：失败，当前用户已经在检测中  
+ -2：失败，用户已进房  
+ -3：失败，音视频均未采集  
+ -4：失败，参数异常  
+ -5：失败，已经存在相同 roomId 的房间


**注意**

+ 调用该方法开始音视频回路检测后，你可以调用 [stopEchoTest](#RTCVideo-stopechotest) 立即结束测试，也可等待测试 60s 后自动结束，以更换设备进行下一次测试，或进房。  
+ 在该方法之前调用的所有跟设备控制、流控制相关的方法均在开始检测时失效，在结束检测后恢复生效。  
+ 在调用 [startEchoTest](#RTCVideo-startechotest) 和 [stopEchoTest](#RTCVideo-stopechotest) 之间调用的所有跟设备采集、流控制、进房相关的方法均不生效，并会收到 [onWarning](Android-callback.md#IRTCVideoEventHandler-onwarning) 回调，提示警告码为 `WARNING_CODE_IN_ECHO_TEST_MODE`。  
+ 音视频回路检测的结果会通过 [onEchoTestResult](Android-callback.md#IRTCVideoEventHandler-onechotestresult) 回调通知。


<span id="RTCVideo-stopechotest"></span>
### stopEchoTest
```java
public abstract int com.ss.bytertc.engine.RTCVideo.stopEchoTest()
```
停止音视频回路测试。  <br>
调用 [startEchoTest](#RTCVideo-startechotest) 开启音视频回路检测后，你必须调用该方法停止检测。

**返回值**
方法调用结果：  

+ 0：成功  
+ -1：失败，未开启回路检测


**注意**
音视频回路检测结束后，所有对系统设备及音视频流的控制均会恢复到开始检测前的状态。

<span id="RTCVideo-setvideowatermark"></span>
### setVideoWatermark
```java
public abstract void com.ss.bytertc.engine.RTCVideo.setVideoWatermark(
    StreamIndex streamIndex,
    String imagePath,
    RTCWatermarkConfig watermarkConfig)
```
在指定视频流上添加水印。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamIndex | **StreamIndex** | 需要添加水印的视频流属性，参看 [StreamIndex](Android-keytype.md#streamindex-2)。 |
| imagePath | **String** | 水印图片路径，支持本地文件绝对路径、Asset 资源路径（/assets/xx.png）、URI 地址（content://），长度限制为 512 字节。  <br/>水印图片为 PNG 或 JPG 格式。 |
| watermarkConfig | **RTCWatermarkConfig** | 水印参数，参看 [RTCWatermarkConfig](Android-keytype.md#rtcwatermarkconfig)。 |


**注意**

+ 调用 [clearVideoWatermark](#RTCVideo-clearvideowatermark) 移除指定视频流的水印。  
+ 同一路流只能设置一个水印，新设置的水印会代替上一次的设置。你可以多次调用本方法来设置不同流的水印。  
+ 进入房间前后均可调用此方法。  
+ 若开启本地预览镜像，或开启本地预览和编码传输镜像，则远端水印均不镜像；在开启本地预览水印时，本端水印会镜像。  
+ 开启大小流后，水印对大小流均生效，且针对小流进行等比例缩小。


<span id="RTCVideo-clearvideowatermark"></span>
### clearVideoWatermark
```java
public abstract void com.ss.bytertc.engine.RTCVideo.clearVideoWatermark(
    StreamIndex streamIndex)
```
移除指定视频流的水印。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamIndex | **StreamIndex** | 需要移除水印的视频流属性，参看 [StreamIndex](Android-keytype.md#streamindex-2)。 |


<span id="RTCVideo-setdummycaptureimagepath"></span>
### setDummyCaptureImagePath
```java
public abstract int com.ss.bytertc.engine.RTCVideo.setDummyCaptureImagePath(
    String filePath)
```
摄像头处于关闭状态时，使用静态图片填充本地推送的视频流。
调用 `stopVideoCapture` 接口时，会开始推静态图片。若要停止发送图片，可传入空字符串或启用内部摄像头采集。
可重复调用该接口来更新图片。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| filePath | **String** | 设置静态图片的路径。  <br/>支持本地文件绝对路径和 Asset 资源路径(/assets/xx.png)，不支持网络链接，长度限制为 512 字节。   <br/>静态图片支持类型为 JPEG/JPG、PNG、BMP。  <br/>若图片宽高比与设置的编码宽高比不一致，图片会被等比缩放，黑边填充空白区域。推流帧率与码率与设置的编码参数一致。 |

**返回值**

+ 0: 成功。  
+ -1: 失败。


**注意**

+ 该接口只适用于 SDK 内部摄像头采集，不适用于自定义视频采集。  
+ 本地预览无法看到静态图片。  
+ 进入房间前后均可调用此方法。在多房间场景中，静态图片仅在发布的房间中生效。  
+ 针对该静态图片，滤镜和镜像效果不生效，水印效果生效。  
+ 只有主流能设置静态图片，屏幕流不支持设置。  
+ 开启大小流后，静态图片对大小流均生效，且针对小流进行等比例缩小。


<span id="RTCVideo-takelocalsnapshot"></span>
### takeLocalSnapshot
```java
public abstract long com.ss.bytertc.engine.RTCVideo.takeLocalSnapshot(
    StreamIndex streamIndex,
    ISnapshotResultCallback callback)
```
截取本地视频画面

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamIndex | **StreamIndex** | 截图的视频流的属性，参看 [StreamIndex](Android-keytype.md#streamindex-2)。 |
| callback | **ISnapshotResultCallback** | 本地截图的回调。参看 [ISnapshotResultCallback](Android-callback.md#isnapshotresultcallback)。 |

**返回值**
本地截图任务的编号，从 `1` 开始递增。


**注意**

+ 对截取的画面，包含本地视频处理的全部效果，包含旋转，镜像，美颜等。
+ 不管采用 SDK 内部采集，还是自定义采集，都可以进行截图。


<span id="RTCVideo-takeremotesnapshot"></span>
### takeRemoteSnapshot
```java
public abstract long com.ss.bytertc.engine.RTCVideo.takeRemoteSnapshot(
    RemoteStreamKey streamKey,
    ISnapshotResultCallback callback)
```
截取远端视频画面

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamKey | **RemoteStreamKey** | 截图的视频流，参看 [RemoteStreamKey](Android-keytype.md#remotestreamkey)。 |
| callback | **ISnapshotResultCallback** | 参看 [ISnapshotResultCallback](Android-callback.md#isnapshotresultcallback)。 |

**返回值**
远端截图任务的编号，从 `1` 开始递增。


<span id="RTCVideo-startcloudproxy"></span>
### startCloudProxy
```java
public abstract void com.ss.bytertc.engine.RTCVideo.startCloudProxy(
    List<CloudProxyInfo> cloudProxiesInfo)
```
开启云代理

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| cloudProxiesInfo | **List<CloudProxyInfo>** | 云代理服务器信息列表。参看 [CloudProxyInfo](Android-keytype.md#cloudproxyinfo)。 |


**注意**

+ 在加入房间前调用此接口  
+ 在开启云代理后，进行通话前网络探测 
+ 开启云代理后，并成功链接云代理服务器后，会收到 [onCloudProxyConnected](Android-callback.md#IRTCVideoEventHandler-oncloudproxyconnected)。
+ 要关闭云代理，调用 [stopCloudProxy](#RTCVideo-stopcloudproxy)。


<span id="RTCVideo-stopcloudproxy"></span>
### stopCloudProxy
```java
public abstract void com.ss.bytertc.engine.RTCVideo.stopCloudProxy()
```
关闭云代理


**注意**
要开启云代理，调用 [startCloudProxy](#RTCVideo-startcloudproxy)。

<span id="RTCVideo-getsingscoringmanager"></span>
### getSingScoringManager
```java
public abstract ISingScoringManager com.ss.bytertc.engine.RTCVideo.getSingScoringManager()
```
创建 K 歌评分管理接口。

**返回值**
K 歌评分管理接口，参看 [ISingScoringManager](#isingscoringmanager)。


<span id="RTCVideo-getnetworktimeinfo"></span>
### getNetworkTimeInfo
```java
public abstract NetworkTimeInfo com.ss.bytertc.engine.RTCVideo.getNetworkTimeInfo()
```
通过 NTP 协议，获取网络时间。

**返回值**
网络时间。参看 [NetworkTimeInfo](Android-keytype.md#networktimeinfo)。


**注意**

+ 第一次调用此接口会启动网络时间同步功能，并返回 `0`。同步完成后，会收到 [onNetworkTimeSynchronized](Android-callback.md#IRTCVideoEventHandler-onnetworktimesynchronized)，此后，再次调用此 API，即可获取准确的网络时间。
+ 在合唱场景下，合唱参与者应在相同的网络时间播放背景音乐。


<span id="RTCVideo-getktvmanager"></span>
### getKTVManager
```java
public abstract KTVManager com.ss.bytertc.engine.RTCVideo.getKTVManager()
```
创建 KTV 管理接口。

**返回值**
KTV 管理接口，参看 [KTVManager](#ktvmanager)。


<span id="RTCVideo-starthardwareechodetection"></span>
### startHardwareEchoDetection
```java
public abstract int com.ss.bytertc.engine.RTCVideo.startHardwareEchoDetection(
    String test_audio_file_path)
```
开启通话前回声检测

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| test_audio_file_path | **String** | 用于回声检测的音频文件的绝对路径，路径字符串使用 UTF-8 编码格式，支持以下音频格式: mp3，aac，m4a，3gp，wav。<br/>音频文件不为静音文件，推荐时长为 10 ～ 20 秒。 |

**返回值**
方法调用结果：  

+ 0: 成功。
+ -1：失败。上一次检测未结束，请先调用 [stopHardwareEchoDetection](#RTCVideo-stophardwareechodetection) 停止检测 后重新调用本接口。
+ -2：失败。路径不合法或音频文件格式不支持。


**注意**

+ 只有当 [ChannelProfile](Android-keytype.md#channelprofile) 为 `CHANNEL_PROFIEL_MEETING` 和 `CHANNEL_PROFILE_MEETING_ROOM` 时支持开启本功能。
+ 开启检测前，你需要向用户获取音频设备的使用权限。
+ 开启检测前，请确保音频设备没有被静音，采集和播放音量正常。
+ 调用本接口后监听 onHardwareEchoDetectionResult 获取检测结果。
+ 检测期间，进程将独占音频设备，无法使用其他音频设备测试接口： [startEchoTest](#RTCVideo-startechotest)、[startAudioDeviceRecordTest](#IRTCAudioDeviceManager-startaudiodevicerecordtest) 或 [startAudioPlaybackDeviceTest](#IRTCAudioDeviceManager-startaudioplaybackdevicetest)。 
+ 调用 [stopHardwareEchoDetection](#RTCVideo-stophardwareechodetection) 停止检测，释放对音频设备的占用。


<span id="RTCVideo-stophardwareechodetection"></span>
### stopHardwareEchoDetection
```java
public abstract int com.ss.bytertc.engine.RTCVideo.stopHardwareEchoDetection()
```
停止通话前回声检测

**返回值**
方法调用结果：  

+ 0: 成功。
+ -1：失败。


**注意**

+ 关于开启通话前回声检测，参看 [startHardwareEchoDetection](#RTCVideo-starthardwareechodetection) 。
+ 建议在收到 [onHardwareEchoDetectionResult](Android-callback.md#IRTCVideoEventHandler-onhardwareechodetectionresult) 通知的检测结果后，调用本接口停止检测。
+ 在用户进入房间前结束回声检测，释放对音频设备的占用，以免影响正常通话。


<span id="RTCVideo-setcellularenhancement"></span>
### setCellularEnhancement
```java
public abstract void com.ss.bytertc.engine.RTCVideo.setCellularEnhancement(
    MediaTypeEnhancementConfig config)
```
启用蜂窝网络辅助增强，改善通话质量。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| config | **MediaTypeEnhancementConfig** | 参看 [MediaTypeEnhancementConfig](Android-keytype.md#mediatypeenhancementconfig)。 |


**注意**
此功能默认不开启。

<span id="RTCVideo-setlocalproxy"></span>
### setLocalProxy
```java
public abstract int com.ss.bytertc.engine.RTCVideo.setLocalProxy(
    List<LocalProxyConfiguration> configurations)
```
设置本地代理。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| configurations | **List<LocalProxyConfiguration>** | 本地代理配置参数。参看 [LocalProxyConfiguration](Android-keytype.md#localproxyconfiguration)。 <br/>你可以根据自己的需要选择同时设置 Http 隧道 和 Socks5 两类代理，或者单独设置其中一类代理。如果你同时设置了 Http 隧道 和 Socks5 两类代理，此时，媒体和信令采用 Socks5 代理， Http 请求采用 Http 隧道代理；如果只设置 Http 隧道 或 Socks5 一类代理，媒体、信令和 Http 请求均采用已设置的代理。 <br/>调用此接口设置本地代理后，若想清空当前已有的代理设置，可再次调用此接口，选择不设置任何代理即可清空。 |


**注意**

+ 该方法需要在进房前调用。
+ 调用该方法设置本地代理后，SDK 会触发 [onLocalProxyStateChanged](Android-callback.md#IRTCVideoEventHandler-onlocalproxystatechanged) ，返回代理连接的状态。 


# IAudioMixingManager
```java
public abstract class com.ss.bytertc.engine.audio.IAudioMixingManager
```

混音管理类


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **abstract void** | [startAudioMixing](#IAudioMixingManager-startaudiomixing) |
| **abstract void** | [stopAudioMixing](#IAudioMixingManager-stopaudiomixing) |
| **abstract void** | [stopAllAudioMixing](#IAudioMixingManager-stopallaudiomixing) |
| **abstract void** | [pauseAudioMixing](#IAudioMixingManager-pauseaudiomixing) |
| **abstract void** | [pauseAllAudioMixing](#IAudioMixingManager-pauseallaudiomixing) |
| **abstract void** | [resumeAudioMixing](#IAudioMixingManager-resumeaudiomixing) |
| **abstract void** | [resumeAllAudioMixing](#IAudioMixingManager-resumeallaudiomixing) |
| **abstract void** | [preloadAudioMixing](#IAudioMixingManager-preloadaudiomixing) |
| **abstract void** | [unloadAudioMixing](#IAudioMixingManager-unloadaudiomixing) |
| **abstract void** | [setAllAudioMixingVolume](#IAudioMixingManager-setallaudiomixingvolume) |
| **abstract void** | [setAudioMixingVolume](#IAudioMixingManager-setaudiomixingvolume) |
| **abstract int** | [getAudioMixingDuration](#IAudioMixingManager-getaudiomixingduration) |
| **abstract int** | [getAudioMixingCurrentPosition](#IAudioMixingManager-getaudiomixingcurrentposition) |
| **abstract void** | [setAudioMixingPosition](#IAudioMixingManager-setaudiomixingposition) |
| **abstract int** | [getAudioMixingPlaybackDuration](#IAudioMixingManager-getaudiomixingplaybackduration) |
| **abstract void** | [setAudioMixingDualMonoMode](#IAudioMixingManager-setaudiomixingdualmonomode) |
| **abstract void** | [setAudioMixingPitch](#IAudioMixingManager-setaudiomixingpitch) |
| **abstract int** | [setAudioMixingPlaybackSpeed](#IAudioMixingManager-setaudiomixingplaybackspeed) |
| **abstract void** | [setAudioMixingLoudness](#IAudioMixingManager-setaudiomixingloudness) |
| **abstract void** | [setAudioMixingProgressInterval](#IAudioMixingManager-setaudiomixingprogressinterval) |
| **abstract void** | [enableAudioMixingFrame](#IAudioMixingManager-enableaudiomixingframe) |
| **abstract void** | [disableAudioMixingFrame](#IAudioMixingManager-disableaudiomixingframe) |
| **abstract int** | [pushAudioMixingFrame](#IAudioMixingManager-pushaudiomixingframe) |
| **abstract int** | [getAudioTrackCount](#IAudioMixingManager-getaudiotrackcount) |
| **abstract void** | [selectAudioTrack](#IAudioMixingManager-selectaudiotrack) |
| **abstract void** | [registerAudioFileFrameObserver](#IAudioMixingManager-registeraudiofileframeobserver) |


## 函数说明
<span id="IAudioMixingManager-startaudiomixing"></span>
### startAudioMixing
```java
public abstract void com.ss.bytertc.engine.audio.IAudioMixingManager.startAudioMixing(
    int mixId,
    String filePath,
    AudioMixingConfig config)
```
开始播放音频文件。<br>
可以通过传入不同的 ID 和 filepath 多次调用本方法，以实现同时播放多个混音文件，实现混音叠加。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mixId | **int** | 混音 ID。用于标识混音，请保证混音 ID 唯一性。  <br/>如果使用相同的 ID 重复调用本方法后，前一次混音会停止，后一次混音开始，SDK 会使用 `onAudioMixingStateChanged` 回调通知前一次混音已停止。 |
| filePath | **String** | 用于混音文件路径。<br/>支持在线文件的 URL、本地文件的 URI、本地文件的绝对路径或以 `/assets/` 开头的本地文件路径。对于在线文件的 URL，仅支持 https 协议。<br/>推荐的音频文件采样率：8KHz、16KHz、22.05KHz、44.1KHz、48KHz。<br/>不同平台支持的本地音频文件格式:<br/><table><br/><tr><th></th><th>mp3</th><th>mp4</th><th>aac</th><th>m4a</th><th>3gp</th><th>wav</th><th>ogg</th><th>ts</th><th>wma</th></tr><br/><tr><td>Android</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td></tr><br/><tr><td>iOS/macOS</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td><td></td></tr><br/><tr><td>Windows</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td>Y</td><td>Y</td></tr><br/><tr><td>Linux</td><td></td><td></td><td></td><td></td><td></td><td>Y</td><td></td><td></td><td></td></tr><br/></table><br/>不同平台支持的在线音频文件格式:<br/><table><br/><tr><th></th><th>mp3</th><th>mp4</th><th>aac</th><th>m4a</th><th>3gp</th><th>wav</th><th>ogg</th><th>ts</th><th>wma</th></tr><br/><tr><td>Android</td><td>Y</td><td></td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td><td></td></tr><br/><tr><td>iOS/macOS</td><td>Y</td><td></td><td>Y</td><td>Y</td><td></td><td>Y</td><td></td><td></td><td></td></tr><br/><tr><td>Windows</td><td>Y</td><td></td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td>Y</td><td>Y</td></tr><br/></table> |
| config | **AudioMixingConfig** | 混音配置  <br/>可以设置混音的播放次数、是否本地播放混音、以及是否将混音发送至远端，详见 [AudioMixingConfig](Android-keytype.md#audiomixingconfig) |


**注意**

+ 如果已经通过 [preloadAudioMixing](#IAudioMixingManager-preloadaudiomixing) 将文件加载至内存，确保此处的 ID 与 [preloadAudioMixing](#IAudioMixingManager-preloadaudiomixing) 设置的 ID 相同。  
+ 调用本方法播放音频文件后，关于当前的混音状态，会收到回调 `onAudioMixingStateChanged`。  
+ 开始播放音频文件后，可以调用 [stopAudioMixing](#IAudioMixingManager-stopaudiomixing) 方法停止播放音频文件。  
+ 本方法的混音数据来源于外部文件，而 [enableAudioMixingFrame](#IAudioMixingManager-enableaudiomixingframe) 的混音数据来源于外部缓存且音频格式为 PCM，这两种混音方式可以共存。


<span id="IAudioMixingManager-stopaudiomixing"></span>
### stopAudioMixing
```java
public abstract void com.ss.bytertc.engine.audio.IAudioMixingManager.stopAudioMixing(
    int mixId)
```
停止播放音频文件及混音。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mixId | **int** | 混音 ID |


**注意**

+ 调用 [startAudioMixing](#IAudioMixingManager-startaudiomixing) 方法开始播放音频文件后，可以调用本方法停止播放音频文件。  
+ 调用本方法停止播放音频文件后，关于当前的混音状态，会收到回调 `onAudioMixingStateChanged`。  
+ 调用本方法停止播放音频文件后，该音频文件会被自动卸载。


<span id="IAudioMixingManager-stopallaudiomixing"></span>
### stopAllAudioMixing
```java
public abstract void com.ss.bytertc.engine.audio.IAudioMixingManager.stopAllAudioMixing()
```
停止播放所有音频文件及混音。


**注意**

+ 调用 [startAudioMixing](#IAudioMixingManager-startaudiomixing) 方法开始播放音频文件及混音后，可以调用本方法停止播放所有音频文件及混音。  
+ 调用本方法停止播放所有音频文件及混音后，会收到 `onAusdioMixingStateChanged` 回调，通知已停止播放和混音。  
+ 调用本方法停止播放所有音频文件及混音后，该音频文件会被自动卸载。


<span id="IAudioMixingManager-pauseaudiomixing"></span>
### pauseAudioMixing
```java
public abstract void com.ss.bytertc.engine.audio.IAudioMixingManager.pauseAudioMixing(
    int mixId)
```
暂停播放音频文件及混音。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mixId | **int** | 混音 ID |


**注意**

+ 调用 [startAudioMixing](#IAudioMixingManager-startaudiomixing) 方法开始播放音频文件后，可以通过调用本方法暂停播放音频文件。  
+ 调用本方法暂停播放音频文件后，可调用 [resumeAudioMixing](#IAudioMixingManager-resumeaudiomixing) 方法恢复播放及混音。  
+ 调用本方法暂停播放音频文件后，关于当前的混音状态，会收到回调 `onAudioMixingStateChanged`。


<span id="IAudioMixingManager-pauseallaudiomixing"></span>
### pauseAllAudioMixing
```java
public abstract void com.ss.bytertc.engine.audio.IAudioMixingManager.pauseAllAudioMixing()
```
暂停播放所有音频文件及混音。


**注意**

+ 调用 [startAudioMixing](#IAudioMixingManager-startaudiomixing) 方法开始播放音频文件及混音后，可以通过调用本方法暂停播放所有音频文件及混音。  
+ 调用本方法暂停播放所有音频文件及混音后，可调用 [resumeAllAudioMixing](#IAudioMixingManager-resumeallaudiomixing) 方法恢复所有播放及混音。  
+ 调用本方法暂停播放所有音频文件及混音后，会收到 `onAudioMixingStateChanged` 回调，通知已暂停播放和混音。


<span id="IAudioMixingManager-resumeaudiomixing"></span>
### resumeAudioMixing
```java
public abstract void com.ss.bytertc.engine.audio.IAudioMixingManager.resumeAudioMixing(
    int mixId)
```
恢复播放音频文件及混音。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mixId | **int** | 混音 ID |


**注意**

+ 调用 [pauseAudioMixing](#IAudioMixingManager-pauseaudiomixing) 方法暂停播放音频文件后，可以通过调用本方法恢复播放及混音。  
+ 调用本方法恢复播放音频文件后，关于当前的混音状态，会收到回调 `onAudioMixingStateChanged`。


<span id="IAudioMixingManager-resumeallaudiomixing"></span>
### resumeAllAudioMixing
```java
public abstract void com.ss.bytertc.engine.audio.IAudioMixingManager.resumeAllAudioMixing()
```
恢复播放所有音频文件及混音。


**注意**

+ 调用 [pauseAllAudioMixing](#IAudioMixingManager-pauseallaudiomixing) 方法暂停所有正在播放音频文件及混音后，可以通过调用本方法恢复播放及混音。  
+ 调用本方法恢复播放所有音频文件及混音后，会收到 `onAudioMixingStateChanged` 回调，通知已恢复播放和混音。


<span id="IAudioMixingManager-preloadaudiomixing"></span>
### preloadAudioMixing
```java
public abstract void com.ss.bytertc.engine.audio.IAudioMixingManager.preloadAudioMixing(
    int mixId,
    String filePath)
```
预加载指定音乐文件到内存中，以避免频繁播放同一文件时的重复加载，减少 CPU 占用。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mixId | **int** | 混音 ID。用于标识混音，请保证混音 ID 唯一性。  <br/>如果使用相同的 ID 重复调用本方法，后一次会覆盖前一次。  <br/>如果先调用 [startAudioMixing](#IAudioMixingManager-startaudiomixing)，再使用相同的 ID 调用本方法 ，会先回调 `onAudioMixingStateChanged`  上一个混音停止，然后加载后一个混音。  <br/>调用本方法预加载 A.mp3 后，如果需要使用相同的 ID 调用 [startAudioMixing](#IAudioMixingManager-startaudiomixing) 播放 B.mp3，请先调用 [unloadAudioMixing](#IAudioMixingManager-unloadaudiomixing) 卸载 A.mp3 ，否则会报错 AUDIO_MIXING_ERROR_LOAD_CONFLICT。 |
| filePath | **String** | 混音文件路径。<br/>支持本地文件的 URI、本地文件的绝对路径或以 `/assets/` 开头的本地文件路径。预加载的文件长度不得超过 20s。<br/>不同平台支持的音频文件格式:<br/><table><br/><tr><th></th><th>mp3</th><th>mp4</th><th>aac</th><th>m4a</th><th>3gp</th><th>wav</th><th>ogg</th><th>ts</th><th>wma</th></tr><br/><tr><td>Android</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td></tr><br/><tr><td>iOS</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td><td></td></tr><br/><tr><td>Windows</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td>Y</td><td>Y</td></tr><br/></table> |


**注意**

+ 本方法只是预加载指定音频文件，只有调用 [startAudioMixing](#IAudioMixingManager-startaudiomixing) 方法才开始播放指定音频文件。 
+ 调用本方法预加载音频文件后，关于当前的混音状态，会收到回调 `onAudioMixingStateChanged`。  
+ 调用本方法预加载的指定音频文件可以通过 [unloadAudioMixing](#IAudioMixingManager-unloadaudiomixing) 卸载。


<span id="IAudioMixingManager-unloadaudiomixing"></span>
### unloadAudioMixing
```java
public abstract void com.ss.bytertc.engine.audio.IAudioMixingManager.unloadAudioMixing(
    int mixId)
```
卸载指定音乐文件。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mixId | **int** | 混音 ID |


**注意**
调用本方法卸载该文件后，关于当前的混音状态，会收到回调 `onAudioMixingStateChanged`。

<span id="IAudioMixingManager-setallaudiomixingvolume"></span>
### setAllAudioMixingVolume
```java
public abstract void com.ss.bytertc.engine.audio.IAudioMixingManager.setAllAudioMixingVolume(
    int volume,
    AudioMixingType type)
```
设置默认的混音音量大小，包括音频文件混音和 PCM 混音。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| volume | **int** | 混音音量相对原音量的比值。范围为 `[0, 400]`，建议范围是 `[0, 100]`。  <br/>• 0：静音  <br/>• 100：原始音量（默认值）  <br/>• 400: 最大可调音量 (自带溢出保护) |
| type | **AudioMixingType** | 混音类型。是否本地播放、以及是否发送到远端，详见 [AudioMixingType](Android-keytype.md#audiomixingtype)。 |


**注意**
该接口的优先级低于 [setAudioMixingVolume](#IAudioMixingManager-setaudiomixingvolume)，即通过 [setAudioMixingVolume](#IAudioMixingManager-setaudiomixingvolume) 单独设置了音量的混音 ID，不受该接口设置的影响。

<span id="IAudioMixingManager-setaudiomixingvolume"></span>
### setAudioMixingVolume
```java
public abstract void com.ss.bytertc.engine.audio.IAudioMixingManager.setAudioMixingVolume(
    int mixId,
    int volume,
    AudioMixingType type)
```
调节指定混音的音量大小，包括音频文件混音和 PCM 混音。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mixId | **int** | 需调节音量的混音 ID |
| volume | **int** | 混音音量相对原音量的比值。范围为 `[0, 400]`，建议范围是 `[0, 100]`。  <br/>• 0：静音  <br/>• 100：原始音量（默认值）  <br/>• 400: 最大可调音量 (自带溢出保护) |
| type | **AudioMixingType** | 混音类型。是否本地播放、以及是否发送到远端，详见 [AudioMixingType](Android-keytype.md#audiomixingtype)。 |


**注意**
该方法仅对指定混音 ID 生效，若想调节全部混音文件播放音量，则需调用 [setAllAudioMixingVolume](#IAudioMixingManager-setallaudiomixingvolume)。

<span id="IAudioMixingManager-getaudiomixingduration"></span>
### getAudioMixingDuration
```java
public abstract int com.ss.bytertc.engine.audio.IAudioMixingManager.getAudioMixingDuration(
    int mixId)
```
获取音频文件时长。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mixId | **int** | 混音 ID |

**返回值**

+ \>0: 成功, 音频文件时长，单位为毫秒。  
+ < 0: 失败


**注意**
调用本方法获取音频文件时长前，需要先调用 [preloadAudioMixing](#IAudioMixingManager-preloadaudiomixing) 或 [startAudioMixing](#IAudioMixingManager-startaudiomixing)。

<span id="IAudioMixingManager-getaudiomixingcurrentposition"></span>
### getAudioMixingCurrentPosition
```java
public abstract int com.ss.bytertc.engine.audio.IAudioMixingManager.getAudioMixingCurrentPosition(
    int mixId)
```
获取音频文件播放进度。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mixId | **int** | 混音 ID |

**返回值**

+ \>0: 成功, 音频文件播放进度，单位为毫秒。  
+ < 0: 失败


**注意**
调用本方法获取音频文件播放进度前，需要先调用 [startAudioMixing](#IAudioMixingManager-startaudiomixing) 开始播放音频文件。

<span id="IAudioMixingManager-setaudiomixingposition"></span>
### setAudioMixingPosition
```java
public abstract void com.ss.bytertc.engine.audio.IAudioMixingManager.setAudioMixingPosition(
    int mixId,
    int position)
```
设置音频文件的起始播放位置。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mixId | **int** | 混音 ID |
| position | **int** | 音频文件起始播放位置，单位为毫秒。  <br/>你可以通过 [getAudioMixingDuration](#IAudioMixingManager-getaudiomixingduration) 获取音频文件总时长，position 的值应小于音频文件总时长。 |


**注意**
在播放在线文件时，调用此接口可能造成播放延迟的现象。

<span id="IAudioMixingManager-getaudiomixingplaybackduration"></span>
### getAudioMixingPlaybackDuration
```java
public abstract int com.ss.bytertc.engine.audio.IAudioMixingManager.getAudioMixingPlaybackDuration(
    int mixId)
```
获取混音音频文件的实际播放时长（单位：毫秒）。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mixId | **int** | 混音ID。 |

**返回值**

+ \>0: 实际播放时长。 
+ < 0: 失败。


**注意**

+ 实际播放时长指的是歌曲不受停止、跳转、倍速、卡顿影响的播放时长。例如，若歌曲正常播放到 1:30 时停止播放 30s 或跳转进度到 2:00, 随后继续正常播放 2分钟，则实际播放时长为 3分30秒。  
+ 调用本接口前，需要先调用 [startAudioMixing](#IAudioMixingManager-startaudiomixing) 开始播放指定音频文件。


<span id="IAudioMixingManager-setaudiomixingdualmonomode"></span>
### setAudioMixingDualMonoMode
```java
public abstract void com.ss.bytertc.engine.audio.IAudioMixingManager.setAudioMixingDualMonoMode(
    int mixId,
    AudioMixingDualMonoMode mode)
```
设置当前音频文件的声道模式

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mixId | **int** | 混音 ID |
| mode | **AudioMixingDualMonoMode** | 声道模式。默认的声道模式和源文件一致，详见 [AudioMixingDualMonoMode](Android-keytype.md#audiomixingdualmonomode)。 |


**注意**

+ 调用本方法设置音频文件的声道模式前，需要先调用 [startAudioMixing](#IAudioMixingManager-startaudiomixing) 开始播放音频文件。
+ 此方法对 [enableAudioMixingFrame](#IAudioMixingManager-enableaudiomixingframe) 播放的音乐无效。


<span id="IAudioMixingManager-setaudiomixingpitch"></span>
### setAudioMixingPitch
```java
public abstract void com.ss.bytertc.engine.audio.IAudioMixingManager.setAudioMixingPitch(
    int mixId,
    int pitch)
```
开启本地播放音乐文件变调功能，多用于 K 歌场景。  <br>
使用该方法，你可以对本地播放音乐文件的音调进行升调或降调等调整。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mixId | **int** | 混音 ID |
| pitch | **int** | 相对于音乐文件原始音调的升高/降低值，取值范围[-12，12]，默认值为 0，即不做调整。  <br/>取值范围内每相邻两个值的音高距离相差半音，正值表示升调，负值表示降调，设置的绝对值越大表示音调升高或降低越多。  <br/>超出取值范围则设置失败，并且会触发 `onAudioMixingStateChanged` 回调，提示 [AudioMixingState](Android-keytype.md#audiomixingstate) 状态为 `AUDIO_MIXING_STATE_FAILED` 混音播放失败，[AudioMixingError](Android-keytype.md#audiomixingerror) 错误码为 `AUDIO_MIXING_ERROR_ID_TYPE_INVALID_PITCH` 设置混音文件音调不合法。 |


**注意**
本方法需要在调用 [startAudioMixing](#IAudioMixingManager-startaudiomixing) 开始播放音频文件后、调用 [stopAudioMixing](#IAudioMixingManager-stopaudiomixing) 停止播放音频文件前使用，否则会触发 `onAudioMixingStateChanged` 回调报错

<span id="IAudioMixingManager-setaudiomixingplaybackspeed"></span>
### setAudioMixingPlaybackSpeed
```java
public abstract int com.ss.bytertc.engine.audio.IAudioMixingManager.setAudioMixingPlaybackSpeed(
    int mixId,
    int speed)
```
设置混音时音频文件的播放速度

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mixId | **int** | 混音 ID |
| speed | **int** | 播放速度与原始文件速度的比例，单位：%，取值范围为 [50,200]，默认值为 100。  <br/>超出取值范围则设置失败，你会收到 `onAudioMixingStateChanged` 回调，提示 [AudioMixingState](Android-keytype.md#audiomixingstate) 状态为 `AUDIO_MIXING_STATE_FAILED` 混音播放失败，[AudioMixingError](Android-keytype.md#audiomixingerror) 错误码为 `AUDIO_MIXING_ERROR_INVALID_PLAYBACK_SPEED` 设置混音文件的播放速度不合法。 |


**注意**

+ 暂不支持对 PCM 音频数据进行变速调整。  
+ 你需要在调用 [startAudioMixing](#IAudioMixingManager-startaudiomixing) 开始混音，并且收到`onAudioMixingStateChanged` 回调提示 [AudioMixingState](Android-keytype.md#audiomixingstate) 状态为 `AUDIO_MIXING_STATE_PLAYING`，[AudioMixingError](Android-keytype.md#audiomixingerror) 错误码为 `AUDIO_MIXING_ERROR_OK` 之后调用该方法。  
+ 在 [stopAudioMixing](#IAudioMixingManager-stopaudiomixing) 停止混音或 [unloadAudioMixing](#IAudioMixingManager-unloadaudiomixing) 卸载音频文件后调用该 API，会收到状态为 `AUDIO_MIXING_STATE_FAILED` 错误码为 `AUDIO_MIXING_ERROR_ID_NOT_FOUND` 的 `onAudioMixingStateChanged` 回调。


<span id="IAudioMixingManager-setaudiomixingloudness"></span>
### setAudioMixingLoudness
```java
public abstract void com.ss.bytertc.engine.audio.IAudioMixingManager.setAudioMixingLoudness(
    int mixId,
    float loudness)
```
如果你需要使用 `enableVocalInstrumentBalance` 对混音音频文件/PCM 音频数据进行音量调整，你必须通过此接口传入其原始响度。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mixId | **int** | 混音 ID |
| loudness | **float** | 原始响度，单位：lufs，取值范围为 [-70.0, 0.0]。  <br/>当设置的值小于 -70.0lufs 时，则默认调整为 -70.0lufs，大于 0.0lufs 时，则不对该响度做音均衡处理。默认值为 1.0lufs，即不做处理。 |


**注意**
建议在 [startAudioMixing](#IAudioMixingManager-startaudiomixing) 开始播放音频文件之前调用该接口，以免播放过程中的音量突变导致听感体验下降。

<span id="IAudioMixingManager-setaudiomixingprogressinterval"></span>
### setAudioMixingProgressInterval
```java
public abstract void com.ss.bytertc.engine.audio.IAudioMixingManager.setAudioMixingProgressInterval(
    int mixId,
    long interval)
```
设置混音时音频文件播放进度回调的间隔

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mixId | **int** | 混音 ID  <br/>可以通过多次调用本接口传入不同的 ID 对多个 ID 进行间隔设置。 |
| interval | **long** | 音频文件播放进度回调的时间间隔，单位毫秒。  <br/>• interval 的值为大于 0 的 10 的倍数，当设置的值不能被 10 整除时，则默认向上取整 10，如设为 52ms 时会默认调整为 60ms。设置完成后 SDK 将会按照设置的时间间隔触发 `onAudioMixingPlayingProgress` 回调。  <br/>• interval 的值小于等于 0 时，不会触发进度回调。 |


**注意**
本方法需要在调用 [startAudioMixing](#IAudioMixingManager-startaudiomixing) 开始播放音频文件后、调用 [stopAudioMixing](#IAudioMixingManager-stopaudiomixing) 停止播放音频文件前使用，否则会触发 `onAudioMixingStateChanged` 回调报错。  若想在音乐文件开始播放前设置播放进度回调间隔，你需调用 [startAudioMixing](#IAudioMixingManager-startaudiomixing) 在 [AudioMixingConfig](Android-keytype.md#audiomixingconfig) 中设置时间间隔，开始播放后可以通过此接口更新回调间隔。


<span id="IAudioMixingManager-enableaudiomixingframe"></span>
### enableAudioMixingFrame
```java
public abstract void com.ss.bytertc.engine.audio.IAudioMixingManager.enableAudioMixingFrame(
    int mixId,
    AudioMixingType type)
```
启动 PCM 音频数据混音。<br>
要实现多个 PCM 音频数据混音，多次调用本方法，并传入不同的 id。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mixId | **int** | 混音 ID。用于标识混音，保证混音 ID 唯一性。  <br/>如果使用相同的 ID 重复调用本方法后，前一次混音会停止，后一次混音开始，会收到 `onAudioMixingStateChanged` 通知前一次混音已停止。 |
| type | **AudioMixingType** | 混音类型。是否本地播放、以及是否发送到远端，详见 [AudioMixingType](Android-keytype.md#audiomixingtype)。 |


**注意**

+ 必须先调用本方法启动 PCM 音频数据混音，随后调用 [pushAudioMixingFrame](#IAudioMixingManager-pushaudiomixingframe) 方法，才会开始混音。 
+ 如要结束 PCM 音频数据混音，使用 [disableAudioMixingFrame](#IAudioMixingManager-disableaudiomixingframe)。


<span id="IAudioMixingManager-disableaudiomixingframe"></span>
### disableAudioMixingFrame
```java
public abstract void com.ss.bytertc.engine.audio.IAudioMixingManager.disableAudioMixingFrame(
    int mixId)
```
关闭 PCM 混音

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mixId | **int** | 混音 ID。 |


<span id="IAudioMixingManager-pushaudiomixingframe"></span>
### pushAudioMixingFrame
```java
public abstract int com.ss.bytertc.engine.audio.IAudioMixingManager.pushAudioMixingFrame(
    int mixId,
    AudioFrame audioFrame)
```
推送 PCM 音频帧数据用于混音

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mixId | **int** | 混音 ID。 |
| audioFrame | **AudioFrame** | 音频帧，详见 [AudioFrame](Android-keytype.md#audioframe)。 |

**返回值**

+ 0: 成功  
+ < 0: 失败


**注意**

+ 调用该方法前，须通过 [enableAudioMixingFrame](#IAudioMixingManager-enableaudiomixingframe) 启动外部音频流混音。  
+ 使用参考建议：首次推送数据，请在应用侧先缓存一定数据（如 200 毫秒），然后一次性推送过去；此后的推送操作定时 10 毫秒一次，并且每次的音频数据量为 10 毫秒数据量。要暂停播放，暂停推送即可。


<span id="IAudioMixingManager-getaudiotrackcount"></span>
### getAudioTrackCount
```java
public abstract int com.ss.bytertc.engine.audio.IAudioMixingManager.getAudioTrackCount(
    int mixId)
```
获取当前音频文件的音轨索引

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mixId | **int** | 混音 ID |

**返回值**
方法调用结果 

+ ≥ 0：成功，返回当前音频文件的音轨索引  
+ < 0：方法调用失败


**注意**

+ 调用本方法获取音频文件的音轨前，需要先调用 [startAudioMixing](#IAudioMixingManager-startaudiomixing) 开始播放音频文件。
+ 此方法对 [enableAudioMixingFrame](#IAudioMixingManager-enableaudiomixingframe) 播放的音频无效。


<span id="IAudioMixingManager-selectaudiotrack"></span>
### selectAudioTrack
```java
public abstract void com.ss.bytertc.engine.audio.IAudioMixingManager.selectAudioTrack(
    int mixId,
    int audioTrackIndex)
```
指定当前音频文件的播放音轨

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mixId | **int** | 混音 ID |
| audioTrackIndex | **int** | 指定的播放音轨  <br/>设置的参数值需要小于或等于 [getAudioTrackCount](#IAudioMixingManager-getaudiotrackcount) 的返回值 |


**注意**

+ 调用本方法设置音频文件的音轨前，需要先调用 [startAudioMixing](#IAudioMixingManager-startaudiomixing) 开始播放音频文件。
+ 此方法对 [enableAudioMixingFrame](#IAudioMixingManager-enableaudiomixingframe) 播放的音乐无效。


<span id="IAudioMixingManager-registeraudiofileframeobserver"></span>
### registerAudioFileFrameObserver
```java
public abstract void com.ss.bytertc.engine.audio.IAudioMixingManager.registerAudioFileFrameObserver(
    IAudioFileFrameObserver observer)
```
注册本地音频文件混音的音频帧观察者。
当本地音频文件混音时，会收到相关回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| observer | **IAudioFileFrameObserver** | 参看 [IAudioFileFrameObserver](Android-callback.md#iaudiofileframeobserver)。 |


# IRangeAudio
```java
public interface com.ss.bytertc.engine.audio.IRangeAudio
```

范围语音接口实例


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **void** | [enableRangeAudio](#IRangeAudio-enablerangeaudio) |
| **int** | [updatePosition](#IRangeAudio-updateposition) |
| **int** | [updateReceiveRange](#IRangeAudio-updatereceiverange) |
| **int** | [setAttenuationModel](#IRangeAudio-setattenuationmodel) |
| **void** | [setNoAttenuationFlags](#IRangeAudio-setnoattenuationflags) |


## 函数说明
<span id="IRangeAudio-enablerangeaudio"></span>
### enableRangeAudio
```java
void com.ss.bytertc.engine.audio.IRangeAudio.enableRangeAudio(
    boolean enable)
```
开启/关闭范围语音功能。  <br>
范围语音是指，在同一 RTC 房间中设定的音频接收距离范围内，本地用户收听到的远端用户音频音量会随着远端用户的靠近/远离而放大/衰减；若远端用户在房间内的位置超出设定范围，则本地用户无法接收其音频。音频接收范围设置参看 [updateReceiveRange](#IRangeAudio-updatereceiverange)。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| enable | **boolean** | 是否开启范围语音功能：  <br/>• true: 开启  <br/>• false: 关闭（默认） |


**注意**
该方法进房前后都可调用，为保证进房后范围语音效果的平滑切换，你需在该方法前先调用 [updatePosition](#IRangeAudio-updateposition) 设置自身位置坐标，然后开启该方法收听范围语音效果。

<span id="IRangeAudio-updateposition"></span>
### updatePosition
```java
int com.ss.bytertc.engine.audio.IRangeAudio.updatePosition(
    Position pos)
```
更新本地用户在房间内空间直角坐标系中的位置坐标。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| pos | **Position** | 三维坐标的值，默认为 [0, 0, 0]，参看 [Position](Android-keytype.md#position-2)。 |

**返回值**
方法调用结果： 

+ 0：成功；  
+ !0：失败。


**注意**

+ 调用该接口更新坐标后，你需调用 [enableRangeAudio](#IRangeAudio-enablerangeaudio) 开启范围语音功能以收听范围语音效果。 


<span id="IRangeAudio-updatereceiverange"></span>
### updateReceiveRange
```java
int com.ss.bytertc.engine.audio.IRangeAudio.updateReceiveRange(
    ReceiveRange range)
```
更新本地用户的音频收听范围。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| range | **ReceiveRange** | 音频收听范围，参看 [ReceiveRange](Android-keytype.md#receiverange)。 |

**返回值**
方法调用结果：  

+ 0：成功；  
+ !0: 失败。


<span id="IRangeAudio-setattenuationmodel"></span>
### setAttenuationModel
```java
int com.ss.bytertc.engine.audio.IRangeAudio.setAttenuationModel(
    AttenuationType type,
    float coefficient)
```
设置范围语音的音量衰减模式。<br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| type | **AttenuationType** | 音量衰减模式。默认为线性衰减。详见 [AttenuationType](Android-keytype.md#attenuationtype)。 |
| coefficient | **float** | 指数衰减模式下的音量衰减系数，默认值为 1。范围 [0.1,100]，推荐设置为 `50`。数值越大，音量的衰减速度越快。 |

**返回值**
调用是否成功

+ `0`:调用成功
+ `-1`:调用失败。原因为在调用 [enableRangeAudio](#IRangeAudio-enablerangeaudio) 开启范围语音前或进房前调用本接口


**注意**
音量衰减范围通过 [updateReceiveRange](#IRangeAudio-updatereceiverange) 进行设置。

<span id="IRangeAudio-setnoattenuationflags"></span>
### setNoAttenuationFlags
```java
void com.ss.bytertc.engine.audio.IRangeAudio.setNoAttenuationFlags(
    List<String> flags)
```
添加标签组，用于标记相互之间通话不衰减的用户组。<br>
在同一个 RTC 房间中，如果多个用户的标签组之间有交集，那么，他们之间互相通话时，通话不衰减。<br>
比如，用户身处多个队伍，队伍成员间通话不衰减。那么，可以为每个队伍绑定专属标签，每个用户的标签组包含用户所属各个队伍的标签。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| flags | **List<String>** | 标签组 |


# ISingScoringManager
```java
public abstract class com.ss.bytertc.engine.audio.ISingScoringManager
```

K 歌评分管理接口。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **abstract int** | [initSingScoring](#ISingScoringManager-initsingscoring) |
| **abstract int** | [setSingScoringConfig](#ISingScoringManager-setsingscoringconfig) |
| **abstract List<StandardPitchInfo>** | [getStandardPitchInfo](#ISingScoringManager-getstandardpitchinfo) |
| **abstract int** | [startSingScoring](#ISingScoringManager-startsingscoring) |
| **abstract int** | [stopSingScoring](#ISingScoringManager-stopsingscoring) |
| **abstract int** | [getLastSentenceScore](#ISingScoringManager-getlastsentencescore) |
| **abstract int** | [getTotalScore](#ISingScoringManager-gettotalscore) |
| **abstract int** | [getAverageScore](#ISingScoringManager-getaveragescore) |


## 函数说明
<span id="ISingScoringManager-initsingscoring"></span>
### initSingScoring
```java
public abstract int com.ss.bytertc.engine.audio.ISingScoringManager.initSingScoring(
    String singScoringAppkey,
    String singAcoringToken,
    ISingScoringEventHandler handler)
```
初始化 K 歌评分。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| singScoringAppkey | **String** | K 歌评分密钥，用于鉴权验证 K 歌功能是否开通。 |
| singAcoringToken | **String** | K 歌评分密钥，用于鉴权验证 K 歌功能是否开通。 |
| handler | **ISingScoringEventHandler** | K 歌评分事件回调类，详见 [ISingScoringEventHandler](Android-callback.md#isingscoringeventhandler)。 |

**返回值**

+ 0：配置成功。
+ -1：接口调用失败。
+ -2：未集成 K 歌评分模块。
+ \>0：其他错误，具体参看[错误码表](https://www.volcengine.com/docs/6489/148198)。


**注意**
输入正确的鉴权信息才可以使用 K 歌评分相关的功能，鉴权方式为离线鉴权，根据包名（bundleID）绑定 Appkey 及 Token，K 歌评分密钥请联系技术支持人员申请。

<span id="ISingScoringManager-setsingscoringconfig"></span>
### setSingScoringConfig
```java
public abstract int com.ss.bytertc.engine.audio.ISingScoringManager.setSingScoringConfig(
    SingScoringConfig config)
```
设置 K 歌评分参数。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| config | **SingScoringConfig** | K 歌评分的各项参数，详见 [SingScoringConfig](Android-keytype.md#singscoringconfig)。 |

**返回值**

+ 0：配置成功。
+ -1：接口调用失败。
+ -2：未集成 K 歌评分模块。
+ \>0：其他错误，具体参看[错误码表](https://www.volcengine.com/docs/6489/148198)。


<span id="ISingScoringManager-getstandardpitchinfo"></span>
### getStandardPitchInfo
```java
public abstract List<StandardPitchInfo> com.ss.bytertc.engine.audio.ISingScoringManager.getStandardPitchInfo(
    String midiFilepath)
```
获取标准音高数据。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| midiFilepath | **String** | 歌曲 midi 文件路径。 |

**返回值**
[StandardPitchInfo](Android-keytype.md#standardpitchinfo) 标准音高数据数组。


**注意**

+ 请保证此接口传入的 midi 文件路径与 [setSingScoringConfig](#ISingScoringManager-setsingscoringconfig) 接口中传入的路径一致。


<span id="ISingScoringManager-startsingscoring"></span>
### startSingScoring
```java
public abstract int com.ss.bytertc.engine.audio.ISingScoringManager.startSingScoring(
    int position,
    int scoringInfoInterval)
```
开始 K 歌评分。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| position | **int** | 开始评分时，音乐的播放进度，单位：ms。 |
| scoringInfoInterval | **int** | 实时回调的时间间隔，单位：ms；默认 50 ms。最低间隔为 20 ms。 |

**返回值**

+ 0：配置成功。
+ -1：接口调用失败。
+ -2：未集成 K 歌评分模块。
+ \>0：其他错误，具体参看[错误码表](https://www.volcengine.com/docs/6489/148198)。


**注意**

+ 在调用 [initSingScoring](#ISingScoringManager-initsingscoring) 初始化 K 歌评分功能后调用该接口。
+ 调用该接口后，将会根据设置的回调时间间隔，收到评分结果 [onCurrentScoringInfo](Android-callback.md#ISingScoringEventHandler-oncurrentscoringinfo) 回调。
+ 如果调用 [startAudioMixing](#IAudioMixingManager-startaudiomixing) 接口播放音频文件，请在收到 [onAudioMixingStateChanged](Android-callback.md#IRTCVideoEventHandler-onaudiomixingstatechanged)(AUDIO_MIXING_STATE_PLAYING(1)) 之后调用此接口。


<span id="ISingScoringManager-stopsingscoring"></span>
### stopSingScoring
```java
public abstract int com.ss.bytertc.engine.audio.ISingScoringManager.stopSingScoring()
```
停止 K 歌评分。

**返回值**

+ 0：成功。
+ <0：失败。


<span id="ISingScoringManager-getlastsentencescore"></span>
### getLastSentenceScore
```java
public abstract int com.ss.bytertc.engine.audio.ISingScoringManager.getLastSentenceScore()
```
获取上一句的演唱评分。调用 [startSingScoring](#ISingScoringManager-startsingscoring) 开始评分后可以调用该接口。

**返回值**

+ <0：获取评分失败。
+ \>=0：上一句歌词的演唱评分。


<span id="ISingScoringManager-gettotalscore"></span>
### getTotalScore
```java
public abstract int com.ss.bytertc.engine.audio.ISingScoringManager.getTotalScore()
```
获取当前演唱总分。调用 [startSingScoring](#ISingScoringManager-startsingscoring) 开始评分后可以调用该接口。

**返回值**

+ <0：获取总分失败。
+ \>=0：当前演唱总分。


<span id="ISingScoringManager-getaveragescore"></span>
### getAverageScore
```java
public abstract int com.ss.bytertc.engine.audio.ISingScoringManager.getAverageScore()
```
获取当前演唱歌曲的平均分。

**返回值**

+ <0：获取平均分失败。
+ \>=0：当前演唱平均分。


# ISpatialAudio
```java
public interface com.ss.bytertc.engine.audio.ISpatialAudio
```

空间音频接口实例


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **void** | [enableSpatialAudio](#ISpatialAudio-enablespatialaudio) |
| **void** | [disableRemoteOrientation](#ISpatialAudio-disableremoteorientation) |
| **int** | [updateSelfPosition](#ISpatialAudio-updateselfposition) |
| **int** | [updateRemotePosition](#ISpatialAudio-updateremoteposition) |
| **int** | [removeRemotePosition](#ISpatialAudio-removeremoteposition) |
| **int** | [removeAllRemotePosition](#ISpatialAudio-removeallremoteposition) |
| **int** | [[deprecated] updatePosition](#ISpatialAudio-updateposition) |
| **int** | [[deprecated] updateSelfOrientation](#ISpatialAudio-updateselforientation) |
| **int** | [[deprecated] updateListenerPosition](#ISpatialAudio-updatelistenerposition) |
| **int** | [[deprecated] updateListenerOrientation](#ISpatialAudio-updatelistenerorientation) |


## 函数说明
<span id="ISpatialAudio-enablespatialaudio"></span>
### enableSpatialAudio
```java
void com.ss.bytertc.engine.audio.ISpatialAudio.enableSpatialAudio(
    boolean enable)
```
开启/关闭空间音频功能。  <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| enable | **boolean** | 是否开启空间音频功能：  <br/>• true：开启  <br/>• false：关闭（默认） |


**注意**
该方法仅开启空间音频功能，你须调用 [updatePosition](#ISpatialAudio-updateposition) 设置自身位置坐标后方可收听空间音频效果。空间音频相关 API 和调用时序详见[空间音频](https://www.volcengine.com/docs/6348/93903)。

<span id="ISpatialAudio-updateposition"></span>
### updatePosition
```java
@Deprecated int com.ss.bytertc.engine.audio.ISpatialAudio.updatePosition(
    Position pos)
```
> Deprecated  since 352.1, will be deleted in 357，use updateSelfPosition instead

更新本地用户发声时，在房间内空间直角坐标系中的位置坐标。  <br>
如果未调用 [updateListenerPosition](#ISpatialAudio-updatelistenerposition) 设定收听位置，默认的收听位置和发声位置一致。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| pos | **Position** | 三维坐标的值，默认为 [0, 0, 0]。参看 [Position](Android-keytype.md#position)。 |

**返回值**

+ 0: 成功；  
+ !0: 失败。  


**注意**
调用该接口更新坐标前，你需调用 [enableSpatialAudio](#ISpatialAudio-enablespatialaudio) 开启空间音频功能。空间音频相关 API 和调用时序详见[空间音频](https://www.volcengine.com/docs/6348/93903)。 

<span id="ISpatialAudio-updateselforientation"></span>
### updateSelfOrientation
```java
@Deprecated int com.ss.bytertc.engine.audio.ISpatialAudio.updateSelfOrientation(
    HumanOrientation orientation)
```
> Deprecated  since 352.1, will be deleted in 357，use updateSelfPosition instead

更新本地用户发声时，在空间音频坐标系下的朝向。  <br>
如果未调用 [updateListenerOrientation](#ISpatialAudio-updatelistenerorientation) 设定收听朝向，默认的收听位朝向和发声朝向一致。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| orientation | **HumanOrientation** | 参看 [HumanOrientation](Android-keytype.md#humanorientation)。 |

**返回值**
方法调用结果：  

+ 0：成功  
+ !0：失败


**注意**

+ 空间音频相关 API 和调用时序详见[空间音频](https://www.volcengine.com/docs/6348/93903)。
+ 调用 [disableRemoteOrientation](#ISpatialAudio-disableremoteorientation) 关闭此效果。


<span id="ISpatialAudio-disableremoteorientation"></span>
### disableRemoteOrientation
```java
void com.ss.bytertc.engine.audio.ISpatialAudio.disableRemoteOrientation()
```
关闭本地用户朝向对本地用户发声效果的影响。<br>
调用此接口后，房间内的其他用户收听本地发声时，声源都在收听者正面。


**注意**

+ 调用本接口关闭朝向功能后，在当前的空间音频实例的生命周期内无法再次开启。
+ 调用此接口不影响本地用户收听朝向的音频效果。要改变本地用户收听朝向，参看 [updateSelfOrientation](#ISpatialAudio-updateselforientation) 和 [updateListenerOrientation](#ISpatialAudio-updatelistenerorientation) 。


<span id="ISpatialAudio-updatelistenerposition"></span>
### updateListenerPosition
```java
@Deprecated int com.ss.bytertc.engine.audio.ISpatialAudio.updateListenerPosition(
    Position pos)
```
> Deprecated  since 352.1, will be deleted in 357，use updateRemotePosition instead

更新在房间内收听音频时的位置。<br>
通过此接口，你可以设定本地发声位置和收听位置不同。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| pos | **Position** | 空间直角坐标系下的坐标值。参看 [Position](Android-keytype.md#position)。<br/>如果未调用此接口设定收听位置，那么默认值为通过 [updatePosition](#ISpatialAudio-updateposition) 设定的值。 |

**返回值**

+ 0: 成功；  
+ !0: 失败。  


**注意**

+ 调用此接口前，你需调用 [enableSpatialAudio](#ISpatialAudio-enablespatialaudio) 开启空间音频功能。
+ 空间音频相关 API 和调用时序详见[空间音频](https://www.volcengine.com/docs/6348/93903)。


<span id="ISpatialAudio-updatelistenerorientation"></span>
### updateListenerOrientation
```java
@Deprecated int com.ss.bytertc.engine.audio.ISpatialAudio.updateListenerOrientation(
    HumanOrientation orientation)
```
> Deprecated  since 352.1, will be deleted in 357，use updateRemotePosition instead

更新在房间内收听音频时的朝向。<br>
通过此接口，你可以设定本地用户的发声朝向和收听朝向不同。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| orientation | **HumanOrientation** | 自身朝向信息，参看 [HumanOrientation](Android-keytype.md#humanorientation)。<br/>如果未调用此接口设定收听朝向，那么默认值为通过 [updateSelfOrientation](#ISpatialAudio-updateselforientation) 设定的值。 |

**返回值**
方法调用结果：  

+ 0：成功  
+ !0：失败


**注意**
空间音频相关 API 和调用时序详见[空间音频](https://www.volcengine.com/docs/6348/93903)。

<span id="ISpatialAudio-updateselfposition"></span>
### updateSelfPosition
```java
int com.ss.bytertc.engine.audio.ISpatialAudio.updateSelfPosition(
    PositionInfo positionInfo)
```
> Available since 3.52.

设置本地用户在自建空间直角坐标系中的收听坐标和收听朝向，以实现本地用户预期的空间音频收听效果。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| positionInfo | **PositionInfo** | 空间音频位置信息。参看 [PositionInfo](Android-keytype.md#positioninfo)。 |

**返回值**

+ 0：成功。  
+ <0：失败。 
+ -2: 失败，原因是校验本地用户的三维朝向信息时，三个向量没有两两垂直。


**注意**
该方法需在进房后调用。调用该接口更新坐标前，你需调用 [enableSpatialAudio](#ISpatialAudio-enablespatialaudio) 开启空间音频功能。空间音频相关 API 和调用时序详见[空间音频](https://www.volcengine.com/docs/6348/93903)。
调用此接口在本地进行的设定对其他用户的空间音频收听效果不会产生任何影响。


<span id="ISpatialAudio-updateremoteposition"></span>
### updateRemotePosition
```java
int com.ss.bytertc.engine.audio.ISpatialAudio.updateRemotePosition(
    String uid,
    PositionInfo positionInfo)
```
> Available since 3.52.

设置房间内某一远端用户在本地用户自建的空间音频坐标系中的发声位置和发声朝向，以实现本地用户预期的空间音频收听效果。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | **String** | 用户 ID |
| positionInfo | **PositionInfo** | 远端用户的空间音频位置信息。参看 [PositionInfo](Android-keytype.md#positioninfo)。 |

**返回值**

+ 0：成功。  
+ <0：失败。 
+ -2: 失败，原因是校验远端用户的三维朝向信息时，三个向量没有两两垂直。


**注意**
该方法需在创建房间后调用。 
调用此接口在本地进行的设定对其他用户的空间音频收听效果不会产生任何影响。


<span id="ISpatialAudio-removeremoteposition"></span>
### removeRemotePosition
```java
int com.ss.bytertc.engine.audio.ISpatialAudio.removeRemotePosition(
    String uid)
```
> Available since 3.52.

移除调用 [updateRemotePosition](#ISpatialAudio-updateremoteposition) 为某一远端用户设置的空间音频效果。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | **String** | 远端用户 ID。 |

**返回值**

+ 0：成功。  
+ <0：失败。


<span id="ISpatialAudio-removeallremoteposition"></span>
### removeAllRemotePosition
```java
int com.ss.bytertc.engine.audio.ISpatialAudio.removeAllRemotePosition()
```
> Available since 3.52.

移除调用 [updateRemotePosition](#ISpatialAudio-updateremoteposition) 为所有远端用户设置的空间音频效果。

**返回值**

+ 0：成功。  
+ <0：失败。


# IVideoEffect
```java
public abstract class com.ss.bytertc.engine.video.IVideoEffect
```

高级视频特效。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **abstract int** | [initCVResource](#IVideoEffect-initcvresource) |
| **abstract int** | [enableVideoEffect](#IVideoEffect-enablevideoeffect) |
| **abstract int** | [disableVideoEffect](#IVideoEffect-disablevideoeffect) |
| **abstract int** | [setEffectNodes](#IVideoEffect-seteffectnodes) |
| **abstract int** | [updateEffectNode](#IVideoEffect-updateeffectnode) |
| **abstract int** | [setColorFilter](#IVideoEffect-setcolorfilter) |
| **abstract int** | [setColorFilterIntensity](#IVideoEffect-setcolorfilterintensity) |
| **abstract int** | [enableVirtualBackground](#IVideoEffect-enablevirtualbackground) |
| **abstract int** | [disableVirtualBackground](#IVideoEffect-disablevirtualbackground) |
| **abstract int** | [enableFaceDetection](#IVideoEffect-enablefacedetection) |
| **abstract int** | [disableFaceDetection](#IVideoEffect-disablefacedetection) |
| **abstract int** | [[deprecated] registerFaceDetectionObserver](#IVideoEffect-registerfacedetectionobserver) |


## 函数说明
<span id="IVideoEffect-initcvresource"></span>
### initCVResource
```java
public abstract int com.ss.bytertc.engine.video.IVideoEffect.initCVResource(
    String license_file,
    String algo_model_dir)
```
检查视频特效证书，设置算法模型路径，并初始化特效模块。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| license_file | **String** | 证书文件的绝对路径，用于鉴权。 |
| algo_model_dir | **String** | 算法模型绝对路径，即存放特效 SDK 所有算法模型的目录。 |

**返回值**

+ 0: 调用成功。
+ –1000: 未集成特效 SDK。
+ –1002: 特效 SDK 版本不兼容。
+ < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。


<span id="IVideoEffect-enablevideoeffect"></span>
### enableVideoEffect
```java
public abstract int com.ss.bytertc.engine.video.IVideoEffect.enableVideoEffect()
```
开启高级美颜、滤镜等视频特效。

**返回值**

+ 0: 调用成功。
+ –1000: 未集成特效 SDK。
+ –1001: 特效 SDK 不支持该功能。
+ –1002: 特效 SDK 版本不兼容。
+ < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。


**注意**

+ 调用本方法前，必须先调用 [initCVResource](#IVideoEffect-initcvresource) 进行初始化。
+ 调用该方法后，特效不直接生效，你还需调用 [setEffectNodes](#IVideoEffect-seteffectnodes) 设置视频特效素材包或调用 [setColorFilter](#IVideoEffect-setcolorfilter) 设置滤镜。
+ 调用 [disableVideoEffect](#IVideoEffect-disablevideoeffect) 关闭视频特效。


<span id="IVideoEffect-disablevideoeffect"></span>
### disableVideoEffect
```java
public abstract int com.ss.bytertc.engine.video.IVideoEffect.disableVideoEffect()
```
关闭视频特效。

**返回值**

+ 0: 调用成功。
+ –1000: 未集成特效 SDK。
+ –1001: 特效 SDK 不支持该功能。
+ –1002: 特效 SDK 版本不兼容。
+ < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。


**注意**
调用 [enableVideoEffect](#IVideoEffect-enablevideoeffect) 开启视频特效。

<span id="IVideoEffect-seteffectnodes"></span>
### setEffectNodes
```java
public abstract int com.ss.bytertc.engine.video.IVideoEffect.setEffectNodes(
    List<String> effect_nodes)
```
设置视频特效素材包。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| effect_nodes | **List<String>** | 特效素材包绝对路径数组。<br/>要取消当前视频特效，将此参数设置为 null。 |

**返回值**

+ 0: 调用成功。
+ –1000: 未集成特效 SDK。
+ –1001: 特效 SDK 不支持该功能。
+ –1002: 特效 SDK 版本不兼容。
+ < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。


**注意**
调用本方法前，必须先调用 [enableVideoEffect](#IVideoEffect-enablevideoeffect)。

<span id="IVideoEffect-updateeffectnode"></span>
### updateEffectNode
```java
public abstract int com.ss.bytertc.engine.video.IVideoEffect.updateEffectNode(
    String effect_node,
    String key,
    float value)
```
设置特效强度。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| effect_node | **String** | 特效素材包绝对路径，参考[素材包结构说明](https://www.volcengine.com/docs/6705/102039)。 |
| key | **String** | 需要设置的素材 key 名称，参考[素材 key 对应说明](https://www.volcengine.com/docs/6705/102041)。 |
| value | **float** | 特效强度值，取值范围 [0,1]，超出范围时设置无效。 |

**返回值**

+ 0: 调用成功。
+ –1000: 未集成特效 SDK。
+ –1001: 特效 SDK 不支持该功能。
+ –1002: 特效 SDK 版本不兼容。
+ < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。


<span id="IVideoEffect-setcolorfilter"></span>
### setColorFilter
```java
public abstract int com.ss.bytertc.engine.video.IVideoEffect.setColorFilter(
    String filter_res)
```
设置颜色滤镜。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| filter_res | **String** | 滤镜资源包绝对路径。 |

**返回值**

+ 0: 调用成功。
+ –1000: 未集成特效 SDK。
+ –1001: 特效 SDK 不支持该功能。
+ –1002: 特效 SDK 版本不兼容。
+ < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。


**注意**
调用 [setColorFilterIntensity](#IVideoEffect-setcolorfilterintensity) 设置已启用颜色滤镜的强度。设置强度为 0 时即关闭颜色滤镜。

<span id="IVideoEffect-setcolorfilterintensity"></span>
### setColorFilterIntensity
```java
public abstract int com.ss.bytertc.engine.video.IVideoEffect.setColorFilterIntensity(
    float intensity)
```
设置已启用颜色滤镜的强度。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| intensity | **float** | 滤镜强度。取值范围 [0,1]，超出范围时设置无效。<br/>当设置滤镜强度为 0 时即关闭颜色滤镜。 |

**返回值**

+ 0: 调用成功。
+ –1000: 未集成特效 SDK。
+ –1001: 特效 SDK 不支持该功能。
+ –1002: 特效 SDK 版本不兼容。
+ < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。


<span id="IVideoEffect-enablevirtualbackground"></span>
### enableVirtualBackground
```java
public abstract int com.ss.bytertc.engine.video.IVideoEffect.enableVirtualBackground(
    String bg_sticker_res,
    VirtualBackgroundSource source)
```
将摄像头采集画面中的人像背景替换为指定图片或纯色背景。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| bg_sticker_res | **String** | 背景贴纸特效素材绝对路径。 |
| source | **VirtualBackgroundSource** | 背景贴纸对象，参看 [VirtualBackgroundSource](Android-keytype.md#virtualbackgroundsource)。 |

**返回值**

+ 0: 调用成功。
+ –1000: 未集成特效 SDK。
+ –1001: 特效 SDK 不支持该功能。
+ –1002: 特效 SDK 版本不兼容。
+ < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。


**注意**

+ 调用本方法前，必须先调用 [initCVResource](#IVideoEffect-initcvresource) 进行初始化。
+ 调用 [disableVirtualBackground](#IVideoEffect-disablevirtualbackground) 关闭虚拟背景。


<span id="IVideoEffect-disablevirtualbackground"></span>
### disableVirtualBackground
```java
public abstract int com.ss.bytertc.engine.video.IVideoEffect.disableVirtualBackground()
```
关闭虚拟背景。

**返回值**

+ 0: 调用成功。
+ –1000: 未集成特效 SDK。
+ –1001: 特效 SDK 不支持该功能。
+ –1002: 特效 SDK 版本不兼容。
+ < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。


**注意**
调用 [enableVirtualBackground](#IVideoEffect-enablevirtualbackground) 开启虚拟背景后，可以调用此接口关闭虚拟背景。

<span id="IVideoEffect-registerfacedetectionobserver"></span>
### registerFaceDetectionObserver
```java
public abstract int com.ss.bytertc.engine.video.IVideoEffect.registerFaceDetectionObserver(
    IFaceDetectionObserver observer,
    int interval_ms)
```
> Deprecated  since 3.50 and will be deleted in 3.55, use [enableFaceDetection](#IVideoEffect-enablefacedetection) and [disableFaceDetection](#IVideoEffect-disablefacedetection) instead.

注册人脸检测结果回调观察者。
注册此观察者后，你会周期性收到 [onFaceDetectResult](Android-callback.md#IFaceDetectionObserver-onfacedetectresult) 回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| observer | **IFaceDetectionObserver** | 人脸检测结果回调观察者，参看 [IFaceDetectionObserver](Android-callback.md#ifacedetectionobserver)。 |
| interval_ms | **int** | 时间间隔，必须大于 0。单位：ms。实际收到回调的时间间隔大于 `interval`，小于 `interval+视频采集帧间隔`。 |

**返回值**

+ 0: 调用成功。
+ –1000: 未集成特效 SDK。
+ –1001: 特效 SDK 不支持该功能。
+ –1002: 特效 SDK 版本不兼容。
+ < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。


<span id="IVideoEffect-enablefacedetection"></span>
### enableFaceDetection
```java
public abstract int com.ss.bytertc.engine.video.IVideoEffect.enableFaceDetection(
    IFaceDetectionObserver observer,
    int interval_ms,
    String face_model_path)
```
开启人脸识别功能，并设置人脸检测结果回调观察者。
此观察者后，你会周期性收到 [onFaceDetectResult](Android-callback.md#IFaceDetectionObserver-onfacedetectresult) 回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| observer | **IFaceDetectionObserver** | 人脸检测结果回调观察者，参看 [IFaceDetectionObserver](Android-callback.md#ifacedetectionobserver)。 |
| interval_ms | **int** | 两次回调之间的最小时间间隔，必须大于 0，单位为毫秒。实际收到回调的时间间隔大于 interval_ms，小于 interval_ms+视频采集帧间隔。 |
| face_model_path | **String** | 人脸检测算法模型文件路径，一般为 ttfacemodel 文件夹中 tt_face_vXXX.model 文件的绝对路径。 |

**返回值**

+ 0: 调用成功。
+ –1000: 未集成特效 SDK。
+ –1001: 特效 SDK 不支持该功能。
+ –1002: 特效 SDK 版本不兼容。
+ -1004: 初始化中，初始化完成后启动此功能。
+ < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。


<span id="IVideoEffect-disablefacedetection"></span>
### disableFaceDetection
```java
public abstract int com.ss.bytertc.engine.video.IVideoEffect.disableFaceDetection()
```
关闭人脸识别功能。

**返回值**

+ 0: 调用成功。
+ –1000: 未集成特效 SDK。
+ –1001: 特效 SDK 不支持该功能。
+ –1002: 特效 SDK 版本不兼容。
+ < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。


# IVideoProcessor
```java
public abstract class com.ss.bytertc.engine.video.IVideoProcessor
```



## 成员函数

| 返回 | 名称 |
| --- | --- |
| **abstract VideoFrame** | [processVideoFrame](#IVideoProcessor-processvideoframe) |
| **void** | [onGLEnvInitiated](#IVideoProcessor-onglenvinitiated) |
| **void** | [onGLEnvRelease](#IVideoProcessor-onglenvrelease) |


## 函数说明
<span id="IVideoProcessor-processvideoframe"></span>
### processVideoFrame
```java
public abstract VideoFrame com.ss.bytertc.engine.video.IVideoProcessor.processVideoFrame(
    VideoFrame frame)
```
获取 RTC SDK 采集得到的视频帧，根据 [registerLocalVideoProcessor](#RTCVideo-registerlocalvideoprocessor) 设置的视频前处理器，进行视频前处理，最终将处理后的视频帧给到 RTC SDK 用于编码传输。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| frame | **VideoFrame** | RTC SDK 采集得到的视频帧，参看 [VideoFrame](Android-keytype.md#videoframe)。 |

**返回值**
经过视频前处理后的视频帧，返回给 RTC SDK 供编码和传输，参看 [VideoFrame](Android-keytype.md#videoframe)。


**注意**

+ 如果你使用此接口所在线程进行视频前处理，你无需设置 OpenGL 环境；如果你选择使用其他线程，必须设置 OpenGL 环境。
+ 使用自定义视频滤镜返回的视频数据，构建返回给 RTC SDK 的视频帧时，根据返回视频数据格式的不同，需要不同的处理：
- 返回的视频数据是纹理格式时，可以使用 [GLTextureVideoFrameBuilder](Android-keytype.md#gltexturevideoframebuilder) 创建返回帧；
- 返回的视频数据是 I420 格式时，可以使用 [CpuBufferVideoFrameBuilder](Android-keytype.md#cpubuffervideoframebuilder) 创建返回帧。
+ 若在构造返回的视频帧时，设置了资源释放回调（详见 [VideoFrame](Android-keytype.md#videoframe) 的构造函数），那么 RTC SDK 会复用该视频帧，所以在回调被调用之前，不要对资源进行操作以避免冲突。
+ 在进行视频前处理前，你需要调用 [registerLocalVideoProcessor](#RTCVideo-registerlocalvideoprocessor) 设置视频前处理器。
+ 如果需要取消视频前处理，可以将视频前处理器设置为 nullptr。


<span id="IVideoProcessor-onglenvinitiated"></span>
### onGLEnvInitiated
```java
public void com.ss.bytertc.engine.video.IVideoProcessor.onGLEnvInitiated()
```
OpenGL 环境创建完成时，收到此回调。


**注意**
当你选择使用 [processVideoFrame](#IVideoProcessor-processvideoframe) 所在线程以外的线程进行视频前处理时，必须设置 OpenGL 环境。环境创建完成时，你会收到此通知，此时，你可以进行一些初始化操作。


<span id="IVideoProcessor-onglenvrelease"></span>
### onGLEnvRelease
```java
public void com.ss.bytertc.engine.video.IVideoProcessor.onGLEnvRelease()
```
OpenGL 环境即将销毁时，收到此回调。此时，你可以释放纹理等资源。


# IRTCAudioDeviceManager
```java
public interface com.ss.bytertc.engine.IRTCAudioDeviceManager
```

IRTCAudioDeviceManager 接口


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **abstract int** | [startAudioPlaybackDeviceTest](#IRTCAudioDeviceManager-startaudioplaybackdevicetest) |
| **abstract int** | [stopAudioPlaybackDeviceTest](#IRTCAudioDeviceManager-stopaudioplaybackdevicetest) |
| **abstract int** | [startAudioDeviceRecordTest](#IRTCAudioDeviceManager-startaudiodevicerecordtest) |
| **abstract int** | [stopAudioDeviceRecordAndPlayTest](#IRTCAudioDeviceManager-stopaudiodevicerecordandplaytest) |
| **abstract int** | [stopAudioDevicePlayTest](#IRTCAudioDeviceManager-stopaudiodeviceplaytest) |


## 函数说明
<span id="IRTCAudioDeviceManager-startaudioplaybackdevicetest"></span>
### startAudioPlaybackDeviceTest
```java
public abstract int com.ss.bytertc.engine.IRTCAudioDeviceManager.startAudioPlaybackDeviceTest(
    String testAudioFilePath,
    int interval)
```
启动音频播放设备检测。测试启动后，循环播放指定的音频文件，同时将通过 `onAudioPlaybackDeviceTestVolume` 回调播放时的音量信息。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| testAudioFilePath | **String** | 指定播放设备检测的音频文件网络地址。支持的格式包括 mp3，aac，m4a，3gp 和 wav。 |
| interval | **int** | 设置 `onAudioPlaybackDeviceTestVolume` 音量回调的时间间隔，推荐设置为 200 毫秒或以上。单位为毫秒。最小值为 10 毫秒。 |

**返回值**
方法调用结果  

+ 0：方法调用成功  
+ < 0：方法调用失败  


**注意**

+ 该方法可在进房前和进房后调用，不可与其它音频设备测试功能同时应用。  
+ 调用 [stopAudioPlaybackDeviceTest](#IRTCAudioDeviceManager-stopaudioplaybackdevicetest) 可以停止测试。


<span id="IRTCAudioDeviceManager-stopaudioplaybackdevicetest"></span>
### stopAudioPlaybackDeviceTest
```java
public abstract int com.ss.bytertc.engine.IRTCAudioDeviceManager.stopAudioPlaybackDeviceTest()
```
停止音频播放测试。

**返回值**
方法调用结果  

+ 0：方法调用成功  
+ < 0：方法调用失败


**注意**
调用 [startAudioPlaybackDeviceTest](#IRTCAudioDeviceManager-startaudioplaybackdevicetest) 后，调用本方法停止测试。

<span id="IRTCAudioDeviceManager-startaudiodevicerecordtest"></span>
### startAudioDeviceRecordTest
```java
public abstract int com.ss.bytertc.engine.IRTCAudioDeviceManager.startAudioDeviceRecordTest(
    int interval)
```
开始音频采集设备和音频播放设备测试。<br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| interval | **int** | 测试中会收到 `enableAudioPropertiesReport` 回调，本参数指定了该周期回调的时间间隔，单位为毫秒。建议设置到大于 200 毫秒。最小不得少于 10 毫秒。 |

**返回值**
方法调用结果  

+ 0：方法调用成功  
+ < 0：方法调用失败  


**注意**

+ 该方法在进房前后均可调用。且不可与其它音频设备测试功能同时应用。  
+ 调用本接口 30 s 后，采集自动停止，并开始播放采集到的声音。录音播放完毕后，设备测试流程自动结束。你也可以在 30 s 内调用 [stopAudioDeviceRecordAndPlayTest](#IRTCAudioDeviceManager-stopaudiodevicerecordandplaytest) 来停止采集并开始播放此前采集到的声音。
+ 调用 [stopAudioDevicePlayTest](#IRTCAudioDeviceManager-stopaudiodeviceplaytest) 可以停止音频设备采集和播放测试。
+ 你不应在测试过程中，调用 `enableAudioPropertiesReport` 注册音量提示回调。
+ 该方法仅在本地进行音频设备测试，不涉及网络连接。  


<span id="IRTCAudioDeviceManager-stopaudiodevicerecordandplaytest"></span>
### stopAudioDeviceRecordAndPlayTest
```java
public abstract int com.ss.bytertc.engine.IRTCAudioDeviceManager.stopAudioDeviceRecordAndPlayTest()
```
停止采集本地音频，并开始播放采集到的声音。录音播放完毕后，设备测试流程结束。<br>
调用 [startAudioDeviceRecordTest](#IRTCAudioDeviceManager-startaudiodevicerecordtest) 30 s 内调用本接口来停止采集并开始播放此前采集到的声音。

**返回值**
方法调用结果  

+ 0：方法调用成功  
+ < 0：方法调用失败  


**注意**
调用本接口开始播放录音后，可以在播放过程中调用 [stopAudioDevicePlayTest](#IRTCAudioDeviceManager-stopaudiodeviceplaytest) 停止播放。

<span id="IRTCAudioDeviceManager-stopaudiodeviceplaytest"></span>
### stopAudioDevicePlayTest
```java
public abstract int com.ss.bytertc.engine.IRTCAudioDeviceManager.stopAudioDevicePlayTest()
```
停止由调用 [startAudioDeviceRecordTest](#IRTCAudioDeviceManager-startaudiodevicerecordtest) 开始的音频播放设备测试。
在音频播放设备测试自动结束前，可调用本接口停止音频采集与播放测试。

**返回值**
方法调用结果  

+ 0：方法调用成功  
+ < 0：方法调用失败


# KTVManager
```java
public abstract class com.ss.bytertc.ktv.KTVManager
```

KTV 管理接口。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **abstract void** | [setKTVManagerEventHandler](#KTVManager-setktvmanagereventhandler) |
| **abstract void** | [setMaxCacheSize](#KTVManager-setmaxcachesize) |
| **abstract void** | [getMusicList](#KTVManager-getmusiclist) |
| **abstract void** | [searchMusic](#KTVManager-searchmusic) |
| **abstract void** | [getHotMusic](#KTVManager-gethotmusic) |
| **abstract void** | [getMusicDetail](#KTVManager-getmusicdetail) |
| **abstract int** | [downloadMusic](#KTVManager-downloadmusic) |
| **abstract int** | [downloadLyric](#KTVManager-downloadlyric) |
| **abstract int** | [downloadMidi](#KTVManager-downloadmidi) |
| **abstract void** | [cancelDownload](#KTVManager-canceldownload) |
| **abstract void** | [clearCache](#KTVManager-clearcache) |
| **abstract KTVPlayer** | [getKTVPlayer](#KTVManager-getktvplayer) |


## 函数说明
<span id="KTVManager-setktvmanagereventhandler"></span>
### setKTVManagerEventHandler
```java
public abstract void com.ss.bytertc.ktv.KTVManager.setKTVManagerEventHandler(
    IKTVManagerEventHandler ktvManagerEventHandler)
```
设置 KTV 回调接口。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| ktvManagerEventHandler | **IKTVManagerEventHandler** | KTV 回调类，参看 [IKTVManagerEventHandler](Android-callback.md#iktvmanagereventhandler)。 |


<span id="KTVManager-setmaxcachesize"></span>
### setMaxCacheSize
```java
public abstract void com.ss.bytertc.ktv.KTVManager.setMaxCacheSize(
    int maxCacheSizeMB)
```
设置歌曲文件最大占用的本地缓存。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| maxCacheSizeMB | **int** | 本地缓存，单位 MB。<br/>设置值小于等于 0 时，使用默认值 1024 MB。 |


<span id="KTVManager-getmusiclist"></span>
### getMusicList
```java
public abstract void com.ss.bytertc.ktv.KTVManager.getMusicList(
    int pageNum,
    int pageSize,
    @NonNull MusicFilterType[] filters)
```
获取歌曲列表。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| pageNum | **int** | 页码，默认从 1 开始。 |
| pageSize | **int** | 每页显示歌曲的最大数量，取值范围 [1,99]。 |
| filters | **@NonNull MusicFilterType[]** | 歌曲过滤方式，参看 [MusicFilterType](Android-keytype.md#musicfiltertype)。多个过滤方式可以按位或组合。 |


**注意**
调用接口后，你会收到 [onMusicListResult](Android-callback.md#IKTVManagerEventHandler-onmusiclistresult) 回调歌曲列表。

<span id="KTVManager-searchmusic"></span>
### searchMusic
```java
public abstract void com.ss.bytertc.ktv.KTVManager.searchMusic(
    @NonNull String keyWord,
    int pageNum,
    int pageSize,
    @NonNull MusicFilterType[] filters)
```
根据关键词搜索歌曲。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| keyWord | **@NonNull String** | 关键词，字符串长度最大为 20 个字符。 |
| pageNum | **int** | 页码，默认从 1 开始。 |
| pageSize | **int** | 每页显示歌曲的最大数量，取值范围 [1,99]。 |
| filters | **@NonNull MusicFilterType[]** | 歌曲过滤方式，参看 [MusicFilterType](Android-keytype.md#musicfiltertype)。多个过滤方式可以按位或组合。 |


**注意**
调用接口后，你会收到 [onSearchMusicResult](Android-callback.md#IKTVManagerEventHandler-onsearchmusicresult) 回调歌曲列表。

<span id="KTVManager-gethotmusic"></span>
### getHotMusic
```java
public abstract void com.ss.bytertc.ktv.KTVManager.getHotMusic(
    @NonNull MusicHotType[] hotTypes,
    @NonNull MusicFilterType[] filters)
```
根据热榜类别获取每个榜单的歌曲列表。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| hotTypes | **@NonNull MusicHotType[]** | 热榜类别，参看 [MusicHotType](Android-keytype.md#musichottype)。多个热榜类别可以按位或组合。 |
| filters | **@NonNull MusicFilterType[]** | 歌曲过滤方式，参看 [MusicFilterType](Android-keytype.md#musicfiltertype)。多个过滤方式可以按位或组合。 |


**注意**
调用接口后，你会收到 [onHotMusicResult](Android-callback.md#IKTVManagerEventHandler-onhotmusicresult) 回调歌曲列表。

<span id="KTVManager-getmusicdetail"></span>
### getMusicDetail
```java
public abstract void com.ss.bytertc.ktv.KTVManager.getMusicDetail(
    @NonNull String musicId)
```
获取音乐详细信息。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| musicId | **@NonNull String** | 音乐 ID。 |


**注意**
调用接口后，你会收到 [onMusicDetailResult](Android-callback.md#IKTVManagerEventHandler-onmusicdetailresult) 回调。

<span id="KTVManager-downloadmusic"></span>
### downloadMusic
```java
public abstract int com.ss.bytertc.ktv.KTVManager.downloadMusic(
    @NonNull String musicId)
```
下载音乐。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| musicId | **@NonNull String** | 音乐 ID。 |

**返回值**
下载任务 ID。


**注意**

+ 若音乐下载成功，你会收到 [onDownloadSuccess](Android-callback.md#IKTVManagerEventHandler-ondownloadsuccess) 回调。
+ 若音乐下载失败，你会收到 [onDownloadFailed](Android-callback.md#IKTVManagerEventHandler-ondownloadfailed) 回调。
+ 音乐下载进度更新时，你会收到 [onDownloadMusicProgress](Android-callback.md#IKTVManagerEventHandler-ondownloadmusicprogress) 回调。


<span id="KTVManager-downloadlyric"></span>
### downloadLyric
```java
public abstract int com.ss.bytertc.ktv.KTVManager.downloadLyric(
    @NonNull String musicId,
    @NonNull DownloadLyricType lyricType)
```
下载歌词。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| musicId | **@NonNull String** | 音乐 ID。 |
| lyricType | **@NonNull DownloadLyricType** | 歌词文件类型，参看 [DownloadLyricType](Android-keytype.md#downloadlyrictype)。 |

**返回值**
下载任务 ID。


**注意**

+ 若歌词下载成功，你会收到 [onDownloadSuccess](Android-callback.md#IKTVManagerEventHandler-ondownloadsuccess) 回调。
+ 若歌词下载失败，你会收到 [onDownloadFailed](Android-callback.md#IKTVManagerEventHandler-ondownloadfailed) 回调。


<span id="KTVManager-downloadmidi"></span>
### downloadMidi
```java
public abstract int com.ss.bytertc.ktv.KTVManager.downloadMidi(
    @NonNull String musicId)
```
下载 MIDI 文件。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| musicId | **@NonNull String** | 音乐 ID。 |

**返回值**
下载任务 ID。


**注意**

+ 若文件下载成功，你会收到 [onDownloadSuccess](Android-callback.md#IKTVManagerEventHandler-ondownloadsuccess) 回调。
+ 若文件下载失败，你会收到 [onDownloadFailed](Android-callback.md#IKTVManagerEventHandler-ondownloadfailed) 回调。


<span id="KTVManager-canceldownload"></span>
### cancelDownload
```java
public abstract void com.ss.bytertc.ktv.KTVManager.cancelDownload(
    int downloadId)
```
取消下载任务。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| downloadId | **int** | 下载任务 ID。 |


<span id="KTVManager-clearcache"></span>
### clearCache
```java
public abstract void com.ss.bytertc.ktv.KTVManager.clearCache()
```
清除当前音乐缓存文件，包括音乐音频和歌词。


<span id="KTVManager-getktvplayer"></span>
### getKTVPlayer
```java
public abstract KTVPlayer com.ss.bytertc.ktv.KTVManager.getKTVPlayer()
```
获取 KTV 播放器。

**返回值**
KTV 播放器接口，参看 [KTVPlayer](#ktvplayer)。


# KTVPlayer
```java
public abstract class com.ss.bytertc.ktv.KTVPlayer
```

KTV 播放器接口。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **abstract void** | [setPlayerEventHandler](#KTVPlayer-setplayereventhandler) |
| **abstract void** | [playMusic](#KTVPlayer-playmusic) |
| **abstract void** | [pauseMusic](#KTVPlayer-pausemusic) |
| **abstract void** | [resumeMusic](#KTVPlayer-resumemusic) |
| **abstract void** | [stopMusic](#KTVPlayer-stopmusic) |
| **abstract void** | [seekMusic](#KTVPlayer-seekmusic) |
| **abstract void** | [setMusicVolume](#KTVPlayer-setmusicvolume) |
| **abstract void** | [switchAudioTrackType](#KTVPlayer-switchaudiotracktype) |
| **abstract void** | [setMusicPitch](#KTVPlayer-setmusicpitch) |


## 函数说明
<span id="KTVPlayer-setplayereventhandler"></span>
### setPlayerEventHandler
```java
public abstract void com.ss.bytertc.ktv.KTVPlayer.setPlayerEventHandler(
    IKTVPlayerEventHandler playerEventHandler)
```
设置 KTV 播放器进度及状态回调接口。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| playerEventHandler | **IKTVPlayerEventHandler** | KTV 播放器回调类，参看 [IKTVPlayerEventHandler](Android-callback.md#iktvplayereventhandler)。 |


<span id="KTVPlayer-playmusic"></span>
### playMusic
```java
public abstract void com.ss.bytertc.ktv.KTVPlayer.playMusic(
    @NonNull String musicId,
    @NonNull AudioTrackType trackType,
    @NonNull AudioPlayType playType)
```
播放歌曲。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| musicId | **@NonNull String** | 音乐 ID。<br/>若同一 musicId 的歌曲正在播放，再次调用接口会从开始位置重新播放。若 musicId 对应的音频文件不存在会触发报错。 |
| trackType | **@NonNull AudioTrackType** | 原唱伴唱类型，参看 [AudioTrackType](Android-keytype.md#audiotracktype)。 |
| playType | **@NonNull AudioPlayType** | 音乐播放类型。参看 [AudioPlayType](Android-keytype.md#audioplaytype)。 |


**注意**

+ 调用接口后，你会收到 [onPlayStateChanged](Android-callback.md#IKTVPlayerEventHandler-onplaystatechanged) 回调歌曲播放状态。
+ 若音乐 ID 错误，会触发 [onPlayStateChanged](Android-callback.md#IKTVPlayerEventHandler-onplaystatechanged) 回调，errorCode 为 –3023，playState 为 4。
+ 若未进房，会触发 [onPlayStateChanged](Android-callback.md#IKTVPlayerEventHandler-onplaystatechanged) 回调，errorCode 为 –3022，playState 为 4。
+ 若音乐文件不存在，会触发 [onPlayStateChanged](Android-callback.md#IKTVPlayerEventHandler-onplaystatechanged) 回调，errorCode 为 –3020，playState 为 4。


<span id="KTVPlayer-pausemusic"></span>
### pauseMusic
```java
public abstract void com.ss.bytertc.ktv.KTVPlayer.pauseMusic(
    @NonNull String musicId)
```
暂停播放歌曲。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| musicId | **@NonNull String** | 音乐 ID。 |


**注意**

+ 调用接口后，你会收到 [onPlayStateChanged](Android-callback.md#IKTVPlayerEventHandler-onplaystatechanged) 回调歌曲播放状态。
+ 若音乐 ID 错误，会触发 [onPlayStateChanged](Android-callback.md#IKTVPlayerEventHandler-onplaystatechanged) 回调，errorCode 为 –3023，playState 为 4。
+ 若未进房，会触发 [onPlayStateChanged](Android-callback.md#IKTVPlayerEventHandler-onplaystatechanged) 回调，errorCode 为 –3022，playState 为 4。


<span id="KTVPlayer-resumemusic"></span>
### resumeMusic
```java
public abstract void com.ss.bytertc.ktv.KTVPlayer.resumeMusic(
    @NonNull String musicId)
```
继续播放歌曲。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| musicId | **@NonNull String** | 音乐 ID。 |


**注意**

+ 调用接口后，你会收到 [onPlayStateChanged](Android-callback.md#IKTVPlayerEventHandler-onplaystatechanged) 回调歌曲播放状态。
+ 若音乐 ID 错误，会触发 [onPlayStateChanged](Android-callback.md#IKTVPlayerEventHandler-onplaystatechanged) 回调，errorCode 为 –3023，playState 为 4。
+ 若未进房，会触发 [onPlayStateChanged](Android-callback.md#IKTVPlayerEventHandler-onplaystatechanged) 回调，errorCode 为 –3022，playState 为 4。


<span id="KTVPlayer-stopmusic"></span>
### stopMusic
```java
public abstract void com.ss.bytertc.ktv.KTVPlayer.stopMusic(
    @NonNull String musicId)
```
停止播放歌曲。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| musicId | **@NonNull String** | 音乐 ID。 |


**注意**

+ 调用接口后，你会收到 [onPlayStateChanged](Android-callback.md#IKTVPlayerEventHandler-onplaystatechanged) 回调歌曲播放状态。
+ 若音乐 ID 错误，会触发 [onPlayStateChanged](Android-callback.md#IKTVPlayerEventHandler-onplaystatechanged) 回调，errorCode 为 –3023，playState 为 4。
+ 若未进房，会触发 [onPlayStateChanged](Android-callback.md#IKTVPlayerEventHandler-onplaystatechanged) 回调，errorCode 为 –3022，playState 为 4。


<span id="KTVPlayer-seekmusic"></span>
### seekMusic
```java
public abstract void com.ss.bytertc.ktv.KTVPlayer.seekMusic(
    @NonNull String musicId,
    int position)
```
设置音乐文件的起始播放位置。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| musicId | **@NonNull String** | 音乐 ID。 |
| position | **int** | 音乐起始位置，单位为毫秒，取值小于音乐文件总时长。 |


**注意**

+ 调用本接口时音乐必须处于播放中状态。
+ 调用接口后，你会收到 [onPlayStateChanged](Android-callback.md#IKTVPlayerEventHandler-onplaystatechanged) 回调歌曲播放状态。
+ 若音乐 ID 错误，会触发 [onPlayStateChanged](Android-callback.md#IKTVPlayerEventHandler-onplaystatechanged) 回调，errorCode 为 –3023，playState 为 4。
+ 若未进房，会触发 [onPlayStateChanged](Android-callback.md#IKTVPlayerEventHandler-onplaystatechanged) 回调，errorCode 为 –3022，playState 为 4。


<span id="KTVPlayer-setmusicvolume"></span>
### setMusicVolume
```java
public abstract void com.ss.bytertc.ktv.KTVPlayer.setMusicVolume(
    @NonNull String musicId,
    int volume)
```
设置歌曲播放音量，只能在开始播放后进行设置。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| musicId | **@NonNull String** | 音乐 ID。 |
| volume | **int** | 歌曲播放音量，调节范围：[0,400]。<br/>• 0：静音。<br/>• 100：原始音量。<br/>• 400: 原始音量的 4 倍(自带溢出保护)。 |


**注意**

+ 调用本接口时音乐必须处于播放中状态。
+ 若设置的音量大于 400，则按最大值 400 进行调整；若设置的音量小于 0，则按最小值 0 进行调整。
+ 若音乐 ID 错误，会触发 [onPlayStateChanged](Android-callback.md#IKTVPlayerEventHandler-onplaystatechanged) 回调，errorCode 为 –3023，playState 为 4。
+ 若未进房，会触发 [onPlayStateChanged](Android-callback.md#IKTVPlayerEventHandler-onplaystatechanged) 回调，errorCode 为 –3022，playState 为 4。


<span id="KTVPlayer-switchaudiotracktype"></span>
### switchAudioTrackType
```java
public abstract void com.ss.bytertc.ktv.KTVPlayer.switchAudioTrackType(
    @NonNull String musicId)
```
切换歌曲原唱伴唱。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| musicId | **@NonNull String** | 音乐 ID。 |


**注意**
调用本接口时音乐必须处于播放中状态。

<span id="KTVPlayer-setmusicpitch"></span>
### setMusicPitch
```java
public abstract void com.ss.bytertc.ktv.KTVPlayer.setMusicPitch(
    @NonNull String musicId,
    int pitch)
```
对播放中的音乐设置升降调信息。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| musicId | **@NonNull String** | 音乐 ID。 |
| pitch | **int** | 相对于音乐文件原始音调的升高/降低值，取值范围 [-12，12]，默认值为 0，即不做调整。<br/>取值范围内每相邻两个值的音高距离相差半音，正值表示升调，负值表示降调，设置的绝对值越大表示音调升高或降低越多。 |


**注意**

+ 调用本接口时音乐必须处于播放中状态。
+ 若设置的 pitch 大于 12，则按最大值 12 进行调整；若设置的 pitch 小于 –12，，则按最小值 –12 进行调整。
+ 若音乐 ID 错误，会触发 [onPlayStateChanged](Android-callback.md#IKTVPlayerEventHandler-onplaystatechanged) 回调，errorCode 为 –3023，playState 为 4。
+ 若未进房，会触发 [onPlayStateChanged](Android-callback.md#IKTVPlayerEventHandler-onplaystatechanged) 回调，errorCode 为 –3022，playState 为 4。