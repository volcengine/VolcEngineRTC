
include(GetPrerequisites)
message("---------------start----------------")
message("step 1:find QTDIR, ENV{QTDIR}=$ENV{QTDIR}")

if ("${QTDIR}" STREQUAL "")
    set(QTDIR $ENV{QTDIR})
endif()

if ("${QTDIR}" STREQUAL "")
    message(FATAL_ERROR "NOT FOUND QTDIR")
endif()

message("QTDIR=${QTDIR}")
list(APPEND CMAKE_PREFIX_PATH "${QTDIR}")

cmake_minimum_required(VERSION 3.5)
project(API_Demo VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    message("current platform is Windows")
    set(DEPLOYQT ${QTDIR}\\bin\\windeployqt.exe)
    set(PLATFORM "Windows")
    set(3RD_PATH ${CMAKE_CURRENT_LIST_DIR}/3rd/Windows)

    set(VolcEngineRTC_PATH ${3RD_PATH}/VolcEngineRTC)
    set(VolcEngineRTC_PATH_INCLUDE ${VolcEngineRTC_PATH}/include)
    set(FaceUnity_PATH ${3RD_PATH}/FaceUnity-SDK)
    set(FaceUnity_INCLUDE_PATH ${3RD_PATH}/FaceUnity-SDK/include)


        if(NOT CMAKE_BUILD_TYPE) #默认Debug
                set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type" FORCE)
        endif()
        if(CMAKE_BUILD_TYPE STREQUAL "Debug")
                add_compile_options(/DEBUG /Od)
        else()
                add_compile_options(/O2 /DNDEBUG)
        endif()


    if(CMAKE_SIZEOF_VOID_P EQUAL 4) #32位
        message("platform is: windows x86")
        set(OUT_BIT_DIR "Win32")
        set(VolcEngineRTC_Lib ${VolcEngineRTC_PATH}/lib/Win32/VolcEngineRTC.lib)
        set(VolcEngineRTC_Bin ${VolcEngineRTC_PATH}/bin/Win32)
        set(FaceUnity_Lib ${3RD_PATH}/FaceUnity-SDK/lib/win32/CNamaSDK.lib)
        set(FaceUnity_Bin ${3RD_PATH}/FaceUnity-SDK/lib/win32)

        set(libeay32_Lib ${3RD_PATH}/openssl/win32/libeay32.lib)
        set(ssleay32_Lib ${3RD_PATH}/openssl//win32/ssleay32.lib)

    else()
        message("platform is: windows x64")
        set(OUT_BIT_DIR "x64")
        set(VolcEngineRTC_Lib ${VolcEngineRTC_PATH}/lib/x64/VolcEngineRTC.lib)
        set(VolcEngineRTC_Bin ${VolcEngineRTC_PATH}/bin/x64)
        set(FaceUnity_Lib ${3RD_PATH}/FaceUnity-SDK/lib/win64/CNamaSDK.lib)
        set(FaceUnity_Bin ${3RD_PATH}/FaceUnity-SDK/lib/win64)
        set(libeay32_Lib ${3RD_PATH}/openssl/x64/libeay32.lib)
        set(ssleay32_Lib ${3RD_PATH}/openssl/x64/ssleay32.lib)
    endif()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/Windows/${OUT_BIT_DIR})
    set(OpenSSL_INCLUDE ${3RD_PATH}/openssl/include)

elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")

    set(PLATFORM "macos")
    set(DEPLOYQT ${QTDIR}/bin/macdeployqt)
    set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64" CACHE INTERNAL "" FORCE) #支持x86和arm64两种架构
    set(3RD_PATH ${CMAKE_CURRENT_LIST_DIR}/3rd/mac)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/mac)
    set(VolcEngineRTC_PATH ${3RD_PATH}/VolcEngineRTC/VolcEngineRTC.framework)
    set(VolcEngineRTC_PATH_INCLUDE ${VolcEngineRTC_PATH}/Headers/native)
    set(VolcEngineRTC_Lib ${VolcEngineRTC_PATH}/Versions/3/VolcEngineRTC)

    set(FaceUnity_PATH ${3RD_PATH}/FaceUnity)
    set(FaceUnity_INCLUDE_PATH ${FaceUnity_PATH}/include)
    set(FaceUnity_Lib ${FaceUnity_PATH}/lib/libCnamaSDK.dylib)

    set(OpenSSL_INCLUDE ${3RD_PATH}/openssl/include)
    set(libcrypto_Lib ${3RD_PATH}/openssl/lib/libcrypto.a)

    message(DEPLOYQT=${DEPLOYQT})



    set(SRC_COPY
        ${3RD_PATH}/VolcEngineRTC
        ${FaceUnity_PATH}/lib
    )
endif()

set(QRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/resources.qrc)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
message("QT version=${QT_VERSION_MAJOR}")
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
	set(CMAKE_CXX_STANDARD 17)
	set(CMAKE_CXX_STANDARD_REQUIRED ON)
	find_package(Qt6 COMPONENTS Core Gui Widgets Network REQUIRED)
	qt_add_resources(QRC_SOURCES ${QRC_FILES})
else()

	find_package(Qt5 COMPONENTS Core Gui Widgets Network REQUIRED)
	qt5_add_resources(QRC_SOURCES ${QRC_FILES})
endif()




set(PROJECT_SOURCES
        src/main.cpp
        src/Basic/QuickStartWidget.cpp
        src/Basic/QuickStartWidget.h
        src/Basic/QuickStartWidget.ui
        src/Public/token/AccessToken.h
        src/Public/token/Packer.cpp
        src/Public/token/Packer.h
        src/Public/token/utils.h
        src/Public/BaseItem.h
        src/Public/Config.h
        src/Public/Resources.h
        src/Public/Utils.h
        src/Public/Utils.cpp
        src/Public/http/http.h
        src/Public/http/http.cpp
        src/mainwindow.cpp
        src/mainwindow.h
        src/mainwindow.ui
        src/Advanced/MultiRoom/MultiRoom.h
        src/Advanced/MultiRoom/MultiRoom.cpp
        src/Advanced/MultiRoom/MultiRoom.ui
        src/Advanced/FuBeauty/FaceUnityWidget.cpp
        src/Advanced/FuBeauty/FaceUnityWidget.h
        src/Advanced/FuBeauty/FaceUnityWidget.ui
        src/Advanced/FuBeauty/PixTextWidget.h
        src/Advanced/ByteBeauty/ByteBeautyWidget.cpp
        src/Advanced/ByteBeauty/ByteBeautyWidget.h
        src/Advanced/ByteBeauty/ByteBeautyWidget.ui
        src/Advanced/FuBeauty/PixTextWidget.cpp
        src/Advanced/FuBeauty/PixTextWidget.ui
        src/Advanced/FuBeauty/Nama.h
        src/Advanced/FuBeauty/Nama.cpp
        src/Advanced/CDNStream/CDNStreamByServer.h
        src/Advanced/CDNStream/CDNStreamByServer.cpp
        src/Advanced/CDNStream/CDNStreamByServer.ui
        src/Public/UserWidget.h
        src/Public/UserWidget.cpp
        src/Public/UserWidget.ui
        src/Advanced/SoundEffects/SoundEffectsWidget.h
        src/Advanced/SoundEffects/SoundEffectsWidget.cpp
        src/Advanced/SoundEffects/SoundEffectsWidget.ui
        src/Public/ByteRTCEventHandler.h
        src/Public/ByteRTCEventHandler.cpp
        src/Public/LogWidget.h
        src/Public/LogWidget.cpp
        src/Public/LogWidget.ui
        src/Advanced/CrossRoomPK/CrossRoomPK.h
        src/Advanced/CrossRoomPK/CrossRoomPK.cpp
        src/Advanced/CrossRoomPK/CrossRoomPK.ui
        src/Advanced/VideoConfig/VideoConfigWidget.h
        src/Advanced/VideoConfig/VideoConfigWidget.cpp
        src/Advanced/VideoConfig/VideoConfigWidget.ui
        src/Advanced/AudioMixing/AudioMixingEffect.ui
        src/Advanced/AudioMixing/AudioMixingEffect.h
        src/Advanced/AudioMixing/AudioMixingEffect.cpp
        src/Advanced/AudioMixing/AudioMixingMedia.ui
        src/Advanced/AudioMixing/AudioMixingMedia.h
        src/Advanced/AudioMixing/AudioMixingMedia.cpp
        src/Advanced/AudioMixing/AudioMixItem.h
        src/Advanced/AudioMixing/AudioMixItem.cpp
        src/Advanced/AudioMixing/AudioMixItem.ui
        src/Advanced/AudioMixing/RawAudioData.cpp
        src/Advanced/AudioMixing/RawAudioData.h
        src/Advanced/AudioMixing/RawAudioData.ui
        src/Public/ListWidget.h
        src/Public/ListWidget.cpp
        src/Public/BaseWidget.h
        src/Public/BaseWidget.cpp
        src/resources.rc
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${QRC_SOURCES})

include_directories(
    ${VolcEngineRTC_PATH_INCLUDE}
    ${FaceUnity_INCLUDE_PATH}
    ${OpenSSL_INCLUDE}
    src
    src/Advanced/MultiRoom
    src/Public
    src/Public/http
    src/Public/token
    src/Advanced/FuBeauty
    src/Advanced/FuBeauty/Sound
    src/Advanced/
    src/Basic
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/src/Info.plist
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

message("step 2: target_link_libraries")
target_link_libraries(${PROJECT_NAME} PRIVATE ${FaceUnity_Lib} ${VolcEngineRTC_Lib})
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
	target_link_libraries(${PROJECT_NAME} PRIVATE
		Qt6::Widgets
		Qt6::Network
	)
elseif()
	target_link_libraries(${PROJECT_NAME} PRIVATE
		Qt5::Widgets
		Qt5::Network
	)
endif()

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        opengl32
        ${FaceUnity_Lib}
        ${libeay32_Lib}
        ${ssleay32_Lib}
    )
elseif(APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        "-framework OpenGL"
        ${libcrypto_Lib}
    )
endif()


message("step 3: copy resources to app dir")


if (${PLATFORM} STREQUAL "macos")
    message("copy 3rd libs to bin")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${SRC_COPY} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.app/Contents/Frameworks
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/Resources ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.app/Contents/MacOS/Resources
        COMMENT "copy mac 3rd libs"
    )


    message("execute mac_depends")
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND bash -c "cd ${CMAKE_CURRENT_SOURCE_DIR}"
        COMMAND bash -c "${CMAKE_CURRENT_SOURCE_DIR}/script/mac_depens.sh ${DEPLOYQT} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} ${PROJECT_NAME} >${CMAKE_CURRENT_SOURCE_DIR}/script/output.txt"
        COMMENT "execute mac_depends"
        DEPENDS ${PROJECT_NAME}
    )

elseif(${PLATFORM} STREQUAL "Windows")
        message("VolcEngineRTC_Bin= ${VolcEngineRTC_Bin}")
        message("CMAKE_RUNTIME_OUTPUT_DIRECTORY=${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
        message("DEPLOYQT=${DEPLOYQT}")
        message("Configuration=$(Configuration)")
        message("CMAKE_BUILD_TYPE =${CMAKE_BUILD_TYPE}")


        set(DST_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration))
        message("DST_DIR=${DST_DIR}")


        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory ${VolcEngineRTC_Bin} ${FaceUnity_Bin} ${DST_DIR}
                COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/Resources ${DST_DIR}/Resources
                COMMAND ${DEPLOYQT} ${DST_DIR}\\${PROJECT_NAME}.exe
        )


endif()

message("-------------------- stop ------------------------")







