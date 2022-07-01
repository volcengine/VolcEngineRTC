﻿const buildConfigCommon = require("./builder-config-common");

let buildConfigMac = {
    "mac": {
      "target": "dmg",
      "icon": "assets/favicon.icns",
      "entitlements": "builder-config/entitlements.mac.plist",
      "hardenedRuntime": true,
      "extendInfo": {
        "NSCameraUsageDescription": "Request camera usage",
        "NSMicrophoneUsageDescription": "Request mic usage"
      }
    },
    "asar": false, // asar打包
    "extraResources":  { // 拷贝dll等静态文件到指定位置
        "from": "./assets/",
        "to": "assets"
    }
}


Object.assign(buildConfigMac, buildConfigCommon);

module.exports = buildConfigMac;
