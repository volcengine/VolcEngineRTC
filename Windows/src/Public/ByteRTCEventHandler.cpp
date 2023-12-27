#include "ByteRTCEventHandler.h"
#include <QMetaType>
#include <QDebug>


ByteRTCRoomHandler::ByteRTCRoomHandler() {


}
ByteRTCRoomHandler::ByteRTCRoomHandler(std::string roomid, std::string uid)
{
    m_roomid = roomid;
    m_uid = uid;
}

ByteRTCRoomHandler::~ByteRTCRoomHandler() {
    qDebug() << Q_FUNC_INFO;
}

std::string ByteRTCRoomHandler::getRoomID()
{
    return m_roomid;
}

void ByteRTCRoomHandler::onTokenWillExpire()
{
    /*
    Token 进房权限过期前 30 秒将触发该回调。<br>
    *收到该回调后，你需调用 updateToken 更新 Token 进房权限。
    * 
    */
    emit sigTokenWillExpire();
}


void ByteRTCRoomHandler::onRoomStateChanged(const char* room_id, const char* uid, int state, const char* extra_info)
{
    std::string strroom, struid, strextra;
    strroom = room_id == nullptr ? "" : room_id;
    struid = uid == nullptr ? "" : uid;
    strextra = extra_info == nullptr ? "" : extra_info;
    emit sigRoomStateChanged(strroom, struid, state, strextra);
}

void ByteRTCRoomHandler::onUserPublishStream(const char* uid, bytertc::MediaStreamType type)
{
    std::string struid = uid == nullptr ? "" : uid;
    emit sigUserPublishStream(m_roomid, struid, type);
}

void ByteRTCRoomHandler::onUserUnpublishStream(const char* uid, bytertc::MediaStreamType type, bytertc::StreamRemoveReason reason)
{
    std::string struid = uid == nullptr ? "" : uid;
    emit sigUserUnPublishStream(m_roomid, struid, type, reason);
}

void ByteRTCRoomHandler::onUserJoined(const bytertc::UserInfo& user_info, int elapsed)
{
    ByteRTCRoomHandler::UserInfo info;
    info.roomid = m_roomid;
    info.uid = user_info.uid == nullptr ? "" : user_info.uid;
    info.extra_info = user_info.extra_info == nullptr ? "" : user_info.extra_info;
    emit sigUserJoined(info, elapsed);
}

void ByteRTCRoomHandler::onUserLeave(const char* uid, bytertc::UserOfflineReason reason)
{
    std::string struid = uid == nullptr ? "" : uid;
    emit sigUserLeave(m_roomid, struid, reason);
}

void ByteRTCRoomHandler::onLeaveRoom(const bytertc::RtcRoomStats& stats)
{
    emit sigLeaveRoom(m_roomid, m_uid, stats);
}






void ByteRTCRoomHandler::onForwardStreamStateChanged(bytertc::ForwardStreamStateInfo* infos, int info_count) {

    std::vector<ByteRTCRoomHandler::Stru_ForwardStreamStateInfo> result;

    for (int i = 0; i < info_count; i++) {
        ByteRTCRoomHandler::Stru_ForwardStreamStateInfo info;
        int tmp = info_count - 1;
        info.error = infos[tmp].error;
        info.roomid = infos[tmp].room_id;
        info.state = infos[tmp].state;
        result.push_back(info);
    }

    emit sigForwardStreamStateChanged(result);
}


ByteRTCEventHandler::ByteRTCEventHandler(QObject* parent)
    : QObject{ parent }
{
    qRegisterMetaType<std::string>();
    qRegisterMetaType<int64_t>();
    qRegisterMetaType<bytertc::RtcRoomStats>();
    qRegisterMetaType<bytertc::PlayerState>();
    qRegisterMetaType<bytertc::PlayerError>();
    qRegisterMetaType<bytertc::MediaStreamType>();
    qRegisterMetaType<bytertc::StreamRemoveReason>();
    qRegisterMetaType<bytertc::StreamMixingEvent>();
    qRegisterMetaType<bytertc::StreamMixingErrorCode>();
    qRegisterMetaType<bytertc::MixedStreamType>();

    qRegisterMetaType<ByteRTCRoomHandler::Stru_ForwardStreamStateInfo>("ByteRTCRoomHandler::Stru_ForwardStreamStateInfo");
    qRegisterMetaType<std::vector<ByteRTCRoomHandler::Stru_ForwardStreamStateInfo>>("std::vector<ByteRTCRoomHandler::Stru_ForwardStreamStateInfo>");
    qRegisterMetaType<ByteRTCRoomHandler::Stru_ForwardStreamEvent>("ByteRTCRoomHandler::Stru_ForwardStreamEvent");
    qRegisterMetaType<std::vector<ByteRTCRoomHandler::Stru_ForwardStreamEvent>>("std::vector<ByteRTCRoomHandler::Stru_ForwardStreamEvent>");
    qRegisterMetaType<ByteRTCRoomHandler::UserInfo>();
    qRegisterMetaType<bytertc::RTCAudioDeviceType>();
    qRegisterMetaType<bytertc::MediaDeviceState>();
    qRegisterMetaType<bytertc::MediaDeviceError>();
    qRegisterMetaType<bytertc::UserOfflineReason>();
    qRegisterMetaType<bytertc::RemoteStreamKey>();
    qRegisterMetaType<bytertc::VideoFrameInfo>();
    qRegisterMetaType<bytertc::StreamIndex>();
    
}

ByteRTCEventHandler::~ByteRTCEventHandler()
{
    qDebug() << Q_FUNC_INFO;
}

void ByteRTCEventHandler::setIsSupportClientPushStream(bool support) {
    m_supportClientPushStream = support;
}

void ByteRTCEventHandler::onWarning(int warn)
{
    emit sigWarning(warn);
}

void ByteRTCEventHandler::onError(int err)
{
    emit sigError(err);
}

void ByteRTCEventHandler::onConnectionStateChanged(bytertc::ConnectionState state)
{
    emit sigConnectionStateChanged(state);
}

void ByteRTCEventHandler::onNetworkTypeChanged(bytertc::NetworkType type)
{
    emit sigNetworkTypeChanged(type);
}

void ByteRTCEventHandler::onAudioDeviceStateChanged(const char *device_id, bytertc::RTCAudioDeviceType device_type, bytertc::MediaDeviceState device_state, bytertc::MediaDeviceError device_error)
{
    std::string str_device_id = device_id == nullptr ? "" : device_id;
    emit sigAudioDeviceStateChanged(str_device_id, device_type, device_state, device_error);
}

void ByteRTCEventHandler::onVideoDeviceStateChanged(const char *device_id, bytertc::RTCVideoDeviceType device_type, bytertc::MediaDeviceState device_state, bytertc::MediaDeviceError device_error)
{
    std::string str_device_id = device_id == nullptr ? "" : device_id;
    emit sigVideoDeviceStateChanged(str_device_id, device_type, device_state, device_error);
}

void ByteRTCEventHandler::onAudioDeviceWarning(const char *device_id, bytertc::RTCAudioDeviceType device_type, bytertc::MediaDeviceWarning device_warning)
{
    std::string str_device_id = device_id == nullptr ? "" : device_id;
    emit sigAudioDeviceWarning(str_device_id, device_type, device_warning);
}

void ByteRTCEventHandler::onVideoDeviceWarning(const char *device_id, bytertc::RTCVideoDeviceType device_type, bytertc::MediaDeviceWarning device_warning)
{
    std::string str_device_id = device_id == nullptr ? "" : device_id;
    emit sigVideoDeviceWarning(str_device_id, device_type, device_warning);
}

void ByteRTCEventHandler::onSysStats(const bytertc::SysStats &stats)
{
    emit sigSysStats(stats);
}

void ByteRTCEventHandler::onLocalVideoSizeChanged(bytertc::StreamIndex index, const bytertc::VideoFrameInfo &info)
{
    qDebug() << Q_FUNC_INFO << "index:" << index << ",w=" << info.width << ",h=" << info.height << ",rotation=" << info.rotation;
    emit sigLocalVideoSizeChanged(index, info);
}

void ByteRTCEventHandler::onFirstLocalVideoFrameCaptured(bytertc::StreamIndex index, bytertc::VideoFrameInfo info)
{
    emit sigFirstLocalVideoFrameCaptured(index, info);
}

void ByteRTCEventHandler::onFirstLocalAudioFrame(bytertc::StreamIndex index)
{
    emit sigFirstLocalAudioFrame(index);
}

void ByteRTCEventHandler::onAudioEffectPlayerStateChanged(int effect_id, bytertc::PlayerState state, bytertc::PlayerError error)
{
    emit sigAudioEffectPlayerStateChanged(effect_id, state, error);
}

bool ByteRTCEventHandler::isSupportClientPushStream()
{
    return m_supportClientPushStream;
}

void ByteRTCEventHandler::onMixingEvent(bytertc::StreamMixingEvent event, const char* task_id, bytertc::StreamMixingErrorCode error, bytertc::MixedStreamType mix_type)
{
    if (task_id == nullptr) return;
    std::string str_task_id = task_id;
    emit sigMixingEvent(event, str_task_id, error, mix_type);
}

void ByteRTCEventHandler::onMixingVideoFrame(const char* task_id, bytertc::IVideoFrame* video_frame)
{
}

void ByteRTCEventHandler::onMixingAudioFrame(const char* task_id, bytertc::IAudioFrame* audio_frame)
{
}

void ByteRTCEventHandler::onMixingDataFrame(const char* task_id, bytertc::IDataFrame* data_frame)
{
}

void ByteRTCEventHandler::onCacheSyncVideoFrames(const char* task_id, const char* uids[], bytertc::IVideoFrame* video_frames[], bytertc::IDataFrame* data_frame[], int count)
{


}

void ByteRTCEventHandler::onMediaPlayerStateChanged(int playerId, bytertc::PlayerState state, bytertc::PlayerError error)
{
    emit sigMediaPlayerStateChanged(playerId, state, error);
}

void ByteRTCEventHandler::onMediaPlayerPlayingProgress(int playerId, int64_t progress)
{
    emit sigMediaPlayerPlayingProgress(playerId, progress);
}

void ByteRTCEventHandler::onFirstRemoteVideoFrameRendered(const bytertc::RemoteStreamKey key, const bytertc::VideoFrameInfo& info)
{
    qDebug() << Q_FUNC_INFO << "roomid=" << key.room_id << ",uid=" << key.user_id << ",width=" << info.width << ",height=" << info.height << ",rotation=" << info.rotation;
    ByteRTCEventHandler::Stru_RemoteStreamKey skey;
    skey.room_id = key.room_id == nullptr ? "" : key.room_id;
    skey.user_id = key.user_id == nullptr ? "" : key.user_id;
    skey.stream_index = key.stream_index;

    emit sigFirstRemoteVideoFrameRendered(skey, info);
}

void ByteRTCEventHandler::onFirstRemoteVideoFrameDecoded(const bytertc::RemoteStreamKey key, const bytertc::VideoFrameInfo &info)
{
    qDebug() << Q_FUNC_INFO << "roomid=" << key.room_id << ",uid=" << key.user_id << ",w=" << info.width << ",h=" << info.height << ",rotation=" << info.rotation;
}

void ByteRTCRoomHandler::onForwardStreamEvent(bytertc::ForwardStreamEventInfo* infos, int info_count)
{
    std::vector<Stru_ForwardStreamEvent> events;
    for (int i = 0; i < info_count; i++) {
        Stru_ForwardStreamEvent event;
        event.roomid = infos[i].room_id;
        event.event = infos[i].event;
        events.push_back(event);
    }

    emit sigForwardStreamEvent(events);
}
