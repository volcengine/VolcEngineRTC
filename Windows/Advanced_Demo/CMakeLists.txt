cmake_minimum_required(VERSION 3.1)

project(Advanced_Demo)

IF(CMAKE_CL_64)
    set(BYTERTC_WIN32 0)
ELSE(CMAKE_CL_64)
    set(BYTERTC_WIN32 1)
ENDIF(CMAKE_CL_64)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC OFF)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

#set ouput path    
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_BINARY_DIR}/$(Configuration)/Advanced_Demo)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_BINARY_DIR}/$(Configuration)/Advanced_Demo)
message(STATUS "EXECUTABLE_OUTPUT_PATH = ****${PROJECT_BINARY_DIR}")

IF (BYTERTC_WIN32)
   list(APPEND CMAKE_PREFIX_PATH "$ENV{Qt32Path}")
   set(WINDEPLOYQT_PATH $ENV{Qt32Path}\\..\\..\\bin)
   set(PLATFORM "Win32")
ELSE ()
list(APPEND CMAKE_PREFIX_PATH "$ENV{Qt64Path}")
set(WINDEPLOYQT_PATH $ENV{Qt64Path}\\..\\..\\bin)
set(PLATFORM "x64")
ENDIF ()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
	set(CMAKE_CXX_STANDARD 17)
	set(CMAKE_CXX_STANDARD_REQUIRED ON)
	find_package(Qt6 COMPONENTS Core Gui Widgets Network REQUIRED)
else()
	find_package(Qt5 COMPONENTS Core Gui Widgets Network REQUIRED)
endif()

set(VolcEngineRTC_Lib "VolcEngineRTC")

include_directories(${CMAKE_SOURCE_DIR})

#link VolcEngineRTC lib
include_directories(${CMAKE_SOURCE_DIR}/${VolcEngineRTC_Lib}/include)

set(CMAKE_AUTOMOC TRUE)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#ui
FILE(GLOB UI_FILES "ui/*.ui")
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_wrap_ui(MainWindow_UI_FILES ${UI_FILES})
else()
	qt5_wrap_ui(MainWindow_UI_FILES ${UI_FILES})
endif()
list(APPEND ALL_SOURCES_AND_HEADERS ${UI_FILES})

message(STATUS "**************${MainWindow_UI_FILES}*************")


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_resources(MainWindow_QRC_FILES app.qrc)
else()
	qt5_add_resources(MainWindow_QRC_FILES app.qrc)
endif()
#qrc

#sources
FILE(GLOB SOURCES_SOURCES_AND_HEADERS "sources/*.h" "sources/*.cpp")
source_group(sources FILES ${SOURCES_SOURCES_AND_HEADERS})
list(APPEND ALL_SOURCES_AND_HEADERS ${SOURCES_SOURCES_AND_HEADERS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/sources)

#sources/http
FILE(GLOB SOURCES_SOURCES_AND_HEADERS "sources/http/*.h" "sources/http/*.cpp")
source_group(sources/http FILES ${SOURCES_SOURCES_AND_HEADERS})
list(APPEND ALL_SOURCES_AND_HEADERS ${SOURCES_SOURCES_AND_HEADERS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/sources/http)

FILE(GLOB SOURCES_SOURCES_AND_HEADERS "sources/screen_share/*.h" "sources/screen_share/*.cpp")
source_group(sources/screen_share FILES ${SOURCES_SOURCES_AND_HEADERS})
list(APPEND ALL_SOURCES_AND_HEADERS ${SOURCES_SOURCES_AND_HEADERS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/sources/screen_share)

add_executable(Advanced_Demo WIN32
	${ALL_SOURCES_AND_HEADERS}
	${MainWindow_QRC_FILES}
	"app.rc"
	)
	
set( ENV{PATH} ${QTDIR} )

IF (BYTERTC_WIN32)
target_link_directories(Advanced_Demo PUBLIC ${CMAKE_SOURCE_DIR}/${VolcEngineRTC_Lib}/lib/${PLATFORM})
ELSE ()
target_link_directories(Advanced_Demo PUBLIC ${CMAKE_SOURCE_DIR}/${VolcEngineRTC_Lib}/lib/${PLATFORM})
ENDIF ()

target_link_libraries(Advanced_Demo
	Qt${QT_VERSION_MAJOR}::Core
	Qt${QT_VERSION_MAJOR}::Gui
	Qt${QT_VERSION_MAJOR}::Widgets
	Qt${QT_VERSION_MAJOR}::Network
	${VolcEngineRTC_Lib}
	)
	
set(SRC_DIR ${CMAKE_SOURCE_DIR}/${VolcEngineRTC_Lib}/bin/${PLATFORM})
string(REPLACE "/" "\\" SRC_DIR ${SRC_DIR})
message(${SRC_DIR})	

set(DEPENDS_DIR ${CMAKE_SOURCE_DIR}/Depends/${PLATFORM})
string(REPLACE "/" "\\" DEPENDS_DIR ${DEPENDS_DIR})
message(${DEPENDS_DIR})	

set(DST_DIR \"${PROJECT_BINARY_DIR}/$(Configuration)/Advanced_Demo\")
string(REPLACE "/" "\\" DST_DIR ${DST_DIR})
message(${DST_DIR})

set(CVLAB ${CMAKE_SOURCE_DIR}/Resources/cvlab)
string(REPLACE "/" "\\" CVLAB ${CVLAB})
message(${CVLAB})

set(CVLAB_DST_DIR "${DST_DIR}\\cvlab\\")
add_custom_command(TARGET Advanced_Demo POST_BUILD
	COMMAND cd ${DST_DIR}
    COMMAND copy ${SRC_DIR}\\*.dll . /y
	COMMAND copy ${DEPENDS_DIR}\\*.dll . /y
	COMMAND xcopy ${CVLAB} ${CVLAB_DST_DIR} /y/e
	COMMAND cd ${WINDEPLOYQT_PATH}
    COMMAND if $(Configuration) equ Debug (${WINDEPLOYQT_PATH}\\windeployqt.exe --debug ${DST_DIR}\\Advanced_Demo.exe)
    COMMAND if $(Configuration) equ Release (${WINDEPLOYQT_PATH}\\windeployqt.exe --release ${DST_DIR}\\Advanced_Demo.exe)
	)