project(multiarcball)

add_subdirectory(math)
add_subdirectory(FLui)

if(GTKMM_FOUND)
add_subdirectory(gtkmm3ui)
endif(GTKMM_FOUND)