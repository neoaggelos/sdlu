# Configure paths for SDLU
# Copy of sdl2.m4, modified for SDLU

# serial 1

dnl AM_PATH_SDLU([MINIMUM-VERSION, [ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND]]])
dnl Test for SDLU, and define SDLU_CFLAGS and SDLU_LIBS
dnl
AC_DEFUN([AM_PATH_SDLU],
[dnl 
dnl Get the cflags and libraries from the sdlu-config script
dnl
AC_ARG_WITH(sdlu-prefix,[  --with-sdlu-prefix=PFX   Prefix where SDLU is installed (optional)],
            sdlu_prefix="$withval", sdlu_prefix="")
AC_ARG_WITH(sdlu-exec-prefix,[  --with-sdlu-exec-prefix=PFX Exec prefix where SDLU is installed (optional)],
            sdlu_exec_prefix="$withval", sdlu_exec_prefix="")
AC_ARG_ENABLE(sdlutest, [  --disable-sdlutest       Do not try to compile and run a test SDLU program],
		    , enable_sdlutest=yes)

  min_sdlu_version=ifelse([$1], ,2.0.0,$1)

  if test "x$sdlu_prefix$sdlu_exec_prefix" = x ; then
    PKG_CHECK_MODULES([SDLU], [sdlu >= $min_sdl_version],
           [sdlu_pc=yes],
           [sdlu_pc=no])
  else
    sdlu_pc=no
    if test x$sdlu_exec_prefix != x ; then
      sdlu_config_args="$sdlu_config_args --exec-prefix=$sdlu_exec_prefix"
      if test x${SDLU_CONFIG+set} != xset ; then
        SDLU_CONFIG=$sdlu_exec_prefix/bin/sdlu-config
      fi
    fi
    if test x$sdlu_prefix != x ; then
      sdlu_config_args="$sdlu_config_args --prefix=$sdlu_prefix"
      if test x${SDLU_CONFIG+set} != xset ; then
        SDLU_CONFIG=$sdlu_prefix/bin/sdlu-config
      fi
    fi
  fi

  if test "x$sdlu_pc" = xyes ; then
    no_sdlu=""
    SDLU_CONFIG="pkg-config sdlu"
  else
    as_save_PATH="$PATH"
    if test "x$prefix" != xNONE && test "$cross_compiling" != yes; then
      PATH="$prefix/bin:$prefix/usr/bin:$PATH"
    fi
    AC_PATH_PROG(SDLU_CONFIG, sdlu-config, no, [$PATH])
    PATH="$as_save_PATH"
    AC_MSG_CHECKING(for SDLU - version >= $min_sdlu_version)
    no_sdlu=""

    if test "$SDLU_CONFIG" = "no" ; then
      no_sdlu=yes
    else
      SDLU_CFLAGS=`$SDLU_CONFIG $sdlu_config_args --cflags`
      SDLU_LIBS=`$SDLU_CONFIG $sdlu_config_args --libs`

      sdlu_major_version=`$SDLU_CONFIG $sdlu_config_args --version | \
             sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\1/'`
      sdlu_minor_version=`$SDLU_CONFIG $sdlu_config_args --version | \
             sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\2/'`
      sdlu_micro_version=`$SDLU_CONFIG $sdlu_config_args --version | \
             sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\3/'`
      if test "x$enable_sdlutest" = "xyes" ; then
        ac_save_CFLAGS="$CFLAGS"
        ac_save_CXXFLAGS="$CXXFLAGS"
        ac_save_LIBS="$LIBS"
        CFLAGS="$CFLAGS $SDLU_CFLAGS"
        CXXFLAGS="$CXXFLAGS $SDLU_CFLAGS"
        LIBS="$LIBS $SDLU_LIBS"
dnl
dnl Now check if the installed SDLU is sufficiently new. (Also sanity
dnl checks the results of sdlu-config to some extent)
dnl
      rm -f conf.sdlutest
      AC_TRY_RUN([
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SDLU.h"

char*
my_strdup (char *str)
{
  char *new_str;
  
  if (str)
    {
      new_str = (char *)malloc ((strlen (str) + 1) * sizeof(char));
      strcpy (new_str, str);
    }
  else
    new_str = NULL;
  
  return new_str;
}

int main (int argc, char *argv[])
{
  int major, minor, micro;
  char *tmp_version;

  /* This hangs on some systems (?)
  system ("touch conf.sdlutest");
  */
  { FILE *fp = fopen("conf.sdlutest", "a"); if ( fp ) fclose(fp); }

  /* HP/UX 9 (%@#!) writes to sscanf strings */
  tmp_version = my_strdup("$min_sdlu_version");
  if (sscanf(tmp_version, "%d.%d.%d", &major, &minor, &micro) != 3) {
     printf("%s, bad version string\n", "$min_sdlu_version");
     exit(1);
   }

   if (($sdlu_major_version > major) ||
      (($sdlu_major_version == major) && ($sdlu_minor_version > minor)) ||
      (($sdlu_major_version == major) && ($sdlu_minor_version == minor) && ($sdlu_micro_version >= micro)))
    {
      return 0;
    }
  else
    {
      printf("\n*** 'sdlu-config --version' returned %d.%d.%d, but the minimum version\n", $sdlu_major_version, $sdlu_minor_version, $sdlu_micro_version);
      printf("*** of SDLU required is %d.%d.%d. If sdlu-config is correct, then it is\n", major, minor, micro);
      printf("*** best to upgrade to the required version.\n");
      printf("*** If sdlu-config was wrong, set the environment variable SDLU_CONFIG\n");
      printf("*** to point to the correct copy of sdlu-config, and remove the file\n");
      printf("*** config.cache before re-running configure\n");
      return 1;
    }
}

],, no_sdlu=yes,[echo $ac_n "cross compiling; assumed OK... $ac_c"])
        CFLAGS="$ac_save_CFLAGS"
        CXXFLAGS="$ac_save_CXXFLAGS"
        LIBS="$ac_save_LIBS"
      fi
    fi
    if test "x$no_sdlu" = x ; then
      AC_MSG_RESULT(yes)
    else
      AC_MSG_RESULT(no)
    fi
  fi
  if test "x$no_sdlu" = x ; then
     ifelse([$2], , :, [$2])
  else
     if test "$SDLU_CONFIG" = "no" ; then
       echo "*** The sdlu-config script installed by SDLU could not be found"
       echo "*** If SDLU was installed in PREFIX, make sure PREFIX/bin is in"
       echo "*** your path, or set the SDLU_CONFIG environment variable to the"
       echo "*** full path to sdlu-config."
     else
       if test -f conf.sdlutest ; then
        :
       else
          echo "*** Could not run SDLU test program, checking why..."
          CFLAGS="$CFLAGS $SDLU_CFLAGS"
          CXXFLAGS="$CXXFLAGS $SDLU_CFLAGS"
          LIBS="$LIBS $SDLU_LIBS"
          AC_TRY_LINK([
#include <stdio.h>
#include "SDLU.h"

int main(int argc, char *argv[])
{ return 0; }
#undef  main
#define main K_and_R_C_main
],      [ return 0; ],
        [ echo "*** The test program compiled, but did not run. This usually means"
          echo "*** that the run-time linker is not finding SDLU or finding the wrong"
          echo "*** version of SDLU. If it is not finding SDLU, you'll need to set your"
          echo "*** LD_LIBRARY_PATH environment variable, or edit /etc/ld.so.conf to point"
          echo "*** to the installed location  Also, make sure you have run ldconfig if that"
          echo "*** is required on your system"
	  echo "***"
          echo "*** If you have an old version installed, it is best to remove it, although"
          echo "*** you may also be able to get things to work by modifying LD_LIBRARY_PATH"],
        [ echo "*** The test program failed to compile or link. See the file config.log for the"
          echo "*** exact error that occured. This usually means SDLU was incorrectly installed"
          echo "*** or that you have moved SDLU since it was installed. In the latter case, you"
          echo "*** may want to edit the sdlu-config script: $SDLU_CONFIG" ])
          CFLAGS="$ac_save_CFLAGS"
          CXXFLAGS="$ac_save_CXXFLAGS"
          LIBS="$ac_save_LIBS"
       fi
     fi
     SDLU_CFLAGS=""
     SDLU_LIBS=""
     ifelse([$3], , :, [$3])
  fi
  AC_SUBST(SDLU_CFLAGS)
  AC_SUBST(SDLU_LIBS)
  rm -f conf.sdlutest
])
