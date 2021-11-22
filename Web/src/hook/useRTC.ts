import {useState, useEffect, useCallback, useRef} from 'react';
import {RTCClient, Stream} from '../app-interfaces';
import RTC from '../sdk/index';

type User = {
  userId: string, stream: Stream
};
type Event = {
  stream: Stream;
  streamId: string;
  type: string;
  uid: string;
};

const rtcSDK = new RTC();

export default function useRTC(): {
  join: (roomId: string, userId: string) => Promise<void>;
  client: RTCClient | undefined;
  isVideoOn: boolean;
  changeVideoState: () => void;
  isMicOn: boolean;
  changeMicState: () => void;
  userList: User[];
  leaveRoom: () => void;
} {
  const [client, setClient] = useState<RTCClient>();
  const [user, setLocalUser] = useState<string>();
  const [localStream, setLocalStream] = useState<Stream>();
  const [remoteStreams, setRemoteStreams] = useState<{
    [key: string]: Stream;
  }>({});
  const [isMicOn, setMicOn] = useState<boolean>(false);
  const [isVideoOn, setVideoOn] = useState<boolean>(false);
  const [userList, setUsers] = useState<User[]>([]);
  const count = useRef<number>(0);

  /**
   * @type function
   * @brief user leave room function
   */
  const leaveRoom = useCallback(() => {
    rtcSDK.leave();
  }, []);

  const handler = useCallback(() => {
    if (client) {
      leaveRoom();
    }
  }, [client, leaveRoom]);

  /**
   * @brief call leaveRoom function when the browser window closes or refreshes
   */
  useEffect(() => {
    window.addEventListener('beforeunload', handler);
    return () => {
      handler();
      window.removeEventListener('beforeunload', handler);
    };
  }, [client, handler]);

  /**
   * @brief create local stream and update localStream state
   * @param {string} userId
   */
  const createLocalStream = useCallback(async (userId: string) => {
    const res = await rtcSDK.checkPermission();
    const devices = await rtcSDK.getDevices();

    const param = Object.assign({}, res?.[0], res?.[1]);
    if (param?.video) {
      setVideoOn(true);
    }
    if (param?.audio) {
      setMicOn(true);
    }
    if (!devices.audioInputs?.length && !devices.videoInputs?.length) {
      alert('设备获取失败');
      return;
    }

    rtcSDK.createStream(
      {
        ...param,
        microphoneId: devices.audioInputs[0].deviceId ?? undefined,
        cameraId: devices.videoInputs[0].deviceId ?? undefined,
      },
      (localStream) => {
        setLocalStream(localStream);
        setLocalUser(userId);
      },
    );
  }, []);

  /**
   * @brief join meeting
   * @param {string} roomId
   * @param {string} userId
   */
  const join = useCallback(
    async (roomId: string, userId: string) => {
      rtcSDK
        .join(roomId, userId)
        .then((client) => {
          count.current += 1;
          createLocalStream(userId);
          setClient(client);
        })
        .catch((err) => alert(err));
    },
    [createLocalStream],
  );

  /**
   * @brief change stream audio state and component mic on/off state
   */
  const changeMicState = useCallback((): void => {
    if (localStream) {
      if (!isMicOn) {
        localStream.enableAudio();
        setMicOn(true);
      } else {
        localStream.disableAudio();
        setMicOn(false);
      }
    }
  }, [isMicOn, localStream]);

  /**
   * @brief change stream video state and component video on/off state
   */
  const changeVideoState = useCallback((): void => {
    if (localStream) {
      if (!isVideoOn) {
        localStream.enableVideo();
        setVideoOn(true);
      } else {
        localStream.disableVideo();
        setVideoOn(false);
      }
    }
  }, [isVideoOn, localStream]);

  /**
   * @brief merge localstream and remotestream into user LIS
   */
  useEffect(() => {
    if (!user || !localStream) return;
    const _remote = Object.keys(remoteStreams)?.map((i: string) => ({
      userId: i,
      stream: remoteStreams[i],
    }));
    const _user = [{userId: user, stream: localStream}, ..._remote];
    setUsers(_user);
    count.current = _user.length;
  }, [localStream, remoteStreams, user]);

  /**
   * @brief subscribe stream after stream add
   * @param {Event} event
   */
  const handleStreamAdd = useCallback((event: Event) => {
    rtcSDK.subscribe(event.stream);
  }, []);

  /**
   * @brief subscribed stream & update remote streams list
   * @param {Event} event
   */
  const handleStreamSubscribed = useCallback(
    (event: Event) => {
      const userId = event.stream.uid;
      if (count.current < 4 && userList.length < 4) {
        setRemoteStreams({
          ...remoteStreams,
          [userId]: event.stream,
        });
        count.current += 1;
      }
    },
    [remoteStreams, userList.length],
  );

  /**
   * @brief remove stream & update remote streams list
   * @param {Event} event
   */
  const handleStreamRemove = useCallback(
    (event: Event) => {
      const uid = event.stream.uid;
      if (remoteStreams[uid]) {
        delete remoteStreams[uid];
      }
      setRemoteStreams({
        ...remoteStreams,
      });
    },
    [remoteStreams],
  );

  /**
   * @brief leave room when receive client-banned event
   * @param {Event} event
   */
  const handleClientBanned = useCallback(
    (event: Event) => {
      if (event.uid === user) {
        leaveRoom();
      }
    },
    [leaveRoom, user],
  );

  useEffect(() => {
    if (!client) return;

    client.on('stream-added', handleStreamAdd);
    client.on('stream-subscribed', handleStreamSubscribed);
    client.on('stream-removed', handleStreamRemove);

    client.on('mute-audio', () => {});
    client.on('mute-video', () => {});
    client.on('unmute-audio', () => {});
    client.on('unmute-video', () => {});
    client.on('client-banned', handleClientBanned);
    return () => {
      client.off('stream-added', handleStreamAdd);
      client.off('stream-subscribed', handleStreamSubscribed);
      client.off('stream-removed', handleStreamRemove);
      client.off('stream-removed', handleClientBanned);
    };
  }, [
    client,
    handleStreamAdd,
    handleStreamSubscribed,
    handleStreamRemove,
    handleClientBanned,
  ]);

  return {
    join,
    client,
    isVideoOn,
    changeVideoState,
    isMicOn,
    changeMicState,
    userList,
    leaveRoom,
  };
}