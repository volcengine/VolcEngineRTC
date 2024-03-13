#ifndef CROSSROOMPK_H
#define CROSSROOMPK_H

#include <QWidget>
#include <memory>
#include "ByteRTCEventHandler.h"
#include "BaseWidget.h"

namespace Ui {
class CrossRoomPK;
}

namespace bytertc {
    class IRTCVideo;
    class IRTCRoom;
};

class ByteRTCRoomHandler;
class CrossRoomPK : public BaseWidget
{
    Q_OBJECT

public:
    explicit CrossRoomPK(QWidget *parent = nullptr);
    ~CrossRoomPK();

private slots:
    void onBtnJoinClicked(); //room1 进房
    void onBtnCrossStartClicked(); //跨房间开始
    void onBtnCrossUpdateClicked(); //跨房间更新
    void onBtnCrossPauseClicked(); //暂停
    void onBtnCrossResumeClicked(); //恢复
    void onBtnCrossStopClicked(); //停止

private:
    void initRTCVideo();
    void cleanRTCVideo();
    void initUI();
    std::unique_ptr<ByteRTCRoomHandler> createRoomHandler(std::string roomid, std::string uid);

private slots:
    void onSigRoomStateChanged(std::string roomid, std::string uid, int state, std::string extra_info);
    void onSigUserPublishStream(std::string roomid, std::string uid, bytertc::MediaStreamType);
    void onSigUserUnPublishStream(std::string roomid, std::string uid, bytertc::MediaStreamType, bytertc::StreamRemoveReason);
    void onSigLeaveRoom(std::string roomid, std::string uid, const bytertc::RtcRoomStats stats);
    void onSigForwardStreamStateChanged(std::vector<ByteRTCRoomHandler::Stru_ForwardStreamStateInfo> result);
    void onForwardStreamEvent(std::vector<ByteRTCRoomHandler::Stru_ForwardStreamEvent> events);

private:
    Ui::CrossRoomPK *ui;
    std::string m_uid;
    bytertc::IRTCVideo* m_video = nullptr;
    bytertc::IRTCRoom* m_room1 = nullptr;
    std::unique_ptr<ByteRTCEventHandler> m_handler;
    std::unique_ptr<ByteRTCRoomHandler>  m_room_handler1, m_room_handler2;
};

#endif // CROSSROOMPK_H
