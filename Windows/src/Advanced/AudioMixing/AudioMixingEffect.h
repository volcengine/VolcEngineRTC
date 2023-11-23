#ifndef AudioMixingEffect_H
#define AudioMixingEffect_H

#include <QWidget>
#include <atomic>
#include "ByteRTCEventHandler.h"
#include "AudioMixItem.h"

#include "BaseWidget.h"

#include <map>
#include <memory>

namespace bytertc {
    class IRTCVideo;
    class IRTCRoom;
};

namespace Ui {
class AudioMixingEffect;
}

class AudioMixingEffect : public BaseWidget
{
    Q_OBJECT

public:

    struct Stru_EffectInfos {
        std::string path; //本地或远端路径
        AudioMixItem* widget;

    };
    explicit AudioMixingEffect(QWidget *parent = nullptr);
    ~AudioMixingEffect();

private:
    void initConnections();
    void initRTCVideo();
    void cleanRTCVideo();
    std::unique_ptr<ByteRTCRoomHandler> createRoomHandler(std::string roomid, std::string uid);

    void addItem();

private slots:
    void onBtnJoinClicked(); //进房
    void onBtnBrowserClicked(); //浏览
    void onBtnAddClicked(); //添加到列表中
    void onBtnStopAllClicked(); //停止所有
    void onBtnPuaseAllClicked();//暂停所有
    void onBtnResumeAllClicked(); //恢复所有
    void onSpinVolumeChanged(int value); //设置所有的音量
    

    void onItemBtnStartClicked(int id, int type);//点击了列表中的开始
    void onItemBtnStopClicked(int id); //点击了列表中的停止
    void onItemBtnPauseClicked(int id); //点击了列表中的暂停
    void onItemBtnResumeClicked(int id); //点击了列表中的恢复
    void onItemSpinVolumeChanged(int id, int volume); //修改了列表中的音量
    void onItemSpinPosChanged(int id, int pos); //修改了列表中的位置

private slots:
    void onSigRoomStateChanged(std::string roomid, std::string uid, int state, std::string extra_info);
    void onSigAudioEffectPlayerStateChanged(int effect_id, bytertc::PlayerState state, bytertc::PlayerError error);

    void onSigUserPublishStream(std::string roomid, std::string uid, bytertc::MediaStreamType);
    void onSigUserUnPublishStream(std::string roomid, std::string uid, bytertc::MediaStreamType, bytertc::StreamRemoveReason);
    void onSigUserJoined(ByteRTCRoomHandler::UserInfo info, int);
    void onSigUserLeave(std::string roomid, std::string uid, bytertc::UserOfflineReason);
    void onSigLeaveRoom(std::string roomid, std::string uid, bytertc::RtcRoomStats);

private:
    Ui::AudioMixingEffect *ui;
    bytertc::IRTCVideo* m_video = nullptr;
    bytertc::IRTCRoom* m_room = nullptr;
    std::string m_roomid;
    std::unique_ptr<ByteRTCEventHandler> m_handler;
    std::unique_ptr<ByteRTCRoomHandler>  m_room_handler;
    std::map<int, Stru_EffectInfos> m_infos; //混音id, Stru_EffectInfos(path, widget)
    bytertc::IAudioEffectPlayer* m_player = nullptr;

    
};

#endif // AudioMixingEffect_H
