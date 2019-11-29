project(FLarcball)

include_directories(
    ${3dmath_SOURCE_DIR}
    ${FLTK_INCLUDE_DIR}
)

set(SOURCES
FlGlArcballWindow.cpp
)
set(HEADERS
FlGlArcballWindow.h
)

if(WIN32)
add_definitions(-DFL_DLL)
endif(WIN32)

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})
add_dependencies(${PROJECT_NAME} 3dmath)

target_link_libraries(${PROJECT_NAME} 3dmath ${FLTK_LIBRARY})
target_link_options(${PROJECT_NAME} PUBLIC "LINKER:--as-needed")

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
     SOVERSION ${PACKAGE_VERSION}
     VERSION ${PACKAGE_VERSION}
)

install(FILES ${HEADERS} DESTINATION include/multiarcball/FL )
