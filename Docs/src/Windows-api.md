# Public API
## 函数

| 返回 | 名称 |
| --- | --- |
| **BYTERTC_API bytertc::IRTCVideo*** | [createRTCVideo](#creatertcvideo) |
| **BYTERTC_API void** | [destroyRTCVideo](#destroyrtcvideo) |
| **BYTERTC_API const char*** | [getErrorDescription](#geterrordescription) |
| **BYTERTC_API const char*** | [getSDKVersion](#getsdkversion) |
| **BYTERTC_API IAudioFrame*** | [buildAudioFrame](#buildaudioframe) |
| **BYTERTC_API ITranscoderParam*** | [createTranscoderParam](#createtranscoderparam) |
| **BYTERTC_API IVideoFrame*** | [buildVideoFrame](#buildvideoframe) |
| **STREAMING_RTC_API IStreamingRTCEngine*** | [CreateStreamingRTCEngine](#createstreamingrtcengine) |
| **STREAMING_RTC_API void** | [DestroyStreamingRTCEngine](#destroystreamingrtcengine) |


## 函数说明
### createRTCVideo
```cpp
BYTERTC_API bytertc::IRTCVideo* bytertc::createRTCVideo(
    const char* app_id,
    bytertc::IRTCVideoEventHandler *event_handler,
    const char* parameters)
```
创建 IRTCVideo 实例。  <br>
如果当前进程中未创建引擎实例，那么你必须先使用此方法，以使用 RTC 提供的各种音视频能力。  <br>
如果当前进程中已创建了引擎实例，再次调用此方法时，会返回已创建的引擎实例。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| app_id | **const char*** | 每个应用的唯一标识符。只有使用相同的 app_id 生成的实例，才能够进行音视频通信。 |
| event_handler | **bytertc::IRTCVideoEventHandler*** | SDK 回调给应用层的 Callback 对象，详见 [IRTCVideoEventHandler](Windows-callback.md#irtcvideoeventhandler) 。 |
| parameters | **const char*** | 私有参数。如需使用请联系技术支持人员。 |

**返回值**

+ IRTCVideo：创建成功。返回一个可用的 [IRTCVideo](#irtcvideo) 实例  
+ Null：创建失败。


### destroyRTCVideo
```cpp
BYTERTC_API void bytertc::destroyRTCVideo();
```
销毁由 [createRTCVideo](#creatertcvideo) 创建的 IRTCVideo 实例，并释放所有相关资源。

**注意**

+ 请确保和需要销毁的 [IRTCVideo](#irtcvideo) 实例相关的业务场景全部结束后，才调用此方法。如果在多线程场景下，调用此接口后，又调用了其他 [IRTCVideo](#irtcvideo) 相关接口，可能导致 SDK 崩溃。该方法在调用之后，会销毁所有和此 [IRTCVideo](#irtcvideo) 实例相关的内存，并且停止与媒体服务器的任何交互。  
+ 调用本方法会启动 SDK 退出逻辑。引擎线程会保留，直到退出逻辑完成。因此，不要在回调线程中直接调用此 API，也不要在回调中等待主线程的执行，并同时在主线程调用本方法。不然会造成死锁。


### getErrorDescription
```cpp
BYTERTC_API const char* bytertc::getErrorDescription(
    int code)
```
获取错误码的描述

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| code | **int** | 需要获取描述的错误码 |

**返回值**
错误码的描述

**注意**
该接口是通用功能，调用时不需要依赖引擎对象。

### getSDKVersion
```cpp
BYTERTC_API const char* bytertc::getSDKVersion();
```
获取当前 SDK 版本信息。

**返回值**
当前 SDK 版本信息。


### buildAudioFrame
```cpp
BYTERTC_API IAudioFrame* bytertc::buildAudioFrame(
    const AudioFrameBuilder& builder)
```
创建 IAudioFrame

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| builder | **const AudioFrameBuilder&** | 音频帧构建实例，参看 [AudioFrameBuilder](Windows-keytype.md#audioframebuilder) |

**返回值**
详见 [IAudioFrame](Windows-keytype.md#iaudioframe)


### createTranscoderParam
```cpp
BYTERTC_API ITranscoderParam* bytertc::createTranscoderParam();
```
创建合流转推参数实例。

**返回值**
创建的 [ITranscoderParam](Windows-keytype.md#itranscoderparam) 实例。

**注意**
该接口创建的实例需在使用完毕后手动调用 delete 销毁。

### buildVideoFrame
```cpp
BYTERTC_API IVideoFrame* bytertc::buildVideoFrame(
    const VideoFrameBuilder& builder)
```
创建 IVideoFrame

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| builder | **const VideoFrameBuilder&** | 视频帧构建实例，参看 [VideoFrameBuilder](Windows-keytype.md#videoframebuilder) |

**返回值**
[IVideoFrame](Windows-keytype.md#ivideoframe) 实例


### CreateStreamingRTCEngine
```cpp
STREAMING_RTC_API IStreamingRTCEngine* bytertc::CreateStreamingRTCEngine(
    const streamingrtc::EngineConfig& config,
    IStreamingRTCEventHandler* handler,
    const char* parameters)
```
创建 IStreamingRTCEngine 实例。  <br>
如果当前线程中未创建引擎实例，那么你必须先使用此方法，以使用 IStreamingRTCEngine 提供的各种音视频能力。  <br>
如果当前线程中已创建了引擎实例，再次调用此方法时，会创建另一个独立的引擎实例。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| config | **const streamingrtc::EngineConfig&** | 设置引擎类型服务端或客户端，端口范围，和 appid。详见 [EngineConfig](Windows-keytype.md#engineconfig)。 |
| handler | **IStreamingRTCEventHandler*** | SDK 回调给应用层的回调对象，详见 [IStreamingRTCEventHandler](Windows-callback.md#istreamingrtceventhandler) 。 |
| parameters | **const char*** | 用以覆盖默认参数的本引擎实例参数。JSON 字符串格式。 |

**返回值**

+ IStreamingRTCEngine：创建成功。返回一个可用的 [IStreamingRTCEngine](#istreamingrtcengine) 实例  
+ Null：创建失败。

**注意**

+ 如果你在同一个线程中创建了多个引擎实例，这些实例必须分别调用 [DestroyStreamingRTCEngine](#destroystreamingrtcengine) 销毁。
+ 创建引擎实例的数量取决于系统的硬件性能。


### DestroyStreamingRTCEngine
```cpp
STREAMING_RTC_API void bytertc::DestroyStreamingRTCEngine(
    IStreamingRTCEngine* engine)
```
销毁由 [CreateStreamingRTCEngine](#createstreamingrtcengine) 创建的 IStreamingRTCEngine 实例，并释放所有相关资源。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | **IStreamingRTCEngine*** | [CreateStreamingRTCEngine](#createstreamingrtcengine) 时，返回的实例。 |

**注意**

+ 请确保和需要销毁的 [IStreamingRTCEngine](#istreamingrtcengine) 实例相关的业务场景全部结束后，才调用此方法。  
+ 该方法在调用之后，会销毁所有和此 [IStreamingRTCEngine](#istreamingrtcengine) 实例相关的内存，并且停止与媒体服务器的任何交互。  
+ 调用本方法会启动 SDK 退出逻辑。引擎线程会保留，直到退出逻辑完成。因此，不要在回调线程中直接调用此 API，也不要在回调中等待主线程的执行，并同时在主线程调用本方法。不然会造成死锁。


# IRTCRoom
```cpp
class bytertc::IRTCRoom
```

房间接口


`Defined in : bytertc_room.h`

## 成员函数

| 返回 | 名称 |
| --- | --- |
| **virtual void** | [destroy](#IRTCRoom-destroy) |
| **virtual void** | [setUserVisibility](#IRTCRoom-setuservisibility) |
| **virtual void** | [setRTCRoomEventHandler](#IRTCRoom-setrtcroomeventhandler) |
| **virtual int** | [joinRoom](#IRTCRoom-joinroom) |
| **virtual void** | [leaveRoom](#IRTCRoom-leaveroom) |
| **virtual void** | [updateToken](#IRTCRoom-updatetoken) |
| **virtual int64_t** | [sendUserMessage](#IRTCRoom-sendusermessage) |
| **virtual int64_t** | [sendUserBinaryMessage](#IRTCRoom-senduserbinarymessage) |
| **virtual int64_t** | [sendRoomMessage](#IRTCRoom-sendroommessage) |
| **virtual int64_t** | [sendRoomBinaryMessage](#IRTCRoom-sendroombinarymessage) |
| **virtual void** | [publishStream](#IRTCRoom-publishstream) |
| **virtual void** | [unpublishStream](#IRTCRoom-unpublishstream) |
| **virtual void** | [publishScreen](#IRTCRoom-publishscreen) |
| **virtual void** | [unpublishScreen](#IRTCRoom-unpublishscreen) |
| **virtual void** | [setRemoteVideoConfig](#IRTCRoom-setremotevideoconfig) |
| **virtual void** | [subscribeStream](#IRTCRoom-subscribestream) |
| **virtual void** | [subscribeAllStreams](#IRTCRoom-subscribeallstreams) |
| **virtual void** | [unsubscribeStream](#IRTCRoom-unsubscribestream) |
| **virtual void** | [unsubscribeAllStreams](#IRTCRoom-unsubscribeallstreams) |
| **virtual void** | [subscribeScreen](#IRTCRoom-subscribescreen) |
| **virtual void** | [unsubscribeScreen](#IRTCRoom-unsubscribescreen) |
| **virtual void** | [pauseAllSubscribedStream](#IRTCRoom-pauseallsubscribedstream) |
| **virtual void** | [resumeAllSubscribedStream](#IRTCRoom-resumeallsubscribedstream) |
| **virtual void** | [setMultiDeviceAVSync](#IRTCRoom-setmultideviceavsync) |
| **virtual int** | [startForwardStreamToRooms](#IRTCRoom-startforwardstreamtorooms) |
| **virtual int** | [updateForwardStreamToRooms](#IRTCRoom-updateforwardstreamtorooms) |
| **virtual void** | [stopForwardStreamToRooms](#IRTCRoom-stopforwardstreamtorooms) |
| **virtual void** | [pauseForwardStreamToAllRooms](#IRTCRoom-pauseforwardstreamtoallrooms) |
| **virtual void** | [resumeForwardStreamToAllRooms](#IRTCRoom-resumeforwardstreamtoallrooms) |
| **virtual IRangeAudio*** | [getRangeAudio](#IRTCRoom-getrangeaudio) |
| **virtual ISpatialAudio*** | [getSpatialAudio](#IRTCRoom-getspatialaudio) |


## 函数说明
<span id="IRTCRoom-destroy"></span>
### destroy
```cpp
virtual void bytertc::IRTCRoom::destroy()
```
退出并销毁调用 [createRTCRoom](#IRTCVideo-creatertcroom) 所创建的房间实例。


<span id="IRTCRoom-setuservisibility"></span>
### setUserVisibility
```cpp
virtual void bytertc::IRTCRoom::setUserVisibility(
    bool enable)
```
设置用户可见性。未调用该接口前，本地用户默认对他人可见。 <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| enable | **bool** | 设置用户是否对房间内其他用户可见：  <br/>• true: 可以在房间内发布音视频流，房间中的其他用户将收到用户的行为通知，例如进房、开启视频采集和退房。  <br/>• false: 不可以在房间内发布音视频流，房间中的其他用户不会收到用户的行为通知，例如进房、开启视频采集和退房。 |


**注意**

+ 该方法在加入房间前后均可调用。 
+ 在房间内调用此方法，房间内其他用户会收到相应的回调通知：
- 从 false 切换至 true 时，房间内其他用户会收到 [onUserJoined](Windows-callback.md#IRTCRoomEventHandler-onuserjoined) 回调通知；  
- 从 true 切换至 false 时，房间内其他用户会收到 [onUserLeave](Windows-callback.md#IRTCRoomEventHandler-onuserleave) 回调通知。  
+ 若调用该方法将可见性设为 false，此时尝试发布流会收到 `kWarningCodePublishStreamForbiden` 警告。


<span id="IRTCRoom-setrtcroomeventhandler"></span>
### setRTCRoomEventHandler
```cpp
virtual void bytertc::IRTCRoom::setRTCRoomEventHandler(
    IRTCRoomEventHandler* room_event_handler)
```
通过设置 [IRTCRoom](#irtcroom) 对象的事件句柄，监听此对象对应的回调事件。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| room_event_handler | **IRTCRoomEventHandler*** | 参见 [IRTCRoomEventHandler](Windows-callback.md#irtcroomeventhandler) |


<span id="IRTCRoom-joinroom"></span>
### joinRoom
```cpp
virtual int bytertc::IRTCRoom::joinRoom(
    const char* token,
    const UserInfo& user_info,
    const RTCRoomConfig& config)
```
创建/加入房间：房间不存在时即创建房间；房间存在时，未加入房间的用户可加入这个房间。  <br>
同一房间内的用户间可以相互通话。  <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| token | **const char*** | 动态密钥，用于对登录用户进行鉴权验证。  <br/>进入房间需要携带 Token。测试时可使用控制台生成临时 Token，正式上线需要使用密钥 SDK 在您的服务端生成并下发 Token。Token 有效期及生成方式参看[使用 Token 完成鉴权](70121)。  <br/>• 使用不同 App ID 的 App 是不能互通的。  <br/>• 请务必保证生成 Token 使用的 App ID 和创建引擎时使用的 App ID 相同，否则会导致加入房间失败。具体失败原因会通过 [onRoomStateChanged](Windows-callback.md#IRTCRoomEventHandler-onroomstatechanged) 回调告知。 |
| user_info | **const UserInfo&** | 用户信息，参看 [UserInfo](Windows-keytype.md#userinfo)。 |
| config | **const RTCRoomConfig&** | 房间参数配置，设置房间模式以及是否自动发布或订阅流。具体配置模式参看 [RTCRoomConfig](Windows-keytype.md#rtcroomconfig)。 |

**返回值**

+  0: 成功  
+ -1：room_id / user_info.uid 包含了无效的参数。  
+ -2：已经在房间内。接口调用成功后，只要收到返回值为 0 ，且未调用 leaveRoom:[leaveRoom](#leaveroom) 成功，则再次调用进房接口时，无论填写的房间 ID 和用户 ID 是否重复，均触发此返回值。  


**注意**

+ 同一个 App ID 的同一个房间内，每个用户的用户 ID 必须是唯一的。如果两个用户的用户 ID 相同，则后进房的用户会将先进房的用户踢出房间，并且先进房的用户会收到 [onRoomStateChanged](Windows-callback#IRTCRoomEventHandler-onroomstatechanged) 回调通知，错误类型详见 [ErrorCode](Windows-errorcode.md#errorcode) 中的 kErrorCodeDuplicateLogin。  
+ 本地用户调用此方法加入房间成功后，会收到 [onRoomStateChanged](Windows-callback.md#IRTCRoomEventHandler-onroomstatechanged) 回调通知。若本地用户同时为可见用户，加入房间时远端用户会收到 [onUserJoined](Windows-callback.md#IRTCRoomEventHandler-onuserjoined) 回调通知。关于可见性设置参看 [setUserVisibility](#IRTCRoom-setuservisibility)。
+ 用户加入房间成功后，在本地网络状况不佳的情况下，SDK 可能会与服务器失去连接，并触发 [onConnectionStateChanged](Windows-callback.md#IRTCVideoEventHandler-onConnectionStateChanged) 回调。此时 SDK 会自动重试，直到成功重连。重连成功后，本地会收到 [onRoomStateChanged](Windows-callback.md#IRTCRoomEventHandler-onroomstatechanged) 回调通知。


<span id="IRTCRoom-leaveroom"></span>
### leaveRoom
```cpp
virtual void bytertc::IRTCRoom::leaveRoom()
```
离开房间。  <br>
用户调用此方法离开房间，结束通话过程，释放所有通话相关的资源。  <br>
加入房间后，必须调用此方法结束通话，否则无法开始下一次通话。无论当前是否在房间内，都可以调用此方法。重复调用此方法没有负面影响。  <br>
此方法是异步操作，调用返回时并没有真正退出房间。真正退出房间后，本地会收到 [onLeaveRoom](Windows-callback.md#IRTCRoomEventHandler-onleaveroom) 回调通知。  <br>


**注意**

+ 可见的用户离开房间后，房间内其他用户会收到 [onUserLeave](Windows-callback.md#IRTCRoomEventHandler-onuserleave) 回调通知。  
+ 如果调用此方法后立即销毁引擎，SDK 将无法触发 [onLeaveRoom](Windows-callback.md#IRTCRoomEventHandler-onleaveroom) 回调。  


<span id="IRTCRoom-updatetoken"></span>
### updateToken
```cpp
virtual void bytertc::IRTCRoom::updateToken(
    const char* token)
```

更新 Token。
在 Token 进房权限过期前 30 秒，会收到 [onTokenWillExpire](Windows-callback.md#IRTCRoomEventHandler-ontokenwillexpire) 回调，此时需要重新获取 Token，并调用此方法更新 Token，否则用户将因为 Token 过期被移出房间。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| token | **const char*** | 获取的新的有效 Token。  <br/>如果传入的 Token 无效，回调错误码为 [ErrorCode](Windows-errorcode.md#errorcode) 中的 `–1010`。 |


**注意**
请勿同时调用 [updateToken](Windows-api.md#IRTCRoom-updatetoken) 和 [joinRoom](Windows-api.md#joinroom) 方法更新 Token。若因 Token 过期或无效导致加入房间失败或已被移出房间，你应该在获取新的有效 Token 后调用 [joinRoom](Windows-api.md#joinroom) 重新加入房间。

<span id="IRTCRoom-sendusermessage"></span>
### sendUserMessage
```cpp
virtual int64_t bytertc::IRTCRoom::sendUserMessage(
    const char* uid,
    const char* message,
    MessageConfig config)
```
给房间内指定的用户发送文本消息（P2P）

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | **const char*** | 消息接收用户的 ID |
| message | **const char*** | 发送的文本消息内容。  <br/>消息不超过 64 KB。 |
| config | **MessageConfig** | 消息类型，参看 [MessageConfig](Windows-keytype.md#messageconfig)。 |

**返回值**
这次发送消息的编号，从 1 开始递增。


**注意**

+ 在发送房间内文本消息前，必须先调用 [joinRoom](#IRTCRoom-joinroom) 加入房间。  
+ 调用该函数后会收到一次 [onUserMessageSendResult](Windows-callback.md#IRTCRoomEventHandler-onusermessagesendresult) 回调，通知消息发送方发送成功或失败；  
+ 若文本消息发送成功，则 uid 所指定的用户会收到 [onUserMessageReceived](Windows-callback.md#IRTCRoomEventHandler-onusermessagereceived) 回调。


<span id="IRTCRoom-senduserbinarymessage"></span>
### sendUserBinaryMessage
```cpp
virtual int64_t bytertc::IRTCRoom::sendUserBinaryMessage(
    const char* uid,
    int length,
    const uint8_t* message,
    MessageConfig config)
```
给房间内指定的用户发送二进制消息（P2P）

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | **const char*** | 消息接收用户的 ID |
| length | **int** | 二进制字符串的长度。 |
| message | **const uint8_t*** | 二进制消息的内容。<br/>消息不超过 64KB。 |
| config | **MessageConfig** | 消息类型，参看 [MessageConfig](Windows-keytype.md#messageconfig)。 |

**返回值**
这次发送消息的编号，从 1 开始递增。


**注意**

+ 在发送房间内二进制消息前，必须先调用 [joinRoom](#IRTCRoom-joinroom) 加入房间。  
+ 调用该函数后会收到一次 [onUserMessageSendResult](Windows-callback.md#IRTCRoomEventHandler-onusermessagesendresult) 回调，通知消息发送方发送成功或失败；  
+ 若二进制消息发送成功，则 uid 所指定的用户会收到 [onUserBinaryMessageReceived](Windows-callback.md#IRTCRoomEventHandler-onuserbinarymessagereceived) 回调。


<span id="IRTCRoom-sendroommessage"></span>
### sendRoomMessage
```cpp
virtual int64_t bytertc::IRTCRoom::sendRoomMessage(
    const char* message)
```
给房间内的所有其他用户群发文本消息。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| message | **const char*** | 用户发送的广播消息  <br/>消息不超过 64 KB。 |


**注意**

+ 在发送房间内二进制消息前，必须先调用 [joinRoom](#IRTCRoom-joinroom) 加入房间。  
+ 调用该函数后，会收到一次 [onRoomMessageSendResult](Windows-callback.md#IRTCRoomEventHandler-onroommessagesendresult) 回调。  
+ 同一房间内的其他用户会收到 [onRoomMessageReceived](Windows-callback.md#IRTCRoomEventHandler-onroommessagereceived) 回调。


<span id="IRTCRoom-sendroombinarymessage"></span>
### sendRoomBinaryMessage
```cpp
virtual int64_t bytertc::IRTCRoom::sendRoomBinaryMessage(
    int size,
    const uint8_t* message)
```
给房间内的所有其他用户群发二进制消息。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| size | **int** | 发送的二进制消息长度 |
| message | **const uint8_t*** | 用户发送的二进制广播消息  <br/>消息不超过 64KB。 |

**返回值**
这次发送消息的编号，从 1 开始递增。


**注意**

+ 在发送房间内二进制消息前，必须先调用 [joinRoom](#IRTCRoom-joinroom) 加入房间。  
+ 调用该函数后，会收到一次 [onRoomMessageSendResult](Windows-callback.md#IRTCRoomEventHandler-onroommessagesendresult) 回调。  
+ 同一房间内的其他用户会收到 [onRoomBinaryMessageReceived](Windows-callback.md#IRTCRoomEventHandler-onroombinarymessagereceived) 回调。


<span id="IRTCRoom-publishstream"></span>
### publishStream
```cpp
virtual void bytertc::IRTCRoom::publishStream(
    MediaStreamType type)
```
在当前所在房间内发布本地通过摄像头/麦克风采集的媒体流

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| type | **MediaStreamType** | 媒体流类型，用于指定发布音频/视频，参看 [MediaStreamType](Windows-keytype.md#mediastreamtype) |


**注意**

+ 如果你已经在用户进房时通过调用 [joinRoom](#IRTCRoom-joinroom) 成功选择了自动发布，则无需再调用本接口。
+ 调用 [setUserVisibility](#IRTCRoom-setuservisibility) 方法将自身设置为不可见后无法调用该方法，需将自身切换至可见后方可调用该方法发布摄像头音视频流。 
+ 如果你需要发布屏幕共享流，调用 [publishScreen](#IRTCRoom-publishscreen)。(Linux 不适用)
+ 如果你需要向多个房间发布流，调用 [startForwardStreamToRooms](#IRTCRoom-startforwardstreamtorooms)。  
+ 调用此方法后，房间中的所有远端用户会收到 [onUserPublishStream](Windows-callback.md#IRTCRoomEventHandler-onuserpublishstream) 回调通知，其中成功收到了音频流的远端用户会收到 [onFirstRemoteAudioFrame](Windows-callback.md#IRTCVideoEventHandler-onfirstremoteaudioframe) 回调，订阅了视频流的远端用户会收到 [onFirstRemoteVideoFrameDecoded](Windows-callback.md#IRTCVideoEventHandler-onfirstremotevideoframedecoded) 回调。
+ 调用 [unpublishStream](#IRTCRoom-unpublishstream) 取消发布。


<span id="IRTCRoom-unpublishstream"></span>
### unpublishStream
```cpp
virtual void bytertc::IRTCRoom::unpublishStream(
    MediaStreamType type)
```
停止将本地摄像头/麦克风采集的媒体流发布到当前所在房间中

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| type | **MediaStreamType** | 媒体流类型，用于指定停止发布音频/视频，参看 [MediaStreamType](Windows-keytype.md#mediastreamtype) |


**注意**

+ 调用 [publishStream](#IRTCRoom-publishstream) 手动发布摄像头音视频流后，你需调用此接口停止发布。
+ 调用此方法停止发布音视频流后，房间中的其他用户将会收到 [onUserUnpublishStream](Windows-callback.md#IRTCRoomEventHandler-onuserunpublishstream) 回调通知。


<span id="IRTCRoom-publishscreen"></span>
### publishScreen
```cpp
virtual void bytertc::IRTCRoom::publishScreen(
    MediaStreamType type)
```
在当前所在房间内发布本地屏幕共享音视频流

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| type | **MediaStreamType** | 媒体流类型，用于指定发布屏幕音频/视频，参看 [MediaStreamType](Windows-keytype.md#mediastreamtype)。 |


**注意**

+ 即使你已经在用户进房时通过调用 [joinRoom](#IRTCRoom-joinroom) 成功选择了自动发布，也需要调用本接口。
+ 调用 [setUserVisibility](#IRTCRoom-setuservisibility) 方法将自身设置为不可见后无法调用该方法，需将自身切换至可见后方可调用该方法发布屏幕流。 
+ 调用该方法后，房间中的所有远端用户会收到 [onUserPublishScreen](Windows-callback.md#IRTCRoomEventHandler-onuserpublishscreen) 回调，其中成功收到音频流的远端用户会收到 [onFirstRemoteAudioFrame](Windows-callback.md#IRTCVideoEventHandler-onfirstremoteaudioframe) 回调，订阅了视频流的远端用户会收到 [onFirstRemoteVideoFrameDecoded](Windows-callback.md#IRTCVideoEventHandler-onfirstremotevideoframedecoded) 回调。
+ 调用 [unpublishScreen](#IRTCRoom-unpublishscreen) 取消发布。 
+ 查看 [PC 端屏幕共享](https://www.volcengine.com/docs/6348/70144)，获取更多信息。


<span id="IRTCRoom-unpublishscreen"></span>
### unpublishScreen
```cpp
virtual void bytertc::IRTCRoom::unpublishScreen(
    MediaStreamType type)
```
停止将本地屏幕共享音视频流发布到当前所在房间中

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| type | **MediaStreamType** | 媒体流类型，用于指定停止发布屏幕音频/视频，参看 [MediaStreamType](Windows-keytype.md#mediastreamtype) |


**注意**

+ 调用 [publishScreen](#IRTCRoom-publishscreen) 发布屏幕流后，你需调用此接口停止发布。 
+ 调用此方法停止发布屏幕音视频流后，房间中的其他用户将会收到 [onUserUnpublishScreen](Windows-callback.md#IRTCRoomEventHandler-onuserunpublishscreen) 回调。


<span id="IRTCRoom-setremotevideoconfig"></span>
### setRemoteVideoConfig
```cpp
virtual void bytertc::IRTCRoom::setRemoteVideoConfig(
    const char *user_id,
    const RemoteVideoConfig &remote_video_config)
```
设置期望订阅的远端视频流的参数。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| user_id | **const char*** | 期望配置订阅参数的远端视频流发布用户的 ID。 |
| remote_video_config | **const RemoteVideoConfig &** | 期望配置的远端视频流参数，参看 [RemoteVideoConfig](Windows-keytype.md#remotevideoconfig)。 |


**注意**

+ 若使用 342 及以前版本的 SDK，调用该方法前请联系技术支持人员开启按需订阅功能。  
+ 该方法仅在发布端调用 [enableSimulcastMode](#IRTCVideo-enablesimulcastmode) 开启了发送多路视频流的情况下生效，此时订阅端将收到来自发布端与期望设置的参数最相近的一路流；否则订阅端只会收到一路参数为分辨率 640px × 360px、帧率 15fps 的视频流。  
+ 若发布端开启了推送多路流功能，但订阅端不对流参数进行设置，则默认接受发送端设置的分辨率最大的一路视频流。  
+ 该方法需在进房后调用，若想进房前设置，你需调用 [joinRoom](#IRTCRoom-joinroom)，并对 `room_config` 中的 `remote_video_config` 进行设置。  
+ SDK 会根据发布端和所有订阅端的设置灵活调整视频流的参数，具体调整策略详见[推送多路流](https://www.volcengine.com/docs/6348/70139)文档。


<span id="IRTCRoom-subscribestream"></span>
### subscribeStream
```cpp
virtual void bytertc::IRTCRoom::subscribeStream(
    const char *user_id,
    MediaStreamType type)
```
订阅房间内指定的通过摄像头/麦克风采集的媒体流，或更新对指定远端用户的订阅选项

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| user_id | **const char*** | 指定订阅的远端发布音视频流的用户 ID。 |
| type | **MediaStreamType** | 媒体流类型，用于指定订阅音频/视频。参看 [MediaStreamType](Windows-keytype.md#mediastreamtype)。 |


**注意**

+ 当调用本接口时，当前用户已经订阅该远端用户，不论是通过手动订阅还是自动订阅，都将根据本次传入的参数，更新订阅配置。
+ 你必须先通过 [onUserPublishStream](Windows-callback.md#IRTCRoomEventHandler-onuserpublishstream)} 回调获取当前房间里的远端摄像头音视频流信息，然后调用本方法按需订阅。  
+ 调用该方法后，你会收到 [onStreamSubscribed](Windows-callback.md#IRTCRoomEventHandler-onstreamsubscribed) 通知方法调用结果。  
+ 成功订阅远端用户的媒体流后，订阅关系将持续到调用 [unsubscribeStream](#IRTCRoom-unsubscribestream) 取消订阅或本端用户退房。 
+ 关于其他调用异常，你会收到 [onStreamStateChanged](Windows-callback#IRTCRoomEventHandler-onstreamstatechanged) 回调通知，具体异常原因参看 [ErrorCode](Windows-errorcode.md#errorcode)。


<span id="IRTCRoom-subscribeallstreams"></span>
### subscribeAllStreams
```cpp
virtual void bytertc::IRTCRoom::subscribeAllStreams(
    MediaStreamType type)
```
订阅房间内所有通过摄像头/麦克风采集的媒体流，或更新订阅选项。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| type | **MediaStreamType** | 媒体流类型，用于指定订阅音频/视频。参看 [MediaStreamType](Windows-keytype.md#mediastreamtype)。 |


**注意**

+ 多次调用订阅接口时，将根据末次调用接口和传入的参数，更新订阅配置。
+ 大会模式下，如果房间内的媒体流超过上限，建议通过调用 [subscribeStream](#IRTCRoom-subscribestream) 逐一指定需要订阅的媒体流。
+ 调用该方法后，你会收到 [onStreamSubscribed](Windows-callback.md#IRTCRoomEventHandler-onstreamsubscribed) 通知方法调用结果。  
+ 成功订阅远端用户的媒体流后，订阅关系将持续到调用 [unsubscribeStream](#IRTCRoom-unsubscribestream) 取消订阅或本端用户退房。 
+ 关于其他调用异常，你会收到 [onStreamStateChanged](Windows-callback#IRTCRoomEventHandler-onstreamstatechanged) 回调通知，具体异常原因参看 [ErrorCode](Windows-errorcode.md#errorcode)。


<span id="IRTCRoom-unsubscribestream"></span>
### unsubscribeStream
```cpp
virtual void bytertc::IRTCRoom::unsubscribeStream(
    const char *user_id,
    MediaStreamType type)
```
取消订阅房间内指定的通过摄像头/麦克风采集的媒体流。  <br>
该方法对自动订阅和手动订阅模式均适用。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| user_id | **const char*** | 指定取消订阅的远端发布音视频流的用户 ID。 |
| type | **MediaStreamType** | 媒体流类型，用于指定取消订阅音频/视频。参看 [MediaStreamType](Windows-keytype.md#mediastreamtype)。 |


**注意**

+ 调用该方法后，你会收到 [onStreamSubscribed](Windows-callback.md#IRTCRoomEventHandler-onstreamsubscribed) 通知方法调用结果。  
+ 关于其他调用异常，你会收到 [onStreamStateChanged](Windows-callback#IRTCRoomEventHandler-onstreamstatechanged) 回调通知，具体失败原因参看 [ErrorCode](Windows-errorcode.md#errorcode)。


<span id="IRTCRoom-unsubscribeallstreams"></span>
### unsubscribeAllStreams
```cpp
virtual void bytertc::IRTCRoom::unsubscribeAllStreams(
    MediaStreamType type)
```
取消订阅房间内所有的通过摄像头/麦克风采集的媒体流。  <br>
自动订阅和手动订阅的流都可以通过本方法取消订阅。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| type | **MediaStreamType** | 媒体流类型，用于指定取消订阅音频/视频。参看 [MediaStreamType](Windows-keytype.md#mediastreamtype)。 |


**注意**

+ 调用该方法后，你会收到 [onStreamSubscribed](Windows-callback.md#IRTCRoomEventHandler-onstreamsubscribed) 通知方法调用结果。  
+ 关于其他调用异常，你会收到 [onStreamStateChanged](Windows-callback#IRTCRoomEventHandler-onstreamstatechanged) 回调通知，具体失败原因参看 [ErrorCode](Windows-errorcode.md#errorcode)。


<span id="IRTCRoom-subscribescreen"></span>
### subscribeScreen
```cpp
virtual void bytertc::IRTCRoom::subscribeScreen(
    const char *user_id,
    MediaStreamType type)
```
订阅房间内指定的远端屏幕共享音视频流，或更新对指定远端用户的订阅选项

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| user_id | **const char*** | 指定订阅的远端发布屏幕流的用户 ID。 |
| type | **MediaStreamType** | 媒体流类型，用于指定订阅音频/视频。参看 [MediaStreamType](Windows-keytype.md#mediastreamtype)。 |


**注意**

+ 当调用本接口时，当前用户已经订阅该远端用户，不论是通过手动订阅还是自动订阅，都将根据本次传入的参数，更新订阅配置。
+ 你必须先通过 [onUserPublishScreen](Windows-callback.md#IRTCRoomEventHandler-onuserpublishscreen)} 回调获取当前房间里的远端屏幕流信息，然后调用本方法按需订阅。  
+ 调用该方法后，你会收到 [onStreamSubscribed](Windows-callback.md#IRTCRoomEventHandler-onstreamsubscribed) 通知方法调用结果。  
+ 成功订阅远端用户的媒体流后，订阅关系将持续到调用 [unsubscribeScreen](#IRTCRoom-unsubscribescreen) 取消订阅或本端用户退房。 
+ 关于其他调用异常，你会收到 [onStreamStateChanged](Windows-callback#IRTCRoomEventHandler-onstreamstatechanged) 回调通知，具体异常原因参看 [ErrorCode](Windows-errorcode.md#errorcode)。


<span id="IRTCRoom-unsubscribescreen"></span>
### unsubscribeScreen
```cpp
virtual void bytertc::IRTCRoom::unsubscribeScreen(
    const char *user_id,
    MediaStreamType type)
```
取消订阅房间内指定的远端屏幕共享音视频流。  <br>
该方法对自动订阅和手动订阅模式均适用。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| user_id | **const char*** | 指定取消订阅的远端发布屏幕流的用户 ID。 |
| type | **MediaStreamType** | 媒体流类型，用于指定取消订阅音频/视频。参看 [MediaStreamType](Windows-keytype.md#mediastreamtype)。 |


**注意**

+ 调用该方法后，你会收到 [onStreamSubscribed](Windows-callback.md#IRTCRoomEventHandler-onstreamsubscribed) 通知方法调用结果。  
+ 关于其他调用异常，你会收到 [onStreamStateChanged](Windows-callback#IRTCRoomEventHandler-onstreamstatechanged) 回调通知，具体失败原因参看 [ErrorCode](Windows-errorcode.md#errorcode)。


<span id="IRTCRoom-pauseallsubscribedstream"></span>
### pauseAllSubscribedStream
```cpp
virtual void bytertc::IRTCRoom::pauseAllSubscribedStream(
    PauseResumeControlMediaType media_type)
```
暂停接收来自远端的媒体流。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| media_type | **PauseResumeControlMediaType** | 媒体流类型，指定需要暂停接收音频还是视频流，参看 [PauseResumeControlMediaType](Windows-keytype.md#pauseresumecontrolmediatype)。 |


**注意**

+ 该方法仅暂停远端流的接收，并不影响远端流的采集和发送；  
+ 该方法不改变用户的订阅状态以及订阅流的属性。  
+ 若想恢复接收远端流，需调用 [resumeAllSubscribedStream](#IRTCRoom-resumeallsubscribedstream)。 
+ 多房间场景下，仅暂停接收发布在当前所在房间的流。


<span id="IRTCRoom-resumeallsubscribedstream"></span>
### resumeAllSubscribedStream
```cpp
virtual void bytertc::IRTCRoom::resumeAllSubscribedStream(
    PauseResumeControlMediaType media_type)
```
恢复接收来自远端的媒体流

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| media_type | **PauseResumeControlMediaType** | 媒体流类型，指定需要暂停接收音频还是视频流，参看 [PauseResumeControlMediaType](Windows-keytype.md#pauseresumecontrolmediatype) |


**注意**

+ 该方法仅恢复远端流的接收，并不影响远端流的采集和发送；  
+ 该方法不改变用户的订阅状态以及订阅流的属性。


<span id="IRTCRoom-setmultideviceavsync"></span>
### setMultiDeviceAVSync
```cpp
virtual void bytertc::IRTCRoom::setMultiDeviceAVSync(
    const char* audio_user_id)
```
设置发流端音画同步。  <br>
当同一用户同时使用两个通话设备分别采集发送音频和视频时，有可能会因两个设备所处的网络环境不一致而导致发布的流不同步，此时你可以在视频发送端调用该接口，SDK 会根据音频流的时间戳自动校准视频流，以保证接收端听到音频和看到视频在时间上的同步性。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audio_user_id | **const char*** | 音频发送端的用户 ID，将该参数设为空则可解除当前音视频的同步关系。 |


**注意**

+ 该方法在进房前后均可调用。  
+ 进行音画同步的音频发布用户 ID 和视频发布用户 ID 须在同一个 RTC 房间内。  
+ 调用该接口后音画同步状态发生改变时，你会收到 [onAVSyncStateChange](Windows-callback.md#IRTCRoomEventHandler-onavsyncstatechange) 回调。  
+ 同一 RTC 房间内允许存在多个音视频同步关系，但需注意单个音频源不支持与多个视频源同时同步。  
+ 如需更换同步音频源，再次调用该接口传入新的 `audio_user_id` 即可；如需更换同步视频源，需先解除当前的同步关系，后在新视频源端开启同步。


<span id="IRTCRoom-startforwardstreamtorooms"></span>
### startForwardStreamToRooms
```cpp
virtual int bytertc::IRTCRoom::startForwardStreamToRooms(
    const ForwardStreamConfiguration& configuration)
```
开始跨房间转发媒体流。
在用户进入房间后调用本接口，实现向多个房间转发媒体流，适用于跨房间连麦等场景。<br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| configuration | **const ForwardStreamConfiguration&** | 跨房间媒体流转发指定房间的信息。参看 [ForwardStreamConfiguration](Windows-keytype.md#forwardstreamconfiguration)。 |

**返回值**

0: 方法调用成功  
<0: 方法调用失败  


**注意**

+ 调用本方法后，将在本端触发 [onForwardStreamStateChanged](Windows-callback.md#IRTCRoomEventHandler-onforwardstreamstatechanged) 回调。
+ 调用本方法后，你可以通过监听 [onForwardStreamEvent](Windows-callback.md#IRTCRoomEventHandler-onforwardstreamevent) 回调来获取各个目标房间在转发媒体流过程中的相关事件。
+ 开始转发后，目标房间中的用户将接收到本地用户进房 [onUserJoined](Windows-callback.md#IRTCRoomEventHandler-onuserjoined) 和发流 [onUserPublishStream](Windows-callback.md#IRTCRoomEventHandler-onuserpublishstream)/[onUserPublishScreen](Windows-callback.md#IRTCRoomEventHandler-onuserpublishscreen) 的回调。
+ 调用本方法后，可以调用 [updateForwardStreamToRooms](#IRTCRoom-updateforwardstreamtorooms) 更新目标房间信息，例如，增加或减少目标房间等。
+ 调用本方法后，可以调用 [stopForwardStreamToRooms](#IRTCRoom-stopforwardstreamtorooms) 停止向所有房间转发媒体流。
+ 调用本方法后，可以调用 [pauseForwardStreamToAllRooms](#IRTCRoom-pauseforwardstreamtoallrooms) 暂停向所有房间转发媒体流。


<span id="IRTCRoom-updateforwardstreamtorooms"></span>
### updateForwardStreamToRooms
```cpp
virtual int bytertc::IRTCRoom::updateForwardStreamToRooms(
    const ForwardStreamConfiguration& configuration)
```
更新跨房间媒体流转发信息。<br>
通过 [startForwardStreamToRooms](#IRTCRoom-startforwardstreamtorooms) 发起媒体流转发后，可调用本方法增加或者减少目标房间，或更新房间密钥。
调用本方法增加或删减房间后，将在本端触发 [onForwardStreamStateChanged](Windows-callback.md#IRTCRoomEventHandler-onforwardstreamstatechanged) 回调，包含发生了变动的目标房间中媒体流转发状态。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| configuration | **const ForwardStreamConfiguration&** | 跨房间媒体流转发目标房间信息。参看 [ForwardStreamConfiguration](Windows-keytype.md#forwardstreamconfiguration)。 |

**返回值**

+ 0: 方法调用成功  
+ <0: 方法调用失败  


**注意**

+ 增加目标房间后，新增目标房间中的用户将接收到本地用户进房 [onUserJoined](Windows-callback.md#IRTCRoomEventHandler-onuserjoined) 和发布 [onUserPublishStream](Windows-callback.md#IRTCRoomEventHandler-onuserpublishstream)/[onUserPublishScreen](Windows-callback.md#IRTCRoomEventHandler-onuserpublishscreen) 的回调。
+ 删减目标房间后，原目标房间中的用户将接收到本地用户停止发布 [onUserUnpublishStream](Windows-callback.md#IRTCRoomEventHandler-onuserunpublishstream)/[onUserUnpublishScreen](Windows-callback.md#IRTCRoomEventHandler-onuserunpublishscreen) 和退房 [onUserLeave](Windows-callback.md#IRTCRoomEventHandler-onuserleave) 的回调。


<span id="IRTCRoom-stopforwardstreamtorooms"></span>
### stopForwardStreamToRooms
```cpp
virtual void bytertc::IRTCRoom::stopForwardStreamToRooms()
```
停止跨房间媒体流转发。
通过 [startForwardStreamToRooms](#IRTCRoom-startforwardstreamtorooms) 发起媒体流转发后，可调用本方法停止向所有目标房间转发媒体流。


**注意**

+ 调用本方法后，将在本端触发 [onForwardStreamStateChanged](Windows-callback.md#IRTCRoomEventHandler-onforwardstreamstatechanged) 回调。
+ 调用本方法后，原目标房间中的用户将接收到本地用户停止发布 [onUserUnpublishStream](Windows-callback.md#IRTCRoomEventHandler-onuserunpublishstream)/[onUserUnpublishScreen](Windows-callback.md#IRTCRoomEventHandler-onuserunpublishscreen) 和退房 [onUserLeave](Windows-callback.md#IRTCRoomEventHandler-onuserleave) 的回调。
+ 如果需要停止向指定的房间转发媒体流，请调用 [updateForwardStreamToRooms](#IRTCRoom-updateforwardstreamtorooms) 更新房间信息。
+ 如果需要暂停转发，请调用 [pauseForwardStreamToAllRooms](#IRTCRoom-pauseforwardstreamtoallrooms)，并在之后随时调用 [resumeForwardStreamToAllRooms](#IRTCRoom-resumeforwardstreamtoallrooms) 快速恢复转发。


<span id="IRTCRoom-pauseforwardstreamtoallrooms"></span>
### pauseForwardStreamToAllRooms
```cpp
virtual void bytertc::IRTCRoom::pauseForwardStreamToAllRooms()
```
暂停跨房间媒体流转发。
通过 [startForwardStreamToRooms](#IRTCRoom-startforwardstreamtorooms) 发起媒体流转发后，可调用本方法暂停向所有目标房间转发媒体流。
调用本方法暂停向所有目标房间转发后，你可以随时调用 [resumeForwardStreamToAllRooms](#IRTCRoom-resumeforwardstreamtoallrooms) 快速恢复转发。


**注意**
调用本方法后，目标房间中的用户将接收到本地用户停止发布 [onUserUnpublishStream](Windows-callback.md#IRTCRoomEventHandler-onuserunpublishstream)/[onUserUnpublishScreen](Windows-callback.md#IRTCRoomEventHandler-onuserunpublishscreen) 和退房 [onUserLeave](Windows-callback.md#IRTCRoomEventHandler-onuserleave) 的回调。

<span id="IRTCRoom-resumeforwardstreamtoallrooms"></span>
### resumeForwardStreamToAllRooms
```cpp
virtual void bytertc::IRTCRoom::resumeForwardStreamToAllRooms()
```
恢复跨房间媒体流转发。
调用 [pauseForwardStreamToAllRooms](#IRTCRoom-pauseforwardstreamtoallrooms) 暂停转发之后，调用本方法恢复向所有目标房间转发媒体流。


**注意**
目标房间中的用户将接收到本地用户进房 [onUserJoined](Windows-callback.md#IRTCRoomEventHandler-onuserjoined) 和发布 [onUserPublishStream](Windows-callback.md#IRTCRoomEventHandler-onuserpublishstream)/[onUserPublishScreen](Windows-callback.md#IRTCRoomEventHandler-onuserpublishscreen) 的回调。


<span id="IRTCRoom-getrangeaudio"></span>
### getRangeAudio
```cpp
virtual IRangeAudio* bytertc::IRTCRoom::getRangeAudio()
```
获取范围语音接口实例。

**返回值**
方法调用结果： 

+ IRangeAudio：成功，返回一个 [IRangeAudio](#irangeaudio) 实例。  
+ nullptr：失败，当前 SDK 不支持范围语音功能。


**注意**
首次调用该方法须在创建房间后、加入房间前。范围语音相关 API 和调用时序详见[范围语音](https://www.volcengine.com/docs/6348/114727)。

<span id="IRTCRoom-getspatialaudio"></span>
### getSpatialAudio
```cpp
virtual ISpatialAudio* bytertc::IRTCRoom::getSpatialAudio()
```
获取空间音频接口实例。  <br>

**返回值**
方法调用结果：  

+ ISpatialAudio：成功，返回一个 [ISpatialAudio](#ispatialaudio) 实例。  
+ nullptr：失败，当前 SDK 不支持空间音频功能。


**注意**

+ 首次调用该方法须在创建房间后、加入房间前。 空间音频相关 API 和调用时序详见[空间音频](https://www.volcengine.com/docs/6348/93903)。 
+ 只有在使用支持真双声道播放的设备时，才能开启空间音频效果；  
+ 机型性能不足可能会导致音频卡顿，使用低端机时，不建议开启空间音频效果；  
+ SDK 最多支持 30 个用户同时开启空间音频功能。


# IRTCVideo
```cpp
class bytertc::IRTCVideo
```

引擎 API


`Defined in : bytertc_video.h`

## 成员函数

| 返回 | 名称 |
| --- | --- |
| **virtual void** | [setCaptureVolume](#IRTCVideo-setcapturevolume) |
| **virtual void** | [setPlaybackVolume](#IRTCVideo-setplaybackvolume) |
| **virtual void** | [startAudioCapture](#IRTCVideo-startaudiocapture) |
| **virtual void** | [stopAudioCapture](#IRTCVideo-stopaudiocapture) |
| **virtual int** | [setVoiceChangerType](#IRTCVideo-setvoicechangertype) |
| **virtual int** | [setVoiceReverbType](#IRTCVideo-setvoicereverbtype) |
| **virtual void** | [setAudioProfile](#IRTCVideo-setaudioprofile) |
| **virtual int** | [setAudioSourceType](#IRTCVideo-setaudiosourcetype) |
| **virtual int** | [setAudioRenderType](#IRTCVideo-setaudiorendertype) |
| **virtual bool** | [pushExternalAudioFrame](#IRTCVideo-pushexternalaudioframe) |
| **virtual bool** | [pullExternalAudioFrame](#IRTCVideo-pullexternalaudioframe) |
| **virtual void** | [startVideoCapture](#IRTCVideo-startvideocapture) |
| **virtual void** | [stopVideoCapture](#IRTCVideo-stopvideocapture) |
| **virtual int** | [setVideoCaptureConfig](#IRTCVideo-setvideocaptureconfig) |
| **virtual int** | [enableSimulcastMode](#IRTCVideo-enablesimulcastmode) |
| **virtual int** | [setVideoEncoderConfig](#IRTCVideo-setvideoencoderconfig) |
| **virtual int** | [setVideoEncoderConfig](#IRTCVideo-setvideoencoderconfig) |
| **virtual int** | [setScreenVideoEncoderConfig](#IRTCVideo-setscreenvideoencoderconfig) |
| **virtual int** | [setLocalVideoCanvas](#IRTCVideo-setlocalvideocanvas) |
| **virtual void** | [updateLocalVideoCanvas](#IRTCVideo-updatelocalvideocanvas) |
| **virtual void** | [setRemoteStreamVideoCanvas](#IRTCVideo-setremotestreamvideocanvas) |
| **virtual void** | [updateRemoteStreamVideoCanvas](#IRTCVideo-updateremotestreamvideocanvas) |
| **virtual void** | [setLocalVideoSink](#IRTCVideo-setlocalvideosink) |
| **virtual void** | [setRemoteVideoSink](#IRTCVideo-setremotevideosink) |
| **virtual bool** | [pushScreenFrame](#IRTCVideo-pushscreenframe) |
| **virtual void** | [updateScreenCaptureRegion](#IRTCVideo-updatescreencaptureregion) |
| **virtual int** | [startScreenVideoCapture](#IRTCVideo-startscreenvideocapture) |
| **virtual void** | [stopScreenVideoCapture](#IRTCVideo-stopscreenvideocapture) |
| **virtual void** | [updateScreenCaptureHighlightConfig](#IRTCVideo-updatescreencapturehighlightconfig) |
| **virtual void** | [updateScreenCaptureMouseCursor](#IRTCVideo-updatescreencapturemousecursor) |
| **virtual void** | [updateScreenCaptureFilterConfig](#IRTCVideo-updatescreencapturefilterconfig) |
| **virtual IScreenCaptureSourceList*** | [getScreenCaptureSourceList](#IRTCVideo-getscreencapturesourcelist) |
| **virtual IVideoFrame*** | [getThumbnail](#IRTCVideo-getthumbnail) |
| **virtual IVideoFrame*** | [getWindowAppIcon](#IRTCVideo-getwindowappicon) |
| **virtual void** | [setVideoSourceType](#IRTCVideo-setvideosourcetype) |
| **virtual bool** | [pushExternalVideoFrame](#IRTCVideo-pushexternalvideoframe) |
| **virtual IRTCRoom*** | [createRTCRoom](#IRTCVideo-creatertcroom) |
| **virtual int** | [setPublishFallbackOption](#IRTCVideo-setpublishfallbackoption) |
| **virtual int** | [setSubscribeFallbackOption](#IRTCVideo-setsubscribefallbackoption) |
| **virtual int** | [setRemoteUserPriority](#IRTCVideo-setremoteuserpriority) |
| **virtual int** | [setBusinessId](#IRTCVideo-setbusinessid) |
| **virtual void** | [setLocalVideoMirrorType](#IRTCVideo-setlocalvideomirrortype) |
| **virtual IVideoEffect*** | [getVideoEffectInterface](#IRTCVideo-getvideoeffectinterface) |
| **virtual int** | [enableEffectBeauty](#IRTCVideo-enableeffectbeauty) |
| **virtual int** | [setBeautyIntensity](#IRTCVideo-setbeautyintensity) |
| **virtual void** | [setEncryptInfo](#IRTCVideo-setencryptinfo) |
| **virtual void** | [setCustomizeEncryptHandler](#IRTCVideo-setcustomizeencrypthandler) |
| **virtual void** | [enableAudioFrameCallback](#IRTCVideo-enableaudioframecallback) |
| **virtual void** | [disableAudioFrameCallback](#IRTCVideo-disableaudioframecallback) |
| **virtual void** | [registerAudioFrameObserver](#IRTCVideo-registeraudioframeobserver) |
| **virtual void** | [registerAudioProcessor](#IRTCVideo-registeraudioprocessor) |
| **virtual void** | [enableAudioProcessor](#IRTCVideo-enableaudioprocessor) |
| **virtual void** | [disableAudioProcessor](#IRTCVideo-disableaudioprocessor) |
| **virtual int** | [registerLocalVideoProcessor](#IRTCVideo-registerlocalvideoprocessor) |
| **virtual int** | [sendSEIMessage](#IRTCVideo-sendseimessage) |
| **virtual IVideoDeviceManager*** | [getVideoDeviceManager](#IRTCVideo-getvideodevicemanager) |
| **virtual IAudioDeviceManager*** | [getAudioDeviceManager](#IRTCVideo-getaudiodevicemanager) |
| **virtual int** | [startFileRecording](#IRTCVideo-startfilerecording) |
| **virtual void** | [stopFileRecording](#IRTCVideo-stopfilerecording) |
| **virtual void** | [enableExternalSoundCard](#IRTCVideo-enableexternalsoundcard) |
| **virtual void** | [setRuntimeParameters](#IRTCVideo-setruntimeparameters) |
| **virtual int** | [feedback](#IRTCVideo-feedback) |
| **virtual IAudioMixingManager*** | [getAudioMixingManager](#IRTCVideo-getaudiomixingmanager) |
| **virtual int64_t** | [login](#IRTCVideo-login) |
| **virtual void** | [logout](#IRTCVideo-logout) |
| **virtual void** | [updateLoginToken](#IRTCVideo-updatelogintoken) |
| **virtual void** | [setServerParams](#IRTCVideo-setserverparams) |
| **virtual void** | [getPeerOnlineStatus](#IRTCVideo-getpeeronlinestatus) |
| **virtual int64_t** | [sendUserMessageOutsideRoom](#IRTCVideo-sendusermessageoutsideroom) |
| **virtual int64_t** | [sendUserBinaryMessageOutsideRoom](#IRTCVideo-senduserbinarymessageoutsideroom) |
| **virtual int64_t** | [sendServerMessage](#IRTCVideo-sendservermessage) |
| **virtual int64_t** | [sendServerBinaryMessage](#IRTCVideo-sendserverbinarymessage) |
| **virtual NetworkDetectionStartReturn** | [startNetworkDetection](#IRTCVideo-startnetworkdetection) |
| **virtual void** | [stopNetworkDetection](#IRTCVideo-stopnetworkdetection) |
| **virtual void** | [setScreenAudioSourceType](#IRTCVideo-setscreenaudiosourcetype) |
| **virtual void** | [setScreenAudioStreamIndex](#IRTCVideo-setscreenaudiostreamindex) |
| **virtual void** | [startScreenAudioCapture](#IRTCVideo-startscreenaudiocapture) |
| **virtual void** | [stopScreenAudioCapture](#IRTCVideo-stopscreenaudiocapture) |
| **virtual int** | [pushScreenAudioFrame](#IRTCVideo-pushscreenaudioframe) |
| **virtual void** | [startLiveTranscoding](#IRTCVideo-startlivetranscoding) |
| **virtual void** | [stopLiveTranscoding](#IRTCVideo-stoplivetranscoding) |
| **virtual void** | [updateLiveTranscoding](#IRTCVideo-updatelivetranscoding) |
| **virtual void** | [startPushSingleStreamToCDN](#IRTCVideo-startpushsinglestreamtocdn) |
| **virtual void** | [stopPushStreamToCDN](#IRTCVideo-stoppushstreamtocdn) |
| **virtual int** | [startPushPublicStream](#IRTCVideo-startpushpublicstream) |
| **virtual int** | [stopPushPublicStream](#IRTCVideo-stoppushpublicstream) |
| **virtual int** | [updatePublicStreamParam](#IRTCVideo-updatepublicstreamparam) |
| **virtual void** | [enableAudioPropertiesReport](#IRTCVideo-enableaudiopropertiesreport) |
| **virtual void** | [setRemoteAudioPlaybackVolume](#IRTCVideo-setremoteaudioplaybackvolume) |
| **virtual void** | [enableVocalInstrumentBalance](#IRTCVideo-enablevocalinstrumentbalance) |
| **virtual void** | [enablePlaybackDucking](#IRTCVideo-enableplaybackducking) |
| **virtual void** | [registerLocalEncodedVideoFrameObserver](#IRTCVideo-registerlocalencodedvideoframeobserver) |
| **virtual void** | [registerRemoteEncodedVideoFrameObserver](#IRTCVideo-registerremoteencodedvideoframeobserver) |
| **virtual void** | [setExternalVideoEncoderEventHandler](#IRTCVideo-setexternalvideoencodereventhandler) |
| **virtual bool** | [pushExternalEncodedVideoFrame](#IRTCVideo-pushexternalencodedvideoframe) |
| **virtual void** | [setVideoDecoderConfig](#IRTCVideo-setvideodecoderconfig) |
| **virtual void** | [requestRemoteVideoKeyFrame](#IRTCVideo-requestremotevideokeyframe) |
| **virtual int** | [sendStreamSyncInfo](#IRTCVideo-sendstreamsyncinfo) |
| **virtual void** | [setLocalVoicePitch](#IRTCVideo-setlocalvoicepitch) |
| **virtual int** | [startPlayPublicStream](#IRTCVideo-startplaypublicstream) |
| **virtual int** | [stopPlayPublicStream](#IRTCVideo-stopplaypublicstream) |
| **virtual int** | [setPublicStreamVideoCanvas](#IRTCVideo-setpublicstreamvideocanvas) |
| **virtual void** | [setPublicStreamVideoSink](#IRTCVideo-setpublicstreamvideosink) |
| **virtual void** | [setVideoWatermark](#IRTCVideo-setvideowatermark) |
| **virtual void** | [clearVideoWatermark](#IRTCVideo-clearvideowatermark) |
| **virtual long** | [takeLocalSnapshot](#IRTCVideo-takelocalsnapshot) |
| **virtual long** | [takeRemoteSnapshot](#IRTCVideo-takeremotesnapshot) |
| **virtual void** | [startCloudProxy](#IRTCVideo-startcloudproxy) |
| **virtual void** | [stopCloudProxy](#IRTCVideo-stopcloudproxy) |
| **virtual int** | [startEchoTest](#IRTCVideo-startechotest) |
| **virtual int** | [stopEchoTest](#IRTCVideo-stopechotest) |
| **virtual IKTVManager*** | [getKTVManager](#IRTCVideo-getktvmanager) |
| **virtual ISingScoringManager*** | [getSingScoringManager](#IRTCVideo-getsingscoringmanager) |


## 函数说明
<span id="IRTCVideo-setcapturevolume"></span>
### setCaptureVolume
```cpp
virtual void bytertc::IRTCVideo::setCaptureVolume(
    StreamIndex index,
    int volume)
```
调节音频采集音量

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| index | **StreamIndex** | 流索引，指定调节主流还是调节屏幕流的音量，参看 [StreamIndex](Windows-keytype.md#streamindex) |
| volume | **int** | 采集的音量值和原始音量的比值，范围是 [0, 400]，单位为 %，自带溢出保护。只改变音频数据的音量信息，不涉及本端硬件的音量调节。<br/>为保证更好的通话质量，建议将 volume 值设为 [0,100]。<br/>• 0：静音  <br/>• 100：原始音量  <br/>• 400: 最大可为原始音量的 4 倍(自带溢出保护) |


**注意**
在开启音频采集前后，你都可以使用此接口设定采集音量。

<span id="IRTCVideo-setplaybackvolume"></span>
### setPlaybackVolume
```cpp
virtual void bytertc::IRTCVideo::setPlaybackVolume(
    const int volume)
```
调节本地播放的所有远端用户混音后的音量。播放音频前或播放音频时，你都可以使用此接口设定播放音量。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| volume | **const int** | 音频播放音量值和原始音量的比值，范围是 [0, 400]，单位为 %，自带溢出保护。只改变音频数据的音量信息，不涉及本端硬件的音量调节。  <br/>为保证更好的通话质量，建议将 volume 值设为 [0,100]。  <br/>• 0: 静音  <br/>• 100: 原始音量  <br/>• 400: 最大可为原始音量的 4 倍(自带溢出保护) |


<span id="IRTCVideo-startaudiocapture"></span>
### startAudioCapture
```cpp
virtual void bytertc::IRTCVideo::startAudioCapture()
```
开启内部音频采集。默认为关闭状态。  <br>
内部采集是指：使用 RTC SDK 内置的音频采集机制进行视频采集。
调用该方法开启后，本地用户会收到 [onAudioDeviceStateChanged](Windows-callback.md#IRTCVideoEventHandler-onaudiodevicestatechanged) 的回调。 <br>
非隐身用户进房后调用该方法，房间中的其他用户会收到 [onUserStartAudioCapture](Windows-callback.md#IRTCVideoEventHandler-onuserstartaudiocapture) 的回调。


**注意**

+ 若未取得当前设备的麦克风权限，调用该方法后会触发 [onWarning](Windows-callback.md#IRTCVideoEventHandler-onwarning) 回调。  
+ 调用 [stopAudioCapture](#IRTCVideo-stopaudiocapture) 可以关闭音频采集设备，否则，SDK 只会在销毁引擎的时候自动关闭设备。  
+ 由于不同硬件设备初始化响应时间不同，频繁调用 [stopAudioCapture](#IRTCVideo-stopaudiocapture) 和本接口闭麦/开麦可能出现短暂无声问题，建议使用 [publishStream](#IRTCRoom-publishstream)/[unpublishStream](#IRTCRoom-unpublishstream) 实现临时闭麦和重新开麦。
+ 创建引擎后，无论是否发布音频数据，你都可以调用该方法开启音频采集，并且调用后方可发布音频。  
+ 如果需要从自定义音频采集切换为内部音频采集，你必须先停止发布流，调用 [setAudioSourceType](#IRTCVideo-setaudiosourcetype) 关闭自定义采集，再调用此方法手动开启内部采集。


<span id="IRTCVideo-stopaudiocapture"></span>
### stopAudioCapture
```cpp
virtual void bytertc::IRTCVideo::stopAudioCapture()
```
立即关闭内部音频采集。默认为关闭状态。  <br>
内部采集是指：使用 RTC SDK 内置的音频采集机制进行视频采集。
调用该方法，本地用户会收到 [onAudioDeviceStateChanged](Windows-callback.md#IRTCVideoEventHandler-onaudiodevicestatechanged) 的回调。  <br>
非隐身用户进房后调用该方法后，房间中的其他用户会收到 [onUserStopAudioCapture](Windows-callback.md#IRTCVideoEventHandler-onuserstopaudiocapture) 的回调。


**注意**

+ 调用 [startAudioCapture](#IRTCVideo-startaudiocapture) 可以开启音频采集设备。  
+ 如果不调用本方法停止内部视频采集，则只有当销毁引擎实例时，内部音频采集才会停止。


<span id="IRTCVideo-setvoicechangertype"></span>
### setVoiceChangerType
```cpp
virtual int bytertc::IRTCVideo::setVoiceChangerType(
    VoiceChangerType voice_changer)
```
设置变声特效类型

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| voice_changer | **VoiceChangerType** | 变声特效类型，参看 [VoiceChangerType](Windows-keytype.md#voicechangertype) |


**注意**

+ 在进房前后都可设置。  
+ 对 RTC SDK 内部采集的音频和自定义采集的音频都生效。 
+ 只对单声道音频生效。
+ 只在包含美声特效能力的 SDK 中有效。
+ 与 [setVoiceReverbType](#IRTCVideo-setvoicereverbtype) 互斥，后设置的特效会覆盖先设置的特效。
+ 使用本接口前，请联系 RTC 技术支持了解更多详情。


<span id="IRTCVideo-setvoicereverbtype"></span>
### setVoiceReverbType
```cpp
virtual int bytertc::IRTCVideo::setVoiceReverbType(
    VoiceReverbType voice_reverb)
```
设置混响特效类型

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| voice_reverb | **VoiceReverbType** | 混响特效类型，参看 [VoiceReverbType](Windows-keytype.md#voicereverbtype) |


**注意**

+ 在进房前后都可设置。  
+ 对 RTC SDK 内部采集的音频和自定义采集的音频都生效。 
+ 只对单声道音频生效。
+ 只在包含美声特效能力的 SDK 中有效。
+ 与 [setVoiceChangerType](#IRTCVideo-setvoicechangertype) 互斥，后设置的特效会覆盖先设置的特效。 
+ 使用本接口前，请联系 RTC 技术支持了解更多详情。 


<span id="IRTCVideo-setaudioprofile"></span>
### setAudioProfile
```cpp
virtual void bytertc::IRTCVideo::setAudioProfile(
    AudioProfileType audio_profile)
```
设置音质档位。当所选的 [RoomProfileType](Windows-keytype.md#roomprofiletype) 中的音频参数无法满足你的场景需求时，调用本接口切换的音质档位。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audio_profile | **AudioProfileType** | 音质档位，参看 [AudioProfileType](Windows-keytype.md#audioprofiletype) |


**注意**

+ 该方法在进房前后均可调用；  
+ 支持通话过程中动态切换音质档位。


<span id="IRTCVideo-setaudiosourcetype"></span>
### setAudioSourceType
```cpp
virtual int bytertc::IRTCVideo::setAudioSourceType (
    AudioSourceType type)
```
切换音频采集方式

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| type | **AudioSourceType** | 音频数据源，详见 [AudioSourceType](Windows-keytype.md#audiosourcetype)。<br/>默认使用内部音频采集。音频采集和渲染方式无需对应。 |

**返回值**
方法调用结果：  

+ \>0: 切换成功。
+ -1：切换失败。


**注意**

+ 进房前后调用此方法均有效。
+ 如果你调用此方法由内部采集切换至自定义采集，SDK 会自动关闭内部采集。然后，调用 [pushExternalAudioFrame](#IRTCVideo-pushexternalaudioframe) 推送自定义采集的音频数据到 RTC SDK 用于传输。 
+ 如果你调用此方法由自定义采集切换至内部采集，你必须再调用 [startAudioCapture](#IRTCVideo-startaudiocapture) 手动开启内部采集。 


<span id="IRTCVideo-setaudiorendertype"></span>
### setAudioRenderType
```cpp
virtual int bytertc::IRTCVideo::setAudioRenderType (
    AudioRenderType type)
```
切换音频渲染方式

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| type | **AudioRenderType** | 音频输出类型，详见 [AudioRenderType](Windows-keytype.md#audiorendertype) <br/>默认使用内部音频渲染。音频采集和渲染方式无需对应。 |

**返回值**
方法调用结果：  

+ \>0: 切换成功。
+ -1：切换失败。


**注意**

+ 进房前后调用此方法均有效。
+ 如果你调用此方法切换至自定义渲染，调用 [pullExternalAudioFrame](#IRTCVideo-pullexternalaudioframe) 获取音频数据。 


<span id="IRTCVideo-pushexternalaudioframe"></span>
### pushExternalAudioFrame
```cpp
virtual bool bytertc::IRTCVideo::pushExternalAudioFrame(
    IAudioFrame* audioFrame)
```
推送自定义音频数据。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioFrame | **IAudioFrame*** | 10 ms 对应的音频数据。详见 [IAudioFrame](Windows-keytype.md#iaudioframe)。 |

**返回值**
方法调用结果  

+ true: 方法调用成功  
+ false：方法调用失败  


**注意**

+ 推送自定义采集的音频数据前，必须先调用 [setAudioSourceType](#IRTCVideo-setaudiosourcetype) 开启自定义采集。
+ 你必须每 10 ms 推送一次数据。


<span id="IRTCVideo-pullexternalaudioframe"></span>
### pullExternalAudioFrame
```cpp
virtual bool bytertc::IRTCVideo::pullExternalAudioFrame(
    IAudioFrame* audioFrame)
```
拉取远端音频数据。可用于自定义音频渲染。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioFrame | **IAudioFrame*** | 获取的 10 ms 内的音频数据。详见 [IAudioFrame](Windows-keytype.md#iaudioframe)。 |

**返回值**
方法调用结果：  

+ true: 方法调用成功  
+ false：方法调用失败  


**注意**

+ 获取音频数据用于自定义渲染前，必须先调用 [setAudioRenderType](#IRTCVideo-setaudiorendertype) 开启自定义渲染。
+ 由于 RTC SDK 的帧长为 10 毫秒，你应当每隔 10 毫秒拉取一次音频数据。确保音频采样点数（sample）x 拉取频率等于 audioFrame 的采样率 （sampleRate）。如设置采样率为 48000 时，每 10 毫秒调用本接口拉取数据，每次应拉取 480 个采样点。 
+ 该函数运行在用户调用线程内，是一个同步函数。  


<span id="IRTCVideo-startvideocapture"></span>
### startVideoCapture
```cpp
virtual void bytertc::IRTCVideo::startVideoCapture()
```
立即开启内部视频采集。默认为关闭状态。  <br>
内部视频采集指：使用 RTC SDK 内置视频采集模块，进行采集。<br>
调用该方法后，本地用户会收到 [onVideoDeviceStateChanged](Windows-callback.md#IRTCVideoEventHandler-onvideodevicestatechanged) 的回调。  <br>
本地用户在非隐身状态下调用该方法后，房间中的其他用户会收到 [onUserStartVideoCapture](Windows-callback.md#IRTCVideoEventHandler-onuserstartvideocapture) 的回调。


**注意**

+ 调用 [stopVideoCapture](#IRTCVideo-stopvideocapture) 可以停止内部视频采集。否则，只有当销毁引擎实例时，内部视频采集才会停止。  
+ 创建引擎后，无论是否发布视频数据，你都可以调用该方法开启内部视频采集。只有当（内部或外部）视频采集开始以后视频流才会发布。  
+ 如果需要从自定义视频采集切换为内部视频采集，你必须先关闭自定义采集，再调用此方法手动开启内部采集。


<span id="IRTCVideo-stopvideocapture"></span>
### stopVideoCapture
```cpp
virtual void bytertc::IRTCVideo::stopVideoCapture()
```
立即关闭内部视频采集。默认为关闭状态。  <br>
内部视频采集指：使用 RTC SDK 内置视频采集模块，进行采集。<br>
调用该方法后，本地用户会收到 [onVideoDeviceStateChanged](Windows-callback.md#IRTCVideoEventHandler-onvideodevicestatechanged) 的回调。  <br>
非隐身用户进房后调用该方法，房间中的其他用户会收到 [onUserStopVideoCapture](Windows-callback.md#IRTCVideoEventHandler-onuserstopvideocapture) 的回调。


**注意**

+ 调用 [startVideoCapture](#IRTCVideo-startvideocapture) 可以开启内部视频采集。  
+ 如果不调用本方法停止内部视频采集，则只有当销毁引擎实例时，内部视频采集才会停止。


<span id="IRTCVideo-setvideocaptureconfig"></span>
### setVideoCaptureConfig
```cpp
virtual int bytertc::IRTCVideo::setVideoCaptureConfig(
    const VideoCaptureConfig& videoCaptureConfig)
```
设置 RTC SDK 内部采集时的视频采集参数。<br>
如果你的项目使用了 SDK 内部采集模块，可以通过本接口指定视频采集参数，包括模式、分辨率、帧率。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| videoCaptureConfig | **const VideoCaptureConfig&** | 视频采集参数。参看: [VideoCaptureConfig](Windows-keytype.md#videocaptureconfig)。 |

**返回值**

+ 0: 成功；  
+ < 0: 失败；  


**注意**

+ 本接口在引擎创建后可调用，调用后立即生效。建议在调用 [startVideoCapture](#IRTCVideo-startvideocapture) 前调用本接口。
+ 建议同一设备上的不同引擎使用相同的视频采集参数。
+ 如果调用本接口前使用内部模块开始视频采集，采集参数默认为 Auto 模式。


<span id="IRTCVideo-enablesimulcastmode"></span>
### enableSimulcastMode
```cpp
virtual int bytertc::IRTCVideo::enableSimulcastMode(
    bool enabled)
```
该方法设置视频流发布端是否开启发布多路编码参数不同的视频流的模式。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| enabled | **bool** | 是否开启推送多路视频流模式： <br/>• True：开启 <br/>• False：关闭（默认） |

**返回值**
方法调用结果： 

+ 0: 成功 
+ <0: 失败


**注意**

+ 你应在进房前或进房后但未发布流时，调用此方法。  
+ 开启推送多路流后，不能动态关闭，也不能更新多路流的路数和编码参数。
+ 开启推送多路视频流模式后，你可以调用 [SetVideoEncoderConfig](#IRTCVideo-setvideoencoderconfig-2) 为多路视频流分别设置编码参数。  
+ 该功能关闭时，或该功能开启但未设置多路流参数时，默认只发一路视频流，该流的编码参数为：分辨率 640px × 360px，帧率 15fps。


<span id="IRTCVideo-setvideoencoderconfig"></span>
### setVideoEncoderConfig
```cpp
virtual int bytertc::IRTCVideo::setVideoEncoderConfig(
    const VideoEncoderConfig& max_solution)
```
<span id="IRTCVideo-setvideoencoderconfig-1"></span>
视频发布端设置期望发布的最大分辨率视频流参数，包括分辨率、帧率、码率、网络不佳时的回退策略等。  <br>
该接口支持设置一路视频流参数，设置多路参数请使用重载 API：[setVideoEncoderConfig](#IRTCVideo-setvideoencoderconfig-2)。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| max_solution | **const VideoEncoderConfig&** | 期望发布的最大分辨率视频流参数。参看 [VideoEncoderConfig](Windows-keytype.md#videoencoderconfig)。 |

**返回值**
方法调用结果： 

+ 0：成功  
+ !0：失败  


**注意**

+ 若调用该方法设置了期望发布的最大分辨率的流参数之前，已调用 [enableSimulcastMode](#IRTCVideo-enablesimulcastmode) 开启发布多路视频流的模式，SDK 会根据订阅端的设置自动调整发布的流数以及各路流的参数，其中最大分辨率为设置的分辨率，流数最多 4 条，具体参看[推送多路流](https://www.volcengine.com/docs/6348/70139)文档；否则仅发布该条最大分辨率的视频流。 
+ 调用该方法设置多路视频流参数前，SDK 默认仅发布一条分辨率为 640px × 360px，帧率为 15fps 的视频流。  
+ 自定义采集的场景下，务必调用该接口设置分辨率，以保证远端收到画面的完整性。
+ 该方法适用于摄像头采集的视频流，设置屏幕共享视频流参数参看 [setScreenVideoEncoderConfig](#IRTCVideo-setscreenvideoencoderconfig)（Linux 不适用）。


<span id="IRTCVideo-setvideoencoderconfig"></span>
### setVideoEncoderConfig
```cpp
virtual int bytertc::IRTCVideo::setVideoEncoderConfig(
    const VideoEncoderConfig* channel_solutions,
    int solution_num)
```
<span id="IRTCVideo-setvideoencoderconfig-2"></span>
视频发布端设置推送多路流时各路流的参数，包括分辨率、帧率、码率、网络不佳时的回退策略等。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| channel_solutions | **const VideoEncoderConfig*** | 要推送的多路视频流的参数需注意，所设置的分辨率是各路流的最大分辨率。参看 [VideoEncoderConfig](Windows-keytype.md#videoencoderconfig)。 |
| solution_num | **int** | 视频参数数组长度，最多支持设置 3 路参数，超过 3 路时默认取前 3 路的值。当设置了多路参数时，分辨率和帧率必须是从大到小排列。需注意，所设置的分辨率是各路流的最大分辨率。 |

**返回值**
方法调用结果： 

+ 0：成功  
+ !0：失败  


**注意**

+ 该方法是否生效取决于是否同时调用了 [enableSimulcastMode](#IRTCVideo-enablesimulcastmode) 开启发布多路参数不同的视频流模式。若未开启推送多路流模式，但调用本方法设置了多个分辨率，SDK 默认发布分辨率最大的一条流，多个分辨率的设置会在开启推送多路流模式之后生效。  
+ 开启推送多路流后，不能动态关闭，也不能更新多路流的路数和编码参数。
+ 调用该方法设置多路视频流参数前，SDK 默认仅发布一条分辨率为 640px × 360px，帧率为 15fps 的视频流。  
+ 调用该方法设置分辨率不同的多条流后，SDK 会根据订阅端设置的期望订阅参数自动匹配发送的流，具体规则参看[推送多路流](https://www.volcengine.com/docs/6348/70139)文档。  
+ 该方法适用于摄像头采集的视频流，设置屏幕共享视频流参数参看 [setScreenVideoEncoderConfig](#IRTCVideo-setscreenvideoencoderconfig)（Linux 不适用）。


<span id="IRTCVideo-setscreenvideoencoderconfig"></span>
### setScreenVideoEncoderConfig
```cpp
virtual int bytertc::IRTCVideo::setScreenVideoEncoderConfig(
    const VideoEncoderConfig& screen_solution)
```
为发布的屏幕共享视频流设置期望的编码参数，包括分辨率、帧率、码率、网络不佳时的回退策略等。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| screen_solution | **const VideoEncoderConfig&** | 屏幕共享视频流参数。参看 [VideoEncoderConfig](Windows-keytype.md#videoencoderconfig)。 |

**返回值**
方法调用结果： 
0：成功  
!0：失败  


**注意**
调用该方法之前，屏幕共享视频流默认的编码参数为：分辨率 1920px × 1080px，帧率 15fps。

<span id="IRTCVideo-setlocalvideocanvas"></span>
### setLocalVideoCanvas
```cpp
virtual int bytertc::IRTCVideo::setLocalVideoCanvas(
    StreamIndex index,
    const VideoCanvas& canvas)
```
设置本地视频渲染时，使用的视图，并设置渲染模式。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| index | **StreamIndex** | 视频流属性, 参看 [StreamIndex](Windows-keytype.md#streamindex) |
| canvas | **const VideoCanvas&** | 视图信息和渲染模式，参看：[VideoCanvas](Windows-keytype.md#videocanvas) |

**返回值**

+ 0：成功  
+ !0：失败  


**注意**

+ 你应在加入房间前，绑定本地视图。退出房间后，此设置仍然有效。  
+ 如果需要解除绑定，你可以调用本方法传入空视图。


<span id="IRTCVideo-updatelocalvideocanvas"></span>
### updateLocalVideoCanvas
```cpp
virtual void bytertc::IRTCVideo::updateLocalVideoCanvas(
    StreamIndex index,
    const enum RenderMode renderMode,
    const uint32_t backgroundColor)
```
修改本地视频渲染模式和背景色。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| index | **StreamIndex** | 视频流属性, 参看 [StreamIndex](Windows-keytype.md#streamindex) |
| renderMode | **const enum RenderMode** | 渲染模式，参看 [RenderMode](Windows-keytype.md#rendermode) |
| backgroundColor | **const uint32_t** | 背景颜色，参看 [VideoCanvas](Windows-keytype.md#videocanvas).background_color |


**注意**
你可以在本地视频渲染过程中，调用此接口。调用结果会实时生效。

<span id="IRTCVideo-setremotestreamvideocanvas"></span>
### setRemoteStreamVideoCanvas
```cpp
virtual void bytertc::IRTCVideo::setRemoteStreamVideoCanvas(
    RemoteStreamKey stream_key,
    const VideoCanvas& canvas)
```
设置渲染指定视频流 `stream_key` 时，使用的视图和渲染模式。 <br>
如果需要解除某个用户的绑定视图，你可以把 `canvas` 设置为空。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stream_key | **RemoteStreamKey** | 参看 [RemoteStreamKey](Windows-keytype.md#remotestreamkey) |
| canvas | **const VideoCanvas&** | 视图信息和渲染模式，参看：[VideoCanvas](Windows-keytype.md#videocanvas) |

**返回值**

+ 0：成功  
+ !0：失败  


**注意**

+ 你应在收到 [onUserJoined](Windows-callback.md#IRTCRoomEventHandler-onuserjoined) 或 [onFirstRemoteVideoFrameDecoded](Windows-callback.md#IRTCVideoEventHandler-onfirstremotevideoframedecoded) 后，为远端视频绑定渲染视图。这两个回调的差别是：如果启用了视频录制功能，视频录制服务会作为一个哑客户端加入房间，因此其他客户端会收到对应的 [onUserJoined](Windows-callback.md#IRTCRoomEventHandler-onuserjoined) 回调，而不会收到 [onFirstRemoteVideoFrameDecoded](Windows-callback.md#IRTCVideoEventHandler-onfirstremotevideoframedecoded) 回调。你不应给录制的哑亚客户端绑定视图（因为它不会发送视频流）。
+ 本地用户离开房间时，会解除调用此 API 建立的绑定关系；远端用户离开房间则不会影响。


<span id="IRTCVideo-updateremotestreamvideocanvas"></span>
### updateRemoteStreamVideoCanvas
```cpp
virtual void bytertc::IRTCVideo::updateRemoteStreamVideoCanvas(
    RemoteStreamKey stream_key,
    const enum RenderMode renderMode,
    const uint32_t backgroundColor)
```
修改远端视频渲染模式和背景色。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stream_key | **RemoteStreamKey** | 远端流信息。参看 [RemoteStreamKey](Windows-keytype.md#remotestreamkey) |
| renderMode | **const enum RenderMode** | 渲染模式，参看 [RenderMode](Windows-keytype.md#rendermode) |
| backgroundColor | **const uint32_t** | 背景颜色，参看 [VideoCanvas](Windows-keytype.md#videocanvas).background_color |


**注意**
你可以在远端视频渲染过程中，调用此接口。调用结果会实时生效。

<span id="IRTCVideo-setlocalvideosink"></span>
### setLocalVideoSink
```cpp
virtual void bytertc::IRTCVideo::setLocalVideoSink(
    StreamIndex index,
    IVideoSink* video_sink,
    IVideoSink::PixelFormat required_format)
```
将本地视频流与自定义渲染器绑定。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| index | **StreamIndex** | 视频流属性。采集的视频流/屏幕视频流，参看 [StreamIndex](Windows-keytype.md#streamindex) |
| video_sink | **IVideoSink*** | 自定义视频渲染器，参看 [IVideoSink](Windows-keytype.md#ivideosink)。 |
| required_format | **IVideoSink::PixelFormat** | video_sink 适用的视频帧编码格式，参看 [PixelFormat](Windows-keytype.md#pixelformat) |


**注意**

+ RTC SDK 默认使用 RTC SDK 自带的渲染器（内部渲染器）进行视频渲染。
+ 如果需要解除绑定，必须将 video_sink 设置为 null。退房时将清除绑定状态。
+ 一般在收到 [onFirstLocalVideoFrameCaptured](Windows-callback.md#IRTCVideoEventHandler-onfirstlocalvideoframecaptured) 回调通知完成本地视频首帧采集后，调用此方法为视频流绑定自定义渲染器；然后加入房间。


<span id="IRTCVideo-setremotevideosink"></span>
### setRemoteVideoSink
```cpp
virtual void bytertc::IRTCVideo::setRemoteVideoSink(
    RemoteStreamKey stream_key,
    IVideoSink* video_sink,
    IVideoSink::PixelFormat required_format)
```
将远端视频流与自定义渲染器绑定。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stream_key | **RemoteStreamKey** | 远端流信息，用于指定需要渲染的视频流来源及属性，参看 [RemoteStreamKey](Windows-keytype.md#remotestreamkey)。 |
| video_sink | **IVideoSink*** | 自定义视频渲染器，参看 [IVideoSink](Windows-keytype.md#ivideosink)。 |
| required_format | **IVideoSink::PixelFormat** | video_sink 适用的视频帧编码格式，参看 [PixelFormat](Windows-keytype.md#pixelformat)。 |


**注意**

+ RTC SDK 默认使用 RTC SDK 自带的渲染器（内部渲染器）进行视频渲染。
+ 该方法进房前后均可以调用。若想在进房前调用，你需要在加入房间前获取远端流信息；若无法预先获取远端流信息，你可以在加入房间并通过 [onUserPublishStream](Windows-callback.md#IRTCRoomEventHandler-onuserpublishstream) 回调获取到远端流信息之后，再调用该方法。
+ 如果需要解除绑定，必须将 video_sink 设置为 null。退房时将清除绑定状态。


<span id="IRTCVideo-pushscreenframe"></span>
### pushScreenFrame
```cpp
virtual bool bytertc::IRTCVideo::pushScreenFrame(
    IVideoFrame* frame)
```
推送屏幕视频帧

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| frame | **IVideoFrame*** | 设置屏幕视频帧，详见：[IVideoFrame](Windows-keytype.md#ivideoframe)。 |

**返回值**

+ true: 成功；  
+ false: 失败；  


**注意**

+ 暂时只支持 YUV420P 格式的视频帧。  
+ 该函数运行在用户调用线程内，即将销毁 IRTCVideo 实例前，请停止调用该函数推送屏幕共享数据  


<span id="IRTCVideo-updatescreencaptureregion"></span>
### updateScreenCaptureRegion
```cpp
virtual void bytertc::IRTCVideo::updateScreenCaptureRegion(
    const Rectangle& region_rect)
```
通过 RTC SDK 提供的采集模块采集屏幕视频流时，更新采集区域。<br>
仅用于采集源为显示器屏幕时。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| region_rect | **const Rectangle&** | 采集区域。参见 [Rectangle](Windows-keytype.md#rectangle)  <br/>此参数描述了调用此接口后的采集区域，和 [startScreenVideoCapture](#IRTCVideo-startscreenvideocapture) 中 `source_info` 设定区域的相对关系。 |


**注意**
调用此接口前，必须已通过调用 [startScreenVideoCapture](#IRTCVideo-startscreenvideocapture) 开启了内部屏幕流采集。

<span id="IRTCVideo-startscreenvideocapture"></span>
### startScreenVideoCapture
```cpp
virtual int bytertc::IRTCVideo::startScreenVideoCapture(
    const ScreenCaptureSourceInfo& source_info,
    const ScreenCaptureParameters& capture_params)
```
采集屏幕视频流，用于共享。屏幕视频流包括：屏幕上显示的内容，应用窗口中显示的内容，或虚拟屏幕中显示的内容。<br>
其中，虚拟屏幕中显示的内容仅在 Windows 平台上支持。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| source_info | **const ScreenCaptureSourceInfo&** | 待共享的屏幕源，参看 [ScreenCaptureSourceInfo](Windows-keytype.md#screencapturesourceinfo)。<br/>你可以调用 [getScreenCaptureSourceList](#IRTCVideo-getscreencapturesourcelist) 获得所有可以共享的屏幕源。 |
| capture_params | **const ScreenCaptureParameters&** | 共享参数。参看 [ScreenCaptureParameters](Windows-keytype.md#screencaptureparameters)。 |

**返回值**

+ 0: 成功  
+ -1: 失败  


**注意**

+ 调用此方法仅开启屏幕流视频采集，不会发布采集到的视频。发布屏幕流视频需要调用 [publishScreen](#IRTCRoom-publishscreen)。
+ 调用 [stopScreenVideoCapture](#IRTCVideo-stopscreenvideocapture) 关闭屏幕视频源采集。  
+ 本地用户通过 [onVideoDeviceStateChanged](Windows-callback.md#IRTCVideoEventHandler-onvideodevicestatechanged) 的回调获取屏幕采集状态，包括开始、暂停、恢复、错误等。  
+ 调用成功后，本端会收到 [onFirstLocalVideoFrameCaptured](Windows-callback.md#IRTCVideoEventHandler-onfirstlocalvideoframecaptured) 回调。  
+ 调用此接口前，你可以调用 [setScreenVideoEncoderConfig](#IRTCVideo-setscreenvideoencoderconfig) 设置屏幕视频流的采集帧率和编码分辨率。  
+ 在收到 [onFirstLocalVideoFrameCaptured](Windows-callback.md#IRTCVideoEventHandler-onfirstlocalvideoframecaptured) 回调后通过调用 [setLocalVideoCanvas](#IRTCVideo-setlocalvideocanvas) 或 [setLocalVideoSink](#IRTCVideo-setlocalvideosink) 函数设置本地屏幕共享视图。  
+ 可以调用 [setLocalVideoSink](#IRTCVideo-setlocalvideosink) 将本地视频流与自定义渲染器绑定，通过回调 [onFrame](Windows-keytype.md#IVideoSink-onframe) 获取采集成功的本地视频帧。 
+ 再开启采集屏幕视频流后，你可以调用 updateScreenCaptureHighlightConfig[updatescreencapturehighlightconfig](#updatescreencapturehighlightconfig)更新边框高亮设置，调用 updateScreenCaptureMouseCursor[updatescreencapturemousecursor](#updatescreencapturemousecursor)更新对鼠标的处理设置，调用 updateScreenCaptureFilterConfig[updatescreencapturefilterconfig](#updatescreencapturefilterconfig)设置需要过滤的窗口。  


<span id="IRTCVideo-stopscreenvideocapture"></span>
### stopScreenVideoCapture
```cpp
virtual void bytertc::IRTCVideo::stopScreenVideoCapture()
```
停止屏幕视频流采集。


**注意**

+ 要开启屏幕视频流采集，调用 [startScreenVideoCapture](#IRTCVideo-startscreenvideocapture)。  
+ 调用后，本地用户会收到 [onVideoDeviceStateChanged](Windows-callback.md#IRTCVideoEventHandler-onvideodevicestatechanged) 的回调。  
+ 调用此接口不影响屏幕视频流发布。


<span id="IRTCVideo-updatescreencapturehighlightconfig"></span>
### updateScreenCaptureHighlightConfig
```cpp
virtual void bytertc::IRTCVideo::updateScreenCaptureHighlightConfig(
    const HighlightConfig& highlight_config)
```
通过 RTC SDK 提供的采集模块采集屏幕视频流时，更新边框高亮设置。默认展示表框。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| highlight_config | **const HighlightConfig&** | 边框高亮设置。参见 [HighlightConfig](Windows-keytype.md#highlightconfig) |


**注意**
调用此接口前，必须已通过调用 [startScreenVideoCapture](#IRTCVideo-startscreenvideocapture) 开启了内部屏幕流采集。

<span id="IRTCVideo-updatescreencapturemousecursor"></span>
### updateScreenCaptureMouseCursor
```cpp
virtual void bytertc::IRTCVideo::updateScreenCaptureMouseCursor(
    MouseCursorCaptureState capture_mouse_cursor)
```
通过 RTC SDK 提供的采集模块采集屏幕视频流时，更新对鼠标的处理设置。默认采集鼠标。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| capture_mouse_cursor | **MouseCursorCaptureState** | 参看 [MouseCursorCaptureState](Windows-keytype.md#mousecursorcapturestate) |


**注意**
调用此接口前，必须已通过调用 [startScreenVideoCapture](#IRTCVideo-startscreenvideocapture) 开启了内部屏幕流采集。

<span id="IRTCVideo-updatescreencapturefilterconfig"></span>
### updateScreenCaptureFilterConfig
```cpp
virtual void bytertc::IRTCVideo::updateScreenCaptureFilterConfig(
    const ScreenFilterConfig& filter_config)
```
通过 RTC SDK 提供的采集模块采集屏幕视频流时，设置需要过滤的窗口。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| filter_config | **const ScreenFilterConfig&** | 窗口过滤设置，参看 [ScreenFilterConfig](Windows-keytype.md#screenfilterconfig) |


**注意**

+ 调用此接口前，必须已通过调用 [startScreenVideoCapture](#IRTCVideo-startscreenvideocapture) 开启了内部屏幕流采集。
+ 本函数在屏幕源类别是屏幕而非应用窗体时才起作用。详见：[ScreenCaptureSourceType](Windows-keytype.md#screencapturesourcetype)


<span id="IRTCVideo-getscreencapturesourcelist"></span>
### getScreenCaptureSourceList
```cpp
virtual IScreenCaptureSourceList* bytertc::IRTCVideo::getScreenCaptureSourceList()
```
获取共享对象列表。使用完之后需要调用 [release](#IScreenCaptureSourceList-release) 接口释放。

**返回值**
共享对象列表，包括应用窗口和屏幕。详见 [IScreenCaptureSourceList](#iscreencapturesourcelist)。由用户选择其中一个共享对象，并在调用 [startScreenVideoCapture](#IRTCVideo-startscreenvideocapture) 时作为参数传给 RTC SDK。


<span id="IRTCVideo-getthumbnail"></span>
### getThumbnail
```cpp
virtual IVideoFrame* bytertc::IRTCVideo::getThumbnail(
    ScreenCaptureSourceType type,
    view_t source_id,
    int max_width,
    int max_height)
```
获取共享对象缩略图

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| type | **ScreenCaptureSourceType** | 屏幕采集对象的类型。详见 [ScreenCaptureSourceType](Windows-keytype.md#screencapturesourcetype)。 |
| source_id | **view_t** | 屏幕共享对象的 ID，可通过 [getScreenCaptureSourceList](#IRTCVideo-getscreencapturesourcelist) 枚举共享对象列表中获取。详见 [view_t](Windows-keytype.md#view_t) |
| max_width | **int** | 最大宽度。保持采集对象本身的宽高比不变，将缩略图缩放到指定范围内的最大宽高。如果给出的尺寸与共享对象比例不同，得到的缩略图会有黑边。 |
| max_height | **int** | 最大高度。参见 max_width 的说明。 |

**返回值**
共享对象缩略图，详见 [IVideoFrame](Windows-keytype.md#ivideoframe)。


<span id="IRTCVideo-getwindowappicon"></span>
### getWindowAppIcon
```cpp
virtual IVideoFrame* bytertc::IRTCVideo::getWindowAppIcon(
    view_t source_id,
    int max_width)
```
获取应用窗体所属应用的图标。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| source_id | **view_t** | 屏幕共享对象的 ID，可通过 [getScreenCaptureSourceList](#IRTCVideo-getscreencapturesourcelist) 枚举共享对象列表中获取。详见 [view_t](Windows-keytype.md#view_t) |
| max_width | **int** | 最大宽度。返回的图标将是宽高相等的，输入宽高不等时，取二者较小值。宽高范围为 [32,256]，超出该范围将返回 nullptr，默认输出 100 x 100 的图像。 |
| max_height | **int** | 最大高度。参见 max_width 的说明。 |

**返回值**
详见 [IVideoFrame](Windows-keytype.md#ivideoframe)。当屏幕共享对象为应用窗体时有效，否则返回 nullptr。


<span id="IRTCVideo-setvideosourcetype"></span>
### setVideoSourceType
```cpp
virtual void bytertc::IRTCVideo::setVideoSourceType(
    StreamIndex stream_index,
    VideoSourceType type)
```
设置向 SDK 输入的视频源，包括屏幕流
默认使用内部采集。内部采集指：使用 RTC SDK 内置的视频采集机制进行视频采集。 <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stream_index | **StreamIndex** | 视频流的属性，参看 [StreamIndex](Windows-keytype.md#streamindex) |
| type | **VideoSourceType** | 视频输入源类型，参看 [VideoSourceType](Windows-keytype.md#videosourcetype) |


**注意**

+ 该方法进房前后均可调用。  
+ 当你已调用 [startVideoCapture](#IRTCVideo-startvideocapture) 开启内部采集后，再调用此方法切换至自定义采集时，SDK 会自动关闭内部采集。  
+ 当你调用此方法开启自定义采集后，想要切换至内部采集，你必须先调用此方法关闭自定义采集，然后调用 [startVideoCapture](#IRTCVideo-startvideocapture) 手动开启内部采集。  
+ 当你需要向 SDK 推送自定义编码后的视频帧，你需调用该方法将视频源切换至自定义编码视频源。


<span id="IRTCVideo-pushexternalvideoframe"></span>
### pushExternalVideoFrame
```cpp
virtual bool bytertc::IRTCVideo::pushExternalVideoFrame(
    IVideoFrame* frame)
```
发送外部源视频数据

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| frame | **IVideoFrame*** | 设置视频帧，参看 [IVideoFrame](Windows-keytype.md#ivideoframe)。 |


**注意**

+ 支持格式：I420, NV12, RGBA, BGRA, ARGB  
+ 该函数运行在用户调用线程内  
+ 推送外部视频帧前，必须调用 [setVideoSourceType](#IRTCVideo-setvideosourcetype) 开启外部视频源采集。


<span id="IRTCVideo-creatertcroom"></span>
### createRTCRoom
```cpp
virtual IRTCRoom* bytertc::IRTCVideo::createRTCRoom(
    const char* room_id)
```
创建房间实例。
调用此方法仅返回一个房间实例，你仍需调用 [joinRoom](#IRTCRoom-joinroom) 才能真正地创建/加入房间。
多次调用此方法以创建多个 [IRTCRoom](#irtcroom) 实例。分别调用各 IRTCRoom 实例中的 [joinRoom](#IRTCRoom-joinroom) 方法，同时加入多个房间。
多房间模式下，用户可以同时订阅各房间的音视频流。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| room_id | **const char*** | 标识通话房间的房间 ID，最大长度为 128 字节的非空字符串。支持的字符集范围为:  <br/>• 26 个大写字母 A ~ Z； <br/>• 26 个小写字母 a ~ z； <br/>• 10 个数字 0 ~ 9；  <br/>• 下划线 "_", at 符 "@", 减号 "-"。 |

**返回值**
创建的 [IRTCRoom](#irtcroom) 房间实例。


**注意**

+ 如果需要加入的房间已存在，你仍需先调用本方法来获取 IRTCRoom 实例，再调用 [joinRoom](#IRTCRoom-joinroom) 加入房间。
+ 请勿使用同样的 roomId 创建多个房间，否则后创建的房间实例会替换先创建的房间实例。
+ 如果你需要在多个房间发布音视频流，无须创建多房间，直接调用 [startForwardStreamToRooms](#IRTCRoom-startforwardstreamtorooms) 开始跨房间转发媒体流。


<span id="IRTCVideo-setpublishfallbackoption"></span>
### setPublishFallbackOption
```cpp
virtual int bytertc::IRTCVideo::setPublishFallbackOption(
    PublishFallbackOption option)
```
设置发布的音视频流的回退选项。  <br>
你可以调用该接口设置网络不佳或设备性能不足时从大流起进行降级处理，以保证通话质量。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| option | **PublishFallbackOption** | 本地发布的音视频流回退选项，参看 [PublishFallbackOption](Windows-keytype.md#publishfallbackoption)。 |

**返回值**
方法调用结果： 

+ 0：成功  
+ < 0：失败


**注意**

+ 该方法仅在调用 [enableSimulcastMode](#IRTCVideo-enablesimulcastmode) 开启了发送多路视频流的情况下生效。  
+ 该方法必须在进房前设置，进房后设置或更改设置无效。  
+ 设置回退后，本地发布的音视频流发生回退或从回退中恢复时，远端会收到 [onSimulcastSubscribeFallback](Windows-callback.md#IRTCVideoEventHandler-onsimulcastsubscribefallback) 回调通知。  
+ 你可以调用客户端 API 或者在服务端下发策略设置回退。当使用服务端下发配置实现时，下发配置优先级高于在客户端使用 API 设定的配置。


<span id="IRTCVideo-setsubscribefallbackoption"></span>
### setSubscribeFallbackOption
```cpp
virtual int bytertc::IRTCVideo::setSubscribeFallbackOption(
    SubscribeFallbackOption option)
```
设置订阅的音视频流的回退选项。 <br>
你可调用该接口设置网络不佳或设备性能不足时允许订阅流进行降级或只订阅音频流，以保证通话流畅。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| option | **SubscribeFallbackOption** | 订阅的音视频流回退选项，参看 [SubscribeFallbackOption](Windows-keytype.md#subscribefallbackoption) 。 |

**返回值**
方法调用结果： 

+ 0：成功  
+ < 0：失败


**注意**

+ 你必须在进房前设置，进房后设置或更改设置无效。  
+ 设置回退选项后，订阅的音视频流发生回退或从回退中恢复时，会收到 [onSimulcastSubscribeFallback](Windows-callback.md#IRTCVideoEventHandler-onsimulcastsubscribefallback) 和 [onRemoteVideoSizeChanged](Windows-callback.md#IRTCVideoEventHandler-onremotevideosizechanged) 回调通知。  
+ 你可以调用 API 或者在服务端下发策略设置回退。当使用服务端下发配置实现时，下发配置优先级高于在客户端使用 API 设定的配置。


<span id="IRTCVideo-setremoteuserpriority"></span>
### setRemoteUserPriority
```cpp
virtual int bytertc::IRTCVideo::setRemoteUserPriority(
    const char* room_id,
    const char* user_id,
    RemoteUserPriority priority)
```
设置用户优先级

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| room_id | **const char*** | 房间 ID |
| user_id | **const char*** | 远端用户的 ID |
| priority | **RemoteUserPriority** | 远端用户的需求优先级，详见枚举类型[RemoteUserPriority](Windows-keytype.md#remoteuserpriority) |

**返回值**
0: 方法调用成功  

+ < 0: 方法调用失败  


**注意**

+ 1. 该方法与 [setSubscribeFallbackOption](#IRTCVideo-setsubscribefallbackoption) 搭配使用。  
+ 2. 如果开启了订阅流回退选项，弱网或性能不足时会优先保证收到的高优先级用户的流的质量。  
+ 3. 该方法在进房前后都可以使用，可以修改远端用户的优先级。  


<span id="IRTCVideo-setbusinessid"></span>
### setBusinessId
```cpp
virtual int bytertc::IRTCVideo::setBusinessId(
    const char* business_id)
```
设置业务标识参数  <br>
可通过 businessId 区分不同的业务场景。businessId 由客户自定义，相当于一个“标签”，可以分担和细化现在 AppId 的逻辑划分的功能，但不需要鉴权。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| business_id | **const char*** | 用户设置的自己的 businessId 值<br/>businessId 只是一个标签，颗粒度需要用户自定义。 |

**返回值**

+ 0： 成功  
+ < 0： 失败，具体原因参照 [BusinessCheckCode](Windows-keytype.md#businesscheckcode) 。  
+ -6001： 用户已经在房间中。  
+ -6002： 输入非法，合法字符包括所有小写字母、大写字母和数字，除此外还包括四个独立字符，分别是：英文句号，短横线，下划线和 @ 。


**注意**

+ 需要在调用 [joinRoom](#IRTCRoom-joinroom) 之前调用，[joinRoom](#IRTCRoom-joinroom)之后调用该方法无效。


<span id="IRTCVideo-setlocalvideomirrortype"></span>
### setLocalVideoMirrorType
```cpp
virtual void bytertc::IRTCVideo::setLocalVideoMirrorType(
    MirrorType mirrorType)
```
为采集到的视频流开启镜像

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mirrorType | **MirrorType** | 镜像类型，参看 [MirrorType](Windows-keytype.md#mirrortype) |


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


<span id="IRTCVideo-getvideoeffectinterface"></span>
### getVideoEffectInterface
```cpp
virtual IVideoEffect* bytertc::IRTCVideo::getVideoEffectInterface()
```
获取视频特效接口

**返回值**
视频特效接口指针，参看 [IVideoEffect](#ivideoeffect)


<span id="IRTCVideo-enableeffectbeauty"></span>
### enableEffectBeauty
```cpp
virtual int bytertc::IRTCVideo::enableEffectBeauty(
    bool enable)
```
开启/关闭基础美颜

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| enable | **bool** | 基础美颜开关 <br/>• true: 开启基础美颜 <br/>• false: 关闭基础美颜（默认） |

**返回值**

+ 0: 开启/关闭成功。 
+ 1000: 未集成特效 SDK。 
+ 1001: RTC SDK 版本不支持此功能。 
+ 1002: 特效 SDK 当前版本不支持此功能，建议使用特效 SDK V4.3.1 版本。 
+ 1003: 联系技术支持人员。 
+ 1004: 正在下载相关资源，下载完成后生效。 
+ <0: 调用失败，特效 SDK 内部错误，具体错误码请参考[错误码表](https://www.volcengine.com/docs/6705/102042)。  


**注意**

+ 本方法不能与高级视频特效接口共用。如已购买高级视频特效，建议调用 [enableEffect](#IVideoEffect-enableeffect) 使用高级特效、贴纸功能等。 
+ 使用此功能需要集成特效 SDK，建议使用特效 SDK V4.3.1+ 版本。 
+ 调用 [setBeautyIntensity](#IRTCVideo-setbeautyintensity) 设置基础美颜强度。若在调用本方法前没有设置美颜强度，则初始美白、磨皮、锐化强度均为 0.5。 
+ 本方法仅适用于视频源，不适用于屏幕源。 


<span id="IRTCVideo-setbeautyintensity"></span>
### setBeautyIntensity
```cpp
virtual int bytertc::IRTCVideo::setBeautyIntensity(
    EffectBeautyMode beauty_mode,
    float intensity)
```
调整基础美颜强度

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| beauty_mode | **EffectBeautyMode** | 基础美颜模式，参看 [EffectBeautyMode](Windows-keytype.md#effectbeautymode)。 |
| intensity | **float** | 美颜强度，取值范围为 [0,1]。强度为 0 表示关闭，默认强度为 0.5。 |

**返回值**

+ 0: 开启成功。 
+ 1000: 未集成特效 SDK。 
+ 1001: RTC SDK 版本不支持此功能。 
+ <0: 调用失败，特效 SDK 内部错误，具体错误码请参考[错误码表](https://www.volcengine.com/docs/6705/102042)。  


**注意**

+ 若在调用 [enableEffectBeauty](#IRTCVideo-enableeffectbeauty) 前设置美颜强度，则对应美颜功能的强度初始值会根据设置更新。 
+ 销毁引擎后，美颜功能强度恢复默认值。


<span id="IRTCVideo-setencryptinfo"></span>
### setEncryptInfo
```cpp
virtual void bytertc::IRTCVideo::setEncryptInfo(
    EncryptType encrypt_type,
    const char* key,
    int key_size)
```
设置传输时使用内置加密的方式 <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| encrypt_type | **EncryptType** | 加密类型，详见 [EncryptType](Windows-keytype.md#encrypttype) |
| key | **const char*** | 加密密钥，长度限制为 36 位，超出部分将会被截断 |
| key_size | **int** | 参数 key 的长度 |


**注意**

+ 使用传输时内置加密时，使用此方法；如果需要使用传输时自定义加密，参看 [onEncryptData](Windows-callback.md#IEncryptHandler-onencryptdata)。 内置加密和自定义加密互斥，根据最后一个调用的方法确定传输是加密的方案。  
+ 该方法必须在进房之前调用，可重复调用，以最后调用的参数作为生效参数。  


<span id="IRTCVideo-setcustomizeencrypthandler"></span>
### setCustomizeEncryptHandler
```cpp
virtual void bytertc::IRTCVideo::setCustomizeEncryptHandler(
    IEncryptHandler* handler)
```
设置自定义加密  <br>
需要实现对应的加密/解密方法，详情参考 [EncryptType](Windows-keytype.md#encrypttype) 。 <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| handler | **IEncryptHandler*** | 自定义加密 handler，需要实现 handler 的加密和解密方法 |


**注意**

+ 该方法与 [setEncryptInfo](#IRTCVideo-setencryptinfo) 为互斥关系，只能选择自定义加密方式或者默认加密方式。最终生效的加密方式取决于最后一个调用的方法。  
+ 该方法必须在进房之前调用，可重复调用，以最后调用的参数作为生效参数。  
+ 无论加密或者解密，其对原始数据的长度修改，需要控制在 90% ~ 120% 之间，即如果输入数据为 100 字节，则处理完成后的数据必须在 90 至 120 字节之间，如果加密或解密结果超出该长度限制，则该音视频帧会被丢弃。  
+ 数据加密/解密为串行执行，因而视实现方式不同，可能会影响到最终渲染效率。是否使用该方法，需要由使用方谨慎评估。



<span id="IRTCVideo-enableaudioframecallback"></span>
### enableAudioFrameCallback
```cpp
virtual void bytertc::IRTCVideo::enableAudioFrameCallback(
    AudioFrameCallbackMethod method,
    AudioFormat format)
```
设置并开启指定的音频数据帧回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| method | **AudioFrameCallbackMethod** | 音频回调方法，参看 [AudioFrameCallbackMethod](Windows-keytype.md#audioframecallbackmethod)。  <br/>当音频回调方法设置为 `kAudioFrameCallbackRecord`、`kAudioFrameCallbackPlayback`、`kAudioFrameCallbackMixed`、`kAudioFrameCallbackRecordScreen`时，你需要在参数 `format` 中指定准确的采样率和声道，暂不支持设置为自动。  <br/>当音频回调方法设置为 `kAudioFrameCallbackRemoteUser`时，暂不支持音频参数格式中设置准确的采样率和声道，你需要设置为自动。 |
| format | **AudioFormat** | 音频参数格式，参看 [AudioFormat](Windows-keytype.md#audioformat)。 |


**注意**
开启音频回调并调用 [registerAudioFrameObserver](#IRTCVideo-registeraudioframeobserver) 后，[IAudioFrameObserver](Windows-callback.md#iaudioframeobserver) 会收到对应的音频回调。两者调用顺序没有限制且相互独立。  

<span id="IRTCVideo-disableaudioframecallback"></span>
### disableAudioFrameCallback
```cpp
virtual void bytertc::IRTCVideo::disableAudioFrameCallback(
    AudioFrameCallbackMethod method)
```
关闭音频回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| method | **AudioFrameCallbackMethod** | 音频回调方法，参看 [AudioFrameCallbackMethod](Windows-keytype.md#audioframecallbackmethod)。 |


**注意**
该方法需要在调用 [enableAudioFrameCallback](#IRTCVideo-enableaudioframecallback) 之后调用。

<span id="IRTCVideo-registeraudioframeobserver"></span>
### registerAudioFrameObserver
```cpp
virtual void bytertc::IRTCVideo::registerAudioFrameObserver(
    IAudioFrameObserver* observer)
```
注册音频数据回调观察者。  <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| observer | **IAudioFrameObserver*** | 音频数据观察者，参看 [IAudioFrameObserver](Windows-callback.md#iaudioframeobserver)。如果传入 null，则取消注册。 |

**返回值**

+ 0: 方法调用成功 
+ < 0: 方法调用失败 


**注意**
注册音频数据回调观察者并调用 [enableAudioFrameCallback](#IRTCVideo-enableaudioframecallback) 后，[IAudioFrameObserver](Windows-callback.md#iaudioframeobserver) 会收到对应的音频回调。

<span id="IRTCVideo-registeraudioprocessor"></span>
### registerAudioProcessor
```cpp
virtual void bytertc::IRTCVideo::registerAudioProcessor(
    IAudioFrameProcessor* processor)
```
注册自定义音频处理器。<br>
注册完成后，你可以调用 [enableAudioProcessor](#IRTCVideo-enableaudioprocessor)，对本地采集或接收到的远端音频进行处理。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| processor | **IAudioFrameProcessor*** | 自定义音频处理器，详见 [IAudioFrameProcessor](Windows-callback.md#iaudioframeprocessor)。<br/>SDK 只持有 processor 的弱引用，你应保证其生命周期。 |


**注意**
重复调用此接口时，仅最后一次调用生效。

<span id="IRTCVideo-enableaudioprocessor"></span>
### enableAudioProcessor
```cpp
virtual void bytertc::IRTCVideo::enableAudioProcessor(
    AudioProcessorMethod method,
    AudioFormat format)
```
设置并开启指定的音频帧回调，进行自定义处理。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| method | **AudioProcessorMethod** | 音频帧类型，参看 [AudioProcessorMethod](Windows-keytype#audioprocessormethod)。可多次调用此接口，处理不同类型的音频帧。<br/>选择不同类型的音频帧将收到对应的回调：  <br/>• 选择本地采集的音频时，会收到 [onProcessRecordAudioFrame](Windows-callback.md#IAudioFrameProcessor-onprocessrecordaudioframe)。  <br/>• 选择远端音频流的混音音频时，会收到 [onProcessPlayBackAudioFrame](Windows-callback.md#IAudioFrameProcessor-onprocessplaybackaudioframe)。  <br/>• 选择远端音频流时，会收到 [onProcessRemoteUserAudioFrame](Windows-callback.md#IAudioFrameProcessor-onprocessremoteuseraudioframe)。  <br/>• 选择屏幕共享音频流时，会收到 [onProcessScreenAudioFrame](Windows-callback.md#IAudioFrameProcessor-onprocessscreenaudioframe)。（Linux 不适用） |
| format | **AudioFormat** | 设定自定义处理时获取的音频帧格式，参看 [AudioFormat](Windows-keytype.md#audioformat)。 |


**注意**

+ 在调用此接口前，你需要调用 [registerAudioProcessor](#IRTCVideo-registeraudioprocessor) 注册自定义音频处理器。
+ 要关闭音频自定义处理，调用 [disableAudioProcessor](#IRTCVideo-disableaudioprocessor)。


<span id="IRTCVideo-disableaudioprocessor"></span>
### disableAudioProcessor
```cpp
virtual void bytertc::IRTCVideo::disableAudioProcessor(
    AudioProcessorMethod method)
```
关闭自定义音频处理。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| method | **AudioProcessorMethod** | 音频帧类型，参看 [AudioProcessorMethod](Windows-keytype.md#audioprocessormethod)。 |


<span id="IRTCVideo-registerlocalvideoprocessor"></span>
### registerLocalVideoProcessor
```cpp
virtual int bytertc::IRTCVideo::registerLocalVideoProcessor(
    IVideoProcessor* processor,
    VideoPreprocessorConfig config)
```
设置自定义视频前处理器。<br>
使用这个视频前处理器，你可以调用 [processVideoFrame](#IVideoProcessor-processvideoframe) 对 RTC SDK 采集得到的视频帧进行前处理，并将处理后的视频帧用于 RTC 音视频通信。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| processor | **IVideoProcessor*** | 自定义视频处理器，详见 [IVideoProcessor](#ivideoprocessor)。如果传入 null，则不对 RTC SDK 采集得到的视频帧进行前处理。<br/>SDK 只持有 processor 的弱引用，你应保证其生命周期。 |
| config | **VideoPreprocessorConfig** | 自定义视频前处理器适用的设置，详见 [VideoPreprocessorConfig](Windows-keytype.md#videopreprocessorconfig)。<br/>当前，`config` 中的 `required_pixel_format` 仅支持：`kVideoPixelFormatI420` 和 `kVideoPixelFormatUnknown`：<br/>• 设置为 `kVideoPixelFormatUnknown` 时，RTC SDK 给出供 processor 处理的视频帧格式即采集的格式。<br/>你可以通过 [VideoFrameType](Windows-keytype.md#videoframetype) 和 [VideoPixelFormat](Windows-keytype.md#videopixelformat) 获取实际采集的视频帧格式和像素类型。<br/>• 设置为 `kVideoPixelFormatI420` 时，RTC SDK 会将采集得到的视频帧转变为对应的格式，供前处理使用。<br/>• 设置为其他值时，此方法调用失败。 |

**返回值**

+ 0：方法调用成功 
+ !0：方法调用失败 


**注意**

+ 对于 Windows 平台，经前处理返回的视频帧格式仅支持 `kVideoPixelFormatI420` 
+ 对于 Windows 平台，将 `config` 中的 required_pixel_format 设置为 `kVideoPixelFormatI420`，可以通过避免格式转换带来一些性能优化。
+ 重复调用此接口时，仅最后一次调用生效。效果不会叠加。


<span id="IRTCVideo-sendseimessage"></span>
### sendSEIMessage
```cpp
virtual int bytertc::IRTCVideo::sendSEIMessage(
    StreamIndex stream_index,
    const uint8_t* message,
    int length,
    int repeat_count)
```
通过视频帧发送 SEI 数据。  <br>
在视频通话场景下，SEI 数据会随视频帧发送；在语音通话场景下，SDK 会自动生成一路 16px × 16px 的黑帧视频流用来发送 SEI 数据。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stream_index | **StreamIndex** | 指定携带 SEI 数据的媒体流类型，参看 [StreamIndex](Windows-keytype.md#streamindex)。  <br/>语音通话场景下，该值需设为 `kStreamIndexMain`，否则 SEI 数据会被丢弃从而无法送达远端。 |
| message | **const uint8_t*** | SEI 消息。 |
| length | **int** | SEI 消息长度，不超过 4KB。 |
| repeat_count | **int** | 消息发送重复次数。取值范围是 [0, max{29, %{视频帧率}-1}]。推荐范围 [2,4]。<br/>调用此接口后，SEI 数据会添加到从当前视频帧开始的连续 `repeat_count` 个视频帧中。 |

**返回值**

+ \>=0: 将被添加到视频帧中的 SEI 的数量  
+ <0: 发送失败


**注意**

+ 每秒发送的 SEI 消息数量建议不超过当前的视频帧率。在语音通话场景下，黑帧帧率为 15 fps。
+ 语音通话场景中，仅支持在内部采集模式下调用该接口发送 SEI 数据。
+ 视频帧仅携带前后 2s 内收到的 SEI 数据；语音通话场景下，若调用此接口后 1min 内未有 SEI 数据发送，则 SDK 会自动取消发布视频黑帧。  
+ 消息发送成功后，远端会收到 [onSEIMessageReceived](Windows-callback.md#IRTCVideoEventHandler-onseimessagereceived) 回调。
+ 视频通话场景中，使用自定义采集并通过 pushExternalVideoFrame 推送至 SDK 的视频帧，若本身未携带 SEI 数据，也可通过本接口发送 SEI 数据。
+ 语音通话切换至视频通话时，会停止 SEI 数据发送，你需再次调用该接口方可恢复发送。


<span id="IRTCVideo-getvideodevicemanager"></span>
### getVideoDeviceManager
```cpp
virtual IVideoDeviceManager* bytertc::IRTCVideo::getVideoDeviceManager()
```
创建视频设备管理实例

**返回值**
视频设备管理实例，详见[IVideoDeviceManager](#ivideodevicemanager)


<span id="IRTCVideo-getaudiodevicemanager"></span>
### getAudioDeviceManager
```cpp
virtual IAudioDeviceManager* bytertc::IRTCVideo::getAudioDeviceManager()
```
设备音频管理接口创建

**返回值**
音频设备管理接口


<span id="IRTCVideo-startfilerecording"></span>
### startFileRecording
```cpp
virtual int bytertc::IRTCVideo::startFileRecording(
    StreamIndex type,
    RecordingConfig config,
    RecordingType recording_type)
```
该方法将通话过程中的音视频数据录制到本地的文件中。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| type | **StreamIndex** | 流属性，指定录制主流还是屏幕流，参看 [StreamIndex](Windows-keytype.md#streamindex) |
| config | **RecordingConfig** | 本地录制参数配置，参看 [RecordingConfig](Windows-keytype.md#recordingconfig) |
| recording_type | **RecordingType** | 本地录制的媒体类型，参看 [RecordingType](Windows-keytype.md#recordingtype) |

**返回值**

+ 0: 正常
+ -1: 参数设置异常
+ -2: 当前版本 SDK 不支持该特性，请联系技术支持人员


**注意**

+ 调用该方法后，你会收到 [onRecordingStateUpdate](Windows-callback.md#IRTCVideoEventHandler-onrecordingstateupdate) 回调。  
+ 如果录制正常，系统每秒钟会通过 [onRecordingProgressUpdate](Windows-callback.md#IRTCVideoEventHandler-onrecordingprogressupdate) 回调通知录制进度。
+ 你需要在成功发流后才可以调用该方法进行录制。


<span id="IRTCVideo-stopfilerecording"></span>
### stopFileRecording
```cpp
virtual void bytertc::IRTCVideo::stopFileRecording(
    StreamIndex type)
```
停止本地录制

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| type | **StreamIndex** | 流属性，指定停止主流或者屏幕流录制，参看 [StreamIndex](Windows-keytype.md#streamindex) |


**注意**

+ 调用 [startFileRecording](#IRTCVideo-startfilerecording) 开启本地录制后，你必须调用该方法停止录制。  
+ 调用该方法后，你会收到 [onRecordingStateUpdate](Windows-callback.md#IRTCVideoEventHandler-onrecordingstateupdate) 回调提示录制结果。


<span id="IRTCVideo-enableexternalsoundcard"></span>
### enableExternalSoundCard
```cpp
virtual void bytertc::IRTCVideo::enableExternalSoundCard(
    bool enable)
```
启用匹配外置声卡的音频处理模式

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| enable | **bool** | • true: 开启 <br/>• false: 不开启(默认) |


**注意**

+ 当采用外接声卡进行音频采集时，建议开启此模式，以获得更好的音质。
+ 开启此模式时，仅支持耳机播放。如果需要使用扬声器或者外置音箱播放，关闭此模式。


<span id="IRTCVideo-setruntimeparameters"></span>
### setRuntimeParameters
```cpp
virtual void bytertc::IRTCVideo::setRuntimeParameters(
    const char * json_string)
```
设置运行时的参数

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| json_string | **const char*** | json 序列化之后的字符串 |


**注意**
该接口需在 [joinRoom](#IRTCRoom-joinroom) 和 [startAudioCapture](#IRTCVideo-startaudiocapture) 之前调用。

<span id="IRTCVideo-feedback"></span>
### feedback
```cpp
virtual int bytertc::IRTCVideo::feedback(
    ProblemFeedbackOption *type,
    int count,
    const char* problem_desc)
```
将用户反馈的问题上报到 RTC

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| type | **ProblemFeedbackOption*** | 预设问题列表，参看 [ProblemFeedbackOption](Windows-keytype.md#problemfeedbackoption) |
| count | **int** | ProblemFeedbackOption 数组长度 |
| problem_desc | **const char*** | 预设问题以外的其他问题的具体描述 |

**返回值**

+ 0: 上报成功  
+ -1: 上报失败，还没加入过房间 
+ -2: 上报失败，数据解析错误  
+ -3: 上报失败，字段缺失  


**注意**
如果用户上报时在房间内，那么问题会定位到用户当前所在的一个或多个房间；如果用户上报时不在房间内，那么问题会定位到引擎此前退出的房间。


<span id="IRTCVideo-getaudiomixingmanager"></span>
### getAudioMixingManager
```cpp
virtual IAudioMixingManager* bytertc::IRTCVideo::getAudioMixingManager()
```
混音管理接口创建

**返回值**
混音管理实例，详见[IAudioMixingManager](#iaudiomixingmanager)


<span id="IRTCVideo-login"></span>
### login
```cpp
virtual int64_t bytertc::IRTCVideo::login(
    const char* token,
    const char* uid)
```
必须先登录，才能发送房间外点对点消息和向应用服务器发送消息<br>
在调用本接口登录后，如果想要登出，需要调用 [logout](#IRTCVideo-logout)。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| token | **const char*** | 用户登录必须携带的 Token，用于鉴权验证。<br/>测试时可使用[控制台](https://console.volcengine.com/rtc/listRTC)生成临时 Token，`roomId` 填任意值。<br/>正式上线需要使用密钥 SDK 在你的服务端生成并下发 Token，`roomId` 置空，Token 有效期及生成方式参看[使用 Token 完成鉴权](70121)。 |
| uid | **const char*** | 用户 ID  <br/>用户 ID 在 appid 的维度下是唯一的。 |

**返回值**

+ `0`：成功
+ `-1`：失败。无效参数
+ `-2`：无效调用。用户已经登录。成功登录后再次调用本接口将收到此返回值


**注意**
本地用户调用此方法登录后，会收到 [onLoginResult](Windows-callback.md#IRTCVideoEventHandler-onloginresult) 回调通知登录结果，远端用户不会收到通知。

<span id="IRTCVideo-logout"></span>
### logout
```cpp
virtual void bytertc::IRTCVideo::logout()
```
调用本接口登出后，无法调用房间外消息以及端到服务器消息相关的方法或收到相关回调。


**注意**

+ 调用本接口登出前，必须先调用 [login](#IRTCVideo-login) 登录。  
+ 本地用户调用此方法登出后，会收到 [onLogout](Windows-callback.md#IRTCVideoEventHandler-onlogout) 回调通知结果，远端用户不会收到通知。


<span id="IRTCVideo-updatelogintoken"></span>
### updateLoginToken
```cpp
virtual void bytertc::IRTCVideo::updateLoginToken(
    const char* token)
```
更新用户用于登录的 Token  <br>
Token 有一定的有效期，当 Token 过期时，需调用此方法更新登录的 Token 信息。  <br>
调用 [login](#IRTCVideo-login) 方法登录时，如果使用了过期的 Token 将导致登录失败，并会收到 [onLoginResult](Windows-callback.md#IRTCVideoEventHandler-onloginresult) 回调通知，错误码为 kLoginErrorCodeInvalidToken。此时需要重新获取 Token，并调用此方法更新 Token。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| token | **const char*** | 更新的动态密钥 |


**注意**

+ 如果 Token 无效导致登录失败，则调用此方法更新 Token 后，SDK 会自动重新登录，而用户不需要自己调用 [login](#IRTCVideo-login) 方法。  
+ Token 过期时，如果已经成功登录，则不会受到影响。Token 过期的错误会在下一次使用过期 Token 登录时，或因本地网络状况不佳导致断网重新登录时通知给用户。


<span id="IRTCVideo-setserverparams"></span>
### setServerParams
```cpp
virtual void bytertc::IRTCVideo::setServerParams(
    const char* signature,
    const char* url)
```
设置应用服务器参数  <br>
客户端调用 [sendServerMessage](#IRTCVideo-sendservermessage) 或 [sendServerBinaryMessage](#IRTCVideo-sendserverbinarymessage) 发送消息给应用服务器之前，必须设置有效签名和应用服务器地址。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| signature | **const char*** | 动态签名  <br/>应用服务器会使用该签名对请求进行鉴权验证。 |
| url | **const char*** | 应用服务器的地址 |


**注意**

+ 用户必须调用 [login](#IRTCVideo-login) 登录后，才能调用本接口。  
+ 调用本接口后，SDK 会使用 [onServerParamsSetResult](Windows-callback.md#IRTCVideoEventHandler-onserverparamssetresult) 返回相应结果。


<span id="IRTCVideo-getpeeronlinestatus"></span>
### getPeerOnlineStatus
```cpp
virtual void bytertc::IRTCVideo::getPeerOnlineStatus(
    const char* peer_user_id)
```
查询对端用户或本端用户的登录状态

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| peer_user_id | **const char*** | 需要查询的用户 ID |


**注意**

+ 必须调用 [login](#IRTCVideo-login) 登录后，才能调用本接口。  
+ 调用本接口后，SDK 会使用 [onGetPeerOnlineStatus](Windows-callback.md#IRTCVideoEventHandler-ongetpeeronlinestatus) 回调通知查询结果。  
+ 在发送房间外消息之前，用户可以通过本接口了解对端用户是否登录，从而决定是否发送消息。也可以通过本接口查询自己查看自己的登录状态。


<span id="IRTCVideo-sendusermessageoutsideroom"></span>
### sendUserMessageOutsideRoom
```cpp
virtual int64_t bytertc::IRTCVideo::sendUserMessageOutsideRoom(
    const char* uid,
    const char* message,
    MessageConfig config)
```
给房间外指定的用户发送文本消息（P2P）

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | **const char*** | 消息接收用户的 ID |
| message | **const char*** | 发送的文本消息内容  <br/>消息不超过 64 KB。 |
| config | **MessageConfig** | 消息类型，参看 [MessageConfig](Windows-keytype.md#messageconfig)。 |

**返回值**

+ \>0：发送成功，返回这次发送消息的编号，从 1 开始递增  
+ -1：发送失败，IRTCVideo 实例未创建  
+ -2：发送失败，uid 为空


**注意**

+ 在发送房间外文本消息前，必须先调用 [login](#IRTCVideo-login) 完成登录。  
+ 用户调用本接口发送文本信息后，会收到一次 [onUserMessageSendResultOutsideRoom](Windows-callback.md#IRTCVideoEventHandler-onusermessagesendresultoutsideroom) 回调，得知消息是否成功发送。  
+ 若文本消息发送成功，则 uid 所指定的用户会通过 [onUserMessageReceivedOutsideRoom](Windows-callback.md#IRTCVideoEventHandler-onusermessagereceivedoutsideroom) 回调收到该消息。


<span id="IRTCVideo-senduserbinarymessageoutsideroom"></span>
### sendUserBinaryMessageOutsideRoom
```cpp
virtual int64_t bytertc::IRTCVideo::sendUserBinaryMessageOutsideRoom(
    const char* uid,
    int length,
    const uint8_t* message,
    MessageConfig config)
```
给房间外指定的用户发送二进制消息（P2P）

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | **const char*** | 消息接收用户的 ID |
| length | **int** | 二进制字符串的长度 |
| message | **const uint8_t*** | 发送的二进制消息内容  <br/>消息不超过 64KB。 |
| config | **MessageConfig** | 消息类型，参看 [MessageConfig](Windows-keytype.md#messageconfig)。 |

**返回值**

+ \>0：发送成功，返回这次发送消息的编号，从 1 开始递增  
+ -1：发送失败，IRTCVideo 实例未创建  
+ -2：发送失败，uid 为空


**注意**

+ 在发送房间外二进制消息前，必须先调用 [login](#IRTCVideo-login) 完成登录。  
+ 用户调用本接口发送二进制消息后，会收到一次 [onUserMessageSendResultOutsideRoom](Windows-callback.md#IRTCVideoEventHandler-onusermessagesendresultoutsideroom) 回调，通知消息是否发送成功。  
+ 若二进制消息发送成功，则 uid 所指定的用户会通过 [onUserBinaryMessageReceivedOutsideRoom](Windows-callback.md#IRTCVideoEventHandler-onuserbinarymessagereceivedoutsideroom) 回调收到该条消息。


<span id="IRTCVideo-sendservermessage"></span>
### sendServerMessage
```cpp
virtual int64_t bytertc::IRTCVideo::sendServerMessage(
    const char* message)
```
客户端给应用服务器发送文本消息（P2Server）

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| message | **const char*** | 发送的文本消息内容  <br/>消息不超过 64 KB。 |

**返回值**

+ \>0：发送成功，返回这次发送消息的编号，从 1 开始递增  
+ -1：发送失败，IRTCVideo 实例未创建


**注意**

+ 在向应用服务器发送文本消息前，必须先调用 [login](#IRTCVideo-login) 完成登录，随后调用 [setServerParams](#IRTCVideo-setserverparams) 设置应用服务器。  
+ 调用本接口后，会收到一次 [onServerMessageSendResult](Windows-callback.md#IRTCVideoEventHandler-onservermessagesendresult) 回调，通知消息发送方是否发送成功。  
+ 若文本消息发送成功，则之前调用 [setServerParams](#IRTCVideo-setserverparams) 设置的应用服务器会收到该条消息。


<span id="IRTCVideo-sendserverbinarymessage"></span>
### sendServerBinaryMessage
```cpp
virtual int64_t bytertc::IRTCVideo::sendServerBinaryMessage(
    int length,
    const uint8_t* message)
```
客户端给应用服务器发送二进制消息（P2Server）

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| length | **int** | 二进制字符串的长度 |
| message | **const uint8_t*** | 发送的二进制消息内容  <br/>消息不超过 64KB。 |

**返回值**

+ \>0：发送成功，返回这次发送消息的编号，从 1 开始递增  
+ -1：发送失败，IRTCVideo 实例未创建


**注意**

+ 在向应用服务器发送二进制消息前，必须先调用 [login](#IRTCVideo-login) 完成登录，随后调用 [setServerParams](#IRTCVideo-setserverparams) 设置应用服务器。  
+ 调用本接口后，会收到一次 [onServerMessageSendResult](Windows-callback.md#IRTCVideoEventHandler-onservermessagesendresult) 回调，通知消息发送方发送成功或失败。  
+ 若二进制消息发送成功，则之前调用 [setServerParams](#IRTCVideo-setserverparams) 设置的应用服务器会收到该条消息。


<span id="IRTCVideo-startnetworkdetection"></span>
### startNetworkDetection
```cpp
virtual NetworkDetectionStartReturn bytertc::IRTCVideo::startNetworkDetection(
    bool is_test_uplink,
    int expected_uplink_bitrate,
    bool is_test_downlink,
    int expected_downlink_biterate)
```
开启通话前网络探测

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| is_test_uplink | **bool** | 是否探测上行带宽 |
| expected_uplink_bitrate | **int** | 期望上行带宽，单位：kbps范围为 {0, [100-10000]}，其中， `0` 表示由 SDK 指定最高码率。 |
| is_test_downlink | **bool** | 是否探测下行带宽 |
| expected_downlink_biterate | **int** | 期望下行带宽，单位：kbps范围为 {0, [100-10000]}，其中， `0` 表示由 SDK 指定最高码率。 |

**返回值**
开启通话前网络探测结果，详见 [NetworkDetectionStartReturn](Windows-errorcode.md#networkdetectionstartreturn)


**注意**

+ 成功调用本接口后，会在 3s 内收到一次 [onNetworkDetectionResult](Windows-callback.md#IRTCVideoEventHandler-onnetworkdetectionresult) 回调，此后每 2s 会收到一次该回调，通知探测结果；  
+ 若探测停止，则会收到一次 [onNetworkDetectionStopped](Windows-callback.md#IRTCVideoEventHandler-onnetworkdetectionstopped) 通知探测停止。


<span id="IRTCVideo-stopnetworkdetection"></span>
### stopNetworkDetection
```cpp
virtual void bytertc::IRTCVideo::stopNetworkDetection()
```
停止通话前网络探测


**注意**

+ 调用本接口后，会收到一次 [onNetworkDetectionStopped](Windows-callback.md#IRTCVideoEventHandler-onnetworkdetectionstopped) 回调通知探测停止。


<span id="IRTCVideo-setscreenaudiosourcetype"></span>
### setScreenAudioSourceType
```cpp
virtual void bytertc::IRTCVideo::setScreenAudioSourceType(
    AudioSourceType source_type)
```
在屏幕共享时，设置屏幕音频的采集方式（内部采集/自定义采集）

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| source_type | **AudioSourceType** | 屏幕音频输入源类型, 参看 [AudioSourceType](Windows-keytype.md#audiosourcetype) |


**注意**

+ 默认采集方式是 RTC SDK 内部采集。
+ 你应该在 [publishScreen](#IRTCRoom-publishscreen) 前，调用此方法。否则，你将收到 [onWarning](Windows-callback.md#IRTCVideoEventHandler-onwarning) 的报错：`kWarningCodeSetScreenAudioSourceTypeFailed` 
+ 如果设定为内部采集，你必须再调用 [startScreenAudioCapture](#IRTCVideo-startscreenaudiocapture) 开始采集；
+ 如果设定为自定义采集，你必须再调用 [pushScreenAudioFrame](#IRTCVideo-pushscreenaudioframe) 将自定义采集到的屏幕音频帧推送到 RTC SDK。
+ 无论是内部采集还是自定义采集，你都必须调用 [publishScreen](#IRTCRoom-publishscreen) 将采集到的屏幕音频推送到远端。


<span id="IRTCVideo-setscreenaudiostreamindex"></span>
### setScreenAudioStreamIndex
```cpp
virtual void bytertc::IRTCVideo::setScreenAudioStreamIndex(
    StreamIndex index)
```
在屏幕共享时，设置屏幕音频流和麦克风采集到的音频流的混流方式

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| index | **StreamIndex** | 混流方式，参看 [StreamIndex](Windows-keytype.md#streamindex) <br/>• `kStreamIndexMain`: 将屏幕音频流和麦克风采集到的音频流混流 <br/>• `kStreamIndexScreen`: 默认值， 将屏幕音频流和麦克风采集到的音频流分为两路音频流 |


**注意**
你应该在 [publishScreen](#IRTCRoom-publishscreen) 之前，调用此方法。否则，你将收到 [onWarning](Windows-callback.md#IRTCVideoEventHandler-onwarning) `的报错：kWarningCodeSetScreenAudioStreamIndexFailed`

<span id="IRTCVideo-startscreenaudiocapture"></span>
### startScreenAudioCapture
```cpp
virtual void bytertc::IRTCVideo::startScreenAudioCapture()
```
在屏幕共享时，开始使用 RTC SDK 内部采集方式，采集屏幕音频


**注意**

+ 采集后，你还需要调用 [publishScreen](#IRTCRoom-publishscreen) 将采集到的屏幕音频推送到远端。
+ 要关闭屏幕音频内部采集，调用 [stopScreenAudioCapture](#IRTCVideo-stopscreenaudiocapture)。


<span id="IRTCVideo-stopscreenaudiocapture"></span>
### stopScreenAudioCapture
```cpp
virtual void bytertc::IRTCVideo::stopScreenAudioCapture()
```
在屏幕共享时，停止使用 RTC SDK 内部采集方式，采集屏幕音频。


**注意**
要开始屏幕音频内部采集，调用 [startScreenAudioCapture](#IRTCVideo-startscreenaudiocapture)。

<span id="IRTCVideo-pushscreenaudioframe"></span>
### pushScreenAudioFrame
```cpp
virtual int bytertc::IRTCVideo::pushScreenAudioFrame(
    IAudioFrame* frame)
```
使用自定义采集方式，采集屏幕共享时的屏幕音频时，将音频帧推送至 RTC SDK 处进行编码等处理。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| frame | **IAudioFrame*** | 音频数据帧，参见 [IAudioFrame](Windows-keytype.md#iaudioframe) |

**返回值**
方法调用结果  

+ 0: 设置成功  
+ < 0: 设置失败  


**注意**

+ 调用此接口推送屏幕共享时的自定义采集的音频数据前，必须调用 [setScreenAudioSourceType](#IRTCVideo-setscreenaudiosourcetype) 开启屏幕音频自定义采集。  
+ 你应每隔 10 毫秒，调用一次此方法推送一次自定义采集的音频帧。一次推送的音频帧中应包含 frame.sample_rate / 100 个音频采样点。比如，假如采样率为 48000Hz，则每次应该推送 480 个采样点。  
+ 音频采样格式为 S16。音频缓冲区内的数据格式必须为 PCM 数据，其容量大小应该为 samples × frame.channel × 2。  
+ 调用此接口将自定义采集的音频帧推送到 RTC SDK 后，你必须调用 [publishScreen](#IRTCRoom-publishscreen) 将采集到的屏幕音频推送到远端。在调用 [publishScreen](#IRTCRoom-publishscreen) 前，推送到 RTC SDK 的音频帧信息会丢失。


<span id="IRTCVideo-startlivetranscoding"></span>
### startLiveTranscoding
```cpp
virtual void bytertc::IRTCVideo::startLiveTranscoding(
    const char* task_id,
    ITranscoderParam* param,
    ITranscoderObserver* observer)
```
新增转推直播任务，并设置合流的图片、视频视图布局和音频属性。  <br>
同一个任务中转推多路直播流时，SDK 会先将多路流合成一路流，然后再进行转推。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| task_id | **const char*** | 转推直播任务 ID。<br/>你可以在同一房间内发起多个转推直播任务，并用不同的任务 ID 加以区分。当你需要发起多个转推直播任务时，应使用多个 ID；当你仅需发起一个转推直播任务时，建议使用空字符串。 |
| param | **ITranscoderParam*** | 转推直播配置参数。参看 [ITranscoderParam](Windows-keytype.md#itranscoderparam)。 |
| observer | **ITranscoderObserver*** | 端云一体转推直播观察者。参看 [ITranscoderObserver](Windows-callback.md#itranscoderobserver)。  <br/>通过注册 observer 接收转推直播相关的回调。 |


**注意**

+ 调用该方法后，关于启动结果和推流过程中的错误，会收到 [onStreamMixingEvent](Windows-callback.md#ITranscoderObserver-onstreammixingevent) 回调。
+ 调用 [stopLiveTranscoding](#IRTCVideo-stoplivetranscoding) 停止转推直播。


<span id="IRTCVideo-stoplivetranscoding"></span>
### stopLiveTranscoding
```cpp
virtual void bytertc::IRTCVideo::stopLiveTranscoding(
    const char* task_id)
```
停止转推直播，会收到 [onStreamMixingEvent](Windows-callback.md#ITranscoderObserver-onstreammixingevent) 回调。  <br>
关于启动转推直播，参看 [startLiveTranscoding](#IRTCVideo-startlivetranscoding)。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| task_id | **const char*** | 转推直播任务 ID。可以指定想要停止的转推直播任务。 |


<span id="IRTCVideo-updatelivetranscoding"></span>
### updateLiveTranscoding
```cpp
virtual void bytertc::IRTCVideo::updateLiveTranscoding(
    const char* task_id,
    ITranscoderParam* param)
```
更新转推直播参数，会收到 [onStreamMixingEvent](Windows-callback.md#ITranscoderObserver-onstreammixingevent) 回调。  <br>
使用 [startLiveTranscoding](#IRTCVideo-startlivetranscoding) 启用转推直播功能后，使用此方法更新功能配置参数。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| task_id | **const char*** | 转推直播任务 ID。指定想要更新参数设置的转推直播任务。 |
| param | **ITranscoderParam*** | 配置参数，参看 [ITranscoderParam](Windows-keytype.md#itranscoderparam)。除特殊说明外，均支持过程中更新。调用时，结构体中没有传入值的属性，会被更新为默认值。 |


<span id="IRTCVideo-startpushsinglestreamtocdn"></span>
### startPushSingleStreamToCDN
```cpp
virtual void bytertc::IRTCVideo::startPushSingleStreamToCDN(
    const char* task_id,
    PushSingleStreamParam& param,
    IPushSingleStreamToCDNObserver* observer)
```
新增单流转推直播任务。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| task_id | **const char*** | 任务 ID。<br/>你可以发起多个转推直播任务，并用不同的任务 ID 加以区分。当你需要发起多个转推直播任务时，应使用多个 ID；当你仅需发起一个转推直播任务时，建议使用空字符串。 |
| param | **PushSingleStreamParam&** | 转推直播配置参数。详见 [PushSingleStreamParam](Windows-keytype.md#pushsinglestreamparam)。 |
| observer | **IPushSingleStreamToCDNObserver*** | 单流转推直播观察者。详见 [IPushSingleStreamToCDNObserver](Windows-callback.md#ipushsinglestreamtocdnobserver)。  <br/>通过注册 observer 接收单流转推直播相关的回调。 |


**注意**

+ 调用该方法后，关于启动结果和推流过程中的错误，会收到 [onStreamPushEvent](Windows-callback.md#IPushSingleStreamToCDNObserver-onstreampushevent) 回调。
+ 调用 [stopPushStreamToCDN](#IRTCVideo-stoppushstreamtocdn) 停止任务。
+ 由于本功能不进行编解码，所以推到 RTMP 的视频流会根据推流端的分辨率、编码方式、关闭摄像头等变化而变化。


<span id="IRTCVideo-stoppushstreamtocdn"></span>
### stopPushStreamToCDN
```cpp
virtual void bytertc::IRTCVideo::stopPushStreamToCDN(
    const char* task_id)
```
停止转推直播。<br>
关于启动转推直播，参看 [startPushSingleStreamToCDN](#IRTCVideo-startpushsinglestreamtocdn)。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| task_id | **const char*** | 任务 ID。可以指定想要停止的单流转推直播任务。 |


<span id="IRTCVideo-startpushpublicstream"></span>
### startPushPublicStream
```cpp
virtual int bytertc::IRTCVideo::startPushPublicStream(
    const char* public_stream_id,
    IPublicStreamParam* param)
```
发布一路公共流<br>
用户可以指定房间内多个用户发布的媒体流合成一路公共流。使用同一 `appID` 的用户，可以调用 [startPlayPublicStream](#IRTCVideo-startplaypublicstream) 获取和播放指定的公共流。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| public_stream_id | **const char*** | 公共流 ID |
| param | **IPublicStreamParam*** | 公共流参数。详见 [IPublicStreamParam](Windows-keytype.md#ipublicstreamparam)。<br/>一路公共流可以包含多路房间内的媒体流，按照指定的布局方式进行聚合。<br/>如果指定的媒体流还未发布，则公共流将在指定流开始发布后实时更新。 |

**返回值**

+ 0: 成功。同时将收到 [onPushPublicStreamResult](Windows-callback.md#IRTCVideoEventHandler-onpushpublicstreamresult) 回调。
+ !0: 失败。当参数不合法或参数为空，调用失败。


**注意**

+ 同一用户使用同一公共流 ID 多次调用本接口无效。如果你希望更新公共流参数，调用 [updatePublicStreamParam](#IRTCVideo-updatepublicstreamparam) 接口。
+ 不同用户使用同一公共流 ID 多次调用本接口时，RTC 将使用最后一次调用时传入的参数更新公共流。
+ 使用不同的 ID 多次调用本接口可以发布多路公共流。
+ 调用 [stopPushPublicStream](#IRTCVideo-stoppushpublicstream) 停止发布公共流。
+ 关于公共流功能的介绍，详见[发布和订阅公共流](https://www.volcengine.com/docs/6348/108930)


<span id="IRTCVideo-stoppushpublicstream"></span>
### stopPushPublicStream
```cpp
virtual int bytertc::IRTCVideo::stopPushPublicStream(
    const char* public_stream_id)
```
停止发布当前用户发布的公共流<br>
关于发布公共流，查看 [startPushPublicStream](#IRTCVideo-startpushpublicstream)。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| public_stream_id | **const char*** | 公共流 ID<br/>指定的流必须为当前用户所发布。 |

**返回值**

+ 0: 成功
+ !0: 失败


<span id="IRTCVideo-updatepublicstreamparam"></span>
### updatePublicStreamParam
```cpp
virtual int bytertc::IRTCVideo::updatePublicStreamParam(
    const char* public_stream_id,
    IPublicStreamParam* param)
```
更新公共流参数<br>
关于发布公共流，查看 [startPushPublicStream](#IRTCVideo-startpushpublicstream)。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| public_stream_id | **const char*** | 公共流 ID |
| param | **IPublicStreamParam*** | 公共流参数。详见 [IPublicStreamParam](Windows-keytype.md#ipublicstreamparam)。<br/>指定的流必须为当前用户所发布的。 |

**返回值**

+ 0: 成功
+ !0: 失败


**注意**
调用本接口前需要通过 [onPushPublicStreamResult](Windows-callback.md#IRTCVideoEventHandler-onpushpublicstreamresult) 确认公共流是否已经成功启动。

<span id="IRTCVideo-enableaudiopropertiesreport"></span>
### enableAudioPropertiesReport
```cpp
virtual void bytertc::IRTCVideo::enableAudioPropertiesReport(
    const AudioPropertiesConfig& config)
```
启用音频信息提示。  <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| config | **const AudioPropertiesConfig&** | 详见 [AudioPropertiesConfig](Windows-keytype.md#audiopropertiesconfig) |


**注意**
开启提示后，你可以：  

+ 通过 [onLocalAudioPropertiesReport](Windows-callback.md#IRTCVideoEventHandler-onlocalaudiopropertiesreport) 回调获取本地麦克风和屏幕音频流采集的音频信息；  
+ 通过 [onRemoteAudioPropertiesReport](Windows-callback.md#IRTCVideoEventHandler-onremoteaudiopropertiesreport) 回调获取订阅的远端用户的音频信息。  
+ 通过 [onActiveSpeaker](Windows-callback.md#IRTCVideoEventHandler-onactivespeaker) 回调获取房间内的最活跃用户信息。


<span id="IRTCVideo-setremoteaudioplaybackvolume"></span>
### setRemoteAudioPlaybackVolume
```cpp
virtual void bytertc::IRTCVideo::setRemoteAudioPlaybackVolume(
    const char* room_id,
    const char* user_id,
    int volume)
```
调节来自远端用户的音频播放音量

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| room_id | **const char*** | 音频来源用户所在的房间 ID |
| user_id | **const char*** | 音频来源的远端用户 ID |
| volume | **int** | 音频播放音量值和原始音量的比值，范围是 [0, 400]，单位为 %，自带溢出保护。只改变音频数据的音量信息，不涉及本端硬件的音量调节。为保证更好的通话质量，建议将 volume 值设为 [0,100]。 <br/>• 0: 静音  <br/>• 100: 原始音量，默认值  <br/>• 400: 最大可为原始音量的 4 倍(自带溢出保护) |


<span id="IRTCVideo-enablevocalinstrumentbalance"></span>
### enableVocalInstrumentBalance
```cpp
virtual void bytertc::IRTCVideo::enableVocalInstrumentBalance(
    bool enable)
```
开启/关闭音量均衡功能。  <br>
开启音量均衡功能后，人声的响度会调整为 -16lufs。如果已调用 [setAudioMixingLoudness](#IAudioMixingManager-setaudiomixingloudness) 传入了混音音乐的原始响度，此音乐播放时，响度会调整为 -20lufs。（Linux 不支持）

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| enable | **bool** | 是否开启音量均衡功能：  <br/>• True: 是  <br/>• False: 否 |


**注意**
该接口须在调用 [startAudioMixing](#IAudioMixingManager-startaudiomixing) 开始播放音频文件之前调用。

<span id="IRTCVideo-enableplaybackducking"></span>
### enablePlaybackDucking
```cpp
virtual void bytertc::IRTCVideo::enablePlaybackDucking(
    bool enable)
```
打开/关闭音量闪避功能，适用于在 RTC 通话过程中会同时播放短视频或音乐的场景，如“一起看”、“在线 KTV”等。  <br>
开启该功能后，当检测到远端人声时，本地的媒体播放音量会自动减弱，从而保证远端人声的清晰可辨；当远端人声消失时，本地媒体音量会恢复到闪避前的音量水平。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| enable | **bool** | 是否开启音量闪避：  <br/>• True: 是  <br/>• False: 否 |


<span id="IRTCVideo-registerlocalencodedvideoframeobserver"></span>
### registerLocalEncodedVideoFrameObserver
```cpp
virtual void bytertc::IRTCVideo::registerLocalEncodedVideoFrameObserver(
    ILocalEncodedVideoFrameObserver* observer)
```
注册本地视频帧监测器。  <br>
无论使用内部采集还是自定义采集，调用该方法后，SDK 每监测到一帧本地视频帧时，都会将视频帧信息通过 [onLocalEncodedVideoFrame](Windows-callback.md#ILocalEncodedVideoFrameObserver-onlocalencodedvideoframe) 回调给用户

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| observer | **ILocalEncodedVideoFrameObserver*** | 本地视频帧监测器，参看 [ILocalEncodedVideoFrameObserver](Windows-callback.md#ilocalencodedvideoframeobserver)。将参数设置为 nullptr 则取消注册。 |


**注意**
该方法可在进房前后的任意时间调用，在进房前调用可保证尽可能早地监测视频帧并触发回调

<span id="IRTCVideo-registerremoteencodedvideoframeobserver"></span>
### registerRemoteEncodedVideoFrameObserver
```cpp
virtual void bytertc::IRTCVideo::registerRemoteEncodedVideoFrameObserver(
    IRemoteEncodedVideoFrameObserver* observer)
```
注册远端编码后视频数据回調。  <br>
完成注册后，当 SDK 监测到远端编码后视频帧时，会触发 [onRemoteEncodedVideoFrame](Windows-callback.md#IRemoteEncodedVideoFrameObserver-onremoteencodedvideoframe) 回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| observer | **IRemoteEncodedVideoFrameObserver*** | 远端编码后视频数据监测器，参看 [IRemoteEncodedVideoFrameObserver](Windows-callback.md#iremoteencodedvideoframeobserver) |


**注意**

+ 更多自定义解码功能说明参看 [自定义视频编解码](https://www.volcengine.com/docs/6348/82921#%E8%87%AA%E5%AE%9A%E4%B9%89%E8%A7%86%E9%A2%91%E8%A7%A3%E7%A0%81)。
+ 该方法适用于手动订阅，并且进房前后均可调用，建议在进房前调用。
+ 引擎销毁前需取消注册，调用该方法将参数设置为 nullptr 即可。


<span id="IRTCVideo-setexternalvideoencodereventhandler"></span>
### setExternalVideoEncoderEventHandler
```cpp
virtual void bytertc::IRTCVideo::setExternalVideoEncoderEventHandler(
    IExternalVideoEncoderEventHandler* encoder_handler)
```
注册自定义编码帧推送事件回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| encoder_handler | **IExternalVideoEncoderEventHandler*** | 自定义编码帧回调类，参看 [IExternalVideoEncoderEventHandler](Windows-callback.md#iexternalvideoencodereventhandler) |


**注意**

+ 该方法需在进房前调用。 
+ 引擎销毁前需取消注册，调用该方法将参数设置为 nullptr 即可。


<span id="IRTCVideo-pushexternalencodedvideoframe"></span>
### pushExternalEncodedVideoFrame
```cpp
virtual bool bytertc::IRTCVideo::pushExternalEncodedVideoFrame(
    StreamIndex index,
    int video_index,
    IEncodedVideoFrame* video_stream)
```
推送自定义编码后的视频流

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| index | **StreamIndex** | 需要推送的编码流的属性，参看 [StreamIndex](Windows-keytype.md#streamindex) |
| video_index | **int** | 对应的编码流下标，从 0 开始，如果调用 [setVideoEncoderConfig](#IRTCVideo-setvideoencoderconfig) 设置了多路流，此处数量须与之保持一致 |
| video_stream | **IEncodedVideoFrame*** | 编码流视频帧信息，参看 [IEncodedVideoFrame](Windows-keytype.md#iencodedvideoframe)。 |


**注意**

+ 目前仅支持推送 H264 和 ByteVC1 格式的视频帧，且视频流协议格式须为 Annex B 格式。  
+ 该函数运行在用户调用线程内  
+ 推送自定义编码视频帧前，必须调用 [setVideoSourceType](#IRTCVideo-setvideosourcetype) 将视频输入源切换至自定义编码视频源。


<span id="IRTCVideo-setvideodecoderconfig"></span>
### setVideoDecoderConfig
```cpp
virtual void bytertc::IRTCVideo::setVideoDecoderConfig(
    RemoteStreamKey key,
    VideoDecoderConfig config)
```
在订阅远端视频流之前，设置远端视频数据解码方式

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| key | **RemoteStreamKey** | 远端流信息，即对哪一路视频流进行解码方式设置，参看 [RemoteStreamKey](Windows-keytype.md#remotestreamkey)。 |
| config | **VideoDecoderConfig** | 视频解码方式，参看 [VideoDecoderConfig](Windows-keytype.md#videodecoderconfig)。 |


**注意**

+ 该方法仅适用于手动订阅模式，并且在订阅远端流之前使用。  
+ 当你想要对远端流进行自定义解码时，你需要先调用 [registerRemoteEncodedVideoFrameObserver](#IRTCVideo-registerremoteencodedvideoframeobserver) 注册远端视频流监测器，然后再调用该接口将解码方式设置为自定义解码。监测到的视频数据会通过 [onRemoteEncodedVideoFrame](Windows-callback.md#IRemoteEncodedVideoFrameObserver-onremoteencodedvideoframe) 回调出来。


<span id="IRTCVideo-requestremotevideokeyframe"></span>
### requestRemoteVideoKeyFrame
```cpp
virtual void bytertc::IRTCVideo::requestRemoteVideoKeyFrame(
    const RemoteStreamKey& stream_info)
```
在订阅远端视频流之后，向远端请求关键帧

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stream_info | **const RemoteStreamKey&** | 远端流信息，参看 [RemoteStreamKey](Windows-keytype.md#remotestreamkey)。 |


**注意**

+ 该方法仅适用于手动订阅模式，并且在成功订阅远端流之后使用。  
+ 该方法适用于调用 [setVideoDecoderConfig](#IRTCVideo-setvideodecoderconfig) 开启自定义解码功能后，并且自定义解码失败的情况下使用


<span id="IRTCVideo-sendstreamsyncinfo"></span>
### sendStreamSyncInfo
```cpp
virtual int bytertc::IRTCVideo::sendStreamSyncInfo(
    const uint8_t* data,
    int32_t length,
    const StreamSycnInfoConfig& config)
```
发送音频流同步信息。将消息通过音频流发送到远端，并实现与音频流同步，该接口调用成功后，远端用户会收到 [onStreamSyncInfoReceived](Windows-callback.md#IRTCVideoEventHandler-onstreamsyncinforeceived) 回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| data | **const uint8_t*** | 消息内容。 |
| length | **int32_t** | 消息长度。取值范围是 [1,255] 字节，建议小于 16 字节，否则可能占用较大带宽。 |
| config | **const StreamSycnInfoConfig&** | 媒体流信息同步的相关配置，详见 [StreamSycnInfoConfig](Windows-keytype.md#streamsycninfoconfig) 。 |

**返回值**

+ \>=0: 消息发送成功。返回成功发送的次数。  
+ -1: 消息发送失败。消息长度大于 255 字节。  
+ -2: 消息发送失败。传入的消息内容为空。  
+ -3: 消息发送失败。通过屏幕流进行消息同步时，此屏幕流还未发布。  
+ -4: 消息发送失败。通过用麦克风或自定义设备采集到的音频流进行消息同步时，此音频流还未发布，详见错误码 [ErrorCode](Windows-errorcode.md#errorcode)。  


**注意**

+ 调用本接口的频率建议不超过 50 次每秒。
+ 在采用 `kRoomProfileTypeInteractivePodcast` 作为房间模式时，此消息一定会送达。在其他房间模式下，如果本地用户未说话，此消息不一定会送达。

<span id="IRTCVideo-setlocalvoicepitch"></span>
### setLocalVoicePitch
```cpp
virtual void bytertc::IRTCVideo::setLocalVoicePitch(
    int pitch)
```
开启本地语音变调功能，多用于 K 歌场景。  <br>
使用该方法，你可以对本地语音的音调进行升调或降调等调整。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| pitch | **int** | 相对于语音原始音调的升高/降低值，取值范围[-12，12]，默认值为 0，即不做调整。  <br/>取值范围内每相邻两个值的音高距离相差半音，正值表示升调，负值表示降调，设置的绝对值越大表示音调升高或降低越多。  <br/>超出取值范围则设置失败，并且会触发 [onWarning](Windows-callback#IRTCVideoEventHandler-onwarning) 回调，提示 [WarningCode](Windows-errorcode.md#warningcode) 错误码为 `WARNING_CODE_SET_SCREEN_STREAM_INVALID_VOICE_PITCH` 设置语音音调不合法 |


<span id="IRTCVideo-startplaypublicstream"></span>
### startPlayPublicStream
```cpp
virtual int bytertc::IRTCVideo::startPlayPublicStream(
    const char* public_stream_id)
```
订阅指定公共流<br>
无论用户是否在房间内，都可以调用本接口获取和播放指定的公共流。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| public_stream_id | **const char*** | 公共流 ID，如果指定流暂未发布，则本地客户端将在其开始发布后接收到流数据。 |

**返回值**

+ 0: 成功。同时将收到 [onPlayPublicStreamResult](Windows-callback.md#IRTCVideoEventHandler-onplaypublicstreamresult) 回调。
+ !0: 失败。当参数不合法或参数为空，调用失败。


**注意**

+ 在调用本接口之前，建议先绑定渲染视图。
- 调用 [setPublicStreamVideoCanvas](#IRTCVideo-setpublicstreamvideocanvas) 绑定内部渲染视图：
- 调用 [setPublicStreamVideoSink](#IRTCVideo-setpublicstreamvideosink) 绑定自定义渲染视图：
+ 调用本接口后，可以通过 [onFirstPublicStreamVideoFrameDecoded](Windows-callback.md#IRTCVideoEventHandler-onfirstpublicstreamvideoframedecoded) 和 [onFirstPublicStreamAudioFrame](Windows-callback.md#IRTCVideoEventHandler-onfirstpublicstreamaudioframe) 回调公共流的视频和音频首帧解码情况。
+ 调用本接口后，可以通过 [onPublicStreamSEIMessageReceived](Windows-callback.md#IRTCVideoEventHandler-onpublicstreamseimessagereceived) 回调公共流中包含的 SEI 信息。
+ 订阅公共流之后，可以通过调用 [stopPlayPublicStream](#IRTCVideo-stopplaypublicstream) 接口取消订阅公共流。


<span id="IRTCVideo-stopplaypublicstream"></span>
### stopPlayPublicStream
```cpp
virtual int bytertc::IRTCVideo::stopPlayPublicStream(
    const char* public_stream_id)
```
取消订阅指定公共流<br>
关于订阅公共流，查看 [startPlayPublicStream](#IRTCVideo-startplaypublicstream)。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| public_stream_id | **const char*** | 公共流 ID |

**返回值**

+ 0：成功  
+ !0：失败  


<span id="IRTCVideo-setpublicstreamvideocanvas"></span>
### setPublicStreamVideoCanvas
```cpp
virtual int bytertc::IRTCVideo::setPublicStreamVideoCanvas(
    const char* public_stream_id,
    const VideoCanvas& canvas)
```
为指定公共流绑定内部渲染视图

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| public_stream_id | **const char*** | 公共流 ID |
| canvas | **const VideoCanvas&** | 内部渲染视图，如果需要解除视频的绑定视图，把 videoCanvas 设置为空。详见 [VideoCanvas](Windows-keytype.md#videocanvas)。 |

**返回值**

+ 0：成功  
+ !0：失败  


<span id="IRTCVideo-setpublicstreamvideosink"></span>
### setPublicStreamVideoSink
```cpp
virtual void bytertc::IRTCVideo::setPublicStreamVideoSink(
    const char* public_stream_id,
    IVideoSink* video_sink,
    IVideoSink::PixelFormat format)
```
为指定公共流绑定自定义渲染器。详见[自定义视频渲染](https://www.volcengine.com/docs/6348/81201)。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| public_stream_id | **const char*** | 公共流 ID |
| video_sink | **IVideoSink*** | 自定义视频渲染器，自定义视频渲染器，需要释放渲染器资源时，将 videoSink 设置为 `null`。参看 [IVideoSink](Windows-keytype.md#ivideosink) |
| format | **IVideoSink::PixelFormat** | videoSink 适用的视频帧编码格式，参看 [PixelFormat](Windows-keytype.md#pixelformat) |

**返回值**

+ 0：成功  
+ !0：失败  


<span id="IRTCVideo-setvideowatermark"></span>
### setVideoWatermark
```cpp
virtual void bytertc::IRTCVideo::setVideoWatermark(
    StreamIndex streamIndex,
    const char* image_path,
    RTCWatermarkConfig config)
```
在指定视频流上添加水印。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamIndex | **StreamIndex** | 需要添加水印的视频流属性，参看 [StreamIndex](Windows-keytype.md#streamindex)。 |
| image_path | **const char*** | 水印图片路径，仅支持本地文件绝对路径，长度限制为 512 字节。  <br/>水印图片为 PNG 或 JPG 格式。 |
| config | **RTCWatermarkConfig** | 水印参数，参看 [RTCWatermarkConfig](Windows-keytype.md#rtcwatermarkconfig)。 |


**注意**

+ 调用 [clearVideoWatermark](#IRTCVideo-clearvideowatermark) 移除指定视频流的水印。  
+ 同一路流只能设置一个水印，新设置的水印会代替上一次的设置。你可以多次调用本方法来设置不同流的水印。  
+ 开启本地预览镜像，或本地预览和编码传输镜像时，远端水印均不镜像；开启本地预览镜像时，本端水印会镜像。
+ 开启大小流后，水印对大小流均生效，且针对小流进行等比例缩小。


<span id="IRTCVideo-clearvideowatermark"></span>
### clearVideoWatermark
```cpp
virtual void bytertc::IRTCVideo::clearVideoWatermark(
    StreamIndex streamIndex)
```
移除指定视频流的水印。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamIndex | **StreamIndex** | 需要移除水印的视频流属性，参看 [StreamIndex](Windows-keytype.md#streamindex)。 |


<span id="IRTCVideo-takelocalsnapshot"></span>
### takeLocalSnapshot
```cpp
virtual long bytertc::IRTCVideo::takeLocalSnapshot(
    const StreamIndex streamIndex,
    ISnapshotResultCallback* callback)
```
截取本地视频画面

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamIndex | **const StreamIndex** | 截图的视频流的属性，参看 [StreamIndex](Windows-keytype.md#streamindex)。 |
| callback | **ISnapshotResultCallback*** | 本地截图的回调。参看 [ISnapshotResultCallback](Windows-callback.md#isnapshotresultcallback)。 |

**返回值**
本地截图任务的编号，从 `1` 开始递增。


**注意**

+ 对截取的画面，包含本地视频处理的全部效果，包含旋转，镜像，美颜等。
+ 不管采用 SDK 内部采集，还是自定义采集，都可以进行截图。


<span id="IRTCVideo-takeremotesnapshot"></span>
### takeRemoteSnapshot
```cpp
virtual long bytertc::IRTCVideo::takeRemoteSnapshot(
    const RemoteStreamKey streamKey,
    ISnapshotResultCallback* callback)
```
截取远端视频画面

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamKey | **const RemoteStreamKey** | 截图的视频流，参看 [RemoteStreamKey](Windows-keytype.md#remotestreamkey)。 |
| callback | **ISnapshotResultCallback*** | 参看 [ISnapshotResultCallback](Windows-callback.md#isnapshotresultcallback)。 |

**返回值**
远端截图任务的编号，从 `1` 开始递增。


<span id="IRTCVideo-startcloudproxy"></span>
### startCloudProxy
```cpp
virtual void bytertc::IRTCVideo::startCloudProxy(
    const CloudProxyConfiguration& configuration)
```
开启云代理

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| configuration | **const CloudProxyConfiguration&** | 云代理服务器信息列表。参看 [CloudProxyConfiguration](Windows-keytype.md#cloudproxyconfiguration)。 |


**注意**

+ 在加入房间前调用此接口  
+ 在开启云代理后，进行通话前网络探测 
+ 开启云代理后，并成功链接云代理服务器后，会收到 [onCloudProxyConnected](Windows-callback.md#IRTCVideoEventHandler-oncloudproxyconnected)。
+ 要关闭云代理，调用 [stopCloudProxy](#IRTCVideo-stopcloudproxy)。


<span id="IRTCVideo-stopcloudproxy"></span>
### stopCloudProxy
```cpp
virtual void bytertc::IRTCVideo::stopCloudProxy()
```
关闭云代理


**注意**
要开启云代理，调用 [startCloudProxy](#IRTCVideo-startcloudproxy)。

<span id="IRTCVideo-startechotest"></span>
### startEchoTest
```cpp
virtual int bytertc::IRTCVideo::startEchoTest(
    EchoTestConfig echo_test_config,
    unsigned int play_delay_time)
```
开启音视频回路测试。  <br>
在进房前，用户可调用该接口对音视频通话全链路进行检测，包括对音视频设备以及用户上下行网络的检测，从而帮助用户判断是否可以正常发布和接收音视频流。  <br>
开始检测后，SDK 会录制你声音或视频。如果你在设置的延时范围内收到了回放，则视为音视频回路测试正常。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| echo_test_config | **EchoTestConfig** | 回路测试参数设置，参看 [EchoTestConfig](Windows-keytype.md#echotestconfig)。 |
| play_delay_time | **unsigned int** | 音视频延迟播放的时间间隔，用于指定在开始检测多长时间后期望收到回放。取值范围为 [2,10]，单位为秒，默认为 2 秒。 |

**返回值**
方法调用结果：  

+ 0：成功  
+ -1：失败，当前用户已经在检测中  
+ -2：失败，用户已进房  
+ -3：失败，音视频均未采集  
+ -4：失败，参数异常  
+ -5：失败，已经存在相同 roomId 的房间


**注意**

+ 调用该方法开始音视频回路检测后，你可以调用 [stopEchoTest](#IRTCVideo-stopechotest) 立即结束测试，也可等待测试 60s 后自动结束，以更换设备进行下一次测试，或进房。  
+ 在该方法之前调用的所有跟设备控制、流控制相关的方法均在开始检测时失效，在结束检测后恢复生效。  
+ 在调用 [startEchoTest](#IRTCVideo-startechotest) 和 [stopEchoTest](#IRTCVideo-stopechotest) 之间调用的所有跟设备采集、流控制、进房相关的方法均不生效，并会收到 [onWarning](Windows-callback.md#IRTCVideoEventHandler-onwarning) 回调，提示警告码为 `kWarningCodeInEchoTestMode`。  
+ 音视频回路检测的结果会通过 [onEchoTestResult](Windows-callback.md#IRTCVideoEventHandler-onechotestresult) 回调通知。


<span id="IRTCVideo-stopechotest"></span>
### stopEchoTest
```cpp
virtual int bytertc::IRTCVideo::stopEchoTest()
```
停止音视频回路测试。  <br>
调用 [startEchoTest](#IRTCVideo-startechotest) 开启音视频回路检测后，你必须调用该方法停止检测。

**返回值**
方法调用结果：  

+ 0：成功  
+ -1：失败，未开启回路检测


**注意**
音视频回路检测结束后，所有对系统设备及音视频流的控制均会恢复到开始检测前的状态。

<span id="IRTCVideo-getktvmanager"></span>
### getKTVManager
```cpp
virtual IKTVManager* bytertc::IRTCVideo::getKTVManager()
```
创建 KTV 管理接口。

**返回值**
KTV 管理接口，参看 [IKTVManager](#iktvmanager)。


<span id="IRTCVideo-getsingscoringmanager"></span>
### getSingScoringManager
```cpp
virtual ISingScoringManager* bytertc::IRTCVideo::getSingScoringManager()
```
创建 K 歌评分管理接口。

**返回值**
K 歌评分管理接口,详见 [ISingScoringManager](#isingscoringmanager)。


# IAudioDeviceCollection
```cpp
class bytertc::IAudioDeviceCollection
```

音频设备相关的信息


`Defined in : bytertc_audio_device_manager.h`

## 成员函数

| 返回 | 名称 |
| --- | --- |
| **virtual int** | [getCount](#IAudioDeviceCollection-getcount) |
| **virtual int** | [getDevice](#IAudioDeviceCollection-getdevice) |
| **virtual void** | [release](#IAudioDeviceCollection-release) |
| **virtual int** | [getDevice](#IAudioDeviceCollection-getdevice) |


## 函数说明
<span id="IAudioDeviceCollection-getcount"></span>
### getCount
```cpp
virtual int bytertc::IAudioDeviceCollection::getCount() override
```
获取当前系统内音频设备数量

**返回值**
音频设备数量


<span id="IAudioDeviceCollection-getdevice"></span>
### getDevice
```cpp
virtual int bytertc::IAudioDeviceCollection::getDevice(
    int index,
    char device_name[MAX_DEVICE_ID_LENGTH],
    char device_id[MAX_DEVICE_ID_LENGTH])
```
根据索引号，获取设备信息

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| index | **int** | 设备索引号，从 0 开始，注意需小于 [getCount](#IAudioDeviceCollection-getcount) 返回值。 |
| device_name | **char** | 设备名称 |
| device_id | **char** | 设备 ID |

**返回值**

+ 0：方法调用成功  
+ !0：方法调用失败  


<span id="IAudioDeviceCollection-release"></span>
### release
```cpp
virtual void bytertc::IAudioDeviceCollection::release()override
```
释放当前 [IAudioDeviceCollection](#iaudiodevicecollection) 对象占用的资源。


**注意**
不需要返回音频设备相关信息列表时应该调用本方法释放相关资源。

<span id="IAudioDeviceCollection-getdevice"></span>
### getDevice
```cpp
virtual int bytertc::IAudioDeviceCollection::getDevice(
    int index,
    AudioDeviceInfo* audio_device_info)
```
根据索引号，获取设备信息

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| index | **int** | 设备索引号，从 0 开始，注意需小于 [getCount](#IAudioDeviceCollection-getcount) 返回值。 |
| audio_device_info | **AudioDeviceInfo*** | 设备信息，详见 [AudioDeviceInfo](Windows-keytype.md#audiodeviceinfo) |

**返回值**

+ 0：方法调用成功  
+ !0：方法调用失败  


# IAudioDeviceManager
```cpp
class bytertc::IAudioDeviceManager
```

音频设备管理类


`Defined in : bytertc_audio_device_manager.h`

## 成员函数

| 返回 | 名称 |
| --- | --- |
| **virtual IAudioDeviceCollection*** | [enumerateAudioPlaybackDevices](#IAudioDeviceManager-enumerateaudioplaybackdevices) |
| **virtual IAudioDeviceCollection*** | [enumerateAudioCaptureDevices](#IAudioDeviceManager-enumerateaudiocapturedevices) |
| **virtual void** | [followSystemPlaybackDevice](#IAudioDeviceManager-followsystemplaybackdevice) |
| **virtual void** | [followSystemCaptureDevice](#IAudioDeviceManager-followsystemcapturedevice) |
| **virtual int** | [setAudioPlaybackDevice](#IAudioDeviceManager-setaudioplaybackdevice) |
| **virtual int** | [setAudioCaptureDevice](#IAudioDeviceManager-setaudiocapturedevice) |
| **virtual int** | [setAudioPlaybackDeviceVolume](#IAudioDeviceManager-setaudioplaybackdevicevolume) |
| **virtual int** | [getAudioPlaybackDeviceVolume](#IAudioDeviceManager-getaudioplaybackdevicevolume) |
| **virtual int** | [setAudioCaptureDeviceVolume](#IAudioDeviceManager-setaudiocapturedevicevolume) |
| **virtual int** | [getAudioCaptureDeviceVolume](#IAudioDeviceManager-getaudiocapturedevicevolume) |
| **virtual int** | [setAudioPlaybackDeviceMute](#IAudioDeviceManager-setaudioplaybackdevicemute) |
| **virtual int** | [getAudioPlaybackDeviceMute](#IAudioDeviceManager-getaudioplaybackdevicemute) |
| **virtual int** | [setAudioCaptureDeviceMute](#IAudioDeviceManager-setaudiocapturedevicemute) |
| **virtual int** | [getAudioCaptureDeviceMute](#IAudioDeviceManager-getaudiocapturedevicemute) |
| **virtual int** | [getAudioPlaybackDevice](#IAudioDeviceManager-getaudioplaybackdevice) |
| **virtual int** | [getAudioCaptureDevice](#IAudioDeviceManager-getaudiocapturedevice) |
| **virtual int** | [initAudioPlaybackDeviceForTest](#IAudioDeviceManager-initaudioplaybackdevicefortest) |
| **virtual int** | [initAudioCaptureDeviceForTest](#IAudioDeviceManager-initaudiocapturedevicefortest) |
| **virtual int** | [startAudioPlaybackDeviceTest](#IAudioDeviceManager-startaudioplaybackdevicetest) |
| **virtual int** | [stopAudioPlaybackDeviceTest](#IAudioDeviceManager-stopaudioplaybackdevicetest) |
| **virtual int** | [startAudioDeviceRecordTest](#IAudioDeviceManager-startaudiodevicerecordtest) |
| **virtual int** | [stopAudioDeviceRecordAndPlayTest](#IAudioDeviceManager-stopaudiodevicerecordandplaytest) |
| **virtual int** | [stopAudioDevicePlayTest](#IAudioDeviceManager-stopaudiodeviceplaytest) |


## 函数说明
<span id="IAudioDeviceManager-enumerateaudioplaybackdevices"></span>
### enumerateAudioPlaybackDevices
```cpp
virtual IAudioDeviceCollection* bytertc::IAudioDeviceManager::enumerateAudioPlaybackDevices()
```
获取当前系统内音频播放设备列表。如果后续设备有变更，你会收到 `onAudioMediaDeviceStateChanged` 回调通知，然后需要重新调用本接口以获得新的设备列表。

**返回值**
包含系统中所有音频播放设备的列表，参看 [IAudioDeviceCollection](#iaudiodevicecollection)。


<span id="IAudioDeviceManager-enumerateaudiocapturedevices"></span>
### enumerateAudioCaptureDevices
```cpp
virtual IAudioDeviceCollection* bytertc::IAudioDeviceManager::enumerateAudioCaptureDevices()
```
获取当前系统内音频采集设备列表。如果后续设备有变更，你需要重新调用本接口以获得新的设备列表。

**返回值**
一个包含系统中所有音频采集设备列表的对象，详见 [IAudioDeviceCollection](#iaudiodevicecollection)。


<span id="IAudioDeviceManager-followsystemplaybackdevice"></span>
### followSystemPlaybackDevice
```cpp
virtual void bytertc::IAudioDeviceManager::followSystemPlaybackDevice(
    bool followed)
```
设置音频播放路由是否跟随系统。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| followed | **bool** | • true: 跟随。此时，调用 [setAudioPlaybackDevice](#IAudioDeviceManager-setaudioplaybackdevice) 会失败。<br/>• false: 不跟随系统。此时，可以调用 [setAudioPlaybackDevice](#IAudioDeviceManager-setaudioplaybackdevice) 进行设置。 |


<span id="IAudioDeviceManager-followsystemcapturedevice"></span>
### followSystemCaptureDevice
```cpp
virtual void bytertc::IAudioDeviceManager::followSystemCaptureDevice(
    bool followed)
```
设置音频采集路由是否跟随系统。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| followed | **bool** | • true: 跟随。此时，调用 [setAudioCaptureDevice](#IAudioDeviceManager-setaudiocapturedevice) 会失败。<br/>• false: 不跟随系统。此时，可以调用 [setAudioCaptureDevice](#IAudioDeviceManager-setaudiocapturedevice) 进行设置。 |


<span id="IAudioDeviceManager-setaudioplaybackdevice"></span>
### setAudioPlaybackDevice
```cpp
virtual int bytertc::IAudioDeviceManager::setAudioPlaybackDevice(
    const char device_id[MAX_DEVICE_ID_LENGTH])
```
设置音频播放设备。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| device_id | **const char** | 音频播放设备 ID，可通过 [enumerateAudioPlaybackDevices](#IAudioDeviceManager-enumerateaudioplaybackdevices)<br/>获取。 |

**返回值**

+ 0：方法调用成功  
+ < 0：方法调用失败


**注意**
当你调用 [followSystemPlaybackDevice](#IAudioDeviceManager-followsystemplaybackdevice) 设置音频播放设备跟随系统后，将无法调用此接口设置音频播放设备。

<span id="IAudioDeviceManager-setaudiocapturedevice"></span>
### setAudioCaptureDevice
```cpp
virtual int bytertc::IAudioDeviceManager::setAudioCaptureDevice(
    const char device_id[MAX_DEVICE_ID_LENGTH])
```
设置音频采集设备。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| device_id | **const char** | 音频采集设备 ID，可通过 [enumerateAudioCaptureDevices](#IAudioDeviceManager-enumerateaudiocapturedevices) 获取。 |

**返回值**
方法调用结果  

+ 0：方法调用成功  
+ < 0：方法调用失败


**注意**
当你调用 [followSystemCaptureDevice](#IAudioDeviceManager-followsystemcapturedevice) 设置音频采集设备跟随系统后，将无法调用此接口设置音频采集设备。

<span id="IAudioDeviceManager-setaudioplaybackdevicevolume"></span>
### setAudioPlaybackDeviceVolume
```cpp
virtual int bytertc::IAudioDeviceManager::setAudioPlaybackDeviceVolume(
    unsigned int volume)
```
设置当前音频播放设备音量

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| volume | **unsigned int** | 音频播放设备音量，取值范围为 [0,255], 超出此范围设置无效。<br/>• [0,25] 接近无声；  <br/>• [25,75] 为低音量；  <br/>• [76,204] 为中音量；  <br/>• [205,255] 为高音量。 |

**返回值**
方法调用结果  

+ 0：方法调用成功  
+ < 0：方法调用失败


<span id="IAudioDeviceManager-getaudioplaybackdevicevolume"></span>
### getAudioPlaybackDeviceVolume
```cpp
virtual int bytertc::IAudioDeviceManager::getAudioPlaybackDeviceVolume(
    unsigned int* volume)
```
获取当前音频播放设备音量

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| volume | **unsigned int*** | 音频播放设备音量，范围应在 [0,255] 内。<br/>• [0,25] 接近无声；  <br/>• [25,75] 为低音量；  <br/>• [76,204] 为中音量；  <br/>• [205,255] 为高音量。 |

**返回值**
方法调用结果  

+ 0：方法调用成功  
+ < 0：方法调用失败


<span id="IAudioDeviceManager-setaudiocapturedevicevolume"></span>
### setAudioCaptureDeviceVolume
```cpp
virtual int bytertc::IAudioDeviceManager::setAudioCaptureDeviceVolume(
    unsigned int volume)
```
设置当前音频采集设备音量

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| volume | **unsigned int** | 音频采集设备音量，取值范围为 [0,255], 超出此范围设置无效。<br/>• [0,25] 接近无声；  <br/>• [25,75] 为低音量；  <br/>• [76,204] 为中音量；  <br/>• [205,255] 为高音量。 |

**返回值**
方法调用结果  

+ 0：方法调用成功  
+ < 0：方法调用失败


<span id="IAudioDeviceManager-getaudiocapturedevicevolume"></span>
### getAudioCaptureDeviceVolume
```cpp
virtual int bytertc::IAudioDeviceManager::getAudioCaptureDeviceVolume(
    unsigned int* volume)
```
获取当前音频采集设备音量

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| volume | **unsigned int*** | 音频采集设备音量，范围应在 [0,255] 内。<br/>• [0,25] 接近无声；  <br/>• [25,75] 为低音量；  <br/>• [76,204] 为中音量；  <br/>• [205,255] 为高音量。 |

**返回值**
方法调用结果  

+ 0：方法调用成功  
+ < 0：方法调用失败


<span id="IAudioDeviceManager-setaudioplaybackdevicemute"></span>
### setAudioPlaybackDeviceMute
```cpp
virtual int bytertc::IAudioDeviceManager::setAudioPlaybackDeviceMute(
    bool mute)
```
设置当前音频播放设备静音状态，默认为非静音。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mute | **bool** | • true：静音  <br/>• false：非静音 |

**返回值**
方法调用结果  

+ 0：方法调用成功  
+ < 0：方法调用失败


<span id="IAudioDeviceManager-getaudioplaybackdevicemute"></span>
### getAudioPlaybackDeviceMute
```cpp
virtual int bytertc::IAudioDeviceManager::getAudioPlaybackDeviceMute(
    bool* mute)
```
获取当前音频播放设备是否静音的信息。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mute | **bool*** | • true：静音  <br/>• false：非静音 |

**返回值**
方法调用结果  

+ 0：方法调用成功  
+ < 0：方法调用失败


<span id="IAudioDeviceManager-setaudiocapturedevicemute"></span>
### setAudioCaptureDeviceMute
```cpp
virtual int bytertc::IAudioDeviceManager::setAudioCaptureDeviceMute(
    bool mute)
```
设置当前音频采集设备静音状态，默认为非静音。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mute | **bool** | • true：静音  <br/>• false：非静音 |

**返回值**
方法调用结果  

+ 0：方法调用成功  
+ < 0：方法调用失败


<span id="IAudioDeviceManager-getaudiocapturedevicemute"></span>
### getAudioCaptureDeviceMute
```cpp
virtual int bytertc::IAudioDeviceManager::getAudioCaptureDeviceMute(
    bool* mute)
```
获取当前音频采集设备是否静音的信息。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mute | **bool*** | • true：静音  <br/>• false：非静音 |

**返回值**
方法调用结果  

+ 0：方法调用成功  
+ < 0：方法调用失败


<span id="IAudioDeviceManager-getaudioplaybackdevice"></span>
### getAudioPlaybackDevice
```cpp
virtual int bytertc::IAudioDeviceManager::getAudioPlaybackDevice(
    char device_id[MAX_DEVICE_ID_LENGTH])
```
获取当前音频播放设备 ID。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| device_id | **char** | 音频播放设备 ID |

**返回值**
方法调用结果  

+ 0：方法调用成功  
+ < 0：方法调用失败


<span id="IAudioDeviceManager-getaudiocapturedevice"></span>
### getAudioCaptureDevice
```cpp
virtual int bytertc::IAudioDeviceManager::getAudioCaptureDevice(
    char device_id[MAX_DEVICE_ID_LENGTH])
```
获取当前音频采集设备 ID。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| device_id | **char** | 音频采集设备 ID，使用方负责按 MAX_DEVICE_ID_LENGTH 大小，分配与释放内存 |

**返回值**
方法调用结果  

+ 0：方法调用成功  
+ < 0：方法调用失败


<span id="IAudioDeviceManager-initaudioplaybackdevicefortest"></span>
### initAudioPlaybackDeviceForTest
```cpp
virtual int bytertc::IAudioDeviceManager::initAudioPlaybackDeviceForTest(
    const char deviceId[MAX_DEVICE_ID_LENGTH])
```
尝试初始化音频播放设备，可检测出设备不存在、权限被拒绝/禁用等异常问题。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| deviceId | **const char** | 设备索引号 |

**返回值**
设备状态错误码

+ 0: 设备检测结果正常
+ -1: 接口状态不正确，例如在正常启动采集后再调用该接口进行检测
+ -2: 采集设备无麦克风权限，尝试初始化设备失败
+ -3: 设备不存在，当前没有设备或设备被移除时返回
+ -4: 设备音频格式不支持
+ -5: 其它原因错误


**注意**
1. 该接口需在进房前调用；  2. 检测成功不代表设备一定可以启动成功，还可能因设备被其他应用进程独占，或 CPU/内存不足等原因导致启动失败。


<span id="IAudioDeviceManager-initaudiocapturedevicefortest"></span>
### initAudioCaptureDeviceForTest
```cpp
virtual int bytertc::IAudioDeviceManager::initAudioCaptureDeviceForTest(
    const char deviceId[MAX_DEVICE_ID_LENGTH])
```
尝试初始化音频采集设备，可检测设备不存在、权限被拒绝/禁用等异常问题。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| deviceId | **const char** | 设备索引 |

**返回值**
设备状态错误码

+ 0: 设备检测结果正常
+ -1: 接口状态不正确，例如在正常启动采集后再调用该接口进行检测
+ -2: 采集设备无麦克风权限，尝试初始化设备失败
+ -3: 设备不存在，当前没有设备或设备被移除时返回
+ -4: 设备音频格式不支持
+ -5: 其它原因错误


**注意**
1. 该接口需在进房前调用;  2. 检测成功不代表设备一定可以启动成功，还可能因设备被其他应用进程独占，或 CPU/内存不足等原因导致启动失败。


<span id="IAudioDeviceManager-startaudioplaybackdevicetest"></span>
### startAudioPlaybackDeviceTest
```cpp
virtual int bytertc::IAudioDeviceManager::startAudioPlaybackDeviceTest(
    const char* test_audio_file_path,
    int indication_interval)
```
启动音频播放设备检测。测试启动后，循环播放指定的音频文件，同时将通过 `onAudioPlaybackDeviceTestVolume` 回调播放时的音量信息。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| test_audio_file_path | **const char*** | 指定播放设备检测的音频文件网络地址。支持的格式包括 mp3，aac，m4a，3gp 和 wav。 |
| indication_interval | **int** | 设置 `onAudioPlaybackDeviceTestVolume` 音量回调的时间间隔，推荐设置为 200 毫秒或以上。单位为毫秒。最小值为 10 毫秒。 |

**返回值**
方法调用结果  

+ 0：方法调用成功  
+ < 0：方法调用失败


**注意**

+ 该方法可在进房前和进房后调用，不可与其它音频设备测试功能同时应用。  
+ 调用 [stopAudioPlaybackDeviceTest](#IAudioDeviceManager-stopaudioplaybackdevicetest) 可以停止测试。


<span id="IAudioDeviceManager-stopaudioplaybackdevicetest"></span>
### stopAudioPlaybackDeviceTest
```cpp
virtual int bytertc::IAudioDeviceManager::stopAudioPlaybackDeviceTest()
```
停止音频播放测试。  <br>

**返回值**
方法调用结果  

+ 0：方法调用成功  
+ < 0：方法调用失败


**注意**
调用 [startAudioPlaybackDeviceTest](#IAudioDeviceManager-startaudioplaybackdevicetest) 后，调用本方法停止测试。

<span id="IAudioDeviceManager-startaudiodevicerecordtest"></span>
### startAudioDeviceRecordTest
```cpp
virtual int bytertc::IAudioDeviceManager::startAudioDeviceRecordTest(
    int indication_interval)
```
开始音频采集设备和音频播放设备测试。<br>
建议提前调用 `enableAudioPropertiesReport` 启用音频信息提示，测试开始后，音频设备开始采集本地声音，可以通过 `onLocalAudioPropertiesReport` 获取采集音量。<br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| indication_interval | **int** | 测试录音播放时触发 `onLocalAudioPropertiesReport` 播放音量回调，本参数指定了该周期回调的时间间隔，单位为毫秒。建议设置到大于 200 毫秒。最小不得少于 10 毫秒。 |

**返回值**
方法调用结果  

+ 0：方法调用成功  
+ < 0：方法调用失败


**注意**

+ 该方法在进房前后均可调用。且不可与其它音频设备测试功能同时应用。  
+ 调用本接口 30 s 后，采集自动停止，并开始播放采集到的声音。录音播放完毕后，设备测试流程自动结束。你也可以在 30 s 内调用 [stopAudioDeviceRecordAndPlayTest](#IAudioDeviceManager-stopaudiodevicerecordandplaytest)  来停止采集并开始播放此前采集到的声音。
+ 调用 [stopAudioDevicePlayTest](#IAudioDeviceManager-stopaudiodeviceplaytest) 可以停止音频设备采集和播放测试。
+ 该方法仅在本地进行音频设备测试，不涉及网络连接。  


<span id="IAudioDeviceManager-stopaudiodevicerecordandplaytest"></span>
### stopAudioDeviceRecordAndPlayTest
```cpp
virtual int bytertc::IAudioDeviceManager::stopAudioDeviceRecordAndPlayTest()
```
停止采集本地音频，并开始播放采集到的声音。录音播放完毕后，设备测试流程结束。<br>
调用 [startAudioDeviceRecordTest](#IAudioDeviceManager-startaudiodevicerecordtest) 30 s 内调用本接口来停止采集并开始播放此前采集到的声音。

**返回值**
方法调用结果  

+ 0：方法调用成功  
+ < 0：方法调用失败


**注意**
调用本接口开始播放录音后，可以在播放过程中调用 [stopAudioDevicePlayTest](#IAudioDeviceManager-stopaudiodeviceplaytest) 停止播放。

<span id="IAudioDeviceManager-stopaudiodeviceplaytest"></span>
### stopAudioDevicePlayTest
```cpp
virtual int bytertc::IAudioDeviceManager::stopAudioDevicePlayTest()
```
停止由调用 [startAudioDeviceRecordTest](#IAudioDeviceManager-startaudiodevicerecordtest) 开始的音频播放设备测试。<br>
在音频播放设备测试自动结束前，可调用本接口停止音频采集与播放测试。

**返回值**
方法调用结果  

+ 0：方法调用成功  
+ < 0：方法调用失败


# IAudioMixingManager
```cpp
class bytertc::IAudioMixingManager
```

混音管理类


`Defined in : bytertc_audio_mixing_manager.h`

## 成员函数

| 返回 | 名称 |
| --- | --- |
| **virtual void** | [startAudioMixing](#IAudioMixingManager-startaudiomixing) |
| **virtual void** | [stopAudioMixing](#IAudioMixingManager-stopaudiomixing) |
| **virtual void** | [pauseAudioMixing](#IAudioMixingManager-pauseaudiomixing) |
| **virtual void** | [resumeAudioMixing](#IAudioMixingManager-resumeaudiomixing) |
| **virtual void** | [preloadAudioMixing](#IAudioMixingManager-preloadaudiomixing) |
| **virtual void** | [unloadAudioMixing](#IAudioMixingManager-unloadaudiomixing) |
| **virtual void** | [setAudioMixingVolume](#IAudioMixingManager-setaudiomixingvolume) |
| **virtual int** | [getAudioMixingDuration](#IAudioMixingManager-getaudiomixingduration) |
| **virtual int** | [getAudioMixingCurrentPosition](#IAudioMixingManager-getaudiomixingcurrentposition) |
| **virtual int** | [getAudioMixingPlaybackDuration](#IAudioMixingManager-getaudiomixingplaybackduration) |
| **virtual void** | [setAudioMixingPosition](#IAudioMixingManager-setaudiomixingposition) |
| **virtual void** | [setAudioMixingDualMonoMode](#IAudioMixingManager-setaudiomixingdualmonomode) |
| **virtual void** | [setAudioMixingPitch](#IAudioMixingManager-setaudiomixingpitch) |
| **virtual int** | [setAudioMixingPlaybackSpeed](#IAudioMixingManager-setaudiomixingplaybackspeed) |
| **virtual void** | [setAudioMixingProgressInterval](#IAudioMixingManager-setaudiomixingprogressinterval) |
| **virtual void** | [setAudioMixingLoudness](#IAudioMixingManager-setaudiomixingloudness) |
| **virtual void** | [enableAudioMixingFrame](#IAudioMixingManager-enableaudiomixingframe) |
| **virtual void** | [disableAudioMixingFrame](#IAudioMixingManager-disableaudiomixingframe) |
| **virtual int** | [pushAudioMixingFrame](#IAudioMixingManager-pushaudiomixingframe) |
| **virtual int** | [getAudioTrackCount](#IAudioMixingManager-getaudiotrackcount) |
| **virtual void** | [selectAudioTrack](#IAudioMixingManager-selectaudiotrack) |


## 函数说明
<span id="IAudioMixingManager-startaudiomixing"></span>
### startAudioMixing
```cpp
virtual void bytertc::IAudioMixingManager::startAudioMixing(
    int mix_id,
    const char * file_path,
    const AudioMixingConfig& config)
```
开始播放音频文件。
可以通过传入不同的 ID 和 filepath 多次调用本方法，以实现同时播放多个混音文件，实现混音叠加。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mix_id | **int** | 混音 ID。用于标识混音，请保证混音 ID 唯一性。  <br/>如果使用相同的 ID 重复调用本方法后，前一次混音会停止，后一次混音开始，SDK 会使用 `onAudioMixingStateChanged` 回调通知前一次混音已停止。 |
| file_path | **const char*** | 用于混音文件路径。<br/>支持在线文件的 URL、和本地文件的绝对路径。对于在线文件的 URL，仅支持 https 协议。<br/>推荐的音频文件采样率：8KHz、16KHz、22.05KHz、44.1KHz、48KHz。<br/>不同平台支持的音频文件格式:<br/><table><br/><tr><th></th><th>mp3</th><th>mp4</th><th>aac</th><th>m4a</th><th>3gp</th><th>wav</th><th>ogg</th><th>ts</th><th>wma</th></tr><br/><tr><td>Android</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td></tr><br/><tr><td>iOS</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td><td></td></tr><br/><tr><td>Windows</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td>Y</td><td>Y</td></tr><br/></table> |
| config | **const AudioMixingConfig&** | 混音配置  <br/>可以设置混音的播放次数、是否本地播放混音、以及是否将混音发送至远端，详见 [AudioMixingConfig](Windows-keytype.md#audiomixingconfig)。 |


**注意**

+ 如果已经通过 [preloadAudioMixing](#IAudioMixingManager-preloadaudiomixing) 将文件加载至内存，确保此处的 ID 与预加载时设置的 ID 相同。  
+ 调用本方法播放音频文件后，关于当前的混音状态，会收到回调 `onAudioMixingStateChanged`。  
+ 开始播放音频文件后，可以调用 [stopAudioMixing](#IAudioMixingManager-stopaudiomixing) 方法停止播放音频文件。  
+ 本方法的混音数据来源于外部文件，而 [enableAudioMixingFrame](#IAudioMixingManager-enableaudiomixingframe) 的混音数据来源于外部缓存且音频格式为 PCM，这两种混音方式可以共存。


<span id="IAudioMixingManager-stopaudiomixing"></span>
### stopAudioMixing
```cpp
virtual void bytertc::IAudioMixingManager::stopAudioMixing(
    int mix_id)
```
停止播放音乐文件及混音

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mix_id | **int** | 混音 ID |


**注意**

+ 调用 [startAudioMixing](#IAudioMixingManager-startaudiomixing) 方法开始播放音乐文件及混音后，可以调用本方法停止播放音乐文件及混音。  
+ 调用本方法停止播放音乐文件后，SDK 会向本地回调通知已停止混音，见 `onAudioMixingStateChanged`。  
+ 调用本方法停止播放音乐文件后，该音乐文件会被自动卸载。


<span id="IAudioMixingManager-pauseaudiomixing"></span>
### pauseAudioMixing
```cpp
virtual void bytertc::IAudioMixingManager::pauseAudioMixing(
    int mix_id)
```
暂停播放音乐文件及混音

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mix_id | **int** | 混音 ID |


**注意**

+ 调用 [startAudioMixing](#IAudioMixingManager-startaudiomixing) 方法开始播放音乐文件及混音后，可以通过调用本方法暂停播放音乐文件及混音。  
+ 调用本方法暂停播放音乐文件及混音后，可调用 [resumeAudioMixing](#IAudioMixingManager-resumeaudiomixing) 方法恢复播放及混音。  
+ 调用本方法暂停播放音乐文件后，SDK 会向本地回调通知已暂停混音，见 `onAudioMixingStateChanged`。


<span id="IAudioMixingManager-resumeaudiomixing"></span>
### resumeAudioMixing
```cpp
virtual void bytertc::IAudioMixingManager::resumeAudioMixing(
    int mix_id)
```
恢复播放音乐文件及混音

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mix_id | **int** | 混音 ID |


**注意**

+ 调用 [pauseAudioMixing](#IAudioMixingManager-pauseaudiomixing) 方法暂停播放音乐文件及混音后，可以通过调用本方法恢复播放及混音。  
+ 调用本方法恢复播放音乐文件及混音后，SDK 会向本地回调通知音乐文件正在播放中，见 `onAudioMixingStateChanged`。


<span id="IAudioMixingManager-preloadaudiomixing"></span>
### preloadAudioMixing
```cpp
virtual void bytertc::IAudioMixingManager::preloadAudioMixing(
    int mix_id,
    const char* file_path)
```
预加载指定音乐文件到内存中，以避免频繁播放同一文件时的重复加载，减少 CPU 占用。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mix_id | **int** | 混音 ID。用于标识混音，请保证混音 ID 唯一性。  <br/>如果使用相同的 ID 重复调用本方法，后一次会覆盖前一次。  <br/>如果先调用 [startAudioMixing](#IAudioMixingManager-startaudiomixing)，再使用相同的 ID 调用本方法 ，会先回调 `onAudioMixingStateChanged` 通知上一个混音停止，然后加载后一个混音。  <br/>调用本方法预加载 A.mp3 后，如果需要使用相同的 ID 调用 [startAudioMixing](#IAudioMixingManager-startaudiomixing) 播放 B.mp3，请先调用 [unloadAudioMixing](#IAudioMixingManager-unloadaudiomixing) 卸载 A.mp3。 |
| file_path | **const char*** | 混音文件路径。<br/>支持本地文件的绝对路径。预加载的文件长度不得超过 20s。<br/>不同平台支持的音频文件格式: <br/><table><br/><tr><th></th><th>mp3</th><th>mp4</th><th>aac</th><th>m4a</th><th>3gp</th><th>wav</th><th>ogg</th><th>ts</th><th>wma</th></tr><br/><tr><td>Android</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td></tr><br/><tr><td>iOS</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td><td></td></tr><br/><tr><td>Windows</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td>Y</td><td>Y</td></tr><br/></table> |


**注意**

+ 本方法只是预加载指定音频文件，只有调用 [startAudioMixing](#IAudioMixingManager-startaudiomixing) 方法才开始播放指定音频文件。 
+ 调用本方法预加载音频文件后，关于当前的混音状态，会收到回调 `onAudioMixingStateChanged`。  
+ 调用本方法预加载的指定音频文件可以通过 [unloadAudioMixing](#IAudioMixingManager-unloadaudiomixing) 卸载。


<span id="IAudioMixingManager-unloadaudiomixing"></span>
### unloadAudioMixing
```cpp
virtual void bytertc::IAudioMixingManager::unloadAudioMixing(
    int mix_id)
```
卸载指定音乐文件

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mix_id | **int** | 混音 ID |


**注意**
不论音乐文件是否播放，调用本方法卸载该文件后，SDK 会回调通知混音已停止，见 `onAudioMixingStateChanged`。

<span id="IAudioMixingManager-setaudiomixingvolume"></span>
### setAudioMixingVolume
```cpp
virtual void bytertc::IAudioMixingManager::setAudioMixingVolume(
    int mix_id,
    int volume,
    AudioMixingType type)
```
调节指定混音的音量大小，包括音频文件混音和 PCM 混音。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mix_id | **int** | 需调节音量的混音 ID |
| volume | **int** | 混音音量相对原音量的比值。范围为 `[0, 400]`，建议范围是 `[0, 100]`。  <br/>• 0：静音  <br/>• 100：原始音量（默认值）  <br/>• 400: 最大可调音量 (自带溢出保护) |
| type | **AudioMixingType** | 混音类型。是否本地播放、以及是否发送到远端，详见 [AudioMixingType](Windows-keytype.md#audiomixingtype)。 |


**注意**
该方法仅对指定混音 ID 生效。移动端提供 `setAllAudioMixingVolume` 接口调节全部混音文件播放音量。

<span id="IAudioMixingManager-getaudiomixingduration"></span>
### getAudioMixingDuration
```cpp
virtual int bytertc::IAudioMixingManager::getAudioMixingDuration(
    int mix_id)
```
获取音乐文件时长

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mix_id | **int** | 混音 ID |

**返回值**

+ \>0: 成功, 音乐文件时长，单位为毫秒。  
+ < 0: 失败


**注意**
调用本方法获取音乐文件时长前，需要先调用 [preloadAudioMixing](#IAudioMixingManager-preloadaudiomixing) 或 [startAudioMixing](#IAudioMixingManager-startaudiomixing)。

<span id="IAudioMixingManager-getaudiomixingcurrentposition"></span>
### getAudioMixingCurrentPosition
```cpp
virtual int bytertc::IAudioMixingManager::getAudioMixingCurrentPosition(
    int mix_id)
```
获取音乐文件播放进度

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mix_id | **int** | 混音 ID |

**返回值**

+ \>0: 成功, 音乐文件播放进度，单位为毫秒。  
+ < 0: 失败


**注意**
调用本方法获取音乐文件播放进度前，需要先调用 [startAudioMixing](#IAudioMixingManager-startaudiomixing) 开始播放音乐文件。

<span id="IAudioMixingManager-getaudiomixingplaybackduration"></span>
### getAudioMixingPlaybackDuration
```cpp
virtual int bytertc::IAudioMixingManager::getAudioMixingPlaybackDuration(
    int mix_id)
```
获取混音音频文件的实际播放时长（单位：毫秒）。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mix_id | **int** | 混音 ID。 |

**返回值**

+ \>0: 实际播放时长。 
+ < 0: 失败。


**注意**

+ 实际播放时长指的是歌曲不受停止、跳转、倍速、卡顿影响的播放时长。例如，若歌曲正常播放到 1:30 时停止播放 30s 或跳转进度到 2:00, 随后继续正常播放 2分钟，则实际播放时长为 3分30秒。  
+ 调用本接口前，需要先调用 [startAudioMixing](#IAudioMixingManager-startaudiomixing) 开始播放指定音频文件。


<span id="IAudioMixingManager-setaudiomixingposition"></span>
### setAudioMixingPosition
```cpp
virtual void bytertc::IAudioMixingManager::setAudioMixingPosition(
    int mix_id,
    int position)
```
设置音频文件的起始播放位置

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mix_id | **int** | 混音 ID |
| position | **int** | 音频文件起始播放位置，单位为毫秒。  <br/>你可以通过 [getAudioMixingDuration](#IAudioMixingManager-getaudiomixingduration) 获取音频文件总时长，position 的值应小于音频文件总时长。 |


**注意**
在播放在线文件时，调用此接口可能造成播放延迟的现象。

<span id="IAudioMixingManager-setaudiomixingdualmonomode"></span>
### setAudioMixingDualMonoMode
```cpp
virtual void bytertc::IAudioMixingManager::setAudioMixingDualMonoMode(
    int mix_id,
    AudioMixingDualMonoMode mode)
```
设置当前音频文件的声道模式

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mix_id | **int** | 混音 ID |
| mode | **AudioMixingDualMonoMode** | 声道模式。默认的声道模式和源文件一致，详见 [AudioMixingDualMonoMode](Windows-keytype.md#audiomixingdualmonomode)。 |


**注意**

+ 调用本方法设置音频文件的声道模式前，需要先调用 [startAudioMixing](#IAudioMixingManager-startaudiomixing) 开始播放音频文件。
+ 此方法对 [enableAudioMixingFrame](#IAudioMixingManager-enableaudiomixingframe) 播放的音乐无效。


<span id="IAudioMixingManager-setaudiomixingpitch"></span>
### setAudioMixingPitch
```cpp
virtual void bytertc::IAudioMixingManager::setAudioMixingPitch(
    int mix_id,
    int pitch)
```
开启本地播放音乐文件变调功能，多用于 K 歌场景。  <br>
使用该方法，你可以对本地播放音乐文件的音调进行升调或降调等调整。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mix_id | **int** | 混音 ID |
| pitch | **int** | 相对于音乐文件原始音调的升高/降低值，取值范围[-12，12]，默认值为 0，即不做调整。  <br/>取值范围内每相邻两个值的音高距离相差半音，正值表示升调，负值表示降调，设置的绝对值越大表示音调升高或降低越多。  <br/>超出取值范围则设置失败，并且会触发 `onAudioMixingStateChanged` 回调，提示 [AudioMixingState](Windows-keytype.md#audiomixingstate) 状态为 `AUDIO_MIXING_STATE_FAILED` 混音播放失败，[AudioMixingError](Windows-keytype.md#audiomixingerror) 错误码为 `AUDIO_MIXING_ERROR_ID_TYPE_INVALID_PITCH` 设置混音文件音调不合法。 |


**注意**
本方法需要在调用 [startAudioMixing](#IAudioMixingManager-startaudiomixing) 开始播放音频文件后、调用 [stopAudioMixing](#IAudioMixingManager-stopaudiomixing) 停止播放音频文件前使用，否则会触发 `onAudioMixingStateChanged` 回调报错

<span id="IAudioMixingManager-setaudiomixingplaybackspeed"></span>
### setAudioMixingPlaybackSpeed
```cpp
virtual int bytertc::IAudioMixingManager::setAudioMixingPlaybackSpeed(
    int mix_id,
    int speed)
```
设置混音时音频文件的播放速度

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mix_id | **int** | 混音 ID |
| speed | **int** | 播放速度与原始文件速度的比例，单位：%，取值范围为 [50,200]，默认值为 100。  <br/>超出取值范围则设置失败，你会收到 `onAudioMixingStateChanged` 回调，提示 [AudioMixingState](Windows-keytype.md#audiomixingstate) 状态为 `kAudioMixingStateFailed` 混音播放失败，[AudioMixingError](Windows-keytype.md#audiomixingerror) 错误码为 `kAudioMixingErrorInValidPlaybackSpeed` 设置混音文件的播放速度不合法。 |


**注意**

+ 暂不支持对 PCM 音频数据进行变速调整。  
+ 你需要在调用 [startAudioMixing](#IAudioMixingManager-startaudiomixing) 开始混音，并且收到`onAudioMixingStateChanged` 回调提示 [AudioMixingState](Windows-keytype.md#audiomixingstate) 状态为 `kAudioMixingStatePlaying`，[AudioMixingError](Windows-keytype.md#audiomixingerror) 错误码为 `kAudioMixingErrorOk` 之后调用该方法。  
+ 在 [stopAudioMixing](#IAudioMixingManager-stopaudiomixing) 停止混音或 [unloadAudioMixing](#IAudioMixingManager-unloadaudiomixing) 卸载音频文件后调用该 API，会收到状态为 `kAudioMixingStateFailed` 错误码为 `kAudioMixingErrorIdNotFound` 的 `onAudioMixingStateChanged` 回调。


<span id="IAudioMixingManager-setaudiomixingprogressinterval"></span>
### setAudioMixingProgressInterval
```cpp
virtual void bytertc::IAudioMixingManager::setAudioMixingProgressInterval(
    int mix_id,
    int64_t interval)
```
设置混音时音频文件播放进度回调的间隔

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mix_id | **int** | 混音 ID  <br/>可以通过多次调用本接口传入不同的 ID 对多个 ID 进行间隔设置。 |
| interval | **int64_t** | 音频文件播放进度回调的时间间隔，单位毫秒。  <br/>• interval 的值为大于 0 的 10 的倍数，当设置的值不能被 10 整除时，则默认向上取整 10，如设为 52ms 时会默认调整为 60ms。设置完成后 SDK 将会按照设置的时间间隔触发 `onAudioMixingPlayingProgress` 回调。  <br/>• interval 的值小于等于 0 时，不会触发进度回调。 |


**注意**
本方法需要在调用 [startAudioMixing](#IAudioMixingManager-startaudiomixing) 开始播放音频文件后、调用 [stopAudioMixing](#IAudioMixingManager-stopaudiomixing) 停止播放音频文件前使用，否则会触发 `onAudioMixingStateChanged` 回调报错。  若想在音乐文件开始播放前设置播放进度回调间隔，你需调用 [startAudioMixing](#IAudioMixingManager-startaudiomixing) 在 [AudioMixingConfig](Windows-keytype.md#audiomixingconfig) 中设置时间间隔，开始播放后可以通过此接口更新回调间隔。


<span id="IAudioMixingManager-setaudiomixingloudness"></span>
### setAudioMixingLoudness
```cpp
virtual void bytertc::IAudioMixingManager::setAudioMixingLoudness(
    int mix_id,
    float loudness)
```
如果你需要使用 `enableVocalInstrumentBalance` 对混音音频文件/PCM 音频数据进行音量调整，你必须通过此接口传入其原始响度。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mix_id | **int** | 混音 ID |
| loudness | **float** | 原始响度，单位：lufs，取值范围为 [-70.0, 0.0]。  <br/>当设置的值小于 -70.0lufs 时，则默认调整为 -70.0lufs，大于 0.0lufs 时，则不对该响度做音均衡处理。默认值为 1.0lufs，即不做处理。 |


**注意**
建议在 [startAudioMixing](#IAudioMixingManager-startaudiomixing) 开始播放音频文件之前调用该接口，以免播放过程中的音量突变导致听感体验下降。

<span id="IAudioMixingManager-enableaudiomixingframe"></span>
### enableAudioMixingFrame
```cpp
virtual void bytertc::IAudioMixingManager::enableAudioMixingFrame(
    int mix_id,
    AudioMixingType type)
```
启动外部音频流混音
启动 PCM 音频数据混音。<br>
要实现多个 PCM 音频数据混音，多次调用本方法，并传入不同的 mix_id。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mix_id | **int** | 混音 ID，用于标识混音，保证混音 ID 唯一性。  <br/>如果使用相同的 ID 重复调用本方法后，前一次混音会停止，后一次混音开始，会收到 `onAudioMixingStateChanged` 通知前一次混音已停止。 |
| type | **AudioMixingType** | 混音播放类型  <br/>是否本地播放、以及是否发送到远端，详见 [AudioMixingType](Windows-keytype.md#audiomixingtype)。 |


**注意**

+ 必须先调用本方法启动 PCM 音频数据混音，随后调用 [pushAudioMixingFrame](#IAudioMixingManager-pushaudiomixingframe) 方法，才会开始混音。 
+ 如要结束 PCM 音频数据混音，使用 [disableAudioMixingFrame](#IAudioMixingManager-disableaudiomixingframe)。


<span id="IAudioMixingManager-disableaudiomixingframe"></span>
### disableAudioMixingFrame
```cpp
virtual void bytertc::IAudioMixingManager::disableAudioMixingFrame(
    int mix_id)
```
关闭 PCM 混音

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mix_id | **int** | 混音 ID。 |


<span id="IAudioMixingManager-pushaudiomixingframe"></span>
### pushAudioMixingFrame
```cpp
virtual int bytertc::IAudioMixingManager::pushAudioMixingFrame(
    int mix_id,
    IAudioFrame* audio_frame)
```
推送 PCM 音频帧数据用于混音

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mix_id | **int** | 混音 ID。 |
| audio_frame | **IAudioFrame*** | 音频帧，详见 [IAudioFrame](Windows-keytype.md#iaudioframe)。 |

**返回值**

+ 0: 成功  
+ < 0: 失败


**注意**

+ 调用该方法前，须通过 [enableAudioMixingFrame](#IAudioMixingManager-enableaudiomixingframe) 启动外部音频流混音。  
+ 使用参考建议：首次推送数据，请在应用侧先缓存一定数据（如 100 毫秒），然后一次性推送过去；此后的推送操作定时 10 毫秒一次，并且每次的音频数据量为 10 毫秒数据量。要暂停播放，暂停推送即可。


<span id="IAudioMixingManager-getaudiotrackcount"></span>
### getAudioTrackCount
```cpp
virtual int bytertc::IAudioMixingManager::getAudioTrackCount(
    int mix_id)
```
获取当前音频文件的音轨索引

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mix_id | **int** | 混音 ID |

**返回值**
方法调用结果 

+ ≥ 0：成功，返回当前音频文件的音轨索引  
+ < 0：方法调用失败


**注意**

+ 调用本方法获取音频文件的音轨前，需要先调用 [startAudioMixing](#IAudioMixingManager-startaudiomixing) 开始播放音频文件。
+ 此方法对 [enableAudioMixingFrame](#IAudioMixingManager-enableaudiomixingframe) 播放的音频无效。


<span id="IAudioMixingManager-selectaudiotrack"></span>
### selectAudioTrack
```cpp
virtual void bytertc::IAudioMixingManager::selectAudioTrack(
    int mix_id,
    int audio_track_index)
```
指定当前音频文件的播放音轨

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mix_id | **int** | 混音 ID |
| audio_track_index | **int** | 指定的播放音轨  <br/>设置的参数值需要小于或等于 [getAudioTrackCount](#IAudioMixingManager-getaudiotrackcount) 的返回值 |


**注意**

+ 调用本方法设置音频文件的音轨前，需要先调用 [startAudioMixing](#IAudioMixingManager-startaudiomixing) 开始播放音频文件。
+ 此方法对 [enableAudioMixingFrame](#IAudioMixingManager-enableaudiomixingframe) 播放的音乐无效。


# IKTVPlayer
```cpp
class bytertc::IKTVPlayer
```

KTV 播放器接口。


`Defined in : bytertc_ktv_manager_interface.h`

## 成员函数

| 返回 | 名称 |
| --- | --- |
| **virtual void** | [setPlayerEventHandler](#IKTVPlayer-setplayereventhandler) |
| **virtual void** | [playMusic](#IKTVPlayer-playmusic) |
| **virtual void** | [pauseMusic](#IKTVPlayer-pausemusic) |
| **virtual void** | [resumeMusic](#IKTVPlayer-resumemusic) |
| **virtual void** | [stopMusic](#IKTVPlayer-stopmusic) |
| **virtual void** | [seekMusic](#IKTVPlayer-seekmusic) |
| **virtual void** | [setMusicVolume](#IKTVPlayer-setmusicvolume) |
| **virtual void** | [switchAudioTrackType](#IKTVPlayer-switchaudiotracktype) |
| **virtual void** | [setMusicPitch](#IKTVPlayer-setmusicpitch) |


## 函数说明
<span id="IKTVPlayer-setplayereventhandler"></span>
### setPlayerEventHandler
```cpp
virtual void bytertc::IKTVPlayer::setPlayerEventHandler(
    IKTVPlayerEventHandler *handler)
```
设置 KTV 播放器进度及状态回调接口。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| handler | **IKTVPlayerEventHandler*** | KTV 播放器回调类，参看 [IKTVPlayerEventHandler](Windows-callback.md#iktvplayereventhandler)。 |


<span id="IKTVPlayer-playmusic"></span>
### playMusic
```cpp
virtual void bytertc::IKTVPlayer::playMusic(
    const char* music_id,
    AudioTrackType track_type,
    AudioPlayType play_type)
```
播放歌曲。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| music_id | **const char*** | 音乐 ID。<br/>若同一 music_id 的歌曲正在播放，再次调用接口会从开始位置重新播放。若 music_id 对应的音频文件不存在会触发报错。 |
| track_type | **AudioTrackType** | 原唱伴唱类型，参看 [AudioTrackType](Windows-keytype.md#audiotracktype)。 |
| play_type | **AudioPlayType** | 音乐播放类型。参看 [AudioPlayType](Windows-keytype.md#audioplaytype)。 |


**注意**

+ 调用接口后，你会收到 [onPlayStateChange](Windows-callback.md#IKTVPlayerEventHandler-onplaystatechange) 回调歌曲播放状态。
+ 若音乐 ID 错误，会触发 [onPlayStateChange](Windows-callback.md#IKTVPlayerEventHandler-onplaystatechange) 回调，error_code 为 –3023，play_state 为 4。
+ 若未进房，会触发 [onPlayStateChange](Windows-callback.md#IKTVPlayerEventHandler-onplaystatechange) 回调，error_code 为 –3022，play_state 为 4。
+ 若音乐文件不存在，会触发 [onPlayStateChange](Windows-callback.md#IKTVPlayerEventHandler-onplaystatechange) 回调，error_code 为 –3020，play_state 为 4。


<span id="IKTVPlayer-pausemusic"></span>
### pauseMusic
```cpp
virtual void bytertc::IKTVPlayer::pauseMusic(
    const char *music_id)
```
暂停播放歌曲。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| music_id | **const char*** | 音乐 ID。 |


**注意**

+ 调用接口后，你会收到 [onPlayStateChange](Windows-callback.md#IKTVPlayerEventHandler-onplaystatechange) 回调歌曲播放状态。
+ 若音乐 ID 错误，会触发 [onPlayStateChange](Windows-callback.md#IKTVPlayerEventHandler-onplaystatechange) 回调，error_code 为 –3023，play_state 为 4。
+ 若未进房，会触发 [onPlayStateChange](Windows-callback.md#IKTVPlayerEventHandler-onplaystatechange) 回调，error_code 为 –3022，play_state 为 4。


<span id="IKTVPlayer-resumemusic"></span>
### resumeMusic
```cpp
virtual void bytertc::IKTVPlayer::resumeMusic(
    const char *music_id)
```
继续播放歌曲。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| music_id | **const char*** | 音乐 ID。 |


**注意**

+ 调用接口后，你会收到 [onPlayStateChange](Windows-callback.md#IKTVPlayerEventHandler-onplaystatechange) 回调歌曲播放状态。
+ 若音乐 ID 错误，会触发 [onPlayStateChange](Windows-callback.md#IKTVPlayerEventHandler-onplaystatechange) 回调，error_code 为 –3023，play_state 为 4。
+ 若未进房，会触发 [onPlayStateChange](Windows-callback.md#IKTVPlayerEventHandler-onplaystatechange) 回调，error_code 为 –3022，play_state 为 4。


<span id="IKTVPlayer-stopmusic"></span>
### stopMusic
```cpp
virtual void bytertc::IKTVPlayer::stopMusic(
    const char *music_id)
```
停止播放歌曲。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| music_id | **const char*** | 音乐 ID。 |


**注意**

+ 调用接口后，你会收到 [onPlayStateChange](Windows-callback.md#IKTVPlayerEventHandler-onplaystatechange) 回调歌曲播放状态。
+ 若音乐 ID 错误，会触发 [onPlayStateChange](Windows-callback.md#IKTVPlayerEventHandler-onplaystatechange) 回调，error_code 为 –3023，play_state 为 4。
+ 若未进房，会触发 [onPlayStateChange](Windows-callback.md#IKTVPlayerEventHandler-onplaystatechange) 回调，error_code 为 –3022，play_state 为 4。


<span id="IKTVPlayer-seekmusic"></span>
### seekMusic
```cpp
virtual void bytertc::IKTVPlayer::seekMusic(
    const char *music_id,
    int position)
```
设置音乐文件的起始播放位置。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| music_id | **const char*** | 音乐 ID。 |
| position | **int** | 音乐起始位置，单位为毫秒，取值小于音乐文件总时长。 |


**注意**

+ 调用本接口时音乐必须处于播放中状态。
+ 调用接口后，你会收到 [onPlayStateChange](Windows-callback.md#IKTVPlayerEventHandler-onplaystatechange) 回调歌曲播放状态。
+ 若音乐 ID 错误，会触发 [onPlayStateChange](Windows-callback.md#IKTVPlayerEventHandler-onplaystatechange) 回调，error_code 为 –3023，play_state 为 4。
+ 若未进房，会触发 [onPlayStateChange](Windows-callback.md#IKTVPlayerEventHandler-onplaystatechange) 回调，error_code 为 –3022，play_state 为 4。


<span id="IKTVPlayer-setmusicvolume"></span>
### setMusicVolume
```cpp
virtual void bytertc::IKTVPlayer::setMusicVolume(
    const char *music_id,
    int volume)
```
设置歌曲播放音量，只能在开始播放后进行设置。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| music_id | **const char*** | 音乐 ID。 |
| volume | **int** | 歌曲播放音量，调节范围：[0,400]。<br/>• 0：静音。<br/>• 100：原始音量。<br/>• 400: 原始音量的 4 倍(自带溢出保护)。 |


**注意**

+ 调用本接口时音乐必须处于播放中状态。
+ 若设置的音量大于 400，则按最大值 400 进行调整；若设置的音量小于 0，则按最小值 0 进行调整。
+ 若音乐 ID 错误，会触发 [onPlayStateChange](Windows-callback.md#IKTVPlayerEventHandler-onplaystatechange) 回调，error_code 为 –3023，play_state 为 4。
+ 若未进房，会触发 [onPlayStateChange](Windows-callback.md#IKTVPlayerEventHandler-onplaystatechange) 回调，error_code 为 –3022，play_state 为 4。


<span id="IKTVPlayer-switchaudiotracktype"></span>
### switchAudioTrackType
```cpp
virtual void bytertc::IKTVPlayer::switchAudioTrackType(
    const char *music_id)
```
切换歌曲原唱伴唱。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| music_id | **const char*** | 音乐 ID。 |


**注意**
调用本接口时音乐必须处于播放中状态。

<span id="IKTVPlayer-setmusicpitch"></span>
### setMusicPitch
```cpp
virtual void bytertc::IKTVPlayer::setMusicPitch(
    const char* music_id,
    int pitch)
```
对播放中的音乐设置升降调信息。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| music_id | **const char*** | 音乐 ID。 |
| pitch | **int** | 相对于音乐文件原始音调的升高/降低值，取值范围 [-12，12]，默认值为 0，即不做调整。<br/>取值范围内每相邻两个值的音高距离相差半音，正值表示升调，负值表示降调，设置的绝对值越大表示音调升高或降低越多。 |


**注意**

+ 调用本接口时音乐必须处于播放中状态。
+ 若设置的 pitch 大于 12，则按最大值 12 进行调整；若设置的 pitch 小于 –12，，则按最小值 –12 进行调整。
+ 若音乐 ID 错误，会触发 [onPlayStateChange](Windows-callback.md#IKTVPlayerEventHandler-onplaystatechange) 回调，error_code 为 –3023，play_state 为 4。
+ 若未进房，会触发 [onPlayStateChange](Windows-callback.md#IKTVPlayerEventHandler-onplaystatechange) 回调，error_code 为 –3022，play_state 为 4。


# IKTVManager
```cpp
class bytertc::IKTVManager
```

KTV 管理接口。


`Defined in : bytertc_ktv_manager_interface.h`

## 成员函数

| 返回 | 名称 |
| --- | --- |
| **virtual void** | [setMaxCacheSize](#IKTVManager-setmaxcachesize) |
| **virtual void** | [setKTVEventHandler](#IKTVManager-setktveventhandler) |
| **virtual void** | [getMusicList](#IKTVManager-getmusiclist) |
| **virtual void** | [searchMusic](#IKTVManager-searchmusic) |
| **virtual void** | [getHotMusic](#IKTVManager-gethotmusic) |
| **virtual void** | [getMusicDetail](#IKTVManager-getmusicdetail) |
| **virtual int** | [downloadMusic](#IKTVManager-downloadmusic) |
| **virtual int** | [downloadLyric](#IKTVManager-downloadlyric) |
| **virtual int** | [downloadMidi](#IKTVManager-downloadmidi) |
| **virtual void** | [cancelDownload](#IKTVManager-canceldownload) |
| **virtual void** | [clearCache](#IKTVManager-clearcache) |
| **virtual IKTVPlayer*** | [getPlayer](#IKTVManager-getplayer) |


## 函数说明
<span id="IKTVManager-setmaxcachesize"></span>
### setMaxCacheSize
```cpp
virtual void bytertc::IKTVManager::setMaxCacheSize(
    int max_cache_size_MB)
```
设置歌曲文件最大占用的本地缓存。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| max_cache_size_MB | **int** | 本地缓存，单位 MB。<br/>设置值小于等于 0 时，使用默认值 1024 MB。 |


<span id="IKTVManager-setktveventhandler"></span>
### setKTVEventHandler
```cpp
virtual void bytertc::IKTVManager::setKTVEventHandler(
    IKTVEventHandler *ktvEventHandler)
```
设置 KTV 回调接口。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| ktvEventHandler | **IKTVEventHandler*** | KTV 回调类，参看 [IKTVEventHandler](Windows-callback.md#iktveventhandler)。 |


<span id="IKTVManager-getmusiclist"></span>
### getMusicList
```cpp
virtual void bytertc::IKTVManager::getMusicList(
    int page_num,
    int page_size,
    int filters)
```
获取歌曲列表。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| page_num | **int** | 页码，默认从 1 开始。 |
| page_size | **int** | 每页显示歌曲的最大数量，取值范围 [1,99]。 |
| filters | **int** | 歌曲过滤方式，参看 [MusicFilterType](Windows-keytype.md#musicfiltertype)。多个过滤方式可以按位或组合。 |


**注意**
调用接口后，你会收到 [onMusicListResult](Windows-callback.md#IKTVEventHandler-onmusiclistresult) 回调歌曲列表。

<span id="IKTVManager-searchmusic"></span>
### searchMusic
```cpp
virtual void bytertc::IKTVManager::searchMusic(
    const char* key_world,
    int page_num,
    int page_size,
    int filters)
```
根据关键词搜索歌曲。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| key_world | **const char*** | 关键词，字符串长度最大为 20 个字符。 |
| page_num | **int** | 页码，默认从 1 开始。 |
| page_size | **int** | 每页显示歌曲的最大数量，取值范围 [1,99]。 |
| filters | **int** | 歌曲过滤方式，参看 [MusicFilterType](Windows-keytype.md#musicfiltertype)。多个过滤方式可以按位或组合。 |


**注意**
调用接口后，你会收到 [onSearchMusicResult](Windows-callback.md#IKTVEventHandler-onsearchmusicresult) 回调歌曲列表。

<span id="IKTVManager-gethotmusic"></span>
### getHotMusic
```cpp
virtual void bytertc::IKTVManager::getHotMusic(
    int hot_types,
    int filters)
```
根据热榜类别获取每个榜单的歌曲列表。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| hot_types | **int** | 热榜类别，参看 [MusicHotType](Windows-keytype.md#musichottype)。多个热榜类别可以按位或组合。 |
| filters | **int** | 歌曲过滤方式，参看 [MusicFilterType](Windows-keytype.md#musicfiltertype)。多个过滤方式可以按位或组合。 |


**注意**
调用接口后，你会收到 [onHotMusicResult](Windows-callback.md#IKTVEventHandler-onhotmusicresult) 回调歌曲列表。

<span id="IKTVManager-getmusicdetail"></span>
### getMusicDetail
```cpp
virtual void bytertc::IKTVManager::getMusicDetail(
    const char* music_id)
```
获取音乐详细信息。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| music_id | **const char*** | 音乐 ID。 |


**注意**
调用接口后，你会收到 [onMusicDetailResult](Windows-callback.md#IKTVEventHandler-onmusicdetailresult) 回调。

<span id="IKTVManager-downloadmusic"></span>
### downloadMusic
```cpp
virtual int bytertc::IKTVManager::downloadMusic(
    const char* music_id)
```
下载音乐。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| music_id | **const char*** | 音乐 ID。 |

**返回值**
下载任务 ID。


**注意**

+ 若音乐下载成功，你会收到 [onDownloadSuccess](Windows-callback.md#IKTVEventHandler-ondownloadsuccess) 回调。
+ 若音乐下载失败，你会收到 [onDownloadFailed](Windows-callback.md#IKTVEventHandler-ondownloadfailed) 回调。
+ 音乐下载进度更新时，你会收到 [onDownloadMusicProgress](Windows-callback.md#IKTVEventHandler-ondownloadmusicprogress) 回调。


<span id="IKTVManager-downloadlyric"></span>
### downloadLyric
```cpp
virtual int bytertc::IKTVManager::downloadLyric(
    const char* music_id,
    DownloadLyricType type)
```
下载歌词。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| music_id | **const char*** | 音乐 ID。 |
| type | **DownloadLyricType** | 歌词文件类型，参看 [DownloadLyricType](Windows-keytype.md#downloadlyrictype)。 |

**返回值**
下载任务 ID。


**注意**

+ 若歌词下载成功，你会收到 [onDownloadSuccess](Windows-callback.md#IKTVEventHandler-ondownloadsuccess) 回调。
+ 若歌词下载失败，你会收到 [onDownloadFailed](Windows-callback.md#IKTVEventHandler-ondownloadfailed) 回调。


<span id="IKTVManager-downloadmidi"></span>
### downloadMidi
```cpp
virtual int bytertc::IKTVManager::downloadMidi(
    const char* music_id)
```
下载 MIDI 文件。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| music_id | **const char*** | 音乐 ID。 |

**返回值**
下载任务 ID。


**注意**

+ 若文件下载成功，你会收到 [onDownloadSuccess](Windows-callback.md#IKTVEventHandler-ondownloadsuccess) 回调。
+ 若文件下载失败，你会收到 [onDownloadFailed](Windows-callback.md#IKTVEventHandler-ondownloadfailed) 回调。


<span id="IKTVManager-canceldownload"></span>
### cancelDownload
```cpp
virtual void bytertc::IKTVManager::cancelDownload(
    int download_id)
```
取消下载任务。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| download_id | **int** | 下载任务 ID。 |


<span id="IKTVManager-clearcache"></span>
### clearCache
```cpp
virtual void bytertc::IKTVManager::clearCache()
```
清除当前音乐缓存文件，包括音乐音频和歌词。


<span id="IKTVManager-getplayer"></span>
### getPlayer
```cpp
virtual IKTVPlayer *bytertc::IKTVManager::getPlayer()
```
获取 KTV 播放器。

**返回值**
KTV 播放器接口，参看 [IKTVPlayer](#iktvplayer)。


# IRangeAudio
```cpp
class bytertc::IRangeAudio
```

范围语音接口实例


`Defined in : bytertc_range_audio_interface.h`

## 成员函数

| 返回 | 名称 |
| --- | --- |
| **virtual void** | [enableRangeAudio](#IRangeAudio-enablerangeaudio) |
| **virtual int** | [updateReceiveRange](#IRangeAudio-updatereceiverange) |
| **virtual int** | [updatePosition](#IRangeAudio-updateposition) |
| **virtual void** | [registerRangeAudioObserver](#IRangeAudio-registerrangeaudioobserver) |
| **virtual int** | [setAttenuationModel](#IRangeAudio-setattenuationmodel) |


## 函数说明
<span id="IRangeAudio-enablerangeaudio"></span>
### enableRangeAudio
```cpp
virtual void bytertc::IRangeAudio::enableRangeAudio(
    bool enable)
```
开启/关闭范围语音功能。  <br>
范围语音是指，在同一 RTC 房间中设定的音频接收距离范围内，本地用户收听到的远端用户音频音量会随着远端用户的靠近/远离而放大/衰减；若远端用户在房间内的位置超出设定范围，则本地用户无法接收其音频。音频接收范围设置参看 [updateReceiveRange](#IRangeAudio-updatereceiverange)。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| enable | **bool** | 是否开启范围语音功能：  <br/>• true: 开启  <br/>• false: 关闭（默认） |


**注意**
该方法进房前后都可调用，为保证进房后范围语音效果的平滑切换，你需在该方法前先调用 [updatePosition](#IRangeAudio-updateposition) 设置自身位置坐标，然后开启该方法收听范围语音效果。

<span id="IRangeAudio-updatereceiverange"></span>
### updateReceiveRange
```cpp
virtual int bytertc::IRangeAudio::updateReceiveRange(
    const ReceiveRange &range)
```
更新本地用户的音频收听范围。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| range | **const ReceiveRange &** | 音频收听范围，参看 [ReceiveRange](Windows-keytype.md#receiverange)。 |

**返回值**
方法调用结果：  

+ 0：成功；  
+ !0: 失败。


**注意**
若此前你已调用 [registerRangeAudioObserver](#IRangeAudio-registerrangeaudioobserver) 注册了范围语音衰减系数监测器，房间内有任何用户调用该接口更新音频收听范围后，你都会收到 [onRangeAudioInfo](Windows-callback.md#IRangeAudioObserver-onrangeaudioinfo) 回调。

<span id="IRangeAudio-updateposition"></span>
### updatePosition
```cpp
virtual int bytertc::IRangeAudio::updatePosition(
    const Position &pos)
```
更新本地用户在房间内空间直角坐标系中的位置坐标。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| pos | **const Position &** | 三维坐标的值，默认为 [0, 0, 0]，参看 [Position](Windows-keytype.md#position-2) |

**返回值**
方法调用结果： 

+ 0：成功；  
+ !0：失败。


**注意**

+ 调用该接口更新坐标后，你需调用 [enableRangeAudio](#IRangeAudio-enablerangeaudio) 开启范围语音功能以收听范围语音效果。 
+ 若此前你已调用 [registerRangeAudioObserver](#IRangeAudio-registerrangeaudioobserver) 注册了范围语音衰减系数监测器，房间内有任何用户调用该接口更新自身位置坐标后，你都会收到 [onRangeAudioInfo](Windows-callback.md#IRangeAudioObserver-onrangeaudioinfo) 回调。


<span id="IRangeAudio-registerrangeaudioobserver"></span>
### registerRangeAudioObserver
```cpp
virtual void bytertc::IRangeAudio::registerRangeAudioObserver(
    IRangeAudioObserver* observer)
```
设置范围语音衰减系数监测器。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| observer | **IRangeAudioObserver*** | 范围语音衰减系数监测器。  <br/>设置后，SDK 会在监测到房间内有用户更新自身位置坐标或音频收听范围后，触发 [onRangeAudioInfo](Windows-callback.md#IRangeAudioObserver-onrangeaudioinfo) 回调。具体参看 [IRangeAudioObserver](Windows-callback.md#irangeaudioobserver)。 |


**注意**
该方法仅适用于手动订阅模式，自动订阅无需设置。

<span id="IRangeAudio-setattenuationmodel"></span>
### setAttenuationModel
```cpp
virtual int bytertc::IRangeAudio::setAttenuationModel(
    AttenuationType type,
    float coefficient)
```
设置范围语音的音量衰减模式。<br>
衰减模式更改后，[onRangeAudioInfo](Windows-callback.md#IRangeAudioObserver-onrangeaudioinfo) 回调将根据最后设置的衰减模式进行计算并返回音量衰减数值

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| type | **AttenuationType** | 音量衰减模式。默认为线性衰减。详见 [AttenuationType](Windows-keytype.md#attenuationtype)。 |
| coefficient | **float** | 指数衰减模式下的音量衰减系数，默认值为 1。范围 [0.1,100]，推荐设置为 `50`。数值越大，音量的衰减速度越快。 |

**返回值**
调用是否成功

+ `0`:调用成功
+ `-1`:调用失败。原因为在调用 [enableRangeAudio](#IRangeAudio-enablerangeaudio) 开启范围语音前或进房前调用本接口


**注意**
音量衰减范围通过 [updateReceiveRange](#IRangeAudio-updatereceiverange) 进行设置。

# IStandardPitchCollection
```cpp
class bytertc::IStandardPitchCollection
```

标准音高数据数组。


`Defined in : bytertc_sing_scoring_interface.h`

## 成员函数

| 返回 | 名称 |
| --- | --- |
| **virtual int** | [getCount](#IStandardPitchCollection-getcount) |
| **virtual StandardPitchInfo** | [getStandardPitchInfo](#IStandardPitchCollection-getstandardpitchinfo) |
| **virtual void** | [release](#IStandardPitchCollection-release) |


## 函数说明
<span id="IStandardPitchCollection-getcount"></span>
### getCount
```cpp
virtual int bytertc::IStandardPitchCollection::getCount()
```
获取歌词句子总数


<span id="IStandardPitchCollection-getstandardpitchinfo"></span>
### getStandardPitchInfo
```cpp
virtual StandardPitchInfo bytertc::IStandardPitchCollection::getStandardPitchInfo(
    int index)
```
获取每句歌词的标准音高信息

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| index | **int** | 歌词句子数，取值范围为 0 到调用 [getCount](#IStandardPitchCollection-getcount) 获取到的句子总数减 1。 |

**返回值**
标准音高数据，参看 [StandardPitchInfo](Windows-keytype.md#standardpitchinfo)。


<span id="IStandardPitchCollection-release"></span>
### release
```cpp
virtual void bytertc::IStandardPitchCollection::release()
```
销毁 IStandardPitchCollection 类，释放资源


# ISingScoringManager
```cpp
class bytertc::ISingScoringManager
```

K 歌评分管理接口。


`Defined in : bytertc_sing_scoring_interface.h`

## 成员函数

| 返回 | 名称 |
| --- | --- |
| **virtual int** | [initSingScoring](#ISingScoringManager-initsingscoring) |
| **virtual int** | [setSingScoringConfig](#ISingScoringManager-setsingscoringconfig) |
| **virtual IStandardPitchCollection*** | [getStandardPitchInfoCollection](#ISingScoringManager-getstandardpitchinfocollection) |
| **virtual int** | [startSingScoring](#ISingScoringManager-startsingscoring) |
| **virtual int** | [stopSingScoring](#ISingScoringManager-stopsingscoring) |
| **virtual int** | [getLastSentenceScore](#ISingScoringManager-getlastsentencescore) |
| **virtual int** | [getTotalScore](#ISingScoringManager-gettotalscore) |
| **virtual int** | [getAverageScore](#ISingScoringManager-getaveragescore) |
| **virtual** | [~ISingScoringManager](#ISingScoringManager-~isingscoringmanager) |


## 函数说明
<span id="ISingScoringManager-initsingscoring"></span>
### initSingScoring
```cpp
virtual int bytertc::ISingScoringManager::initSingScoring(
    const char* sing_scoring_appkey,
    const char* sing_scoring_token,
    ISingScoringEventHandler* handler)
```
初始化 K 歌评分。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| sing_scoring_appkey | **const char*** | K 歌评分密钥，用于鉴权验证 K 歌功能是否开通。 |
| sing_scoring_token | **const char*** | K 歌评分密钥，用于鉴权验证 K 歌功能是否开通。 |
| handler | **ISingScoringEventHandler*** | K 歌评分事件回调类，详见 [ISingScoringEventHandler](Windows-callback.md#isingscoringeventhandler)。 |

**返回值**

+ 0：配置成功。
+ -1：接口调用失败。
+ -2：未集成 K 歌评分模块。
+ \>0：其他错误，具体参看[错误码表](https://www.volcengine.com/docs/6489/148198)。


**注意**
输入正确的鉴权信息才可以使用 K 歌评分相关的功能，鉴权方式为离线鉴权，根据包名（bundleID）绑定 Appkey 及 Token，K 歌评分密钥请联系技术支持同学申请。

<span id="ISingScoringManager-setsingscoringconfig"></span>
### setSingScoringConfig
```cpp
virtual int bytertc::ISingScoringManager::setSingScoringConfig(
    const SingScoringConfig& config)
```
设置 K 歌评分参数。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| config | **const SingScoringConfig&** | K 歌评分的各项参数，详见 [SingScoringConfig](Windows-keytype.md#singscoringconfig)。 |

**返回值**

+ 0：配置成功。
+ -1：接口调用失败。
+ -2：未集成 K 歌评分模块。
+ \>0：其他错误，具体参看[错误码表](https://www.volcengine.com/docs/6489/148198)。


<span id="ISingScoringManager-getstandardpitchinfocollection"></span>
### getStandardPitchInfoCollection
```cpp
virtual IStandardPitchCollection* bytertc::ISingScoringManager::getStandardPitchInfoCollection(
    const char* midi_filepath)
```
获取标准音高数据。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| midi_filepath | **const char*** | 歌曲 midi 文件路径。 |

**返回值**
[IStandardPitchCollection](#istandardpitchcollection) 标准音高数据数组。


**注意**
请保证此接口传入的 midi 文件路径与 [setSingScoringConfig](#ISingScoringManager-setsingscoringconfig) 接口中传入的路径一致。

<span id="ISingScoringManager-startsingscoring"></span>
### startSingScoring
```cpp
virtual int bytertc::ISingScoringManager::startSingScoring(
    int position,
    int scoring_info_interval)
```
开始 K 歌评分。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| position | **int** | 开始评分时，音乐的播放进度，单位：ms。 |
| scoring_info_interval | **int** | 实时回调的时间间隔，单位：ms；默认 50 ms。最低间隔为 20 ms。 |

**返回值**

+ 0：配置成功。
+ -1：接口调用失败。
+ -2：未集成 K 歌评分模块。
+ \>0：其他错误，具体参看[错误码表](https://www.volcengine.com/docs/6489/148198)。


**注意**

+ 在调用 [initSingScoring](#ISingScoringManager-initsingscoring) 初始化 K 歌评分功能后调用该接口。
+ 调用该接口后，将会根据设置的回调时间间隔，收到评分结果 [onCurrentScoringInfo](Windows-callback.md#ISingScoringEventHandler-oncurrentscoringinfo) 回调。
+ 如果调用 [startAudioMixing](#IAudioMixingManager-startaudiomixing) 接口播放音频文件，请在收到 [onAudioMixingStateChanged](Windows-callback.md#IRTCVideoEventHandler-onaudiomixingstatechanged)(AUDIO_MIXING_STATE_PLAYING(1)) 之后调用此接口。


<span id="ISingScoringManager-stopsingscoring"></span>
### stopSingScoring
```cpp
virtual int bytertc::ISingScoringManager::stopSingScoring()
```
停止 K 歌评分。

**返回值**

+ 0：成功。
+ <0：失败。


<span id="ISingScoringManager-getlastsentencescore"></span>
### getLastSentenceScore
```cpp
virtual int bytertc::ISingScoringManager::getLastSentenceScore()
```
获取上一句的演唱评分。调用 [startSingScoring](#ISingScoringManager-startsingscoring) 开始评分后可以调用该接口。

**返回值**

+ <0：获取评分失败。
+ \>=0：上一句歌词的演唱评分。


<span id="ISingScoringManager-gettotalscore"></span>
### getTotalScore
```cpp
virtual int bytertc::ISingScoringManager::getTotalScore()
```
获取当前演唱总分。调用 [startSingScoring](#ISingScoringManager-startsingscoring) 开始评分后可以调用该接口。

**返回值**

+ <0：获取总分失败。
+ \>=0：当前演唱总分。


<span id="ISingScoringManager-getaveragescore"></span>
### getAverageScore
```cpp
virtual int bytertc::ISingScoringManager::getAverageScore()
```
获取当前演唱歌曲的平均分。

**返回值**

+ <0：获取平均分失败。
+ \>=0：当前演唱平均分。


<span id="ISingScoringManager-~isingscoringmanager"></span>
### ~ISingScoringManager
```cpp
virtual bytertc::ISingScoringManager::~ISingScoringManager()
```

# ISpatialAudio
```cpp
class bytertc::ISpatialAudio
```

空间音频接口实例


`Defined in : bytertc_spatial_audio_interface.h`

## 成员函数

| 返回 | 名称 |
| --- | --- |
| **virtual void** | [enableSpatialAudio](#ISpatialAudio-enablespatialaudio) |
| **virtual int** | [updatePosition](#ISpatialAudio-updateposition) |
| **virtual int** | [updateSelfOrientation](#ISpatialAudio-updateselforientation) |
| **virtual void** | [disableRemoteOrientation](#ISpatialAudio-disableremoteorientation) |


## 函数说明
<span id="ISpatialAudio-enablespatialaudio"></span>
### enableSpatialAudio
```cpp
virtual void bytertc::ISpatialAudio::enableSpatialAudio(
    bool enable)
```
开启/关闭空间音频功能。  <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| enable | **bool** | 是否开启空间音频功能：  <br/>• true：开启  <br/>• false：关闭（默认） |


**注意**
该方法仅开启空间音频功能，你须调用 [updatePosition](#ISpatialAudio-updateposition) 设置自身位置坐标后方可收听空间音频效果。空间音频相关 API 和调用时序详见[空间音频](https://www.volcengine.com/docs/6348/93903)。

<span id="ISpatialAudio-updateposition"></span>
### updatePosition
```cpp
virtual int bytertc::ISpatialAudio::updatePosition(
    const Position& pos)
```
更新本地用户在房间内空间直角坐标系中的位置坐标。  <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| pos | **const Position&** | 三维坐标的值，默认为 [0, 0, 0]。参看 [Position](Windows-keytype.md#position) |

**返回值**

+ 0: 成功；  
+ !0: 失败。  


**注意**
调用该接口更新坐标前，你需调用 [enableSpatialAudio](#ISpatialAudio-enablespatialaudio) 开启空间音频功能。空间音频相关 API 和调用时序详见[空间音频](https://www.volcengine.com/docs/6348/93903)。 

<span id="ISpatialAudio-updateselforientation"></span>
### updateSelfOrientation
```cpp
virtual int bytertc::ISpatialAudio::updateSelfOrientation(
    const HumanOrientation& orientation)
```
更新本地用户在空间音频坐标系下的朝向。  <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| orientation | **const HumanOrientation&** | 自身朝向信息，参看 [HumanOrientation](Windows-keytype.md#humanorientation)。 |

**返回值**
方法调用结果：  

+ 0：成功  
+ !0：失败


**注意**

+ 空间音频相关 API 和调用时序详见[空间音频](https://www.volcengine.com/docs/6348/93903)。
+ 调用 [disableRemoteOrientation](#ISpatialAudio-disableremoteorientation) 可忽略远端用户朝向。


<span id="ISpatialAudio-disableremoteorientation"></span>
### disableRemoteOrientation
```cpp
virtual void bytertc::ISpatialAudio::disableRemoteOrientation()
```
参与通话的各端调用本接口后，将忽略远端用户的朝向，认为所有远端用户都面向本地用户。<br>
如果此后调用 [updateSelfOrientation](#ISpatialAudio-updateselforientation) 更新本地用户朝向，远端用户无法感知这些变化，但本地用户接收音频时可以感知自身朝向改变带来的音频效果变化。


**注意**

+ 进房前后都可以调用该接口。  
+ 调用本接口关闭朝向功能后，在当前的空间音频实例的生命周期内无法再次开启。


# IScreenCaptureSourceList
```cpp
class bytertc::IScreenCaptureSourceList
```

屏幕共享对象信息列表
共享对象相关数据将在调用 [release](#IScreenCaptureSourceList-release) 后被释放。


`Defined in : bytertc_video_defines.h`

## 成员函数

| 返回 | 名称 |
| --- | --- |
| **virtual int32_t** | [getCount](#IScreenCaptureSourceList-getcount) |
| **virtual ScreenCaptureSourceInfo** | [getSourceInfo](#IScreenCaptureSourceList-getsourceinfo) |
| **virtual void** | [release](#IScreenCaptureSourceList-release) |


## 函数说明
<span id="IScreenCaptureSourceList-getcount"></span>
### getCount
```cpp
virtual int32_t bytertc::IScreenCaptureSourceList::getCount()
```
获取列表长度

**返回值**
可共享对象数量


<span id="IScreenCaptureSourceList-getsourceinfo"></span>
### getSourceInfo
```cpp
virtual ScreenCaptureSourceInfo bytertc::IScreenCaptureSourceList::getSourceInfo(
    int32_t index)
```
根据索引号，获取屏幕共享列表中的元素

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| index | **int32_t** | 列表索引号 |

**返回值**
屏幕源类型信息，详见 [ScreenCaptureSourceInfo](Windows-keytype.md#screencapturesourceinfo)。


<span id="IScreenCaptureSourceList-release"></span>
### release
```cpp
virtual void bytertc::IScreenCaptureSourceList::release()
```
[IScreenCaptureSourceList](#iscreencapturesourcelist) 使用结束后，调用本接口删除对象，清空和释放内存。


# IVideoDeviceCollection
```cpp
class bytertc::IVideoDeviceCollection
```

视频设备相关的信息


`Defined in : bytertc_video_device_manager.h`

## 成员函数

| 返回 | 名称 |
| --- | --- |
| **virtual int** | [getCount](#IVideoDeviceCollection-getcount) |
| **virtual int** | [getDevice](#IVideoDeviceCollection-getdevice) |
| **virtual void** | [release](#IVideoDeviceCollection-release) |
| **virtual int** | [getDevice](#IVideoDeviceCollection-getdevice) |


## 函数说明
<span id="IVideoDeviceCollection-getcount"></span>
### getCount
```cpp
virtual int bytertc::IVideoDeviceCollection::getCount() override
```
获取当前系统内视频设备数量

**返回值**
视频设备数量


<span id="IVideoDeviceCollection-getdevice"></span>
### getDevice
```cpp
virtual int bytertc::IVideoDeviceCollection::getDevice(
    int index,
    char device_name[MAX_DEVICE_ID_LENGTH],
    char device_id[MAX_DEVICE_ID_LENGTH])
```
根据索引号，获取设备信息

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| index | **int** | 设备索引号，从 0 开始，注意需小于 [getCount](#IVideoDeviceCollection-getcount) 返回值。 |
| device_name | **char** | 设备名称 |
| device_id | **char** | 设备 ID |

**返回值**

+ 0：方法调用成功  
+ !0：方法调用失败  


<span id="IVideoDeviceCollection-release"></span>
### release
```cpp
virtual void bytertc::IVideoDeviceCollection::release()override
```
释放当前 [IVideoDeviceCollection](#ivideodevicecollection) 对象占用的资源。


**注意**
不需要返回视频设备相关信息列表时应该调用本方法释放相关资源。

<span id="IVideoDeviceCollection-getdevice"></span>
### getDevice
```cpp
virtual int bytertc::IVideoDeviceCollection::getDevice(
    int index,
    VideoDeviceInfo* video_device_info)
```
根据索引号，获取设备信息

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| index | **int** | 设备索引号，从 0 开始，注意需小于 [getCount](#IVideoDeviceCollection-getcount) 返回值。 |
| video_device_info | **VideoDeviceInfo*** | 设备信息 |

**返回值**

+ 0：方法调用成功  
+ !0：方法调用失败  


# IVideoDeviceManager
```cpp
class bytertc::IVideoDeviceManager
```

主要用于枚举、设置视频采集设备


`Defined in : bytertc_video_device_manager.h`

## 成员函数

| 返回 | 名称 |
| --- | --- |
| **virtual IVideoDeviceCollection*** | [enumerateVideoCaptureDevices](#IVideoDeviceManager-enumeratevideocapturedevices) |
| **virtual int** | [setVideoCaptureDevice](#IVideoDeviceManager-setvideocapturedevice) |
| **virtual int** | [getVideoCaptureDevice](#IVideoDeviceManager-getvideocapturedevice) |


## 函数说明
<span id="IVideoDeviceManager-enumeratevideocapturedevices"></span>
### enumerateVideoCaptureDevices
```cpp
virtual IVideoDeviceCollection* bytertc::IVideoDeviceManager::enumerateVideoCaptureDevices()
```
获取当前系统内视频采集设备列表。

**返回值**
包含系统中所有视频采集设备的列表，参看 [IVideoDeviceCollection](#ivideodevicecollection)。  


<span id="IVideoDeviceManager-setvideocapturedevice"></span>
### setVideoCaptureDevice
```cpp
virtual int bytertc::IVideoDeviceManager::setVideoCaptureDevice(
    const char device_id[MAX_DEVICE_ID_LENGTH])
```
设置当前视频采集设备

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| device_id | **const char** | 视频设备 ID，可以通过 [enumerateVideoCaptureDevices](#IVideoDeviceManager-enumeratevideocapturedevices) 获取 |

**返回值**

+ 0：方法调用成功  
+ !0：方法调用失败  


<span id="IVideoDeviceManager-getvideocapturedevice"></span>
### getVideoCaptureDevice
```cpp
virtual int bytertc::IVideoDeviceManager::getVideoCaptureDevice(
    char device_id[MAX_DEVICE_ID_LENGTH])
```
获取当前 SDK 正在使用的视频采集设备信息

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| device_id | **char** | 视频设备 ID |

**返回值**

+ 0：方法调用成功  
+ !0：方法调用失败  


# IVideoEffect
```cpp
class bytertc::IVideoEffect
```

视频特效接口


`Defined in : bytertc_video_effect_interface.h`

## 成员函数

| 返回 | 名称 |
| --- | --- |
| **virtual int** | [checkLicense](#IVideoEffect-checklicense) |
| **virtual int** | [getAuthMessage](#IVideoEffect-getauthmessage) |
| **virtual int** | [freeAuthMessage](#IVideoEffect-freeauthmessage) |
| **virtual int** | [enableEffect](#IVideoEffect-enableeffect) |
| **virtual void** | [setAlgoModelPath](#IVideoEffect-setalgomodelpath) |
| **virtual int** | [setEffectNodes](#IVideoEffect-seteffectnodes) |
| **virtual int** | [updateNode](#IVideoEffect-updatenode) |
| **virtual int** | [setColorFilter](#IVideoEffect-setcolorfilter) |
| **virtual int** | [setColorFilterIntensity](#IVideoEffect-setcolorfilterintensity) |
| **virtual int** | [registerFaceDetectionObserver](#IVideoEffect-registerfacedetectionobserver) |
| **virtual int** | [setBackgroundSticker](#IVideoEffect-setbackgroundsticker) |


## 函数说明
<span id="IVideoEffect-checklicense"></span>
### checkLicense
```cpp
virtual int bytertc::IVideoEffect::checkLicense(
    void* androidContext,
    void* jnienv,
    const char* licensePath)
```
视频特效许可证检查

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| androidContext | **void*** | Android Context 对象指针(jobject 类型)。Android 以外平台传入 nullptr |
| jnienv | **void*** | Android  <br/>JNIEnv 指针。Android 以外平台传入 nullptr |
| licensePath | **const char*** | 许可证文件绝对路径 |

**返回值**

+ 0: 调用成功。  
+ 1000: 未集成特效 SDK。  
+ 1001: 特效 SDK 不支持该功能。  
+ < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。  


**注意**
开始使用视频特效前，你必须先调用这个方法进行许可证验证

<span id="IVideoEffect-getauthmessage"></span>
### getAuthMessage
```cpp
virtual int bytertc::IVideoEffect::getAuthMessage(
    char ** ppmsg,
    int * len)
```
从特效 SDK 获取授权消息，用于获取在线许可证。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| ppmsg | **char**** | 授权消息字符串地址 |
| len | **int*** | 授权消息字符串的长度 |

**返回值**

+ 0: 调用成功。  
+ 1000: 未集成特效 SDK。  
+ 1001: 特效 SDK 不支持该功能。  
+ < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。  


**注意**

+ 使用视频特效的功能前，你必须获取特效 SDK 的在线许可证。  
+ 通过此接口获取授权消息后，你必须参考 [在线授权说明](https://www.volcengine.com/docs/6705/102012) 自行实现获取在线许可证的业务逻辑。获取许可证后，你必须调用 [checkLicense](#IVideoEffect-checklicense) 确认许可证有效。然后，你才可以使用 CV 功能。  
+ 获取授权消息后，调用 [freeAuthMessage](#IVideoEffect-freeauthmessage) 释放内存。


<span id="IVideoEffect-freeauthmessage"></span>
### freeAuthMessage
```cpp
virtual int bytertc::IVideoEffect::freeAuthMessage(
    char * pmsg)
```
使用完授权消息字符串后，释放内存。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| pmsg | **char*** | getAuthMessage 返回的授权消息字符串。 |

**返回值**

+ 0: 调用成功。  
+ 1000: 未集成特效 SDK。  
+ 1001: 特效 SDK 不支持该功能。  
+ < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。  


<span id="IVideoEffect-enableeffect"></span>
### enableEffect
```cpp
virtual int bytertc::IVideoEffect::enableEffect(
    bool enabled)
```
开启关闭视频特效

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| enabled | **bool** | 是否开启特效，true: 开启，false: 关闭 |

**返回值**

+ 0: 调用成功。  
+ 1000: 未集成特效 SDK。  
+ 1001: 特效 SDK 不支持该功能。  
+ < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。  


**注意**
在调用 [checkLicense](#IVideoEffect-checklicense) 和 [setAlgoModelPath](#IVideoEffect-setalgomodelpath) 后调用此方法。

<span id="IVideoEffect-setalgomodelpath"></span>
### setAlgoModelPath
```cpp
virtual void bytertc::IVideoEffect::setAlgoModelPath(
    const char* modelPath)
```
设置视频特效算法模型路径

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| modelPath | **const char*** | 模型路径 |


<span id="IVideoEffect-seteffectnodes"></span>
### setEffectNodes
```cpp
virtual int bytertc::IVideoEffect::setEffectNodes(
    const char** effectNodePaths,
    int nodeNum)
```
设置视频特效素材包

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| effectNodePaths | **const char**** | 特效素材包路径数组 <br/>要取消当前视频特效，将此参数设置为 null。 |
| nodeNum | **int** | 特效素材包个数 |

**返回值**

+ 0: 调用成功。  
+ 1000: 未集成特效 SDK。  
+ 1001: 特效 SDK 不支持该功能。  
+ < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。  


<span id="IVideoEffect-updatenode"></span>
### updateNode
```cpp
virtual int bytertc::IVideoEffect::updateNode(
    const char* nodePath,
    const char* nodeKey,
    float nodeValue)
```
设置特效强度

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| nodePath | **const char*** | 特效素材包路径 |
| nodeKey | **const char*** | 需要设置的素材 key 名称，取值请参考 [素材 key 对应说明](http://ailab-cv-sdk.bytedance.com/docs/2036/99769/)。 |
| nodeValue | **float** | 需要设置的强度值 取值范围 [0,1]，超出范围时设置无效。 |

**返回值**

+ 0: 调用成功。  
+ 1000: 未集成特效 SDK。  
+ 1001: 特效 SDK 不支持该功能。  
+ < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。  


<span id="IVideoEffect-setcolorfilter"></span>
### setColorFilter
```cpp
virtual int bytertc::IVideoEffect::setColorFilter(
    const char* resPath)
```
设置颜色滤镜

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| resPath | **const char*** | 滤镜资源包绝对路径。 |

**返回值**

+ 0: 调用成功。  
+ 1000: 未集成特效 SDK。  
+ 1001: 特效 SDK 不支持该功能。  
+ < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。  


<span id="IVideoEffect-setcolorfilterintensity"></span>
### setColorFilterIntensity
```cpp
virtual int bytertc::IVideoEffect::setColorFilterIntensity(
    float intensity)
```
设置已启用颜色滤镜的强度

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| intensity | **float** | 滤镜强度。取值范围 [0,1]，超出范围时设置无效。 |

**返回值**

+ 0: 调用成功。  
+ 1000: 未集成特效 SDK。  
+ 1001: 特效 SDK 不支持该功能。  
+ < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。  


<span id="IVideoEffect-registerfacedetectionobserver"></span>
### registerFaceDetectionObserver
```cpp
virtual int bytertc::IVideoEffect::registerFaceDetectionObserver(
    IFaceDetectionObserver * observer,
    int interval_ms)
```
注册人脸检测结果回调观察者 <br>
注册此观察者后，你会周期性收到 [onFaceDetectResult](Windows-callback.md#IFaceDetectionObserver-onfacedetectresult) 回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| observer | **IFaceDetectionObserver*** | 人脸检测结果回调观察者，参看 [IFaceDetectionObserver](Windows-callback.md#ifacedetectionobserver)。 |
| interval_ms | **int** | 时间间隔，必须大于 0。单位：ms。实际收到回调的时间间隔大于 `interval`，小于 `interval + 视频采集帧间隔`。 |

**返回值**

+ 0：方法调用成功  
+ < 0：方法调用失败  


<span id="IVideoEffect-setbackgroundsticker"></span>
### setBackgroundSticker
```cpp
virtual int bytertc::IVideoEffect::setBackgroundSticker(
    const char* modelPath,
    const VirtualBackgroundSource& source)
```
将摄像头采集画面中的人像背景替换为指定图片或纯色背景。
若要取消背景特效，将背景贴纸特效素材路径设置为null。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| modelPath | **const char*** | 传入背景贴纸特效素材路径。 |
| source | **const VirtualBackgroundSource&** | 设置背景特效图片的本地路径。参看 [VirtualBackgroundSource](Windows-keytype.md#virtualbackgroundsource)。 |

**返回值**

+ 0：调用成功。  
+ 1000：未集成特效 SDK。  
+ 1001：特效 SDK 不支持该功能。  
+ < 0：调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。


**注意**
调用此接口前需依次调用以下接口：
1、检查视频特效许可证 [checkLicense](#IVideoEffect-checklicense)；
2、设置视频特效算法模型路径 [setAlgoModelPath](#IVideoEffect-setalgomodelpath)；
3、开启视频特效 [enableEffect](#IVideoEffect-enableeffect)。


# IVideoProcessor
```cpp
class bytertc::IVideoProcessor
```



`Defined in : bytertc_video_processor_interface.h`

## 成员函数

| 返回 | 名称 |
| --- | --- |
| **virtual IVideoFrame*** | [processVideoFrame](#IVideoProcessor-processvideoframe) |


## 函数说明
<span id="IVideoProcessor-processvideoframe"></span>
### processVideoFrame
```cpp
virtual IVideoFrame* bytertc::IVideoProcessor::processVideoFrame(
    IVideoFrame* src_frame)
```
获取 RTC SDK 采集得到的视频帧，根据 [registerLocalVideoProcessor](#IRTCVideo-registerlocalvideoprocessor) 设置的视频前处理器，进行视频前处理，最终将处理后的视频帧给到 RTC SDK 用于编码传输。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| src_frame | **IVideoFrame*** | RTC SDK 采集得到的视频帧，参看 [IVideoFrame](Windows-keytype.md#ivideoframe)。 |

**返回值**
经过视频前处理后的视频帧，返回给 RTC SDK 供编码和传输，参看 [IVideoFrame](Windows-keytype.md#ivideoframe)。


**注意**

+ 在进行视频前处理前，你需要调用 [registerLocalVideoProcessor](#IRTCVideo-registerlocalvideoprocessor) 设置视频前处理器。
+ 如果需要取消视频前处理，可以将视频前处理器设置为 nullptr。


# IStreamingRTCEngine
```cpp
class streamingrtc::IStreamingRTCEngine
```

串流引擎具有高码率，低延迟的特点，特别适合游戏串流等点对点传输的业务场景。
如果你需要使用串流引擎的能力，请联系售前或技术支持，获取包含串流引擎的 SDK 包。


`Defined in : streaming_rtc_engine_interface.h`

## 成员函数

| 返回 | 名称 |
| --- | --- |
| **virtual int** | [Startup](#IStreamingRTCEngine-startup) |
| **virtual int** | [Shutdown](#IStreamingRTCEngine-shutdown) |
| **virtual int64_t** | [SendP2PMessage](#IStreamingRTCEngine-sendp2pmessage) |
| **virtual int64_t** | [SendP2PBinaryMessage](#IStreamingRTCEngine-sendp2pbinarymessage) |
| **virtual bool** | [PullAudioFrame](#IStreamingRTCEngine-pullaudioframe) |
| **virtual bool** | [PushAudioFrame](#IStreamingRTCEngine-pushaudioframe) |
| **virtual int** | [SetVideoEncoderConfig](#IStreamingRTCEngine-setvideoencoderconfig) |
| **virtual void** | [SetVideoDecoderConfig](#IStreamingRTCEngine-setvideodecoderconfig) |
| **virtual void** | [SetVideoSourceType](#IStreamingRTCEngine-setvideosourcetype) |
| **virtual bool** | [PushVideoFrame](#IStreamingRTCEngine-pushvideoframe) |
| **virtual bool** | [PushEncodedVideoFrame](#IStreamingRTCEngine-pushencodedvideoframe) |
| **virtual void** | [RequestRemoteVideoKeyFrame](#IStreamingRTCEngine-requestremotevideokeyframe) |
| **virtual void** | [SetReportExtraInfo](#IStreamingRTCEngine-setreportextrainfo) |


## 函数说明
<span id="IStreamingRTCEngine-startup"></span>
### Startup
```cpp
virtual int streamingrtc::IStreamingRTCEngine::Startup()
```
启动串流引擎 <br>
通过 [EngineConfig](Windows-keytype.md#engineconfig) 设置引擎类型服务端或客户端和端口号范围 <br>

**返回值**

+ 0：成功 
+ !0：失败 


**注意**
如果连接过程中断开了连接，客户端会继续不断尝试连接连接。

<span id="IStreamingRTCEngine-shutdown"></span>
### Shutdown
```cpp
virtual int streamingrtc::IStreamingRTCEngine::Shutdown()
```
关闭串流引擎

**返回值**

+ 0：成功 
+ !0：失败 


<span id="IStreamingRTCEngine-sendp2pmessage"></span>
### SendP2PMessage
```cpp
virtual int64_t streamingrtc::IStreamingRTCEngine::SendP2PMessage(
    const char* message,
    bool reliable)
```
发送点对点文本消息

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| message | **const char*** | 消息文本，最大 62 KB<br/>不可靠消息最大 1 KB |
| reliable | **bool** | true：如果对端存在，保证消息可靠到达对端 <br/>false：消息可能会丢失，但是速度上更快一些 |

**返回值**

+ `\>= 0`：发送成功，数值代表消息 id
+ `< 0`：发送失败


<span id="IStreamingRTCEngine-sendp2pbinarymessage"></span>
### SendP2PBinaryMessage
```cpp
virtual int64_t streamingrtc::IStreamingRTCEngine::SendP2PBinaryMessage(
    const uint8_t* message,
    int length,
    bool reliable)
```
发送点对点二进制消息

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| message | **const uint8_t*** | 消息文本 |
| length | **int** | 消息长度，最大 62 KB。不可靠消息最大 1 KB |
| reliable | **bool** | true：如果对端存在，保证消息可靠到达对端 <br/>false：消息可能会丢失，但是速度上更快一些 |

**返回值**

+ `\>= 0`：发送成功，数值代表消息 id
+ `< 0`：发送失败


<span id="IStreamingRTCEngine-pullaudioframe"></span>
### PullAudioFrame
```cpp
virtual bool streamingrtc::IStreamingRTCEngine::PullAudioFrame(
    bytertc::IAudioFrame* audio_frame)
```
拉取音频数据

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audio_frame | **bytertc::IAudioFrame*** | 接收到的音频帧，参看 [IAudioFrame](Windows-keytype.md#iaudioframe) <br/>关于推送音频帧，参看 [PushAudioFrame](#IStreamingRTCEngine-pushaudioframe) |

**返回值**

+ True：成功 
+ False：失败


<span id="IStreamingRTCEngine-pushaudioframe"></span>
### PushAudioFrame
```cpp
virtual bool streamingrtc::IStreamingRTCEngine::PushAudioFrame(
    bytertc::IAudioFrame* audio_frame)
```
推送自定义音频数据

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audio_frame | **bytertc::IAudioFrame*** | 发送的音频帧，参看 [IAudioFrame](Windows-keytype.md#iaudioframe) <br/>创建音频帧，参看 [AudioFrameBuilder](Windows-keytype.md#audioframebuilder) 和 [buildAudioFrame](#buildaudioframe)。<br/>关于接收音频帧，参看 [PullAudioFrame](#IStreamingRTCEngine-pullaudioframe) |

**返回值**

+ True：成功 
+ False：失败 


**注意**
推送音频帧必须设置时间戳 AudioFrameBuilder.timestamp_us

<span id="IStreamingRTCEngine-setvideoencoderconfig"></span>
### SetVideoEncoderConfig
```cpp
virtual int streamingrtc::IStreamingRTCEngine::SetVideoEncoderConfig(
    streamingrtc::StreamIndex stream_index,
    const VideoSolution* solutions,
    int solution_num)
```
设置推送多路流时的各路视频参数，包括分辨率、帧率、码率、缩放模式、网络不佳时的回退策略等。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stream_index | **streamingrtc::StreamIndex** | 视频流标识，参看 [StreamIndex](Windows-keytype.md#streamindex)。 |
| solutions | **const VideoSolution*** | 要推送的多路视频流参数，参看 [VideoSolution](Windows-keytype.md#videosolution)。<br/>最大分辨率为 4096 px × 4096 px，超过或设置的分辨率无法编码时，会导致编码推流失败。 |
| solution_num | **int** | 视频参数数组长度。<br/>最多支持 4 路参数。当设置了多路参数时，分辨率必须是从大到小排列。 |

**返回值**

+ 0：成功  
+ !0：失败  


<span id="IStreamingRTCEngine-setvideodecoderconfig"></span>
### SetVideoDecoderConfig
```cpp
virtual void streamingrtc::IStreamingRTCEngine::SetVideoDecoderConfig(
    streamingrtc::StreamIndex stream_index,
    VideoDecoderConfig config)
```
设置远端视频数据解码方式。<br>
需要在 [Startup](#IStreamingRTCEngine-startup) 之前调用本接口。  <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stream_index | **streamingrtc::StreamIndex** | 远端流信息，即对哪一路视频流进行解码方式设置，参看 [StreamIndex](Windows-keytype.md#streamindex)。 |
| config | **VideoDecoderConfig** | 视频解码方式，参看 [VideoDecoderConfig](Windows-keytype.md#videodecoderconfig)。 |


**注意**
当你想要对远端流进行自定义解码时，调用该接口将解码方式设置为自定义解码。监测到的视频数据会通过 [OnP2PRemoteEncodedVideoFrame](Windows-callback.md#IStreamingRTCEventHandler-onp2premoteencodedvideoframe) 和/或 [OnP2PRemoteVideoFrame](Windows-callback.md#IStreamingRTCEventHandler-onp2premotevideoframe) 回调出来。

<span id="IStreamingRTCEngine-setvideosourcetype"></span>
### SetVideoSourceType
```cpp
virtual void streamingrtc::IStreamingRTCEngine::SetVideoSourceType(
    streamingrtc::StreamIndex stream_index,
    VideoSourceType type)
```
设置输入到串流引擎的视频源<br>
默认使用内部采集。内部采集指：使用 SDK 内置的视频采集机制进行视频采集。 <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stream_index | **streamingrtc::StreamIndex** | 视频流的属性，参看 [StreamIndex](Windows-keytype.md#streamindex) |
| type | **VideoSourceType** | 视频输入源类型。参看 [VideoSourceType](Windows-keytype.md#videosourcetype)，暂不支持内部编码模式 `VideoSourceTypeInternal`。 |


**注意**
该方法启动引擎前后均可调用。

<span id="IStreamingRTCEngine-pushvideoframe"></span>
### PushVideoFrame
```cpp
virtual bool streamingrtc::IStreamingRTCEngine::PushVideoFrame(
    streamingrtc::StreamIndex stream_index,
    IVideoFrame* frame)
```
发送外部源视频数据

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stream_index | **streamingrtc::StreamIndex** | 选择作为哪一路流发送视频帧 参看 [StreamIndex](Windows-keytype.md#streamindex) |
| frame | **IVideoFrame*** | 设置视频帧，暂时只支持 YUV420P 格式的视频帧。参看 [IVideoFrame](Windows-keytype.md#ivideoframe)。 |

**返回值**

+ True：成功 
+ False：失败


**注意**

+ 该函数运行在用户调用线程内  
+ 推送外部视频帧前，必须调用 [SetVideoSourceType](#IStreamingRTCEngine-setvideosourcetype) 开启外部视频源采集。


<span id="IStreamingRTCEngine-pushencodedvideoframe"></span>
### PushEncodedVideoFrame
```cpp
virtual bool streamingrtc::IStreamingRTCEngine::PushEncodedVideoFrame(
    streamingrtc::StreamIndex stream_index,
    int video_index,
    IEncodedVideoFrame* video_stream)
```
推送自定义编码后的视频流

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stream_index | **streamingrtc::StreamIndex** | 需要推送的编码流的属性，参看 [StreamIndex](Windows-keytype.md#streamindex)。 |
| video_index | **int** | 启用多分辨率编码时的流标识，从 0 开始。如果调用 [SetVideoEncoderConfig](#IStreamingRTCEngine-setvideoencoderconfig) 设置了多路流，此处数量须与之保持一致。 |
| video_stream | **IEncodedVideoFrame*** | 编码流视频帧信息，仅支持推送 H264 和 ByteVC1 格式的视频帧。参看 [IEncodedVideoFrame](Windows-keytype.md#iencodedvideoframe)。 |

**返回值**

+ True：成功 
+ False：失败


**注意**

+ 该函数运行在用户调用线程内  
+ 推送自定义编码视频帧前，必须调用 [SetVideoSourceType](#IStreamingRTCEngine-setvideosourcetype) 将视频输入源切换至自定义编码视频源。


<span id="IStreamingRTCEngine-requestremotevideokeyframe"></span>
### RequestRemoteVideoKeyFrame
```cpp
virtual void streamingrtc::IStreamingRTCEngine::RequestRemoteVideoKeyFrame(
    streamingrtc::StreamIndex stream_index)
```
在订阅远端视频流之后，向远端请求关键帧

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stream_index | **streamingrtc::StreamIndex** | 选择哪一路流请求视频关键帧 参看 [StreamIndex](Windows-keytype.md#streamindex)。 |


**注意**

+ 该方法仅适用于手动订阅模式，并且在成功订阅远端流之后使用。  
+ 该方法适用于调用 [SetVideoDecoderConfig](#IStreamingRTCEngine-setvideodecoderconfig) 开启自定义解码功能后，并且自定义解码失败的情况下使用


<span id="IStreamingRTCEngine-setreportextrainfo"></span>
### SetReportExtraInfo
```cpp
virtual void streamingrtc::IStreamingRTCEngine::SetReportExtraInfo(
    const char* extra_info)
```
设置上报的 trace 的 extra_info