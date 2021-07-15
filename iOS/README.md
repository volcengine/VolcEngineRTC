## 目录结构说明

本目录包含 iOS 版 VolcEngineRTC 的所有场景 Demo 源代码，在veRTC_Demo目录下包括多个场景：
- MeetingDemo： 会议场景案例
- VoiceDemo： 语音沙龙场景案例

```
├─ veRTC_Demo                   // VolcEngineRTC场景化Demo，包括会议
│  │─ Podfile                   // Pod描述文件
│  │─ Vender                    // 基础组件
│  │─ VoiceDemo                 // 场景一：语音沙龙
│  │─ MeetingDemo               // 场景二：多人会议，包含屏幕分享
│  │  ├─ Feature                // 会议场景，业务功能，包含房间，设置，登录等功能。
│  │  ├─ Common                 // 会议场景，业务组件，包含屏幕共享组件，Alert,Toast等组件。
│  │  ├─ Core                   // 会议场景，使用RTC，Socket 核心组件。
│  │  ├─ Resource               // 会议场景，图片资源。
│  
├─ Frameworks 
│  ├─ byteaudio.xcframework         // Byte Audio SDK 
│  ├─ ByteRtcEngineKit.xcframework  // Byte Rtc SDK

```
