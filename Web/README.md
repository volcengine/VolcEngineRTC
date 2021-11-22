### 获取 AppId 和临时 Token

可参考 RTC 接入指南获取 AppId 和临时 Token。临时 Token 的生成需要输入房间 ID 和用户 ID，这里输入的房间 ID 和用户 ID 需要在编译成功的 Demo 的登录页输入相同的，才可以正常进入房间。

### 配置 Demo 工程文件

1. 全局安装 node、yarn
2. 进入工程目录，修改 AppID。使用控制台获取的 AppID 覆盖 src 文件夹下 config.ts 里的 appId 值
3. 进入工程目录，修改 Token。临时 Token 覆盖 src 文件下 config.ts 里的 token 值

### 编译运行

1. 在命令行里输入 yarn
2. 运行项目 yarn start
