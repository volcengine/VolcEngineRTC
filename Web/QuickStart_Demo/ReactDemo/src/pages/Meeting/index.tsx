import React, { useState, useContext, useEffect, useCallback, useRef } from 'react';
import { message } from 'antd';
import styled from 'styled-components';
import {
  MediaType,
  onUserJoinedEvent,
  onUserLeaveEvent,
  PlayerEvent,
  AutoPlayFailedEvent,
} from '@volcengine/rtc';
import { ControlBar, AutoPlayModal } from '../../modules';
import { Context } from '../../context';

import RTCComponent from '../../sdk/rtc-component';
import { RTCClient } from '../../app-interfaces';
import { streamOptions } from './constant';
import config from '../../config';
import MediaPlayer from '../../components/MediaPlayer';
import { removeLoginInfo } from '../../utils';

const Container = styled.div`
  width: 100%;
  height: 100%;
  display: flex;
  flex-wrap: wrap;
  padding: 8px;
  gap: 8px;
`;

const Item = styled.div`
  flex: 1;
  width: calc(50% - 8px);
  min-width: calc(50% - 8px);
  max-width: calc(50% - 8px);
  height: calc(50% - 8px);
  position: relative;
`;

const Meeting: React.FC<Record<string, unknown>> = () => {
  const { roomId, userId, setJoin, setJoinFailReason } = useContext(Context);
  const [isMicOn, setMicOn] = useState<boolean>(true);
  const [isVideoOn, setVideoOn] = useState<boolean>(true);
  const rtc = useRef<RTCClient>();
  const [autoPlayFailUser, setAutoPlayFailUser] = useState<string[]>([]);
  const playStatus = useRef<{ [key: string]: { audio: boolean; video: boolean } }>({});
  const autoPlayFailUserdRef = useRef<string[]>([]);

  const [remoteStreams, setRemoteStreams] = useState<{
    [key: string]: {
      playerComp: React.ReactNode;
    };
  }>({});

  const leaveRoom = useCallback(
    (refresh: boolean) => {
      if (!rtc.current) return;

      // off the event
      rtc.current.removeEventListener();

      rtc.current.leave();
      if (!refresh) {
        setJoin(false);
        removeLoginInfo();
      }

      setAutoPlayFailUser([]);
      setJoinFailReason('');
    },
    [rtc, setJoin]
  );
  // alert(111);

  // useEffect(() => {
  //   if (sessionStorage.getItem('store')) {
  //     const a = sessionStorage.getItem('store');
  //     a && alert(a);
  //   }
  // }, []);
  /**
   * @brief call leaveRoom function when the browser window closes or refreshes
   */
  const leaveFunc = () => {
    leaveRoom(true);
    sessionStorage.setItem('store', JSON.stringify({ test: new Date().toString() }));
  };
  useEffect(() => {
    window.addEventListener('pagehide', leaveFunc);
    return () => {
      leaveRoom(true);
      window.removeEventListener('pagehide', leaveFunc);
    };
  }, [leaveRoom]);

  const handleUserPublishStream = useCallback(
    (stream: { userId: string; mediaType: MediaType }) => {
      const userId = stream.userId;
      if (stream.mediaType & MediaType.VIDEO) {
        if (remoteStreams[userId]) {
          rtc.current?.setRemoteVideoPlayer(userId, `remoteStream_${userId}`);
        }
      }
    },
    [remoteStreams]
  );

  /**
   * @brief remove stream & update remote streams list
   * @param {Event} event
   */
  const handleUserUnpublishStream = (event: { userId: string; mediaType: MediaType }) => {
    const { userId, mediaType } = event;

    if (mediaType & MediaType.VIDEO) {
      rtc.current?.setRemoteVideoPlayer(userId, undefined);
    }
  };

  const handleUserStartVideoCapture = (event: { userId: string }) => {
    const { userId } = event;

    if (remoteStreams[userId]) {
      rtc.current?.setRemoteVideoPlayer(userId, `remoteStream_${userId}`);
    }
  };

  /**
   * Remove the user specified from the room in the local and clear the unused dom
   * @param {*} event
   */
  const handleUserStopVideoCapture = (event: { userId: string }) => {
    const { userId } = event;

    rtc.current?.setRemoteVideoPlayer(userId, undefined);
  };

  const handleUserJoin = (e: onUserJoinedEvent) => {
    console.log('handleUserJoin', e);

    const { userInfo } = e;
    const remoteUserId = userInfo.userId;

    if (Object.keys(remoteStreams).length < 3) {
      if (remoteStreams[remoteUserId]) return;
      remoteStreams[remoteUserId] = {
        playerComp: <MediaPlayer userId={remoteUserId} />,
      };

      setRemoteStreams({
        ...remoteStreams,
      });
    }
  };

  useEffect(() => {
    const streams = Object.keys(remoteStreams);
    const _autoPlayFailUser = autoPlayFailUser.filter(
      (item) => streams.findIndex((stream) => stream === item) !== -1
    );
    setAutoPlayFailUser([..._autoPlayFailUser]);
  }, [remoteStreams]);

  const handleUserLeave = (e: onUserLeaveEvent) => {
    const { userInfo } = e;
    const remoteUserId = userInfo.userId;
    if (remoteStreams[remoteUserId]) {
      delete remoteStreams[remoteUserId];
    }
    setRemoteStreams({
      ...remoteStreams,
    });
  };

  useEffect(() => {
    (async () => {
      if (!roomId || !userId || !rtc.current) return;
      // rtc.current.bindEngineEvents();

      let token = null;
      config.tokens.forEach((item) => {
        if (item.userId === userId) {
          token = item.token;
        }
      });

      rtc.current
        .join((token as any) || null, roomId, userId)
        .then(() =>
          rtc?.current?.createLocalStream(userId, (res: any) => {
            const { code, msg, devicesStatus } = res;
            if (code === -1) {
              alert(msg);
              setMicOn(false);
              setVideoOn(false);
            }
          })
        )
        .catch((err: any) => {
          console.log('err', err);
          leaveRoom(false);
          setJoinFailReason(JSON.stringify(err));
        });
    })();
  }, [roomId, userId, rtc]);

  const changeMicState = useCallback((): void => {
    if (!rtc.current) return;
    rtc.current.changeAudioState(!isMicOn);
    setMicOn(!isMicOn);
  }, [isMicOn, rtc]);

  const changeVideoState = useCallback((): void => {
    if (!rtc.current) return;
    rtc.current.changeVideoState(!isVideoOn);
    setVideoOn(!isVideoOn);
  }, [isVideoOn, rtc]);

  const handleEventError = (e: any, VERTC: any) => {
    if (e.errorCode === VERTC.ErrorCode.DUPLICATE_LOGIN) {
      message.error('你的账号被其他人顶下线了');
      leaveRoom(false);
    }
  };

  const handleAutoPlayFail = (event: AutoPlayFailedEvent) => {
    console.log('handleAutoPlayFail', event.userId, event);
    const { userId, kind } = event;

    let playUser = playStatus.current?.[userId] || {};
    playUser = { ...playUser, [kind]: false };
    playStatus.current[userId] = playUser;

    addFailUser(userId);
  };

  const addFailUser = (userId: string) => {
    const index = autoPlayFailUser.findIndex((item) => item === userId);
    if (index === -1) {
      autoPlayFailUser.push(userId);
    }
    setAutoPlayFailUser([...autoPlayFailUser]);
  };

  const playerFail = (params: { type: 'audio' | 'video'; userId: string }) => {
    const { type, userId } = params;
    let playUser = playStatus.current?.[userId] || {};

    console.log('pause', event);

    playUser = { ...playUser, [type]: false };

    const { audio, video } = playUser;

    if (audio === false || video === false) {
      addFailUser(userId);
    }
  };

  const handlePlayerEvent = (event: PlayerEvent) => {
    const { userId, rawEvent, type } = event;

    console.log('handlePlayerEvent', event, userId, type, rawEvent.type);

    let playUser = playStatus.current?.[userId] || {};

    if (!playStatus.current) return;

    if (rawEvent.type === 'playing') {
      playUser = { ...playUser, [type]: true };
      const { audio, video } = playUser;
      if (audio !== false && video !== false) {
        const _autoPlayFailUser = autoPlayFailUserdRef.current.filter((item) => item !== userId);
        setAutoPlayFailUser([..._autoPlayFailUser]);
      }
    } else if (rawEvent.type === 'pause') {
      playerFail({ userId, type });
    }

    playStatus.current[userId] = playUser;
    console.log('playStatusplayStatusplayStatus', playStatus);
  };

  const handleAutoPlay = () => {
    const users: string[] = autoPlayFailUser;
    console.log('handleAutoPlay autoPlayFailUser', autoPlayFailUser);
    if (users && users.length) {
      users.forEach((user) => {
        rtc.current?.engine.play(user);
      });
    }
    setAutoPlayFailUser([]);
  };

  useEffect(() => {
    autoPlayFailUserdRef.current = autoPlayFailUser;
  }, [autoPlayFailUser]);

  return (
    <>
      <RTCComponent
        onRef={(ref: any) => (rtc.current = ref)}
        config={{
          ...config,
          roomId,
          uid: '',
        }}
        streamOptions={streamOptions}
        handleUserPublishStream={handleUserPublishStream}
        handleUserUnpublishStream={handleUserUnpublishStream}
        handleUserStartVideoCapture={handleUserStartVideoCapture}
        handleUserStopVideoCapture={handleUserStopVideoCapture}
        handleUserJoin={handleUserJoin}
        handleUserLeave={handleUserLeave}
        handleEventError={handleEventError}
        handleAutoPlayFail={handleAutoPlayFail}
        handlePlayerEvent={handlePlayerEvent}
      />
      <Container>
        <Item>
          <div
            style={{
              width: '100%',
              height: '100%',
              position: 'relative',
              background: '#000',
            }}
            id={'local-player'}
          >
            <span
              style={{
                color: '#fff',
                position: 'absolute',
                bottom: 0,
                right: 0,
                zIndex: 1000,
                maxWidth: 120,
                overflow: 'hidden',
                textOverflow: 'ellipsis',
                whiteSpace: 'nowrap',
              }}
            >
              {userId}
            </span>
          </div>
        </Item>
        {Object.keys(remoteStreams)?.map((key) => {
          const Comp = remoteStreams[key].playerComp;
          return <Item key={key}>{Comp}</Item>;
        })}
      </Container>
      <ControlBar
        RClient={rtc}
        systemConf={[
          {
            moduleName: 'DividerModule',
            moduleProps: {
              width: 2,
              height: 32,
              marginL: 20,
            },
            visible: true,
          },
          {
            moduleName: 'HangUpModule',
            moduleProps: {
              changeHooks: () => {
                leaveRoom(false);
              },
            },
          },
        ]}
        moduleConf={[
          {
            moduleName: 'MicoPhoneControlModule',
            moduleProps: {
              changeHooks: () => changeMicState(),
              isMicOn,
            },
            visible: true,
          },
          {
            moduleName: 'VideoControlModule',
            moduleProps: {
              changeHooks: () => changeVideoState(),
              isVideoOn,
            },
            visible: true,
          },
        ]}
      />
      <AutoPlayModal handleAutoPlay={handleAutoPlay} autoPlayFailUser={autoPlayFailUser} />
    </>
  );
};

export default Meeting;
