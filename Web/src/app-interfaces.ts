export interface AudioStats {
  CodecType: string;
  End2EndDelay: number;
  MuteState: boolean;
  PacketLossRate: number;
  RecvBitrate: number;
  RecvLevel: number;
  TotalFreezeTime: number;
  TotalPlayDuration: number;
  TransportDelay: number;
}

export interface RTCClient {
  init: (...args: any[]) => void;
  join: (...args: any[]) => void;
  publish: (...args: any[]) => Promise<void>;
  unpublish: (...args: any[]) => Promise<void>;
  subscribe: (...args: any[]) => void;
  leave: (...args: any[]) => void;
  on: (...args: any[]) => void;
  off: (...args: any[]) => void;
}


export interface Stream {
  uid: string;
  stream: {
    screen: boolean;
  };
  getId: () => string;
  enableAudio: () => void;
  disableAudio: () => void;
  enableVideo: () => void;
  disableVideo: () => void;
  close: () => void;
  init: (...args: any[]) => void;
  play: (id: string, options?: any) => void;
  setVideoEncoderConfiguration: (...args: any[]) => void;
  getStats(): any;
  getAudioLevel(): number;
}

export type SubscribeOption = {
  video?: boolean;
  audio?: boolean;
};

export type DeviceInstance = {
  deviceId: string;
  groupId: string;
  kind: 'audioinput' | 'audiooutput' | 'videoinput';
  label: string;
};

export type StreamOption = {
  audio: boolean;
  video: boolean;
  data?: boolean;
  screen?: boolean;
  mediaStream?: MediaStream;
  microphoneId?: string;
  cameraId?: string;
};