//
//  AudioSEI.swift
//  ApiExample
//
//  Created by bytedance on 2024/1/18.
//  Copyright © 2021 bytedance. All rights reserved.
//

import UIKit
import SnapKit
import VolcEngineRTC

class AudioSEIViewController: BaseViewController, ByteRTCVideoDelegate, ByteRTCRoomDelegate {
    
    var rtcVideo: ByteRTCVideo?
    var rtcRoom: ByteRTCRoom?
    
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
        
        // 开启本地音频采集
        self.rtcVideo?.startAudioCapture()
    }
    
    // 发送SEI信息
    @objc func sendSEIMessage()  {
        let message = self.seiTextFieldView.text;
        
        if !message!.isEmpty, let data = message?.data(using: .utf8) {
            let config = ByteRTCStreamSycnInfoConfig.init()
            config.streamIndex = .indexMain
            config.streamType = .audio
            config.repeatCount = 3
            self.rtcVideo?.sendStreamSyncInfo(data, config: config)
        } else {
            ToastComponents.shared.show(withMessage: "本端不能发送空消息")
        }
    }
    
    func createUI() -> Void {

        view.addSubview(roomSettingItem)
        view.addSubview(userSettingItem)
        view.addSubview(joinButton)
        
        roomSettingItem.snp.makeConstraints { make in
            make.top.equalTo(topView.snp.bottom).offset(10)
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
        
        view.addSubview(receivedSEIItem)
        receivedSEIItem.snp.makeConstraints { make in
            make.top.equalTo(sendButton.snp.bottom).offset(20)
            make.left.equalToSuperview().offset(10)
            make.right.equalToSuperview().offset(-10)
            make.height.equalTo(30)
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
        settingView.inputTextField.keyboardType = .default
        settingView.title = "SEI信息"
        return settingView
    }()
    
    lazy var sendButton: UIButton = {
        let button = BaseButton()
        button.setTitle("发送SEI", for: .normal)
        button.addTarget(self, action: #selector(sendSEIMessage), for: .touchUpInside)
        return button
    }()
    
    lazy var receivedSEIItem: TextFieldView = {
        let settingView = TextFieldView()
        settingView.title = "本端收到的SEI信息"
        return settingView
    }()
    
    // MARK: ByteRTCVideoDelegate & ByteRTCRoomDelegate
    //进房状态
    func rtcRoom(_ rtcRoom: ByteRTCRoom, onRoomStateChanged roomId: String, withUid uid: String, state: Int, extraInfo: String) {
        ToastComponents.shared.show(withMessage: "onRoomStateChanged uid: \(uid) state:\(state)")
        
    }
    
    // 远端用户发布流
    func rtcRoom(_ rtcRoom: ByteRTCRoom, onUserPublishStream userId: String, type: ByteRTCMediaStreamType) {
        ToastComponents.shared.show(withMessage: "onUserPublishStream uid: \(userId) type = \(type)")
    }
    
     // 远端用户取消发布流
    func rtcRoom(_ rtcRoom: ByteRTCRoom, onUserUnpublishStream userId: String, type: ByteRTCMediaStreamType, reason: ByteRTCStreamRemoveReason) {
        ToastComponents.shared.show(withMessage: "onUserUnpublishStream uid: \(userId)")
        
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
    func rtcEngine(_ engine: ByteRTCVideo, onStreamSyncInfoReceived remoteStreamKey: ByteRTCRemoteStreamKey, streamType: ByteRTCSyncInfoStreamType, data: Data) {
        if let string = String(data: data, encoding: .utf8) {
            ToastComponents.shared.show(withMessage: "onStreamSyncInfoReceived uid: \(remoteStreamKey.userId!) streamType = \(streamType.rawValue) data = \(string)")
            self.receivedSEIItem.text = "uid = \(remoteStreamKey.userId ?? ""), data = \(string)"
        }
    }
}

