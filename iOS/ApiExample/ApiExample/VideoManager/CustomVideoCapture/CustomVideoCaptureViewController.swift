//
//  CustomVideoCaptureViewController.swift
//  ApiExample
//
//  Created by bytedance on 2024/3/21.
//  Copyright © 2021 bytedance. All rights reserved.
//

import UIKit
import SnapKit
import VolcEngineRTC

class CustomVideoCaptureViewController: BaseViewController, ByteRTCEngineDelegate, ByteRTCRoomDelegate, CameraDelegate {
    
    var rtcVideo: ByteRTCEngine?
    var rtcRoom: ByteRTCRoom?
    var userVideoStreamMap: Dictionary = Dictionary<String, ByteRTCStreamInfo>()

    
    var customCamera: CustomVideoCapture?
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        self.createUI()
        self.buildRTCEngine()
        self.buildActions()
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
        self.rtcVideo?.startAudioCapture()
        
        // 开启自定义采集
        self.rtcVideo?.setVideoSourceType(.external)
        self.customCamera = CustomVideoCapture()
        self.customCamera?.delegate = self
        
        self.customCamera?.start()
        
        self.bindLocalRenderView()
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
        var roomId: String?
        var remoteUserId: String?
        
        for (_, info) in self.userVideoStreamMap {
            roomId = info.roomId
            remoteUserId = info.userId
            break
        }
        
        if let remoteUserId = remoteUserId, let roomId = roomId {
            self.bindRemoteRenderView(view: self.firstRemoteView, roomId: roomId, userId: remoteUserId)
        }
    }
    
    func buildActions() {
        weak var weakSelf = self
     
        // 设置格式
        self.captureFormatSheetView.didSelectOption = {(value) in

            if (value == 0) {
                weakSelf?.customCamera?.updateFormat(to: kCVPixelFormatType_32BGRA)
                ToastComponents.shared.show(withMessage: "BGRA")

            } else {
                weakSelf?.customCamera?.updateFormat(to: kCVPixelFormatType_420YpCbCr8BiPlanarVideoRange)
                ToastComponents.shared.show(withMessage: "NV12")
            }
            
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
            make.height.equalTo(containerView.snp.width)
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

        view.addSubview(captureFormatSheetView)
        captureFormatSheetView.snp.makeConstraints { make in
            make.top.equalTo(containerView.snp.bottom).offset(10)
            make.left.equalTo(containerView)
            make.right.equalToSuperview()
            make.height.equalTo(30)
        }
        
        view.addSubview(roomSettingItem)
        view.addSubview(userSettingItem)
        view.addSubview(joinButton)
        
        roomSettingItem.snp.makeConstraints { make in
            make.top.equalTo(captureFormatSheetView.snp.bottom).offset(10)
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
    
    lazy var captureFormatSheetView: ActionSheetView = {
        let actionSheetView = ActionSheetView.init(title: "采集格式", optionArray: ["BGRA","NV12"], defaultIndex: 0)
        actionSheetView.presentingViewController = self
        
        return actionSheetView
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
    
    func camera(_ camera: CustomVideoCapture, didOutput sampleBuffer: CMSampleBuffer) {
        
        self.pushExternalVideoFrame(sampleBuffer)
    }
    
    func pushExternalVideoFrame(_  sampleBuffer: CMSampleBuffer) {
        
        guard let pixelBufferRef = CMSampleBufferGetImageBuffer(sampleBuffer) else {
            return
        }
        
        let newFrame = ByteRTCVideoFrameData()
        newFrame.bufferType = .cvPixelBuffer
        newFrame.timestamp = getCMTime()
        newFrame.width = Int32(CVPixelBufferGetWidth(pixelBufferRef))
        newFrame.height = Int32(CVPixelBufferGetHeight(pixelBufferRef))
        newFrame.cvpixelbuffer = pixelBufferRef
        newFrame.rotation = .rotation90
        newFrame.seiData = nil
        
        // 推送视频帧
        rtcVideo?.pushExternalVideoFrame(newFrame)
    }
    
    func getCMTime() -> CMTime {
        let value = Int64(CACurrentMediaTime() * 1000000000)
        let time = CMTimeMake(value: value, timescale: 1000000000)
        return time
    }
}

