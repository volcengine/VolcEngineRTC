import '@douyin-microapp/typings';

declare module '@douyin-microapp/typings/types/api' {
    /**
     *  通过 tt.createRtcRoomContext 获取的实例。
     * 
     *  [文档](https://developer.open-douyin.com/docs/resource/zh-CN/mini-app/develop/api/media/rtc-room/rtc-room-context/overview)
     */
    export interface RtcRoomContext {
        [key: string]: any;
    }

    /**
     * @see https://developer.open-douyin.com/docs/resource/zh-CN/mini-app/develop/api/media/rtc-room/tt-create-rtc-room-context
     * @param options 
     */
    export function createRtcRoomContext(options: {
        /**
         * 每个应用的唯一标识符，由 RTC 控制台随机生成的。不同的 appId 生成的实例在 RTC 中进行音视频通话完全独立，无法互通。
         * 
         * [文档](https://www.volcengine.com/docs/6348/69865) 
         */
        appId: string;
    }): RtcRoomContext;
}

declare module '@douyin-microapp/typings' {
    export interface OnRtcVideoMembersChangedEvent {
        userIdList: string[];
        errCode?: string;
        errMsg?: string;
    }

    export interface OnRtcChatSpeakersChangedEvent {
        userIdList: string[];
        errCode?: string;
        errMsg?: string;
    }

    export interface OnRtcChatMembersChangedEvent {
        userIdList: string[];
        errCode?: string;
        errMsg?: string;
    } 

    export interface OnRtcPublishScreenMembersChangedEvent {
        userIdList: string[];
        errCode?: string;
        errMsg?: string;
    }
}
