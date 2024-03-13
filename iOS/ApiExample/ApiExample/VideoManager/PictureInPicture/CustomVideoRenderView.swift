//
//  CustomVideoRender.swift
//  ApiExample
//
//  Created by bytedance on 2023/11/7.
//  Copyright © 2021 bytedance. All rights reserved.
//

import UIKit
import VolcEngineRTC

class CustomVideoRenderView: UIView,ByteRTCVideoSinkDelegate {
    
    lazy var imageView: UIImageView = {
        let imageView = UIImageView.init()
        imageView.contentMode = .scaleAspectFill
        imageView.clipsToBounds = true
        return imageView
    }()
    
    override init(frame: CGRect) {
        super.init(frame: frame)
        self.addSubview(self.imageView)
        
        self.imageView.snp.makeConstraints { make in
            make.edges.equalTo(self)
        }
    }
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    private func render(imageBuffer: CVImageBuffer, forImageView imageView: UIImageView, rotation: ByteRTCVideoRotation) {
        let ciImage = CIImage(cvImageBuffer: imageBuffer)
        let context = CIContext()
        
        let imageRect = CGRect(x: 0, y: 0,
                               width: CVPixelBufferGetWidth(imageBuffer),
                               height: CVPixelBufferGetHeight(imageBuffer))
        guard let cgImage = context.createCGImage(ciImage, from: imageRect) else { return }
        
        var imageOrientation: UIImage.Orientation
        
        switch rotation {
        case .rotation0:
            imageOrientation = .up
        case .rotation90:
            imageOrientation = .right
        case .rotation180:
            imageOrientation = .down
        case .rotation270:
            imageOrientation = .left
        default:
            imageOrientation = .up
            break
        }
        
        let image = UIImage(cgImage: cgImage, scale: UIScreen.main.scale, orientation: imageOrientation)
        DispatchQueue.main.async {
            imageView.image = image
        }
    }
    
    // MARK: ByteRTCVideoSinkDelegate
    func onFrame(_ videoFrame: ByteRTCVideoFrame) {
        self.render(imageBuffer: videoFrame.textureBuf!, forImageView: self.imageView, rotation: videoFrame.rotation)
    }
    
    func getRenderElapse() -> Int32 {
        return 0
    }
    
    func renderPixelBuffer(_ pixelBuffer: CVPixelBuffer, rotation: ByteRTCVideoRotation, contentType: ByteRTCVideoContentType, extendedData: Data?) {
        
    }

}
