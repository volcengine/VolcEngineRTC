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

void ByteRTCRoomHandler::onUserPublishStreamAudio(const char* stream_id, const bytertc::StreamInfo& stream_info, bool is_publish)
{

    if (stream_id == nullptr || stream_info.room_id == nullptr || stream_info.user_id == nullptr) return;
    std::string s_stream_id(stream_id);
    std::string s_room(stream_info.room_id);
    std::string s_uid(stream_info.user_id);
    qDebug() << Q_FUNC_INFO 
             << "stream_id:" << QString::fromStdString(s_stream_id)
             << "roomid:" << QString::fromStdString(s_room)
             << ",uid:" << QString::fromStdString(s_uid)
             << ",is_publish:" << is_publish;
    emit sigUserPublishStreamAudio(s_stream_id, s_room, s_uid, is_publish);
}

void ByteRTCRoomHandler::onUserPublishStreamVideo(const char* stream_id, const bytertc::StreamInfo& stream_info, bool is_publish)
{
    if (stream_id == nullptr || stream_info.room_id == nullptr || stream_info.user_id == nullptr) return;
    std::string s_stream_id(stream_id);
    std::string s_room(stream_info.room_id);
    std::string s_uid(stream_info.user_id);
    emit sigUserPublishStreamVideo(s_stream_id, s_room, s_uid, is_publish);
}

//void ByteRTCRoomHandler::onUserPublishScreenVideo(const char *room_id, const char *uid, bool is_publish)
//{
//    if (room_id == nullptr || uid == nullptr) return;
//    std::string s_room(room_id);
//    std::string s_uid(uid);
//    emit sigUserPublishScreenVideo(s_room, s_uid, is_publish);
//}
//
//void ByteRTCRoomHandler::onUserPublishScreenAudio(const char *room_id, const char *uid, bool is_publish)
//{
//    if (room_id == nullptr || uid == nullptr) return;
//    std::string s_room(room_id);
//    std::string s_uid(uid);
//    emit sigUserPublishScreenAudio(s_room, s_uid, is_publish);
//}

//void ByteRTCRoomHandler::onUserPublishStream(const char* uid, bytertc::MediaStreamType type)
//{
//    std::string struid = uid == nullptr ? "" : uid;
//    emit sigUserPublishStream(m_roomid, struid, type);
//}

//void ByteRTCRoomHandler::onUserUnpublishStream(const char* uid, bytertc::MediaStreamType type, bytertc::StreamRemoveReason reason)
//{
//    std::string struid = uid == nullptr ? "" : uid;
//    emit sigUserUnPublishStream(m_roomid, struid, type, reason);
//}

//void ByteRTCRoomHandler::onUserUnpublishScreen(const char *uid, bytertc::MediaStreamType type, bytertc::StreamRemoveReason reason)
//{
//    std::string struid = uid == nullptr ? "" : uid;
//    emit sigUserUnPublishScreen(m_roomid, struid, type, reason);

//}

//void ByteRTCRoomHandler::onUserPublishScreen(const char *uid, bytertc::MediaStreamType type)
//{
//    std::string struid = uid == nullptr ? "" : uid;
//    emit sigUserPublishScreen(m_roomid, struid, type);

//}

void ByteRTCRoomHandler::onUserJoined(const bytertc::UserInfo& user_info)
{
    ByteRTCRoomHandler::UserInfo info;
    info.roomid = m_roomid;
    info.uid = user_info.uid == nullptr ? "" : user_info.uid;
    info.extra_info = user_info.extra_info == nullptr ? "" : user_info.extra_info;
    emit sigUserJoined(info);
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
        qDebug() << Q_FUNC_INFO << i << infos[i].room_id << infos[i].state << infos[i].error;
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
//    qRegisterMetaType<bytertc::StreamMixingEvent>();
//    qRegisterMetaType<bytertc::StreamMixingErrorCode>();
    qRegisterMetaType<bytertc::MixedStreamType>();

    qRegisterMetaType<bytertc::MixedStreamTaskEvent>("bytertc::MixedStreamTaskEvent");
    qRegisterMetaType<ByteRTCEventHandler::MixedStreamTaskInfo>("ByteRTCEventHandler::MixedStreamTaskInfo");
    qRegisterMetaType<bytertc::MixedStreamTaskErrorCode>("bytertc::MixedStreamTaskErrorCode");

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
    qRegisterMetaType<bytertc::SyncInfoStreamType>();
    qRegisterMetaType<bytertc::FirstFramePlayState>();
    qRegisterMetaType<ByteRTCEventHandler::Stru_RemoteStreamKey>();
    qRegisterMetaType<ByteRTCEventHandler::Stru_RtcUser>();
    qRegisterMetaType<bytertc::FirstFrameSendState>();
    
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
    qDebug() << Q_FUNC_INFO << "deviceid:" << QString::fromStdString(str_device_id) << ",devicetype:" << device_type << ",state:" << device_state << ",error:" << device_error;
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

void ByteRTCEventHandler::onLocalVideoSizeChanged(bytertc::IVideoSource* video_source, const bytertc::VideoFrameInfo& info)
{
    qDebug() << Q_FUNC_INFO << ",w=" << info.width << ",h=" << info.height << ",rotation=" << info.rotation;
    emit sigLocalVideoSizeChanged(info);
}

void ByteRTCEventHandler::onFirstLocalVideoFrameCaptured(bytertc::IVideoSource* video_source, const bytertc::VideoFrameInfo& info)
{
    qDebug() <<Q_FUNC_INFO << ",w:" << info.width << ",h:" << info.height;
     emit sigFirstLocalVideoFrameCaptured(info);
}

void ByteRTCEventHandler::onFirstLocalAudioFrame(bytertc::IAudioSource* audio_source)
{
    emit sigFirstLocalAudioFrame();
}

void ByteRTCEventHandler::onAudioEffectPlayerStateChanged(int effect_id, bytertc::PlayerState state, bytertc::PlayerError error)
{
    emit sigAudioEffectPlayerStateChanged(effect_id, state, error);
}

void ByteRTCEventHandler::onMixedStreamEvent(bytertc::MixedStreamTaskInfo info, bytertc::MixedStreamTaskEvent event, bytertc::MixedStreamTaskErrorCode error_code)
{
    qDebug() << Q_FUNC_INFO << info.task_id << info.push_target_type << event << error_code;
    ByteRTCEventHandler::MixedStreamTaskInfo binfo;
    binfo.task_id = info.task_id;
    binfo.push_target_type = info.push_target_type;
    emit sigMixingEvent(binfo, event, error_code);
}

void ByteRTCEventHandler::onSingleStreamEvent(const char *task_id, bytertc::SingleStreamTaskEvent event, bytertc::SingleStreamTaskErrorCode error_code)
{

}

#if 0
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
#endif

void ByteRTCEventHandler::onMediaPlayerStateChanged(int playerId, bytertc::PlayerState state, bytertc::PlayerError error)
{
    emit sigMediaPlayerStateChanged(playerId, state, error);
}

void ByteRTCEventHandler::onMediaPlayerPlayingProgress(int playerId, int64_t progress)
{
    emit sigMediaPlayerPlayingProgress(playerId, progress);
}

void ByteRTCEventHandler::onSEIMessageReceived(const char* stream_id, const bytertc::StreamInfo& stream_info, const uint8_t* message, int length)
{

    std::string str(reinterpret_cast<const char*>(message), length);
    qDebug() << Q_FUNC_INFO << "roomid:" << stream_info.room_id
             << ",uid:" << stream_info.user_id
             << ",message:" << QString::fromStdString(str);

    Stru_RemoteStreamKey sstream_key;
    sstream_key.stream_id = stream_id == nullptr ? "" : stream_id;
    sstream_key.stream_index = static_cast<bytertc::StreamIndex>(stream_info.stream_index);
    sstream_key.room_id = stream_info.room_id == nullptr ? "" : stream_info.room_id;
    sstream_key.user_id = stream_info.user_id == nullptr ? "" : stream_info.user_id;

    emit sigSEIMessageReceived(sstream_key, str);
}

void ByteRTCEventHandler::onStreamSyncInfoReceived(const char* stream_id, const bytertc::StreamInfo& stream_info, bytertc::SyncInfoStreamType stream_type,
    const uint8_t* data, int32_t length)
{

    std::string str(reinterpret_cast<const char*>(data), length);
    Stru_RemoteStreamKey sstream_key;
    sstream_key.stream_id = stream_id == nullptr ? "" : stream_id;
    sstream_key.stream_index = static_cast<bytertc::StreamIndex>(stream_info.stream_index);
    sstream_key.room_id = stream_info.room_id == nullptr ? "" : stream_info.room_id;
    sstream_key.user_id = stream_info.user_id == nullptr ? "" : stream_info.user_id;

    emit sigStreamSyncInfoReceived(sstream_key, stream_type, str);
}

void ByteRTCEventHandler::onMediaPlayerEvent(int player_id, bytertc::PlayerEvent event, const char *message)
{

}

//void ByteRTCEventHandler::onScreenVideoFrameSendStateChanged(const char *room_id, const bytertc::RtcUser &user, bytertc::FirstFrameSendState state)
//{
//    qDebug() << Q_FUNC_INFO << room_id << "," << user.user_id << ",state:" << state;
//    if(room_id == nullptr) return;
//    std::string str_roomid = room_id;
//    Stru_RtcUser s_user;
//    s_user.user_id = user.user_id == nullptr ? "" : user.user_id;
//    s_user.meta_data = user.meta_data == nullptr ? "" : user.meta_data;
//    emit sigScreenVideoFrameSendStateChanged(str_roomid, s_user, state);
//}


void ByteRTCEventHandler::onRemoteVideoSizeChanged(bytertc::RemoteStreamKey key, const bytertc::VideoFrameInfo& info)
{
    qDebug() << Q_FUNC_INFO << "roomid:" << key.room_id << ",uid:" << key.user_id << ",size:" << info.width << "x" << info.height;
}

void ByteRTCEventHandler::onFirstRemoteVideoFrameRendered(const char* stream_id, const bytertc::StreamInfo& stream_info, const bytertc::VideoFrameInfo& info)
{
    qDebug() << Q_FUNC_INFO << "streamid=" << stream_id << ",roomid=" << stream_info.room_id << ",uid=" << stream_info.user_id << ",width=" << info.width << ",height=" << info.height << ",rotation=" << info.rotation;
    ByteRTCEventHandler::Stru_RemoteStreamKey skey;
    skey.stream_id = stream_id == nullptr ? "" : stream_id;
    skey.room_id = stream_info.room_id == nullptr ? "" : stream_info.room_id;
    skey.user_id = stream_info.user_id == nullptr ? "" : stream_info.user_id;
    skey.stream_index = static_cast<bytertc::StreamIndex>(stream_info.stream_index);

    emit sigFirstRemoteVideoFrameRendered(skey, info);
}

void ByteRTCEventHandler::onFirstRemoteVideoFrameDecoded(const char* stream_id, const bytertc::StreamInfo& stream_info, const bytertc::VideoFrameInfo& info)
{
    qDebug() << Q_FUNC_INFO << "streamid=" << stream_id << ",roomid=" << stream_info.room_id << ",uid=" << stream_info.user_id << ",w=" << info.width << ",h=" << info.height << ",rotation=" << info.rotation;
}

void ByteRTCRoomHandler::onForwardStreamEvent(bytertc::ForwardStreamEventInfo* infos, int info_count)
{

    std::vector<Stru_ForwardStreamEvent> events;
    for (int i = 0; i < info_count; i++) {
        Stru_ForwardStreamEvent event;
        event.roomid = infos[i].room_id;
        event.event = infos[i].event;
        events.push_back(event);
        qDebug() << Q_FUNC_INFO << "roomid:" << QString::fromStdString(event.roomid) << ",event:" << event.event;
    }

    emit sigForwardStreamEvent(events);
}
