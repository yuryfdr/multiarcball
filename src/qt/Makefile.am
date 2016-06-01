
AM_CPPFLAGS = -I../math

if USE_QT

lib_LTLIBRARIES = libQarcball.la

libQarcball_la_CXXFLAGS =  @QT_CFLAGS@ 

libQarcball_la_SOURCES = moc_QArcballWidget.cpp QArcballWidget.cpp 

libQarcball_la_LDFLAGS = @LTNOUNDEF@ @LIB_XCURSOR@ @QT_LIBS@ -version-info @MA_LT_VERSION@ 

libQarcball_la_LIBADD = ../math/lib3dmath.la 

libQarcball_la_HEADERS = QArcballWidget.h

libQarcball_ladir = \
	$(pkgincludedir)/Qt

moc_QArcballWidget.cpp:QArcballWidget.h Makefile
	@MOC@ @MOC_ADD_OPT@ -o$@ $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(MOC_CPPFLAGS) QArcballWidget.h # $<
#	@MOC@ -I@QMK_INC@ -I@QMK_INC@/QtOpenGL -o moc_QArcballWidget.cpp QArcballWidget.h
endif

distclean-local:
	rm moc_QArcballWidget.cpp
