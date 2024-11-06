/**
 * Copyright 2024 Beijing Volcano Engine Technology Co., Ltd. All Rights Reserved.
 * SPDX-license-identifier: BSD-3-Clause
 */

import styled from 'styled-components';
import IProps from './type';

const DividerWrapper = styled.div`
  width: ${(props: IProps) => props.width || 24}px;
  height: ${(props: IProps) => props.height || 24}px;
  background: ${(props: IProps) => props.bgColor || '#E5E5E5'};
  margin-left: ${(props: IProps) => props.marginL || 20}px;
`;

export default DividerWrapper;