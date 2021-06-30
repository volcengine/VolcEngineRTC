## 目录结构说明

本目录包含 windows 版 VolcEngineRTC 的所有场景 Demo 源代码，在veRTC_Demo目录下包括多个场景：
- MeetingDemo： 会议场景案例

```
├─ ByteRTCStart                  // VolcEngineRTC场景化Demo，包括会议
│  │─ BDUIKit                   // 基础组件
│  │─ bus                       // 线程包装库
│  │─ ByteRTCSDK_x86            // x86 编译产物文档和 byte sdk 依赖目录
│  │  ├─ include               // byte sdk include 目录
│  │  ├─ RTCSDK.lib            // byte sdk lib 文件
│  │  ├─ RTCSDK.dll            // byte sdk dll 文件
│  │  ├─ *.dll                 // byte sdk dll 依赖 dll
│  │  ├─ resource              // 运行时资源文件
│  │  ├─ crash                 // 运行时 crash 产生目录
│  │─ jsoncpp                   // jsoncpp 库目录
│  │─ meeting-manager           // 会议协议处理文件
│  │─ res                       // 编译时资源文件
│  │─ socket.io-client-cpp      // socket.io 库
│  │─ utils                     // 工具包
│  │─ third_party               // 第三方开源库
│  │  ├─ openssl               // openssl include 目录
│  │  ├─ openssl_lib           // openssl lib 目录
│  
├─ ByteRTCStart.sln               // ByteRTCStart.sln 工程解决方案

```
- x86 架构时请将调试目录设置为 $(ProjectDir)\ByteRTCSDK_x86
- x64 架构时请将调试目录设置为 $(ProjectDir)\ByteRTCSDK_x64
