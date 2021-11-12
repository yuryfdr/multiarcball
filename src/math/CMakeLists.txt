project(3dmath)

set(SOURCES
	3dcontrols.cpp
	basic_ball.cpp
	)
set(HEADERS
	3dcontrols.h
	basic_ball.h
	vmmath.h
	)

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})
#add_dependencies(${PROJECT_NAME} ...)
add_library(3dmathinc INTERFACE ${HEADERS})
target_include_directories(3dmathinc
	INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	$<INSTALL_INTERFACE:include/multiarcball>
	)
target_include_directories(3dmath
	INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	$<INSTALL_INTERFACE:include/multiarcball>
	)

target_link_libraries(${PROJECT_NAME} OpenGL::GLU)
target_link_options(${PROJECT_NAME} PUBLIC "LINKER:--as-needed")

install(TARGETS ${PROJECT_NAME}
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	)
set_target_properties(
	${PROJECT_NAME}
	PROPERTIES
	SOVERSION ${PACKAGE_VERSION}
	VERSION ${PACKAGE_VERSION}
	)

install(FILES ${HEADERS} DESTINATION include/multiarcball )
