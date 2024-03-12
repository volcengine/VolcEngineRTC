#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "bytertc_video.h"


#include <QDebug>
#include <vector>
#include <QScrollBar>

#include "MultiRoom.h"
#include "FaceUnityWidget.h"
#include "ByteBeautyWidget.h"
#include "CDNStreamByServer.h"
#include "SoundEffectsWidget.h"
#include "CrossRoomPK.h"
#include "VideoConfigWidget.h"
#include "AudioMixingEffect.h"
#include "AudioMixingMedia.h"
#include "RawAudioData.h"
#include "QuickStartWidget.h"
#include "Resources.h"
#include "SEIMessage.h"
#include "AudioMessage.h"


enum FunctionTyp{
    TYPE_BEGIN,
    TYPE_QUICK_START,
    TYPE_MULTI_ROOM,
    TYPE_CROSS_ROOM_PK,
    TYPE_RAW_AUDIO,
    TYPE_AUDIOMIXING_EFFECT,
    TYPE_AUDIOMIXING_MEDIA,
    TYPE_SOUND_EFFECTS,   
    TYPE_VIDEO_CONFIG,
    TYPE_PUSHCDN_BYSERVER,
    TYPE_BYTE_BEAUTY,    
    TYPE_FU_BEAUTY ,
    TYPE_SEI,
    TYPE_AUDIO_MESSAGE,
    TYPE_END
};

std::vector<int> g_types;
MainWindow* g_mainWindow = nullptr;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    g_mainWindow = this;

    for (int i = TYPE_BEGIN + 1; i < TYPE_END; i++) {
        g_types.push_back(i);
    }
    initUI();
}

MainWindow::~MainWindow()
{
    qDebug() << Q_FUNC_INFO;
    if (m_currentItem) {
        delete m_currentItem;
        m_currentItem = nullptr;
    }
    delete ui;
}

LogWidget *MainWindow::getLogWidget()
{
    return ui->widget_log;
}

void MainWindow::initUI()
{
    setWindowTitle("API-Demo");
    initListViews();
    std::string version = bytertc::getSDKVersion() == nullptr ? "" : bytertc::getSDKVersion();
    ui->label_version->setText(QString::fromStdString(version));
    ui->label_version->setStyleSheet(APIDemo::str_qss_label);
    ui->label_v->setStyleSheet(APIDemo::str_qss_label);
}

QString getStringByType(int type) {
    QString result;
    switch (type) {
    case TYPE_QUICK_START:
        result = QStringLiteral("快速开始");
        break;
    case TYPE_MULTI_ROOM:
        result = QStringLiteral("多房间");
        break;
    case TYPE_CROSS_ROOM_PK:
        result = QStringLiteral("跨房PK");
        break;
    case TYPE_RAW_AUDIO:
        result = QStringLiteral("原始音频数据");
        break;
    case TYPE_AUDIOMIXING_EFFECT:
        result = QStringLiteral("音效混音");
        break;
    case TYPE_AUDIOMIXING_MEDIA:
        result = QStringLiteral("音乐混音");
        break;
    case TYPE_SOUND_EFFECTS:
        result = QStringLiteral("美声与音效");
        break;
    case TYPE_VIDEO_CONFIG:
        result = QStringLiteral("视频常用配置");
        break;
    case TYPE_PUSHCDN_BYSERVER:
        result = QStringLiteral("推流到CDN");
        break;

    case TYPE_BYTE_BEAUTY:
        result = QStringLiteral("字节美颜");
        break;
    case TYPE_FU_BEAUTY:
        result = QStringLiteral("相芯美颜");
        break;

    case TYPE_SEI:
        result = QStringLiteral("发送SEI");
        break;
    case TYPE_AUDIO_MESSAGE:
        result = QStringLiteral("音频随帧");
        break;
    default:
        break;
    }

    return result;
}

BaseWidget* MainWindow::createFunctionWidget(int type, QWidget* parent) {
    BaseWidget*item = nullptr;
    switch (type) {

    case TYPE_QUICK_START:
        item = new QuickStartWidget(parent);
        break;
        break;
    case TYPE_MULTI_ROOM:
        item = new MultiRoom(parent);
        break;
    case TYPE_CROSS_ROOM_PK:
        item = new CrossRoomPK(parent);
        break;
    case TYPE_RAW_AUDIO:
        item = new RawAudioData(parent);
        break;
    case TYPE_AUDIOMIXING_EFFECT:
        item = new AudioMixingEffect(parent);
        break;
    case TYPE_AUDIOMIXING_MEDIA:
        item = new AudioMixingMedia(parent);
        break;
    case TYPE_SOUND_EFFECTS:
        item = new SoundEffectsWidget(parent);
        break;
    case TYPE_VIDEO_CONFIG:
        item = new VideoConfigWidget(parent);
        break;
    case TYPE_PUSHCDN_BYSERVER:
        item = new CDNStreamByServer(parent);
        break;
    case TYPE_BYTE_BEAUTY:
        item = new ByteBeautyWidget(parent);
        break;
    case TYPE_FU_BEAUTY:
        item = new FaceUnityWidget(parent);
        break;

    case TYPE_SEI:
        item = new SEIMessage(parent);
        break;

    case TYPE_AUDIO_MESSAGE:
        item = new AudioMessage(parent);
        break;
    default:
        break;
    }

    return item;
}

QListWidgetItem *MainWindow::createListItem(int type, QListWidget *&widget){

    qDebug() << Q_FUNC_INFO << "createListItem:" << type;
    QListWidgetItem *item = nullptr;
    switch (type) {
    case TYPE_QUICK_START:
        widget = ui->listWidget_quick_start;
        break;
    case TYPE_MULTI_ROOM:
        widget = ui->listWidget_room;
        break;
    case TYPE_CROSS_ROOM_PK:
        widget = ui->listWidget_audio_video;
        break;
    case TYPE_RAW_AUDIO:
    case TYPE_AUDIOMIXING_EFFECT:
    case TYPE_AUDIOMIXING_MEDIA:
    case TYPE_SOUND_EFFECTS:
        widget = ui->listWidget_audio;
        break;
    case TYPE_VIDEO_CONFIG:
        widget = ui->listWidget_video;
        break;
    case TYPE_PUSHCDN_BYSERVER:
        widget = ui->listWidget_stream;
        break;
    case TYPE_BYTE_BEAUTY:
    case TYPE_FU_BEAUTY:
        widget = ui->listWidget_plugin;
        break;
    case TYPE_SEI:
    case TYPE_AUDIO_MESSAGE:
        widget = ui->listWidget_message;
        break;
    default:
        break;
    }
    item = new QListWidgetItem(getStringByType(type), widget, type);
    item->setSizeHint(QSize(200, 26));
    if (widget) {
        widget->addItem(item);
        widget->setStyleSheet("QListWidget{font-family: PingFang SC;font-size: 13px;font-style: normal;font-weight: 400;}"
                              "QListWidget::item:selected { background-color: #E0EAFA; color: #1664FF; font-family: PingFang SC;font-size: 13px;font-style: normal;font-weight: 400;}"
                              "QListWidget::item:!selected { background-color: #f6f8fa; color: #020814; font-family: PingFang SC;font-size: 13px;font-style: normal;font-weight: 400;}");
    }

    return item;
}


void MainWindow::initListViews()
{
    for (int i=0; i< g_types.size(); i++) {
        QListWidget *widget = nullptr;
        QListWidgetItem *item = createListItem(g_types[i], widget);

        connect(widget, &QListWidget::itemClicked, this, [this](QListWidgetItem* item){
            qDebug() << Q_FUNC_INFO << item->text();
            if (m_lastWidget != item) {

                if (m_currentItem) {
                    delete m_currentItem;
                    m_currentItem = nullptr;
                }
                if (m_lastWidget) {
                    m_lastWidget->setSelected(false);
                }
                m_currentItem = createFunctionWidget(item->type(), this);
                if (m_currentItem == nullptr) return;
                ui->verticalLayout_widget->addWidget(dynamic_cast<QWidget*>(m_currentItem));
            } else {
                //ignore
            }

            m_lastWidget = item;
        });
    }

    ui->listWidget_quick_start->autoAdjustHeight();
    ui->listWidget_room->autoAdjustHeight();
    ui->listWidget_audio->autoAdjustHeight();
    ui->listWidget_audio_video->autoAdjustHeight();
    ui->listWidget_plugin->autoAdjustHeight();
    ui->listWidget_video->autoAdjustHeight();
    ui->listWidget_stream->autoAdjustHeight();
    ui->listWidget_message->autoAdjustHeight();
}

