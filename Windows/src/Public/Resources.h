#ifndef RESOURCES_H
#define RESOURCES_H

#include <string>
#include <QString>

namespace APIDemo {
static std::string str_AR_annimoji = "/Resources/AR/icon_annimoji.png";
static std::string str_AR = "/Resources/AR/icon_AR.png";
static std::string str_AR_propmap = "/Resources/AR/icon_propmap.png";

static std::string str_Tool_propmap_bling = "/Resources/AR/PropMap/bling.png";
static std::string str_Tool_propmap_fengya = "/Resources/AR/PropMap/fengya.png";
static std::string str_Tool_propmap_hudie = "/Resources/AR/PropMap/hudie.png";
static std::string str_Tool_propmap_juanhuzi = "/Resources/AR/PropMap/juanhuzi.png";
static std::string str_Tool_propmap_mask_hat = "/Resources/AR/PropMap/mask_hat.png";
static std::string str_AR_propmap_mask_touhua = "/Resources/AR/PropMap/touhua.png";



static std::string str_AR_mask_afd = "/Resources/AR/AR/afd.png";
static std::string str_AR_mask_armesh = "/Resources/AR/AR/armesh.png";
static std::string str_AR_mask_baozi = "/Resources/AR/AR/baozi.png";
static std::string str_AR_mask_bluebird = "/Resources/AR/AR/bluebird.png";
static std::string str_AR_mask_fenhudie = "/Resources/AR/AR/fenhudie.png";
static std::string str_AR_mask_lanhudie = "/Resources/AR/AR/lanhudie.png";
static std::string str_AR_mask_tiger = "/Resources/AR/AR/tiger.png";
static std::string str_AR_mask_tiger_bai = "/Resources/AR/AR/tiger_bai.png";
static std::string str_AR_mask_tiger_huang = "/Resources/AR/AR/tiger_huang.png";
static std::string str_AR_mask_xiongmao = "/Resources/AR/AR/xiongmao.png";

static std::string str_Video_Watermark = "/Resources/video/watermark.png";

static QString str_qss_btn1 = "QPushButton{background-color:#1664FF;color:white;border-radius:4px;font-family: PingFang SC;font-size: 13px;} "
                                  "QPushButton:hover{background-color:#4a79f6;color:white;font-family: PingFang SC;font-size: 13px;} "
                                  "QPushButton:pressed{background-color:#114AB9;color:white;font-family: PingFang SC;font-size: 13px;} "
                                  "QPushButton:disabled{background-color:#9fbbfa;color:white;font-family: PingFang SC;font-size: 13px;}";

static QString str_qss_btn2_3 = "QPushButton{background-color:#F6F8FA;color:#42464E;border-radius:4px;font-family: PingFang SC;font-size: 13px;} "
                                  "QPushButton:hover{background-color:#FAFBFC;color:#42464E; border: 1px solid #4a79f6;font-family: PingFang SC;font-size: 13px;} "
                                  "QPushButton:hover{background-color:#FAFBFC;color:#42464E;border: 1px  solid #05F;font-family: PingFang SC;font-size: 13px;} "
                                  "QPushButton:disabled{background-color:#F6F8FA;color:#42464E;border: 1px solid #05F;font-family: PingFang SC;font-size: 13px;}";

static QString str_qss_btn4 = "QPushButton{color:#1664FF; border:none; background:transparent;font-family: PingFang SC;font-size: 12px;} "
                                "QPushButton:hover{color:#387BFF;border:none;background:transparent;font-family: PingFang SC;font-size: 12px;} "
                                "QPushButton:hover{color:#1759DD;border:none;background:transparent;font-family: PingFang SC;font-size: 12px;} "
                                "QPushButton:disabled{color:#97BCFF;border:none;background:transparent;font-family: PingFang SC;font-size: 12px;}";


static  QString str_qss_scrollstyle="QScrollBar:vertical"          // 纵向的滚动条样式
                             "{"
                             "width:4px;"
                             "background:transparent;"
                             "margin:0px,0px,0px,0px;"
                             "padding-top:0px;"
                             "padding-bottom:0px;"
                             "}"
                             "QScrollBar::handle:vertical"       // 可滚动区域样式
                             "{"
                             "width:4px;"
                             "background:#f7f8fa;"
                             "border-radius:4px;"
                             "}"
                             "QScrollBar::handle:vertical:hover" // 触摸或点击滚动条样式
                             "{"
                             "width:4px;"
                             "background:#f7f8fa;"
                             "border-radius:4px;"
                             "}"
                             "QScrollBar::add-line:vertical"
                             "{"
                             "height:6px;width:4px;"
                             "subcontrol-position:bottom;"
                             "}"
                             "QScrollBar::sub-line:vertical"
                             "{"
                             "height:6px;width:4px;"
                             "subcontrol-position:top;"
                             "}"
                             "QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical"
                             "{"
                             "background:#E8EAEF;"  // 滚动条底色
                             "border-radius:4px;"
                             "}";

static QString str_qss_label = "QLabel{color:#42464E; background-color:transparent;font-family: PingFang SC;font-size: 13px;}";

static QString str_qss_label_user_info = "QLabel{color:white; background-color:transparent;font-family: PingFang SC;font-size: 13px;}";


static QString str_qss_label_ttile = "QLabel{color: var(--text-color-text-1, #0C0D0E);text-align: center;font-family: PingFang SC;font-size: 14px;font-style: normal;font-weight: 600;line-height: normal;}";

static QString str_qss_text = "border-radius:4px;border: 1px solid #EAEDF1;background: white;font-family: PingFang SC;font-size: 13px;";

static QString str_qss_combobox = "QComboBox {border-radius:4px;border: 2px solid #EAEDF1;PingFang SC;font-size: 13px;} QComboBox QAbstractItemView {color: #0C0D0E;background-color: white; selection-background-color: #f6f8fa;selection-color:#1664FF;PingFang SC;font-size: 13px;}";

static QString str_qss_spinbox = "QSpinBox {border: 2px solid #EAEDF1;PingFang SC;font-size: 13px;}"
                                 "QSpinBox::up-arrow {"
                                 "border-image:url(:/img/Resources/ui/spin_up.png);"
                                 "background: transparent;}"
                                 "QSpinBox::down-arrow {"
                                 "border-image: url(:/img/Resources/ui/spin_up.png);"
                                 "background: transparent;}";

static QString str_qss_checkbox = "QCheckBox{color:#42464E; background-color:transparent;font-family: PingFang SC;font-size: 13px;}";

static QString str_qss_groupbox = "QGroupBox{color: var(--text-color-text-1, #0C0D0E);text-align: center;font-family: PingFang SC;font-size: 14px;font-style: normal;font-weight: 600;line-height: normal;}";

}

#endif // RESOURCES_H
