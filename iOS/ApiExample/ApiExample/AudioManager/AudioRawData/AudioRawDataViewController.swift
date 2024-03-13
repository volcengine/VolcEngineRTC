/**
* 功能名称： VolcEngineRTC 原始音频数据
* 功能简单描述：通过注册回调接口，获取原始的指定类型的音频数据
* 参考文档：
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
*     registerAudioFrameObserver  注册音频数据回调观察者
*     enableAudioFrameCallback  设置并开启指定的音频数据帧回调
*
*     onRoomStateChanged 房间状态回调
*     onLeaveRoom 离房回调
*     onUserJoined 用户加入回调
*     onUserLeave  用户离开回调
*     onUserPublishStream 用户发流回调
*     onUserUnpublishStream 用户停止发流回调
*
*     onRecordAudioFrame 返回麦克风录制的音频数据
*     onPlaybackAudioFrame 返回订阅的所有远端用户混音后的音频数据
*     onRemoteUserAudioFrame 返回远端单个用户的音频数据
*     onMixedAudioFrame  返回本地麦克风录制和订阅的所有远端用户混音后的音频数据
*
* Demo实现时的逻辑
*    本Demo演示功能：获取原始音频数据的代码实现流程
*    ByteRTCAudioFrameObserver 回调的数据不支持修改，修改无效
*    如果想在发送音频前进行处理，请使用 自定义音频处理 接口，参考文档：https://www.volcengine.com/docs/6348/80635
*    为了展示简单，所有功能的token都由客户端TokenGenerator类生成，请在真正接入时视具体情况而定
*/


import UIKit
import SnapKit
import VolcEngineRTC


class AudioRawDataViewController: BaseViewController, ByteRTCVideoDelegate, ByteRTCRoomDelegate,ByteRTCAudioFrameObserver {
    
    var rtcVideo: ByteRTCVideo?
    var rtcRoom1: ByteRTCRoom?
    var lastLogTime: Date?

    override func viewDidLoad() {
        super.viewDidLoad()
        
        self.createUI()
        self.buildRTCEngine()
        self.bindLocalRenderView()
        self.buildActions()
    }
    
    deinit {
        self.rtcVideo!.registerAudioFrameObserver(nil)

        self.rtcRoom1?.leaveRoom()
        self.rtcRoom1?.destroy()
        self.rtcRoom1 = nil
        
        ByteRTCVideo.destroyRTCVideo()
        self.rtcVideo = nil
    }
    
    // MARK: Private method
    
    @objc func joinRoom()  {
        let roomId = self.roomTextField.text ?? ""
        let userId = self.userTextField.text ?? ""
        
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
            self.rtcRoom1 = self.rtcVideo?.createRTCRoom(roomId)
            self.rtcRoom1?.delegate = self
            
            // 获取token,建议从服务端获取
            let token = generatorToken(roomId: roomId, userId: userId)
            
            let userInfo = ByteRTCUserInfo.init()
            userInfo.userId = userId
            
            let roomCfg = ByteRTCRoomConfig.init()
            roomCfg.isAutoPublish = true
            roomCfg.isAutoSubscribeAudio = true
            roomCfg.isAutoSubscribeVideo = true
            
            self.rtcRoom1?.joinRoom(token, userInfo: userInfo, roomConfig: roomCfg)
        }
        else {
            joinButton.setTitle("加入房间", for: .normal)
            self.rtcRoom1?.leaveRoom()
        }
    }
    
    func buildRTCEngine() {
        // 创建引擎
        self.rtcVideo = ByteRTCVideo.createRTCVideo(kAppID, delegate: self, parameters: [:])
        
        // 开启本地音视频采集
        self.rtcVideo?.startVideoCapture()
        self.rtcVideo?.startAudioCapture()
        
        self.bindLocalRenderView()
    }
    
    func buildActions() {
        self.rtcVideo!.registerAudioFrameObserver(self)

        // 本地录制
        self.recordSwitch.switchValueChanged = { [weak self] isOn in
            if isOn {
                let audioFormat = ByteRTCAudioFormat.init()
                audioFormat.sampleRate = .rate44100
                audioFormat.channel = .stereo
                audioFormat.samplesPerCall = 0

                self?.rtcVideo?.enableAudioFrameCallback(.record, format: audioFormat)
            } else {
                self?.rtcVideo?.disableAudioFrameCallback(.record)
            }
        }
        
        // 所有远端混音
        self.playbackSwitch.switchValueChanged = { [weak self] isOn in
            if isOn {
                let palyoutFormat = ByteRTCAudioFormat.init()
                palyoutFormat.sampleRate = .rate44100
                palyoutFormat.channel = .stereo
                palyoutFormat.samplesPerCall = 0

                self?.rtcVideo?.enableAudioFrameCallback(.playback, format: palyoutFormat)
            } else {
                self?.rtcVideo?.disableAudioFrameCallback(.playback)
            }
        }
        
        // 本地 + 远端混音
        self.mixedSwitch.switchValueChanged = { [weak self] isOn in
            if isOn {
                let mixedFormat = ByteRTCAudioFormat.init()
                mixedFormat.sampleRate = .rate44100
                mixedFormat.channel = .stereo
                mixedFormat.samplesPerCall = 0

                self?.rtcVideo?.enableAudioFrameCallback(.mixed, format: mixedFormat)
            } else {
                self?.rtcVideo?.disableAudioFrameCallback(.mixed)
            }
        }
        
        // 单个远端
        self.remoteUserSwitch.switchValueChanged = { [weak self] isOn in
            if isOn {
                let remoteFormat = ByteRTCAudioFormat.init()
                remoteFormat.sampleRate = .rateAuto
                remoteFormat.channel = .auto
                remoteFormat.samplesPerCall = 0

                self?.rtcVideo?.enableAudioFrameCallback(.remoteUser, format: remoteFormat)
            } else {
                self?.rtcVideo?.disableAudioFrameCallback(.remoteUser)
            }
        }
        
    }
    
    func bindLocalRenderView() {
        // 设置本地渲染视图
        let canvas = ByteRTCVideoCanvas.init()
        canvas.view = self.localView.videoView
        canvas.renderMode = .hidden
        self.localView.userId = userTextField.text ?? ""
        
        self.rtcVideo?.setLocalVideoCanvas(.indexMain, withCanvas: canvas);
    }
    
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
        self.view.endEditing(true)
    }
    
    func createUI() -> Void {
        
        // 添加视图
        view.addSubview(containerView)
        self.containerView.addSubview(localView)
        
        containerView.snp.makeConstraints { make in
            make.top.equalTo(self.topView.snp.bottom)
            make.left.right.equalTo(self.view)
        }
        
        self.localView.snp.makeConstraints { make in
            make.left.top.equalTo(self.containerView)
            make.width.height.equalTo(self.containerView)
        }
        
        view.addSubview(roomLabel)
        view.addSubview(roomTextField)
        view.addSubview(userLabel)
        view.addSubview(userTextField)
        view.addSubview(joinButton)
        
        roomLabel.snp.makeConstraints { make in
            make.top.equalTo(containerView.snp.bottom).offset(20)
            make.left.equalToSuperview().offset(10)
        }
        
        roomTextField.snp.makeConstraints { make in
            make.centerY.equalTo(roomLabel)
            make.left.equalTo(roomLabel.snp.right).offset(10)
            make.width.equalTo(100)
            make.height.equalTo(30)
        }
        
        userLabel.snp.makeConstraints { make in
            make.centerY.equalTo(roomLabel)
        }
        
        userTextField.snp.makeConstraints { make in
            make.centerY.equalTo(roomLabel)
            make.left.equalTo(userLabel.snp.right).offset(10)
            make.right.equalTo(view).offset(-10)
            make.width.equalTo(100)
            make.height.equalTo(30)
        }
        
        joinButton.snp.makeConstraints { make in
            make.top.equalTo(roomLabel.snp.bottom).offset(20)
            make.left.equalTo(roomLabel)
            make.right.equalTo(view).offset(-10)
            make.height.equalTo(36)
        }
        
        view.addSubview(recordSwitch)
        view.addSubview(playbackSwitch)
        view.addSubview(mixedSwitch)
        view.addSubview(remoteUserSwitch)

        recordSwitch.snp.makeConstraints { make in
            make.top.equalTo(joinButton.snp.bottom).offset(10)
            make.left.equalToSuperview().offset(10)
        }
        
        playbackSwitch.snp.makeConstraints { make in
            make.top.equalTo(recordSwitch.snp.bottom).offset(10)
            make.left.equalToSuperview().offset(10)
        }
        
        mixedSwitch.snp.makeConstraints { make in
            make.top.equalTo(playbackSwitch.snp.bottom).offset(10)
            make.left.equalToSuperview().offset(10)
        }
        
        remoteUserSwitch.snp.makeConstraints { make in
            make.top.equalTo(mixedSwitch.snp.bottom).offset(10)
            make.left.equalToSuperview().offset(10)
            make.bottom.equalTo(self.view).offset(-getSafeAreaInsets().bottom)
        }
    }
    
    // MARK: Lazy laod
    lazy var roomLabel: UILabel = {
        let label = UILabel()
        label.text = "房间"
        return label
    }()
    
    lazy var roomTextField: UITextField = {
        let textField = UITextField()
        textField.borderStyle = .roundedRect
        return textField
    }()
    
    lazy var userLabel: UILabel = {
        let label = UILabel()
        label.text = "用户"
        return label
    }()
    
    lazy var userTextField: UITextField = {
        let textField = UITextField()
        textField.borderStyle = .roundedRect
        return textField
    }()
    
    lazy var joinButton: UIButton = {
        let button = BaseButton.init()
        button.setTitle("加入房间", for: .normal)
        button.addTarget(self, action: #selector(joinRoom), for: .touchUpInside)
        return button
    }()
    
    lazy var recordSwitch: SwitchSettingView = {
        let switchView = SwitchSettingView.init(text: "本地录制音频回调")
        return switchView
    }()
    
    lazy var playbackSwitch: SwitchSettingView = {
        let switchView = SwitchSettingView.init(text: "所有远端音频回调")
        return switchView
    }()
    
    lazy var mixedSwitch: SwitchSettingView = {
        let switchView = SwitchSettingView.init(text: "本地和远端音频回调")
        return switchView
    }()
    
    lazy var remoteUserSwitch: SwitchSettingView = {
        let switchView = SwitchSettingView.init(text: "单个远端音频回调")
        return switchView
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
    
    // MARK: ByteRTCVideoDelegate & ByteRTCRoomDelegate
    //进房状态
    func rtcRoom(_ rtcRoom: ByteRTCRoom, onRoomStateChanged roomId: String, withUid uid: String, state: Int, extraInfo: String) {
        ToastComponents.shared.show(withMessage: "onRoomStateChanged uid: \(uid) state:\(state)")
        
    }
    
    // MARK: ByteRTCAudioFrameObserver
    func onRecord(_ audioFrame: ByteRTCAudioFrame) {
        print("onRecord audioFrame")
        
        if checkLogTimeVaild() {
            ToastComponents.shared.show(withMessage: "onRecord audioFrame")
        }
    }
    
    func onPlaybackAudioFrame(_ audioFrame: ByteRTCAudioFrame) {
        print("onPlaybackAudioFrame")
        
        if checkLogTimeVaild() {
            ToastComponents.shared.show(withMessage: "onPlaybackAudioFrame")
        }
    }
    
    func onMixedAudioFrame(_ audioFrame: ByteRTCAudioFrame) {
        print("onMixedAudioFrame")
        
        if checkLogTimeVaild() {
            ToastComponents.shared.show(withMessage: "onMixedAudioFrame")
        }
    }
    
    func onRemoteUserAudioFrame(_ streamKey: ByteRTCRemoteStreamKey, audioFrame: ByteRTCAudioFrame) {
        print("onRemoteUserAudioFrame")
        
        if checkLogTimeVaild() {
            ToastComponents.shared.show(withMessage: "onRemoteUserAudioFrame")
        }
    }
    
    // 检查距离上次log是否超过5秒
    func checkLogTimeVaild() -> Bool {
        let currentTime = Date()
        if let lastLogTime = self.lastLogTime, currentTime.timeIntervalSince(lastLogTime) < 5 {
            return false
        }
        
        self.lastLogTime = currentTime
        return true
    }
}
