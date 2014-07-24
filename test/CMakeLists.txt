# SDLU CMakeLists.txt
cmake_minimum_required(VERSION 2.8)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)
set(CMAKE_WIN32_EXECUTABLE TRUE)

# Define the project
project(SDLU_Tests C)

# Also check for a C++ compiler
enable_language(CXX OPTIONAL)

# Load required modules
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/../scripts/cmake")
include("${CMAKE_SOURCE_DIR}/../scripts/cmake/FindSDL2_tests.cmake")
include("${CMAKE_SOURCE_DIR}/../scripts/cmake/FindSDLU.cmake")
include("${CMAKE_SOURCE_DIR}/../scripts/cmake/FindSDL2_ttf.cmake")
include("${CMAKE_SOURCE_DIR}/../scripts/cmake/FindGLES2.cmake")

# Find SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
set(LIBS ${LIBS} ${SDL2_LIBRARY})

# Find SDL2_ttf
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_TTF_INCLUDE_DIR})
set(LIBS ${LIBS} ${SDL2_TTF_LIBRARY})

# Find SDLU
find_package(SDLU REQUIRED)
include_directories(${SDLU_INCLUDE_DIR})
set(LIBS ${LIBS} ${SDLU_LIBRARY})

# Find OpenGL ES 2
find_package(GLES2)
if (GLES2_FOUND)
    include_directories(${GLES2_INCLUDE_DIR})
endif(GLES2_FOUND)

# Find OpenGL
find_package(OpenGL)
if (OPENGL_FOUND)
    include_directories(${OPENGL_INCLUDE_DIR})
endif(OPENGL_FOUND)

# Make sure executables can find the data directory
add_definitions("-DDATA_DIR=\"${CMAKE_SOURCE_DIR}/data\"")

# Add executables
set(TARGETS 
    "testbutton;testcollision;testcolorkey;testcombo;testfiledialog;testini;testmath;testmulticopy;testrender;testsprite;testtext;testturtle"
)
add_library(common OBJECT ${CMAKE_SOURCE_DIR}/common.c)
set(COMMON $<TARGET_OBJECTS:common>)

foreach(target ${TARGETS})
    add_executable(${target} "${CMAKE_SOURCE_DIR}/${target}.c" ${COMMON})
    target_link_libraries(${target} ${LIBS})
endforeach()

# add testgl and testrender2
if (OPENGL_FOUND)
    add_executable(testgl "${CMAKE_SOURCE_DIR}/testgl.c" ${COMMON})
    add_executable(testrender2 "${CMAKE_SOURCE_DIR}/testrender2.c" ${COMMON})
    target_link_libraries(testgl ${LIBS} ${OPENGL_gl_LIBRARY})
    target_link_libraries(testrender2 ${LIBS} ${OPENGL_gl_LIBRARY})
endif()

# add testgles2
if (GLES2_FOUND)
    add_executable(testgles2 "${CMAKE_SOURCE_DIR}/testgles2.c" ${COMMON})
    target_link_libraries(testgles2 ${LIBS} ${GLES2_LIBRARY})
endif()

# add testcxx
if (CMAKE_CXX_COMPILER_WORKS)
    add_executable(testcxx "${CMAKE_SOURCE_DIR}/testcxx.cxx" ${COMMON})
    target_link_libraries(testcxx ${LIBS})
endif()
