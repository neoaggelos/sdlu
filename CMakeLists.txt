# SDLU CMakeLists.txt
cmake_minimum_required(VERSION 2.8)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)
set(CMAKE_MACOSX_RPATH 1)

# Define the project
project(SDLU)

# Project version
file(READ "${CMAKE_SOURCE_DIR}/include/SDLU.h" VERSION)
string(REGEX REPLACE ".*SDLU_VERSION_MAJOR ([0-9]+).*" "\\1" major ${VERSION})
string(REGEX REPLACE ".*SDLU_VERSION_MINOR ([0-9]+).*" "\\1" minor ${VERSION})
set(VERSION "${major}.${minor}")

# Options
option(BUILD_CXX "Build the SDLU C++ interface" OFF)
option(BUILD_STATIC_LIBS "Build the static library" ON)
option(BUILD_SHARED_LIBS "Build the shared library" ON)
option(BUILD_FRAMEWORK "Build framework (Mac OS X)" OFF)

# Also find a C++ compiler if needed
if (BUILD_CXX)
  enable_language(CXX)
endif(BUILD_CXX)

# Load required modules
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/scripts/cmake")
include("${CMAKE_SOURCE_DIR}/scripts/cmake/macros.cmake")
include("${CMAKE_SOURCE_DIR}/scripts/cmake/FindSDL2.cmake")
include("${CMAKE_SOURCE_DIR}/scripts/cmake/FindSDL2_ttf.cmake")

# Standard include directories
include_directories("${CMAKE_SOURCE_DIR}/include")
include_directories("${CMAKE_SOURCE_DIR}/src/common")
include_directories("${CMAKE_BINARY_DIR}")

# Debug builds
if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
  add_definitions("-D_DEBUG")
  set(CMAKE_VERBOSE_MAKEFILE ON)
endif(${CMAKE_BUILD_TYPE} MATCHES "Debug")

# Find SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
set(LIBS ${LIBS} ${SDL2_LIBRARY})

# Find SDL2_ttf
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_TTF_INCLUDE_DIR})
set(LIBS ${LIBS} ${SDL2_TTF_LIBRARY})

# Find a backend for the file dialog API
CheckFileDialogBackend()

# These are for sdlu-config and sdlu.pc
set(SDL_CFLAGS "-I${SDL2_INCLUDE_DIR}")
set(TTF_CFLAGS "-I${SDL2_TTF_INCLUDE_DIR}")

# Basic sources
file(GLOB SOURCES
  ${EXTRA_SOURCES}
  ${CMAKE_SOURCE_DIR}/src/filedialog/*.c
  ${CMAKE_SOURCE_DIR}/src/render/*.c
  ${CMAKE_SOURCE_DIR}/src/common/*.c
  ${CMAKE_SOURCE_DIR}/src/sprite/*.c
  ${CMAKE_SOURCE_DIR}/src/turtle/*.c
  ${CMAKE_SOURCE_DIR}/src/text/*.c
  ${CMAKE_SOURCE_DIR}/src/gui/*.c
  ${CMAKE_SOURCE_DIR}/src/ini/*.c
  ${CMAKE_SOURCE_DIR}/src/gl/*.c
  ${CMAKE_SOURCE_DIR}/src/*.c
)

# Add cxx sources if needed
if (BUILD_CXX)
  file(GLOB CXX_SOURCES ${CMAKE_SOURCE_DIR}/src/cxx/*.cxx)
  set_source_files_properties(CXX_SOURCES PROPERTIES LANGUAGE CXX)
  set(SOURCES ${SOURCES} ${CXX_SOURCES})
  set(SDLU_CXX 1)
endif(BUILD_CXX)

# Shared library
if (BUILD_SHARED_LIBS)
  add_library(SDLU-shared SHARED ${SOURCES} ${HDRS})
  target_link_libraries(SDLU-shared ${LIBS})
  set_target_properties(SDLU-shared PROPERTIES OUTPUT_NAME "SDLU")
  set(INSTALL_LIBS ${INSTALL_LIBS} SDLU-shared)
endif(BUILD_SHARED_LIBS)

# Static library
set(STATIC "#")
if (BUILD_STATIC_LIBS)
  add_library(SDLU-static STATIC ${SOURCES} ${HDRS})
  target_link_libraries(SDLU-static ${LIBS})
  set_target_properties(SDLU-static PROPERTIES OUTPUT_NAME "SDLU")
  set(INSTALL_LIBS ${INSTALL_LIBS} SDLU-static)

  # these are for 'sdlu-config --static-libs'
  set(STATIC "")
endif(BUILD_STATIC_LIBS)

# Installation files
file(GLOB HDRS ${SDLU_SOURCE_DIR}/include/*.h ${SDLU_BINARY_DIR}/SDLU_config.h)
file(GLOB SDLU_PC ${CMAKE_BINARY_DIR}/sdlu.pc)
file(GLOB SDLU_CONFIG ${CMAKE_BINARY_DIR}/sdlu-config)
file(GLOB SDLU_M4 ${CMAKE_SOURCE_DIR}/scripts/autotools/m4/sdlu.m4)

# Framework
if (BUILD_FRAMEWORK)
  set(INST_DIR "@executable_path/../../../Library/Frameworks")
  set(INFO_PLIST "${CMAKE_SOURCE_DIR}/scripts/framework/Info.plist")

  add_library(SDLU-frwk SHARED ${SOURCES} ${HDRS} ${INFO_PLIST})
  target_link_libraries(SDLU-frwk ${LIBS})
  set_target_properties(SDLU-frwk PROPERTIES FRAMEWORK TRUE)
  set_target_properties(SDLU-frwk PROPERTIES OUTPUT_NAME "SDLU")
  set_target_properties(SDLU-frwk PROPERTIES PUBLIC_HEADER "${HDRS}")
  set_target_properties(SDLU-frwk PROPERTIES RESOURCE "${INFO_PLIST}")
  set_target_properties(SDLU-frwk PROPERTIES INSTALL_NAME_DIR "${INST_DIR}")
endif(BUILD_FRAMEWORK)

# Installation paths for sdlu-config and sdlu.pc
set(prefix ${CMAKE_INSTALL_PREFIX})
set(exec_prefix "${prefix}")
set(includedir "${prefix}/include/SDL2")
set(libdir "${exec_prefix}/lib${LIB_SUFFIX}")

# Generate config file (SDLU_config.h)
configure_file(
  ${CMAKE_SOURCE_DIR}/include/SDLU_config_cmake.h.in
  ${CMAKE_BINARY_DIR}/SDLU_config.h
)

# Generate pkg-config file
configure_file(
  ${CMAKE_SOURCE_DIR}/sdlu.pc.in
  ${CMAKE_BINARY_DIR}/sdlu.pc
)

# Generate sdlu-config
configure_file(
  ${CMAKE_SOURCE_DIR}/sdlu-config.in
  ${CMAKE_BINARY_DIR}/sdlu-config
)

# Installation targets
install(TARGETS ${INSTALL_LIBS} DESTINATION ${libdir})
install(PROGRAMS ${SDLU_CONFIG} DESTINATION ${prefix}/bin)
install(FILES ${HDRS} DESTINATION ${includedir})
install(FILES ${SDLU_PC} DESTINATION ${libdir}/pkgconfig)
install(FILES ${SDLU_M4} DESTINATION ${prefix}/share/aclocal)

# CPack Configuration
include("${CMAKE_SOURCE_DIR}/scripts/cmake/ConfigureCPack.cmake")

# Uninstall target (see http://www.cmake.org/Wiki/RecipeAddUninstallTarget)
configure_file(
  "${CMAKE_SOURCE_DIR}/scripts/cmake/cmake_uninstall.cmake.in"
  "${CMAKE_BINARY_DIR}/cmake_uninstall.cmake"
  IMMEDIATE @ONLY
)

add_custom_target(
  uninstall
  "${CMAKE_COMMAND}" -P "${CMAKE_BINARY_DIR}/cmake_uninstall.cmake"
)
