import config from '../config';
import {
  RTCClient,
  Stream,
  SubscribeOption,
  DeviceInstance,
  StreamOption,
} from '../app-interfaces';
import { byteStreamInitial } from './constant';
import RTCSDK from '../lib/VRTC.min';

type Token = {
  [key: string]: string
}

/**
 * @callbacks
 * @param {Stream} rtc stream
 */
type createStreamCallback = (stream: Stream) => void;

/**
 * @callbacks
 * @param {RTCClient} param
 */
type createClientCallback = (param: RTCClient) => void;

/**
* @brief RTC lib
* @type api
* @module RTC
*/
class RTC {
  public client!: RTCClient;
  public audioInputs!: DeviceInstance[];
  public videoInputs!: DeviceInstance[];

  constructor() {}

  /**
   * @brief create rtc client
   * @param {createClientCallback} Callback after creating client successfully
   * @returns {VoidFunction}
   */
  public createClient(callback: createClientCallback): void {
    this.client = RTCSDK.createClient({});
    this.client.init(config.appId, () => callback(this.client));
  }

  /**
   * @brief join room
   * @param {string} roomId
   * @param {string} userId
   * @returns {Promise<RTClient>}  resolve rtc client
   */
  public async join(roomId: string, userId: string): Promise<RTCClient> {
    return new Promise((resolve, reject) => {
      this.createClient((client) => {
        this.client.join(
          (config.token as Token)?.[userId],
          roomId,
          userId,
          () => {
            resolve(client);
          },
          (err: unknown) => {
            reject(err);
          },
        );
      });
    });
  }

  /**
   * @brief subscribe stream
   * @param {Stream} byteStream
   * @param {SubscribeOption?} option
   * @returns {VoidFunction}
   */
  public subscribe(byteStream: Stream, option?: SubscribeOption): void {
    this.client.subscribe(byteStream, option);
  }

  /**
   * @brief check video and audio permission
   * @returns {Promise<[{audio: boolean}, {video: boolean}]>} resolve audio and video permission state
   */
  public checkPermission(): Promise<[{audio: boolean}, {video: boolean}]> {
    const checkAudio = new Promise((resolve) => {
      RTCSDK.checkAudioPermission(
        () => resolve({audio: true}),
        () => resolve({audio: false}),
      );
    }) as Promise<{audio: boolean}>;
    const checkVidoe = new Promise((resolve) => {
      RTCSDK.checkVideoPermission(
        () => resolve({video: true}),
        () => resolve({video: false}),
      );
    }) as Promise<{video: boolean}>;
    return Promise.all([checkAudio, checkVidoe]);
  }

  /**
   * @brief get video and audio inputs
   * @returns {Promise<{ audioInputs: DeviceInstance[]; videoInputs: DeviceInstance[] }>} resolve video and audio inputs array
   */
  public getDevices(): Promise<{
    audioInputs: DeviceInstance[];
    videoInputs: DeviceInstance[];
  }> {
    return new Promise((resolve, reject) => {
      RTCSDK.getDevices(
        (inputs: DeviceInstance[]) => {
          this.audioInputs = inputs.filter((input) => {
            return input.kind === 'audioinput';
          });
          this.videoInputs = inputs.filter((input) => {
            return input.kind === 'videoinput';
          });
          resolve({
            audioInputs: this.audioInputs,
            videoInputs: this.videoInputs,
          });
        },
        (err: Error) => {
          reject(`get devices error at ${err.message}`);
        },
      );
    });
  }

  /**
   * @brief create rtc stream
   * @param {StreamOption} param
   * @param {createStreamCallback} callback
   * @returns {VoidFunction}
   */
  public createStream(
    param: StreamOption,
    callback: createStreamCallback,
  ): void {
    const stream = RTCSDK.createStream(param);

    stream.setVideoEncoderConfiguration(byteStreamInitial);

    stream.init(
      () => {
        if (param.video) {
          stream.unmuteVideo();
        } else {
          stream.muteVideo();
        }
        if (param.audio) {
          stream.unmuteAudio();
        } else {
          stream.muteAudio();
        }
        this.client.publish(stream);
        callback(stream);
      },
      (err: Error) => {
        alert(err);
      },
    );
  }

  /**
   * @brief leave room
   * @returns {VoidFunction}
   */
  public leave(): void {
    this.client.leave();
  }
}

export default RTC;