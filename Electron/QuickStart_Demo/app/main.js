module.exports =
/******/ (function(modules) { // webpackBootstrap
/******/ 	// The module cache
/******/ 	var installedModules = {};
/******/
/******/ 	// The require function
/******/ 	function __webpack_require__(moduleId) {
/******/
/******/ 		// Check if module is in cache
/******/ 		if(installedModules[moduleId]) {
/******/ 			return installedModules[moduleId].exports;
/******/ 		}
/******/ 		// Create a new module (and put it into the cache)
/******/ 		var module = installedModules[moduleId] = {
/******/ 			i: moduleId,
/******/ 			l: false,
/******/ 			exports: {}
/******/ 		};
/******/
/******/ 		// Execute the module function
/******/ 		modules[moduleId].call(module.exports, module, module.exports, __webpack_require__);
/******/
/******/ 		// Flag the module as loaded
/******/ 		module.l = true;
/******/
/******/ 		// Return the exports of the module
/******/ 		return module.exports;
/******/ 	}
/******/
/******/
/******/ 	// expose the modules object (__webpack_modules__)
/******/ 	__webpack_require__.m = modules;
/******/
/******/ 	// expose the module cache
/******/ 	__webpack_require__.c = installedModules;
/******/
/******/ 	// define getter function for harmony exports
/******/ 	__webpack_require__.d = function(exports, name, getter) {
/******/ 		if(!__webpack_require__.o(exports, name)) {
/******/ 			Object.defineProperty(exports, name, { enumerable: true, get: getter });
/******/ 		}
/******/ 	};
/******/
/******/ 	// define __esModule on exports
/******/ 	__webpack_require__.r = function(exports) {
/******/ 		if(typeof Symbol !== 'undefined' && Symbol.toStringTag) {
/******/ 			Object.defineProperty(exports, Symbol.toStringTag, { value: 'Module' });
/******/ 		}
/******/ 		Object.defineProperty(exports, '__esModule', { value: true });
/******/ 	};
/******/
/******/ 	// create a fake namespace object
/******/ 	// mode & 1: value is a module id, require it
/******/ 	// mode & 2: merge all properties of value into the ns
/******/ 	// mode & 4: return value when already ns object
/******/ 	// mode & 8|1: behave like require
/******/ 	__webpack_require__.t = function(value, mode) {
/******/ 		if(mode & 1) value = __webpack_require__(value);
/******/ 		if(mode & 8) return value;
/******/ 		if((mode & 4) && typeof value === 'object' && value && value.__esModule) return value;
/******/ 		var ns = Object.create(null);
/******/ 		__webpack_require__.r(ns);
/******/ 		Object.defineProperty(ns, 'default', { enumerable: true, value: value });
/******/ 		if(mode & 2 && typeof value != 'string') for(var key in value) __webpack_require__.d(ns, key, function(key) { return value[key]; }.bind(null, key));
/******/ 		return ns;
/******/ 	};
/******/
/******/ 	// getDefaultExport function for compatibility with non-harmony modules
/******/ 	__webpack_require__.n = function(module) {
/******/ 		var getter = module && module.__esModule ?
/******/ 			function getDefault() { return module['default']; } :
/******/ 			function getModuleExports() { return module; };
/******/ 		__webpack_require__.d(getter, 'a', getter);
/******/ 		return getter;
/******/ 	};
/******/
/******/ 	// Object.prototype.hasOwnProperty.call
/******/ 	__webpack_require__.o = function(object, property) { return Object.prototype.hasOwnProperty.call(object, property); };
/******/
/******/ 	// __webpack_public_path__
/******/ 	__webpack_require__.p = "";
/******/
/******/
/******/ 	// Load entry module and return exports
/******/ 	return __webpack_require__(__webpack_require__.s = "./src/main/index.js");
/******/ })
/************************************************************************/
/******/ ({

/***/ "./src/main/index.js":
/*!***************************!*\
  !*** ./src/main/index.js ***!
  \***************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

eval("// Modules to control application life and create native browser window\nconst {\n  app,\n  BrowserWindow,\n  ipcMain,\n  systemPreferences\n} = __webpack_require__(/*! electron */ \"electron\");\n\nconst path = __webpack_require__(/*! path */ \"path\");\n\nconst {\n  electron\n} = __webpack_require__(/*! process */ \"process\");\n\nlet mainWindow = null;\nglobal.sharedObject = {\n  mainWindowId: null\n}; // 检查并申请设备权限：麦克风、摄像头、屏幕录制\n\nasync function checkAndApplyDeviceAccessPrivilege() {\n  const cameraPrivilege = systemPreferences.getMediaAccessStatus('camera');\n  console.log(`checkAndApplyDeviceAccessPrivilege before apply cameraPrivilege: ${cameraPrivilege}`);\n\n  if (cameraPrivilege !== 'granted') {\n    await systemPreferences.askForMediaAccess('camera');\n  }\n\n  const micPrivilege = systemPreferences.getMediaAccessStatus('microphone');\n  console.log(`checkAndApplyDeviceAccessPrivilege before apply micPrivilege: ${micPrivilege}`);\n\n  if (micPrivilege !== 'granted') {\n    await systemPreferences.askForMediaAccess('microphone');\n  }\n\n  const screenPrivilege = systemPreferences.getMediaAccessStatus('screen');\n  console.log(`checkAndApplyDeviceAccessPrivilege before apply screenPrivilege: ${screenPrivilege}`);\n}\n\nfunction initAppListeners() {\n  ipcMain.on(\"createShareScreenWindow\", (event, arg) => {\n    event.returnValue = 0;\n  });\n  ipcMain.on(\"destroyShareScreenWindow\", (event, arg) => {\n    event.returnValue = 0;\n  });\n}\n\nfunction initApp() {\n  // Create the browser window.\n  function createWindow() {\n    const windowOptions = {\n      width: 1080,\n      minWidth: 680,\n      height: 840,\n      title: app.getName(),\n      webPreferences: {\n        webSecurity: false,\n        nodeIntegration: true,\n        contextIsolation: false,\n        preload: path.join(__dirname, 'preload.js'),\n        // TODO: Electron(v12.0.2) need this to support retmote feat\n        enableRemoteModule: true\n      }\n    };\n    mainWindow = new BrowserWindow(windowOptions); // and load the index.html of the app.\n\n    mainWindow.loadFile('index.html');\n    global.sharedObject.mainWindowId = mainWindow.webContents.id;\n    mainWindow.on('closed', () => {\n      mainWindow = null;\n    });\n  }\n\n  app.whenReady().then(async () => {\n    await checkAndApplyDeviceAccessPrivilege();\n    createWindow();\n    app.on('activate', () => {\n      if (mainWindow === null) {\n        createWindow();\n      }\n    });\n  });\n  app.on('window-all-closed', () => {\n    if (process.platform !== 'darwin') app.quit();\n  });\n} // In this file you can include the rest of your app's specific main process\n// code. You can also put them in separate files and require them here.\n\n\nfunction main() {\n  initAppListeners();\n  initApp();\n}\n\nmain();\n\n//# sourceURL=webpack:///./src/main/index.js?");

/***/ }),

/***/ "electron":
/*!***************************!*\
  !*** external "electron" ***!
  \***************************/
/*! no static exports found */
/***/ (function(module, exports) {

eval("module.exports = require(\"electron\");\n\n//# sourceURL=webpack:///external_%22electron%22?");

/***/ }),

/***/ "path":
/*!***********************!*\
  !*** external "path" ***!
  \***********************/
/*! no static exports found */
/***/ (function(module, exports) {

eval("module.exports = require(\"path\");\n\n//# sourceURL=webpack:///external_%22path%22?");

/***/ }),

/***/ "process":
/*!**************************!*\
  !*** external "process" ***!
  \**************************/
/*! no static exports found */
/***/ (function(module, exports) {

eval("module.exports = require(\"process\");\n\n//# sourceURL=webpack:///external_%22process%22?");

/***/ })

/******/ });