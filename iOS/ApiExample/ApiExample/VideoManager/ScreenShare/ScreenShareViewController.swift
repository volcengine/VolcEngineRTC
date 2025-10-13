
import UIKit
import AVKit
import SnapKit
import VolcEngineRTC

class ScreenShareViewController: BaseViewController, ByteRTCEngineDelegate, ByteRTCRoomDelegate {
    
    var rtcVideo: ByteRTCEngine?
    var rtcRoom: ByteRTCRoom?
    
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
            self.rtcRoom?.leave()
        }
    }
    
    @objc func startScreenShare()  {
        shareButton.isSelected = !shareButton.isSelected

        if shareButton.isSelected {
            self.rtcVideo?.startScreenCapture(ByteRTCScreenMediaType.videoAndAudio, bundleId: EXTENSION_BUNDLE_ID)
        } else {
            self.rtcVideo?.stopScreenCapture()
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
        
        // 设置屏幕共享参数
        self.rtcVideo?.setExtensionConfig(APP_GROUP)
    }
    
    func bindLocalRenderView() {
        // 设置本地渲染视图
        let canvas = ByteRTCVideoCanvas.init()
        canvas.view = self.localView.videoView
        canvas.renderMode = .hidden
        self.localView.userId = userSettingItem.text ?? ""
        
        self.rtcVideo?.setLocalVideoCanvas(withCanvas: canvas);
    }
    
    func bindRemoteRenderView(streamId: String, userId: String) {
        let canvas = ByteRTCVideoCanvas.init()
        canvas.view = self.firstRemoteView.videoView
        canvas.renderMode = .hidden
        self.firstRemoteView.userId = userId
    
        self.rtcVideo?.setRemoteVideoCanvas(streamId, withCanvas: canvas)
    }
    
    func createUI() -> Void {
        
        // 添加视图
        view.addSubview(containerView)
        self.containerView.addSubview(localView)
        self.containerView.addSubview(firstRemoteView)
        
        containerView.snp.makeConstraints { make in
            make.top.equalTo(topView.snp.bottom)
            make.height.equalTo(containerView.snp.width)
            make.left.right.equalTo(self.view)
        }
        
        self.localView.snp.makeConstraints { make in
            make.left.top.equalTo(self.containerView)
            make.height.equalTo(self.containerView)
            make.width.equalTo(self.containerView).multipliedBy(0.5)
        }
        
        self.firstRemoteView.snp.makeConstraints { make in
            make.top.right.equalTo(self.containerView)
            make.bottom.equalTo(self.containerView)
            make.width.equalTo(self.containerView).multipliedBy(0.5)
        }
        
        view.addSubview(roomSettingItem)
        view.addSubview(userSettingItem)
        view.addSubview(joinButton)
        view.addSubview(shareButton)
        
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
        
        shareButton.snp.makeConstraints { make in
            make.top.equalTo(joinButton.snp.bottom).offset(10)
            make.left.right.width.height.equalTo(joinButton)
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
    
    lazy var shareButton: UIButton = {
        let button = BaseButton()
        button.setTitle("开始屏幕共享", for: .normal)
        button.addTarget(self, action: #selector(startScreenShare), for: .touchUpInside)
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
    
    // MARK: ByteRTCEngineDelegate & ByteRTCRoomDelegate
    //进房状态
    func rtcRoom(_ rtcRoom: ByteRTCRoom, onRoomStateChanged roomId: String, withUid uid: String, state: Int, extraInfo: String) {
        ToastComponents.shared.show(withMessage: "onRoomStateChanged uid: \(uid) state:\(state)")
        
    }
    
    // 远端用户发布流
    func rtcRoom(_ rtcRoom:ByteRTCRoom, onUserPublishStreamVideo streamId:String,info:ByteRTCStreamInfo,isPublish:Bool){
        if isPublish {
                DispatchQueue.main.async {
                    self.bindRemoteRenderView(streamId:streamId, userId:info.userId)
                }
        } else {
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
        }
        
    }


    // 屏幕共享状态
    func rtcEngine(_ engine: ByteRTCEngine, onVideoDeviceStateChanged deviceID: String, device_type deviceType: ByteRTCVideoDeviceType, device_state deviceState: ByteRTCMediaDeviceState, device_error deviceError: ByteRTCMediaDeviceError) {
        
        if deviceType == .screenCaptureDevice {
            if deviceState == .stateStarted {
                ToastComponents.shared.show(withMessage: "screen share start")
                // 屏幕共享开始
                DispatchQueue.main.async {
                    self.shareButton.isSelected = true
                    self.shareButton.setTitle("结束共享", for: .normal)
                }
                
            } else if deviceState == .stateStopped || deviceState == .stateRuntimeError {
                ToastComponents.shared.show(withMessage: "screen share stop")
                DispatchQueue.main.async {
                    self.shareButton.isSelected = false
                    self.shareButton.setTitle("开始共享", for: .normal)
                }
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
}

