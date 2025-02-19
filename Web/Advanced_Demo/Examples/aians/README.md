RTC 提供 AI 降噪插件，你可以通过此插件满足不同场景的降噪需求。
降噪包含传统降噪和 AI 降噪：传统降噪主要用于抑制平稳噪声（如空调声、风扇声）；AI 降噪主要用于抑制非平稳噪声（如键盘声、碰撞声、敲击声），特别适用于对瞬时噪声敏感的场景，例如会议场景中的短时噪声。

# **前置条件**

1. RTC SDK 4.47+ 你需要集成 RTC SDK，并实现音视频通话功能。
2. AI 降噪插件支持如下 PC 端浏览器：
   1. Chrome 94+
   2. Edge 94+
3. 为了更好的使用体验，建议设备满足以下要求：
   1. 双核 Intel Core i5+
   2. RAM 8 GB+
   3. 64 位操作系统

# 操作步骤

1. 在你的项目中引入 AI 降噪插件。

```typescript
import RTCAIAnsExtension from '@volcengine/rtc/extension-ainr';
```

2. 注册 AI 降噪插件。

```typescript
import VERTC from '@volcengine/rtc';
// 创建引擎实例
const engine = VERTC.createEngine('appid');

// 创建 AI 降噪插件实例
const AIAnsExtension = new RTCAIAnsExtension();
// 注册 AI 降噪插件
try {
  await engine.registerExtension(AIAnsExtension);
} catch (error) {
  // 注册失败，详细信息：error.message
}
```

3. 开启内部音频采集。

```typescript
// 开启内部音频采集
engine.startAudioCapture();
```

4. 开启、关闭 AI 降噪。

```typescript
// 开启/关闭降噪
AIAnsExtension.enable();
AIAnsExtension.disable();
```

# API 参考

## IRTCAIAnsExtension

类型: `class`

- **API**

  | 名称                                                           | 描述           |
  | -------------------------------------------------------------- | -------------- |
  | [enable](https://www.volcengine.com/docs/6348/148647#enable)   | 开启 AI 降噪。 |
  | [disable](https://www.volcengine.com/docs/6348/148647#disable) | 关闭 AI 降噪。 |

### enable

类型: () =\> void

开启 AI 降噪。

- **注意**

  AI 降噪适用于内部采集音频。

### disable

类型: () =\> void

关闭 AI 降噪。

