/**
* 功能名称： 拉流SDK拉取直播流
* 功能简单描述：通过拉流 SDK 实现直播拉流播放控制的能力，包括建播放器、初始化配置、事件监听、配置渲染 View、配置播放地址。
* 参考文档：https://www.volcengine.com/docs/6469/97858
*/

import Foundation
import TTSDKFramework


class PullRTMPViewController: BaseViewController,VeLivePlayerObserver {
    var livePlayer: TVLManager?

    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        self.createUI()
        self.buildTVEngine()
        self.buildRenderView()
        
        // app 回到前台通知
        NotificationCenter.default.addObserver(self,
            selector: #selector(applicationDidBecomeActive),
            name: UIApplication.didBecomeActiveNotification,
            object: nil)
        // app 退到后台通知
        NotificationCenter.default.addObserver(self,
            selector: #selector(applicationWillResignActive),
            name: UIApplication.willResignActiveNotification,
            object: nil)
    }
    
    deinit {
        // 销毁拉流引擎，退出前释放播放器，释放内存
        self.livePlayer?.destroy()
    }
    
    // 回到前台处理
    @objc func applicationDidBecomeActive() {
        self.livePlayer?.play() // 回到前台，继续播放
    }

    // 退到后台处理
    @objc func applicationWillResignActive() {
        self.livePlayer?.pause() // 退到后台，暂停播放
    }
    
    func buildTVEngine() -> Void {
        // 创建播放器
        self.livePlayer = TVLManager.init()
        
        // 创建配置
        let config = VeLivePlayerConfiguration.init()
        // 打开 SEI 解析
        config.enableSei = true

        config.enableStatisticsCallback = true

        config.enableLiveDNS = true

        // 初始化播放器
        print("setConfig")
        self.livePlayer?.setConfig(config)
                
        self.livePlayer?.setObserver(self)        
    }
    
    func buildRenderView() -> Void {
        // 配置 metal 渲染
        self.livePlayer?.playerViewRenderType = .metal

        // 配置填充模式
        self.livePlayer?.setRenderFillMode(.aspectFit)

        // 将 playerView 添加到你的自定义 view 上
        if let playerView = self.livePlayer?.playerView {
            self.liveView.addSubview(playerView)
        }
        
        // 配置 playerView 尺寸
        self.livePlayer?.playerView.snp.makeConstraints({ make in
            make.edges.equalToSuperview()
        })
        
    }
    
    func createUI() -> Void {
        
        view.addSubview(liveView)
        view.addSubview(urlTextFieldView)
        
        view.addSubview(startButton)
        view.addSubview(stopButton)
        
        liveView.snp.makeConstraints { make in
            make.top.equalTo(topView.snp.bottom)
            make.left.right.equalToSuperview()
            make.height.equalTo(liveView.snp.width)
        }
        
        urlTextFieldView.snp.makeConstraints { make in
            make.top.equalTo(liveView.snp.bottom).offset(20)
            make.left.equalToSuperview().offset(10)
            make.right.equalToSuperview().offset(-10)
            make.height.equalTo(36)
        }
        
        startButton.snp.makeConstraints { make in
            make.top.equalTo(urlTextFieldView.snp.bottom).offset(10)
            make.left.equalToSuperview().offset(10)
            make.height.equalTo(30)
        }
        
        stopButton.snp.makeConstraints { make in
            make.centerY.equalTo(startButton)
            make.left.equalTo(startButton.snp.right).offset(20)
            make.right.equalToSuperview().offset(-10)
            make.width.height.equalTo(startButton)
        }
        
        view.addSubview(receivedSEILabel)
        view.addSubview(receivedSEITextField)
        
        receivedSEILabel.snp.makeConstraints { make in
            make.top.equalTo(startButton.snp.bottom).offset(20)
            make.left.equalToSuperview().offset(10)
            make.right.equalToSuperview().offset(-10)
            make.height.equalTo(30)
        }
        
        receivedSEITextField.snp.makeConstraints { make in
            make.top.equalTo(receivedSEILabel.snp.bottom).offset(20)
            make.left.equalToSuperview().offset(10)
            make.right.equalToSuperview().offset(-10)
            make.bottom.equalToSuperview().offset(-20)
            
        }
    }
    
    @objc func startPull() {
        if let text = self.urlTextFieldView.text, !text.isEmpty {
            self.livePlayer?.setPlayUrl(text)
            self.livePlayer?.play()
        } else {
            ToastComponents.shared.show(withMessage: "无效的推流地址")
        }
    }
    
    @objc func stopPull() {
        self.livePlayer?.stop()
    }
    
    // MARK: Lazy laod
    lazy var liveView: UIView = {
        let view = UIView.init()
        view.backgroundColor = .groupTableViewBackground
        return view
    }()
    
    lazy var urlTextFieldView: TextFieldView = {
        let settingView = TextFieldView()
        settingView.title = "拉流地址"
        settingView.text = kPullUrl
        return settingView
    }()
    
    lazy var startButton: UIButton = {
        let button = BaseButton()
        button.setTitle("开始拉流", for: .normal)
        button.addTarget(self, action: #selector(startPull), for: .touchUpInside)
        return button
    }()
    
    lazy var stopButton: UIButton = {
        let button = BaseButton()
        button.setTitle("停止拉流", for: .normal)
        button.addTarget(self, action: #selector(stopPull), for: .touchUpInside)
        return button
    }()
    
    lazy var receivedSEILabel: UILabel = {
        let label = UILabel()
        label.text = "本端收到的SEI信息"
        return label
    }()
    
    lazy var receivedSEITextField: UITextView = {
        let textView = UITextView()
        textView.backgroundColor = .groupTableViewBackground
        textView.layer.cornerRadius = 5;
        textView.layer.masksToBounds = true
        return textView
    }()
    
    // MARK: VeLivePlayerObserver
    func onError(_ player: TVLManager, error: VeLivePlayerError) {
        ToastComponents.shared.show(withMessage: "onError:\(error.errorMsg ?? "")")

    }
    
    func onReceiveSeiMessage(_ player: TVLManager, message: String) {
        // 收到SEI信息
        self.receivedSEITextField.text = message
    }
    
    func onPlayerStatusUpdate(_ player: TVLManager, status: VeLivePlayerStatus) {
        ToastComponents.shared.show(withMessage: "onPlayerStatusUpdate:\(status.rawValue)")
        
        
    }
    
}
