#ifndef SOUNDEFFECTSWIDGET_H
#define SOUNDEFFECTSWIDGET_H

#include <QWidget>
#include "ByteRTCEventHandler.h"

#include <map>
#include "Utils.h"
#include "BaseWidget.h"

namespace Ui {
class SoundEffectsWidget;
}
namespace bytertc {
    class IRTCVideo;
    class IRTCRoom;
};

class ByteRTCEventHandler;
class ByteRTCRoomHandler;
class UserWidget;
class SoundEffectsWidget : public BaseWidget
{
    Q_OBJECT

public:

    explicit SoundEffectsWidget(QWidget *parent = nullptr);
    ~SoundEffectsWidget();

private slots:
    void onBtnJoinClicked(); //进房
    void onComboxHXTextChanged(const QString &text); //混响
    void onComboxBSTextChanged(const QString& text); //变声
    void onSliderPitchValueChanged(int value); //变调
    void onBtnChangeVoiceReverbParaClicked(); //修改混响参数
    void onComboxAnsIndexChanged(int value); //降噪


private:
    void initRTCVideo();
    void cleanRTCVideo();
    void initUI();
    ByteRTCRoomHandler* createRoomHandler(std::string roomid, std::string uid);

private slots:
    void onSigRoomStateChanged(std::string roomid, std::string uid, int state, std::string extra_info);
    void onSigUserPublishStream(std::string roomid, std::string uid, bytertc::MediaStreamType);
    void onSigUserUnPublishStream(std::string roomid, std::string uid, bytertc::MediaStreamType, bytertc::StreamRemoveReason);
    void onSigUserJoined(ByteRTCRoomHandler::UserInfo, int);
    void onSigUserLeave(std::string, std::string, bytertc::UserOfflineReason);



private:
    Ui::SoundEffectsWidget *ui;
    std::string m_roomid, m_uid;
    bytertc::IRTCVideo* m_video = nullptr;
    bytertc::IRTCRoom* m_room = nullptr;
    ByteRTCEventHandler *m_handler = nullptr;
};

#endif // SOUNDEFFECTSWIDGET_H
