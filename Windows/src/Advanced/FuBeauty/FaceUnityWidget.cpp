﻿#include "FaceUnityWidget.h"
#include "ui_FaceUnityWidget.h"

#include <QDebug>
#include <QIcon>
#include <QMessageBox>
#include <qiodevice.h>

#include "PixTextWidget.h"
#include "Config.h"
#include "Utils.h"
#include "Resources.h"
#include <tuple>
#include <thread>

#include "bytertc_video.h"
#include "bytertc_room.h"


/**
* 功能名称： VolcEngineRTC 集成第三方美颜SDK
* 功能简单描述：音视频通话中经常会对本地视频进行美化处理，该Demo展示如何集成相芯SDK，展示美颜功能
* 参考文档：
*   美颜CV：https://www.volcengine.com/docs/6348/114717
*   第三方：https://www.volcengine.com/docs/6348/79888
*   第三方美颜常见问题：https://www.volcengine.com/docs/6348/1178328
*
* 此功能涉及的RTC API及回调：
*     createRTCVideo 创建引擎
*     destroyRTCVideo 销毁引擎
*     startAudioCapture 开启音频采集
*     startVideoCapture 开启视频采集
*     createRTCRoom 创建RTC房间
*     joinRoom 进入RTC房间
*     leaveRoom 离开RTC房间
*     destroy 销毁RTC房间
*     registerLocalVideoProcessor 设置自定义视频前处理器，通过IVideoProcessor收到视频帧回调
*
*     onRoomStateChanged 房间状态回调
*     onLeaveRoom 离房回调
*     onUserJoined 用户加入回调
*     onUserLeave  用户离开回调
*     onUserPublishStream 用户发流回调
*     onUserUnpublishStream 用户停止发流回调
* 
*    processVideoFrame 支持修改视频帧并发送到远端
*

*
* Demo实现时的逻辑
*    本Demo演示功能：ByteRTC 集成相芯SDK，展示美颜功能
*    registerLocalVideoProcessor 注册本地视频帧回调，processVideoFrame接口修改视频帧并进行美颜处理
*    processVideoFrame 中收到的视频帧来自不同线程，而相芯SDK不支持跨线程的初始化和调用，因此新增线程统一处理视频数据
*    CNAMASDK_H 宏用来区分是否已经集成过相芯SDK，集成后则展示功能界面；未集成时展示集成步骤
*    使用相芯SDK功能，需先申请付费账号
*    为了展示简单，所有功能的token都由客户端生成，接口Utils::generateToken，请在真正接入时视具体情况而定
*/

enum {
    BEAUTY_SKIN_BLUR=0,
    BEAUTY_SKIN_WHITE,
    BEAUTY_SKIN_RED,
    BEAUTY_SKIN_LIGHT,
    BEAUTY_SKIN_TOOTH,
    BEAUTY_SKIN_COUNT
};

enum {
    SHAPE_FACE_SHOULIAN = 0,
    SHAPE_FACE_DAYAN,
    SHAPE_FACE_XIABA,
    SHAPE_FACE_ETOU,
    SHAPE_FACE_SHOUBI,
    SHAPE_FACE_ZUIXING,
    SHAPE_FACE_VLIAN,
    SHAPE_FACE_ZHAILIAN,
    SHAPE_FACE_XIAOLIAN
};


FaceUnityWidget::FaceUnityWidget(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::FaceUnityWidget)
{
    ui->setupUi(this);
    initUI();
    initConnections();
    showItem();
    initRTC();
    initNama();
    m_thread_process = new std::thread(&FaceUnityWidget::funcProcessVideoFrame, this);

    //用于测试
    m_outFile = new QFile("out.yuv");
    bool ret = m_outFile->open(QIODevice::WriteOnly);
    m_inFile = new QFile("in.yuv");
    ret = m_inFile->open(QIODevice::WriteOnly);
    

}

FaceUnityWidget::~FaceUnityWidget()
{
    cleanThread();
    cleanRTC();
    cleanNama();
    resetFaceBueatyValue();
    onBtnRevertClicked();

    m_outFile->close();
    m_inFile->close();
    delete ui;

}

void FaceUnityWidget::showItem()
{
#ifdef CNAMASDK_H //已经集成相芯SDK
    ui->stackedWidget->setCurrentWidget(ui->page_support);

#else //未集成相芯SDK
    ui->stackedWidget->setCurrentWidget(ui->page_unsupport);
    ui->label_path_mac->hide();
    ui->label_path_win->hide();

#ifdef Q_OS_MAC
    ui->label_path_mac->show();
#else
    ui->label_path_win->show();
#endif
#endif
}

void FaceUnityWidget::initRTC()
{
    if (m_video == nullptr) {
        m_handler.reset(new ByteRTCEventHandler());
        m_video = bytertc::createRTCVideo(g_appid.c_str(), m_handler.get(), nullptr);
        m_video->startAudioCapture();
        m_video->startVideoCapture();
    }
    QStringList list = {"createRTCVideo", "startAudioCapture", "startVideoCapture"};
    appendAPI(list);
}

void FaceUnityWidget::cleanRTC()
{
    QStringList list = {"stopAudioCapture", "stopVideoCapture", "destroyRTCVideo"};
    if (m_video) {
        if (m_room) {
            m_room->leaveRoom();
            m_room->setRTCRoomEventHandler(nullptr);
            m_room->destroy();
            m_room = nullptr;
            list = QStringList{"leaveRoom", "setRTCRoomEventHandler", "destroy"} + list;
        }
        m_video->stopAudioCapture();
        m_video->stopVideoCapture();
        bytertc::destroyRTCVideo();
        m_video = nullptr;
        ui->btn_joinroom->setText(QStringLiteral("进房"));
        appendAPI(list);
    }
}

std::unique_ptr<ByteRTCRoomHandler> FaceUnityWidget::createRoomHandler(std::string roomid, std::string uid)
{
    std::unique_ptr<ByteRTCRoomHandler> roomH = std::make_unique<ByteRTCRoomHandler>(roomid, uid);
    connect(roomH.get(), &ByteRTCRoomHandler::sigRoomStateChanged, this, &FaceUnityWidget::onSigRoomStateChanged);
    connect(roomH.get(), &ByteRTCRoomHandler::sigLeaveRoom, this, &FaceUnityWidget::onSigLeaveRoom);
    connect(roomH.get(), &ByteRTCRoomHandler::sigUserLeave, this, &FaceUnityWidget::onSigUserLeave);
    connect(roomH.get(), &ByteRTCRoomHandler::sigUserJoined, this, &FaceUnityWidget::onSigUserJoined);
    connect(roomH.get(), &ByteRTCRoomHandler::sigUserPublishStream, this, &FaceUnityWidget::onSigUserPublishStream);
    connect(roomH.get(), &ByteRTCRoomHandler::sigUserUnPublishStream, this, &FaceUnityWidget::onSigUserUnPublishStream);
    connect(roomH.get(), &ByteRTCRoomHandler::sigTokenWillExpire, this, [this]() {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("Token will expire,please updateToken"), QMessageBox::Ok);
        box.exec();
        });

    return roomH;

}

int FaceUnityWidget::initNama()
{
#ifdef CNAMASDK_H
    std::unique_lock<std::mutex> l(m_mutex_process);
    m_nama = new NamaNameSpace::Nama();
    if (!m_nama->InitNama()) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"),
            QStringLiteral("相芯美颜初始化失败，请检查相芯证书是否填写到 authpack.h 中"), QMessageBox::Ok);
        box.exec();
    }

#endif
    return 0;
}

void FaceUnityWidget::cleanNama()
{
    if (m_nama) {
        delete m_nama;
        m_nama = nullptr;
    }
}

void FaceUnityWidget::initUI()
{
    QList<QWidget *> childWidgets = this->findChildren<QWidget *>();
    // 遍历子控件并设置样式表
    foreach (QWidget *childWidget, childWidgets) {
        QLabel *label = qobject_cast<QLabel *>(childWidget);
        if (label) {
            if (label->objectName() != "label_user_id") {
                label->setStyleSheet(APIDemo::str_qss_label);
            } else {
                label->setStyleSheet(APIDemo::str_qss_label_user_info);
            }
        }
        QLineEdit *edit = qobject_cast<QLineEdit*>(childWidget);
        if (edit) {
            edit->setStyleSheet(APIDemo::str_qss_text);
        }
    }
    ui->lineEdit_room->setStyleSheet(APIDemo::str_qss_text);
    ui->lineEdit_uid->setStyleSheet(APIDemo::str_qss_text);
    ui->btn_joinroom->setStyleSheet(APIDemo::str_qss_btn1);
    //ui->btn_revert->setStyleSheet(APIDemo::str_qss_btn2_3);
    ui->label_title->setStyleSheet(APIDemo::str_qss_label_ttile);
    ui->label_t1->setStyleSheet(APIDemo::str_qss_label_ttile);
    ui->label_t2->setStyleSheet(APIDemo::str_qss_label_ttile);
}

int FaceUnityWidget::joinRoom()
{
    if (m_video == nullptr) return -1;
    string roomid = ui->lineEdit_room->text().toStdString();
    std::string uid = ui->lineEdit_uid->text().toStdString();
    QString qstr_error;

    if (!Utils::checkIDValid(QString::fromStdString(uid), QStringLiteral("用户名"), qstr_error)) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), "uid error " + qstr_error, QMessageBox::Ok);
        box.exec();
        return -2;
    }

    if (!Utils::checkIDValid(QString::fromStdString(roomid), QStringLiteral("房间号"), qstr_error)) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), "roomid error " + qstr_error, QMessageBox::Ok);
        box.exec();
        return -3;
    }

    bytertc::VideoCanvas canvas((void*)ui->widget->getWinId(), bytertc::RenderMode::kRenderModeHidden, 0);
    m_video->setLocalVideoCanvas(bytertc::StreamIndex::kStreamIndexMain, canvas);
    m_room = m_video->createRTCRoom(roomid.c_str());
    if (m_room == nullptr) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("createRTCRoom error, please check"), QMessageBox::Ok);
        box.exec();
        return -4;
    }


    bytertc::VideoPreprocessorConfig videoConfig;
    videoConfig.required_pixel_format = bytertc::kVideoPixelFormatI420;
    m_video->registerLocalVideoProcessor(dynamic_cast<bytertc::IVideoProcessor*>(this), videoConfig);

    m_room_handler = createRoomHandler(roomid, uid);
    m_room->setRTCRoomEventHandler(m_room_handler.get());
    std::string token = Utils::generateToken(roomid, uid);
    bytertc::UserInfo userinfo;
    userinfo.uid = uid.c_str();
    bytertc::RTCRoomConfig config;
    config.is_auto_publish = true;
    config.is_auto_subscribe_audio = true;
    config.is_auto_subscribe_video = true;

    int ret = m_room->joinRoom(token.c_str(), userinfo, config);
    if (ret != 0) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("joinRoom error, please check"), QMessageBox::Ok);
        box.exec();
        return -5;
    }
    QStringList list = {"registerLocalVideoProcessor", "setLocalVideoCanvas", "createRTCRoom", "setRTCRoomEventHandler", "joinRoom"};
    appendAPI(list);
    return 0;
}

int FaceUnityWidget::leaveRoom()
{
    if (m_room) {
        m_room->leaveRoom();
        m_room->destroy();
        m_room = nullptr;
    }
    bytertc::VideoPreprocessorConfig conf;
    m_video->registerLocalVideoProcessor(nullptr, conf);
    ui->btn_joinroom->setText(QStringLiteral("进房"));
    QStringList list = {"leaveRoom", "destroy"};
    appendAPI(list);
    return 0;
}

void FaceUnityWidget::funcProcessVideoFrame()
{
    while (1)
    {
        if (m_thread_run == false) {
            return;
        }

        VideoFrame curFrame;
        {
            std::unique_lock<std::mutex> l1(m_mutex_in);
            m_cond_in.wait(l1, [this]() { return m_inLocalFrames.size() > 0 || m_thread_run == false; });

            if (m_inLocalFrames.size() > 0) {
                curFrame = m_inLocalFrames.back(); //get 1 frame from in frames
                m_inLocalFrames.pop_back();
            }
        }

        if (curFrame.frame == nullptr) {
            continue;
        }

        if (m_dmp_out) {
            m_inFile->write((const char*)curFrame.yuv_buffer, curFrame.width*curFrame.height*3/2);
        }

        if (m_nama) {
            m_nama->processVideoFrame(curFrame.yuv_buffer, curFrame.width, curFrame.height); //process video frame
        }

        if (m_dmp_out) { //输出到文件
            m_outFile->write((const char*)curFrame.yuv_buffer, curFrame.width * curFrame.height*3/2);
        }

        {
            std::unique_lock<std::mutex> l2(m_mutex_out);
            m_outLocalFrames.push_back(curFrame); // push 1 frame to out frames
            qDebug() << Q_FUNC_INFO << "push frame to m_outLocalFrames,size=" << m_outLocalFrames.size();
        }
    }
}

bytertc::IVideoFrame *FaceUnityWidget::processVideoFrame(bytertc::IVideoFrame * src)
{
    if (!src) return nullptr;
    pushVideoFrame(src); //push to in frames
    return popVideoFrame(src); //pop from out frames
}

void FaceUnityWidget::cleanThread()
{
    m_thread_run = false;
    m_cond_in.notify_all();
    if (m_thread_process ) {
        if (m_thread_process->joinable()) {
            m_thread_process->join();
        }
        delete m_thread_process;
        m_thread_process = nullptr;
    }
}

void FaceUnityWidget::initConnections()
{
    connect(ui->btn_joinroom, &QPushButton::clicked, this, &FaceUnityWidget::onBtnJoinRoomClicked);
    connect(ui->slider_eye, &QSlider::valueChanged, this, &FaceUnityWidget::onSliderValueChanged);
    connect(ui->slider_meiya, &QSlider::valueChanged, this, &FaceUnityWidget::onSliderValueChanged);
    connect(ui->slider_mopi, &QSlider::valueChanged, this, &FaceUnityWidget::onSliderValueChanged);
    connect(ui->slider_white, &QSlider::valueChanged, this, &FaceUnityWidget::onSliderValueChanged);
    connect(ui->slider_red, &QSlider::valueChanged, this, &FaceUnityWidget::onSliderValueChanged);

    connect(ui->slider_shoulian, &QSlider::valueChanged, this, &FaceUnityWidget::onSliderValueChanged);
    connect(ui->slider_xiaba, &QSlider::valueChanged, this, &FaceUnityWidget::onSliderValueChanged);
    connect(ui->slider_etou, &QSlider::valueChanged, this, &FaceUnityWidget::onSliderValueChanged);
    connect(ui->slider_shoubi, &QSlider::valueChanged, this, &FaceUnityWidget::onSliderValueChanged);
    connect(ui->slider_zuixing, &QSlider::valueChanged, this, &FaceUnityWidget::onSliderValueChanged);

    connect(ui->slider_vlian, &QSlider::valueChanged, this, &FaceUnityWidget::onSliderValueChanged);
    connect(ui->slider_zhailian, &QSlider::valueChanged, this, &FaceUnityWidget::onSliderValueChanged);
    connect(ui->slider_xiaolian, &QSlider::valueChanged, this, &FaceUnityWidget::onSliderValueChanged);
    connect(ui->slider_dayan, &QSlider::valueChanged, this, &FaceUnityWidget::onSliderValueChanged);
    //connect(ui->btn_revert, &QPushButton::clicked, this, &FaceUnityWidget::onBtnRevertClicked);

    connect(ui->btn_filter_bailiang, &QPushButton::clicked, this, &FaceUnityWidget::onBtnFilterClicked);
    connect(ui->btn_filter_fennen, &QPushButton::clicked, this, &FaceUnityWidget::onBtnFilterClicked);
    connect(ui->btn_filter_leng, &QPushButton::clicked, this, &FaceUnityWidget::onBtnFilterClicked);
    connect(ui->btn_filter_nuan, &QPushButton::clicked, this, &FaceUnityWidget::onBtnFilterClicked);
    connect(ui->btn_filter_orign, &QPushButton::clicked, this, &FaceUnityWidget::onBtnFilterClicked);
    connect(ui->btn_filter_qingxin, &QPushButton::clicked, this, &FaceUnityWidget::onBtnFilterClicked);



    auto btn_func1 = [this](QPushButton* btn, int type) {
        if (btn) {
            btn->setProperty("type", type);
            connect(btn, &QPushButton::clicked, this, &FaceUnityWidget::onButton1Clicked);
        }
    };
    auto btn_func2 = [this](QPushButton* btn, int type) {
        if (btn) {
            btn->setProperty("type", type);
            connect(btn, &QPushButton::clicked, this, &FaceUnityWidget::onButton2Clicked);
        }
    };

#ifdef CNAMASDK_H
    btn_func1(ui->btn_ar_1, NamaNameSpace::MASK_baozi);
    btn_func1(ui->btn_ar_2, NamaNameSpace::MASK_bluebird);
    btn_func1(ui->btn_ar_3, NamaNameSpace::MASK_fenhudie);
    btn_func1(ui->btn_ar_4, NamaNameSpace::MASK_lanhudie);
    btn_func1(ui->btn_ar_5, NamaNameSpace::MASK_tiger);
    btn_func1(ui->btn_ar_6, NamaNameSpace::MASK_tiger_bai);
    btn_func1(ui->btn_ar_7, NamaNameSpace::MASK_tiger_huang);
    btn_func1(ui->btn_ar_8, NamaNameSpace::MASK_xiongmao);

    btn_func2(ui->btn_tool_1, NamaNameSpace::ItemSticker_CatSparks);
    btn_func2(ui->btn_tool_2, NamaNameSpace::ItemSticker_newy1);
    btn_func2(ui->btn_tool_3, NamaNameSpace::ItemSticker_redribbt);
    btn_func2(ui->btn_tool_4, NamaNameSpace::ItemSticker_sdlr);
    btn_func2(ui->btn_tool_5, NamaNameSpace::ItemSticker_xlong_zh_fu);
#endif

}



void FaceUnityWidget::onBtnJoinRoomClicked()
{
    qDebug() << Q_FUNC_INFO << "will join room:" << ui->lineEdit_room->text();
#ifdef CNAMASDK_H
    if (ui->btn_joinroom->text() == QStringLiteral("进房")) {
        if (joinRoom() != 0) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("joinroom failed"), QMessageBox::Ok);
            box.exec();
            return;
        }
    } else {

        if (leaveRoom() != 0) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("leaveRoom failed"), QMessageBox::Ok);
            box.exec();
            return;
        }
    }
#endif
}

void FaceUnityWidget::onSliderValueChanged(int value)
{
#ifdef CNAMASDK_H
    QSlider *slider = dynamic_cast<QSlider*>(QObject::sender());
    if (slider == ui->slider_mopi) { //磨皮
        NamaNameSpace::Nama::mFaceBeautyLevel[BEAUTY_SKIN_BLUR] = value;
        ui->label_mopi->setText(QString::number(value));

    } else if (slider == ui->slider_white) { //美白
        NamaNameSpace::Nama::mFaceBeautyLevel[BEAUTY_SKIN_WHITE] = value;
        ui->label_meibai->setText(QString::number(value));
    } else if (slider == ui->slider_red) { //红润
        NamaNameSpace::Nama::mFaceBeautyLevel[BEAUTY_SKIN_RED] = value;
        ui->label_red->setText(QString::number(value));
    } else if (slider == ui->slider_eye) { //亮眼
        ui->label_eye->setText(QString::number(value));
        NamaNameSpace::Nama::mFaceBeautyLevel[BEAUTY_SKIN_LIGHT] = value;
    } else if (slider == ui->slider_meiya){ //美牙
        NamaNameSpace::Nama::mFaceBeautyLevel[BEAUTY_SKIN_TOOTH] = value;
        ui->label_meiya->setText(QString::number(value));
    }

    //美型
    else if (slider == ui->slider_xiaba) { //下巴
        NamaNameSpace::Nama::mFaceShapeLevel[SHAPE_FACE_XIABA] = value;
        ui->label_xiaba->setText(QString::number(value));
    }
    else if (slider == ui->slider_etou) { //额头
        NamaNameSpace::Nama::mFaceShapeLevel[SHAPE_FACE_ETOU] = value;
        ui->label_etou->setText(QString::number(value));
    }
    else if (slider == ui->slider_shoubi) { //瘦鼻
        NamaNameSpace::Nama::mFaceShapeLevel[SHAPE_FACE_SHOUBI] = value;
        ui->label_shoubi->setText(QString::number(value));
    }
    else if (slider == ui->slider_zuixing) { //嘴型
        NamaNameSpace::Nama::mFaceShapeLevel[SHAPE_FACE_ZUIXING] = value;
        ui->label_zuixing->setText(QString::number(value));
    }
    else if (slider == ui->slider_vlian) { //v脸
        NamaNameSpace::Nama::mFaceShapeLevel[SHAPE_FACE_VLIAN] = value;
        ui->label_vlian->setText(QString::number(value));
    }
    else if (slider == ui->slider_zhailian) { //窄脸
        NamaNameSpace::Nama::mFaceShapeLevel[SHAPE_FACE_ZHAILIAN] = value;
        ui->label_zhailian->setText(QString::number(value));
    }
    else if (slider == ui->slider_xiaolian) { //小脸
        NamaNameSpace::Nama::mFaceShapeLevel[SHAPE_FACE_XIAOLIAN] = value;
        ui->label_xiaolian->setText(QString::number(value));
    }
    else if (slider == ui->slider_shoulian) { //瘦脸
        NamaNameSpace::Nama::mFaceShapeLevel[SHAPE_FACE_SHOULIAN] = value;
        ui->label_shoulian->setText(QString::number(value));
    }
    else if (slider == ui->slider_dayan) { //大眼睛
        NamaNameSpace::Nama::mFaceShapeLevel[SHAPE_FACE_DAYAN] = value;
        ui->label_dayan->setText(QString::number(value));
    }

    {
        std::unique_lock<std::mutex> l(m_mutex_process);
        if (m_nama) {
            m_nama->m_needUpdateBeauty = true;;
        }
    }
#endif
}

void FaceUnityWidget::onBtnRevertClicked()
{
    ui->slider_shoulian->setValue(0);
    ui->slider_dayan->setValue(0);
    ui->slider_xiaba->setValue(0);
    ui->slider_etou->setValue(0);
    ui->slider_shoubi->setValue(0);
    ui->slider_zuixing->setValue(0);
    ui->slider_vlian->setValue(0);
    ui->slider_zhailian->setValue(0);
    ui->slider_xiaolian->setValue(0);
}

void FaceUnityWidget::onShowErrorTips(int error, QString msg)
{
    if (error == ERROR_VIDEO_CAPTURE) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("视频采集错误"), msg, QMessageBox::Ok);
        box.exec();
    }
}

void FaceUnityWidget::onRTCState(std::string str) {
    appendCallback(QString::fromStdString(str));
}

void FaceUnityWidget::onSigRoomStateChanged(std::string roomid, std::string uid, int state, std::string extra_info)
{
    QString log_str = QString("onRoomStateChanged,roomid:")
        + QString::fromStdString(roomid)
        + ",uid:" + QString::fromStdString(uid)
        + ",state:" + QString::number(state)
        + ",extra:" + QString::fromStdString(extra_info);
    appendCallback(log_str);

    if (state == 0) {
        ui->btn_joinroom->setText(QStringLiteral("离房"));
        ui->widget->setUserInfo(roomid, uid);
    }
    else {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("onRoomStateChanged:") + QString::number(state), QMessageBox::Ok);
        box.exec();

    }

}

void FaceUnityWidget::onSigUserPublishStream(std::string roomid, std::string uid, bytertc::MediaStreamType)
{
    QString str = "onUserPublishStream, roomid:" + QString::fromStdString(roomid)
             + ",uid:" + QString::fromStdString(uid);
    appendCallback(str);

}

void FaceUnityWidget::onSigUserUnPublishStream(std::string roomid, std::string uid, bytertc::MediaStreamType, bytertc::StreamRemoveReason)
{
    QString str = "onUserUnPublishStream, roomid:" + QString::fromStdString(roomid)
             + ",uid:" + QString::fromStdString(uid);
    appendCallback(str);

}

void FaceUnityWidget::onSigUserJoined(ByteRTCRoomHandler::UserInfo info, int)
{
    QString str = "onUserJoined, roomid:" + QString::fromStdString(info.roomid)
             + ",uid:" + QString::fromStdString(info.uid);
    appendCallback(str);

}

void FaceUnityWidget::onSigUserLeave(std::string roomid, std::string uid, bytertc::UserOfflineReason)
{
    QString str = "onUserLeave, roomid:" + QString::fromStdString(roomid)
             + ",uid:" + QString::fromStdString(uid);
    appendCallback(str);

}

void FaceUnityWidget::onSigLeaveRoom(std::string roomid, std::string uid, bytertc::RtcRoomStats)
{
    QString str = "onLeaveRoom, roomid:" + QString::fromStdString(roomid)
             + ",uid:" + QString::fromStdString(uid);
    appendCallback(str);

}

void FaceUnityWidget::pushVideoFrame(bytertc::IVideoFrame *src)
{
    clearVideoFrames(); //only receive 1 frame
   
    VideoFrame frame;
    copyIVideoFram2LocalFrame(src, frame); //copy src buffer data to frame

    std::unique_lock<std::mutex> l(m_mutex_in);
    m_inLocalFrames.push_back(frame); //push in frames
    m_cond_in.notify_one(); // notify another thread to process
}

bytertc::IVideoFrame *FaceUnityWidget::popVideoFrame(bytertc::IVideoFrame *src)
{
    bytertc::IVideoFrame* dst = src;
    std::unique_lock<std::mutex> l(m_mutex_out);

    if (m_outLocalFrames.size() == 0) { //输出队列中没有数据，直接返回
        qDebug() << Q_FUNC_INFO << "m_outLocalFrames size=0";
        return src;
    }

    VideoFrame frame = m_outLocalFrames.back();
    copyLocalFrame2IVideoFrame(dst, frame); //取出一帧处理好的数据
    frame.cleanBuffer();
    m_outLocalFrames.pop_back();

    qDebug() << "popback m_outLocalFrames,size=" << m_outLocalFrames.size();
    return dst;
}

void FaceUnityWidget::clearVideoFrames()
{
    {
        std::unique_lock<std::mutex> l1(m_mutex_in);
        std::vector<VideoFrame>::iterator ite = m_inLocalFrames.begin();
        for (; ite != m_inLocalFrames.end();) {
            ite->cleanBuffer();
            ite = m_inLocalFrames.erase(ite);
        }
    }
}


void FaceUnityWidget::copyIVideoFram2LocalFrame(bytertc::IVideoFrame *src, VideoFrame &frame)
{
    std::unique_lock<std::mutex> l(m_mutex_in);
    int width = src->width();
    int height = src->height();
    int size = width * height;
    frame.frame = src;
    frame.width = width;
    frame.height = height;


    frame.yuv_buffer = new uint8_t[size*3/2];

    //按行拷贝
    if (src->getPlaneStride(0) > src->width() || src->getPlaneStride(1) > src->width() / 2 || src->getPlaneStride(2) > src->width() / 2) {
        int dst_offset = 0;
        int src_offset = 0;
        for (int i = 0; i < src->height(); i++) {
            memcpy(frame.yuv_buffer + dst_offset, src->getPlaneData(0) + src_offset, width);
            src_offset += src->getPlaneStride(0);
            dst_offset += width;
        }
        src_offset = 0;
        for (int i = 0; i < height / 2; i++) {
            memcpy(frame.yuv_buffer + dst_offset, src->getPlaneData(1) + src_offset, width / 2);
            src_offset += src->getPlaneStride(1);
            dst_offset += width / 2;
        }
        src_offset = 0;
        for (int i = 0; i < height / 2; i++) {
            memcpy(frame.yuv_buffer + dst_offset, src->getPlaneData(2) + src_offset, width / 2);
            src_offset += src->getPlaneStride(2);
            dst_offset += width / 2;
        }
    } //按块拷贝
    else {
        memcpy(frame.yuv_buffer, src->getPlaneData(0), size);
        memcpy(frame.yuv_buffer + size, src->getPlaneData(1), size / 4);
        memcpy(frame.yuv_buffer + size *5/4, src->getPlaneData(2), size/4);
    }

}

void FaceUnityWidget::copyLocalFrame2IVideoFrame(bytertc::IVideoFrame *dst, VideoFrame &frame) //dst作为参考帧和目标帧
{
    if (frame.yuv_buffer == nullptr || dst == nullptr) return;
    int size = dst->width() * dst->height();
    int dst_offset = 0;
    int src_offset = 0;

    if (dst->getPlaneStride(0) > dst->width() || dst->getPlaneStride(1) > dst->width() / 2 || dst->getPlaneStride(2) > dst->width() / 2) {
        
        src_offset = 0;
        dst_offset = 0;

        for (int i = 0; i < dst->height(); i++) {
            memcpy(dst->getPlaneData(0) + dst_offset, frame.yuv_buffer + src_offset, dst->width());
            src_offset += dst->width();
            dst_offset += dst->getPlaneStride(0);
        }

        dst_offset = 0;
        for (int i = 0; i < dst->height() / 2; i++) {
            memcpy(dst->getPlaneData(1) + dst_offset, frame.yuv_buffer + src_offset, dst->width() / 2);
            src_offset += dst->width() / 2;
            dst_offset += dst->getPlaneStride(1);
        }

        dst_offset = 0;
        for (int i = 0; i < dst->height() / 2; i++) {
            memcpy(dst->getPlaneData(2) + dst_offset, frame.yuv_buffer + src_offset, dst->width() / 2);
            src_offset += dst->width() / 2;
            dst_offset += dst->getPlaneStride(2);
        }
    }
    else {
        memcpy(dst->getPlaneData(0), frame.yuv_buffer, size);
        memcpy(dst->getPlaneData(1), frame.yuv_buffer + size, size / 4);
        memcpy(dst->getPlaneData(2), frame.yuv_buffer + size*5/4, size/4);
    }
}

void FaceUnityWidget::onBtnFilterClicked()
{
#ifdef CNAMASDK_H
    QPushButton* btn = dynamic_cast<QPushButton*>(QObject::sender());
    if (btn == ui->btn_filter_orign) { //原图
        NamaNameSpace::Nama::m_curFilterIdx = 0;
    }
    else if (btn == ui->btn_filter_bailiang) { //白亮
        NamaNameSpace::Nama::m_curFilterIdx = 1;
    }
    else if (btn == ui->btn_filter_fennen) { //粉嫩
        NamaNameSpace::Nama::m_curFilterIdx = 2;
    }
    else if (btn == ui->btn_filter_leng) { //冷色调
        NamaNameSpace::Nama::m_curFilterIdx = 3;
    }
    else if (btn == ui->btn_filter_nuan) { // 暖色调
        NamaNameSpace::Nama::m_curFilterIdx = 4;
    }
    else if (btn == ui->btn_filter_qingxin) { //小清新
        NamaNameSpace::Nama::m_curFilterIdx = 5;
    }

    {
        std::unique_lock<std::mutex> l(m_mutex_process);
        if (m_nama) {
            m_nama->m_needUpdateFilter = true;
        }
    }

#endif
}

void FaceUnityWidget::onButton1Clicked()
{
#ifdef CNAMASDK_H
    QPushButton* btn = dynamic_cast<QPushButton*>(sender());
    if (btn) {
        int type = btn->property("type").toInt();
        {
            std::unique_lock<std::mutex> l(m_mutex_process);
            if (m_nama) {
                m_nama->m_needUpdateBundle = true;
                m_nama->m_bundleType1 = 2;
                m_nama->m_bundleType2 = type;
            }
        }
    }

#endif
}
void FaceUnityWidget::onButton2Clicked()
{
#ifdef CNAMASDK_H
    QPushButton* btn = dynamic_cast<QPushButton*>(sender());
    if (btn) {
        int type = btn->property("type").toInt();
        {
            std::unique_lock<std::mutex> l(m_mutex_process);
            if (m_nama) {
                m_nama->m_needUpdateBundle = true;
                m_nama->m_bundleType1 = 1;
                m_nama->m_bundleType2 = type;
            }
        }
    }
#endif
}


void FaceUnityWidget::resetFaceBueatyValue() {
    ui->slider_eye->setValue(0);
    ui->slider_meiya->setValue(0);
    ui->slider_mopi->setValue(0);
    ui->slider_red->setValue(0);
    ui->slider_white->setValue(0);
}
