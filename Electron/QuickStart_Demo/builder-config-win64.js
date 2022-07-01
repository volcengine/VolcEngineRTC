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
        "runAfterFinish": true
    },
    "win": {
        "icon": "assets/favicon.ico",
        "target": [
            {
                "target": "nsis",
                "arch": [
                    "x64"
                ]
            }
        ]
    }
};

Object.assign(buildConfigWin, buildConfigCommon);

module.exports = buildConfigWin;


