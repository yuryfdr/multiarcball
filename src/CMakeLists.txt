project(multiarcball)

add_subdirectory(math)
add_subdirectory(FLui)

if(WITH_GTK)
	add_subdirectory(gtkmm3ui)
endif(WITH_GTK)

install(TARGETS 3dmath 3dmathinc FLarcball
	    DESTINATION ${CMAKE_INSTALL_LIBDIR}
		EXPORT MultiarcballTargets
)
install(EXPORT MultiarcballTargets
  FILE MultiarcballTargets.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Multiarcball
)


include(CMakePackageConfigHelpers)
# generate the config file that is includes the exports
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/MultiarcballConfig.cmake"
  INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/Multiarcball"
  NO_SET_AND_CHECK_MACRO
  NO_CHECK_REQUIRED_COMPONENTS_MACRO
  )
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/MultiarcballConfig.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Multiarcball
  )
