project(FLarcball)

include_directories(
    ${3dmath_SOURCE_DIR}
    ${FLTK_INCLUDE_DIR}
)

set(SOURCES
FlGlArcballWindow.cpp
)
add_library(${PROJECT_NAME} SHARED ${SOURCES})
add_dependencies(${PROJECT_NAME} 3dmath)

target_link_libraries(${PROJECT_NAME} 3dmath ${FLTK_LIBRARY})
target_link_options(${PROJECT_NAME} PUBLIC "LINKER:--as-needed")

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
)
set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
     SOVERSION ${PACKAGE_VERSION}
     VERSION ${PACKAGE_VERSION}
)

