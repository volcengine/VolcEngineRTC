/**
* 功能名称： VolcEngineRTC 音乐混音
* 功能简单描述：如果需要在通话过程中播放音效或音乐文件等，而且让房间内的其他成员也听到声音，需要使用混音功能。混音功能可以将麦克风采集的音频数据与音频文件、PCM 音频数据等合并为一路音频流后，发布到房间内
* 参考文档：https://www.volcengine.com/docs/6348/70141
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
*     getMediaPlayer 获取音乐播放功能实例
*
*     ByteRTCMediaPlayer API:
*     setEventHandler 设置回调句柄
*     open 打开音乐文件
*     getTotalDuration  获取音乐文件时长
*     getAudioTrackCount  获取当前音乐文件的音轨数
*     getVolume  setVolume 获取/设置播放音量
*     pause  resume stop 暂停 恢复 停止
*     setAudioPitch 变调
*     setPosition getPosition 设置/获取播放位置
*     setAudioDualMonoMode selectAudioTrack 设置声道模式
*     pushExternalAudioFrame 推送PCM数据
*     openWithCustomSource 打开PCM文件
*
*     onMediaPlayerStateChanged   播放状态改变时回调
*     onMediaPlayerPlayingProgress  播放进度周期性回调
*     onRoomStateChanged 房间状态回调
*     onLeaveRoom 离房回调
*     onUserJoined 用户加入回调
*     onUserLeave  用户离开回调
*     onUserPublishStream 用户发流回调
*     onUserUnpublishStream 用户停止发流回调
*
*
*
*
* Demo实现时的逻辑
*    本Demo演示功能：音乐混音功能，仅展示播放音乐和播放PCM两个实例；
*    为了展示简单，所有功能的token都由客户端TokenGenerator类生成，请在真正接入时视具体情况而定
*/


import UIKit
import SnapKit
import VolcEngineRTC

class AudioMediaMixingViewController: BaseViewController, ByteRTCVideoDelegate, ByteRTCRoomDelegate, ByteRTCMediaPlayerEventHandler {
    
    var rtcVideo: ByteRTCVideo?
    var rtcRoom1: ByteRTCRoom?
    var mediaPlayerAudio: ByteRTCMediaPlayer?
    var mediaPlayerPCM: ByteRTCMediaPlayer?
    var audioPlayerId: Int32! = 0
    var pcmPlalerId: Int32! = 1
    var firstPush:Bool = true
    var timer: GCDTimer?
    var startOffset = 0
    
    override func viewWillDisappear(_ animated: Bool) {
        super.viewWillDisappear(animated)
        self.mediaPlayerAudio?.setEventHandler(nil)
        self.mediaPlayerPCM?.setEventHandler(nil)
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        self.createUI()
        self.buildRTCEngine()
        self.buildMediaPlayer()
        self.buildActions()
    }
    
    deinit {
        self.timer?.cancel()
        self.timer = nil
        
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
    
    // 创建音乐混音player
    func buildMediaPlayer() {
        self.mediaPlayerAudio = self.rtcVideo?.getMediaPlayer(audioPlayerId)
        self.mediaPlayerPCM = self.rtcVideo?.getMediaPlayer(pcmPlalerId)
        
        weak var weakSelf = self
        self.mediaPlayerAudio?.setEventHandler(weakSelf)
        self.mediaPlayerPCM?.setEventHandler(weakSelf)
    }
    
    func buildActions() {
        weak var weakSelf = self
        self.audioVolumeSetting.onValueChanged = {(value) in
            weakSelf?.mediaPlayerAudio?.setVolume(Int32(value), type: .playoutAndPublish)
        }
        
        self.audioPitchSetting.onValueChanged = {(value) in
            weakSelf?.mediaPlayerAudio?.setAudioPitch(Int32(value)!)
        }
        
        self.audioPositionSetting.onValueChanged = {(value) in
            weakSelf?.mediaPlayerAudio?.setPosition(Int32(value)!)
        }
        
        self.audioTrackSetting.onValueChanged = {(value) in
            weakSelf?.mediaPlayerAudio?.selectAudioTrack(Int32(value)!)
        }
        
        self.audioSpeedSetting.onValueChanged = {(value) in
            weakSelf?.mediaPlayerAudio?.setPlaybackSpeed(Int32(value)!)
        }
        
        self.channelModeSheetView.didSelectOption = {(value) in
            weakSelf?.mediaPlayerAudio?.setAudioDualMonoMode(ByteRTCAudioMixingDualMonoMode(rawValue: value)!)
        }
        
        self.pcmVolumeSetting.onValueChanged = {(value) in
            weakSelf?.mediaPlayerPCM?.setVolume(Int32(value), type: .playoutAndPublish)
        }
    }
    
    // 开始音乐混音
    @objc func startAudioMix() {
        var filePath = ""
        if "qilixiang.m4a" == self.audioTextField1.text {
            filePath = Bundle.main.path(forResource: "qilixiang.m4a", ofType: "")!
            
        } else if ((self.audioTextField1.text?.hasPrefix("https:")) ?? false) {
            filePath = self.audioTextField1.text!
        } else {
            ToastComponents.shared.show(withMessage: "不支持的格式")
        }
        
        let config = ByteRTCMediaPlayerConfig.init()
        config.type = .playoutAndPublish
        config.playCount = 1
        
        // auto_play=true时自动播放，无需再调用start接口， auto_play=false时，不自动播放，需要调用start接口
        config.autoPlay = false
        
        self.mediaPlayerAudio?.open(filePath, config: config)
        self.mediaPlayerAudio?.start()
        // 每1s回调一次进度
        self.mediaPlayerAudio?.setProgressInterval(1000)
    }
    
    @objc func pauseAudioMix() {
        self.mediaPlayerAudio?.pause()
    }
    
    @objc func resumeAudioMix() {
        self.mediaPlayerAudio?.resume()
    }
    
    @objc func stopAudioMix()  {
        self.mediaPlayerAudio?.stop()
    }
    
    // 开始pcm混音
    @objc func startPcmMix() {
        
        let source = ByteRTCMediaPlayerCustomSource.init()
        source.mode = .push
        source.type = .raw
        
        let config  = ByteRTCMediaPlayerConfig.init()
        config.type = .playoutAndPublish
        config.playCount = 1
        config.autoPlay = true
        
        self.mediaPlayerPCM?.open(with: source, config: config)
        
        self.startOffset = 0
        
        if (self.timer != nil) {
            self.timer?.cancel()
            self.timer = nil
        }
        
        weak var weakSelf = self
        
        // 开启定时器推送数据,10ms间隔
        self.timer = GCDTimer(interval: .milliseconds(10)) {
            weakSelf!.pushPCMData()
        }
        
        self.timer!.start()
    }
    
    @objc func getAudioPosition() {
        let currentPosion = self.mediaPlayerAudio?.getPosition()
        self.currentProgressLabel.text = "\(currentPosion ?? 0)"
    }
    
    func pushPCMData() {
        if let mediaPlayerPCM = self.mediaPlayerPCM {
            var size = 160 * 1 * 2 // 每10ms的数据=采样数 * 声道数 * 采样占字节数,该pcm文件是16000采样率，单声道，每个样本占2个字节
            
            if self.firstPush {
                size = size * 20 // 第一次建议推送200ms数据，避免噪音
                self.firstPush = false
            }
            
            let filePath = Bundle.main.path(forResource: "16k-mono-speech_fft_32s", ofType: "pcm")!
            let url = URL(fileURLWithPath: filePath)
            
            guard let fileData = try? Data(contentsOf: url) else {
                print("Failed to read PCM file data.")
                return
            }
            
            let endOffset = self.startOffset + size
            
            if endOffset >= fileData.count {
                // 如果只播放一次,超出文件长度则停止
                self.stopPcmMix()
                return
                
                // 如果需要重复播放,则从头再读
//                self.startOffset = 0
//                endOffset = self.startOffset + size
            }
            
            let audioData: Data = fileData.subdata(in: startOffset..<endOffset)
            self.startOffset = endOffset
            
            let audioFrame = ByteRTCAudioFrame()
            audioFrame.channel = .mono
            audioFrame.sampleRate = .rate16000
            audioFrame.samples = Int32(size) / 2 // 每个采样占2字节
            audioFrame.buffer = audioData
            
            mediaPlayerPCM.pushExternalAudioFrame(audioFrame)
        }
    }
    
    @objc func stopPcmMix()  {
        self.mediaPlayerPCM?.stop()
        self.timer?.cancel()
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
        localView.snp.makeConstraints { make in
            make.left.top.equalTo(self.containerView)
            make.width.height.equalTo(self.containerView)
        }
        
        view.addSubview(roomLabel)
        view.addSubview(roomTextField)
        view.addSubview(userLabel)
        view.addSubview(userTextField)
        view.addSubview(joinButton)
        
        roomLabel.snp.makeConstraints { make in
            make.top.equalTo(containerView.snp.bottom).offset(10)
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
            make.right.equalTo(self.view).offset(-10)
            make.width.equalTo(100)
            make.height.equalTo(30)
        }
        
        joinButton.snp.makeConstraints { make in
            make.top.equalTo(roomLabel.snp.bottom).offset(20)
            make.left.equalTo(roomLabel)
            make.right.equalTo(userTextField)
            make.height.equalTo(36)
        }
                
        view.addSubview(fileBackgroundView)
        fileBackgroundView.snp.makeConstraints { make in
            make.top.equalTo(joinButton.snp.bottom).offset(20)
            make.left.right.equalTo(joinButton)
            make.height.equalTo(336)
        }
        
        fileBackgroundView.addSubview(audioMixLabel)
        fileBackgroundView.addSubview(audioTextField1)
        fileBackgroundView.addSubview(startButton1)
        fileBackgroundView.addSubview(pauseButton1)
        fileBackgroundView.addSubview(resumeButton1)
        fileBackgroundView.addSubview(stopButton1)
        
        audioMixLabel.snp.makeConstraints { make in
            make.left.top.equalToSuperview().offset(10)
        }
        
        audioTextField1.snp.makeConstraints { make in
            make.top.equalTo(audioMixLabel.snp.bottom).offset(10)
            make.left.equalTo(audioMixLabel)
            make.right.equalToSuperview().offset(-10)
            make.height.equalTo(30)
        }
        
        startButton1.snp.makeConstraints { make in
            make.top.equalTo(audioTextField1.snp.bottom).offset(20)
            make.left.equalTo(audioTextField1)
            make.height.equalTo(36)
        }
        
        pauseButton1.snp.makeConstraints { make in
            make.centerY.equalTo(startButton1)
            make.left.equalTo(startButton1.snp.right).offset(10)
            make.width.height.equalTo(startButton1)
        }

        resumeButton1.snp.makeConstraints { make in
            make.centerY.equalTo(startButton1)
            make.left.equalTo(pauseButton1.snp.right).offset(10)
            make.width.height.equalTo(startButton1)
        }

        stopButton1.snp.makeConstraints { make in
            make.centerY.equalTo(startButton1)
            make.left.equalTo(resumeButton1.snp.right).offset(10)
            make.width.height.equalTo(startButton1)
            make.right.equalTo(audioTextField1)
        }
        
        fileBackgroundView.addSubview(audioVolumeSetting)
        audioVolumeSetting.snp.makeConstraints { make in
            make.top.equalTo(startButton1.snp.bottom).offset(10)
            make.left.equalTo(startButton1)
            make.right.equalTo(stopButton1)
        }
        
        fileBackgroundView.addSubview(totalTimeLabel1)
        totalTimeLabel1.snp.makeConstraints { make in
            make.top.equalTo(audioVolumeSetting.snp.bottom).offset(20)
            make.left.equalToSuperview().offset(10)
        }
        
        fileBackgroundView.addSubview(audioPositionSetting)
        audioPositionSetting.snp.makeConstraints { make in
            make.centerY.equalTo(totalTimeLabel1)
            make.right.equalToSuperview().offset(-10)
        }
        
        fileBackgroundView.addSubview(totalChannelLabel1)
        
        totalChannelLabel1.snp.makeConstraints { make in
            make.top.equalTo(totalTimeLabel1.snp.bottom).offset(20)
            make.left.equalToSuperview().offset(10)
        }
        
        fileBackgroundView.addSubview(audioTrackSetting)
        audioTrackSetting.snp.makeConstraints { make in
            make.centerY.equalTo(totalChannelLabel1)
            make.right.equalToSuperview().offset(-10)
        }
        
        fileBackgroundView.addSubview(audioPitchSetting)
        audioPitchSetting.snp.makeConstraints { make in
            make.top.equalTo(totalChannelLabel1.snp.bottom).offset(20)
            make.left.equalToSuperview().offset(10)
        }
        
        fileBackgroundView.addSubview(audioSpeedSetting)
        audioSpeedSetting.snp.makeConstraints { make in
            make.centerY.equalTo(audioPitchSetting)
            make.right.equalToSuperview().offset(-10)
        }
        
        fileBackgroundView.addSubview(currentPostionLabel)
        fileBackgroundView.addSubview(currentProgressLabel)
        
        currentPostionLabel.snp.makeConstraints { make in
            make.top.equalTo(audioPitchSetting.snp.bottom).offset(20)
            make.left.equalToSuperview().offset(10)
        }
        
        currentProgressLabel.snp.makeConstraints { make in
            make.centerY.equalTo(currentPostionLabel)
            make.left.equalTo(currentPostionLabel.snp.right).offset(10)
        }
        
        fileBackgroundView.addSubview(channelModeSheetView)
        channelModeSheetView.snp.makeConstraints { make in
            make.centerY.equalTo(currentPostionLabel)
            make.right.equalToSuperview().offset(-10)
        }
        
        view.addSubview(pcmBackgroundView)
        
        pcmBackgroundView.snp.makeConstraints { make in
            make.top.equalTo(fileBackgroundView.snp.bottom).offset(20)
            make.left.right.equalTo(joinButton)
            make.height.equalTo(180)
            make.bottom.equalToSuperview().offset(-10)
        }
        
        pcmBackgroundView.addSubview(pcmMixLabel)
        pcmBackgroundView.addSubview(pcmField)

        pcmBackgroundView.addSubview(pcmStartButton)
        pcmBackgroundView.addSubview(pcmStopButton)
        
        pcmBackgroundView.addSubview(pcmVolumeSetting)
        
        pcmMixLabel.snp.makeConstraints { make in
            make.left.top.equalToSuperview().offset(10)
        }
        
        pcmField.snp.makeConstraints { make in
            make.top.equalTo(pcmMixLabel.snp.bottom).offset(10)
            make.left.equalTo(pcmMixLabel)
            make.right.equalToSuperview().offset(-10)
            make.height.equalTo(30)
        }
        
        pcmStartButton.snp.makeConstraints { make in
            make.top.equalTo(pcmField.snp.bottom).offset(20)
            make.left.equalTo(pcmField)
            make.height.equalTo(36)
        }
        
        pcmStopButton.snp.makeConstraints { make in
            make.centerY.equalTo(pcmStartButton)
            make.left.equalTo(pcmStartButton.snp.right).offset(10)
            make.width.height.equalTo(pcmStartButton)
            make.right.equalToSuperview().offset(-10)
        }
        
        pcmVolumeSetting.snp.makeConstraints { make in
            make.top.equalTo(pcmStartButton.snp.bottom).offset(10)
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
        let button = BaseButton()
        button.setTitle("加入房间", for: .normal)
        button.addTarget(self, action: #selector(joinRoom), for: .touchUpInside)
        return button
    }()
    
    lazy var fileBackgroundView: UIView = {
        let view = UIView()
        view.backgroundColor = .groupTableViewBackground
        view.layer.borderWidth = 1
        view.layer.borderColor = UIColor.lightGray.cgColor
        view.layer.cornerRadius = 5
        view.layer.masksToBounds = true
        return view
    }()
    
    lazy var audioMixLabel: UILabel = {
        let label = UILabel()
        label.text = "音频混音"
        return label
    }()
    
    lazy var audioTextField1: TextFieldView = {
        let textField = TextFieldView()
        textField.title = "文件:"
        textField.text = "qilixiang.m4a"
        return textField
    }()
    
    lazy var startButton1: UIButton = {
        let button = BaseButton()
        button.setTitle("开始", for: .normal)
        button.addTarget(self, action: #selector(startAudioMix), for: .touchUpInside)
        return button
    }()
    
    lazy var pauseButton1: UIButton = {
        let button = BaseButton()
        button.setTitle("暂停", for: .normal)
        button.addTarget(self, action: #selector(pauseAudioMix), for: .touchUpInside)
        return button
    }()
    
    lazy var resumeButton1: UIButton = {
        let button = BaseButton()
        button.setTitle("恢复", for: .normal)
        button.addTarget(self, action: #selector(resumeAudioMix), for: .touchUpInside)
        return button
    }()
    
    lazy var stopButton1: UIButton = {
        let button = BaseButton()
        button.setTitle("停止", for: .normal)
        button.addTarget(self, action: #selector(stopAudioMix), for: .touchUpInside)
        return button
    }()
    
    lazy var audioVolumeSetting: SliderView = {
        let settingView = SliderView(minValue: 0, maxValue: 400, defaultValue: 100)
        settingView.title = "音量"
        return settingView
    }()
    
    lazy var audioPitchSetting: SettingItemView = {
        let settingView = SettingItemView()
        settingView.title = "变调"
        settingView.inputTextField.keyboardType = .default
        return settingView
    }()
    
    lazy var totalTimeLabel1: UILabel = {
        let label = UILabel()
        label.text = "总时长"
        return label
    }()
    
    lazy var audioPositionSetting: SettingItemView = {
        let settingView = SettingItemView()
        settingView.title = "设置播放位置"
        return settingView
    }()
    
    lazy var totalChannelLabel1: UILabel = {
        let label = UILabel()
        label.text = "音轨数"
        return label
    }()
    
    lazy var audioTrackSetting: SettingItemView = {
        let settingView = SettingItemView()
        settingView.title = "播放指定音轨"
        return settingView
    }()
    
    lazy var audioSpeedSetting: SettingItemView = {
        let settingView = SettingItemView()
        settingView.title = "播放速度"
        return settingView
    }()
    
    lazy var channelModeSheetView: ActionSheetView = {
        let actionSheetView = ActionSheetView.init(title: "声道模式", optionArray: ["Auto","ModeL","ModeR","ModeMix"], defaultIndex: 0)
        actionSheetView.presentingViewController = self
        
        return actionSheetView
    }()
    
    lazy var currentPostionLabel: UILabel = {
        let label = UILabel()
        label.text = "当前播放进度:"
        return label
    }()
    
    lazy var currentProgressLabel: UILabel = {
        let label = UILabel()
        label.text = ""
        return label
    }()
    
    lazy var pcmBackgroundView: UIView = {
        let view = UIView()
        view.backgroundColor = .groupTableViewBackground
        view.layer.borderWidth = 1
        view.layer.borderColor = UIColor.lightGray.cgColor
        view.layer.cornerRadius = 5
        view.layer.masksToBounds = true
        return view
    }()
    
    lazy var pcmMixLabel: UILabel = {
        let label = UILabel()
        label.text = "PCM混音"
        return label
    }()
    
    lazy var pcmField: TextFieldView = {
        let field = TextFieldView()
        field.title = "PCM文件:"
        field.text = "16k-mono-speech_fft_32s.pcm"
        return field
    }()
    
    lazy var pcmStartButton: UIButton = {
        let button = BaseButton()
        button.setTitle("开始", for: .normal)
        button.addTarget(self, action: #selector(startPcmMix), for: .touchUpInside)
        return button
    }()
    
    lazy var pcmStopButton: UIButton = {
        let button = BaseButton()
        button.setTitle("停止", for: .normal)
        button.addTarget(self, action: #selector(stopPcmMix), for: .touchUpInside)
        return button
    }()
    
    lazy var pcmVolumeSetting: SliderView = {
        let settingView = SliderView(minValue: 0, maxValue: 400, defaultValue: 100)
        settingView.title = "音量"
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
    
    // MARK: ByteRTCVideoDelegate & ByteRTCRoomDelegate
    //进房状态
    func rtcRoom(_ rtcRoom: ByteRTCRoom, onRoomStateChanged roomId: String, withUid uid: String, state: Int, extraInfo: String) {
        ToastComponents.shared.show(withMessage: "onRoomStateChanged uid: \(uid) state:\(state)")
        
    }
    
    // MARK: ByteRTCMediaPlayerEventHandler
    // 混音状态
    func onMediaPlayerStateChanged(_ playerId: Int32, state: ByteRTCPlayerState, error: ByteRTCPlayerError) {
        ToastComponents.shared.show(withMessage: "onMediaPlayerStateChanged playerId: \(playerId) state:\(state.rawValue) error:\(error.rawValue)")
        
        if playerId == self.audioPlayerId && state == .playing {
            let totalTime = self.mediaPlayerAudio?.getTotalDuration()
            let tracks = self.mediaPlayerAudio?.getAudioTrackCount()
            
            DispatchQueue.main.async {
                self.totalTimeLabel1.text = "总时长: \(totalTime ?? 0)"
                self.totalChannelLabel1.text = "音轨数: \(tracks ?? 0)"
            }
            
        }
    }
    
    // 播放进度
    func onMediaPlayerPlayingProgress(_ playerId: Int32, progress: Int64) {
        if playerId == self.audioPlayerId {
            DispatchQueue.main.async {
                self.currentProgressLabel.text = "\(progress)"
            }
        }
    }
    
}
