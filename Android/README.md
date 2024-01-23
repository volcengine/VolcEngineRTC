火山引擎 RTC 提供了开源示例项目 API Example Demo。获取该项目后，你可以参照本文进行跑通，体验实时音视频功能；也能通过阅读代码，了解最佳实践。

## 前提条件

在开始集成 RTC SDK 前，请确保满足以下要求：

- Android Studio Arctic Fox | 2020.3.1 或以上版本（本文使用 Android Studio Giraffe | 2022.3.1 版本）
- Android 4.4 或以上版本的 Android 真机或模拟器
    > [!NOTE]
    > 推荐使用真机进行调试，连接指南参看[在硬件设备上运行应用](https://developer.android.com/studio/run/device?hl=zh-cn)。
- Android 设备和开发电脑可以正常访问互联网
- 在[火山引擎控制台](https://console.volcengine.com/auth/login/)上[开通实时音视频服务](https://www.volcengine.com/docs/6348/69865)，你需要从控制台获取 AppID 和 AppKey 用于项目跑通

## 获取示例项目

你可以通过 [GitHub](https://github.com/volcengine/VolcEngineRTC) 获取示例项目，具体指令如下：

```bash
git clone https://github.com/volcengine/VolcEngineRTC.git
cd VolcEngineRTC
git checkout ApiExample_Demo
```

`Android/APIExample/app/src/main/java/rtc/volcengine/apiexample` 目录结构如下：

```
.
├── BaseActivity.java
├── MainActivity.java
├── Utils
├── common
└── examples
    ├── QuickStartActivity.java              // 快速开始 https://www.volcengine.com/docs/6348/70134
    ├── AudioMixing
    │   ├── AudioEffectMixingActivity.java  // 播放音效 https://www.volcengine.com/docs/6348/1178326
    │   ├── AudioMediaMixingActivity.java   // 播放音乐文件 https://www.volcengine.com/docs/6348/70141
    │   └── AudioMixingActivity.java
    ├── CDNStreamActivity.java               // 推流到 CDN https://www.volcengine.com/docs/6348/69817
    ├── CrossRoomPKActivity.java             // 跨房 PK https://www.volcengine.com/docs/6348/104398
    ├── MultiRoomActivity.java               // 多房间 https://www.volcengine.com/docs/6348/196844
    ├── PictureInPicture                     // 画中画 https://www.volcengine.com/docs/6348/1178325
    ├── RawAudioDataActivity.java            // 原始音频数据 https://www.volcengine.com/docs/6348/1178324
    ├── ThirdBeauty
    │   ├── Fubeauty                        // 自定义视频处理（相芯美颜） https://www.volcengine.com/docs/6348/79888
    │   ├── ThirdBeautyActivity.java
    │   └── byteBeauty                      // 智能美化特效（付费版） https://www.volcengine.com/docs/6348/114717
    ├── VideoConfigActivity.java             // 视频参数配置 https://www.volcengine.com/docs/6348/70122
    └── VoiceEffectActivity.java             // 变声、混响、降噪 https://www.volcengine.com/docs/6348/1178327
```

## 配置示例项目

1. 在[控制台](https://console.volcengine.com/rtc/listRTC)上获取 AppID 和 AppKey，并将其分别填入 `Android/APIExample/app/src/main/java/rtc/volcengine/apiexample/common/Constants.java` 中的 `APP_ID` 和 `APP_KEY`。请正确填写信息，否则编译无法成功。
	
	![](https://portal.volccdn.com/obj/volcfe/cloud-universal-doc/upload_204f74dd1f10a3850e3707a4d6b42c1c.png)
	
2. （可选）示例项目中智能美化特效、相芯美颜功能需要单独填写鉴权信息。不填写鉴权信息不会影响 Demo 的编译运行，但你将无法体验相关功能。
	- [智能美化特效](https://www.volcengine.com/docs/6705/1160378)：
		1. 请联系[智能美化特效商务团队](https://www.volcengine.com/docs/6705/101956)获取特效证书和素材资源文件。
			
		2. 在 `Android/APIExample/app/src/main/assets` 下新建 `cvlib` 文件夹，并将获取到的证书和素材资源文件放入 `cvlib` 文件夹中。
			
		3. 在 `LicenseBag.bundle` 中获取证书文件的文件名，并将其填入 `Android/APIExample/app/src/main/java/rtc/volcengine/apiexample/common/Constants.java` 中的 `BYTE_EFFECT_LIC_NAME`。例如 `public static final String` *`BYTE_EFFECT_LIC_NAME`* `= "/rtc_xxx.vertcdemo.apiexample_4.5.2_805.licbag";`。
			
	- [相芯美颜](https://www.faceunity.com/developer/)：请联系相芯美颜商务团队 marketing@faceunity.com 获取证书，使用获取到的证书替换 `Android/APIExample/faceunity/src/main/java/com/faceunity/nama` 路径下的 `authpack.java` 文件。

## 编译并运行示例项目

1. 开启 Android 设备的开发者选项，打开 USB 调试，通过 USB 连接线将 Android 设备接入电脑，并在 Android 设备选项中勾选你的 Android 设备。详情参看[在硬件设备上运行应用](https://developer.android.com/studio/run/device?hl=zh-cn)。
	
2. 单击 Android Studio 窗口右上角的 **Sync Project with** **Gradle** **Files**（或使用 **Shift ⇧** + **Command ⌘** + **O** 快捷键）同步项目，拉取项目依赖。
	
3. 单击 Android Studio 窗口右上角的 **Run 'app'** （或使用 **Control ⌃** + **R** 快捷键）开始编译。
	
4. 编译成功后，你的 Android 设备上会出现 API Example 应用，在弹窗中选择开启摄像头和麦克风权限。应用界面如下：
	
	![](https://portal.volccdn.com/obj/volcfe/cloud-universal-doc/upload_7d56419c1081d47306335366aa34b978.png)

## 常见问题

- [如何进行混淆配置？](https://www.volcengine.com/docs/6348/1155036#如何进行混淆配置？)

- [应用的 `targetSDKVersion` >= 31 时如何配置蓝牙权限？](https://www.volcengine.com/docs/6348/1155036#%E5%BA%94%E7%94%A8%E7%9A%84-targetsdkversion-31-%E6%97%B6%E5%A6%82%E4%BD%95%E9%85%8D%E7%BD%AE%E8%93%9D%E7%89%99%E6%9D%83%E9%99%90%EF%BC%9F)

- [如何在华为手机使用硬件耳返功能？](https://www.volcengine.com/docs/6348/1155036#如何在华为手机使用硬件耳返功能？)

- [使用模拟器调试时出现花屏？](https://www.volcengine.com/docs/6348/1155036#使用模拟器调试时出现花屏)

- [OpenCL 库 Android 12 适配说明](1155036#opencl-%E5%BA%93-android-12-%E9%80%82%E9%85%8D%E8%AF%B4%E6%98%8E)
