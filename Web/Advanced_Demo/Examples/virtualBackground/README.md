Web RTC SDK 提供虚拟背景插件，在互动直播、视频会议、在线授课等场景下，可将用户人像和背景分离，采用模糊背景或自定义图片作为虚拟背景，从而避免杂乱背景对观众的影响，保护用户隐私，呈现较高的视频效果。你可以参考本文，实现这一功能。

# 功能变更日志

1. 自 Web SDK v4.52 起，本功能可用。

2. 自 v4.53 版本起，支持在初始化时选择使用 GPU 模式。

# 前置条件

1. 本功能需付费使用，请联系技术支持团队获取符合业务功能需求的鉴权文件。
	
2. RTC SDK v4.52+ 你需要集成 RTC SDK，并实现音视频通话功能。
	
3. 虚拟背景功能兼容性与 [Web SDK 浏览器兼容性](https://www.volcengine.com/docs/6348/111854)一致，不建议在移动端使用本功能。
	
4. 为了更好的使用体验，建议设备满足以下要求：
	1. 双核 Intel Core i5+
		
	2. RAM 8 GB+
		
	3. 64 位操作系统
		
5. 如果你使用了云代理功能，你需要在防火墙白名单中添加虚拟背景域名，参看[在防火墙限制下进行通话](https://www.volcengine.com/docs/6348/146420)。
	

# 操作步骤

1. 在你的项目中引入虚拟背景插件，可直接引入或通过 UMD 方式引入。
	1. 直接引入
		
	
	```typescript
	import RTCBeautyExtension from '@volcengine/rtc/extension-beauty';
	```
	
	2. 通过 UMD 方式引入
		
	
	```typescript
	const {BackgroundMode, RTCBeautyExtension} = window.VERTCExtensions;
	```
	
2. 注册虚拟背景插件。
	
:::warning
注册插件后，无法动态修改视频流帧率。你可以在注册插件前调用 [setVideoEncoderConfig](https://www.volcengine.com/docs/6348/104478#setvideoencoderconfig) 修改帧率。
:::

```typescript
import VERTC from '@volcengine/rtc';
import RTCBeautyExtension, { BackgroundAIBackend } from '@volcengine/rtc/extension-beauty';

// 创建引擎实例
const engine = VERTC.createEngine('appid');

// 创建虚拟背景插件实例，需传入鉴权文件
const extension = new RTCBeautyExtension({ 
  authFileUrl: 'https://xxxx.auth',
  // 自 v4.53 版本起，可设置使用 GPU 模式
  aiBackend: BackgroundAIBackend.GPU
});
// 注册插件
try {
  await engine.registerExtension(extension);
} catch (error) {
  // 注册失败，详细信息：error.message
}
```

3. 开始视频采集，并设置渲染视图及模式。 示例代码以内部采集为例，如需使用外部采集，参看 [setVideoSourceType](www.volcengine.com/docs/6348/104478#setvideosourcetype)。

:::warning
虚拟背景仅对主流、本地流生效，不支持屏幕流、远端流。即 `StreamIndex` 必须为 `STREAM_INDEX_MAIN`。
:::

```typescript
// 开启内部视频采集
engine.startVideoCapture();
// 设置本地视频渲染时使用的视图，并设置渲染模式。
engine.setLocalVideoPlayer(StreamIndex.STREAM_INDEX_MAIN, {
  renderDom: 'yourDomId'
});
```

4. 设置虚拟背景参数。

```typescript
import { BackgroundMode } from '@volcengine/rtc/extension-beauty';

// ① 设置虚拟背景模式为背景模糊（默认）
extension.setBackgroundMode(BackgroundMode.BACKGROUND_BLUR);
// ② 或设置背景模式为背景图片
extension.setBackgroundMode(BackgroundMode.BACKGROUND_IMAGE);
extension.loadBackgroundImage('https://image_url');
```

5. 开启虚拟背景。

```typescript
extension.enableVirtualBackground();
```

6. 关闭虚拟背景。
	

```typescript
extension.disableVirtualBackground();
```

# API 参考

## IRTCBeautyExtension

类型: `interface`

- **API**

| 方法 | 描述 |
| :-- | :-- |
| [checkCompatibility](#irtcbeautyextension-checkcompatibility) | 测试当前浏览器兼容性情况。 |
| [enableVirtualBackground](#irtcbeautyextension-enablevirtualbackground) | 开启虚拟背景。 |
| [disableVirtualBackground](#irtcbeautyextension-disablevirtualbackground) | 关闭虚拟背景。 |
| [setBackgroundMode](#irtcbeautyextension-setbackgroundmode) | 设置虚拟背景模式。 |
| [getBackgroundImage](#irtcbeautyextension-getbackgroundimage) | 获取当前虚拟背景图片。 |
| [loadBackgroundImage](#irtcbeautyextension-loadbackgroundimage) | 设置虚拟背景图片。 |
| [setAIModelType](#irtcbeautyextension-setaimodeltype) | 设置虚拟背景使用的人像识别 AI 算法效果。 |

### checkCompatibility <span id="irtcbeautyextension-checkcompatibility"></span> 

测试当前浏览器兼容性情况。

- **类型**

  ```ts
  () => Promise<CompatibilityCheckResult>
  ```

- **返回值**

  类型: <code>Promise<[CompatibilityCheckResult](#compatibilitycheckresult)\></code>

  兼容性测试结果。

### enableVirtualBackground <span id="irtcbeautyextension-enablevirtualbackground"></span> 

开启虚拟背景。

- **类型**

  ```ts
  () => void
  ```

- **注意**

  + 调用 [setBackgroundMode](#setbackgroundmode) 设置虚拟背景模式。若在调用本方法前没有设置虚拟背景模式，则默认开启背景模糊。
  + 调用 [disableVirtualBackground](#disablevirtualbackground) 关闭虚拟背景。
  + 本方法仅适用于视频源，不适用于屏幕源。

### disableVirtualBackground <span id="irtcbeautyextension-disablevirtualbackground"></span> 

关闭虚拟背景。

- **类型**

  ```ts
  () => void
  ```

### setBackgroundMode <span id="irtcbeautyextension-setbackgroundmode"></span> 

设置虚拟背景模式。

- **类型**

  ```ts
  (mode: BackgroundMode) => void
  ```

- **注意**

  开启虚拟背景后，可调用本方法动态切换使用的虚拟背景模式。

- **参数**

  - **mode**

    类型: <code>[BackgroundMode](#backgroundmode)</code>

    虚拟背景模式。

### getBackgroundImage <span id="irtcbeautyextension-getbackgroundimage"></span> 

获取当前虚拟背景图片。

- **类型**

  ```ts
  () => string
  ```

- **返回值**

  类型: <code>string</code>

  当前虚拟背景图片 URL。

### loadBackgroundImage <span id="irtcbeautyextension-loadbackgroundimage"></span> 

设置虚拟背景图片。

- **类型**

  ```ts
  (url: string) => Promise<void>
  ```

- **注意**

  + 支持的图片格式为 jpg、jpeg、png。
  + 图片和视频长宽比不一致时，为保证图片内容不变形，图片按短边缩放至与视频帧一致，使图片填满视频帧，对多出的高或宽进行剪裁。
  + 自定义图片带有局部透明效果时，透明部分由黑色代替。

- **参数**

  - **url**

    类型: <code>string</code>

    虚拟背景图片 URL。

- **返回值**

  类型: <code>Promise<void\></code>

### setAIModelType <span id="irtcbeautyextension-setaimodeltype"></span> 

设置虚拟背景使用的人像识别 AI 算法效果。

- **类型**

  ```ts
  (type: BackgroundAIModelType) => void
  ```

- **参数**

  - **type**

    类型: <code>[BackgroundAIModelType](#backgroundaimodeltype)</code>

    人像识别 AI 算法效果。


## CompatibilityCheckResult <span id="compatibilitycheckresult"></span>

类型: `interface`

兼容性测试结果。

<p style="font-size: 16px;font-weight: bolder;"> isCompatible <span id="compatibilitycheckresult-iscompatible"></span></p> 

类型: <code>boolean</code>

是否兼容。</br>
  `true`：符合兼容性最低要求，可正常运行。
  `false`：不兼容，无法正常运行。

<p style="font-size: 16px;font-weight: bolder;"> reasons <span id="compatibilitycheckresult-reasons"></span></p> 

类型: <code>number[]</code>

不兼容的原因。</br>
  + 0：其他未知原因。
  + 1：系统不支持 getUserMedia API。
  + 2：系统不支持 WebAssembly。
  + 3：系统获取不到 video input 设备。
  + 100：WebAR SDK 加载失败。

## IRTCBeautyExtensionConfig <span id="irtcbeautyextensionconfig"></span>

类型: `interface`

美颜和虚拟背景插件参数。

<p style="font-size: 16px;font-weight: bolder;"> authFileUrl <span id="irtcbeautyextensionconfig-authfileurl"></span></p> 

类型: <code>string</code>

鉴权文件地址。

<p style="font-size: 16px;font-weight: bolder;"> aiBackend <span id="irtcbeautyextensionconfig-aibackend"></span></p> 

类型: <code>[BackgroundAIBackend](#backgroundaibackend)</code>

初始化时选择使用 CPU/GPU 模式，默认使用 CPU 模式。

<p style="font-size: 16px;font-weight: bolder;"> aiModelType <span id="irtcbeautyextensionconfig-aimodeltype"></span></p> 

类型: <code>[BackgroundAIModelType](#backgroundaimodeltype)</code>

人像识别 AI 算法效果。

## BackgroundMode <span id="backgroundmode"></span>

类型: `enum`

虚拟背景模式。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | BACKGROUND_BLUR | `'blur'` | 背景模糊。 |
  | BACKGROUND_IMAGE | `'image'` | 背景图片。 |

## BackgroundAIModelType <span id="backgroundaimodeltype"></span>

类型: `enum`

人像识别 AI 算法效果。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | PERFORMANCE | `0` | 性能优先。 |
  | QUALITY | `1` | 效果优先。 |

## BackgroundAIBackend <span id="backgroundaibackend"></span>

类型: `enum`

初始化时选择使用 CPU/GPU 模式，默认使用 CPU 模式。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | CPU | `-1` | CPU 模式。 |
  | GPU | `1` | GPU 模式。SDK 内部会自动判断当前环境是否支持开启 GPU 模式，对于不支持的环境会自动回退为 CPU 模式。 |