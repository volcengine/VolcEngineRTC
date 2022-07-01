
const remote = require('electron').remote;
const app = remote.app;
const SDK = require('@byted/vertc-electron-sdk');
const fs = require('fs');
const path = require('path');



////////////////////////////////////////////////////////////////
const mkdirsSync = (dirname) => {
    if (fs.existsSync(dirname)) {
        return true
    } else {
        if (mkdirsSync(path.dirname(dirname))) {
            fs.mkdirSync(dirname)
            return true
        }
    }
}



////////////////////////////////////////////////////////////////
console.log('SDK: ', SDK);
window.veRTCEngine = SDK.veRTCEngine;

window.veTools = {
    getLogPath: () => {
        let USER_DATA_PATH = app.getPath("userData");
        let logFilePath = path.join(USER_DATA_PATH, "logs", "vertc")
        mkdirsSync(logFilePath);
        return logFilePath;
    },
    getPlatform: () => {
        return process.platform;
    }
};