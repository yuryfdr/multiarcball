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
