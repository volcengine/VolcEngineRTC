const { app, BrowserWindow, ipcMain,systemPreferences } = require('electron')
const path = require("path");
const { electron } = require('process');

let mainWindow = null;
global.sharedObject = {
  mainWindowId: null,
}

// 检查并申请设备权限：麦克风、摄像头、屏幕录制
async function checkAndApplyDeviceAccessPrivilege() {
  const cameraPrivilege = systemPreferences.getMediaAccessStatus('camera');
  console.log(`checkAndApplyDeviceAccessPrivilege before apply cameraPrivilege: ${cameraPrivilege}`);
  if (cameraPrivilege !== 'granted') {
    await systemPreferences.askForMediaAccess('camera');
  }

  const micPrivilege = systemPreferences.getMediaAccessStatus('microphone');
  console.log(`checkAndApplyDeviceAccessPrivilege before apply micPrivilege: ${micPrivilege}`);
  if (micPrivilege !== 'granted') {
    await systemPreferences.askForMediaAccess('microphone');
  }

  const screenPrivilege = systemPreferences.getMediaAccessStatus('screen');
  console.log(`checkAndApplyDeviceAccessPrivilege before apply screenPrivilege: ${screenPrivilege}`);
}

function initAppListeners() {
  ipcMain.on("createShareScreenWindow", (event, arg) => {
    event.returnValue = 0;
  });
  ipcMain.on("destroyShareScreenWindow", (event, arg) => {
    event.returnValue = 0;
  });
}

function initApp() {

  // 创建主窗体
  function createWindow() {
    const windowOptions = {
      width: 1080,
      minWidth: 680,
      height: 840,
      title: app.getName(),
      webPreferences: {
        webSecurity: false,
      nodeIntegration: true,
      contextIsolation: false,
      preload: path.join(__dirname, 'preload.js'),
      enableRemoteModule: true
      },
    };
    mainWindow = new BrowserWindow(windowOptions);
    // 加载视图
    mainWindow.loadFile('index.html')
    global.sharedObject.mainWindowId = mainWindow.webContents.id

    mainWindow.on('closed', () => {
      mainWindow = null;
    });
  }

  app.whenReady().then(async() => {
    await checkAndApplyDeviceAccessPrivilege();
    createWindow();
    app.on('activate',  ()=> {
      if (mainWindow === null) {
        createWindow()
      }
    })
  })

  app.on('window-all-closed', () => {
    if (process.platform !== 'darwin') app.quit()
  })
}


function main() {
  initAppListeners();
  initApp();
}

main();
