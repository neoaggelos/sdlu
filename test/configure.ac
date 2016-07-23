# Init
AC_INIT([SDLU_tests], [2.1], [neoaggelos@gmail.com])

# Set directories
AC_CONFIG_AUX_DIR([../scripts/autotools])
AC_CONFIG_MACRO_DIR([../scripts/autotools/m4])

# Figure out what system we are on
AC_CANONICAL_BUILD
AC_CANONICAL_HOST
AC_CANONICAL_TARGET

# Output files
AC_CONFIG_FILES([Makefile])

# Initialize automake
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AM_MAINTAINER_MODE([disable])
AM_SILENT_RULES([yes])

# Search for required tools
AC_PROG_CC
AC_PROG_CXX

# Check if g++ works
AC_MSG_CHECKING(if $CXX works)
cxx_compiler_works=no
AC_LANG_PUSH(C++)
AC_TRY_COMPILE([#include <iostream>],[ ], cxx_compiler_works=yes, CXX="" )
AC_LANG_POP
AC_MSG_RESULT($cxx_compiler_works)

# Find SDL2
if test x$SDL2_FRAMEWORK != x; then
    SDL_FW_DIR=`dirname $SDL2_FRAMEWORK`
    SDL_FW_NAME=`basename $SDL2_FRAMEWORK .framework`

    SDL_CFLAGS="-I$SDL2_FRAMEWORK/Headers"
    SDL_LIBS="-F$SDL_FW_DIR -Wl,-framework,$SDL_FW_NAME"
fi
AM_PATH_SDL2([2.0.0], :, AC_MSG_ERROR([*** Error: Could not find SDL2]))
CFLAGS="$CFLAGS $SDL_CFLAGS"
LIBS="$LIBS $SDL_LIBS"

case "$host" in
    *-*-mingw* | *-*-cygwin*) LIBS="$LIBS -lSDL2main" ;;
    *) ;;
esac

# Find SDL2_ttf
AC_MSG_CHECKING(for SDL2_ttf)
if test x$SDL2_TTF_FRAMEWORK != x; then
    TTF_FW_DIR=`dirname $SDL2_FRAMEWORK`
    TTF_FW_NAME=`basename $SDL2_TTF_FRAMEWORK .framework`

    TTF_CFLAGS="-I$SDL2_TTF_FRAMEWORK/Headers"
    TTF_LIBS="-F$TTF_FW_DIR -Wl,-framework,$TTF_FW_NAME"
fi
AC_CHECK_SDL2_TTF(:, AC_MSG_ERROR([*** Error: Could not find SDL2_ttf]))
CFLAGS="$CFLAGS $TTF_CFLAGS"
LIBS="$LIBS $TTF_LIBS"
AC_MSG_RESULT($have_ttf)

# Find SDLU
if test x$SDLU_FRAMEWORK != x; then
    SDLU_FW_DIR=`dirname $SDLU_FRAMEWORK`
    SDLU_FW_NAME=`basename $SDLU_FRAMEWORK .framework`

    SDLU_CFLAGS="-I$SDLU_FRAMEWORK/Headers"
    SDLU_LIBS="-F$SDLU_FW_DIR -Wl,-framework,$SDLU_FW_NAME"
fi
AM_PATH_SDLU([2.1], :, AC_MSG_ERROR([*** Error: Could not find SDLU]))
CFLAGS="$CFLAGS $SDLU_CFLAGS"
LIBS="$LIBS $SDLU_LIBS"

# System OpenGL libraries
AC_MSG_CHECKING(for OpenGL)
sys_opengl=""
case "$host" in
    *-*-mingw32*)
        sys_opengl="opengl32"
        sys_opengles="GLESv2"
        ;;
    *-*-darwin*)
        sys_opengl="-Wl,-framework,OpenGL"
        sys_opengles="-Wl,-framework,OpenGLES"
        ;;
    *)
        sys_opengl="GL"
        sys_opengles="GLESv2"
        ;;
esac

# Find OpenGL
have_opengl=no
AC_ARG_WITH(
    [opengl],
    AC_HELP_STRING([--with-opengl], [Choose OpenGL library]),
    [opengl_library=$withval],
    [opengl_library=$sys_opengl]
)

AC_TRY_COMPILE([ #include "SDL_opengl.h" ], [], have_opengl=yes )

if test x$have_opengl = xyes; then
    case "$opengl_library" in
        -Wl,* | -l*)    LIBS="$LIBS $opengl_library"    ;;
        *)              LIBS="$LIBS -l$opengl_library"  ;;
    esac
fi

AC_MSG_RESULT($have_opengl)

# Find OpenGL ES 2
AC_MSG_CHECKING(for OpenGL ES 2)
have_opengles=no
AC_ARG_WITH(
    [opengles2],
    AC_HELP_STRING([--with-opengles2], [Choose OpenGL ES 2 library]),
    [opengles_library=$withval],
    [opengles_library=$sys_opengles]
)

AC_TRY_COMPILE([ #include "SDL_opengles2.h" ], [], have_opengles=yes )

if test x$have_opengles = xyes; then
    case "$opengles_library" in
        -Wl,* | -l*)    LIBS="$LIBS $opengles_library"      ;;
        *)              LIBS="$LIBS -l$opengles_library"    ;;
    esac
fi

AC_MSG_RESULT($have_opengles)

# Also set CXXFLAGS
CXXFLAGS="$CXXFLAGS $CFLAGS"

# Conditionals
AM_CONDITIONAL([HAVE_OPENGL], [test x$have_opengl = xyes])
AM_CONDITIONAL([HAVE_OPENGLES2], [test x$have_opengles = xyes])
AM_CONDITIONAL([HAVE_CXX], [test x$cxx_compiler_works = xyes])

# Output files
AC_OUTPUT
