class RtcClient{
  constructor(props) {
    this.config = props.config;
    this.streamOptions = props.streamOptions;
    this.engine = VERTC.createEngine(props.config.appId);
    this.handleStreamAdd = props.handleStreamAdd
    this.handleStreamRemove = props.handleStreamRemove
    this.handleEventError = props.handleEventError
    this.setRemoteVideoPlayer = this.setRemoteVideoPlayer.bind(this);
  }
  SDKVERSION = VERTC.getSdkVersion()
  bindEngineEvents(){
    this.engine.on(VERTC.events.onStreamAdd, this.handleStreamAdd);
    this.engine.on(VERTC.events.onStreamRemove, this.handleStreamRemove);
    this.engine.on(VERTC.events.onError, (e) =>
      this.handleEventError(e, VERTC),
    );
  }
  async setRemoteVideoPlayer(remoteUserId, dom, stream){
    // 如果进房的config有自动订阅，这里就不需要订阅了
    await this.engine.subscribeUserStream(remoteUserId, VERTC.SubscribeMediaType.AUDIO_AND_VIDEO);
    await this.engine.setRemoteVideoPlayer(VERTC.StreamIndex.STREAM_INDEX_MAIN, {
      userId: remoteUserId,
      renderDom: dom,
      isScreen: stream.isScreen,
    });
  }
  /**
  * remove the listeners when `createengine`
  */
  removeEventListener(){
    this.engine.off(VERTC.events.onStreamAdd, this.handleStreamAdd);
    this.engine.off(VERTC.events.onStreamRemove, this.handleStreamRemove);
  }
  join(token, roomId, uid){
    return this.engine.joinRoom(token, roomId, {
      userId: uid,
    }, {
      // 默认值全为false
      isAutoPublish: false,
      isAutoSubscribeAudio: false,
      isAutoSubscribeVideo: false,
    })
  }
  // check permission of browser
  checkPermission(){
    return VERTC.enableDevices();
  };
  /**
  * get the devices
  * @returns
  */
  async getDevices(){
    return {
      audioInputs: await VERTC.getMicrophones(),
      videoInputs: await VERTC.getCameras(),
    }
  };
  /**
  * create the local stream with the config and publish the local stream
  * @param {*} callback
  */
  async createLocalStream(callback){
    const permissions = await this.checkPermission();
    const devices = await this.getDevices();
    const devicesStatus = {
      video: 1,
      audio: 1
    };
    if (!devices.audioInputs.length && !devices.videoInputs.length) {
      alert('设备获取失败');
      return;
    }
    if (streamOptions.audio && permissions.audio) {
      await this.engine.startAudioCapture();
    } else {
      devicesStatus['video'] = 0;
      this.engine.muteLocalAudio(VERTC.MuteState.MUTE_STATE_OFF);
    }
    if (streamOptions.video && permissions.video) {
      await this.engine.startVideoCapture();
    } else {
      devicesStatus['audio'] = 0;
      this.engine.muteLocalVideo(VERTC.MuteState.MUTE_STATE_OFF);
    }

    this.engine.setLocalVideoPlayer(VERTC.StreamIndex.STREAM_INDEX_MAIN, {
      renderDom: 'local-player',
      userId: this.config.uid,
    });

    // 如果joinRoom的config设置了自动发布，这里就不需要发布了
    this.engine.publish();

    callback && callback({
      code: 0,
      msg: '设备获取失败',
      devicesStatus,
    });
  }
  changeAudioState(isMicOn){
    !isMicOn ? this.engine.stopAudioCapture() : this.engine.startAudioCapture()
  }
  changeVideoState(isVideoOn){
    !isVideoOn ? this.engine.stopVideoCapture() : this.engine.startVideoCapture();
  }
  leave(){
    this.engine.leaveRoom();
    VERTC.destroyEngine(this.engine);
  }
}