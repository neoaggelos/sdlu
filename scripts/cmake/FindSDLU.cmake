# Locate SDLU library
# This module defines
# SDLU_LIBRARY, the name of the library to link against
# SDLU_FOUND, if false, do not link to SDLU
# SDLU_INCLUDE_DIR, where to find SDLU.h
#
# $SDLUDIR is an environment variable that would correspond to the:
#   # ./configure --prefix=$SDLUDIR
# used when building the library
#
# -- Aggelos Kolaitis

set(SDLU_SEARCH_PATHS
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local
    /usr
    /sw
    /opt/local
    /opt/csw
    /opt
)

find_path(
    SDLU_INCLUDE_DIR SDLU.h
    HINTS $ENV{SDLUDIR} $ENV{SDL2DIR}
    PATH_SUFFIXES include/SDLU include/SDL2 include
    PATHS ${SDLU_SEARCH_PATHS}
)

find_library(SDLU_LIBRARY
    NAMES SDLU
    HINTS $ENV{SDLUDIR} $ENV{SDL2DIR}
    PATH_SUFFIXES lib64 lib
    PATHS ${SDLU_SEARCH_PATHS}
    DOC "SDLU library path"
)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(
    SDLU REQUIRED_VARS SDLU_LIBRARY SDLU_INCLUDE_DIR
)

if(SDLU_LIBRARY AND SDLU_INCLUDE_DIR)
    set(SDLU_FOUND "YES")
endif(SDLU_LIBRARY AND SDLU_INCLUDE_DIR)


