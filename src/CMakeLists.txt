project(multiarcball)

add_subdirectory(math)
add_subdirectory(FLui)

if(WITH_GTK)
	add_subdirectory(gtkmm3ui)
endif(WITH_GTK)
