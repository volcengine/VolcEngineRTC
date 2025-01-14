/**
 * Copyright 2024 Beijing Volcano Engine Technology Co., Ltd. All Rights Reserved.
 * SPDX-license-identifier: BSD-3-Clause
 */

class RtcClient {
  constructor(props) {
    this.config = props.config;
    this.streamOptions = props.streamOptions;
    this.engine = VERTC.createEngine(props.config.appId);
    this.handleUserPublishStream = props.handleUserPublishStream;
    this.handleUserUnpublishStream = props.handleUserUnpublishStream;
    this.handleUserStartVideoCapture = props.handleUserStartVideoCapture;
    this.handleUserStopVideoCapture = props.handleUserStopVideoCapture;
    this.handleEventError = props.handleEventError;
    this.handleUserJoin = props.handleUserJoin;
    this.handleUserLeave = props.handleUserLeave;
    this.handleAutoPlayFail = this.handleAutoPlayFail.bind(this);
    this.setRemoteVideoPlayer = this.setRemoteVideoPlayer.bind(this);
    this.handlePlayerEvent = this.handlePlayerEvent.bind(this);
    this.autoPlayFailUser = [];
    this.playStatus = {};
  }
  SDKVERSION = VERTC.getSdkVersion();
  MediaType = VERTC.MediaType;
  bindEngineEvents() {
    this.engine.on(VERTC.events.onUserPublishStream, this.handleUserPublishStream);
    this.engine.on(VERTC.events.onUserUnpublishStream, this.handleUserUnpublishStream);
    this.engine.on(VERTC.events.onUserStartVideoCapture, this.handleUserStartVideoCapture);
    this.engine.on(VERTC.events.onUserStopVideoCapture, this.handleUserStopVideoCapture);
    this.engine.on(VERTC.events.onUserJoined, this.handleUserJoin);
    this.engine.on(VERTC.events.onUserLeave, this.handleUserLeave);
    this.engine.on(VERTC.events.onError, this.handleEventError);
    this.engine.on(VERTC.events.onAutoplayFailed, this.handleAutoPlayFail);
    this.engine.on(VERTC.events.onPlayerEvent, this.handlePlayerEvent);
  }
  async setRemoteVideoPlayer(remoteUserId, dom) {
    // 如果进房的config有自动订阅，这里就不需要订阅了
    await this.engine.subscribeStream(remoteUserId, VERTC.MediaType.AUDIO_AND_VIDEO);

    await this.engine.setRemoteVideoPlayer(VERTC.StreamIndex.STREAM_INDEX_MAIN, {
      userId: remoteUserId,
      renderDom: dom,
    });
  }
  /**
   * remove the listeners when `createEngine`
   */
  removeEventListener() {
    this.engine.off(VERTC.events.onUserPublishStream, this.handleUserPublishStream);
    this.engine.off(VERTC.events.onUserUnpublishStream, this.handleUserUnpublishStream);
    this.engine.off(VERTC.events.onUserStartVideoCapture, this.handleUserStartVideoCapture);
    this.engine.off(VERTC.events.onUserStopVideoCapture, this.handleUserStopVideoCapture);
    this.engine.off(VERTC.events.onUserJoined, this.handleUserJoin);
    this.engine.off(VERTC.events.onUserLeave, this.handleUserLeave);
    this.engine.off(VERTC.events.onError, this.handleEventError);
    this.engine.off(VERTC.events.onAutoplayFailed, this.handleAutoPlayFail);
    this.engine.off(VERTC.events.onPlayerEvent, this.handlePlayerEvent);
  }
  join(token, roomId, uid) {
    return this.engine.joinRoom(
      token,
      roomId,
      {
        userId: uid,
      },
      {
        // 默认值全为true
        isAutoPublish: true,
        isAutoSubscribeAudio: true,
        isAutoSubscribeVideo: true,
      }
    );
  }
  // check permission of browser
  checkPermission() {
    return VERTC.enableDevices();
  }
  /**
   * get the devices
   * @returns
   */
  async getDevices() {
    const devices = await VERTC.enumerateDevices();
    return {
      audioInputs: devices.filter((i) => i.deviceId && i.kind === 'audioinput'),
      videoInputs: devices.filter((i) => i.deviceId && i.kind === 'videoinput'),
    };
  }
  /**
   * create the local stream with the config and publish the local stream
   * @param {*} callback
   */
  async createLocalStream(callback) {
    const devices = await this.getDevices();
    const devicesStatus = {
      video: 1,
      audio: 1,
    };
    if (
      !devices.audioInputs.length &&
      devices.videoInputs.length === 0 &&
      devices.audioInputs.length === 0
    ) {
      if (window.confirm('设备权限获取失败, 是否跳转排查文档?')) {
        window.location.href = 'https://www.volcengine.com/docs/6348/1356355';
      } 
      isMicOn = false;
      changeMicOrVideoIconUrl('mic', isMicOn, OFFMICICON, ONMICICON);
      isVideoOn = false;
      changeMicOrVideoIconUrl('video', isVideoOn, OFFVIDEOICON, ONVIDEOICON);
      return;
    }
    if (streamOptions.audio && devices.audioInputs.length) {
      await this.engine.startAudioCapture();
    } else {
      devicesStatus['audio'] = 0;
      this.engine.unpublishStream(VERTC.MediaType.AUDIO);
      isVideoOn = false;
      changeMicOrVideoIconUrl('video', isVideoOn, OFFVIDEOICON, ONVIDEOICON);
    }
    if (streamOptions.video && devices.videoInputs.length) {
      await this.engine.startVideoCapture();
    } else {
      devicesStatus['video'] = 0;
      this.engine.unpublishStream(VERTC.MediaType.VIDEO);
      isMicOn = false;
      changeMicOrVideoIconUrl('mic', isMicOn, OFFMICICON, ONMICICON);
    }

    this.engine.setLocalVideoPlayer(VERTC.StreamIndex.STREAM_INDEX_MAIN, {
      renderDom: 'local-player',
      userId: this.config.uid,
    });

    // 如果joinRoom的config设置了自动发布，这里就不需要发布了
    this.engine.publishStream(VERTC.MediaType.AUDIO_AND_VIDEO);

    callback &&
      callback({
        code: 0,
        msg: '设备权限获取成功',
        devicesStatus,
      });
  }
  async changeAudioState(isMicOn) {
    if (isMicOn) {
      await this.engine.publishStream(VERTC.MediaType.AUDIO);
    } else {
      await this.engine.unpublishStream(VERTC.MediaType.AUDIO);
    }
  }
  async changeVideoState(isVideoOn) {
    if (isVideoOn) {
      await this.engine.startVideoCapture();
    } else {
      await this.engine.stopVideoCapture();
    }
  }
  async leave() {
    this.engine.stopVideoCapture();
    this.engine.stopAudioCapture();
    this.engine.unpublishStream(VERTC.MediaType.AUDIO);
    this.engine.leaveRoom();
    // VERTC.destroyEngine(this.engine);
  }

  addFailUser(userId) {
    const index = this.autoPlayFailUser.findIndex((item) => item === userId);
    if (index === -1) {
      this.autoPlayFailUser.push(userId);
    }
  }

  handleAutoPlayFail(event) {
    console.log('handleAutoPlayFail', event);

    const { userId, kind } = event;

    let playUser = this.playStatus[userId] || {};
    this.playStatus[userId] = { ...playUser, [kind]: false };

    this.addFailUser(event.userId);
    //引导用户进行交互
    openModal();
  }

  playerFail(params) {
    const { type, userId } = params;

    const playUser = this.playStatus[userId] || {};
    this.playStatus[userId] = { ...playUser, [type]: false };
    const { audio, video } = this.playStatus[userId];

    if (audio === false || video === false) {
      this.addFailUser(userId);
    }
  }

  handlePlayerEvent(event) {
    const { userId, rawEvent, type } = event;
    const playUser = this.playStatus[userId] || {};
    if (rawEvent.type === 'playing') {
      this.playStatus[userId] = { ...playUser, [type]: true };
      const { audio, video } = this.playStatus[userId];
      if (audio !== false && video !== false) {
        this.checkAutoPlayFailUser(userId);
      }
    } else if (rawEvent.type === 'pause') {
      this.playerFail({ userId, type });
    }
    console.log('this.playStatus', this.playStatus);
  }

  checkAutoPlayFailUser(userId) {
    this.autoPlayFailUser = this.autoPlayFailUser.filter((item) => item !== userId);

    if (this.autoPlayFailUser.length === 0) {
      closeModal();
    }
  }

  //手动播放
  handleAutoPlay() {
    if (this.autoPlayFailUser.length) {
      this.autoPlayFailUser.forEach((user) => {
        this.engine.play(user);
      });
    }
    this.autoPlayFailUser = [];
  }
}
