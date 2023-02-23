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

    this.setRemoteVideoPlayer = this.setRemoteVideoPlayer.bind(this);
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
    return {
      audioInputs: await VERTC.enumerateAudioCaptureDevices(),
      videoInputs: await VERTC.enumerateVideoCaptureDevices(),
    };
  }
  /**
   * create the local stream with the config and publish the local stream
   * @param {*} callback
   */
  async createLocalStream(callback) {
    const permissions = await this.checkPermission();
    const devices = await this.getDevices();
    const devicesStatus = {
      video: 1,
      audio: 1,
    };
    if (!devices.audioInputs.length && !devices.videoInputs.length) {
      alert('设备获取失败');
      return;
    }
    if (streamOptions.audio && permissions.audio) {
      await this.engine.startAudioCapture();
    } else {
      devicesStatus['video'] = 0;
      this.engine.unpublishStream(VERTC.MediaType.AUDIO);
    }
    if (streamOptions.video && permissions.video) {
      await this.engine.startVideoCapture();
    } else {
      devicesStatus['audio'] = 0;
      this.engine.unpublishStream(VERTC.MediaType.VIDEO);
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
        msg: '设备获取失败',
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
    await this.engine.stopVideoCapture();
    await this.engine.stopAudioCapture();
    await this.engine.unpublishStream(VERTC.MediaType.AUDIO);
    await this.engine.leaveRoom();
    // VERTC.destroyEngine(this.engine);
  }
}
