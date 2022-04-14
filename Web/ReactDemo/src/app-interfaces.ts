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
  join: (...args: any[]) => any;
  publish: (...args: any[]) => Promise<void>;
  unpublish: (...args: any[]) => Promise<void>;
  subscribe: (...args: any[]) => void;
  leave: (...args: any[]) => void;
  on: (...args: any[]) => void;
  off: (...args: any[]) => void;
  setupLocalVideoPlayer: (...args: any[]) => void;
  createLocalStream: (...args: any[]) => void;
  setRemoteVideoPlayer: (...args: any[]) => void;
  removeEventListener: (...args: any[]) => void;
  changeAudioState: (...args: any[]) => void;
  changeVideoState: (...args: any[]) => void;
  bindEngineEvents: (...args: any[]) => void;
}


export interface Stream {
  userId: string;
  hasAudio: boolean;
  hasVideo: boolean;
  isScreen: boolean;
  videoStreamDescriptions: any[]
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
  playerComp: any;
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