# Configure paths for Gtk+ 3

# serial 1

dnl AC_CHECK_GTK([ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND]])
dnl Check the system for GTK+ 3 and define GTK_CFLAGS and GTK_LIBS
dnl
AC_DEFUN([AC_CHECK_GTK],
[
AC_MSG_CHECKING(for gtk+)

have_gtk=no
PKG_CHECK_EXISTS(gtk+-3.0, have_gtk=yes)
if test x$have_gtk = xyes; then
    GTK_CFLAGS=`pkg-config --cflags gtk+-3.0`
    GTK_LIBS=`pkg-config --libs gtk+-3.0`
    ifelse([$1], , :, [$1])
else
    PKG_CHECK_EXISTS(gtk+-2.0, have_gtk=yes)
    if test x$have_gtk = xyes; then
      GTK_CFLAGS=`pkg-config --cflags gtk+-2.0`
      GTK_LIBS=`pkg-config --libs gtk+-2.0`
      ifelse([$1], , :, [$1])
    else
      ifelse([$2], , :, [$2])
    fi
fi

AC_MSG_RESULT($have_gtk)
])
