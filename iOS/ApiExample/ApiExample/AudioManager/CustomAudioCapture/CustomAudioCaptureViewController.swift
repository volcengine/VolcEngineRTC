
import UIKit
import SnapKit
import VolcEngineRTC


class CustomAudioCaptureViewController: BaseViewController, ByteRTCEngineDelegate, ByteRTCRoomDelegate {
    
    var rtcVideo: ByteRTCEngine?
    var rtcRoom1: ByteRTCRoom?
    var firstPush:Bool = true
    var timer: GCDTimer?
    var startOffset = 0

    override func viewDidLoad() {
        super.viewDidLoad()
        
        self.createUI()
        self.buildRTCEngine()
        self.bindLocalRenderView()
        self.buildActions()
    
    }
    
    deinit {
        self.rtcVideo!.registerAudioFrameObserver(nil)

        self.rtcRoom1?.leave()
        self.rtcRoom1?.destroy()
        self.rtcRoom1 = nil
        
        ByteRTCEngine.destroyRTCEngine()
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
            roomCfg.isPublishAudio = true
            roomCfg.isPublishVideo = true
            roomCfg.isAutoSubscribeAudio = true
            roomCfg.isAutoSubscribeVideo = true
            
            self.rtcRoom1?.joinRoom(token, userInfo: userInfo, userVisibility: true, roomConfig: roomCfg)
        }
        else {
            joinButton.setTitle("加入房间", for: .normal)
            self.rtcRoom1?.leave()
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
        
        // 开启外部音频源
        self.rtcVideo?.setAudioSourceType(.external)
        
        self.bindLocalRenderView()
    }
    
    func buildActions() {
        
    }
    
    func bindLocalRenderView() {
        // 设置本地渲染视图
        let canvas = ByteRTCVideoCanvas.init()
        canvas.view = self.localView.videoView
        canvas.renderMode = .hidden
        self.localView.userId = userTextField.text ?? ""
        
        self.rtcVideo?.setLocalVideoCanvas(withCanvas: canvas);
    }
    
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
        self.view.endEditing(true)
    }
    
    @objc func startPush() {
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
    
    func pushPCMData() {
        let size = 160 * 1 * 2 // 每10ms的数据=采样数 * 声道数 * 采样占字节数,该pcm文件是16000采样率，单声道，每个样本占2个字节
        
        if self.firstPush {
            self.firstPush = false
        }
        
        let filePath = Bundle.main.path(forResource: "16k-mono-speech_fft_32s", ofType: "pcm")!
        let url = URL(fileURLWithPath: filePath)
        
        guard let fileData = try? Data(contentsOf: url) else {
            print("Failed to read PCM file data.")
            return
        }
        
        var endOffset = self.startOffset + size
        
        if endOffset >= fileData.count {
            // 从头再读
            self.startOffset = 0
            endOffset = self.startOffset + size
        }
        
        let audioData: Data = fileData.subdata(in: startOffset..<endOffset)
        self.startOffset = endOffset
        
        let audioFrame = ByteRTCAudioFrame()
        audioFrame.channel = .mono
        audioFrame.sampleRate = .rate16000
        audioFrame.samples = Int32(size) / 2 // 每个采样占2字节
        audioFrame.buffer = audioData
        
        self.rtcVideo?.pushExternalAudioFrame(audioFrame)
    }
    
    @objc func stopPush() {
        self.timer?.cancel()
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
        
        view.addSubview(startButton)
        view.addSubview(stopButton)

        startButton.snp.makeConstraints { make in
            make.top.equalTo(joinButton.snp.bottom).offset(10)
            make.left.equalToSuperview().offset(10)
            make.height.equalTo(30)
        }
        
        stopButton.snp.makeConstraints { make in
            make.centerY.equalTo(startButton)
            make.left.equalTo(startButton.snp.right).offset(20)
            make.right.equalToSuperview().offset(-10)
            make.width.height.equalTo(startButton)
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
    
    lazy var containerView: UIView = {
        let view = UIView.init()
        view.backgroundColor = .groupTableViewBackground
        return view
    }()
    
    lazy var localView: UserVideoView = {
        let view = UserVideoView.init()
        return view
    }()
    
    lazy var startButton: UIButton = {
        let button = BaseButton()
        button.setTitle("开始", for: .normal)
        button.addTarget(self, action: #selector(startPush), for: .touchUpInside)
        return button
    }()
    
    lazy var stopButton: UIButton = {
        let button = BaseButton()
        button.setTitle("停止", for: .normal)
        button.addTarget(self, action: #selector(stopPush), for: .touchUpInside)
        return button
    }()
    
    // MARK: ByteRTCEngineDelegate & ByteRTCRoomDelegate
    //进房状态
    func rtcRoom(_ rtcRoom: ByteRTCRoom, onRoomStateChanged roomId: String, withUid uid: String, state: Int, extraInfo: String) {
        ToastComponents.shared.show(withMessage: "onRoomStateChanged uid: \(uid) state:\(state)")
        
    }
    

}

