"use strict";
//
//  index.ts
//
//  Created by huanghao on 2020/7/2.
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
Object.defineProperty(exports, "__esModule", { value: true });
const events_1 = require("events");
const NativeEngine = require("../../build/Release/vertc-electron-sdk.node");
const { logger } = require("../utils/logger");
const yuv_render_1 = require("../utils/yuv_render");
const types_1 = require("../types");
var fs = require('fs');
var path = require('path');
const mkdirsSync = (dirname) => {
    if (fs.existsSync(dirname)) {
        return true;
    }
    else {
        if (mkdirsSync(path.dirname(dirname))) {
            fs.mkdirSync(dirname);
            return true;
        }
    }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// veRTCEngine
function checkInit(target, propertyName, projectDescriptor) {
    // console.log('target: ', target);
    // console.log('propertyName: ', propertyName);
    // console.log('projectDescriptor: ', projectDescriptor);
    const method = projectDescriptor.value;
    projectDescriptor.value = function (...args) {
        let result = 0, params = '';
        try {
            if (!this.instance) {
                throw "instance is null";
            }
            params = args.map(a => JSON.stringify(a)).join();
            // console.log('params: ', params);
            // console.log('this: ', this);
            result = method.apply(this, args);
        }
        catch (err) {
            console.error(`Call ${propertyName} with (${params}) results: ${result}, error: `, err);
            result = -1;
        }
        return result;
    };
    return projectDescriptor;
}
function isNULL(obj) {
    if (typeof (obj) == "undefined" || obj === null) {
        return true;
    }
    else {
        return false;
    }
}
/** {zh}
 * @list 85530
 * @detail 85532
 */
class veRTCEngine extends events_1.EventEmitter {
    constructor() {
        super();
        this.instance = null;
        // userId --> userInfo
        this.remoteUsers = null;
        this.localChannelId = "";
        this.localUserId = "";
        this.localUser = null;
    }
    /** {zh}
     * @brief 创建和初始化引擎
     * @param appId 每个应用的唯一标识符，由 RTC 控制台随机生成的。不同的 AppId 生成的实例在 RTC 中进行音视频通话完全独立，无法互通。
     * @param documentPath 存放日志路径
     * @param params 用以覆盖默认参数的本引擎实例参数。JSON 字符串格式。
     * @return
     * + 0：成功
     * + !0：失败<br>
     * @region 引擎管理
     */
    init(appId, documentPath, params) {
        let ret = -1;
        do {
            if (this.instance) {
                console.warn('Call Init, but the instance is init yet');
                break;
            }
            this.instance = new NativeEngine.veRTCEngine();
            this.instance.Init(appId, documentPath, this.cbEngine.bind(this), params);
            // define an empty userId as the local user
            this.localUser = {
                userId: "",
                renderOptions: { renderMode: types_1.RenderMode.FIT, mirror: false }
            };
            this.remoteUsers = new Map();
            ret = 0;
        } while (false);
        return ret;
    }
    /** {zh}
     * @brief 销毁引擎
     * @return
     * + 0：成功
     * + !0：失败<br>
     * @region 引擎管理
     */
    uninit() {
        this.instance.Uninit();
        this.instance = null;
        this.remoteUsers = null;
        this.localChannelId = "";
        this.localUserId = "";
        this.localUser = null;
        return 0;
    }
    /** {zh}
     * @brief 获取当前 SDK 版本信息
     * @return {string} 当前 SDK 版本信息
     * @region 引擎管理
     */
    static getSDKVersion() {
        return NativeEngine.GetSDKVersion();
    }
    /** {zh}
     * @brief 获取加载引擎进程的 ID 方便调试
     * @return {string} 进程的 ID
     */
    static getCurrentProcessId() {
        return NativeEngine.GetCurrentProcessId();
    }
    /**
     * @region 引擎管理
     * @brief 设置业务标识参数
     * @param business_id 用户设置的自己的 business_id 值。business_id 相当于一个 sub AppId，可以分担和细化现在 AppId 的逻辑划分的功能， 但不需要鉴权。business_id 只是一个标签，颗粒度需要用户自定义。
     * @return + 0： 成功。
     * + <0： 失败
     * + -6001： 用户已经在房间中。
     * + -6002： 输入非法，合法字符包括所有小写字母、大写字母和数字，除此外还包括四个独立字符分别是：英文句号，短横线，下划线和 `@`。<br>
     * @notes
     * + 可通过 business_id 区分不同的业务场景（角色/策略等）。business_id 由客户自定义，相当于一个“标签”，可以分担和细化现在 AppId 的逻辑划分的功能。
     * + 需要在调用 joinRoom{@link #JoinRoom} 之前调用，joinRoom{@link #JoinRoom}之后调用该方法无效。
     */
    setBusinessId(business_id) {
        return this.instance.SetBusinessId(business_id);
    }
    /** {zh}
     * @region 房间管理
     * @brief 创建/加入房间：房间不存在时即创建房间；房间存在时即加入这个房间。
     * @param token 动态密钥，用于对登录用户进行鉴权验证。进入房间需要携带 Token。测试时可使用控制台生成临时 Token，正式上线需要使用密钥 SDK 在您的服务端生成并下发 Token。<br>请务必保证生成 Token 使用的 App ID 和创建引擎时使用的 App ID 相同，否则会导致加入房间失败。<br>Token 过期后，无法成功登录房间或重联。
     * @param room_id 加入的房间 ID。房间 ID 为长度在 128 字节以内的非空字符串，支持以下字符集范围:  1. 26 个大写字母 A ~ Z 。   2. 26 个小写字母 a ~ z 。  3. 10 个数字 0 ~ 9 。   4. 下划线 "_"，at 符 "@"，减号 "-"。
     * @param uid 用户 ID用户 ID 在 appId 的维度下是唯一的。
     * @param info 用户信息
     * @param roomConfig 房间参数配置，设置房间模式以及是否自动发布或订阅流。
     * @return
     * +  0: 成功
     * + -1: room_id 为空，失败<br>
     * + -2: user_info 为空，失败<br>
     * @notes
     * + 同一房间内的用户间可以相互通话。
     * + 进房后重复调用无效，用户必须调用 leaveRoom{@link #LeaveRoom} 退出当前房间后，才能加入下一个房间。
     * + 本地用户调用此方法加入房间成功后，会收到 OnJoinRoomResult{@link 85533#OnJoinRoomResult} 回调通知。
     * + 本地用户调用 setUserVisibility{@link #SetUserVisibility} 将自身设为可见后加入房间，远端用户会收到 OnUserJoined{@link 85533#OnUserJoined}。+ 使用不同 App ID 的 App 是不能互通的。
     * + 用户加入房间成功后，在本地网络状况不佳的情况下，SDK 可能会与服务器失去连接，此时 SDK 将会自动重连。重连成功后，本地会收到 OnJoinRoomResult{@link 85533#OnJoinRoomResult} 回调通知。
     * + 同一个 App ID 的同一个房间内，每个用户的用户 ID 必须是唯一的。如果两个用户的用户 ID 相同，则后进房的用户会将先进房的用户踢出房间，并且先进房的用户会收到 OnError{@link 85533#OnError} 回调通知，错误类型详见 ErrorCode{@link #ErrorCode} 中的 kErrorCodeDuplicateLogin。
     */
    joinRoom(token, room_id, uid, info, roomConfig) {
        this.localChannelId = room_id;
        this.localUserId = uid;
        if (this.localUser) {
            this.localUser.userId = uid;
        }
        return this.instance.JoinRoom(token, room_id, uid, info, roomConfig);
    }
    /** {zh}
     * @region 房间管理
     * @brief 设置用户可见性。默认为可见。
     * @param enable 设置用户是否对房间内其他用户可见：  + `true`: 可以被房间中的其他用户感知，且可以在房间内发布和订阅音视频流；  + `false`: 无法被房间中的其他用户感知，且只能在房间内订阅音视频流。
     * @return
     * + 0：成功
     * + !0：失败<br>
     * @notes
     * + 通过对用户可见性进行设置，可以控制用户在房间内的行为：
     *          + 能否发布音视频流；
     *          + 用户自身是否在房间中隐身。
     * + 该方法在加入房间前后均可调用。
     * + 在房间内调用此方法，房间内其他用户会收到相应的回调通知：
     *            - 从 false 切换至 true 时，房间内其他用户会收到 OnUserJoined{@link 85533#OnUserJoined} 回调通知；
     *            - 从 true 切换至 false 时，房间内其他用户会收到 OnUserLeave{@link 85533#OnUserLeave} 回调通知。
     * + 若调用该方法将可见性设为 false，此时尝试发布流会收到 OnWarning{@link 85533#OnWarning} 警告，具体原因参看 WarningCode{@link #WarningCode} 中的 kWarningCodePublishStreamForbiden 警告码。
     */
    setUserVisibility(enable) {
        return this.instance.SetUserVisibility(enable);
    }
    /** {zh}
     * @region 房间管理
     * @brief 离开房间。调用此方法离开房间，结束通话过程，释放所有通话相关的资源。
     * @return
     * + 0：成功
     * + !0：失败<br>
     * @notes
     * + 加入房间后，必须调用此方法结束通话，否则无法开始下一次通话。无论当前是否在房间内，都可以调用此方法。重复调用此方法没有负面影响。
     * + 此方法是异步操作，调用返回时并没有真正退出房间。真正退出房间后，本地会收到 OnLeaveRoom{@link 85533#OnLeaveRoom} 回调通知。
     * + 调用 setUserVisibility{@link #SetUserVisibility} 将自身设为可见的用户离开房间后，房间内其他用户会收到 OnUserLeave{@link 85533#OnUserLeave} 回调通知。
     * + 如果调用此方法后立即销毁引擎，SDK 将无法触发 OnLeaveRoom{@link 85533#OnLeaveRoom} 回调。
     */
    leaveRoom() {
        return this.instance.LeaveRoom();
    }
    /** {zh}
     * @region 房间管理
     * @brief 更新 Token
     * @param token 更新的动态密钥。
     * @return
     * + 0：成功
     * + !0：失败<br>
     * @notes
     * + Token 有一定的有效期，当 Token 过期时，用户需调用此方法更新房间的 Token 信息。
     * + 用户调用 joinRoom{@link #joinRoom} 方法加入房间时，如果使用了过期的 Token 将导致加入房间失败，并会收到 OnJoinRoomResult{@link #OnJoinRoomResult} 回调通知，错误码为 ErrorCode.kErrorCodeInvalidToken{@link #ErrorCode}。此时需要重新获取 Token，并调用此方法更新 Token。
     * + 如果用户因 Token 过期导致加入房间失败，则调用此方法更新 Token 后，SDK 会自动重新加入房间，而不需要用户自己调用 joinRoom{@link #JoinRoom} 方法。
     */
    updateToken(token) {
        return this.instance.UpdateToken(token);
    }
    /** {zh}
     * @type api
     * @region 音频管理
     * @brief 调节本地播放的所有远端用户混音后的音量
     * @param volume 音频播放音量，取值范围： [0,400] + 0: 静音   + 100: 原始音量   + 400: 最大可为原始音量的 4 倍(自带溢出保护)
     * @return
     * + 0：成功
     * + !0：失败<br>
     * @notes 为保证更好的通话质量，建议将 volume 值设为 [0,100]。
     */
    setPlaybackVolume(volume) {
        return this.instance.SetPlaybackVolume(volume);
    }
    /** {zh}
     * @region 音频管理
     * @brief 开启内部音频采集。默认为关闭状态。
     * @return
     * + 0：成功
     * + !0：失败<br>
     * @notes
     * + 进房前调用该方法，本地用户会收到 OnMediaDeviceStateChanged{@link 85533#OnMediaDeviceStateChanged} 的回调。
     * + 进房后调用该方法，房间中的其他用户会收到 OnUserStartAudioCapture{@link 85533#OnUserStartAudioCapture} 的回调。
     * + 若未取得当前设备的麦克风权限，调用该方法后会触发 OnWarning{@link 85533#OnWarning} 回调。
     * + 调用 stopAudioCapture{@link #StopAudioCapture} 可以关闭音频采集设备，否则，SDK 只会在销毁引擎的时候自动关闭设备。
     * + 无论是否发布音频数据，你都可以调用该方法开启音频采集，并且调用后方可发布音频。
     * + 尚未进房并且已使用自定义采集时，关闭自定义采集后并不会自动开启内部采集。你需调用此方法手动开启内部采集。
     */
    startAudioCapture() {
        return this.instance.StartAudioCapture();
    }
    /** {zh}
     * @region 音频管理
     * @brief 关闭内部音频采集。默认为关闭状态。
     * @return
     * + 0：成功
     * + !0：失败<br>
     * @notes
     * + 进房前调用该方法，本地用户会收到 OnMediaDeviceStateChanged{@link 85533#OnMediaDeviceStateChanged} 的回调。
     * + 进房后调用该方法后，房间中的其他用户会收到 OnUserStopAudioCapture{@link #OnUserStopAudioCapture} 的回调。
     * + 调用 startAudioCapture{@link #StartAudioCapture} 可以开启音频采集设备。
     * + 设备开启后若一直未调用该方法关闭，则 SDK 会在销毁引擎的时候自动关闭音频采集设备。
     */
    stopAudioCapture() {
        return this.instance.StopAudioCapture();
    }
    /** {zh}
     * @region 媒体流管理
     * @brief 控制本地音频流的发送状态：发送/不发送
     * @param muteState 发送状态，标识是否发送本地音频流
     * @return
     * + 0：成功
     * + !0：失败<br>
     * @notes
     * + 使用此方法后，房间中的其他用户会收到回调： OnUserMuteAudio{@link 85533#OnUserMuteAudio}
     * + 本方法仅控制本地音频流的发送状态，并不影响本地音频采集状态。
     */
    muteLocalAudio(muteState) {
        return this.instance.MuteLocalAudio(muteState);
    }
    /** {zh}
     * @region 多房间
     * @brief 开启/关闭音量提示。默认关闭。
     * @param interval 收到音量提示回调的时间间隔：  <br>建议设置为大于等于 200 毫秒；小于 10 毫秒时，行为未定义。<li> ≤ 0：禁用音量提示功能。  </li><li> > 0：启用音量提示功能，并设置收到音量提示回调的时间间隔。单位为毫秒。</li>
     * @return
     * + 0：成功
     * + !0：失败<br> <br>
     * @notes
     * + 开启音量提示后，将按设置的时间间隔收到本地采集音量或订阅的远端用户的音量信息回调。
     * + 关于回调的具体信息，参看 OnAudioVolumeIndication{@link 85533#OnAudioVolumeIndication}
     */
    setAudioVolumeIndicationInterval(interval) {
        return this.instance.SetAudioVolumeIndicationInterval(interval);
    }
    /** {zh}
     * @region 音频管理
     * @brief 调节来自远端用户的音频播放音量
     * @param strUserId 音频来源的远端用户 ID
     * @param volume  播放音量，取值范围： [0,400]  <li> 0: 静音 </li> <li> 100: 原始音量 </li> <li> 400: 最大可为原始音量的 4 倍(自带溢出保护)  </li>
     * @return
     * + 0：成功
     * + !0：失败<br>
     */
    setRemoteAudioPlaybackVolume(strUserId, volume) {
        return this.instance.SetRemoteAudioPlaybackVolume(strUserId, volume);
    }
    /** {zh}
     * @region 媒体流管理
     * @brief 恢复接收来自远端的媒体流
     * @param type 媒体流类型，指定需要暂停接收音频还是视频流
     * @return
     * + 0：成功
     * + !0：失败<br>
     * @notes
     * + 该方法仅恢复远端流的接收，并不影响远端流的采集和发送；
     * + 该方法不改变用户的订阅状态以及订阅流的属性。
     */
    resumeAllSubscribedStream(type) {
        return this.instance.ResumeAllSubscribedStream(type);
    }
    /** {zh}
    * @region 视频管理
    * @brief 开启内部视频采集。默认为关闭状态
    * @return
     * + 0：成功
     * + !0：失败<br>
    * @notes
    * + 调用该方法后，本地用户会收到 OnMediaDeviceStateChanged{@link 85533#OnMediaDeviceStateChanged} 的回调。
    * + 进房后调用该方法后，房间中的其他用户会收到 OnUserStartVideoCapture{@link 85533#OnUserStartVideoCapture} 的回调。
    * + 内部视频采集指：使用 RTC SDK 内置视频采集模块，进行采集。
    * + 若未取得当前设备的摄像头权限，调用该方法会不成功，并触发 OnMediaDeviceStateChanged{@link #OnMediaDeviceStateChanged} 回调。
    * + 调用 stopVideoCapture{@link #StopVideoCapture} 可以关闭视频采集设备，否则，SDK 只会在销毁引擎的时候自动关闭设备。
    * + 无论是否发布视频数据，你都可以调用该方法开启视频采集，并且调用后方可发布视频。
    * + 如果需要从自定义视频采集切换为内部视频采集，你必须先关闭自定义采集，再调用此方法手动开启内部采集。
    */
    startVideoCapture() {
        return this.instance.StartVideoCapture();
    }
    /** {zh}
     * @region 视频管理
     * @brief 关闭内部视频采集。默认为关闭状态。
     * @return
     * + 0：成功
     * + !0：失败<br>
     * @notes
     * + 调用该方法后，本地用户会收到 OnMediaDeviceStateChanged{@link 85533#OnMediaDeviceStateChanged} 的回调。
     * + 进房后调用该方法后，房间中的其他用户会收到 OnUserStopVideoCapture{@link 85533#OnUserStopVideoCapture} 的回调。
     * + 调用 startVideoCapture{@link #StartVideoCapture} 可以开启视频采集设备。
     * + 设备开启后若一直未调用此方法关闭本地视频采集，则 SDK 会在销毁引擎的时候自动关闭。
     */
    stopVideoCapture() {
        return this.instance.StopVideoCapture();
    }
    /** {zh}
     * @region 视频管理
     * @brief 启动推送多路视频流，设置推送多路流时的各路视频参数，包括分辨率、帧率、码率、缩放模式、网络不佳时的回退策略等。
     * @param index 主流 or 屏幕流<li>主流。包括：由摄像头/麦克风通过内部采集机制，采集到的视频/音频;通过自定义采集，采集到的视频/音频。</li><li>屏幕流。屏幕共享时共享的视频流，或来自声卡的本地播放音频流。</li>
     * @param solutions 视频参数数组首地址。<br> 最多支持 3 路参数。当设置了多路参数时，分辨率必须是依次减小，从大到小排列的。 <br>最大分辨率没有限制。但是如果设置的分辨率无法编码，就会导致编码推流失败。
     * @return
     * + 0：成功
     * + !0：失败<br>
     * @notes
     * + 当使用内部采集时，视频采集的分辨率、帧率会根据编码参数进行适配。
     * + 默认的视频编码参数为：分辨率 640px * 360px，帧率 15fps。
     * + 变更编码分辨率后马上生效，可能会引发相机重启。
     * + 屏幕流只取视频参数数组的第一组数据。
     */
    setVideoEncoderConfig(index, solutions) {
        // set default value
        for (let i = 0; i < solutions.length; i++) {
            solutions[i].maxSendKbps = solutions[i].maxSendKbps || types_1.SEND_KBPS_AUTO_CALCULATE;
            solutions[i].scaleMode = solutions[i].scaleMode || types_1.ScaleMode.Auto;
            solutions[i].encodePreference = solutions[i].encodePreference || types_1.EncodePreference.EncodePreferenceFramerate;
        }
        return this.instance.SetVideoEncoderConfig(index, solutions);
    }
    /** {zh}
     * @region 视频管理
     * @brief 停止/启动发送本地视频流，默认不发送。
     * @param muteState 发送状态，标识是否发送本地视频流
     * @return
     * + 0：成功
     * + !0：失败<br>
     * @notes
     * + 无论你使用内部视频采集，还是自定义视频采集，你都应使用此接口启动发送本地视频流。
     * + 调用该方法后，房间中的其他用户会收到 OnUserMuteVideo{@link #OnUserMuteVideo} 的回调。
     * + 本方法只是停止/启动本地视频流的发送，不影响视频采集状态。
     * + 无论是否开启视频采集，你都可以启动发送本地视频流。这样，一旦开始采集视频，即可进行发送。
     */
    muteLocalVideo(muteState) {
        return this.instance.MuteLocalVideo(muteState);
    }
    /** {zh}
     * @type api
     * @region 视频管理
     * @brief 切换视频内部采集时使用的前置/后置摄像头。默认使用前置摄像头。
     * @param camera_id 移动端摄像头。可通过 enumerateVideoCaptureDevices{@link #enumerateVideoCaptureDevices} 获取。
     * @return
     * + 0：成功
     * + !0：失败<br>
     * @notes
     * + 调用此接口后，在本地会触发 OnMediaDeviceStateChanged{@link 85533#onMediaDeviceStateChanged} 回调。
     * + 如果你正在使用相机进行视频采集，切换操作当即生效；如果相机未启动，后续开启内部采集时，会打开设定的摄像头。
     * + 如果本地有多个摄像头且想选择特定工作摄像头可通过 IVideoDeviceManager{@link #IVideoDeviceManager} 来控制。
     */
    switchCamera(camera_id) {
        return this.instance.SwitchCamera(camera_id);
    }
    /** {zh}
     * @region 视频管理
     * @brief 设置采用前置摄像头采集时，是否开启镜像模式。
     * @param nMode 是否开启镜像模式
     * @return
     * + 0：成功
     * + !0：失败<br>
     */
    setLocalVideoMirrorMode(nMode) {
        var _a;
        let user = this.localUser;
        if (user) {
            user.renderOptions.mirror = nMode == 1 ? true : false;
            (_a = user.videoRender) === null || _a === void 0 ? void 0 : _a.setMirrorType(nMode == 1 ? true : false);
        }
        // return this.instance.SetLocalVideoMirrorMode(nMode);
        return 1;
    }
    /** {zh}
     * @region 媒体流处理
     * @brief 暂停接收来自远端的媒体流。
     * @param type 媒体流类型，指定需要暂停接收音频还是视频流
     * @return
     * + 0：成功
     * + !0：失败<br>
     * @notes
     * + 该方法仅暂停远端流的接收，并不影响远端流的采集和发送；
     * + 该方法不改变用户的订阅状态以及订阅流的属性。
     * + 若想恢复接收远端流，需调用 resumeAllSubscribedStream{@link #ResumeAllSubscribedStream}。
     */
    pauseAllSubscribedStream(type) {
        return this.instance.PauseAllSubscribedStream(type);
    }
    /** {zh}
     * @region 屏幕共享
     * @brief 采集屏幕视频流，用于共享。屏幕视频流包括：屏幕上显示的内容，应用窗口中显示的内容，或虚拟屏幕中显示的内容。其中，虚拟屏幕中显示的内容仅在 Windows 平台上支持。
     * @param info 待共享的屏幕源，你可以调用 getScreenCaptureSourceList{@link #GetScreenCaptureSourceList} 获得所有可以共享的屏幕源。
     * @param params 共享参数
     * @return
     * + 0：成功
     * + !0：失败<br>
     * @notes
     * + 调用此方法仅开启屏幕流视频采集，不会发布采集到的视频。发布屏幕流视频需要调用 publishScreen{@link #PublishScreen} 。
     * + 要关闭屏幕视频源采集，调用 stopScreenVideoCapture{@link #StopScreenVideoCapture}。
     * + 调用成功后，本端会收到 OnFirstLocalVideoFrameCaptured{@link 85533#OnFirstLocalVideoFrameCaptured} 回调。然后通过调用 setupLocalScreen{@link #setupLocalScreen} 设置本地屏幕共享视图。
     * + 调用此接口前，你可以调用 setVideoEncoderConfig{@link #SetVideoEncoderConfig} 设置屏幕视频流的采集帧率和编码分辨率。
     * + 监听 OnLocalScreenFrame{@link #OnLocalScreenFrame} 本地屏幕视频回调事件
     */
    startScreenVideoCapture(info, params) {
        return this.instance.StartScreenVideoCapture(info, params);
    }
    /** {zh}
     * @region 屏幕共享
     * @brief 更新屏幕共享区域。
     * @param regionRect <li>当共享屏幕时，指定待共享区域相对于虚拟屏幕的位置</li><li>当共享窗口时，指定待共享区域相对于整个窗口的位置</li>
     * @return
     * + 0：成功
     * + !0：失败<br>
     */
    updateScreenCaptureRegion(regionRect) {
        // default value
        return this.instance.UpdateScreenCaptureRegion(regionRect);
    }
    /** {zh}
     * @type api
     * @region 屏幕共享
     * @brief 通过 RTC SDK 提供的采集模块采集屏幕视频流时，更新对鼠标的处理设置。默认采集鼠标。
     * @param state 内部采集屏幕视频流时，是否采集鼠标信息
     * @return
     * + 0：成功
     * + !0：失败<br>
     * @notes 调用此接口前，必须已通过调用 startScreenVideoCapture{@link #StartScreenVideoCapture} 开启了内部屏幕流采集。
     */
    UpdateScreenCaptureMouseCursor(state) {
        // default value
        return this.instance.UpdateScreenCaptureMouseCursor(state);
    }
    /** {zh}
     * @region 屏幕共享
     * @brief 通过 RTC SDK 提供的采集模块采集屏幕视频流时，更新边框高亮设置。默认展示表框。
     * @param highlight_config 边框高亮设置
     * @return
     * + 0：成功
     * + !0：失败<br>
     * @notes 调用此接口前，必须已通过调用 startScreenVideoCapture{@link #StartScreenVideoCapture} 开启了内部屏幕流采集。
     */
    updateScreenCaptureHighlightConfig(highlight_config) {
        // default value
        return this.instance.UpdateScreenCaptureHighlightConfig(highlight_config);
    }
    /** {zh}
     * @region 屏幕共享
     * @brief 通过 RTC SDK 提供的采集模块采集屏幕视频流时，设置需要过滤的窗口。
     * @param screenFilterConfig 窗口过滤设置，参看 ScreenCaptureParameters{@link #ScreenCaptureParameters}
     * @return
     * + 0：成功
     * + !0：失败<br>
     * @notes
     * + 调用此接口前，必须已通过调用 startScreenVideoCapture{@link #StartScreenVideoCapture} 开启了内部屏幕流采集。
     * + 本函数在屏幕源类别是屏幕而非应用窗体时才起作用。详见： ScreenCaptureSourceType{@link #ScreenCaptureSourceType}
     */
    updateScreenCaptureFilterConfig(screenFilterConfig) {
        return this.instance.UpdateScreenCaptureFilterConfig(screenFilterConfig);
    }
    /** {zh}
     * @region 屏幕共享
     * @brief 停止屏幕视频流采集。
     * @return
     * + 0：成功
     * + !0：失败<br>
     * @notes
     * + 要开启屏幕视频流采集，调用 startScreenVideoCapture{@link #StartScreenVideoCapture}
     * + 调用此接口不影响屏幕视频流发布。
     */
    stopScreenVideoCapture() {
        this.removeLocalScreen();
        return this.instance.StopScreenVideoCapture();
    }
    /** {zh}
     * @brief 获取屏幕采集对象列表。
     * @return 屏幕采集对象列表
     */
    getScreenCaptureSourceList() {
        return this.instance.GetScreenCaptureSourceList();
    }
    // share screen
    /** {zh}
     * @brief 获取屏幕共享对象 thumbnail。
     * @param type 屏幕采集对象的类型
     * @param sourceId 屏幕分享时，共享对象的 ID
     * @param maxWidth 最大宽度
     * @param maxHeight 最大高度
     * @return 屏幕共享对象
     */
    getThumbnail(type, sourceId, maxWidth, maxHeight) {
        let obj = this.instance.GetThumbnail(type, sourceId, maxWidth, maxHeight);
        if (obj.data) {
            obj.data = "data:image/png;base64," + obj.data;
        }
        return obj;
    }
    /** {zh}
     * @region 屏幕共享
     * @brief 发布本地屏幕共享流到房间。
     * @return
     * + 0：成功
     * + !0：失败<br>
     * @notes
     * + 你必须先加入房间，才能调用此方法。
     * + 直播、游戏、云游戏房间模式下，仅可见的用户可以调用此方法。你可以调用 setUserVisibility{@link #setUserVisibility} 方法设置用户在房间中的可见性。
     * + 此方法只影响屏幕共享视频流的发布状态，并不影响屏幕视频流的采集情况。参看 startScreenVideoCapture{@link #startScreenVideoCapture} 和 StartScreenAudioCapture{@link #StartScreenAudioCapture}
     * + 发布成功后，远端会收到 OnStreamAdd{@link 85533#OnStreamAdd} 回调和 OnRemoteScreenFrame{@link 85533#OnRemoteScreenFrame} 回调。
     * + 调用 unpublishScreen{@link #unpublishScreen} 取消发布。
     */
    publishScreen() {
        return this.instance.PublishScreen();
    }
    /** {zh}
     * @region 屏幕共享
     * @brief 停止发布本地屏幕共享流到房间。
     * @return
     * + 0：成功
     * + !0：失败<br>
     * @notes
     * + 远端会收到 OnStreamRemove{@link 85533#OnStreamRemove} 事件。
     * + 此方法只影响屏幕共享视频流的发布状态，并不影响屏幕视频流的采集情况。
     * + 调用 publishScreen{@link #PublishScreen} 启动发布。
     */
    unpublishScreen() {
        return this.instance.UnpublishScreen();
    }
    /** {zh}
     * @region 音量管理
     * @brief 调节音频采集音量
     * @param index 流索引，指定调节主流还是调节屏幕流的音量<li>主流。包括：由摄像头/麦克风通过内部采集机制，采集到的视频/音频;通过自定义采集，采集到的视频/音频。</li><li>屏幕流。屏幕共享时共享的视频流，或来自声卡的本地播放音频流。</li>
     * @param volume 采集的音量值和原始音量的比值，范围是 [0, 400]，单位为 %，自带溢出保护。
     * @return
     * + 0：成功
     * + !0：失败<br>
     * @notes
     * + 无论是采集来自麦克风的音频流，还是屏幕音频流；无论是 RTC SDK 内部采集，还是自定义采集，都可以使用此接口进行音量调节。
     * + 在开启音频采集前后，你都可以使用此接口设定采集音量。
     */
    setCaptureVolume(index, volume) {
        return this.instance.SetCaptureVolume(index, volume);
    }
    /** {zh}
     * @region 混音
     * @brief 开始播放音乐文件及混音
     * @param id  混音 ID，用于标识混音，请保证混音 ID 唯一性。 <br> 如果已经通过 preloadAudioMixing{@link #PreloadAudioMixing} 将音效加载至内存，确保此处的 ID 与 preloadAudioMixing{@link #PreloadAudioMixing} 设置的 ID 相同。  <br>如果使用相同的 ID 重复调用本方法，前一次混音会停止，后一次混音开始，且 SDK 会使用 OnAudioMixingStateChanged{@link 85533#OnAudioMixingStateChanged} 回调通知前一次混音已停止。
     * @param file_path 指定需要混音的本地文件的绝对路径，支持音频文件格式有: mp3，aac，m4a，3gp，wav。  <br>可以通过传入不同的 ID 和 file_path 多次调用本方法，以实现同时播放多个音乐文件，实现混音叠加。
     * @param mixingconfig 混音配置，设置混音的播放次数、是否本地播放混音、以及是否将混音发送至远端，详见 AudioMixingConfig{@link #AudioMixingConfig}
     * @return
     * + 0：成功
     * + !0：失败<br>
     * @notes
     * + 调用本方法成功播放音乐文件后，SDK 会向本地回调当前的混音状态，见 OnAudioMixingStateChanged{@link 85533#OnAudioMixingStateChanged}。
     * + 开始播放音乐文件及混音后，可以调用 stopAudioMixing{@link #StopAudioMixing} 方法停止播放音乐文件。
     */
    startAudioMixing(id, file_path, mixingconfig) {
        return this.instance.StartAudioMixing(id, file_path, mixingconfig);
    }
    /** {zh}
     * @region 混音
     * @brief 停止播放音乐文件及混音
     * @param id 混音 ID
     * @return
     * + 0：成功
     * + !0：失败<br>
     * @notes
     * + 调用 startAudioMixing{@link #StartAudioMixing} 方法开始播放音乐文件及混音后，可以调用本方法停止播放音乐文件及混音。
     * + 调用本方法停止播放音乐文件后，SDK 会向本地回调通知已停止混音，见 OnAudioMixingStateChanged{@link 85533#OnAudioMixingStateChanged}。
     * + 调用本方法停止播放音乐文件后，该音乐文件会被自动卸载。
     */
    stopAudioMixing(id) {
        return this.instance.StopAudioMixing(id);
    }
    /**
     * @type api
     * @region 混音
     * @brief 暂停播放音乐文件及混音
     * @param id 混音 ID
     * @return
     * + 0：成功
     * + !0：失败<br>
     * @notes
     * + 调用 startAudioMixing{@link #StartAudioMixing} 方法开始播放音乐文件及混音后，可以通过调用本方法暂停播放音乐文件及混音。
     * + 调用本方法暂停播放音乐文件及混音后，可调用 resumeAudioMixing{@link #ResumeAudioMixing} 方法恢复播放及混音。
     * + 调用本方法暂停播放音乐文件后，SDK 会向本地回调通知已暂停混音，见 OnAudioMixingStateChanged{@link 85533#OnAudioMixingStateChanged}。
     */
    pauseAudioMixing(id) {
        return this.instance.PauseAudioMixing(id);
    }
    /** {zh}
     * @region 混音
     * @brief 恢复播放音乐文件及混音
     * @param id
     *        混音 ID
     * @return
     * + 0：成功
     * + !0：失败<br>
     * @notes
     * + 调用 pauseAudioMixing{@link #PauseAudioMixing} 方法暂停播放音乐文件及混音后，可以通过调用本方法恢复播放及混音。
     * + 调用本方法恢复播放音乐文件及混音后，SDK 会向本地回调通知音乐文件正在播放中，见 OnAudioMixingStateChanged{@link #OnAudioMixingStateChanged}。
     */
    resumeAudioMixing(id) {
        return this.instance.ResumeAudioMixing(id);
    }
    /** {zh}
     * @region 混音
     * @brief 调节音乐文件在本地和远端播放的音量大小
     * @param id 混音 ID
     * @param volume 音乐文件播放音量范围为 0~400。 <li> 0：静音 </li> <li> 100：原始音量  </li><li> 400: 最大可调音量 (自带溢出保护)</li>
     * @param type 混音播放类型 <br>设置音乐文件是否本地播放、以及是否发送到远端，由此控制音乐文件本地或远端播放的音量，详见 AudioMixingType{@link #AudioMixingType}。
     * @return
     * + 0：成功
     * + !0：失败<br>
     * @notes
     * + 调用本方法设置音量前，请先调用 preloadAudioMixing{@link #PreloadAudioMixing} 或 startAudioMixing{@link #StartAudioMixing}。
     * + 为保证更好的音质，建议将 volume 值设为 [0,100]。
     */
    setAudioMixingVolume(id, volume, type) {
        return this.instance.SetAudioMixingVolume(id, volume, type);
    }
    /** {zh}
     * @region 混音
     * @brief 获取音乐文件时长
     * @param id 混音 ID
     * @return
     * + `>0`: 成功, 音乐文件时长，单位为毫秒。
     * + `<0`: 失败<br>
     * @notes 调用本方法获取音乐文件时长前，需要先调用 preloadAudioMixing{@link #PreloadAudioMixing} 或 startAudioMixing{@link #StartAudioMixing}。
     */
    getAudioMixingDuration(id) {
        return this.instance.GetAudioMixingDuration(id);
    }
    /** {zh}
     * @type api
     * @region 混音
     * @brief 获取音乐文件播放进度
     * @param id 混音 ID
     * @return
     * + `>0`: 成功, 音乐文件播放进度，单位为毫秒。
     * + `<0`: 失败<br>
     * @notes 调用本方法获取音乐文件播放进度前，需要先调用 startAudioMixing{@link #StartAudioMixing} 开始播放音乐文件。
     */
    getAudioMixingCurrentPosition(id) {
        return this.instance.GetAudioMixingCurrentPosition(id);
    }
    /** {zh}
     * @type api
     * @region 混音
     * @brief 设置音乐文件的播放位置
     * @param id 混音 ID
     * @param pos 进度条位置，整数，单位为毫秒。
     * @return
     * + 0：成功
     * + !0：失败<br>
     * @notes
     * + 本方法可以设置音乐文件的播放位置，这样你可以根据实际情况从指定的位置播放音乐文件，无需从头到尾完整播放一个音乐文件。
     * + 调用本方法设置音乐文件的播放位置前，需要先调用 StartAudioMixing{@link #StartAudioMixing} 开始播放音乐文件。
     */
    setAudioMixingPosition(id, pos) {
        return this.instance.SetAudioMixingPosition(id, pos);
    }
    /** {zh}
     * @type api
     * @region 混音
     * @brief 预加载指定音乐文件到内存中
     * @param id 混音 ID  <br>应用调用者维护，请保证唯一性。  <br>如果使用相同的 ID 调用本方法，后一次会覆盖前一次。 <br>如果先调用 startAudioMixing{@link #StartAudioMixing} ，再使用相同的 ID 调用本方法 ，会先回调 OnAudioMixingStateChanged{@link 85533#OnAudioMixingStateChanged} 上一个混音停止，然后加载后一个混音。  <br>使用一个 ID 调用本方法预加载 A.mp3 后，如果需要使用相同的 ID 调用 startAudioMixing{@link #StartAudioMixing} 播放 B.mp3，请先调用 unloadAudioMixing{@link #UnloadAudioMixing} 卸载 A.mp3 ，否则会报错 kAudioMixingErrorLoadConflict。
     * @param file_path  指定需要混音的本地文件的绝对路径，支持音频文件格式有: mp3，aac，m4a，3gp，wav。  <br>如果音乐文件长度超过 20s，会回调加载失败，见 OnAudioMixingStateChanged{@link 85533#OnAudioMixingStateChanged}。
     * @return
     * + 0：成功
     * + !0：失败<br>
     * @notes
     * + 需要频繁播放某个音乐文件的时候，调用本方法预加载该文件，在播放的时候可以只加载一次该文件，减少 CPU 占用。  <br>
     * + 本方法只是预加载指定音乐文件，只有调用 startAudioMixing{@link #StartAudioMixing} 方法才开始播放指定音乐文件。 <br>
     * + 调用本方法预加载音乐文件后，SDK 会回调通知音乐文件已加载，见 OnAudioMixingStateChanged{@link 85533#OnAudioMixingStateChanged}。  <br>
     * + 调用本方法预加载的指定音乐文件可以通过 unloadAudioMixing{@link #UnloadAudioMixing} 卸载。
     */
    preloadAudioMixing(id, file_path) {
        return this.instance.PreloadAudioMixing(id, file_path);
    }
    /** {zh}
     * @type api
     * @region 混音
     * @brief 卸载指定音乐文件
     * @param id 混音 ID
     * @return
     * + 0：成功
     * + !0：失败<br>
     * @notes 不论音乐文件是否播放，调用本方法卸载该文件后，SDK 会回调通知混音已停止，见 OnAudioMixingStateChanged{@link 85533#OnAudioMixingStateChanged}。
     */
    unloadAudioMixing(id) {
        return this.instance.UnloadAudioMixing(id);
    }
    /** {zh}
     * @type api
     * @region 视频设备管理
     * @brief 获取当前系统内视频采集设备列表。
     * @return 包含系统中所有视频采集设备的列表和相关信息
     */
    enumerateVideoCaptureDevices() {
        return this.instance.EnumerateVideoCaptureDevices();
    }
    /** {zh}
     * @type api
     * @region 视频设备管理
     * @brief 设置当前视频采集设备
     * @param deviceId 视频设备 ID，可以通过 EnumerateVideoCaptureDevices{@link #EnumerateVideoCaptureDevice} 获取
     * @return
     * + 0：方法调用成功
     * + !0：方法调用失败<br>
     */
    setVideoCaptureDevice(deviceId) {
        return this.instance.SetVideoCaptureDevice(deviceId);
    }
    /** {zh}
     * @type api
     * @region 视频设备管理
     * @brief 获取当前 SDK 正在使用的视频采集设备信息
     * @return 当前 SDK 正在使用的视频采集设备信息
     */
    getVideoCaptureDevice() {
        return this.instance.GetVideoCaptureDevice();
    }
    /** {zh}
    * @type api
    * @region 音频设备管理
    * @brief 获取当前系统内音频播放设备列表。如果后续设备有变更，你会收到 OnMediaDeviceStateChanged{@link 85533#OnMediaDeviceStateChanged} 回调通知，然后需要重新调用本接口以获得新的设备列表。
    * @return 包含系统中所有音频播放设备的列表和相关信息
    */
    enumerateAudioPlaybackDevices() {
        return this.instance.EnumerateAudioPlaybackDevices();
    }
    /** {zh}
     * @type api
     * @region 音频设备管理
     * @brief 获取当前系统内音频采集设备列表。如果后续设备有变更，你需要重新调用本接口以获得新的设备列表。
     * @return 包含系统中所有音频采集设备列表和相关信息
     */
    enumerateAudioCaptureDevices() {
        return this.instance.EnumerateAudioCaptureDevices();
    }
    /** {zh}
     * @type api
     * @region 音频设备管理
     * @brief 设置音频播放设备。
     * @param deviceId 音频播放设备 ID，可通过 enumerateAudioPlaybackDevices{@link #EnumerateAudioPlaybackDevices} 获取。
     * @return  方法调用结果
     * + 0：方法调用成功
     * + <0：方法调用失败<br>
     */
    setAudioPlaybackDevice(deviceId) {
        return this.instance.SetAudioPlaybackDevice(deviceId);
    }
    /** {zh}
     * @type api
     * @region 音频设备管理
     * @brief 设置音频采集设备。
     * @param deviceId 音频采集设备 ID，可通过 enumerateAudioCaptureDevices{@link #EnumerateAudioCaptureDevices} 获取。
     * @return  方法调用结果
     * + 0：方法调用成功
     * + <0：方法调用失败<br>
     */
    setAudioCaptureDevice(deviceId) {
        return this.instance.SetAudioCaptureDevice(deviceId);
    }
    /** {zh}
     * @type api
     * @region 音频设备管理
     * @brief 获取当前音频播放设备 ID。
     * @param device_id 音频播放设备 ID
     * @return  当前音频播放设备 ID
     */
    getAudioPlaybackDevice() {
        return this.instance.GetAudioPlaybackDevice();
    }
    /** {zh}
     * @type api
     * @region 音频设备管理
     * @brief 获取当前音频采集设备 ID。
     * @return 当前音频采集设备 ID
     */
    getAudioCaptureDevice() {
        return this.instance.GetAudioCaptureDevice();
    }
    /** {zh}
     * @type api
     * @region 音频设备管理
     * @brief 启动音频播放设备测试。  <br>该方法测试播放设备是否能正常工作。SDK 播放指定的音频文件，测试者如果能听到声音，说明播放设备能正常工作。
     * @param test_audio_file_path 音频文件的绝对路径，路径字符串使用 UTF-8 编码格式，支持以下音频格式: mp3，aac，m4a，3gp，wav。
     * @return  方法调用结果  <br>
     * + 0：方法调用成功  <br>
     * + <0：方法调用失败<br> <br>
     * @notes
     * + 该方法必须在 JoinRoom{@link #JoinRoom} 前调用，且不可与其它音频设备测试功能同时应用。  <br>
     * + 你需调用 StopAudioPlaybackDeviceTest{@link #IAudioDeviceManager#StopAudioPlaybackDeviceTest} 停止测试。  <br>
     */
    startAudioPlaybackDeviceTest(test_audio_file_path) {
        return this.instance.StartAudioPlaybackDeviceTest(test_audio_file_path);
    }
    /** {zh}
      * @type api
      * @region 音频设备管理
      * @brief 停止音频播放设备测试。
      * @return  方法调用结果  <br>
      * + 0：方法调用成功  <br>
      * + <0：方法调用失败<br> <br>
      * @notes  调用 StartAudioPlaybackDeviceTest{@link #IAudioDeviceManager#StartAudioPlaybackDeviceTest} 后，需调用本方法停止测试。
      */
    stopAudioPlaybackDeviceTest() {
        return this.instance.StopAudioPlaybackDeviceTest();
    }
    /** {zh}
     * @type api
     * @region 音频设备管理
     * @brief 启动音频采集设备测试。 该方法测试音频采集设备是否能正常工作。启动测试后，会收到 OnAudioVolumeIndication{@link 85533#OnAudioVolumeIndication} 回调上报的音量信息。
     * @param indication_interval OnAudioVolumeIndication{@link 85533#OnAudioVolumeIndication} 回调的时间间隔，单位为毫秒。建议设置到大于 200 毫秒。最小不得少于 10 毫秒。小于10 毫秒行为未定义。
     * @return  方法调用结果  <br>
     * + 0：方法调用成功  <br>
     * + <0：方法调用失败<br> <br>
     * @notes
     * + 该方法必须在 joinRoom{@link #JoinRoom} 前调用，且不可与其它音频设备测试功能同时应用。  <br>
     * + 你需调用 stopAudioCaptureDeviceTest{@link #IAudioDeviceManager#StopAudioCaptureDeviceTest} 停止测试。  <br>
     */
    startAudioCaptureDeviceTest(indication_interval) {
        return this.instance.StartAudioCaptureDeviceTest(indication_interval);
    }
    /** {zh}
     * @type api
     * @region 音频设备管理
     * @brief 停止音频采集设备测试。
     * @return  方法调用结果  <br>
     * + 0：方法调用成功  <br>
     * + <0：方法调用失败<br> <br>
     * @notes  调用 startAudioCaptureDeviceTest{@link #IAudioDeviceManager#StartAudioCaptureDeviceTest} 后，需调用本方法停止测试。
     */
    stopAudioCaptureDeviceTest() {
        return this.instance.StopAudioCaptureDeviceTest();
    }
    /** {zh}
     * @type api
     * @region 音频设备管理
     * @brief 设置当前音频播放设备音量
     * @param volume 音频播放设备音量，取值范围为 [0,255], 超出此范围设置无效。
     * @return  方法调用结果
     * + 0：方法调用成功
     * + <0：方法调用失败<br>
     */
    setAudioPlaybackDeviceVolume(volume) {
        return this.instance.SetAudioPlaybackDeviceVolume(volume);
    }
    /** {zh}
     * @type api
     * @region 音频设备管理
     * @brief 获取当前音频播放设备音量
     * @return  方法调用结果
     * + 0：方法调用成功
     * + <0：方法调用失败<br>
     */
    getAudioPlaybackDeviceVolume() {
        return this.instance.GetAudioPlaybackDeviceVolume();
    }
    /** {zh}
     * @type api
     * @region 音频设备管理
     * @brief 设置当前音频采集设备音量
     * @param volume 音频采集设备音量，取值范围为 [0,255], 超出此范围设置无效。
     * @return  方法调用结果
     * + 0：方法调用成功
     * + <0：方法调用失败<br>
     */
    setAudioCaptureDeviceVolume(volume) {
        return this.instance.SetAudioCaptureDeviceVolume(volume);
    }
    /** {zh}
    * @type api
    * @region 音频设备管理
    * @brief 获取当前音频采集设备音量
    * @return  方法调用结果
    * + 0：方法调用成功
    * + <0：方法调用失败<br>
    */
    getAudioCaptureDeviceVolume() {
        return this.instance.GetAudioCaptureDeviceVolume();
    }
    /** {zh}
     * @type api
     * @region 音频设备管理
     * @brief 开始音频设备回路测试。 <br> 该方法测试音频采集设备和音频播放设备是否能正常工作。一旦测试开始，音频采集设备会采集本地声音，并通过音频播放设备播放出来，同时用户 App 会收到 OnAudioVolumeIndication{@link 85533#OnAudioVolumeIndication} 回调上报的音量信息。
     * @param indication_interval OnAudioVolumeIndication{@link 85533#OnAudioVolumeIndication} 回调的时间间隔，单位为毫秒。建议设置到大于 200 毫秒。最小不得少于 10 毫秒。小于 10 毫秒行为未定义。
     * @return  方法调用结果
     * + 0：方法调用成功
     * + <0：方法调用失败<br>
     * @notes
     * + 该方法必须在 JoinRoom{@link #IRtcEngine#JoinRoom} 前调用。且不可与其它音频设备测试功能同时应用。
     * + 你需调用 StopAudioDeviceLoopbackTest{@link #IAudioDeviceManager#StopAudioDeviceLoopbackTest} 停止测试。
     * + 该方法仅在本地进行音频设备测试，不涉及网络连接。
     */
    startAudioDeviceLoopbackTest(indication_interval) {
        return this.instance.StartAudioDeviceLoopbackTest(indication_interval);
    }
    /** {zh}
     * @type api
     * @region 音频设备管理
     * @brief 停止音频设备回路测试。
     * @return  方法调用结果
     * + 0：方法调用成功
     * + <0：方法调用失败<br>
     * @notes 调用 StartAudioDeviceLoopbackTest{@link #IAudioDeviceManager#StartAudioDeviceLoopbackTest} 后，需调用本方法停止测试。
     */
    stopAudioDeviceLoopbackTest() {
        return this.instance.StopAudioDeviceLoopbackTest();
    }
    /** {zh}
     * @type api
     * @region 音频设备管理
     * @brief 尝试初始化音频播放设备，可检测出设备不存在、权限被拒绝/禁用等异常问题。
     * @param deviceId 设备索引号
     * @return 设备状态错误码
     * + 0: 设备检测结果正常
     * + -1: 接口状态不正确，例如在正常启动采集后再调用该接口进行检测
     * + -2: 采集设备无麦克风权限，尝试初始化设备失败
     * + -3: 设备不存在，当前没有设备或设备被移除时返回
     * + -4: 设备音频格式不支持
     * + -5: 其它原因错误<br>
     * @notes 1. 该接口需在进房前调用；
     *        2. 检测成功不代表设备一定可以启动成功，还可能因设备被其他应用进程独占，或 CPU/内存不足等原因导致启动失败。
     */
    initAudioPlaybackDeviceForTest(deviceId) {
        return this.instance.InitAudioPlaybackDeviceForTest(deviceId);
    }
    /** {zh}
     * @type api
     * @region 音频设备管理
     * @brief 尝试初始化音频播放设备，可检测出设备不存在、权限被拒绝/禁用等异常问题。
     * @param deviceId 设备索引号
     * @return 设备状态错误码
     * + 0: 设备检测结果正常
     * + -1: 接口状态不正确，例如在正常启动采集后再调用该接口进行检测
     * + -2: 采集设备无麦克风权限，尝试初始化设备失败
     * + -3: 设备不存在，当前没有设备或设备被移除时返回
     * + -4: 设备音频格式不支持
     * + -5: 其它原因错误<br>
     * @notes 1. 该接口需在进房前调用；
     *        2. 检测成功不代表设备一定可以启动成功，还可能因设备被其他应用进程独占，或 CPU/内存不足等原因导致启动失败。
     */
    initAudioCaptureDeviceForTest(deviceId) {
        return this.instance.InitAudioCaptureDeviceForTest(deviceId);
    }
    /** {zh}
     * @type api
     * @region 音频设备管理
     * @brief 设置当前音频播放设备静音状态，默认为非静音。
     * @param mute  <li>true：静音</li><li>false：非静音  </li>
     * @return  方法调用结果
     * + 0：方法调用成功
     * + <0：方法调用失败<br>
     */
    setAudioPlaybackDeviceMute(mute) {
        return this.instance.SetAudioPlaybackDeviceMute(mute);
    }
    /** {zh}
     * @type api
     * @region 音频设备管理
     * @brief 获取当前音频播放设备是否静音的信息。
     * @param mute  <li>true：静音</li><li>false：非静音  </li>
     * @return  方法调用结果
     * + `true`：方法调用成功
     * + `false`：方法调用失败<br>
     */
    getAudioPlaybackDeviceMute() {
        return this.instance.GetAudioPlaybackDeviceMute();
    }
    /** {zh}
       * @type api
       * @region 音频设备管理
       * @brief 设置当前音频采集设备静音状态，默认为非静音。
       * @param mute  <li>true：静音</li><li>false：非静音  </li>
       * @return  方法调用结果  <br>
       * + 0：方法调用成功  <br>
       * + <0：方法调用失败<br> <br>
       */
    setAudioCaptureDeviceMute(mute) {
        return this.instance.SetAudioCaptureDeviceMute(mute);
    }
    /** {zh}
     * @type api
      * @region 音频设备管理
      * @brief 获取当前音频采集设备是否静音的信息。
      * @return
      * + true：静音  <br>
      * + false：非静音  <br>
      */
    getAudioCaptureDeviceMute() {
        return this.instance.GetAudioCaptureDeviceMute();
    }
    /** {zh}
     * @type api
     * @region 音视频回退
     * @brief 设置发布的音视频流回退选项 。<br>你可以调用这个接口来设置网络情况不佳或设备性能不足时只发送小流，以保证通话质量。
     * @param option 本地发布的音视频流回退选项  <li>0：（默认）上行网络较弱或性能不佳时，不对音视频流作回退处理。  <li></li>>1：上行网络较弱或性能不佳时，只发送视频小流。</li>
     * @return
     * + 0: 方法调用成功
     * + <0: 方法调用失败<br>
     * @notes
     * + 这个方法只在设置了发送多个流的情况下有效。
     * + 你必须在进房前设置，进房后设置或更改设置无效。
     * + 设置回退选项后，本端发布的音视频流发生回退或从回退中恢复时，订阅该音视频流的客户端会收到 OnSimulcastSubscribeFallback{@link #OnSimulcastSubscribeFallback} 回调通知。
     * + 你可以调用 API 或者在服务端下发策略设置回退。当使用服务端下发配置实现时，下发配置优先级高于在客户端使用 API 设定的配置。
     */
    setPublishFallbackOption(option) {
        return this.instance.SetPublishFallbackOption(option);
    }
    /** {zh}
     * @type api
     * @region 音视频回退
     * @brief 设置订阅的音视频流回退选项。 <br>你可以通过调用该接口来设置网络情况不佳或性能不足时只订阅小流或音频流，以保证通话质量。
     * @param option 远端订阅流回退处理选项<li>`0`: 关闭订阅音视频流时的性能回退功能 </li><li>`1`: 只接收视频小流</li><li>`2`: 先尝试只接收视频小流；如果网络环境无法显示视频，则再回退到只接收远端订阅的音频流</li>
     * @return  方法调用结果
     * + 0：方法调用成功
     * + <0：方法调用失败<br>
     *  @notes
     * + 你必须在进房前设置，进房后设置或更改设置无效。
     * + 设置回退选项后，本端订阅的音视频流发生回退或从回退中恢复时,会收到 OnSimulcastSubscribeFallback{@link 85533#OnSimulcastSubscribeFallback} 回调通知。
     * + 设置回退选项后，本端订阅的视频流因为回退分辨率发生变化时,会收到 OnRemoteVideoSizeChanged{@link 85533#OnRemoteVideoSizeChanged} 回调通知。
     * + 你可以调用 API 或者在服务端下发策略设置回退。当使用服务端下发配置实现时，下发配置优先级高于在客户端使用 API 设定的配置。
     */
    setSubscribeFallbackOption(option) {
        return this.instance.SetSubscribeFallbackOption(option);
    }
    /** {zh}
     * @region 音视频回退
     * @brief 设置用户优先级
     * @param userId 远端用户的 ID
     * @param priority 远端用户的需求优先级，详见枚举类型 RemoteUserPriority{@link #RemoteUserPriority}
     * @return + 0: 方法调用成功
     * + <0: 方法调用失败<br>
     * @notes
     * + 1. 该方法与 setSubscribeFallbackOption{@link #SetSubscribeFallbackOption} 搭配使用。
     * + 2. 如果开启了订阅流回退选项，弱网或性能不足时会优先保证收到的高优先级用户的流的质量。
     * + 3. 该方法在进房前后都可以使用，可以修改远端用户的优先级。
     */
    setRemoteUserPriority(userId, priority) {
        return this.instance.SetRemoteUserPriority(userId, priority);
    }
    /** {zh}
     * @brief 在当前房间内手动开始发布本地音视频流
     * @return + 0: 方法调用成功
     * + <0: 方法调用失败<br>
     * @notes
     * + 如果你已经在用户进房时通过调用 [joinRoom](#joinroom) 选择了自动发布，则无需再调用本接口。<br>
     * + 调用 setUserVisibility{@link #setUserVisibility} 方法将自身设置为不可见后无法调用该方法，需将自身切换至可见后方可调用该方法发布音视频流。 <br>
     * + 同一用户，同一时间，只能在一个房间内发流。如果你需要发布屏幕共享流，调用 publishScreen{@link #publishScreen}。
     * + 用户调用此方法成功发布音视频流后，房间中的其他用户将会收到 OnStreamAdd{@link 85533#onStreamAdd} 回调通知。
     */
    publish() {
        return this.instance.Publish();
    }
    /** {zh}
     * @brief 在当前房间内停止发布本地音视频流。
     * @return + 0: 方法调用成功
     * + <0: 方法调用失败<br>
     * @notes
     * + 调用 publish{@link #publish} 手动发布音视频流后或在用户进房时设置为自动发布，都可以调用此接口停止发布。<br>
     * + 用户调用此方法停止发布音视频流后，房间中的其他用户将会收到 OnStreamRemove{@link 85533#onStreamRemove} 回调通知。
     */
    unpublish() {
        return this.instance.Unpublish();
    }
    /** {zh}
     * @region 多房间
     * @brief 订阅房间内指定的远端音视频流。  或更新已经订阅的流的属性、媒体类型等配置。
     * @param user_id 指定订阅的远端发布音视频流的用户 ID。
     * @param stream_type 流属性，用于指定订阅主流/屏幕流。<li>主流。包括：由摄像头/麦克风通过内部采集机制，采集到的视频/音频;通过自定义采集，采集到的视频/音频。</li><li>屏幕流。屏幕共享时共享的视频流，或来自声卡的本地播放音频流。</li>
     * @param media_type 媒体类型，用于指定订阅音/视频，参看 SubscribeMediaType{@link #SubscribeMediaType}。
     * @param subConfig 视频订阅配置
     * @return + 0: 方法调用成功
     * + <0: 方法调用失败<br>
     * @notes
     * + 无论是自动订阅还是手动订阅模式，你都可以调用此方法按需订阅房间中的音视频流。
     * + 你可以通过 OnStreamAdd{@link 85533#OnStreamAdd} 和 OnStreamRemove{@link 85533#OnStreamRemove} 两个回调获取当前房间你的音视频流信息，并调用本方法按需订阅流或修改订阅配置。
     * + 若订阅失败，你会收到 OnRoomError{@link 85533#OnRoomError} 回调通知，具体失败原因参看 ErrorCode{@link #ErrorCode}。
     * + 若调用 pauseAllSubscribedStream{@link #PauseAllSubscribedStream} 暂停接收远端音视频流，此时仍可使用该方法对暂停接收的流进行设置，你会在调用 resumeAllSubscribedStream{@link #ResumeAllSubscribedStream} 恢复接收流后收到修改设置后的流。
     */
    subscribeUserStream(user_id, stream_type, media_type, subConfig) {
        // set default value
        if (isNULL(subConfig.video_index)) {
            subConfig.video_index = 0;
        }
        if (isNULL(subConfig.priority)) {
            subConfig.priority = 0;
        }
        return this.instance.SubscribeUserStream(user_id, stream_type, media_type, subConfig);
    }
    /** {zh}
     * @brief 停止订阅指定的房间内远端音视频流。无论自动订阅还是手动订阅模式，你都可以调用此方法取消已订阅的音视频流。
     * @param userId 指定需要取消订阅的远端音视频流的所属的用户的 ID 。
     * @param isScreen 是否为屏幕共享流。
     * @return + 0: 方法调用成功
     * + <0: 方法调用失败<br>
     * @notes  无论是否订阅了指定的远端音视频流，都可以调用此方法。`userId` 无效或未订阅时，SDK 不会做任何处理，没有负面影响。
     * */
    unsubscribe(userId, isScreen) {
        return this.instance.Unsubscribe(userId, isScreen);
    }
    /** {zh}
     * @region 流消息
     * @brief 给房间内指定的用户发送消息，返回这次发送消息的编号。  <br>调用该函数后会收到一次 userMessageSendResult 回调，告知发送结果。
     * @param userId 指定用户 ID 。
     * @param message 发送的消息内容。
     * @return 这次发送消息的编号，从 1 开始递增。<br>
     * @notes
     * + 调用该函数后会收到一次 userMessageSendResult 回调；
     * + 若消息发送成功，则 uid 所指定的用户会收到 userMessageReceived 回调。
     */
    sendUserMessage(userId, message) {
        return this.instance.SendUserMessage(userId, message);
    }
    /** {zh}
       * @type api
       * @region 多房间
       * @brief 给房间内指定的用户发送二进制消息（P2P）
       * @param uid  消息接收用户的 ID
       * @param length 二进制字符串的长度
       * @param message 二进制消息的内容。消息不超过 46KB。
       * @return 这次发送消息的编号，从 1 开始递增。<br>
       * @notes
       * + 在发送房间内二进制消息前，必须先调用 joinRoom{@link #JoinRoom} 加入房间。  <br>
       * + 调用该函数后会收到一次 OnUserMessageSendResult{@link 85533#OnUserMessageSendResult} 回调，通知消息发送方发送成功或失败；  <br>
       * + 若二进制消息发送成功，则 uid 所指定的用户会收到 OnUserBinaryMessageReceived{@link 85533#OnUserBinaryMessageReceived} 回调。
       */
    sendUserBinaryMessage(uid, length, message) {
        return this.instance.SendUserBinaryMessage(uid, length, message);
    }
    ;
    /** {zh}
       * @type api
       * @region 音频数据回调
       * @brief 设置本地麦克风录制的音频数据回调参数
       * @param sample_rate 音频采样率（单位HZ），可以设置的值有 8000，16000，32000，44100，48000
       * @param channels 音频通道数，支持单声道（1）和双声道（2）
       * @return + 0: 方法调用成功
       * + <0: 方法调用失败<br>
       * @notes 使用本方法设置参数后可以在 OnRecordAudioFrame{@link 85533#OnRecordAudioFrame} 收到数据
       */
    setRecordingAudioFrameParameters(sample_rate, channels) {
        return this.instance.SetRecordingAudioFrameParameters(sample_rate, channels);
    }
    /** {zh}
     * @type api
     * @region 音频数据回调
     * @brief 设置远端所有用户音频数据混音后的音频数据回调参数
     * @param sample_rate 音频采样率（单位HZ），可以设置的值有 8000，16000，32000，44100，48000
     * @param channels 音频通道数，支持单声道（1）和双声道（2）
     * @return + 0: 方法调用成功
     * + <0: 方法调用失败<br>
     * @notes 使用本方法设置参数后可以在 OnPlaybackAudioFrame{@link 85533#OnPlaybackAudioFrame} 收到数据
     */
    setPlaybackAudioFrameParameters(sample_rate, channels) {
        return this.instance.SetPlaybackAudioFrameParameters(sample_rate, channels);
    }
    /** {zh}
     * @type api
     * @region 音频数据回调
     * @brief 设置本地麦克风录制音频数据和远端所有用户音频数据混音后的音频数据回调参数
     * @param sample_rate 音频采样率（单位HZ），可以设置的值有 8000，16000，32000，44100，48000
     * @param channels 音频通道数，支持单声道（1）和双声道（2）
     * @return + 0: 方法调用成功
     * + <0: 方法调用失败<br>
     * @notes 使用本方法设置参数后可以在 OnMixedAudioFrame{@link 85533#OnMixedAudioFrame} 收到数据
     */
    setMixedAudioFrameParameters(sample_rate, channels) {
        return this.instance.SetMixedAudioFrameParameters(sample_rate, channels);
    }
    /** {zh}
      * @type api
      * @region 本地录制
      * @brief 该方法将通话过程中的音视频数据录制到本地的文件中。
      * @param type 流属性，指定录制主流还是屏幕流<li>主流。包括：由摄像头/麦克风通过内部采集机制，采集到的视频/音频;通过自定义采集，采集到的视频/音频。</li><li>屏幕流。屏幕共享时共享的视频流，或来自声卡的本地播放音频流。</li>
      * @param config 本地录制参数配置
      * @return
      * + 0: 正常
      * + -1: 参数设置异常
      * + -2: 当前版本 SDK 不支持该特性，请联系技术支持人员<br>
      * @notes
      * + 调用该方法后，你会收到 OnRecordingStateUpdate{@link 85533#OnRecordingStateUpdate} 回调。  <br>
      * + 如果录制正常，系统每秒钟会通过 OnRecordingProgressUpdate{@link 85533#OnRecordingProgressUpdate} 回调通知录制进度。
      */
    startFileRecording(type, config) {
        return this.instance.StartFileRecording(type, config);
    }
    /** {zh}
       * @type api
       * @region 本地录制
       * @brief 停止本地录制
       * @param type 流属性，指定停止主流或者屏幕流录制<li>主流。包括：由摄像头/麦克风通过内部采集机制，采集到的视频/音频;通过自定义采集，采集到的视频/音频。</li><li>屏幕流。屏幕共享时共享的视频流，或来自声卡的本地播放音频流。</li>
       * @return + 0: 方法调用成功
       * + <0: 方法调用失败<br>
      * @notes
       * + 调用 startFileRecording{@link #StartFileRecording} 开启本地录制后，你必须调用该方法停止录制。  <br>
       * + 调用该方法后，你会收到 OnRecordingStateUpdate{@link 85533#OnRecordingStateUpdate} 回调提示录制结果。
       */
    stopFileRecording(type) {
        return this.instance.StopFileRecording(type);
    }
    /** {zh}
      * @type api
      * @region 语音识别服务
      * @brief 开启自动语音识别服务。该方法将识别后的用户语音转化成文字，并通过 OnMessage{@link 85533#OnMessage} 事件回调给用户。
      * @param asr_config 校验信息
      * @return + 0: 方法调用成功
      * + <0: 方法调用失败<br>
    */
    startASR(asr_config) {
        return this.instance.StartASR(asr_config);
    }
    /** {zh}
     * @type api
     * @region 语音识别服务
     * @brief 关闭语音识别服务
     * @return + 0: 方法调用成功
     * + <0: 方法调用失败<br>
     */
    stopASR() {
        return this.instance.StopASR();
    }
    /** {zh}
     * @type api
     * @region 流消息
     * @brief 给房间内所有的用户发送消息。
     * @param message 用户发送的广播消息
     * @return + 0: 方法调用成功
     * + <0: 方法调用失败<br>
     * @notes
     * + 调用该函数后会收到一次 roomMessageSendResult 回调；
     * + 同一房间内的其他用户会收到 roomMessageReceived 回调。
     */
    sendRoomMessage(message) {
        return this.instance.SendRoomMessage(message);
    }
    /** {zh}
       * @type api
       * @region 多房间
       * @brief 给房间内的所有其他用户发送广播消息。
       * @param size  发送的二进制消息长度
       * @param message  用户发送的二进制广播消息，每条消息不超过 46KB。
       * @return + >0: 方法调用成功
       * + <0: 方法调用失败<br>
       * @notes
       * + 在发送房间内二进制消息前，必须先调用 joinRoom{@link #JoinRoom} 加入房间。  <br>
       * + 调用该函数后，会收到一次 OnRoomMessageSendResult{@link 85533#OnRoomMessageSendResult} 回调。  <br>
       * + 同一房间内的其他用户会收到 OnRoomBinaryMessageReceived{@link 85533#OnRoomBinaryMessageReceived} 回调。
       */
    sendRoomBinaryMessage(size, message) {
        return this.instance.SendRoomBinaryMessage(size, message);
    }
    /** {zh}
     * @type api
     * @region 实时消息通信
     * @brief 必须先登录注册一个 uid，才能发送房间外消息和向业务服务器发送消息
     * @param token 动态密钥  <br>用户登录必须携带的 Token，用于鉴权验证。  <br>本 Token 与加入房间时必须携带的 Token 不同。测试时可使用控制台生成临时 Token，正式上线需要使用密钥 SDK 在你的服务端生成并下发 Token。
     * @param uid 用户 ID  <br>用户 ID 在 appid 的维度下是唯一的。
     * @return + 0: 方法调用成功
     * + <0: 方法调用失败<br>
     * @notes
     * + 在调用本接口登录后，如果想要登出，需要调用 Logout{@link #Logout}。  <br>
     * + 本地用户调用此方法登录后，会收到 OnLoginResult{@link 85533#OnLoginResult} 回调通知登录结果，远端用户不会收到通知。
     */
    login(token, uid) {
        return this.instance.Login(token, uid);
    }
    /** {zh}
     * @type api
     * @region 实时消息通信
     * @brief 调用本接口登出后，无法调用房间外消息以及端到服务器消息相关的方法或收到相关回调。
     * @return + 0: 方法调用成功
     * + <0: 方法调用失败<br>
     * @notes
     * + 调用本接口登出前，必须先调用 login{@link #Login} 登录。  <br>
     * + 本地用户调用此方法登出后，会收到 OnLogout{@link 85533#OnLogout} 回调通知结果，远端用户不会收到通知。
     */
    logout() {
        return this.instance.Logout();
    }
    /** {zh}
     * @type api
     * @region 实时消息通信
     * @brief 更新用户用于登录的 Token  <br>Token 有一定的有效期，当 Token 过期时，需调用此方法更新登录的 Token 信息。  <br>调用 login{@link #Login} 方法登录时，如果使用了过期的 Token 将导致登录失败，并会收到 OnLoginResult{@link 85533#OnLoginResult} 回调通知，错误码为 kLoginErrorCodeInvalidToken。此时需要重新获取 Token，并调用此方法更新 Token。
     * @param token  <br>
     *        更新的动态密钥
     * @return + 0: 方法调用成功
     * + <0: 方法调用失败<br>
     * @notes
     * + 如果 Token 无效导致登录失败，则调用此方法更新 Token 后，SDK 会自动重新登录，而用户不需要自己调用 login{@link #Login} 方法。  <br>
     * + Token 过期时，如果已经成功登录，则不会受到影响。Token 过期的错误会在下一次使用过期 Token 登录时，或因本地网络状况不佳导致断网重新登录时通知给用户。
     */
    updateLoginToken(token) {
        return this.instance.UpdateLoginToken(token);
    }
    /** {zh}
       * @type api
       * @region 实时消息通信
       * @brief 设置业务服务器参数  <br>客户端调用 sendServerMessage{@link #SendServerMessage} 或 sendServerBinaryMessage{@link #SendServerBinaryMessage} 发送消息给业务服务器之前，必须设置有效签名和业务服务器地址。
       * @param signature 动态签名  <br>业务服务器会使用该签名对请求进行鉴权验证。
       * @param url 业务服务器的地址
       * @return + 0: 方法调用成功
       * + <0: 方法调用失败<br>
       * @notes
       * + 用户必须调用 login{@link #Login} 登录后，才能调用本接口。  <br>
       * + 调用本接口后，SDK 会使用 OnServerParamsSetResult{@link 85533#OnServerParamsSetResult} 返回相应结果。
       */
    setServerParams(signature, url) {
        return this.instance.SetServerParams(signature, url);
    }
    /** {zh}
       * @type api
       * @region 实时消息通信
       * @brief 查询对端用户或本端用户的登录状态
       * @param peer_user_id 需要查询的用户 ID
       * @return + 0: 方法调用成功
       * + <0: 方法调用失败<br>
       * @notes
       * + 必须调用 login{@link #Login} 登录后，才能调用本接口。  <br>
       * + 调用本接口后，SDK 会使用 OnGetPeerOnlineStatus{@link 85533#OnGetPeerOnlineStatus} 回调通知查询结果。  <br>
       * + 在发送房间外消息之前，用户可以通过本接口了解对端用户是否登录，从而决定是否发送消息。也可以通过本接口查询自己查看自己的登录状态。
       */
    getPeerOnlineStatus(peer_user_id) {
        return this.instance.GetPeerOnlineStatus(peer_user_id);
    }
    /** {zh}
       * @type api
       * @region 实时消息通信
       * @brief 给房间外指定的用户发送文本消息（P2P）
       * @param uid 消息接收用户的 ID
       * @param message 发送的文本消息内容，消息不超过 62KB。
       * @return
       * + \>0：发送成功，返回这次发送消息的编号，从 1 开始递增
       * + -1：发送失败，RtcEngine 实例未创建
       * + -2：发送失败，uid 为空<br>
       * @notes
       * + 在发送房间外文本消息前，必须先调用 login{@link #Login} 完成登录。  <br>
       * + 用户调用本接口发送文本信息后，会收到一次 OnUserMessageSendResultOutsideRoom{@link 85533#OnUserMessageSendResultOutsideRoom} 回调，得知消息是否成功发送。  <br>
       * + 若文本消息发送成功，则 uid 所指定的用户会通过 OnUserMessageReceivedOutsideRoom{@link 85533#OnUserMessageReceivedOutsideRoom} 回调收到该消息。
       */
    SendUserMessageOutsideRoom(uid, message) {
        return this.instance.SendUserMessageOutsideRoom(uid, message);
    }
    /** {zh}
     * @type api
     * @region 错误码
     * @brief 获取错误码的描述
     * @param code 需要获取描述的错误码
     * @return 错误码的描述<br>
     * @notes  该接口是通用功能，调用时不需要依赖引擎对象。
     */
    getErrorDescription(code) {
        return this.instance.GetErrorDescription(code);
    }
    /** {zh}
       * @type api
       * @region 实时消息通信
       * @brief 给房间外指定的用户发送二进制消息（P2P）
       * @param uid 消息接收用户的 ID
       * @param length 二进制字符串的长度
       * @param message 发送的二进制消息内容，每条消息不超过 46KB。
       * @return
       * + >0：发送成功，返回这次发送消息的编号，从 1 开始递增  <br>
       * + -1：发送失败，RtcEngine 实例未创建  <br>
       * + -2：发送失败，uid 为空<br>
       * @notes
       * + 在发送房间外二进制消息前，必须先调用 login{@link #Login} 完成登录。  <br>
       * + 用户调用本接口发送二进制消息后，会收到一次 OnUserMessageSendResultOutsideRoom{@link 85533#OnUserMessageSendResultOutsideRoom} 回调，通知消息是否发送成功。  <br>
       * + 若二进制消息发送成功，则 uid 所指定的用户会通过 OnUserBinaryMessageReceivedOutsideRoom{@link 85533#OnUserBinaryMessageReceivedOutsideRoom} 回调收到该条消息。
       */
    sendUserBinaryMessageOutsideRoom(uid, length, message) {
        return this.instance.SendUserBinaryMessageOutsideRoom(uid, length, message);
    }
    /** {zh}
     * @type api
     * @region 实时消息通信
     * @brief 客户端给业务服务器发送文本消息（P2Server）
     * @param message 发送的文本消息内容，消息不超过 62KB。
     * @return
     * + \>0：发送成功，返回这次发送消息的编号，从 1 开始递增
     * + -1：发送失败，RtcEngine 实例未创建<br>
     * @notes
     * + 在向业务服务器发送文本消息前，必须先调用 Login{@link #Login} 完成登录，随后调用 SetServerParams{@link #SetServerParams} 设置业务服务器。  <br>
     * + 调用本接口后，会收到一次 OnServerMessageSendResult{@link 85533#OnServerMessageSendResult} 回调，通知消息发送方是否发送成功。  <br>
     * + 若文本消息发送成功，则之前调用 SetServerParams{@link #SetServerParams} 设置的业务服务器会收到该条消息。
     */
    sendServerMessage(message) {
        return this.instance.SendServerMessage(message);
    }
    /** {zh}
     * @type api
     * @region 实时消息通信
     * @brief 客户端给业务服务器发送二进制消息（P2Server）
     * @param length 二进制字符串的长度
     * @param message 发送的二进制消息内容，消息不超过 46KB。
     * @return
     * + \>0：发送成功，返回这次发送消息的编号，从 1 开始递增  <br>
     * + -1：发送失败，RtcEngine 实例未创建<br>
     * @notes
     * + 在向业务服务器发送二进制消息前，必须先调用 login{@link #Login} 完成登录，随后调用 setServerParams{@link #SetServerParams} 设置业务服务器。  <br>
     * + 调用本接口后，会收到一次 OnServerMessageSendResult{@link 85533#OnServerMessageSendResult} 回调，通知消息发送方发送成功或失败。  <br>
     * + 若二进制消息发送成功，则之前调用 setServerParams{@link #SetServerParams} 设置的业务服务器会收到该条消息。
     */
    sendServerBinaryMessage(length, message) {
        return this.instance.SendServerBinaryMessage(length, message);
    }
    /** {zh}
     * @hidden
     * @brief 关闭背景
     * @return + 0: 方法调用成功
     * + <0: 方法调用失败
     */
    disableBackground() {
        return this.instance.DisableBackground();
    }
    /** {zh}
     * @brief 设置和开启虚拟背景功能，
     * @param effectNodePaths 虚拟背景素材包地址。
     * @param source_path 背景图片本地路径。背景图片的本地地址，例如，file://xxx 或 Asset 资源路径 asset://xxx。 支持JPG、PNG。当背景图片分辨率超过 1080P 时，图片会被等比缩放。如果背景图片和视频分辨率不一致，图片会被裁剪缩放，不留黑边。
     * @return + 0: 调用成功  <br>
     * + 1000: 未集成 CV SDK  <br>
     * + 1001: 本版本不支持 CV 功能  <br>
     * + <0: 调用失败，具体错误码请参考 [CV SDK 文档](https://www.volcengine.com/docs/6705/102042)。<br>
     * @notes + 使用背景分割或视频特效的功能前，你必须自行实现获取智能美化特效产品在线许可证的业务逻辑，参考 [在线授权说明](https://www.volcengine.com/docs/6705/102012)。  <br>
     * + 获取许可证后，建议调用 checkLicense{@link #CheckLicense} 确认许可证有效，再开始使用背景分割或视频特效功能。  <br>
     * + 使用不同的背景图片分别调用本接口，将更新虚拟背景图片。
     * + 开启虚拟背景功能后，如需关闭，再次调用本接口，并给两个参数赋 null 值。
     */
    setBackgroundSticker(effectNodePaths, source_path) {
        return this.instance.SetBackgroundSticker(effectNodePaths, source_path);
    }
    /** {zh}
     * @type api
     * @region 视频特效
     * @brief 视频特效许可证检查
     * @param licensePath 许可证文件绝对路径
     * @return
     * + 0: 调用成功  <br>
     * + 1000: 未集成 CV SDK  <br>
     * + 1001: 本版本不支持 CV 功能  <br>
     * + <0: 调用失败，具体错误码请参考 [CV SDK 文档](https://www.volcengine.com/docs/6705/102042)。<br>
     * @notes 开始使用视频特效前，你必须先调用这个方法进行许可证验证
     */
    checkLicense(licensePath) {
        return this.instance.CheckLicense(licensePath);
    }
    /** {zh}
     * @type api
     * @region 视频特效
     * @brief 从 CV SDK 获取授权消息，用于获取在线许可证。
     * @return 授权消息字符串<br>
     * @notes
     * + 使用背景分割或视频特效的功能前，你必须自行实现获取智能美化特效产品在线许可证的业务逻辑，参考 [在线授权说明](https://www.volcengine.com/docs/6705/102012)。  <br>
     * + 获取许可证后，建议调用 checkLicense{@link #CheckLicense} 确认许可证有效，再开始使用背景分割或视频特效功能。  <br>
     */
    getAuthMessage() {
        return this.instance.GetAuthMessage();
    }
    /** {zh}
     * @type api
     * @region 视频特效
     * @brief 开启关闭视频特效
     * @param enabled 是否开启特效，true: 开启，false: 关闭
     * @return
     * + 0: 调用成功
     * + 1000: 未集成 CV SDK
     * + <0: 调用失败，具体错误码含义请参考 CV SDK 文档<br>
     * @notes 在调用 checkLicense{@link #CheckLicense}和 setAlgoModelPath{@link #SetAlgoModelPath}后调用此方法
     */
    enableEffect(enabled) {
        return this.instance.EnableEffect(enabled);
    }
    /** {zh}
       * @region 视频特效
       * @brief 设置视频特效算法模型路径
       * @param modelPath 模型路径
       * @return
       * + 0：成功
       * + !0：失败<br>
       */
    setAlgoModelPath(modelPath) {
        return this.instance.SetAlgoModelPath(modelPath);
    }
    /** {zh}
     * @type api
     * @region 视频特效
     * @brief 设置视频特效素材包，支持同时设置多个素材包
     * @param effectNodePaths  特效素材包路径数组
     * @return  <br>
     * + 0: 调用成功  <br>
     * + 1000: 未集成 CV SDK  <br>
     * + 1001: 本 RTC 版本不支持 CV 功能  <br>
     * + <0: 调用失败，具体错误码，请参考 [CV SDK 文档](https://www.volcengine.com/docs/6705/102042)。
     */
    setEffectNodes(effectNodePaths) {
        return this.instance.SetEffectNodes(effectNodePaths);
    }
    /** {zh}
     * @type api
     * @region 视频特效
     * @brief 设置特效强度
     * @param nodePath 特效素材包路径
     * @param nodeKey 需要设置的素材 key 名称，取值请参考 [素材 key 对应说明](https://www.volcengine.com/docs/6705/102040)。
     * @param nodeValue 需要设置的强度值 取值范围 [0,1]，超出范围时设置无效。
     * @return  <br>
     * + 0: 调用成功  <br>
     * + 1000: 未集成 CV SDK  <br>
     * + 1001: 本 RTC 版本不支持 CV 功能  <br>
     * + <0: 调用失败，具体错误码，请参考 [CV SDK 文档](https://www.volcengine.com/docs/6705/102042)。
     */
    updateNode(nodePath, nodeKey, nodeValue) {
        return this.instance.UpdateNode(nodePath, nodeKey, nodeValue);
    }
    /** {zh}
     * @type api
     * @region 视频特效
     * @brief 设置颜色滤镜
     * @param resPath 滤镜资源包绝对路径。
     * @return  <br>
     * + 0: 调用成功  <br>
     * + 1000: 未集成 CV SDK  <br>
     * + 1001: 本 RTC 版本不支持 CV 功能  <br>
     * + <0: 调用失败，具体错误码，请参考 [CV SDK 文档](https://www.volcengine.com/docs/6705/102042)。
     */
    setColorFilter(resPath) {
        return this.instance.SetColorFilter(resPath);
    }
    /** {zh}
     * @type api
     * @region 视频特效
     * @brief 设置已启用颜色滤镜的强度
     * @param intensity 滤镜强度。取值范围 [0,1]，超出范围时设置无效。
     * @return  <br>
     * + 0: 调用成功  <br>
     * + 1000: 未集成 CV SDK  <br>
     * + 1001: 本 RTC 版本不支持 CV 功能  <br>
     * + <0: 调用失败，具体错误码，请参考 [CV SDK 文档](https://www.volcengine.com/docs/6705/102042)。
     */
    setColorFilterIntensity(intensity) {
        return this.instance.SetColorFilterIntensity(intensity);
    }
    /** {zh}
     * @type api
     * @region 视频管理
     * @brief 在视频通信时，通过视频帧发送 SEI 数据。
     * @param stream_index 媒体流类型<li>主流。包括：由摄像头/麦克风通过内部采集机制，采集到的视频/音频;通过自定义采集，采集到的视频/音频。</li><li>屏幕流。屏幕共享时共享的视频流，或来自声卡的本地播放音频流。</li>
     * @param message SEI 消息。长度不超过 4 kB。<br>
     * @param repeat_count 消息发送重复次数。取值范围是 [0, 30]。<br>调用此接口后，SEI 数据会添加到当前视频帧开始的连续 `repeatCount` 个视频帧中。
     * @return
     * + \>=0: 将被添加到视频帧中的 SEI 的数量  <br>
     * + < 0: 发送失败<br>
     * @notes
     * + 如果调用此接口之后的 2s 内，没有可带 SEI 的视频帧（比如没有开启视频采集和传输），那么，SEI 数据不会被加进视频帧中。
     * + 消息发送成功后，远端会收到 OnSEIMessageReceived{@link 85533#OnSEIMessageReceived} 回调。
     */
    sendSEIMessage(stream_index, message, repeat_count) {
        return this.instance.SendSEIMessage(stream_index, message, repeat_count);
    }
    /** {zh}
     * @type api
     * @region 屏幕共享
     * @brief 在屏幕共享时，设置屏幕音频流和麦克风采集到的音频流的混流方式
     * @param index 混流方式 <li> `0`: 将屏幕音频流和麦克风采集到的音频流混流 </li><li> `1`: 将屏幕音频流和麦克风采集到的音频流分为两路音频流</li>
     * @notes 你应该在 publishScreen{@link #PublishScreen} 之前，调用此方法。否则，你将收到 OnWarning{@link 85533#OnWarning} `的报错：kWarningCodeSetScreenAudioStreamIndexFailed`
     */
    setScreenAudioStreamIndex(index) {
        return this.instance.SetScreenAudioStreamIndex(index);
    }
    /** {zh}
     * @type api
     * @region 屏幕共享
     * @brief 在屏幕共享时，开始使用 RTC SDK 内部采集方式，采集屏幕音频
     * @notes
     * + 采集后，你还需要调用 publishScreen{@link #PublishScreen} 将采集到的屏幕音频推送到远端。<br>
     * + 要关闭屏幕音频内部采集，调用 stopScreenAudioCapture{@link #StopScreenAudioCapture}。
     */
    startScreenAudioCapture() {
        return this.instance.StartScreenAudioCapture();
    }
    /** {zh}
      * @type api
      * @region 屏幕共享
      * @brief 在屏幕共享时，停止使用 RTC SDK 内部采集方式，采集屏幕音频。
      * @notes 要开始屏幕音频内部采集，调用 startScreenAudioCapture{@link #StartScreenAudioCapture}。
      */
    stopScreenAudioCapture() {
        return this.instance.StopScreenAudioCapture();
    }
    /** {zh}
     * @type api
     * @region 引擎管理
     * @brief 本次通话质量打分评价
     * @param data 上报的数据。JSON 格式，必须包含以下 4 个字段: <li>types: 预设的问题类型集合，可多选。具体的类型参考 [ProblemFeedbackOption](../70098/#problemfeedbackoption) </li><li>problem_desc: 预设问题以外的其他问题的具体描述 </li><li>os_version: 系统版本  </li><li>network_type: 网络类型：包括 WiFi, 2g, 3g, 4g, 5g。如果是台式机，填写 pc 。</li>
     * @return
     * +  0: 上报成功  <br>
     * + -1: 上报失败，还没加入过房间  <br>
     * + -2: 上报失败，传入 JSON 解析失败<br> <br>
     * + -3: 上报失败，传入 JSON 字段缺失  <br>
     * @notes + 如果用户上报时在房间内，那么问题会定位到用户当前所在的一个或多个房间；
     * + 如果用户上报时不在房间内，那么问题会定位到引擎此前退出的房间。
     */
    feedback(data) {
        return this.instance.Feedback(data);
    }
    /** {zh}
       * @private
       * @type api
       * @region 引擎管理
       * @brief 设置运行时的参数
       * @param json_string  json 序列化之后的字符串，用以覆盖全局参数。
       */
    setRuntimeParameters(json_string) {
        return this.instance.SetRuntimeParameters(json_string);
    }
    /** {zh}
       * @region 加密
       * @brief 设置传输时使用内置加密的方式
       * @param encrypt_type 加密算法 <li>`0`: 不使用内置加密</li><li>`1`:AES-128-CBC 加密算法</li><li>`2`:AES-256-CBC 加密算法</li><li>`3`:AES-128-ECB 加密算法</li><li>`4`:AES-256-ECB 加密算法</li>
       * @param key 加密密钥，长度限制为 36 位，超出部分将会被截断
       * @notes 该方法必须在进房之前调用，可重复调用，以最后调用的参数作为生效参数。  <br>
     */
    setEncryptInfo(encrypt_type, key) {
        return this.instance.SetEncryptInfo(encrypt_type, key);
    }
    /** {zh}
     * @brief 开启转推直播，并设置合流的视频视图布局和音频属性。
     * @param param 转推直播配置参数
     * @return
     * + 0：成功
     * + !0：失败<br>
     * @notes <br>
     *        1.只有房间模式为直播模式的用户才能调用此方法。  <br>
     *        2.调用该方法后，关于启动结果和推流过程中的错误，会收到 OnLiveTranscodingResult{@link #OnLiveTranscodingResult} 回调。
     *        3.调用 stopLiveTranscoding{@link #stopLiveTranscoding} 停止转推直播。
     */
    startLiveTranscoding(param) {
        if (!param.audioParam) {
            param.audioParam = {
                i32_sample_rate: 48000,
                i32_channel_num: 2,
                i32_bitrate_kbps: 128,
                audio_codec_profile: 0
            };
        }
        if (!param.videoParam) {
            param.videoParam = {
                i32_width: 640,
                i32_height: 360,
                i32_fps: 15,
                i32_gop: 60,
                i32_bitrate_kpbs: 500,
                video_codec_profile: 0,
                lowLatency: false
            };
        }
        if (!param.backgroundColor) {
            param.backgroundColor = "0x000000";
        }
        return this.instance.StartLiveTranscoding(param);
    }
    /** {zh}
     * @brief 停止转推直播。<br>
     * @return
     * + 0：成功
     * + !0：失败<br>
     * @notes 关于启动转推直播，参看 startLiveTranscoding{@link #startLiveTranscoding}。
     */
    stopLiveTranscoding() {
        return this.instance.StopLiveTranscoding();
    }
    /** {zh}
     * @brief 更新转推直播参数。  <br>
     * @param param 配置参数
     * @return
     * + 0：成功
     * + !0：失败<br>
     * @notes 使用 startLiveTranscoding{@link #startLiveTranscoding} 启用转推直播功能后，使用此方法更新功能配置参数。
     */
    updateLiveTranscoding(param) {
        if (!param.audioParam) {
            param.audioParam = {
                i32_sample_rate: 48000,
                i32_channel_num: 2,
                i32_bitrate_kbps: 128,
                audio_codec_profile: 0
            };
        }
        if (!param.videoParam) {
            param.videoParam = {
                i32_width: 640,
                i32_height: 360,
                i32_fps: 15,
                i32_gop: 60,
                i32_bitrate_kpbs: 500,
                video_codec_profile: 0,
                lowLatency: false
            };
        }
        if (!param.backgroundColor) {
            param.backgroundColor = "0x000000";
        }
        return this.instance.UpdateLiveTranscoding(param);
    }
    //////////////////////////////////////////////
    // JS Render Frame
    /** {zh}
     * @brief 为本地采集到的视频流绑定本地渲染视图
     * @param view 视图
     * @param userId 远端用户 ID
     * @param renderOptions 渲染选项
     * @return `0`：成功<br>
     *         `-1`: 失败
     */
    setupLocalVideo(view, renderOptions = { renderMode: types_1.RenderMode.FIT, mirror: false }) {
        let ret = -1;
        do {
            if (!view) {
                logger.warn("SetupLocalVideo, view is null");
                break;
            }
            let user = this.localUser;
            if (user) {
                user.renderOptions = renderOptions;
                if (!user.videoRender) {
                    user.videoRender = new yuv_render_1.YUVRender(view, renderOptions.renderMode, renderOptions.mirror, {});
                }
                else {
                    logger.info("videoRender is not null");
                }
            }
            else {
                logger.warn("user is null");
            }
            ret = 0;
        } while (false);
        return ret;
    }
    /** {zh}
     * @brief 解绑本地视频流已绑定的渲染视图
     * @return `0`：成功<br>
     *         `-1`: 失败
     */
    removeLocalVideo() {
        let user = this.localUser;
        if (user && user.videoRender) {
            user.videoRender.destroy();
            user.videoRender = null;
        }
        return 0;
    }
    /** {zh}
     * @brief 为远端视频流绑定本地渲染视图
     * @param view 视图
     * @param userId 远端用户 ID
     * @param renderOptions 渲染选项
     * @return `0`：成功<br>
     *         `-1`: 失败
     */
    setupRemoteVideo(userId, view, renderOptions = { renderMode: types_1.RenderMode.FIT, mirror: false }) {
        let ret = -1;
        do {
            if (!view) {
                logger.warn("SetupRemoteVideo, view is null");
                break;
            }
            let user = this.findUser(userId);
            if (user) {
                if (!user.videoRender) {
                    user.videoRender = new yuv_render_1.YUVRender(view, renderOptions.renderMode, renderOptions.mirror, {});
                }
            }
            ret = 0;
        } while (false);
        return ret;
    }
    /** {zh}
     * @brief 解绑指定远端视频流已绑定的本地视图
     * @param userId 远端用户 ID
     * @return `0`：成功<br>
     *         `-1`: 失败
     * @notes 停止接收远端视频流时应解绑视图
     */
    removeRemoteVideo(userId) {
        let user = this.findUser(userId);
        if (user && user.videoRender) {
            user.videoRender.destroy();
            user.videoRender = null;
        }
        return 0;
    }
    /** {zh}
     * @brief 解绑所有已绑定本地视图的指定远端视频流
     * @return 0：成功<br>
     *         -1: 失败
     * @notes 停止接收远端视频流时应解绑视图
     */
    removeAllRemoteVideo() {
        var _a;
        (_a = this.remoteUsers) === null || _a === void 0 ? void 0 : _a.forEach((user) => {
            if (user && user.videoRender) {
                user.videoRender.destroy();
                user.videoRender = null;
            }
        });
        return 0;
    }
    /** {zh}
     * @brief 为本地屏幕共享流绑定视图
     * @param view 视图
     * @param renderOptions 渲染选项
     * @return 0：成功<br>
     *         -1: 失败
     * @notes 本地发起屏幕共享需要先绑定视图
     */
    setupLocalScreen(view, renderOptions = { renderMode: types_1.RenderMode.FIT, mirror: false }) {
        let ret = -1;
        do {
            if (!view) {
                logger.warn("SetupLocalScreen, view is null");
                break;
            }
            let user = this.localUser;
            if (user) {
                if (!user.screenRender) {
                    user.screenRender = new yuv_render_1.YUVRender(view, renderOptions.renderMode, renderOptions.mirror, {});
                }
            }
            ret = 0;
        } while (false);
        return ret;
    }
    /** {zh}
     * @brief 解绑屏幕共享流已绑定的视图
     * @return 0：成功<br>
     *         !0: 失败
     * @notes 本地停止屏幕共享时解绑视图
     */
    removeLocalScreen() {
        let user = this.localUser;
        if (user && user.screenRender) {
            user.screenRender.destroy();
            user.screenRender = null;
        }
        return 0;
    }
    /** {zh}
     * @brief 为远端屏幕共享流绑定本地视图
     * @param view 视图
     * @param userId 远端用户 ID
     * @param renderOptions 渲染选项
     * @return 0：成功<br>
     *         -1: 失败
     * @notes 接收屏幕共享流需要先绑定视图
     */
    setupRemoteScreen(userId, view, renderOptions = { renderMode: types_1.RenderMode.FIT, mirror: false }) {
        let ret = -1;
        do {
            if (!view) {
                logger.warn("SetupRemoteScreen, view is null");
                break;
            }
            let user = this.findUser(userId);
            if (user) {
                if (!user.screenRender) {
                    user.screenRender = new yuv_render_1.YUVRender(view, renderOptions.renderMode, renderOptions.mirror, {});
                }
            }
            ret = 0;
        } while (false);
        return ret;
    }
    /** {zh}
     * @brief 解绑远端屏幕共享流已绑定的本地视图
     * @param userId 远端用户 ID
     * @return 0：成功<br>
     *         -1: 失败
     * @notes 停止接收屏幕共享流时应解绑视图
     */
    removeRemoteScreen(userId) {
        let user = this.findUser(userId);
        if (user && user.screenRender) {
            user.screenRender.destroy();
            user.screenRender = null;
        }
        return 0;
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////
    // callback
    /**
     * @private
     */
    OnLeaveRoom() {
        var _a;
        this.removeLocalVideo();
        this.removeLocalScreen();
        (_a = this.remoteUsers) === null || _a === void 0 ? void 0 : _a.forEach((ele) => {
            this.removeRemoteVideo(ele.userId);
            this.removeRemoteScreen(ele.userId);
        });
    }
    /**
     * @private
     */
    OnUserJoined(obj) {
        var _a;
        const { userId } = obj.Object;
        this.removeRemoteVideo(userId);
        this.removeRemoteScreen(userId);
        let userInfo = {
            userId: userId
        };
        (_a = this.remoteUsers) === null || _a === void 0 ? void 0 : _a.set(userId, userInfo);
    }
    /**
     * @private
     */
    OnUserLeave(obj) {
        var _a;
        const { userId } = obj.Object;
        this.removeRemoteVideo(userId);
        this.removeRemoteScreen(userId);
        (_a = this.remoteUsers) === null || _a === void 0 ? void 0 : _a.delete(userId);
    }
    /**
     * @private
     */
    OnLocalVideoFrame(obj) {
        let user = this.findUser(this.localUserId);
        if (user && user.videoRender) {
            let frame = yuv_render_1.YUVRender.buildYUVFrame(obj.Object);
            user.videoRender.renderFrame(frame);
        }
    }
    /**
     * @private
     */
    OnLocalScreenFrame(obj) {
        let user = this.findUser(this.localUserId);
        if (user && user.screenRender) {
            let frame = yuv_render_1.YUVRender.buildYUVFrame(obj.Object);
            user.screenRender.renderFrame(frame);
        }
    }
    /**
     * @private
     */
    OnRemoteVideoFrame(obj) {
        var _a, _b;
        let user = (_a = this.remoteUsers) === null || _a === void 0 ? void 0 : _a.get(obj.Object.userId);
        if ((_b = user) === null || _b === void 0 ? void 0 : _b.videoRender) {
            let frame = yuv_render_1.YUVRender.buildYUVFrame(obj.Object);
            user.videoRender.renderFrame(frame);
        }
    }
    /**
     * @private
     */
    OnRemoteScreenFrame(obj) {
        var _a, _b;
        let user = (_a = this.remoteUsers) === null || _a === void 0 ? void 0 : _a.get(obj.Object.userId);
        if ((_b = user) === null || _b === void 0 ? void 0 : _b.screenRender) {
            let frame = yuv_render_1.YUVRender.buildYUVFrame(obj.Object);
            user.screenRender.renderFrame(frame);
        }
    }
    /**
     * @private
     */
    clearLocalVideoCanvas() {
        let user = this.findUser(this.localUserId);
        if (user && user.videoRender) {
            user.videoRender.clearFrame();
        }
    }
    /**
     * @private
     */
    clearLocalScreenCanvas() {
        let user = this.findUser(this.localUserId);
        if (user && user.screenRender) {
            user.screenRender.clearFrame();
        }
    }
    /**
     * @private
     */
    clearRemoteVideoCanvas(userId) {
        var _a;
        let user = (_a = this.remoteUsers) === null || _a === void 0 ? void 0 : _a.get(userId);
        if (user && user.videoRender) {
            user.videoRender.clearFrame();
        }
    }
    /**
     * @private
     */
    clearAllRemoteVideoCanvas() {
        if (!this.remoteUsers) {
            return;
        }
        this.remoteUsers.forEach((user) => {
            if (user && user.videoRender) {
                user.videoRender.clearFrame();
            }
        });
    }
    /**
     * @private
     */
    clearRemoteScreenCanvas(userId) {
        var _a;
        let user = (_a = this.remoteUsers) === null || _a === void 0 ? void 0 : _a.get(userId);
        if (user && user.screenRender) {
            user.screenRender.clearFrame();
        }
    }
    /**
     * @private
     */
    cbEngine(obj) {
        this.processCallback(obj);
    }
    /**
     * @private
     */
    fire(event, ...args) {
        setImmediate(() => {
            this.emit(event, ...args);
        });
    }
    ;
    /**
     * @private
     */
    processCallback(obj) {
        let type = obj.Type;
        let data = obj.Object;
        switch (type) {
            case "OnLocalScreenFrame":
                {
                    this.convertYUVBuffer(obj);
                    this.OnLocalScreenFrame(obj);
                    this.fire('OnLocalScreenFrame', data);
                }
                break;
            case "OnLocalVideoFrame":
                {
                    this.convertYUVBuffer(obj);
                    this.OnLocalVideoFrame(obj);
                    this.fire('OnLocalVideoFrame', data);
                }
                break;
            case "OnRemoteScreenFrame":
                {
                    this.convertYUVBuffer(obj);
                    this.OnRemoteScreenFrame(obj);
                    this.fire('OnRemoteScreenFrame', data);
                }
                break;
            case "OnRemoteVideoFrame":
                {
                    this.convertYUVBuffer(obj);
                    this.OnRemoteVideoFrame(obj);
                    this.fire('OnRemoteVideoFrame', data);
                }
                break;
            case "OnWarning":
                {
                    this.fire('OnWarning', data.warn);
                }
                break;
            case "OnError":
                {
                    this.fire('OnError', data.error);
                }
                break;
            case "OnAudioMixingFinished":
                {
                    this.fire('OnAudioMixingFinished');
                }
                break;
            case "OnAudioMixingStateChanged":
                {
                    this.fire('OnAudioMixingStateChanged', data.id, data.state, data.error);
                }
                break;
            case "OnLogReport":
                {
                    this.fire('OnLogReport', data.logType, data.logContent);
                }
                break;
            case "OnConnectionStateChanged":
                {
                    this.fire('OnConnectionStateChanged', data.state);
                }
                break;
            case "OnNetworkTypeChanged":
                {
                    this.fire('OnNetworkTypeChanged', data.type);
                }
                break;
            case "OnPerformanceAlarms":
                {
                    this.fire('OnPerformanceAlarms', data.mode, data.roomId, data.reason, data.sourceWantedDataObject);
                }
                break;
            case "OnMediaDeviceStateChanged":
                {
                    this.fire('OnMediaDeviceStateChanged', data.deviceId, data.deviceType, data.deviceState, data.deviceError);
                }
                break;
            case "OnSysStats":
                {
                    let sysStats = data;
                    this.fire('OnSysStats', sysStats);
                }
                break;
            case "OnJoinRoomResult":
                {
                    this.fire('OnJoinRoomResult', data.roomId, data.userId, data.errorCode, data.joinType, data.elapsed);
                }
                break;
            case "OnLeaveRoom":
                {
                    this.OnLeaveRoom();
                    this.fire('OnLeaveRoom', data);
                }
                break;
            case "OnRoomWarning":
                {
                    this.fire('OnRoomWarning', data);
                }
                break;
            case "OnRoomError":
                {
                    this.fire('OnRoomError', data);
                }
                break;
            case "OnRoomStats":
                {
                    let rtcStats = data;
                    this.fire('OnRoomStats', rtcStats);
                }
                break;
            case "OnLocalStreamStats":
                {
                    let stats = data;
                    this.fire('OnLocalStreamStats', stats);
                }
                break;
            case "OnRemoteStreamStats":
                {
                    let stats = data;
                    this.fire('OnRemoteStreamStats', stats);
                }
                break;
            case "OnUserJoined":
                {
                    this.OnUserJoined(obj);
                    this.fire('OnUserJoined', data.userId, data.elapsed);
                }
                break;
            case "OnUserLeave":
                {
                    this.OnUserLeave(obj);
                    this.fire('OnUserLeave', data.userId, data.reason);
                }
                break;
            case "OnMuteAllRemoteAudio":
                {
                    this.fire('OnMuteAllRemoteAudio', data.userId, data.muteState);
                }
                break;
            case "OnMuteAllRemoteVideo":
                {
                    this.fire('OnMuteAllRemoteVideo', data.userId, data.muteState);
                }
                break;
            case "OnUserMuteAudio":
                {
                    this.fire('OnUserMuteAudio', data.userId, data.muteState);
                }
                break;
            case "OnUserStartAudioCapture":
                {
                    this.fire('OnUserStartAudioCapture', data.userId);
                }
                break;
            case "OnUserStopAudioCapture":
                {
                    this.fire('OnUserStopAudioCapture', data.userId);
                }
                break;
            case "OnFirstLocalAudioFrame":
                {
                    this.fire('OnFirstLocalAudioFrame', data.streamIndex);
                }
                break;
            case "OnFirstRemoteAudioFrame":
                {
                    let remoteKey = data;
                    this.fire('OnFirstRemoteAudioFrame', remoteKey);
                }
                break;
            case "OnStreamRemove":
                {
                    this.fire('OnStreamRemove', data.stream, data.reason);
                }
                break;
            case "OnStreamAdd":
                {
                    this.fire('OnStreamAdd', data.stream);
                }
                break;
            case "OnSimulcastSubscribeFallback":
                {
                    let streamSwitch = data;
                    this.fire('OnSimulcastSubscribeFallback', streamSwitch);
                }
                break;
            case "OnFirstLocalVideoFrameCaptured":
                {
                    let videoFrameInfo = data.info;
                    this.fire('OnFirstLocalVideoFrameCaptured', data.index, videoFrameInfo);
                }
                break;
            case "OnLocalVideoSizeChanged":
                {
                    let videoFrameInfo = data.info;
                    this.fire('OnLocalVideoSizeChanged', data.index, videoFrameInfo);
                }
                break;
            case "OnRemoteVideoSizeChanged":
                {
                    let videoFrameInfo = data.info;
                    this.fire('OnRemoteVideoSizeChanged', data.key, videoFrameInfo);
                }
                break;
            case "OnFirstRemoteVideoFrameRendered":
                {
                    let videoFrameInfo = data.info;
                    this.fire('OnFirstRemoteVideoFrameRendered', data.key, videoFrameInfo);
                }
                break;
            case "OnUserMuteVideo":
                {
                    this.fire('OnUserMuteVideo', data.userId, data.muteState);
                }
                break;
            case "OnUserStartVideoCapture":
                {
                    this.fire('OnUserStartVideoCapture', data.userId);
                }
                break;
            case "OnUserStopVideoCapture":
                {
                    this.fire('OnUserStopVideoCapture', data.userId);
                }
                break;
            case "OnLocalAudioStateChanged":
                {
                    let state = data.state;
                    let error = data.error;
                    this.fire('OnLocalAudioStateChanged', state, error);
                }
                break;
            case "OnRemoteAudioStateChanged":
                {
                    let state = data.state;
                    let reason = data.reason;
                    this.fire('OnRemoteAudioStateChanged', data.key, state, reason);
                }
                break;
            case "OnLocalVideoStateChanged":
                {
                    let state = data.state;
                    let error = data.error;
                    this.fire('OnLocalVideoStateChanged', data.streamIndex, state, error);
                }
                break;
            case "OnRemoteVideoStateChanged":
                {
                    let state = data.state;
                    let reason = data.reason;
                    this.fire('OnRemoteVideoStateChanged', data.key, state, reason);
                }
                break;
            case "OnAudioFrameSendStateChanged":
                {
                    let user = data.user;
                    let state = data.state;
                    this.fire('OnAudioFrameSendStateChanged', user, state);
                }
                break;
            case "OnVideoFrameSendStateChanged":
                {
                    let user = data.user;
                    let state = data.state;
                    this.fire('OnVideoFrameSendStateChanged', user, state);
                }
                break;
            case "OnScreenVideoFrameSendStateChanged":
                {
                    let user = data.user;
                    let state = data.state;
                    this.fire('OnScreenVideoFrameSendStateChanged', user, state);
                }
                break;
            case "OnAudioFramePlayStateChanged":
                {
                    let user = data.user;
                    let state = data.state;
                    this.fire('OnAudioFramePlayStateChanged', user, state);
                }
                break;
            case "OnVideoFramePlayStateChanged":
                {
                    let user = data.user;
                    let state = data.state;
                    this.fire('OnVideoFramePlayStateChanged', user, state);
                }
                break;
            case "OnScreenVideoFramePlayStateChanged":
                {
                    let user = data.user;
                    let state = data.state;
                    this.fire('OnScreenVideoFramePlayStateChanged', user, state);
                }
                break;
            case "OnUserEnableLocalAudio":
                {
                    this.fire('OnUserEnableLocalAudio', data.userId, data.enabled);
                }
                break;
            case "OnUserEnableLocalVideo":
                {
                    this.fire('OnUserEnableLocalVideo', data.userId, data.enabled);
                }
                break;
            case "OnStreamSubscribed":
                {
                    this.fire('OnStreamSubscribed', data.stateCode, data.userId, data.config);
                }
                break;
            // message
            case 'OnRoomMessageReceived':
                {
                    this.fire('OnRoomMessageReceived', data.uid, data.message);
                }
                break;
            case 'OnRoomBinaryMessageReceived':
                {
                    this.fire('OnRoomBinaryMessageReceived', data.uid, data.message);
                }
                break;
            case 'OnRoomMessageSendResult':
                {
                    this.fire('OnRoomMessageSendResult', data.msgId, data.error);
                }
                break;
            case 'OnUserMessageReceived':
                {
                    this.fire('OnUserMessageReceived', data.userId, data.message);
                }
                break;
            case 'OnUserBinaryMessageReceived':
                {
                    this.fire('OnUserBinaryMessageReceived', data.uid, data.message);
                }
                break;
            case 'OnUserMessageSendResult':
                {
                    this.fire('OnUserMessageSendResult', data.msgId, data.error);
                }
                break;
            case 'OnAudioVolumeIndication':
                {
                    this.fire('OnAudioVolumeIndication', data.speakers, data.totalVolume);
                }
                break;
            case 'OnSEIMessageReceived':
                {
                    let stream_key = data.stream_key;
                    this.fire('OnSEIMessageReceived', stream_key, data.message);
                }
                break;
            case 'OnStreamMixingEvent':
                {
                    this.fire('OnStreamMixingEvent', data.event, data.event_data, data.error, data.mix_type);
                }
                break;
            case 'OnStreamMixingVideoFrame':
                {
                    this.fire('OnStreamMixingVideoFrame', data);
                }
                break;
            case 'OnRecordingStateUpdate':
                {
                    let type = data.type;
                    let info = data.info;
                    this.fire('OnRecordingStateUpdate', type, data.state, data.error_code, info);
                }
                break;
            case 'OnRecordingProgressUpdate':
                {
                    let type = data.type;
                    let process = data.process;
                    let info = data.info;
                    this.fire('OnRecordingProgressUpdate', type, process, info);
                }
                break;
            case 'OnRecordAudioFrame':
                {
                    let audioFrame = data.audio_frame;
                    this.fire('OnRecordAudioFrame', audioFrame);
                }
                break;
            case 'OnPlaybackAudioFrame':
                {
                    let audioFrame = data.audio_frame;
                    this.fire('OnPlaybackAudioFrame', audioFrame);
                }
                break;
            case 'OnMixedAudioFrame':
                {
                    let audioFrame = data.audio_frame;
                    this.fire('OnMixedAudioFrame', audioFrame);
                }
                break;
            case 'OnLoginResult':
                {
                    this.fire('OnLoginResult', data.uid, data.error_code, data.elapsed);
                }
                break;
            case 'OnLogout':
                {
                    this.fire('OnLogout');
                }
                break;
            case 'OnServerParamsSetResult':
                {
                    this.fire('OnServerParamsSetResult', data.error);
                }
                break;
            case 'OnGetPeerOnlineStatus':
                {
                    this.fire('OnGetPeerOnlineStatus', data.peer_user_id, data.status);
                }
                break;
            case 'OnUserMessageReceivedOutsideRoom':
                {
                    this.fire('OnUserMessageReceivedOutsideRoom', data.uid, data.message);
                }
                break;
            case 'OnUserBinaryMessageReceivedOutsideRoom':
                {
                    this.fire('OnUserBinaryMessageReceivedOutsideRoom', data.uid, data.message);
                }
                break;
            case 'OnUserMessageSendResultOutsideRoom':
                {
                    this.fire('OnUserMessageSendResultOutsideRoom', data.msgid, data.error);
                }
                break;
            case 'OnServerMessageSendResult':
                {
                    this.fire('OnServerMessageSendResult', data.msgid, data.error);
                }
                break;
            case 'OnASRSuccess':
                {
                    this.fire('OnASRSuccess');
                }
                break;
            case 'OnMessage':
                {
                    this.fire('OnMessage', data.message);
                }
                break;
            case 'OnASRError':
                {
                    this.fire('OnASRError', data.error_code, data.error_message);
                }
                break;
            case 'OnLiveTranscodingResult': {
                this.fire('OnLiveTranscodingResult', data.url, data.error);
            }
            default:
                { }
                break;
        }
    }
    /**
     * @private
     */
    convertYUVBuffer(obj) {
        const bufferY = Buffer.from(obj.Object.planeY);
        const bufferU = Buffer.from(obj.Object.planeU);
        const bufferV = Buffer.from(obj.Object.planeV);
        obj.Object.planeY = null;
        obj.Object.planeU = null;
        obj.Object.planeV = null;
        obj.Object.planeY = bufferY;
        obj.Object.planeU = bufferU;
        obj.Object.planeV = bufferV;
    }
    /**
     * @private
     */
    findUser(userId) {
        var _a;
        let ret = undefined;
        if (userId === this.localUserId) {
            ret = this.localUser;
        }
        else {
            ret = (_a = this.remoteUsers) === null || _a === void 0 ? void 0 : _a.get(userId);
        }
        return ret;
    }
}
__decorate([
    checkInit
], veRTCEngine.prototype, "uninit", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "setBusinessId", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "joinRoom", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "setUserVisibility", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "leaveRoom", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "updateToken", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "setPlaybackVolume", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "startAudioCapture", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "muteLocalAudio", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "setAudioVolumeIndicationInterval", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "setRemoteAudioPlaybackVolume", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "resumeAllSubscribedStream", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "startVideoCapture", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "stopVideoCapture", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "muteLocalVideo", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "switchCamera", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "setLocalVideoMirrorMode", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "pauseAllSubscribedStream", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "startScreenVideoCapture", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "updateScreenCaptureRegion", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "UpdateScreenCaptureMouseCursor", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "updateScreenCaptureHighlightConfig", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "updateScreenCaptureFilterConfig", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "stopScreenVideoCapture", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "getScreenCaptureSourceList", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "getThumbnail", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "publishScreen", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "unpublishScreen", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "setCaptureVolume", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "startAudioMixing", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "stopAudioMixing", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "pauseAudioMixing", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "resumeAudioMixing", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "setAudioMixingVolume", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "getAudioMixingDuration", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "getAudioMixingCurrentPosition", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "setAudioMixingPosition", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "enumerateVideoCaptureDevices", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "setVideoCaptureDevice", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "getVideoCaptureDevice", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "enumerateAudioPlaybackDevices", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "enumerateAudioCaptureDevices", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "setAudioPlaybackDevice", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "setAudioCaptureDevice", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "getAudioPlaybackDevice", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "getAudioCaptureDevice", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "startAudioPlaybackDeviceTest", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "stopAudioPlaybackDeviceTest", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "startAudioCaptureDeviceTest", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "stopAudioCaptureDeviceTest", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "setAudioPlaybackDeviceVolume", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "getAudioPlaybackDeviceVolume", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "setAudioCaptureDeviceVolume", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "getAudioCaptureDeviceVolume", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "startAudioDeviceLoopbackTest", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "stopAudioDeviceLoopbackTest", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "initAudioPlaybackDeviceForTest", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "initAudioCaptureDeviceForTest", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "setAudioPlaybackDeviceMute", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "getAudioPlaybackDeviceMute", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "setAudioCaptureDeviceMute", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "getAudioCaptureDeviceMute", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "setPublishFallbackOption", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "setRemoteUserPriority", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "publish", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "unpublish", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "subscribeUserStream", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "unsubscribe", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "sendUserMessage", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "sendUserBinaryMessage", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "setRecordingAudioFrameParameters", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "setPlaybackAudioFrameParameters", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "setMixedAudioFrameParameters", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "sendRoomMessage", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "sendRoomBinaryMessage", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "login", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "logout", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "updateLoginToken", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "setServerParams", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "getPeerOnlineStatus", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "SendUserMessageOutsideRoom", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "getErrorDescription", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "sendUserBinaryMessageOutsideRoom", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "sendServerMessage", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "sendServerBinaryMessage", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "disableBackground", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "checkLicense", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "getAuthMessage", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "enableEffect", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "setAlgoModelPath", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "setEffectNodes", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "updateNode", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "setColorFilter", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "setColorFilterIntensity", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "sendSEIMessage", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "setScreenAudioStreamIndex", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "startScreenAudioCapture", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "stopScreenAudioCapture", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "feedback", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "setRuntimeParameters", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "setupLocalVideo", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "removeLocalVideo", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "setupRemoteVideo", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "removeRemoteVideo", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "removeAllRemoteVideo", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "setupLocalScreen", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "removeLocalScreen", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "setupRemoteScreen", null);
__decorate([
    checkInit
], veRTCEngine.prototype, "removeRemoteScreen", null);
exports.veRTCEngine = veRTCEngine;
//# sourceMappingURL=index.js.map