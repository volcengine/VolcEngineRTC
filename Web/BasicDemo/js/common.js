'use strict';

const OFFVIDEOICON = './assets/videoOffIcon.png';
const ONVIDEOICON = './assets/videoOnIcon.png';
const OFFMICICON = './assets/micOffIcon.png';
const ONMICICON = './assets/micOnIcon.png';

const TEXTMAP = {
  'room-id': '房间ID',
  'user-id': '用户ID',
};
let isMicOn = false; // control the mic
let isVideoOn = false; // control the video
/*
 * On initiation. `engine` is not attached to any project or room for any specific user.
 */
const config = {
  appId: 'YourAppId',
  token: {
    YourUserId: 'YourToken',
  },
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
