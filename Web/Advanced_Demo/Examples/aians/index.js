/**
 * @module AI-ans
 * @param {appid}: Your AppID
 * @param {appKey}: Your AppKey
 */
const appid = 'your_appid';
const appKey = 'your_appkey';

if (!appid) alert("请先获取 AppID");
if (!appKey) alert("请先获取 AppKey");

const engine = VERTC.createEngine(appid);

// enable aians plugin
const { EffectBeautyMode, RTCBeautyExtension, RTCAinrExtension } =
  window.VERTCExtensions;
const AIAnsExtension = new RTCAinrExtension();

let registryExtension = false;

// registry global message
const message = new Message();

// registry ainr plugin
async function registerAIAnsExtension() {
  try {
    await engine.registerExtension(AIAnsExtension);
    registryExtension = true;
    $("#aians").change(async function (e) {
      if (this.checked) {
        // 开启降噪
        AIAnsExtension.enable();
      } else {
        // 关闭降噪;
        AIAnsExtension.disable();
      }
    });
  } catch (e) {
    $("#aians").prop("disabled", true);
    message.error("注册失败:当前浏览器不支持AI降噪");
    $("#aiansSwitch").on("click", function () {
      if (!registryExtension) {
        message.error("当前浏览器不支持AI降噪");
      }
    });
    return;
  }
}

registerAIAnsExtension();

// enable vertc audio property report
engine.enableAudioPropertiesReport({
  interval: 1000,
});

// tip text map
const TEXTMAP = {
  roomId: "房间 ID",
  userId: "用户 ID",
};

// default device permission
let devicePermissions = {
  video: true,
  audio: true,
};

// save roomId and userId
const JoinRoomConfig = {
  roomId: "",
  userId: "",
};

// devices status
let audioInputs = [];
let videoInputs = [];
let selectedMic = "";
let selectedCamera = "";
let micStatus = true;
let cameraStatus = true;

// save remote audio info
let remoteAudioUsers = [];

let autoPlayFailUser = [];
// stream play status
let playStatus = {};
let roomUsers = [];

const { hasLogin, _roomId, _uid, scene } = checkLoginInfo();

const isRefresh = hasLogin && scene === "aians";
if (isRefresh) {
  $(".loading").removeClass("hidden");
}

/**
 * get media devices
 * @returns
 */
async function getDevices() {
  const devices = await VERTC.enumerateDevices();
  return {
    audioInputs: devices.filter((i) => i.deviceId && i.kind === "audioinput"),
    videoInputs: devices.filter((i) => i.deviceId && i.kind === "videoinput"),
  };
}

/**
 *  when document ready, get device permission and start capture stream
 *  and get default roomId and userId from url query
 */
$(document).ready(async function () {
  const devices = await getDevices();

  devicePermissions = {
    video: (devices.videoInputs || []).length > 0,
    audio: (devices.audioInputs || []).length > 0,
  };

  if (devicePermissions.audio) {
    audioInputs = devices.audioInputs;
    // mic options
    const audioOptions = audioInputs.map((device) => {
      return `<li class='device-item' label='${device.deviceId}'>${device.label}</li>`;
    });
    $(".device-list.micList").append(...audioOptions);
    $("#selectedmic").val(audioInputs?.[0]?.label || "");
    selectedMic = audioInputs?.[0]?.deviceId || "";

    await engine.setAudioCaptureDevice(selectedMic);
    if (devicePermissions.audio) {
      await engine.startAudioCapture();
    }
  } else {
    micStatus = false;
    $("#mic-icon").attr(
      "src",
      `https://lf-cdn-tos.bytescm.com/obj/static/web_advance/images/micOff.svg`
    );
    $("#selectedmic").attr("disabled", "disabled");
  }

  if (devicePermissions.video) {
    videoInputs = devices.videoInputs;

    // camera options
    const videoOptions = videoInputs.map((device) => {
      return `<li class='device-item' label='${device.deviceId}'>${device.label}</li>`;
    });
    $(".device-list.cameraList").append(...videoOptions);
    $("#selectedcamera").val(videoInputs?.[0]?.label || "");

    selectedCamera = videoInputs?.[0]?.deviceId || "";

    await engine.setVideoCaptureDevice(selectedCamera);

    if (devicePermissions.video) {
      await engine.startVideoCapture();
      engine.setLocalVideoPlayer(0 /*StreamIndex.STREAM_INDEX_MAIN*/, {
        renderDom: "preview-player",
        renderMode: 1,
      });
    }
  } else {
    cameraStatus = false;
    $("#camera-icon").attr(
      "src",
      `https://lf-cdn-tos.bytescm.com/obj/static/web_advance/images/cameraOff.svg`
    );
    $("#selectedcamera").attr("disabled", "disabled");
  }

  // if refresh, auto join room
  if (isRefresh) {
    JoinRoomConfig.roomId = _roomId;
    JoinRoomConfig.userId = _uid;
    joinRoom();
  } else {
    // get default roomId and userId from url query
    const urlParams = new URL(location.href).searchParams;
    JoinRoomConfig.roomId = urlParams.get("roomId");
    JoinRoomConfig.userId = urlParams.get("userId");

    $("#roomId").val(JoinRoomConfig.roomId);
    $("#userId").val(JoinRoomConfig.userId);
  }

  registerHideDropDown();
});

// change camera ,show dropdown
$("#selectedcamera").on("click", (e) => {
  e.stopPropagation();
  $(".cameraList").css("display", "block");
});

// change mic ,show dropdown
$("#selectedmic").on("click", (e) => {
  e.stopPropagation();

  $(".micList").css("display", "block");
});

//  select other mic device, hide dropdown
$(".micList").delegate("li", "click", function (e) {
  setDevice(this.getAttribute("label"), "mic");
});

//  select other camera device, hide dropdown
$(".cameraList").delegate("li", "click", function (e) {
  setDevice(this.getAttribute("label"), "camera");
});

/**
 * turn on or turn off mic
 */
$("#mic-btn").on("click", (e) => {
  if (!devicePermissions.audio) {
    message.error("没有麦克风权限！");
    return;
  }

  if (micStatus) {
    micStatus = false;
    engine.stopAudioCapture();
    $("#mic-icon").attr(
      "src",
      `https://lf-cdn-tos.bytescm.com/obj/static/web_advance/images/micOff.svg`
    );
  } else {
    micStatus = true;
    engine.startAudioCapture();
    $("#mic-icon").attr(
      "src",
      `https://lf-cdn-tos.bytescm.com/obj/static/web_advance/images/micOn.svg`
    );
  }
});

/**
 * turn on or turn off camera
 */
$("#camera-btn").on("click", () => {
  if (!devicePermissions.video) {
    message.error("没有摄像头权限！");
    return;
  }

  if (cameraStatus) {
    cameraStatus = false;
    engine.stopVideoCapture();
    $("#camera-icon").attr(
      "src",
      `https://lf-cdn-tos.bytescm.com/obj/static/web_advance/images/cameraOff.svg`
    );
  } else {
    cameraStatus = true;
    engine.startVideoCapture();
    $("#camera-icon").attr(
      "src",
      `https://lf-cdn-tos.bytescm.com/obj/static/web_advance/images/cameraOn.svg`
    );
  }
});

/**
 * update new selected device label ui
 * @param {设备id} deviceId
 * @param {设备类型} deviceType
 */
async function setDevice(deviceId, deviceType) {
  if (deviceType === "camera") {
    const device = findDevice(videoInputs, deviceId);
    selectedCamera = deviceId;
    // await engine.setAudioCaptureDevice(selectedMic)
    await engine.setVideoCaptureDevice(selectedCamera);
    $("#selectedcamera").val(device.label || "");
  }
  if (deviceType === "mic") {
    const device = findDevice(audioInputs, deviceId);
    selectedMic = deviceId;
    await engine.setAudioCaptureDevice(selectedMic);

    $("#selectedmic").val(device.label || "");
  }
}

/**
 * get selected deviceId
 * @param {*} inputs
 * @param {*} deviceId
 * @returns
 */
function findDevice(inputs, deviceId) {
  const device = inputs.find((i) => i.deviceId === deviceId);
  return device;
}

/**
 * registry global click event to hide device list dropdown
 */
function registerHideDropDown() {
  $("body").on("click", (e) => {
    if (!$.contains($(".cameraList"), e.target)) {
      $(".cameraList").css("display", "none");
    }

    if (!$.contains($(".micList"), e.target)) {
      $(".micList").css("display", "none");
    }
  });
}

/**
 * check joinroom field
 * @param {field} name
 * @returns
 */
function checkReg(name) {
  const inputValue = $(`#${name}`).val();
  let pass = false;
  if (!inputValue) {
    $(`#${name}`).css("border-color", "#ff4d4f");
    $(`.${name}-text`).text(`请输入 ${TEXTMAP[name]}`);
  } else if (inputValue.length > 128) {
    $(`#${name}`).css("border-color", "#ff4d4f");
    $(`.${name}-text`).text(`请输入小于128位的 ${TEXTMAP[name]}`);
    pass = false;
  } else if (!/^[0-9a-zA-Z_\-@.]{1,128}$/.test(inputValue)) {
    $(`#${name}`).css("border-color", "#ff4d4f");
    $(`.${name}-text`).text(`${TEXTMAP[name]} 输入有误，请重新输入`);
    pass = false;
  } else {
    $(`.${name}-text`).text("");
    $(`#${name}`).css("border-color", "#d9d9d9");
    JoinRoomConfig[name] = inputValue;
    pass = true;
  }

  return pass;
}

// Auto play. If browser reject auto play, it will trigger autoplayfailed event
const modal = document.querySelector(".modal");
const overlay = document.querySelector(".overlay");
const autoPlayBtn = document.querySelector(".autoPlayBtn");

const closeModal = function () {
  modal.classList.add("hidden");
  overlay.classList.add("hidden");
};

autoPlayBtn.addEventListener("click", function () {
  closeModal();
  handleAutoPlay();
});

const openModal = function () {
  modal.classList.remove("hidden");
  overlay.classList.remove("hidden");
};

/**
 *  registry sdk event
 */
function registerEvents() {
  engine.on(VERTC.events.onUserPublishStream, handleUserPublishStream);
  engine.on(VERTC.events.onUserUnpublishStream, handleUserUnpublishStream);
  engine.on(VERTC.events.onUserStartVideoCapture, handleUserStartVideoCapture);
  engine.on(VERTC.events.onUserStopVideoCapture, handleUserStopVideoCapture);
  engine.on(VERTC.events.onUserStartAudioCapture, handleUserStartAudioCapture);
  engine.on(VERTC.events.onUserStopAudioCapture, handleUserStopAudioCapture);
  engine.on(VERTC.events.onUserJoined, handleUserJoin);
  engine.on(VERTC.events.onUserLeave, handleUserLeave);
  engine.on(VERTC.events.onLocalAudioPropertiesReport, handleLocalAudioReport);
  engine.on(
    VERTC.events.onRemoteAudioPropertiesReport,
    handleRemoteAudioReport
  );

  engine.on(VERTC.events.onError, handleEventError);
  // 处理自动播放失败
  engine.on(VERTC.events.onAutoplayFailed, handleAutoPlayFail);
  engine.on(VERTC.events.onPlayerEvent, handlePlayerEvent);
}

/**
 *  remove sdk event
 */
function removeEvents() {
  engine.off(VERTC.events.onUserPublishStream, handleUserPublishStream);
  engine.off(VERTC.events.onUserUnpublishStream, handleUserUnpublishStream);
  engine.off(VERTC.events.onUserStartVideoCapture, handleUserStartVideoCapture);
  engine.off(VERTC.events.onUserStopVideoCapture, handleUserStopVideoCapture);
  engine.off(VERTC.events.onUserStartAudioCapture, handleUserStartAudioCapture);
  engine.off(VERTC.events.onUserStopAudioCapture, handleUserStopAudioCapture);
  engine.off(VERTC.events.onUserJoined, handleUserJoin);
  engine.off(VERTC.events.onUserLeave, handleUserLeave);
  engine.off(VERTC.events.onLocalAudioPropertiesReport, handleLocalAudioReport);
  engine.off(
    VERTC.events.onRemoteAudioPropertiesReport,
    handleRemoteAudioReport
  );

  engine.off(VERTC.events.onError, handleEventError);
  // 处理自动播放失败
  engine.off(VERTC.events.onAutoplayFailed, handleAutoPlayFail);
  engine.off(VERTC.events.onPlayerEvent, handlePlayerEvent);
}

registerEvents();

// stop stream and leave rtc room when page hide
window.addEventListener("pagehide", function (event) {
  removeEvents();
  engine.stopVideoCapture();
  engine.stopAudioCapture();
  engine.unpublishStream(VERTC.MediaType.AUDIO);
  engine.leaveRoom();
});

/**
 * leve room
 */
async function leaveRoom() {
  $("#joinRoom").css("display", "block");
  $("#example").css("display", "none");
  $(".players-wrapper").empty();
  await engine.setLocalVideoPlayer(0, {
    renderMode: 1,
    renderDom: undefined,
  });
  await engine.setLocalVideoPlayer(0, {
    renderMode: 1,
    renderDom: "preview-player",
  });

  await engine.leaveRoom();
  remoteAudioUsers = [];
  autoPlayFailUser = [];
  playStatus = {};
  roomUsers = [];

  $("#link").val("");

  $("#aians").prop("checked", false);
  AIAnsExtension.disable();
  window.parent.ExampleState && (window.parent.ExampleState.joinRoom = false);
}

/**
 * handle local audio info
 * @param {本端音频信息} event
 * @returns
 */
function handleLocalAudioReport(event) {
  const localAudioInfo = event.find(
    (audioInfo) => audioInfo.streamIndex === VERTC.StreamIndex.STREAM_INDEX_MAIN
  );

  if (!localAudioInfo) {
    return;
  }

  const { audioPropertiesInfo } = localAudioInfo;
  // update ui
  if (Number(audioPropertiesInfo.linearVolume) > 0) {
    $(`#local-${JoinRoomConfig.userId}`)
      .children(".userinfo")
      .children("img")
      .attr(
        "src",
        `https://lf-cdn-tos.bytescm.com/obj/static/web_advance/images/micVolume.svg`
      );
    $(`#local-${JoinRoomConfig.userId}`).addClass("active");
  } else {
    $(`#local-${JoinRoomConfig.userId}`)
      .children(".userinfo")
      .children("img")
      .attr(
        "src",
        `https://lf-cdn-tos.bytescm.com/obj/static/web_advance/images/micOn.svg`
      );
    $(`#local-${JoinRoomConfig.userId}`).removeClass("active");
  }
}

/**
 * handle remote audio info
 * @param {远端音频信息} event
 * @returns
 */
function handleRemoteAudioReport(audioInfos) {
  audioInfos.forEach((info) => {
    const {
      audioPropertiesInfo,
      streamKey: { streamIndex, userId },
    } = info;

    if (streamIndex === VERTC.StreamIndex.STREAM_INDEX_MAIN) {
      // update ui
      if (Number(audioPropertiesInfo.linearVolume) > 0) {
        $(`#remote-${userId}`)
          .children(".userinfo")
          .children("img")
          .attr(
            "src",
            `https://lf-cdn-tos.bytescm.com/obj/static/web_advance/images/micVolume.svg`
          );
        $(`#remote-${userId}`).addClass("active");
      } else {
        if (remoteAudioUsers.includes(userId)) {
          $(`#remote-${userId}`)
            .children(".userinfo")
            .children("img")
            .attr(
              "src",
              `https://lf-cdn-tos.bytescm.com/obj/static/web_advance/images/micOn.svg`
            );
          $(`#remote-${userId}`).removeClass("active");
        }
      }
    }
  });
}

/**
 * update remote user player ui
 * @param {远端媒体流} stream
 */
function handleUserPublishStream(stream) {
  const { userId, mediaType } = stream;

  if (mediaType & VERTC.MediaType.VIDEO) {
    const player = $(`#player-${userId}`);

    if (player[0]) {
      engine.setRemoteVideoPlayer(0, {
        renderDom: player[0],
        renderMode: 1,
        userId,
      });
    }
    $(`#remote-${userId}`).remove(".user-avatar");
  }

  if (mediaType & VERTC.MediaType.AUDIO) {
    $(`#remote-${userId}`)
      .children(".userinfo")
      .children("img")
      .attr(
        "src",
        `https://lf-cdn-tos.bytescm.com/obj/static/web_advance/images/micOn.svg`
      );
    remoteAudioUsers = Array.from(new Set([...remoteAudioUsers, userId]));
  }
}

/**
 * stop remote user player
 * @param {远端媒体流} stream
 */
function handleUserUnpublishStream(stream) {
  const { userId, mediaType } = stream;
  console.log("handleUserUnpublishStream", stream);

  if (mediaType & VERTC.MediaType.VIDEO) {
    engine.setRemoteVideoPlayer(0, {
      renderDom: undefined,
      renderMode: 1,
      userId,
    });
  }

  if (mediaType & VERTC.MediaType.AUDIO) {
    $(`#remote-${userId}`)
      .children(".userinfo")
      .children("img")
      .attr(
        "src",
        `https://lf-cdn-tos.bytescm.com/obj/static/web_advance/images/micOff.svg`
      );

    remoteAudioUsers = remoteAudioUsers.filter((user) => user !== userId);
    $(`#remote-${userId}`).removeClass("active");
  }
}

/**
 * remote user start video,update ui
 * @param {*} event
 */
function handleUserStartVideoCapture(event) {
  console.log("handleUserStartVideoCapture", event);
  const { userId } = event;
  const player = $(`#player-${userId}`);
  if (player[0]) {
    engine.setRemoteVideoPlayer(0, {
      renderDom: player[0],
      renderMode: 1,
      userId,
    });
    $(`#remote-${userId}`).children(".user-avatar").remove();
  }
}

/**
 * remote user stop video,update ui
 * @param {*} event
 */
function handleUserStopVideoCapture(event) {
  const { userId } = event;

  engine.setRemoteVideoPlayer(0, {
    renderMode: 1,
    userId,
    renderDom: undefined,
  });
  let avatar = `<div class='user-avatar'><span>${JoinRoomConfig.userId}</span></div>`;
  $(`#remote-${userId}`).append(avatar);
}

function handleUserStartAudioCapture(event) {
  //   const { userId } = event;
  //   console.log('handleUserStartAudioCapture', event);
  //   remoteAudioUsers = Array.from(new Set([...remoteAudioUsers, userId]));
  //   $(`#remote-${userId}`)
  //     .children('.userinfo')
  //     .children('img')
  //     .attr('src', `https://lf-cdn-tos.bytescm.com/obj/static/web_advance/images/micOn.svg`);
}

/**
 * remote user stop audio,update ui
 * @param {*} event
 */
function handleUserStopAudioCapture(event) {
  const { userId } = event;
  remoteAudioUsers = remoteAudioUsers.filter((user) => user !== userId);
  $(`#remote-${userId}`)
    .children(".userinfo")
    .children("img")
    .attr(
      "src",
      `https://lf-cdn-tos.bytescm.com/obj/static/web_advance/images/micOff.svg`
    );
  $(`#remote-${userId}`).removeClass("active");
}

/**
 * remote user join room
 * @param {*} e
 */
function handleUserJoin(e) {
  console.log("handleUserJoin", e);
  const { userInfo } = e;
  const remoteUserId = userInfo.userId;
  const currentLength = $(".players-wrapper").length;

  roomUsers.push(remoteUserId);
  // add player dom
  if (currentLength < 30) {
    const player = createPlayerDom(remoteUserId, {
      micStatus: false,
      cameraStatus: false,
    });
    $(".players-wrapper").append(player);
  }
}
/**
 * remote user leave room
 * @param {*} e
 */
function handleUserLeave(e) {
  console.log("handleUserLeave", e);
  const { userInfo } = e;
  const remoteUserId = userInfo.userId;
  roomUsers = roomUsers.filter((uid) => uid !== remoteUserId);
  $(`#remote-${remoteUserId}`).remove();

  checkAutoPlayFailUser(remoteUserId);
}

// handle errors
async function handleEventError(e) {
  console.error("handleEventError", e);
  if (e.errorCode === VERTC.ErrorCode.DUPLICATE_LOGIN) {
    leaveRoom();
    alert("你的id被其他人顶下线了");
    closeModal();
  }
}

/**
 * handle autoplay fail
 * @param {*} event
 */
function handleAutoPlayFail(event) {
  console.log("handleAutoPlayFail", event);

  const { userId, kind } = event;

  let playUser = playStatus[userId] || {};
  playStatus[userId] = { ...playUser, [kind]: false };

  addFailUser(event.userId);
  //引导用户进行交互
  openModal();
}

// save autoplay failed user
function addFailUser(userId) {
  const index = autoPlayFailUser.findIndex((item) => item === userId);
  if (index === -1) {
    autoPlayFailUser.push(userId);
  }
}

/**
 * handle player event. when play or play failed ,update ui
 * @param {*} event
 */
function handlePlayerEvent(event) {
  const { userId, rawEvent, type } = event;
  const playUser = playStatus[userId] || {};
  if (rawEvent.type === "playing") {
    playStatus[userId] = { ...playUser, [type]: true };
    const { audio, video } = playStatus[userId];
    if (audio !== false && video !== false) {
      checkAutoPlayFailUser(userId);
    }
  } else if (rawEvent.type === "pause") {
    playerFail({ userId, type });
  }
}

function playerFail(params) {
  const { type, userId } = params;

  const playUser = playStatus[userId] || {};
  playStatus[userId] = { ...playUser, [type]: false };
  const { audio, video } = playStatus[userId];

  if (audio === false || video === false) {
    addFailUser(userId);
  }
}

// when autoplay user update, check to close 'play' modal
function checkAutoPlayFailUser(userId) {
  autoPlayFailUser = autoPlayFailUser.filter((item) => item !== userId);

  if (autoPlayFailUser.length === 0) {
    closeModal();
  }
}

// Guide users to click and play actively
function handleAutoPlay() {
  if (autoPlayFailUser.length) {
    autoPlayFailUser.forEach((user) => {
      engine.play(user);
    });
  }
  autoPlayFailUser = [];
}

/**
 * create video player, update ui
 * @param {*} userId
 * @param {*} options
 * @returns
 */
function createPlayerDom(userId, options) {
  const { micStatus = true, cameraStatus = true, isScreen = false } = options;
  const isLocal = userId === JoinRoomConfig.userId;

  let playerDom = `
	<div class="room-player-wrapper" id="${isLocal ? "local" : "remote"}-${userId}">
	  <div id="player-${userId}" class="player"></div>
	  <p class="userinfo">
	 	<img src="https://lf-cdn-tos.bytescm.com/obj/static/web_advance/images/${
      micStatus ? "micOn" : "micOff"
    }.svg" /> 
		<span>${isLocal ? "本端用户" : "远端用户"}</span>
		<span>${userId}</span>
	  </p>
	  userAvatar
	</div>
  `;

  if (!cameraStatus) {
    playerDom = playerDom.replace(
      "userAvatar",
      `<div class='user-avatar'><span>${userId}</span></div>`
    );
  } else {
    playerDom = playerDom.replace("userAvatar", "");
  }

  return playerDom;
}

let joining = false;

/**
 * click joinRoom button
 */
$(".join-btn").on("click", async (e) => {
  const checkRoomId = checkReg("roomId");
  const checkUserId = checkReg("userId");
  if (checkRoomId && checkUserId) {
    if (!joining) {
      joinRoom();
      joining = true;
    }
  }
});

// rtc join room  and update room ui
async function joinRoom() {
  let token;
  try {
    const res = await fetch(
      `https://demo.volcvideo.com/exampleCenter/openApi/getTokenByAppId?appID=${appid}&roomID=${JoinRoomConfig.roomId}&userID=${JoinRoomConfig.userId}&appKey=${appKey}`
    );

    const result = await res.json();

    token = result.Result;
  } catch (e) {
    alert("get token error");
  }
  $("#joinRoom").css("display", "none");
  $("#example").css("display", "block");
  $(".loading").addClass("hidden");
  $(".info-value.roomId").text(JoinRoomConfig.roomId);
  $(".info-value.userId").text(JoinRoomConfig.userId);

  let playerDom = createPlayerDom(JoinRoomConfig.userId, {
    micStatus,
    cameraStatus,
  });

  const localPlayer = $(playerDom);

  $(".players-wrapper").append(localPlayer);
  await engine.setLocalVideoPlayer(0, {
    renderMode: 1,
    renderDom: undefined,
  });
  await engine.setLocalVideoPlayer(0, {
    renderMode: 1,
    renderDom: `player-${JoinRoomConfig.userId}`,
  });

  await engine.joinRoom(
    token,
    JoinRoomConfig.roomId,
    {
      userId: JoinRoomConfig.userId,
    },
    {
      isAutoPublish: false,
      isAutoSubscribeAudio: true,
      isAutoSubscribeVideo: true,
    }
  );

  // if capture audio, publish
  if (micStatus) {
    engine.publishStream(VERTC.MediaType.AUDIO);
  }

  // if capture video, publish
  if (cameraStatus) {
    engine.publishStream(VERTC.MediaType.VIDEO);
  }

  joining = false;
  setSessionInfo({
    roomId: JoinRoomConfig.roomId,
    uid: JoinRoomConfig.userId,
    scene: "aians",
  });

  window.parent.ExampleState.joinRoom = true;
}

/**
 * click leave room button
 */
$("#leave-room").on("click", async (e) => {
  leaveRoom();
  removeLoginInfo();
});

/**
 * share room url
 */
$("#share-room").on("click", async (e) => {
  const pathname = window.parent.location.pathname.startsWith("/rtc/advance")
    ? "/rtc/advance"
    : "";

  navigator.clipboard.writeText(
    `${location.origin}${pathname}/aians?roomId=${JoinRoomConfig.roomId}`
  );
  message.success("房间链接复制成功！");
});
