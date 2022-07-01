﻿
const packageJson = require("./package.json");
const buildConfigCommon = require("./builder-config-common");

// see https://www.electron.build/configuration/configuration#configuration

let buildConfigWin = {
    "nsis": {
        "artifactName": `${packageJson.name}-${packageJson.version}.exe`,
        "perMachine": true,
        "oneClick": false,
        "warningsAsErrors": false,
        "deleteAppDataOnUninstall": true,
        // "allowElevation": true,
        "createDesktopShortcut": "always",
        "allowToChangeInstallationDirectory": true,
        "runAfterFinish": true,
        "packElevateHelper": true
    },
    "win": {
        "icon": "assets/favicon.ico",
        "target": [
            {
                "target": "nsis",
                "arch": [
                    "ia32"
                ]
            }
        ]
    },
	

    "asar": false, // asar打包
    "extraResources":  { // 拷贝dll等静态文件到指定位置
        "from": "./assets/",
        "to": "assets"
    }
	
};

Object.assign(buildConfigWin, buildConfigCommon);

module.exports = buildConfigWin;


