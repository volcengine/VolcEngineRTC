/**
 * @module Beauty
 * @param {appid}: Your AppID
 * @param {appKey}: Your AppKey
 * @param {auth}:  Your Auth file url
 */
const appid = 'your_appid';
const appKey = 'your_appkey';
const auth = 'xx.auth';

const engine = VERTC.createEngine(appid);

// enable beauty plugin
const { EffectBeautyMode, RTCBeautyExtension } = window.VERTCExtensions;
const BeautyExtension = new RTCBeautyExtension();

let registryExtension = false;

// registry beauty plugin
async function registerBeautyExtension() {
  if (registryExtension) {
    return;
  }
  try {
    await engine.registerExtension(BeautyExtension);
    registryExtension = true;
    BeautyExtension.disableBeauty();
  } catch (e) {
    message.error("注册失败:当前浏览器不支持美颜插件");
    $("#enableBauty").prop("disabled", true);
    $(".setting-item.beauty").css("display", "none");
    $("#enableBautySwitch").on("click", function () {
      if (!registryExtension) {
        message.error("当前浏览器不支持美颜插件");
      }
    });
    return;
  }

  $("#enableBauty").change(async function (e) {
    if (this.checked) {
      /** It's a trick to void lag because of the track changed */
      $(".setting-item.beauty").css("display", "flex");

      BeautyExtension.enableBeauty();
      handleBeautyChanges();
    } else {
      $(".setting-item.beauty").css("display", "none");
      BeautyExtension.disableBeauty();
    }
    window.parent?.onAdjustIframeStyle?.();
  });
}

let initSlider = false;

/**
 * set beauty params
 */
function handleBeautyChanges() {
  if (!registryExtension || initSlider) {
    return;
  }

  initSlider = true;
  // 美颜参数设置-美白
  slider().init(50, "#white", (val) => {
    BeautyExtension.setBeautyIntensity(
      EffectBeautyMode.EFFECT_WHITE_MODE,
      val / 100
    );
  });

  // 美颜参数设置-磨皮
  slider().init(50, "#smooth", (val) => {
    BeautyExtension.setBeautyIntensity(
      EffectBeautyMode.EFFECT_SMOOTH_MODE,
      val / 100
    );
  });

  // 美颜参数设置-锐化
  slider().init(50, "#sharpen", (val) => {
    BeautyExtension.setBeautyIntensity(
      EffectBeautyMode.EFFECT_SHARPEN_MODE,
      val / 100
    );
  });
}

registerBeautyExtension();

// registry global message
const message = new Message();

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

// devices
let audioInputs = [];
let videoInputs = [];
let selectedMic = "";
let selectedCamera = "";
let micStatus = true;
let cameraStatus = true;
// save remote audio info
let remoteAudioUsers = [];
// current user join room status
let joined = false;

let autoPlayFailUser = [];
// stream play status
let playStatus = {};
let roomUsers = [];

const { hasLogin, _roomId, _uid, scene } = checkLoginInfo();
const isRefresh = hasLogin && scene === "beauty";

if (isRefresh) {
  $(".loading").removeClass("hidden");
}

// click browser back button
function back() {
  if (joined) {
    BeautyExtension.disableBeauty();
    $(".setting-item.beauty").css("display", "none");
    leaveRoom();
    joined = false;
    $("canvas").css("width", "1px");
    $("canvas").css("height", "1px");

    sessionStorage.removeItem("scene");
  } else {
    window.parent.location.pathname = location.pathname.includes("rtc/advance")
      ? "/rtc/advance/"
      : "";
  }
  window.parent?.onAdjustIframeStyle?.();
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

// when document ready, get device permission and start capture stream
// and get default roomId and userId from url query
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
  } else {
    micStatus = false;
    // $('#mic-icon').attr('src', `https://lf-cdn-tos.bytescm.com/obj/static/web_advance/images/micOff.svg`);
    $("#selectedmic").attr("disabled", "disabled");
  }

  if (devicePermissions.video) {
    videoInputs = await VERTC.enumerateVideoCaptureDevices();
    videoInputs = videoInputs.filter((i) => i.deviceId);

    // camera options
    const videoOptions = videoInputs.map((device) => {
      return `<li class='device-item' label='${device.deviceId}'>${device.label}</li>`;
    });
    $(".device-list.cameraList").append(...videoOptions);
    $("#selectedcamera").val(videoInputs?.[0]?.label || "");

    selectedCamera = videoInputs?.[0]?.deviceId || "";

    await engine.setVideoCaptureDevice(selectedCamera);

    engine.setVideoEncoderConfig({
      width: 480,
      height: 640,
      frameRate: 15,
      maxKbps: 600,
    });
  } else {
    cameraStatus = false;
    // $('#camera-icon').attr('src', `https://lf-cdn-tos.bytescm.com/obj/static/web_advance/images/cameraOff.svg`);
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
    $(`#${name}-text`).text(`${TEXTMAP[name]} 输入有误，请重新输入`);
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

registerEvents();

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

// stop stream and leave rtc room when page hide
window.addEventListener("pagehide", function (event) {
  removeEvents();
  engine.stopVideoCapture();
  engine.stopAudioCapture();
  engine.unpublishStream(VERTC.MediaType.AUDIO);
  engine.leaveRoom();
});

/**
 *  localuser leave room
 */
async function leaveRoom() {
  $("#joinRoom").css("display", "block");
  $("#example").css("display", "none");
  $(".players-wrapper").empty();
  $(".title-text").html("veRTC 进阶demo演示");
  $(".header_content").css("display", "block");

  await engine.stopAudioCapture();
  await engine.stopVideoCapture();

  await engine.leaveRoom();

  remoteAudioUsers = [];
  autoPlayFailUser = [];
  playStatus = {};
  roomUsers = [];

  $("#link").val("");
  $("#enableBauty").prop("checked", false);
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
    userId,
    renderMode: 1,
    renderDom: undefined,
  });
  let avatar = `<div class='user-avatar'><span>${JoinRoomConfig.userId}</span></div>`;
  $(`#remote-${userId}`).append(avatar);
}

function handleUserStartAudioCapture(event) {}

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

  // add player dom
  if (currentLength < 30) {
    roomUsers.push(remoteUserId);
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

  window.parent?.onAdjustIframeStyle?.();
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
	  ${
      !cameraStatus
        ? `<div class='user-avatar'><span>${userId}</span></div>`
        : ""
    }
	</div>
  `;

  return playerDom;
}

const slider = function () {
  let cb;
  init = function (value, domID, callback) {
    cb = callback;

    const wrapperNode = $(`.wrapper_progress${domID}`);

    const sliderNode = wrapperNode.children(".progress_slider");

    const fillNode = wrapperNode.children(".progress_fill");

    move(wrapperNode[0], sliderNode[0], fillNode[0], value);
  };

  move = function (wrapperDom, sliderDom, fillDom, value, max) {
    const default_max = max || 100;
    const wrapperDom_width = wrapperDom.clientWidth;
    if (value) {
      const left = (value * wrapperDom_width) / default_max + "px";
      sliderDom.style.left = left;
      fillDom.style.width = left;
    }

    let drag = 0;

    wrapperDom.addEventListener("click", function (e) {
      if (e.target === sliderDom) {
      } else {
        if (e.offsetX >= wrapperDom_width) {
          sliderDom.style.left = wrapperDom_width + "px";
          fillDom.style.width = wrapperDom_width + "px";
        } else if (e.offsetX < 10) {
          sliderDom.style.left = "0px";
          fillDom.style.width = "0px";
        } else {
          sliderDom.style.left = e.offsetX + "px";
          fillDom.style.width = e.offsetX + "px";
        }
      }
      if (cb) {
        const calc_width = fillDom.clientWidth;
        const calc_value = (calc_width * default_max) / wrapperDom_width;
        cb(calc_value);
      }
    });

    sliderDom.addEventListener("touchstart", function () {
      drag = 1;
    });

    document.addEventListener("touchend", function () {
      drag = 0;
    });

    wrapperDom.addEventListener("touchmove", function (e) {
      if (drag == 1) {
        const target = e.targetTouches?.[0];
        if (!target) return;
        let pageX = target.clientX - wrapperDom.offsetLeft - 32;
        if (pageX > wrapperDom_width - 5) {
          sliderDom.style.left = wrapperDom_width + "px";
          fillDom.style.width = wrapperDom_width + "px";
        } else if (pageX <= 10) {
          sliderDom.style.left = "0px";
          fillDom.style.width = "0px";
        } else {
          sliderDom.style.left = pageX + "px";
          fillDom.style.width = pageX + "px";
        }
        if (cb) {
          const calc_width = fillDom.clientWidth;
          const calc_value = (calc_width * default_max) / wrapperDom_width;
          cb(calc_value);
        }
      }
    });
  };

  return {
    init: init,
  };
};

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
  $(".header_content").css("display", "none");
  $(".title-text").html("基础美颜");

  joined = true;

  try {
    if (devicePermissions.video) {
      await engine.startVideoCapture();
    }
    if (devicePermissions.audio) {
      await engine.startAudioCapture();
    }
  } catch (e) {
    micStatus = false;
    cameraStatus = false;
    console.warn(e);
  }

  let playerDom = createPlayerDom(JoinRoomConfig.userId, {
    micStatus,
    cameraStatus,
  });

  $(".players-wrapper").append(playerDom);

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
    scene: "beauty",
  });

  document.querySelector("body > video").style.position = "absolute";
  document.querySelector("body > video").style.top = "50px";
  document.querySelector("body > video").style.opacity = 0;
  document.querySelector("body > video").style.width = "100%";
  document.querySelector("body > video").style.height = "1px";
  document.querySelector("body > video").style.zIndex = -99;
}
