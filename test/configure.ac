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

# Find SDL libraries
CheckSDL2
CheckSDLU

# System OpenGL libraries
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
AC_MSG_CHECKING(for OpenGL)
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

# Conditionals
AM_CONDITIONAL([HAVE_OPENGL], [test x$have_opengl = xyes])
AM_CONDITIONAL([HAVE_OPENGLES2], [test x$have_opengles = xyes])

# Output files
AC_OUTPUT
