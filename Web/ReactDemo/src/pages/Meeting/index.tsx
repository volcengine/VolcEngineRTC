import React, {
  useState,
  useContext,
  useEffect,
  useCallback,
  useRef,
} from 'react';
import { message } from 'antd';
import styled from 'styled-components';
import { ControlBar } from '../../modules';
import {Context} from '../../context';

import RTCComponent from '../../sdk/rtc-component';
import {RTCClient, Stream} from '../../app-interfaces';
import { streamOptions } from './constant';
import config from '../../config';
import MediaPlayer from '../../components/MediaPlayer';

const Container = styled.div`
  width: 100%;
  height: 100%;
  display: flex;
  flex-wrap: wrap;
`;

const Item = styled.div`
  flex: 1;
  width: 50%;
  min-width: 50%;
  max-width: 50%;
  height: 50%;
  position: relative;
`;

const Meeting: React.FC<Record<string, unknown>> = () => {
  const {roomId, userId, setJoin} = useContext(Context);
  const [isMicOn, setMicOn] = useState<boolean>(true);
  const [isVideoOn, setVideoOn] = useState<boolean>(true);
  const rtc = useRef<RTCClient>();

  const count = useRef<number>(0);
  const [remoteStreams, setRemoteStreams] = useState<{
    [key: string]: Stream;
  }>({});

  const leaveRoom = useCallback(() => {
    if (!rtc.current) return;
    rtc.current.leave();

    // off the event
    rtc.current.removeEventListener();
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

  const handleStreamAdd = useCallback((event: any) => {
    const stream = event.stream;
    const userId = stream.userId;

    if (count.current < 3) {
      if (remoteStreams[userId]) return;
      remoteStreams[userId] = stream;
      stream.playerComp = (
        <MediaPlayer
          userId={userId}
          stream={stream}
          setRemoteVideoPlayer={rtc?.current?.setRemoteVideoPlayer}
        />
      );
      setRemoteStreams({
        ...remoteStreams,
      });
      count.current += 1;
    }
  }, [remoteStreams]);

  /**
   * @brief remove stream & update remote streams list
   * @param {Event} event
   */
  const handleStreamRemove = useCallback(
    (event: any) => {
      const uid = event.stream.userId;
      if (remoteStreams[uid]) {
        delete remoteStreams[uid];
      }
      setRemoteStreams({
        ...remoteStreams,
      });
      count.current--;
    },
    [remoteStreams],
  );

  useEffect(() => {
    (async () => {
      if (!roomId || !userId || !rtc.current) return;
      rtc.current.bindEngineEvents();
      rtc
        .current.join(config.token, roomId, userId)
        .then(() =>
          rtc?.current?.createLocalStream((res: any) => {
            const {code, msg, devicesStatus} = res;
            if (code === -1) {
              alert(msg);
              setMicOn(false);
              setVideoOn(false);
            } else {
              if (devicesStatus['audio'] === 0) {
                setMicOn(false);
              }
              if (devicesStatus['video'] === 0) {
                setMicOn(false);
              }
            }
          }),
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
        handleStreamAdd={handleStreamAdd}
        handleStreamRemove={handleStreamRemove}
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