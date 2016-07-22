### Build rpm and deb packages
set(CPACK_GENERATOR "DEB;RPM")
exec_program("dpkg" ARGS "--print-architecture" OUTPUT_VARIABLE ARCH)

### Generic settings
set(CPACK_PACKAGE_NAME "libsdlu-dev")
set(CPACK_PACKAGE_VENDOR "Aggelos Kolaitis <neoaggelos@gmail.com>")
set(CPACK_PACKAGE_VERSION "2.1")
set(CPACK_PACKAGE_VERSION_MAJOR "2")
set(CPACK_PACKAGE_VERSION_MINOR "1")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "The SDL Utility library")
set(CPACK_PACKAGE_DESCRIPTION "The SDL Utility library is a cross-platform library that makes development of SDL2 programs faster and easier")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_SOURCE_DIR}/README")

### Resource files
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING")
set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README")

### Debian specific settings
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Aggelos Kolaitis <neoaggelos@gmail.com>")
set(CPACK_DEBIAN_PACKAGE_SECTION "Development")
set(CPACK_DEBIAN_PACKAGE_VERSION "${CPACK_PACKAGE_VERSION}")
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "${ARCH}")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libsdl2-dev (>= 2.0.0), libsdl2-ttf-dev")

### RPM specific settings
set(CPACK_RPM_PACKAGE_LICENSE "zlib")
set(CPACK_RPM_PACKAGE_ARHITECTURE "${ARCH}")
set(CPACK_RPM_PACKAGE_REQUIRES "SDL2-devel")

### libsdlu-dev-$(version)-$(arch)
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_DEBIAN_PACKAGE_ARCHITECTURE}")

### Include CPack
include(CPack)
