project(multiarcball_tests)
include_directories(
    ${3dmath_SOURCE_DIR}
    ${FLarcball_SOURCE_DIR}
    ${FLTK_INCLUDE_DIR}
)
add_executable(exampleFL exampleFL.cpp)
add_dependencies(exampleFL FLarcball)
target_link_libraries(exampleFL FLarcball)

add_executable(testFL testFL.cpp)
add_dependencies(testFL FLarcball )
target_link_libraries(testFL FLarcball)

add_executable(testmath testmath.cpp)

if(GTKMM_FOUND)
add_executable(testGtk3 testGtk3.cxx)
add_dependencies(testGtk3 gtk3arcball)
target_link_libraries(testGtk3 gtk3arcball)
target_include_directories(testGtk3 PRIVATE ${gtk3arcball_SOURCE_DIR} PUBLIC ${GTKMM_INCLUDE_DIRS})
endif(GTKMM_FOUND)
