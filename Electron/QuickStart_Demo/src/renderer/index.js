/**
 * VolcEngineRTC 视频通话的主页面
 * 本示例不限制房间内最大用户数；同时最多渲染四个用户的视频数据（自己和三个远端用户视频数据）；
 *
 * 包含如下简单功能：
 * - 创建引擎
 * - 设置视频发布参数
 * - 渲染自己的视频数据
 * - 加入音视频通话房间
 * - 切换前置/后置摄像头
 * - 打开/关闭麦克风
 * - 打开/关闭摄像头
 * - 切换听筒/扬声器
 * - 渲染远端用户的视频数据
 * - 离开房间
 * - 销毁引擎
 *
 * 实现一个基本的音视频通话的流程如下：
 * 1.创建引擎               vEngine.init();
 * 2.设置编码参数            vEngine.setVideoEncoderConfig();
 * 3.开启本地视频采集         vEngine.startVideoCapture();
 * 4.设置本地视频渲染视图      vEngine.setupLocalVideo();
 * 4.加入音视频通话房间        vEngine.joinRoom();
 * 5.在收到远端用户视频首帧之后，设置用户的视频渲染视图 vEngine.setupRemoteVideo（）
 * 6.离开音视频通话房间        vEngine.leaveRoom();
 * 7.销毁引擎         vEngine.uninit():
 
 * 有以下常见的注意事项：
 * 1.本示例中，我们在 OnFirstRemoteVideoFrameRendered 这个事件中给远端用户设置远端用户视频渲染视图，这个回调表示的是收到了远端用户的视频第一帧。当然也可以在 onUserJoined:elapsed: 回调中设置远端用户视频渲染视图
 * 2.SDK 回调不在主线程，UI 操作需要切换线程
 * 3.用户成功加入房间后，SDK 会通过 OnUserJoined 回调已经在房间的用户信息
 * 4.SDK 支持同时发布多个参数的视频流，接口是 setVideoEncoderConfig:
 * 5.加入房间时，需要有有效的 token，加入失败时会通过 onError: 输出对应的错误码
 * 6.用户可以通过vEngine.joinRoom(); 中的 roomConfig 来获得不同场景下的性能优化。本示例是音视频通话场景
 * 7.不需要在每次加入/退出房间时销毁引擎。本示例退出房间时销毁引擎是为了展示完整的使用流程
 *
 * 详细的API文档参见: https://site.bytedance.net/docs/1/6/85530/
 */
const ipcRenderer = require('electron').ipcRenderer
const remote = require('electron').remote
const { app, dialog } = require('electron')
const path = require('path')
const config = require('../config/config')

const OFFVIDEOICON = './assets/videoOffIcon.png';
const ONVIDEOICON = './assets/videoOnIcon.png';
const OFFMICICON = './assets/micOffIcon.png';
const ONMICICON = './assets/micOnIcon.png';
const TEXTMAP = {
    'idRoomId': '房间ID',
    'idUserId': '用户ID',
  };
///////////////////////////////////////////////////////////////////
$('#control').hide();
$('.player').hide();
$('#room-id-text').text('');
$('#user-id-text').text('');
checkRoomIdAndUserId('idRoomId');
checkRoomIdAndUserId('idUserId');
///////////////////////////////////////////
// Engine 需要的参数
let vEngine;
// Note: 请输入你的 appId
let appId = config.appId;
let token  = config.token;
// Note: 房间 id
let roomId = '';
// Note: 用户 id
let userId = '';

let isMicOn = false; // control the mic
let isVideoOn = false; // control the video
const MAIN_STREAM_INDEX = 0;

let remoteUsers = [];
// UI Elements
let idRoomId, idUserId;
let idJoin, idLeave;
let idOpenMicrophone;
let idOpenCamera;
let idLocalVideoContainer;
let isEngineCreated = false;
let bigSolution = { width: 1280, height: 720, fps: 15 };
let smallSolution = {width: 120, height: 120, fps: 15};

// 如果你只想发送一路音频流，可只配置一组音视频分辨率信息
let profiles = [bigSolution, smallSolution];
let roomConfig = {
    room_profile_type: 1,
    is_auto_publish: true,
    is_auto_subscribe_audio: true,
    is_auto_subscribe_video: true
};

/////////////////////////////////////////////////////////////////////////
// Callback
// 有人加入音视频会议
const userJoined_handler = (userId, elapsed) => {
  remoteUsers.push({ userId });
};
// 有人离开音视频会议
const userOffline_handler = (userId, reason) => {
    const remoteUserId = userId
    if (remoteUserId === idUserId) {
      $('#idLocalVideoContainer').hide();
      $('#local-player-name').text('');
    }
    $(`#player-wrapper-${remoteUserId}`).remove();
    remoteUsers = remoteUsers.filter((ele) => {
      return !ele.userId === userId;
    });
};
// 收到远端用户视频第一帧
const firstRemoteVideoFrame_handler = (key, info) => {

  const userId = key.user_id
  const remoteUserId="player-wrapper-"+key.user_id
  let stream_index = key.stream_index;
  const currentLength = $('.player-wrapper').length;
  // Player doms are created when there are no more than four in a room
  if (currentLength < 4) {
    const player = $(`
    <div id="player-wrapper-${userId}" class="player-wrapper re-player">
      <p class="player-name">${userId}</p>
    </div>
  `);
    $('#player-list').append(player);
  }
  if (stream_index == 0) {
    ///解绑指定远端视频流已绑定的本地视图
    vEngine.removeRemoteVideo(key.user_id);  
    ///设置远端用户视频渲染视图  
    vEngine.setupRemoteVideo(key.user_id,document.getElementById(remoteUserId),1);
  } 
    
};

///收到sdk危险警告回调
const warning_handler = (warn) => {
};
///收到sdk报错回调
const error_handler = (error) => {
};
vEngine = new window.veRTCEngine();
///初始化RTC引擎
createEngine();

document.getElementById('header-version').innerHTML = 'VolcEngingRTC ' + window.veRTCEngine.getSDKVersion() 
        + ' DebugProcessId ' + window.veRTCEngine.getCurrentProcessId();

// 检查输入是否合法
function checkRoomIdAndUserId(name) {
  $(`#${name}`).keyup(() => {
    checkReg(name)
  });
}

function checkReg(name){
    const inputValue = $(`#${name}`).val();
    let hasError = false;
    if (!inputValue) {
      $(`#${name}`).css('border-color', '#ff4d4f');
      $(`#${name}-text`).text(`请输入${TEXTMAP[name]}`);
      hasError = true;
    } else if (!/^[0-9a-zA-Z_\-@.]{1,128}$/.test(inputValue)) {
      $(`#${name}`).css('border-color', '#ff4d4f');
      $(`#${name}-text`).text(`${TEXTMAP[name]}输入有误，请重新输入`);
      hasError = true;
    } else {
      $(`#${name}-text`).text('');
      $(`#${name}`).css('border-color', '#d9d9d9');
      hasError = false;
    }
    return hasError
}

/////////////////////////////////////////////////////////////////////////
// Callback Function
function initEventListeners() {
  ///监听用户加入音视频房间回调
  vEngine.on('OnUserJoined', userJoined_handler);
  ///监听用户离开音视频房间回调
  vEngine.on('OnUserLeave', userOffline_handler);
  ///监听远端用户视频第一帧回调
  vEngine.on('OnFirstRemoteVideoFrameRendered', firstRemoteVideoFrame_handler);
  ///监听RTC警告
  vEngine.on('OnWarning', warning_handler);
  ///监听RTC报错
  vEngine.on('OnError', error_handler);
}

function createEngine() {
    console.log('create engine')
    if (!vEngine) {
        vEngine = new window.veRTCEngine();
    }
    ///初始化引擎
    vEngine.init(appId, '', JSON.stringify(""));    
    initEventListeners();
    isEngineCreated = true;
    onBtnOpenCamera();
    onBtnOpenMicrophone();
}

function destoryEngine() {
    if (vEngine) {
      ///销毁RTC引擎
      vEngine.uninit()
      vEngine = null;
    }
    isEngineCreated = false;
}

function onBtnJoin() {

    if(checkReg('idRoomId') || checkReg('idUserId')){
        return
    }
    roomId = idRoomId.value;
    userId = idUserId.value;
    $('#control').show();
    $('.player').show();
    $('#pannel').hide();
    $('#header-version').text(`${roomId}`);
    $('#local-player-name').text(`${userId}`);

    if (!isEngineCreated || vEngine == null) {
        createEngine();
    }
    vEngine.setVideoEncoderConfig(MAIN_STREAM_INDEX, profiles);
    // 设置本地视频渲染 view
    vEngine.setupLocalVideo(idLocalVideoContainer);
    ///加入音视频房间
    let ret = vEngine.joinRoom(token, roomId, userId, "", roomConfig);
    console.log('join room ret : ' + ret);
}

function onBtnLeave() {
    ///离开音视频房间
    vEngine.leaveRoom();
    $('#control').hide();
    $('.player').hide();
    $('#pannel').show();
    document.getElementById('header-version').innerHTML = 'VolcEngingRTC ' + window.veRTCEngine.getSDKVersion() 
        + ' DebugProcessId ' + window.veRTCEngine.getCurrentProcessId();
}

function onBtnOpenMicrophone() {
  isMicOn = !isMicOn;
  if(isMicOn) {
    ///开启本地音频采集
    vEngine.startAudioCapture()
  $(`#idOpenMicrophone img`).attr('src', `${ONMICICON}`);
  }else {
    ///关闭本地音频采集
    vEngine.stopAudioCapture();
    $(`#idOpenMicrophone img`).attr('src', `${OFFMICICON}`);
  }
}

function onBtnOpenCamera() {
  isVideoOn = !isVideoOn;
  if(isVideoOn) {
    ///开启本地视频采集
    vEngine.startVideoCapture();
    $(`#idOpenCamera img`).attr('src', `${ONVIDEOICON}`);
  }else {
    ///关闭本地视频采集
    vEngine.stopVideoCapture();
    $(`#idOpenCamera img`).attr('src', `${OFFVIDEOICON}`);
  }
}

window.onload = () => {
    idRoomId = document.getElementById('idRoomId');
    idUserId = document.getElementById('idUserId');
    idJoin = document.getElementById('idJoin');
    idLeave = document.getElementById('idLeave');
    idOpenMicrophone = document.getElementById('idOpenMicrophone');
    idOpenCamera = document.getElementById('idOpenCamera');
    idLocalVideoContainer = document.getElementById('idLocalVideoContainer');

    idJoin.addEventListener('click', onBtnJoin);
    idLeave.addEventListener('click', onBtnLeave);
    idOpenMicrophone.addEventListener('click', onBtnOpenMicrophone);
    idOpenCamera.addEventListener('click', onBtnOpenCamera);
};