cmake_minimum_required(VERSION 3.15)

cmake_policy(SET CMP0092 NEW)  # don't use CMake's default compiler warning settings, as we're adding our own below

project(avpipe
	VERSION 0.1.0
	DESCRIPTION "Tool for editing and converting audio and video streams"
	HOMEPAGE_URL "https://github.com/DrFrankenstein/avpipe"
	LANGUAGES CXX
)

find_package(Git)
if(NOT ${GIT_FOUND})
	set(PROJECT_BUILD unknown)
else()
	execute_process(
		COMMAND ${GIT_EXECUTABLE} describe --always --dirty
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
		OUTPUT_VARIABLE PROJECT_BUILD
		OUTPUT_STRIP_TRAILING_WHITESPACE
	)
endif()

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/scripts")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Boost REQUIRED)

find_package(Qt5 COMPONENTS Widgets MultimediaWidgets REQUIRED)

find_package(FFMPEG)
if(NOT ${FFMPEG_FOUND})
	# try with pkg-config
	# This is probably brittle as we link by library name instead of using PkgConfig::module,
	# but it works for now.
	message("Trying to find FFmpeg through pkg-config instead...")

	set(USING_PKG_CONFIG ON)
	find_package(PkgConfig REQUIRED)
	pkg_check_modules(FFMPEG REQUIRED
		libavformat libavcodec libavdevice libavfilter)
endif()

include_directories(${FFMPEG_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
link_directories(${FFMPEG_LIBRARY_DIRS})

if(MSVC)
	# level 4 warnings, no warnings in external headers
	# /Wall provides nothing useful over /W4, and warns on really insignificant things such as the existence of padding
	add_compile_options(/W4 /experimental:external /external:anglebrackets /external:W0)
else()
	# ALL THE WARNINGS
	add_compile_options(-Wall -Wextra -pedantic)
endif()

configure_file(config.h.in ${CMAKE_SOURCE_DIR}/config.h)

set(HEADERS
	config.h
	avpipe.h
	libavxx/Dictionary.hpp
	libavxx/Error.hpp
	libavxx/FormatContext.hpp
	Gui/MainWindow.hpp
	Gui/AboutDialog.hpp
	Gui/ViewModels/SourceViewModel.hpp
)

set(SOURCES
	avpipe.cpp
	libavxx/Error.cpp
	Gui/MainWindow.cpp
	Gui/AboutDialog.cpp
	Gui/ViewModels/SourceViewModel.cpp
)

set(UIS
	Gui/MainWindow.ui
	Gui/AboutDialog.ui
)

set(LIBS
	Qt5::Widgets
	Qt5::MultimediaWidgets
	avformat
	avutil
)

add_executable(avpipe ${SOURCES} ${HEADERS} ${UIS})
target_link_libraries(avpipe ${LIBS})

if(WIN32)
	include(DeployQt)
	windeployqt(avpipe)
endif()

