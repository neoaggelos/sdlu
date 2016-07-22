### This script will create SDLU.framework

wd=`dirname $0`
wd=`cd $wd && echo $PWD`
wd=`cd $wd/../.. && echo $PWD`

BUILDDIR="$wd/build"

# Configure and build
if [ "x$1" == "x" ]; then
    mkdir -p $BUILDDIR && cd $BUILDDIR
    ../configure $configure_flags --disable-static --enable-shared
    make V=0
    library="$wd/build/.libs/libSDLU.0.dylib"
    config_h="$wd/build/include/SDLU_config.h"
else
    library="$1"
    config_h="$2"
fi

## Create framework
FRAMEWORK="$wd/SDLU.framework"
rm -rf $FRAMEWORK
mkdir -p $FRAMEWORK
mkdir -p $FRAMEWORK/Versions
mkdir -p $FRAMEWORK/Versions/A
mkdir -p $FRAMEWORK/Versions/A/Headers
mkdir -p $FRAMEWORK/Versions/A/Resources

# Copy files
headers=`find $wd/include -name '*.h'`
headers=`echo $headers $config_h`
plist="$wd/scripts/framework/Info.plist"
cp -R $library "$FRAMEWORK/Versions/A/SDLU"
cp -R $headers "$FRAMEWORK/Versions/A/Headers/"
cp -R $plist   "$FRAMEWORK/Versions/A/Resources/Info.plist"

# Create links
cd $FRAMEWORK && ln -s A                            Versions/Current
cd $FRAMEWORK && ln -s Versions/Current/SDLU        SDLU
cd $FRAMEWORK && ln -s Versions/Current/Resources   Resources
cd $FRAMEWORK && ln -s Versions/Current/Headers     Headers

# Finish
echo "Finished building -- framework name is SDLU.framework"

