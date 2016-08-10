## This script will cross-compile SDLU for the Raspberry Pi

wd=`dirname $0`
wd=`cd $wd && echo $PWD`
wd=`cd $wd/../.. && echo $PWD`

die() {
    echo "*** Error: $@"
    exit 1
}

# Check RPI_TOOLS (directory of cross-compiler)
if [ x$RPI_TOOLS == "x" ]; then
    die "\$RPI_TOOLS is not set, see README-raspberrypi"
fi

# Check RPI_SYSROOT (rasbian sysroot)
if [ x$RPI_SYSROOT == "x" ]; then
    die "\$RPI_SYSROOT is not set, see README-raspberrypi"
fi

if [ x$SDL2_PI_LIBRARY == "x" ]; then
    die "\$SDL2_PI_LIBRARY is not set, see README-raspberrypi"
fi

if [ x$SDL2_TTF_PI_LIBRARY == "x" ]; then
    die "\$SDL2_TTF_PI_LIBRARY is not set, see README-raspberrypi"
fi

if [ x$SDL2_INCLUDE_DIR == "x" ]; then
    die "\$SDL2_INCLUDE_DIR is not set, see README-raspberrypi"
fi

if [ x$SDL2_TTF_INCLUDE_DIR == "x" ]; then
    die "\$SDL2_TTF_INCLUDE_DIR is not set, see README-raspberrypi"
fi

# Make command
if [ x$MAKE == "x" ]; then
    MAKE="make -j`cat /proc/cpuinfo | grep vendor_id | wc -l`"
fi

# Initialization

# Setup cross-compilation tools
export CC="$RPI_TOOLS/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian/bin/arm-linux-gnueabihf-gcc --sysroot=$RPI_SYSROOT -I$RPI_SYSROOT/opt/vc/include -I$RPI_SYSROOT/usr/include -L$RPI_SYSROOT/opt/vc/lib -L$RPI_SYSROOT/usr/lib/arm-linux-gnueabihf"

# Configure and build
BUILDDIR="$wd/rpi-build"
mkdir -p $BUILDDIR && cd $BUILDDIR
../configure --with-sysroot="$RPI_SYSROOT" --host=arm-raspberry-linux-gnueabihf --prefix="$PWD" --with-sdl-prefix="$SDL2_ROOT"
$MAKE V=0
$MAKE install

if [ $? != 0 ]; then
    echo "*** Error: Build process failed"
    exit 1
fi

# Edit paths in sdlu.pc, sdlu-config and libSDLU.la
SDLU_PC=$BUILDDIR/lib/pkgconfig/sdlu.pc
SDLU_CONFIG=$BUILDDIR/bin/sdlu-config
LIBSDLU_LA=$BUILDDIR/lib/libSDLU.la
if [ x$INSTALL_PATH == "x" ]; then
    INSTALL_PATH=/usr/local
fi
mv $SDLU_PC $SDLU_PC.old >> /dev/null 2>&1
cat $SDLU_PC.old | sed "s,\<prefix=.*\>,prefix=$INSTALL_PATH," >> $SDLU_PC
rm $SDLU_PC.old >> /dev/null 2>&1
mv $SDLU_CONFIG $SDLU_CONFIG.old >> /dev/null 2>&1
cat $SDLU_CONFIG.old | sed "s,\<prefix=.*\>,prefix=$INSTALL_PATH," >> $SDLU_CONFIG
rm $SDLU_CONFIG.old >> /dev/null 2>&1
chmod a+x $SDLU_CONFIG
mv $LIBSDLU_LA $LIBSDLU_LA.old >> /dev/null 2>&1
cat $LIBSDLU_LA.old | sed "s,libdir='.*',libdir='$INSTALL_PATH'," >> $LIBSDLU_LA
rm $LIBSDLU_LA.old >> /dev/null 2>&1

# Create archive
tar cvzf sdlu-rpi.tar.gz include lib bin
mv sdlu-rpi.tar.gz $BUILDDIR/..
# $MAKE distclean

# Finish
echo "Finished building -- archive name is sdlu-rpi.tar.gz"

