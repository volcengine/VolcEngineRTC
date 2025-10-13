/**
* 功能名称： VolcEngineRTC 推流到CDN
* 功能简单描述：对于一个音视频通话，你可以将其中的多路音视频流合为一路，并将合并得到的音视频流推送到指定的推流地址（通常是 CDN 地址）
* 参考文档：推流到 CDN——服务端合流（客户端发起） https://www.volcengine.com/docs/6348/69817

*
* 此功能涉及的API及回调：
*     createRTCEngine 创建引擎
*     destroyRTCEngine 销毁引擎
*     startAudioCapture 开启音频采集
*     startVideoCapture 开启视频采集
*     createRTCRoom 创建RTC房间
*     joinRoom 进入RTC房间
*     leaveRoom 离开RTC房间
*     destroy 销毁RTC房间
*
*     startPushMixedStream 开启合流转推
*     updatePushMixedStream 更新合流转推参数
*     stopPushCDN 停止合流转推
*
*     onRoomStateChanged 房间状态回调
*     onLeaveRoom 离房回调
*     onUserJoined 用户加入回调
*     onUserLeave  用户离开回调
*     onUserPublishStream 用户发流回调
*     onUserUnpublishStream 用户停止发流回调
*
*     onMixingEvent 合流事件回调
*
* Demo实现时的逻辑
*    本Demo演示功能：合流转推，
*       当布局方式为1*4时(一排显示4个视图),每路流宽度为0.25,高度为1
*       当布局方式为2*2时(四宫格),每路流宽度为0.5,高度为0.5
*       房间内最多展示4路流
*    为了展示简单，所有功能的token都由客户端TokenGenerator类生成，请在真正接入时视具体情况而定
*/

import UIKit
import SnapKit
import VolcEngineRTC
import Foundation
import CommonCrypto

class PushCDNViewController: BaseViewController, ByteRTCEngineDelegate, ByteRTCRoomDelegate {
    
    var rtcVideo: ByteRTCEngine?
    var rtcRoom: ByteRTCRoom?
    var userVideoStreamMap: Dictionary = Dictionary<String, ByteRTCStreamInfo>()
    var mixConfig: ByteRTCMixedStreamConfig?
    var targetConfig: ByteRTCMixedStreamPushTargetConfig?
    let taskId = "pushCDNtaskId_001"
    
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
            self.stopPushCDN()
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
        self.rtcVideo?.startVideoCapture()
        self.rtcVideo?.startAudioCapture()
        
        // 开启本地预览
        self.bindLocalRenderView()
        
        // 设置默认合流参数
        self.mixConfig = ByteRTCMixedStreamConfig.default()
        self.targetConfig = ByteRTCMixedStreamPushTargetConfig.init()
        self.mixConfig?.backgroundColor = "#FFFFFF"

    }
    


    func signURL(roomID: String) -> String? {
    // 获取当前时间戳
    let timeStamp = Int(Date().timeIntervalSince1970)
    let expire = timeStamp + 7200
    
    // 构建路径
    let path = "/rtc_test/pushcdn\(roomID)111"
    let authKey = "Uq8e962ghCCY2pBUB9Me2Fwy"
    
    // 构建签名字符串
    let keyStr = "\(path)\(authKey)\(expire)"
    
    // 计算 MD5 签名
    guard let sign = md5(string: keyStr) else {
        return nil
    }
    
    // 构建最终的 URL
    let finalURL = "rtmp://fcdn-test-hl.uplive.ixigua.com/rtc_test/pushcdn\(roomID)111?sign=\(sign)&expire=\(expire)"
    
    return finalURL
    }

    // MD5 计算函数
    func md5(string: String) -> String? {
        let length = Int(CC_MD5_DIGEST_LENGTH)
        let messageData = string.data(using: .utf8)!
        var digest = [UInt8](repeating: 0, count: length)
        
        messageData.withUnsafeBytes {
            _ = CC_MD5($0.baseAddress, CC_LONG(messageData.count), &digest)
        }
        
        return digest.map { String(format: "%02hhx", $0) }.joined()
    }
    @objc func startPushCDN() {
        let roomId = roomSettingItem.text ?? ""
        let userId = userSettingItem.text ?? ""
        if let text = signURL(roomID: roomId), !text.isEmpty {
            if let cdnurl = signURL(roomID: roomId) {
                self.mixConfig?.regions = self.getMixRegions()
                self.mixConfig?.roomID = roomId
                self.mixConfig?.userID = userId
                self.targetConfig?.pushCDNURL = cdnurl
                self.urlTextField.text = cdnurl
                self.targetConfig?.pushTargetType = .toCDN
                
                print("URL: \(cdnurl)")
//                ToastComponents.shared.show(withMessage: "Updated URL: \(cdnurl)")
//                ToastComponents.shared.show(withMessage: "Pull sdk using key : pushcdn\(roomId)111")
                
                let ret = self.rtcVideo?.startPushMixedStream(taskId, with: self.targetConfig, withMixedConfig: self.mixConfig)
                if (ret != 0){
                    ToastComponents.shared.show(withMessage: "startPushMixedStream failed, ret:\(String(describing: ret))")
                }
            } else {
                print("Failed to generate signed URL")
            }
        } else {
            ToastComponents.shared.show(withMessage: "无效的推流地址")
        }
    }

    
    @objc func updatePushConfig()  {
        // 更新布局
        self.mixConfig?.regions = self.getMixRegions()

        self.rtcVideo?.updatePushMixedStream(taskId, with: self.targetConfig, withMixedConfig: self.mixConfig!)
    }
    
    @objc func stopPushCDN()  {
        self.rtcVideo?.stopPushMixedStream(taskId, with: .toCDN)
    }
    
    func getMixRegions() -> [ByteRTCMixedStreamLayoutRegionConfig] {
        let roomId = roomSettingItem.text
        let userId = userSettingItem.text
        
        var regions = [ByteRTCMixedStreamLayoutRegionConfig]()
        var users = self.userVideoStreamMap.values

        if self.layoutSheetView.selectedIndex == 0 {
            // 1x4 布局
            
            let width = 360/4
            let height = 640
            
            // 本地用户
            let regionConfig = ByteRTCMixedStreamLayoutRegionConfig.init()
            regionConfig.userID = userId!
            regionConfig.roomID = roomId!
            regionConfig.locationX = 0
            regionConfig.locationY = 0
            regionConfig.width = 360/4
            regionConfig.height = 640
            regionConfig.zOrder = 0
            regionConfig.isLocalUser = true
            regionConfig.mediaType = .audioAndVideo
            
            regions.append(regionConfig)
            
            
            //远端用户
            for (index, item) in users.enumerated() {
                if index < 3 {
                    let regionConfig = ByteRTCMixedStreamLayoutRegionConfig.init()
                    regionConfig.userID = item.userId
                    regionConfig.roomID = item.roomId
                    
                    regionConfig.locationX = width*(index+1)
                    regionConfig.locationY = 0
                    regionConfig.width = width
                    regionConfig.height = height
                    regionConfig.zOrder = 0
                    regionConfig.isLocalUser = false
                    regionConfig.mediaType = .audioAndVideo
                    
                    regions.append(regionConfig)
                }
            }
        } else {
            // 2x2 布局
            let width = 360/2
            let height = 640/2
            
            // 本地用户
            let regionConfig = ByteRTCMixedStreamLayoutRegionConfig.init()
            regionConfig.userID = userId!
            regionConfig.roomID = roomId!
            regionConfig.locationX = 0
            regionConfig.locationY = 0
            regionConfig.width = width
            regionConfig.height = height
            regionConfig.zOrder = 0
            regionConfig.isLocalUser = true
            regionConfig.mediaType = .audioAndVideo
            
            regions.append(regionConfig)
            
            //远端用户
            for (index, item) in users.enumerated() {
                if index < 3 {
                    let regionConfig = ByteRTCMixedStreamLayoutRegionConfig.init()
                    regionConfig.userID = item.userId
                    regionConfig.roomID = item.roomId
                    
                    let col = (index + 1)%2
                    let row = (index + 1)/2
                    
                    regionConfig.locationX = width*col
                    regionConfig.locationY = height*row
                    regionConfig.width = width
                    regionConfig.height = height
                    regionConfig.zOrder = 0
                    regionConfig.isLocalUser = false
                    regionConfig.mediaType = .audioAndVideo
                    
                    regions.append(regionConfig)
                }
            }
        }
        
        return regions
    }
    
    func buildActions() {
        weak var weakSelf = self
        
        // 音频采样率
        self.audioSampleRateSheetView.didSelectOption = {(value) in
            var sampleRate = 48000
            
            switch value {
            case 0:
                sampleRate = 48000
            case 1:
                sampleRate = 44100
            case 2:
                sampleRate = 32000
            default:
                sampleRate = 48000
            }
            
            weakSelf?.mixConfig?.audioConfig.sampleRate = sampleRate
        }
        
        // 声道数量
        self.audioChannelSheetView.didSelectOption = {(value) in
            var channels = 2
            
            switch value {
            case 0:
                channels = 2
            case 1:
                channels = 1
            default:
                channels = 2
            }
            
            weakSelf?.mixConfig?.audioConfig.channels = channels
        }
        
        // 音频码率
        self.audioBitrateSettingItem.onValueChanged = {(value) in
            
            weakSelf?.mixConfig?.audioConfig.bitrate = Int(value) ?? 64
        }
        
        // 音频编码规格
        self.audioProfileSheetView.didSelectOption = {(value) in
            var profile:ByteRTCMixedStreamAudioProfile = .LC
            
            switch value {
            case 0:
                profile = .LC
            case 1:
                profile = .hEv1
            case 2:
                profile = .hEv2
            default:
                profile = .LC
            }
            
            weakSelf?.mixConfig?.audioConfig.audioProfile = profile
        }
        
        // 视频宽度
        self.videoWidthSettingItem.onValueChanged = {(value) in
            
            weakSelf?.mixConfig?.videoConfig.width = Int(value)!
        }
        
        // 视频高度
        self.videoHeightSettingItem.onValueChanged = {(value) in
            
            weakSelf?.mixConfig?.videoConfig.height = Int(value)!
        }
        
        // 背景色
        self.backgroundSettingItem.onValueChanged = {(value) in
            
            weakSelf?.mixConfig?.backgroundColor = value
        }
        
        // 帧率
        self.videoFpsSettingItem.onValueChanged = {(value) in
            
            weakSelf?.mixConfig?.videoConfig.fps = Int(value)!
        }
        
        // 码率
        self.videoBitrateSettingItem.onValueChanged = {(value) in
            
            weakSelf?.mixConfig?.videoConfig.bitrate = Int(value)!
        }
        
        // 编码格式
        self.videoCodecSheetView.didSelectOption = {(value) in
            var codec:ByteRTCMixedStreamVideoCodecType = .H264
            
            switch value {
            case 0:
                codec = .H264
            case 1:
                codec = .byteVC1
            default:
                codec = .H264
            }
            
            weakSelf?.mixConfig?.videoConfig.videoCodec = codec
        }
        
        // 布局方式:1*4  或者2*2
        self.layoutSheetView.didSelectOption = {(value) in
            weakSelf?.mixConfig?.regions = (weakSelf?.getMixRegions())!
        }
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
        var remoteStreamInfo:ByteRTCStreamInfo?
        
        for (userId, info) in self.userVideoStreamMap {
            if info.roomId == self.roomSettingItem.text {
                remoteStreamInfo = info
            }
        }
        
        if (remoteStreamInfo != nil) {
            self.bindRemoteRenderView(view: self.firstRemoteView, roomId:remoteStreamInfo!.roomId, userId:remoteStreamInfo!.userId)
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
        
        view.addSubview(actionLabel)
        view.addSubview(startPushButton)
        view.addSubview(updatePushButton)
        view.addSubview(stopPushButton)
        
        actionLabel.snp.makeConstraints { make in
            make.top.equalTo(joinButton.snp.bottom).offset(20)
            make.left.equalToSuperview().offset(10)
        }
        
        startPushButton.snp.makeConstraints { make in
            make.top.equalTo(actionLabel.snp.bottom).offset(10)
            make.left.equalToSuperview().offset(10)
            make.height.equalTo(36)
        }
        
        updatePushButton.snp.makeConstraints { make in
            make.centerY.equalTo(startPushButton)
            make.left.equalTo(startPushButton.snp.right).offset(20)
            make.width.height.equalTo(startPushButton)
        }
        
        stopPushButton.snp.makeConstraints { make in
            make.centerY.equalTo(startPushButton)
            make.left.equalTo(updatePushButton.snp.right).offset(20)
            make.right.equalToSuperview().offset(-10)
            make.width.height.equalTo(startPushButton)
        }
        
        view.addSubview(pushConfigLabel)
        view.addSubview(urlTextField)
        
        pushConfigLabel.snp.makeConstraints { make in
            make.top.equalTo(startPushButton.snp.bottom).offset(20)
            make.left.equalToSuperview().offset(10)
        }
        
        urlTextField.snp.makeConstraints { make in
            make.top.equalTo(pushConfigLabel.snp.bottom).offset(10)
            make.left.equalToSuperview().offset(10)
            make.height.equalTo(30)
            make.right.equalToSuperview().offset(-10)
        }
        
        view.addSubview(audioConfigLabel)
        view.addSubview(audioBitrateSettingItem)
        view.addSubview(audioSampleRateSheetView)
        view.addSubview(audioChannelSheetView)
        view.addSubview(audioBitrateSettingItem)
        view.addSubview(audioProfileSheetView)
        view.addSubview(audioCodecSheetView)
        
        audioConfigLabel.snp.makeConstraints { make in
            make.top.equalTo(urlTextField.snp.bottom).offset(20)
            make.left.equalToSuperview().offset(10)
        }
        
        audioBitrateSettingItem.snp.makeConstraints { make in
            make.top.equalTo(audioConfigLabel.snp.bottom).offset(10)
            make.left.equalToSuperview().offset(10)
        }
        
        audioSampleRateSheetView.snp.makeConstraints { make in
            make.top.equalTo(audioBitrateSettingItem.snp.bottom).offset(10)
            make.left.equalToSuperview().offset(10)
            make.right.equalToSuperview().offset(-10)
        }
        
        audioChannelSheetView.snp.makeConstraints { make in
            make.top.equalTo(audioSampleRateSheetView.snp.bottom).offset(10)
            make.left.equalToSuperview().offset(10)
            make.right.equalToSuperview().offset(-10)
        }
        
        view.addSubview(audioProfileSheetView)
        view.addSubview(audioCodecSheetView)
        
        audioProfileSheetView.snp.makeConstraints { make in
            make.top.equalTo(audioChannelSheetView.snp.bottom).offset(10)
            make.left.equalToSuperview().offset(10)
            make.right.equalToSuperview().offset(-10)
        }
        
        audioCodecSheetView.snp.makeConstraints { make in
            make.top.equalTo(audioProfileSheetView.snp.bottom).offset(10)
            make.left.equalToSuperview().offset(10)
            make.right.equalToSuperview().offset(-10)
        }
        
        view.addSubview(videoConfigLabel)
        view.addSubview(videoWidthSettingItem)
        view.addSubview(videoHeightSettingItem)
        view.addSubview(videoFpsSettingItem)
        view.addSubview(videoBitrateSettingItem)
        view.addSubview(backgroundSettingItem)
        view.addSubview(videoCodecSheetView)
        
        videoConfigLabel.snp.makeConstraints { make in
            make.top.equalTo(audioCodecSheetView.snp.bottom).offset(20)
            make.left.equalToSuperview().offset(10)
        }
        
        videoWidthSettingItem.snp.makeConstraints { make in
            make.top.equalTo(videoConfigLabel.snp.bottom).offset(10)
            make.left.equalToSuperview().offset(10)
        }
        
        videoHeightSettingItem.snp.makeConstraints { make in
            make.centerY.equalTo(videoWidthSettingItem)
            make.right.equalToSuperview().offset(-10)
        }
        
        videoFpsSettingItem.snp.makeConstraints { make in
            make.top.equalTo(videoWidthSettingItem.snp.bottom).offset(20)
            make.left.equalToSuperview().offset(10)
        }
        
        videoBitrateSettingItem.snp.makeConstraints { make in
            make.centerY.equalTo(videoFpsSettingItem)
            make.right.equalToSuperview().offset(-10)
        }
        
        videoCodecSheetView.snp.makeConstraints { make in
            make.top.equalTo(videoFpsSettingItem.snp.bottom).offset(10)
            make.left.equalToSuperview().offset(10)
            make.right.equalToSuperview().offset(-10)
        }
        
        backgroundSettingItem.snp.makeConstraints { make in
            make.top.equalTo(videoCodecSheetView.snp.bottom).offset(10)
            make.left.equalToSuperview().offset(10)
        }

        view.addSubview(layoutLabel)
        view.addSubview(layoutSheetView)
        
        layoutLabel.snp.makeConstraints { make in
            make.top.equalTo(backgroundSettingItem.snp.bottom).offset(20)
            make.left.equalToSuperview().offset(10)
        }
        
        layoutSheetView.snp.makeConstraints { make in
            make.top.equalTo(layoutLabel.snp.bottom).offset(10)
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
    
    lazy var actionLabel: UILabel = {
        let label = UILabel.init()
        label.text = "推流操作"
        label.font = UIFont.boldSystemFont(ofSize: 18)
        return label
    }()
    
    lazy var startPushButton: UIButton = {
        let button = BaseButton()
        button.setTitle("开始推流", for: .normal)
        button.addTarget(self, action: #selector(startPushCDN), for: .touchUpInside)
        return button
    }()
    
    lazy var updatePushButton: UIButton = {
        let button = BaseButton()
        button.setTitle("更新参数", for: .normal)
        button.addTarget(self, action: #selector(updatePushConfig), for: .touchUpInside)
        return button
    }()
    
    lazy var stopPushButton: UIButton = {
        let button = BaseButton()
        button.setTitle("停止推流", for: .normal)
        button.addTarget(self, action: #selector(stopPushCDN), for: .touchUpInside)
        return button
    }()
    
    lazy var pushConfigLabel: UILabel = {
        let label = UILabel.init()
        label.text = "推流参数设置"
        label.font = actionLabel.font

        return label
    }()
    
    lazy var urlTextField: TextFieldView = {
        let textField = TextFieldView()
        textField.title = "推流地址:"
        textField.text = ""
        textField.inputTextField.keyboardType = .URL
        return textField
    }()
    
    lazy var audioConfigLabel: UILabel = {
        let label = UILabel.init()
        label.text = "音频设置"
        label.font = actionLabel.font
        return label
    }()
    
    lazy var audioSampleRateSheetView: ActionSheetView = {
        let actionSheetView = ActionSheetView.init(title: "音频采样率", optionArray: ["48000","44100","32000"], defaultIndex: 0)
        actionSheetView.presentingViewController = self
        
        return actionSheetView
    }()
    
    lazy var audioChannelSheetView: ActionSheetView = {
        let actionSheetView = ActionSheetView.init(title: "音频声道", optionArray: ["2","1"], defaultIndex: 0)
        actionSheetView.presentingViewController = self
        
        return actionSheetView
    }()
    
    lazy var audioBitrateSettingItem: SettingItemView = {
        let settingView = SettingItemView()
        settingView.title = "码率Kbps"
        return settingView
    }()
    
    lazy var audioProfileSheetView: ActionSheetView = {
        let actionSheetView = ActionSheetView.init(title: "音频编码规格", optionArray: ["LC","HEv1","HEv2"], defaultIndex: 0)
        actionSheetView.presentingViewController = self
        
        return actionSheetView
    }()
    
    lazy var audioCodecSheetView: ActionSheetView = {
        let actionSheetView = ActionSheetView.init(title: "音频编码格式", optionArray: ["AAC"], defaultIndex: 0)
        actionSheetView.presentingViewController = self
        
        return actionSheetView
    }()
    
    lazy var videoConfigLabel: UILabel = {
        let label = UILabel.init()
        label.text = "视频设置"
        label.font = actionLabel.font
        return label
    }()
    
    lazy var videoWidthSettingItem: SettingItemView = {
        let settingView = SettingItemView()
        settingView.title = "宽度:"
        return settingView
    }()
    
    lazy var videoHeightSettingItem: SettingItemView = {
        let settingView = SettingItemView()
        settingView.title = "高度:"
        return settingView
    }()
    
    lazy var videoFpsSettingItem: SettingItemView = {
        let settingView = SettingItemView()
        settingView.title = "帧率:"
        return settingView
    }()
    
    lazy var videoBitrateSettingItem: SettingItemView = {
        let settingView = SettingItemView()
        settingView.title = "码率:"
        return settingView
    }()
    
    lazy var backgroundSettingItem: SettingItemView = {
        let settingView = SettingItemView()
        settingView.title = "背景色:"
        settingView.inputTextField.keyboardType = .default
        settingView.inputTextField.placeholder = "#FFFFFF"

        return settingView
    }()
    
    lazy var videoCodecSheetView: ActionSheetView = {
        let actionSheetView = ActionSheetView.init(title: "视频编码格式", optionArray: ["H264","ByteVC1"], defaultIndex: 0)
        actionSheetView.presentingViewController = self
        
        return actionSheetView
    }()
    
    lazy var layoutLabel: UILabel = {
        let label = UILabel.init()
        label.text = "布局方式"
        label.font = actionLabel.font
        return label
    }()
    
    lazy var layoutSheetView: ActionSheetView = {
        let actionSheetView = ActionSheetView.init(title: "布局方式", optionArray: ["1x4","2x2"], defaultIndex: 0)
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
    func rtcRoom(_ rtcRoom: ByteRTCRoom, onUserPublishStreamVideo streamId: String, info: ByteRTCStreamInfo, isPublish: Bool) {
        ToastComponents.shared.show(withMessage: "onUserPublishStream uid: \(info.userId), isPub: \(isPublish)")
        
        if isPublish {
            self.userVideoStreamMap.updateValue(info, forKey: info.userId)
            
            DispatchQueue.main.async {
                self.updateRenderView()
            }
        } else {
            // 从self.users中移除
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
    
    func rtcEngine(_ engine: ByteRTCEngine, onMixedStreamEvent event: ByteRTCMixedStreamTaskEvent, withMixedStreamInfo info: ByteRTCMixedStreamTaskInfo, with errorCode: ByteRTCMixedStreamTaskErrorCode) {
            ToastComponents.shared.show(withMessage: "onMixedStreamEvent:\(event.rawValue) taskId:\(info.taskId) errorCode:\(errorCode.rawValue) + mixType:\(info.description)")
        NSLog("onMixedStreamEvent: \(event), info_des: \(info.description), errorcode : \(errorCode)")
    }
    

}
