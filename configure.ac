# Init
AC_INIT([SDLU],[2.1.1],[neoaggelos@gmail.com])

# Project version
header="$srcdir/include/SDLU.h"
major=`grep "define SDLU_VERSION_MAJOR" $header | sed "s,.*\([[0-9]]\).*,\1,"`
minor=`grep "define SDLU_VERSION_MINOR" $header | sed "s,.*\([[0-9]]\).*,\1,"`

# Set directories
AC_CONFIG_AUX_DIR([scripts/autotools])
AC_CONFIG_MACRO_DIR([scripts/autotools/m4])

# Output files
AC_CONFIG_FILES([Makefile sdlu.pc sdlu-config])

# Initialize automake
AM_INIT_AUTOMAKE([-Wall -Werror subdir-objects foreign])
AM_MAINTAINER_MODE([disable])
AM_SILENT_RULES([yes])

# Search for required tools
AC_PROG_CC
AC_PROG_OBJC
AM_PROG_AR

# Initialize libtool
LT_INIT

# Basic flags
CFLAGS="$CFLAGS -Wall -Wextra -fvisibility=hidden"

# System specific
case "$host" in
    arm-raspberry-linux-gnueabihf) CFLAGS="$CFLAGS -Wno-psabi" ;;
    *macosx* | *apple* | *darwin*) macosx_system="yes" ;;
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

# Find libraries
CheckSDL2
CheckSDL2_ttf
CheckFileDialogBackends
CheckFileSystemBackends

# Check -fvisibility=hidden
CheckVisibilityHidden

# set the include directory
includedir="$includedir/SDL2"

# make sure sdlu-config can be executed
AC_CONFIG_COMMANDS([sdlu_config], [chmod a+x sdlu-config])

# file dialog backend
AM_CONDITIONAL([FILEDIALOG_COCOA], [test x$filedialog_cocoa = xyes])
AM_CONDITIONAL([FILEDIALOG_WINDOWS], [test x$filedialog_windows = xyes])
AM_CONDITIONAL([FILEDIALOG_GTK], [test x$filedialog_gtk = xyes])

# file system backend
AM_CONDITIONAL([FILESYSTEM_WINDOWS], [test x$filesystem_windows = xyes])
AM_CONDITIONAL([FILESYSTEM_DIRENT], [test x$filesystem_dirent = xyes])

# mac os x system
AM_CONDITIONAL([MACOSX_SYSTEM], [test x$macosx_system = xyes])

# also set Objective C flags
OBJCFLAGS="$OBJCFLAGS $CFLAGS"

# substitutions for sdlu.pc and sdlu-config
AC_SUBST([SDL_LIBS])
AC_SUBST([SDL_CFLAGS])
AC_SUBST([TTF_LIBS])
AC_SUBST([TTF_CFLAGS])
AC_SUBST([STATIC])
AC_SUBST([major])
AC_SUBST([minor])

# Output files
AC_OUTPUT
