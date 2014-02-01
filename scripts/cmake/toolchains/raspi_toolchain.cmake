# Raspberry Pi system info
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_SYSTEM_VERSION 1)

# Root dir for cross-compiler
set(ROOT "$ENV{RPI_TOOLS}/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian")
set(ROOTFS "$ENV{RPI_SYSROOT}")

# Set cross-compiler
set(CMAKE_C_COMPILER "${ROOT}/bin/arm-linux-gnueabihf-gcc")
set(CMAKE_ASM_COMPILER "${ROOT}/bin/arm-linux-gnueabihf-gcc")
set(CMAKE_CXX_COMPILER "${ROOT}/bin/arm-linux-gnueabihf-g++")

# Cross-compiler flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --sysroot=${ROOTFS} -I${ROOTFS}/usr/include -L${ROOTFS}/usr/lib/arm-linux-gnueabihf -I${ROOTFS}/opt/vc/include -L${ROOTFS}/opt/vc/lib -Wno-psabi")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS}")

# Set sysroot
set(CMAKE_FIND_ROOT_PATH "${ROOT}")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
