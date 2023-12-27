/**
* 功能名称： VolcEngineRTC 视频常用配置
* 功能简单描述：修改视频常用的采集、编码参数，设置旋转角度、水印等功能
* 参考文档：视频旋转 https://www.volcengine.com/docs/6348/106458

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
*     setVideoWatermark 在指定视频流上添加水印
*     clearVideoWatermark 清除水印
*     setVideoOrientation 设置本端采集的视频帧的旋转角度
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

class VideoRotationViewController: BaseViewController, ByteRTCVideoDelegate, ByteRTCRoomDelegate {
    
    var rtcVideo: ByteRTCVideo?
    var rtcRoom: ByteRTCRoom?
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
    
    @objc func addWatermark() {
        addWatermarkButton.isSelected = !addWatermarkButton.isSelected
        
        if (addWatermarkButton.isSelected) {
            addWatermarkButton.setTitle("移除水印", for: .normal)
            
            let filePath = Bundle.main.path(forResource: "watermark", ofType: "jpg")!
            let config = ByteRTCVideoWatermarkConfig.init()
            config.visibleInPreview = true
            
            let position = ByteRTCVideoByteWatermark.init()
            position.x = Float(200.0/480.0)
            position.y = Float(200.0/640)
            position.width = Float(100.0/480.0)
            position.height = Float(100.0/640.0)
            
            config.positionInPortraitMode = position
            config.positionInLandscapeMode = position
            
            self.rtcVideo?.setVideoWatermark(.indexMain, withImagePath: filePath, withRtcWatermarkConfig: config)
        } else {
            addWatermarkButton.setTitle("添加水印", for: .normal)
            
            self.rtcVideo?.clearVideoWatermark(.indexMain)
        }
    }
    
    func buildActions() {
        weak var weakSelf = self
        // 设置视频帧朝向
        self.videoOrientationSheetView.didSelectOption = {(value) in
            weakSelf?.rtcVideo?.setVideoOrientation(ByteRTCVideoOrientation(rawValue: UInt(value))!)
        }
        
        // 设置采集视频的旋转模式
        self.appOrientationSheetView.didSelectOption = {(value) in
            weakSelf?.rtcVideo?.setVideoRotationMode(ByteRTCVideoRotationMode(rawValue: UInt(value))!)
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

        view.addSubview(roomSettingItem)
        view.addSubview(userSettingItem)
        view.addSubview(joinButton)
        view.addSubview(addWatermarkButton)
        
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
        
        addWatermarkButton.snp.makeConstraints { make in
            make.top.equalTo(joinButton.snp.bottom).offset(10)
            make.left.right.width.height.equalTo(joinButton)
        }
        
        view.addSubview(videoOrientationSheetView)
        view.addSubview(appOrientationSheetView)
        
        videoOrientationSheetView.snp.makeConstraints { make in
            make.top.equalTo(addWatermarkButton.snp.bottom).offset(10)
            make.left.right.equalTo(joinButton)
        }
        
        appOrientationSheetView.snp.makeConstraints { make in
            make.top.equalTo(videoOrientationSheetView.snp.bottom).offset(10)
            make.left.right.equalTo(joinButton)
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
    
    lazy var addWatermarkButton: UIButton = {
        let button = BaseButton()
        button.setTitle("添加水印", for: .normal)
        button.addTarget(self, action: #selector(addWatermark), for: .touchUpInside)
        return button
    }()
    
    lazy var videoOrientationSheetView: ActionSheetView = {
        let actionSheetView = ActionSheetView.init(title: "视频朝向", optionArray: ["Adaptive","Portrait","Landscape"], defaultIndex: 0)
        actionSheetView.presentingViewController = self
        
        return actionSheetView
    }()
    
    lazy var appOrientationSheetView: ActionSheetView = {
        let actionSheetView = ActionSheetView.init(title: "旋转模式", optionArray: ["FollowApp","FollowGSensor"], defaultIndex: 0)
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
