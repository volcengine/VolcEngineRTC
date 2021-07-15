## 目录结构说明

本目录包含 Android 版 VolcEngineRTC 的所有场景 Demo 源代码，在veRTC_Demo目录下包括多个场景：
- MeetingRTCDemo： 会议场景案例
- Voicechat： 语音沙龙场景案例

```
├─ veRTC_Demo                   // VolcEngineRTC场景化Demo，包括会议
│  │─ voicechat                 // 场景一：语音沙龙
│  │─ meetingrtcdemo            // 场景一：多人会议，包含屏幕分享
│  │  ├─ feature                // 会议场景，业务功能，包含房间，设置，登录等功能。
│  │  ├─ common                 // 会议场景，业务组件。
│  │  ├─ entity                 // 会议场景，数据结构定义。
│  │  ├─ core                   // 会议场景，使用 RTC、Socket、EventBus 核心组件。
│  │  ├─ resource               // 会议场景，常量定义。
│  
├─ lib 
│  ├─ ByteAudio.aar            // Byte Audio SDK 
│  ├─ RtcEngine.aar            // Byte Rtc SDK

```
