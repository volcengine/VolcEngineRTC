# API Example 抖音小程序

火山引擎 RTC 提供了开源示例项目 API Example Demo。获取该项目后，你可以参照本文进行跑通，体验实时音视频功能；也能通过阅读代码，了解最佳实践。你可以加入[官网交流群](https://applink.feishu.cn/client/chat/chatter/add_by_link?link_token=823r62a3-03f6-40dd-939a-99bde262a20a)了解详情。

## 前提条件

- 已开通 [抖音开放平台](https://developer.open-douyin.com/) 的开发者账号。
- 已加入 [官网交流群](https://applink.feishu.cn/client/chat/chatter/add_by_link?link_token=823r62a3-03f6-40dd-939a-99bde262a20a) 申请开通抖音小程序 RTC 组件能力。
- 已开通 RTC 服务，参考[开通服务](https://www.volcengine.com/docs/6348/69865)。你需要从控制台获取 [AppID](https://www.volcengine.com/docs/6348/69865#%E6%AD%A5%E9%AA%A44%EF%BC%9A%E5%88%9B%E5%BB%BA-rtc-%E5%BA%94%E7%94%A8%EF%BC%8C%E8%8E%B7%E5%8F%96-appid) 和[临时 Token](https://www.volcengine.com/docs/6348/70121#%E4%BD%BF%E7%94%A8%E4%B8%B4%E6%97%B6-token) 用于项目跑通。
- 已安装[抖音开发者工具 IDE](https://developer.open-douyin.com/docs/resource/zh-CN/mini-app/develop/developer-instrument/download/developer-instrument-update-and-download) V4.0.1+。

## 获取示例项目

你可以通过 [GitHub](https://github.com/volcengine/VolcEngineRTC) 获取示例项目，具体指令如下：

```bash
git clone https://github.com/volcengine/VolcEngineRTC.git
cd VolcEngineRTC
git checkout main
cd DouyinMicroApp
```

抖音小程序示例项目的目录结构如下：

```
.
├── app.json
├── app.ts
├── app.ttss
├── common
├── constant.ts         // RTC 相关配置
├── image
├── package.json
├── pages
│   ├── basic
│   │   └── quickstart  // 快速开始页面
│   └── index           // 首页
├── project.config.json
├── tsconfig.json
└── types
```

## 配置示例项目

使用 [抖音开发者工具 IDE](https://developer.open-douyin.com/docs/resource/zh-CN/mini-app/develop/developer-instrument/download/developer-instrument-update-and-download) 打开示例项目，在 `constant.ts` 的如下位置填入获取的 `AppId` 和 `Token`。

![](https://portal.volccdn.com/obj/volcfe/cloud-universal-doc/upload_22e08db995ade1baf744dc6efa870212.png)

## 编译并运行示例项目

该步骤可参考 [真机调试\_小程序\_抖音开放平台](https://developer.open-douyin.com/docs/resource/zh-CN/mini-app/develop/developer-instrument/debug/device-debug)
运行成功后效果如下：
![](https://portal.volccdn.com/obj/volcfe/cloud-universal-doc/upload_5e7b5444a6d445bdb917d65c28815a66.png)

官网交流群二维码：

<img src="https://portal.volccdn.com/obj/volcfe/cloud-universal-doc/upload_8f8bd59c78ed57aa18246208dcee08d7.png" width="50%"/>
