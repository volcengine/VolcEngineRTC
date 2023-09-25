'use strict';

const OFFVIDEOICON = './assets/videoOffIcon.png';
const ONVIDEOICON = './assets/videoOnIcon.png';
const OFFMICICON = './assets/micOffIcon.png';
const ONMICICON = './assets/micOnIcon.png';

const TEXTMAP = {
  'room-id': '房间ID',
  'user-id': '用户ID',
};
let isMicOn = true; // control the mic
let isVideoOn = true; // control the video
/*
 * On initiation. `engine` is not attached to any project or room for any specific user.
 */
const config = {
  appId: 'yourAppId',
  roomId: 'yourRoomId',
  tokens: [
    {
      userId: 'yourUserId1',
      token: 'yourToken1',
    },
    {
      userId: 'yourUserId2',
      token: 'yourToken2',
    }
  ],
};

/**
 * On initiation. `engine` will use the object to config the stream.
 */
const initStreamOption = {
  resolution: {
    width: 640,
    height: 480,
  },
  frameRate: {
    min: 10,
    max: 15,
  },
  bitrate: {
    min: 250,
    max: 600,
  },
};

/**
 * On initiation. `engine` will use the object to config the stream.
 */
const streamOptions = {
  audio: true,
  video: true,
};

function checkReg(name) {
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
  return hasError;
}

function checkRoomIdAndUserId(name) {
  $(`#${name}`).keyup(() => {
    checkReg(name);
  });
}

function getUrlArgs() {
  var args = {};
  var query = window.location.search.substring(1);
  var pairs = query.split('&');
  for (var i = 0; i < pairs.length; i++) {
    var pos = pairs[i].indexOf('=');
    if (pos == -1) continue;
    var name = pairs[i].substring(0, pos);
    var value = pairs[i].substring(pos + 1);
    value = decodeURIComponent(value);
    args[name] = value;
  }
  return args;
}

function changeUrl(roomId) {
  const baseUrl = `${window.location.origin}?roomId=${roomId}`;
  window.history.replaceState('', '', baseUrl);
}

function setSessionInfo(params) {
  Object.keys(params).forEach((key) => {
    sessionStorage.setItem(key, params[key]);
  });
}

function removeLoginInfo() {
  const variable = ['roomId', 'uid'];
  variable.forEach((v) => sessionStorage.removeItem(v));
}

function getSessionInfo() {
  const roomId = sessionStorage.getItem('roomId');
  const uid = sessionStorage.getItem('uid');
  return {
    roomId,
    uid,
  };
}

function checkLoginInfo() {
  const { roomId } = getUrlArgs();
  roomId && setSessionInfo({ roomId });

  const _roomId = roomId;
  const _uid = sessionStorage.getItem('uid');

  let hasLogin = true;
  if (!_roomId || !_uid) {
    hasLogin = false;
  } else if (
    !/^[0-9a-zA-Z_\-@.]{1,128}$/.test(_roomId) ||
    !/^[0-9a-zA-Z_\-@.]{1,128}$/.test(_uid)
  ) {
    hasLogin = false;
  }
  return hasLogin;
}

function fillRoomId() {
  $('#room-id').val(config.roomId);
}
