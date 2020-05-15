project(multiarcball)
cmake_minimum_required(VERSION 3.9)

find_package(FLTK)
find_package(OpenGL)
find_package(PkgConfig)

if(PkgConfig_FOUND)
pkg_check_modules(GTKMM gtkmm-3.0)
message(STATUS "gtkmm" ${GTKMM_VERSION})
endif(PkgConfig_FOUND)

set(PACKAGE_VERSION 0.4)
set(PACKAGE_FULL_VERSION 0.4.0)

add_subdirectory(src)
add_subdirectory(test)
