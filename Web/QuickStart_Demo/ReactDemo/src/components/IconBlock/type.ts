/**
 * Copyright 2024 Beijing Volcano Engine Technology Co., Ltd. All Rights Reserved.
 * SPDX-license-identifier: BSD-3-Clause
 */

import { ReactEventHandler } from 'react';

export default interface IIconBlockProps {
  size?: number;
  radius?: number;
  shape?: 'circle' | 'square';
  onClick?: ReactEventHandler;
  children?: React.ReactNode;
// eslint-disable-next-line semi
}