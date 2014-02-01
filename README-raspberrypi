================================================================================
SDLU Raspberry Pi port 
================================================================================

Requirements:

Rasbian (other distros might also work)
SDL2 for the Raspberry Pi
VideoCore (should be installed by default)


================================================================================
Building the library for Raspberry Pi with configure [recommended]
================================================================================

Open a shell and execute:

    $ mkdir build && cd build
    $ ../configure; make; sudo make install


================================================================================
Cross-compiling from Linux x86
================================================================================

Requirements:
* Raspberry Pi cross-compiler (http://github.com/raspberrypi/tools)
* Rasbian system image (http://downloads.raspberrypi.org/rasbian_latest)
* SDL2 and SDL2_ttf for the Raspberry Pi (prefer the static libraries)

Get the cross-compilation tools with git and place them somewhere convenient.
For this tutorial, we will put them in '/opt/rpi-tools'.

    $ export RPI_TOOLS=/opt/rpi-tools
    $ git clone http://github.com/raspberrypi/tools $RPI_TOOLS --depth 1

Download the rasbian system image, unzip it, and you'll get *-wheezy-rasbian.img
Assuming the sysroot will be built in '/opt/rpi-sysroot'.

    $ export RPI_SYSROOT=/opt/rpi-sysroot
    $ sudo kpartx -a -v <path_to_rasbian_image>.img
    $ sudo mount -o loop /dev/mapper/loop0p2 /mnt
    $ sudo cp -r /mnt $RPI_SYSROOT

Next, set the following environment variables:

    $ SDL2_PI_LIBRARY       : /full/path/to/libSDL2.a (for Raspberry Pi)
    $ SDL2_TTF_PI_LIBRARY   : /full/path/to/libSDL2_ttf.a (for Raspberry Pi)
    $ SDL2_INCLUDE_DIR      : Directory where SDL.h is located
    $ SDL2_TTF_INCLUDE_DIR  : Directory where SDL_ttf.h is located

The final step is to build SDLU.

    $ ./scripts/build-scripts/rpibuild.sh

You can find the binaries in 'rpi-build/lib'. Finally, sdlu-rpi.tar.gz will be
built, which will contain the binaries ready for installation on the Raspberry
Pi.


================================================================================
Notes
================================================================================

By default, the files contained in the archive sdlu-rpi.tar.gz are ready to be
installed under '/usr/local'. If you want to install them in another directory,
set $INSTALL_PATH to this directory and re-build the library. For example, if
you want to install the library at '/opt/sdlu', you can do this:

    $ export INSTALL_PATH=/opt/sdlu
    $ ./scripts/build-scripts/rpibuild.sh


================================================================================
Feedback
================================================================================

The port is currently in a usable but still expiremental state. For that reason,
and since it is still rather untested, there may be bugs. Please try out the
library and report any issues you encounter in the SDLU issue tracker:

    http://bitbucket.org/sdlu/sdlu/issues


-- Aggelos Kolaitis
