/**
* 功能名称： VolcEngineRTC 视频常用配置
* 功能简单描述：修改视频常用的采集、编码参数，设置旋转角度、水印等功能
* 参考文档：https://www.volcengine.com/docs/6348/70122
*
* 此功能涉及的API及回调：
*     createRTCVideo 创建引擎
*     destroyRTCVideo 销毁引擎
*     startAudioCapture 开启音频采集
*     startVideoCapture 开启视频采集
*     createRTCRoom 创建RTC房间
*     joinRoom 进入RTC房间
*     leaveRoom 离开RTC房间
*     destroy 销毁RTC房间
*
*     setVideoCaptureConfig 设置 RTC SDK 内部采集时的视频采集参数
*     setMaxVideoEncoderConfig 设置视频编码参数
*     setLocalVideoMirrorType 为采集到的视频流开启镜像
*
*     onRoomStateChanged 房间状态回调
*     onLeaveRoom 离房回调
*     onUserJoined 用户加入回调
*     onUserLeave  用户离开回调
*     onUserPublishStream 用户发流回调
*     onUserUnpublishStream 用户停止发流回调
*

*
* Demo实现时的逻辑
*    本Demo演示功能：视频常用参数的设置
*    为了展示简单，所有功能的token都由客户端生成，接口Utils::generateToken，接入SDK时建议将Token生成逻辑放在服务端
*/


import UIKit
import SnapKit
import VolcEngineRTC

class CommonVideoConfigViewController: BaseViewController, ByteRTCVideoDelegate, ByteRTCRoomDelegate {
    
    var rtcVideo: ByteRTCVideo?
    var rtcRoom: ByteRTCRoom?
    var captureConfig: ByteRTCVideoCaptureConfig?
    var encoderCfg : ByteRTCVideoEncoderConfig?
    
    var users : Array = Array<ByteRTCRemoteStreamKey>()
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        self.createUI()
        self.buildRTCEngine()
        self.buildActions()
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
        
        // 设置视频采集参数
        let config = ByteRTCVideoCaptureConfig.init()
        config.preference = .mannal
        config.videoSize = CGSize(width: 480, height: 640)
        config.frameRate = 15
        self.captureConfig = config;
        self.rtcVideo?.setVideoCaptureConfig(config)
        
        // 设置视频发布参数
        let encoderCfg = ByteRTCVideoEncoderConfig.init()
        encoderCfg.width = 480
        encoderCfg.height = 640
        encoderCfg.frameRate = 15
        encoderCfg.maxBitrate = 1000
        self.encoderCfg = encoderCfg
        self.rtcVideo?.setMaxVideoEncoderConfig(encoderCfg)
        
        // 开启本地音视频采集
        self.rtcVideo?.startVideoCapture()
        self.rtcVideo?.startAudioCapture()
        
        self.bindLocalRenderView()
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
    
    func buildActions() {
        weak var weakSelf = self
        
        // 设置采集分辨率
        self.resolutionSheetView.didSelectOption = {(value) in
            var videoSize:CGSize?
            
            switch value {
            case 0:
                videoSize = CGSizeMake(480, 640)
            case 1:
                videoSize = CGSizeMake(720, 1280)
            case 2:
                videoSize = CGSizeMake(1080, 1920)
            default:
                videoSize = CGSizeMake(480, 640)
            }
            
            weakSelf?.captureConfig?.videoSize = videoSize!
            
            weakSelf?.rtcVideo?.setVideoCaptureConfig(weakSelf?.captureConfig)
        }
        
        // 设置采集偏好设置
        self.captureModeSheetView.didSelectOption = {(value) in
            
            switch value {
            case 0:
                weakSelf?.captureConfig?.preference = .auto
            case 1:
                weakSelf?.captureConfig?.preference = .mannal
            case 2:
                weakSelf?.captureConfig?.preference = .autoPerformance
            default:
                weakSelf?.captureConfig?.preference = .auto
            }
            
            weakSelf?.rtcVideo?.setVideoCaptureConfig(weakSelf?.captureConfig)
        }
        
        // 设置采集帧率
        self.captureFpsSheetView.didSelectOption = {(value) in
            weakSelf?.captureConfig?.frameRate = Int(value)
            weakSelf?.rtcVideo?.setVideoCaptureConfig(weakSelf?.captureConfig)
        }
        
        // 设置编码分辨率
        self.encoderResolutionSheetView.didSelectOption = {(value) in
            
            switch value {
            case 0:
                weakSelf?.encoderCfg?.width = 480
                weakSelf?.encoderCfg?.height = 640
            case 1:
                weakSelf?.encoderCfg?.width = 720
                weakSelf?.encoderCfg?.height = 1280
            case 2:
                weakSelf?.encoderCfg?.width = 1080
                weakSelf?.encoderCfg?.height = 1920
            default:
                weakSelf?.encoderCfg?.width = 480
                weakSelf?.encoderCfg?.height = 640
            }
            
            weakSelf?.rtcVideo?.setMaxVideoEncoderConfig(weakSelf?.encoderCfg)
        }
        
        // 设置帧率
        self.fpsSheetView.didSelectOption = {(value) in
            weakSelf?.encoderCfg?.frameRate = Int(value)
            
            weakSelf?.rtcVideo?.setMaxVideoEncoderConfig(weakSelf?.encoderCfg)
        }
        
        // 设置最大码率
        self.maxBitrateSettingItem.onValueChanged = {(value) in
            weakSelf?.encoderCfg?.maxBitrate = Int(value)!
            weakSelf?.rtcVideo?.setMaxVideoEncoderConfig(weakSelf?.encoderCfg)
        }
        
        // 设置最低码率
        self.maxBitrateSettingItem.onValueChanged = {(value) in
            weakSelf?.encoderCfg?.minBitrate = Int(value)!
            weakSelf?.rtcVideo?.setMaxVideoEncoderConfig(weakSelf?.encoderCfg)
        }
        
        // 设置编码策略偏好
        self.encodePrefrenceSheetView.didSelectOption = {(value) in
            weakSelf?.encoderCfg?.encoderPreference = ByteRTCVideoEncoderPreference(rawValue: value)!
            
            weakSelf?.rtcVideo?.setMaxVideoEncoderConfig(weakSelf?.encoderCfg)
        }
        
        // 设置本地渲染填充模式
        self.localRenderModeSheetView.didSelectOption = {(value) in
            weakSelf?.rtcVideo?.updateLocalVideoCanvas(.indexMain, withRenderMode: ByteRTCRenderMode(rawValue: UInt(value)+1)!, withBackgroundColor: 0xffffff)
        }
        
        // 设置本地视频镜像模式
        self.localMirrorModeSheetView.didSelectOption = {(value) in
            var mirrorType:ByteRTCMirrorType?
            switch value {
            case 0:
                mirrorType = ByteRTCMirrorType.none
            case 1:
                mirrorType = ByteRTCMirrorType.render
            case 2:
                mirrorType = ByteRTCMirrorType.renderAndEncoder
            default:
                mirrorType = ByteRTCMirrorType.none
            }
            
            weakSelf?.rtcVideo?.setLocalVideoMirrorType(mirrorType!)
        }
        
        // 设置远端渲染填充模式
        self.remoteRenderModeSheetView.didSelectOption = {[weak self] value in
            weak var weakSelf = self

            var remoteUser:ByteRTCRemoteStreamKey?
            
            if let users = self?.users {
                for streamKey in users {
                    if remoteUser == nil && streamKey.roomId == self?.roomSettingItem.text {
                        remoteUser = streamKey
                    }
                }
            }
            
            if (remoteUser != nil) {
                weakSelf?.rtcVideo?.updateRemoteStreamVideoCanvas(remoteUser!, withRenderMode:  ByteRTCRenderMode(rawValue: UInt(value)+1)!, withBackgroundColor: 0xffffff)
            }
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
        // scrollView
        self.view.addSubview(scrollView)
        scrollView.snp.makeConstraints { make in
            make.top.equalTo(topView.snp.bottom)
            make.left.right.bottom.equalToSuperview()
        }
        
        // 内容视图
        let view = UIView()
        scrollView.addSubview(view)
        
        view.snp.makeConstraints { make in
            make.edges.equalToSuperview()
            make.width.equalToSuperview()
        }

        // 添加UI
        view.addSubview(containerView)
        containerView.snp.makeConstraints { make in
            make.top.left.right.equalToSuperview()
            make.height.equalTo(scrollView).multipliedBy(0.4)
        }
        
        containerView.addSubview(localView)
        containerView.addSubview(firstRemoteView)
        
        localView.snp.makeConstraints { make in
            make.left.top.equalTo(self.containerView)
            make.width.equalTo(self.containerView).multipliedBy(0.5)
            make.height.equalTo(self.containerView)
        }
        
        firstRemoteView.snp.makeConstraints { make in
            make.right.top.equalTo(self.containerView)
            make.width.equalTo(self.containerView).multipliedBy(0.5)
            make.height.equalTo(self.containerView)        }
        
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
            make.top.equalTo(roomSettingItem.snp.bottom).offset(20)
            make.left.equalToSuperview().offset(10)
            make.right.equalToSuperview().offset(-10)
            make.height.equalTo(36)
        }
        
        view.addSubview(renderLabel)
        renderLabel.snp.makeConstraints { make in
            make.top.equalTo(joinButton.snp.bottom).offset(20)
            make.left.equalToSuperview().offset(10)
            make.right.equalToSuperview().offset(-10)
        }
        
        view.addSubview(localRenderModeSheetView)
        view.addSubview(remoteRenderModeSheetView)
        view.addSubview(localMirrorModeSheetView)
        
        localRenderModeSheetView.snp.makeConstraints { make in
            make.top.equalTo(renderLabel.snp.bottom).offset(10)
            make.left.equalToSuperview().offset(10)
            make.right.equalToSuperview().offset(-10)
            
        }

        remoteRenderModeSheetView.snp.makeConstraints { make in
            make.top.equalTo(localRenderModeSheetView.snp.bottom).offset(10)
            make.left.equalToSuperview().offset(10)
            make.right.equalToSuperview().offset(-10)
        }
        
        localMirrorModeSheetView.snp.makeConstraints { make in
            make.top.equalTo(remoteRenderModeSheetView.snp.bottom).offset(10)
            make.left.equalToSuperview().offset(10)
            make.right.equalToSuperview().offset(-10)
        }
        
        
        view.addSubview(captureLabel)
        captureLabel.snp.makeConstraints { make in
            make.top.equalTo(localMirrorModeSheetView.snp.bottom).offset(20)
            make.left.equalToSuperview().offset(10)
            make.right.equalToSuperview().offset(-10)
        }

        view.addSubview(resolutionSheetView)
        view.addSubview(captureModeSheetView)
        view.addSubview(captureFpsSheetView)
        
        resolutionSheetView.snp.makeConstraints { make in
            make.top.equalTo(captureLabel.snp.bottom).offset(20)
            make.left.equalToSuperview().offset(10)
            make.right.equalToSuperview().offset(-10)
        }
        
        captureModeSheetView.snp.makeConstraints { make in
            make.top.equalTo(resolutionSheetView.snp.bottom).offset(20)
            make.left.equalToSuperview().offset(10)
            make.right.equalToSuperview().offset(-10)
        }
        
        captureFpsSheetView.snp.makeConstraints { make in
            make.top.equalTo(captureModeSheetView.snp.bottom).offset(20)
            make.left.equalToSuperview().offset(10)
            make.right.equalToSuperview().offset(-10)
        }
        
        view.addSubview(encodeLabel)
        encodeLabel.snp.makeConstraints { make in
            make.top.equalTo(captureFpsSheetView.snp.bottom).offset(20)
            make.left.equalToSuperview().offset(10)
        }
        
        view.addSubview(encoderResolutionSheetView)
        encoderResolutionSheetView.snp.makeConstraints { make in
            make.top.equalTo(encodeLabel.snp.bottom).offset(20)
            make.left.equalToSuperview().offset(10)
            make.right.equalToSuperview().offset(-10)
        }
        
        view.addSubview(fpsSheetView)
        fpsSheetView.snp.makeConstraints { make in
            make.top.equalTo(encoderResolutionSheetView.snp.bottom).offset(20)
            make.left.equalToSuperview().offset(10)
            make.right.equalToSuperview().offset(-10)
        }
        
        view.addSubview(maxBitrateSettingItem)
        maxBitrateSettingItem.snp.makeConstraints { make in
            make.top.equalTo(fpsSheetView.snp.bottom).offset(20)
            make.left.equalToSuperview().offset(10)
        }
        
        view.addSubview(minBitrateSettingItem)
        minBitrateSettingItem.snp.makeConstraints { make in
            make.centerY.equalTo(maxBitrateSettingItem)
            make.right.equalToSuperview().offset(-10)
            make.width.equalTo(maxBitrateSettingItem)
        }
        
        view.addSubview(encodePrefrenceSheetView)
        encodePrefrenceSheetView.snp.makeConstraints { make in
            make.top.equalTo(minBitrateSettingItem.snp.bottom).offset(20)
            make.left.equalToSuperview().offset(10)
            make.right.equalToSuperview().offset(-10)
            make.bottom.equalToSuperview().offset(-10)
        }
        
    }
    
    // MARK: Lazy laod
    lazy var scrollView: UIScrollView = {
        let scrollView = UIScrollView()
        scrollView.showsVerticalScrollIndicator = false
        return scrollView
    }()
    
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
    
    lazy var renderLabel: UILabel = {
        let label = UILabel()
        label.text = "渲染设置"
        label.font = UIFont.boldSystemFont(ofSize: 18)
        return label
    }()
    
    lazy var captureLabel: UILabel = {
        let label = UILabel()
        label.text = "采集设置"
        label.font = renderLabel.font
        return label
    }()
    
    lazy var resolutionSheetView: ActionSheetView = {
        let actionSheetView = ActionSheetView.init(title: "采集分辨率", optionArray: ["640*480","1280*720","1920*1080"], defaultIndex: 0)
        actionSheetView.presentingViewController = self
        
        return actionSheetView
    }()
    
    lazy var captureModeSheetView: ActionSheetView = {
        let actionSheetView = ActionSheetView.init(title: "视频采集模式", optionArray: ["Auto","mannal","autoPerformance"], defaultIndex: 0)
        actionSheetView.presentingViewController = self
        
        return actionSheetView
    }()
    
    lazy var captureFpsSheetView: ActionSheetView = {
        let actionSheetView = ActionSheetView.init(title: "采集帧率", optionArray: ["15","30","60"], defaultIndex: 0)
        actionSheetView.presentingViewController = self
        
        return actionSheetView
    }()
    
    lazy var encoderResolutionSheetView: ActionSheetView = {
        let actionSheetView = ActionSheetView.init(title: "编码分辨率", optionArray: ["640*480","1280*720","1920*1080"], defaultIndex: 0)
        actionSheetView.presentingViewController = self
        
        return actionSheetView
    }()
    
    lazy var encodeLabel: UILabel = {
        let label = UILabel()
        label.text = "编码设置"
        label.font = renderLabel.font
        return label
    }()
    
    lazy var fpsSheetView: ActionSheetView = {
        let actionSheetView = ActionSheetView.init(title: "编码帧率", optionArray: ["15","30","60"], defaultIndex: 0)
        actionSheetView.presentingViewController = self
        
        return actionSheetView
    }()
    
    lazy var maxBitrateSettingItem: SettingItemView = {
        let settingView = SettingItemView()
        settingView.title = "最大码率"
        return settingView
    }()
    
    lazy var minBitrateSettingItem: SettingItemView = {
        let settingView = SettingItemView()
        settingView.title = "最小码率"
        return settingView
    }()
    
    lazy var encodePrefrenceSheetView: ActionSheetView = {
        let actionSheetView = ActionSheetView.init(title: "编码策略", optionArray: ["Disable","MaintainFramerate","MaintainQuality","Balance"], defaultIndex: 0)
        actionSheetView.presentingViewController = self
        
        return actionSheetView
    }()
    
    lazy var localRenderModeSheetView: ActionSheetView = {
        let actionSheetView = ActionSheetView.init(title: "本地渲染模式", optionArray: ["Hidden","Fit","Fill"], defaultIndex: 0)
        actionSheetView.presentingViewController = self
        
        return actionSheetView
    }()
    
    lazy var localMirrorModeSheetView: ActionSheetView = {
        let actionSheetView = ActionSheetView.init(title: "镜像模式", optionArray: ["None","Render","RenderAndEncoder"], defaultIndex: 0)
        actionSheetView.presentingViewController = self
        
        return actionSheetView
    }()
    
    lazy var remoteRenderModeSheetView: ActionSheetView = {
        let actionSheetView = ActionSheetView.init(title: "远端渲染模式", optionArray: ["Hidden","Fit","Fill"], defaultIndex: 0)
        actionSheetView.presentingViewController = self
        
        return actionSheetView
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
    
    // 本地视频尺寸或者方向发生变化回调
    func rtcEngine(_ engine: ByteRTCVideo, onLocalVideoSizeChanged streamIndex: ByteRTCStreamIndex, withFrameInfo frameInfo: ByteRTCVideoFrameInfo) {
        ToastComponents.shared.show(withMessage: "onLocalVideoSizeChanged width: \(frameInfo.width) height: \(frameInfo.height) rotation: \(frameInfo.rotation)")
    }
    
    // 远端用户加入房间
    func rtcRoom(_ rtcRoom: ByteRTCRoom, onUserJoined userInfo: ByteRTCUserInfo, elapsed: Int) {
        ToastComponents.shared.show(withMessage: "onUserJoined uid: \(userInfo.userId)")
        
    }
    
    // 远端用户离开房间
    func rtcRoom(_ rtcRoom: ByteRTCRoom, onUserLeave uid: String, reason: ByteRTCUserOfflineReason) {
        ToastComponents.shared.show(withMessage: "onUserLeave uid: \(uid)")
        
    }
}

