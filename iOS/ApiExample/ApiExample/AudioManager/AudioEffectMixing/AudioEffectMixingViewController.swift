/**
* 功能名称： VolcEngineRTC 音效混音
* 功能简单描述：如果需要在通话过程中播放音效或音乐文件等，而且让房间内的其他成员也听到声音，需要使用混音功能。混音功能可以将麦克风采集的音频数据与音频文件、PCM 音频数据等合并为一路音频流后，发布到房间内
* 参考文档：https://www.volcengine.com/docs/6348/1178326
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
*     getAudioEffectPlayer 获取音效播放功能实例
*
*     ByteRTCAudioEffectPlayer API:
*     setEventHandler 设置回调句柄
*     preload 预加载音效
*     start 开始播放音效文件
*     stop 停止播放音效文件
*     stopAll 停止播放所有音效文件
*     pauseAll 暂停播放所有音效文件
*     resumeAll 恢复播放所有音效文件
*     getDuration 获取音效文件时长 setPosition 设置播放位置
*     getVolume 获取播放音量  setVolumeAll 设置所有音效的音量大小  setVolume调节指定音效的音量大小
*
*    onAudioEffectPlayerStateChanged   播放状态改变时回调
*
*     onRoomStateChanged 房间状态回调
*     onLeaveRoom 离房回调
*     onUserJoined 用户加入回调
*     onUserLeave  用户离开回调
*     onUserPublishStream 用户发流回调
*     onUserUnpublishStream 用户停止发流回调
*
*     onAudioEffectPlayerStateChanged 播放状态回调
*

*
* Demo实现时的逻辑
*    本Demo演示功能：音效混音功能，添加到列表：设置好地址的音效文件放在待播放队列中
*    为了展示简单，所有功能的token都由客户端TokenGenerator类生成，请在真正接入时视具体情况而定
*/


import UIKit
import SnapKit
import VolcEngineRTC

class AudioEffectMixingViewController: BaseViewController, ByteRTCVideoDelegate, ByteRTCRoomDelegate,ByteRTCAudioEffectPlayerEventHandler {
    
    var rtcVideo: ByteRTCVideo?
    var rtcRoom1: ByteRTCRoom?
    var effectPlayer: ByteRTCAudioEffectPlayer?
    var effectId1: Int32!
    var effectId2: Int32!
    
    override func viewWillDisappear(_ animated: Bool) {
        super.viewWillDisappear(animated)
        self.effectPlayer?.setEventHandler(nil)
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        self.createUI()
        self.buildRTCEngine()
        self.buildEffectPlayer()
        self.buildActions()
    }
    
    deinit {
        self.rtcRoom1?.leaveRoom()
        self.rtcRoom1?.destroy()
        self.rtcRoom1 = nil
        
        ByteRTCVideo.destroyRTCVideo()
        self.rtcVideo = nil
    }
    
    // MARK: Private method
    // 加入房间
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
    
    func buildActions() {
        self.changePositionItem1.onValueChanged = {[weak self] value in
            self?.effectPlayer?.setPosition(self?.effectId1 ?? 0, position: Int32(value)!)
        }
        
        self.changeVolumeSlider1.onValueChanged = {[weak self] value in
            self?.effectPlayer?.setVolume(self?.effectId1 ?? 0, volume: Int32(value))
        }
        
        self.changePositionItem2.onValueChanged = {[weak self] value in
            self?.effectPlayer?.setPosition(self?.effectId2 ?? 0, position: Int32(value)!)
        }
        
        self.changeVolumeSlider2.onValueChanged = {[weak self] value in
            self?.effectPlayer?.setVolume(self?.effectId2 ?? 0, volume: Int32(value))
        }
  
        self.changeAllVolumeSlider.onValueChanged = {[weak self] value in
            self?.effectPlayer?.setVolumeAll(Int32(value))
        }
    }
    
    @objc func preloadFile()  {
        let filePath = Bundle.main.path(forResource: "rtc_test", ofType: "aac")

        self.effectPlayer?.preload(self.effectId1, filePath: filePath)
    }
    
    @objc func unloadFile()  {
        self.effectPlayer?.unload(self.effectId1)
    }
    
    // 开始播放音效1
    @objc func startPlayEffect1()  {
        let filePath = Bundle.main.path(forResource: "rtc_test", ofType: "aac")
        
        let config = ByteRTCAudioEffectPlayerConfig.init()
        config.type = .playoutAndPublish
        config.playCount = -1
        
        //注意：
        //1. 如果你需要经常播放同一个本地文件，可以使用preload 进行预加载，避免内存多次申请释放
        //2. 建议 start 后不要马上调用 getDuration getVolume 等 get 类接口， 内部 start 是异步执行，get 是同步执行，同时调用无法保证前后执行顺序
        //   应该在收到 start 对应的回调后再执行get接口
        let code = self.effectPlayer?.start(self.effectId1, filePath: filePath, config: config)
        print("start play effect1 code = \(code!)")
    }
    
    @objc func pausePlayEffect1()  {
        self.effectPlayer?.pause(self.effectId1)
    }
    
    @objc func resumePlayEffect1()  {
        self.effectPlayer?.resume(self.effectId1)
    }
    
    @objc func stopPlayEffect1()  {
        self.effectPlayer?.stop(self.effectId1)
    }
    
    // 开始播放音效2
    @objc func startPlayEffect2()  {
        let filePath = self.urlTextField.text
        
        let config = ByteRTCAudioEffectPlayerConfig.init()
        config.type = .playoutAndPublish
        config.playCount = 1
        
        let code = self.effectPlayer?.start(self.effectId2, filePath: filePath, config: config)
        print("start play effect2 code = \(code!)")
    }
    
    @objc func pausePlayEffect2()  {
        self.effectPlayer?.pause(self.effectId2)
    }
    
    @objc func resumePlayEffect2()  {
        self.effectPlayer?.resume(self.effectId2)
    }
    
    @objc func stopPlayEffect2()  {
        self.effectPlayer?.stop(self.effectId2)
    }
    
    @objc func pauseAllEffect()  {
        self.effectPlayer?.pauseAll()
    }
    
    @objc func resumeAllEffect()  {
        self.effectPlayer?.resumeAll()
    }
    
    @objc func stopAllEffect()  {
        self.effectPlayer?.stopAll()
    }
    
    func buildRTCEngine() {
        // 创建引擎
        self.rtcVideo = ByteRTCVideo.createRTCVideo(kAppID, delegate: self, parameters: [:])
        
        // 开启本地音视频采集
        self.rtcVideo?.startVideoCapture()
        self.rtcVideo?.startAudioCapture()
        
        self.bindLocalRenderView()
    }
    
    // 获取音效播放器
    func buildEffectPlayer() {
        self.effectPlayer = self.rtcVideo?.getAudioEffectPlayer()
        
        weak var weakSelf = self
        self.effectPlayer?.setEventHandler(weakSelf)
        
        self.effectId1 = 1001
        self.effectId2 = 1002
    }
    
    func bindLocalRenderView() {
        // 设置本地渲染视图
        let canvas = ByteRTCVideoCanvas.init()
        canvas.view = self.localView.videoView
         canvas.renderMode = .hidden
        self.localView.userId = userTextField.text ?? ""
        
        self.rtcVideo?.setLocalVideoCanvas(.indexMain, withCanvas: canvas);
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
            make.height.equalTo(248)
        }
        
        fileBackgroundView.addSubview(fileTitleLabel)
        fileBackgroundView.addSubview(fileTextField)
        
        fileBackgroundView.addSubview(preloadButton)
        fileBackgroundView.addSubview(unloadButton)
        
        fileBackgroundView.addSubview(totalTimeLabel1)
        fileBackgroundView.addSubview(changePositionItem1)
        fileBackgroundView.addSubview(changeVolumeSlider1)

        fileBackgroundView.addSubview(startButton1)
        fileBackgroundView.addSubview(pauseButton1)
        fileBackgroundView.addSubview(resumeButton1)
        fileBackgroundView.addSubview(stopButton1)
        
        fileTitleLabel.snp.makeConstraints { make in
            make.left.top.equalToSuperview().offset(10)
        }
        
        fileTextField.snp.makeConstraints { make in
            make.top.equalTo(fileTitleLabel.snp.bottom).offset(10)
            make.left.equalTo(fileTitleLabel)
            make.right.equalToSuperview().offset(-10)
            make.height.equalTo(30)
        }
        
        preloadButton.snp.makeConstraints { make in
            make.top.equalTo(fileTextField.snp.bottom).offset(10)
            make.left.equalTo(fileTextField)
            make.height.equalTo(30)
        }
        
        unloadButton.snp.makeConstraints { make in
            make.top.equalTo(preloadButton)
            make.left.equalTo(preloadButton.snp.right).offset(20)
            make.width.height.equalTo(preloadButton)
            make.right.equalTo(fileTextField)
        }
        
        totalTimeLabel1.snp.makeConstraints { make in
            make.top.equalTo(preloadButton.snp.bottom).offset(10)
            make.left.equalTo(preloadButton).offset(10)
        }

        changePositionItem1.snp.makeConstraints { make in
            make.centerY.equalTo(totalTimeLabel1)
            make.right.equalTo(unloadButton)
        }

        changeVolumeSlider1.snp.makeConstraints { make in
            make.top.equalTo(totalTimeLabel1.snp.bottom).offset(20)
            make.left.equalTo(totalTimeLabel1)
            make.right.equalTo(unloadButton)
        }

        startButton1.snp.makeConstraints { make in
            make.top.equalTo(changeVolumeSlider1.snp.bottom).offset(20)
            make.left.equalTo(changeVolumeSlider1)
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
            make.width.equalTo(startButton1)
            make.right.height.equalTo(unloadButton)
        }
        
        view.addSubview(urlBackgroundView)
        
        urlBackgroundView.snp.makeConstraints { make in
            make.top.equalTo(fileBackgroundView.snp.bottom).offset(20)
            make.left.right.equalTo(joinButton)
            make.height.equalTo(210)
        }

        urlBackgroundView.addSubview(urlTitleLabel)
        urlBackgroundView.addSubview(urlTextField)
        urlBackgroundView.addSubview(totalTimeLabel2)
        urlBackgroundView.addSubview(changePositionItem2)
        urlBackgroundView.addSubview(changeVolumeSlider2)
        
        urlBackgroundView.addSubview(startButton2)
        urlBackgroundView.addSubview(pauseButton2)
        urlBackgroundView.addSubview(resumeButton2)
        urlBackgroundView.addSubview(stopButton2)
        
        urlTitleLabel.snp.makeConstraints { make in
            make.left.top.equalToSuperview().offset(10)
        }
        
        urlTextField.snp.makeConstraints { make in
            make.top.equalTo(urlTitleLabel.snp.bottom).offset(10)
            make.left.equalTo(urlTitleLabel)
            make.right.equalToSuperview().offset(-10)
            make.height.equalTo(30)
        }

        totalTimeLabel2.snp.makeConstraints { make in
            make.top.equalTo(urlTextField.snp.bottom).offset(10)
            make.left.equalTo(urlTextField)
        }

        changePositionItem2.snp.makeConstraints { make in
            make.centerY.equalTo(totalTimeLabel2)
            make.right.equalTo(urlTextField)
        }
        
        changeVolumeSlider2.snp.makeConstraints { make in
            make.top.equalTo(totalTimeLabel2.snp.bottom).offset(20)
            make.left.equalTo(totalTimeLabel2)
            make.right.equalTo(urlTextField)
        }

        startButton2.snp.makeConstraints { make in
            make.top.equalTo(changeVolumeSlider2.snp.bottom).offset(20)
            make.left.equalTo(changeVolumeSlider2)
            make.height.equalTo(36)
        }

        pauseButton2.snp.makeConstraints { make in
            make.centerY.equalTo(startButton2)
            make.left.equalTo(startButton2.snp.right).offset(10)
            make.width.height.equalTo(startButton2)
        }

        resumeButton2.snp.makeConstraints { make in
            make.centerY.equalTo(startButton2)
            make.left.equalTo(pauseButton2.snp.right).offset(10)
            make.width.height.equalTo(startButton2)
        }

        stopButton2.snp.makeConstraints { make in
            make.centerY.equalTo(startButton2)
            make.left.equalTo(resumeButton2.snp.right).offset(10)
            make.width.height.equalTo(startButton2)
            make.right.equalTo(changeVolumeSlider2)
        }
        
        view.addSubview(changeAllVolumeSlider)
        
        view.addSubview(pauseAllButton)
        view.addSubview(resumeAllButton)
        view.addSubview(stopAllButton)

        changeAllVolumeSlider.snp.makeConstraints { make in
            make.top.equalTo(urlBackgroundView.snp.bottom).offset(20)
            make.left.right.equalTo(urlBackgroundView)
        }

        pauseAllButton.snp.makeConstraints { make in
            make.top.equalTo(changeAllVolumeSlider.snp.bottom).offset(10)
            make.left.equalTo(changeAllVolumeSlider)
            make.height.equalTo(36)
        }

        resumeAllButton.snp.makeConstraints { make in
            make.centerY.equalTo(pauseAllButton)
            make.left.equalTo(pauseAllButton.snp.right).offset(10)
            make.width.height.equalTo(pauseAllButton)
        }

        stopAllButton.snp.makeConstraints { make in
            make.centerY.equalTo(pauseAllButton)
            make.left.equalTo(resumeAllButton.snp.right).offset(10)
            make.right.equalTo(changeAllVolumeSlider)
            make.width.height.equalTo(pauseAllButton)
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
        let button = BaseButton.init()
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
    
    lazy var fileTitleLabel: UILabel = {
        let label = UILabel()
        label.text = "播放本地文件"
        return label
    }()
    
    lazy var fileTextField: TextFieldView = {
        let textField = TextFieldView()
        textField.title = "文件:"
        textField.text = "rtc_test.aac"
        return textField
    }()
    
    lazy var preloadButton: UIButton = {
        let button = BaseButton.init()
        button.setTitle("预加载", for: .normal)
        button.addTarget(self, action: #selector(preloadFile), for: .touchUpInside)
        return button
    }()
    
    lazy var unloadButton: UIButton = {
        let button = BaseButton.init()
        button.setTitle("卸载", for: .normal)
        button.addTarget(self, action: #selector(unloadFile), for: .touchUpInside)
        return button
    }()
    
    lazy var totalTimeLabel1: UILabel = {
        let label = UILabel()
        label.text = "总时长"
        return label
    }()
    
    lazy var changePositionItem1: SettingItemView = {
        let settingView = SettingItemView()
        settingView.title = "跳转"
        return settingView
    }()
    
    lazy var changeVolumeSlider1: SliderView = {
        let sliderView = SliderView.init(minValue: 0, maxValue: 400, defaultValue: 100)
        sliderView.title = "音量"
        return sliderView
    }()
    
    lazy var startButton1: UIButton = {
        let button = BaseButton.init()
        button.setTitle("开始", for: .normal)
        button.addTarget(self, action: #selector(startPlayEffect1), for: .touchUpInside)
        return button
    }()
    
    lazy var pauseButton1: UIButton = {
        let button = BaseButton.init()
        button.setTitle("暂停", for: .normal)
        button.addTarget(self, action: #selector(pausePlayEffect1), for: .touchUpInside)
        return button
    }()
    
    lazy var resumeButton1: UIButton = {
        let button = BaseButton.init()
        button.setTitle("恢复", for: .normal)
        button.addTarget(self, action: #selector(resumePlayEffect1), for: .touchUpInside)
        return button
    }()
    
    lazy var stopButton1: UIButton = {
        let button = BaseButton.init()
        button.setTitle("停止", for: .normal)
        button.addTarget(self, action: #selector(stopPlayEffect1), for: .touchUpInside)
        return button
    }()
    
    lazy var urlBackgroundView: UIView = {
        let view = UIView()
        view.backgroundColor = .groupTableViewBackground
        view.layer.borderWidth = 1
        view.layer.borderColor = UIColor.lightGray.cgColor
        view.layer.cornerRadius = 5
        view.layer.masksToBounds = true
        return view
    }()
    
    lazy var urlTitleLabel: UILabel = {
        let label = UILabel()
        label.text = "播放在线音乐"
        return label
    }()
    
    lazy var urlTextField: TextFieldView = {
        let textField = TextFieldView()
        textField.title = "在线音乐地址:"
        textField.text = "https://preview.tosound.com:3321/preview?file=freesound/0/137/239241.mp3"
        return textField
    }()
    
    lazy var totalTimeLabel2: UILabel = {
        let label = UILabel()
        label.text = "总时长"
        return label
    }()
    
    lazy var changePositionItem2: SettingItemView = {
        let settingView = SettingItemView()
        settingView.title = "跳转"
        return settingView
    }()
    
    lazy var changeVolumeSlider2: SliderView = {
        let sliderView = SliderView.init(minValue: 0, maxValue: 400, defaultValue: 100)
        sliderView.title = "音量"
        return sliderView
    }()
    
    lazy var startButton2: UIButton = {
        let button = BaseButton()
        button.setTitle("开始", for: .normal)
        button.addTarget(self, action: #selector(startPlayEffect2), for: .touchUpInside)
        return button
    }()
    
    lazy var pauseButton2: UIButton = {
        let button = BaseButton()
        button.setTitle("暂停", for: .normal)
        button.addTarget(self, action: #selector(pausePlayEffect2), for: .touchUpInside)
        return button
    }()
    
    lazy var resumeButton2: UIButton = {
        let button = BaseButton()
        button.setTitle("恢复", for: .normal)
        button.addTarget(self, action: #selector(resumePlayEffect2), for: .touchUpInside)
        return button
    }()
    
    lazy var stopButton2: UIButton = {
        let button = BaseButton()
        button.setTitle("停止", for: .normal)
        button.addTarget(self, action: #selector(stopPlayEffect2), for: .touchUpInside)
        return button
    }()
    
    lazy var pauseAllButton: UIButton = {
        let button = BaseButton()
        button.setTitle("暂停所有", for: .normal)
        button.addTarget(self, action: #selector(pauseAllEffect), for: .touchUpInside)
        return button
    }()
    
    lazy var resumeAllButton: UIButton = {
        let button = BaseButton()
        button.setTitle("恢复所有", for: .normal)
        button.addTarget(self, action: #selector(resumeAllEffect), for: .touchUpInside)
        return button
    }()
    
    lazy var stopAllButton: UIButton = {
        let button = BaseButton()
        button.setTitle("停止所有", for: .normal)
        button.addTarget(self, action: #selector(stopAllEffect), for: .touchUpInside)
        return button
    }()
    
    lazy var changeAllVolumeSlider: SliderView = {
        let sliderView = SliderView.init(minValue: 0, maxValue: 400, defaultValue: 100)
        sliderView.title = "所有音效音量"
        return sliderView
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
    
    // MARK: ByteRTCAudioEffectPlayerEventHandler
    // 音效播放状态
    func onAudioEffectPlayerStateChanged(_ effectId: Int32, state: ByteRTCPlayerState, error: ByteRTCPlayerError) {
        
        ToastComponents.shared.show(withMessage: "onAudioEffectPlayerStateChanged effectId: \(effectId) state:\(state.rawValue) error:\(error.rawValue)")
        
        DispatchQueue.main.async
        {
            if effectId == self.effectId1 {
                
                if state == .playing {
                    
                    let totalTime = self.effectPlayer?.getDuration(self.effectId1!)
                    self.totalTimeLabel1.text = "总时长: \(totalTime ?? 0) ms"
                }
                
            } else {
                
                if state == .playing {
                    let totalTime = self.effectPlayer?.getDuration(self.effectId2!)
                    self.totalTimeLabel2.text = "总时长: \(totalTime ?? 0) ms"
                }
            }
        }
    }
}
