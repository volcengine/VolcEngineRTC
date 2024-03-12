# API Example iOS

火山引擎 RTC 提供了开源示例项目 API Example Demo。获取该项目后，你可以参照本文进行跑通，体验实时音视频功能；也能通过阅读代码，了解最佳实践。

## 前提条件

- macOS 开发电脑，且可以正常访问互联网
- Xcode 14.1 或以上版本
- Apple 开发者账号
- iOS 11.0 或以上版本真机设备，且可以正常访问互联网
- 在[火山引擎控制台](https://console.volcengine.com/auth/login/)上[开通实时音视频服务](https://www.volcengine.com/docs/6348/69865)，你需要从控制台获取 AppID 和 AppKey 用于项目跑通

## 获取示例项目

你可以通过 [GitHub](https://github.com/volcengine/VolcEngineRTC) 获取示例项目，具体指令如下：

```bash
git clone https://github.com/volcengine/VolcEngineRTC.git
cd VolcEngineRTC
git checkout ApiExample_Demo
```

iOS 示例项目的目录结构如下：

```
.
├── ApiExample
│   ├── ApiExample
│   │   ├── ApiExample-Bridging-Header.h
│   │   ├── AppDelegate.swift
│   │   ├── Assets.xcassets
│   │   ├── QuickStart                 // 快速开始 https://www.volcengine.com/docs/6348/1181844
│   │   ├── AudioManager
│   │   │   ├── AudioEffectMixing      // 播放音效 https://www.volcengine.com/docs/6348/1178326
│   │   │   ├── AudioMediaMixing       // 播放音乐文件 https://www.volcengine.com/docs/6348/70141
│   │   │   ├── AudioRawData           // 原始音频数据 https://www.volcengine.com/docs/6348/1178324
│   │   │   └── SoundEffects           // 变声、混响、降噪 https://www.volcengine.com/docs/6348/1178327
│   │   ├── AudioVideoTransmission
│   │   │   └── CrossRoomPK            // 跨房 PK https://www.volcengine.com/docs/6348/104398
│   │   ├── ImportantComponents
│   │   │   └── Beauty
│   │   │   │   ├── BeautyViewController.swift
│   │   │   │   ├── FaceUnityBeauty    // 自定义视频处理（相芯美颜） https://www.volcengine.com/docs/6348/79888
│   │   │   │   └── VolcBeauty         // 智能美化特效（付费版） https://www.volcengine.com/docs/6348/114717
│   │   │   └── PullRTMP 			   // 本地拉流RTMP https://www.volcengine.com/docs/6469/97858
│   │   ├── LiveManager
│   │   │   └── PushCDN                // 推流到 CDN https://www.volcengine.com/docs/6348/69817
│   │   ├── RoomManager
│   │   │   └── MutiRoom               // 多房间 https://www.volcengine.com/docs/6348/196844
│   │   ├── SEI						   // SEI  https://www.volcengine.com/docs/6348/70140
│   │   ├── VideoManager
│   │   │   ├── CommonConfig           // 视频参数配置 https://www.volcengine.com/docs/6348/70122
│   │   │   ├── PictureInPicture       // 画中画 https://www.volcengine.com/docs/6348/1178325
│   │   │   └── VideoRotation          // 视频采集旋转方向 https://www.volcengine.com/docs/6348/106458
│   │   ├── Base.lproj
│   │   ├── Common
│   │   ├── Config.swift
│   │   ├── Info.plist
│   │   ├── TokenGenerator
│   │   └── ViewController.swift
│   ├── ApiExample.xcodeproj
│   ├── Podfile
│   └── bdaudioeffect.framework
└── README.md
```

## 配置示例项目

1. 在 `iOS/ApiExample` 目录下，执行命令 `pod install` 安装工程依赖。
	```bash
	cd iOS/ApiExample
	pod install --repo-update
	```

2. 使用 XCode 打开 `ApiExample.xcworkspace`，在[控制台](https://console.volcengine.com/rtc/listRTC)上获取 AppID 和 AppKey，并将其分别填入 `ApiExample/Config.swift` 中的 `kAppID` 和 `kAppKey`。请正确填写信息，否则编译无法成功。
	![](https://portal.volccdn.com/obj/volcfe/cloud-universal-doc/upload_49fda580e4ae64d34c1f1306e2e6defe.png)

3. 配置开发者证书：
    1. 选中 Xcode 左侧导航栏中的 `ApiExample` 项目，进入 **Signing & Capabilities** 标签页，勾选 **Automatically manage signing** 自动生成证书。你也可以通过[苹果官网]([https://developer.apple.com/](https://developer.apple.com/))手动配置，下载证书。
    2. **Team** 选择 `Personal Team`。
    3. **Bundle Identifier** 默认的 `rtc.vertcdemo.apiexample.dev` 已被注册，将其修改为其他有效的 Bundle ID。
	![](https://portal.volccdn.com/obj/volcfe/cloud-universal-doc/upload_18711cf35916194388ebdce2790ec8de.png)
	
4. （可选）示例项目中智能美化特效、相芯美颜功能需要单独填写鉴权信息。不填写鉴权信息不会影响 Demo 的编译运行，但你将无法体验相关功能。
	- [智能美化特效](https://www.volcengine.com/docs/6705/1160378)：
		1. 请联系[智能美化特效商务团队](https://www.volcengine.com/docs/6705/101956)获取特效证书和素材资源文件。
		2. 将获取到的证书和素材资源文件放入 `ApiExample/ImportantComponents/Beauty/VolcBeauty/resource` 文件夹中，勾选 `Copy items if needed`。
			![](https://portal.volccdn.com/obj/volcfe/cloud-universal-doc/upload_64d691a20a1deeabeddaa486f1beb1d6.png)
		3. 在 `LicenseBag.bundle` 中获取证书文件的文件名，并将其填入 `ApiExample/Config.swift` 中的 `CVLicenseName`。例如 `let CVLicenseName = "rtc_test_vertc.veRTCDemo.ios_4.4.2_633.licbag"`。请注意，证书对应的包名需与你在步骤 3 中设置的 Bundle Identifier 一致。
		4. 下载 [RTC SDK iOS 离线包](https://www.volcengine.com/docs/6348/75707#%E4%B8%8B%E8%BD%BD-sdk)，解压后获取 `effect-sdk.framework` 文件，将其放入 `ApiExample/ImportantComponents/Beauty/VolcBeauty` 文件夹中，勾选 `Copy items if needed`。选中项目，进入 **General** 设置页面，在 **Frameworks, Libraries, and Embedded Content** 中将 `effect-sdk.framework` 的属性设置为 **Embed & Sign**。
			![](https://portal.volccdn.com/obj/volcfe/cloud-universal-doc/upload_d9f63b61be74c3bce0bd596a736157a7.png)
			
	- [相芯美颜](https://www.faceunity.com/developer/)：请联系相芯美颜商务团队 marketing@faceunity.com 获取证书，使用获取到的证书替换 `ApiExample/ImportantComponents/Beauty/FaceUnityBeauty` 路径下的 `authpack.h` 文件。

## 编译并运行示例项目

> [!NOTE]
> 如果你尚未信任开发者，请根据 Xcode 提示，在 iOS 设备上打开**设置**，选择**通用** > **VPN 与设备管理**，在**开发者 APP** 中单击信任开发者。

1. 在 Xcode 中连接并选择你的 iOS 真机设备，单击 XCode 窗口左上角的运行按钮（或使用 **Command ⌘** + **R** 快捷键）。
2. 在 iOS 设备上打开 Demo 应用时，在弹窗中选择开启摄像头和麦克风权限。应用界面如下：
    ![](https://portal.volccdn.com/obj/volcfe/cloud-universal-doc/upload_71e860a6953009adc11112a8dd5bc873.png)

## 常见问题

- 使用模拟器编译报错 `No such module 'VolcEngineRTC'`？

	**解决方案**：如果你使用的是搭载 Apple 芯片的 Mac 电脑，该问题可能是编译的架构（ARM64）和模拟器的架构（x86_64）不匹配导致的，请使用真机编译。
- Xcode 15 编译报错 `Sandbox: rsync.samba(xxxxx) deny(1)`？

  **解决方案**：选中项目，进入 **TARGETS** > **项目名称** > **Build Settings**，在 **Build Options** 中将 **User Script Sandboxing** 修改为 **No**。
	![](https://portal.volccdn.com/obj/volcfe/cloud-universal-doc/upload_0a34216d68b3a916cb081ed62acdf2ea.png)

## 相关文档

- [API 文档](https://www.volcengine.com/docs/6348/70084)
- [发版说明](https://www.volcengine.com/docs/6348/110078)
- [高级功能](https://www.volcengine.com/docs/6348/69814)
- [最佳实践](https://www.volcengine.com/docs/6348/130768)
- [场景方案](https://www.volcengine.com/docs/6348/70008)