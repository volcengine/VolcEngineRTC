/**
* 功能名称： VolcEngineRTC 美声与音效
* 功能简单描述：该功能展示了混响、变声、降噪等功能
* 参考文档：https://www.volcengine.com/docs/6348/1178327
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
*     setVoiceReverbType 设置混响特效类型
*     setVoiceChangerType 设置变声特效类型
*     setLocalVoicePitch 开启本地语音变调功能
*     enableLocalVoiceReverb 开启本地音效混响效果
*     setLocalVoiceReverbParam 设置本地采集音频的混响效果
*     setAnsMode  设置通话中的音频降噪模式
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
*    本Demo演示功能：美声与音效，演示了各种声音处理特效，使用该功能前请咨询技术人员
*    为了展示简单，所有功能的token都由客户端TokenGenerator类生成，请在真正接入时视具体情况而定
*/


import UIKit
import SnapKit
import VolcEngineRTC


class SoundEffectsViewController: BaseViewController, ByteRTCVideoDelegate, ByteRTCRoomDelegate {
    var rtcVideo: ByteRTCVideo?
    var rtcRoom: ByteRTCRoom?
    
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
    
    func buildActions() {
        weak var weakSelf = self
        
        // 变声
        self.voiceTypeSheetView.didSelectOption = {(value) in
            weakSelf?.rtcVideo?.setVoiceChangerType(ByteRTCVoiceChangerType(rawValue: Int(value))!)
        }
        
        // 混响
        self.voiceReverbSheetView.didSelectOption = {(value) in
            weakSelf?.rtcVideo?.setVoiceReverbType(ByteRTCVoiceReverbType(rawValue: Int(value))!)
        }
        
        //变调
        self.pitchSetting.onValueChanged = {(value) in
            weakSelf?.rtcVideo?.setLocalVoicePitch(Int(value))
        }
        
        // 降噪
        self.voiceAnsSheetView.didSelectOption = {(value) in
            weakSelf?.rtcVideo?.setAnsMode(ByteRTCAnsMode(rawValue: Int(value))!)
        }
    }
    
    @objc func modifyReverbConfig() {
        self.rtcVideo?.enableLocalVoiceReverb(true)
        
        let config = ByteRTCVoiceReverbConfig.init()
        config.roomSize = Float(self.roomSizeSetting.valueLabel.text!)!
        config.decayTime = Float(self.decayTimeSetting.valueLabel.text!)!
        config.damping = Float(self.dampingSetting.valueLabel.text!)!
        config.wetGain = Float(self.wetGainSetting.valueLabel.text!)!
        config.dryGain = Float(self.dryGainSetting.valueLabel.text!)!
        config.preDelay = Float(self.preDelaySetting.valueLabel.text!)!
        
        self.rtcVideo?.setLocalVoiceReverbParam(config)
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
        localView.snp.makeConstraints { make in
            make.left.top.equalTo(self.containerView)
            make.width.height.equalTo(self.containerView)
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
            make.top.equalTo(roomSettingItem.snp.bottom).offset(20)
            make.left.equalToSuperview().offset(10)
            make.right.equalToSuperview().offset(-10)
            make.height.equalTo(36)
        }
        
        view.addSubview(effectLabel)
        effectLabel.snp.makeConstraints { make in
            make.top.equalTo(joinButton.snp.bottom).offset(20)
            make.left.equalToSuperview().offset(10)
        }
        
        view.addSubview(voiceTypeSheetView)
        view.addSubview(voiceReverbSheetView)
        view.addSubview(pitchSetting)
        
        voiceTypeSheetView.snp.makeConstraints { make in
            make.top.equalTo(effectLabel.snp.bottom).offset(10)
            make.left.equalToSuperview().offset(10)
            make.right.equalToSuperview().offset(-10)
        }
        
        voiceReverbSheetView.snp.makeConstraints { make in
            make.top.equalTo(voiceTypeSheetView.snp.bottom).offset(10)
            make.left.equalToSuperview().offset(10)
            make.right.equalToSuperview().offset(-10)
        }
        
        pitchSetting.snp.makeConstraints { make in
            make.top.equalTo(voiceReverbSheetView.snp.bottom).offset(10)
            make.left.equalToSuperview().offset(10)
            make.right.equalToSuperview().offset(-10)
        }
        
        view.addSubview(reverbConfigLabel)
        view.addSubview(roomSizeSetting)
        view.addSubview(decayTimeSetting)
        view.addSubview(dampingSetting)
        view.addSubview(wetGainSetting)
        view.addSubview(dryGainSetting)
        view.addSubview(preDelaySetting)
        view.addSubview(modifyReverbButton)
        
        reverbConfigLabel.snp.makeConstraints { make in
            make.top.equalTo(pitchSetting.snp.bottom).offset(30)
            make.left.equalTo(pitchSetting)
            make.right.equalToSuperview().offset(-10)
        }
        
        roomSizeSetting.snp.makeConstraints { make in
            make.top.equalTo(reverbConfigLabel.snp.bottom).offset(20)
            make.left.equalTo(reverbConfigLabel)
            make.right.equalToSuperview().offset(-10)
        }
        
        decayTimeSetting.snp.makeConstraints { make in
            make.top.equalTo(roomSizeSetting.snp.bottom).offset(20)
            make.left.equalTo(reverbConfigLabel)
            make.right.equalToSuperview().offset(-10)
        }
        
        dampingSetting.snp.makeConstraints { make in
            make.top.equalTo(decayTimeSetting.snp.bottom).offset(20)
            make.left.equalTo(roomSizeSetting)
            make.right.equalToSuperview().offset(-10)
        }
        
        wetGainSetting.snp.makeConstraints { make in
            make.top.equalTo(dampingSetting.snp.bottom).offset(20)
            make.left.equalTo(dampingSetting)
            make.right.equalToSuperview().offset(-10)
        }
        
        dryGainSetting.snp.makeConstraints { make in
            make.top.equalTo(wetGainSetting.snp.bottom).offset(20)
            make.left.equalTo(wetGainSetting)
            make.right.equalToSuperview().offset(-10)
        }
        
        preDelaySetting.snp.makeConstraints { make in
            make.top.equalTo(dryGainSetting.snp.bottom).offset(20)
            make.left.equalTo(dryGainSetting)
            make.right.equalToSuperview().offset(-10)
        }
        
        modifyReverbButton.snp.makeConstraints { make in
            make.top.equalTo(preDelaySetting.snp.bottom).offset(20)
            make.left.equalTo(preDelaySetting)
            make.right.equalToSuperview().offset(-10)
        }
        
        view.addSubview(ansLabel)
        view.addSubview(voiceAnsSheetView)
        
        ansLabel.snp.makeConstraints { make in
            make.top.equalTo(modifyReverbButton.snp.bottom).offset(20)
            make.left.equalTo(modifyReverbButton)
        }
        
        voiceAnsSheetView.snp.makeConstraints { make in
            make.top.equalTo(ansLabel.snp.bottom).offset(10)
            make.left.equalTo(modifyReverbButton)
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
    
    lazy var effectLabel: UILabel = {
        let label = UILabel()
        label.text = "特效"
        label.font = UIFont.boldSystemFont(ofSize: 18)
        return label
    }()
    
    lazy var voiceTypeSheetView: ActionSheetView = {
        let actionSheetView = ActionSheetView.init(title: "变声特效", optionArray: ["Original","Giant","Chipmunk","Minionst","Vibrato","Robot"], defaultIndex: 0)
        actionSheetView.presentingViewController = self
        
        return actionSheetView
    }()
    
    lazy var voiceReverbSheetView: ActionSheetView = {
        let actionSheetView = ActionSheetView.init(title: "混响特效", optionArray: ["Original","Echo","Concert","Ethereal","KTV","Studio","VirtualStereo","Spacious","3D"], defaultIndex: 0)
        actionSheetView.presentingViewController = self
        
        return actionSheetView
    }()
    
    lazy var pitchSetting: SliderView = {
        let settingView = SliderView(minValue: -12, maxValue: 12, defaultValue: 0)
        settingView.title = "变调"
        return settingView
    }()
    
    lazy var reverbConfigLabel: UILabel = {
        let label = UILabel()
        label.text = "混响配置"
        label.font = effectLabel.font
        return label
    }()
    
    lazy var roomSizeSetting: SliderView = {
        let settingView = SliderView(minValue: 0, maxValue: 100, defaultValue: 50)
        settingView.title = "房间大小"
        return settingView
    }()
    
    lazy var decayTimeSetting: SliderView = {
        let settingView = SliderView(minValue: 0, maxValue: 100, defaultValue: 50)
        settingView.title = "拖尾长度"
        return settingView
    }()
    
    lazy var dampingSetting: SliderView = {
        let settingView = SliderView(minValue: 0, maxValue: 100, defaultValue: 50)
        settingView.title = "衰减阻尼大小"
        return settingView
    }()
    
    lazy var wetGainSetting: SliderView = {
        let settingView = SliderView(minValue: -20, maxValue: 10, defaultValue: 0)
        settingView.title = "早期反射信号强度"
        return settingView
    }()
    
    lazy var dryGainSetting: SliderView = {
        let settingView = SliderView(minValue: -20, maxValue: 10, defaultValue: 0)
        settingView.title = "原始信号强度"
        return settingView
    }()
    
    lazy var preDelaySetting: SliderView = {
        let settingView = SliderView(minValue: 0, maxValue: 200, defaultValue: 0)
        settingView.title = "早期反射信号延迟"
        return settingView
    }()
    
    lazy var modifyReverbButton: UIButton = {
        let button = BaseButton()
        button.setTitle("确认修改", for: .normal)
        button.addTarget(self, action: #selector(modifyReverbConfig), for: .touchUpInside)
        return button
    }()
    
    lazy var ansLabel: UILabel = {
        let label = UILabel()
        label.text = "降噪模式"
        label.font = effectLabel.font
        return label
    }()
    
    lazy var voiceAnsSheetView: ActionSheetView = {
        let actionSheetView = ActionSheetView.init(title: "音频降噪", optionArray: ["Disable","Low","Medium","High","Automatic"], defaultIndex: 0)
        actionSheetView.presentingViewController = self
        
        return actionSheetView
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
}
