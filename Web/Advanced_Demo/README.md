### 获取 AppId 和临时 Token

可参考 [RTC 接入指南](https://www.volcengine.com/docs/6348/69865)获取 AppId 和临时 Token。临时 Token 的生成需要输入房间 ID 和用户 ID，这里输入的房间 ID 和用户 ID 需要在编译成功的 Demo 的登录页输入相同的，才可以正常进入房间。

### 配置 Demo 工程文件

1. 全局安装 node、yarn
2. 进入工程目录，修改 AppID 和 RoomID。使用控制台获取的 AppID 覆盖各进阶能力文件夹里的 index.js 里的 appId 和 roomId
3. 进入工程目录，修改 Token。临时 Token 覆盖各进阶能力文件夹里的 index.js 里的 token 值
4. 虚拟背景能力需付费使用，请联系技术支持团队获取符合业务功能需求的鉴权文件，也可在线体验[进阶能力-虚拟背景](https://demo.volcvideo.com/rtc/advance/virtualBackground)


## 运行 demo

1. 进入对应进阶能力文件夹下执行以下步骤

2. 安装 yarn

```
 npm install -g yarn
```

3. 安装依赖

```
yarn
```

4. 启动项目

```
yarn dev
```