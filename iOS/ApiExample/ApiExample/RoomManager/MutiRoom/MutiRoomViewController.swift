/**
 * 功能名称： VolcEngineRTC 多房间
 * 功能简单描述：你可能需要让同一个用户加入多个 RTC 房间，同时收听/收看不同房间中的音视频，并在其中一个房间中发布音视频
 * 参考文档： https://www.volcengine.com/docs/6348/196844
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
 *     setLocalVideoCanvas 设置本地视频渲染视图
 *     setRemoteVideoCanvas 设置远端视频渲染视图
 *
 *     onRoomStateChanged 房间状态回调
 *     onLeaveRoom 离房回调
 *     onUserJoined 用户加入回调
 *     onUserLeave  用户离开回调
 *     onUserPublishStream 用户发流回调
 *     onUserUnpublishStream 用户停止发流回调
 *
 * Demo实现时的逻辑
 *    为了展示简单，所有功能的token都由客户端TokenGenerator类生成，请在真正接入时视具体情况而定
 *    本Demo演示功能：仅展示3个视频窗口，第一行展示本地采集画面，第二行分别展示room1 远端用户和room2远端用户
*/

import Foundation
import SnapKit
import VolcEngineRTC

class MutiRoomViewController: BaseViewController, ByteRTCEngineDelegate, ByteRTCRoomDelegate {
    
    var rtcVideo: ByteRTCEngine?
    var rtcRoom1: ByteRTCRoom?
    var rtcRoom2: ByteRTCRoom?
    var userVideoStreamMap: Dictionary = Dictionary<String, ByteRTCStreamInfo>()

    override func viewDidLoad() {
        super.viewDidLoad()
        
        self.createUI()
        self.buildRTCEngine()
    }
    
    deinit {
        self.rtcRoom1?.leave()
        self.rtcRoom1?.destroy()
        self.rtcRoom1 = nil
        
        self.rtcRoom2?.leave()
        self.rtcRoom2?.destroy()
        self.rtcRoom2 = nil
        
        ByteRTCEngine.destroyRTCEngine()
        self.rtcVideo = nil
    }
    
    // MARK: Private method
    
    @objc func joinRoom1()  {
        let roomId = self.roomTextField1.text ?? ""
        let userId = self.userTextField1.text ?? ""
        
        var vaild = checkValid(roomId)
        if vaild == false {
            ToastComponents.shared.show(withMessage: "roomid1 不合法")
            return
        }
        
        vaild = checkValid(userId)
        if vaild == false {
            ToastComponents.shared.show(withMessage: "userid1 不合法")
            return
        }
        
        joinButton1.isSelected = !joinButton1.isSelected
        
        if joinButton1.isSelected {
            joinButton1.setTitle("离开房间1", for: .normal)
            
            // 加入房间
            self.rtcRoom1 = self.rtcVideo?.createRTCRoom(roomId)
            self.rtcRoom1?.delegate = self
            
            // 获取token,建议从服务端获取
            let token = generatorToken(roomId: roomId, userId: userId)
            
            let userInfo = ByteRTCUserInfo.init()
            userInfo.userId = userId
            
            // 自动发布和订阅流
            let roomCfg = ByteRTCRoomConfig.init()
            roomCfg.isPublishAudio = true
            roomCfg.isPublishVideo = true
            roomCfg.isAutoSubscribeAudio = true
            roomCfg.isAutoSubscribeVideo = true
            
            self.rtcRoom1?.joinRoom(token, userInfo: userInfo, userVisibility: true, roomConfig: roomCfg)
        }
        else {
            joinButton1.setTitle("加入房间1", for: .normal)
            self.rtcRoom1?.leave()
            self.firstRemoteView.userId = ""
        }
        
    }
    
    @objc func joinRoom2() -> Void {
        let roomId = self.roomTextField2.text ?? ""
        let userId = self.userTextField2.text ?? ""
        
        var vaild = checkValid(roomId)
        if vaild == false {
            ToastComponents.shared.show(withMessage: "roomid2 不合法")
            return
        }
        
        vaild = checkValid(userId)
        if vaild == false {
            ToastComponents.shared.show(withMessage: "userid2 不合法")
            return
        }
        
        joinButton2.isSelected = !joinButton2.isSelected
        
        if joinButton2.isSelected {
            joinButton2.setTitle("离开房间2", for: .normal)
            
            // 加入房间
            self.rtcRoom2 = self.rtcVideo?.createRTCRoom(roomId)
            self.rtcRoom2?.delegate = self
            
            // 获取token,建议从服务端获取
            let token = generatorToken(roomId: roomId, userId: userId)
            
            let userInfo = ByteRTCUserInfo.init()
            userInfo.userId = userId
            
            let roomCfg = ByteRTCRoomConfig.init()
            // 房间2不自动发流,只能在一个房间内publish
            roomCfg.isPublishAudio = false
            roomCfg.isPublishVideo = false
            roomCfg.isAutoSubscribeAudio = true
            roomCfg.isAutoSubscribeVideo = true
            
            let ret = self.rtcRoom2?.joinRoom(token, userInfo: userInfo, userVisibility: true, roomConfig: roomCfg)
            if (ret != 0) {
                ToastComponents.shared.show(withMessage: "加房失败， ret: \(String(describing: ret))")
            }
        }
        else {
            joinButton2.setTitle("加入房间2", for: .normal)
            self.rtcRoom2?.leave()
            self.secondRemoteView.userId = ""
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
        
        // 开启本地渲染
        self.bindLocalRenderView()
    }
    
    func bindLocalRenderView() {
        // 设置本地渲染视图
        let canvas = ByteRTCVideoCanvas.init()
        canvas.view = self.localView.videoView
        canvas.renderMode = .hidden
        self.localView.userId = userTextField1.text ?? ""
        
        self.rtcVideo?.setLocalVideoCanvas(withCanvas: canvas);
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
    
    func updateRenderView() {
        // 获取room1的第一个用户和room2的第一个用户
        var remoteStreamInfo1:ByteRTCStreamInfo?
        var remoteStreamInfo2:ByteRTCStreamInfo?

        for (userId, info) in self.userVideoStreamMap {
            if info.roomId == self.roomTextField1.text {
                remoteStreamInfo1 = info
            }
            if info.roomId == self.roomTextField2.text {
                remoteStreamInfo2 = info
            }
        }
        
        
        if (remoteStreamInfo1 != nil) {
            self.bindRemoteRenderView(view: self.firstRemoteView, roomId:remoteStreamInfo1!.roomId, userId:remoteStreamInfo1!.userId)
        }
        
        if (remoteStreamInfo2 != nil) {
            self.bindRemoteRenderView(view: self.secondRemoteView, roomId:remoteStreamInfo1!.roomId, userId:remoteStreamInfo1!.userId)
        }
    }
    
    func createUI() -> Void {
        // 添加视图
        view.addSubview(containerView)
        self.containerView.addSubview(localView)
        self.containerView.addSubview(firstRemoteView)
        self.containerView.addSubview(secondRemoteView)
        
        containerView.snp.makeConstraints { make in
            make.top.equalTo(self.topView.snp.bottom)
            make.left.right.equalTo(self.view)
        }
        
        self.localView.snp.makeConstraints { make in
            make.left.top.equalTo(self.containerView)
            make.width.equalTo(self.containerView)
            make.height.equalTo(self.containerView).multipliedBy(0.5)
        }
        
        self.firstRemoteView.snp.makeConstraints { make in
            make.left.bottom.equalTo(self.containerView)
            make.width.height.equalTo(self.containerView).multipliedBy(0.5)
        }
        
        self.secondRemoteView.snp.makeConstraints { make in
            make.right.bottom.equalTo(self.containerView)
            make.width.height.equalTo(self.containerView).multipliedBy(0.5)
        }
        
        view.addSubview(roomLabel1)
        view.addSubview(roomTextField1)
        view.addSubview(userLabel1)
        view.addSubview(userTextField1)
        view.addSubview(joinButton1)
        view.addSubview(publishLabel)
        
        roomLabel1.snp.makeConstraints { make in
            make.top.equalTo(self.containerView.snp.bottom).offset(10)
            make.left.equalToSuperview().offset(10)
        }
        
        roomTextField1.snp.makeConstraints { make in
            make.centerY.equalTo(roomLabel1)
            make.left.equalTo(roomLabel1.snp.right).offset(10)
            make.width.equalTo(100)
            make.height.equalTo(30)
        }
        
        userLabel1.snp.makeConstraints { make in
            make.centerY.equalTo(roomLabel1)
        }
        
        userTextField1.snp.makeConstraints { make in
            make.centerY.equalTo(roomLabel1)
            make.left.equalTo(userLabel1.snp.right).offset(10)
            make.right.equalTo(self.view).offset(-10)
            make.width.equalTo(100)
            make.height.equalTo(30)
        }
        
        publishLabel.snp.makeConstraints { make in
            make.top.equalTo(roomLabel1.snp.bottom).offset(10)
            make.left.equalTo(roomLabel1)
        }
        
        joinButton1.snp.makeConstraints { make in
            make.top.equalTo(publishLabel.snp.bottom).offset(10)
            make.left.equalTo(publishLabel)
            make.right.equalTo(self.view).offset(-10)
            make.height.equalTo(36)
        }
        
        // 添加视图
        view.addSubview(roomLabel2)
        view.addSubview(roomTextField2)
        view.addSubview(userLabel2)
        view.addSubview(userTextField2)
        view.addSubview(joinButton2)
        
        roomLabel2.snp.makeConstraints { make in
            make.top.equalTo(joinButton1.snp.bottom).offset(20)
            make.left.equalToSuperview().offset(10)
        }
        
        roomTextField2.snp.makeConstraints { make in
            make.centerY.equalTo(roomLabel2)
            make.left.equalTo(roomLabel2.snp.right).offset(10)
            make.width.equalTo(100)
            make.height.equalTo(30)
        }
        
        userLabel2.snp.makeConstraints { make in
            make.centerY.equalTo(roomLabel2)
        }
        
        userTextField2.snp.makeConstraints { make in
            make.centerY.equalTo(roomLabel2)
            make.left.equalTo(userLabel2.snp.right).offset(10)
            make.right.equalTo(userTextField1)
            make.width.equalTo(100)
            make.height.equalTo(30)
        }
        
        joinButton2.snp.makeConstraints { make in
            make.top.equalTo(roomLabel2.snp.bottom).offset(10)
            make.bottom.equalToSuperview().offset(-getSafeAreaInsets().bottom)
            make.left.right.equalTo(joinButton1)
            make.height.equalTo(36)
        }
    }
    
    // MARK: Lazy laod
    lazy var roomLabel1: UILabel = {
        let label = UILabel()
        label.text = "房间1"
        return label
    }()
    
    lazy var roomTextField1: UITextField = {
        let textField = UITextField()
        textField.borderStyle = .roundedRect
        return textField
    }()
    
    lazy var userLabel1: UILabel = {
        let label = UILabel()
        label.text = "用户1"
        return label
    }()
    
    lazy var userTextField1: UITextField = {
        let textField = UITextField()
        textField.borderStyle = .roundedRect
        return textField
    }()
    
    lazy var joinButton1: UIButton = {
        let button = BaseButton.init()
        button.setTitle("加入房间1", for: .normal)
        button.addTarget(self, action: #selector(joinRoom1), for: .touchUpInside)
        return button
    }()
    
    lazy var publishLabel: UILabel = {
        let label = UILabel()
        label.text = "房间1可以发流"
        return label
    }()
    
    lazy var roomLabel2: UILabel = {
        let label = UILabel()
        label.text = "房间2"
        return label
    }()
    
    lazy var roomTextField2: UITextField = {
        let textField = UITextField()
        textField.borderStyle = .roundedRect
        return textField
    }()
    
    lazy var userLabel2: UILabel = {
        let label = UILabel()
        label.text = "用户2"
        return label
    }()
    
    lazy var userTextField2: UITextField = {
        let textField = UITextField()
        textField.borderStyle = .roundedRect
        return textField
    }()
    
    lazy var joinButton2: UIButton = {
        let button = BaseButton.init()
        button.setTitle("加入房间2", for: .normal)
        button.addTarget(self, action: #selector(joinRoom2), for: .touchUpInside)
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
    
    lazy var firstRemoteView: UserVideoView = {
        let view = UserVideoView.init()
        return view
    }()
    
    lazy var secondRemoteView: UserVideoView = {
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
        ToastComponents.shared.show(withMessage: "onUserPublishStreamVideo uid: \(info.userId), isPub: \(isPublish)")
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
  
    func rtcRoom(_ rtcRoom: ByteRTCRoom, onUserPublishStreamAudio streamId: String, info: ByteRTCStreamInfo, isPublish: Bool) {
        ToastComponents.shared.show(withMessage: "onUserPublishStreamAudio uid: \(info.userId), isPub: \(isPublish)")
    }
    
    
    // 远端用户加入房间
    func rtcRoom(_ rtcRoom: ByteRTCRoom, onUserJoined userInfo: ByteRTCUserInfo) {
        ToastComponents.shared.show(withMessage: "onUserJoined uid: \(userInfo.userId)")
        
    }
    
    // 远端用户离开房间
    func rtcRoom(_ rtcRoom: ByteRTCRoom, onUserLeave uid: String, reason: ByteRTCUserOfflineReason) {
        ToastComponents.shared.show(withMessage: "onUserLeave uid: \(uid)")
        
    }
    
    // token 即将过期
    func onTokenWillExpire(_ rtcRoom: ByteRTCRoom) {
        ToastComponents.shared.show(withMessage: "token即将过期,请重新获取token")
    }
}
