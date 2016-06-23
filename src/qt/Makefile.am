
AM_CPPFLAGS = -I../math

if USE_QT4

QA4 = libQarcball4.la

libQarcball4_la_CXXFLAGS =  @QT4_CFLAGS@ 

libQarcball4_la_SOURCES = moc_QArcballWidget4.cpp QArcballWidget.cpp 

libQarcball4_la_LDFLAGS = @LTNOUNDEF@ @LIB_XCURSOR@ @QT4_LIBS@ -version-info @MA_LT_VERSION@ 

libQarcball4_la_LIBADD = ../math/lib3dmath.la 

libQarcball4_la_HEADERS = QArcballWidget.h

libQarcball4_ladir = \
	$(pkgincludedir)/Qt4

moc_QArcballWidget4.cpp:QArcballWidget.h Makefile
	@MOC4@ @MOC4_ADD_OPT@ -o$@ -DHAVE_QT4 $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(MOC4_CPPFLAGS) QArcballWidget.h 
endif

if USE_QT5

QA5 = libQarcball5.la

libQarcball5_la_CXXFLAGS =  @QT_CFLAGS@ 

libQarcball5_la_SOURCES = moc_QArcballWidget5.cpp QArcballWidget.cpp 

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
	rm moc_QArcballWidget4.cpp
	rm moc_QArcballWidget5.cpp
