
AM_CPPFLAGS = -I${top_srcdir}/src/math

if USE_FLTK 

testfl = testfl1

testfl1_CXXFLAGS =  @FL_CXXFLAGS@ -I${top_srcdir}/src/FLui

testfl1_SOURCES = testFL.cpp

testfl1_LDFLAGS = ../src/FLui/libFLarcball.la @FL_LDFLAGS@ @LIB_XCURSOR@

testfl1_LDADD = 

testfl1ex = examplefl1

examplefl1_CXXFLAGS =  @FL_CXXFLAGS@ -I${top_srcdir}/src/FLui

examplefl1_SOURCES = exampleFL.cpp

examplefl1_LDFLAGS = ../src/FLui/libFLarcball.la @FL_LDFLAGS@ @LIB_XCURSOR@

examplefl1_LDADD = 

endif
if USE_FLTK2
testfltk = testfl2

testfl2_CXXFLAGS =  @FL2_CXXFLAGS@ -I${top_srcdir}/src/fltkui

testfl2_SOURCES = testFL2.cpp

testfl2_LDFLAGS = ../src/fltkui/libfltkarcball.la @FL2_LDFLAGS@

testfl2_LDADD = 


endif
if USE_GTK

testmm = testgtkmm

testgtkmm_CXXFLAGS =   @GTKGLEXTMM_CFLAGS@ -I${top_srcdir}/src/gtkmmui @CXX11REQ@

testgtkmm_SOURCES = testGtkmm.cxx

testgtkmm_LDFLAGS =  ../src/gtkmmui/libgtkmmarcball.la @GTKGLEXTMM_LIBS@ 

testgtkmm_LDADD =

exmm = examplegtkmm

examplegtkmm_CXXFLAGS =   @GTKGLEXTMM_CFLAGS@ -I${top_srcdir}/src/gtkmmui @CXX11REQ@

examplegtkmm_SOURCES = exampleGtkmm.cxx

examplegtkmm_LDFLAGS =  ../src/gtkmmui/libgtkmmarcball.la @GTKGLEXTMM_LIBS@

examplegtkmm_LDADD = 

endif

testmath = testmath

testmath_CXXFLAGS = 

testmath_SOURCES = testmath.cpp

testmath_LDFLAGS = 

testmath_LDADD = 


if USE_QT5
testqt = testQt exampleQt

testQt_CXXFLAGS =  @QT_CFLAGS@ -I${top_srcdir}/src/qt

testQt_SOURCES = testQt.cpp

testQt_LDFLAGS = ../src/qt/libQarcball5.la 

testQt_LDADD =

exampleQt_CXXFLAGS =  @QT_CFLAGS@ -I${top_srcdir}/src/qt

exampleQt_SOURCES = exampleQt.cpp moc_exampleQt.cpp 

exampleQt_LDFLAGS = ../src/qt/libQarcball5.la 

moc_exampleQt.cpp:exampleQt.h
	@MOC@ @MOC_ADD_OPT@ -o$@ $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(MOC_CPPFLAGS) exampleQt.h

endif
 

noinst_PROGRAMS= ${testmath} ${testfl} ${testfl1ex} ${testfltk} ${testmm} ${exmm} ${testqt}  ${testqt4}

noinst_HEADERS= draw_cube.h exampleQt.h

EXTRA_DIST=$(noinst_DATA) CMakeLists.txt

all: ${test_PROGRAMS}
