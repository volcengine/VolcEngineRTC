import React, { useState, useContext, useEffect, useCallback, useRef } from 'react';
import { message } from 'antd';
import styled from 'styled-components';
import { MediaType, onUserJoinedEvent, onUserLeaveEvent } from '@volcengine/rtc';
import { ControlBar } from '../../modules';
import { Context } from '../../context';

import RTCComponent from '../../sdk/rtc-component';
import { RTCClient, Stream } from '../../app-interfaces';
import { streamOptions } from './constant';
import config from '../../config';
import MediaPlayer from '../../components/MediaPlayer';

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
  const { roomId, userId, setJoin } = useContext(Context);
  const [isMicOn, setMicOn] = useState<boolean>(true);
  const [isVideoOn, setVideoOn] = useState<boolean>(true);
  const rtc = useRef<RTCClient>();

  const [remoteStreams, setRemoteStreams] = useState<{
    [key: string]: {
      playerComp: React.ReactNode;
    };
  }>({});

  const leaveRoom = useCallback(() => {
    if (!rtc.current) return;

    // off the event
    rtc.current.removeEventListener();

    rtc.current.leave();
    setJoin(false);
  }, [rtc, setJoin]);

  /**
   * @brief call leaveRoom function when the browser window closes or refreshes
   */
  useEffect(() => {
    window.addEventListener('beforeunload', leaveRoom);
    return () => {
      leaveRoom();
      window.removeEventListener('beforeunload', leaveRoom);
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
      rtc.current.bindEngineEvents();
      rtc.current
        .join((config.token as any)?.[userId] || null, roomId, userId)
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
        .catch((err: any) => console.log('err', err));
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
      leaveRoom();
    }
  };

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
                leaveRoom();
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
    </>
  );
};

export default Meeting;
