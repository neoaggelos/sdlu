# Configure paths for SDL2_ttf

# serial 1

dnl AC_CHECK_SDL2_TTF([ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND]]
dnl Check the system for SDL2_ttf and define TTF_CFLAGS and TTF_LIBS
dnl
AC_DEFUN([AC_CHECK_SDL2_TTF],
[
AC_ARG_WITH([sdl-ttf-pc],
    AC_HELP_STRING([--with-sdl-ttf-pc=FILE], [Path to SDL2_ttf.pc]),
    sdl2_ttf_pc="$withval", sdl2_ttf_pc=SDL2_ttf
)

AC_ARG_VAR([TTF_CFLAGS], [C compiler flags for SDL2_ttf, overriding pkg-config])
AC_ARG_VAR([TTF_LIBS], [linker flags for SDL2_ttf, overriding pkg-config])

have_ttf=no
if test "x$TTF_CFLAGS$TTF_LIBS" = x; then
    PKG_CHECK_EXISTS([$sdl2_ttf_pc], have_ttf=yes)

    if test x$have_ttf = xyes; then
        TTF_CFLAGS=`pkg-config --cflags $sdl2_ttf_pc`
        TTF_LIBS=`pkg-config --libs $sdl2_ttf_pc`
        ifelse([$1], , :, [$1])
    else
        ac_save_LIBS="$LIBS"
        LIBS="$LIBS -lSDL2_ttf"
        AC_TRY_COMPILE([#include "SDL_ttf.h"],[TTF_Init()],have_ttf=yes)
        if test x$have_ttf = xyes; then
            TTF_LIBS="-lSDL2_ttf"
            TTF_CFLAGS=""
            ifelse([$1], , :, [$1])
        else
            LIBS="$ac_save_LIBS"
        fi

        if test x$have_ttf = xno; then
            ifelse([$2], , :, [$2])
        fi
    fi
else
    ifelse([$1], , :, [$1])
fi

])
