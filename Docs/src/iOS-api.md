# ByteRTCRoom
```objectivec
@interface ByteRTCRoom : NSObject
```



## 成员函数

| 返回 | 名称 |
| --- | --- |
| **void** | [destroy](#ByteRTCRoom-destroy) |
| **void** | [setRtcRoomDelegate:](#ByteRTCRoom-setrtcroomdelegate) |
| **int** | [joinRoomByToken:userInfo:roomConfig:](#ByteRTCRoom-joinroombytoken-userinfo-roomconfig) |
| **BOOL** | [setUserVisibility:](#ByteRTCRoom-setuservisibility) |
| **BOOL** | [setMultiDeviceAVSync:](#ByteRTCRoom-setmultideviceavsync) |
| **int** | [leaveRoom](#ByteRTCRoom-leaveroom) |
| **int** | [renewToken:](#ByteRTCRoom-renewtoken) |
| **int** | [setRemoteVideoConfig:remoteVideoConfig:](#ByteRTCRoom-setremotevideoconfig-remotevideoconfig) |
| **int** | [publishStream:](#ByteRTCRoom-publishstream) |
| **int** | [unpublishStream:](#ByteRTCRoom-unpublishstream) |
| **int** | [publishScreen:](#ByteRTCRoom-publishscreen) |
| **int** | [unpublishScreen:](#ByteRTCRoom-unpublishscreen) |
| **void** | [subscribeStream:mediaStreamType:](#ByteRTCRoom-subscribestream-mediastreamtype) |
| **void** | [subscribeAllStreamsWithMeidaStreamType:](#ByteRTCRoom-subscribeallstreamswithmeidastreamtype) |
| **void** | [unSubscribeStream:mediaStreamType:](#ByteRTCRoom-unsubscribestream-mediastreamtype) |
| **void** | [unSubscribeAllStreamsWithMeidaStreamType:](#ByteRTCRoom-unsubscribeallstreamswithmeidastreamtype) |
| **void** | [subscribeScreen:mediaStreamType:](#ByteRTCRoom-subscribescreen-mediastreamtype) |
| **void** | [unSubscribeScreen:mediaStreamType:](#ByteRTCRoom-unsubscribescreen-mediastreamtype) |
| **void** | [pauseAllSubscribedStream:](#ByteRTCRoom-pauseallsubscribedstream) |
| **void** | [resumeAllSubscribedStream:](#ByteRTCRoom-resumeallsubscribedstream) |
| **int64_t** | [sendUserMessage:message:config:](#ByteRTCRoom-sendusermessage-message-config) |
| **int64_t** | [sendUserBinaryMessage:message:config:](#ByteRTCRoom-senduserbinarymessage-message-config) |
| **int64_t** | [sendRoomMessage:](#ByteRTCRoom-sendroommessage) |
| **int64_t** | [sendRoomBinaryMessage:](#ByteRTCRoom-sendroombinarymessage) |
| **int** | [startForwardStreamToRooms:](#ByteRTCRoom-startforwardstreamtorooms) |
| **int** | [updateForwardStreamToRooms:](#ByteRTCRoom-updateforwardstreamtorooms) |
| **void** | [stopForwardStreamToRooms](#ByteRTCRoom-stopforwardstreamtorooms) |
| **void** | [pauseForwardStreamToAllRooms](#ByteRTCRoom-pauseforwardstreamtoallrooms) |
| **void** | [resumeForwardStreamToAllRooms](#ByteRTCRoom-resumeforwardstreamtoallrooms) |
| **ByteRTCRangeAudio*** | [getRangeAudio](#ByteRTCRoom-getrangeaudio) |
| **ByteRTCSpatialAudio*** | [getSpatialAudio](#ByteRTCRoom-getspatialaudio) |
| **int** | [enableCloudRending:](#ByteRTCRoom-enablecloudrending) |
| **int** | [updateCloudRending:](#ByteRTCRoom-updatecloudrending) |
| **int** | [disableCloudRending](#ByteRTCRoom-disablecloudrending) |


## 函数说明
<span id="ByteRTCRoom-destroy"></span>
### destroy
```objectivec

- (void)destroy;
```
退出并销毁调用 [createRTCRoom:](#ByteRTCVideo-creatertcroom) 所创建的房间实例。


<span id="ByteRTCRoom-setrtcroomdelegate"></span>
### setRtcRoomDelegate:
```objectivec

- (void)setRtcRoomDelegate:(id<ByteRTCRoomDelegate> _Nullable)roomDelegate;
```
通过设置 [ByteRTCRoomDelegate](iOS-callback.md#bytertcroomdelegate) 代理，可以监听此 `ByteRTCRoom` 对象对应的回调事件。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| roomDelegate | **id<ByteRTCRoomDelegate>** | 参看 [ByteRTCRoomDelegate](iOS-callback.md#bytertcroomdelegate)。 |


<span id="ByteRTCRoom-joinroombytoken-userinfo-roomconfig"></span>
### joinRoomByToken:userInfo:roomConfig:
```objectivec

- (int)joinRoomByToken:(NSString *_Nullable)token userInfo:(ByteRTCUserInfo *_Nonnull)userInfo roomConfig:(ByteRTCRoomConfig *_Nonnull)roomConfig;
```
加入房间。<br>
调用 [createRTCRoom:](#ByteRTCVideo-creatertcroom) 创建房间后，调用此方法加入房间，同房间内其他用户进行音视频通话。  <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| token | **NSString*** | 动态密钥，用于对进房用户进行鉴权验证。  <br/>进入房间需要携带 Token。测试时可使用控制台生成临时 Token，正式上线需要使用密钥 SDK 在你的服务端生成并下发 Token。Token 有效期及生成方式参看[使用 Token 完成鉴权](70121)  <br/>使用不同 AppID 的 App 是不能互通的。  <br/>请务必保证生成 Token 使用的 AppID 和创建引擎时使用的 AppID 相同，否则会导致加入房间失败。具体失败原因会通过 [rtcRoom:onRoomStateChanged:withUid:state:extraInfo:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onroomstatechanged-withuid-state-extrainfo) 回调告知。 |
| userInfo | **ByteRTCUserInfo*** | 用户信息。参看 [ByteRTCUserInfo](iOS-keytype.md#bytertcuserinfo)。 |
| roomConfig | **ByteRTCRoomConfig*** | 房间参数配置，设置房间模式以及是否自动发布或订阅流。具体配置模式参看 [ByteRTCRoomConfig](iOS-keytype.md#bytertcroomconfig)。 |

**返回值**
方法调用结果。  

+  0: 成功  
+ -1: 参数无效  
+ -2: 已经在房间内。接口调用成功后，只要收到返回值为 0 ，且未调用 [leaveRoom](#ByteRTCRoom-leaveroom) 成功，则再次调用进房接口时，无论填写的房间 ID 和用户 ID 是否重复，均触发此返回值。  
+ -3: room 为空 


**注意**

+ 同一个 AppID 的同一个房间内，每个用户的用户 ID 必须是唯一的。如果两个用户的用户 ID 相同，则后加入房间的用户会将先加入房间的用户踢出房间，并且先加入房间的用户会收到 [rtcRoom:onRoomStateChanged:withUid:state:extraInfo:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onroomstatechanged-withuid-state-extrainfo) 回调通知，错误类型为重复登录 ByteRTCErrorCodeDuplicateLogin。  
+ 本地用户调用此方法加入房间成功后，会收到 [rtcRoom:onRoomStateChanged:withUid:state:extraInfo:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onroomstatechanged-withuid-state-extrainfo) 回调通知。若本地用户同时为可见用户，加入房间时远端用户会收到 [rtcRoom:onUserJoined:elapsed:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onuserjoined-elapsed) 回调通知。关于可见性设置参看 [setUserVisibility:](#ByteRTCRoom-setuservisibility)。  
+ 用户加入房间成功后，在本地网络状况不佳的情况下，SDK 可能会与服务器失去连接，并触发 [rtcEngine:onConnectionStateChanged:](iOS-callback.md#ByteRTCVideoDelegate-rtcEngine-onConnectionStateChanged) 回调。此时 SDK 会自动重试，直到成功重连。重连成功后，本地会收到 [rtcRoom:onRoomStateChanged:withUid:state:extraInfo:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onroomstatechanged-withuid-state-extrainfo)。


<span id="ByteRTCRoom-setuservisibility"></span>
### setUserVisibility:
```objectivec

- (BOOL)setUserVisibility:(BOOL)enable;
```
设置用户可见性。未调用该接口前，本地用户默认对他人可见。 <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| enable | **BOOL** | 设置用户是否对房间内其他用户可见：  <br/>• true: 可以在房间内发布音视频流，房间中的其他用户将收到用户的行为通知，例如进房、开启视频采集和退房。  <br/>• false: 不可以在房间内发布音视频流，房间中的其他用户不会收到用户的行为通知，例如进房、开启视频采集和退房。 |

**返回值**

+ 0: 方法调用成功  
+ < 0: 方法调用失败  


**注意**

+ 该方法在加入房间前后均可调用。 
+ 在房间内调用此方法，房间内其他用户会收到相应的回调通知：
- 从 false 切换至 true 时，房间内其他用户会收到 [rtcRoom:onUserJoined:elapsed:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onuserjoined-elapsed) 回调通知；  
- 从 true 切换至 false 时，房间内其他用户会收到 [rtcRoom:onUserLeave:reason:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onuserleave-reason) 回调通知。  
+ 若调用该方法将可见性设为 false，此时尝试发布流会收到 `ByteRTCWarningCodeSubscribeStreamForbiden` 警告。


<span id="ByteRTCRoom-setmultideviceavsync"></span>
### setMultiDeviceAVSync:
```objectivec

- (BOOL)setMultiDeviceAVSync:(NSString* _Nullable) audioUserId;
```
设置发流端音画同步。  <br>
当同一用户同时使用两个通话设备分别采集发送音频和视频时，有可能会因两个设备所处的网络环境不一致而导致发布的流不同步，此时你可以在视频发送端调用该接口，SDK 会根据音频流的时间戳自动校准视频流，以保证接收端听到音频和看到视频在时间上的同步性。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioUserId | **NSString*** | 音频发送端的用户 ID，将该参数设为空则可解除当前音视频的同步关系。 |

**返回值**
方法调用结果：  

+ True：成功  
+ False：失败


**注意**

+ 该方法在进房前后均可调用。  
+ 进行音画同步的音频发布用户 ID 和视频发布用户 ID 须在同一个 RTC 房间内。  
+ 调用该接口后音画同步状态发生改变时，你会收到 [rtcRoom:onAVSyncStateChange:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onavsyncstatechange) 回调。  
+ 同一 RTC 房间内允许存在多个音视频同步关系，但需注意单个音频源不支持与多个视频源同时同步。  
+ 如需更换同步音频源，再次调用该接口传入新的 `audioUserId` 即可；如需更换同步视频源，需先解除当前的同步关系，后在新视频源端开启同步。


<span id="ByteRTCRoom-leaveroom"></span>
### leaveRoom
```objectivec

- (int)leaveRoom;
```
离开房间。  <br>
用户调用此方法离开房间，结束通话过程，释放所有通话相关的资源。  <br>

**返回值**
方法调用结果。  

+  0: 方法调用成功  
+ < 0: 方法调用失败  


**注意**

+ 用户离开房间后，本地会收到 [rtcRoom:onLeaveRoomWithStats:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onleaveroomwithstats) 的回调；  
+ 调用 [setUserVisibility:](#ByteRTCRoom-setuservisibility) 方法将自身设为可见的用户离开房间后，房间内其他用户会收到 [rtcRoom:onUserLeave:reason:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onuserleave-reason) 回调通知。  


<span id="ByteRTCRoom-renewtoken"></span>
### renewToken:
```objectivec

- (int)renewToken:(NSString *_Nullable)token;
```

更新 Token。
在 Token 进房权限过期前 30 秒，会收到 [onTokenWillExpire:](iOS-callback.md#ByteRTCRoomDelegate-ontokenwillexpire) 回调，此时需要重新获取 Token，并调用此方法更新 Token，否则用户将因为 Token 过期被移出房间。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| token | **NSString** | 获取的新的有效 Token。  <br/>如果传入的 Token 无效，回调错误码为 [ByteRTCErrorCode](iOS-errorcode.md#bytertcerrorcode) 中的 `–1010`。 |


**返回值**

+  0: 成功。  
+ < 0: 失败。  

**注意**
请勿同时调用 [renewToken:](iOS-api.md#ByteRTCRoom-renewtoken) 和 [joinRoomByToken:userInfo:roomConfig:](iOS-api.md#ByteRTCRoom-joinroombytoken-userinfo-roomconfig) 方法更新 Token。若因 Token 过期或无效导致加入房间失败或已被移出房间，你应该在获取新的有效 Token 后调用 [joinRoomByToken:userInfo:roomConfig:](iOS-api.md#ByteRTCRoom-joinroombytoken-userinfo-roomconfig) 重新加入房间。

<span id="ByteRTCRoom-setremotevideoconfig-remotevideoconfig"></span>
### setRemoteVideoConfig:remoteVideoConfig:
```objectivec

- (int) setRemoteVideoConfig:(NSString * _Nonnull) userId remoteVideoConfig:(ByteRTCRemoteVideoConfig *_Nonnull) remoteVideoConfig;
```
设置期望订阅的远端视频流的参数。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| userId | **NSString*** | 期望配置订阅参数的远端视频流发布用户的 ID。 |
| remoteVideoConfig | **ByteRTCRemoteVideoConfig*** | 期望配置的远端视频流参数，参看 [ByteRTCRemoteVideoConfig](iOS-keytype.md#bytertcremotevideoconfig)。 |


**注意**

+ 若使用 342 及以前版本的 SDK，调用该方法前请联系技术支持人员开启按需订阅功能。  
+ 该方法仅在发布端调用 [enableSimulcastMode:](#ByteRTCVideo-enablesimulcastmode) 开启了发送多路视频流的情况下生效，此时订阅端将收到来自发布端与期望设置的参数最相近的一路流；否则订阅端只会收到一路参数为分辨率 640px × 360px、帧率 15fps 的视频流。  
+ 若发布端开启了推送多路流功能，但订阅端不对流参数进行设置，则默认接受发送端设置的分辨率最大的一路视频流。  
+ 该方法需在进房后调用，若想进房前设置，你需调用 [joinRoomByToken:userInfo:roomConfig:](#ByteRTCRoom-joinroombytoken-userinfo-roomconfig)，并对 `roomConfig` 中的 `remoteVideoConfig` 进行设置。  
+ SDK 会根据发布端和所有订阅端的设置灵活调整视频流的参数，具体调整策略详见[推送多路流](https://www.volcengine.com/docs/6348/70139)文档。


<span id="ByteRTCRoom-publishstream"></span>
### publishStream:
```objectivec

- (int)publishStream:(ByteRTCMediaStreamType)type;
```
在当前所在房间内发布本地通过摄像头/麦克风采集的媒体流

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| type | **ByteRTCMediaStreamType** | 媒体流类型，用于指定发布音频/视频，参看 [ByteRTCMediaStreamType](iOS-keytype.md#bytertcmediastreamtype) |

**返回值**
方法调用结果： 

+ 0: 发布成功  
+ -1: 发布失败


**注意**

+ 如果你已经在用户进房时通过调用 [joinRoomByToken:userInfo:roomConfig:](#ByteRTCRoom-joinroombytoken-userinfo-roomconfig) 成功选择了自动发布，则无需再调用本接口。
+ 调用 [setUserVisibility:](#ByteRTCRoom-setuservisibility) 方法将自身设置为不可见后无法调用该方法，需将自身切换至可见后方可调用该方法发布摄像头音视频流。 
+ 如果你需要发布屏幕共享流，调用 [publishScreen:](#ByteRTCRoom-publishscreen)。
+ 如果你需要向多个房间发布流，调用 [startForwardStreamToRooms:](#ByteRTCRoom-startforwardstreamtorooms)。  
+ 调用此方法后，房间中的所有远端用户会收到 [rtcRoom:onUserPublishStream:type:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onuserpublishstream-type) 回调通知，其中成功收到了音频流的远端用户会收到 [rtcEngine:onFirstRemoteAudioFrame:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onfirstremoteaudioframe) 回调，订阅了视频流的远端用户会收到 [rtcEngine:onFirstRemoteVideoFrameDecoded:withFrameInfo:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onfirstremotevideoframedecoded-withframeinfo) 回调。
+ 调用 [unpublishStream:](#ByteRTCRoom-unpublishstream) 取消发布。


<span id="ByteRTCRoom-unpublishstream"></span>
### unpublishStream:
```objectivec

- (int)unpublishStream:(ByteRTCMediaStreamType)type;
```
停止将本地摄像头/麦克风采集的媒体流发布到当前所在房间中

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| type | **ByteRTCMediaStreamType** | 媒体流类型，用于指定停止发布音频/视频，参看 [ByteRTCMediaStreamType](iOS-keytype.md#bytertcmediastreamtype) |

**返回值**

+ 0: 停止发布成功  
+ -1: 停止发布失败


**注意**

+ 调用 [publishStream:](#ByteRTCRoom-publishstream) 手动发布摄像头音视频流后，你需调用此接口停止发布。
+ 调用此方法停止发布音视频流后，房间中的其他用户将会收到 [rtcRoom:onUserUnpublishStream:type:reason:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onuserunpublishstream-type-reason) 回调通知。


<span id="ByteRTCRoom-publishscreen"></span>
### publishScreen:
```objectivec

- (int)publishScreen:(ByteRTCMediaStreamType)type;
```
在当前所在房间内发布本地屏幕共享音视频流

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| type | **ByteRTCMediaStreamType** | 媒体流类型，用于指定发布屏幕音频/视频，参看 [ByteRTCMediaStreamType](iOS-keytype.md#bytertcmediastreamtype)。 |

**返回值**

+ 0: 发布成功 
+ -1: 发布失败


**注意**

+ 如果你已经在用户进房时通过调用 [joinRoomByToken:userInfo:roomConfig:](#ByteRTCRoom-joinroombytoken-userinfo-roomconfig) 成功选择了自动发布，则无需再调用本接口。
+ 调用 [setUserVisibility:](#ByteRTCRoom-setuservisibility) 方法将自身设置为不可见后无法调用该方法，需将自身切换至可见后方可调用该方法发布屏幕流。 
+ 调用该方法后，房间中的所有远端用户会收到 [rtcRoom:onUserPublishScreen:type:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onuserpublishscreen-type) 回调，其中成功收到音频流的远端用户会收到 [rtcEngine:onFirstRemoteAudioFrame:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onfirstremoteaudioframe) 回调，订阅了视频流的远端用户会收到 [rtcEngine:onFirstRemoteVideoFrameDecoded:withFrameInfo:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onfirstremotevideoframedecoded-withframeinfo) 回调。
+ 调用 [unpublishScreen:](#ByteRTCRoom-unpublishscreen) 取消发布。
+ 查看 [屏幕共享](https://www.volcengine.com/docs/6348/80225)，获取更多信息。


<span id="ByteRTCRoom-unpublishscreen"></span>
### unpublishScreen:
```objectivec

- (int)unpublishScreen:(ByteRTCMediaStreamType)type;
```
停止将本地屏幕共享音视频流发布到当前所在房间中

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| type | **ByteRTCMediaStreamType** | 媒体流类型，用于指定停止发布屏幕音频/视频，参看 [ByteRTCMediaStreamType](iOS-keytype.md#bytertcmediastreamtype) |

**返回值**

+ 0: 停止发布成功 
+ -1: 停止发布失败


**注意**

+ 调用 [publishScreen:](#ByteRTCRoom-publishscreen) 发布屏幕流后，你需调用此接口停止发布。 
+ 调用此方法停止发布屏幕音视频流后，房间中的其他用户将会收到 [rtcRoom:onUserUnpublishScreen:type:reason:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onuserunpublishscreen-type-reason) 回调。


<span id="ByteRTCRoom-subscribestream-mediastreamtype"></span>
### subscribeStream:mediaStreamType:
```objectivec

- (void)subscribeStream:(NSString *_Nonnull)userId mediaStreamType:(ByteRTCMediaStreamType)mediaStreamType;
```
订阅房间内指定的通过摄像头/麦克风采集的媒体流，或更新对指定远端用户的订阅选项

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| userId | **NSString*** | 指定订阅的远端发布音视频流的用户 ID。 |
| mediaStreamType | **ByteRTCMediaStreamType** | 媒体流类型，用于指定订阅音频/视频。参看 [ByteRTCMediaStreamType](iOS-keytype.md#bytertcmediastreamtype)。 |


**注意**

+ 当调用本接口时，当前用户已经订阅该远端用户，不论是通过手动订阅还是自动订阅，都将根据本次传入的参数，更新订阅配置。
+ 你必须先通过 [rtcRoom:onUserPublishStream:type:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onuserpublishstream-type) 回调获取当前房间里的远端摄像头音视频流信息，然后调用本方法按需订阅。  
+ 调用该方法后，你会收到 [rtcRoom:onStreamSubscribed:userId:subscribeConfig:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onstreamsubscribed-userid-subscribeconfig) 通知方法调用结果。  
+ 成功订阅远端用户的媒体流后，订阅关系将持续到调用 [unSubscribeStream:mediaStreamType:](#ByteRTCRoom-unsubscribestream-mediastreamtype) 取消订阅或本端用户退房。 
+ 关于其他调用异常，你会收到 [rtcRoom:onStreamStateChanged:withUid:state:extraInfo:](iOS-callback#ByteRTCRoomDelegate-rtcroom-onstreamstatechanged-withuid-state-extrainfo) 回调通知，具体异常原因参看 [ByteRTCErrorCode](iOS-errorcode.md#bytertcerrorcode)。


<span id="ByteRTCRoom-subscribeallstreamswithmeidastreamtype"></span>
### subscribeAllStreamsWithMeidaStreamType:
```objectivec

- (void)subscribeAllStreamsWithMeidaStreamType:(ByteRTCMediaStreamType)mediaStreamType;
```
订阅房间内所有通过摄像头/麦克风采集的媒体流，或更新订阅选项。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mediaStreamType | **ByteRTCMediaStreamType** | 媒体流类型，用于指定订阅音频/视频。参看 [ByteRTCMediaStreamType](iOS-keytype.md#bytertcmediastreamtype)。 |


**注意**

+ 多次调用订阅接口时，将根据末次调用接口和传入的参数，更新订阅配置。
+ 大会模式下，如果房间内的媒体流超过上限，建议通过调用 [subscribeStream:mediaStreamType:](#ByteRTCRoom-subscribestream-mediastreamtype) 逐一指定需要订阅的媒体流。
+ 调用该方法后，你会收到 [rtcRoom:onStreamSubscribed:userId:subscribeConfig:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onstreamsubscribed-userid-subscribeconfig) 通知方法调用结果。  
+ 成功调用本接口后，订阅关系将持续到调用 [unSubscribeStream:mediaStreamType:](#ByteRTCRoom-unsubscribestream-mediastreamtype) 或 [unSubscribeAllStreamsWithMeidaStreamType:](#ByteRTCRoom-unsubscribeallstreamswithmeidastreamtype) 取消订阅或本端用户退房。 
+ 关于其他调用异常，你会收到 rtcRoom:onRoomStateChanged:withUid:state:extraInfo:[rtcRoom:onStreamStateChanged:withUid:state:extraInfo:](#rtcroom-onstreamstatechanged-withuid-state-extrainfo) 回调通知，具体异常原因参看 [ByteRTCErrorCode](iOS-errorcode.md#bytertcerrorcode)。


<span id="ByteRTCRoom-unsubscribestream-mediastreamtype"></span>
### unSubscribeStream:mediaStreamType:
```objectivec

- (void)unSubscribeStream:(NSString *_Nonnull)userId mediaStreamType:(ByteRTCMediaStreamType)mediaStreamType;
```
取消订阅房间内指定的通过摄像头/麦克风采集的媒体流。  <br>
该方法对自动订阅和手动订阅模式均适用。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| userId | **NSString*** | 指定取消订阅的远端发布音视频流的用户 ID。 |
| mediaStreamType | **ByteRTCMediaStreamType** | 媒体流类型，用于指定取消订阅音频/视频。参看 [ByteRTCMediaStreamType](iOS-keytype.md#bytertcmediastreamtype)。 |


**注意**

+ 调用该方法后，你会收到 [rtcRoom:onStreamSubscribed:userId:subscribeConfig:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onstreamsubscribed-userid-subscribeconfig) 通知方法调用结果。  
+ 关于其他调用异常，你会收到 [rtcRoom:onStreamStateChanged:withUid:state:extraInfo:](iOS-callback#ByteRTCRoomDelegate-rtcroom-onstreamstatechanged-withuid-state-extrainfo) 回调通知，具体失败原因参看 [ByteRTCErrorCode](iOS-errorcode.md#bytertcerrorcode)。


<span id="ByteRTCRoom-unsubscribeallstreamswithmeidastreamtype"></span>
### unSubscribeAllStreamsWithMeidaStreamType:
```objectivec

- (void)unSubscribeAllStreamsWithMeidaStreamType:(ByteRTCMediaStreamType)mediaStreamType;
```
取消订阅房间内所有的通过摄像头/麦克风采集的媒体流。  <br>
自动订阅和手动订阅的流都可以通过本方法取消订阅。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mediaStreamType | **ByteRTCMediaStreamType** | 媒体流类型，用于指定取消订阅音频/视频。参看 [ByteRTCMediaStreamType](iOS-keytype.md#bytertcmediastreamtype)。 |


**注意**

+ 调用该方法后，你会收到 [rtcRoom:onStreamSubscribed:userId:subscribeConfig:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onstreamsubscribed-userid-subscribeconfig) 通知方法调用结果。  
+ 关于其他调用异常，你会收到 rtcRoom:onRoomStateChanged:withUid:state:extraInfo:[rtcRoom:onStreamStateChanged:withUid:state:extraInfo:](#rtcroom-onstreamstatechanged-withuid-state-extrainfo) 回调通知，具体失败原因参看 [ByteRTCErrorCode](iOS-errorcode.md#bytertcerrorcode)。


<span id="ByteRTCRoom-subscribescreen-mediastreamtype"></span>
### subscribeScreen:mediaStreamType:
```objectivec

- (void)subscribeScreen:(NSString *_Nonnull)userId mediaStreamType:(ByteRTCMediaStreamType)mediaStreamType;
```
订阅房间内指定的远端屏幕共享音视频流，或更新对指定远端用户的订阅选项

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| userId | **NSString*** | 指定订阅的远端发布屏幕流的用户 ID。 |
| mediaStreamType | **ByteRTCMediaStreamType** | 媒体流类型，用于指定订阅音频/视频。参看 [ByteRTCMediaStreamType](iOS-keytype.md#bytertcmediastreamtype)。 |


**注意**

+ 当调用本接口时，当前用户已经订阅该远端用户，不论是通过手动订阅还是自动订阅，都将根据本次传入的参数，更新订阅配置。
+ 你必须先通过 [rtcRoom:onUserPublishScreen:type:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onuserpublishscreen-type) 回调获取当前房间里的远端屏幕流信息，然后调用本方法按需订阅。  
+ 调用该方法后，你会收到 [rtcRoom:onStreamSubscribed:userId:subscribeConfig:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onstreamsubscribed-userid-subscribeconfig) 通知方法调用结果。  
+ 成功订阅远端用户的媒体流后，订阅关系将持续到调用 [unSubscribeScreen:mediaStreamType:](#ByteRTCRoom-unsubscribescreen-mediastreamtype) 取消订阅或本端用户退房。 
+ 关于其他调用异常，你会收到 [rtcRoom:onStreamStateChanged:withUid:state:extraInfo:](iOS-callback#ByteRTCRoomDelegate-rtcroom-onstreamstatechanged-withuid-state-extrainfo) 回调通知，具体异常原因参看 [ByteRTCErrorCode](iOS-errorcode.md#bytertcerrorcode)。


<span id="ByteRTCRoom-unsubscribescreen-mediastreamtype"></span>
### unSubscribeScreen:mediaStreamType:
```objectivec

- (void)unSubscribeScreen:(NSString *_Nonnull)userId mediaStreamType:(ByteRTCMediaStreamType)mediaStreamType;
```
取消订阅房间内指定的远端屏幕共享音视频流。  <br>
该方法对自动订阅和手动订阅模式均适用。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| userId | **NSString*** | 指定取消订阅的远端发布屏幕流的用户 ID。 |
| mediaStreamType | **ByteRTCMediaStreamType** | 媒体流类型，用于指定取消订阅音频/视频。参看 [ByteRTCMediaStreamType](iOS-keytype.md#bytertcmediastreamtype)。 |


**注意**

+ 调用该方法后，你会收到 [rtcRoom:onStreamSubscribed:userId:subscribeConfig:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onstreamsubscribed-userid-subscribeconfig) 通知方法调用结果。  
+ 关于其他调用异常，你会收到 [rtcRoom:onStreamStateChanged:withUid:state:extraInfo:](iOS-callback#ByteRTCRoomDelegate-rtcroom-onstreamstatechanged-withuid-state-extrainfo) 回调通知，具体失败原因参看 [ByteRTCErrorCode](iOS-errorcode.md#bytertcerrorcode)。


<span id="ByteRTCRoom-pauseallsubscribedstream"></span>
### pauseAllSubscribedStream:
```objectivec

- (void)pauseAllSubscribedStream:(ByteRTCPauseResumControlMediaType) mediaType;
```
暂停接收来自远端的媒体流

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mediaType | **ByteRTCPauseResumControlMediaType** | 媒体流类型，指定需要暂停接收音频还是视频流，参看 [ByteRTCPauseResumControlMediaType](iOS-keytype.md#bytertcpauseresumcontrolmediatype) |


**注意**

+ 该方法仅暂停远端流的接收，并不影响远端流的采集和发送；  
+ 该方法不改变用户的订阅状态以及订阅流的属性。  
+ 若想恢复接收远端流，需调用 [resumeAllSubscribedStream:](#ByteRTCRoom-resumeallsubscribedstream)。 
+ 多房间场景下，仅暂停接收发布在当前所在房间的流。


<span id="ByteRTCRoom-resumeallsubscribedstream"></span>
### resumeAllSubscribedStream:
```objectivec

- (void)resumeAllSubscribedStream:(ByteRTCPauseResumControlMediaType) mediaType;
```
恢复接收来自远端的媒体流

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mediaType | **ByteRTCPauseResumControlMediaType** | 媒体流类型，指定需要暂停接收音频还是视频流，参看 [ByteRTCPauseResumControlMediaType](iOS-keytype.md#bytertcpauseresumcontrolmediatype) |


**注意**

+ 该方法仅恢复远端流的接收，并不影响远端流的采集和发送；  
+ 该方法不改变用户的订阅状态以及订阅流的属性。


<span id="ByteRTCRoom-sendusermessage-message-config"></span>
### sendUserMessage:message:config:
```objectivec

- (int64_t)sendUserMessage:(NSString *_Nonnull)userId message:(NSString *_Nonnull)message config:(ByteRTCMessageConfig)config;
```
给房间内指定的用户发送文本消息（P2P）。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| userId | **NSString*** | 消息接收用户的 ID |
| message | **NSString*** | 发送的文本消息内容。  <br/>消息不超过 64 KB。 |
| config | **ByteRTCMessageConfig** | 消息发送的可靠/有序类型，参看 [ByteRTCMessageConfig](iOS-keytype.md#bytertcmessageconfig) |

**返回值**
这次发送消息的编号，从 1 开始递增。


**注意**

+ 在发送房间内文本消息前，必须先调用 [joinRoomByToken:userInfo:roomConfig:](#ByteRTCRoom-joinroombytoken-userinfo-roomconfig) 加入房间。  
+ 调用该函数后会收到一次 [rtcRoom:onUserMessageSendResult:error:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onusermessagesendresult-error) 回调，通知消息发送方发送成功或失败。  
+ 若文本消息发送成功，则 uid 所指定的用户会收到 [rtcRoom:onUserMessageReceived:message:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onusermessagereceived-message) 回调。


<span id="ByteRTCRoom-senduserbinarymessage-message-config"></span>
### sendUserBinaryMessage:message:config:
```objectivec

- (int64_t)sendUserBinaryMessage:(NSString * _Nonnull)uid message:(NSData * _Nonnull)message config:(ByteRTCMessageConfig)config;
```
给房间内指定的用户发送二进制消息（P2P）。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | **NSString*** | 消息接收用户的 ID |
| message | **NSData*** | 发送的二进制消息内容  <br/>消息不超过 64KB。 |
| config | **ByteRTCMessageConfig** | 消息发送的可靠/有序类型，参看 [ByteRTCMessageConfig](iOS-keytype.md#bytertcmessageconfig)。 |

**返回值**
这次发送消息的编号，从 1 开始递增。


**注意**

+ 在发送房间内二进制消息前，必须先调用 [joinRoomByToken:userInfo:roomConfig:](#ByteRTCRoom-joinroombytoken-userinfo-roomconfig) 加入房间。  
+ 调用该函数后会收到一次 [rtcRoom:onUserMessageSendResult:error:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onusermessagesendresult-error) 回调，通知消息发送方发送成功或失败；  
+ 若二进制消息发送成功，则 uid 所指定的用户会收到 [rtcRoom:onUserBinaryMessageReceived:message:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onuserbinarymessagereceived-message) 回调。


<span id="ByteRTCRoom-sendroommessage"></span>
### sendRoomMessage:
```objectivec

- (int64_t)sendRoomMessage:(NSString *_Nonnull)message;
```
给房间内的所有其他用户发送文本消息。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| message | **NSString*** | 发送的文本消息内容。  <br/>消息不超过 64 KB。 |

**返回值**
这次发送消息的编号，从 1 开始递增。


**注意**

+ 在发送房间内文本消息前，必须先调用 [joinRoomByToken:userInfo:roomConfig:](#ByteRTCRoom-joinroombytoken-userinfo-roomconfig) 加入房间。  
+ 调用该函数后会收到一次 [rtcRoom:onRoomMessageSendResult:error:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onroommessagesendresult-error) 回调，通知消息发送方发送成功或失败；  
+ 若文本消息发送成功，则房间内所有远端用户会收到 [rtcRoom:onRoomMessageReceived:message:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onroommessagereceived-message) 回调。


<span id="ByteRTCRoom-sendroombinarymessage"></span>
### sendRoomBinaryMessage:
```objectivec

- (int64_t)sendRoomBinaryMessage:(NSData * _Nonnull)message;
```
给房间内的所有其他用户发送二进制消息。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| message | **NSData*** | 用户发送的二进制广播消息  <br/>消息不超过 64KB。 |

**返回值**
这次发送消息的编号，从 1 开始递增。


**注意**

+ 在房间内广播二进制消息前，必须先调用 [joinRoomByToken:userInfo:roomConfig:](#ByteRTCRoom-joinroombytoken-userinfo-roomconfig) 加入房间。  
+ 调用该函数后会收到一次 [rtcRoom:onRoomMessageSendResult:error:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onroommessagesendresult-error) 回调，通知消息发送方发送成功或失败；  
+ 若二进制消息发送成功，则房间内所有用户会收到 [rtcRoom:onRoomBinaryMessageReceived:message:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onroombinarymessagereceived-message) 回调。


<span id="ByteRTCRoom-startforwardstreamtorooms"></span>
### startForwardStreamToRooms:
```objectivec

- (int)startForwardStreamToRooms:(NSArray <ForwardStreamConfiguration *> * _Nullable)configurations;
```
开始跨房间转发媒体流。
在用户进入房间后调用本接口，实现向多个房间转发媒体流，适用于跨房间连麦等场景。<br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| configurations | **NSArray <ForwardStreamConfiguration*>*** | 跨房间媒体流转发指定房间的信息。参看 [ForwardStreamConfiguration](iOS-keytype.md#forwardstreamconfiguration)。 |

**返回值**

0: 方法调用成功
<0: 方法调用失败  


**注意**

+ 调用本方法后，将在本端触发 [rtcRoom:onForwardStreamStateChanged:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onforwardstreamstatechanged) 回调。
+ 调用本方法后，你可以通过监听 [rtcRoom:onForwardStreamEvent:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onforwardstreamevent) 回调来获取各个目标房间在转发媒体流过程中的相关事件。
+ 开始转发后，目标房间中的用户将接收到本地用户进房 [rtcRoom:onUserJoined:elapsed:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onuserjoined-elapsed) 和发流 [rtcRoom:onUserPublishStream:type:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onuserpublishstream-type)/[rtcRoom:onUserPublishScreen:type:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onuserpublishscreen-type) 的回调。
+ 调用本方法后，可以调用 [updateForwardStreamToRooms:](#ByteRTCRoom-updateforwardstreamtorooms) 更新目标房间信息，例如，增加或减少目标房间等。
+ 调用本方法后，可以调用 [stopForwardStreamToRooms](#ByteRTCRoom-stopforwardstreamtorooms) 停止向所有房间转发媒体流。
+ 调用本方法后，可以调用 [pauseForwardStreamToAllRooms](#ByteRTCRoom-pauseforwardstreamtoallrooms) 暂停向所有房间转发媒体流。


<span id="ByteRTCRoom-updateforwardstreamtorooms"></span>
### updateForwardStreamToRooms:
```objectivec

- (int)updateForwardStreamToRooms:(NSArray <ForwardStreamConfiguration *> * _Nullable)configurations;
```
更新跨房间媒体流转发信息。<br>
通过 [startForwardStreamToRooms:](#ByteRTCRoom-startforwardstreamtorooms) 发起媒体流转发后，可调用本方法增加或者减少目标房间，或更新房间密钥。
调用本方法增加或删减房间后，将在本端触发 [rtcRoom:onForwardStreamStateChanged:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onforwardstreamstatechanged) 回调，包含发生了变动的目标房间中媒体流转发状态。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| configurations | **NSArray <ForwardStreamConfiguration*>*** | 跨房间媒体流转发目标房间信息。参看 [ForwardStreamConfiguration](iOS-keytype.md#forwardstreamconfiguration)。 |

**返回值**

+ 0: 方法调用成功  
+ <0: 方法调用失败  


**注意**

+ 增加目标房间后，新增目标房间中的用户将接收到本地用户进房 [rtcRoom:onUserJoined:elapsed:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onuserjoined-elapsed) 和发布 [rtcRoom:onUserJoined:elapsed:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onuserjoined-elapsed) 的回调。
+ 删减目标房间后，原目标房间中的用户将接收到本地用户停止发布 [rtcRoom:onUserUnpublishStream:type:reason:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onuserunpublishstream-type-reason) 和退房 [rtcRoom:onUserLeave:reason:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onuserleave-reason) 的回调。


<span id="ByteRTCRoom-stopforwardstreamtorooms"></span>
### stopForwardStreamToRooms
```objectivec

- (void)stopForwardStreamToRooms;
```
停止跨房间媒体流转发。
通过 [startForwardStreamToRooms:](#ByteRTCRoom-startforwardstreamtorooms) 发起媒体流转发后，可调用本方法停止向所有目标房间转发媒体流。


**注意**

+ 调用本方法后，将在本端触发 [rtcRoom:onForwardStreamStateChanged:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onforwardstreamstatechanged) 回调。
+ 调用本方法后，原目标房间中的用户将接收到本地用户停止发布 [rtcRoom:onUserUnpublishStream:type:reason:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onuserunpublishstream-type-reason) 和退房 [rtcRoom:onUserLeave:reason:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onuserleave-reason) 的回调。
+ 如果需要停止向指定的房间转发媒体流，请调用 [updateForwardStreamToRooms:](#ByteRTCRoom-updateforwardstreamtorooms) 更新房间信息。
+ 如果需要暂停转发，请调用 [pauseForwardStreamToAllRooms](#ByteRTCRoom-pauseforwardstreamtoallrooms)，并在之后随时调用 [resumeForwardStreamToAllRooms](#ByteRTCRoom-resumeforwardstreamtoallrooms) 快速恢复转发。


<span id="ByteRTCRoom-pauseforwardstreamtoallrooms"></span>
### pauseForwardStreamToAllRooms
```objectivec

- (void)pauseForwardStreamToAllRooms;
```
暂停跨房间媒体流转发。
通过 [startForwardStreamToRooms:](#ByteRTCRoom-startforwardstreamtorooms) 发起媒体流转发后，可调用本方法暂停向所有目标房间转发媒体流。
调用本方法暂停向所有目标房间转发后，你可以随时调用 [resumeForwardStreamToAllRooms](#ByteRTCRoom-resumeforwardstreamtoallrooms) 快速恢复转发。


**注意**
调用本方法后，目标房间中的用户将接收到本地用户停止发布 [rtcRoom:onUserUnpublishStream:type:reason:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onuserunpublishstream-type-reason) 和退房 [rtcRoom:onUserLeave:reason:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onuserleave-reason) 的回调。

<span id="ByteRTCRoom-resumeforwardstreamtoallrooms"></span>
### resumeForwardStreamToAllRooms
```objectivec

- (void)resumeForwardStreamToAllRooms;
```
恢复跨房间媒体流转发。
调用 [pauseForwardStreamToAllRooms](#ByteRTCRoom-pauseforwardstreamtoallrooms) 暂停转发之后，调用本方法恢复向所有目标房间转发媒体流。


**注意**
目标房间中的用户将接收到本地用户进房 [rtcRoom:onUserJoined:elapsed:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onuserjoined-elapsed) 和发布 [rtcRoom:onUserJoined:elapsed:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onuserjoined-elapsed) 的回调。


<span id="ByteRTCRoom-getrangeaudio"></span>
### getRangeAudio
```objectivec

- (ByteRTCRangeAudio *_Nullable)getRangeAudio;
```
获取范围语音接口实例。

**返回值**
方法调用结果： 

+ ByteRTCRangeAudio：成功，返回一个 [ByteRTCRangeAudio](#bytertcrangeaudio) 实例。  
+ NULL：失败，当前 SDK 不支持范围语音功能。


**注意**
首次调用该方法须在创建房间后、加入房间前。范围语音相关 API 和调用时序详见[范围语音](https://www.volcengine.com/docs/6348/114727)。

<span id="ByteRTCRoom-getspatialaudio"></span>
### getSpatialAudio
```objectivec

- (ByteRTCSpatialAudio *_Nullable)getSpatialAudio;
```
获取空间音频接口实例。  <br>

**返回值**
方法调用结果：  

+ ByteRTCSpatialAudio：成功，返回一个 [ByteRTCSpatialAudio](#bytertcspatialaudio) 实例。  
+ NULL：失败，当前 SDK 不支持空间音频功能。


**注意**

+ 首次调用该方法须在创建房间后、加入房间前。 空间音频相关 API 和调用时序详见[空间音频](https://www.volcengine.com/docs/6348/93903)。 
+ 只有在使用支持真双声道播放的设备时，才能开启空间音频效果；  
+ 机型性能不足可能会导致音频卡顿，使用低端机时，不建议开启空间音频效果；  
+ SDK 最多支持 30 个用户同时开启空间音频功能。


<span id="ByteRTCRoom-enablecloudrending"></span>
### enableCloudRending:
```objectivec

- (int)enableCloudRending:(NSString *_Nonnull)rendingInfo;
```
按照传入的布局信息开启云端渲染。 <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rendingInfo | **NSString*** | 渲染功能相关参数。 |

**返回值**
方法调用结果。  

+  0: 方法调用成功  
+  < 0: 方法调用失败  


<span id="ByteRTCRoom-updatecloudrending"></span>
### updateCloudRending:
```objectivec

- (int)updateCloudRending:(NSString *_Nonnull)rendingInfo;
```
按照传入的布局信息更新云端渲染。 <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rendingInfo | **NSString*** | 渲染功能相关参数。 |

**返回值**
方法调用结果。  

+  0: 方法调用成功  
+ < 0: 方法调用失败  


<span id="ByteRTCRoom-disablecloudrending"></span>
### disableCloudRending
```objectivec

- (int)disableCloudRending;
```
停止云端渲染。 <br>

**返回值**
方法调用结果。  

+  0: 方法调用成功  
+ < 0: 方法调用失败  


# ByteRTCVideo
```objectivec
@interface ByteRTCVideo : NSObject
```

SDK 回调给应用层的 delegate 对象，详见 [ByteRTCVideoDelegate](iOS-callback.md#bytertcvideodelegate)


## 静态函数

| 返回 | 名称 |
| --- | --- |
| **void** | [destroyRTCVideo](#ByteRTCVideo-destroyrtcvideo) |
| **NSString*** | [getSdkVersion](#ByteRTCVideo-getsdkversion) |
| **NSString*** | [getErrorDescription:](#ByteRTCVideo-geterrordescription) |


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **ByteRTCVideo*** | [createRTCVideo:delegate:parameters:](#ByteRTCVideo-creatertcvideo-delegate-parameters) |
| **int** | [setAudioSourceType:](#ByteRTCVideo-setaudiosourcetype) |
| **int** | [setAudioRenderType:](#ByteRTCVideo-setaudiorendertype) |
| **void** | [startAudioCapture](#ByteRTCVideo-startaudiocapture) |
| **void** | [stopAudioCapture](#ByteRTCVideo-stopaudiocapture) |
| **void** | [setAudioScenario:](#ByteRTCVideo-setaudioscenario) |
| **void** | [setAudioProfile:](#ByteRTCVideo-setaudioprofile) |
| **void** | [setVoiceChangerType:](#ByteRTCVideo-setvoicechangertype) |
| **void** | [setVoiceReverbType:](#ByteRTCVideo-setvoicereverbtype) |
| **void** | [setCaptureVolume:volume:](#ByteRTCVideo-setcapturevolume-volume) |
| **void** | [setPlaybackVolume:](#ByteRTCVideo-setplaybackvolume) |
| **void** | [enableAudioPropertiesReport:](#ByteRTCVideo-enableaudiopropertiesreport) |
| **void** | [setRemoteAudioPlaybackVolume:remoteUid:playVolume:](#ByteRTCVideo-setremoteaudioplaybackvolume-remoteuid-playvolume) |
| **void** | [setEarMonitorMode:](#ByteRTCVideo-setearmonitormode) |
| **void** | [setEarMonitorVolume:](#ByteRTCVideo-setearmonitorvolume) |
| **void** | [setLocalVoicePitch:](#ByteRTCVideo-setlocalvoicepitch) |
| **void** | [enableVocalInstrumentBalance:](#ByteRTCVideo-enablevocalinstrumentbalance) |
| **void** | [enablePlaybackDucking:](#ByteRTCVideo-enableplaybackducking) |
| **void** | [setLocalVideoSink:withSink:withPixelFormat:](#ByteRTCVideo-setlocalvideosink-withsink-withpixelformat) |
| **void** | [setRemoteVideoSink:withSink:withPixelFormat:](#ByteRTCVideo-setremotevideosink-withsink-withpixelformat) |
| **int** | [enableSimulcastMode:](#ByteRTCVideo-enablesimulcastmode) |
| **int** | [SetMaxVideoEncoderConfig:](#ByteRTCVideo-setmaxvideoencoderconfig) |
| **int** | [SetVideoEncoderConfig:](#ByteRTCVideo-setvideoencoderconfig) |
| **int** | [SetScreenVideoEncoderConfig:](#ByteRTCVideo-setscreenvideoencoderconfig) |
| **int** | [setVideoCaptureConfig:](#ByteRTCVideo-setvideocaptureconfig) |
| **int** | [setLocalVideoCanvas:withCanvas:](#ByteRTCVideo-setlocalvideocanvas-withcanvas) |
| **int** | [updateLocalVideoCanvas:withRenderMode:withBackgroundColor:](#ByteRTCVideo-updatelocalvideocanvas-withrendermode-withbackgroundcolor) |
| **int** | [setRemoteVideoCanvas:withIndex:withCanvas:](#ByteRTCVideo-setremotevideocanvas-withindex-withcanvas) |
| **int** | [updateRemoteStreamVideoCanvas:withUserId:withIndex:withRenderMode:withBackgroundColor:](#ByteRTCVideo-updateremotestreamvideocanvas-withuserid-withindex-withrendermode-withbackgroundcolor) |
| **void** | [startVideoCapture](#ByteRTCVideo-startvideocapture) |
| **void** | [stopVideoCapture](#ByteRTCVideo-stopvideocapture) |
| **int** | [setLocalVideoMirrorType:](#ByteRTCVideo-setlocalvideomirrortype) |
| **int** | [setVideoRotationMode:](#ByteRTCVideo-setvideorotationmode) |
| **void** | [setVideoOrientation:](#ByteRTCVideo-setvideoorientation) |
| **int** | [switchCamera:](#ByteRTCVideo-switchcamera) |
| **int** | [checkVideoEffectLicense:](#ByteRTCVideo-checkvideoeffectlicense) |
| **int** | [enableVideoEffect:](#ByteRTCVideo-enablevideoeffect) |
| **void** | [setVideoEffectAlgoModelPath:](#ByteRTCVideo-setvideoeffectalgomodelpath) |
| **int** | [setVideoEffectNodes:](#ByteRTCVideo-setvideoeffectnodes) |
| **int** | [updateVideoEffectNode:nodeKey:nodeValue:](#ByteRTCVideo-updatevideoeffectnode-nodekey-nodevalue) |
| **int** | [setVideoEffectColorFilter:](#ByteRTCVideo-setvideoeffectcolorfilter) |
| **int** | [setVideoEffectColorFilterIntensity:](#ByteRTCVideo-setvideoeffectcolorfilterintensity) |
| **int** | [setBackgroundSticker:source:](#ByteRTCVideo-setbackgroundsticker-source) |
| **int** | [enableEffectBeauty:](#ByteRTCVideo-enableeffectbeauty) |
| **int** | [setBeautyIntensity:withIntensity:](#ByteRTCVideo-setbeautyintensity-withintensity) |
| **int** | [setCameraZoomRatio:](#ByteRTCVideo-setcamerazoomratio) |
| **float** | [getCameraZoomMaxRatio](#ByteRTCVideo-getcamerazoommaxratio) |
| **bool** | [isCameraZoomSupported](#ByteRTCVideo-iscamerazoomsupported) |
| **bool** | [isCameraTorchSupported](#ByteRTCVideo-iscameratorchsupported) |
| **int** | [setCameraTorch:](#ByteRTCVideo-setcameratorch) |
| **bool** | [isCameraFocusPositionSupported](#ByteRTCVideo-iscamerafocuspositionsupported) |
| **int** | [setCameraFocusPosition:](#ByteRTCVideo-setcamerafocusposition) |
| **bool** | [isCameraExposurePositionSupported](#ByteRTCVideo-iscameraexposurepositionsupported) |
| **int** | [setCameraExposurePosition:](#ByteRTCVideo-setcameraexposureposition) |
| **int** | [setCameraExposureCompensation:](#ByteRTCVideo-setcameraexposurecompensation) |
| **int** | [registerFaceDetectionObserver:withInterval:](#ByteRTCVideo-registerfacedetectionobserver-withinterval) |
| **int** | [sendSEIMessage:andMessage:andRepeatCount:](#ByteRTCVideo-sendseimessage-andmessage-andrepeatcount) |
| **int** | [registerLocalVideoProcessor:withConfig:](#ByteRTCVideo-registerlocalvideoprocessor-withconfig) |
| **void** | [registerLocalEncodedVideoFrameObserver:](#ByteRTCVideo-registerlocalencodedvideoframeobserver) |
| **int** | [setAudioRoute:](#ByteRTCVideo-setaudioroute) |
| **ByteRTCAudioRoute** | [getAudioRoute](#ByteRTCVideo-getaudioroute) |
| **void** | [enableExternalSoundCard:](#ByteRTCVideo-enableexternalsoundcard) |
| **int** | [setDefaultAudioRoute:](#ByteRTCVideo-setdefaultaudioroute) |
| **int** | [startLiveTranscoding:transcoding:observer:](#ByteRTCVideo-startlivetranscoding-transcoding-observer) |
| **int** | [stopLiveTranscoding:](#ByteRTCVideo-stoplivetranscoding) |
| **int** | [updateLiveTranscoding:transcoding:](#ByteRTCVideo-updatelivetranscoding-transcoding) |
| **int** | [startPushSingleStreamToCDN:singleStream:observer:](#ByteRTCVideo-startpushsinglestreamtocdn-singlestream-observer) |
| **int** | [stopPushStreamToCDN:](#ByteRTCVideo-stoppushstreamtocdn) |
| **int** | [startPushPublicStream:withLayout:](#ByteRTCVideo-startpushpublicstream-withlayout) |
| **int** | [stopPushPublicStream:](#ByteRTCVideo-stoppushpublicstream) |
| **int** | [updatePublicStreamParam:withLayout:](#ByteRTCVideo-updatepublicstreamparam-withlayout) |
| **int** | [startPlayPublicStream:](#ByteRTCVideo-startplaypublicstream) |
| **int** | [stopPlayPublicStream:](#ByteRTCVideo-stopplaypublicstream) |
| **int** | [setPublicStreamVideoCanvas:withCanvas:](#ByteRTCVideo-setpublicstreamvideocanvas-withcanvas) |
| **int** | [setPublicStreamVideoSink:withSink:withPixelFormat:](#ByteRTCVideo-setpublicstreamvideosink-withsink-withpixelformat) |
| **BOOL** | [pushExternalVideoFrame:time:](#ByteRTCVideo-pushexternalvideoframe-time) |
| **BOOL** | [pushExternalVideoFrame:time:rotation:](#ByteRTCVideo-pushexternalvideoframe-time-rotation) |
| **BOOL** | [pushExternalVideoFrame:time:rotation:extendedData:supplementaryInfo:](#ByteRTCVideo-pushexternalvideoframe-time-rotation-extendeddata-supplementaryinfo) |
| **BOOL** | [pushExternalByteVideoFrame:](#ByteRTCVideo-pushexternalbytevideoframe) |
| **void** | [enableAudioFrameCallback:format:](#ByteRTCVideo-enableaudioframecallback-format) |
| **void** | [disableAudioFrameCallback:](#ByteRTCVideo-disableaudioframecallback) |
| **BOOL** | [setAudioFrameObserver:](#ByteRTCVideo-setaudioframeobserver) |
| **BOOL** | [registerAudioProcessor:](#ByteRTCVideo-registeraudioprocessor) |
| **void** | [enableAudioProcessor:audioFormat:](#ByteRTCVideo-enableaudioprocessor-audioformat) |
| **void** | [disableAudioProcessor:](#ByteRTCVideo-disableaudioprocessor) |
| **int** | [pushExternalAudioFrame:](#ByteRTCVideo-pushexternalaudioframe) |
| **int** | [pullExternalAudioFrame:](#ByteRTCVideo-pullexternalaudioframe) |
| **int** | [setBusinessId:](#ByteRTCVideo-setbusinessid) |
| **int** | [feedback:desc:](#ByteRTCVideo-feedback-desc) |
| **int** | [setPublishFallbackOption:](#ByteRTCVideo-setpublishfallbackoption) |
| **int** | [setSubscribeFallbackOption:](#ByteRTCVideo-setsubscribefallbackoption) |
| **int** | [setRemoteUserPriority:InRoomId:uid:](#ByteRTCVideo-setremoteuserpriority-inroomid-uid) |
| **void** | [setEncryptType:key:](#ByteRTCVideo-setencrypttype-key) |
| **void** | [setCustomizeEncryptHandler:](#ByteRTCVideo-setcustomizeencrypthandler) |
| **ByteRTCRoom*** | [createRTCRoom:](#ByteRTCVideo-creatertcroom) |
| **void** | [pushScreenCaptureFrame:time:rotation:](#ByteRTCVideo-pushscreencaptureframe-time-rotation) |
| **void** | [setExtensionConfig:](#ByteRTCVideo-setextensionconfig) |
| **void** | [startScreenCapture:bundleId:](#ByteRTCVideo-startscreencapture-bundleid) |
| **void** | [updateScreenCapture:](#ByteRTCVideo-updatescreencapture) |
| **void** | [stopScreenCapture](#ByteRTCVideo-stopscreencapture) |
| **void** | [sendScreenCaptureExtensionMessage:](#ByteRTCVideo-sendscreencaptureextensionmessage) |
| **void** | [setRuntimeParameters:](#ByteRTCVideo-setruntimeparameters) |
| **void** | [startASR:handler:](#ByteRTCVideo-startasr-handler) |
| **void** | [stopASR](#ByteRTCVideo-stopasr) |
| **int** | [startFileRecording:withRecordingConfig:type:](#ByteRTCVideo-startfilerecording-withrecordingconfig-type) |
| **void** | [stopFileRecording:](#ByteRTCVideo-stopfilerecording) |
| **ByteRTCAudioMixingManager*** | [getAudioMixingManager](#ByteRTCVideo-getaudiomixingmanager) |
| **void** | [login:uid:](#ByteRTCVideo-login-uid) |
| **void** | [logout](#ByteRTCVideo-logout) |
| **void** | [updateLoginToken:](#ByteRTCVideo-updatelogintoken) |
| **void** | [setServerParams:url:](#ByteRTCVideo-setserverparams-url) |
| **void** | [getPeerOnlineStatus:](#ByteRTCVideo-getpeeronlinestatus) |
| **int64_t** | [sendUserMessageOutsideRoom:message:config:](#ByteRTCVideo-sendusermessageoutsideroom-message-config) |
| **int64_t** | [sendUserBinaryMessageOutsideRoom:message:config:](#ByteRTCVideo-senduserbinarymessageoutsideroom-message-config) |
| **int64_t** | [sendServerMessage:](#ByteRTCVideo-sendservermessage) |
| **int64_t** | [sendServerBinaryMessage:](#ByteRTCVideo-sendserverbinarymessage) |
| **ByteRTCNetworkDetectionStartReturn** | [startNetworkDetection:uplinkBandwidth:downlink:downlinkBandwidth:](#ByteRTCVideo-startnetworkdetection-uplinkbandwidth-downlink-downlinkbandwidth) |
| **void** | [stopNetworkDetection](#ByteRTCVideo-stopnetworkdetection) |
| **void** | [setScreenAudioSourceType:](#ByteRTCVideo-setscreenaudiosourcetype) |
| **void** | [setScreenAudioStreamIndex:](#ByteRTCVideo-setscreenaudiostreamindex) |
| **int** | [pushScreenAudioFrame:](#ByteRTCVideo-pushscreenaudioframe) |
| **void** | [setVideoSourceType:WithStreamIndex:](#ByteRTCVideo-setvideosourcetype-withstreamindex) |
| **void** | [setExternalVideoEncoderEventHandler:](#ByteRTCVideo-setexternalvideoencodereventhandler) |
| **BOOL** | [pushExternalEncodedVideoFrame:withVideoIndex:withEncodedVideoFrame:](#ByteRTCVideo-pushexternalencodedvideoframe-withvideoindex-withencodedvideoframe) |
| **void** | [setVideoDecoderConfig:withVideoDecoderConfig:](#ByteRTCVideo-setvideodecoderconfig-withvideodecoderconfig) |
| **void** | [requestRemoteVideoKeyFrame:](#ByteRTCVideo-requestremotevideokeyframe) |
| **void** | [registerRemoteEncodedVideoFrameObserver:](#ByteRTCVideo-registerremoteencodedvideoframeobserver) |
| **int** | [sendStreamSyncInfo:config:](#ByteRTCVideo-sendstreamsyncinfo-config) |
| **int** | [startEchoTest:playDelay:](#ByteRTCVideo-startechotest-playdelay) |
| **int** | [stopEchoTest](#ByteRTCVideo-stopechotest) |
| **void** | [SetVideoWatermark:WithImagePath:WithRtcWatermarkConfig:](#ByteRTCVideo-setvideowatermark-withimagepath-withrtcwatermarkconfig) |
| **void** | [ClearVideoWatermark:](#ByteRTCVideo-clearvideowatermark) |
| **NSInteger** | [takeLocalSnapshot:callback:](#ByteRTCVideo-takelocalsnapshot-callback) |
| **NSInteger** | [takeRemoteSnapshot:callback:](#ByteRTCVideo-takeremotesnapshot-callback) |
| **void** | [startCloudProxy:](#ByteRTCVideo-startcloudproxy) |
| **void** | [stopCloudProxy](#ByteRTCVideo-stopcloudproxy) |
| **ByteRTCSingScoringManager*** | [getSingScoringManager](#ByteRTCVideo-getsingscoringmanager) |
| **ByteRTCKTVManager*** | [getKTVManager](#ByteRTCVideo-getktvmanager) |


## 函数说明
<span id="ByteRTCVideo-destroyrtcvideo"></span>
### destroyRTCVideo
```objectivec

+ (void)destroyRTCVideo;
```
销毁引擎实例对象


**注意**

+ 请确保和需要销毁的 [ByteRTCVideo](#bytertcvideo) 实例相关的业务场景全部结束后，才调用此方法  
+ 该方法在调用之后，会销毁所有和此 [ByteRTCVideo](#bytertcvideo) 实例相关的内存，并且停止与媒体服务器的任何交互  
+ 调用本方法会启动 SDK 退出逻辑。引擎线程会保留，直到退出逻辑完成。因此，不要在回调线程中直接调用此 API，也不要在回调中等待主线程的执行，并同时在主线程调用本方法。不然会造成死锁。  
+ 可以通过 Objective-C 的ARC机制，在 dealloc 时自动触发销毁逻辑


<span id="ByteRTCVideo-getsdkversion"></span>
### getSdkVersion
```objectivec

+ (NSString * _Nonnull)getSdkVersion;
```
获取 SDK 当前的版本号。

**返回值**
SDK 当前的版本号。


<span id="ByteRTCVideo-geterrordescription"></span>
### getErrorDescription:
```objectivec

+ (NSString * _Nonnull)getErrorDescription:(NSInteger)code;
```
获取 SDK 内各种错误码、警告码的描述文字。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| code | **NSInteger** | 通过 [rtcEngine:onWarning:](iOS-callback#ByteRTCVideoDelegate-rtcengine-onwarning) 和 [rtcEngine:onError:](iOS-callback#ByteRTCVideoDelegate-rtcengine-onerror) 回调获得的值，<br/>具体可以参考 [ByteRTCWarningCode](iOS-errorcode.md#bytertcwarningcode) 和 [ByteRTCErrorCode](iOS-errorcode.md#bytertcerrorcode) 。 |

**返回值**
描述文字。


<span id="ByteRTCVideo-creatertcvideo-delegate-parameters"></span>
### createRTCVideo:delegate:parameters:
```objectivec

+ (ByteRTCVideo * _Nullable) createRTCVideo:(NSString * _Nonnull)appId delegate:(id<ByteRTCVideoDelegate> _Nullable)delegate parameters:(NSDictionary * _Nonnull)parameters;
```
创建引擎对象。<br>
如果当前进程中未创建引擎实例，那么你必须先使用此方法，以使用 RTC 提供的各种音视频能力。  <br>
如果当前进程中已创建了引擎实例，再次调用此方法时，会返回已创建的引擎实例。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| appId | **NSString*** | 每个应用的唯一标识符，由 RTC 控制台随机生成的。<br/>不同的 AppId 生成的实例在 RTC 中进行音视频通话完全独立，无法互通。 |
| delegate | **id<ByteRTCVideoDelegate>** | SDK 回调给应用层的 delegate，详见 [ByteRTCVideoDelegate](iOS-callback.md#bytertcvideodelegate) |
| parameters | **NSDictionary*** | 私有参数。如需使用请联系技术支持人员。 |

**返回值**
可用的 [ByteRTCVideo](#bytertcvideo) 实例


<span id="ByteRTCVideo-setaudiosourcetype"></span>
### setAudioSourceType:
```objectivec

- (int)setAudioSourceType:(ByteRTCAudioSourceType) type;
```
切换音频采集方式

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| type | **ByteRTCAudioSourceType** | 音频数据源，详见 [ByteRTCAudioSourceType](iOS-keytype.md#bytertcaudiosourcetype)。<br/>默认使用内部音频采集。音频采集和渲染方式无需对应。 |

**返回值**
方法调用结果：  

+ \>0: 切换成功。
+ -1：切换失败。


**注意**

+ 进房前后调用此方法均有效。
+ 如果你调用此方法由内部采集切换至自定义采集，SDK 会自动关闭内部采集。然后，调用 [pushExternalAudioFrame:](#ByteRTCVideo-pushexternalaudioframe) 推送自定义采集的音频数据到 RTC SDK 用于传输。 
+ 如果你调用此方法由自定义采集切换至内部采集，你必须再调用 [startAudioCapture](#ByteRTCVideo-startaudiocapture) 手动开启内部采集。


<span id="ByteRTCVideo-setaudiorendertype"></span>
### setAudioRenderType:
```objectivec

- (int)setAudioRenderType:(ByteRTCAudioRenderType) type;
```
切换音频渲染方式

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| type | **ByteRTCAudioRenderType** | 音频输出类型，详见 [ByteRTCAudioRenderType](iOS-keytype.md#bytertcaudiorendertype) <br/>默认使用内部音频渲染。音频采集和渲染方式无需对应。 |

**返回值**
方法调用结果：  

+ \>0: 切换成功。
+ -1：切换失败。


**注意**

+ 进房前后调用此方法均有效。
+ 如果你调用此方法切换至自定义渲染，调用 [pullExternalAudioFrame:](#ByteRTCVideo-pullexternalaudioframe) 获取音频数据。 


<span id="ByteRTCVideo-startaudiocapture"></span>
### startAudioCapture
```objectivec

- (void)startAudioCapture;
```
开启内部音频采集。默认为关闭状态。  <br>
内部采集是指：使用 RTC SDK 内置的音频采集机制进行视频采集。
调用该方法开启后，本地用户会收到 [rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onaudiodevicestatechanged-device_type-device_state-device_error) 的回调。  <br>
非隐身用户进房后调用该方法，房间中的其他用户会收到 [rtcEngine:onUserStartAudioCapture:uid:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onuserstartaudiocapture-uid) 的回调。


**注意**

+ 若未取得当前设备的麦克风权限，调用该方法后会触发 [rtcEngine:onWarning:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onwarning) 回调。  
+ 调用 [stopAudioCapture](#ByteRTCVideo-stopaudiocapture) 可以关闭音频采集设备，否则，SDK 只会在销毁引擎的时候自动关闭设备。  
+ 由于不同硬件设备初始化响应时间不同，频繁调用 [stopAudioCapture](#ByteRTCVideo-stopaudiocapture) 和本接口闭麦/开麦可能出现短暂无声问题，建议使用 [publishStream:](#ByteRTCRoom-publishstream)/[unpublishStream:](#ByteRTCRoom-unpublishstream) 实现临时闭麦和重新开麦。
+ 创建引擎后，无论是否发布音频数据，你都可以调用该方法开启音频采集，并且调用后方可发布音频。  
+ 尚未进房并且已使用自定义采集时，关闭自定义采集后并不会自动开启内部采集。你需调用此方法手动开启内部采集。
+ 如果需要从自定义音频采集切换为内部音频采集，你必须先停止发布流，调用 [setAudioSourceType:](#ByteRTCVideo-setaudiosourcetype) 关闭自定义采集，再调用此方法手动开启内部采集。


<span id="ByteRTCVideo-stopaudiocapture"></span>
### stopAudioCapture
```objectivec

- (void)stopAudioCapture;
```
关闭内部音频采集。默认为关闭状态。  <br>
内部采集是指：使用 RTC SDK 内置的音频采集机制进行视频采集。
调用该方法，本地用户会收到 [rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onaudiodevicestatechanged-device_type-device_state-device_error) 的回调。  <br>
非隐身用户进房后调用该方法，房间中的其他用户会收到 [rtcEngine:onUserStopAudioCapture:uid:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onuserstopaudiocapture-uid) 的回调。


**注意**

+ 调用 [startAudioCapture](#ByteRTCVideo-startaudiocapture) 可以开启音频采集设备。  
+ 如果不调用本方法停止内部视频采集，则只有当销毁引擎实例时，内部音频采集才会停止。


<span id="ByteRTCVideo-setaudioscenario"></span>
### setAudioScenario:
```objectivec

- (void)setAudioScenario:(ByteRTCAudioScenarioType)audioScenario;
```
设置音频场景类型  <br>
你可以根据你的应用所在场景，选择合适的音频场景类型。  <br>
选择音频场景后，SDK 会自动根据客户端音频采集播放设备和状态，适用通话音量/媒体音量。  <br>
本方法在进房前和进房后设置均可生效。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioScenario | **ByteRTCAudioScenarioType** | 音频场景类型，参看 [ByteRTCAudioScenarioType](iOS-keytype.md#bytertcaudioscenariotype)。 |


**注意**

+ 通话音量更适合通话、会议等对信息准确度更高的场景。通话音量会激活系统硬件信号处理，使通话声音更清晰。同时，音量无法降低到 0。  
+ 媒体音量更适合娱乐场景，因其声音的表现力会更强。媒体音量下，最低音量可以为 0。


<span id="ByteRTCVideo-setaudioprofile"></span>
### setAudioProfile:
```objectivec

- (void)setAudioProfile:(ByteRTCAudioProfileType)audioProfile;
```
设置音质档位。当所选的 [ByteRTCRoomProfile](iOS-keytype.md#bytertcroomprofile) 中的音频参数无法满足你的场景需求时，调用本接口切换的音质档位。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioProfile | **ByteRTCAudioProfileType** | 音质档位，参看 [ByteRTCAudioProfileType](iOS-keytype.md#bytertcaudioprofiletype) |


**注意**

+ 该方法在进房前后均可调用；  
+ 支持通话过程中动态切换音质档位。


<span id="ByteRTCVideo-setvoicechangertype"></span>
### setVoiceChangerType:
```objectivec

- (void)setVoiceChangerType:(ByteRTCVoiceChangerType)voiceChanger;
```
设置变声特效类型

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| voiceChanger | **ByteRTCVoiceChangerType** | 变声特效类型，参看 [ByteRTCVoiceChangerType](iOS-keytype.md#bytertcvoicechangertype) |


**注意**

+ 在进房前后都可设置。  
+ 对 RTC SDK 内部采集的音频和自定义采集的音频都生效。 
+ 只对单声道音频生效。
+ 只在包含美声特效能力的 SDK 中有效。
+ 与 [setVoiceReverbType:](#ByteRTCVideo-setvoicereverbtype) 互斥，后设置的特效会覆盖先设置的特效。 
+ 使用本接口前，请联系 RTC 技术支持了解更多详情。 


<span id="ByteRTCVideo-setvoicereverbtype"></span>
### setVoiceReverbType:
```objectivec

- (void)setVoiceReverbType:(ByteRTCVoiceReverbType)voiceReverb;
```
设置混响特效类型

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| voiceReverb | **ByteRTCVoiceReverbType** | 混响特效类型，参看 [ByteRTCVoiceReverbType](iOS-keytype.md#bytertcvoicereverbtype) |


**注意**

+ 在进房前后都可设置。  
+ 对 RTC SDK 内部采集的音频和自定义采集的音频都生效。 
+ 只对单声道音频生效。
+ 只在包含美声特效能力的 SDK 中有效。
+ 与 [setVoiceChangerType:](#ByteRTCVideo-setvoicechangertype) 互斥，后设置的特效会覆盖先设置的特效。
+ 使用本接口前，请联系 RTC 技术支持了解更多详情。 


<span id="ByteRTCVideo-setcapturevolume-volume"></span>
### setCaptureVolume:volume:
```objectivec

- (void)setCaptureVolume:(ByteRTCStreamIndex)index volume:(int)volume;
```
调节音频采集音量

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| index | **ByteRTCStreamIndex** | 流索引，指定调节主流还是调节屏幕流的音量，参看 [ByteRTCStreamIndex](iOS-keytype.md#bytertcstreamindex) |
| volume | **int** | 采集的音量值和原始音量的比值，范围是 [0, 400]，单位为 %，自带溢出保护。只改变音频数据的音量信息，不涉及本端硬件的音量调节。<br/>为保证更好的通话质量，建议将 volume 值设为 [0,100]。<br/>• 0：静音  <br/>• 100：原始音量  <br/>• 400: 最大可为原始音量的 4 倍(自带溢出保护) |


**注意**
在开启音频采集前后，你都可以使用此接口设定采集音量。

<span id="ByteRTCVideo-setplaybackvolume"></span>
### setPlaybackVolume:
```objectivec

- (void)setPlaybackVolume:(NSInteger)volume;
```
调节本地播放的所有远端用户混音后的音量。播放音频前或播放音频时，你都可以使用此接口设定播放音量。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| volume | **NSInteger** | 音频播放音量值和原始音量的比值，范围是 [0, 400]，单位为 %，自带溢出保护。只改变音频数据的音量信息，不涉及本端硬件的音量调节。  <br/>为保证更好的通话质量，建议将 volume 值设为 [0,100]。  <br/>• 0: 静音  <br/>• 100: 原始音量  <br/>• 400: 最大可为原始音量的 4 倍(自带溢出保护) |


<span id="ByteRTCVideo-enableaudiopropertiesreport"></span>
### enableAudioPropertiesReport:
```objectivec

- (void)enableAudioPropertiesReport:(ByteRTCAudioPropertiesConfig* _Nonnull)config;
```
启用音频信息提示。  <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| config | **ByteRTCAudioPropertiesConfig*** | 详见 [ByteRTCAudioPropertiesConfig](iOS-keytype.md#bytertcaudiopropertiesconfig) |


**注意**
开启提示后，你可以：  

+ 通过 [rtcEngine:onLocalAudioPropertiesReport:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onlocalaudiopropertiesreport) 回调获取本地麦克风和屏幕音频流采集的音频信息；  
+ 通过 [rtcEngine:onRemoteAudioPropertiesReport:totalRemoteVolume:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onremoteaudiopropertiesreport-totalremotevolume) 回调获取订阅的远端用户的音频信息。  
+ 通过 [rtcEngine:onActiveSpeaker:uid:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onactivespeaker-uid) 回调获取房间内的最活跃用户信息。


<span id="ByteRTCVideo-setremoteaudioplaybackvolume-remoteuid-playvolume"></span>
### setRemoteAudioPlaybackVolume:remoteUid:playVolume:
```objectivec

- (void)setRemoteAudioPlaybackVolume:(NSString *_Nonnull)room_id remoteUid:(NSString *_Nonnull)uid playVolume:(NSInteger)volume;
```
调节来自远端用户的音频播放音量

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| room_id | **NSString*** | 音频来源用户所在的房间 ID |
| uid | **NSString*** | 音频来源的远端用户 ID |
| volume | **NSInteger** | 音频播放音量值和原始音量的比值，范围是 [0, 400]，单位为 %，自带溢出保护。只改变音频数据的音量信息，不涉及本端硬件的音量调节。为保证更好的通话质量，建议将 volume 值设为 [0,100]。 <br/>• 0: 静音  <br/>• 100: 原始音量，默认值  <br/>• 400: 最大可为原始音量的 4 倍(自带溢出保护) |


<span id="ByteRTCVideo-setearmonitormode"></span>
### setEarMonitorMode:
```objectivec

- (void)setEarMonitorMode:(ByteRTCEarMonitorMode)mode;
```
开启/关闭耳返功能。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mode | **ByteRTCEarMonitorMode** | 是否开启耳返功能，参看 [ByteRTCEarMonitorMode](iOS-keytype.md#bytertcearmonitormode)。 |


**注意**

+ 耳返功能仅适用于由 RTC SDK 内部采集的音频。  
+ 使用耳返必须佩戴耳机。为保证低延时耳返最佳体验，建议佩戴有线耳机。  
+ 受 iOS 平台限制，RTC 仅支持软件耳返功能。


<span id="ByteRTCVideo-setearmonitorvolume"></span>
### setEarMonitorVolume:
```objectivec

- (void)setEarMonitorVolume:(NSInteger)volume;
```
设置耳返的音量。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| volume | **NSInteger** | 耳返的音量，取值范围：[0,100]，单位：% |


**注意**
设置耳返音量前，你必须先调用 [setEarMonitorMode:](#ByteRTCVideo-setearmonitormode) 打开耳返功能。

<span id="ByteRTCVideo-setlocalvoicepitch"></span>
### setLocalVoicePitch:
```objectivec

- (void)setLocalVoicePitch:(NSInteger)pitch;
```
开启本地语音变调功能，多用于 K 歌场景。  <br>
使用该方法，你可以对本地语音的音调进行升调或降调等调整。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| pitch | **NSInteger** | 相对于语音原始音调的升高/降低值，取值范围[-12，12]，默认值为 0，即不做调整。  <br/>取值范围内每相邻两个值的音高距离相差半音，正值表示升调，负值表示降调，设置的绝对值越大表示音调升高或降低越多。  <br/>超出取值范围则设置失败，并且会触发 [rtcEngine:onWarning:](iOS-callback#ByteRTCVideoDelegate-rtcengine-onwarning) 回调，提示 [ByteRTCWarningCode](iOS-errorcode.md#bytertcwarningcode) 错误码为 `WARNING_CODE_SET_SCREEN_STREAM_INVALID_VOICE_PITCH` 设置语音音调不合法 |


<span id="ByteRTCVideo-enablevocalinstrumentbalance"></span>
### enableVocalInstrumentBalance:
```objectivec

- (void)enableVocalInstrumentBalance:(BOOL)enable;
```
开启/关闭音量均衡功能。  <br>
开启音量均衡功能后，人声的响度会调整为 -16lufs。如果已调用 [setAudioMixingLoudness:loudness:](#ByteRTCAudioMixingManager-setaudiomixingloudness-loudness) 传入了混音音乐的原始响度，此音乐播放时，响度会调整为 -20lufs。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| enable | **BOOL** | 是否开启音量均衡功能：  <br/>• True: 是  <br/>• False: 否 |


**注意**
该接口须在调用 [startAudioMixing:filePath:config:](#ByteRTCAudioMixingManager-startaudiomixing-filepath-config) 开始播放音频文件之前调用。

<span id="ByteRTCVideo-enableplaybackducking"></span>
### enablePlaybackDucking:
```objectivec

- (void)enablePlaybackDucking:(BOOL)enable;
```
打开/关闭音量闪避功能，适用于在 RTC 通话过程中会同时播放短视频或音乐的场景，如“一起看”、“在线 KTV”等。  <br>
开启该功能后，当检测到远端人声时，本地的媒体播放音量会自动减弱，从而保证远端人声的清晰可辨；当远端人声消失时，本地媒体音量会恢复到闪避前的音量水平。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| enable | **BOOL** | 是否开启音量闪避：  <br/>• True: 是  <br/>• False: 否 |


<span id="ByteRTCVideo-setlocalvideosink-withsink-withpixelformat"></span>
### setLocalVideoSink:withSink:withPixelFormat:
```objectivec

- (void)setLocalVideoSink:(ByteRTCStreamIndex)index withSink:(id<ByteRTCVideoSinkDelegate> _Nullable)videoSink withPixelFormat:(ByteRTCVideoSinkPixelFormat)requiredFormat;
```
将本地视频流与自定义渲染器绑定。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| index | **ByteRTCStreamIndex** | 视频流属性。采集的视频流/屏幕视频流，参看 [ByteRTCStreamIndex](iOS-keytype.md#bytertcstreamindex) |
| videoSink | **id<ByteRTCVideoSinkDelegate>** | 自定义视频渲染器，参看 [ByteRTCVideoSinkDelegate](iOS-keytype.md#bytertcvideosinkdelegate) |
| requiredFormat | **ByteRTCVideoSinkPixelFormat** | videoSink 适用的视频帧编码格式，参看 [ByteRTCVideoSinkPixelFormat](iOS-keytype.md#bytertcvideosinkpixelformat) |


**注意**

+ RTC SDK 默认使用 RTC SDK 自带的渲染器（内部渲染器）进行视频渲染。
+ 如果需要解除绑定，必须将 videoSink 设置为 null。退房时将清除绑定状态。
+ 一般在收到 [rtcEngine:onFirstLocalVideoFrameCaptured:withFrameInfo:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onfirstlocalvideoframecaptured-withframeinfo) 回调通知完成本地视频首帧采集后，调用此方法为视频流绑定自定义渲染器；然后加入房间。


<span id="ByteRTCVideo-setremotevideosink-withsink-withpixelformat"></span>
### setRemoteVideoSink:withSink:withPixelFormat:
```objectivec

- (void)setRemoteVideoSink:(ByteRTCRemoteStreamKey* _Nonnull)streamKey withSink:(id<ByteRTCVideoSinkDelegate> _Nullable)videoSink withPixelFormat:(ByteRTCVideoSinkPixelFormat)requiredFormat;
```
将远端视频流与自定义渲染器绑定。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamKey | **ByteRTCRemoteStreamKey*** | 远端流信息，用于指定需要渲染的视频流来源及属性，参看 [ByteRTCRemoteStreamKey](iOS-keytype.md#bytertcremotestreamkey) |
| videoSink | **id<ByteRTCVideoSinkDelegate>** | 自定义视频渲染器，参看 [ByteRTCVideoSinkDelegate](iOS-keytype.md#bytertcvideosinkdelegate) |
| requiredFormat | **ByteRTCVideoSinkPixelFormat** | videoSink 适用的视频帧编码格式，参看 [ByteRTCVideoSinkPixelFormat](iOS-keytype.md#bytertcvideosinkpixelformat) |


**注意**

+ RTC SDK 默认使用 RTC SDK 自带的渲染器（内部渲染器）进行视频渲染。
+ 该方法进房前后均可以调用。若想在进房前调用，你需要在加入房间前获取远端流信息；若无法预先获取远端流信息，你可以在加入房间并通过 [rtcRoom:onUserPublishStream:type:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onuserpublishstream-type) 回调获取到远端流信息之后，再调用该方法。
+ 如果需要解除绑定，必须将 videoSink 设置为 null。退房时将清除绑定状态。


<span id="ByteRTCVideo-enablesimulcastmode"></span>
### enableSimulcastMode:
```objectivec

- (int) enableSimulcastMode:(BOOL) enabled;
```
该方法设置视频流发布端是否开启发布多路编码参数不同的视频流的模式。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| enabled | **BOOL** | 是否开启推送多路视频流模式： <br/>• True：开启 <br/>• False：关闭（默认） |

**返回值**
方法调用结果： 

+ 0: 成功 
+ <0: 失败


**注意**

+ 你应在进房前或进房后但未发布流时，调用此方法。  
+ 开启推送多路流后，不能动态关闭，也不能更新多路流的路数和编码参数。
+ 开启推送多路视频流模式后，你可以调用 [SetVideoEncoderConfig:](#ByteRTCVideo-setvideoencoderconfig) 为多路视频流分别设置编码参数。  
+ 该功能关闭时，或该功能开启但未设置多路流参数时，默认只发一路视频流，该流的编码参数为：分辨率 640px × 360px，帧率 15fps。


<span id="ByteRTCVideo-setmaxvideoencoderconfig"></span>
### SetMaxVideoEncoderConfig:
```objectivec

- (int)SetMaxVideoEncoderConfig:(ByteRTCVideoEncoderConfig * _Nullable) max_solution;
```
视频发布端设置期望发布的最大分辨率视频流参数，包括分辨率、帧率、码率、网络不佳时的回退策略等。  <br>
该接口支持设置一路视频流参数，设置多路参数请使用 [SetVideoEncoderConfig:](#ByteRTCVideo-setvideoencoderconfig)。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| max_solution | **ByteRTCVideoEncoderConfig*** | 期望发布的最大分辨率视频流参数。参看 [ByteRTCVideoEncoderConfig](iOS-keytype.md#bytertcvideoencoderconfig)。 |

**返回值**
方法调用结果： 

+ 0：成功  
+ !0：失败  


**注意**

+ 若调用该方法设置了期望发布的最大分辨率的流参数之前，已调用 [enableSimulcastMode:](#ByteRTCVideo-enablesimulcastmode) 开启发布多路视频流的模式，SDK 会根据订阅端的设置自动调整发布的流数以及各路流的参数，其中最大分辨率为设置的分辨率，流数最多 4 条，具体参看[推送多路流](https://www.volcengine.com/docs/6348/70139)文档；否则仅发布该条最大分辨率的视频流。 
+ 调用该方法设置多路视频流参数前，SDK 默认仅发布一条分辨率为 640px × 360px，帧率为 15fps 的视频流。  
+ 自定义采集的场景下，务必调用该接口设置分辨率，以保证远端收到画面的完整性。
+ 该方法适用于摄像头采集的视频流，设置屏幕共享视频流参数参看 [SetScreenVideoEncoderConfig:](#ByteRTCVideo-setscreenvideoencoderconfig)。


<span id="ByteRTCVideo-setvideoencoderconfig"></span>
### SetVideoEncoderConfig:
```objectivec
-(int)SetVideoEncoderConfig:(NSArray <ByteRTCVideoEncoderConfig *> * _Nullable) channel_solutions;
```
视频发布端设置推送多路流时各路流的参数，包括分辨率、帧率、码率、网络不佳时的回退策略等。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| channel_solutions | **NSArray <ByteRTCVideoEncoderConfig*>*** | 要推送的多路视频流的参数，最多支持设置 3 路参数，超过 3 路时默认取前 3 路的值。  <br/>当设置了多路参数时，分辨率和帧率必须是从大到小排列。需注意，所设置的分辨率是各路流的最大分辨率。参看 [ByteRTCVideoEncoderConfig](iOS-keytype.md#bytertcvideoencoderconfig)。 |

**返回值**
方法调用结果： 

+ 0：成功  
+ !0：失败  


**注意**

+ 该方法是否生效取决于是否同时调用了 [enableSimulcastMode:](#ByteRTCVideo-enablesimulcastmode) 开启发布多路参数不同的视频流模式。若未开启推送多路流模式，但调用本方法设置了多个分辨率，SDK 默认发布分辨率最大的一条流，多个分辨率的设置会在开启推送多路流模式之后生效。  
+ 开启推送多路流后，不能动态关闭，也不能更新多路流的路数和编码参数。
+ 调用该方法设置多路视频流参数前，SDK 默认仅发布一条分辨率为 640px × 360px，帧率为 15fps 的视频流。  
+ 调用该方法设置分辨率不同的多条流后，SDK 会根据订阅端设置的期望订阅参数自动匹配发送的流，具体规则参看[推送多路流](https://www.volcengine.com/docs/6348/70139)文档。  
+ 该方法适用于摄像头采集的视频流，设置屏幕共享视频流参数参看 [SetScreenVideoEncoderConfig:](#ByteRTCVideo-setscreenvideoencoderconfig)。


<span id="ByteRTCVideo-setscreenvideoencoderconfig"></span>
### SetScreenVideoEncoderConfig:
```objectivec
-(int)SetScreenVideoEncoderConfig:(ByteRTCVideoEncoderConfig * _Nullable) screen_solution;
```
为发布的屏幕共享视频流设置期望的编码参数，包括分辨率、帧率、码率、网络不佳时的回退策略等。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| screen_solution | **ByteRTCVideoEncoderConfig*** | 屏幕共享视频流参数。参看 [ByteRTCVideoEncoderConfig](iOS-keytype.md#bytertcvideoencoderconfig)。 |

**返回值**
方法调用结果： 
0：成功  
!0：失败  


**注意**

+ 调用该方法之前，屏幕共享视频流默认的编码参数为：分辨率 1920px × 1080px，帧率 15fps。
+ 该方法需在 [publishScreen:](#ByteRTCRoom-publishscreen) 发布屏幕共享流之前调用，之后调用不生效。


<span id="ByteRTCVideo-setvideocaptureconfig"></span>
### setVideoCaptureConfig:
```objectivec

- (int)setVideoCaptureConfig:(ByteRTCVideoCaptureConfig * _Nullable)captureConfig;
```
设置 RTC SDK 内部采集时的视频采集参数。<br>
如果你的项目使用了 SDK 内部采集模块，可以通过本接口指定视频采集参数包括模式、分辨率、帧率。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| captureConfig | **ByteRTCVideoCaptureConfig*** | 视频采集参数。参看: [ByteRTCVideoCaptureConfig](iOS-keytype.md#bytertcvideocaptureconfig)。 |

**返回值**

+ 0: 成功；  
+ < 0: 失败；  


**注意**

+ 本接口在引擎创建后可调用，调用后立即生效。建议在调用 [startVideoCapture](#ByteRTCVideo-startvideocapture) 前调用本接口。
+ 建议同一设备上的不同引擎使用相同的视频采集参数。
+ 如果调用本接口前使用内部模块开始视频采集，采集参数默认为 Auto 模式。


<span id="ByteRTCVideo-setlocalvideocanvas-withcanvas"></span>
### setLocalVideoCanvas:withCanvas:
```objectivec

- (int)setLocalVideoCanvas:(ByteRTCStreamIndex)streamIndex withCanvas:(ByteRTCVideoCanvas * _Nullable)canvas;
```
设置本地视频渲染时，使用的视图，并设置渲染模式。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamIndex | **ByteRTCStreamIndex** | 流属性，参看 [ByteRTCStreamIndex](iOS-keytype.md#bytertcstreamindex) |
| canvas | **ByteRTCVideoCanvas*** | 视图信息和渲染模式，参看 [ByteRTCVideoCanvas](iOS-keytype.md#bytertcvideocanvas) |

**返回值**

+ 0：方法调用成功  
+ < 0：方法调用失败  


**注意**

+ 你应在加入房间前，绑定本地视图。退出房间后，此设置仍然有效。 
+ 如果需要解除绑定，你可以调用本方法传入空视图。


<span id="ByteRTCVideo-updatelocalvideocanvas-withrendermode-withbackgroundcolor"></span>
### updateLocalVideoCanvas:withRenderMode:withBackgroundColor:
```objectivec

- (int)updateLocalVideoCanvas:(ByteRTCStreamIndex)streamIndex withRenderMode:(ByteRTCRenderMode)renderMode withBackgroundColor:(NSUInteger)backgroundColor;
```
修改本地视频渲染模式和背景色。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamIndex | **ByteRTCStreamIndex** | 视频流属性。参看 [ByteRTCStreamIndex](iOS-keytype.md#bytertcstreamindex) |
| renderMode | **ByteRTCRenderMode** | 渲染模式。参看 [ByteRTCRenderMode](iOS-keytype.md#bytertcrendermode) |
| backgroundColor | **NSUInteger** | 背景颜色。参看 [ByteRTCVideoCanvas](iOS-keytype.md#bytertcvideocanvas).backgroundColor |

**返回值**

+ 0: 成功  
+ -1: 失败。VideoCanvas 为空  


**注意**
你可以在本地视频渲染过程中，调用此接口。调用结果会实时生效。

<span id="ByteRTCVideo-setremotevideocanvas-withindex-withcanvas"></span>
### setRemoteVideoCanvas:withIndex:withCanvas:
```objectivec

- (int)setRemoteVideoCanvas:(NSString * _Nonnull)uid withIndex:(ByteRTCStreamIndex)streamIndex withCanvas:(ByteRTCVideoCanvas * _Nullable)canvas;
```
渲染来自指定远端用户 uid 的视频流时，设置使用的视图和渲染模式。  <br>
如果需要解除视频的绑定视图，把 `canvas.view` 设置为空。(`canvas` 中其他参数不能为空。)

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | **NSString*** | 视频来源的远端用户 ID |
| streamIndex | **ByteRTCStreamIndex** | 视频流属性，参看 [ByteRTCStreamIndex](iOS-keytype.md#bytertcstreamindex) |
| canvas | **ByteRTCVideoCanvas*** | 视图信息和渲染模式，参看 [ByteRTCVideoCanvas](iOS-keytype.md#bytertcvideocanvas) |

**返回值**

+ 0：方法调用成功  
+ < 0：方法调用失败  


**注意**

+ 你应在收到回调 [rtcRoom:onUserJoined:elapsed:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onuserjoined-elapsed) 或 [rtcEngine:onFirstRemoteVideoFrameDecoded:withFrameInfo:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onfirstremotevideoframedecoded-withframeinfo) 后，为此远端视频流绑定视图。
这两个回调的差别是：如果启用了视频录制功能，视频录制服务会作为一个哑客户端加入房间，因此其他客户端会收到对应的 [rtcRoom:onUserJoined:elapsed:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onuserjoined-elapsed) 回调；
而不会收到 [rtcEngine:onFirstRemoteVideoFrameDecoded:withFrameInfo:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onfirstremotevideoframedecoded-withframeinfo) 回调。你不应给录制的哑客户端绑定视图（因为它不会发送视频流）。

+ 本地用户离开房间时，会解除调用此 API 建立的绑定关系；远端用户离开房间则不会影响。


<span id="ByteRTCVideo-updateremotestreamvideocanvas-withuserid-withindex-withrendermode-withbackgroundcolor"></span>
### updateRemoteStreamVideoCanvas:withUserId:withIndex:withRenderMode:withBackgroundColor:
```objectivec

- (int)updateRemoteStreamVideoCanvas:(NSString * _Nonnull)roomid withUserId:(NSString * _Nonnull)uid withIndex:(ByteRTCStreamIndex)streamIndex withRenderMode:(ByteRTCRenderMode)renderMode withBackgroundColor:(NSUInteger)backgroundColor;
```
修改远端视频渲染模式和背景色。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| roomid | **NSString*** | 房间 ID |
| uid | **NSString*** | 用户 ID |
| streamIndex | **ByteRTCStreamIndex** | 远端流信息。参看 [ByteRTCStreamIndex](iOS-keytype.md#bytertcstreamindex)。 |
| renderMode | **ByteRTCRenderMode** | 渲染模式，参看 [ByteRTCRenderMode](iOS-keytype.md#bytertcrendermode) |
| backgroundColor | **NSUInteger** | 背景颜色，参看 [ByteRTCVideoCanvas](iOS-keytype.md#bytertcvideocanvas).backgroundColor |


**注意**
你可以在远端视频渲染过程中，调用此接口。调用结果会实时生效。

<span id="ByteRTCVideo-startvideocapture"></span>
### startVideoCapture
```objectivec

- (void)startVideoCapture;
```
立即开启内部视频采集。默认为关闭状态。  <br>
内部视频采集指：使用 RTC SDK 内置视频采集模块，进行采集。<br>
调用该方法后，本地用户会收到 [rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onvideodevicestatechanged-device_type-device_state-device_error) 的回调。  <br>
非隐身用户进房后调用该方法，房间中的其他用户会收到 [rtcEngine:onUserStartVideoCapture:uid:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onuserstartvideocapture-uid) 的回调。


**注意**

+ 调用 [stopVideoCapture](#ByteRTCVideo-stopvideocapture) 可以停止内部视频采集。否则，只有当销毁引擎实例时，内部视频采集才会停止。  
+ 创建引擎后，无论是否发布视频数据，你都可以调用该方法开启内部视频采集。只有当（内部或外部）视频采集开始以后视频流才会发布。  
+ 如果需要从自定义视频采集切换为内部视频采集，你必须先停止发布流，关闭自定义采集，再调用此方法手动开启内部采集。
+ 内部视频采集使用的摄像头由 [switchCamera:](#ByteRTCVideo-switchcamera) 接口指定。（macOS 不支持）
+ 自 v3.37.0 升级版本，你需要在应用中向用户申请摄像头权限后才能开始采集。


<span id="ByteRTCVideo-stopvideocapture"></span>
### stopVideoCapture
```objectivec

- (void)stopVideoCapture;
```
立即关闭内部视频采集。默认为关闭状态。  <br>
内部视频采集指：使用 RTC SDK 内置视频采集模块，进行采集。<br>
调用该方法后，本地用户会收到 [rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onvideodevicestatechanged-device_type-device_state-device_error) 的回调。  <br>
非隐身用户进房后调用该方法，房间中的其他用户会收到 [rtcEngine:onUserStopVideoCapture:uid:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onuserstopvideocapture-uid) 的回调。


**注意**

+ 调用 [startVideoCapture](#ByteRTCVideo-startvideocapture) 可以开启内部视频采集。  
+ 如果不调用本方法停止内部视频采集，则只有当销毁引擎实例时，内部视频采集才会停止。 


<span id="ByteRTCVideo-setlocalvideomirrortype"></span>
### setLocalVideoMirrorType:
```objectivec

- (int)setLocalVideoMirrorType:(ByteRTCMirrorType) mirrorType;
```
为采集到的视频流开启镜像

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mirrorType | **ByteRTCMirrorType** | 镜像类型，参看 [ByteRTCMirrorType](iOS-keytype.md#bytertcmirrortype) |


**注意**

+ 切换视频源不影响镜像设置。
+ 屏幕视频流始终不受镜像设置影响。
+ 使用外部渲染器时，`mirrorType` 支持设置为 `0`（无镜像）和 `3`（本地预览和编码传输镜像），不支持设置为 `1`（编码传输镜像）。
+ 该接口调用前，各视频源的初始状态如下：
<table>
<tr><th></th><th>前置摄像头</th><th>后置摄像头</th><th>自定义采集视频源</th> <th>桌面端摄像头</th> </tr>
<tr><td>移动端</td><td>本地预览镜像，编码传输不镜像</td><td> 本地预览不镜像，编码传输不镜像 </td><td> 本地预览不镜像，编码传输不镜像 </td><td>/</td></tr>
<tr><td>桌面端</td><td>/</td><td>/</td><td> 本地预览不镜像，编码传输不镜像 </td><td> 本地预览镜像，编码传输不镜像 </td></tr> 
</table>


<span id="ByteRTCVideo-setvideorotationmode"></span>
### setVideoRotationMode:
```objectivec

- (int)setVideoRotationMode:(ByteRTCVideoRotationMode) rotationMode;
```
设置采集视频的旋转模式。默认以 App 方向为旋转参考系。<br>
接收端渲染视频时，将按照和发送端相同的方式进行旋转。<br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rotationMode | **ByteRTCVideoRotationMode** | 视频旋转参考系为 App 方向或重力方向，参看 [ByteRTCVideoRotationMode](iOS-keytype.md#bytertcvideorotationmode)。 |

**返回值**
0:设置成功
<0:设置失败


**注意**

+ 旋转仅对内部视频采集生效，不适用于外部视频源和屏幕源。
+ 调用该接口时已开启视频采集，将立即生效；调用该接口时未开启视频采集，则将在采集开启后生效。
+ 更多信息请参考[视频采集方向](https://www.volcengine.com/docs/6348/106458)。


<span id="ByteRTCVideo-setvideoorientation"></span>
### setVideoOrientation:
```objectivec

- (void)setVideoOrientation:(ByteRTCVideoOrientation) orientation;
```
在自定义视频前处理及编码前，设置 RTC 链路中的视频帧朝向，默认为 Adaptive 模式。
移动端开启视频特效贴纸，或使用自定义视频前处理时，建议固定视频帧朝向为 Portrait 模式。单流转推场景下，建议根据业务需要固定视频帧朝向为 Portrait 或 Landscape 模式。不同模式的具体显示效果参看[视频帧朝向](https://www.volcengine.com/docs/6348/128787)。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| orientation | **ByteRTCVideoOrientation** | 视频帧朝向，参看 [ByteRTCVideoOrientation](iOS-keytype.md#bytertcvideoorientation)。 |


**注意**

+ 设置视频帧朝向仅对内部视频采集生效，不适用于外部视频源和屏幕源。
+ 编码分辨率的更新与视频帧处理是异步操作，进房后切换视频帧朝向可能导致画面出现短暂的裁切异常，因此建议在进房前设置视频帧朝向，且不在进房后进行切换。


<span id="ByteRTCVideo-switchcamera"></span>
### switchCamera:
```objectivec

- (int)switchCamera:(ByteRTCCameraID) cameraId;
```
切换视频内部采集时使用的前置/后置摄像头 <br>
调用此接口后，在本地会触发 [rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onvideodevicestatechanged-device_type-device_state-device_error) 回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| cameraId | **ByteRTCCameraID** | 摄像头类型，参看 [ByteRTCCameraID](iOS-keytype.md#bytertccameraid)。 |

**返回值**

+ 0：方法调用成功  
+ < 0：方法调用失败  


**注意**

+ 默认使用前置摄像头。
+ 如果你正在使用相机进行视频采集，切换操作当即生效；如果相机未启动，后续开启内部采集时，会打开设定的摄像头。


<span id="ByteRTCVideo-checkvideoeffectlicense"></span>
### checkVideoEffectLicense:
```objectivec

- (int)checkVideoEffectLicense:(NSString * _Nonnull)licenseFile;
```
视频特效许可证检查

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| licenseFile | **NSString*** | 许可证文件绝对路径 |

**返回值**

+ 0: 调用成功。  
+ 1000: 未集成特效 SDK。  
+ 1001: 特效 SDK 不支持该功能。  
+ < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。  


**注意**
[enableVideoEffect:](#ByteRTCVideo-enablevideoeffect) 开始使用视频特效前，需要先调用这个方法进行许可证验证

<span id="ByteRTCVideo-enablevideoeffect"></span>
### enableVideoEffect:
```objectivec

- (int)enableVideoEffect:(BOOL)enabled;
```
创建/销毁视频特效引擎

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| enabled | **BOOL** | 是否创建视频特效引擎  <br/>• true: 创建  <br/>• false: 销毁 |

**返回值**

+ 0: 调用成功。  
+ 1000: 未集成特效 SDK。  
+ 1001: 特效 SDK 不支持该功能。  
+ < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。  


**注意**

+ 该方法须在调用 [checkVideoEffectLicense:](#ByteRTCVideo-checkvideoeffectlicense) 和 [setVideoEffectAlgoModelPath:](#ByteRTCVideo-setvideoeffectalgomodelpath) 后调用。  
+ 该方法不直接开启/关闭视频特效，你须在调用该方法后，调用 [setVideoEffectNodes:](#ByteRTCVideo-setvideoeffectnodes) 开启视频特效。  
+ 通用场景下，特效引擎会随 RTC 引擎销毁而销毁。当你对性能有较高要求时，可在不使用特效相关功能时调用该方法中 false 单独销毁特效引擎。


<span id="ByteRTCVideo-setvideoeffectalgomodelpath"></span>
### setVideoEffectAlgoModelPath:
```objectivec

- (void)setVideoEffectAlgoModelPath:(NSString * _Nonnull)modelPath;
```
设置视频特效算法模型路径

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| modelPath | **NSString*** | 模型路径 |


<span id="ByteRTCVideo-setvideoeffectnodes"></span>
### setVideoEffectNodes:
```objectivec

- (int) setVideoEffectNodes:(NSArray <NSString *> *_Nonnull)effectNodePaths;
```
设置视频特效素材包

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| effectNodePaths | **NSArray <NSString*>*** | 特效素材包路径数组 <br/>要取消当前视频特效，将此参数设置为 null。 |

**返回值**

+ 0: 调用成功。  
+ 1000: 未集成特效 SDK。  
+ 1001: 特效 SDK 不支持该功能。  
+ < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。  


**注意**
在调用这个方法之前，你须先调用 [enableVideoEffect:](#ByteRTCVideo-enablevideoeffect) 。

<span id="ByteRTCVideo-updatevideoeffectnode-nodekey-nodevalue"></span>
### updateVideoEffectNode:nodeKey:nodeValue:
```objectivec

- (int) updateVideoEffectNode:(NSString * _Nonnull)nodePath nodeKey:(NSString * _Nonnull)nodeKey nodeValue:(float) nodeValue;
```
设置特效强度

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| nodePath | **NSString*** | 特效素材包路径。 |
| nodeKey | **NSString*** | 需要设置的素材 key 名称。参看 [素材key对应说明](https://www.volcengine.com/docs/6705/102041)。 |
| nodeValue | **float** | 需要设置的强度值。取值范围为 [0,1]，超出该范围设置无效。 |

**返回值**

+ 0: 调用成功。  
+ 1000: 未集成特效 SDK。  
+ 1001: 特效 SDK 不支持该功能。  
+ < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。  


**注意**
该接口仅适用于同时含有上述三个参数的特效资源，对于如大部分贴纸类等没有强度参数的特效，该接口调用无效。

<span id="ByteRTCVideo-setvideoeffectcolorfilter"></span>
### setVideoEffectColorFilter:
```objectivec

- (int) setVideoEffectColorFilter:(NSString * _Nonnull)resPath;
```
设置颜色滤镜

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| resPath | **NSString*** | 滤镜资源包绝对路径 |

**返回值**

+ 0: 调用成功。  
+ 1000: 未集成特效 SDK。  
+ 1001: 特效 SDK 不支持该功能。  
+ < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。  


<span id="ByteRTCVideo-setvideoeffectcolorfilterintensity"></span>
### setVideoEffectColorFilterIntensity:
```objectivec

- (int) setVideoEffectColorFilterIntensity:(float) intensity;
```
设置已启用的颜色滤镜强度

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| intensity | **float** | 滤镜强度。取值范围 [0,1]，超出范围时设置无效 |

**返回值**

+ 0: 调用成功。  
+ 1000: 未集成特效 SDK。  
+ 1001: 特效 SDK 不支持该功能。  
+ < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。  


<span id="ByteRTCVideo-setbackgroundsticker-source"></span>
### setBackgroundSticker:source:
```objectivec

- (int) setBackgroundSticker:(NSString* _Nullable)modelPath source:(ByteRTCVirtualBackgroundSource* _Nonnull)source;
```
将摄像头采集画面中的人像背景替换为指定图片或纯色背景。
若要取消背景特效，将背景贴纸特效素材路径设置为null。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| modelPath | **NSString*** | 传入背景贴纸特效素材路径。 |
| source | **ByteRTCVirtualBackgroundSource*** | 设置背景特效图片的本地路径。参看 [ByteRTCVirtualBackgroundSource](iOS-keytype.md#bytertcvirtualbackgroundsource)。 |

**返回值**

+ 0：调用成功。  
+ 1000：未集成特效 SDK。  
+ 1001：特效 SDK 不支持该功能。  
+ < 0：调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。


**注意**
调用此接口前需依次调用以下接口：1、检查视频特效许可证 [checkVideoEffectLicense:](#ByteRTCVideo-checkvideoeffectlicense)；2、设置视频特效算法模型路径 [setVideoEffectAlgoModelPath:](#ByteRTCVideo-setvideoeffectalgomodelpath)；3、开启视频特效 [enableVideoEffect:](#ByteRTCVideo-enablevideoeffect)。


<span id="ByteRTCVideo-enableeffectbeauty"></span>
### enableEffectBeauty:
```objectivec

- (int) enableEffectBeauty:(BOOL)enable;
```
开启/关闭基础美颜

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| enable | **BOOL** | 基础美颜开关 <br/>• true: 开启基础美颜 <br/>• false: 关闭基础美颜（默认） |

**返回值**

+ 0: 开启/关闭成功。 
+ 1000: 未集成特效 SDK。 
+ 1001: RTC SDK 版本不支持此功能。 
+ 1002: 特效 SDK 当前版本不支持此功能，建议使用特效 SDK V4.3.1 版本。 
+ 1003: 联系技术支持人员。 
+ 1004: 正在下载相关资源，下载完成后生效。 
+ <0: 调用失败，特效 SDK 内部错误，具体错误码请参考[错误码表](https://www.volcengine.com/docs/6705/102042)。  


**注意**

+ 本方法不能与高级视频特效接口共用。如已购买高级视频特效，建议调用 [enableVideoEffect:](#ByteRTCVideo-enablevideoeffect) 使用高级特效、贴纸功能等。 
+ 使用此功能需要集成特效 SDK，建议使用特效 SDK V4.3.1+ 版本。 
+ 调用 [setBeautyIntensity:withIntensity:](#ByteRTCVideo-setbeautyintensity-withintensity) 设置基础美颜强度。若在调用本方法前没有设置美颜强度，则初始美白、磨皮、锐化强度均为 0.5。 
+ 本方法仅适用于视频源，不适用于屏幕源。 


<span id="ByteRTCVideo-setbeautyintensity-withintensity"></span>
### setBeautyIntensity:withIntensity:
```objectivec

- (int) setBeautyIntensity:(ByteRTCEffectBeautyMode) beautyMode withIntensity:(float)intensity;
```
调整基础美颜强度

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| beautyMode | **ByteRTCEffectBeautyMode** | 基础美颜模式，参看 [ByteRTCEffectBeautyMode](iOS-keytype.md#bytertceffectbeautymode)。 |
| intensity | **float** | 美颜强度，取值范围为 [0,1]。强度为 0 表示关闭，默认强度为 0.5。 |

**返回值**

+ 0: 开启成功。 
+ 1000: 未集成特效 SDK。 
+ 1001: RTC SDK 版本不支持此功能。 
+ <0: 调用失败，特效 SDK 内部错误，具体错误码请参考[错误码表](https://www.volcengine.com/docs/6705/102042)。  


**注意**

+ 若在调用 [enableVideoEffect:](#ByteRTCVideo-enablevideoeffect) 前设置美颜强度，则对应美颜功能的强度初始值会根据设置更新。 
+ 销毁引擎后，美颜功能强度恢复默认值。 


<span id="ByteRTCVideo-setcamerazoomratio"></span>
### setCameraZoomRatio:
```objectivec

- (int) setCameraZoomRatio: (float) zoom_val;
```
设置当前使用的摄像头（前置/后置）的变焦倍数

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| zoom_val | **float** | 变焦倍数。取值范围是 [1, <最大变焦倍数>]。<br/>最大变焦倍数可以通过调用 [getCameraZoomMaxRatio](#ByteRTCVideo-getcamerazoommaxratio) 获取。 |

**返回值**

+ 0： 成功。 
+ < 0： 失败。


**注意**

+ 必须已调用 [startVideoCapture](#ByteRTCVideo-startvideocapture) 使用 SDK 内部采集模块进行视频采集时，才能设置摄像头变焦倍数。
+ 设置结果在调用 [stopVideoCapture](#ByteRTCVideo-stopvideocapture) 关闭内部采集后失效。


<span id="ByteRTCVideo-getcamerazoommaxratio"></span>
### getCameraZoomMaxRatio
```objectivec

- (float) getCameraZoomMaxRatio;
```
获取当前使用的摄像头（前置/后置）的最大变焦倍数

**返回值**
最大变焦倍数


**注意**
必须已调用 [startVideoCapture](#ByteRTCVideo-startvideocapture) 使用 SDK 内部采集模块进行视频采集时，才能检测摄像头最大变焦倍数。

<span id="ByteRTCVideo-iscamerazoomsupported"></span>
### isCameraZoomSupported
```objectivec

- (bool) isCameraZoomSupported;
```
检测当前使用的摄像头（前置/后置），是否支持变焦（数码/光学变焦）。

**返回值**

+ true: 支持 
+ false: 不支持


**注意**
必须已调用 [startVideoCapture](#ByteRTCVideo-startvideocapture) 使用 SDK 内部采集模块进行视频采集时，才能检测摄像头变焦能力。

<span id="ByteRTCVideo-iscameratorchsupported"></span>
### isCameraTorchSupported
```objectivec

- (bool) isCameraTorchSupported;
```
检测当前使用的摄像头（前置/后置），是否支持闪光灯。

**返回值**

+ true: 支持 
+ false: 不支持


**注意**
必须已调用 [startVideoCapture](#ByteRTCVideo-startvideocapture) 使用 SDK 内部采集模块进行视频采集时，才能检测闪光能力。

<span id="ByteRTCVideo-setcameratorch"></span>
### setCameraTorch:
```objectivec

- (int) setCameraTorch: (ByteRTCTorchState)torch_state;
```
打开/关闭当前使用的摄像头（前置/后置）的闪光灯

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| torch_state | **ByteRTCTorchState** | 打开/关闭。参看 [ByteRTCTorchState](iOS-keytype.md#bytertctorchstate)。 |

**返回值**

+ 0： 成功。
+ < 0： 失败。


**注意**

+ 必须已调用 [startVideoCapture](#ByteRTCVideo-startvideocapture) 使用 SDK 内部采集模块进行视频采集时，才能设置闪光灯。
+ 设置结果在调用 [stopVideoCapture](#ByteRTCVideo-stopvideocapture) 关闭内部采集后失效。


<span id="ByteRTCVideo-iscamerafocuspositionsupported"></span>
### isCameraFocusPositionSupported
```objectivec

- (bool)isCameraFocusPositionSupported;
```
检查当前使用的摄像头是否支持手动对焦。

**返回值**

+ true: 支持。 
+ false: 不支持。


**注意**
必须已调用 [startVideoCapture](#ByteRTCVideo-startvideocapture) 使用 SDK 内部采集模块进行视频采集，才能检查摄像头是否支持手动对焦。

<span id="ByteRTCVideo-setcamerafocusposition"></span>
### setCameraFocusPosition:
```objectivec

- (int)setCameraFocusPosition:(CGPoint)position;
```
设置当前使用的摄像头的对焦点。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| position | **CGPoint** | 对焦点坐标。以本地预览画布的左上为坐标原点，`position`的`x`字段为对焦点水平方向归一化坐标，`y`字段为对焦点垂直方向归一化坐标，取值范围为 [0, 1]。 |

**返回值**

+ 0: 成功。 
+ < 0: 失败。


**注意**

+ 必须已调用 [startVideoCapture](#ByteRTCVideo-startvideocapture) 使用 SDK 内部采集模块进行视频采集，并且使用 SDK 内部渲染时，才能设置对焦点。  
+ 对焦点设置为画布中央（即`x`和`y`均取 0.5）时，恢复系统默认值。  
+ 调用 [stopVideoCapture](#ByteRTCVideo-stopvideocapture) 关闭内部采集后，设置的对焦点失效。


<span id="ByteRTCVideo-iscameraexposurepositionsupported"></span>
### isCameraExposurePositionSupported
```objectivec

- (bool)isCameraExposurePositionSupported;
```
检查当前使用的摄像头是否支持手动设置曝光点。

**返回值**

+ true: 支持。 
+ false: 不支持。


**注意**
必须已调用 [startVideoCapture](#ByteRTCVideo-startvideocapture) 使用 SDK 内部采集模块进行视频采集时，才能检查曝光点设置能力。

<span id="ByteRTCVideo-setcameraexposureposition"></span>
### setCameraExposurePosition:
```objectivec

- (int)setCameraExposurePosition:(CGPoint)position;
```
设置当前使用的摄像头的曝光点。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| position | **CGPoint** | 曝光点坐标。以本地预览画布的左上为坐标原点，`position`的`x`字段为曝光点水平方向归一化坐标，`y`字段为曝光点垂直方向归一化坐标，取值范围为 [0, 1]。 |

**返回值**

+ 0: 成功。 
+ < 0: 失败。


**注意**

+ 必须已调用 [startVideoCapture](#ByteRTCVideo-startvideocapture) 使用 SDK 内部采集模块进行视频采集，并且使用 SDK 内部渲染时，才能设置曝光点。  
+ 曝光点设置为画布中央（即`x`和`y`均取 0.5）时，恢复系统默认值。  
+ 调用 [stopVideoCapture](#ByteRTCVideo-stopvideocapture) 关闭内部采集后，设置的曝光点失效。


<span id="ByteRTCVideo-setcameraexposurecompensation"></span>
### setCameraExposureCompensation:
```objectivec

- (int)setCameraExposureCompensation:(float)val;
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

+ 必须已调用 [startVideoCapture](#ByteRTCVideo-startvideocapture) 使用 SDK 内部采集模块进行视频采集时，才能设置曝光补偿。  
+ 调用 [stopVideoCapture](#ByteRTCVideo-stopvideocapture) 关闭内部采集后，设置的曝光补偿失效。


<span id="ByteRTCVideo-registerfacedetectionobserver-withinterval"></span>
### registerFaceDetectionObserver:withInterval:
```objectivec

- (int) registerFaceDetectionObserver:(_Nullable id<ByteRTCFaceDetectionObserver>)faceDetectionObserver withInterval:(NSInteger)interval;
```
注册人脸检测结果回调观察者 <br>
注册此观察者后，你会周期性收到 [onFaceDetectionResult:](iOS-callback.md#ByteRTCFaceDetectionObserver-onfacedetectionresult) 回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| faceDetectionObserver | **id<ByteRTCFaceDetectionObserver>** | 人脸检测结果回调观察者，参看 [ByteRTCFaceDetectionObserver](iOS-callback.md#bytertcfacedetectionobserver)。 |
| interval | **NSInteger** | 时间间隔，必须大于 0。单位：ms。实际收到回调的时间间隔大于 `interval`，小于 `interval + 视频采集帧间隔`。 |

**返回值**

+ 0：方法调用成功  
+ < 0：方法调用失败  


<span id="ByteRTCVideo-sendseimessage-andmessage-andrepeatcount"></span>
### sendSEIMessage:andMessage:andRepeatCount:
```objectivec

- (int)sendSEIMessage:(ByteRTCStreamIndex)streamIndex andMessage:(NSData* _Nonnull)message andRepeatCount:(int)repeatCount;
```
通过视频帧发送 SEI 数据。  <br>
在视频通话场景下，SEI 数据会随视频帧发送；在语音通话场景下，SDK 会自动生成一路 16px × 16px 的黑帧视频流用来发送 SEI 数据。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamIndex | **ByteRTCStreamIndex** | 指定携带 SEI 数据的媒体流类型，参看 [ByteRTCStreamIndex](iOS-keytype.md#bytertcstreamindex)。  <br/>语音通话场景下，该值需设为 `ByteRTCStreamIndexMain`，否则 SEI 数据会被丢弃从而无法送达远端。 |
| message | **NSData*** | SEI 消息。长度不超过 4KB。 |
| repeatCount | **int** | 消息发送重复次数。取值范围是 [0, max{29, %{视频帧率}-1}]。推荐范围 [2,4]。<br/>调用此接口后，SEI 数据会添加到从当前视频帧开始的连续 `repeatCount` 个视频帧中。 |

**返回值**

+ \>=0: 将被添加到视频帧中的 SEI 的数量  
+ <0: 发送失败


**注意**

+ 每秒发送的 SEI 消息数量建议不超过当前的视频帧率。在语音通话场景下，黑帧帧率为 15 fps。
+ 语音通话场景中，仅支持在内部采集模式下调用该接口发送 SEI 数据。
+ 视频帧仅携带前后 2s 内收到的 SEI 数据；语音通话场景下，若调用此接口后 1min 内未有 SEI 数据发送，则 SDK 会自动取消发布视频黑帧。  
+ 消息发送成功后，远端会收到 [rtcEngine:onSEIMessageReceived:andMessage:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onseimessagereceived-andmessage) 回调。
+ 视频通话场景中，使用自定义采集并通过 pushExternalVideoFrame 推送至 SDK 的视频帧，若本身未携带 SEI 数据，也可通过本接口发送 SEI 数据。 
+ 语音通话切换至视频通话时，会停止 SEI 数据发送，你需再次调用该接口方可恢复发送。


<span id="ByteRTCVideo-registerlocalvideoprocessor-withconfig"></span>
### registerLocalVideoProcessor:withConfig:
```objectivec

- (int)registerLocalVideoProcessor:(_Nullable id<ByteRTCVideoProcessorDelegate>) processor withConfig:(ByteRTCVideoPreprocessorConfig* _Nullable)config;
```
设置自定义视频前处理器。<br>
使用这个视频前处理器，你能够调用 [processVideoFrame:](iOS-callback.md#ByteRTCVideoProcessorDelegate-processvideoframe) 对 RTC SDK 采集得到的视频帧进行前处理，并将处理后的视频帧用于 RTC 音视频通信。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| processor | **id<ByteRTCVideoProcessorDelegate>** | 自定义视频处理器，详见 [ByteRTCVideoProcessorDelegate](iOS-callback#bytertcvideoprocessordelegate)。如果传入 null，则不对 RTC SDK 采集得到的视频帧进行前处理。<br/>SDK 只持有 processor 的弱引用，你应保证其生命周期。<br/>在设计 `processor` 时，应从 [ByteRTCVideoFrame](iOS-keytype.md#bytertcvideoframe) 的 `textureBuf` 字段获取视频帧数据；<br/>处理后返回的视频帧数据格式应为 [ByteRTCVideoPixelFormat](iOS-keytype.md#bytertcvideopixelformat) 中的 `ByteRTCVideoPixelFormatCVPixelBuffer`，且必须存放在返回帧数据的 `textureBuf` 字段中。 |
| config | **ByteRTCVideoPreprocessorConfig*** | 自定义视频前处理器适用的设置，详见 [ByteRTCVideoPreprocessorConfig](iOS-keytype.md#bytertcvideopreprocessorconfig)。<br/>当前，`config` 中的 `required_pixel_format` 仅支持：`ByteRTCVideoPixelFormatI420` 和 `ByteRTCVideoPixelFormatUnknown`：<br/>• 设置为 `UNKNOW` 时，RTC SDK 给出供 processor 处理的视频帧格式即采集的格式。<br/>• 设置为 `ByteRTCVideoPixelFormatI420` 时，RTC SDK 会将采集得到的视频转变为对应的格式，供前处理使用。<br/>• 设置为其他值时，此方法调用失败。 |

**返回值**

+ 0：方法调用成功 
+ !0：方法调用失败 


**注意**

+ 重复调用此接口时，仅最后一次调用生效。效果不会叠加。
+ 对于 iOS 平台，将 [ByteRTCVideoPreprocessorConfig](iOS-keytype.md#bytertcvideopreprocessorconfig) 中的 required_pixel_format 设置为 `kVideoPixelFormatUnknown`，可以通过避免格式转换带来一些性能优化。


<span id="ByteRTCVideo-registerlocalencodedvideoframeobserver"></span>
### registerLocalEncodedVideoFrameObserver:
```objectivec

- (void)registerLocalEncodedVideoFrameObserver:(_Nullable id<ByteRTCLocalEncodedVideoFrameObserver>) frameObserver;
```
注册本地视频帧监测器。  <br>
无论使用内部采集还是自定义采集，调用该方法后，SDK 每监测到一帧本地视频帧时，都会将视频帧信息通过 [onLocalEncodedVideoFrame:Frame:](iOS-callback.md#ByteRTCLocalEncodedVideoFrameObserver-onlocalencodedvideoframe-frame) 回调给用户

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| frameObserver | **id<ByteRTCLocalEncodedVideoFrameObserver>** | 本地视频帧监测器，参看 [ByteRTCLocalEncodedVideoFrameObserver](iOS-callback.md#bytertclocalencodedvideoframeobserver)。将参数设置为 nullptr 则取消注册。 |


**注意**
该方法可在进房前后任意时间调用，在进房前调用可保证尽可能早地监测视频帧并触发回调

<span id="ByteRTCVideo-setaudioroute"></span>
### setAudioRoute:
```objectivec

- (int)setAudioRoute:(ByteRTCAudioRoute)audioRoute;
```
设置当前音频播放路由。默认使用 [setDefaultAudioRoute:](#ByteRTCVideo-setdefaultaudioroute) 中设置的音频路由。
音频播放路由发生变化时，会收到 [rtcEngine:onAudioRouteChanged:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onaudioroutechanged) 回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioRoute | **ByteRTCAudioRoute** | 音频播放路由，参见 [ByteRTCAudioRoute](iOS-keytype.md#bytertcaudioroute)。<br/>不支持 `ByteRTCAudioRouteUnknown`。 |

**返回值**

+ 0: 方法调用成功  
+ < 0: 方法调用失败。失败原因参看 [ByteRTCMediaDeviceWarning](iOS-keytype.md#bytertcmediadevicewarning) 回调。指定为 `kAudioRouteUnknown` 时将会失败。  


**注意**

+ 你需要调用 [setAudioScenario:](#ByteRTCVideo-setaudioscenario) 将音频场景切换为 `ByteRTCAudioScenarioCommunication` 后再调用本接口。
+ 连接有线或者蓝牙音频播放设备后，音频路由将自动切换至此设备。
+ 移除后，音频设备会自动切换回原设备。
+ 不同音频场景中，音频路由和发布订阅状态到音量类型的映射关系详见 [ByteRTCAudioScenarioType](iOS-keytype.md#bytertcaudioscenariotype) 。


<span id="ByteRTCVideo-getaudioroute"></span>
### getAudioRoute
```objectivec

- (ByteRTCAudioRoute)getAudioRoute;
```
获取当前使用的音频播放路由。  <br>

**返回值**
详见 [ByteRTCAudioRoute](iOS-keytype.md#bytertcaudioroute)


**注意**
要设置音频路由，移动端详见 [setAudioRoute:](#ByteRTCVideo-setaudioroute)，桌面端详见 [setAudioPlaybackDevice:](#setaudioplaybackdevice)。

<span id="ByteRTCVideo-enableexternalsoundcard"></span>
### enableExternalSoundCard:
```objectivec

- (void)enableExternalSoundCard:(bool)enable;
```
启用匹配外置声卡的音频处理模式

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| enable | **bool** | • true: 开启 <br/>• false: 不开启(默认) |


**注意**

+ 当采用外接声卡进行音频采集时，建议开启此模式，以获得更好的音质。
+ 开启此模式时，仅支持耳机播放。如果需要使用扬声器或者外置音箱播放，关闭此模式。


<span id="ByteRTCVideo-setdefaultaudioroute"></span>
### setDefaultAudioRoute:
```objectivec

- (int)setDefaultAudioRoute:(ByteRTCAudioRoute)audioRoute;
```
将默认的音频播放设备设置为听筒或扬声器。  <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioRoute | **ByteRTCAudioRoute** | 音频播放设备。参看 [ByteRTCAudioRoute](iOS-keytype.md#bytertcaudioroute) |

**返回值**
方法调用结果  

+ 0: 方法调用成功。立即生效。当所有音频外设移除后，音频路由将被切换到默认设备。
+ < 0: 方法调用失败。指定除扬声器和听筒以外的设备将会失败。   


**注意**
参见[移动端设置音频路由](https://www.volcengine.com/docs/6348/117836)。

<span id="ByteRTCVideo-startlivetranscoding-transcoding-observer"></span>
### startLiveTranscoding:transcoding:observer:
```objectivec

- (int)startLiveTranscoding:(NSString * _Nonnull)task_id transcoding:(ByteRTCLiveTranscoding *_Nullable)transcoding observer:(id<LiveTranscodingDelegate> _Nullable)observer;
```
新增转推直播任务，并设置合流的图片、视频视图布局和音频属性。  <br>
同一个任务中转推多路直播流时，SDK 会先将多路流合成一路流，然后再进行转推。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| task_id | **NSString*** | 转推直播任务 ID。<br/>你可以在同一房间内发起多个转推直播任务，并用不同的任务 ID 加以区分。当你需要发起多个转推直播任务时，应使用多个 ID；当你仅需发起一个转推直播任务时，建议使用空字符串。 |
| transcoding | **ByteRTCLiveTranscoding*** | 转推直播配置参数，详见 [ByteRTCLiveTranscoding](iOS-keytype.md#bytertclivetranscoding)。 |
| observer | **id<LiveTranscodingDelegate>** | 端云一体转推直播观察者。详见 [LiveTranscodingDelegate](iOS-callback.md#livetranscodingdelegate)。  <br/>通过注册 observer 接收转推直播相关的回调。 |


**注意**

+ 调用该方法后，启动结果和推流过程中的错误均会通过回调 [onStreamMixingEvent:taskId:error:mixType:](iOS-callback.md#LiveTranscodingDelegate-onstreammixingevent-taskid-error-mixtype) 通知用户。
+ 调用 [stopLiveTranscoding:](#ByteRTCVideo-stoplivetranscoding) 停止转推直播


<span id="ByteRTCVideo-stoplivetranscoding"></span>
### stopLiveTranscoding:
```objectivec

- (int)stopLiveTranscoding:(NSString *_Nonnull)task_id;
```
停止转推直播，会收到 [onStreamMixingEvent:taskId:error:mixType:](iOS-callback.md#LiveTranscodingDelegate-onstreammixingevent-taskid-error-mixtype) 回调。  <br>
关于启动转推直播，参看 [startLiveTranscoding:transcoding:observer:](#ByteRTCVideo-startlivetranscoding-transcoding-observer)。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| task_id | **NSString*** | 转推直播任务 ID。可以指定想要停止的转推直播任务。 |

**返回值**
方法调用结果。  

+  0：方法调用成功  
+ < 0：方法调用失败


<span id="ByteRTCVideo-updatelivetranscoding-transcoding"></span>
### updateLiveTranscoding:transcoding:
```objectivec

- (int)updateLiveTranscoding:(NSString *_Nonnull)task_id transcoding:(ByteRTCLiveTranscoding *_Nonnull)transcoding;
```
更新转推直播参数，会收到 [onStreamMixingEvent:taskId:error:mixType:](iOS-callback.md#LiveTranscodingDelegate-onstreammixingevent-taskid-error-mixtype) 回调。  <br>
开启转推直播功能后，你可以使用此方法更新合流转推功能配置参数。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| task_id | **NSString*** | 转推直播任务 ID。指定想要更新参数设置的转推直播任务。 |
| transcoding | **ByteRTCLiveTranscoding*** | 配置参数，详见 [ByteRTCLiveTranscoding](iOS-keytype.md#bytertclivetranscoding) 。除特殊说明外，均支持过程中更新。调用时，结构体中没有传入值的属性，会被更新为默认值。 |

**返回值**
方法调用结果。  

+  0：方法调用成功  
+ < 0：方法调用失败


<span id="ByteRTCVideo-startpushsinglestreamtocdn-singlestream-observer"></span>
### startPushSingleStreamToCDN:singleStream:observer:
```objectivec

- (int)startPushSingleStreamToCDN:(NSString *_Nonnull)task_id singleStream:(ByteRTCPushSingleStreamParam *_Nonnull)singleStream observer:(id<ByteRTCPushSingleStreamToCDNObserver>_Nullable)observer;
```
新增单流转推直播任务。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| task_id | **NSString*** | 任务 ID。<br/>你可以发起多个转推直播任务，并用不同的任务 ID 加以区分。当你需要发起多个转推直播任务时，应使用多个 ID；当你仅需发起一个转推直播任务时，建议使用空字符串。 |
| singleStream | **ByteRTCPushSingleStreamParam*** | 转推直播配置参数。详见 [ByteRTCPushSingleStreamParam](iOS-keytype.md#bytertcpushsinglestreamparam)。 |
| observer | **id<ByteRTCPushSingleStreamToCDNObserver>** | 单流转推直播观察者。详见 [ByteRTCPushSingleStreamToCDNObserver](iOS-callback.md#bytertcpushsinglestreamtocdnobserver)。  <br/>通过注册 observer 接收单流转推直播相关的回调。 |


**注意**

+ 调用该方法后，关于启动结果和推流过程中的错误，会收到 [onStreamPushEvent:taskId:error:](iOS-callback.md#ByteRTCPushSingleStreamToCDNObserver-onstreampushevent-taskid-error) 回调。
+ 调用 [stopPushStreamToCDN:](#ByteRTCVideo-stoppushstreamtocdn) 停止任务。
+ 由于本功能不进行编解码，所以推到 RTMP 的视频流会根据推流端的分辨率、编码方式、关闭摄像头等变化而变化。


<span id="ByteRTCVideo-stoppushstreamtocdn"></span>
### stopPushStreamToCDN:
```objectivec

- (int)stopPushStreamToCDN:(NSString *_Nonnull)task_id;
```
停止转推直播。<br>
关于启动转推直播，参看 [startPushSingleStreamToCDN:singleStream:observer:](#ByteRTCVideo-startpushsinglestreamtocdn-singlestream-observer)。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| task_id | **NSString*** | 任务 ID。可以指定想要停止的单流转推直播任务。 |


<span id="ByteRTCVideo-startpushpublicstream-withlayout"></span>
### startPushPublicStream:withLayout:
```objectivec

- (int)startPushPublicStream:(NSString * _Nonnull)publicStreamId withLayout:(ByteRTCPublicStreaming *_Nullable)publicStream;
```
发布一路公共流<br>
用户可以指定房间内多个用户发布的媒体流合成一路公共流。使用同一 `appID` 的用户，可以调用 [startPlayPublicStream:](#ByteRTCVideo-startplaypublicstream) 获取和播放指定的公共流。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| publicStreamId | **NSString*** | 公共流 ID。 |
| publicStream | **NSString*** | 公共流参数。详见 [ByteRTCPublicStreaming](iOS-keytype.md#bytertcpublicstreaming)。<br/>一路公共流可以包含多路房间内的媒体流，按照指定的布局方式进行聚合。<br/>如果指定的媒体流还未发布，则公共流将在指定流开始发布后实时更新。 |

**返回值**

+ 0: 成功。同时将收到 [rtcEngine:onPushPublicStreamResult:publicStreamId:errorCode:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onpushpublicstreamresult-publicstreamid-errorcode) 回调。
+ !0: 失败。当参数不合法或参数为空，调用失败。


**注意**

+ 同一用户使用同一公共流 ID 多次调用本接口无效。如果你希望更新公共流参数，调用 [updatePublicStreamParam:withLayout:](#ByteRTCVideo-updatepublicstreamparam-withlayout) 接口。
+ 不同用户使用同一公共流 ID 多次调用本接口时，RTC 将使用最后一次调用时传入的参数更新公共流。
+ 使用不同的 ID 多次调用本接口可以发布多路公共流。
+ 调用 [stopPushPublicStream:](#ByteRTCVideo-stoppushpublicstream) 停止发布公共流。
+ 关于公共流功能的介绍，详见[发布和订阅公共流](https://www.volcengine.com/docs/6348/108930)


<span id="ByteRTCVideo-stoppushpublicstream"></span>
### stopPushPublicStream:
```objectivec

- (int)stopPushPublicStream:(NSString * _Nonnull)publicStreamId;
```
停止发布当前用户发布的公共流<br>
关于发布公共流，查看 [startPushPublicStream:withLayout:](#ByteRTCVideo-startpushpublicstream-withlayout)。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| publicStreamId | **NSString*** | 公共流 ID<br/>指定的流必须为当前用户所发布。 |

**返回值**

+ 0: 成功
+ !0: 失败


<span id="ByteRTCVideo-updatepublicstreamparam-withlayout"></span>
### updatePublicStreamParam:withLayout:
```objectivec

- (int)updatePublicStreamParam:(NSString * _Nonnull)publicStreamId withLayout:(ByteRTCPublicStreaming *_Nullable)publicStream;
```
更新公共流参数<br>
关于发布公共流，查看 [startPushPublicStream:withLayout:](#ByteRTCVideo-startpushpublicstream-withlayout)。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| publicStreamId | **NSString*** | 公共流ID<br/>指定的流必须为当前用户所发布的。 |
| publicStream | **NSString*** | 推公共流配置参数。详见 [ByteRTCPublicStreaming](iOS-keytype.md#bytertcpublicstreaming)。 |

**返回值**

+ 0: 成功
+ !0: 失败


**注意**
调用本接口前需要通过 onPushPublicStreamResult[rtcEngine:onPushPublicStreamResult:publicStreamId:errorCode:](#rtcengine-onpushpublicstreamresult-publicstreamid-errorcode) 确认公共流是否已经成功启动。

<span id="ByteRTCVideo-startplaypublicstream"></span>
### startPlayPublicStream:
```objectivec

- (int)startPlayPublicStream:(NSString * _Nonnull)publicStreamId;
```
订阅指定公共流<br>
无论用户是否在房间内，都可以调用本接口获取和播放指定的公共流。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| publicStreamId | **NSString*** | 公共流ID，如果指定流暂未发布，则本地客户端将在其开始发布后接收到流数据。 |

**返回值**

+ 0: 成功。同时将收到 [rtcEngine:onPlayPublicStreamResult:errorCode:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onplaypublicstreamresult-errorcode) 回调。
+ !0: 失败。当参数不合法或参数为空，调用失败。


**注意**

+ 在调用本接口之前，建议先绑定渲染视图。
- 调用 [setPublicStreamVideoCanvas:withCanvas:](#ByteRTCVideo-setpublicstreamvideocanvas-withcanvas) 绑定内部渲染视图。
- 调用 [setPublicStreamVideoSink:withSink:withPixelFormat:](#ByteRTCVideo-setpublicstreamvideosink-withsink-withpixelformat) 绑定自定义渲染视图：
+ 调用本接口后，可以通过 [rtcEngine:onFirstPublicStreamVideoFrameDecoded:withFrameInfo:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onfirstpublicstreamvideoframedecoded-withframeinfo) 和 [rtcEngine:onFirstPublicStreamAudioFrame:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onfirstpublicstreamaudioframe) 回调公共流的视频和音频首帧解码情况。
+ 调用本接口后，可以通过 [rtcEngine:onPublicStreamSEIMessageReceived:andMessage:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onpublicstreamseimessagereceived-andmessage) 回调公共流中包含的 SEI 信息。
+ 订阅公共流之后，可以通过调用 [stopPlayPublicStream:](#ByteRTCVideo-stopplaypublicstream) 接口取消订阅公共流。


<span id="ByteRTCVideo-stopplaypublicstream"></span>
### stopPlayPublicStream:
```objectivec

- (int)stopPlayPublicStream:(NSString * _Nonnull)publicStreamId;
```
取消订阅指定公共流<br>
关于订阅公共流，查看 [startPlayPublicStream:](#ByteRTCVideo-startplaypublicstream)。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| publicStreamId | **NSString*** | 公共流ID |

**返回值**

+ 0：成功  
+ !0：失败  


<span id="ByteRTCVideo-setpublicstreamvideocanvas-withcanvas"></span>
### setPublicStreamVideoCanvas:withCanvas:
```objectivec

- (int)setPublicStreamVideoCanvas:(NSString *_Nonnull)publicStreamId withCanvas:(ByteRTCVideoCanvas * _Nullable)canvas;
```
为指定公共流绑定内部渲染视图。  <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| publicStreamId | **NSString*** | 公共流ID |
| canvas | **ByteRTCVideoCanvas*** | 内部渲染视图，如果需要解除视频的绑定视图，把 videoCanvas 设置为空。详见 [ByteRTCVideoCanvas](iOS-keytype.md#bytertcvideocanvas) |

**返回值**

+ 0：成功  
+ !0：失败  


<span id="ByteRTCVideo-setpublicstreamvideosink-withsink-withpixelformat"></span>
### setPublicStreamVideoSink:withSink:withPixelFormat:
```objectivec

- (int)setPublicStreamVideoSink:(NSString *_Nonnull)publicStreamId withSink:(id<ByteRTCVideoSinkDelegate> _Nullable)videoSink withPixelFormat:(ByteRTCVideoSinkPixelFormat)requiredFormat;
```
为指定公共流绑定自定义渲染器。详见[自定义视频渲染](https://www.volcengine.com/docs/6348/81201)。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| publicStreamId | **NSString*** | 公共流ID |
| videoSink | **id<ByteRTCVideoSinkDelegate>** | 自定义视频渲染器，需要释放渲染器资源时，将 videoSink 设置为 `null`。参看 [ByteRTCVideoSinkDelegate](iOS-keytype.md#bytertcvideosinkdelegate) |
| requiredFormat | **ByteRTCVideoSinkPixelFormat** | videoSink 适用的视频帧编码格式，参看 [ByteRTCVideoSinkPixelFormat](iOS-keytype.md#bytertcvideosinkpixelformat) |

**返回值**

+ 0: 成功  
+ <0: 失败  


<span id="ByteRTCVideo-pushexternalvideoframe-time"></span>
### pushExternalVideoFrame:time:
```objectivec

- (BOOL)pushExternalVideoFrame:(CVPixelBufferRef _Nonnull )frame time:(CMTime)pts;
```
推送外部视频帧。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| frame | **CVPixelBufferRef** | 该视频帧包含待 SDK 编码的视频数据 |
| pts | **CMTime** | CMTime |

**返回值**

+ YES 推送成功  
+ NO 推送失败  


**注意**

+ 支持的格式：NV12, BGRA, ARGB
+ 推送外部视频帧前，必须调用 [setVideoSourceType:WithStreamIndex:](#ByteRTCVideo-setvideosourcetype-withstreamindex) 开启外部视频源采集。


<span id="ByteRTCVideo-pushexternalvideoframe-time-rotation"></span>
### pushExternalVideoFrame:time:rotation:
```objectivec

- (BOOL)pushExternalVideoFrame:(CVPixelBufferRef _Nonnull )frame time:(CMTime)pts rotation:(ByteRTCVideoRotation)rotation;
```
推送外部视频帧。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| frame | **CVPixelBufferRef** | 该视频帧包含待 SDK 编码的视频数据 |
| pts | **CMTime** | CMTime |
| rotation | **ByteRTCVideoRotation** | 当前视频角度，参看 [ByteRTCVideoRotation](iOS-keytype.md#bytertcvideorotation) |

**返回值**

+ YES 推送成功  
+ NO 推送失败  


**注意**

+ 支持的格式：NV12, BGRA, ARGB
+ 推送外部视频帧前，必须调用 [setVideoSourceType:WithStreamIndex:](#ByteRTCVideo-setvideosourcetype-withstreamindex) 开启外部视频源采集。


<span id="ByteRTCVideo-pushexternalvideoframe-time-rotation-extendeddata-supplementaryinfo"></span>
### pushExternalVideoFrame:time:rotation:extendedData:supplementaryInfo:
```objectivec

- (BOOL)pushExternalVideoFrame:(CVPixelBufferRef _Nonnull )frame time:(CMTime)pts rotation:(ByteRTCVideoRotation)rotation extendedData:(NSData* _Nullable)extendedData supplementaryInfo:(NSData* _Nullable)supplementoryInfo;
```
推送外部视频帧。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| frame | **CVPixelBufferRef** | 该视频帧包含待 SDK 编码的视频数据 |
| pts | **CMTime** | CMTime |
| rotation | **ByteRTCVideoRotation** | 当前视频角度，参看 [ByteRTCVideoRotation](iOS-keytype.md#bytertcvideorotation) |
| extendedData | **NSData*** | 当前帧的扩展数据，没有的话就传空 |
| supplementoryInfo | **NSData*** | 附加信息，比如人脸位置等等 |

**返回值**

+ YES 推送成功  
+ NO 推送失败  


**注意**

+ 支持的格式：NV12, BGRA, ARGB
+ 推送外部视频帧前，必须调用 [setVideoSourceType:WithStreamIndex:](#ByteRTCVideo-setvideosourcetype-withstreamindex) 开启外部视频源采集。


<span id="ByteRTCVideo-pushexternalbytevideoframe"></span>
### pushExternalByteVideoFrame:
```objectivec

- (BOOL)pushExternalByteVideoFrame:(ByteRTCVideoFrame * _Nonnull)frame;
```
推送外部视频帧，使用 ByteRTCVideoFrame 进行封装。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| frame | **ByteRTCVideoFrame*** | 该视频帧包含待 SDK 编码的视频数据，参考 [ByteRTCVideoFrame](iOS-keytype.md#bytertcvideoframe) |

**返回值**

+ YES 推送成功  
+ NO 推送失败  


**注意**
推送外部视频帧前，必须调用 [setVideoSourceType:WithStreamIndex:](#ByteRTCVideo-setvideosourcetype-withstreamindex) 开启外部视频源采集。

<span id="ByteRTCVideo-enableaudioframecallback-format"></span>
### enableAudioFrameCallback:format:
```objectivec

- (void)enableAudioFrameCallback:(ByteRTCAudioFrameCallbackMethod) method format:(ByteRTCAudioFormat* _Nullable)format;
```
设置并开启指定的音频数据帧回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| method | **ByteRTCAudioFrameCallbackMethod** | 音频回调方法，参看 [ByteRTCAudioFrameCallbackMethod](iOS-keytype.md#bytertcaudioframecallbackmethod)。  <br/>当音频回调方法设置为 `0`、`1`、`2`时，你需要在参数 `format` 中指定准确的采样率和声道，暂不支持设置为自动。  <br/>当音频回调方法设置为 `3`时，暂不支持音频参数格式中设置准确的采样率和声道，你需要设置为自动。 |
| format | **ByteRTCAudioFormat*** | 音频参数格式，参看 [ByteRTCAudioFormat](iOS-keytype.md#bytertcaudioformat)。 |


**注意**
开启音频回调并调用 [setAudioFrameObserver:](#ByteRTCVideo-setaudioframeobserver) 后，[ByteRTCAudioFrameObserver](iOS-callback.md#bytertcaudioframeobserver) 会收到对应的音频回调。两者调用顺序没有限制且相互独立。  

<span id="ByteRTCVideo-disableaudioframecallback"></span>
### disableAudioFrameCallback:
```objectivec

- (void)disableAudioFrameCallback:(ByteRTCAudioFrameCallbackMethod) method;
```
关闭音频回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| method | **ByteRTCAudioFrameCallbackMethod** | 音频回调方法，参看 [ByteRTCAudioFrameCallbackMethod](iOS-keytype.md#bytertcaudioframecallbackmethod)。 |


**注意**
该方法需要在调用 [enableAudioFrameCallback:format:](#ByteRTCVideo-enableaudioframecallback-format) 之后调用。

<span id="ByteRTCVideo-setaudioframeobserver"></span>
### setAudioFrameObserver:
```objectivec

- (BOOL)setAudioFrameObserver:(_Nullable id<ByteRTCAudioFrameObserver>) audioFrameObserver;
```
注册音频数据回调观察者。  <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioFrameObserver | **id<ByteRTCAudioFrameObserver>** | 音频数据观察者，参看 [ByteRTCAudioFrameObserver](iOS-callback.md#bytertcaudioframeobserver)。如果传入 null，则取消注册。 |

**返回值**

+ 0: 方法调用成功 
+ < 0: 方法调用失败 


**注意**
注册音频数据回调观察者并调用 [enableAudioFrameCallback:format:](#ByteRTCVideo-enableaudioframecallback-format) 后，[ByteRTCAudioFrameObserver](iOS-callback.md#bytertcaudioframeobserver) 会收到对应的音频回调。

<span id="ByteRTCVideo-registeraudioprocessor"></span>
### registerAudioProcessor:
```objectivec

- (BOOL)registerAudioProcessor:(_Nullable id<ByteRTCAudioFrameProcessor>)processor;
```
注册自定义音频处理器。<br>
注册完成后，你可以调用 [enableAudioProcessor:audioFormat:](#ByteRTCVideo-enableaudioprocessor-audioformat)，对本地采集或接收到的远端音频进行处理。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| processor | **id<ByteRTCAudioFrameProcessor>** | 自定义音频处理器，详见 [ByteRTCAudioFrameProcessor](iOS-callback.md#bytertcaudioframeprocessor)。<br/>SDK 只持有 processor 的弱引用，你应保证其生命周期。 |


**注意**
重复调用此接口时，仅最后一次调用生效。

<span id="ByteRTCVideo-enableaudioprocessor-audioformat"></span>
### enableAudioProcessor:audioFormat:
```objectivec

- (void)enableAudioProcessor:(ByteRTCAudioFrameMethod)method audioFormat:(ByteRTCAudioFormat *_Nullable)format;
```
设置并开启指定的音频帧回调，进行自定义处理。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| method | **ByteRTCAudioFrameMethod** | 音频帧类型，参看 [ByteRTCAudioFrameMethod](iOS-keytype#bytertcaudioframemethod)。可多次调用此接口，处理不同类型的音频帧。  <br/>选择不同类型的音频帧将收到对应的回调：  <br/>• 选择本地采集的音频时，会收到 [onProcessRecordAudioFrame:](iOS-callback.md#ByteRTCAudioFrameProcessor-onprocessrecordaudioframe)。<br/>• 选择远端音频流的混音音频时，会收到 [onProcessPlayBackAudioFrame:](iOS-callback.md#ByteRTCAudioFrameProcessor-onprocessplaybackaudioframe)。 <br/>• 选择远端音频流时，会收到 [onProcessRemoteUserAudioFrame:audioFrame:](iOS-callback.md#ByteRTCAudioFrameProcessor-onprocessremoteuseraudioframe-audioframe)。 <br/>• 选择软件耳返音频时，会收到 [onProcessEarMonitorAudioFrame:](iOS-callback.md#ByteRTCAudioFrameProcessor-onprocessearmonitoraudioframe)。(仅适用于 iOS 平台)<br/>• 选择屏幕共享音频流时，会收到 [onProcessScreenAudioFrame:](iOS-callback.md#ByteRTCAudioFrameProcessor-onprocessscreenaudioframe)。 |
| format | **ByteRTCAudioFormat*** | 设定自定义处理时获取的音频帧格式，参看 [ByteRTCAudioFormat](iOS-keytype.md#bytertcaudioformat)。 |


**注意**

+ 在调用此接口前，你需要调用 [registerAudioProcessor:](#ByteRTCVideo-registeraudioprocessor) 注册自定义音频处理器。
+ 要关闭音频自定义处理，调用 [disableAudioProcessor:](#ByteRTCVideo-disableaudioprocessor)。


<span id="ByteRTCVideo-disableaudioprocessor"></span>
### disableAudioProcessor:
```objectivec

- (void)disableAudioProcessor:(ByteRTCAudioFrameMethod)method;
```
关闭自定义音频处理。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| method | **ByteRTCAudioFrameMethod** | 音频帧类型，参看 [ByteRTCAudioFrameMethod](iOS-keytype.md#bytertcaudioframemethod)。 |


<span id="ByteRTCVideo-pushexternalaudioframe"></span>
### pushExternalAudioFrame:
```objectivec

- (int)pushExternalAudioFrame:(ByteRTCAudioFrame * _Nonnull) audioFrame;
```
推送自定义采集的音频数据到 RTC SDK。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioFrame | **ByteRTCAudioFrame*** | 音频数据帧，详见 [ByteRTCAudioFrame](iOS-keytype.md#bytertcaudioframe) |

**返回值**
方法调用结果  

+ 0: 设置成功  
+ < 0: 设置失败  


**注意**

+ 推送外部音频数据前，必须先调用 [setAudioSourceType:](#ByteRTCVideo-setaudiosourcetype) 开启自定义采集。
+ 你必须每隔 10 毫秒推送一次外部采集的音频数据。单次推送的 samples (音频采样点个数）应该为 audioFrame.sampleRate / 100。比如设置采样率为 48000 时， 每次应该推送 480 个采样点。  
+ 音频采样格式为 S16。音频缓冲区内的数据格式必须为 PCM 数据，其容量大小应该为 audioFrame.samples × audioFrame.channel × 2。


<span id="ByteRTCVideo-pullexternalaudioframe"></span>
### pullExternalAudioFrame:
```objectivec

- (int)pullExternalAudioFrame:(ByteRTCAudioFrame * _Nonnull) audioFrame;
```
拉取音频数据，用于自定义渲染。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioFrame | **ByteRTCAudioFrame*** | 音频数据帧，详见 [ByteRTCAudioFrame](iOS-keytype.md#bytertcaudioframe) |

**返回值**
方法调用结果  

+ 0: 设置成功  
+ < 0: 设置失败  


**注意**

+ 拉取外部音频数据前，必须先调用 [setAudioRenderType:](#ByteRTCVideo-setaudiorendertype) 开启自定义渲染。
+ 由于 RTC SDK 的帧长为 10 毫秒，你应当每隔 10 毫秒拉取一次音频数据。确保音频采样点数（sample）x 拉取频率等于 audioFrame 的采样率 （sampleRate）。如设置采样率为 48000 时，每 10 毫秒调用本接口拉取数据，每次应拉取 480 个采样点。 
+ 音频采样格式为 S16。音频缓冲区内的数据格式必须为 PCM 数据，其容量大小应该为 audioFrame.samples × audioFrame.channel × 2。  


<span id="ByteRTCVideo-setbusinessid"></span>
### setBusinessId:
```objectivec

- (int)setBusinessId:(NSString* _Nullable)businessId;
```
设置业务标识参数  <br>
可通过 businessId 区分不同的业务场景。businessId 由客户自定义，相当于一个“标签”，可以分担和细化现在 AppId 的逻辑划分的功能，但不需要鉴权。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| businessId | **NSString*** | 用户设置的自己的 businessId 值<br/>businessId 只是一个标签，颗粒度需要用户自定义。 |

**返回值**

+ 0： 成功  
+ < 0： 失败  
+ -6001： 用户已经在房间中。  
+ -6002： 输入非法，合法字符包括所有小写字母、大写字母和数字，除此外还包括四个独立字符分别是：英文句号，短横线，下划线和 @ 。


**注意**

+ 需要在调用 [joinRoomByToken:userInfo:roomConfig:](#ByteRTCRoom-joinroombytoken-userinfo-roomconfig) 之前调用，[joinRoomByToken:userInfo:roomConfig:](#ByteRTCRoom-joinroombytoken-userinfo-roomconfig)之后调用该方法无效。


<span id="ByteRTCVideo-feedback-desc"></span>
### feedback:desc:
```objectivec

- (int)feedback:(NSArray<ByteRTCProblemOption *> * _Nullable)types desc:(NSString* _Nullable)desc;
```
通话结束，将用户反馈的问题上报到 RTC <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| types | **NSArray<ByteRTCProblemOption*>*** | 预设问题列表，参看 [ByteRTCProblemOption](iOS-keytype.md#bytertcproblemoption) |
| desc | **NSString*** | 预设问题以外的其他问题的具体描述 |

**返回值**

+ 0: 上报成功  
+ -1: 上报失败，还没加入过房间 
+ -2: 上报失败，数据解析错误  
+ -3: 上报失败，字段缺失  


**注意**
如果用户上报时在房间内，那么问题会定位到用户当前所在的一个或多个房间；如果用户上报时不在房间内，那么问题会定位到引擎此前退出的房间。


<span id="ByteRTCVideo-setpublishfallbackoption"></span>
### setPublishFallbackOption:
```objectivec

- (int)setPublishFallbackOption:(ByteRTCPublishFallbackOption)option;
```
设置发布的音视频流的回退选项。  <br>
你可以调用该接口设置网络不佳或设备性能不足时从大流起进行降级处理，以保证通话质量。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| option | **ByteRTCPublishFallbackOption** | 本地发布的音视频流回退选项，参看 [ByteRTCPublishFallbackOption](iOS-keytype.md#bytertcpublishfallbackoption)。 |

**返回值**
方法调用结果： 

+ 0：成功  
+ < 0：失败


**注意**

+ 该方法仅在调用 [enableSimulcastMode:](#ByteRTCVideo-enablesimulcastmode) 开启了发送多路视频流的情况下生效。  
+ 该方法必须在进房前设置，进房后设置或更改设置无效。  
+ 设置回退后，本地发布的音视频流发生回退或从回退中恢复时，远端会收到 [rtcEngine:OnSimulcastSubscribeFallback:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onsimulcastsubscribefallback) 回调通知。  
+ 你可以调用客户端 API 或者在服务端下发策略设置回退。当使用服务端下发配置实现时，下发配置优先级高于在客户端使用 API 设定的配置。


<span id="ByteRTCVideo-setsubscribefallbackoption"></span>
### setSubscribeFallbackOption:
```objectivec

- (int)setSubscribeFallbackOption:(ByteRTCSubscribeFallbackOption)option;
```
设置订阅的音视频流的回退选项。 <br>
你可调用该接口设置网络不佳或设备性能不足时允许订阅流进行降级或只订阅音频流，以保证通话流畅。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| option | **ByteRTCSubscribeFallbackOption** | 订阅的音视频流回退选项，参看 [ByteRTCSubscribeFallbackOption](iOS-keytype.md#bytertcsubscribefallbackoption) 。 |

**返回值**
方法调用结果： 

+ 0：成功  
+ < 0：失败


**注意**

+ 你必须在进房前设置，进房后设置或更改设置无效。  
+ 设置回退选项后，订阅的音视频流发生回退或从回退中恢复时，会收到 [rtcEngine:OnSimulcastSubscribeFallback:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onsimulcastsubscribefallback) 和 [rtcEngine:onRemoteVideoSizeChanged:withFrameInfo:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onremotevideosizechanged-withframeinfo) 回调通知。  
+ 你可以调用 API 或者在服务端下发策略设置回退。当使用服务端下发配置实现时，下发配置优先级高于在客户端使用 API 设定的配置。


<span id="ByteRTCVideo-setremoteuserpriority-inroomid-uid"></span>
### setRemoteUserPriority:InRoomId:uid:
```objectivec

- (int)setRemoteUserPriority:(ByteRTCRemoteUserPriority)priority InRoomId:(NSString *_Nonnull)roomId uid:(NSString *_Nonnull)uid;
```
设置用户优先级

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| priority | **ByteRTCRemoteUserPriority** | 远端用户的优先级, 详见枚举类型 [ByteRTCRemoteUserPriority](iOS-keytype.md#bytertcremoteuserpriority) |
| roomId | **NSString*** | 房间 ID |
| uid | **NSString*** | 远端用户的 ID |

**返回值**

+ 0：方法调用成功  
+ < 0：方法调用失败  


**注意**

+ 该方法与 [setSubscribeFallbackOption:](#ByteRTCVideo-setsubscribefallbackoption)  搭配使用。  
+ 如果开启了订阅流回退选项，弱网或性能不足时会优先保证收到的高优先级用户的流的质量。  
+ 该方法在进房前后都可以使用，可以修改远端用户的优先级。


<span id="ByteRTCVideo-setencrypttype-key"></span>
### setEncryptType:key:
```objectivec

- (void)setEncryptType:(ByteRTCEncryptType)encrypt_type key:(NSString * _Nonnull)key;
```
设置传输时使用内置加密的方式 <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| encrypt_type | **ByteRTCEncryptType** | 内置加密算法，详见 [ByteRTCEncryptType](iOS-keytype.md#bytertcencrypttype) |
| key | **NSString*** | 加密密钥，长度限制为 36 位，超出部分将会被截断 |


**注意**

+ 使用传输时内置加密时，使用此方法；如果需要使用传输时自定义加密，参看 [ByteRTCEncryptRawData:](iOS-callback.md#ByteRTCEncryptHandler-bytertcencryptrawdata)。
内置加密和自定义加密互斥，根据最后一个调用的方法确定传输加密的方案。  

+ 该方法必须在进房之前调用，可重复调用，以最后调用的参数作为生效参数。  


<span id="ByteRTCVideo-setcustomizeencrypthandler"></span>
### setCustomizeEncryptHandler:
```objectivec

- (void)setCustomizeEncryptHandler:(id<ByteRTCEncryptHandler> _Nullable)handler;
```
设置自定义加密和解密方式
需要实现对应的加密和解密方法。详情参考 [ByteRTCEncryptHandler](iOS-callback.md#bytertcencrypthandler)  <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| handler | **id<ByteRTCEncryptHandler>** | 自定义加密 handler，需要实现里面的加密和解密方法 |


**注意**

+ 该方法与 [setEncryptType:key:](#ByteRTCVideo-setencrypttype-key) 为互斥关系,
即按照调用顺序，最后一个调用的方法为最终生效的版本  

+ 该方法必须在调用 [joinRoomByToken:userInfo:roomConfig:](#ByteRTCRoom-joinroombytoken-userinfo-roomconfig)
之前调用，可重复调用，以最后调用的参数作为生效参数  

+ 无论加密或者解密，其对原始数据的长度修改，需要控制在90%-120%之间，即如果输入数据为100字节，则处理完成后的数据必须在
90至120字节之间，如果加密或解密结果超出该长度限制，则该音视频桢会被丢弃  

+ 数据加密/解密为串行执行，因而视实现方式不同，可能会影响到最终渲染效率，是否使用该方法，需要由使用方谨慎评估  


<span id="ByteRTCVideo-creatertcroom"></span>
### createRTCRoom:
```objectivec

- ( ByteRTCRoom * _Nullable)createRTCRoom:(NSString * _Nonnull)roomId;
```
创建房间实例。
调用此方法仅返回一个房间实例，你仍需调用 [joinRoomByToken:userInfo:roomConfig:](#ByteRTCRoom-joinroombytoken-userinfo-roomconfig) 才能真正地创建/加入房间。
多次调用此方法以创建多个 [ByteRTCRoom](#bytertcroom) 实例。分别调用各 ByteRTCRoom 实例中的 [joinRoomByToken:userInfo:roomConfig:](#ByteRTCRoom-joinroombytoken-userinfo-roomconfig) 方法，同时加入多个房间。
多房间模式下，用户可以同时订阅各房间的音视频流。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| roomId | **NSString*** | 标识通话房间的房间 ID，最大长度为 128 字节的非空字符串。支持的字符集范围为:  <br/>• 26 个大写字母 A ~ Z； <br/>• 26 个小写字母 a ~ z； <br/>• 10 个数字 0 ~ 9；  <br/>• 下划线 "_", at 符 "@", 减号 "-"。 |

**返回值**
创建的 [ByteRTCRoom](#bytertcroom) 房间实例。


**注意**

+ 如果需要加入的房间已存在，你仍需先调用本方法来获取 ByteRTCRoom 实例，再调用 [joinRoomByToken:userInfo:roomConfig:](#ByteRTCRoom-joinroombytoken-userinfo-roomconfig) 加入房间。
+ 请勿使用同样的 roomId 创建多个房间，否则后创建的房间实例会替换先创建的房间实例。
+ 如果你需要在多个房间发布音视频流，无须创建多房间，直接调用 [startForwardStreamToRooms:](#ByteRTCRoom-startforwardstreamtorooms) 开始跨房间转发媒体流。


<span id="ByteRTCVideo-pushscreencaptureframe-time-rotation"></span>
### pushScreenCaptureFrame:time:rotation:
```objectivec

- (void)pushScreenCaptureFrame:(CVPixelBufferRef _Nonnull )frame time:(CMTime)pts rotation:(int)rotation;
```
推送外部屏幕采集帧

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| frame | **CVPixelBufferRef** | 该视频帧包含待 SDK 编码的视频数据 <br>支持的视频像素格式：NV12、BGRA、ARGB |
| pts | **CMTime** | 每一帧的时间戳，单位 ms |
| rotation | **int** | 帧的旋转角度包含: 0, 90, 180, 270 |


**注意**
屏幕采集分为内部采集和外部采集，本方法属于外部采集。

<span id="ByteRTCVideo-setextensionconfig"></span>
### setExtensionConfig:
```objectivec

- (void)setExtensionConfig:(NSString *_Nullable)groupId;
```
设置 Extension 配置项。你必须在使用屏幕内部采集功能前，设置使用的 Extension。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| groupId | **NSString*** | 你的应用和 Extension 应该归属于同一个 App Group，此处需要传入 Group Id。 |


**注意**
必须在调用 [createRTCVideo:delegate:parameters:](#ByteRTCVideo-creatertcvideo-delegate-parameters) 之后立即调用此方法。在引擎实例的生命周期中，此方法只需要调用一次。  

<span id="ByteRTCVideo-startscreencapture-bundleid"></span>
### startScreenCapture:bundleId:
```objectivec

- (void)startScreenCapture:(ByteRTCScreenMediaType) type bundleId:(NSString *_Nullable)bundleId;
```
使用 RTC SDK 内部采集模块开始采集屏幕音频流和（或）视频流。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| type | **ByteRTCScreenMediaType** | 媒体类型，参看 [ByteRTCScreenMediaType](iOS-keytype.md#bytertcscreenmediatype)。 |
| bundleId | **NSString*** | 绑定 Extension 的 Bundle ID，绑定后应用中共享屏幕的选择列表中只展示你的 Extension 可供选择。 |


**注意**

+ 当从 iOS 控制中心发起屏幕采集时无需调用本方法。 
+ 采集后，你还需要调用 [publishScreen:](#ByteRTCRoom-publishscreen) 发布采集到的屏幕音视频。
+ 开启屏幕音频/视频采集成功后，本地用户会收到 [rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onvideodevicestatechanged-device_type-device_state-device_error) 和 [rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onaudiodevicestatechanged-device_type-device_state-device_error) 回调。


<span id="ByteRTCVideo-updatescreencapture"></span>
### updateScreenCapture:
```objectivec

- (void)updateScreenCapture:(ByteRTCScreenMediaType) type;
```
更新内部屏幕采集时采集的媒体类型。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| type | **ByteRTCScreenMediaType** | 媒体类型，参看 [ByteRTCScreenMediaType](iOS-keytype.md#bytertcscreenmediatype)。 |


**注意**

+ 你需在开启屏幕视频流采集后调用该方法。
+ 本地用户会收到 [rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onvideodevicestatechanged-device_type-device_state-device_error) 或 [rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onaudiodevicestatechanged-device_type-device_state-device_error) 回调。


<span id="ByteRTCVideo-stopscreencapture"></span>
### stopScreenCapture
```objectivec

- (void)stopScreenCapture;
```
在屏幕共享时，停止使用 RTC SDK 内部采集方式采集屏幕音视频。


**注意**

+ 本方法只会停止本地屏幕采集，并不会影响屏幕流的发布状态。
+ 本地用户会收到 [rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onvideodevicestatechanged-device_type-device_state-device_error) 和 [rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onaudiodevicestatechanged-device_type-device_state-device_error) 的回调。 


<span id="ByteRTCVideo-sendscreencaptureextensionmessage"></span>
### sendScreenCaptureExtensionMessage:
```objectivec

- (void)sendScreenCaptureExtensionMessage:(NSData *_Nonnull) messsage;
```
向屏幕共享 Extension 发送自定义消息

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| messsage | **NSData*** | 发送给 Extension 的消息内容 |


**注意**
在 [startScreenCapture:bundleId:](#ByteRTCVideo-startscreencapture-bundleid) 后调用该方法。

<span id="ByteRTCVideo-setruntimeparameters"></span>
### setRuntimeParameters:
```objectivec

- (void)setRuntimeParameters:(NSDictionary * _Nullable)parameters;
```
设置运行时的参数

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| parameters | **NSDictionary*** | 保留参数 |


**注意**
该接口需在 [joinRoomByToken:userInfo:roomConfig:](#ByteRTCRoom-joinroombytoken-userinfo-roomconfig) 和 [startAudioCapture](#ByteRTCVideo-startaudiocapture) 之前调用。

<span id="ByteRTCVideo-startasr-handler"></span>
### startASR:handler:
```objectivec

- (void)startASR:(ByteRTCASRConfig *_Nonnull)asrConfig handler:(id<ByteRTCASREngineEventHandler> _Nonnull)handler ;
```
开启自动语音识别服务。该方法将识别后的用户语音转化成文字，并通过 [onMessage:](iOS-keytype.md#ByteRTCASREngineEventHandler-onmessage) 事件回调给用户。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| handler | **id<ByteRTCASREngineEventHandler>** | 语音识别服务使用状态回调，参看 [ByteRTCASREngineEventHandler](iOS-keytype.md#bytertcasrengineeventhandler) |
| asrConfig | **ByteRTCASRConfig*** | 校验信息，参看 [ByteRTCASRConfig](iOS-keytype.md#bytertcasrconfig) |


<span id="ByteRTCVideo-stopasr"></span>
### stopASR
```objectivec

- (void)stopASR;
```
关闭语音识别服务


<span id="ByteRTCVideo-startfilerecording-withrecordingconfig-type"></span>
### startFileRecording:withRecordingConfig:type:
```objectivec

- (int)startFileRecording:(ByteRTCStreamIndex)streamIndex withRecordingConfig:(ByteRTCRecordingConfig* _Nonnull)recordingConfig type:(ByteRTCRecordingType)recordingType;
```
该方法将通话过程中的音视频数据录制到本地的文件中。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamIndex | **ByteRTCStreamIndex** | 流属性，指定录制主流还是屏幕流，参看 [ByteRTCStreamIndex](iOS-keytype.md#bytertcstreamindex) |
| recordingConfig | **ByteRTCRecordingConfig*** | 本地录制参数配置，参看 [ByteRTCRecordingConfig](iOS-keytype.md#bytertcrecordingconfig) |
| recordingType | **ByteRTCRecordingType** | 本地录制的媒体类型，参看 [ByteRTCRecordingType](iOS-keytype.md#bytertcrecordingtype) |

**返回值**

+ 0: 正常
+ -1: 参数设置异常
+ -2: 当前版本 SDK 不支持该特性，请联系技术支持人员


**注意**

+ 调用该方法后，你会收到 [rtcEngine:onRecordingStateUpdate:state:error_code:recording_info:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onrecordingstateupdate-state-error_code-recording_info) 回调。  
+ 如果录制正常，系统每秒钟会通过 [rtcEngine:onRecordingProgressUpdate:process:recording_info:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onrecordingprogressupdate-process-recording_info) 回调通知录制进度。
+ 你需要在成功发流后才可以调用该方法进行录制。


<span id="ByteRTCVideo-stopfilerecording"></span>
### stopFileRecording:
```objectivec

- (void)stopFileRecording:(ByteRTCStreamIndex)streamIndex;
```
停止本地录制

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamIndex | **ByteRTCStreamIndex** | 流属性，指定停止主流或者屏幕流录制，参看 [ByteRTCStreamIndex](iOS-keytype.md#bytertcstreamindex) |


**注意**

+ 调用 [startFileRecording:withRecordingConfig:type:](#ByteRTCVideo-startfilerecording-withrecordingconfig-type) 开启本地录制后，你必须调用该方法停止录制。  
+ 调用该方法后，你会收到 [rtcEngine:onRecordingStateUpdate:state:error_code:recording_info:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onrecordingstateupdate-state-error_code-recording_info) 回调提示录制结果。


<span id="ByteRTCVideo-getaudiomixingmanager"></span>
### getAudioMixingManager
```objectivec

- (ByteRTCAudioMixingManager *_Nullable)getAudioMixingManager;
```
混音管理接口创建

**返回值**
混音管理实例，详见[ByteRTCAudioMixingManager](#bytertcaudiomixingmanager)


<span id="ByteRTCVideo-login-uid"></span>
### login:uid:
```objectivec

- (void)login:(NSString * _Nonnull)token uid:(NSString * _Nonnull)uid;
```
必须先登录，才能发送房间外点对点消息和向应用服务器发送消息<br>
在调用本接口登录后，如果想要登出，需要调用 [logout](#ByteRTCVideo-logout)

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| token | **NSString*** | 用户登录必须携带的 Token，用于鉴权验证。<br/>测试时可使用[控制台](https://console.volcengine.com/rtc/listRTC)生成临时 Token，`roomId` 填任意值。<br/>正式上线需要使用密钥 SDK 在你的服务端生成并下发 Token，`roomId` 置空，Token 有效期及生成方式参看[使用 Token 完成鉴权](70121)。 |
| uid | **NSString*** | 用户 ID  <br/>用户 ID 在 appid的维度下是唯一的。 |


**注意**
本地用户调用此方法登录后，会收到 [rtcEngine:onLoginResult:errorCode:elapsed:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onloginresult-errorcode-elapsed) 回调通知登录结果，远端用户不会收到通知。

<span id="ByteRTCVideo-logout"></span>
### logout
```objectivec

- (void)logout;
```
调用本接口登出后，无法调用房间外消息以及端到服务器消息相关的方法或收到相关回调。


**注意**

+ 调用本接口登出前，必须先调用 [login:uid:](#ByteRTCVideo-login-uid) 登录  
+ 本地用户调用此方法登出后，会收到 [rtcEngineOnLogout:](iOS-callback.md#ByteRTCVideoDelegate-rtcengineonlogout)  回调通知结果，远端用户不会收到通知。


<span id="ByteRTCVideo-updatelogintoken"></span>
### updateLoginToken:
```objectivec

- (void)updateLoginToken:(NSString * _Nonnull)token;
```
更新用户用于登录的 Token  <br>
Token 有一定的有效期，当 Token 过期时，需调用此方法更新登录的 Token 信息。  <br>
调用 [login:uid:](#ByteRTCVideo-login-uid) 方法登录时，如果使用了过期的 Token 将导致登录失败，并会收到 [rtcEngine:onLoginResult:errorCode:elapsed:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onloginresult-errorcode-elapsed) 回调通知，错误码为 ByteRTCLoginErrorCodeInvalidToken。此时需要重新获取 Token，并调用此方法更新 Token。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| token | **NSString*** | 更新的动态密钥 |


**注意**

+ 如果 Token 无效导致登录失败，则调用此方法更新 Token 后，SDK 会自动重新登录，而用户不需要自己调用 [login:uid:](#ByteRTCVideo-login-uid) 方法。  
+ Token 过期时，如果已经成功登录，则不会受到影响。Token 过期的错误会在下一次使用过期 Token 登录时，或因本地网络状况不佳导致断网重新登录时通知给用户。


<span id="ByteRTCVideo-setserverparams-url"></span>
### setServerParams:url:
```objectivec

- (void)setServerParams:(NSString * _Nonnull)signature url:(NSString * _Nonnull)url;
```
设置应用服务器参数  <br>
客户端调用 [sendServerMessage:](#ByteRTCVideo-sendservermessage) 或 [sendServerBinaryMessage:](#ByteRTCVideo-sendserverbinarymessage) 发送消息给应用服务器之前，必须需要设置有效签名和应用服务器地址。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| signature | **NSString*** | 动态签名  <br/>应用服务器会使用该签名对请求进行鉴权验证。 |
| url | **NSString*** | 应用服务器的地址 |


**注意**

+ 用户必须调用 [login:uid:](#ByteRTCVideo-login-uid) 登录后，才能调用本接口。  
+ 调用本接口后，SDK 会使用 [rtcEngine:onServerParamsSetResult:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onserverparamssetresult) 返回相应结果。


<span id="ByteRTCVideo-getpeeronlinestatus"></span>
### getPeerOnlineStatus:
```objectivec

- (void)getPeerOnlineStatus:(NSString * _Nonnull)peerUserId;
```
查询对端用户或本端用户的登录状态

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| peerUserId | **NSString*** | 需要查询的用户 ID |


**注意**

+ 必须调用 [login:uid:](#ByteRTCVideo-login-uid) 登录后，才能调用本接口。  
+ 调用本接口后，SDK 会使用 [rtcEngine:onGetPeerOnlineStatus:status:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-ongetpeeronlinestatus-status) 回调通知查询结果。  
+ 在发送房间外消息之前，用户可以通过本接口了解对端用户是否登录，从而决定是否发送消息。也可以通过本接口查询自己查看自己的登录状态。


<span id="ByteRTCVideo-sendusermessageoutsideroom-message-config"></span>
### sendUserMessageOutsideRoom:message:config:
```objectivec

- (int64_t)sendUserMessageOutsideRoom:(NSString * _Nonnull)userId message:(NSString * _Nonnull)messageStr config:(ByteRTCMessageConfig)config;
```
给房间外指定的用户发送文本消息（P2P）

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| userId | **NSString*** | 消息接收用户的 ID |
| messageStr | **NSString*** | 发送的文本消息内容  <br/>消息不超过 64 KB。 |
| config | **ByteRTCMessageConfig** | 消息类型，参看 [ByteRTCMessageConfig](iOS-keytype.md#bytertcmessageconfig)。 |

**返回值**

+ \>0：发送成功，返回这次发送消息的编号，从 1 开始递增  
+ -1：发送失败，ByteRTCVideo 实例未创建  
+ -2：发送失败，userId 为空


**注意**

+ 在发送房间外文本消息前，必须先调用 [login:uid:](#ByteRTCVideo-login-uid) 完成登录。  
+ 用户调用本接口发送文本信息后，会收到一次 [rtcEngine:onUserMessageSendResultOutsideRoom:error:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onusermessagesendresultoutsideroom-error) 回调，得知消息是否成功发送；  
+ 若文本消息发送成功，则 userId 所指定的用户会通过 [rtcEngine:onUserMessageReceivedOutsideRoom:message:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onusermessagereceivedoutsideroom-message) 回调收到该消息。


<span id="ByteRTCVideo-senduserbinarymessageoutsideroom-message-config"></span>
### sendUserBinaryMessageOutsideRoom:message:config:
```objectivec

- (int64_t)sendUserBinaryMessageOutsideRoom:(NSString * _Nonnull)userId message:(NSData * _Nonnull)messageStr config:(ByteRTCMessageConfig)config;
```
给房间外指定的用户发送二进制消息（P2P）

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| userId | **NSString*** | 消息接收用户的 ID |
| messageStr | **NSData*** | 发送的二进制消息内容  <br/>消息不超过 64KB。 |
| config | **ByteRTCMessageConfig** | 消息类型，参看 [ByteRTCMessageConfig](iOS-keytype.md#bytertcmessageconfig)。 |

**返回值**

+ \>0：发送成功，返回这次发送消息的编号，从 1 开始递增  
+ -1：发送失败，ByteRTCVideo 实例未创建  
+ -2：发送失败，userId 为空


**注意**

+ 在发送房间外二进制消息前，必须先调用 [login:uid:](#ByteRTCVideo-login-uid) 完成登录。  
+ 用户调用本接口发送二进制消息后，会收到一次 [rtcEngine:onUserMessageSendResultOutsideRoom:error:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onusermessagesendresultoutsideroom-error) 回调，通知消息是否发送成功；  
+ 若二进制消息发送成功，则 userId 所指定的用户会通过 [rtcEngine:onUserBinaryMessageReceivedOutsideRoom:message:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onuserbinarymessagereceivedoutsideroom-message)  回调收到该条消息。


<span id="ByteRTCVideo-sendservermessage"></span>
### sendServerMessage:
```objectivec

- (int64_t)sendServerMessage:(NSString * _Nonnull)messageStr;
```
客户端给应用服务器发送文本消息（P2Server）

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| messageStr | **NSString*** | 发送的文本消息内容  <br/>消息不超过 64 KB。 |

**返回值**

+ \>0：发送成功，返回这次发送消息的编号，从 1 开始递增  
+ -1：发送失败，ByteRTCVideo 实例未创建


**注意**

+ 在向应用服务器发送文本消息前，必须先调用 [login:uid:](#ByteRTCVideo-login-uid) 完成登录，随后调用 [setServerParams:url:](#ByteRTCVideo-setserverparams-url) 设置应用服务器。  
+ 调用本接口后，会收到一次 [rtcEngine:onServerMessageSendResult:error:message:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onservermessagesendresult-error-message) 回调，通知消息发送方是否发送成功。  
+ 若文本消息发送成功，则之前调用 [setServerParams:url:](#ByteRTCVideo-setserverparams-url) 设置的应用服务器会收到该条消息。


<span id="ByteRTCVideo-sendserverbinarymessage"></span>
### sendServerBinaryMessage:
```objectivec

- (int64_t)sendServerBinaryMessage:(NSData * _Nonnull)messageStr;
```
客户端给应用服务器发送二进制消息（P2Server）

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| messageStr | **NSData*** | 发送的二进制消息内容  <br/>消息不超过 64KB。 |

**返回值**

+ \>0：发送成功，返回这次发送消息的编号，从 1 开始递增  
+ -1：发送失败，ByteRTCVideo 实例未创建


**注意**

+ 在向应用服务器发送二进制消息前，先调用 [login:uid:](#ByteRTCVideo-login-uid) 完成登录，随后调用 [setServerParams:url:](#ByteRTCVideo-setserverparams-url) 设置应用服务器。  
+ 调用本接口后，会收到一次 [rtcEngine:onServerMessageSendResult:error:message:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onservermessagesendresult-error-message) 回调，通知消息发送方发送成功或失败；  
+ 若二进制消息发送成功，则之前调用 [setServerParams:url:](#ByteRTCVideo-setserverparams-url) 设置的应用服务器会收到该条消息。


<span id="ByteRTCVideo-startnetworkdetection-uplinkbandwidth-downlink-downlinkbandwidth"></span>
### startNetworkDetection:uplinkBandwidth:downlink:downlinkBandwidth:
```objectivec

- (ByteRTCNetworkDetectionStartReturn)startNetworkDetection:(bool)is_test_uplink uplinkBandwidth:(int)expected_uplink_bitrate downlink:(bool)is_test_downlink downlinkBandwidth:(int)expected_downlink_bitrate;
```
开始通话前网络探测

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| is_test_uplink | **bool** | 是否探测上行带宽 |
| expected_uplink_bitrate | **int** | 期望上行带宽，单位：kbps范围为 {0, [100-10000]}，其中， `0` 表示由 SDK 指定最高码率。 |
| is_test_downlink | **bool** | 是否探测下行带宽 |
| expected_downlink_bitrate | **int** | 期望下行带宽，单位：kbps范围为 {0, [100-10000]}，其中， `0` 表示由 SDK 指定最高码率。 |

**返回值**
开启通话前网络探测结果，详见 [ByteRTCNetworkDetectionStartReturn](iOS-errorcode.md#bytertcnetworkdetectionstartreturn)


**注意**

+ 成功调用本接口后，会在 3s 内收到一次 [rtcEngine:onNetworkDetectionResult:quality:rtt:lostRate:bitrate:jitter:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onnetworkdetectionresult-quality-rtt-lostrate-bitrate-jitter) 回调，此后每 2s 会收到一次该回调，通知探测结果；  
+ 若探测停止，则会收到一次 [rtcEngine:onNetworkDetectionStopped:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onnetworkdetectionstopped) 通知探测停止。


<span id="ByteRTCVideo-stopnetworkdetection"></span>
### stopNetworkDetection
```objectivec

- (void)stopNetworkDetection;
```
停止通话前网络探测


**注意**
调用本接口后，会收到一次 [rtcEngine:onNetworkDetectionStopped:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onnetworkdetectionstopped) 通知探测停止。


<span id="ByteRTCVideo-setscreenaudiosourcetype"></span>
### setScreenAudioSourceType:
```objectivec

- (void)setScreenAudioSourceType:(ByteRTCAudioSourceType)sourceType;
```
在屏幕共享时，设置屏幕音频的采集方式（内部采集/自定义采集）

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| sourceType | **ByteRTCAudioSourceType** | 屏幕音频输入源类型, 参看 [ByteRTCAudioSourceType](iOS-keytype.md#bytertcaudiosourcetype)。 |


**注意**

+ 默认采集方式是 RTC SDK 内部采集。
+ 你应该在 [publishScreen:](#ByteRTCRoom-publishscreen) 前，调用此方法。否则，你将收到 [rtcEngine:onWarning:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onwarning) 的报错：`ByteRTCWarningSetScreenAudioSourceTypeFailed`。 
+ 如果设定为内部采集，你必须重新开始采集。
+ 如果设定为自定义采集，你必须再调用 [pushScreenAudioFrame:](#ByteRTCVideo-pushscreenaudioframe) 将自定义采集到的屏幕音频帧推送到 RTC SDK。
+ 无论是内部采集还是自定义采集，你都必须调用 [publishScreen:](#ByteRTCRoom-publishscreen) 将采集到的屏幕音频发布给远端。


<span id="ByteRTCVideo-setscreenaudiostreamindex"></span>
### setScreenAudioStreamIndex:
```objectivec

- (void)setScreenAudioStreamIndex:(ByteRTCStreamIndex) index;
```
在屏幕共享时，设置屏幕音频流和麦克风采集到的音频流的混流方式

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| index | **ByteRTCStreamIndex** | 混流方式，参看 [ByteRTCStreamIndex](iOS-keytype.md#bytertcstreamindex) <br/>• `ByteRTCStreamIndexMain`: 将屏幕音频流和麦克风采集到的音频流混流 <br/>• `ByteRTCStreamIndexScreen`: 默认值，将屏幕音频流和麦克风采集到的音频流分为两路音频流 |


**注意**
你应该在 [publishScreen:](#ByteRTCRoom-publishscreen) 之前，调用此方法。否则，你将收到 [rtcEngine:onWarning:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onwarning) 的报错：`ByteRTCWarningSetScreenAudioStreamIndexFailed`

<span id="ByteRTCVideo-pushscreenaudioframe"></span>
### pushScreenAudioFrame:
```objectivec

- (int) pushScreenAudioFrame:(ByteRTCAudioFrame* _Nonnull)audioFrame;
```
使用自定义采集方式，采集屏幕共享时的屏幕音频时，将音频帧推送至 RTC SDK 处进行编码等处理。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioFrame | **ByteRTCAudioFrame*** | 音频数据帧，参见 [ByteRTCAudioFrame](iOS-keytype.md#bytertcaudioframe) |

**返回值**
方法调用结果  

+ 0: 设置成功  
+ < 0: 设置失败  


**注意**

+ 调用此接口推送屏幕共享时的自定义采集的音频数据前，必须调用 [setScreenAudioSourceType:](#ByteRTCVideo-setscreenaudiosourcetype) 开启屏幕音频自定义采集。  
+ 你应每隔 10 毫秒，调用一次此方法推送一次自定义采集的音频帧。一次推送的音频帧中应包含 frame.sample_rate / 100 个音频采样点。比如，假如采样率为 48000Hz，则每次应该推送 480 个采样点。  
+ 音频采样格式为 S16。音频缓冲区内的数据格式必须为 PCM 数据，其容量大小应该为 samples × frame.channel × 2。  
+ 调用此接口将自定义采集的音频帧推送到 RTC SDK 后，你必须调用 [publishScreen:](#ByteRTCRoom-publishscreen) 将采集到的屏幕音频推送到远端。在调用 [publishScreen:](#ByteRTCRoom-publishscreen) 前，推送到 RTC SDK 的音频帧信息会丢失。


<span id="ByteRTCVideo-setvideosourcetype-withstreamindex"></span>
### setVideoSourceType:WithStreamIndex:
```objectivec

- (void)setVideoSourceType:(ByteRTCVideoSourceType)type WithStreamIndex:(ByteRTCStreamIndex)streamIndex;
```
设置向 SDK 输入的视频源，包括屏幕流
默认使用内部采集。内部采集指：使用 RTC SDK 内置的视频采集机制进行视频采集。 <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| type | **ByteRTCVideoSourceType** | 视频输入源类型，参看 [ByteRTCVideoSourceType](iOS-keytype.md#bytertcvideosourcetype) |
| streamIndex | **ByteRTCStreamIndex** | 视频流的属性，参看 [ByteRTCStreamIndex](iOS-keytype.md#bytertcstreamindex) |


**注意**

+ 该方法进房前后均可调用。  
+ 当你已调用 [startVideoCapture](#ByteRTCVideo-startvideocapture) 开启内部采集后，再调用此方法切换至自定义采集时，SDK 会自动关闭内部采集。  
+ 当你调用此方法开启自定义采集后，想要切换至内部采集，你必须先调用此方法关闭自定义采集，然后调用 [startVideoCapture](#ByteRTCVideo-startvideocapture) 手动开启内部采集。
+ 当你需要向 SDK 推送自定义编码后的视频帧，你需调用该方法将视频源切换至自定义编码视频源。


<span id="ByteRTCVideo-setexternalvideoencodereventhandler"></span>
### setExternalVideoEncoderEventHandler:
```objectivec

- (void)setExternalVideoEncoderEventHandler:(id<ByteRTCExternalVideoEncoderEventHandler> _Nullable)handler;
```
注册自定义编码帧推送事件回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| handler | **id<ByteRTCExternalVideoEncoderEventHandler>** | 自定义编码帧回调类，参看 [ByteRTCExternalVideoEncoderEventHandler](iOS-callback.md#bytertcexternalvideoencodereventhandler) |


**注意**

+ 该方法需在进房前调用。 
+ 引擎销毁前需取消注册，调用该方法将参数设置为 nullptr 即可。


<span id="ByteRTCVideo-pushexternalencodedvideoframe-withvideoindex-withencodedvideoframe"></span>
### pushExternalEncodedVideoFrame:withVideoIndex:withEncodedVideoFrame:
```objectivec

- (BOOL)pushExternalEncodedVideoFrame:(ByteRTCStreamIndex)streamIndex withVideoIndex:(NSInteger)videoIndex withEncodedVideoFrame:(ByteRTCEncodedVideoFrame* _Nonnull)videoFrame;
```
推送自定义编码后的视频流

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamIndex | **ByteRTCStreamIndex** | 需要推送的编码流的属性，参看 [ByteRTCStreamIndex](iOS-keytype.md#bytertcstreamindex) |
| videoIndex | **NSInteger** | 对应的编码流下标，从 0 开始，如果调用 [SetVideoEncoderConfig:](#ByteRTCVideo-setvideoencoderconfig) 设置了多路流，此处数量须与之保持一致 |
| videoFrame | **ByteRTCEncodedVideoFrame*** | 编码流视频帧信息，参看 [ByteRTCEncodedVideoFrame](iOS-keytype.md#bytertcencodedvideoframe)。 |


**注意**

+ 目前仅支持推送 H264 和 ByteVC1 格式的视频帧，且视频流协议格式须为 Annex B 格式。  
+ 该函数运行在用户调用线程内  
+ 推送自定义编码视频帧前，必须调用 [setVideoSourceType:WithStreamIndex:](#ByteRTCVideo-setvideosourcetype-withstreamindex) 将视频输入源切换至自定义编码视频源。


<span id="ByteRTCVideo-setvideodecoderconfig-withvideodecoderconfig"></span>
### setVideoDecoderConfig:withVideoDecoderConfig:
```objectivec

- (void)setVideoDecoderConfig:(ByteRTCRemoteStreamKey * _Nonnull)key withVideoDecoderConfig:(ByteRTCVideoDecoderConfig)config;
```
在订阅远端视频流之前，设置远端视频数据解码方式

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| key | **ByteRTCRemoteStreamKey*** | 远端流信息，指定对哪一路视频流进行解码方式设置，参看 [ByteRTCRemoteStreamKey](iOS-keytype.md#bytertcremotestreamkey)。 |
| config | **ByteRTCVideoDecoderConfig** | 视频解码方式，参看 [ByteRTCVideoDecoderConfig](iOS-keytype.md#bytertcvideodecoderconfig)。 |


**注意**

+ 该方法仅适用于手动订阅模式，并且在订阅远端流之前使用。  
+ 当你想要对远端流进行自定义解码时，你需要先调用 [registerRemoteEncodedVideoFrameObserver:](#ByteRTCVideo-registerremoteencodedvideoframeobserver) 注册远端视频流监测器，然后再调用该接口将解码方式设置为自定义解码。监测到的视频数据会通过 [onRemoteEncodedVideoFrame:withEncodedVideoFrame:](iOS-callback.md#ByteRTCRemoteEncodedVideoFrameObserver-onremoteencodedvideoframe-withencodedvideoframe) 回调出来。


<span id="ByteRTCVideo-requestremotevideokeyframe"></span>
### requestRemoteVideoKeyFrame:
```objectivec

- (void)requestRemoteVideoKeyFrame:(ByteRTCRemoteStreamKey * _Nonnull)key;
```
在订阅远端视频流之后，向远端请求关键帧

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| key | **ByteRTCRemoteStreamKey*** | 远端流信息，参看 [ByteRTCRemoteStreamKey](iOS-keytype.md#bytertcremotestreamkey)。 |


**注意**

+ 该方法仅适用于手动订阅模式，并且在成功订阅远端流之后使用。  
+ 该方法适用于调用 [setVideoDecoderConfig:withVideoDecoderConfig:](#ByteRTCVideo-setvideodecoderconfig-withvideodecoderconfig) 开启自定义解码功能后，并且自定义解码失败的情况下使用


<span id="ByteRTCVideo-registerremoteencodedvideoframeobserver"></span>
### registerRemoteEncodedVideoFrameObserver:
```objectivec

- (void)registerRemoteEncodedVideoFrameObserver:(id<ByteRTCRemoteEncodedVideoFrameObserver> _Nullable)observer;
```
注册远端编码后视频数据回調。  <br>
完成注册后，当 SDK 监测到远端编码后视频帧时，会触发 [onRemoteEncodedVideoFrame:withEncodedVideoFrame:](iOS-callback.md#ByteRTCRemoteEncodedVideoFrameObserver-onremoteencodedvideoframe-withencodedvideoframe) 回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| observer | **id<ByteRTCRemoteEncodedVideoFrameObserver>** | 远端编码后视频数据监测器，参看 [ByteRTCRemoteEncodedVideoFrameObserver](iOS-callback.md#bytertcremoteencodedvideoframeobserver) |


**注意**

+ 更多自定义解码功能说明参看 [自定义视频编解码](https://www.volcengine.com/docs/6348/82921#%E8%87%AA%E5%AE%9A%E4%B9%89%E8%A7%86%E9%A2%91%E8%A7%A3%E7%A0%81)。
+ 该方法适用于手动订阅，并且进房前后均可调用，建议在进房前调用。
+ 引擎销毁前需取消注册，调用该方法将参数设置为 nullptr 即可。


<span id="ByteRTCVideo-sendstreamsyncinfo-config"></span>
### sendStreamSyncInfo:config:
```objectivec

- (int)sendStreamSyncInfo:(NSData* _Nonnull)data config:(ByteRTCStreamSycnInfoConfig * _Nonnull)config;
```
发送音频流同步信息。将消息通过音频流发送到远端，并实现与音频流同步，该接口调用成功后，远端用户会收到 [rtcEngine:onStreamSyncInfoReceived:streamType:data:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onstreamsyncinforeceived-streamtype-data) 回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| data | **NSData*** | 消息内容。 |
| config | **ByteRTCStreamSycnInfoConfig*** | 媒体流信息同步的相关配置，详见 [ByteRTCStreamSycnInfoConfig](iOS-keytype.md#bytertcstreamsycninfoconfig) 。 |

**返回值**

+ \>=0: 消息发送成功。返回成功发送的次数。  
+ -1: 消息发送失败。消息长度大于 255 字节。  
+ -2: 消息发送失败。传入的消息内容为空。  
+ -3: 消息发送失败。通过屏幕流进行消息同步时，此屏幕流还未发布。  
+ -4: 消息发送失败。通过用麦克风或自定义设备采集到的音频流进行消息同步时，此音频流还未发布，详见错误码 [ByteRTCErrorCode](iOS-errorcode.md#bytertcerrorcode)。  


**注意**

+ 调用本接口的频率建议不超过 50 次每秒。
+ 在采用 `ByteRTCRoomProfileInteractivePodcast` 作为房间模式时，此消息一定会送达。在其他房间模式下，如果本地用户未说话，此消息不一定会送达。

<span id="ByteRTCVideo-startechotest-playdelay"></span>
### startEchoTest:playDelay:
```objectivec

- (int)startEchoTest:(ByteRTCEchoTestConfig *_Nullable)echoConfig playDelay:(NSInteger)delayTime;
```
开启音视频回路测试。  <br>
在进房前，用户可调用该接口对音视频通话全链路进行检测，包括对音视频设备以及用户上下行网络的检测，从而帮助用户判断是否可以正常发布和接收音视频流。  <br>
开始检测后，SDK 会录制你声音或视频。如果你在设置的延时范围内收到了回放，则视为音视频回路测试正常。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| echoConfig | **ByteRTCEchoTestConfig*** | 回路测试参数设置，参看 [ByteRTCEchoTestConfig](iOS-keytype.md#bytertcechotestconfig)。 |
| delayTime | **NSInteger** | 音视频延迟播放的时间间隔，用于指定在开始检测多长时间后期望收到回放。取值范围为 [2,10]，单位为秒，默认为 2 秒。 |

**返回值**
方法调用结果：  

+ 0：成功  
+ -1：失败，当前用户已经在检测中  
+ -2：失败，用户已进房  
+ -3：失败，音视频均未采集  
+ -4：失败，参数异常  
+ -5：失败，已经存在相同 roomId 的房间


**注意**

+ 调用该方法开始音视频回路检测后，你可以调用 [stopEchoTest](#ByteRTCVideo-stopechotest) 立即结束测试，也可等待测试 60s 后自动结束，以更换设备进行下一次测试，或进房。  
+ 在该方法之前调用的所有跟设备控制、流控制相关的方法均在开始检测时失效，在结束检测后恢复生效。  
+ 在调用 [startEchoTest:playDelay:](#ByteRTCVideo-startechotest-playdelay) 和 [stopEchoTest](#ByteRTCVideo-stopechotest) 之间调用的所有跟设备采集、流控制、进房相关的方法均不生效，并会收到 [rtcEngine:onWarning:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onwarning) 回调，提示警告码为 `ByteRTCWarningCodeInEchoTestMode`。  
+ 音视频回路检测的结果会通过 [rtcEngine:onEchoTestResult:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onechotestresult) 回调通知。


<span id="ByteRTCVideo-stopechotest"></span>
### stopEchoTest
```objectivec

- (int)stopEchoTest;
```
停止音视频回路测试。  <br>
调用 [startEchoTest:playDelay:](#ByteRTCVideo-startechotest-playdelay) 开启音视频回路检测后，你必须调用该方法停止检测。

**返回值**
方法调用结果：  

+ 0：成功  
+ -1：失败，未开启回路检测


**注意**
音视频回路检测结束后，所有对系统设备及音视频流的控制均会恢复到开始检测前的状态。

<span id="ByteRTCVideo-setvideowatermark-withimagepath-withrtcwatermarkconfig"></span>
### SetVideoWatermark:WithImagePath:WithRtcWatermarkConfig:
```objectivec

- (void)SetVideoWatermark:(ByteRTCStreamIndex)streamIndex WithImagePath:(NSString * _Nullable)imagePath WithRtcWatermarkConfig:(ByteRTCVideoWatermarkConfig* _Nonnull)rtcWatermarkConfig;
```
在指定视频流上添加水印。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamIndex | **ByteRTCStreamIndex** | 需要添加水印的视频流属性，参看 [ByteRTCStreamIndex](iOS-keytype.md#bytertcstreamindex)。 |
| imagePath | **NSString*** | 水印图片路径，仅支持本地文件绝对路径，长度限制为 512 字节。   <br/>水印图片为 PNG 或 JPG 格式。 |
| rtcWatermarkConfig | **ByteRTCVideoWatermarkConfig*** | 水印参数，参看 [ByteRTCVideoWatermarkConfig](iOS-keytype.md#bytertcvideowatermarkconfig)。 |


**注意**

+ 调用 ClearVideoWatermark[ClearVideoWatermark:](#clearvideowatermark) 移除指定视频流的水印。  
+ 同一路流只能设置一个水印，新设置的水印会代替上一次的设置。你可以多次调用本方法来设置不同流的水印。  
+ 进入房间前后均可调用此方法。  
+ 开启本地预览镜像，或本地预览和编码传输镜像时，远端水印均不镜像；开启本地预览镜像时，本端水印会镜像。
+ 开启大小流后，水印对大小流均生效，且针对小流进行等比例缩小。


<span id="ByteRTCVideo-clearvideowatermark"></span>
### ClearVideoWatermark:
```objectivec

- (void)ClearVideoWatermark:(ByteRTCStreamIndex)streamIndex;
```
移除指定视频流的水印。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamIndex | **ByteRTCStreamIndex** | 需要移除水印的视频流属性，参看 [ByteRTCStreamIndex](iOS-keytype.md#bytertcstreamindex) |


<span id="ByteRTCVideo-takelocalsnapshot-callback"></span>
### takeLocalSnapshot:callback:
```objectivec

- (NSInteger)takeLocalSnapshot:(ByteRTCStreamIndex)streamIndex callback:(id<ByteRTCVideoSnapshotCallbackDelegate> _Nullable)callback;
```
截取本地视频画面

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamIndex | **ByteRTCStreamIndex** | 截图的视频流的属性，参看 [ByteRTCStreamIndex](iOS-keytype.md#bytertcstreamindex)。 |
| callback | **id<ByteRTCVideoSnapshotCallbackDelegate>** | 本地截图的回调。参看 [ByteRTCVideoSnapshotCallbackDelegate](iOS-callback.md#bytertcvideosnapshotcallbackdelegate)。 |

**返回值**
本地截图任务的编号，从 `1` 开始递增。


**注意**

+ 对截取的画面，包含本地视频处理的全部效果，包含旋转，镜像，美颜等。
+ 不管采用 SDK 内部采集，还是自定义采集，都可以进行截图。


<span id="ByteRTCVideo-takeremotesnapshot-callback"></span>
### takeRemoteSnapshot:callback:
```objectivec

- (NSInteger)takeRemoteSnapshot:(ByteRTCRemoteStreamKey* _Nonnull)streamKey callback:(id<ByteRTCVideoSnapshotCallbackDelegate> _Nullable)callback;
```
截取远端视频画面

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamKey | **ByteRTCRemoteStreamKey*** | 截图的视频流，参看 [ByteRTCRemoteStreamKey](iOS-keytype.md#bytertcremotestreamkey)。 |
| callback | **id<ByteRTCVideoSnapshotCallbackDelegate>** | 参看 [ByteRTCVideoSnapshotCallbackDelegate](iOS-callback.md#bytertcvideosnapshotcallbackdelegate)。 |

**返回值**
远端截图任务的编号，从 `1` 开始递增。


<span id="ByteRTCVideo-startcloudproxy"></span>
### startCloudProxy:
```objectivec

- (void)startCloudProxy:(NSArray <ByteRTCCloudProxyInfo *> * _Nullable)cloudProxiesInfo;
```
开启云代理

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| cloudProxiesInfo | **NSArray <ByteRTCCloudProxyInfo*>*** | 云代理服务器信息列表。参看 [ByteRTCCloudProxyInfo](iOS-keytype.md#bytertccloudproxyinfo)。 |


**注意**

+ 在加入房间前调用此接口  
+ 在开启云代理后，进行通话前网络探测 
+ 开启云代理后，并成功链接云代理服务器后，会收到 [rtcEngine:onCloudProxyConnected:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-oncloudproxyconnected)。
+ 要关闭云代理，调用 [stopCloudProxy](#ByteRTCVideo-stopcloudproxy)。


<span id="ByteRTCVideo-stopcloudproxy"></span>
### stopCloudProxy
```objectivec

- (void)stopCloudProxy;
```
关闭云代理


**注意**
要开启云代理，调用 [startCloudProxy:](#ByteRTCVideo-startcloudproxy)

<span id="ByteRTCVideo-getsingscoringmanager"></span>
### getSingScoringManager
```objectivec

- (ByteRTCSingScoringManager *_Nullable)getSingScoringManager;
```
创建 K 歌评分管理接口。

**返回值**
K 歌评分管理接口,详见 [ByteRTCSingScoringManager](#bytertcsingscoringmanager)。


<span id="ByteRTCVideo-getktvmanager"></span>
### getKTVManager
```objectivec

- (ByteRTCKTVManager * _Nullable)getKTVManager;
```
创建 KTV 管理接口。

**返回值**
KTV 管理接口，参看 [ByteRTCKTVManager](#bytertcktvmanager)。


# ByteRTCAudioMixingManager
```objectivec
@interface ByteRTCAudioMixingManager : NSObject
```



## 成员函数

| 返回 | 名称 |
| --- | --- |
| **void** | [startAudioMixing:filePath:config:](#ByteRTCAudioMixingManager-startaudiomixing-filepath-config) |
| **void** | [stopAudioMixing:](#ByteRTCAudioMixingManager-stopaudiomixing) |
| **void** | [pauseAudioMixing:](#ByteRTCAudioMixingManager-pauseaudiomixing) |
| **void** | [resumeAudioMixing:](#ByteRTCAudioMixingManager-resumeaudiomixing) |
| **void** | [preloadAudioMixing:filePath:](#ByteRTCAudioMixingManager-preloadaudiomixing-filepath) |
| **void** | [unloadAudioMixing:](#ByteRTCAudioMixingManager-unloadaudiomixing) |
| **void** | [setAllAudioMixingVolume:type:](#ByteRTCAudioMixingManager-setallaudiomixingvolume-type) |
| **void** | [setAudioMixingVolume:volume:type:](#ByteRTCAudioMixingManager-setaudiomixingvolume-volume-type) |
| **int** | [getAudioMixingDuration:](#ByteRTCAudioMixingManager-getaudiomixingduration) |
| **int** | [getAudioMixingCurrentPosition:](#ByteRTCAudioMixingManager-getaudiomixingcurrentposition) |
| **void** | [setAudioMixingPosition:position:](#ByteRTCAudioMixingManager-setaudiomixingposition-position) |
| **void** | [setAudioMixingDualMonoMode:mode:](#ByteRTCAudioMixingManager-setaudiomixingdualmonomode-mode) |
| **void** | [setAudioMixingPitch:pitch:](#ByteRTCAudioMixingManager-setaudiomixingpitch-pitch) |
| **int** | [setAudioMixingPlaybackSpeed:speed:](#ByteRTCAudioMixingManager-setaudiomixingplaybackspeed-speed) |
| **void** | [setAudioMixingLoudness:loudness:](#ByteRTCAudioMixingManager-setaudiomixingloudness-loudness) |
| **void** | [setAudioMixingProgressInterval:interval:](#ByteRTCAudioMixingManager-setaudiomixingprogressinterval-interval) |
| **void** | [enableAudioMixingFrame:type:](#ByteRTCAudioMixingManager-enableaudiomixingframe-type) |
| **void** | [disableAudioMixingFrame:](#ByteRTCAudioMixingManager-disableaudiomixingframe) |
| **int** | [pushAudioMixingFrame:audioFrame:](#ByteRTCAudioMixingManager-pushaudiomixingframe-audioframe) |
| **int** | [getAudioTrackCount:](#ByteRTCAudioMixingManager-getaudiotrackcount) |
| **void** | [selectAudioTrack:audioTrackIndex:](#ByteRTCAudioMixingManager-selectaudiotrack-audiotrackindex) |
| **int** | [getAudioMixingPlaybackDuration:](#ByteRTCAudioMixingManager-getaudiomixingplaybackduration) |


## 函数说明
<span id="ByteRTCAudioMixingManager-startaudiomixing-filepath-config"></span>
### startAudioMixing:filePath:config:
```objectivec

- (void)startAudioMixing:(int)mixId filePath:(NSString *_Nullable)filePath config:(ByteRTCAudioMixingConfig *_Nullable)config;
```
开始播放音频文件。
可以通过传入不同的 mixId 和 filepath 多次调用本方法，以实现同时播放多个混音文件，实现混音叠加。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mixId | **int** | 混音 ID。用于标识混音，请保证混音 ID 唯一性。  <br/>如果使用相同的 ID 重复调用本方法后，前一次混音会停止，后一次混音开始，SDK 会使用 `onAudioMixingStateChanged` 回调通知前一次混音已停止。 |
| filePath | **NSString*** | 用于混音文件路径。<br/>支持在线文件的 URL、和本地文件的绝对路径。对于在线文件的 URL，仅支持 https 协议。<br/>推荐的音频文件采样率：8KHz、16KHz、22.05KHz、44.1KHz、48KHz。<br/>不同平台支持的音频文件格式:<br/><table><br/><tr><th></th><th>mp3</th><th>mp4</th><th>aac</th><th>m4a</th><th>3gp</th><th>wav</th><th>ogg</th><th>ts</th><th>wma</th></tr><br/><tr><td>Android</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td></tr><br/><tr><td>iOS</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td><td></td></tr><br/><tr><td>Windows</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td>Y</td><td>Y</td></tr><br/></table> |
| config | **ByteRTCAudioMixingConfig*** | 混音配置  <br/>可以设置混音的播放次数、是否本地播放混音、以及是否将混音发送至远端，详见 [ByteRTCAudioMixingConfig](iOS-keytype.md#bytertcaudiomixingconfig) |


**注意**

+ 如果已经通过 [preloadAudioMixing:filePath:](#ByteRTCAudioMixingManager-preloadaudiomixing-filepath) 将文件加载至内存，确保此处的 ID
与预加载时设置的 ID 相同。  

+ 调用本方法播放音频文件后，关于当前的混音状态，会收到回调 `onAudioMixingStateChanged`。  
+ 开始播放音频文件后，可以调用 [stopAudioMixing:](#ByteRTCAudioMixingManager-stopaudiomixing) 方法停止播放音频文件。  
+ 本方法的混音数据来源于外部文件，而 [enableAudioMixingFrame:type:](#ByteRTCAudioMixingManager-enableaudiomixingframe-type)
的混音数据来源于外部缓存且音频格式为 PCM，这两种混音方式可以共存。


<span id="ByteRTCAudioMixingManager-stopaudiomixing"></span>
### stopAudioMixing:
```objectivec

- (void)stopAudioMixing:(int)mixId;
```
停止播放音频文件及混音

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mixId | **int** | 混音 ID |


**注意**

+ 调用 [startAudioMixing:filePath:config:](#ByteRTCAudioMixingManager-startaudiomixing-filepath-config)
方法开始播放音频文件及混音后，可以调用本方法停止播放音频文件及混音。  

+ 调用本方法停止播放音频文件后，SDK 会向本地回调通知已停止混音，见 `onAudioMixingStateChanged`。  
+ 调用本方法停止播放音频文件后，该音频文件会被自动卸载。


<span id="ByteRTCAudioMixingManager-pauseaudiomixing"></span>
### pauseAudioMixing:
```objectivec

- (void)pauseAudioMixing:(int)mixId;
```
暂停播放音频文件

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mixId | **int** | 混音 ID |


**注意**

+ 调用 [startAudioMixing:filePath:config:](#ByteRTCAudioMixingManager-startaudiomixing-filepath-config)
方法开始播放音频文件及混音后，可以通过调用该方法暂停播放音频文件。  

+ 调用本方法暂停播放音频文件后，可调用 [resumeAudioMixing:](#ByteRTCAudioMixingManager-resumeaudiomixing) 方法恢复播放及混音。  
+ 调用本方法暂停播放音频文件后，SDK 会向本地回调通知已暂停混音，见 `onAudioMixingStateChanged`。


<span id="ByteRTCAudioMixingManager-resumeaudiomixing"></span>
### resumeAudioMixing:
```objectivec

- (void)resumeAudioMixing:(int)mixId;
```
恢复播放音频文件

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mixId | **int** | 混音 ID |


**注意**

+ 调用 [pauseAudioMixing:](#ByteRTCAudioMixingManager-pauseaudiomixing) 方法暂停播放音频文件后，可以通过调用本方法恢复播放及混音。  
+ 调用本方法恢复播放音频文件后，SDK 会向本地回调通知音频文件正在播放中，见 `onAudioMixingStateChanged`。


<span id="ByteRTCAudioMixingManager-preloadaudiomixing-filepath"></span>
### preloadAudioMixing:filePath:
```objectivec

- (void)preloadAudioMixing:(int)mixId filePath:(NSString *_Nullable)filePath;
```
预加载指定音乐文件到内存中，以避免频繁播放同一文件时的重复加载，减少 CPU 占用。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mixId | **int** | 混音 ID。用于标识混音，请保证混音 ID 唯一性。  <br/>如果使用相同的 ID 重复调用本方法，后一次会覆盖前一次。  <br/>如果先调用 [startAudioMixing:filePath:config:](#ByteRTCAudioMixingManager-startaudiomixing-filepath-config)，再使用相同的 ID 调用本方法<br/>，会先回调 `onAudioMixingStateChanged` 通知上一个混音停止，然后加载后一个混音。   调用本方法预加载 A.mp3 后，如果需要使用相同的 ID 调用<br/>[startAudioMixing:filePath:config:](#ByteRTCAudioMixingManager-startaudiomixing-filepath-config) 播放 B.mp3，请先调用 [unloadAudioMixing:](#ByteRTCAudioMixingManager-unloadaudiomixing) 卸载 A.mp3。 |
| filePath | **NSString*** | 混音文件路径。<br/>支持本地文件的绝对路径。预加载的文件长度不得超过 20s。不同平台支持的音频文件格式: <table><tr><th></th><th>mp3</th><th>mp4</th><th>aac</th><th>m4a</th><th>3gp</th><th>wav</th><th>ogg</th><th>ts</th><th>wma</th></tr><br/><tr><td>Android</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td></tr><br/><tr><td>iOS</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td><td></td></tr><br/><tr><td>Windows</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td>Y</td><td>Y</td></tr></table> |


**注意**

+ 本方法只是预加载指定音频文件，只有调用 [startAudioMixing:filePath:config:](#ByteRTCAudioMixingManager-startaudiomixing-filepath-config)
方法才开始播放指定音频文件。 

+ 调用本方法预加载音频文件后，关于当前的混音状态，会收到回调 `onAudioMixingStateChanged`。  
+ 调用本方法预加载的指定音频文件可以通过 [unloadAudioMixing:](#ByteRTCAudioMixingManager-unloadaudiomixing) 卸载。


<span id="ByteRTCAudioMixingManager-unloadaudiomixing"></span>
### unloadAudioMixing:
```objectivec

- (void)unloadAudioMixing:(int)mixId;
```
卸载指定音频文件

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mixId | **int** | 混音 ID |


**注意**
不论音频文件是否播放，调用本方法卸载该文件后，SDK 会回调通知混音已停止，见 `onAudioMixingStateChanged`。

<span id="ByteRTCAudioMixingManager-setallaudiomixingvolume-type"></span>
### setAllAudioMixingVolume:type:
```objectivec
-(void)setAllAudioMixingVolume:(int)volume type:(ByteRTCAudioMixingType)type;
```
设置默认的混音音量大小，包括音频文件混音和 PCM 混音。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| volume | **int** | 混音音量相对原音量的比值。范围为 `[0, 400]`，建议范围是 `[0, 100]`。  <br/>• 0：静音  <br/>• 100：原始音量（默认值）  <br/>• 400: 最大可调音量 (自带溢出保护) |
| type | **ByteRTCAudioMixingType** | 混音类型。是否本地播放、以及是否发送到远端，详见 [ByteRTCAudioMixingType](iOS-keytype.md#bytertcaudiomixingtype)。 |


**注意**
该接口的优先级低于 [setAudioMixingVolume:volume:type:](#ByteRTCAudioMixingManager-setaudiomixingvolume-volume-type)，即通过 [setAudioMixingVolume:volume:type:](#ByteRTCAudioMixingManager-setaudiomixingvolume-volume-type) 单独设置了音量的混音 ID，不受该接口设置的影响。

<span id="ByteRTCAudioMixingManager-setaudiomixingvolume-volume-type"></span>
### setAudioMixingVolume:volume:type:
```objectivec

- (void)setAudioMixingVolume:(int)mixId volume:(int)volume type:(ByteRTCAudioMixingType)type;
```
调节指定混音的音量大小，包括音频文件混音和 PCM 混音。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mixId | **int** | 需调节音量的混音 ID |
| volume | **int** | 混音音量相对原音量的比值。范围为 `[0, 400]`，建议范围是 `[0, 100]`。  <br/>• 0：静音  <br/>• 100：原始音量（默认值）  <br/>• 400: 最大可调音量 (自带溢出保护) |
| type | **ByteRTCAudioMixingType** | 混音类型。是否本地播放、以及是否发送到远端，详见 [ByteRTCAudioMixingType](iOS-keytype.md#bytertcaudiomixingtype)。 |


**注意**
该方法仅对指定混音 ID 生效。iOS 端提供 [setAllAudioMixingVolume:type:](#ByteRTCAudioMixingManager-setallaudiomixingvolume-type) 接口调节全部混音文件播放音量。

<span id="ByteRTCAudioMixingManager-getaudiomixingduration"></span>
### getAudioMixingDuration:
```objectivec

- (int)getAudioMixingDuration:(int)mixId;
```
获取音频文件时长

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mixId | **int** | 混音 ID |

**返回值**

+ \>0: 成功, 音频文件时长，单位为毫秒。  
+ < 0: 失败


**注意**
调用本方法获取音频文件时长前，需要先调用 [preloadAudioMixing:filePath:](#ByteRTCAudioMixingManager-preloadaudiomixing-filepath) 或[startAudioMixing:filePath:config:](#ByteRTCAudioMixingManager-startaudiomixing-filepath-config)。


<span id="ByteRTCAudioMixingManager-getaudiomixingcurrentposition"></span>
### getAudioMixingCurrentPosition:
```objectivec

- (int)getAudioMixingCurrentPosition:(int)mixId;
```
获取音频文件播放进度

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mixId | **int** | 混音 ID |

**返回值**

+ \>0: 成功, 音频文件播放进度，单位为毫秒。  
+ < 0: 失败


**注意**
调用本方法获取音频文件播放进度前，需要先调用 [startAudioMixing:filePath:config:](#ByteRTCAudioMixingManager-startaudiomixing-filepath-config)开始播放音频文件。


<span id="ByteRTCAudioMixingManager-setaudiomixingposition-position"></span>
### setAudioMixingPosition:position:
```objectivec

- (void)setAudioMixingPosition:(int)mixId position:(int)position;
```
设置音频文件的起始播放位置

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mixId | **int** | 混音 ID |
| position | **int** | 音频文件起始播放位置，单位为毫秒。  <br/>你可以通过 [getAudioMixingDuration:](#ByteRTCAudioMixingManager-getaudiomixingduration) 获取音频文件总时长，position 的值不得大于音频文件总时长。 |


**注意**
在播放在线文件时，调用此接口可能造成播放延迟的现象。

<span id="ByteRTCAudioMixingManager-setaudiomixingdualmonomode-mode"></span>
### setAudioMixingDualMonoMode:mode:
```objectivec

- (void)setAudioMixingDualMonoMode:(int)mixId mode:(ByteRTCAudioMixingDualMonoMode)mode;
```
设置当前音频文件的声道模式

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mixId | **int** | 混音 ID |
| mode | **ByteRTCAudioMixingDualMonoMode** | 声道模式。默认的声道模式和源文件一致，详见 [ByteRTCAudioMixingDualMonoMode](iOS-keytype.md#bytertcaudiomixingdualmonomode)。 |


**注意**

+ 调用本方法设置音频文件的声道模式前，需要先调用 [startAudioMixing:filePath:config:](#ByteRTCAudioMixingManager-startaudiomixing-filepath-config) 开始播放音频文件。
+ 此方法对 [enableAudioMixingFrame:type:](#ByteRTCAudioMixingManager-enableaudiomixingframe-type) 播放的音乐无效。


<span id="ByteRTCAudioMixingManager-setaudiomixingpitch-pitch"></span>
### setAudioMixingPitch:pitch:
```objectivec

- (void)setAudioMixingPitch:(int)mixId pitch:(int)pitch;
```
开启本地播放音乐文件变调功能，多用于 K 歌场景。  <br>
使用该方法，你可以对本地播放音乐文件的音调进行升调或降调等调整。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mixId | **int** | 混音 ID |
| pitch | **int** | 相对于音乐文件原始音调的升高/降低值，取值范围[-12，12]，默认值为 0，即不做调整。  <br/>取值范围内每相邻两个值的音高距离相差半音，正值表示升调，负值表示降调，设置的绝对值越大表示音调升高或降低越多。  <br/>超出取值范围则设置失败，并且会触发 `onAudioMixingStateChanged` 回调，提示 [ByteRTCAudioMixingState](iOS-keytype.md#bytertcaudiomixingstate) 状态为<br/>`AUDIO_MIXING_STATE_FAILED` 混音播放失败，[ByteRTCAudioMixingError](iOS-keytype.md#bytertcaudiomixingerror) 错误码为 `AUDIO_MIXING_ERROR_ID_TYPE_INVALID_PITCH`<br/>设置混音文件音调不合法。 |


**注意**
本方法需要在调用 [startAudioMixing:filePath:config:](#ByteRTCAudioMixingManager-startaudiomixing-filepath-config) 开始播放音频文件后、调用[stopAudioMixing:](#ByteRTCAudioMixingManager-stopaudiomixing) 停止播放音频文件前使用，否则会触发 `onAudioMixingStateChanged` 回调报错


<span id="ByteRTCAudioMixingManager-setaudiomixingplaybackspeed-speed"></span>
### setAudioMixingPlaybackSpeed:speed:
```objectivec
-(int)setAudioMixingPlaybackSpeed:(int)mixId speed:(int)speed;
```
设置混音时音频文件的播放速度

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mixId | **int** | 混音 ID |
| speed | **int** | 播放速度与原始文件速度的比例，单位：%，取值范围为 [50,200]，默认值为 100。  <br/>超出取值范围则设置失败，你会收到 `onAudioMixingStateChanged` 回调，提示 [ByteRTCAudioMixingState](iOS-keytype.md#bytertcaudiomixingstate) 状态为<br/>`ByteRTCAudioMixingStateFailed` 混音播放失败，[ByteRTCAudioMixingError](iOS-keytype.md#bytertcaudiomixingerror) 错误码为 `ByteRTCAudioMixingErrorInValidPlaybackSpeed`<br/>设置混音文件的播放速度不合法。 |


**注意**

+ 暂不支持对 PCM 音频数据进行变速调整。  
+ 你需要在调用 [startAudioMixing:filePath:config:](#ByteRTCAudioMixingManager-startaudiomixing-filepath-config)
开始混音，并且收到`onAudioMixingStateChanged` 回调提示 [ByteRTCAudioMixingState](iOS-keytype.md#bytertcaudiomixingstate) 状态为
`ByteRTCAudioMixingStatePlaying`，[ByteRTCAudioMixingError](iOS-keytype.md#bytertcaudiomixingerror) 错误码为 `AUDIO_MIXING_ERROR_OK` 之后调用该方法。  

+ 在 [stopAudioMixing:](#ByteRTCAudioMixingManager-stopaudiomixing) 停止混音或 [unloadAudioMixing:](#ByteRTCAudioMixingManager-unloadaudiomixing) 卸载音频文件后调用该 API，会收到状态为 `ByteRTCAudioMixingStateFailed` 错误码为
`ByteRTCAudioMixingErrorIdNotFound` 的 `onAudioMixingStateChanged` 回调。


<span id="ByteRTCAudioMixingManager-setaudiomixingloudness-loudness"></span>
### setAudioMixingLoudness:loudness:
```objectivec

- (void)setAudioMixingLoudness:(int)mixId loudness:(float)loudness;
```
如果你需要使用 `enableVocalInstrumentBalance:` 对混音音频文件/PCM 音频数据进行音量调整，你必须通过此接口传入其原始响度。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mixId | **int** | 混音 ID |
| loudness | **float** | 原始响度，单位：lufs，取值范围为 [-70.0, 0.0]。  <br/>当设置的值小于 -70.0lufs 时，则默认调整为 -70.0lufs，大于 0.0lufs 时，则不对该响度做音均衡处理。默认值为 1.0lufs，即不做处理。 |


**注意**
建议在 [startAudioMixing:filePath:config:](#ByteRTCAudioMixingManager-startaudiomixing-filepath-config)开始播放音频文件之前调用该接口，以免播放过程中的音量突变导致听感体验下降。


<span id="ByteRTCAudioMixingManager-setaudiomixingprogressinterval-interval"></span>
### setAudioMixingProgressInterval:interval:
```objectivec

- (void)setAudioMixingProgressInterval:(int)mixId interval:(int64_t)interval;
```
设置混音时音频文件播放进度回调的间隔

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mixId | **int** | 混音 ID  <br/>可以通过多次调用本接口传入不同的 ID 对多个 ID 进行间隔设置。 |
| interval | **int64_t** | 音频文件播放进度回调的时间间隔，单位毫秒。  <br/>• interval 的值为大于 0 的 10 的倍数，当设置的值不能被 10 整除时，则默认向上取整 10，如设为 52ms 时会默认调整为 60ms。设置完成后 SDK<br/>将会按照设置的时间间隔触发 `onAudioMixingPlayingProgress` 回调。  <br/>• interval 的值小于等于 0 时，不会触发进度回调。 |


**注意**
本方法需要在调用 [startAudioMixing:filePath:config:](#ByteRTCAudioMixingManager-startaudiomixing-filepath-config) 开始播放音频文件后、调用[stopAudioMixing:](#ByteRTCAudioMixingManager-stopaudiomixing) 停止播放音频文件前使用，否则会触发 `onAudioMixingStateChanged` 回调报错。  
若想在音乐文件开始播放前设置播放进度回调间隔，你需调用 [startAudioMixing:filePath:config:](#ByteRTCAudioMixingManager-startaudiomixing-filepath-config) 在 [ByteRTCAudioMixingConfig](iOS-keytype.md#bytertcaudiomixingconfig)
中设置时间间隔，开始播放后可以通过此接口更新回调间隔。


<span id="ByteRTCAudioMixingManager-enableaudiomixingframe-type"></span>
### enableAudioMixingFrame:type:
```objectivec
-(void)enableAudioMixingFrame:(int)mixId type:(ByteRTCAudioMixingType)type;
```
启动 PCM 音频数据混音。<br>
要实现多个 PCM 音频数据混音，多次调用本方法，并传入不同的 id。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mixId | **int** | 混音 ID。用于标识混音，保证混音 ID 唯一性。  <br/>如果使用相同的 ID 重复调用本方法后，前一次混音会停止，后一次混音开始，会收到 `onAudioMixingStateChanged` 通知前一次混音已停止。 |
| type | **ByteRTCAudioMixingType** | 混音类型。是否本地播放、以及是否发送到远端，详见 [ByteRTCAudioMixingType](iOS-keytype.md#bytertcaudiomixingtype)。 |


**注意**

+ 必须先调用本方法启动 PCM 音频数据混音，随后调用 [pushAudioMixingFrame:audioFrame:](#ByteRTCAudioMixingManager-pushaudiomixingframe-audioframe) 方法，才会开始混音。 
+ 如要结束 PCM 音频数据混音，使用 [disableAudioMixingFrame:](#ByteRTCAudioMixingManager-disableaudiomixingframe)。


<span id="ByteRTCAudioMixingManager-disableaudiomixingframe"></span>
### disableAudioMixingFrame:
```objectivec

- (void)disableAudioMixingFrame:(int)mixId;
```
关闭 PCM 混音

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mixId | **int** | 混音 ID。 |


<span id="ByteRTCAudioMixingManager-pushaudiomixingframe-audioframe"></span>
### pushAudioMixingFrame:audioFrame:
```objectivec
-(int)pushAudioMixingFrame:(int)mixId audioFrame:(ByteRTCAudioFrame* _Nullable)audioFrame;
```
推送 PCM 音频帧数据用于混音

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mixId | **int** | 混音 ID。 |
| audioFrame | **ByteRTCAudioFrame*** | 音频帧，详见 [ByteRTCAudioFrame](iOS-keytype.md#bytertcaudioframe)。 |

**返回值**

+ 0: 成功  
+ < 0: 失败


**注意**

+ 调用该方法前，须通过 [enableAudioMixingFrame:type:](#ByteRTCAudioMixingManager-enableaudiomixingframe-type) 启动外部音频流混音。  
+ 使用参考建议：首次推送数据，请在应用侧先缓存一定数据（如 200 毫秒），然后一次性推送过去；此后的推送操作定时 10 毫秒一次，并且每次的音频数据量为 10
毫秒数据量。要暂停播放，暂停推送即可。


<span id="ByteRTCAudioMixingManager-getaudiotrackcount"></span>
### getAudioTrackCount:
```objectivec

- (int)getAudioTrackCount:(int)mixId;
```
获取当前音频文件的音轨索引。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mixId | **int** | 混音 ID |

**返回值**
方法调用结果 

+ ≥ 0：成功，返回当前音频文件的音轨索引。  
+ < 0：方法调用失败。


**注意**

+ 调用本方法获取音频文件的音轨前，需要先调用 [startAudioMixing:filePath:config:](#ByteRTCAudioMixingManager-startaudiomixing-filepath-config)
开始播放音频文件。

+ 此方法对 [enableAudioMixingFrame:type:](#ByteRTCAudioMixingManager-enableaudiomixingframe-type) 播放的音频无效。


<span id="ByteRTCAudioMixingManager-selectaudiotrack-audiotrackindex"></span>
### selectAudioTrack:audioTrackIndex:
```objectivec

- (void)selectAudioTrack:(int)mixId audioTrackIndex:(int)audioTrackIndex;
```
指定当前音频文件的播放音轨。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mixId | **int** | 混音 ID |
| audioTrackIndex | **int** | 指定的播放音轨。  <br/>设置的参数值需要小于或等于 [getAudioTrackCount:](#ByteRTCAudioMixingManager-getaudiotrackcount) 的返回值 |


**注意**

+ 调用本方法设置音频文件的音轨前，需要先调用 [startAudioMixing:filePath:config:](#ByteRTCAudioMixingManager-startaudiomixing-filepath-config)
开始播放音频文件。

+ 此方法对 [enableAudioMixingFrame:type:](#ByteRTCAudioMixingManager-enableaudiomixingframe-type) 播放的音乐无效。


<span id="ByteRTCAudioMixingManager-getaudiomixingplaybackduration"></span>
### getAudioMixingPlaybackDuration:
```objectivec
-(int)getAudioMixingPlaybackDuration:(int)mixId;
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
+ 调用本接口前，需要先调用 [startAudioMixing:filePath:config:](#ByteRTCAudioMixingManager-startaudiomixing-filepath-config) 开始播放指定音频文件。


# ByteRTCKTVManager
```objectivec
@interface ByteRTCKTVManager : NSObject
```

KTV 管理接口。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **void** | [getMusicList:pageSize:filterType:](#ByteRTCKTVManager-getmusiclist-pagesize-filtertype) |
| **void** | [searchMusic:pageNumber:pageSize:filterType:](#ByteRTCKTVManager-searchmusic-pagenumber-pagesize-filtertype) |
| **void** | [getHotMusic:filterType:](#ByteRTCKTVManager-gethotmusic-filtertype) |
| **void** | [getMusicDetail:](#ByteRTCKTVManager-getmusicdetail) |
| **int** | [downloadMusic:](#ByteRTCKTVManager-downloadmusic) |
| **int** | [downloadLyric:lyricType:](#ByteRTCKTVManager-downloadlyric-lyrictype) |
| **int** | [downloadMidi:](#ByteRTCKTVManager-downloadmidi) |
| **void** | [cancelDownload:](#ByteRTCKTVManager-canceldownload) |
| **void** | [clearCache](#ByteRTCKTVManager-clearcache) |
| **void** | [setMaxCacheSize:](#ByteRTCKTVManager-setmaxcachesize) |
| **ByteRTCKTVPlayer*** | [getKTVPlayer](#ByteRTCKTVManager-getktvplayer) |


## 函数说明
<span id="ByteRTCKTVManager-getmusiclist-pagesize-filtertype"></span>
### getMusicList:pageSize:filterType:
```objectivec

- (void)getMusicList:(int)pageNumber pageSize:(int)pageSize filterType:(ByteRTCKTVMusicFilterType)filterType;
```
获取歌曲列表。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| pageNumber | **int** | 页码，默认从 1 开始。 |
| pageSize | **int** | 每页显示歌曲的最大数量，取值范围 [1,99]。 |
| filterType | **ByteRTCKTVMusicFilterType** | 歌曲过滤方式，参看 [ByteRTCKTVMusicFilterType](iOS-keytype.md#bytertcktvmusicfiltertype)。多个过滤方式可以按位或组合。 |


**注意**
调用接口后，你会收到 [ktvManager:onMusicListResult:totalSize:musics:](iOS-callback.md#ByteRTCKTVManagerDelegate-ktvmanager-onmusiclistresult-totalsize-musics) 回调歌曲列表。

<span id="ByteRTCKTVManager-searchmusic-pagenumber-pagesize-filtertype"></span>
### searchMusic:pageNumber:pageSize:filterType:
```objectivec

- (void)searchMusic:(NSString * _Nonnull)keyWord pageNumber:(int)pageNumber pageSize:(int)pageSize filterType:(ByteRTCKTVMusicFilterType)filterType;
```
根据关键词搜索歌曲。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| keyWord | **NSString*** | 关键词，字符串长度最大为 20 个字符。 |
| pageNumber | **int** | 页码，默认从 1 开始。 |
| pageSize | **int** | 每页显示歌曲的最大数量，取值范围 [1,99]。 |
| filterType | **ByteRTCKTVMusicFilterType** | 歌曲过滤方式，参看 [ByteRTCKTVMusicFilterType](iOS-keytype.md#bytertcktvmusicfiltertype)。多个过滤方式可以按位或组合。 |


**注意**
调用接口后，你会收到 [ktvManager:onSearchMusicResult:totalSize:musics:](iOS-callback.md#ByteRTCKTVManagerDelegate-ktvmanager-onsearchmusicresult-totalsize-musics) 回调歌曲列表。

<span id="ByteRTCKTVManager-gethotmusic-filtertype"></span>
### getHotMusic:filterType:
```objectivec

- (void)getHotMusic:(ByteRTCKTVMusicHotType)hotType filterType:(ByteRTCKTVMusicFilterType)filterType;
```
根据热榜获取每个榜单的歌曲列表。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| hotType | **ByteRTCKTVMusicHotType** | 热榜类别，参看 [ByteRTCKTVMusicHotType](iOS-keytype.md#bytertcktvmusichottype)。多个热榜类别可以按位或组合。 |
| filterType | **ByteRTCKTVMusicFilterType** | 歌曲过滤方式，参看 [ByteRTCKTVMusicFilterType](iOS-keytype.md#bytertcktvmusicfiltertype)。多个过滤方式可以按位或组合。 |


**注意**
调用接口后，你会收到 [ktvManager:onHotMusicResult:hotMusicInfos:](iOS-callback.md#ByteRTCKTVManagerDelegate-ktvmanager-onhotmusicresult-hotmusicinfos) 回调歌曲列表。

<span id="ByteRTCKTVManager-getmusicdetail"></span>
### getMusicDetail:
```objectivec

- (void)getMusicDetail:(NSString * _Nonnull)musicId;
```
获取音乐详细信息。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| musicId | **NSString*** | 音乐 ID。 |


**注意**
调用接口后，你会收到 [ktvManager:onMusicDetailResult:music:](iOS-callback.md#ByteRTCKTVManagerDelegate-ktvmanager-onmusicdetailresult-music) 回调。

<span id="ByteRTCKTVManager-downloadmusic"></span>
### downloadMusic:
```objectivec

- (int)downloadMusic:(NSString * _Nonnull)musicId;
```
下载音乐。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| musicId | **NSString*** | 音乐 ID。 |

**返回值**
下载任务 ID。


**注意**

+ 若音乐下载成功，你会收到 [ktvManager:onDownloadSuccess:downloadResult:](iOS-callback.md#ByteRTCKTVManagerDelegate-ktvmanager-ondownloadsuccess-downloadresult) 回调。
+ 若音乐下载失败，你会收到 [ktvManager:onDownloadFail:errorCode:](iOS-callback.md#ByteRTCKTVManagerDelegate-ktvmanager-ondownloadfail-errorcode) 回调。
+ 音乐下载进度更新时，你会收到 [ktvManager:onDownloadMusicProgress:progress:](iOS-callback.md#ByteRTCKTVManagerDelegate-ktvmanager-ondownloadmusicprogress-progress) 回调。


<span id="ByteRTCKTVManager-downloadlyric-lyrictype"></span>
### downloadLyric:lyricType:
```objectivec

- (int)downloadLyric:(NSString * _Nonnull)musicId lyricType:(ByteRTCKTVDownloadLyricType)lyricType;
```
下载歌词。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| musicId | **NSString*** | 音乐 ID。 |
| lyricType | **ByteRTCKTVDownloadLyricType** | 歌词文件类型，参看 [ByteRTCKTVDownloadLyricType](iOS-keytype.md#bytertcktvdownloadlyrictype)。 |

**返回值**
下载任务 ID。


**注意**

+ 若歌词下载成功，你会收到 [ktvManager:onDownloadSuccess:downloadResult:](iOS-callback.md#ByteRTCKTVManagerDelegate-ktvmanager-ondownloadsuccess-downloadresult) 回调。
+ 若歌词下载失败，你会收到 [ktvManager:onDownloadFail:errorCode:](iOS-callback.md#ByteRTCKTVManagerDelegate-ktvmanager-ondownloadfail-errorcode) 回调。


<span id="ByteRTCKTVManager-downloadmidi"></span>
### downloadMidi:
```objectivec

- (int)downloadMidi:(NSString * _Nonnull)musicId;
```
下载 MIDI 文件。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| musicId | **NSString*** | 音乐 ID。 |

**返回值**
下载任务 ID。


**注意**

+ 若文件下载成功，你会收到 [ktvManager:onDownloadSuccess:downloadResult:](iOS-callback.md#ByteRTCKTVManagerDelegate-ktvmanager-ondownloadsuccess-downloadresult) 回调。
+ 若文件下载失败，你会收到 [ktvManager:onDownloadFail:errorCode:](iOS-callback.md#ByteRTCKTVManagerDelegate-ktvmanager-ondownloadfail-errorcode) 回调。


<span id="ByteRTCKTVManager-canceldownload"></span>
### cancelDownload:
```objectivec

- (void)cancelDownload:(int)downloadId;
```
取消下载任务。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| downloadId | **int** | 下载任务 ID。 |


<span id="ByteRTCKTVManager-clearcache"></span>
### clearCache
```objectivec

- (void)clearCache;
```
清除当前音乐缓存文件，包括音乐音频和歌词。


<span id="ByteRTCKTVManager-setmaxcachesize"></span>
### setMaxCacheSize:
```objectivec

- (void)setMaxCacheSize:(int)maxCacheSizeMB;
```
设置歌曲文件最大占用的本地缓存。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| maxCacheSizeMB | **int** | 本地缓存，单位 MB。<br/>设置值小于等于 0 时，使用默认值 1024 MB。 |


<span id="ByteRTCKTVManager-getktvplayer"></span>
### getKTVPlayer
```objectivec

- (ByteRTCKTVPlayer * _Nullable)getKTVPlayer;
```
获取 KTV 播放器。

**返回值**
KTV 播放器接口，参看 [ByteRTCKTVPlayer](#bytertcktvplayer)。


# ByteRTCKTVPlayer
```objectivec
@interface ByteRTCKTVPlayer : NSObject
```

KTV 播放器接口。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **void** | [playMusic:audioTrackType:audioPlayType:](#ByteRTCKTVPlayer-playmusic-audiotracktype-audioplaytype) |
| **void** | [pauseMusic:](#ByteRTCKTVPlayer-pausemusic) |
| **void** | [resumeMusic:](#ByteRTCKTVPlayer-resumemusic) |
| **void** | [stopMusic:](#ByteRTCKTVPlayer-stopmusic) |
| **void** | [seekMusic:position:](#ByteRTCKTVPlayer-seekmusic-position) |
| **void** | [setMusicVolume:volume:](#ByteRTCKTVPlayer-setmusicvolume-volume) |
| **void** | [switchAudioTrackType:](#ByteRTCKTVPlayer-switchaudiotracktype) |
| **void** | [setMusicPitch:pitch:](#ByteRTCKTVPlayer-setmusicpitch-pitch) |


## 函数说明
<span id="ByteRTCKTVPlayer-playmusic-audiotracktype-audioplaytype"></span>
### playMusic:audioTrackType:audioPlayType:
```objectivec

- (void)playMusic:(NSString * _Nonnull)musicId audioTrackType:(ByteRTCKTVAudioTrackType)trackType audioPlayType:(ByteRTCKTVAudioPlayType)playType;
```
播放歌曲。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| musicId | **NSString*** | 音乐 ID。<br/>若同一 musicId 的歌曲正在播放，再次调用接口会从开始位置重新播放。若 musicId 对应的音频文件不存在会触发报错。 |
| trackType | **ByteRTCKTVAudioTrackType** | 原唱伴唱类型，参看 [ByteRTCKTVAudioTrackType](iOS-keytype.md#bytertcktvaudiotracktype)。 |
| playType | **ByteRTCKTVAudioPlayType** | 音乐播放类型。参看 [ByteRTCKTVAudioPlayType](iOS-keytype.md#bytertcktvaudioplaytype)。 |


**注意**

+ 调用接口后，你会收到 [ktvPlayer:onPlayStateChange:state:error:](iOS-callback.md#ByteRTCKTVPlayerDelegate-ktvplayer-onplaystatechange-state-error) 回调歌曲播放状态。
+ 若音乐 ID 错误，会触发 [ktvPlayer:onPlayStateChange:state:error:](iOS-callback.md#ByteRTCKTVPlayerDelegate-ktvplayer-onplaystatechange-state-error) 回调，errorCode 为 –3023，playState 为 4。
+ 若未进房，会触发 [ktvPlayer:onPlayStateChange:state:error:](iOS-callback.md#ByteRTCKTVPlayerDelegate-ktvplayer-onplaystatechange-state-error) 回调，errorCode 为 –3022，playState 为 4。
+ 若音乐文件不存在，会触发 [ktvPlayer:onPlayStateChange:state:error:](iOS-callback.md#ByteRTCKTVPlayerDelegate-ktvplayer-onplaystatechange-state-error) 回调，errorCode 为 –3020，playState 为 4。


<span id="ByteRTCKTVPlayer-pausemusic"></span>
### pauseMusic:
```objectivec

- (void)pauseMusic:(NSString * _Nonnull)musicId;
```
暂停播放歌曲。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| musicId | **NSString*** | 音乐 ID。 |


**注意**

+ 调用接口后，你会收到 [ktvPlayer:onPlayStateChange:state:error:](iOS-callback.md#ByteRTCKTVPlayerDelegate-ktvplayer-onplaystatechange-state-error) 回调歌曲播放状态。
+ 若音乐 ID 错误，会触发 [ktvPlayer:onPlayStateChange:state:error:](iOS-callback.md#ByteRTCKTVPlayerDelegate-ktvplayer-onplaystatechange-state-error) 回调，errorCode 为 –3023，playState 为 4。
+ 若未进房，会触发 [ktvPlayer:onPlayStateChange:state:error:](iOS-callback.md#ByteRTCKTVPlayerDelegate-ktvplayer-onplaystatechange-state-error) 回调，errorCode 为 –3022，playState 为 4。


<span id="ByteRTCKTVPlayer-resumemusic"></span>
### resumeMusic:
```objectivec

- (void)resumeMusic:(NSString * _Nonnull)musicId;
```
继续播放歌曲。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| musicId | **NSString*** | 音乐 ID。 |


**注意**

+ 调用接口后，你会收到 [ktvPlayer:onPlayStateChange:state:error:](iOS-callback.md#ByteRTCKTVPlayerDelegate-ktvplayer-onplaystatechange-state-error) 回调歌曲播放状态。
+ 若音乐 ID 错误，会触发 [ktvPlayer:onPlayStateChange:state:error:](iOS-callback.md#ByteRTCKTVPlayerDelegate-ktvplayer-onplaystatechange-state-error) 回调，errorCode 为 –3023，playState 为 4。
+ 若未进房，会触发 [ktvPlayer:onPlayStateChange:state:error:](iOS-callback.md#ByteRTCKTVPlayerDelegate-ktvplayer-onplaystatechange-state-error) 回调，errorCode 为 –3022，playState 为 4。


<span id="ByteRTCKTVPlayer-stopmusic"></span>
### stopMusic:
```objectivec

- (void)stopMusic:(NSString * _Nonnull)musicId;
```
停止播放歌曲。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| musicId | **NSString*** | 音乐 ID。 |


**注意**

+ 调用接口后，你会收到 [ktvPlayer:onPlayStateChange:state:error:](iOS-callback.md#ByteRTCKTVPlayerDelegate-ktvplayer-onplaystatechange-state-error) 回调歌曲播放状态。
+ 若音乐 ID 错误，会触发 [ktvPlayer:onPlayStateChange:state:error:](iOS-callback.md#ByteRTCKTVPlayerDelegate-ktvplayer-onplaystatechange-state-error) 回调，errorCode 为 –3023，playState 为 4。
+ 若未进房，会触发 [ktvPlayer:onPlayStateChange:state:error:](iOS-callback.md#ByteRTCKTVPlayerDelegate-ktvplayer-onplaystatechange-state-error) 回调，errorCode 为 –3022，playState 为 4。


<span id="ByteRTCKTVPlayer-seekmusic-position"></span>
### seekMusic:position:
```objectivec

- (void)seekMusic:(NSString * _Nonnull)musicId position:(int)position;
```
设置音乐文件的起始播放位置。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| musicId | **NSString*** | 音乐 ID。 |
| position | **int** | 音乐起始位置，单位为毫秒，取值小于音乐文件总时长。 |


**注意**

+ 调用本接口时音乐必须处于播放中状态。
+ 调用接口后，你会收到 [ktvPlayer:onPlayStateChange:state:error:](iOS-callback.md#ByteRTCKTVPlayerDelegate-ktvplayer-onplaystatechange-state-error) 回调歌曲播放状态。
+ 若音乐 ID 错误，会触发 [ktvPlayer:onPlayStateChange:state:error:](iOS-callback.md#ByteRTCKTVPlayerDelegate-ktvplayer-onplaystatechange-state-error) 回调，errorCode 为 –3023，playState 为 4。
+ 若未进房，会触发 [ktvPlayer:onPlayStateChange:state:error:](iOS-callback.md#ByteRTCKTVPlayerDelegate-ktvplayer-onplaystatechange-state-error) 回调，errorCode 为 –3022，playState 为 4。


<span id="ByteRTCKTVPlayer-setmusicvolume-volume"></span>
### setMusicVolume:volume:
```objectivec

- (void)setMusicVolume:(NSString * _Nonnull)musicId volume:(int)volume;
```
设置歌曲播放音量，只能在开始播放后进行设置。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| musicId | **NSString*** | 音乐 ID。 |
| volume | **int** | 歌曲播放音量，调节范围：[0,400]。<br/>• 0：静音。<br/>• 100：原始音量。<br/>• 400: 原始音量的 4 倍(自带溢出保护)。 |


**注意**

+ 调用本接口时音乐必须处于播放中状态。
+ 若设置的音量大于 400，则按最大值 400 进行调整；若设置的音量小于 0，则按最小值 0 进行调整。
+ 若音乐 ID 错误，会触发 [ktvPlayer:onPlayStateChange:state:error:](iOS-callback.md#ByteRTCKTVPlayerDelegate-ktvplayer-onplaystatechange-state-error) 回调，errorCode 为 –3023，playState 为 4。
+ 若未进房，会触发 [ktvPlayer:onPlayStateChange:state:error:](iOS-callback.md#ByteRTCKTVPlayerDelegate-ktvplayer-onplaystatechange-state-error) 回调，errorCode 为 –3022，playState 为 4。


<span id="ByteRTCKTVPlayer-switchaudiotracktype"></span>
### switchAudioTrackType:
```objectivec

- (void)switchAudioTrackType:(NSString * _Nonnull)musicId;
```
切换歌曲原唱伴唱。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| musicId | **NSString*** | 音乐 ID。 |


**注意**
调用本接口时音乐必须处于播放中状态。

<span id="ByteRTCKTVPlayer-setmusicpitch-pitch"></span>
### setMusicPitch:pitch:
```objectivec

- (void)setMusicPitch:(NSString * _Nonnull)musicId pitch:(int)pitch;
```
对播放中的音乐设置升降调信息。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| musicId | **NSString*** | 音乐 ID。 |
| pitch | **int** | 相对于音乐文件原始音调的升高/降低值，取值范围 [-12，12]，默认值为 0，即不做调整。<br/>取值范围内每相邻两个值的音高距离相差半音，正值表示升调，负值表示降调，设置的绝对值越大表示音调升高或降低越多。 |


**注意**

+ 调用本接口时音乐必须处于播放中状态。
+ 若设置的 pitch 大于 12，则按最大值 12 进行调整；若设置的 pitch 小于 –12，，则按最小值 –12 进行调整。
+ 若音乐 ID 错误，会触发 [ktvPlayer:onPlayStateChange:state:error:](iOS-callback.md#ByteRTCKTVPlayerDelegate-ktvplayer-onplaystatechange-state-error) 回调，errorCode 为 –3023，playState 为 4。
+ 若未进房，会触发 [ktvPlayer:onPlayStateChange:state:error:](iOS-callback.md#ByteRTCKTVPlayerDelegate-ktvplayer-onplaystatechange-state-error) 回调，errorCode 为 –3022，playState 为 4。


# ByteRTCRangeAudio
```objectivec
@interface ByteRTCRangeAudio :NSObject
```

范围语音接口实例


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **void** | [enableRangeAudio:](#ByteRTCRangeAudio-enablerangeaudio) |
| **int** | [updateReceiveRange:](#ByteRTCRangeAudio-updatereceiverange) |
| **int** | [updatePosition:](#ByteRTCRangeAudio-updateposition) |
| **void** | [registerRangeAudioObserver:](#ByteRTCRangeAudio-registerrangeaudioobserver) |
| **int** | [setAttenuationModel:coefficient:](#ByteRTCRangeAudio-setattenuationmodel-coefficient) |


## 函数说明
<span id="ByteRTCRangeAudio-enablerangeaudio"></span>
### enableRangeAudio:
```objectivec

- (void)enableRangeAudio:(BOOL)enable;
```
开启/关闭范围语音功能。  <br>
范围语音是指，在同一 RTC 房间中设定的音频接收距离范围内，本地用户收听到的远端用户音频音量会随着远端用户的靠近/远离而放大/衰减；若远端用户在房间内的位置超出设定范围，则本地用户无法接收其音频。音频接收范围设置参看 [updateReceiveRange:](#ByteRTCRangeAudio-updatereceiverange)。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| enable | **BOOL** | 是否开启范围语音功能：  <br/>• true: 开启  <br/>• false: 关闭（默认） |


**注意**
该方法进房前后都可调用，为保证进房后范围语音效果的平滑切换，你需在该方法前先调用 [updatePosition:](#ByteRTCRangeAudio-updateposition) 设置自身位置坐标，然后开启该方法收听范围语音效果。

<span id="ByteRTCRangeAudio-updatereceiverange"></span>
### updateReceiveRange:
```objectivec

- (int)updateReceiveRange:(ReceiveRange* _Nonnull) range;
```
更新本地用户的音频收听范围。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| range | **ReceiveRange*** | 音频收听范围，参看 [ReceiveRange](iOS-keytype.md#receiverange)。 |

**返回值**
方法调用结果：  

+ 0：成功；  
+ !0: 失败。


**注意**
若此前你已调用 [registerRangeAudioObserver:](#ByteRTCRangeAudio-registerrangeaudioobserver) 注册了范围语音衰减系数监测器，房间内有任何用户调用该接口更新音频收听范围后，你都会收到 [onRangeAudioInfo:](iOS-callback.md#ByteRTCRangeAudioObserver-onrangeaudioinfo) 回调。

<span id="ByteRTCRangeAudio-updateposition"></span>
### updatePosition:
```objectivec

- (int)updatePosition:(Position* _Nonnull) pos;
```
更新本地用户在房间内空间直角坐标系中的位置坐标。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| pos | **Position*** | 三维坐标的值，默认为 [0, 0, 0]，参看 [Position](iOS-keytype.md#position-2)。 |

**返回值**
方法调用结果： 

+ 0：成功；  
+ !0：失败。


**注意**

+ 调用该接口更新坐标后，你需调用 [enableRangeAudio:](#ByteRTCRangeAudio-enablerangeaudio) 开启范围语音功能以收听范围语音效果。 
+ 若此前你已调用 [registerRangeAudioObserver:](#ByteRTCRangeAudio-registerrangeaudioobserver) 注册了范围语音衰减系数监测器，房间内有任何用户调用该接口更新自身位置坐标后，你都会收到 [onRangeAudioInfo:](iOS-callback.md#ByteRTCRangeAudioObserver-onrangeaudioinfo) 回调。


<span id="ByteRTCRangeAudio-registerrangeaudioobserver"></span>
### registerRangeAudioObserver:
```objectivec

- (void)registerRangeAudioObserver:(_Nullable id<ByteRTCRangeAudioObserver>) observer;
```
设置范围语音衰减系数监测器。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| observer | **id<ByteRTCRangeAudioObserver>** | 范围语音衰减系数监测器。  <br/>设置后，SDK 会在监测到房间内有用户更新自身位置坐标或音频收听范围后，触发 [onRangeAudioInfo:](iOS-callback.md#ByteRTCRangeAudioObserver-onrangeaudioinfo) 回调。具体参看 [ByteRTCRangeAudioObserver](iOS-callback.md#bytertcrangeaudioobserver)。 |


**注意**
该方法仅适用于手动订阅模式，自动订阅无需设置。

<span id="ByteRTCRangeAudio-setattenuationmodel-coefficient"></span>
### setAttenuationModel:coefficient:
```objectivec

- (int)setAttenuationModel:(AttenuationType) type coefficient:(float)coefficient;
```
设置范围语音的音量衰减模式。<br>
衰减模式更改后，[onRangeAudioInfo:](iOS-callback.md#ByteRTCRangeAudioObserver-onrangeaudioinfo) 回调将根据最后设置的衰减模式进行计算并返回音量衰减数值

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| type | **AttenuationType** | 音量衰减模式。默认为线性衰减。详见 [AttenuationType](iOS-keytype.md#attenuationtype)。 |
| coefficient | **float** | 指数衰减模式下的音量衰减系数，默认值为 1。范围 [0.1,100]，推荐设置为 `50`。数值越大，音量的衰减速度越快。 |

**返回值**
调用是否成功

+ `0`:调用成功
+ `-1`:调用失败。原因为在调用 [enableRangeAudio:](#ByteRTCRangeAudio-enablerangeaudio) 开启范围语音前或进房前调用本接口


**注意**
音量衰减范围通过 [updateReceiveRange:](#ByteRTCRangeAudio-updatereceiverange) 进行设置。

# ByteRTCSingScoringManager
```objectivec
@interface ByteRTCSingScoringManager :NSObject
```

K 歌评分管理接口。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **int** | [initSingScoring:singScoringToken:delegate:](#ByteRTCSingScoringManager-initsingscoring-singscoringtoken-delegate) |
| **int** | [setSingScoringConfig:](#ByteRTCSingScoringManager-setsingscoringconfig) |
| **NSArray<ByteRTCStandardPitchInfo* >*** | [getStandardPitchInfo:](#ByteRTCSingScoringManager-getstandardpitchinfo) |
| **int** | [startSingScoring:scoringInfoInterval:](#ByteRTCSingScoringManager-startsingscoring-scoringinfointerval) |
| **int** | [stopSingScoring](#ByteRTCSingScoringManager-stopsingscoring) |
| **int** | [getLastSentenceScore](#ByteRTCSingScoringManager-getlastsentencescore) |
| **int** | [getTotalScore](#ByteRTCSingScoringManager-gettotalscore) |
| **int** | [getAverageScore](#ByteRTCSingScoringManager-getaveragescore) |


## 函数说明
<span id="ByteRTCSingScoringManager-initsingscoring-singscoringtoken-delegate"></span>
### initSingScoring:singScoringToken:delegate:
```objectivec
-(int)initSingScoring:(NSString * _Nullable)singScoringAppkey singScoringToken:(NSString * _Nullable)singScoringToken delegate:(id<ByteRTCSingScoringDelegate> _Nullable)delegate;
```
初始化 K 歌评分。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| singScoringAppkey | **NSString*** | K 歌评分密钥，用于鉴权验证 K 歌功能是否开通。 |
| singScoringToken | **NSString*** | K 歌评分密钥，用于鉴权验证 K 歌功能是否开通。 |
| delegate | **id<ByteRTCSingScoringDelegate>** | K 歌评分事件回调类，详见 [ByteRTCSingScoringDelegate](iOS-callback.md#bytertcsingscoringdelegate)。 |

**返回值**

+ 0：配置成功。
+ -1：接口调用失败。
+ -2：未集成 K 歌评分模块。
+ \>0：其他错误，具体参看[错误码表](https://www.volcengine.com/docs/6489/148198)。


**注意**
输入正确的鉴权信息才可以使用 K 歌评分相关的功能，鉴权方式为离线鉴权，根据包名（bundleID）绑定 Appkey 及 Token，K 歌评分密钥请联系技术支持同学申请。

<span id="ByteRTCSingScoringManager-setsingscoringconfig"></span>
### setSingScoringConfig:
```objectivec
-(int)setSingScoringConfig:(ByteRTCSingScoringConfig * _Nullable)config;
```
设置 K 歌评分参数。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| config | **ByteRTCSingScoringConfig*** | K 歌评分的各项参数，详见 [ByteRTCSingScoringConfig](iOS-keytype.md#bytertcsingscoringconfig)。 |

**返回值**

+ 0：配置成功。
+ -1：接口调用失败。
+ -2：未集成 K 歌评分模块。
+ \>0：其他错误，具体参看[错误码表](https://www.volcengine.com/docs/6489/148198)。


<span id="ByteRTCSingScoringManager-getstandardpitchinfo"></span>
### getStandardPitchInfo:
```objectivec
-(NSArray<ByteRTCStandardPitchInfo* > * _Nullable)getStandardPitchInfo:(NSString* _Nullable)midiFilepath;
```
获取标准音高数据。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| midiFilepath | **NSString*** | 歌曲 midi 文件路径。 |

**返回值**
[ByteRTCStandardPitchInfo](iOS-keytype.md#bytertcstandardpitchinfo) 标准音高数据数组。


**注意**

+ 请保证此接口传入的 midi 文件路径与 [setSingScoringConfig:](#ByteRTCSingScoringManager-setsingscoringconfig) 接口中传入的路径一致。


<span id="ByteRTCSingScoringManager-startsingscoring-scoringinfointerval"></span>
### startSingScoring:scoringInfoInterval:
```objectivec
-(int)startSingScoring:(int)position scoringInfoInterval:(int)scoringInfoInterval;
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

+ 在调用 [initSingScoring:singScoringToken:delegate:](#ByteRTCSingScoringManager-initsingscoring-singscoringtoken-delegate) 初始化 K 歌评分功能后调用该接口。
+ 调用该接口后，将会根据设置的回调时间间隔，收到评分结果 [onCurrentScoringInfo:](iOS-callback.md#ByteRTCSingScoringDelegate-oncurrentscoringinfo) 回调。
+ 如果调用 [startAudioMixing:filePath:config:](#ByteRTCAudioMixingManager-startaudiomixing-filepath-config) 接口播放音频文件，请在收到 [rtcEngine:onAudioMixingStateChanged:state:error:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onaudiomixingstatechanged-state-error)(ByteRTCAudioMixingStatePlaying) 之后调用此接口。


<span id="ByteRTCSingScoringManager-stopsingscoring"></span>
### stopSingScoring
```objectivec
-(int)stopSingScoring;
```
停止 K 歌评分。

**返回值**

+ 0：成功。
+ <0：失败。


<span id="ByteRTCSingScoringManager-getlastsentencescore"></span>
### getLastSentenceScore
```objectivec
-(int)getLastSentenceScore;
```
获取上一句的演唱评分。调用 [startSingScoring:scoringInfoInterval:](#ByteRTCSingScoringManager-startsingscoring-scoringinfointerval) 开始评分后可以调用该接口。

**返回值**

+ <0：获取评分失败。
+ \>=0：上一句歌词的演唱评分。


<span id="ByteRTCSingScoringManager-gettotalscore"></span>
### getTotalScore
```objectivec
-(int)getTotalScore;
```
获取当前演唱总分。调用 [startSingScoring:scoringInfoInterval:](#ByteRTCSingScoringManager-startsingscoring-scoringinfointerval) 开始评分后可以调用该接口。

**返回值**

+ <0：获取总分失败。
+ \>=0：当前演唱总分。


<span id="ByteRTCSingScoringManager-getaveragescore"></span>
### getAverageScore
```objectivec
-(int)getAverageScore;
```
获取当前演唱歌曲的平均分。

**返回值**

+ <0：获取平均分失败。
+ \>=0：当前演唱平均分。


# ByteRTCSpatialAudio
```objectivec
@interface ByteRTCSpatialAudio :NSObject
```

空间音频接口实例


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **void** | [enableSpatialAudio:](#ByteRTCSpatialAudio-enablespatialaudio) |
| **int** | [updatePosition:](#ByteRTCSpatialAudio-updateposition) |
| **int** | [updateSelfOrientation:](#ByteRTCSpatialAudio-updateselforientation) |
| **void** | [disableRemoteOrientation](#ByteRTCSpatialAudio-disableremoteorientation) |


## 函数说明
<span id="ByteRTCSpatialAudio-enablespatialaudio"></span>
### enableSpatialAudio:
```objectivec

- (void)enableSpatialAudio:(BOOL)enable;
```
开启/关闭空间音频功能。  <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| enable | **BOOL** | 是否开启空间音频功能：  <br/>• true：开启  <br/>• false：关闭（默认） |


**注意**
该方法仅开启空间音频功能，你须调用 [updatePosition:](#ByteRTCSpatialAudio-updateposition) 设置自身位置坐标后方可收听空间音频效果。空间音频相关 API 和调用时序详见[空间音频](https://www.volcengine.com/docs/6348/93903)。

<span id="ByteRTCSpatialAudio-updateposition"></span>
### updatePosition:
```objectivec
-(int)updatePosition:(Position* _Nonnull) pos;
```
更新本地用户在房间内空间直角坐标系中的位置坐标。  <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| pos | **Position*** | 三维坐标的值，默认为 [0, 0, 0]。参看 [Position](iOS-keytype.md#position) |

**返回值**

+ 0: 成功；  
+ !0: 失败。  


**注意**
调用该接口更新坐标前，你需调用 [enableSpatialAudio:](#ByteRTCSpatialAudio-enablespatialaudio) 开启空间音频功能。 空间音频相关 API 和调用时序详见[空间音频](https://www.volcengine.com/docs/6348/93903)。

<span id="ByteRTCSpatialAudio-updateselforientation"></span>
### updateSelfOrientation:
```objectivec
-(int)updateSelfOrientation:(HumanOrientation* _Nonnull) orientation;
```
更新本地用户在空间音频坐标系下的朝向。 <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| orientation | **HumanOrientation*** | 自身朝向信息，参看 [HumanOrientation](iOS-keytype.md#humanorientation)。 |

**返回值**
方法调用结果：  

+ 0：成功  
+ !0：失败


**注意**

+ 空间音频相关 API 和调用时序详见[空间音频](https://www.volcengine.com/docs/6348/93903)。
+ 调用 [disableRemoteOrientation](#ByteRTCSpatialAudio-disableremoteorientation) 可忽略远端用户朝向。


<span id="ByteRTCSpatialAudio-disableremoteorientation"></span>
### disableRemoteOrientation
```objectivec
-(void)disableRemoteOrientation;
```
参与通话的各端调用本接口后，将忽略远端用户的朝向，认为所有远端用户都面向本地用户。<br>
如果此后调用 [updateSelfOrientation:](#ByteRTCSpatialAudio-updateselforientation) 更新本地用户朝向，远端用户无法感知这些变化，但本地用户接收音频时可以感知自身朝向改变带来的音频效果变化。


**注意**

+ 进房前后都可以调用该接口。  
+ 调用本接口关闭朝向功能后，在当前的空间音频实例的生命周期内无法再次开启。