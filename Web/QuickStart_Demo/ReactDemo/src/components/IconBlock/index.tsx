/**
 * Copyright 2024 Beijing Volcano Engine Technology Co., Ltd. All Rights Reserved.
 * SPDX-license-identifier: BSD-3-Clause
 */

import React from 'react';

import IIconBlockProps from './type';
import SC from './style';

const IconBlock: React.FC<IIconBlockProps> = (props) => {
  const {children, ...restProps} = props;
  return <SC.IconBlockWrapper {...restProps}>{children}</SC.IconBlockWrapper>;
};

export default IconBlock;
