
火山引擎 RTC 提供了开源示例项目 API Example Demo。获取该项目后，你可以参照本文进行跑通，体验实时音视频功能；也能通过阅读代码，了解最佳实践。

## 前提条件

在开始集成 RTC SDK 前，请确保满足以下要求：

- macOS 11.0 或以上版本设备，且可以正常访问互联网
- Qt 5.12 或以上版本，详细操作参看[如何在 macOS 上安装 Qt？](https://www.volcengine.com/docs/6348/1152682#%E5%A6%82%E4%BD%95%E5%9C%A8-macos-%E4%B8%8A%E5%AE%89%E8%A3%85-qt%EF%BC%9F)
- Xcode 14.0 或以上版本
- 麦克风、摄像头等音视频设备
- 在[火山引擎控制台](https://console.volcengine.com/auth/login/)上[开通实时音视频服务](https://www.volcengine.com/docs/6348/69865)，你需要从控制台获取 AppID 和 AppKey 用于项目跑通

## 获取示例项目

你可以通过 [GitHub](https://github.com/volcengine/VolcEngineRTC) 获取示例项目，具体指令如下：

```bash
git clone https://github.com/volcengine/VolcEngineRTC.git
cd VolcEngineRTC
git checkout ApiExample_Demo
cd Windows
```

示例项目的目录结构如下：

```
.
├── 3rd
│   ├── Windows
│   └── mac
├── API_Example.pro
├── CMakeLists.txt
├── README.md
├── Resources
├── bin
├── resources.qrc
└── src
    ├── Basic               // 快速开始 https://www.volcengine.com/docs/6348/1169314
    │   ├── QuickStartWidget.cpp
    │   ├── QuickStartWidget.h
    │   └── QuickStartWidget.ui
    ├── Advanced
    │   ├── AudioMixing    // 播放音乐文件 https://www.volcengine.com/docs/6348/70141、播放音效 https://www.volcengine.com/docs/6348/1178326
    │   ├── ByteBeauty     // 智能美化特效（付费版） https://www.volcengine.com/docs/6348/114717
    │   ├── CDNStream      // 推流到 CDN https://www.volcengine.com/docs/6348/69817
    │   ├── CrossRoomPK    // 跨房 PK https://www.volcengine.com/docs/6348/104398
    │   ├── FuBeauty       // 自定义视频处理（相芯美颜） https://www.volcengine.com/docs/6348/79888
    │   ├── MultiRoom      // 多房间 https://www.volcengine.com/docs/6348/196844
    │   ├── RawAudioData   // 原始音频数据 https://www.volcengine.com/docs/6348/1178324
    │   ├── SoundEffects   // 变声、混响、降噪 https://www.volcengine.com/docs/6348/1178327
    │   └── VideoConfig    // 视频参数配置 https://www.volcengine.com/docs/6348/70122、视频采集旋转方向 https://www.volcengine.com/docs/6348/106458
    ├── Info.plist
    ├── Public
    ├── app.ico
    ├── main.cpp
    ├── mainwindow.cpp
    ├── mainwindow.h
    ├── mainwindow.ui
    └── resources.rc
```

## 配置示例项目

1. 在[控制台](https://console.volcengine.com/rtc/listRTC)上获取 AppID 和 AppKey，并将其分别填入 `src/Public/Config.h` 中的 `g_appid` 和 `g_appkey`。请正确填写信息，否则编译无法成功。
2. （可选）示例项目中智能美化特效、相芯美颜、美声与特效功能需要单独填写鉴权信息。不填写鉴权信息不会影响 Demo 的编译运行，但你将无法体验相关功能。
  - [智能美化特效](https://www.volcengine.com/docs/6705/1160378)：在 `src/Public/Config.h` 填写 `g_byte_beauty_key` 和 `g_byte_secret`，请联系[智能美化特效商务团队](https://www.volcengine.com/docs/6705/101956)获取相关信息。
  - [相芯美颜](https://www.faceunity.com/developer/)：在 `src/Advanced/FuBeauty/authpack.h` 填写 `g_auth_package`，请发送邮件至 marketing@faceunity.com 进行咨询。
  - [美声与特效](https://www.volcengine.com/docs/6489/171423)：在 `src/Public/Config.h` 填写 `g_sami_key` 和 `g_sami_token`，请参考 [SDK 快速入门](https://www.volcengine.com/docs/6489/171423)文档**获取授权信息**章节。
  
## 编译并运行示例项目

1. 打开 Qt 安装路径下的 Qt Creator。使用 Qt Creator 打开 `API_Example.pro`，并选择已安装的构建套件。
	
	![](https://portal.volccdn.com/obj/volcfe/cloud-universal-doc/upload_de906345dc3f69a5efb4d7227ccfe102.png)
	
2. 单击 Qt Creator 窗口左下角的运行按钮（或使用 **Command ⌘** + **R** 快捷键），运行效果如下：
	
	![](https://portal.volccdn.com/obj/volcfe/cloud-universal-doc/upload_a1f2564c0a9cb1dda0b8b59d896c3dc5.png)

## 常见问题

- [如何在 macOS 上安装 Qt？](https://www.volcengine.com/docs/6348/1152682#%E5%A6%82%E4%BD%95%E5%9C%A8-macos-%E4%B8%8A%E5%AE%89%E8%A3%85-qt%EF%BC%9F)
	
- [如何设置日志文件？](https://www.volcengine.com/docs/6348/114721)

## 相关文档

- [API 文档](https://www.volcengine.com/docs/6348/70094)
- [发版说明](https://www.volcengine.com/docs/6348/110078)
- [高级功能](https://www.volcengine.com/docs/6348/69814)
- [最佳实践](https://www.volcengine.com/docs/6348/130768)
- [场景方案](https://www.volcengine.com/docs/6348/70008)
