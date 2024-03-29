#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)
AC_INIT([multiarcball],0.4.0,[yfdrnchk at mail dot ru])
AC_CONFIG_SRCDIR([src/FLui/FlGlArcballWindow.h])
AM_INIT_AUTOMAKE
AC_CONFIG_HEADER([config.h])

# from libtool info
# 3. If the library source code has changed at all since the last
#     update, then increment REVISION (`C:R:A' becomes `C:r+1:A').
#  4. If any interfaces have been added, removed, or changed since the
#     last update, increment CURRENT, and set REVISION to 0.
#  5. If any interfaces have been added since the last public release,
#     then increment AGE.
#  6. If any interfaces have been removed since the last public release,
#     then set AGE to 0.

MA_CURRENT=4
MA_REVISION=2
MA_AGE=0

MA_LT_VERSION="$MA_CURRENT:$MA_REVISION:$MA_AGE"
#MA_LT_VERSION="2:0:1"

AC_SUBST(MA_LT_VERSION)

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

AX_CXX_COMPILE_STDCXX_11
AC_LANG_CPLUSPLUS
AC_LANG_COMPILER_REQUIRE

AC_PROG_LIBTOOL

HAVE_XCURSOR=""
LIB_XCURSOR=""
LIB_OPEGL_32=""
LTNOUNDEF=""
# Checks for libraries
case "$host" in
    *-*-mingw* | *-*-cygwin*)
    LTNOUNDEF='-no-undefined'
    AC_MSG_CHECKING([for glVertex3d in -lopengl32])
    have_opengl32=no
    LIBS="-lopengl32"
    AC_TRY_LINK([#include <windows.h>
                 #include <GL/gl.h>], 
                [glVertex3d(0.0, 0.0, 0.0);], 
                [GL_LIBS="-lopengl32"
                have_opengl32=yes])
    AC_MSG_RESULT([$have_opengl32])
    if test "x$have_opengl32" = "xno" ; then
       AC_MSG_ERROR([Cannot find GL library])
    fi
    AC_MSG_CHECKING([for gluNewQuadric in -lglu32])
       have_glu32=no
       LIBS="-lglu32 $LIBS"
    AC_TRY_LINK([#include <windows.h>
               #include <GL/gl.h>
               #include <GL/glu.h>], 
              [gluNewQuadric();], 
              [GL_LIBS="-lglu32 $GL_LIBS"
               have_glu32=yes])
    AC_MSG_RESULT([$have_glu32])
    if test "x$have_glu32" = "xno" ; then
      AC_MSG_ERROR([Cannot find GLU library])
    fi
    LIB_OPENGL_32=" -lglu32 -lopengl32"
        ;;
    *)
    LIB_OPENGL_32=" -lGLU -lGL"
esac
AC_SUBST(LTNOUNDEF)
AC_SUBST(LIB_OPENGL_32)

NEWCURSORS=""

#fltk
AC_ARG_ENABLE(fltk,[  --enable-fltk   build fltk-1.x.x GUI part [default=yes] ])
    if test "x$enable_fltk" != xno; then
       AC_PATH_PROG(FLTK,fltk-config)        
    fi
    if test "x$FLTK" != x; then
      HAVE_FLTK=1
      AC_SUBST([FL_CXXFLAGS],["`$FLTK --cxxflags` $CXXFLAGS"])
      AC_SUBST([FL_LDFLAGS],["`$FLTK --use-gl --ldflags` $LDFLAGS"])
      AC_SUBST([FL_VER],["`$FLTK --version`"])
      FL_MINOR=`expr "$FL_VER" : '..\(.\)'`
      FL_PATCH=`expr "$FL_VER" : '....\(.\)'`
      if test ${FL_MINOR} -ge 3 -a ${FL_PATCH} -ge 3 ;then 
        NEWCURSORS=1
      fi
      SLIBS=$LIBS
    case "$host" in
      *-*-mingw* | *-*-cygwin*)
      # don't use fltk lib list
      AC_SUBST([FL_LDFLAGS],[" -lfltk_gl -lfltk -lgdi32"])
      ;;
      *)
	if test x"$NEWCURSORS" != x1 ; then
        AC_CHECK_HEADER(
	  X11/Xcursor/Xcursor.h,
	  AC_CHECK_LIB(Xcursor, XcursorImageLoadCursor,
	  HAVE_XCURSOR=1
	  LIB_XCURSOR="-lXcursor",
	  AC_MSG_ERROR("XCursor library not found"))
	)
	fi
      AC_SUBST([FL_LDFLAGS],["`$FLTK --use-gl --ldflags` $LDFLAGS"])
	;;
      esac

      AC_SUBST([FL_CXXFLAGS],["`$FLTK --cxxflags` $CXXFLAGS"])
      AC_SUBST(HAVE_XCURSOR)
      AC_SUBST(LIB_XCURSOR)
      LIBS=$SLIBS
    #
    else
      AC_MSG_WARN("can not find fltk-config in ${with_fltk_dir}/bin $PATH")
    fi

AC_SUBST(HAVE_FLTK)

AM_CONDITIONAL([USE_OLDCURSORS],[test "x$NEWCURSORS" != x1])

AM_CONDITIONAL([USE_FLTK],[test "x$HAVE_FLTK" == x1])


#fltk2    
HAVE_FLTK2=""
AC_ARG_ENABLE(fltk2,[  --enable-fltk2   build fltk-2.x GUI part [default=no] ])

if test "x$enable_fltk2" == xyes; then
    AC_PATH_PROG(FLTK2,fltk2-config)        
    if test "x$FLTK2" != x; then
      HAVE_FLTK2=1
      AC_SUBST([FL2_CXXFLAGS],["`$FLTK2 --cxxflags` $CXXFLAGS"])
      AC_SUBST([FL2_LDFLAGS],["`$FLTK2 --use-gl --ldflags` $LDFLAGS"])
    else
      AC_MSG_WARN("can not find fltk2-config in ${with_fltk_dir}/bin $PATH")
    fi
fi

AC_SUBST(HAVE_FLTK2)
AM_CONDITIONAL([USE_FLTK2],[test "x$HAVE_FLTK2" == x1])

# modify pkg-config path
AC_ARG_ENABLE(gtk,[  --enable-gtk   build gtkmm GUI part [default=yes] ])

HAVE_GTKMM=0
CXX11REQ=""
    
if test "x$enable_gtk" != xno; then    
    AC_ARG_WITH(pkg-config-path, 
       AC_HELP_STRING([--with-pkg-config-path],[colon-separated list of pkg-config(1) dirs]),
       [export PKG_CONFIG_PATH=${withval}])


    PKG_CHECK_MODULES(GTKGLEXTMM, [gtkglextmm-1.2 >= 1.2],
      [HAVE_GTKMM=1
      AC_SUBST(HAVE_GTKMM)],
      [AC_MSG_WARN("can not find gtkglextmm")]
    )
    PKG_CHECK_MODULES(PANGOFT2, [pangoft2],
      [HAVE_PANGOFT2=1],
      [AC_MSG_WARN("can not find pangoft2")]
    )
    PKG_CHECK_MODULES(SIGC, [sigc++-2.0 >= 2.6],
	[CXX11REQ="-std=c++11"
	AC_SUBST(CXX11REQ)],
	[ PKG_CHECK_MODULES(SIGC, [sigc++-2.0 >= 2.2]) ]
    )

fi

AM_CONDITIONAL([USE_GTK],[test "x$HAVE_GTKMM" == x1])

AC_ARG_ENABLE(qt5,[  --enable-qt5   build qt5 GUI part [default=yes] ])
AC_ARG_WITH(qt5-dir,[  --with-qt5-dir - path to Qt binary dir ])

HAVE_QT=0
if test x"$enable_qt5" != xno ; then
    QT_REQ=5
    MOC_ADD_OPT=""
    QT5_MODULE="Qt5OpenGL"
    PKG_CHECK_MODULES(QT, [$QT5_MODULE], [HAVE_QT=1], [AC_MSG_WARN([Qt5widgets libraries not found.])])
    if test x"$HAVE_QT" != x0 ; then
	HAVE_QT=`pkg-config --modversion $QT5_MODULE`
	QT_CFLAGS+=" -fPIC "
	AC_SUBST(QT5_MODULE)
	AC_MSG_NOTICE([find Qt $HAVE_QT now search for suitable moc])
	if test "x$with_qt_dir" != x ;then
	    QT_DIR=$with_qt_dir
	fi
        AC_PATH_PROG(MOC, [moc] ,[], [$QT_DIR:$PATH])
        if test -z "$MOC" ; then #|| test -z "$UIC" || test -z "$RCC"; then
		AC_MSG_ERROR([Qt utility programs moc are required.])
        fi
	MOC_VER="$($MOC -v 2>&1)"
	AC_MSG_NOTICE($MOC_VER $HAVE_QT)
	case $MOC_VER in
	    *$HAVE_QT*)
	    AC_MSG_NOTICE([moc found $MOC_VER])
	;;
	*)
	    MOC_VER="$($MOC --qt$QT_REQ -v 2>&1)"
	    case $MOC_VER in
	    *$HAVE_QT*)
	    MOC_ADD_OPT=" --qt$QT_REQ "
	    ;;
	    *)
	    AC_MSG_ERROR([ $MOC version differ from Qt version $HAVE_QT try use --with-qt-dir])
	    ;;
	    esac
	;;
	esac
	AC_SUBST(MOC_ADD_OPT)
    fi
fi

AC_SUBST(HAVE_QT)
AM_CONDITIONAL([USE_QT5],[test x"$HAVE_QT" != x0])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for library functions.
AC_HEADER_STDC
AC_FUNC_VPRINTF
AC_CHECK_FUNCS([memset sqrt])

AC_CONFIG_FILES([Makefile
                 src/FLui/Makefile
                 src/Makefile
                 src/fltkui/Makefile
                 src/gtkmmui/Makefile
                 src/math/Makefile
                 src/qt/Makefile
		 test/Makefile
		 multiarcball.pc
		 multiarcball-FL.pc
		 multiarcball-fltk2.pc
		 multiarcballmm.pc
		 multiarcballQt.pc
		 ])
AC_OUTPUT
