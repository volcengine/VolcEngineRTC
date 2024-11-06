/**
 * Copyright 2024 Beijing Volcano Engine Technology Co., Ltd. All Rights Reserved.
 * SPDX-license-identifier: BSD-3-Clause
 */

import styled from 'styled-components';
import IProps from './type';

const IconBlockWrapper = styled.div`
  display: flex;
  justify-content: center;
  align-items: center;
  cursor: pointer;
  transition: background-color 0.3s ease;
  user-select: none;

  border-radius: ${({shape = 'circle', radius}: IProps) => shape === 'circle' ? '50%' : radius};
  width: ${(props: IProps) => props.size || 24}px;
  &:hover {
    background: darken(#f2f3f5, 5%);
  }
  img {
    width: 100%;
    display: block;
  }
`;

const StyledComp = {
  IconBlockWrapper,
};

export default StyledComp;