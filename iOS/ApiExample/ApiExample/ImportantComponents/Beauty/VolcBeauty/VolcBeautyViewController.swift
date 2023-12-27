/*
* 功能名称： VolcEngineRTC 美颜功能
* 功能简单描述：对于一个音视频通话，你可以将其中的多路音视频流合为一路，并将合并得到的音视频流推送到指定的推流地址（通常是 CDN 地址）
* 参考文档：https://www.volcengine.com/docs/6348/114717
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
*     getVideoEffectInterface 获取视频特效接口
*     initCVResource 检查视频特效证书，设置算法模型路径，并初始化特效模块
*     setColorFilter 设置颜色滤镜
*     setColorFilterIntensity 设置已启用颜色滤镜的强度
*     setEffectNodes 设置视频特效素材包
*     updateNode 设置特效强度
*     enableVirtualBackground
*     disableVirtualBackground
*
*
*     onRoomStateChanged 房间状态回调
*     onLeaveRoom 离房回调
*     onUserJoined 用户加入回调
*     onUserLeave  用户离开回调
*     onUserPublishStream 用户发流回调
*     onUserUnpublishStream 用户停止发流回调
*
* 火山美颜集成参考：https://www.volcengine.com/docs/6348/114717
* 本功能需付费使用，请联系美颜技术支持团队获取 v4.4.2+ 的 Standard/Lite 版本特效 SDK 及符合业务功能需求的 License 和素材资源包。
* 申请付费使用后：
* 1. 修改demo Config.h 中的 CVLicenseName为license的文件名
* 2. 将模型等资源放在 ApiExample/ApiExample/ImportantComponents/Beauty/VolcBeauty/resource 目录中
*
* Demo实现时的逻辑
*    本Demo演示功能：字节美颜
*    为了展示简单，所有功能的token都由客户端TokenGenerator类生成，请在真正接入时视具体情况而定
*/


import UIKit
import SnapKit
import VolcEngineRTC

class VolcBeautyViewController: BaseViewController, ByteRTCVideoDelegate, ByteRTCRoomDelegate,BeautyBarViewDelegate {
    
    var rtcVideo: ByteRTCVideo?
    var rtcRoom: ByteRTCRoom?
    let roomId = "202311"
    let userId = "888888"
    
    private var makeupNodes: [String] = []
    private var rtcVideoEffect: ByteRTCVideoEffect?
    
    deinit {
        self.rtcRoom?.leaveRoom()
        self.rtcRoom?.destroy()
        self.rtcRoom = nil
        
        ByteRTCVideo.destroyRTCVideo()
        self.rtcVideo = nil
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        self.createUI()
        self.buildRTCEngine()
        self.buildVideoEffect()
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
        
        // 美颜操作栏
        view.addSubview(beautyView)
        beautyView.snp.makeConstraints { make in
            make.bottom.equalTo(self.view)
            make.left.right.equalToSuperview()
            make.height.equalTo(240)
        }
    }
    
    func buildRTCEngine() {
        // 创建引擎
        self.rtcVideo = ByteRTCVideo.createRTCVideo(kAppID, delegate: self, parameters: [:])
        
        // 开启本地音视频采集
        self.rtcVideo?.startVideoCapture()
        self.rtcVideo?.startAudioCapture()
        
        // 设置视频朝向
        self.rtcVideo?.setVideoOrientation(.portrait)
    }
    
    func buildVideoEffect() {
        // 初始化
        self.rtcVideoEffect = self.rtcVideo?.getVideoEffectInterface()
        
        // license 验证
        let licensePath = EffectResource.licensePath()
        let modelPath = EffectResource.modelPath()
        let errorCode = self.rtcVideoEffect?.initCVResource(licensePath, withAlgoModelDir: modelPath)
        
        if errorCode == 0 {
            print("VolcBeauty initCVResource success")
        } else {
            print("VolcBeauty initCVResource failed \(errorCode ?? -1)")
        }
        
        // 创建视频特效引擎
        let isEnable = self.rtcVideoEffect?.enable()
        if isEnable == 0 {
            print("VolcBeauty enable video effect success")
        } else {
            print("VolcBeauty enable video effect failed \(isEnable ?? -1)")
        }
        
        // 设置视频特效素材包
        let beautyPath = EffectResource.beautyCameraPath()
        let reshapePath = EffectResource.reshapeCameraPath()
        self.makeupNodes = [beautyPath, reshapePath]
        let isEffectNodes = self.rtcVideoEffect?.setEffectNodes(self.makeupNodes) ?? -1
        if isEffectNodes == 0 {
            print("VolcBeauty enable effect nodes success")
        } else {
            print("VolcBeauty enable effect nodes failed \(isEnable ?? -1)")
        }
        
        // 默认滤镜
        self.rtcVideoEffect?.setColorFilter(EffectResource.filterPath(withName: "Filter_06_03"))
        self.rtcVideoEffect?.setColorFilterIntensity(0.0)
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
    
    //MARK: 处理美颜点击事件
    func beautyBarView(barView: BeautyBarView, didClickedEffect model: EffectModel) {
        switch model.type {
        case .sticker: // 贴纸
            let stickerPath = EffectResource.stickerPath(withName: model.key!)
            
            if model.selected {
                let allNodes = self.makeupNodes + [stickerPath]
                self.rtcVideoEffect?.setEffectNodes(allNodes)
            } else {
                self.rtcVideoEffect?.setEffectNodes(self.makeupNodes)
            }
            break
        case .filter: // 滤镜
            let filterPath = EffectResource.filterPath(withName: model.key!)
            self.rtcVideoEffect?.setColorFilter(filterPath)
            self.rtcVideoEffect?.setColorFilterIntensity(model.value)
            break
        case .virtual: // 虚拟背景
            let source = ByteRTCVirtualBackgroundSource()
            
            if model.selected {
                if model.subType == .image {
                    // 图片
                    let path = Bundle.main.path(forResource: "background", ofType: "jpg") ?? ""
                    source.sourceType = .image
                    source.sourcePath = path
                } else {
                    // 纯色
                    source.sourceType = .color
                    source.sourceColor = Int32(bitPattern: UInt32(0xff1678ff))
                }
                
                // 背景分割
                let portraitPath = EffectResource.getByteEffectPortraitPath()
                let result = self.rtcVideoEffect?.enableVirtualBackground(portraitPath, with: source) ?? -1
                if result != 0 {
                    ToastComponents.shared.show(withMessage: "开启背景分割失败")
                }
            } else {
                // 关闭背景分割效果
                self.rtcVideoEffect?.disableVirtualBackground()
            }
            break
        default:
            break
        }
    }
    
    // 修改效果强度值
    func beautyBarView(barView: BeautyBarView, didChangeEffectValue model: EffectModel) {
        switch model.type {
        case .beauty:
            if model.subType == .reshape {
                // 美形
                let path = EffectResource.reshapeCameraPath()
                self.rtcVideoEffect?.updateNode(path, key: model.key!, value: model.value)
            } else {
                // 美颜
                let path = EffectResource.beautyCameraPath()
                self.rtcVideoEffect?.updateNode(path, key: model.key!, value: model.value)            }
            
        case .filter:
            // 滤镜
            self.rtcVideoEffect?.setColorFilterIntensity(model.value)
            
        default:
            
            break
        }
    }
    
    // MARK: ByteRTCVideoDelegate & ByteRTCRoomDelegate
    //进房状态
    func rtcRoom(_ rtcRoom: ByteRTCRoom, onRoomStateChanged roomId: String, withUid uid: String, state: Int, extraInfo: String) {
        ToastComponents.shared.show(withMessage: "onRoomStateChanged uid: \(uid) state:\(state)")
        
    }
    
    // MARK: Lazy laod
    lazy var beautyView: BeautyBarView = {
        let view = BeautyBarView.init(frame: CGRectZero)
        view.delegate = self
        return view
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
}
