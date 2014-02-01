# Try to find OpenGL ES 2
#
# This module defines the following:
# GLES2_INCLUDE_DIR -> Location of 'GLES2/gl2.h'
# GLES2_LIBRARY     -> The library to link to
# GLES2_FOUND       -> Whether we actually found GLES2

# You can set the environment variable $GLES2DIR, to specify
# the location of the OpenGL ES 2 headers and the libraries


######################################################################


# Basic paths
set(GLES2_SEARCH_PATHS
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local
    /usr
    /sw
    /opt/vc     # Raspberry Pi
    /opt/local
    /opt/csw
    /opt
)

# Find GLESv2
find_library(
    GLES2_LIBRARY_TEMP NAME GLESv2
    HINTS $ENV{GLES2DIR}
    PATH_SUFFIXES lib lib64
    PATHS ${GLES2_SEARCH_PATHS}
)

# Find GLES2/gl2.h
find_path(
    GLES2_INCLUDE_DIR GLES2/gl2.h
    HINTS $ENV{GLES2DIR}
    PATHS ${GLES2_SEARCH_DIRS}
)

# X11 is most likely required for Linux systems
if (NOT APPLE AND NOT WIN32)

    # Check if we have to also link to X11
    include(CheckCSourceCompiles)

    set(CMAKE_REQUIRED_INCLUDES ${CMAKE_REQUIRED_INCLUDES} ${GLES2_INCLUDE_DIR})
    check_c_source_compiles(
        "#include <GLES2/gl2.h>\nint main(int argc, char** argv) {}"
        NO_X11_NEEDED
    )

    # Add X11 flags
    if (NOT X11_FOUND AND (NOT NO_X11_NEEDED))
        find_package(X11 QUIET)
    endif()
    if (X11_FOUND)
        set(GLES2_LIBRARY ${GLES2_LIBRARY_TEMP} ${X11_LIBRARIES})
    else()
        set(GLES2_LIBRARY ${GLES2_LIBRARY_TEMP})
    endif()
else()
    set(GLES2_LIBRARY ${GLES2_LIBRARY_TEMP})
endif()

# Setup what is shown on CACHE (for GUIs) and what doesn't
set(GLES2_LIBRARY ${GLES2_LIBRARY} CACHE STRING "OpenGL ES 2 libraries")
mark_as_advanced(GLES2_LIBRARY_TEMP)


#####################################################################


include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(
    GLES2 REQUIRED_VARS GLES2_LIBRARY GLES2_INCLUDE_DIR
)

if (GLES2_LIBRARY AND GLES2_INCLUDE_DIR)
    set(GLES2_FOUND "YES")
endif()
