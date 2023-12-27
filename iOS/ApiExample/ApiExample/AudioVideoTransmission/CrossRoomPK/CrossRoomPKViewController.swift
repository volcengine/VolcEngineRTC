/*
* 功能名称： VolcEngineRTC 跨房转推
* 功能简单描述：跨房间转发媒体流，指可见用户的媒体流可以同时转发到多个 RTC 房间。
*             转发目标房间的数量在 RTC 侧没有限制。 本功能适用于以下场景，观众在原来的房间中就能够接收到来自其他房间主播的媒体流。
* 参考文档： https://www.volcengine.com/docs/6348/104398
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
*     startForwardStreamToRooms 开始转发媒体流
*     stopForwardStreamToRooms  停止转发媒体流
*     updateForwardStreamToRooms 更新参数
*     pauseForwardStreamToAllRooms 暂停转发媒体流
*     resumeforward 恢复转发媒体流
*
*     setLocalVideoCanvas 设置本地视频渲染视图
*     setRemoteVideoCanvas 设置远端视频渲染视图
*
*     onForwardStreamStateChanged  跨房间媒体流转发状态和错误回调
*     onForwardStreamEvent 跨房间媒体流转发事件回调
*     onRoomStateChanged 房间状态回调
*     onLeaveRoom 离房回调
*     onUserJoined 用户加入回调
*     onUserLeave  用户离开回调
*     onUserPublishStream 用户发流回调
*     onUserUnpublishStream 用户停止发流回调
*
* Demo实现时的逻辑
*    本Demo演示功能：在本端房间向其他房间转推媒体流
*    为了展示简单，所有功能的token都由客户端TokenGenerator类生成，请在真正接入时视具体情况而定
*/


import UIKit
import SnapKit
import VolcEngineRTC

class CrossRoomPKViewController: BaseViewController, ByteRTCVideoDelegate, ByteRTCRoomDelegate {
    var rtcVideo: ByteRTCVideo?
    var rtcRoom: ByteRTCRoom?
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        self.createUI()
        self.buildRTCEngine()
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
        
        let roomId2 = self.forwardRoomTextField.text ?? ""
        
        if roomId == roomId2 {
            ToastComponents.shared.show(withMessage: "roomId 不能与转推房间 一样")
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
    
    @objc func startforward()  {
        let roomId = self.forwardRoomTextField.text ?? ""
        
        let vaild = checkValid(roomId)
        if vaild == false {
            ToastComponents.shared.show(withMessage: "输入不合法，只支持数字、大小写字母、@._-,长度小于128字符")
            return
        }
        
        let config = ByteRTCForwardStreamConfiguration.init()
        config.roomId = roomId
        
        // 获取token,建议从服务端获取
        let userId = userTextField.text!
        let token = generatorToken(roomId: roomId, userId: userId)
        
        config.token = token
        
        // 支持向多个房间转推,数组内传入多个config即可
        self.rtcRoom?.startForwardStreamToRooms([config])
    }
    
    @objc func updateforward()  {
        let roomId = self.forwardRoomTextField.text ?? ""
        
        let vaild = checkValid(roomId)
        if vaild == false {
            ToastComponents.shared.show(withMessage: "输入不合法，只支持数字、大小写字母、@._-,长度小于128字符")
            return
        }
        
        let config = ByteRTCForwardStreamConfiguration.init()
        config.roomId = roomId
        
        // 获取token,建议从服务端获取
        let userId = userTextField.text!
        let token = generatorToken(roomId: roomId, userId: userId)
        
        config.token = token
        
        // 支持向多个房间转推,数组内传入多个config即可
        self.rtcRoom?.updateForwardStreamToRooms([config])
    }
    
    @objc func pauseforward()  {
        self.rtcRoom?.pauseForwardStreamToAllRooms()
    }
    
    @objc func resumeforward()  {
        self.rtcRoom?.resumeForwardStreamToAllRooms()
    }
    
    @objc func stopforward()  {
        self.rtcRoom?.stopForwardStreamToRooms()
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
            make.top.equalTo(topView.snp.bottom)
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
            make.right.equalTo(self.view).offset(-10)
            make.width.equalTo(100)
            make.height.equalTo(30)
        }
        
        joinButton.snp.makeConstraints { make in
            make.top.equalTo(roomLabel.snp.bottom).offset(20)
            make.left.equalTo(roomLabel)
            make.right.equalTo(self.view).offset(-10)
            make.height.equalTo(36)
        }
        
        view.addSubview(forwardRoomLabel)
        view.addSubview(forwardRoomTextField)
        view.addSubview(startforwardButton)
        view.addSubview(updateforwardButton)
        view.addSubview(pauseforwardButton)
        view.addSubview(resumeforwardButton)
        view.addSubview(stopforwardButton)
        
        forwardRoomLabel.snp.makeConstraints { make in
            make.top.equalTo(joinButton.snp.bottom).offset(20)
            make.left.equalTo(roomLabel)
        }
        
        forwardRoomTextField.snp.makeConstraints { make in
            make.centerY.equalTo(forwardRoomLabel)
            make.left.equalTo(forwardRoomLabel.snp.right).offset(10)
            make.width.equalTo(100)
            make.height.equalTo(30)
        }

        // 将按钮添加进一个数组
        let buttons: [UIButton] = [startforwardButton, updateforwardButton, pauseforwardButton, resumeforwardButton, stopforwardButton]

        let stackView = UIStackView(arrangedSubviews: buttons)

        // 设置stack view的属性
        stackView.axis = .horizontal
        stackView.distribution = .fillEqually
        stackView.spacing = 10
        stackView.alignment = .fill

        view.addSubview(stackView)
        stackView.snp.makeConstraints { (make) in
            make.top.equalTo(forwardRoomLabel.snp.bottom).offset(10)
            make.bottom.equalTo(self.view.snp.bottom).offset(-getSafeAreaInsets().bottom)
            make.left.equalTo(view).offset(10)
            make.right.equalTo(view).offset(-10)
            make.height.equalTo(36)
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
    
    lazy var forwardRoomLabel: UILabel = {
        let label = UILabel()
        label.text = "跨房间转发"
        return label
    }()
    
    lazy var forwardRoomTextField: UITextField = {
        let textField = UITextField()
        textField.borderStyle = .roundedRect
        return textField
    }()
    
    lazy var startforwardButton: UIButton = {
        let button = BaseButton.init()
        button.setTitle("开始", for: .normal)
        button.addTarget(self, action: #selector(startforward), for: .touchUpInside)
        return button
    }()
    
    lazy var updateforwardButton: UIButton = {
        let button = BaseButton.init()
        button.setTitle("更新", for: .normal)
        button.addTarget(self, action: #selector(updateforward), for: .touchUpInside)
        return button
    }()
    
    lazy var pauseforwardButton: UIButton = {
        let button = BaseButton.init()
        button.setTitle("暂停", for: .normal)
        button.addTarget(self, action: #selector(pauseforward), for: .touchUpInside)
        return button
    }()
    
    lazy var resumeforwardButton: UIButton = {
        let button = BaseButton.init()
        button.setTitle("恢复", for: .normal)
        button.addTarget(self, action: #selector(resumeforward), for: .touchUpInside)
        return button
    }()
    
    lazy var stopforwardButton: UIButton = {
        let button = BaseButton.init()
        button.setTitle("停止", for: .normal)
        button.addTarget(self, action: #selector(stopforward), for: .touchUpInside)
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
    
    // MARK: ByteRTCVideoDelegate & ByteRTCRoomDelegate
    //进房状态
    func rtcRoom(_ rtcRoom: ByteRTCRoom, onRoomStateChanged roomId: String, withUid uid: String, state: Int, extraInfo: String) {
        ToastComponents.shared.show(withMessage: "onRoomStateChanged uid: \(uid) state:\(state)")
        
    }
    
    // 远端用户发布流
    func rtcRoom(_ rtcRoom: ByteRTCRoom, onUserPublishStream userId: String, type: ByteRTCMediaStreamType) {
        ToastComponents.shared.show(withMessage: "onUserPublishStream uid: \(userId)")
        
    }
    
     // 远端用户取消发布流
    func rtcRoom(_ rtcRoom: ByteRTCRoom, onUserUnpublishStream userId: String, type: ByteRTCMediaStreamType, reason: ByteRTCStreamRemoveReason) {
        ToastComponents.shared.show(withMessage: "onUserUnpublishStream uid: \(userId)")
        
    }
    
    // 远端用户加入房间
    func rtcRoom(_ rtcRoom: ByteRTCRoom, onUserJoined userInfo: ByteRTCUserInfo, elapsed: Int) {
        ToastComponents.shared.show(withMessage: "onUserJoined uid: \(userInfo.userId)")
        
    }
    
    // 远端用户离开房间
    func rtcRoom(_ rtcRoom: ByteRTCRoom, onUserLeave uid: String, reason: ByteRTCUserOfflineReason) {
        ToastComponents.shared.show(withMessage: "onUserLeave uid: \(uid)")
        
    }
    
    // 转推状态
    func rtcRoom(_ rtcRoom: ByteRTCRoom, onForwardStreamStateChanged infos: [ByteRTCForwardStreamStateInfo]) {
        ToastComponents.shared.show(withMessage: "onForwardStreamStateChanged state: \(String(describing: infos.first?.state.rawValue))")
    }
    
    // 转推事件
    func rtcRoom(_ rtcRoom: ByteRTCRoom, onForwardStreamEvent infos: [ByteRTCForwardStreamEventInfo]) {
        ToastComponents.shared.show(withMessage: "onForwardStreamEvent event: \(String(describing: infos.first?.event.rawValue))")
    }
}
