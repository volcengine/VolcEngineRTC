import { OnRtcChatMembersChangedEvent, OnRtcChatSpeakersChangedEvent, OnRtcPublishScreenMembersChangedEvent, OnRtcVideoMembersChangedEvent } from "@douyin-microapp/typings";
import { promisify } from "../../../common/promisify";
import { AppId, InputRegex, Token } from "../../../constant";
import { fetchToken } from '../../../common/token';

type RemoteStream = {
  userId: string;
  // video:   远端用户普通画面
  // screen:  远端用户共享屏幕画面
  mode: 'video' | 'screen';
  isMe: boolean;
  isCameraOn: boolean;
  isAudioOn: boolean;
}

Page({
  rtcContext: null as any,

  data: {
    userId: '',
    roomId: '',
    token: '',

    showLocalStream: false,

    roomMembers: [] as string[],
    videoMembers: [] as string[],
    audioMembers: [] as string[],
    screenMembers: [] as string[],
    remoteStreams: [] as RemoteStream[],
    showRemoteStream: false,
  },

  onShow() {
    tt.login({
      success: (loginRes) => {
        console.log('登录成功:', loginRes);

        const userId = loginRes.anonymousCode.slice(0, 8);
        this.setData({ userId });
      },
      fail: (err) => {
        console.error('登录失败:', err);

        // 网络断开
        if (
          // android
          err.errNo === 10103
          // ios
          || err.errNo === 21101
        ) {
          tt.showToast({
            title: '网络断开，请检查网络！',
            icon: 'fail'
          });
          return;
        }

        tt.showToast({
          title: '请先登录抖音',
          icon: 'fail'
        });
      },
    });
  },

  onUnload() {
    if (this.rtcContext) {
      this.leaveRoom();
    }
  },

  handleRoomIdInput(e: { detail: { value: string } }) {
    const input = e.detail.value;

    this.setData({
      roomId: input,
    });
  },

  /**
   * step1: 创建引擎
   */
  createEngine() {
    this.rtcContext = tt.createRtcRoomContext({
      appId: AppId,
    });
    console.log('rtc', this.rtcContext);
  },

  /**
   * step2: 采集音视频
   */
  async startCapture() {
    const rtcContext = this.rtcContext;
    if (!rtcContext) return;

    await promisify(rtcContext.changeVideoCapture)({
      state: 1
    });
    await promisify(rtcContext.changeAudioCapture)({
      state: 1
    });
  },

  async stopCapture() {
    const rtcContext = this.rtcContext;
    if (!rtcContext) return;

    await promisify(rtcContext.changeVideoCapture)({
      state: 0
    });
    await promisify(rtcContext.changeAudioCapture)({
      state: 0
    });

    this.setData({ showLocalStream: false });
  },

  /**
   * step3: 使用 rtc-room 组件渲染本地流
   */
  async renderLocalStream() {
    this.setData({ showLocalStream: true });
  },

  /**
   * step4: 加入房间
   */
  async joinRtcRoom() {
    if (!InputRegex.test(this.data.roomId)) {
      tt.showToast({
        title: "roomId 输入不正确!",
        icon: 'fail',
      });
      return;
    }

    await this.updateToken();
    
    const rtcContext = this.rtcContext;
    if (!rtcContext) return;

    console.log('加入房间:', AppId, this.data.roomId, this.data.userId, this.data.token);
    tt.showLoading({ title: '加入房间中' });
    this.addRtcListeners();
    rtcContext.joinRtcRoom({
      roomId: this.data.roomId,
      userId: this.data.userId,
      token: this.data.token,
      roomConfig: {
        autoPublish: true,
        autoSubscribe: true,
      },
      success() {
        tt.hideLoading({});
      },
      fail(e: any) {
        console.error('加入房间失败:', e);
        tt.hideLoading({});
        tt.showToast({
          icon: 'fail',
          title: '加入房间失败!',
        });
      },
    });
  },

  async updateToken() {
    const { roomId, userId } = this.data;
    const res = await fetchToken(roomId, userId);
    return new Promise<void>((resolve) => {
      this.setData(res, resolve);
    });
  },

  addRtcListeners() {
    const rtcContext = this.rtcContext;
    if (!rtcContext) return;

    rtcContext.onRtcVideoMembersChanged(this.onRtcVideoMembersChanged);
    rtcContext.onRtcChatSpeakersChanged(this.onRtcChatSpeakersChanged);
    rtcContext.onRtcChatMembersChanged(this.onRtcChatMembersChanged);
    rtcContext.onRtcPublishScreenMembersChanged(this.onRtcPublishScreenMembersChanged);
  },

  removeRtcListeners() {
    const rtcContext = this.rtcContext;

    rtcContext.offRtcVideoMembersChanged(this.onRtcVideoMembersChanged);
    rtcContext.offRtcChatSpeakersChanged(this.onRtcChatSpeakersChanged);
    rtcContext.offRtcChatMembersChanged(this.onRtcChatMembersChanged);
    rtcContext.offRtcPublishScreenMembersChanged(this.onRtcPublishScreenMembersChanged);
  },

  onRtcChatMembersChanged(ev: OnRtcChatMembersChangedEvent) {
    const { userIdList } = ev;
    console.log('onRtcChatMembersChanged ', ev, userIdList);
    this.setData(
      {
        roomMembers: userIdList,
      },
      () => {
        this.calcRemoteStreams();
      }
    );
  },

  onRtcVideoMembersChanged({ userIdList, errCode, errMsg }: OnRtcVideoMembersChangedEvent) {
    console.log('onRtcVideoMembersChanged', userIdList, errCode, errMsg);
    this.setData(
      {
        videoMembers: userIdList,
      },
      () => {
        this.calcRemoteStreams();
      }
    );
  },

  onRtcChatSpeakersChanged({ userIdList, errCode, errMsg }: OnRtcChatSpeakersChangedEvent) {
    console.log('onRtcChatSpeakersChanged ', userIdList, errCode, errMsg);
    this.setData(
      {
        audioMembers: userIdList,
      },
      () => {
        this.calcRemoteStreams();
      }
    );
  },

  onRtcPublishScreenMembersChanged({ userIdList }: OnRtcPublishScreenMembersChangedEvent) {
    console.log('onRtcPublishScreenMembersChanged ', userIdList);
    this.setData(
      {
        screenMembers: userIdList,
      },
      () => {
        this.calcRemoteStreams();
      }
    );
  },

  calcRemoteStreams() {
    const roomMembers = [...this.data.roomMembers];
    const videoMembers = [...this.data.videoMembers];
    const audioMembers = [...this.data.audioMembers];
    const screenMembers = [...this.data.screenMembers];

    const streams = roomMembers.map((userId) => {
      const isMe = this.data.userId === userId;
      const mode: RemoteStream['mode'] = screenMembers.includes(userId) ? 'screen' : 'video';
      return {
        userId,
        mode,
        isMe: isMe,
        isCameraOn: videoMembers.includes(userId),
        isAudioOn: audioMembers.includes(userId),
      } as RemoteStream;
    });

    const remoteStreams = streams.filter(s => !s.isMe);
    this.setData({
      remoteStreams,
      showRemoteStream: remoteStreams.length > 0,
    });
  },

  async leaveRoom() {
    const rtcContext = this.rtcContext;
    if (!rtcContext) return;

    await promisify(rtcContext.exitRtcRoom)({
      roomId: this.data.roomId
    });

    this.setData({
      showRemoteStream: false,
      roomMembers: [],
      audioMembers: [],
      videoMembers: [],
      screenMembers: [],
      remoteStreams: [],
    });
  },

  handleRTCError(e: any) {
    console.error('rtc error', e);
  },
});

