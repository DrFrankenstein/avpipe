cmake_minimum_required(VERSION 3.8)

project(avpipe
	VERSION 0.1.0
	DESCRIPTION "Tool for editing and converting audio and video streams"
	HOMEPAGE_URL "https://github.com/DrFrankenstein/avpipe"
	LANGUAGES CXX
)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/scripts")

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets MultimediaWidgets REQUIRED)

# add these to your CMake variables before building
include_directories(${FFMPEG_INCLUDE_DIR})
link_directories(${FFMPEG_LIB_DIR})

if (MSVC)
	# level 4 warnings, no warnings in external headers
	# /Wall provides nothing useful over /W4, and warns on really insignificant things such as the existence of padding
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /experimental:external /external:anglebrackets /external:W0 ")
else ()
	# ALL THE WARNINGS
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic ")
endif ()

set(HEADERS
	avpipe.h
	mainwindow.hpp
)

set(SOURCES
	avpipe.cpp
	mainwindow.cpp
)

set(UIS
	mainwindow.ui
)

set(LIBS
	Qt5::Widgets
	Qt5::MultimediaWidgets
)

qt5_wrap_ui(${UIS})
add_executable(avpipe ${SOURCES} ${HEADERS})
target_link_libraries(avpipe ${LIBS})

if(WIN32)
	include(DeployQt)
	windeployqt(avpipe)
endif()

