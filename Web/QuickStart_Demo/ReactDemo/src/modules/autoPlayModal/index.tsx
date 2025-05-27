/**
 * Copyright 2024 Beijing Volcano Engine Technology Co., Ltd. All Rights Reserved.
 * SPDX-license-identifier: BSD-3-Clause
 */

import React, { useEffect, useState } from 'react';
import { Modal, Button } from 'antd';
import styled from 'styled-components';

const ModalWrapper = styled(Modal)`
  .ant-modal-body {
    min-height: 150px;
    display: flex;
    flex-direction: column;
    justify-content: center;
  }
`;

const ButtonWrapper = styled(Button)`
  font-weight: 700;
  background-color: black;
  color: white;
  text-align: center;
  font-size: 1em;
  cursor: pointer;
  border: none;
  font-weight: 600;
  :active {
    background-color: black;
    color: white;
  }
  :hover {
    background-color: rgba(0, 0, 0, 0.8);
    color: white;
  }
  :focus {
    background-color: black;
    color: white;
  }
`;

type AutoPlayModalProps = { handleAutoPlay: () => void; autoPlayFailUser: string[] };

const AutoPlayModal: React.FC<AutoPlayModalProps> = ({ handleAutoPlay, autoPlayFailUser }) => {
  const [visible, setVisible] = useState<boolean>(false);

  useEffect(() => {
    setVisible(autoPlayFailUser.length ? true : false);
  }, [autoPlayFailUser]);

  return (
    <ModalWrapper
      footer={null}
      closable={false}
      width={450}
      visible={visible}
      style={{ top: '20%', minHeight: 150 }}
    >
      <ButtonWrapper block size="large" onClick={handleAutoPlay}>
        自动播放
      </ButtonWrapper>
    </ModalWrapper>
  );
};

export default AutoPlayModal;
