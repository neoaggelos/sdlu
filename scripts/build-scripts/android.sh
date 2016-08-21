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

usage="Usage: $0 <ANDROID_PROJECT_DIR>"

if test x$1 = x; then
  echo $usage
  exit 1
fi

if [ ! -d "$1" ]; then
  echo $usage
  exit 1
fi

echo "Linking SDLU to jni directory"
ln -s "$wd" "$1/jni/SDLU"

if test x$2 != xupdate; then
  # add SDLU in shared libraries
  update_file "$1/jni/src/Android.mk" 'LOCAL_SHARED_LIBRARIES :=' 'LOCAL_SHARED_LIBRARIES := SDLU'

  # load SDLU and SDL2_ttf at runtime
  update_file "$1/src/org/libsdl/app/SDLActivity.java" '\"SDL2\"\,' '\"SDL2\"\, \"SDLU\"\,'
fi

echo "Done."
exit 1

