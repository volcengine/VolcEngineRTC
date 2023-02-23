import React, { useState } from 'react';
import 'antd/dist/antd.css';
import styled from 'styled-components';
import VERTC from '@volcengine/rtc';


import LogoHeaderImg from 'src/assets/images/header_logo.png';
import JoinRoom from './pages/JoinRoom';
import Meeting from './pages/Meeting';
import { Context } from './context';
import { getQueryString } from './utils';

const head = '64px';

const HeaderWrapper = styled.div`
  padding: 0px 22px;
  width: 100%;
  height: ${head};
  background: #0a1e39;
  z-index: 1000;
  position: relative;
  display: flex;
  flex-direction: row;
  align-items: center;
`;

const ContentWrapper = styled.div`
  height: calc(100vh - ${head});
  background: #c4c4c4;
`;

const Logo = styled.div`
  display:flex;
  flex-direction: row;
  height: 60%;
  flex: 1;
`;

const SDKVersion = styled.span`
  float: right;
  color: #ffffff;
  font-size: 12px;
  line-height: 64px;
  font-weight: 600;
  font-family: PingFang SC;
`;

const RoomId = styled.div`
  text-align: center;
  font-family: PingFang SC;
  font-size: 16px;
  font-weight: 600;
  line-height: 64px;
  color: #ffffff;
  max-width: 120px;
  overflow: hidden;
  text-overflow: ellipsis;
  white-space: nowrap;
`;

/**
 * 模块描述
 * @module App index
 */
const App: React.FC<Record<string, unknown>> = () => {
  const [hasJoin, setJoin] = useState(false);
  const [userId, setUserId] = useState<string>(getQueryString('userId') || '');
  const [roomId, setRoomId] = useState<string>(getQueryString('roomId') || '');

  return (
    <Context.Provider
      value={{hasJoin, userId, roomId, setUserId, setRoomId, setJoin}}
    >
      <HeaderWrapper>
        <Logo>
          <img src={LogoHeaderImg} />
        </Logo>
        {hasJoin ? (
          <RoomId>{roomId}</RoomId>
        ) : (
          <SDKVersion>RTC版本 v{VERTC.getSdkVersion()}</SDKVersion>
        )}
      </HeaderWrapper>
      <ContentWrapper>
        {hasJoin ? <Meeting /> : <JoinRoom joinRoom={() => setJoin(true)} />}
      </ContentWrapper>
    </Context.Provider>
  );
};

export default App;