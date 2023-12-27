火山引擎 RTC 提供了开源示例项目 APIExample-Demo。获取该项目后，你可以参照本文进行跑通，体验实时音视频功能；也能通过阅读代码，了解最佳实践。
此示例源码为一个桌面端跨平台的 Qt C++ 应用程序，同时支持 Windows/macOS 平台。

# 前提条件
在开始集成 RTC SDK 前，请确保满足以下要求：
- Windows：Windows 7 或以上版本，安装了 Visual Studio 2017 或以上版本。
- macOS：macOS 11.0 或以上版本，安装了 Xcode 14.0 或以上版本。
- 麦克风、摄像头等支持音视频功能的外部设备正常。
- 能正常访问互联网的设备
- 安装了 Qt（5.12及以上 版本）：[下载 Qt](https://download.qt.io/archive/qt/)，首次使用 Qt 的开发者可阅读其 官方教程 学习使用。
- 已在 火山引擎 [控制台](https://console.volcengine.com/home) 创建项目，并申请有效的 AppID 和 AppKey，详情请参考 [控制台 - 应用管理](https://console.volcengine.com/rtc/listRTC) 中的“应用信息”。

# 获取示例项目
- 下载源码离线包
- 或 通过GitHub获取
	- `git clone https://github.com/volcengine/VolcEngineRTC.git`
	- `cd VolcEngineRTC`
	- `git checkout ApiDemo/3.54`
	- `cd Windows`
	
# 配置示例项目

在 src/Public/Config.h 的如下位置填入在 [控制台](https://console.volcengine.com/rtc/listRTC) 上获取到的 **AppID 和 AppKey**。请正确填写信息，否则编译无法成功。
![图片](https://internal-api-drive-stream.larkoffice.com/space/api/box/stream/download/v2/cover/BYP0bUOkCo1P97xsGQucAowunYb/?fallback_source=1&height=1280&mount_node_token=EgQOdTiyioQFFqxZRHvcAmm4nCf&mount_point=docx_image&policy=equal&width=1280)

# 注意：
>Config.h中 还有字节美颜 key、secret 及 火山音频 key、token，如不填写，将不会影响demo的编译运行，但无法体验对应字节美颜和美声音效功能，使用时请联系技术人员。
>
>**字节美颜**：
>
>	- 参考链接：https://www.volcengine.com/docs/6705/101956
>
>	- 申请好后在Config.h中修改 g_byte_beauty_key 和 g_byte_secret的值，编译运行后可以体验字节美颜功能
>
>**相芯美颜**：
>
>
>    - 申请好后在authpack.h中修改 g_auth_package 的值，编译运行后可以体验相芯美颜功能
>
>**美声音效**：
>
>	- 参考链接：https://www.volcengine.com/docs/6489/171423
>	- APIExample-Demo中已经集成了音效SDK，如需要单独集成可以参考：[美声音效集成](https://www.volcengine.com/docs/6489/72021)
>
>   - 申请好证书后在Config.h中修改 g_sami_key 和 g_sami_token 的值，编译运行后可以体验美声音效功能。

# 编译步骤
## Mac: 
下载并安装 Qt Creator，然后用 Qt Creator 打开 API_Example.pro ，填写好 AppID和 AppKey 即可进行编译调试；
## Windows: 
### 方式1：QT-Creator编译
下载并安装 Qt Creator，然后用 Qt Creator 打开 API_Example.pro ，填写好 AppID和 AppKey 即可进行编译调试；
### 方式2：VS+QT插件编译
您需要安装 Visual Studio（2017或以上版本）来运行调试，同时配置 VS 下的 Qt 编译环境，步骤如下：
1. 打开VS并在工具栏找到 QT VS Tools -> Qt Options -> Qt Versions，add 添加我们自己的Qt编译器
2. 重启 msvc
3. 打开 msvc 工具栏——扩展——Qt VS Tool——Open Qt  Project File(.pro)，打开 API_Example.pro
4. 填写好 AppID和 AppKey，编译项目，调试运行即可
### 方式3：命令行编译
1. 从开始菜单中打开VS命令行工具：x86 Native Tools Command Prompt for  VS 2019
2. 切换到代码仓库目录，如 cd ApiExample-Demo\Windows
3. 修改 src/Public/Config.h中 AppID和 AppKey等信息
4. 在“x86 Native Tools Command Prompt for  VS 2019” 中执行：（其中qmake和jom的位置请根据你的安装位置进行调整）
  1. C:\Qt5.15\5.15.2\msvc2019\bin\qmake.exe API_Example.pro
  2. C:\Qt5.15\Tools\QtCreator\bin\jom\jom.exe
5. 等待 jom 执行完成，即可在 bin/Windows/Win32/release下看到生成的二进制 API_Example.exe，双击运行即可

	

# 目录说明
API-Demo包含以下功能：
- 基础功能
    - [快速开始](https://github.com/volcengine/VolcEngineRTC/tree/ApiExample_Demo/Windows/src/Basic)
- 高阶功能
    - [多房间](https://github.com/volcengine/VolcEngineRTC/blob/ApiExample_Demo/Windows/src/Advanced/MultiRoom/MultiRoom.cpp)  
    - [跨房PK](https://github.com/volcengine/VolcEngineRTC/blob/ApiExample_Demo/Windows/src/Advanced/CrossRoomPK/CrossRoomPK.cpp)
    - [原始音频数据](https://github.com/volcengine/VolcEngineRTC/blob/ApiExample_Demo/Windows/src/Advanced/AudioMixing/RawAudioData.cpp)
    - [音效混音](https://github.com/volcengine/VolcEngineRTC/blob/ApiExample_Demo/Windows/src/Advanced/AudioMixing/AudioMixingEffect.cpp)
    - [音乐混音](https://github.com/volcengine/VolcEngineRTC/blob/ApiExample_Demo/Windows/src/Advanced/AudioMixing/AudioMixingMedia.cpp)
    - [美声与音效](https://github.com/volcengine/VolcEngineRTC/blob/ApiExample_Demo/Windows/src/Advanced/SoundEffects/SoundEffectsWidget.cpp)
    - [常用视频配置](https://github.com/volcengine/VolcEngineRTC/blob/ApiExample_Demo/Windows/src/Advanced/VideoConfig/VideoConfigWidget.cpp)
    - [合流转推CDN](https://github.com/volcengine/VolcEngineRTC/blob/ApiExample_Demo/Windows/src/Advanced/CDNStream/CDNStreamByServer.cpp)
    - [字节美颜](https://github.com/volcengine/VolcEngineRTC/blob/ApiExample_Demo/Windows/src/Advanced/ByteBeauty/ByteBeautyWidget.cpp)
    - [相芯美颜](https://github.com/volcengine/VolcEngineRTC/blob/ApiExample_Demo/Windows/src/Advanced/FuBeauty/FaceUnityWidget.cpp)





# 相关文档
- [API 文档](https://www.volcengine.com/docs/6348/70010)
- [升级指南](https://www.volcengine.com/docs/6348/70007)
- [最佳实践](https://www.volcengine.com/docs/6348/130768)
- [场景方案](https://www.volcengine.com/docs/6348/70008)
- [高级功能](https://www.volcengine.com/docs/6348/69814)
- [服务端openAPI](https://www.volcengine.com/docs/6348/69815)




