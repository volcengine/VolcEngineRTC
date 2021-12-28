import React, {useEffect, useContext} from 'react';
import styled from 'styled-components';
import { ControlBar } from '../../modules';
import {Context} from '../../context';
import useRTC from '../../hook/useRTC';
import MediaPlayer from '../../components/MediaPlayer';

const Container = styled.div`
  width: 100%;
  height: 100%;
  display: grid;
  grid-template-columns: 1fr 1fr;
  grid-template-rows: 1fr 1fr;
`;

const Item = styled.div`
`;

const Meeting: React.FC<Record<string, unknown>> = () => {
  const {
    join,
    client,
    isMicOn,
    changeMicState,
    isVideoOn,
    changeVideoState,
    userList,
    leaveRoom,
  } = useRTC();

  const {roomId, userId, setJoin} = useContext(Context);

  useEffect(() => {
    if (!roomId || !userId) return;
    join(roomId, userId);
  }, [join, roomId, userId]);

  return (
    <>
      <Container>
        {userList?.map((key, index: number) => (
          <Item key={index}>
            {key ? (
              <MediaPlayer stream={key['stream']} userId={key['userId']} />
            ) : null}
          </Item>
        ))}
      </Container>
      <ControlBar
        RClient={client}
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
                setJoin(false);
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