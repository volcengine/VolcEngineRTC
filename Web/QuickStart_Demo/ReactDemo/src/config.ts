/**
 * Copyright 2024 Beijing Volcano Engine Technology Co., Ltd. All Rights Reserved.
 * SPDX-license-identifier: BSD-3-Clause
 */

/*
 * On initiation. `engine` is not attached to any project or room for any specific user.
 */

const config = {
  appId: 'yourAppId',
  roomId: 'yourRoomId',
  tokens: [
    {
      userId: 'yourUserId1',
      token: 'yourToken1',
    },
    {
      userId: 'yourUserId2',
      token: 'yourToken2',
    }
  ],
};

export default config;
