class RtcClient {
  constructor(props) {
    this.config = props.config;
    this.streamOptions = props.streamOptions;
    this.engine = VERTC.createEngine(props.config.appId);
    this.handleStreamAdd = props.handleStreamAdd;
    this.handleStreamRemove = props.handleStreamRemove;
    this.handleEventError = props.handleEventError;
    this.setRemoteVideoPlayer = this.setRemoteVideoPlayer.bind(this);
  }
  SDKVERSION = VERTC.getSdkVersion();
  MediaType = VERTC.MediaType;
  bindEngineEvents() {
    this.engine.on(VERTC.events.onUserPublishStream, this.handleStreamAdd);
    this.engine.on(VERTC.events.onUserUnpublishStream, this.handleStreamRemove);
    this.engine.on(VERTC.events.onError, (e) =>
      this.handleEventError(e, VERTC)
    );
  }
  async setRemoteVideoPlayer(remoteUserId, dom, stream) {
    // 如果进房的config有自动订阅，这里就不需要订阅了
    await this.engine.subscribeStream(
      remoteUserId,
      VERTC.MediaType.AUDIO_AND_VIDEO
    );

    await this.engine.setRemoteVideoPlayer(
      VERTC.StreamIndex.STREAM_INDEX_MAIN,
      {
        userId: remoteUserId,
        renderDom: dom,
        isScreen: stream.isScreen,
      }
    );
  }
  /**
   * remove the listeners when `createEngine`
   */
  removeEventListener() {
    this.engine.off(VERTC.events.onUserPublishStream, this.handleStreamAdd);
    this.engine.off(
      VERTC.events.onUserUnpublishStream,
      this.handleStreamRemove
    );
  }
  join(token, roomId, uid) {
    return this.engine.joinRoom(
      null,
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
  changeAudioState(isMicOn) {
    !isMicOn
      ? this.engine.unpublishStream(VERTC.MediaType.AUDIO)
      : this.engine.publishStream(VERTC.MediaType.AUDIO);
  }
  changeVideoState(isVideoOn) {
    !isVideoOn
      ? this.engine.unpublishStream(VERTC.MediaType.VIDEO)
      : this.engine.publishStream(VERTC.MediaType.VIDEO);
  }
  leave() {
    this.engine.leaveRoom();
    VERTC.destroyEngine(this.engine);
  }
}
