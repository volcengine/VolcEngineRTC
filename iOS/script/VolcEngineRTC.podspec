Pod::Spec.new do |s|
    s.name             = 'VolcEngineRTC'
    s.version          = '3.60.102.3000'
    s.summary          = 'VolcEngineRTC is an realtime communication SDK of IOS.'
    s.homepage         = 'https://github.com/volcengine/VolcEngineRTC'
    s.license          = { :type => 'MIT'}
    s.author           = { 'bytertc' => 'bytertc@bytedance.com' }
    s.source           = { :http => 'https://ios.bytedance.net/wlapi/tosDownload/rtcsdk/3.60.102.3000/full/ios/VolcEngineRTC.zip' }
    s.ios.deployment_target = '11.0'
    s.default_subspec = ['Core', 'RealXBase', 'RTCFFmpeg', 'CVByteNN', 'BMF', 'ByteRTCVideoDenoiseExtension', 'ByteRTCVideoSharpenExtension', 'ByteRTCVideoSRExtension']
    s.subspec 'Core' do |rtc|
        rtc.vendored_frameworks = 'VolcEngineRTC.xcframework'
    end
    s.subspec 'ScreenCapture' do |rtc|
        rtc.vendored_frameworks = 'VolcEngineRTCScreenCapturer.xcframework'
    end
s.subspec 'RTCFFmpeg' do |rtc|
	rtc.vendored_frameworks = 'RTCFFmpeg.xcframework'
end
s.subspec 'ByteRTCFFmpegAudioExtension' do |rtc|
	rtc.vendored_frameworks = 'ByteRTCFFmpegAudioExtension.xcframework'
end
    s.subspec 'CVByteNN' do |rtc|
        rtc.vendored_frameworks = 'bytenn.xcframework'
    end
    s.subspec 'BMF' do |rtc|
        rtc.vendored_frameworks = 'bmf_mods_shared.xcframework'
    end
s.subspec 'RealX' do |rtc|
	rtc.vendored_frameworks = 'RealX.xcframework'
end
s.subspec 'RealXBase' do |rtc|
	rtc.vendored_frameworks = 'RealXBase.xcframework'
end
s.subspec 'bytevc1enc' do |rtc|
	rtc.vendored_frameworks = 'bytevc1enc.xcframework'
end
s.subspec 'ByteRTCNICOExtension' do |rtc|
	rtc.vendored_frameworks = 'ByteRTCNICOExtension.xcframework'
end
s.subspec 'ByteRTCFDK-AACExtension' do |rtc|
	rtc.vendored_frameworks = 'ByteRTCFDK-AACExtension.xcframework'
end
s.subspec 'ByteRTCVp8CodecExtension' do |rtc|
	rtc.vendored_frameworks = 'ByteRTCVp8CodecExtension.xcframework'
end
s.subspec 'h265enc' do |rtc|
	rtc.vendored_frameworks = 'h265enc.xcframework'
end
    s.subspec 'ByteRTCVideoDenoiseExtension' do |rtc|
        rtc.vendored_frameworks = 'ByteRTCVideoDenoiseExtension.xcframework'
    end
    s.subspec 'ByteRTCVideoSharpenExtension' do |rtc|
        rtc.vendored_frameworks = 'ByteRTCVideoSharpenExtension.xcframework'
    end
    s.subspec 'ByteRTCVideoSRExtension' do |rtc|
        rtc.vendored_frameworks = 'ByteRTCVideoSRExtension.xcframework'
    end
end
