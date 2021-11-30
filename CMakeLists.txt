project(multiarcball)
cmake_minimum_required(VERSION 3.9)

option(WITH_FLTK "enable GUI fltk" ON)
option(WITH_GTK "enable GUI fltk" OFF)

if(WITH_FLTK)
	if(WIN32 AND NOT MINGW)
		set(FLTK_SKIP_FLUID TRUE)
		set(FLTK_SKIP_FORMS TRUE)
		set(FLTK_SKIP_IMAGES TRUE)
		set(FLTK_SKIP_OPENGL TRUE)
		add_definitions(-DFL_DLL -DNOMINMAX -D_USE_MATH_DEFINES)
		find_library(ws2_32 NAMES ws2_32)
	endif(WIN32)

	find_package(FLTK)
endif(WITH_FLTK)

find_package(OpenGL)
if(WITH_GTK)
	find_package(PkgConfig)

	if(PkgConfig_FOUND)
		pkg_check_modules(GTKMM gtkmm-3.0)
		message(STATUS "gtkmm" ${GTKMM_VERSION})
	endif(PkgConfig_FOUND)
endif(WITH_GTK)

set(PACKAGE_VERSION 0.4)
set(PACKAGE_FULL_VERSION 0.4.0)

include(GNUInstallDirs)

add_subdirectory(src)
add_subdirectory(test)
