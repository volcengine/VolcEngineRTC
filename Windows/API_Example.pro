#-------------------------------------------------
#
# Project created by QtCreator 2019-10-28T09:17:50
#
#-------------------------------------------------
QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = API_Example
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++14

RC_ICONS += $$PWD/Resources/app.ico


INCLUDEPATH += \
    src/ \
    src/Public \
    src/Public/token \
    src/Advanced/MultiRoom \
    src/Advanced/AudioMixing \
    src/Advanced/RawAudioData \
    src/Advanced/ByteBeauty \
    src/Advanced/CDNStream \
    src/Advanced/FuBeauty \
    src/Advanced/SoundEffects \
    src/Advanced/VideoConfig \
    src/Advanced/CrossRoomPK \
    src/Public/http \
    src/Advanced/FuBeauty \
    src/Advanced/FuBeauty/Sound \
    src/Advanced/ \
    src/Basic

SOURCES += \
    src/Advanced/AudioMixing/AudioMixItem.cpp \
    src/Advanced/AudioMixing/AudioMixingEffect.cpp \
    src/Advanced/AudioMixing/AudioMixingMedia.cpp \
    src/Advanced/RawAudioData/RawAudioData.cpp \
    src/Advanced/ByteBeauty/ByteBeautyWidget.cpp \
    src/Advanced/CDNStream/CDNStreamByServer.cpp \
    src/Advanced/CrossRoomPK/CrossRoomPK.cpp \
    src/Advanced/FuBeauty/FaceUnityWidget.cpp \
    src/Advanced/FuBeauty/Nama.cpp \
    src/Advanced/FuBeauty/PixTextWidget.cpp \
    src/Advanced/MultiRoom/MultiRoom.cpp \
    src/Advanced/SoundEffects/SoundEffectsWidget.cpp \
    src/Advanced/VideoConfig/VideoConfigWidget.cpp \
    src/Basic/QuickStartWidget.cpp \
    src/Public/BaseWidget.cpp \
    src/Public/ByteRTCEventHandler.cpp \
    src/Public/ListWidget.cpp \
    src/Public/LogWidget.cpp \
    src/Public/UserWidget.cpp \
    src/Public/Utils.cpp \
    src/Public/http/http.cpp \
    src/Public/token/Packer.cpp \
    src/main.cpp \
    src/mainwindow.cpp


HEADERS += \
    src/Advanced/AudioMixing/AudioMixItem.h \
    src/Advanced/AudioMixing/AudioMixingEffect.h \
    src/Advanced/AudioMixing/AudioMixingMedia.h \
    src/Advanced/RawAudioData/RawAudioData.h \
    src/Advanced/ByteBeauty/ByteBeautyWidget.h \
    src/Advanced/CDNStream/CDNStreamByServer.h \
    src/Advanced/CrossRoomPK/CrossRoomPK.h \
    src/Advanced/FuBeauty/FConfig.h \
    src/Advanced/FuBeauty/FaceUnityWidget.h \
    src/Advanced/FuBeauty/Language.h \
    src/Advanced/FuBeauty/Nama.h \
    src/Advanced/FuBeauty/PixTextWidget.h \
    src/Advanced/FuBeauty/authpack.h \
    src/Advanced/MultiRoom/MultiRoom.h \
    src/Advanced/SoundEffects/SoundEffectsWidget.h \
    src/Advanced/VideoConfig/VideoConfigWidget.h \
    src/Basic/QuickStartWidget.h \
    src/Public/BaseItem.h \
    src/Public/BaseWidget.h \
    src/Public/ByteRTCEventHandler.h \
    src/Public/Config.h \
    src/Public/ListWidget.h \
    src/Public/LogWidget.h \
    src/Public/Resources.h \
    src/Public/UserWidget.h \
    src/Public/Utils.h \
    src/Public/http/http.h \
    src/Public/rapidjson/allocators.h \
    src/Public/rapidjson/document.h \
    src/Public/rapidjson/encodedstream.h \
    src/Public/rapidjson/encodings.h \
    src/Public/rapidjson/error/en.h \
    src/Public/rapidjson/error/error.h \
    src/Public/rapidjson/filereadstream.h \
    src/Public/rapidjson/filewritestream.h \
    src/Public/rapidjson/fwd.h \
    src/Public/rapidjson/internal/biginteger.h \
    src/Public/rapidjson/internal/diyfp.h \
    src/Public/rapidjson/internal/dtoa.h \
    src/Public/rapidjson/internal/ieee754.h \
    src/Public/rapidjson/internal/itoa.h \
    src/Public/rapidjson/internal/meta.h \
    src/Public/rapidjson/internal/pow10.h \
    src/Public/rapidjson/internal/regex.h \
    src/Public/rapidjson/internal/stack.h \
    src/Public/rapidjson/internal/strfunc.h \
    src/Public/rapidjson/internal/strtod.h \
    src/Public/rapidjson/internal/swap.h \
    src/Public/rapidjson/istreamwrapper.h \
    src/Public/rapidjson/memorybuffer.h \
    src/Public/rapidjson/memorystream.h \
    src/Public/rapidjson/msinttypes/inttypes.h \
    src/Public/rapidjson/msinttypes/stdint.h \
    src/Public/rapidjson/ostreamwrapper.h \
    src/Public/rapidjson/pointer.h \
    src/Public/rapidjson/prettywriter.h \
    src/Public/rapidjson/rapidjson.h \
    src/Public/rapidjson/reader.h \
    src/Public/rapidjson/schema.h \
    src/Public/rapidjson/stream.h \
    src/Public/rapidjson/stringbuffer.h \
    src/Public/rapidjson/writer.h \
    src/Public/token/AccessToken.h \
    src/Public/token/Packer.h \
    src/mainwindow.h


FORMS += \
    src/Advanced/AudioMixing/AudioMixItem.ui \
    src/Advanced/AudioMixing/AudioMixingEffect.ui \
    src/Advanced/AudioMixing/AudioMixingMedia.ui \
    src/Advanced/RawAudioData/RawAudioData.ui \
    src/Advanced/ByteBeauty/ByteBeautyWidget.ui \
    src/Advanced/CDNStream/CDNStreamByServer.ui \
    src/Advanced/CrossRoomPK/CrossRoomPK.ui \
    src/Advanced/FuBeauty/FaceUnityWidget.ui \
    src/Advanced/FuBeauty/PixTextWidget.ui \
    src/Advanced/MultiRoom/MultiRoom.ui \
    src/Advanced/SoundEffects/SoundEffectsWidget.ui \
    src/Advanced/VideoConfig/VideoConfigWidget.ui \
    src/Basic/QuickStartWidget.ui \
    src/Public/LogWidget.ui \
    src/Public/UserWidget.ui \
    src/mainwindow.ui



# For Windows
msvc {

    #QMAKE_CFLAGS += /utf-8
    #QMAKE_CXXFLAGS += /utf-8
    QMAKE_CXXFLAGS_WARN_ON += -wd4819
    QMAKE_CXXFLAGS_WARN_ON += -wd4100

    MOC_DIR = $$PWD/build/obj
    RCC_DIR = $$PWD/build/obj
    UI_DIR = $$PWD/build/obj
    OBJECTS_DIR = $$PWD/build/obj

    LIBS +=  \
        -luser32 \
        -lgdi32 \
        -lopengl32 \
        -lkernel32 \
        -luser32 \
        -lgdi32 \
        -lwinspool \
        -lshell32 \
        -lole32 \
        -loleaut32 \
        -luuid \
        -lcomdlg32 \
        -ladvapi32

    QMAKE_CXXFLAGS += /bigobj

    INCLUDEPATH += $$PWD/3rd/Windows/VolcEngineRTC/include \
                   $$PWD/3rd/Windows/FaceUnity-SDK/include \
                   $$PWD/3rd/Windows/openssl/include



    contains(QT_ARCH, i386) {
        LIBS += -L$$PWD/3rd/Windows/VolcEngineRTC/lib/Win32 -lVolcEngineRTC
        LIBS += -L$$PWD/3rd/Windows/FaceUnity-SDK/lib/win32 -lCNamaSDK
        LIBS += -L$$PWD/3rd/Windows/openssl/win32/ -llibeay32
        LIBS += -L$$PWD/3rd/Windows/openssl/win32/ -lssleay32

        CONFIG(debug, debug|release){
            # Set debug path
            DESTDIR = $$PWD/bin/Windows/Win32/debug
        } else {
            # Set release path
            DESTDIR = $$PWD/bin/Windows/Win32/release
        }
        QMAKE_PREFIX_PATH += $$[QT_INSTALL_BINS]/..
        PATH1=$$PWD/3rd/Windows/VolcEngineRTC/bin/Win32/*.dll
        PATH2=$$PWD/3rd/Windows/FaceUnity-SDK/lib/win32/*.dll
        PATH3=$$PWD/Resources
        PATH4=$$PWD/3rd/Windows/VolcEngineRTC/cvlab
        PATH5=$$PWD/3rd/Windows/depends/Win32/*.dll
        QMAKE_POST_LINK += xcopy /I /Y /R $$system_path($$PATH1) $$system_path($$DESTDIR)
        QMAKE_POST_LINK += && xcopy /I /Y /R $$system_path($$PATH2) $$system_path($$DESTDIR)
        QMAKE_POST_LINK += && xcopy /I /Y /R /E $$system_path($$PATH3) $$system_path($$DESTDIR/Resources)
        QMAKE_POST_LINK += && xcopy /I /Y /R /E $$system_path($$PATH4) $$system_path($$DESTDIR/Resources/cvlab)
        QMAKE_POST_LINK += && xcopy /I /Y /R /E $$system_path($$PATH5) $$system_path($$DESTDIR)

        QMAKE_POST_LINK += && $$[QT_INSTALL_BINS]/windeployqt.exe $$DESTDIR/API_Example.exe

    } else {
        LIBS += -L$$PWD/3rd/Windows/VolcEngineRTC/lib/x64 -lVolcEngineRTC
        LIBS += -L$$PWD/3rd/Windows/FaceUnity-SDK/lib/win64 -lCNamaSDK
        LIBS += -L$$PWD/3rd/Windows/openssl/x64 -lssleay32
        LIBS += -L$$PWD/3rd/Windows/openssl/x64 -llibeay32

        CONFIG(debug, debug|release){
            # Set debug path
            DESTDIR = $$PWD/bin/Windows/x64/debug
        } else {
            # Set release path
            DESTDIR = $$PWD/bin/Windows/x64/release
        }
        QMAKE_PREFIX_PATH += $$[QT_INSTALL_BINS]/..
        PATH1=$$PWD/3rd/Windows/VolcEngineRTC/bin/x64/*.dll
        PATH2=$$PWD/3rd/Windows/FaceUnity-SDK/lib/win64/*.dll
        PATH3=$$PWD/Resources
        PATH4=$$PWD/3rd/Windows/VolcEngineRTC/cvlab
        PATH5=$$PWD/3rd/Windows/depends/x64/*.dll

        QMAKE_POST_LINK += xcopy /I /Y /R $$system_path($$PATH1) $$system_path($$DESTDIR)
        QMAKE_POST_LINK += && xcopy /I /Y /R $$system_path($$PATH2) $$system_path($$DESTDIR)
        QMAKE_POST_LINK += && xcopy /I /Y /R /E $$system_path($$PATH3) $$system_path($$DESTDIR/Resources)
        QMAKE_POST_LINK += && xcopy /I /Y /R /E $$system_path($$PATH4) $$system_path($$DESTDIR/Resources/cvlab)
        QMAKE_POST_LINK += && xcopy /I /Y /R /E $$system_path($$PATH5) $$system_path($$DESTDIR)
        QMAKE_POST_LINK += && $$[QT_INSTALL_BINS]/windeployqt.exe $$DESTDIR/API_Example.exe
    }

    message("windeployqt path=$$[QT_INSTALL_BINS]/windeployqt")
    message("QMAKE_PREFIX_PATH = $$QMAKE_PREFIX_PATH")
}

macx: {

    message("QMAKE_HOST.arch=$$QMAKE_HOST.arch")
    QMAKE_INFO_PLIST = $$PWD/src/Info.plist
    contains(QMAKE_HOST.arch, arm64) {
        message("ARM 架构")

        INCLUDEPATH += $$PWD/3rd/mac/openssl/include \
            $$PWD/3rd/mac/VolcEngineRTC/arm64/VolcEngineRTC.framework/Headers/native \
            $$PWD/3rd/mac/FaceUnity/include #相芯美颜

        LIBS += -L$$PWD/3rd/mac/openssl/lib/ -lcrypto
        LIBS += -L$$PWD/3rd/mac/FaceUnity/lib/arm64/ -lCnamaSDK #相芯美颜
        LIBS += -L$$PWD/3rd/mac/VolcEngineRTC/arm64/ -lbdaudioeffect
        LIBS += $$PWD/3rd/mac/VolcEngineRTC/arm64/VolcEngineRTC.framework/Versions/3/VolcEngineRTC
        PATH1=$$PWD/3rd/mac/VolcEngineRTC/arm64/*
        PATH2=$$PWD/3rd/mac/FaceUnity/lib/arm64/*.dylib #相芯美颜

    } else {
        message("x86 架构")
        INCLUDEPATH += $$PWD/3rd/mac/openssl/include \
            $$PWD/3rd/mac/VolcEngineRTC/x86/VolcEngineRTC.framework/Headers/native \
            $$PWD/3rd/mac/FaceUnity/include #相芯美颜

        LIBS += -L$$PWD/3rd/mac/openssl/lib/ -lcrypto
        LIBS += -L$$PWD/3rd/mac/FaceUnity/lib/x86_64/ -lCnamaSDK #相芯美颜
        LIBS += -L$$PWD/3rd/mac/VolcEngineRTC/x86/ -lbdaudioeffect
        LIBS += $$PWD/3rd/mac/VolcEngineRTC/x86/VolcEngineRTC.framework/Versions/3/VolcEngineRTC
        PATH1=$$PWD/3rd/mac/VolcEngineRTC/x86/*
        PATH2=$$PWD/3rd/mac/FaceUnity/lib/x86_64/*.dylib #相芯美颜
    }

    LIBS +=  \
        -lssl \
        -lcrypto \


    PRE_TARGETDEPS += $$PWD/3rd/mac/openssl/lib/libcrypto.a

    CONFIG(debug, debug|release){
        DESTDIR = $$PWD/bin/mac/debug
    } else {
        DESTDIR = $$PWD/bin/mac/release
    }

    QMAKE_PRE_LINK += rm -f $$DESTDIR/*.dmg

    PATH3=$$PWD/Resources
    PATH4=$$PWD/3rd/mac/VolcEngineRTC/cvlab
    QMAKE_POST_LINK += $$[QT_INSTALL_BINS]/macdeployqt $$DESTDIR/API_Example.app
    QMAKE_POST_LINK += && cp -R $$system_path($$PATH1) $$system_path($$DESTDIR/API_Example.app/Contents/Frameworks)
    QMAKE_POST_LINK += && cp -R $$system_path($$PATH2) $$system_path($$DESTDIR/API_Example.app/Contents/Frameworks) #相芯美颜
    QMAKE_POST_LINK += && cp -R $$system_path($$PATH3) $$system_path($$DESTDIR/API_Example.app/Contents/MacOS)
    QMAKE_POST_LINK += && cp -R $$system_path($$PATH4) $$system_path($$DESTDIR/API_Example.app/Contents/MacOS/Resources)
    #QMAKE_POST_LINK += && $$[QT_INSTALL_BINS]/macdeployqt $$DESTDIR/API_Example.app -dmg
}


RESOURCES += \
    resources.qrc


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



