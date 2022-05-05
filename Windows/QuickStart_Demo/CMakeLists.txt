cmake_minimum_required(VERSION 3.1)

project(QuickStart)

IF(CMAKE_CL_64)
    set(BYTERTC_WIN32 0)
ELSE(CMAKE_CL_64)
    set(BYTERTC_WIN32 1)
ENDIF(CMAKE_CL_64)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /source-charset:utf-8")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC OFF)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

#set ouput path    
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_BINARY_DIR}/$(Configuration)/QuickStart)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_BINARY_DIR}/$(Configuration)/QuickStart)
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
	
find_package(Qt5Widgets ${FIND_MODE})
find_package(Qt5Network ${FIND_MODE})
find_package(Qt5Core ${FIND_MODE})
find_package(Qt5Gui ${FIND_MODE})

set(VolcEngineRTC_Lib "VolcEngineRTC")

include_directories(${CMAKE_SOURCE_DIR})

#link VolcEngineRTC lib
include_directories(${CMAKE_SOURCE_DIR}/${VolcEngineRTC_Lib}/include/rtc)
include_directories(${CMAKE_SOURCE_DIR}/${VolcEngineRTC_Lib}/include/rts)

set(CMAKE_AUTOMOC TRUE)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#ui
FILE(GLOB UI_FILES "ui/*.ui")
qt5_wrap_ui(MainWindow_UI_FILES ${UI_FILES})
list(APPEND ALL_SOURCES_AND_HEADERS ${UI_FILES})

message(STATUS "**************${MainWindow_UI_FILES}*************")
qt5_add_resources(MainWindow_QRC_FILES QuickStart.qrc)
#qrc

#sources
FILE(GLOB SOURCES_SOURCES_AND_HEADERS "sources/*.h" "sources/*.cpp")
source_group(sources FILES ${SOURCES_SOURCES_AND_HEADERS})
list(APPEND ALL_SOURCES_AND_HEADERS ${SOURCES_SOURCES_AND_HEADERS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/sources)

add_executable(QuickStart WIN32
	${ALL_SOURCES_AND_HEADERS}
	${MainWindow_QRC_FILES}
	"app.rc"
	)
	
set( ENV{PATH} ${QTDIR} )

IF (BYTERTC_WIN32)
target_link_directories(QuickStart PUBLIC ${CMAKE_SOURCE_DIR}/${VolcEngineRTC_Lib}/lib/${PLATFORM})
ELSE ()
target_link_directories(QuickStart PUBLIC ${CMAKE_SOURCE_DIR}/${VolcEngineRTC_Lib}/lib/${PLATFORM})
ENDIF ()

target_link_libraries(QuickStart
	Qt5::Widgets
	Qt5::Network
	${VolcEngineRTC_Lib}
	)
	
set(SRC_DIR ${CMAKE_SOURCE_DIR}/${VolcEngineRTC_Lib}/bin/${PLATFORM})
string(REPLACE "/" "\\" SRC_DIR ${SRC_DIR})
message(${SRC_DIR})	

set(DST_DIR \"${PROJECT_BINARY_DIR}/$(Configuration)/QuickStart\")
string(REPLACE "/" "\\" DST_DIR ${DST_DIR})
message(${DST_DIR})
	
add_custom_command(TARGET QuickStart POST_BUILD
	COMMAND cd ${DST_DIR}
    COMMAND copy ${SRC_DIR}\\*.dll . /y
	COMMAND cd ${WINDEPLOYQT_PATH}
    COMMAND if $(Configuration) equ Debug (${WINDEPLOYQT_PATH}\\windeployqt.exe --debug ${DST_DIR}\\QuickStart.exe)
    COMMAND if $(Configuration) equ Release (${WINDEPLOYQT_PATH}\\windeployqt.exe --release ${DST_DIR}\\QuickStart.exe)
	)