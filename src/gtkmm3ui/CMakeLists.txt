project(gtk3arcball)

include_directories(
    ${3dmath_SOURCE_DIR}
    ${GTKMM_INCLUDE_DIRS}
)

set(SOURCES
gtkmm_arcball.cpp
)
set(HEADERS
gtkmm_arcball.h
)

if(WIN32)
add_definitions(-DFL_DLL)
endif(WIN32)

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})
add_dependencies(${PROJECT_NAME} 3dmath)

target_link_libraries(${PROJECT_NAME} 3dmath ${GTKMM_LIBRARIES})
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

install(FILES ${HEADERS} DESTINATION include/multiarcball/gtk )
