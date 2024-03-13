//
//  FaceUnityProcessor.swift
//  ApiExample
//
//  Created by bytedance on 2023/11/2.
//  Copyright © 2021 bytedance. All rights reserved.
//
import AVFoundation
import VolcEngineRTC

// 处理RTC的视频帧回调
class FaceUnityProcessor: NSObject, ByteRTCVideoProcessorDelegate {
    func processVideoFrame(_ srcFrame: ByteRTCVideoFrame) -> ByteRTCVideoFrame? {
        
        FUDemoManager.shared().checkAITrackedResult()
        if !FUDemoManager.shared().shouldRender {
            return srcFrame
        }
        
        FUDemoManager.updateBeautyBlurEffect()
        
        guard let srcPixelBuffer = srcFrame.textureBuf else { return nil }
        CVPixelBufferLockBaseAddress(srcPixelBuffer, CVPixelBufferLockFlags(rawValue: 0))
        
        let width = CVPixelBufferGetWidth(srcPixelBuffer)
        let height = CVPixelBufferGetHeight(srcPixelBuffer)
        
        guard let buffer0 = CVPixelBufferGetBaseAddressOfPlane(srcPixelBuffer, 0),
              let buffer1 = CVPixelBufferGetBaseAddressOfPlane(srcPixelBuffer, 1),
              let buffer2 = CVPixelBufferGetBaseAddressOfPlane(srcPixelBuffer, 2) else { return nil }
        
        let stride0 = CVPixelBufferGetBytesPerRowOfPlane(srcPixelBuffer, 0)
        let stride1 = CVPixelBufferGetBytesPerRowOfPlane(srcPixelBuffer, 1)
        let stride2 = CVPixelBufferGetBytesPerRowOfPlane(srcPixelBuffer, 2)
        
        let imageBuffer = FUImageBufferMakeI420(buffer0, buffer1, buffer2, width, height, stride0, stride1, stride2)
        
        let input = FURenderInput()
        input.imageBuffer = imageBuffer
        input.renderConfig.imageOrientation = FUImageOrientationRight
        input.renderConfig.gravityEnable = true
        input.renderConfig.isFromFrontCamera = FUDemoManager.shared().stickerH
        
        input.renderConfig.stickerFlipH = FUDemoManager.shared().stickerH
        FURenderKit.share().render(with: input)
        CVPixelBufferUnlockBaseAddress(srcPixelBuffer, CVPixelBufferLockFlags(rawValue: 0))
        
        return srcFrame
    }
}
