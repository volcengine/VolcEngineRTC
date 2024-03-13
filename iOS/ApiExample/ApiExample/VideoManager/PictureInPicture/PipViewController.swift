/**
* 功能名称： VolcEngineRTC 画中画
* 功能简单描述：实现画中画功能
* 参考文档：画中画https://www.volcengine.com/docs/6348/1178325
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
*    setRemoteVideoSink  设置远端视频外部渲染
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
*    本Demo演示功能：开启画中画功能
*    为了展示简单，所有功能的token都由客户端生成，接口Utils::generateToken，接入SDK时建议将Token生成逻辑放在服务端
*/



import UIKit
import AVKit
import SnapKit
import VolcEngineRTC

class PipViewController: BaseViewController, ByteRTCVideoDelegate, ByteRTCRoomDelegate, AVPictureInPictureControllerDelegate {
    
    var rtcVideo: ByteRTCVideo?
    var rtcRoom: ByteRTCRoom?
    var users : Array = Array<ByteRTCRemoteStreamKey>()
    var pipVC: AVPictureInPictureController?
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        self.createUI()
        self.buildRTCEngine()
        self.setupPipController(with: self.containerView)
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
    
    @objc func startPip()  {
        if #available(iOS 16, *) {
            if self.pipVC!.isPictureInPictureActive {
                self.pipVC!.stopPictureInPicture()
                pipButton.setTitle("开启画中画", for: .normal)
            } else {
                self.pipVC!.startPictureInPicture()
                pipButton.setTitle("关闭画中画", for: .normal)
            }
        }else {
            ToastComponents.shared.show(withMessage: "当前系统不支持画中画功能")
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
        // 获取room1的第一个用户和room2的第一个用户
        var remoteUser:ByteRTCRemoteStreamKey?
        
        for streamKey in self.users {
            if remoteUser == nil && streamKey.roomId ==  self.roomSettingItem.text {
                remoteUser = streamKey
            }
        }
        
        if (remoteUser != nil) {
            let roomId = remoteUser!.roomId!
            let userId = remoteUser!.userId!
            
            self.bindRemoteRenderView(view: self.customRenderView,roomId: roomId,userId: userId)
            self.remoteUserIdLabel.text = "\(roomId):\(userId)"
        }else {
            self.remoteUserIdLabel.text = ""
        }
    }
    
    func bindRemoteRenderView(view: CustomVideoRenderView, roomId: String, userId: String) {
        let streamKey = ByteRTCRemoteStreamKey.init()
        streamKey.userId = userId;
        streamKey.roomId = roomId;
        streamKey.streamIndex = .indexMain
        
        // 使用外部渲染
        // 画中画功能依赖外部渲染功能,使用内部渲染会黑屏
        self.rtcVideo?.setRemoteVideoSink(streamKey, withSink: self.customRenderView, withPixelFormat: .original)
    }
    
    func createUI() -> Void {
        
        // 添加视图
        view.addSubview(containerView)
        self.containerView.addSubview(localView)
        self.containerView.addSubview(customRenderView)
        self.containerView.addSubview(remoteUserIdLabel)
        
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
        
        self.customRenderView.snp.makeConstraints { make in
            make.top.right.equalTo(self.containerView)
            make.bottom.equalTo(self.containerView).offset(-30)
            make.width.equalTo(self.containerView).multipliedBy(0.5)
        }
        
        self.remoteUserIdLabel.snp.makeConstraints { make in
            make.left.equalTo(localView.snp.right)
            make.right.bottom.equalTo(self.containerView)
            make.height.equalTo(30)
        }
        
        view.addSubview(roomSettingItem)
        view.addSubview(userSettingItem)
        view.addSubview(joinButton)
        view.addSubview(pipButton)
        
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
        
        pipButton.snp.makeConstraints { make in
            make.top.equalTo(joinButton.snp.bottom).offset(10)
            make.left.right.width.height.equalTo(joinButton)
        }
    }
    
    func setupPipController(with sourceView: UIView) {
        
        if #available(iOS 16, *) {
            let callViewController = AVPictureInPictureVideoCallViewController()
            callViewController.preferredContentSize = CGSize(width: 360, height: 640)
            callViewController.view.backgroundColor = UIColor.clear
            
            let source = AVPictureInPictureController.ContentSource(activeVideoCallSourceView: sourceView, contentViewController: callViewController)
            
            let pipVC = AVPictureInPictureController(contentSource: source)
            pipVC.canStartPictureInPictureAutomaticallyFromInline = true
            pipVC.delegate = self
            self.pipVC = pipVC
        } else {
            ToastComponents.shared.show(withMessage: "当前系统不支持画中画功能")
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
    
    lazy var pipButton: UIButton = {
        let button = BaseButton()
        button.setTitle("开启画中画", for: .normal)
        button.addTarget(self, action: #selector(startPip), for: .touchUpInside)
        return button
    }()
    
    lazy var remoteUserIdLabel: UILabel = {
        let label = UILabel.init()
        label.textAlignment = .center
        return label
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
    
    lazy var customRenderView: CustomVideoRenderView = {
        let view = CustomVideoRenderView.init(frame: CGRectZero)
        return view
    }()
    
    // MARK: AVPictureInPictureControllerDelegate
    func pictureInPictureControllerWillStartPictureInPicture(_ pictureInPictureController: AVPictureInPictureController) {
        // 画中画即将开始
        ToastComponents.shared.show(withMessage: "pictureInPictureControllerWillStart")
    }
    
    func pictureInPictureControllerDidStartPictureInPicture(_ pictureInPictureController: AVPictureInPictureController) {
        ToastComponents.shared.show(withMessage: "pictureInPictureControllerDidStart")
        
        // 画中画已经开始
        pipButton.setTitle("关闭画中画", for: .normal)
        
        if #available(iOS 16.0, *) {
            if let vc = pictureInPictureController.contentSource?.activeVideoCallContentViewController {
                vc.view.addSubview(self.customRenderView)
                self.customRenderView.snp.remakeConstraints() { make in
                    make.edges.equalTo(vc.view)
                }
            }
        }
    }
    
    func pictureInPictureController(_ pictureInPictureController: AVPictureInPictureController, failedToStartPictureInPictureWithError error: Error) {
        // 画中画开始失败
        ToastComponents.shared.show(withMessage: "failedToStartPictureInPicture")
    }
    
    func pictureInPictureControllerWillStopPictureInPicture(_ pictureInPictureController: AVPictureInPictureController) {
        // 画中画即将停止
        ToastComponents.shared.show(withMessage: "pictureInPictureControllerWillStop")
    }
    
    func pictureInPictureControllerDidStopPictureInPicture(_ pictureInPictureController: AVPictureInPictureController) {
        ToastComponents.shared.show(withMessage: "pictureInPictureControllerDidStop")
        
        // 画中画已经停止
        pipButton.setTitle("开启画中画", for: .normal)
        
        self.containerView.addSubview(customRenderView)
        self.customRenderView.snp.remakeConstraints() { make in
            make.top.right.equalTo(self.containerView)
            make.bottom.equalTo(self.containerView).offset(-30)
            make.width.equalTo(self.containerView).multipliedBy(0.5)
        }
    }
    
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
    
    
    // 远端用户加入房间
    func rtcRoom(_ rtcRoom: ByteRTCRoom, onUserJoined userInfo: ByteRTCUserInfo, elapsed: Int) {
        ToastComponents.shared.show(withMessage: "onUserJoined uid: \(userInfo.userId)")
        
    }
    
    // 远端用户离开房间
    func rtcRoom(_ rtcRoom: ByteRTCRoom, onUserLeave uid: String, reason: ByteRTCUserOfflineReason) {
        ToastComponents.shared.show(withMessage: "onUserLeave uid: \(uid)")
        
    }
}

