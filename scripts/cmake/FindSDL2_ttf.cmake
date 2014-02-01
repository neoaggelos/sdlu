SET(SDL2_SEARCH_PATHS
        ~/Library/Frameworks
        /Library/Frameworks
        /usr/local
        /usr
        /sw # Fink
        /opt/local # DarwinPorts
        /opt/csw # Blastwave
        /opt
)

FIND_PATH(SDL2_TTF_INCLUDE_DIR SDL_ttf.h
        HINTS
        $ENV{SDL2TTFDIR}
        PATH_SUFFIXES include/SDL2 include
        PATHS ${SDL2_SEARCH_PATHS}
)

FIND_LIBRARY(SDL2_TTF_LIBRARY
        NAMES SDL2_ttf
        HINTS
        $ENV{SDL2TTFDIR}
        PATH_SUFFIXES lib64 lib
        PATHS ${SDL2_SEARCH_PATHS}
        DOC "SDL2 ttf Library Path"
)

INCLUDE(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(SDL2_ttf REQUIRED_VARS SDL2_TTF_LIBRARY
    SDL2_TTF_INCLUDE_DIR)

IF(SDL2_TTF_LIBRARY AND SDL2_TTF_INCLUDE_DIR)
        SET(SDL2_TTF_FOUND "YES")
ENDIF(SDL2_TTF_LIBRARY AND SDL2_TTF_INCLUDE_DIR)
