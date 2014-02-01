## android.sh: Script to add SDLU in an SDL2 android-project

wd=`dirname $0`
wd=`cd $wd && echo $PWD`
wd=`cd $wd/../.. && echo $PWD`

usage="Usage: ./scripts/build-scripts/android.sh <PROJECT_DIR>"

updatefile() {
    cp $1 $1.old
    cat $1.old | sed "s,$2,$3," > $1
    rm $1.old
}

if test x$1 = x; then
    echo "$usage"
    exit 1
fi

# calculate needed files/dirs
PROJECT_DIR="$1"
JNI_DIR="$PROJECT_DIR/jni"
SDLU_DIR="$JNI_DIR/SDLU"
SRC_DEST="$SDLU_DIR/src"
INCLUDE_DEST="$SDLU_DIR/include"
ANDROID_MK="$SDLU_DIR/Android.mk"
SDL_ACTIVITY="$PROJECT_DIR/src/org/libsdl/app/SDLActivity.java"
CONFIG_H="$INCLUDE_DEST/SDLU_config_android.h"
APP_ANDROID_MK="$JNI_DIR/src/Android.mk"

sources=`find $wd/src -type f`
includes="$wd/include/*.h"

echo "Creating directories..."
mkdir -p $SDLU_DIR
mkdir -p $SRC_DEST
mkdir -p $INCLUDE_DEST

echo "Copying source code..."
cp -r $sources $SRC_DEST
cp -r $includes $INCLUDE_DEST
cp -r $wd/Android.mk $ANDROID_MK

echo "Creating config file..."
echo '#include "SDLU_config_android.h"' > $INCLUDE_DEST/SDLU_config.h

echo "Updating configuration..."

if test x$2 != "xupdate"; then
    updatefile $SDL_ACTIVITY 'System.loadLibrary("main");' 'System.loadLibrary("SDLU");\n\t\tSystem.loadLibrary("main");'
    updatefile $APP_ANDROID_MK 'LOCAL_SHARED_LIBRARIES :=' 'LOCAL_SHARED_LIBRARIES := SDLU'
fi

echo "Done."
exit 1

