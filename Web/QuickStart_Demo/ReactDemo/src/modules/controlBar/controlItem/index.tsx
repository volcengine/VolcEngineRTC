/**
 * Copyright 2024 Beijing Volcano Engine Technology Co., Ltd. All Rights Reserved.
 * SPDX-license-identifier: BSD-3-Clause
 */

import MicoPhoneControlModule from './microPhone';
import VideoControlModule from './videoControl';

type modulesOptions = {
  [key: string]: React.FC<any>;
};

const controlModules: modulesOptions = {
  MicoPhoneControlModule,
  VideoControlModule,
};

export default controlModules;