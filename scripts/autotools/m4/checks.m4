# Function to check for SDL2
AC_DEFUN([CheckSDL2], [
    if test x$SDL2_FRAMEWORK != x; then
        SDL_FW_DIR=`dirname $SDL2_FRAMEWORK`
        SDL_FW_NAME=`basename $SDL2_FRAMEWORK .framework`

        SDL_CFLAGS="-I$SDL2_FRAMEWORK/Headers"
        SDL_LIBS="-F$SDL_FW_DIR -Wl,-framework,$SDL_FW_NAME"
    fi
    AM_PATH_SDL2(2.0.0, :, AC_MSG_ERROR([*** Error: Could not find SDL2]))
    CFLAGS="$CFLAGS $SDL_CFLAGS"
    LIBS="$LIBS $SDL_LIBS"
])

AC_DEFUN([CheckSDL2_ttf], [
    AC_MSG_CHECKING(for SDL2_ttf)
    if test x$SDL2_TTF_FRAMEWORK != x; then
        TTF_FW_DIR=`dirname $SDL2_TTF_FRAMEWORK`
        TTF_FW_NAME=`basename $SDL2_TTF_FRAMEWORK .framework`

        TTF_CFLAGS="-I$SDL2_TTF_FRAMEWORK/Headers"
        TTF_LIBS="-F$TTF_FW_DIR -Wl,-framework,$TTF_FW_NAME"
    fi
    AC_CHECK_SDL2_TTF(:, AC_MSG_ERROR([*** Error: Could not find SDL2_ttf]))
    CFLAGS="$CFLAGS $TTF_CFLAGS"
    LIBS="$LIBS $TTF_LIBS"
    AC_MSG_RESULT($have_ttf)
])

AC_DEFUN([CheckFileSystemBackends], [
    case "$host" in
        *windows* | *win32* | *mingw* | *msys*)
            filesystem_windows=yes
            CFLAGS="$CFLAGS -DFILESYSTEM_WINDOWS"
        ;;
        *)
            filesystem_dirent=yes
            CFLAGS="$CFLAGS -DFILESYSTEM_DIRENT"
        ;;
    esac
])

AC_DEFUN([CheckFileDialogBackends], [
    case "$host" in
        *windows* | *win32* | *mingw* | *msys*)
            LIBS="$LIBS -mwindows"
            CFLAGS="$CFLAGS -DFILEDIALOG_WINDOWS"
            filedialog_windows=yes
        ;;
        *darwin*|*macosx*|*apple*)
            LIBS="$LIBS -Wl,-framework,Cocoa -lobjc"
            CFLAGS="$CFLAGS -DFILEDIALOG_COCOA -fpascal-strings"
            OBJCFLAGS="$CFLAGS"
            filedialog_cocoa=yes
        ;;
        *)
            AC_CHECK_GTK(have_gtk=yes, have_gtk=no)
            if test x$have_gtk = xyes; then
                CFLAGS="$CFLAGS $GTK_CFLAGS -DFILEDIALOG_GTK"
                LIBS="$LIBS $GTK_LIBS"
                filedialog_gtk=yes
            fi
        ;;
    esac
])

AC_DEFUN([CheckSDLU], [
    if test x$SDLU_FRAMEWORK != x; then
        SDLU_FW_DIR=`dirname $SDLU_FRAMEWORK`
        SDLU_FW_NAME=`basename $SDLU_FRAMEWORK .framework`

        SDLU_CFLAGS="-I$SDLU_FRAMEWORK/Headers"
        SDLU_LIBS="-F$SDLU_FW_DIR -Wl,-framework,$SDLU_FW_NAME"
    fi
    AM_PATH_SDLU([2.1], :, AC_MSG_ERROR([*** Error: Could not find SDLU]))
    CFLAGS="$CFLAGS $SDLU_CFLAGS"
    LIBS="$LIBS $SDLU_LIBS"
])

AC_DEFUN([CheckVisibilityHidden], [
	AC_MSG_CHECKING(for -fvisibility=hidden)
	ac_save_CFLAGS="$CFLAGS"
	CFLAGS="$CFLAGS -fvisibility=hidden"
	have_visibility=no
	AC_COMPILE_IFELSE([AC_LANG_PROGRAM([],[])], have_visibility=yes,)
	CFLAGS="$ac_save_CFLAGS"
	if test "x$have_visibility" = xyes; then
		CFLAGS="$CFLAGS -fvisibility=hidden"
	fi

	AC_MSG_RESULT($have_visibility)
])
		
