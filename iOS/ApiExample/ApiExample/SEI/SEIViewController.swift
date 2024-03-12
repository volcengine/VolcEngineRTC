//
//  SEIViewController.swift
//  ApiExample
//
//  Created by bytedance on 2024/1/17.
//  Copyright © 2021 bytedance. All rights reserved.
//

import UIKit
import SnapKit
import VolcEngineRTC

class SEIViewController: BaseViewController, ByteRTCVideoDelegate, ByteRTCRoomDelegate, ByteRTCMixedStreamObserver {
    
    var rtcVideo: ByteRTCVideo?
    var rtcRoom: ByteRTCRoom?
    var users : Array = Array<ByteRTCRemoteStreamKey>()
    var mixConfig: ByteRTCMixedStreamConfig?
    let taskId = "1999"
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        self.createUI()
        self.buildRTCEngine()
    }
    
    deinit {
        
        self.rtcRoom?.leaveRoom()
        self.rtcRoom?.destroy()
        self.rtcRoom = nil
        
        ByteRTCVideo.destroyRTCVideo()
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
            roomCfg.isAutoPublish = true
            roomCfg.isAutoSubscribeAudio = true
            roomCfg.isAutoSubscribeVideo = true
            
            self.rtcRoom?.joinRoom(token, userInfo: userInfo, roomConfig: roomCfg)
        }
        else {
            joinButton.setTitle("加入房间", for: .normal)
            self.rtcRoom?.leaveRoom()
        }
    }
    
    func buildRTCEngine() {
        // 创建引擎
        self.rtcVideo = ByteRTCVideo.createRTCVideo(kAppID, delegate: self, parameters: [:])
        
        // 开启本地音视频采集
        self.rtcVideo?.startVideoCapture()
        self.rtcVideo?.startAudioCapture()
        
        self.bindLocalRenderView()
        
        // 设置默认合流参数
        self.mixConfig = ByteRTCMixedStreamConfig.default()
    }
    
    func bindLocalRenderView() {
        // 设置本地渲染视图
        let canvas = ByteRTCVideoCanvas.init()
        canvas.view = self.localView.videoView
        canvas.renderMode = .hidden
        self.localView.userId = userSettingItem.text ?? ""
        
        self.rtcVideo?.setLocalVideoCanvas(.indexMain, withCanvas: canvas);
    }
    
    func updateRenderView() {
        // 获取room的第一个用户
        var remoteUser:ByteRTCRemoteStreamKey?
        
        for streamKey in self.users {
            if remoteUser == nil && streamKey.roomId ==  self.roomSettingItem.text {
                remoteUser = streamKey
            }
        }
        
        if (remoteUser != nil) {
            self.bindRemoteRenderView(view: self.firstRemoteView,roomId: (remoteUser?.roomId)!,userId: (remoteUser?.userId)!)
        }
    }
    
    @objc func startPushCDN() {
        if let text = self.urlTextFieldView.text, !text.isEmpty {
            self.mixConfig?.pushURL = text
            
            let roomId = roomSettingItem.text
            let userId = userSettingItem.text
            
            self.mixConfig?.layoutConfig.regions = self.getMixRegions()
            self.mixConfig?.layoutConfig.backgroundColor = "#FFFFFF"
            
            // 合流用户透传的额外数据,通过拉流端SEI接收
            self.mixConfig?.layoutConfig.userConfigExtraInfo = self.layoutTextFieldView.text ?? ""
            
            self.mixConfig?.roomID = roomId!
            self.mixConfig?.userID = userId!
            
            self.rtcVideo?.startPushMixedStream(toCDN: taskId, mixedConfig: self.mixConfig, observer: self)
        } else {
            ToastComponents.shared.show(withMessage: "无效的推流地址")
        }
    }
    
    @objc func updatePushCDN()  {
        // 合流用户透传的额外数据,通过拉流端SEI接收
        self.mixConfig?.layoutConfig.userConfigExtraInfo = self.layoutTextFieldView.text ?? ""
        
        self.rtcVideo?.updatePushMixedStream(toCDN: taskId, mixedConfig: self.mixConfig!)
    }
    
    
    @objc func stopPushCDN()  {
        self.rtcVideo?.stopPushStreamToCDN(taskId)
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
            self.rtcVideo?.sendSEIMessage(.indexMain, andMessage: data, andRepeatCount: 3, andCountPerFrame: .single)
        }else {
            ToastComponents.shared.show(withMessage: "本端不能发送空消息")
        }

    }
    
    func bindRemoteRenderView(view: UserVideoView, roomId: String, userId: String) {
        // 设置远端用户视频渲染视图
        let canvas = ByteRTCVideoCanvas.init()
        canvas.view = view.videoView
        canvas.renderMode = .hidden
        view.userId = userId

        let streamKey = ByteRTCRemoteStreamKey.init()
        streamKey.userId = userId;
        streamKey.roomId = roomId;
        streamKey.streamIndex = .indexMain
        
        self.rtcVideo?.setRemoteVideoCanvas(streamKey, withCanvas: canvas)
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
        settingView.text = kCDNUrl
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
    
    // MARK: ByteRTCVideoDelegate & ByteRTCRoomDelegate
    //进房状态
    func rtcRoom(_ rtcRoom: ByteRTCRoom, onRoomStateChanged roomId: String, withUid uid: String, state: Int, extraInfo: String) {
        ToastComponents.shared.show(withMessage: "onRoomStateChanged uid: \(uid) state:\(state)")
        
    }
    
    // 远端用户发布流
    func rtcRoom(_ rtcRoom: ByteRTCRoom, onUserPublishStream userId: String, type: ByteRTCMediaStreamType) {
        ToastComponents.shared.show(withMessage: "onUserPublishStream uid: \(userId)")
        
        if type == .video || type == .both {
            
            let streamKey = ByteRTCRemoteStreamKey.init()
            streamKey.userId = userId;
            streamKey.roomId = rtcRoom.getId();
            streamKey.streamIndex = .indexMain
            
            self.users.append(streamKey)
            
            DispatchQueue.main.async {
                self.updateRenderView()
            }
        }
    }
    
     // 远端用户取消发布流
    func rtcRoom(_ rtcRoom: ByteRTCRoom, onUserUnpublishStream userId: String, type: ByteRTCMediaStreamType, reason: ByteRTCStreamRemoveReason) {
        ToastComponents.shared.show(withMessage: "onUserUnpublishStream uid: \(userId)")
        
        if type == .video || type == .both {
            
            // 从self.users中移除
            var itemsToRemove: [ByteRTCRemoteStreamKey] = []
            
            for streamKey in self.users {
                if streamKey.userId == userId {
                    itemsToRemove.append(streamKey)
                }
            }
            
            for item in itemsToRemove {
                if let index = self.users.firstIndex(of: item) {
                    self.users.remove(at: index)
                }
            }
            
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
    func rtcRoom(_ rtcRoom: ByteRTCRoom, onUserJoined userInfo: ByteRTCUserInfo, elapsed: Int) {
        ToastComponents.shared.show(withMessage: "onUserJoined uid: \(userInfo.userId)")
        
    }
    
    // 远端用户离开房间
    func rtcRoom(_ rtcRoom: ByteRTCRoom, onUserLeave uid: String, reason: ByteRTCUserOfflineReason) {
        ToastComponents.shared.show(withMessage: "onUserLeave uid: \(uid)")
        
    }
    
    // 收到SEI信息
    func rtcEngine(_ engine: ByteRTCVideo, onSEIMessageReceived remoteStreamKey: ByteRTCRemoteStreamKey, andMessage message: Data) {
       
        
        if let string = String(data: message, encoding: .utf8) {
            ToastComponents.shared.show(withMessage: "onSEIMessageReceived: uid = \(remoteStreamKey.userId ?? ""), data = \(string)")

            self.receivedSEIItem.text = string
        }
    }
    
    // MARK: ByteRTCMixedStreamObserver
    func isSupportClientPushStream() -> Bool {
        return false
    }
    
    // 合流事件回调
    func onMixingEvent(_ event: ByteRTCStreamMixingEvent, taskId: String, error errorCode: ByteRTCStreamMixingErrorCode, mix mixType: ByteRTCMixedStreamType) {
        ToastComponents.shared.show(withMessage: "onMixingEvent:\(event.rawValue) taskId:\(taskId) errorCode:\(errorCode.rawValue) + mixType:\(mixType.rawValue)")
    }
    
}
