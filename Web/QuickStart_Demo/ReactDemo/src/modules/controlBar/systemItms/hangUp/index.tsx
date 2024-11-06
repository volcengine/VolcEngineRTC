/**
 * Copyright 2024 Beijing Volcano Engine Technology Co., Ltd. All Rights Reserved.
 * SPDX-license-identifier: BSD-3-Clause
 */

import React from 'react';
import {ILeaveRoomProps} from './type';
import leaveIcon from 'src/assets/images/leaveIcon.png';
import IconBlock from 'src/components/IconBlock';

const commonProps = {
  size: 28,
  style: {background: 'transparent', margin: 0},
};

const HangUpModule: React.FC<ILeaveRoomProps> = ({changeHooks}) => {
  return (
    <IconBlock onClick={() => changeHooks && changeHooks()} {...commonProps}>
      <img src={leaveIcon} alt='leave' />
    </IconBlock>
  );
};

export default HangUpModule;