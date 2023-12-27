
/**
* 功能名称： VolcEngineRTC 集成第三方美颜SDK
* 功能简单描述：音视频通话中经常会对本地视频进行美化处理，该Demo展示如何集成相芯SDK，展示美颜功能
* 参考文档：https://www.volcengine.com/docs/6348/79888
*
* 此功能涉及的RTC API及回调：
*     createRTCVideo 创建引擎
*     destroyRTCVideo 销毁引擎
*     startAudioCapture 开启音频采集
*     startVideoCapture 开启视频采集
*     createRTCRoom 创建RTC房间
*     joinRoom 进入RTC房间
*     leaveRoom 离开RTC房间
*     destroy 销毁RTC房间
*     registerLocalVideoProcessor 设置自定义视频前处理器，通过ByteRTCVideoProcessorDelegate收到视频帧回调
*
*     onRoomStateChanged 房间状态回调
*     onLeaveRoom 离房回调
*     onUserJoined 用户加入回调
*     onUserLeave  用户离开回调
*     onUserPublishStream 用户发流回调
*     onUserUnpublishStream 用户停止发流回调
*
*    processVideoFrame 支持修改视频帧并发送到远端
*

*
* Demo实现时的逻辑
*    本Demo演示功能：ByteRTC 集成相芯SDK，展示美颜功能
*    registerLocalVideoProcessor 注册本地视频帧回调，processVideoFrame接口修改视频帧并进行美颜处理
*    processVideoFrame 中收到的视频帧来自不同线程，而相芯SDK不支持跨线程的初始化和调用，因此新增线程统一处理视频数据
*    CNAMASDK_H 宏用来区分是否已经集成过相芯SDK，集成后则展示功能界面；未集成时展示集成步骤
*    使用相芯SDK功能，需先申请账号
*    为了展示简单，所有功能的token都由客户端TokenGenerator类生成，请在真正接入时视具体情况而定
*/


import UIKit
import SnapKit
import VolcEngineRTC

class FaceUnityViewController: BaseViewController, ByteRTCVideoDelegate, ByteRTCRoomDelegate {
    
    var rtcVideo: ByteRTCVideo?
    var rtcRoom: ByteRTCRoom?
    let roomId = "202311"
    let userId = "999999"
    var processor:FaceUnityProcessor?
    
    deinit {
        self.rtcRoom?.leaveRoom()
        self.rtcRoom?.destroy()
        self.rtcRoom = nil
        
        ByteRTCVideo.destroyRTCVideo()
        self.rtcVideo = nil
        
        FUDemoManager.destory()
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        self.createUI()
        self.buildRTCEngine()
        self.bindLocalRenderView()
        self.joinRoom()
    }
    
    // MARK: Private method
    func createUI() -> Void {
        // 添加视图
        view.addSubview(containerView)
        self.containerView.addSubview(localView)
        
        containerView.snp.makeConstraints { make in
            make.top.equalTo(topView.snp.bottom)
            make.height.equalTo(self.view).multipliedBy(0.6)
            make.left.right.equalTo(self.view)
        }
        
        self.localView.snp.makeConstraints { make in
            make.left.top.equalTo(self.containerView)
            make.height.equalTo(self.containerView)
            make.width.equalTo(self.containerView)
        }
        
        // 相芯操作界面
        FUDemoManager.setupFUSDK()
        FUDemoManager.shared().stickerH = true
        FUDemoManager.shared().addDemoView(to: self.view, originY: CGRectGetHeight(self.view.frame) - FUBottomBarHeight - CGRectGetHeight(self.topView.frame))
    }
    
    func buildRTCEngine() {
        // 创建引擎
        self.rtcVideo = ByteRTCVideo.createRTCVideo(kAppID, delegate: self, parameters: [:])
        
        // 开启本地音视频采集
        self.rtcVideo?.startVideoCapture()
        self.rtcVideo?.startAudioCapture()
        
        let processorConfig = ByteRTCVideoPreprocessorConfig.init()
        processorConfig.requiredPixelFormat = .I420
        
        self.processor = FaceUnityProcessor.init()
        
        // 注册视频帧回调,用于相芯美颜处理,回调处理参看FaceUnityProcessor
        self.rtcVideo?.registerLocalVideoProcessor(self.processor, withConfig: processorConfig)
    }
    
    func bindLocalRenderView() {
        // 设置本地渲染视图
        let canvas = ByteRTCVideoCanvas.init()
        canvas.view = self.localView.videoView
        canvas.renderMode = .hidden
        self.localView.userId = userId
        
        self.rtcVideo?.setLocalVideoCanvas(.indexMain, withCanvas: canvas);
    }
    
    @objc func joinRoom()  {
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
    
    // MARK: ByteRTCVideoDelegate & ByteRTCRoomDelegate
    //进房状态
    func rtcRoom(_ rtcRoom: ByteRTCRoom, onRoomStateChanged roomId: String, withUid uid: String, state: Int, extraInfo: String) {
        ToastComponents.shared.show(withMessage: "onRoomStateChanged uid: \(uid) state:\(state)")
        
    }
    
    // MARK: Lazy laod
    lazy var containerView: UIView = {
        let view = UIView.init()
        view.backgroundColor = .groupTableViewBackground
        return view
    }()
    
    lazy var localView: UserVideoView = {
        let view = UserVideoView.init()
        return view
    }()
}
