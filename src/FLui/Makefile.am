
AM_CPPFLAGS = -I../math

if USE_FLTK 

if USE_OLDCURSORS
CURSSRC = ../flcursors/fltk1/Fl_Custom_Cursor.cxx
CURDEF = -DUSE_OLDCURSORS
endif

lib_LTLIBRARIES = libFLarcball.la

libFLarcball_la_CXXFLAGS =  @FL_CXXFLAGS@ $(CURDEF)

libFLarcball_la_SOURCES = FlGlArcballWindow.cpp $(CURSSRC)

libFLarcball_la_LDFLAGS = @LTNOUNDEF@ @LIB_XCURSOR@ @FL_LDFLAGS@ -version-info @MA_LT_VERSION@ 

libFLarcball_la_LIBADD = ../math/lib3dmath.la 

libFLarcball_la_HEADERS = FlGlArcballWindow.h

libFLarcball_ladir = \
	$(pkgincludedir)/FL

noinst_HEADERS = ../flcursors/fltk1/Fl_Custom_Cursor.H

endif

EXTRA_DIST=$(noinst_DATA) CMakeLists.txt
