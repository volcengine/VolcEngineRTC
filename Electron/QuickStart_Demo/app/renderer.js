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
/******/ 	return __webpack_require__(__webpack_require__.s = "./src/renderer/index.js");
/******/ })
/************************************************************************/
/******/ ({

/***/ "./src/config/config.js":
/*!******************************!*\
  !*** ./src/config/config.js ***!
  \******************************/
/*! no static exports found */
/***/ (function(module, exports) {

eval("const config = {\n  /// APPID 使用SDK前需要为自己的应用申请一个AppId，详情参见: https://www.volcengine.com/docs/6348/69865\n  appId: '',\n  ///TOKEN 加入房间的时候需要使用token完成鉴权，详情参见: https://www.volcengine.com/docs/6348/70121\n  token: ''\n};\nmodule.exports = config;\n\n//# sourceURL=webpack:///./src/config/config.js?");

/***/ }),

/***/ "./src/renderer/index.js":
/*!*******************************!*\
  !*** ./src/renderer/index.js ***!
  \*******************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

eval("/**\n * VolcEngineRTC 视频通话的主页面\n * 本示例不限制房间内最大用户数；同时最多渲染四个用户的视频数据（自己和三个远端用户视频数据）；\n *\n * 包含如下简单功能：\n * - 创建引擎\n * - 设置视频发布参数\n * - 渲染自己的视频数据\n * - 加入音视频通话房间\n * - 切换前置/后置摄像头\n * - 打开/关闭麦克风\n * - 打开/关闭摄像头\n * - 切换听筒/扬声器\n * - 渲染远端用户的视频数据\n * - 离开房间\n * - 销毁引擎\n *\n * 实现一个基本的音视频通话的流程如下：\n * 1.创建引擎               vEngine.init();\n * 2.设置编码参数            vEngine.setVideoEncoderConfig();\n * 3.开启本地视频采集         vEngine.startVideoCapture();\n * 4.设置本地视频渲染视图      vEngine.setupLocalVideo();\n * 4.加入音视频通话房间        vEngine.joinRoom();\n * 5.在收到远端用户视频首帧之后，设置用户的视频渲染视图 vEngine.setupRemoteVideo（）\n * 6.离开音视频通话房间        vEngine.leaveRoom();\n * 7.销毁引擎         vEngine.uninit():\n \n * 有以下常见的注意事项：\n * 1.本示例中，我们在 OnFirstRemoteVideoFrameRendered 这个事件中给远端用户设置远端用户视频渲染视图，这个回调表示的是收到了远端用户的视频第一帧。当然也可以在 onUserJoined:elapsed: 回调中设置远端用户视频渲染视图\n * 2.SDK 回调不在主线程，UI 操作需要切换线程\n * 3.用户成功加入房间后，SDK 会通过 OnUserJoined 回调已经在房间的用户信息\n * 4.SDK 支持同时发布多个参数的视频流，接口是 setVideoEncoderConfig:\n * 5.加入房间时，需要有有效的 token，加入失败时会通过 onError: 输出对应的错误码\n * 6.用户可以通过vEngine.joinRoom(); 中的 roomConfig 来获得不同场景下的性能优化。本示例是音视频通话场景\n * 7.不需要在每次加入/退出房间时销毁引擎。本示例退出房间时销毁引擎是为了展示完整的使用流程\n *\n * 详细的API文档参见: https://site.bytedance.net/docs/1/6/85530/\n */\nconst ipcRenderer = __webpack_require__(/*! electron */ \"electron\").ipcRenderer;\n\nconst remote = __webpack_require__(/*! electron */ \"electron\").remote;\n\nconst {\n  app,\n  dialog\n} = __webpack_require__(/*! electron */ \"electron\");\n\nconst path = __webpack_require__(/*! path */ \"path\");\n\nconst config = __webpack_require__(/*! ../config/config */ \"./src/config/config.js\");\n\nconst OFFVIDEOICON = './assets/videoOffIcon.png';\nconst ONVIDEOICON = './assets/videoOnIcon.png';\nconst OFFMICICON = './assets/micOffIcon.png';\nconst ONMICICON = './assets/micOnIcon.png';\nconst TEXTMAP = {\n  'idRoomId': '房间ID',\n  'idUserId': '用户ID'\n}; ///////////////////////////////////////////////////////////////////\n\n$('#control').hide();\n$('.player').hide();\n$('#room-id-text').text('');\n$('#user-id-text').text('');\ncheckRoomIdAndUserId('idRoomId');\ncheckRoomIdAndUserId('idUserId'); ///////////////////////////////////////////\n// Engine 需要的参数\n\nlet vEngine; // Note: 请输入你的 appId\n\nlet appId = config.appId;\nlet token = config.token; // Note: 房间 id\n\nlet roomId = ''; // Note: 用户 id\n\nlet userId = '';\nlet isMicOn = false; // control the mic\n\nlet isVideoOn = false; // control the video\n\nconst MAIN_STREAM_INDEX = 0;\nlet remoteUsers = []; // UI Elements\n\nlet idRoomId, idUserId;\nlet idJoin, idLeave;\nlet idOpenMicrophone;\nlet idOpenCamera;\nlet idLocalVideoContainer;\nlet isEngineCreated = false;\nlet bigSolution = {\n  width: 1280,\n  height: 720,\n  fps: 15\n};\nlet smallSolution = {\n  width: 120,\n  height: 120,\n  fps: 15\n}; // 如果你只想发送一路音频流，可只配置一组音视频分辨率信息\n\nlet profiles = [bigSolution, smallSolution];\nlet roomConfig = {\n  room_profile_type: 1,\n  is_auto_publish: true,\n  is_auto_subscribe_audio: true,\n  is_auto_subscribe_video: true\n}; /////////////////////////////////////////////////////////////////////////\n// Callback\n// 有人加入音视频会议\n\nconst userJoined_handler = (userId, elapsed) => {\n  remoteUsers.push({\n    userId\n  });\n}; // 有人离开音视频会议\n\n\nconst userOffline_handler = (userId, reason) => {\n  const remoteUserId = userId;\n\n  if (remoteUserId === idUserId) {\n    $('#idLocalVideoContainer').hide();\n    $('#local-player-name').text('');\n  }\n\n  $(`#player-wrapper-${remoteUserId}`).remove();\n  remoteUsers = remoteUsers.filter(ele => {\n    return !ele.userId === userId;\n  });\n}; // 收到远端用户视频第一帧\n\n\nconst firstRemoteVideoFrame_handler = (key, info) => {\n  const userId = key.user_id;\n  const remoteUserId = \"player-wrapper-\" + key.user_id;\n  let stream_index = key.stream_index;\n  const currentLength = $('.player-wrapper').length; // Player doms are created when there are no more than four in a room\n\n  if (currentLength < 4) {\n    const player = $(`\n    <div id=\"player-wrapper-${userId}\" class=\"player-wrapper re-player\">\n      <p class=\"player-name\">${userId}</p>\n    </div>\n  `);\n    $('#player-list').append(player);\n  }\n\n  if (stream_index == 0) {\n    ///解绑指定远端视频流已绑定的本地视图\n    vEngine.removeRemoteVideo(key.user_id); ///设置远端用户视频渲染视图  \n\n    vEngine.setupRemoteVideo(key.user_id, document.getElementById(remoteUserId), 1);\n  }\n}; ///收到sdk危险警告回调\n\n\nconst warning_handler = warn => {}; ///收到sdk报错回调\n\n\nconst error_handler = error => {};\n\nvEngine = new window.veRTCEngine(); ///初始化RTC引擎\n\ncreateEngine();\ndocument.getElementById('header-version').innerHTML = 'VolcEngingRTC ' + window.veRTCEngine.getSDKVersion() + ' DebugProcessId ' + window.veRTCEngine.getCurrentProcessId(); // 检查输入是否合法\n\nfunction checkRoomIdAndUserId(name) {\n  $(`#${name}`).keyup(() => {\n    checkReg(name);\n  });\n}\n\nfunction checkReg(name) {\n  const inputValue = $(`#${name}`).val();\n  let hasError = false;\n\n  if (!inputValue) {\n    $(`#${name}`).css('border-color', '#ff4d4f');\n    $(`#${name}-text`).text(`请输入${TEXTMAP[name]}`);\n    hasError = true;\n  } else if (!/^[0-9a-zA-Z_\\-@.]{1,128}$/.test(inputValue)) {\n    $(`#${name}`).css('border-color', '#ff4d4f');\n    $(`#${name}-text`).text(`${TEXTMAP[name]}输入有误，请重新输入`);\n    hasError = true;\n  } else {\n    $(`#${name}-text`).text('');\n    $(`#${name}`).css('border-color', '#d9d9d9');\n    hasError = false;\n  }\n\n  return hasError;\n} /////////////////////////////////////////////////////////////////////////\n// Callback Function\n\n\nfunction initEventListeners() {\n  ///监听用户加入音视频房间回调\n  vEngine.on('OnUserJoined', userJoined_handler); ///监听用户离开音视频房间回调\n\n  vEngine.on('OnUserLeave', userOffline_handler); ///监听远端用户视频第一帧回调\n\n  vEngine.on('OnFirstRemoteVideoFrameRendered', firstRemoteVideoFrame_handler); ///监听RTC警告\n\n  vEngine.on('OnWarning', warning_handler); ///监听RTC报错\n\n  vEngine.on('OnError', error_handler);\n}\n\nfunction createEngine() {\n  console.log('create engine');\n\n  if (!vEngine) {\n    vEngine = new window.veRTCEngine();\n  } ///初始化引擎\n\n\n  vEngine.init(appId, '', JSON.stringify(\"\"));\n  initEventListeners();\n  isEngineCreated = true;\n  onBtnOpenCamera();\n  onBtnOpenMicrophone();\n}\n\nfunction destoryEngine() {\n  if (vEngine) {\n    ///销毁RTC引擎\n    vEngine.uninit();\n    vEngine = null;\n  }\n\n  isEngineCreated = false;\n}\n\nfunction onBtnJoin() {\n  if (checkReg('idRoomId') || checkReg('idUserId')) {\n    return;\n  }\n\n  roomId = idRoomId.value;\n  userId = idUserId.value;\n  $('#control').show();\n  $('.player').show();\n  $('#pannel').hide();\n  $('#header-version').text(`${roomId}`);\n  $('#local-player-name').text(`${userId}`);\n\n  if (!isEngineCreated || vEngine == null) {\n    createEngine();\n  }\n\n  vEngine.setVideoEncoderConfig(MAIN_STREAM_INDEX, profiles); // 设置本地视频渲染 view\n\n  vEngine.setupLocalVideo(idLocalVideoContainer); ///加入音视频房间\n\n  let ret = vEngine.joinRoom(token, roomId, userId, \"\", roomConfig);\n  console.log('join room ret : ' + ret);\n}\n\nfunction onBtnLeave() {\n  ///离开音视频房间\n  vEngine.leaveRoom();\n  $('#control').hide();\n  $('.player').hide();\n  $('#pannel').show();\n  document.getElementById('header-version').innerHTML = 'VolcEngingRTC ' + window.veRTCEngine.getSDKVersion() + ' DebugProcessId ' + window.veRTCEngine.getCurrentProcessId();\n}\n\nfunction onBtnOpenMicrophone() {\n  isMicOn = !isMicOn;\n\n  if (isMicOn) {\n    ///开启本地音频采集\n    vEngine.startAudioCapture();\n    $(`#idOpenMicrophone img`).attr('src', `${ONMICICON}`);\n  } else {\n    ///关闭本地音频采集\n    vEngine.stopAudioCapture();\n    $(`#idOpenMicrophone img`).attr('src', `${OFFMICICON}`);\n  }\n}\n\nfunction onBtnOpenCamera() {\n  isVideoOn = !isVideoOn;\n\n  if (isVideoOn) {\n    ///开启本地视频采集\n    vEngine.startVideoCapture();\n    $(`#idOpenCamera img`).attr('src', `${ONVIDEOICON}`);\n  } else {\n    ///关闭本地视频采集\n    vEngine.stopVideoCapture();\n    $(`#idOpenCamera img`).attr('src', `${OFFVIDEOICON}`);\n  }\n}\n\nwindow.onload = () => {\n  idRoomId = document.getElementById('idRoomId');\n  idUserId = document.getElementById('idUserId');\n  idJoin = document.getElementById('idJoin');\n  idLeave = document.getElementById('idLeave');\n  idOpenMicrophone = document.getElementById('idOpenMicrophone');\n  idOpenCamera = document.getElementById('idOpenCamera');\n  idLocalVideoContainer = document.getElementById('idLocalVideoContainer');\n  idJoin.addEventListener('click', onBtnJoin);\n  idLeave.addEventListener('click', onBtnLeave);\n  idOpenMicrophone.addEventListener('click', onBtnOpenMicrophone);\n  idOpenCamera.addEventListener('click', onBtnOpenCamera);\n};\n\n//# sourceURL=webpack:///./src/renderer/index.js?");

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

/***/ })

/******/ });