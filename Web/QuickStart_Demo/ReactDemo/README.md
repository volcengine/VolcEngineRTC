### 获取 AppId 和临时 Token

可参考 [RTC 接入指南](https://www.volcengine.com/docs/6348/69865)获取 AppId 和临时 Token。临时 Token 的生成需要输入房间 ID 和用户 ID，这里输入的房间 ID 和用户 ID 需要在编译成功的 Demo 的登录页输入相同的，才可以正常进入房间。

### 配置 Demo 工程文件

1. 全局安装 node、yarn
2. 进入工程目录，修改 AppID 和 RoomID。使用控制台获取的 AppID 覆盖 src 文件夹下 config.ts 里的 appId 和 roomId
3. 进入工程目录，修改 Token。临时 Token 覆盖 src 文件下 config.ts 里的 token 值

```
const config = {
  appId: 'yourAppId',
  roomId: 'yourRoomId',
  tokens: [
    {
      userId: 'yourUserId1',
      token: 'yourToken1',
    },
    {
      userId: 'yourUserId2',
      token: 'yourToken2',
    }
  ],
};
```

### 编译运行

1. 在命令行里输入  ```yarn```
2. 运行项目 ```yarn start```

### 注意
如遇到设备权限获取失败问题，可参考 [Web 排查设备权限获取失败问题](https://www.volcengine.com/docs/6348/1356355)。