# Init
AC_INIT([SDLU],[2.1],[neoaggelos@gmail.com])

# Project version
header="$srcdir/include/SDLU.h"
major=`grep "define SDLU_VERSION_MAJOR" $header | sed "s,.*\([[0-9]]\).*,\1,"`
minor=`grep "define SDLU_VERSION_MINOR" $header | sed "s,.*\([[0-9]]\).*,\1,"`

# Set directories
AC_CONFIG_AUX_DIR([scripts/autotools])
AC_CONFIG_MACRO_DIR([scripts/autotools/m4])

# Output files
AC_CONFIG_FILES([Makefile sdlu.pc sdlu-config include/SDLU_config.h])

# Initialize automake
AM_INIT_AUTOMAKE([-Wall -Werror subdir-objects foreign])
AM_MAINTAINER_MODE([disable])
AM_SILENT_RULES([yes])

# Search for required tools
AC_PROG_CC
AC_PROG_CXX
AC_PROG_OBJC
AM_PROG_AR

# Initialize libtool
LT_INIT

# Basic flags
CFLAGS="$CFLAGS -Wall -Wextra -Iinclude -I$srcdir/include -I$srcdir/src/common"

# Extra flags for static linking (substituted in sdlu-config and sdlu.pc)
EXTRA_FLAGS=""

# Raspberry Pi special flags
case "$host" in
    arm-raspberry-linux-gnueabihf) CFLAGS="$CFLAGS -Wno-psabi" ;;
    *) ;;
esac

# Check if we are building the static library
# This is required for 'sdlu-config --static-libs'
if test x$enable_static = xyes; then
    STATIC=''
else
    STATIC='#'
fi

# Debug
AC_MSG_CHECKING(whether to build with debugging information)
debug=no
AC_ARG_ENABLE(
    [debug],
    AS_HELP_STRING([--enable-debug],[Build library with debug info]),
    [debug=${enableval}]
)
if test x$debug = xyes; then
    CFLAGS="$CFLAGS -D_DEBUG -g"
fi
AC_MSG_RESULT($debug)

# Function to check for SDL2
CheckSDL2() {
    if test x$SDL2_FRAMEWORK != x; then
        SDL_CFLAGS="-I$SDL2_FRAMEWORK/Headers"
        SDL_LIBS="$SDL2_FRAMEWORK/SDL2"
    fi
    AM_PATH_SDL2(2.0.0, :, AC_MSG_ERROR([*** Error: Could not find SDL2]))
    CFLAGS="$CFLAGS $SDL_CFLAGS"
    LIBS="$LIBS $SDL_LIBS"
}

# Function to check for SDL2_ttf
CheckSDL2_ttf() {
    AC_MSG_CHECKING(for SDL2_ttf)
    if test x$SDL2_TTF_FRAMEWORK != x; then
        TTF_CFLAGS="-I$SDL2_TTF_FRAMEWORK/Headers"
        TTF_LIBS="$SDL2_TTF_FRAMEWORK/SDL2_ttf"
    fi
    AC_CHECK_SDL2_TTF(:, AC_MSG_ERROR([*** Error: Could not find SDL2_ttf]))
    CFLAGS="$CFLAGS $TTF_CFLAGS"
    LIBS="$LIBS $TTF_LIBS"
    AC_MSG_RESULT($have_ttf)
}

# Function to check for a file dialog backend
CheckFileDialogBackends() {
    case "$host" in
        *windows* | *win32* | *mingw* | *msys*)
            LIBS="$LIBS -mwindows"
            CFLAGS="$CFLAGS -DFILEDIALOG_WIN32"
        ;;
        *darwin*|*macosx*|*apple*)
            LIBS="$LIBS -Wl,-framework,Cocoa -lobjc"
            CFLAGS="$CFLAGS -DFILEDIALOG_COCOA -fpascal-strings"
            filedialog_cocoa=yes
        ;;
        *)
            AC_CHECK_GTK(have_gtk=yes, have_gtk=no)
            if test x$have_gtk = xyes; then
                CFLAGS="$CFLAGS $GTK_CFLAGS -DFILEDIALOG_GTK"
                LIBS="$LIBS $GTK_LIBS"
            else
                CFLAGS="$CFLAGS -DFILEDIALOG_DUMMY"
            fi
        ;;
    esac
}

# Find libraries
case "$host" in
    custom-apple-darwin) # this is iosbuild.sh
        CFLAGS="$CFLAGS -I$SDL2_INCLUDE_DIR -I$SDL2_TTF_INCLUDE_DIR"
        CFLAGS="$CFLAGS -DFILEDIALOG_DUMMY"
        ;;
    arm-raspberry-linux-gnueabihf) # this is rpibuild.sh
        LIBS="$LIBS $SDL2_PI_LIBRARY $SDL2_TTF_PI_LIBRARY"
        CFLAGS="$CFLAGS -I$SDL2_INCLUDE_DIR -I$SDL2_TTF_INCLUDE_DIR"
        CFLAGS="$CFLAGS -DFILEDIALOG_DUMMY"
        ;;
    *)
        CheckSDL2
        CheckSDL2_ttf
        CheckFileDialogBackends
        ;;
esac

# cxx interface
AC_MSG_CHECKING(whether to build the cxx interface)
build_cxx=no
AC_ARG_ENABLE(
    [cxx],
    AS_HELP_STRING([--enable-cxx],[Build the cxx interface]),
    [build_cxx=${enableval}]
)

if test x${build_cxx} = xyes; then
    DEFINE_SDLU_CXX="#define SDLU_CXX 1"
else
    DEFINE_SDLU_CXX="/* #undef SDLU_CXX */"
fi
AM_CONDITIONAL([CXX], [test x${build_cxx} = xyes])
AC_MSG_RESULT($build_cxx)

# set the include directory
includedir="$includedir/SDL2"

# make sure sdlu-config can be executed
AC_CONFIG_COMMANDS([sdlu_config], [chmod a+x sdlu-config])

# add objective-c sources if needed
AM_CONDITIONAL([FILEDIALOG_COCOA], [test x$filedialog_cocoa = xyes])

# also set CXXFLAGS
CXXFLAGS="$CXXFLAGS $CFLAGS"

# substitutions for the config header
AC_SUBST([DEFINE_SDLU_CXX])

# substitutions for sdlu.pc and sdlu-config
AC_SUBST([SDL_LIBS])
AC_SUBST([TTF_LIBS])
AC_SUBST([STATIC])
AC_SUBST([EXTRA_FLAGS])
AC_SUBST([major])
AC_SUBST([minor])

# Output files
AC_OUTPUT
