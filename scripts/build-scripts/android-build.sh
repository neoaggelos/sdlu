## android-build.sh: Adds SDLU to an existing SDL2 android project

# update_file <file> <old_pattern> <new_pattern>
update_file() {
  cp $1 $1.old
  cat $1.old | sed "s,$2,$3," > $1
  rm $1.old
}

wd=`dirname $0`
wd=`cd $wd && echo $PWD`
wd=`cd $wd/../../ && echo $PWD`

usage="Usage: $0 <ANDROID_PROJECT_DIR> (update)"

if test x$1 = x; then
  echo $usage
  exit 1
fi

if [ ! -d "$1" ]; then
  echo $usage
  exit 1
fi

sources=`find $wd/src -type f`
headers=`find $wd/include/*.h -type f`

echo "Creating new directories..."
mkdir -p "$1/jni/SDLU/src" && rm -rf "$1/jni/SDLU/src/*"
mkdir -p "$1/jni/SDLU/include" && rm -rf "$1/jni/SDLU/include/*"

echo "Copying files..."
for file in $sources; do cp "$file" "$1/jni/SDLU/src/"; done
for file in $headers; do cp "$file" "$1/jni/SDLU/include/"; done
cp $wd/Android.mk "$1/jni/SDLU/Android.mk"

if test x$2 != xupdate; then
  # add SDLU in shared libraries
  update_file "$1/jni/src/Android.mk" 'LOCAL_SHARED_LIBRARIES :=' 'LOCAL_SHARED_LIBRARIES := SDLU'

  # load SDLU and SDL2_ttf at runtime
  update_file "$1/src/org/libsdl/app/SDLActivity.java" '\"SDL2_ttf\"' '\"SDL2_ttf\"\, \"SDLU\"'
  update_file "$1/src/org/libsdl/app/SDLActivity.java" '// \"SDL2_ttf\"' '\"SDL2_ttf\"'
fi

x=`find $1/jni | grep SDL2_ttf`
if test "x$x" = x; then
  echo "Warning: Required depency SDL2_ttf wasn't found in $1/jni"
fi

echo "Done."
exit 1

