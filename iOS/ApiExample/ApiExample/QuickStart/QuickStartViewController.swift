/**
* 功能名称： VolcEngineRTC 快速开始
* 功能简单描述：快速跑通 ByteRTC 音视频通话功能
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
*     onRoomStateChanged 房间状态回调
*     onLeaveRoom 离房回调
*     onUserJoined 用户加入回调
*     onUserLeave  用户离开回调
*     onUserPublishStream 用户发流回调
*     onUserUnpublishStream 用户停止发流回调
*
*
* Demo实现时的逻辑
*    请按照界面给出的步骤开发音视频通话功能
*    为了展示简单，所有功能的token都由客户端TokenGenerator类生成，请在真正接入时视具体情况而定
*/


import UIKit
import SnapKit
import VolcEngineRTC

class QuickStartViewController: BaseViewController, ByteRTCVideoDelegate, ByteRTCRoomDelegate {
    
    var rtcVideo: ByteRTCVideo?
    var rtcRoom: ByteRTCRoom?
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        self.createUI()
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
    
    func buildActions() {
        stepButton1.buttonAction = { [weak self] in
            if self?.rtcVideo == nil {
                // 创建引擎
                self?.rtcVideo = ByteRTCVideo.createRTCVideo(kAppID, delegate: self, parameters: [:])
            }
        }
        
        stepButton2.buttonAction = { [weak self] in
            if self?.rtcVideo != nil {
                // 开启本地音视频采集
                self?.rtcVideo?.startVideoCapture()
                self?.rtcVideo?.startAudioCapture()
            }
        }
        
        stepButton3.buttonAction = { [weak self] in
            if self?.rtcVideo != nil {
                // 设置本地渲染
                self?.bindLocalRenderView()
            }
        }
        
        stepButton4.buttonAction = { [weak self] in
            if self?.rtcVideo != nil {
                // 加入房间
                self?.joinRoom()
            }
        }
        
        stepButton6.buttonAction = { [weak self] in
            if self?.rtcRoom != nil {
                // 离开房间
                self?.rtcRoom?.leaveRoom()
            }
        }
        
        stepButton7.buttonAction = { [weak self] in
            if self?.rtcRoom != nil {
                // 销毁房间
                self?.rtcRoom?.destroy()
                self?.rtcRoom = nil
            }
        }
        
        stepButton8.buttonAction = { [weak self] in
            self?.localView.userId = ""
            if self?.rtcVideo != nil {
                // 销毁引擎
                ByteRTCVideo.destroyRTCVideo()
                self?.rtcVideo = nil
            }
        }
    }
    
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
    
    func bindLocalRenderView() {
        // 设置本地渲染视图
        let userId = self.userTextField.text ?? ""
        self.localView.userId = userId
        
        let canvas = ByteRTCVideoCanvas.init()
        canvas.view = self.localView.videoView
        canvas.renderMode = .hidden
        
        self.rtcVideo?.setLocalVideoCanvas(.indexMain, withCanvas: canvas);
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
    
    func removeRemoteRenderView(view: UserVideoView, roomId: String, userId: String) {
        // 移除远端用户视频渲染视图
        let canvas = ByteRTCVideoCanvas.init()
        // view置为空
        canvas.view = nil
        canvas.renderMode = .hidden
        view.userId = ""
        
        let streamKey = ByteRTCRemoteStreamKey.init()
        streamKey.userId = userId;
        streamKey.roomId = roomId;
        streamKey.streamIndex = .indexMain
        
        self.rtcVideo?.setRemoteVideoCanvas(streamKey, withCanvas: canvas)
    }
    
    func createUI() -> Void {
        // 添加视图
        view.addSubview(containerView)
        self.containerView.addSubview(localView)
        self.containerView.addSubview(remoteView)
        
        containerView.snp.makeConstraints { make in
            make.top.equalTo(topView.snp.bottom)
            make.left.right.equalTo(self.view)
        }
        
        self.localView.snp.makeConstraints { make in
            make.left.top.equalTo(self.containerView)
            make.height.equalTo(self.containerView)
            make.width.equalTo(self.containerView).multipliedBy(0.5)
        }
        
        self.remoteView.snp.makeConstraints { make in
            make.right.bottom.equalTo(self.containerView)
            make.height.equalTo(self.containerView)
            make.width.equalTo(self.containerView).multipliedBy(0.5)
        }
        
        view.addSubview(roomTextField)
        view.addSubview(userTextField)
        view.addSubview(stepButton1)
        view.addSubview(stepButton2)
        view.addSubview(stepButton3)
        view.addSubview(stepButton4)
        view.addSubview(stepLabel5)
        view.addSubview(stepButton6)
        view.addSubview(stepButton7)
        view.addSubview(stepButton8)
        
        roomTextField.snp.makeConstraints { make in
            make.left.equalToSuperview().offset(10)
            make.height.equalTo(32)
            make.top.lessThanOrEqualTo(containerView.snp.bottom).offset(10)
        }
        
        userTextField.snp.makeConstraints { make in
            make.centerY.equalTo(roomTextField)
            make.left.equalTo(roomTextField.snp.right).offset(20)
            make.right.equalToSuperview().offset(-10)
            make.width.equalTo(roomTextField)
            make.height.equalTo(32)
        }
        
        stepButton1.snp.makeConstraints { make in
            make.top.equalTo(roomTextField.snp.bottom).offset(10)
            make.left.right.equalToSuperview()
        }
        
        stepButton2.snp.makeConstraints { make in
            make.top.equalTo(stepButton1.snp.bottom).offset(10)
            make.left.right.equalToSuperview()
        }
        
        stepButton3.snp.makeConstraints { make in
            make.top.equalTo(stepButton2.snp.bottom).offset(10)
            make.left.right.equalToSuperview()
        }
        
        stepButton4.snp.makeConstraints { make in
            make.top.equalTo(stepButton3.snp.bottom).offset(10)
            make.left.right.equalToSuperview()
        }
        
        stepLabel5.snp.makeConstraints { make in
            make.top.equalTo(stepButton4.snp.bottom).offset(10)
            make.left.equalToSuperview().offset(10)
        }
        
        stepButton6.snp.makeConstraints { make in
            make.top.equalTo(stepLabel5.snp.bottom).offset(10)
            make.left.right.equalToSuperview()
        }
        
        stepButton7.snp.makeConstraints { make in
            make.top.equalTo(stepButton6.snp.bottom).offset(10)
            make.left.right.equalToSuperview()
        }
        
        stepButton8.snp.makeConstraints { make in
            make.top.equalTo(stepButton7.snp.bottom).offset(10)
            make.bottom.equalTo(self.view.snp.bottom).offset(-20)
            make.left.right.equalToSuperview()
        }
    }
    
    // MARK: lazyload
    lazy var roomTextField: UITextField = {
        let textField = UITextField()
        textField.placeholder = "请输入房间ID"
        textField.borderStyle = .roundedRect
        return textField
    }()
    
    lazy var userTextField: UITextField = {
        let textField = UITextField()
        textField.placeholder = "请输入用户ID"
        textField.borderStyle = .roundedRect
        return textField
    }()
    
    lazy var stepButton1: StepButton = {
        let stepButton = StepButton.init(labelText: "Step1: 创建引擎", buttonText: "创建引擎")
        
        return stepButton
    }()
    
    lazy var stepButton2: StepButton = {
        let stepButton = StepButton.init(labelText: "Step2: 开启音视频采集", buttonText: "开启采集")
        
        return stepButton
    }()
    lazy var stepButton3: StepButton = {
        let stepButton = StepButton.init(labelText: "Step3: 设置本地渲染", buttonText: "设置本地渲染")
        
        return stepButton
    }()
    
    lazy var stepButton4: StepButton = {
        let stepButton = StepButton.init(labelText: "Step4: 加入房间", buttonText: "加入房间")
        
        return stepButton
    }()
    
    lazy var stepLabel5: UILabel = {
        let label = UILabel.init()
        label.textAlignment = .center
        label.font = UIFont.systemFont(ofSize: 16)
        label.text = "Step5: 更新远端用户View"
        return label
    }()
    
    lazy var stepButton6: StepButton = {
        let stepButton = StepButton.init(labelText: "Step6: 离开房间", buttonText: "离开房间")
        
        return stepButton
    }()
    lazy var stepButton7: StepButton = {
        let stepButton = StepButton.init(labelText: "Step7: 销毁房间", buttonText: "销毁房间")
        
        return stepButton
    }()
    lazy var stepButton8: StepButton = {
        let stepButton = StepButton.init(labelText: "Step8: 销毁引擎", buttonText: "销毁引擎")
        
        return stepButton
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
    
    lazy var remoteView: UserVideoView = {
        let view = UserVideoView.init()
        return view
    }()
    
    // MARK: ByteRTCVideoDelegate & ByteRTCRoomDelegate
    //进房状态
    func rtcRoom(_ rtcRoom: ByteRTCRoom, onRoomStateChanged roomId: String, withUid uid: String, state: Int, extraInfo: String) {
        ToastComponents.shared.show(withMessage: "onRoomStateChanged uid: \(uid) state:\(state)")
        
        if state == 0 {
            print("Join Room Success")
        }
    }

    // 远端用户发布流
    func rtcRoom(_ rtcRoom: ByteRTCRoom, onUserPublishStream userId: String, type: ByteRTCMediaStreamType) {
        ToastComponents.shared.show(withMessage: "onUserPublishStream uid: \(userId)")
        // 渲染远端用户
        if type == .video || type == .both {
            DispatchQueue.main.async {
                self.bindRemoteRenderView(view: self.remoteView, roomId: rtcRoom.getId(), userId: userId)
            }
        }
    }
    
    // 远端用户取消发布流
    func rtcRoom(_ rtcRoom: ByteRTCRoom, onUserUnpublishStream userId: String, type: ByteRTCMediaStreamType, reason: ByteRTCStreamRemoveReason) {
        ToastComponents.shared.show(withMessage: "onUserUnpublishStream uid: \(userId)")
        
        if type == .video || type == .both {
            // 移除UI显示
            DispatchQueue.main.async {
                // 移除远端视图
                if userId == self.remoteView.userId {
                    self.removeRemoteRenderView(view: self.remoteView, roomId: rtcRoom.getId(), userId: userId)
                }
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
    
    func onTokenWillExpire(_ rtcRoom: ByteRTCRoom) {
       // token 即将过期
        ToastComponents.shared.show(withMessage: "token即将过期,请重新获取token")
    }
}
