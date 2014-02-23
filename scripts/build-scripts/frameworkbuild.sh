### This script will create SDLU.framework
#
wd=`dirname $0`
wd=`cd $wd && echo $PWD`
wd=`cd $wd/../.. && echo $PWD`

# Configure and build
BUILDDIR="$wd/build"
mkdir -p $BUILDDIR && cd $BUILDDIR
../configure $configure_flags --disable-static --enable-shared
make V=0

## Create framework
FRAMEWORK="$wd/SDLU.framework"
rm -rf $FRAMEWORK
mkdir -p $FRAMEWORK && cd $FRAMEWORK
mkdir -p $FRAMEWORK/Versions
mkdir -p $FRAMEWORK/Versions/A
mkdir -p $FRAMEWORK/Versions/A/Headers
mkdir -p $FRAMEWORK/Versions/A/Resources

# Copy files
library="$wd/build/.libs/libSDLU.dylib.0.0.0"
headers=`find $wd/include -name '*.h'`
headers=`echo $headers $wd/build/include/SDLU_config.h`
plist="$wd/scripts/framework/Info.plist"
cp $library "$FRAMEWORK/Versions/A/SDLU" -r
cp $headers "$FRAMEWORK/Versions/A/Headers/" -r
cp $plist   "$FRAMEWORK/Versions/A/Resources/Info.plist" -r

# Create links
cd $FRAMEWORK && ln -s Versions/A/SDLU SDLU
cd $FRAMEWORK && ln -s Versions/A/Resources Resources 
cd $FRAMEWORK && ln -s Versions/A/Headers Headers 

# Finish
echo "Finished building -- framework name is SDLU.framework"

