import AVFoundation

// 定义我们的代理协议
protocol CameraDelegate: AnyObject {
    func camera(_ camera: CustomVideoCapture, didOutput sampleBuffer: CMSampleBuffer)
}

class CustomVideoCapture: NSObject, AVCaptureVideoDataOutputSampleBufferDelegate {

    weak var delegate: CameraDelegate?
    var session: AVCaptureSession
    
    override init() {
        self.session = AVCaptureSession()
        
        super.init()
        
        // 设置默认摄像头为前置摄像头
        let frontCamera = AVCaptureDevice.default(.builtInWideAngleCamera, for: .video, position: .front)

        if let camera = frontCamera {
            do {
                let videoInput = try AVCaptureDeviceInput(device: camera)
                
                if self.session.canAddInput(videoInput) {
                    self.session.addInput(videoInput)
                }
                
            } catch {
                print("Error creating capture device input: \(error.localizedDescription)")
            }
        } else {
            print("Unable to access front camera.")
        }
        
        // 设置分辨率
        if self.session.canSetSessionPreset(.vga640x480) {
            self.session.sessionPreset = .vga640x480
        }
        
        let videoOutput = AVCaptureVideoDataOutput()
        // 设置输出的视频帧格式为 32BGRA
        videoOutput.videoSettings = [kCVPixelBufferPixelFormatTypeKey as String: kCVPixelFormatType_32BGRA]
        
        videoOutput.setSampleBufferDelegate(self, queue: DispatchQueue.global())
        
        if self.session.canAddOutput(videoOutput) {
            self.session.addOutput(videoOutput)
        }
    }
    
    func updateFormat(to type: OSType) {
        guard let videoOutput = session.outputs.first(where: { $0 is AVCaptureVideoDataOutput }) as? AVCaptureVideoDataOutput else {
            print("No video data output found in the session.")
            return
        }
        
        if type == kCVPixelFormatType_32BGRA || type == kCVPixelFormatType_420YpCbCr8BiPlanarVideoRange {
            videoOutput.videoSettings = [kCVPixelBufferPixelFormatTypeKey as String: Int(type)]
        } else {
            print("Unsupported pixel format type.")
        }
    }
    
    func start() {
        if !self.session.isRunning {
            self.session.startRunning()
        }
    }
    
    func stop() {
        if self.session.isRunning {
            self.session.stopRunning()
        }
    }
    
    func captureOutput(_ output: AVCaptureOutput, didOutput sampleBuffer: CMSampleBuffer, from connection: AVCaptureConnection) {
        delegate?.camera(self, didOutput: sampleBuffer)
    }
    
}
