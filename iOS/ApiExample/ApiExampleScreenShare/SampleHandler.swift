import ReplayKit
import Foundation
import VolcEngineRTC

class SampleHandler: RPBroadcastSampleHandler, ByteRtcScreenCapturerExtDelegate {
    

    override func broadcastStarted(withSetupInfo setupInfo: [String : NSObject]?) {
        // User has requested to start the broadcast. Setup info from the UI extension can be supplied but optional.
        print("-------")
        ByteRtcScreenCapturerExt.shared.start(with: self, groupId: APP_GROUP);
        
    }
    
    override func broadcastPaused() {
        // User has requested to pause the broadcast. Samples will stop being delivered.
    }
    
    override func broadcastResumed() {
        // User has requested to resume the broadcast. Samples delivery will resume.
    }
    
    override func broadcastFinished() {
        ByteRtcScreenCapturerExt.shared.stop()
    }
    
    override func processSampleBuffer(_ sampleBuffer: CMSampleBuffer, with sampleBufferType: RPSampleBufferType) {
        switch sampleBufferType {
            
        case .video, .audioApp: // 采集到的屏幕视频流 和 屏幕音频流
            ByteRtcScreenCapturerExt.shared.processSampleBuffer(sampleBuffer, with: sampleBufferType)
            
            break
        case .audioMic:
            // Handle audio sample buffer for mic audio
            break
        @unknown default:
            // Handle other sample buffer types
            fatalError("Unknown type of sample buffer")
        }
    }
    
    // MARK: ByteRtcScreenCapturerExtDelegate
    func onQuitFromApp() {
        let userInfo = [
            NSLocalizedFailureReasonErrorKey: "您停止了屏幕共享"
        ]
        let error = NSError(domain: RPRecordingErrorDomain,
                            code: RPRecordingErrorCode.userDeclined.rawValue,
                            userInfo: userInfo)
        self.finishBroadcastWithError(error)

    }
    
    func onReceiveMessage(fromApp message: Data) {
        print("SampleHandler onReceiveMessageFromApp")
    }
    
    func onSocketDisconnect() {
        print("SampleHandler onSocketDisconnect")
    }
    
    func onSocketConnect() {
        print("SampleHandler onSocketConnect")
    }
    
    func onNotifyAppRunning() {
        print("SampleHandler onNotifyAppRunning")
    }
}
