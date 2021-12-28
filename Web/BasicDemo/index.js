'use strict';
/*
 *  These procedures use RTC SDK for Web to enable local and remote
 *  users to join and leave a room managed by RTC Platform.
 */
const client = VRTC.createClient({});
const OFFVIDEOICON = './assets/videoOffIcon.png';
const ONVIDEOICON = './assets/videoOnIcon.png';
const OFFMICICON = './assets/micOffIcon.png';
const ONMICICON = './assets/micOnIcon.png';
const SDKVERSION = 'RTC版本 v3.21.0';
const TEXTMAP = {
  'room-id': '房间ID',
  'user-id': '用户ID',
};
let localStream;
let isMicOn = false; // control the mic
let isVideoOn = false; // control the video
/*
 * On initiation. `client` is not attached to any project or room for any specific user.
 */
const config = {
  appId: '',
  roomId: '',
  token: '',
};

/**
 * On initiation. `client` will use the object to config the stream.
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
 * On initiation. `client` will use the object to config the stream.
 */
const streamOptions = {
  audio: true,
  video: true,
};

/**
 * hide the voice and mic control pannel
 */

$('#control').hide();
$('#room-id-text').text('');
$('#user-id-text').text('');
$('#header-version').text(`${SDKVERSION}`);
checkRoomIdAndUserId('room-id');
checkRoomIdAndUserId('user-id');

function checkRoomIdAndUserId(name) {
  $(`#${name}`).keyup(() => {
    const inputValue = $(`#${name}`).val();
    if (!inputValue) {
      $(`#${name}`).css('border-color', '#ff4d4f');
      $(`#${name}-text`).text(`请输入${TEXTMAP[name]}`);
    } else if (!/^[0-9a-zA-Z_\-@.]{1,128}$/.test(inputValue)) {
      $(`#${name}`).css('border-color', '#ff4d4f');
      $(`#${name}-text`).text(`${TEXTMAP[name]}输入有误，请重新输入`);
    } else {
      $(`#${name}-text`).text('');
      $(`#${name}`).css('border-color', '#d9d9d9');
    }
  });
}
/*
 * When a user clicks Join or Leave in the HTML form, this procedure gathers the information
 * entered in the form and calls join asynchronously. The UI is updated to match the options entered
 * by the user.
 */
$('#submit').on('click', async () => {
  config.roomId = $('#room-id').val();
  config.uid = $('#user-id').val();
  $('#control').show();
  $('#pannel').hide();
  try {
    await join();
    $('#header-version').text(`${config.roomId}`);
    $('#local-player').show();
    $('#local-player-name').text(`${config.uid}`);
    createLocalStream((stream) => {
      stream.play('local-player', { fit: 'cover' });
    });
  } catch (err) {
    $('#control').hide();
    $('#pannel').show();
  }
});

/**
 * click change the state of mic
 */
$('#control-mic').click(() => {
  actionChangeMicState();
});

/**
 * click change the state of video
 */
$('#control-video').click(() => {
  actionChangeVideoState();
});

/*
 * Called when a user clicks Leave in order to exit a room.
 */
$('#leave').click(() => {
  actionToLeave();
});

/**
 * When you reload page you can make leave action and keep the next load is fine
 */
$(window).on('beforeunload unload', () => {
  actionToLeave();
});

/*---------------------- action handler start --------------------*/
/**
 * change the micro state
 */
const actionChangeMicState = () => {
  if (localStream) {
    !isMicOn ? localStream.muteAudio() : localStream.unmuteAudio();
    isMicOn = !isMicOn;
    // toggle the mic icon url
    changeMicOrVideoIconUrl('mic', isMicOn, OFFMICICON, ONMICICON);
  }
};
/**
 * change the video state
 */
const actionChangeVideoState = () => {
  if (localStream) {
    !isVideoOn ? localStream.muteVideo() : localStream.unmuteVideo();
    isVideoOn = !isVideoOn;
    // toggle the video icon url
    changeMicOrVideoIconUrl('video', isVideoOn, OFFVIDEOICON, ONVIDEOICON);
  }
};

/*
 * leave the room and clear the wrapper dom of `client` and info
 */
const actionToLeave = () => {
  // leave the room
  client.unpublish(localStream);
  client.leave();
  // off the event
  removeEventListener();
  $('#header-version').text(`${SDKVERSION}`);
  $('.re-player').remove();
  // clear the dom
  $('#user-id').val('');
  $('#room-id').val('');
  $('#control').hide();
  $('#pannel').show();
};
/*---------------------- action handler end --------------------*/

/*------------------------- common handler start ----------------*/

/**
 * @param {function} callback
 */
const createClient = (callback) => {
  // Add some listeners to get some messages when remote user publishes.
  client.on('stream-added', handleStreamAdd);
  client.on('stream-subscribed', handleStreamSubscribed);
  client.on('stream-removed', handleStreamRemove);
  client.init(config.appId, () => callback(client));
};

// check permission of browser
const checkPermission = () => {
  const checkAudio = new Promise((resolve) => {
    VRTC.checkAudioPermission(
      () => resolve({ audio: true }),
      () => resolve({ audio: false })
    );
  });
  const checkVideo = new Promise((resolve) => {
    VRTC.checkVideoPermission(
      () => resolve({ video: true }),
      () => resolve({ video: false })
    );
  });
  return Promise.all([checkAudio, checkVideo]);
};
/**
 * get the devices
 * @returns
 */
const getDevices = () => {
  return new Promise((resolve, reject) => {
    VRTC.getDevices(
      (inputs) => {
        let audioInputs = inputs.filter((input) => {
          return input.kind === 'audioinput';
        });
        let videoInputs = inputs.filter((input) => {
          return input.kind === 'videoinput';
        });
        resolve({
          audioInputs,
          videoInputs,
        });
      },
      (err) => {
        reject(`get devices error at ${err.message}`);
      }
    );
  });
};
/**
 * create the local stream with the config and publish the local stream
 * @param {*} callback
 */
const createLocalStream = async (callback) => {
  const res = await checkPermission();
  const devices = await getDevices();
  if (!devices.audioInputs.length && !devices.videoInputs.length) {
    alert('设备获取失败');
    return;
  }
  const params = Object.assign({}, res?.[0], res?.[1]);
  localStream = VRTC.createStream({
    ...streamOptions,
    ...params,
    microphoneId: devices.audioInputs[0]?.deviceId,
    cameraId: devices.videoInputs[0]?.deviceId,
  });
  localStream.setVideoEncoderConfiguration(initStreamOption);
  localStream.init(() => {
    streamOptions.video ? localStream.unmuteVideo() : localStream.muteVideo();
    streamOptions.audio ? localStream.unmuteAudio() : localStream.muteAudio();
    client.publish(localStream);
    callback(localStream);
  });
};

/*
 * before join a room, you should create a room,then you can join it with `client.join(token,roomId,uid, onSuccessFunc, onFailFunc)`
 */
const join = () => {
  return new Promise((resolve, reject) => {
    createClient((client) => {
      client.join(
        config.token,
        config.roomId,
        config.uid,
        resolve.bind(this, client),
        reject
      );
    });
  });
};

/**
 *
 * @param {String} type video / mic
 * @param {Boolean} statusTag
 * @param {String} offIcon
 * @param {String} onIcon
 */
const changeMicOrVideoIconUrl = (type, statusTag, offIconUrl, onIconUrl) => {
  let iconSrc = statusTag ? offIconUrl : onIconUrl;
  $(`#control-${type} img`).attr('src', `${iconSrc}`);
};

/**
 * Add a user who has subscribed to the live room to the local interface.
 * @param {*} event
 */
const handleStreamAdd = (event) => {
  client.subscribe(event.stream);
};

/**
 * after into the room, create some wrap doms to wrap the players
 * @param {*} event
 */
const handleStreamSubscribed = (event) => {
  const remoteUserId = event.stream.uid;
  const currentLength = $('.player-wrapper').length;
  // Player doms are created when there are no more than four in a room
  if (currentLength < 4) {
    const player = $(`
    <div id="player-wrapper-${remoteUserId}" class="player-wrapper re-player">
      <p class="player-name">${remoteUserId}</p>
      <div id="player-${remoteUserId}" class="remote-player"></div>
    </div>
  `);
    $('#player-list').append(player);
    event.stream.play(`player-${remoteUserId}`, { fit: 'cover' });
  }
};
/**
 * Remove the user specified from the room in the local and clear the unused dom
 * @param {*} event
 */
const handleStreamRemove = (event) => {
  const remoteUserId = event.stream.uid;
  if (remoteUserId === config.uid) {
    $('#local-player').hide();
    $('#local-player-name').text('');
  }
  $(`#player-wrapper-${remoteUserId}`).remove();
};
/**
 * remove the listeners when `createClient`
 */
const removeEventListener = () => {
  client.off('stream-added', handleStreamAdd);
  client.off('stream-subscribed', handleStreamSubscribed);
  client.off('stream-removed', handleStreamRemove);
};
/*------------------------- common handler end ----------------*/
