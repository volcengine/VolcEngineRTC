/**
* 功能名称： VolcEngineRTC SEI方案
* 功能简单描述：在音视频流媒体应用中，除了可以收发音视频内容外，可能还需要收发一些与音视频内容同步的文本消息。
*   你可以 H.264/H.265 视频视频流中插入 SEI，并在订阅端接收这些信息。
* 参考文档：https://www.volcengine.com/docs/6348/70140
*
* 此功能涉及的API及回调：
*     createRTCEngine 创建引擎
*     destroyRTCEngine 销毁引擎
*     startAudioCapture 开启音频采集
*     startVideoCapture 开启视频采集
*     createRTCRoom 创建RTC房间
*     joinRoom 进入RTC房间
*     leaveRoom 离开RTC房间
*     destroy 销毁RTC房间
*
*     通用方案： RTC本端通过sendSEIMessage发送SEI， RTC远端收到onSEIMessageReceived，当合流转推时，RTMP流 h264视频中包含SEI信息
*     相关接口：
*     sendSEIMessage 发送SEI信息
*     onSEIMessageReceived 收到SEI信息的回调
*     当时纯音频场景时，本端需要发布视频流，远端需要订阅视频流才能收到SEI
*
*     合流转推方案：合流转推时通过 setLayoutConfig 接口将app_data设置在SEI信息中，观众端拉流时可以解析SEI，SEI结构如下
*     {
        "app_data": "自定义消息",
        "canvas": {
            "bgnd": "#000000",
            "h": 640,
            "w": 360
        },
        "regions": [{
            "alpha": 1.0,
            "contentControl": 0,
            "height": 640,
            "locationX": 0,
            "locationY": 50,
            "renderMode": 1,
            "uid": "user_343",
            "width": 360,
            "zorder": 0
            }],
        "ts": 1705994199709
    }
      相关接口：
*     startPushMixedStreamToCDN 开始合流转推
*     setLayoutConfig 设置SEI中的app_data信息
*     stopPushStreamToCDN 停止合流转推
*
*
*     音频随帧方案：请参考音频随帧部分
*
*     其他接口：
*     setLocalVideoCanvas 设置本地视频渲染视图

*
*     onRoomStateChanged 房间状态回调
*     onLeaveRoom 离房回调
*     onUserJoined 用户加入回调
*     onUserLeave  用户离开回调
*     onUserPublishStream 用户发流回调
*     onUserUnpublishStream 用户停止发流回调
*/

import UIKit
import SnapKit
import VolcEngineRTC
import Foundation
import CommonCrypto
class SEIViewController: BaseViewController, ByteRTCEngineDelegate, ByteRTCRoomDelegate {
    
    var rtcVideo: ByteRTCEngine?
    var rtcRoom: ByteRTCRoom?
    var userVideoStreamMap: Dictionary = Dictionary<String, ByteRTCStreamInfo>()
    var mixConfig: ByteRTCMixedStreamConfig?
    var targetMixConfig: ByteRTCMixedStreamPushTargetConfig?
    let taskId = "1999"
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        self.createUI()
        self.buildRTCEngine()
    }
    
    deinit {
        self.rtcRoom?.leave()
        self.rtcRoom?.destroy()
        self.rtcRoom = nil
        
        ByteRTCEngine.destroyRTCEngine()
        self.rtcVideo = nil
    }
    
    // MARK: Private method
    
    @objc func joinRoom()  {
        let roomId = self.roomSettingItem.text ?? ""
        let userId = self.userSettingItem.text ?? ""
        
        var vaild = checkValid(roomId)
        if vaild == false {
            ToastComponents.shared.show(withMessage: "输入不合法，只支持数字、大小写字母、@._-,长度小于128字符")
            return
        }
        
        vaild = checkValid(userId)
        if vaild == false {
            ToastComponents.shared.show(withMessage: "输入不合法，只支持数字、大小写字母、@._-,长度小于128字符")
            return
        }
        
        joinButton.isSelected = !joinButton.isSelected
        
        if joinButton.isSelected {
            joinButton.setTitle("离开房间", for: .normal)
            
            // 加入房间
            self.rtcRoom = self.rtcVideo?.createRTCRoom(roomId)
            self.rtcRoom?.delegate = self
            
            // 获取token,建议从服务端获取
            let token = generatorToken(roomId: roomId, userId: userId)
            
            let userInfo = ByteRTCUserInfo.init()
            userInfo.userId = userId
            
            let roomCfg = ByteRTCRoomConfig.init()
            roomCfg.isPublishAudio = true
            roomCfg.isPublishVideo = true
            roomCfg.isAutoSubscribeAudio = true
            roomCfg.isAutoSubscribeVideo = true
            
            self.rtcRoom?.joinRoom(token, userInfo: userInfo, userVisibility: true, roomConfig: roomCfg)
        }
        else {
            joinButton.setTitle("加入房间", for: .normal)
            self.stopPushCDN()
            self.rtcRoom?.leave()
        }
    }
    
    func buildRTCEngine() {
        // 创建引擎
        let engineCfg = ByteRTCEngineConfig.init()
        engineCfg.appID = kAppID
        engineCfg.parameters = [:]
        self.rtcVideo = ByteRTCEngine.createRTCEngine(engineCfg, delegate: self)

        // 开启本地音视频采集
        self.rtcVideo?.startVideoCapture()
        self.rtcVideo?.startAudioCapture()
        
        self.bindLocalRenderView()
        
        // 设置默认合流参数
        self.mixConfig = ByteRTCMixedStreamConfig.default()
        self.targetMixConfig = ByteRTCMixedStreamPushTargetConfig()
    }
    
    func bindLocalRenderView() {
        // 设置本地渲染视图
        let canvas = ByteRTCVideoCanvas.init()
        canvas.view = self.localView.videoView
        canvas.renderMode = .hidden
        self.localView.userId = userSettingItem.text ?? ""
        
        self.rtcVideo?.setLocalVideoCanvas(withCanvas: canvas);
    }
    
    func updateRenderView() {
        // 获取room的第一个用户
        var remoteStreamInfo:ByteRTCStreamInfo?
        
        for (userId, info) in self.userVideoStreamMap {
            if info.roomId == self.roomSettingItem.text {
                remoteStreamInfo = info
            }
        }
        
        if (remoteStreamInfo != nil) {
            self.bindRemoteRenderView(view: self.firstRemoteView, roomId:remoteStreamInfo!.roomId, userId:remoteStreamInfo!.userId)
        }
    }
    
//    @objc func startPushCDN() {
//        if let text = self.urlTextFieldView.text, !text.isEmpty {
//            self.mixConfig?.pushURL = text
//            
//            let roomId = roomSettingItem.text
//            let userId = userSettingItem.text
//            
//            self.mixConfig?.regions = self.getMixRegions()
//            self.mixConfig?.backgroundColor = "#FFFFFF"
//            
//            // 合流用户透传的额外数据,通过拉流端SEI接收
//            self.mixConfig?.userConfigExtraInfo = self.layoutTextFieldView.text ?? ""
//            
//            self.mixConfig?.roomID = roomId!
//            self.mixConfig?.userID = userId!
//            
//            self.targetMixConfig?.pushCDNURL = text
//            self.targetMixConfig?.pushTargetType = .toCDN
//            
//            self.rtcVideo?.startPushMixedStream(taskId, with: self.targetMixConfig, withMixedConfig: self.mixConfig)
//        } else {
//            ToastComponents.shared.show(withMessage: "无效的推流地址")
//        }
//    }
    
    func signURL(roomID: String) -> String? {
    // 获取当前时间戳
    let timeStamp = Int(Date().timeIntervalSince1970)
    let expire = timeStamp + 7200
    
    // 构建路径
    let path = "/rtc_test/sei\(roomID)111"
    let authKey = "Uq8e962ghCCY2pBUB9Me2Fwy"
    
    // 构建签名字符串
    let keyStr = "\(path)\(authKey)\(expire)"
    
    // 计算 MD5 签名
    guard let sign = md5(string: keyStr) else {
        return nil
    }
    
    // 构建最终的 URL
    let finalURL = "rtmp://fcdn-test-hl.uplive.ixigua.com/rtc_test/sei\(roomID)111?sign=\(sign)&expire=\(expire)"
    
    return finalURL
    }

    // MD5 计算函数
    func md5(string: String) -> String? {
        let length = Int(CC_MD5_DIGEST_LENGTH)
        let messageData = string.data(using: .utf8)!
        var digest = [UInt8](repeating: 0, count: length)
        
        messageData.withUnsafeBytes {
            _ = CC_MD5($0.baseAddress, CC_LONG(messageData.count), &digest)
        }
        
        return digest.map { String(format: "%02hhx", $0) }.joined()
    }
    
    @objc func startPushCDN() {
        let roomId = roomSettingItem.text ?? ""
        let userId = userSettingItem.text ?? ""
        if let text = signURL(roomID: roomId), !text.isEmpty {
            if let cdnurl = signURL(roomID: roomId) {
                self.mixConfig?.regions = self.getMixRegions()
                self.mixConfig?.roomID = roomId
                self.mixConfig?.userID = userId
                self.mixConfig?.userConfigExtraInfo = self.layoutTextFieldView.text ?? ""

                self.targetMixConfig?.pushCDNURL = cdnurl
                self.urlTextFieldView.text = cdnurl
                self.targetMixConfig?.pushTargetType = .toCDN
                
                print("URL: \(cdnurl)")
                ToastComponents.shared.show(withMessage: "Updated URL: \(cdnurl)")
                ToastComponents.shared.show(withMessage: "Pull sdk using key : sei\(roomId)111")

                self.rtcVideo?.startPushMixedStream(taskId, with: self.targetMixConfig, withMixedConfig: self.mixConfig)
            } else {
                print("Failed to generate signed URL")
            }
        } else {
            ToastComponents.shared.show(withMessage: "无效的推流地址")
        }
    }
    @objc func updatePushCDN()  {
        // 合流用户透传的额外数据,通过拉流端SEI接收
        self.mixConfig?.userConfigExtraInfo = self.layoutTextFieldView.text ?? ""
        
        self.rtcVideo?.updatePushMixedStream(taskId, with: self.targetMixConfig, withMixedConfig: self.mixConfig!)
    }
    
    
    @objc func stopPushCDN()  {
        self.rtcVideo?.stopPushMixedStream(taskId, with: ByteRTCMixedStreamPushTargetType.toCDN)
    }
    
    func getMixRegions() -> [ByteRTCMixedStreamLayoutRegionConfig] {
        let roomId = roomSettingItem.text
        let userId = userSettingItem.text
        
        var regions = [ByteRTCMixedStreamLayoutRegionConfig]()
        
        let width = 360
        let height = 640
        
        // 本地用户
        let regionConfig = ByteRTCMixedStreamLayoutRegionConfig.init()
        regionConfig.userID = userId!
        regionConfig.roomID = roomId!
        regionConfig.locationX = 0
        regionConfig.locationY = 0
        regionConfig.width = width
        regionConfig.height = height
        regionConfig.zOrder = 0
        regionConfig.isLocalUser = true
        regionConfig.mediaType = .audioAndVideo
        
        regions.append(regionConfig)
        
        return regions
    }
    
    // 发送SEI信息
    @objc func sendSEIMessage()  {
        let message = self.seiTextFieldView.text;
        
        if !message!.isEmpty, let data = message?.data(using: .utf8) {
            self.rtcVideo?.sendSEIMessage(data, andRepeatCount: 3, andCountPerFrame: .single)
        }else {
            ToastComponents.shared.show(withMessage: "本端不能发送空消息")
        }

    }
    
    func bindRemoteRenderView(view: UserVideoView, roomId: String, userId: String) {
        // 设置远端用户视频渲染视图
        var streamInfo = self.userVideoStreamMap[userId]
        if streamInfo == nil {
            return
        }
        var streamId = streamInfo?.streamId
        if streamId == nil {
            return
        }
        
        let canvas = ByteRTCVideoCanvas.init()
        canvas.view = view.videoView
        canvas.renderMode = .hidden
        view.userId = userId
        
        self.rtcVideo?.setRemoteVideoCanvas(streamId!, withCanvas: canvas)
    }
    
    func createUI() -> Void {
        
        // 添加视图
        view.addSubview(containerView)
        containerView.snp.makeConstraints { make in
            make.left.right.equalTo(self.view)
            make.top.equalTo(topView.snp.bottom)
//            make.height.equalTo(containerView.snp.width)
        }
        
        self.containerView.addSubview(localView)
        self.containerView.addSubview(firstRemoteView)
        self.localView.snp.makeConstraints { make in
            make.left.top.equalTo(self.containerView)
            make.height.equalTo(self.containerView)
            make.width.equalTo(self.containerView).multipliedBy(0.5)
        }
        
        self.firstRemoteView.snp.makeConstraints { make in
            make.right.bottom.equalTo(self.containerView)
            make.height.equalTo(self.containerView)
            make.width.equalTo(self.containerView).multipliedBy(0.5)
        }

        view.addSubview(roomSettingItem)
        view.addSubview(userSettingItem)
        view.addSubview(joinButton)
        
        roomSettingItem.snp.makeConstraints { make in
            make.top.equalTo(containerView.snp.bottom).offset(10)
            make.left.equalToSuperview().offset(10)
            make.height.equalTo(30)
        }
        
        userSettingItem.snp.makeConstraints { make in
            make.centerY.equalTo(roomSettingItem)
            make.left.equalTo(roomSettingItem.snp.right).offset(20)
            make.right.equalToSuperview().offset(-10)
            make.width.height.equalTo(roomSettingItem)
        }
        
        joinButton.snp.makeConstraints { make in
            make.top.equalTo(roomSettingItem.snp.bottom).offset(10)
            make.left.equalToSuperview().offset(10)
            make.right.equalToSuperview().offset(-10)
            make.height.equalTo(36)
        }
        
        view.addSubview(seiTextFieldView)
        view.addSubview(sendButton)
        
        seiTextFieldView.snp.makeConstraints { make in
            make.top.equalTo(joinButton.snp.bottom).offset(20)
            make.left.equalToSuperview().offset(10)
            make.right.equalToSuperview().offset(-10)
            make.height.equalTo(30)
        }
        
        sendButton.snp.makeConstraints { make in
            make.top.equalTo(seiTextFieldView.snp.bottom).offset(10)
            make.left.right.width.height.equalTo(joinButton)
        }
        
        view.addSubview(urlTextFieldView)
        view.addSubview(layoutTextFieldView)
        view.addSubview(startPushButton)
        view.addSubview(updatePushButton)
        view.addSubview(stopPushButton)

        urlTextFieldView.snp.makeConstraints { make in
            make.top.equalTo(sendButton.snp.bottom).offset(20)
            make.left.equalToSuperview().offset(10)
            make.right.equalToSuperview().offset(-10)
            make.height.equalTo(30)
        }
        
        layoutTextFieldView.snp.makeConstraints { make in
            make.top.equalTo(urlTextFieldView.snp.bottom).offset(10)
            make.left.equalToSuperview().offset(10)
            make.right.equalToSuperview().offset(-10)
            make.height.equalTo(30)
        }
        
        startPushButton.snp.makeConstraints { make in
            make.top.equalTo(layoutTextFieldView.snp.bottom).offset(10)
            make.left.equalToSuperview().offset(10)
            make.height.equalTo(30)
        }
        
        updatePushButton.snp.makeConstraints { make in
            make.centerY.equalTo(startPushButton)
            make.left.equalTo(startPushButton.snp.right).offset(20)
            make.width.height.equalTo(startPushButton)
        }
        
        stopPushButton.snp.makeConstraints { make in
            make.centerY.equalTo(startPushButton)
            make.left.equalTo(updatePushButton.snp.right).offset(20)
            make.right.equalToSuperview().offset(-10)
            make.width.height.equalTo(startPushButton)
        }
        
        view.addSubview(receivedSEIItem)
        receivedSEIItem.snp.makeConstraints { make in
            make.top.equalTo(startPushButton.snp.bottom).offset(20)
            make.left.equalToSuperview().offset(10)
            make.right.equalToSuperview().offset(-10)
            make.height.equalTo(30)
            make.bottom.equalToSuperview().offset(-20)
        }
    }
    
    // MARK: Lazy laod
    
    lazy var roomSettingItem: TextFieldView = {
        let settingView = TextFieldView()
        settingView.title = "房间"
        return settingView
    }()
    
    lazy var userSettingItem: TextFieldView = {
        let settingView = TextFieldView()
        settingView.title = "用户"
        return settingView
    }()
    
    lazy var joinButton: UIButton = {
        let button = BaseButton()
        button.setTitle("加入房间", for: .normal)
        button.addTarget(self, action: #selector(joinRoom), for: .touchUpInside)
        return button
    }()
    
    lazy var seiTextFieldView: TextFieldView = {
        let settingView = TextFieldView()
        settingView.title = "SEI信息"
        settingView.inputTextField.keyboardType = .default
        return settingView
    }()
    
    lazy var sendButton: UIButton = {
        let button = BaseButton()
        button.setTitle("发送SEI", for: .normal)
        button.addTarget(self, action: #selector(sendSEIMessage), for: .touchUpInside)
        return button
    }()
    
    lazy var urlTextFieldView: TextFieldView = {
        let settingView = TextFieldView()
        settingView.title = "推流地址"
        settingView.text = ""
        return settingView
    }()
    
    lazy var layoutTextFieldView: TextFieldView = {
        let settingView = TextFieldView()
        settingView.title = "合流转推自定义信息"
        settingView.inputTextField.keyboardType = .default
        return settingView
    }()
    
    lazy var startPushButton: UIButton = {
        let button = BaseButton()
        button.setTitle("开始推流", for: .normal)
        button.addTarget(self, action: #selector(startPushCDN), for: .touchUpInside)
        return button
    }()
    
    lazy var updatePushButton: UIButton = {
        let button = BaseButton()
        button.setTitle("更新推流", for: .normal)
        button.addTarget(self, action: #selector(updatePushCDN), for: .touchUpInside)
        return button
    }()
    
    lazy var stopPushButton: UIButton = {
        let button = BaseButton()
        button.setTitle("停止推流", for: .normal)
        button.addTarget(self, action: #selector(stopPushCDN), for: .touchUpInside)
        return button
    }()
    
    lazy var receivedSEIItem: TextFieldView = {
        let settingView = TextFieldView()
        settingView.title = "本端收到的SEI信息"
        return settingView
    }()
    
    lazy var containerView: UIView = {
        let view = UIView.init()
        view.backgroundColor = .groupTableViewBackground
        return view
    }()
    
    lazy var localView: UserVideoView = {
        let view = UserVideoView.init()
        return view
    }()
    
    lazy var firstRemoteView: UserVideoView = {
        let view = UserVideoView.init()
        return view
    }()
    
    // MARK: ByteRTCEngineDelegate & ByteRTCRoomDelegate
    //进房状态
    func rtcRoom(_ rtcRoom: ByteRTCRoom, onRoomStateChanged roomId: String, withUid uid: String, state: Int, extraInfo: String) {
        ToastComponents.shared.show(withMessage: "onRoomStateChanged uid: \(uid) state:\(state)")
        
    }
    
    // 远端用户发布流
    func rtcRoom(_ rtcRoom: ByteRTCRoom, onUserPublishStreamVideo streamId: String, info: ByteRTCStreamInfo, isPublish: Bool) {
        ToastComponents.shared.show(withMessage: "onUserPublishStream uid: \(info.userId), isPub: \(isPublish)")

        
        if isPublish {
            self.userVideoStreamMap.updateValue(info, forKey: info.userId)
            
            DispatchQueue.main.async {
                self.updateRenderView()
            }
        } else {
            // 从self.users中移除
            self.userVideoStreamMap.removeValue(forKey: info.userId)

            DispatchQueue.main.async {
                for videoView in self.containerView.subviews {
                    if let view = videoView as? UserVideoView {
                        let userId = view.userId
                        
                        if userId == userId {
                            view.userId = ""
                        }
                    }
                }
            }
            
            DispatchQueue.main.async {
                self.updateRenderView()
            }
        }
    }
    
    
    // 远端用户加入房间
    func rtcRoom(_ rtcRoom: ByteRTCRoom, onUserJoined userInfo: ByteRTCUserInfo) {
        ToastComponents.shared.show(withMessage: "onUserJoined uid: \(userInfo.userId)")
        
    }
    
    // 远端用户离开房间
    func rtcRoom(_ rtcRoom: ByteRTCRoom, onUserLeave uid: String, reason: ByteRTCUserOfflineReason) {
        ToastComponents.shared.show(withMessage: "onUserLeave uid: \(uid)")
        
    }
    
    // 收到SEI信息
    func rtcEngine(_ engine: ByteRTCEngine, onSEIMessageReceived streamId: String, info: ByteRTCStreamInfo, andMessage message: Data) {
       
        
        if let string = String(data: message, encoding: .utf8) {
            ToastComponents.shared.show(withMessage: "onSEIMessageReceived: streamId = \(streamId), userId = \(info.userId), data = \(string)")

            self.receivedSEIItem.text = string
        }
    }
    
    
    // 合流事件回调
    func onMixedStreamEvent(event: ByteRTCMixedStreamTaskEvent, with info: ByteRTCMixedStreamTaskInfo, withErrorCode errorCode: ByteRTCMixedStreamTaskErrorCode) {
        ToastComponents.shared.show(withMessage: "onMixedStreamEvent:\(event.rawValue) taskId:\(info.taskId) errorCode:\(errorCode.rawValue) + mixType:\(info.description)")
    }
    
    func rtcEngine(_ engine: ByteRTCEngine, onMixedStreamEvent event: ByteRTCMixedStreamTaskEvent, withMixedStreamInfo info: ByteRTCMixedStreamTaskInfo, with errorCode: ByteRTCMixedStreamTaskErrorCode) {
            ToastComponents.shared.show(withMessage: "onMixedStreamEvent:\(event.rawValue) taskId:\(info.taskId) errorCode:\(errorCode.rawValue) + mixType:\(info.description)")
        NSLog("onMixedStreamEvent: \(event), info_des: \(info.description), errorcode : \(errorCode)")
    }
    

    
}
