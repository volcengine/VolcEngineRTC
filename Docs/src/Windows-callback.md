# IRTCRoomEventHandler
```cpp
class bytertc::IRTCRoomEventHandler
```

音视频房间事件回调接口


`Defined in : bytertc_room_event_handler.h`

## 成员函数

| 返回 | 名称 |
| --- | --- |
| **virtual void** | [onRoomStateChanged](#IRTCRoomEventHandler-onroomstatechanged) |
| **virtual void** | [onStreamStateChanged](#IRTCRoomEventHandler-onstreamstatechanged) |
| **virtual void** | [onLeaveRoom](#IRTCRoomEventHandler-onleaveroom) |
| **virtual void** | [onTokenWillExpire](#IRTCRoomEventHandler-ontokenwillexpire) |
| **virtual void** | [onRoomStats](#IRTCRoomEventHandler-onroomstats) |
| **virtual void** | [onLocalStreamStats](#IRTCRoomEventHandler-onlocalstreamstats) |
| **virtual void** | [onRemoteStreamStats](#IRTCRoomEventHandler-onremotestreamstats) |
| **virtual void** | [onUserJoined](#IRTCRoomEventHandler-onuserjoined) |
| **virtual void** | [onUserLeave](#IRTCRoomEventHandler-onuserleave) |
| **virtual void** | [onUserPublishStream](#IRTCRoomEventHandler-onuserpublishstream) |
| **virtual void** | [onUserUnpublishStream](#IRTCRoomEventHandler-onuserunpublishstream) |
| **virtual void** | [onUserPublishScreen](#IRTCRoomEventHandler-onuserpublishscreen) |
| **virtual void** | [onUserUnpublishScreen](#IRTCRoomEventHandler-onuserunpublishscreen) |
| **virtual void** | [onStreamSubscribed](#IRTCRoomEventHandler-onstreamsubscribed) |
| **virtual void** | [onRoomMessageReceived](#IRTCRoomEventHandler-onroommessagereceived) |
| **virtual void** | [onRoomBinaryMessageReceived](#IRTCRoomEventHandler-onroombinarymessagereceived) |
| **virtual void** | [onUserMessageReceived](#IRTCRoomEventHandler-onusermessagereceived) |
| **virtual void** | [onUserBinaryMessageReceived](#IRTCRoomEventHandler-onuserbinarymessagereceived) |
| **virtual void** | [onUserMessageSendResult](#IRTCRoomEventHandler-onusermessagesendresult) |
| **virtual void** | [onRoomMessageSendResult](#IRTCRoomEventHandler-onroommessagesendresult) |
| **virtual void** | [onVideoStreamBanned](#IRTCRoomEventHandler-onvideostreambanned) |
| **virtual void** | [onAVSyncStateChange](#IRTCRoomEventHandler-onavsyncstatechange) |
| **virtual void** | [onAudioStreamBanned](#IRTCRoomEventHandler-onaudiostreambanned) |
| **virtual void** | [onForwardStreamStateChanged](#IRTCRoomEventHandler-onforwardstreamstatechanged) |
| **virtual void** | [onForwardStreamEvent](#IRTCRoomEventHandler-onforwardstreamevent) |
| **virtual void** | [onNetworkQuality](#IRTCRoomEventHandler-onnetworkquality) |


## 函数说明
<span id="IRTCRoomEventHandler-onroomstatechanged"></span>
### onRoomStateChanged
```cpp
virtual void bytertc::IRTCRoomEventHandler::onRoomStateChanged(
    const char* room_id,
    const char* uid,
    int state,
    const char* extra_info)
```
房间状态改变回调，加入房间、异常退出房间、发生房间相关的警告或错误时会收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| room_id | **const char*** | 房间 ID。 |
| uid | **const char*** | 用户 ID。 |
| state | **int** | 房间状态码。  <br/>• 0: 成功。  <br/>• !0: 失败或异常退房。具体原因参看 [ErrorCode](Windows-errorcode.md#errorcode) 及 [WarningCode](Windows-errorcode.md#warningcode)。异常退出房间，具体原因包括<br/>- -1004：相同 ID 用户在其他端进房； <br/>- -1006：用户被踢出当前房间。 |
| extra_info | **const char*** | 额外信息，如 `{"elapsed":1187,"join_type":0}`。<br/>`join_type` 表示加入房间的类型，`0`为首次进房，`1`为重连进房。<br/>`elapsed`表示加入房间耗时，即本地用户从调用 [joinRoom](Windows-api.md#IRTCRoom-joinroom) 到加入房间成功所经历的时间间隔，单位为 ms。 |


<span id="IRTCRoomEventHandler-onstreamstatechanged"></span>
### onStreamStateChanged
```cpp
virtual void bytertc::IRTCRoomEventHandler::onStreamStateChanged(
    const char* room_id,
    const char* uid,
    int state,
    const char* extra_info)
```
流状态改变回调，发生流相关的警告或错误时会收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| room_id | **const char*** | 房间 ID。 |
| uid | **const char*** | 用户 ID。 |
| state | **int** | 流状态码，参看 [ErrorCode](Windows-errorcode.md#errorcode) 及 [WarningCode](Windows-errorcode.md#warningcode)。 |
| extra_info | **const char*** | 附加信息，目前为空。 |


<span id="IRTCRoomEventHandler-onleaveroom"></span>
### onLeaveRoom
```cpp
virtual void bytertc::IRTCRoomEventHandler::onLeaveRoom(
    const RtcRoomStats& stats)
```
离开房间回调。  <br>
用户调用 [leaveRoom](Windows-api.md#IRTCRoom-leaveroom) 方法后，SDK 会停止所有的发布订阅流，并在释放所有与通话相关的音视频资源后，通过此回调通知用户离开房间成功。  <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stats | **const RtcRoomStats&** | 保留参数，目前为空。 |


**注意**

+ 用户调用 [leaveRoom](Windows-api.md#IRTCRoom-leaveroom) 方法离开房间后，若立即调用 [destroyRTCVideo](Windows-api.md#destroyrtcvideo) 方法销毁 RTC 引擎，则将无法收到此回调事件。  
+ 离开房间后，如果 App 需要使用系统音视频设备，则建议收到此回调后再初始化音视频设备，否则可能由于 SDK 占用音视频设备而导致初始化失败。  


<span id="IRTCRoomEventHandler-ontokenwillexpire"></span>
### onTokenWillExpire
```cpp
virtual void bytertc::IRTCRoomEventHandler::onTokenWillExpire()
```
Token 过期前 30 秒将触发该回调。<br>
调用 [updateToken](Windows-api.md#IRTCRoom-updatetoken) 更新 Token。否则 Token 过期后，用户将被移出房间无法继续进行音视频通话。


<span id="IRTCRoomEventHandler-onroomstats"></span>
### onRoomStats
```cpp
virtual void bytertc::IRTCRoomEventHandler::onRoomStats(
    const RtcRoomStats& stats)
```
房间内通话统计信息回调。   <br>
用户进房开始通话后，每 2s 收到一次本回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stats | **const RtcRoomStats&** | 当前 RtcEngine 统计数据，详见 [RtcRoomStats](Windows-keytype.md#rtcroomstats) |


<span id="IRTCRoomEventHandler-onlocalstreamstats"></span>
### onLocalStreamStats
```cpp
virtual void bytertc::IRTCRoomEventHandler::onLocalStreamStats(
    const LocalStreamStats& stats)
```
发布流成功后，每隔 2s 收到此回调，了解发布的流在此周期内的网络质量信息。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stats | **const LocalStreamStats&** | 当前 RtcEngine 统计数据，详见 [LocalStreamStats](Windows-keytype.md#localstreamstats) |


<span id="IRTCRoomEventHandler-onremotestreamstats"></span>
### onRemoteStreamStats
```cpp
virtual void bytertc::IRTCRoomEventHandler::onRemoteStreamStats(
    const RemoteStreamStats& stats)
```
每隔 2s 收到此回调，了解订阅的远端用户发布的流在此周期内的网络质量信息。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stats | **const RemoteStreamStats&** | 当前 RtcEngine 统计数据，详见 [RemoteStreamStats](Windows-keytype.md#remotestreamstats) |


<span id="IRTCRoomEventHandler-onuserjoined"></span>
### onUserJoined
```cpp
virtual void bytertc::IRTCRoomEventHandler::onUserJoined(
    const UserInfo& user_info,
    int elapsed)
```
远端可见用户加入房间，或房内隐身用户切换为可见的回调。<br>
1. 远端用户调用 [setUserVisibility](Windows-api.md#IRTCRoom-setuservisibility) 方法将自身设为可见后加入房间时，房间内其他用户将收到该事件。  <br>
2. 远端可见用户断网后重新连入房间时，房间内其他用户将收到该事件。  <br>
3. 房间内隐身远端用户调用 [setUserVisibility](Windows-api.md#IRTCRoom-setuservisibility) 方法切换至可见时，房间内其他用户将收到该事件。  <br>
4. 新进房用户会收到进房前已在房内的可见用户的进房回调通知。  <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| user_info | **const UserInfo&** | 用户信息，详见 [UserInfo](Windows-keytype.md#userinfo) |
| elapsed | **int** | 保留字段，无意义。 |


<span id="IRTCRoomEventHandler-onuserleave"></span>
### onUserLeave
```cpp
virtual void bytertc::IRTCRoomEventHandler::onUserLeave(
    const char* uid,
    UserOfflineReason reason)
```
远端用户离开房间，或切至不可见时，本地用户会收到此事件

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | **const char*** | 离开房间，或切至不可见的的远端用户 ID。 |
| reason | **UserOfflineReason** | 用户离开房间的原因，详见 [UserOfflineReason](Windows-keytype#userofflinereason)。 <br/>• 0: 远端用户调用 [leaveRoom](Windows-api.md#IRTCRoom-leaveroom) 主动退出房间。  <br/>• 1: 远端用户因 Token 过期或网络原因等掉线。 详细信息请参看[连接状态提示](https://www.volcengine.com/docs/6348/95376)<br/>• 2: 远端用户调用 [setUserVisibility](Windows-api.md#IRTCRoom-setuservisibility) 切换至不可见状态。 <br/>• 3: 服务端调用 OpenAPI 将远端用户踢出房间。 |


<span id="IRTCRoomEventHandler-onuserpublishstream"></span>
### onUserPublishStream
```cpp
virtual void bytertc::IRTCRoomEventHandler::onUserPublishStream(
    const char* uid,
    MediaStreamType type)
```
房间内新增远端摄像头/麦克风采集的媒体流的回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | **const char*** | 远端流发布用户的用户 ID。 |
| type | **MediaStreamType** | 远端媒体流的类型，参看 [MediaStreamType](Windows-keytype.md#mediastreamtype)。 |


**注意**
当房间内的远端用户调用 [publishStream](Windows-api.md#IRTCRoom-publishstream) 成功发布由摄像头/麦克风采集的媒体流时，本地用户会收到该回调，此时本地用户可以自行选择是否调用 [subscribeStream](Windows-api.md#IRTCRoom-subscribestream) 订阅此流。

<span id="IRTCRoomEventHandler-onuserunpublishstream"></span>
### onUserUnpublishStream
```cpp
virtual void bytertc::IRTCRoomEventHandler::onUserUnpublishStream(
    const char* uid,
    MediaStreamType type,
    StreamRemoveReason reason)
```
房间内远端摄像头/麦克风采集的媒体流移除的回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | **const char*** | 移除的远端流发布用户的用户 ID。 |
| type | **MediaStreamType** | 移除的远端流类型，参看 [MediaStreamType](Windows-keytype.md#mediastreamtype)。 |
| reason | **StreamRemoveReason** | 远端流移除的原因，参看 [StreamRemoveReason](Windows-keytype.md#streamremovereason)。 |


**注意**
收到该回调通知后，你可以自行选择是否调用 [unsubscribeStream](Windows-api.md#IRTCRoom-unsubscribestream) 取消订阅此流。

<span id="IRTCRoomEventHandler-onuserpublishscreen"></span>
### onUserPublishScreen
```cpp
virtual void bytertc::IRTCRoomEventHandler::onUserPublishScreen(
    const char* uid,
    MediaStreamType type)
```
房间内新增远端屏幕共享音视频流的回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | **const char*** | 远端流发布用户的用户 ID。 |
| type | **MediaStreamType** | 远端媒体流的类型，参看 [MediaStreamType](Windows-keytype.md#mediastreamtype)。 |


**注意**
当房间内的远端用户调用 [publishScreen](Windows-api.md#IRTCRoom-publishscreen) 成功发布来自屏幕共享的音视频流时，本地用户会收到该回调，此时本地用户可以自行选择是否调用 [subscribeScreen](Windows-api.md#IRTCRoom-subscribescreen) 订阅此流。（Linux 不支持）

<span id="IRTCRoomEventHandler-onuserunpublishscreen"></span>
### onUserUnpublishScreen
```cpp
virtual void bytertc::IRTCRoomEventHandler::onUserUnpublishScreen(
    const char* uid,
    MediaStreamType type,
    StreamRemoveReason reason)
```
房间内远端屏幕共享音视频流移除的回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | **const char*** | 移除的远端流发布用户的用户 ID。 |
| type | **MediaStreamType** | 移除的远端流类型，参看 [MediaStreamType](Windows-keytype.md#mediastreamtype)。 |
| reason | **StreamRemoveReason** | 远端流移除的原因，参看 [StreamRemoveReason](Windows-keytype.md#streamremovereason)。 |


**注意**
收到该回调通知后，你可以自行选择是否调用 [unsubscribeScreen](Windows-api.md#IRTCRoom-unsubscribescreen) 取消订阅此流。

<span id="IRTCRoomEventHandler-onstreamsubscribed"></span>
### onStreamSubscribed
```cpp
virtual void bytertc::IRTCRoomEventHandler::onStreamSubscribed(
    SubscribeState state_code,
    const char* user_id,
    const SubscribeConfig& info)
```
关于订阅媒体流状态改变的回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| state_code | **SubscribeState** | 订阅媒体流状态，参看 [SubscribeState](Windows-keytype.md#subscribestate) |
| user_id | **const char*** | 流发布用户的用户 ID |
| info | **const SubscribeConfig&** | 流的属性，参看 [SubscribeConfig](Windows-keytype.md#subscribeconfig) |


**注意**
本地用户收到该回调的时机包括：  

+ 调用 [subscribeStream](Windows-api.md#IRTCRoom-subscribestream) 或 [unsubscribeStream](Windows-api.md#IRTCRoom-unsubscribestream) 订阅/取消订阅指定远端摄像头音视频流后；  
+ 调用 [subscribeScreen](Windows-api.md#IRTCRoom-subscribescreen) 或 [unsubscribeScreen](Windows-api.md#IRTCRoom-unsubscribescreen) 订阅/取消订阅指定远端屏幕共享流后。


<span id="IRTCRoomEventHandler-onroommessagereceived"></span>
### onRoomMessageReceived
```cpp
virtual void bytertc::IRTCRoomEventHandler::onRoomMessageReceived(
    const char* uid,
    const char* message)
```
接收到房间内广播消息的回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | **const char*** | 消息发送者 ID |
| message | **const char*** | 收到的消息内容 |


**注意**
同一房间内其他用户调用 [sendRoomMessage](Windows-api.md#IRTCRoom-sendroommessage) 发送广播消息时会收到该回调。

<span id="IRTCRoomEventHandler-onroombinarymessagereceived"></span>
### onRoomBinaryMessageReceived
```cpp
virtual void bytertc::IRTCRoomEventHandler::onRoomBinaryMessageReceived(
    const char* uid,
    int size,
    const uint8_t* message)
```
接收到房间内二进制广播消息的回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | **const char*** | 消息发送者 ID |
| size | **int** | 收到的二进制消息长度 |
| message | **const uint8_t*** | 收到的二进制消息内容 |


**注意**
同一房间内其他用户调用 [sendRoomBinaryMessage](Windows-api.md#IRTCRoom-sendroombinarymessage) 发送二进制广播消息时会收到该回调。

<span id="IRTCRoomEventHandler-onusermessagereceived"></span>
### onUserMessageReceived
```cpp
virtual void bytertc::IRTCRoomEventHandler::onUserMessageReceived(
    const char* uid,
    const char* message)
```
收到来自房间中其他用户发来的文本消息时（P2P），会收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | **const char*** | 消息发送者 ID 。 |
| message | **const char*** | 收到的文本消息内容。 |


**注意**

+ 你必须先调用 [sendUserMessage](Windows-api.md#IRTCRoom-sendusermessage) 方法，才能收到该回调。


<span id="IRTCRoomEventHandler-onuserbinarymessagereceived"></span>
### onUserBinaryMessageReceived
```cpp
virtual void bytertc::IRTCRoomEventHandler::onUserBinaryMessageReceived(
    const char* uid,
    int size,
    const uint8_t* message)
```
单个用户接收到同一房间内其他 uid 所属用户发来二进制消息的回调（P2P）。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | **const char*** | 消息发送者 ID 。 |
| message | **const uint8_t*** | 收到的二进制消息内容。 |


**注意**

+ 同一房间内其他用户调用 [sendUserBinaryMessage](Windows-api.md#IRTCRoom-senduserbinarymessage) 发送二进制消息给本地用户时，本地用户会收到该回调。


<span id="IRTCRoomEventHandler-onusermessagesendresult"></span>
### onUserMessageSendResult
```cpp
virtual void bytertc::IRTCRoomEventHandler::onUserMessageSendResult(
    int64_t msgid,
    int error)
```
向房间内单个用户发送文本或二进制消息后（P2P），消息发送方会收到该消息发送结果回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| msgid | **int64_t** | 本条消息的 ID。 |
| error | **int** | 文本或二进制消息发送结果，详见 [UserMessageSendResult](Windows-keytype.md#usermessagesendresult) |


**注意**

+ 你必须先调用 [sendUserMessage](Windows-api.md#IRTCRoom-sendusermessage) 或 [sendUserBinaryMessage](Windows-api.md#IRTCRoom-senduserbinarymessage) 接口，才能收到此回调。


<span id="IRTCRoomEventHandler-onroommessagesendresult"></span>
### onRoomMessageSendResult
```cpp
virtual void bytertc::IRTCRoomEventHandler::onRoomMessageSendResult(
    int64_t msgid,
    int error)
```
当调用 [sendRoomMessage](Windows-api.md#IRTCRoom-sendroommessage) 函数发送消息后，回调此条消息的发送结果（反馈）。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| msgid | **int64_t** | 本条消息的 ID |
| error | **int** | 消息发送结果  <br/>详见 [RoomMessageSendResult](Windows-keytype.md#roommessagesendresult) |


<span id="IRTCRoomEventHandler-onvideostreambanned"></span>
### onVideoStreamBanned
```cpp
virtual void bytertc::IRTCRoomEventHandler::onVideoStreamBanned(
    const char* uid,
    bool banned)
```
通过调用服务端 BanUserStream/UnbanUserStream 方法禁用/解禁指定房间内指定用户视频流的发送时，触发此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | **const char*** | 被禁用/解禁的视频流用户 ID |
| banned | **bool** | 视频流发送状态 <br/>• true: 视频流发送被禁用 <br/>• false: 视频流发送被解禁 |


**注意**

+ 房间内指定用户被禁止/解禁视频流发送时，房间内所有用户都会收到该回调。  
+ 若被封禁用户断网或退房后再进房，则依然是封禁状态，且房间内所有人会再次收到该回调。  
+ 指定用户被封禁后，房间内其他用户退房后再进房，会再次收到该回调。  
+ 在控制台开启大会模式后，只有被封禁/解禁用户会收到该回调。  
+ 同一房间解散后再次创建，房间内状态清空。


<span id="IRTCRoomEventHandler-onavsyncstatechange"></span>
### onAVSyncStateChange
```cpp
virtual void bytertc::IRTCRoomEventHandler::onAVSyncStateChange(
    AVSyncState state)
```
发布端调用 [setMultiDeviceAVSync](Windows-api.md#IRTCRoom-setmultideviceavsync) 后音视频同步状态发生改变时，会收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| state | **AVSyncState** | 音视频同步状态，参看 [AVSyncState](Windows-keytype.md#avsyncstate)。 |


<span id="IRTCRoomEventHandler-onaudiostreambanned"></span>
### onAudioStreamBanned
```cpp
virtual void bytertc::IRTCRoomEventHandler::onAudioStreamBanned(
    const char* uid,
    bool banned)
```
通过调用服务端 BanUserStream/UnbanUserStream 方法禁用/解禁指定房间内指定用户音频流的发送时，触发此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | **const char*** | 被禁用/解禁的音频流用户 ID |
| banned | **bool** | 音频流发送状态 <br/>• true: 音频流发送被禁用 <br/>• false: 音频流发送被解禁 |


**注意**

+ 房间内指定用户被禁止/解禁音频流发送时，房间内所有用户都会收到该回调。  
+ 若被封禁用户断网或退房后再进房，则依然是封禁状态，且房间内所有人会再次收到该回调。  
+ 指定用户被封禁后，房间内其他用户退房后再进房，会再次收到该回调。  
+ 在控制台开启大会模式后，只有被封禁/解禁用户会收到该回调。   
+ 同一房间解散后再次创建，房间内状态清空。


<span id="IRTCRoomEventHandler-onforwardstreamstatechanged"></span>
### onForwardStreamStateChanged
```cpp
virtual void bytertc::IRTCRoomEventHandler::onForwardStreamStateChanged(
    ForwardStreamStateInfo* infos,
    int info_count)
```
跨房间媒体流转发状态和错误回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| infos | **ForwardStreamStateInfo*** | 跨房间媒体流转发目标房间信息数组，详见 [ForwardStreamStateInfo](Windows-keytype.md#forwardstreamstateinfo) |
| info_count | **int** | 数组长度，代表目标房间数 |


<span id="IRTCRoomEventHandler-onforwardstreamevent"></span>
### onForwardStreamEvent
```cpp
virtual void bytertc::IRTCRoomEventHandler::onForwardStreamEvent(
    ForwardStreamEventInfo* infos,
    int info_count)
```
跨房间媒体流转发事件回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| infos | **ForwardStreamEventInfo*** | 跨房间媒体流转发目标房间事件数组，详见 [ForwardStreamEventInfo](Windows-keytype.md#forwardstreameventinfo) |
| info_count | **int** | 数组长度，代表目标房间数 |


<span id="IRTCRoomEventHandler-onnetworkquality"></span>
### onNetworkQuality
```cpp
virtual void bytertc::IRTCRoomEventHandler::onNetworkQuality(
    const NetworkQualityStats& localQuality,
    const NetworkQualityStats* remoteQualities,
    int remoteQualityNum)
```
加入房间并发布或订阅流后， 以每 2 秒一次的频率，报告本地用户和已订阅的远端用户的上下行网络质量信息。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| localQuality | **const NetworkQualityStats&** | 本端网络质量，详见 [NetworkQualityStats](Windows-keytype.md#networkqualitystats)。 |
| remoteQualities | **const NetworkQualityStats*** | 已订阅用户的网络质量，详见 [NetworkQualityStats](Windows-keytype.md#networkqualitystats)。 |
| remoteQualityNum | **int** | `remoteQualities` 数组长度<br/>@note 更多通话中的监测接口，详见[通话中质量监测](https://www.volcengine.com/docs/6348/106866) |


# IRTCVideoEventHandler
```cpp
class bytertc::IRTCVideoEventHandler
```

音视频引擎事件回调接口


`Defined in : bytertc_video_event_handler.h`

## 成员函数

| 返回 | 名称 |
| --- | --- |
| **virtual void** | [onWarning](#IRTCVideoEventHandler-onwarning) |
| **virtual void** | [onError](#IRTCVideoEventHandler-onerror) |
| **virtual void** | [onAudioMixingStateChanged](#IRTCVideoEventHandler-onaudiomixingstatechanged) |
| **virtual void** | [onAudioMixingPlayingProgress](#IRTCVideoEventHandler-onaudiomixingplayingprogress) |
| **virtual void** | [onLogReport](#IRTCVideoEventHandler-onlogreport) |
| **virtual void** | [onConnectionStateChanged](#IRTCVideoEventHandler-onconnectionstatechanged) |
| **virtual void** | [onNetworkTypeChanged](#IRTCVideoEventHandler-onnetworktypechanged) |
| **virtual void** | [onSimulcastSubscribeFallback](#IRTCVideoEventHandler-onsimulcastsubscribefallback) |
| **virtual void** | [onPerformanceAlarms](#IRTCVideoEventHandler-onperformancealarms) |
| **virtual void** | [onAudioDeviceStateChanged](#IRTCVideoEventHandler-onaudiodevicestatechanged) |
| **virtual void** | [onVideoDeviceStateChanged](#IRTCVideoEventHandler-onvideodevicestatechanged) |
| **virtual void** | [onAudioDeviceWarning](#IRTCVideoEventHandler-onaudiodevicewarning) |
| **virtual void** | [onVideoDeviceWarning](#IRTCVideoEventHandler-onvideodevicewarning) |
| **virtual void** | [onSysStats](#IRTCVideoEventHandler-onsysstats) |
| **virtual void** | [onCreateRoomStateChanged](#IRTCVideoEventHandler-oncreateroomstatechanged) |
| **virtual void** | [onHttpProxyState](#IRTCVideoEventHandler-onhttpproxystate) |
| **virtual void** | [onHttpsProxyState](#IRTCVideoEventHandler-onhttpsproxystate) |
| **virtual void** | [onSocks5ProxyState](#IRTCVideoEventHandler-onsocks5proxystate) |
| **virtual void** | [onRecordingStateUpdate](#IRTCVideoEventHandler-onrecordingstateupdate) |
| **virtual void** | [onRecordingProgressUpdate](#IRTCVideoEventHandler-onrecordingprogressupdate) |
| **virtual void** | [onLoginResult](#IRTCVideoEventHandler-onloginresult) |
| **virtual void** | [onLogout](#IRTCVideoEventHandler-onlogout) |
| **virtual void** | [onServerParamsSetResult](#IRTCVideoEventHandler-onserverparamssetresult) |
| **virtual void** | [onGetPeerOnlineStatus](#IRTCVideoEventHandler-ongetpeeronlinestatus) |
| **virtual void** | [onUserMessageReceivedOutsideRoom](#IRTCVideoEventHandler-onusermessagereceivedoutsideroom) |
| **virtual void** | [onUserBinaryMessageReceivedOutsideRoom](#IRTCVideoEventHandler-onuserbinarymessagereceivedoutsideroom) |
| **virtual void** | [onUserMessageSendResultOutsideRoom](#IRTCVideoEventHandler-onusermessagesendresultoutsideroom) |
| **virtual void** | [onServerMessageSendResult](#IRTCVideoEventHandler-onservermessagesendresult) |
| **virtual void** | [onSEIMessageReceived](#IRTCVideoEventHandler-onseimessagereceived) |
| **virtual void** | [onRemoteAudioPropertiesReport](#IRTCVideoEventHandler-onremoteaudiopropertiesreport) |
| **virtual void** | [onLocalAudioPropertiesReport](#IRTCVideoEventHandler-onlocalaudiopropertiesreport) |
| **virtual void** | [onAudioPlaybackDeviceTestVolume](#IRTCVideoEventHandler-onaudioplaybackdevicetestvolume) |
| **virtual void** | [onAudioDeviceVolumeChanged](#IRTCVideoEventHandler-onaudiodevicevolumechanged) |
| **virtual void** | [onLocalAudioStateChanged](#IRTCVideoEventHandler-onlocalaudiostatechanged) |
| **virtual void** | [onUserStartAudioCapture](#IRTCVideoEventHandler-onuserstartaudiocapture) |
| **virtual void** | [onUserStopAudioCapture](#IRTCVideoEventHandler-onuserstopaudiocapture) |
| **virtual void** | [onActiveSpeaker](#IRTCVideoEventHandler-onactivespeaker) |
| **virtual void** | [onStreamSyncInfoReceived](#IRTCVideoEventHandler-onstreamsyncinforeceived) |
| **virtual void** | [onNetworkDetectionResult](#IRTCVideoEventHandler-onnetworkdetectionresult) |
| **virtual void** | [onNetworkDetectionStopped](#IRTCVideoEventHandler-onnetworkdetectionstopped) |
| **virtual void** | [onPlayPublicStreamResult](#IRTCVideoEventHandler-onplaypublicstreamresult) |
| **virtual void** | [onPublicStreamSEIMessageReceived](#IRTCVideoEventHandler-onpublicstreamseimessagereceived) |
| **virtual void** | [onFirstPublicStreamVideoFrameDecoded](#IRTCVideoEventHandler-onfirstpublicstreamvideoframedecoded) |
| **virtual void** | [onUserStartVideoCapture](#IRTCVideoEventHandler-onuserstartvideocapture) |
| **virtual void** | [onUserStopVideoCapture](#IRTCVideoEventHandler-onuserstopvideocapture) |
| **virtual void** | [onLocalVideoSizeChanged](#IRTCVideoEventHandler-onlocalvideosizechanged) |
| **virtual void** | [onRemoteVideoSizeChanged](#IRTCVideoEventHandler-onremotevideosizechanged) |
| **virtual void** | [onFirstLocalVideoFrameCaptured](#IRTCVideoEventHandler-onfirstlocalvideoframecaptured) |
| **virtual void** | [onFirstRemoteAudioFrame](#IRTCVideoEventHandler-onfirstremoteaudioframe) |
| **virtual void** | [onRemoteAudioStateChanged](#IRTCVideoEventHandler-onremoteaudiostatechanged) |
| **virtual void** | [onLocalVideoStateChanged](#IRTCVideoEventHandler-onlocalvideostatechanged) |
| **virtual void** | [onRemoteVideoStateChanged](#IRTCVideoEventHandler-onremotevideostatechanged) |
| **virtual void** | [onAudioFrameSendStateChanged](#IRTCVideoEventHandler-onaudioframesendstatechanged) |
| **virtual void** | [onVideoFrameSendStateChanged](#IRTCVideoEventHandler-onvideoframesendstatechanged) |
| **virtual void** | [onFirstRemoteVideoFrameRendered](#IRTCVideoEventHandler-onfirstremotevideoframerendered) |
| **virtual void** | [onFirstRemoteVideoFrameDecoded](#IRTCVideoEventHandler-onfirstremotevideoframedecoded) |
| **virtual void** | [onScreenVideoFrameSendStateChanged](#IRTCVideoEventHandler-onscreenvideoframesendstatechanged) |
| **virtual void** | [onAudioFramePlayStateChanged](#IRTCVideoEventHandler-onaudioframeplaystatechanged) |
| **virtual void** | [onVideoFramePlayStateChanged](#IRTCVideoEventHandler-onvideoframeplaystatechanged) |
| **virtual void** | [onScreenVideoFramePlayStateChanged](#IRTCVideoEventHandler-onscreenvideoframeplaystatechanged) |
| **virtual void** | [onFirstLocalAudioFrame](#IRTCVideoEventHandler-onfirstlocalaudioframe) |
| **virtual void** | [onPushPublicStreamResult](#IRTCVideoEventHandler-onpushpublicstreamresult) |
| **virtual void** | [onFirstPublicStreamAudioFrame](#IRTCVideoEventHandler-onfirstpublicstreamaudioframe) |
| **virtual void** | [onCloudProxyConnected](#IRTCVideoEventHandler-oncloudproxyconnected) |
| **virtual void** | [onEchoTestResult](#IRTCVideoEventHandler-onechotestresult) |


## 函数说明
<span id="IRTCVideoEventHandler-onwarning"></span>
### onWarning
```cpp
virtual void bytertc::IRTCVideoEventHandler::onWarning(
    int warn)
```
当内部发生警告事件时触发该回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| warn | **int** | 警告标识码，详见:[WarningCode](Windows-errorcode.md#warningcode) |


<span id="IRTCVideoEventHandler-onerror"></span>
### onError
```cpp
virtual void bytertc::IRTCVideoEventHandler::onError(
    int err)
```
当 SDK 内部发生不可逆转错误时触发该回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| err | **int** | 错误标识码，参看 [ErrorCode](Windows-errorcode.md#errorcode) |


<span id="IRTCVideoEventHandler-onaudiomixingstatechanged"></span>
### onAudioMixingStateChanged
```cpp
virtual void bytertc::IRTCVideoEventHandler::onAudioMixingStateChanged(
    int mix_id,
    bytertc::AudioMixingState state,
    bytertc::AudioMixingError error)
```
音频混音文件播放状态改变时回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mix_id | **int** | 混音 ID  <br/>使用 [IAudioMixingManager](Windows-api.md#iaudiomixingmanager) 相关接口时传入的唯一 ID。 |
| state | **bytertc::AudioMixingState** | 混音状态  <br/>其混音状态可参考： [AudioMixingState](Windows-keytype.md#audiomixingstate)。 |
| error | **bytertc::AudioMixingError** | 错误码  <br/>详见 [AudioMixingError](Windows-keytype.md#audiomixingerror) |


**注意**
此回调会被触发的时机汇总如下：  

+ 1. 音乐文件类型： 
+ 当调用 [startAudioMixing](Windows-api.md#IAudioMixingManager-startaudiomixing) 方法成功后，会触发 state 值为 kAudioMixingStatePlaying 回调；否则触发 state 值为 kAudioMixingStateFailed 的回调。  
+ 当使用相同的 ID 重复调用 [startAudioMixing](Windows-api.md#IAudioMixingManager-startaudiomixing) 后，后一次会覆盖前一次，且本回调会以 kAudioMixingStateStopped 通知前一次混音已停止。  
+ 当调用 [pauseAudioMixing](Windows-api.md#IAudioMixingManager-pauseaudiomixing) 方法暂停播放成功后，会触发 state 值为 kAudioMixingStatePaused 回调；否则触发 state 值为 kAudioMixingStateFailed 的回调。  
+ 当调用 [resumeAudioMixing](Windows-api.md#IAudioMixingManager-resumeaudiomixing) 方法恢复播放成功后，会触发 state 值为 kAudioMixingStatePlaying 回调；否则触发 state 值为 kAudioMixingStateFailed 的回调。  
+ 当调用 [stopAudioMixing](Windows-api.md#IAudioMixingManager-stopaudiomixing) 方法暂停止播放成功后，会触发 state 值为 kAudioMixingStateStopped 回调；否则触发 state 值为 kAudioMixingStateFailed 的回调。  
+ 播放结束会触发 state 值为 kAudioMixingStateFinished 回调。 
+ 2. PCM 流类型： 
+ 当调用 [enableAudioMixingFrame](Windows-api.md#IAudioMixingManager-enableaudiomixingframe) 方法成功后，会触发 state 值为 kAudioMixingStatePCMEnabled 回调；否则触发 state 值为 kAudioMixingStateFailed 的回调。（Linux 不支持）  
+ 当调用 [disableAudioMixingFrame](Windows-api.md#IAudioMixingManager-disableaudiomixingframe) 方法成功后，会触发 state 值为 kAudioMixingStatePCMDisabled 回调；否则触发 state 值为 kAudioMixingStateFailed 的回调。


<span id="IRTCVideoEventHandler-onaudiomixingplayingprogress"></span>
### onAudioMixingPlayingProgress
```cpp
virtual void bytertc::IRTCVideoEventHandler::onAudioMixingPlayingProgress(
    int mix_id,
    int64_t progress)
```
混音音频文件播放进度回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mix_id | **int** | 混音 ID |
| progress | **int64_t** | 当前混音音频文件播放进度，单位毫秒 |


**注意**
调用 [setAudioMixingProgressInterval](Windows-api.md#IAudioMixingManager-setaudiomixingprogressinterval) 将时间间隔设为大于 0 的值后，或调用 [startAudioMixing](Windows-api.md#IAudioMixingManager-startaudiomixing) 将 [AudioMixingConfig](Windows-keytype.md#audiomixingconfig) 中的时间间隔设为大于 0 的值后，SDK 会按照设置的时间间隔回调该事件。 

<span id="IRTCVideoEventHandler-onlogreport"></span>
### onLogReport
```cpp
virtual void bytertc::IRTCVideoEventHandler::onLogReport(
    const char* log_type,
    const char* log_content)
```
端监控日志回调。当产生一个端监控事件时触发该回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| log_type | **const char*** | 事件类型。目前类型固定为 "live_webrtc_monitor_log"。 |
| log_content | **const char*** | 端监控日志内容。 |


<span id="IRTCVideoEventHandler-onconnectionstatechanged"></span>
### onConnectionStateChanged
```cpp
virtual void bytertc::IRTCVideoEventHandler::onConnectionStateChanged(
    bytertc::ConnectionState state)
```
SDK 与信令服务器连接状态改变回调。连接状态改变时触发。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| state | **bytertc::ConnectionState** | 当前 SDK 与信令服务器的连接状态，详见 [ConnectionState](Windows-keytype.md#connectionstate)。 |


**注意**
更多信息参见 [连接状态提示](https://www.volcengine.com/docs/6348/95376)。

<span id="IRTCVideoEventHandler-onnetworktypechanged"></span>
### onNetworkTypeChanged
```cpp
virtual void bytertc::IRTCVideoEventHandler::onNetworkTypeChanged(
    bytertc::NetworkType type)
```
SDK 当前网络连接类型改变回调。当 SDK 的当前网络连接类型发生改变时回调该事件。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| type | **bytertc::NetworkType** | SDK 当前的网络连接类型，详见：[NetworkType](Windows-keytype.md#networktype) 。 |


<span id="IRTCVideoEventHandler-onsimulcastsubscribefallback"></span>
### onSimulcastSubscribeFallback
```cpp
virtual void bytertc::IRTCVideoEventHandler::onSimulcastSubscribeFallback(
    const RemoteStreamSwitch& event)
```
音视频流因网络环境变化等原因发生回退，或从回退中恢复时，触发该回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| event | **const RemoteStreamSwitch&** | 音视频流发生变化的信息。参看 [RemoteStreamSwitch](Windows-keytype.md#remotestreamswitch)。 |


<span id="IRTCVideoEventHandler-onperformancealarms"></span>
### onPerformanceAlarms
```cpp
virtual void bytertc::IRTCVideoEventHandler::onPerformanceAlarms(
    bytertc::PerformanceAlarmMode mode,
    const char* room_id,
    bytertc::PerformanceAlarmReason reason,
    const bytertc::SourceWantedData& data)
```
本地未开启发布性能回退，检测到设备性能不足时，收到此回调。<br>
本地开启发布性能回退，因设备性能/网络原因，造成发布性能回退/恢复时，收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mode | **bytertc::PerformanceAlarmMode** | 指示本地是否开启发布回退功能。参看 [PerformanceAlarmMode](Windows-keytype.md#performancealarmmode)  <br/>• 当发布端未开启发布性能回退时，mode 值为 kPerformanceAlarmModeNormal。  <br/>• 当发布端开启发布性能回退时，mode 值为 kPerformanceAlarmModeSimulcast。 |
| room_id | **const char*** | • 未开启发布性能回退时，room_id 为空 <br/>• 开启发布性能回退时，room_id 是告警影响的房间 ID。 |
| reason | **bytertc::PerformanceAlarmReason** | 告警原因，参看 [PerformanceAlarmReason](Windows-keytype.md#performancealarmreason) |
| data | **const bytertc::SourceWantedData&** | 性能回退相关数据，详见 [SourceWantedData](Windows-keytype.md#sourcewanteddata)。 |


<span id="IRTCVideoEventHandler-onaudiodevicestatechanged"></span>
### onAudioDeviceStateChanged
```cpp
virtual void bytertc::IRTCVideoEventHandler::onAudioDeviceStateChanged(
    const char* device_id,
    bytertc::RTCAudioDeviceType device_type,
    bytertc::MediaDeviceState device_state,
    bytertc::MediaDeviceError device_error)
```
音频设备状态回调。提示音频采集、音频播放等设备设备的状态。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| device_id | **const char*** | 设备 ID。 |
| device_type | **bytertc::RTCAudioDeviceType** | 设备类型，详见 [RTCAudioDeviceType](Windows-keytype.md#rtcaudiodevicetype) |
| device_state | **bytertc::MediaDeviceState** | 设备状态，详见 [MediaDeviceState](Windows-keytype.md#mediadevicestate) |
| device_error | **bytertc::MediaDeviceError** | 设备错误类型，详见 [MediaDeviceError](Windows-keytype.md#mediadeviceerror) |


<span id="IRTCVideoEventHandler-onvideodevicestatechanged"></span>
### onVideoDeviceStateChanged
```cpp
virtual void bytertc::IRTCVideoEventHandler::onVideoDeviceStateChanged(
    const char* device_id,
    bytertc::RTCVideoDeviceType device_type,
    bytertc::MediaDeviceState device_state,
    bytertc::MediaDeviceError device_error)
```
视频频设备状态回调。提示摄像头视频采集、屏幕视频采集等设备的状态。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| device_id | **const char*** | 设备 ID。采集屏幕共享流时，设备 ID 为固定字符串 `screen_capture_video` |
| device_type | **bytertc::RTCVideoDeviceType** | 设备类型，详见 [RTCVideoDeviceType](Windows-keytype.md#rtcvideodevicetype) |
| device_state | **bytertc::MediaDeviceState** | 设备状态，详见 [MediaDeviceState](Windows-keytype.md#mediadevicestate) |
| device_error | **bytertc::MediaDeviceError** | 设备错误类型，详见 [MediaDeviceError](Windows-keytype.md#mediadeviceerror) |


<span id="IRTCVideoEventHandler-onaudiodevicewarning"></span>
### onAudioDeviceWarning
```cpp
virtual void bytertc::IRTCVideoEventHandler::onAudioDeviceWarning(
    const char* device_id,
    bytertc::RTCAudioDeviceType device_type,
    bytertc::MediaDeviceWarning device_warning)
```
音频设备警告回调。音频设备包括音频采集设备和音频渲染设备。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| device_id | **const char*** | 设备 ID |
| device_type | **bytertc::RTCAudioDeviceType** | 详见 [RTCAudioDeviceType](Windows-keytype.md#rtcaudiodevicetype) |
| device_warning | **bytertc::MediaDeviceWarning** | 详见 [MediaDeviceWarning](Windows-keytype.md#mediadevicewarning) |


<span id="IRTCVideoEventHandler-onvideodevicewarning"></span>
### onVideoDeviceWarning
```cpp
virtual void bytertc::IRTCVideoEventHandler::onVideoDeviceWarning(
    const char* device_id,
    bytertc::RTCVideoDeviceType device_type,
    bytertc::MediaDeviceWarning device_warning)
```
视频设备警告回调，包括视频采集设备等。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| device_id | **const char*** | 设备 ID |
| device_type | **bytertc::RTCVideoDeviceType** | 详见 [RTCVideoDeviceType](Windows-keytype.md#rtcvideodevicetype) |
| device_warning | **bytertc::MediaDeviceWarning** | 详见 [MediaDeviceWarning](Windows-keytype.md#mediadevicewarning) |


<span id="IRTCVideoEventHandler-onsysstats"></span>
### onSysStats
```cpp
virtual void bytertc::IRTCVideoEventHandler::onSysStats(
    const bytertc::SysStats& stats)
```
周期性（2s）地发出回调，报告当前cpu与memory使用率

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stats | **const bytertc::SysStats&** | 返回包含当前系统状态信息的结构体，详见 [SysStats](Windows-keytype.md#sysstats) |


<span id="IRTCVideoEventHandler-oncreateroomstatechanged"></span>
### onCreateRoomStateChanged
```cpp
virtual void bytertc::IRTCVideoEventHandler::onCreateRoomStateChanged(
    const char* room_id,
    int error_code)
```
创建房间失败回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| room_id | **const char*** | 房间 ID。 |
| error_code | **int** | 创建房间错误码，具体原因参看 [ErrorCode](Windows-errorcode.md#errorcode)。 |


<span id="IRTCVideoEventHandler-onhttpproxystate"></span>
### onHttpProxyState
```cpp
virtual void bytertc::IRTCVideoEventHandler::onHttpProxyState(
    int state)
```
HTTP 代理连接状态改变时，收到该回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| state | **int** | 当前 HTTP 代理连接状态，详见 [HttpProxyState](Windows-keytype.md#httpproxystate) |


<span id="IRTCVideoEventHandler-onhttpsproxystate"></span>
### onHttpsProxyState
```cpp
virtual void bytertc::IRTCVideoEventHandler::onHttpsProxyState(
    int state)
```
HTTPS 代理连接状态改变时，收到该回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| state | **int** | 当前 HTTPS 代理连接状态，详见 [HttpProxyState](Windows-keytype.md#httpproxystate) |


<span id="IRTCVideoEventHandler-onsocks5proxystate"></span>
### onSocks5ProxyState
```cpp
virtual void bytertc::IRTCVideoEventHandler::onSocks5ProxyState(
    int state,
    const char* cmd,
    const char* proxy_address,
    const char* local_address,
    const char* remote_address)
```
Socks5 代理状态改变时，收到该回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| state | **int** | SOCKS5 代理连接状态，详见 [Socks5ProxyState](Windows-keytype.md#socks5proxystate) |
| cmd | **const char*** | 代理连接的每一步操作命令 |
| proxy_address | **const char*** | 代理地址信息 |
| local_address | **const char*** | 当前连接使用的本地地址 |
| remote_address | **const char*** | 远端的连接地址 |


<span id="IRTCVideoEventHandler-onrecordingstateupdate"></span>
### onRecordingStateUpdate
```cpp
virtual void bytertc::IRTCVideoEventHandler::onRecordingStateUpdate(
    StreamIndex type,
    RecordingState state,
    RecordingErrorCode error_code,
    RecordingInfo info)
```
获取本地录制状态回调。  <br>
该回调由 [startFileRecording](Windows-api.md#IRTCVideo-startfilerecording) 或 [stopFileRecording](Windows-api.md#IRTCVideo-stopfilerecording) 触发。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| type | **StreamIndex** | 录制流的流属性，参看 [StreamIndex](Windows-keytype.md#streamindex) |
| state | **RecordingState** | 录制状态，参看 [RecordingState](Windows-keytype.md#recordingstate) |
| error_code | **RecordingErrorCode** | 录制错误码，参看 [RecordingErrorCode](Windows-keytype.md#recordingerrorcode) |
| info | **RecordingInfo** | 录制文件的详细信息，参看 [RecordingInfo](Windows-keytype.md#recordinginfo) |


<span id="IRTCVideoEventHandler-onrecordingprogressupdate"></span>
### onRecordingProgressUpdate
```cpp
virtual void bytertc::IRTCVideoEventHandler::onRecordingProgressUpdate(
    StreamIndex type,
    RecordingProgress process,
    RecordingInfo info)
```
本地录制进度回调。  <br>
该回调由 [startFileRecording](Windows-api.md#IRTCVideo-startfilerecording) 触发，录制状态正常时，系统每秒钟都会通过该回调提示录制进度。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| type | **StreamIndex** | 录制流的流属性，参看 [StreamIndex](Windows-keytype.md#streamindex) |
| process | **RecordingProgress** | 录制进度，参看 [RecordingProgress](Windows-keytype.md#recordingprogress) |
| info | **RecordingInfo** | 录制文件的详细信息，参看 [RecordingInfo](Windows-keytype.md#recordinginfo) |


<span id="IRTCVideoEventHandler-onloginresult"></span>
### onLoginResult
```cpp
virtual void bytertc::IRTCVideoEventHandler::onLoginResult(
    const char* uid,
    int error_code,
    int elapsed)
```
登录结果回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | **const char*** | 登录用户 ID |
| error_code | **int** | 登录结果  <br/>详见 [LoginErrorCode](Windows-errorcode.md#loginerrorcode)。 |
| elapsed | **int** | 从调用 [login](Windows-api.md#IRTCVideo-login) 接口开始到返回结果所用时长  <br/>单位为 ms。 |


**注意**
调用 [login](Windows-api.md#IRTCVideo-login) 后，会收到此回调。

<span id="IRTCVideoEventHandler-onlogout"></span>
### onLogout
```cpp
virtual void bytertc::IRTCVideoEventHandler::onLogout()
```
登出结果回调


**注意**
调用 [logout](Windows-api.md#IRTCVideo-logout) 后，会收到此回调。

<span id="IRTCVideoEventHandler-onserverparamssetresult"></span>
### onServerParamsSetResult
```cpp
virtual void bytertc::IRTCVideoEventHandler::onServerParamsSetResult(
    int error)
```
设置应用服务器参数的返回结果

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| error | **int** | 设置结果  <br/>• 返回 200，设置成功  <br/>• 返回其他，设置失败，详见 [UserMessageSendResult](Windows-keytype.md#usermessagesendresult) |


**注意**
调用 [setServerParams](Windows-api.md#IRTCVideo-setserverparams) 后，会收到此回调。

<span id="IRTCVideoEventHandler-ongetpeeronlinestatus"></span>
### onGetPeerOnlineStatus
```cpp
virtual void bytertc::IRTCVideoEventHandler::onGetPeerOnlineStatus(
    const char* peer_user_id,
    int status)
```
查询对端或本端用户登录状态的返回结果

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| peer_user_id | **const char*** | 需要查询的用户 ID |
| status | **int** | 查询的用户登录状态  <br/>详见 [USER_ONLINE_STATUS](Windows-keytype.md#user_online_status). |


**注意**
必须先调用 [getPeerOnlineStatus](Windows-api.md#IRTCVideo-getpeeronlinestatus)，才能收到此回调。

<span id="IRTCVideoEventHandler-onusermessagereceivedoutsideroom"></span>
### onUserMessageReceivedOutsideRoom
```cpp
virtual void bytertc::IRTCVideoEventHandler::onUserMessageReceivedOutsideRoom(
    const char* uid,
    const char* message)
```
收到房间外用户调用 [sendUserMessageOutsideRoom](Windows-api.md#IRTCVideo-sendusermessageoutsideroom) 发来的文本消息时，会收到此回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | **const char*** | 消息发送者 ID |
| message | **const char*** | 收到的文本消息内容 |


<span id="IRTCVideoEventHandler-onuserbinarymessagereceivedoutsideroom"></span>
### onUserBinaryMessageReceivedOutsideRoom
```cpp
virtual void bytertc::IRTCVideoEventHandler::onUserBinaryMessageReceivedOutsideRoom(
    const char* uid,
    int size,
    const uint8_t* message)
```
收到房间外用户调用 [sendUserBinaryMessageOutsideRoom](Windows-api.md#IRTCVideo-senduserbinarymessageoutsideroom) 发来的二进制消息时，会收到此回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | **const char*** | 消息发送者 ID |
| size | **int** | 二进制消息长度 |
| message | **const uint8_t*** | 收到的二进制消息内容 |


<span id="IRTCVideoEventHandler-onusermessagesendresultoutsideroom"></span>
### onUserMessageSendResultOutsideRoom
```cpp
virtual void bytertc::IRTCVideoEventHandler::onUserMessageSendResultOutsideRoom(
    int64_t msgid,
    int error)
```
给房间外指定的用户发送消息的回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| msgid | **int64_t** | 本条消息的 ID  <br/>所有的 P2P 和 P2Server 消息共用一个 ID 序列。 |
| error | **int** | 消息发送结果  <br/>详见 [UserMessageSendResult](Windows-keytype.md#usermessagesendresult)。 |


**注意**
当调用 [sendUserMessageOutsideRoom](Windows-api.md#IRTCVideo-sendusermessageoutsideroom) 或 [sendUserBinaryMessageOutsideRoom](Windows-api.md#IRTCVideo-senduserbinarymessageoutsideroom) 发送消息后，会收到此回调。

<span id="IRTCVideoEventHandler-onservermessagesendresult"></span>
### onServerMessageSendResult
```cpp
virtual void bytertc::IRTCVideoEventHandler::onServerMessageSendResult(
    int64_t msgid,
    int error,
    const bytertc::ServerACKMsg& msg)
```
给应用服务器发送消息的回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| msgid | **int64_t** | 本条消息的 ID。<br/>所有的 P2P 和 P2Server 消息共用一个 ID 序列。 |
| error | **int** | 消息发送结果，详见 [UserMessageSendResult](Windows-keytype.md#usermessagesendresult)。 |
| msg | **int64_t** | 应用服务器收到 HTTP 请求后，在 ACK 中返回的信息。消息不超过 64 KB。 |


**注意**
本回调为异步回调。当调用 [sendServerMessage](Windows-api.md#IRTCVideo-sendservermessage) 或 [sendServerBinaryMessage](Windows-api.md#IRTCVideo-sendserverbinarymessage) 接口发送消息后，会收到此回调。

<span id="IRTCVideoEventHandler-onseimessagereceived"></span>
### onSEIMessageReceived
```cpp
virtual void bytertc::IRTCVideoEventHandler::onSEIMessageReceived(
    RemoteStreamKey stream_key,
    const uint8_t* message,
    int length)
```
收到通过 [sendSEIMessage](Windows-api.md#IRTCVideo-sendseimessage) 发送的带有 SEI 消息的视频帧时，收到此回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stream_key | **RemoteStreamKey** | 包含 SEI 发送者的用户名，所在的房间名和媒体流，参看 [RemoteStreamKey](Windows-keytype.md#remotestreamkey) |
| message | **const uint8_t*** | 收到的 SEI 消息内容 |
| length | **int** | 收到的 SEI 消息长度 |


<span id="IRTCVideoEventHandler-onremoteaudiopropertiesreport"></span>
### onRemoteAudioPropertiesReport
```cpp
virtual void bytertc::IRTCVideoEventHandler::onRemoteAudioPropertiesReport(
    const RemoteAudioPropertiesInfo* audio_properties_infos,
    int audio_properties_info_number,
    int total_remote_volume)
```
远端用户进房后，本地调用 [enableAudioPropertiesReport](Windows-api.md#IRTCVideo-enableaudiopropertiesreport)，根据设置的 interval 值，本地会周期性地收到此回调，了解订阅的远端用户的音频信息。<br>
远端用户的音频包括使用 RTC SDK 内部机制/自定义机制采集的麦克风音频和屏幕音频。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audio_properties_infos | **const RemoteAudioPropertiesInfo*** | 远端音频信息，其中包含音频流属性、房间 ID、用户 ID ，详见 [RemoteAudioPropertiesInfo](Windows-keytype.md#remoteaudiopropertiesinfo)。 |
| audio_properties_info_number | **int** | 数组长度 |
| total_remote_volume | **int** | 所有订阅的远端流的总音量，范围是 [0,255]。  <br/>• [0,25] 接近无声；  <br/>• [25,75] 为低音量；  <br/>• [76,204] 为中音量；  <br/>• [205,255] 为高音量。 |


<span id="IRTCVideoEventHandler-onlocalaudiopropertiesreport"></span>
### onLocalAudioPropertiesReport
```cpp
virtual void bytertc::IRTCVideoEventHandler::onLocalAudioPropertiesReport(
    const LocalAudioPropertiesInfo * audio_properties_infos,
    int audio_properties_info_number)
```
调用 [enableAudioPropertiesReport](Windows-api.md#IRTCVideo-enableaudiopropertiesreport) 后，根据设置的 interval 值，你会周期性地收到此回调，了解本地音频的相关信息。  <br>
本地音频包括使用 RTC SDK 内部机制采集的麦克风音频和屏幕音频。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audio_properties_infos | **const LocalAudioPropertiesInfo*** | 本地音频信息，详见 [LocalAudioPropertiesInfo](Windows-keytype.md#localaudiopropertiesinfo) 。 |
| audio_properties_info_number | **int** | 数组长度 |


<span id="IRTCVideoEventHandler-onaudioplaybackdevicetestvolume"></span>
### onAudioPlaybackDeviceTestVolume
```cpp
virtual void bytertc::IRTCVideoEventHandler::onAudioPlaybackDeviceTestVolume(
    int volume)
```
回调音频设备测试时的播放音量

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| volume | **int** | 音频设备测试播放音量。单位：毫秒。推荐设置为 200 ms。范围：[0,255] |


**注意**
调用 [startAudioPlaybackDeviceTest](Windows-api.md#IAudioDeviceManager-startaudioplaybackdevicetest) 或 [startAudioDeviceRecordTest](Windows-api.md#IAudioDeviceManager-startaudiodevicerecordtest)，开始播放音频文件或录音时，将开启该回调。本回调为周期性回调，回调周期由上述接口的 `interval` 参数指定。

<span id="IRTCVideoEventHandler-onaudiodevicevolumechanged"></span>
### onAudioDeviceVolumeChanged
```cpp
virtual void bytertc::IRTCVideoEventHandler::onAudioDeviceVolumeChanged(
    bytertc::RTCAudioDeviceType device_type,
    int volume,
    bool muted)
```
音频设备音量改变回调。当通过系统设置，改变音频设备音量或静音状态时，触发本回调。本回调无需手动开启。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| device_type | **bytertc::RTCAudioDeviceType** | 设备类型，包括麦克风和扬声器，参阅 [RTCAudioDeviceType](Windows-keytype.md#rtcaudiodevicetype)。 |
| volume | **int** | 音量值，[0, 255]。当 volume 变为 0 时，muted 会变为 True。注意：在 Windows 端，当麦克风 volume 变为 0 时，muted 值不变。 |
| muted | **bool** | 是否禁音状态。扬声器被设置为禁音时，muted 为 True，但 volume 保持不变。 |


<span id="IRTCVideoEventHandler-onlocalaudiostatechanged"></span>
### onLocalAudioStateChanged
```cpp
virtual void bytertc::IRTCVideoEventHandler::onLocalAudioStateChanged(
    LocalAudioStreamState state,
    LocalAudioStreamError error)
```
本地音频的状态发生改变时，该回调通知当前的本地音频状态。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| state | **LocalAudioStreamState** | 本地音频设备的状态，详见： [LocalAudioStreamState](Windows-keytype.md#localaudiostreamstate) |
| error | **LocalAudioStreamError** | 本地音频状态改变时的错误码，详见：[LocalAudioStreamError](Windows-keytype.md#localaudiostreamerror) |


<span id="IRTCVideoEventHandler-onuserstartaudiocapture"></span>
### onUserStartAudioCapture
```cpp
virtual void bytertc::IRTCVideoEventHandler::onUserStartAudioCapture(
    const char* room_id,
    const char* user_id)
```
房间内的用户调用 [startAudioCapture](Windows-api.md#IRTCVideo-startaudiocapture) 开启音频采集时，房间内其他用户会收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| room_id | **const char*** | 开启音频采集的远端用户所在的房间 ID |
| user_id | **const char*** | 开启音频采集的远端用户 ID |


<span id="IRTCVideoEventHandler-onuserstopaudiocapture"></span>
### onUserStopAudioCapture
```cpp
virtual void bytertc::IRTCVideoEventHandler::onUserStopAudioCapture(
    const char* room_id,
    const char* user_id)
```
房间内的用户调用 [stopAudioCapture](Windows-api.md#IRTCVideo-stopaudiocapture) 关闭音频采集时，房间内其他用户会收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| room_id | **const char*** | 关闭音频采集的远端用户所在的房间 ID |
| user_id | **const char*** | 关闭音频采集的远端用户 ID |


<span id="IRTCVideoEventHandler-onactivespeaker"></span>
### onActiveSpeaker
```cpp
virtual void bytertc::IRTCVideoEventHandler::onActiveSpeaker(
    const char* room_id,
    const char* uid)
```
调用 [enableAudioPropertiesReport](Windows-api.md#IRTCVideo-enableaudiopropertiesreport) 后，根据设置的 `config.interval`，你会周期性地收到此回调，获取房间内的最活跃用户信息。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| room_id | **const char*** | 房间 ID |
| uid | **const char*** | 最活跃用户（ActiveSpeaker）的用户 ID |


<span id="IRTCVideoEventHandler-onstreamsyncinforeceived"></span>
### onStreamSyncInfoReceived
```cpp
virtual void bytertc::IRTCVideoEventHandler::onStreamSyncInfoReceived(
    RemoteStreamKey stream_key,
    SyncInfoStreamType stream_type,
    const uint8_t* data,
    int32_t length)
```
音频流同步信息回调。可以通过此回调，在远端用户调用 [sendStreamSyncInfo](Windows-api.md#IRTCVideo-sendstreamsyncinfo) 发送音频流同步消息后，收到远端发送的音频流同步信息。  <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stream_key | **RemoteStreamKey** | 远端流信息，详见 [RemoteStreamKey](Windows-keytype.md#remotestreamkey) 。 |
| stream_type | **SyncInfoStreamType** | 媒体流类型，详见 [SyncInfoStreamType](Windows-keytype.md#syncinfostreamtype) 。 |
| data | **const uint8_t*** | 消息内容。 |
| length | **int32_t** | 消息长度。 |


<span id="IRTCVideoEventHandler-onnetworkdetectionresult"></span>
### onNetworkDetectionResult
```cpp
virtual void bytertc::IRTCVideoEventHandler::onNetworkDetectionResult(
    NetworkDetectionLinkType type,
    NetworkQuality quality,
    int rtt,
    double lost_rate,
    int bitrate,
    int jitter)
```
通话前网络探测结果。  <br>
成功调用 [startNetworkDetection](Windows-api.md#IRTCVideo-startnetworkdetection) 接口开始探测后，会在 3s 内首次收到该回调，之后每 2s 收到一次该回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| type | **NetworkDetectionLinkType** | 探测网络类型为上行/下行 |
| quality | **NetworkQuality** | 探测网络的质量，参看 [NetworkQuality](Windows-keytype.md#networkquality)。 |
| rtt | **int** | 探测网络的 RTT，单位：ms |
| lost_rate | **double** | 探测网络的丢包率 |
| bitrate | **int** | 探测网络的带宽，单位：kbps |
| jitter | **int** | 探测网络的抖动,单位：ms |


<span id="IRTCVideoEventHandler-onnetworkdetectionstopped"></span>
### onNetworkDetectionStopped
```cpp
virtual void bytertc::IRTCVideoEventHandler::onNetworkDetectionStopped(
    NetworkDetectionStopReason reason)
```
通话前网络探测结束
以下情况将停止探测并收到本一次本回调：<br>
1. 当调用 [stopNetworkDetection](Windows-api.md#IRTCVideo-stopnetworkdetection) 接口停止探测后，会收到一次该回调；
2. 当收到远端/本端音频首帧后，停止探测；
3. 当探测超过3分钟后，停止探测；
4. 当探测链路断开一定时间之后，停止探测。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| reason | **NetworkDetectionStopReason** | 停止探测的原因类型,参考 [NetworkDetectionStopReason](Windows-keytype.md#networkdetectionstopreason) |


<span id="IRTCVideoEventHandler-onplaypublicstreamresult"></span>
### onPlayPublicStreamResult
```cpp
virtual void bytertc::IRTCVideoEventHandler::onPlayPublicStreamResult(
    const char* public_stream_id,
    int errorCode)
```
订阅公共流的结果回调<br>
通过 [startPlayPublicStream](Windows-api.md#IRTCVideo-startplaypublicstream) 订阅公共流后，可以通过本回调获取订阅结果。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| public_stream_id | **const char*** | 公共流的 ID |
| errorCode | **int** | 公共流订阅结果状态码。详见 [PublicStreamErrorCode](Windows-keytype.md#publicstreamerrorcode)。 |


<span id="IRTCVideoEventHandler-onpublicstreamseimessagereceived"></span>
### onPublicStreamSEIMessageReceived
```cpp
virtual void bytertc::IRTCVideoEventHandler::onPublicStreamSEIMessageReceived(
    const char* public_stream_id,
    const uint8_t* message,
    int message_length)
```
回调公共流中包含的 SEI 信息<br>
通过 [startPlayPublicStream](Windows-api.md#IRTCVideo-startplaypublicstream) 开始播放公共流后，可以通过本回调获取公共流中包含的 SEI 信息。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| public_stream_id | **const char*** | 公共流 ID |
| message | **const uint8_t*** | SEI 信息 |
| message_length | **int** | SEI 信息的长度 |


**注意**
当公共流中的多路视频流均包含有 SEI 信息时：SEI 不互相冲突时，将通过多次回调分别发送；
SEI 在同一帧有冲突时，则只有一条流中的 SEI 信息被透传并融合到公共流中。


<span id="IRTCVideoEventHandler-onfirstpublicstreamvideoframedecoded"></span>
### onFirstPublicStreamVideoFrameDecoded
```cpp
virtual void bytertc::IRTCVideoEventHandler::onFirstPublicStreamVideoFrameDecoded(
    const char* public_stream_id,
    const VideoFrameInfo& info)
```
公共流的首帧视频解码成功<br>
关于订阅公共流，详见 [startPlayPublicStream](Windows-api.md#IRTCVideo-startplaypublicstream)。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| public_stream_id | **const char*** | 公共流 ID |
| info | **const VideoFrameInfo&** | 视频帧信息。详见 [VideoFrameInfo](Windows-keytype.md#videoframeinfo)。 |


<span id="IRTCVideoEventHandler-onuserstartvideocapture"></span>
### onUserStartVideoCapture
```cpp
virtual void bytertc::IRTCVideoEventHandler::onUserStartVideoCapture(
    const char* room_id,
    const char* user_id)
```
房间内的可见用户调用 [startVideoCapture](Windows-api.md#IRTCVideo-startvideocapture) 开启内部视频采集时，房间内其他用户会收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| room_id | **const char*** | 开启视频采集的远端用户所在的房间 ID |
| user_id | **const char*** | 开启视频采集的远端用户 ID |


<span id="IRTCVideoEventHandler-onuserstopvideocapture"></span>
### onUserStopVideoCapture
```cpp
virtual void bytertc::IRTCVideoEventHandler::onUserStopVideoCapture(
    const char* room_id,
    const char* user_id)
```
房间内的可见用户调用 [stopVideoCapture](Windows-api.md#IRTCVideo-stopvideocapture) 关闭内部视频采集时，房间内其他用户会收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| room_id | **const char*** | ID of the room where the remote video stream stops being published. |
| user_id | **const char*** | 关闭视频采集的远端用户 ID |


<span id="IRTCVideoEventHandler-onlocalvideosizechanged"></span>
### onLocalVideoSizeChanged
```cpp
virtual void bytertc::IRTCVideoEventHandler::onLocalVideoSizeChanged(
    StreamIndex index,
    const VideoFrameInfo& info)
```
本地视频大小或旋转配置发生改变时，收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| index | **StreamIndex** | 流属性。参看 [StreamIndex](Windows-keytype.md#streamindex)。 |
| info | **const VideoFrameInfo&** | 视频帧信息。参看 [VideoFrameInfo](Windows-keytype.md#videoframeinfo)。 |


<span id="IRTCVideoEventHandler-onremotevideosizechanged"></span>
### onRemoteVideoSizeChanged
```cpp
virtual void bytertc::IRTCVideoEventHandler::onRemoteVideoSizeChanged(
    RemoteStreamKey key,
    const VideoFrameInfo& info)
```
远端视频大小或旋转配置发生改变时，房间内订阅此视频流的用户会收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| key | **RemoteStreamKey** | 远端流信息。参看 [RemoteStreamKey](Windows-keytype.md#remotestreamkey)。 |
| info | **const VideoFrameInfo&** | 视频帧信息。参看 [VideoFrameInfo](Windows-keytype.md#videoframeinfo)。 |


<span id="IRTCVideoEventHandler-onfirstlocalvideoframecaptured"></span>
### onFirstLocalVideoFrameCaptured
```cpp
virtual void bytertc::IRTCVideoEventHandler::onFirstLocalVideoFrameCaptured(
    StreamIndex index,
    VideoFrameInfo info)
```
RTC SDK 在本地完成第一帧视频帧或屏幕视频帧采集时，收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| index | **StreamIndex** | 流属性。参看 [StreamIndex](Windows-keytype.md#streamindex)。 |
| info | **VideoFrameInfo** | 视频信息。参看 [VideoFrameInfo](Windows-keytype.md#videoframeinfo)。 |


**注意**
对于采集到的本地视频帧，你可以调用 [setLocalVideoCanvas](Windows-api.md#IRTCVideo-setlocalvideocanvas) 或 [setLocalVideoSink](Windows-api.md#IRTCVideo-setlocalvideosink) 在本地渲染。

<span id="IRTCVideoEventHandler-onfirstremoteaudioframe"></span>
### onFirstRemoteAudioFrame
```cpp
virtual void bytertc::IRTCVideoEventHandler::onFirstRemoteAudioFrame(
    const RemoteStreamKey& key)
```
接收到来自远端某音频流的第一帧时，收到该回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| key | **const RemoteStreamKey&** | 远端音频流信息, 详见 [RemoteStreamKey](Windows-keytype.md#remotestreamkey) |


**注意**
用户刚收到房间内每一路音频流时，都会收到该回调。

<span id="IRTCVideoEventHandler-onremoteaudiostatechanged"></span>
### onRemoteAudioStateChanged
```cpp
virtual void bytertc::IRTCVideoEventHandler::onRemoteAudioStateChanged(
    const RemoteStreamKey& key,
    RemoteAudioState state,
    RemoteAudioStateChangeReason reason)
```
用户订阅来自远端的音频流状态发生改变时，会收到此回调，了解当前的远端音频流状态。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| key | **const RemoteStreamKey&** | 远端流信息, 参看 [RemoteStreamKey](Windows-keytype.md#remotestreamkey) |
| state | **RemoteAudioState** | 远端音频流状态，参看 [RemoteAudioState](Windows-keytype.md#remoteaudiostate) |
| reason | **RemoteAudioStateChangeReason** | 远端音频流状态改变的原因，参看 [RemoteAudioStateChangeReason](Windows-keytype.md#remoteaudiostatechangereason) |


<span id="IRTCVideoEventHandler-onlocalvideostatechanged"></span>
### onLocalVideoStateChanged
```cpp
virtual void bytertc::IRTCVideoEventHandler::onLocalVideoStateChanged(
    StreamIndex index,
    LocalVideoStreamState state,
    LocalVideoStreamError error)
```
本地视频流的状态发生改变时，收到该事件。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| index | **StreamIndex** | 音/视频属性，参看 [StreamIndex](Windows-keytype.md#streamindex) |
| state | **LocalVideoStreamState** | 本地视频流状态，参看 [LocalVideoStreamState](Windows-keytype.md#localvideostreamstate) |
| error | **LocalVideoStreamError** | 本地视频状态改变时的错误码，参看 [LocalVideoStreamError](Windows-errorcode.md#localvideostreamerror) |


<span id="IRTCVideoEventHandler-onremotevideostatechanged"></span>
### onRemoteVideoStateChanged
```cpp
virtual void bytertc::IRTCVideoEventHandler::onRemoteVideoStateChanged(
    RemoteStreamKey key,
    RemoteVideoState state,
    RemoteVideoStateChangeReason reason)
```
远端视频流的状态发生改变时，房间内订阅此流的用户会收到该事件。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| key | **RemoteStreamKey** | 远端视频流的信息，房间、用户 ID、流属性等。参看 [RemoteStreamKey](Windows-keytype.md#remotestreamkey)。 |
| state | **RemoteVideoState** | 远端视频流状态，参看 [RemoteVideoState](Windows-keytype.md#remotevideostate)。 |
| reason | **RemoteVideoStateChangeReason** | 远端视频流状态改变的原因，参看 [RemoteVideoStateChangeReason](Windows-keytype.md#remotevideostatechangereason)。 |


<span id="IRTCVideoEventHandler-onaudioframesendstatechanged"></span>
### onAudioFrameSendStateChanged
```cpp
virtual void bytertc::IRTCVideoEventHandler::onAudioFrameSendStateChanged(
    const char* room_id,
    const RtcUser& user,
    FirstFrameSendState state)
```
音频首帧发送状态改变回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| room_id | **const char*** | 音频发布用户所在的房间 ID |
| user | **const RtcUser&** | 本地用户信息，详见 [RtcUser](Windows-keytype.md#rtcuser) |
| state | **FirstFrameSendState** | 首帧发送状态，详见 [FirstFrameSendState](Windows-keytype.md#firstframesendstate) |


<span id="IRTCVideoEventHandler-onvideoframesendstatechanged"></span>
### onVideoFrameSendStateChanged
```cpp
virtual void bytertc::IRTCVideoEventHandler::onVideoFrameSendStateChanged(
    const char* room_id,
    const RtcUser& user,
    FirstFrameSendState state)
```
视频首帧发送状态改变回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| room_id | **const char*** | 视频发布用户所在的房间 ID |
| user | **const RtcUser&** | 本地用户信息，详见 [RtcUser](Windows-keytype.md#rtcuser) |
| state | **FirstFrameSendState** | 首帧发送状态，详见 [FirstFrameSendState](Windows-keytype.md#firstframesendstate) |


<span id="IRTCVideoEventHandler-onfirstremotevideoframerendered"></span>
### onFirstRemoteVideoFrameRendered
```cpp
virtual void bytertc::IRTCVideoEventHandler::onFirstRemoteVideoFrameRendered(
    const RemoteStreamKey key,
    const VideoFrameInfo& info)
```
SDK 内部渲染成功远端视频流首帧后，收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| key | **const RemoteStreamKey** | 远端流信息。参看 [RemoteStreamKey](Windows-keytype.md#remotestreamkey)。 |
| info | **const VideoFrameInfo&** | 视频帧信息。参看 [VideoFrameInfo](Windows-keytype.md#videoframeinfo)。 |


<span id="IRTCVideoEventHandler-onfirstremotevideoframedecoded"></span>
### onFirstRemoteVideoFrameDecoded
```cpp
virtual void bytertc::IRTCVideoEventHandler::onFirstRemoteVideoFrameDecoded(
    const RemoteStreamKey key,
    const VideoFrameInfo& info)
```
SDK 接收并解码远端视频流首帧后，收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| key | **const RemoteStreamKey** | 远端流信息。参看 [RemoteStreamKey](Windows-keytype.md#remotestreamkey)。 |
| info | **const VideoFrameInfo&** | 视频帧信息。参看 [VideoFrameInfo](Windows-keytype.md#videoframeinfo)。 |


<span id="IRTCVideoEventHandler-onscreenvideoframesendstatechanged"></span>
### onScreenVideoFrameSendStateChanged
```cpp
virtual void bytertc::IRTCVideoEventHandler::onScreenVideoFrameSendStateChanged(
    const char* room_id,
    const RtcUser& user,
    FirstFrameSendState state)
```
屏幕共享流视频首帧发送状态改变回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| room_id | **const char*** | 流的发布房间的 ID |
| user | **const RtcUser&** | 本地用户信息，详见 [RtcUser](Windows-keytype.md#rtcuser) |
| state | **FirstFrameSendState** | 首帧发送状态，详见 [FirstFrameSendState](Windows-keytype.md#firstframesendstate) |


<span id="IRTCVideoEventHandler-onaudioframeplaystatechanged"></span>
### onAudioFramePlayStateChanged
```cpp
virtual void bytertc::IRTCVideoEventHandler::onAudioFramePlayStateChanged(
    const char* room_id,
    const RtcUser& user,
    FirstFramePlayState state)
```
音频首帧播放状态改变回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| room_id | **const char*** | 首帧播放状态发生改变的流所在的房间 ID |
| user | **const RtcUser&** | 远端用户信息，详见 [RtcUser](Windows-keytype.md#rtcuser) |
| state | **FirstFramePlayState** | 首帧播放状态，详见 [FirstFramePlayState](Windows-keytype.md#firstframeplaystate) |


<span id="IRTCVideoEventHandler-onvideoframeplaystatechanged"></span>
### onVideoFramePlayStateChanged
```cpp
virtual void bytertc::IRTCVideoEventHandler::onVideoFramePlayStateChanged(
    const char* room_id,
    const RtcUser& user,
    FirstFramePlayState state)
```
视频首帧播放状态改变回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| room_id | **const char*** | 首帧播放状态发生改变的流所在的房间 ID |
| user | **const RtcUser&** | 远端用户信息，详见 [RtcUser](Windows-keytype.md#rtcuser) |
| state | **FirstFramePlayState** | 首帧播放状态，详见 [FirstFramePlayState](Windows-keytype.md#firstframeplaystate) |


<span id="IRTCVideoEventHandler-onscreenvideoframeplaystatechanged"></span>
### onScreenVideoFramePlayStateChanged
```cpp
virtual void bytertc::IRTCVideoEventHandler::onScreenVideoFramePlayStateChanged(
    const char* room_id,
    const RtcUser& user,
    FirstFramePlayState state)
```
屏幕共享流视频首帧播放状态改变回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| room_id | **const char*** | 首帧播放状态发生改变的流所在的房间 ID |
| user | **const RtcUser&** | 远端用户信息，详见 [RtcUser](Windows-keytype.md#rtcuser) |
| state | **FirstFramePlayState** | 首帧播放状态，详见 [FirstFramePlayState](Windows-keytype.md#firstframeplaystate) |


<span id="IRTCVideoEventHandler-onfirstlocalaudioframe"></span>
### onFirstLocalAudioFrame
```cpp
virtual void bytertc::IRTCVideoEventHandler::onFirstLocalAudioFrame(
    StreamIndex index)
```
发布音频流时，采集到第一帧音频帧，收到该回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| index | **StreamIndex** | 音频流属性, 参看 [StreamIndex](Windows-keytype.md#streamindex) |


**注意**
如果发布音频流时，未开启本地音频采集，SDK 会推送静音帧，也会收到此回调。

<span id="IRTCVideoEventHandler-onpushpublicstreamresult"></span>
### onPushPublicStreamResult
```cpp
virtual void bytertc::IRTCVideoEventHandler::onPushPublicStreamResult(
    const char* room_id,
    const char* public_streamid,
    int errorCode)
```
公共流发布结果回调。<br>
调用 [startPushPublicStream](Windows-api.md#IRTCVideo-startpushpublicstream) 接口发布公共流后，启动结果通过此回调方法通知用户。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| room_id | **const char*** | 公共流的发布房间的 ID |
| public_streamid | **const char*** | 公共流 ID |
| errorCode | **int** | 公共流发布结果状态码。<br/>`200`: 发布成功<br/>`1191`: 推流参数存在异常 <br/>`1192`: 当前状态异常，通常为无法发起任务<br/>`1193`: 服务端错误，不可恢复<br/>`1195`: 服务端调用发布接口返回失败<br/>`1196`: 超时无响应。推流请求发送后 10s 没有收到服务端的结果回调。客户端将每隔 10s 重试，3 次重试失败后停止。 |


<span id="IRTCVideoEventHandler-onfirstpublicstreamaudioframe"></span>
### onFirstPublicStreamAudioFrame
```cpp
virtual void bytertc::IRTCVideoEventHandler::onFirstPublicStreamAudioFrame(
    const char* public_stream_id)
```
公共流的音频首帧解码成功<br>
关于订阅公共流，详见 [startPlayPublicStream](Windows-api.md#IRTCVideo-startplaypublicstream)。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| public_stream_id | **const char*** | 公共流 ID |


<span id="IRTCVideoEventHandler-oncloudproxyconnected"></span>
### onCloudProxyConnected
```cpp
virtual void bytertc::IRTCVideoEventHandler::onCloudProxyConnected(
    int interval)
```
调用 [startCloudProxy](Windows-api.md#IRTCVideo-startcloudproxy) 开启云代理，SDK 首次成功连接云代理服务器时，回调此事件。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| interval | **int** | 从开启云代理到连接成功经过的时间，单位为 ms |


<span id="IRTCVideoEventHandler-onechotestresult"></span>
### onEchoTestResult
```cpp
virtual void bytertc::IRTCVideoEventHandler::onEchoTestResult(
    EchoTestResult result)
```
关于音视频回路测试结果的回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| result | **EchoTestResult** | 测试结果，参看 [EchoTestResult](Windows-keytype.md#echotestresult) |


**注意**
该回调触发的时机包括： + 检测过程中采集设备发生错误时；  

+ 检测成功后；  
+ 非设备原因导致检测过程中未接收到音/视频回放，停止检测后。


# IAudioFrameObserver
```cpp
class bytertc::IAudioFrameObserver
```

音频数据回调观察者


`Defined in : bytertc_audio_frame.h`

## 成员函数

| 返回 | 名称 |
| --- | --- |
| **virtual void** | [onRecordAudioFrame](#IAudioFrameObserver-onrecordaudioframe) |
| **virtual void** | [onPlaybackAudioFrame](#IAudioFrameObserver-onplaybackaudioframe) |
| **virtual void** | [onRemoteUserAudioFrame](#IAudioFrameObserver-onremoteuseraudioframe) |
| **virtual void** | [onMixedAudioFrame](#IAudioFrameObserver-onmixedaudioframe) |
| **virtual void** | [onRecordScreenAudioFrame](#IAudioFrameObserver-onrecordscreenaudioframe) |


## 函数说明
<span id="IAudioFrameObserver-onrecordaudioframe"></span>
### onRecordAudioFrame
```cpp
virtual void bytertc::IAudioFrameObserver::onRecordAudioFrame(
    const IAudioFrame& audio_frame)
```
返回麦克风录制的音频数据

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audio_frame | **const IAudioFrame&** | 音频数据, 详见：[IAudioFrame](Windows-keytype.md#iaudioframe) |


<span id="IAudioFrameObserver-onplaybackaudioframe"></span>
### onPlaybackAudioFrame
```cpp
virtual void bytertc::IAudioFrameObserver::onPlaybackAudioFrame(
    const IAudioFrame& audio_frame)
```
返回订阅的所有远端用户混音后的音频数据

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audio_frame | **const IAudioFrame&** | 音频数据, 详见：[IAudioFrame](Windows-keytype.md#iaudioframe) |


<span id="IAudioFrameObserver-onremoteuseraudioframe"></span>
### onRemoteUserAudioFrame
```cpp
virtual void bytertc::IAudioFrameObserver::onRemoteUserAudioFrame(
    const RemoteStreamKey& stream_info,
    const IAudioFrame& audio_frame)
```
返回远端单个用户的音频数据

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stream_info | **const RemoteStreamKey&** | 远端流信息，参看 [RemoteStreamKey](Windows-keytype.md#remotestreamkey)。 |
| audio_frame | **const IAudioFrame&** | 音频数据, 参看 [IAudioFrame](Windows-keytype.md#iaudioframe)。 |


**注意**
此回调在播放线程调用。不要在此回调中做任何耗时的事情，否则可能会影响整个音频播放链路。

<span id="IAudioFrameObserver-onmixedaudioframe"></span>
### onMixedAudioFrame
```cpp
virtual void bytertc::IAudioFrameObserver::onMixedAudioFrame(
    const IAudioFrame& audio_frame)
```
返回本地麦克风录制和订阅的所有远端用户混音后的音频数据

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audio_frame | **const IAudioFrame&** | 音频数据, 详见：[IAudioFrame](Windows-keytype.md#iaudioframe) |


<span id="IAudioFrameObserver-onrecordscreenaudioframe"></span>
### onRecordScreenAudioFrame
```cpp
virtual void bytertc::IAudioFrameObserver::onRecordScreenAudioFrame(
    const IAudioFrame& audio_frame)
```
返回本地屏幕录制的音频数据

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audio_frame | **const IAudioFrame&** | 音频数据, 详见：[IAudioFrame](Windows-keytype.md#iaudioframe) |


# IAudioFrameProcessor
```cpp
class bytertc::IAudioFrameProcessor
```

自定义音频处理器。


`Defined in : bytertc_audio_frame.h`

## 成员函数

| 返回 | 名称 |
| --- | --- |
| **virtual int** | [onProcessRecordAudioFrame](#IAudioFrameProcessor-onprocessrecordaudioframe) |
| **virtual int** | [onProcessPlayBackAudioFrame](#IAudioFrameProcessor-onprocessplaybackaudioframe) |
| **virtual int** | [onProcessRemoteUserAudioFrame](#IAudioFrameProcessor-onprocessremoteuseraudioframe) |
| **virtual int** | [onProcessScreenAudioFrame](#IAudioFrameProcessor-onprocessscreenaudioframe) |


## 函数说明
<span id="IAudioFrameProcessor-onprocessrecordaudioframe"></span>
### onProcessRecordAudioFrame
```cpp
virtual int bytertc::IAudioFrameProcessor::onProcessRecordAudioFrame(
    IAudioFrame& audioFrame)
```
回调本地采集的音频帧地址，供自定义音频处理。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioFrame | **IAudioFrame&** | 音频帧地址，参看 [IAudioFrame](Windows-keytype.md#iaudioframe) |


**注意**

+ 完成自定义音频处理后，SDK 会对处理后的音频帧进行编码，并传输到远端。
+ 调用 `enableAudioProcessor`，并在参数中选择本地采集的音频时，收到此回调。


<span id="IAudioFrameProcessor-onprocessplaybackaudioframe"></span>
### onProcessPlayBackAudioFrame
```cpp
virtual int bytertc::IAudioFrameProcessor::onProcessPlayBackAudioFrame(
    IAudioFrame& audioFrame)
```
回调远端音频混音的音频帧地址，供自定义音频处理。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioFrame | **IAudioFrame&** | 音频帧地址，参看 [IAudioFrame](Windows-keytype.md#iaudioframe) |


**注意**
调用 `enableAudioProcessor`，并在参数中选择远端音频流的的混音音频时，收到此回调。

<span id="IAudioFrameProcessor-onprocessremoteuseraudioframe"></span>
### onProcessRemoteUserAudioFrame
```cpp
virtual int bytertc::IAudioFrameProcessor::onProcessRemoteUserAudioFrame(
    const RemoteStreamKey& stream_info,
    IAudioFrame& audioFrame)
```
回调单个远端用户的音频帧地址，供自定义音频处理。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stream_info | **const RemoteStreamKey&** | 音频流信息，参看 [RemoteStreamKey](Windows-keytype.md#remotestreamkey) |
| audioFrame | **IAudioFrame&** | 音频帧地址，参看 [IAudioFrame](Windows-keytype.md#iaudioframe) |


**注意**
调用 `enableAudioProcessor`，并在参数中选择各个远端音频流时，收到此回调。

<span id="IAudioFrameProcessor-onprocessscreenaudioframe"></span>
### onProcessScreenAudioFrame
```cpp
virtual int bytertc::IAudioFrameProcessor::onProcessScreenAudioFrame(
    IAudioFrame& audioFrame)
```
屏幕共享的音频帧地址回调。你可根据此回调自定义处理音频。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioFrame | **IAudioFrame&** | 音频帧地址，参看 [IAudioFrame](Windows-keytype.md#iaudioframe)。 |


**注意**
调用 `enableAudioProcessor`，把返回给音频处理器的音频类型设置为屏幕共享音频后，你将收到此回调。

# IEncryptHandler
```cpp
class bytertc::IEncryptHandler
```

加密/解密处理函数


`Defined in : bytertc_common_defines.h`

## 成员函数

| 返回 | 名称 |
| --- | --- |
| **virtual unsigned int** | [onEncryptData](#IEncryptHandler-onencryptdata) |
| **virtual unsigned int** | [onDecryptData](#IEncryptHandler-ondecryptdata) |


## 函数说明
<span id="IEncryptHandler-onencryptdata"></span>
### onEncryptData
```cpp
virtual unsigned int bytertc::IEncryptHandler::onEncryptData(
    const unsigned char* data,
    unsigned int length,
    unsigned char* buf,
    unsigned int buf_len)
```
自定义加密。  <br>
使用设定的自定义加密方式，对编码后传输前的音视频帧数据进行加密。暂不支持对原始音视频帧进行加密。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| data | **const unsigned char*** | 原始音视频帧数据 |
| length | **unsigned int** | 原始音视频帧数据的长度 |
| buf | **unsigned char*** | 可供写入的加密后数据缓冲区 |
| buf_len | **unsigned int** | 可供写入的加密后数据缓冲区大小 |

**返回值**
加密后的数据  

+ ≥ 0：加密后实际写入缓冲区的数据大小  
+ 0：丢弃该帧  


**注意**

+ 使用此接口进行自定义加密前，你必须先设置自定义加密方式，参看 `setCustomizeEncryptHandler`。
+ 使用 [onDecryptData](#IEncryptHandler-ondecryptdata) 对已加密的音视频帧数据进行解密。
+ 返回的数据大小应控制在原始数据的 90% ~ 120% 范围以内，不然将被丢弃。


<span id="IEncryptHandler-ondecryptdata"></span>
### onDecryptData
```cpp
virtual unsigned int bytertc::IEncryptHandler::onDecryptData(
    const unsigned char* data,
    unsigned int length,
    unsigned char* buf,
    unsigned int buf_len)
```
自定义解密。  <br>
对自定义加密后的音视频帧数据进行解密。关于自定义加密，参看 [onEncryptData](#IEncryptHandler-onencryptdata)。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| data | **const unsigned char*** | 原始音视频帧数据 |
| length | **unsigned int** | 原始音视频帧数据的长度 |
| buf | **unsigned char*** | 可供写入的加密后数据缓冲区 |
| buf_len | **unsigned int** | 可供写入的加密后数据缓冲区大小 |

**返回值**
加密后的数据  

+ ≥ 0：加密后实际写入缓冲区的数据大小  
+ 0：丢弃该帧  


**注意**

+ 使用此接口进行解密前，你必须先设定解密方式，参看 `setCustomizeEncryptHandler`。
+ 返回的数据大小应控制在原始数据的 90% ~ 120% 范围以内，不然将被丢弃。


# IKTVEventHandler
```cpp
class bytertc::IKTVEventHandler
```

KTV 事件回调接口。


`Defined in : bytertc_ktv_manager_interface.h`

## 成员函数

| 返回 | 名称 |
| --- | --- |
| **virtual void** | [onMusicListResult](#IKTVEventHandler-onmusiclistresult) |
| **virtual void** | [onSearchMusicResult](#IKTVEventHandler-onsearchmusicresult) |
| **virtual void** | [onHotMusicResult](#IKTVEventHandler-onhotmusicresult) |
| **virtual void** | [onMusicDetailResult](#IKTVEventHandler-onmusicdetailresult) |
| **virtual void** | [onDownloadSuccess](#IKTVEventHandler-ondownloadsuccess) |
| **virtual void** | [onDownloadFailed](#IKTVEventHandler-ondownloadfailed) |
| **virtual void** | [onDownloadMusicProgress](#IKTVEventHandler-ondownloadmusicprogress) |


## 函数说明
<span id="IKTVEventHandler-onmusiclistresult"></span>
### onMusicListResult
```cpp
virtual void bytertc::IKTVEventHandler::onMusicListResult(
    KTVErrorCode error_code,
    int total_musics_size,
    MusicInfo *music_infos,
    int music_count)
```
歌曲列表回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| error_code | **KTVErrorCode** | 错误码，成功时返回 0，其余值参看 [KTVErrorCode](Windows-keytype.md#ktverrorcode)。 |
| total_musics_size | **int** | 数据条目总数。 |
| music_infos | **MusicInfo*** | 歌曲数据数组，参看 [MusicInfo](Windows-keytype.md#musicinfo)。 |
| music_count | **int** | 当前查询的数据条目数。 |


<span id="IKTVEventHandler-onsearchmusicresult"></span>
### onSearchMusicResult
```cpp
virtual void bytertc::IKTVEventHandler::onSearchMusicResult(
    KTVErrorCode error_code,
    int total_musics_size,
    MusicInfo* music_infos,
    int music_count)
```
搜索歌曲结果回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| error_code | **KTVErrorCode** | 错误码，成功时返回 0，其余值参看 [KTVErrorCode](Windows-keytype.md#ktverrorcode)。 |
| total_musics_size | **int** | 数据条目总数。 |
| music_infos | **MusicInfo*** | 歌曲数据数组，参看 [MusicInfo](Windows-keytype.md#musicinfo)。 |
| music_count | **int** | 当前查询的数据条目数。 |


<span id="IKTVEventHandler-onhotmusicresult"></span>
### onHotMusicResult
```cpp
virtual void bytertc::IKTVEventHandler::onHotMusicResult(
    KTVErrorCode error_code,
    HotMusicInfo* hot_infos,
    int hot_count)
```
热榜歌曲结果回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| error_code | **KTVErrorCode** | 错误码，成功时返回 0，其余值参看 [KTVErrorCode](Windows-keytype.md#ktverrorcode)。 |
| hot_infos | **HotMusicInfo*** | 热榜歌曲数据数组，参看 [HotMusicInfo](Windows-keytype.md#hotmusicinfo)。 |
| hot_count | **int** | 当前查询的热榜歌曲数据条目数。 |


<span id="IKTVEventHandler-onmusicdetailresult"></span>
### onMusicDetailResult
```cpp
virtual void bytertc::IKTVEventHandler::onMusicDetailResult(
    KTVErrorCode error_code,
    MusicInfo* music_info)
```
歌曲详细信息回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| error_code | **KTVErrorCode** | 错误码，成功时返回 0，其余值参看 [KTVErrorCode](Windows-keytype.md#ktverrorcode)。 |
| music_info | **MusicInfo*** | 歌曲数据，参看 [MusicInfo](Windows-keytype.md#musicinfo)。 |


<span id="IKTVEventHandler-ondownloadsuccess"></span>
### onDownloadSuccess
```cpp
virtual void bytertc::IKTVEventHandler::onDownloadSuccess(
    int download_id,
    DownloadResult* download_info)
```
下载成功回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| download_id | **int** | 下载任务 ID。 |
| download_info | **DownloadResult*** | 下载信息，参看 [DownloadResult](Windows-keytype.md#downloadresult)。 |


<span id="IKTVEventHandler-ondownloadfailed"></span>
### onDownloadFailed
```cpp
virtual void bytertc::IKTVEventHandler::onDownloadFailed(
    KTVErrorCode error_code,
    int download_id)
```
下载失败回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| error_code | **KTVErrorCode** | 错误码，参看 [KTVErrorCode](Windows-keytype.md#ktverrorcode)。 |
| download_id | **int** | 下载任务 ID。 |


<span id="IKTVEventHandler-ondownloadmusicprogress"></span>
### onDownloadMusicProgress
```cpp
virtual void bytertc::IKTVEventHandler::onDownloadMusicProgress(
    int download_id,
    int download_percentage)
```
歌曲文件下载进度回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| download_id | **int** | 下载任务 ID。 |
| download_percentage | **int** | 下载进度百分比，取值范围 [0,100]。 |


# IKTVPlayerEventHandler
```cpp
class bytertc::IKTVPlayerEventHandler
```

KTV 播放器回调接口。


`Defined in : bytertc_ktv_manager_interface.h`

## 成员函数

| 返回 | 名称 |
| --- | --- |
| **virtual void** | [onPlayProgress](#IKTVPlayerEventHandler-onplayprogress) |
| **virtual void** | [onPlayStateChange](#IKTVPlayerEventHandler-onplaystatechange) |


## 函数说明
<span id="IKTVPlayerEventHandler-onplayprogress"></span>
### onPlayProgress
```cpp
virtual void bytertc::IKTVPlayerEventHandler::onPlayProgress(
    const char *music_id,
    int64_t progress)
```
音乐播放进度回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| music_id | **const char*** | 音乐 ID。 |
| progress | **int64_t** | 音乐播放进度，单位为毫秒。 |


<span id="IKTVPlayerEventHandler-onplaystatechange"></span>
### onPlayStateChange
```cpp
virtual void bytertc::IKTVPlayerEventHandler::onPlayStateChange(
    bytertc::KTVPlayerErrorCode error_code,
    const char* music_id,
    PlayState play_state)
```
音乐播放状态改变回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| error_code | **bytertc::KTVPlayerErrorCode** | 错误码，参看 [KTVPlayerErrorCode](Windows-keytype.md#ktvplayererrorcode)。 |
| music_id | **const char*** | 音乐 ID。 |
| play_state | **PlayState** | 音乐播放状态，参看 [PlayState](Windows-keytype.md#playstate)。 |


**注意**
此回调被触发的时机汇总如下：

+ 调用 [playMusic](Windows-api.md#IKTVPlayer-playmusic) 成功后，会触发 playState 值为 PlayStatePlaying 的回调；否则会触发 playState 值为 PlayStateFailed 的回调。
+ 使用相同的音乐 ID 重复调用 [playMusic](Windows-api.md#IKTVPlayer-playmusic) 后，后一次播放会覆盖前一次，且会触发 playState 值为 PlayStatePlaying 的回调，表示后一次音乐播放已开始。
+ 调用 [pauseMusic](Windows-api.md#IKTVPlayer-pausemusic) 方法暂停播放成功后，会触发 playState 值为 PlayStatePaused 的回调；否则触发 playState 值为 PlayStateFailed 的回调。
+ 调用 [resumeMusic](Windows-api.md#IKTVPlayer-resumemusic) 方法恢复播放成功后，会触发 playState 值为 PlayStatePlaying 的回调；否则触发 playState 值为 PlayStateFailed 的回调。
+ 调用 [stopMusic](Windows-api.md#IKTVPlayer-stopmusic) 方法停止播放成功后，会触发 playState 值为 PlayStateStoped 的回调；否则触发 playState 值为 PlayStateFailed 的回调。
+ 音乐播放结束会触发 playState 值为 PlayStateFinished 的回调。


# IRangeAudioObserver
```cpp
class bytertc::IRangeAudioObserver
```

范围语音衰减系数监测器


`Defined in : bytertc_range_audio_interface.h`

## 成员函数

| 返回 | 名称 |
| --- | --- |
| **virtual void** | [onRangeAudioInfo](#IRangeAudioObserver-onrangeaudioinfo) |


## 函数说明
<span id="IRangeAudioObserver-onrangeaudioinfo"></span>
### onRangeAudioInfo
```cpp
virtual void bytertc::IRangeAudioObserver::onRangeAudioInfo(
    const RangeAudioInfo* range_audio_info,
    int len)
```
关于当前范围语音衰减系数的回调。  <br>
手动订阅的场景下，房间内任一用户调用 [updatePosition](Windows-api.md#IRangeAudio-updateposition) 更新自身位置或调用 [updateReceiveRange](Windows-api.md#IRangeAudio-updatereceiverange) 更新语音接收范围时，该用户与房间内其他用户的相对距离都会发生改变，据此计算的衰减系数也会发生改变，并通过该回调通知用户。 <br>
你可以通过关注该回调中包含的远端用户的衰减系数决定是否订阅该远端用户的流。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| range_audio_info | **const RangeAudioInfo*** | 包含范围语音流信息的数组，参看 [RangeAudioInfo](Windows-keytype.md#rangeaudioinfo) |
| len | **int** | 范围语音流信息数组长度 |


**注意**
更新自身位置或语音接收范围后，并不会马上触发该回调。SDK 会每 500 ms 计算一次衰减系数，并且只在计算结果与上次不同，或结果相同但是距离上次计算已超过 3 秒的时候推送回调。

# ISingScoringEventHandler
```cpp
class bytertc::ISingScoringEventHandler
```

K 歌评分事件回调类。


`Defined in : bytertc_sing_scoring_interface.h`

## 成员函数

| 返回 | 名称 |
| --- | --- |
| **virtual void** | [onCurrentScoringInfo](#ISingScoringEventHandler-oncurrentscoringinfo) |


## 函数说明
<span id="ISingScoringEventHandler-oncurrentscoringinfo"></span>
### onCurrentScoringInfo
```cpp
virtual void bytertc::ISingScoringEventHandler::onCurrentScoringInfo(
    const SingScoringRealtimeInfo& info)
```
实时评分信息回调。调用 [startSingScoring](Windows-api.md#ISingScoringManager-startsingscoring) 后，会收到该回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| info | **const SingScoringRealtimeInfo&** | 实时评分信息。 |


# ITranscoderObserver
```cpp
class bytertc::ITranscoderObserver
```

推流 Observer


`Defined in : bytertc_transcoder_interface.h`

## 成员函数

| 返回 | 名称 |
| --- | --- |
| **virtual void** | [onStreamMixingEvent](#ITranscoderObserver-onstreammixingevent) |
| **virtual void** | [onStreamMixingVideoFrame](#ITranscoderObserver-onstreammixingvideoframe) |
| **virtual void** | [onStreamMixingAudioFrame](#ITranscoderObserver-onstreammixingaudioframe) |
| **virtual void** | [onStreamMixingDataFrame](#ITranscoderObserver-onstreammixingdataframe) |


## 函数说明
<span id="ITranscoderObserver-onstreammixingevent"></span>
### onStreamMixingEvent
```cpp
virtual void bytertc::ITranscoderObserver::onStreamMixingEvent(
    StreamMixingEvent event,
    const char* task_id,
    StreamMixingErrorCode error,
    StreamMixingType mix_type)
```
转推直播状态回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| event | **StreamMixingEvent** | 转推直播任务状态，参看 [StreamMixingEvent](Windows-keytype.md#streammixingevent) |
| task_id | **const char*** | 转推直播任务 ID |
| error | **StreamMixingErrorCode** | 转推直播错误码，参看 [TransCodingError](Windows-keytype.md#transcodingerror)。 |
| mix_type | **StreamMixingType** | 转推直播类型，参看 [StreamMixingType](Windows-keytype.md#streammixingtype) |


<span id="ITranscoderObserver-onstreammixingvideoframe"></span>
### onStreamMixingVideoFrame
```cpp
virtual void bytertc::ITranscoderObserver::onStreamMixingVideoFrame(
    const char* task_id,
    IVideoFrame* video_frame)
```
合流视频回调，运行在视频回调线程

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| task_id | **const char*** | 合流任务 ID |
| video_frame | **IVideoFrame*** | 视频帧，参看 [IVideoFrame](Windows-keytype.md#ivideoframe)。 |


**注意**
收到该回调的周期与视频的帧间隔一致。

<span id="ITranscoderObserver-onstreammixingaudioframe"></span>
### onStreamMixingAudioFrame
```cpp
virtual void bytertc::ITranscoderObserver::onStreamMixingAudioFrame(
    const char* task_id,
    IAudioFrame* audio_frame)
```
合流音频回调，运行在音频回调线程

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| task_id | **const char*** | 转推直播任务 ID |
| audio_frame | **IAudioFrame*** | 音频帧，参看 [IAudioFrame](Windows-keytype.md#iaudioframe)。 |


**注意**
收到该回调的周期为每 10 毫秒一次，并且每次的音频数据量为 10 毫秒数据量。

<span id="ITranscoderObserver-onstreammixingdataframe"></span>
### onStreamMixingDataFrame
```cpp
virtual void bytertc::ITranscoderObserver::onStreamMixingDataFrame(
    const char* task_id,
    IDataFrame* data_frame)
```
视频 SEI 帧回调，运行在视频回调线程

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| task_id | **const char*** | 转推直播任务 ID |
| data_frame | **IDataFrame*** | SEI 数据 |


# IPushSingleStreamToCDNObserver
```cpp
class bytertc::IPushSingleStreamToCDNObserver
```

单流转推直播观察者。  <br>


`Defined in : bytertc_transcoder_interface.h`

## 成员函数

| 返回 | 名称 |
| --- | --- |
| **virtual void** | [onStreamPushEvent](#IPushSingleStreamToCDNObserver-onstreampushevent) |


## 函数说明
<span id="IPushSingleStreamToCDNObserver-onstreampushevent"></span>
### onStreamPushEvent
```cpp
virtual void bytertc::IPushSingleStreamToCDNObserver::onStreamPushEvent(
    SingleStreamPushEvent event,
    const char *task_id,
    int error)
```
单流转推直播状态回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| event | **SingleStreamPushEvent** | 任务状态, 参看 [SingleStreamPushEvent](Windows-errorcode.md#singlestreampushevent) |
| task_id | **const char*** | 任务 ID |
| error | **int** | 错误码，参看 [TransCodingError](Windows-keytype.md#transcodingerror) |


# IExternalVideoEncoderEventHandler
```cpp
class bytertc::IExternalVideoEncoderEventHandler
```

自定义编码帧回调类


`Defined in : bytertc_video_defines.h`

## 成员函数

| 返回 | 名称 |
| --- | --- |
| **virtual void** | [onStart](#IExternalVideoEncoderEventHandler-onstart) |
| **virtual void** | [onStop](#IExternalVideoEncoderEventHandler-onstop) |
| **virtual void** | [onRateUpdate](#IExternalVideoEncoderEventHandler-onrateupdate) |
| **virtual void** | [onRequestKeyFrame](#IExternalVideoEncoderEventHandler-onrequestkeyframe) |


## 函数说明
<span id="IExternalVideoEncoderEventHandler-onstart"></span>
### onStart
```cpp
virtual void bytertc::IExternalVideoEncoderEventHandler::onStart(
    StreamIndex index)
```
提示自定义编码帧可以开始推送的回调。  <br>
收到该回调后，你即可调用 [pushExternalEncodedVideoFrame](Windows-api.md#IRTCVideo-pushexternalencodedvideoframe) 向 SDK 推送自定义编码视频帧

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| index | **StreamIndex** | 可以推送的编码流的属性，参看 [StreamIndex](Windows-keytype.md#streamindex) |


<span id="IExternalVideoEncoderEventHandler-onstop"></span>
### onStop
```cpp
virtual void bytertc::IExternalVideoEncoderEventHandler::onStop(
    StreamIndex index)
```
当收到该回调时，你需停止向 SDK 推送自定义编码视频帧

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| index | **StreamIndex** | 需停止推送的编码流的属性，参看 [StreamIndex](Windows-keytype.md#streamindex) |


<span id="IExternalVideoEncoderEventHandler-onrateupdate"></span>
### onRateUpdate
```cpp
virtual void bytertc::IExternalVideoEncoderEventHandler::onRateUpdate(
    StreamIndex index,
    int32_t video_index,
    VideoRateInfo info)
```
当自定义编码流的帧率或码率发生变化时，触发该回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| index | **StreamIndex** | 发生变化的编码流的属性，参看 [StreamIndex](Windows-keytype.md#streamindex) |
| video_index | **int32_t** | 对应编码流的下标 |
| info | **VideoRateInfo** | 变化后的编码流信息，参看 [VideoRateInfo](Windows-keytype.md#videorateinfo) |


<span id="IExternalVideoEncoderEventHandler-onrequestkeyframe"></span>
### onRequestKeyFrame
```cpp
virtual void bytertc::IExternalVideoEncoderEventHandler::onRequestKeyFrame(
    StreamIndex index,
    int32_t video_index)
```
提示流发布端需重新生成关键帧的回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| index | **StreamIndex** | 远端编码流的属性，参看 [StreamIndex](Windows-keytype.md#streamindex) |
| video_index | **int32_t** | 对应编码流的下标 |


# ILocalEncodedVideoFrameObserver
```cpp
class bytertc::ILocalEncodedVideoFrameObserver
```

本地视频帧监测器


`Defined in : bytertc_video_defines.h`

## 成员函数

| 返回 | 名称 |
| --- | --- |
| **virtual void** | [onLocalEncodedVideoFrame](#ILocalEncodedVideoFrameObserver-onlocalencodedvideoframe) |


## 函数说明
<span id="ILocalEncodedVideoFrameObserver-onlocalencodedvideoframe"></span>
### onLocalEncodedVideoFrame
```cpp
virtual void bytertc::ILocalEncodedVideoFrameObserver::onLocalEncodedVideoFrame(
    StreamIndex type,
    const IEncodedVideoFrame& video_stream)
```
调用 [registerLocalEncodedVideoFrameObserver](Windows-api.md#IRTCVideo-registerlocalencodedvideoframeobserver) 后，SDK 每次使用内部采集，采集到一帧视频帧，或收到一帧外部视频帧时，都会回调该事件。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| type | **StreamIndex** | 本地视频帧类型，参看 [StreamIndex](Windows-keytype.md#streamindex) |
| video_stream | **const IEncodedVideoFrame&** | 本地视频帧信息，参看 [IEncodedVideoFrame](Windows-keytype.md#iencodedvideoframe) |


# IRemoteEncodedVideoFrameObserver
```cpp
class bytertc::IRemoteEncodedVideoFrameObserver
```

远端编码后视频数据监测器


`Defined in : bytertc_video_defines.h`

## 成员函数

| 返回 | 名称 |
| --- | --- |
| **virtual void** | [onRemoteEncodedVideoFrame](#IRemoteEncodedVideoFrameObserver-onremoteencodedvideoframe) |


## 函数说明
<span id="IRemoteEncodedVideoFrameObserver-onremoteencodedvideoframe"></span>
### onRemoteEncodedVideoFrame
```cpp
virtual void bytertc::IRemoteEncodedVideoFrameObserver::onRemoteEncodedVideoFrame(
    const RemoteStreamKey& stream_info,
    const IEncodedVideoFrame& video_stream)
```
调用 [registerRemoteEncodedVideoFrameObserver](Windows-api.md#IRTCVideo-registerremoteencodedvideoframeobserver) 后，SDK 监测到远端编码后视频数据时，触发该回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stream_info | **const RemoteStreamKey&** | 收到的远端流信息，参看 [RemoteStreamKey](Windows-keytype.md#remotestreamkey) |
| video_stream | **const IEncodedVideoFrame&** | 收到的远端视频帧信息，参看 [IEncodedVideoFrame](Windows-keytype.md#iencodedvideoframe) |


# IVideoFrameObserver
```cpp
class bytertc::IVideoFrameObserver
```

视频数据回调观察者


`Defined in : bytertc_video_defines.h`

## 成员函数

| 返回 | 名称 |
| --- | --- |
| **virtual bool** | [onLocalScreenFrame](#IVideoFrameObserver-onlocalscreenframe) |
| **virtual bool** | [onLocalVideoFrame](#IVideoFrameObserver-onlocalvideoframe) |
| **virtual bool** | [onRemoteScreenFrame](#IVideoFrameObserver-onremotescreenframe) |
| **virtual bool** | [onRemoteVideoFrame](#IVideoFrameObserver-onremotevideoframe) |


## 函数说明
<span id="IVideoFrameObserver-onlocalscreenframe"></span>
### onLocalScreenFrame
```cpp
virtual bool bytertc::IVideoFrameObserver::onLocalScreenFrame(
    IVideoFrame* videoFrame)
```
获取采集成功的本地屏幕视频帧，用于自定义处理或渲染。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| videoFrame | **IVideoFrame*** | 视频数据，参看 [IVideoFrame](Windows-keytype.md#ivideoframe)。 |


<span id="IVideoFrameObserver-onlocalvideoframe"></span>
### onLocalVideoFrame
```cpp
virtual bool bytertc::IVideoFrameObserver::onLocalVideoFrame(
    IVideoFrame* videoFrame)
```
获取采集成功的本地摄像头流视频帧，用于自定义处理或渲染。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| videoFrame | **IVideoFrame*** | 视频数据，参看 [IVideoFrame](Windows-keytype.md#ivideoframe)。 |


<span id="IVideoFrameObserver-onremotescreenframe"></span>
### onRemoteScreenFrame
```cpp
virtual bool bytertc::IVideoFrameObserver::onRemoteScreenFrame(
    const char* roomid,
    const char* uid,
    IVideoFrame* videoFrame)
```
获取采集成功的远端屏幕视频帧，用于自定义处理或渲染。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| roomid | **const char*** | 房间 ID。 |
| uid | **const char*** | 远端用户 ID。 |
| videoFrame | **IVideoFrame*** | 视频数据，参看 [IVideoFrame](Windows-keytype.md#ivideoframe)。 |


<span id="IVideoFrameObserver-onremotevideoframe"></span>
### onRemoteVideoFrame
```cpp
virtual bool bytertc::IVideoFrameObserver::onRemoteVideoFrame(
    const char* roomid,
    const char* uid,
    IVideoFrame* videoFrame)
```
获取采集成功的远端摄像头流视频帧，用于自定义处理或渲染。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| roomid | **const char*** | 房间 ID。 |
| uid | **const char*** | 远端用户 ID。 |
| videoFrame | **IVideoFrame*** | 视频数据，参看 [IVideoFrame](Windows-keytype.md#ivideoframe)。 |


**注意**
不同的平台上（macOS, Windows, Linux）上获取的视频帧的 pixelFormat 可能不同。

# ISnapshotResultCallback
```cpp
class bytertc::ISnapshotResultCallback
```

截图的回调。


`Defined in : bytertc_video_defines.h`

## 成员函数

| 返回 | 名称 |
| --- | --- |
| **virtual** | [~ISnapshotResultCallback](#ISnapshotResultCallback-~isnapshotresultcallback) |
| **virtual void** | [onTakeLocalSnapshotResult](#ISnapshotResultCallback-ontakelocalsnapshotresult) |
| **virtual void** | [onTakeRemoteSnapshotResult](#ISnapshotResultCallback-ontakeremotesnapshotresult) |


## 函数说明
<span id="ISnapshotResultCallback-~isnapshotresultcallback"></span>
### ~ISnapshotResultCallback
```cpp
virtual bytertc::ISnapshotResultCallback::~ISnapshotResultCallback()
```

<span id="ISnapshotResultCallback-ontakelocalsnapshotresult"></span>
### onTakeLocalSnapshotResult
```cpp
virtual void bytertc::ISnapshotResultCallback::onTakeLocalSnapshotResult(
    long taskId,
    StreamIndex streamIndex,
    IVideoFrame* image,
    int errorCode)
```
调用 [takeLocalSnapshot](Windows-api.md#IRTCVideo-takelocalsnapshot) 截取视频画面时，收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| taskId | **long** | 本地截图任务的编号。和 [takeLocalSnapshot](Windows-api.md#IRTCVideo-takelocalsnapshot) 的返回值一致。 |
| streamIndex | **StreamIndex** | 截图的视频流的属性，参看 [StreamIndex](Windows-keytype.md#streamindex)。 |
| image | **IVideoFrame*** | 截图。你可以保存为文件，或对其进行二次处理。截图失败时，为空。 |
| errorCode | **int** | 截图错误码：<br/>• 0: 成功 <br/>• -1: 截图错误。生成图片数据失败或 RGBA 编码失败 <br/>• -2: 截图错误。流无效。 |


<span id="ISnapshotResultCallback-ontakeremotesnapshotresult"></span>
### onTakeRemoteSnapshotResult
```cpp
virtual void bytertc::ISnapshotResultCallback::onTakeRemoteSnapshotResult(
    long taskId,
    RemoteStreamKey streamKey,
    IVideoFrame* image,
    int errorCode)
```
调用 [takeRemoteSnapshot](Windows-api.md#IRTCVideo-takeremotesnapshot) 截取视频画面时，收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| taskId | **long** | 远端截图任务的编号。和 [takeRemoteSnapshot](Windows-api.md#IRTCVideo-takeremotesnapshot) 的返回值一致。 |
| streamKey | **RemoteStreamKey** | 截图的视频流，参看 [RemoteStreamKey](Windows-keytype.md#remotestreamkey)。 |
| image | **IVideoFrame*** | 截图。你可以保存为文件，或对其进行二次处理。截图失败时，为空。 |
| errorCode | **int** | 截图错误码：<br/>• 0: 成功 <br/>• -1: 截图错误。生成图片数据失败或 RGBA 编码失败 <br/>• -2: 截图错误。流无效。 |


# IFaceDetectionObserver
```cpp
class bytertc::IFaceDetectionObserver
```

人脸检测结果回调观察者


`Defined in : bytertc_video_effect_interface.h`

## 成员函数

| 返回 | 名称 |
| --- | --- |
| **virtual void** | [onFaceDetectResult](#IFaceDetectionObserver-onfacedetectresult) |


## 函数说明
<span id="IFaceDetectionObserver-onfacedetectresult"></span>
### onFaceDetectResult
```cpp
virtual void bytertc::IFaceDetectionObserver::onFaceDetectResult(
    const FaceDetectResult& result)
```
特效 SDK 进行人脸检测结果的回调。 <br>
调用 [registerFaceDetectionObserver](Windows-api.md#IVideoEffect-registerfacedetectionobserver) 注册了 [IFaceDetectionObserver](#ifacedetectionobserver)，并使用 RTC SDK 中包含的特效 SDK 进行视频特效处理时，你会收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| result | **const FaceDetectResult&** | 人脸检测结果, 参看 [FaceDetectResult](Windows-keytype.md#facedetectresult)。 |


# IStreamingRTCEventHandler
```cpp
class streamingrtc::IStreamingRTCEventHandler
```

串流引擎事件回调接口。  <br>
调用 [CreateStreamingRTCEngine](Windows-api.md#createstreamingrtcengine) 创建 [IStreamingRTCEngine](Windows-api.md#istreamingrtcengine) 实例时，传入该回调实例。


`Defined in : streaming_rtc_engine_event_handler.h`

## 成员函数

| 返回 | 名称 |
| --- | --- |
| **virtual void** | [OnLogReport](#IStreamingRTCEventHandler-onlogreport) |
| **virtual void** | [OnWarning](#IStreamingRTCEventHandler-onwarning) |
| **virtual void** | [OnError](#IStreamingRTCEventHandler-onerror) |
| **virtual void** | [OnP2PConnectionStateChanged](#IStreamingRTCEventHandler-onp2pconnectionstatechanged) |
| **virtual void** | [OnP2PConnectionStats](#IStreamingRTCEventHandler-onp2pconnectionstats) |
| **virtual void** | [OnP2PLocalStreamStats](#IStreamingRTCEventHandler-onp2plocalstreamstats) |
| **virtual void** | [OnP2PRemoteStreamStats](#IStreamingRTCEventHandler-onp2premotestreamstats) |
| **virtual void** | [OnP2PMessageSendResult](#IStreamingRTCEventHandler-onp2pmessagesendresult) |
| **virtual void** | [OnP2PMessageReceived](#IStreamingRTCEventHandler-onp2pmessagereceived) |
| **virtual void** | [OnP2PBinaryMessageReceived](#IStreamingRTCEventHandler-onp2pbinarymessagereceived) |
| **virtual bool** | [OnP2PRemoteVideoFrame](#IStreamingRTCEventHandler-onp2premotevideoframe) |
| **virtual bool** | [OnP2PRemoteEncodedVideoFrame](#IStreamingRTCEventHandler-onp2premoteencodedvideoframe) |
| **virtual void** | [OnP2PLocalExternalEncoderStart](#IStreamingRTCEventHandler-onp2plocalexternalencoderstart) |
| **virtual void** | [OnP2PLocalExternalEncoderStop](#IStreamingRTCEventHandler-onp2plocalexternalencoderstop) |
| **virtual void** | [OnP2PSuggestLocalExternalEncoderRateUpdate](#IStreamingRTCEventHandler-onp2psuggestlocalexternalencoderrateupdate) |
| **virtual void** | [OnP2PRequestLocalExternalEncoderKeyFrame](#IStreamingRTCEventHandler-onp2prequestlocalexternalencoderkeyframe) |


## 函数说明
<span id="IStreamingRTCEventHandler-onlogreport"></span>
### OnLogReport
```cpp
virtual void streamingrtc::IStreamingRTCEventHandler::OnLogReport(
    const char* log_type,
    const char* log_content)
```
端监控日志回调。当产生一个端监控事件时触发该回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| log_type | **const char*** | 事件类型。目前类型固定为 `live_webrtc_monitor_log`。 |
| log_content | **const char*** | 端监控日志内容。 |


<span id="IStreamingRTCEventHandler-onwarning"></span>
### OnWarning
```cpp
virtual void streamingrtc::IStreamingRTCEventHandler::OnWarning(
    int code)
```
当内部发生警告事件时触发该回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| code | **int** | 警告标识码，详见:[WarningCode](Windows-errorcode.md#warningcode) |


<span id="IStreamingRTCEventHandler-onerror"></span>
### OnError
```cpp
virtual void streamingrtc::IStreamingRTCEventHandler::OnError(
    int code)
```
当 SDK 内部发生不可逆转错误时触发该回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| code | **int** | 错误标识码，参看 [ErrorCode](Windows-errorcode.md#errorcode) |


<span id="IStreamingRTCEventHandler-onp2pconnectionstatechanged"></span>
### OnP2PConnectionStateChanged
```cpp
virtual void streamingrtc::IStreamingRTCEventHandler::OnP2PConnectionStateChanged(
    ConnectionState state)
```
串流引擎连接状态改变回调。连接状态改变时触发。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| state | **ConnectionState** | 当前 SDK 与对端的连接状态，详见 [ConnectionState](Windows-keytype.md#connectionstate) |


<span id="IStreamingRTCEventHandler-onp2pconnectionstats"></span>
### OnP2PConnectionStats
```cpp
virtual void streamingrtc::IStreamingRTCEventHandler::OnP2PConnectionStats(
    const ConnectionStats& stats)
```
P2P 通话统计信息回调。   <br>
串流引擎启动后，每 2s 收到一次本回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stats | **const ConnectionStats&** | 当前 StreamingRtcEngine 统计数据，详见 [ConnectionStats](Windows-keytype.md#connectionstats) |


<span id="IStreamingRTCEventHandler-onp2plocalstreamstats"></span>
### OnP2PLocalStreamStats
```cpp
virtual void streamingrtc::IStreamingRTCEventHandler::OnP2PLocalStreamStats(
    const LocalStreamStats& stats)
```
串流引擎启动后，每隔 2s 收到此回调，了解本端发布的流在此周期内的网络质量信息。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stats | **const LocalStreamStats&** | 当前 StreamingRtcEngine 统计数据，详见 [LocalStreamStats](Windows-keytype.md#localstreamstats) |


<span id="IStreamingRTCEventHandler-onp2premotestreamstats"></span>
### OnP2PRemoteStreamStats
```cpp
virtual void streamingrtc::IStreamingRTCEventHandler::OnP2PRemoteStreamStats(
    const RemoteStreamStats& stats)
```
每隔 2s 收到此回调，了解远端用户发布的流在此周期内的网络质量信息。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stats | **const RemoteStreamStats&** | 当前 StreamingRtcEngine 统计数据，详见 [RemoteStreamStats](Windows-keytype.md#remotestreamstats) |


<span id="IStreamingRTCEventHandler-onp2pmessagesendresult"></span>
### OnP2PMessageSendResult
```cpp
virtual void streamingrtc::IStreamingRTCEventHandler::OnP2PMessageSendResult(
    int64_t msg_id,
    int error)
```
调用 [SendP2PMessage](Windows-api.md#IStreamingRTCEngine-sendp2pmessage) 或 [SendP2PBinaryMessage](Windows-api.md#IStreamingRTCEngine-sendp2pbinarymessage) ，向远端用户发送文本或二进制消息后，消息发送方会收到本次发送的结果回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| msg_id | **int64_t** | 本条消息的 ID。 |
| error | **int** | 错误码<br/>0: 成功<br/>102: 失败，未建立连接 |


<span id="IStreamingRTCEventHandler-onp2pmessagereceived"></span>
### OnP2PMessageReceived
```cpp
virtual void streamingrtc::IStreamingRTCEventHandler::OnP2PMessageReceived(
    const char* message)
```
收到远端用户发来的文本消息时，会收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| message | **const char*** | 收到的文本消息内容。 |


**注意**
关于发送点对点消息，参看 [SendP2PMessage](Windows-api.md#IStreamingRTCEngine-sendp2pmessage) 。

<span id="IStreamingRTCEventHandler-onp2pbinarymessagereceived"></span>
### OnP2PBinaryMessageReceived
```cpp
virtual void streamingrtc::IStreamingRTCEventHandler::OnP2PBinaryMessageReceived(
    const uint8_t* message,
    int size)
```
收到远端用户发来的二进制消息时，会收到此回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| message | **const uint8_t*** | 收到的二进制消息内容。 |
| size | **int** | 收到的二进制消息内容的大小，单位为 byte. |


**注意**
关于发送二进制点对点消息，参看 [SendP2PBinaryMessage](Windows-api.md#IStreamingRTCEngine-sendp2pbinarymessage) 。

<span id="IStreamingRTCEventHandler-onp2premotevideoframe"></span>
### OnP2PRemoteVideoFrame
```cpp
virtual bool streamingrtc::IStreamingRTCEventHandler::OnP2PRemoteVideoFrame(
    IVideoFrame* video_frame,
    streamingrtc::StreamIndex stream_index)
```
获取远端用户发送的视频帧。 <br>
关于推送视频帧，参看 [PushVideoFrame](Windows-api.md#IStreamingRTCEngine-pushvideoframe) <br>
关于推送已编码的视频流，参看 [PushEncodedVideoFrame](Windows-api.md#IStreamingRTCEngine-pushencodedvideoframe) <br>
关于编码设置，参看 [SetVideoDecoderConfig](Windows-api.md#IStreamingRTCEngine-setvideodecoderconfig) <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| video_frame | **IVideoFrame*** | 视频数据，参看 [IVideoFrame](Windows-keytype.md#ivideoframe) |
| stream_index | **streamingrtc::StreamIndex** | 视频流序号 参看 [StreamIndex](Windows-keytype.md#streamindex) |

**返回值**

+ `True`：成功 
+ `False`：失败


<span id="IStreamingRTCEventHandler-onp2premoteencodedvideoframe"></span>
### OnP2PRemoteEncodedVideoFrame
```cpp
virtual bool streamingrtc::IStreamingRTCEventHandler::OnP2PRemoteEncodedVideoFrame(
    const IEncodedVideoFrame& encoded_video_frame,
    streamingrtc::StreamIndex stream_index)
```
获取远端用户解码前的视频数据。获取数据后传入自定义解码器进行解码。 <br>
关于推送视频帧，参看 [PushVideoFrame](Windows-api.md#IStreamingRTCEngine-pushvideoframe) <br>
关于推送已编码的视频流，参看 [PushEncodedVideoFrame](Windows-api.md#IStreamingRTCEngine-pushencodedvideoframe) <br>
关于编码设置，参看 [SetVideoDecoderConfig](Windows-api.md#IStreamingRTCEngine-setvideodecoderconfig) <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| encoded_video_frame | **const IEncodedVideoFrame&** | 解码前的视频数据，参看 [IEncodedVideoFrame](Windows-keytype.md#iencodedvideoframe) |
| stream_index | **streamingrtc::StreamIndex** | 视频流序号 参看 [StreamIndex](Windows-keytype.md#streamindex) |

**返回值**

+ `True`：成功
+ `False`：失败


<span id="IStreamingRTCEventHandler-onp2plocalexternalencoderstart"></span>
### OnP2PLocalExternalEncoderStart
```cpp
virtual void streamingrtc::IStreamingRTCEventHandler::OnP2PLocalExternalEncoderStart(
    streamingrtc::StreamIndex stream_index)
```
提醒外部视频编码器开始工作。 <br>
关于编码设置，参看 [SetVideoSourceType](Windows-api.md#IStreamingRTCEngine-setvideosourcetype) <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stream_index | **streamingrtc::StreamIndex** | 视频流序号 参看 [StreamIndex](Windows-keytype.md#streamindex) |


<span id="IStreamingRTCEventHandler-onp2plocalexternalencoderstop"></span>
### OnP2PLocalExternalEncoderStop
```cpp
virtual void streamingrtc::IStreamingRTCEventHandler::OnP2PLocalExternalEncoderStop(
    streamingrtc::StreamIndex stream_index)
```
提醒外部视频编码器停止工作。 <br>
关于编码设置，参看 [SetVideoSourceType](Windows-api.md#IStreamingRTCEngine-setvideosourcetype) <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stream_index | **streamingrtc::StreamIndex** | 视频流序号 参看 [StreamIndex](Windows-keytype.md#streamindex) |


<span id="IStreamingRTCEventHandler-onp2psuggestlocalexternalencoderrateupdate"></span>
### OnP2PSuggestLocalExternalEncoderRateUpdate
```cpp
virtual void streamingrtc::IStreamingRTCEventHandler::OnP2PSuggestLocalExternalEncoderRateUpdate(
    streamingrtc::StreamIndex stream_index,
    int32_t video_index,
    VideoRateInfo info)
```
提醒外部视频编码器调整编码码率。 <br>
关于编码设置，参看 [SetVideoSourceType](Windows-api.md#IStreamingRTCEngine-setvideosourcetype) <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stream_index | **streamingrtc::StreamIndex** | 视频流序号。 参看 [StreamIndex](Windows-keytype.md#streamindex) |
| video_index | **int32_t** | video solution 序号。 |
| info | **VideoRateInfo** | 建议调整的码率信息。 参看 [VideoRateInfo](Windows-keytype.md#videorateinfo) |


<span id="IStreamingRTCEventHandler-onp2prequestlocalexternalencoderkeyframe"></span>
### OnP2PRequestLocalExternalEncoderKeyFrame
```cpp
virtual void streamingrtc::IStreamingRTCEventHandler::OnP2PRequestLocalExternalEncoderKeyFrame(
    streamingrtc::StreamIndex stream_index,
    int32_t video_index)
```
提醒外部视频编码器发送关键帧。 <br>
关于编码设置，参看 [SetVideoSourceType](Windows-api.md#IStreamingRTCEngine-setvideosourcetype) <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| stream_index | **streamingrtc::StreamIndex** | 视频流序号。 参看 [StreamIndex](Windows-keytype.md#streamindex) |
| video_index | **int32_t** | video solution 序号。 |