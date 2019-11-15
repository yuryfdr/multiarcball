SUBDIRS=. src test 

if USE_FLTK
flpc=multiarcball-FL.pc
endif
if USE_FLTK2
fl2pc=multiarcball-fltk2.pc
endif
if USE_GTK
mmpc=multiarcballmm.pc
endif
if USE_QT5 #pkg-config file only for qt5
qtpc=multiarcballQt.pc
endif


pkgconfigdir= $(libdir)/pkgconfig
pkgconfig_DATA= multiarcball.pc $(flpc) $(fl2pc) $(mmpc) $(qtpc)

noinst_DATA=TODO Doxyfile

multiarcball_docdir = $(docdir)

multiarcball_doc_DATA= doc/eventsmap.html \
		doc/fivepercent.png

EXTRA_DIST = $(multiarcball_doc_DATA) $(noinst_DATA) CMakeLists.txt
