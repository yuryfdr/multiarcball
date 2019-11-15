
AM_CPPFLAGS = -I../math -I..

if USE_QT5

QA5 = libQarcball5.la

libQarcball5_la_CXXFLAGS =  @QT_CFLAGS@ 

nodist_libQarcball5_la_SOURCES = moc_QArcballWidget5.cpp 

libQarcball5_la_SOURCES = QArcballWidget.cpp 

libQarcball5_la_LDFLAGS = @LTNOUNDEF@ @LIB_XCURSOR@ @QT_LIBS@ -version-info @MA_LT_VERSION@ 

libQarcball5_la_LIBADD = ../math/lib3dmath.la 

libQarcball5_la_HEADERS = QArcballWidget.h

libQarcball5_ladir = \
	$(pkgincludedir)/Qt5

moc_QArcballWidget5.cpp:QArcballWidget.h Makefile
	@MOC@ @MOC_ADD_OPT@ -o$@ $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(MOC_CPPFLAGS) QArcballWidget.h 
endif

lib_LTLIBRARIES = $(QA4) $(QA5)
distclean-local:
	rm -f moc_QArcballWidget5.cpp
