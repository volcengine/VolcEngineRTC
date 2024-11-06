/**
 * Copyright 2024 Beijing Volcano Engine Technology Co., Ltd. All Rights Reserved.
 * SPDX-license-identifier: BSD-3-Clause
 */

export const TEXTMAP = {
  'room-id': '房间ID',
  'user-id': '用户ID',
};
export const isMicOn = false; // control the mic
export const isVideoOn = false; // control the video

/**
 * On initiation. `engine` will use the object to config the stream.
 */
export const initStreamOption = {
  resolution: {
    width: 640,
    height: 480,
  },
  frameRate: {
    min: 10,
    max: 15,
  },
  bitrate: {
    min: 250,
    max: 600,
  },
};

/**
 * On initiation. `engine` will use the object to config the stream.
 */
export const streamOptions = {
  audio: true,
  video: true,
};
