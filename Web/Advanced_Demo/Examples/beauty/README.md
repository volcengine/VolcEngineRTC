RTC 提供基础美颜插件，你可以通过此插件实现美白、磨皮、锐化等基础美颜功能。

# 功能变更日志

1. 自 Web SDK v4.47 起，本功能可用。

2. Web SDK v4.52 对本功能做了如下修改：
   - 注册插件后，美颜不再默认开启，需要调用 [enableBeauty](#enablebeauty) 开启美颜。
   - 开启美颜的接口名由 `enable` 变更为 `enableBeauty`，关闭美颜的接口名由 `disable` 变更为 `disableBeauty`，原接口废弃。
   - 优化该功能的浏览器兼容性，由支持在桌面端 Chrome 94+、Edge 94+ 上使用变更为支持在桌面端 Chrome 70+、	Edge 83+、Safari 12+、Firefox 80+ 上使用，即与当前 [Web SDK 浏览器兼容性](https://www.volcengine.com/docs/6348/111854)下限一致。

3. Web SDK v4.60.2 及之后版本需传入鉴权文件 [Web 端基础美颜](https://www.volcengine.com/docs/6348/148646)

# 前置条件

1. RTC SDK v4.47+ 你需要集成 RTC SDK，并实现音视频通话功能。
	
2. 基础美颜功能兼容性与 [Web SDK 浏览器兼容性](https://www.volcengine.com/docs/6348/111854)一致，不建议在移动端使用本功能。
		
3. 为了更好的使用体验，建议设备满足以下要求：
	1. 双核 Intel Core i5+
		
	2. RAM 8 GB+
		
	3. 64 位操作系统

4. 如果你使用了云代理功能，你需要在防火墙白名单中添加基础美颜域名，参看[在防火墙限制下进行通话](https://www.volcengine.com/docs/6348/146420)。
		

# 操作步骤

1. 在你的项目中引入美颜插件：
   - 可以直接引入。
   ```typescript
   import RTCBeautyExtension from '@volcengine/rtc/extension-beauty';
   ```
   - 自 v4.51.1 版本起，可以通过 UMD 方式引入。
   ```typescript
   const {EffectBeautyMode, RTCBeautyExtension} = window.VERTCExtensions;
   ```
2. 注册美颜插件。

:::warning
注册插件后，无法动态修改视频流帧率。你可以在注册插件前调用 [setVideoEncoderConfig](https://www.volcengine.com/docs/6348/104478#setvideoencoderconfig) 修改帧率。
:::

```typescript
import VERTC from '@volcengine/rtc';

// 创建引擎实例
const engine = VERTC.createEngine('appid');

// 创建美颜插件实例
const beautyExtension = new RTCBeautyExtension({
    authFileUrl: 'xx.auth',
});
// 注册美颜插件
try {
  await engine.registerExtension(beautyExtension);
} catch (error) {
  // 注册失败，详细信息：error.message
}
```

3. 开始视频采集，并设置渲染视图及模式。 示例代码以内部采集为例，如需使用外部采集，参看 [setVideoSourceType](104478#setvideosourcetype)。
	
:::warning
基础美颜仅对主流、本地流生效，不支持屏幕流、远端流。即 `StreamIndex` 必须为 `STREAM_INDEX_MAIN`。
:::

```typescript
// 开启内部视频采集
engine.startVideoCapture();
// 设置本地视频渲染时使用的视图，并设置渲染模式。
engine.setLocalVideoPlayer(StreamIndex.STREAM_INDEX_MAIN, {
  renderDom: 'yourDomId'
});
```

4. 设置基础美颜参数，包括美白、磨皮、锐化。参看 [setBeautyIntensity](#setbeautyintensity)。
	

```typescript
import { EffectBeautyMode } from '@volcengine/rtc/extension-beauty';

// 美颜参数设置-美白
beautyExtension.setBeautyIntensity(EffectBeautyMode.EFFECT_WHITE_MODE, 0.2);
// 美颜参数设置-磨皮
beautyExtension.setBeautyIntensity(EffectBeautyMode.EFFECT_SMOOTH_MODE, 0.2);
// 美颜参数设置-锐化
beautyExtension.setBeautyIntensity(EffectBeautyMode.EFFECT_SHARPEN_MODE, 0.2);
```

5. 开启基础美颜。

:::tip
如调用本方法前未调用 [setBeautyIntensity](#setbeautyintensity) 设置参数，则基础美颜强度使用默认值。
:::

```typescript
// 开启美颜
beautyExtension.enableBeauty();
```

6. 关闭基础美颜。
	
:::tip
若关闭基础美颜后再次调用 [enableBeauty](#enablebeauty) 开启基础美颜，则保留上次的美颜强度设置。若销毁引擎，则美颜强度恢复为默认值。
:::

```typescript
// 关闭美颜
beautyExtension.disableBeauty();
```

# API 参考

## IRTCBeautyExtension

类型: `interface`

- **API**

| 方法 | 描述 |
| :-- | :-- |
| [checkCompatibility](#irtcbeautyextension-checkcompatibility) | 测试当前浏览器兼容性情况。 |
| [enableBeauty](#irtcbeautyextension-enablebeauty) | 开启基础美颜。 |
| [disableBeauty](#irtcbeautyextension-disablebeauty) | 关闭基础美颜。 |
| [setBeautyIntensity](#irtcbeautyextension-setbeautyintensity) | 设置基础美颜强度。 |

### checkCompatibility <span id="irtcbeautyextension-checkcompatibility"></span> 

测试当前浏览器兼容性情况。

- **类型**

  ```ts
  () => Promise<CompatibilityCheckResult>
  ```

- **返回值**

  类型: <code>Promise<[CompatibilityCheckResult](#compatibilitycheckresult)\></code>

  兼容性测试结果。

### enableBeauty <span id="irtcbeautyextension-enablebeauty"></span> 

开启基础美颜。

- **类型**

  ```ts
  () => void
  ```

- **注意**

  + 调用 [setBeautyIntensity](#setbeautyintensity) 设置基础美颜强度。若在调用本方法前没有设置美颜强度，则初始美白、磨皮、锐化强度均为 0.5。
  + 调用 [disableBeauty](#disablebeauty) 关闭基础美颜。
  + 本方法仅适用于视频源，不适用于屏幕源。

### disableBeauty <span id="irtcbeautyextension-disablebeauty"></span> 

关闭基础美颜。

- **类型**

  ```ts
  () => void
  ```

### setBeautyIntensity <span id="irtcbeautyextension-setbeautyintensity"></span> 

设置基础美颜强度。

- **类型**

  ```ts
  (beautyMode: EffectBeautyMode, intensity: number) => void
  ```

- **注意**

  + 若在调用 [enableBeauty](#enablebeauty) 前设置美颜强度，则对应美颜功能的强度初始值会根据设置更新。
  + 销毁引擎后，美颜功能强度恢复默认值。

- **参数**

  - **beautyMode**

    类型: <code>[EffectBeautyMode](#effectbeautymode)</code>

    基础美颜模式。

  - **intensity**

    类型: <code>number</code>

    美颜强度，取值范围为 [0,1]。强度为 0 表示关闭，默认强度为 0.5。

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

## EffectBeautyMode <span id="effectbeautymode"></span>

类型: `enum`

基础美颜模式。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | EFFECT_WHITE_MODE | `0` | 美白。 |
  | EFFECT_SMOOTH_MODE | `1` | 磨皮。 |
  | EFFECT_SHARPEN_MODE | `2` | 锐化。 |