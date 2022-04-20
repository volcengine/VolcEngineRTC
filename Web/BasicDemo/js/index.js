'use strict';


let rtc = new RtcClient({
  config,
  streamOptions,
  handleStreamAdd,
  handleStreamRemove,
  handleEventError
});

/**
 * hide the voice and mic control pannel
 */
$('.player').hide();
$('#control').hide();
$('#room-id-text').text('');
$('#user-id-text').text('');
$('#header-version').text(`${rtc.SDKVERSION}`);
checkRoomIdAndUserId('room-id');
checkRoomIdAndUserId('user-id');

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

/*
 * When a user clicks Join or Leave in the HTML form, this procedure gathers the information
 * entered in the form and calls join asynchronously. The UI is updated to match the options entered
 * by the user.
 */

$('#header-version').text(`${rtc.SDKVERSION}`);

$('#submit').on('click', async () => {
  if(checkReg('room-id') || checkReg('user-id')){
    return
  }
  config.roomId = $('#room-id').val();
  config.uid = $('#user-id').val();
  $('#control').show();
  $('.player').show();
  $('#pannel').hide();
  try {
    rtc.bindEngineEvents()
    /*
    * before join a room, you should create a room,then you can join it with `engine.join(token,roomId,uid, onSuccessFunc, onFailFunc)`
    */
    await rtc.join((config.token || {})[config.uid], config.roomId, config.uid);
    $('#header-version').text(`${config.roomId}`);
    $('#local-player').show();
    $('#local-player-name').text(`${config.uid}`);
    rtc.createLocalStream();
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
  rtc.changeAudioState(isMicOn);
  isMicOn = !isMicOn;
  // toggle the mic icon url
  changeMicOrVideoIconUrl('mic', isMicOn, OFFMICICON, ONMICICON);
};
/**
 * change the video state
 */
const actionChangeVideoState = () => {
  rtc.changeVideoState(isVideoOn);
  isVideoOn = !isVideoOn;
  // toggle the video icon url
  changeMicOrVideoIconUrl('video', isVideoOn, OFFVIDEOICON, ONVIDEOICON);
};

/*
 * leave the room and clear the wrapper dom of `engine` and info
 */
const actionToLeave = () => {
  // leave the room
  rtc.leave()
  // off the event
  rtc.removeEventListener();
  $('#header-version').text(`RTC版本 v${rtc.SDKVERSION}`);
  $('.re-player').remove();
  // clear the dom
  $('#user-id').val('');
  $('#room-id').val('');
  $('#control').hide();
  $('.player').hide();
  $('#pannel').show();
};
/*---------------------- action handler end --------------------*/

/*------------------------- common handler start ----------------*/
/*
*  These procedures use RTC SDK for Web to enable local and remote
*  users to join and leave a room managed by RTC Platform.
*/
// const engine = VERTC.createEngine(config.appId);
// bindEngineEvents();

/**
 * Add a user who has subscribed to the live room to the local interface.
 * @param {*} event
 */
async function handleStreamAdd({ stream }) {
  const remoteUserId = stream.userId
  const currentLength = $('.player-wrapper').length;
  // Player doms are created when there are no more than four in a room
  if (currentLength < 4) {
    const player = $(`
    <div id="player-wrapper-${remoteUserId}" class="player-wrapper re-player">
      <p class="player-name">${remoteUserId}</p>
    </div>
  `);
    $('#player-list').append(player);
    rtc.setRemoteVideoPlayer(remoteUserId, player[0], stream);
  }
};

/**
 * Remove the user specified from the room in the local and clear the unused dom
 * @param {*} event
 */
function handleStreamRemove({ stream }) {
  const remoteUserId = stream.userId
  if (remoteUserId === config.uid) {
    $('#local-player').hide();
    $('#local-player-name').text('');
  }
  $(`#player-wrapper-${remoteUserId}`).remove();
};
/*------------------------- common handler end ----------------*/


function handleEventError(e, VERTC){
  if (e.errorCode === VERTC.ErrorCode.DUPLICATE_LOGIN) {
    actionToLeave();
    alert('你的账号被其他人顶下线了');
  }
}