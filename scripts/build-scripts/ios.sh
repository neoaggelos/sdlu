## ios.sh: Build a fat binary for the iOS port

die() {
  echo $@
  exit 0
}

wd=`dirname $0`
wd=`cd $wd && echo $PWD`
wd=`cd $wd/../.. && echo $PWD`

usage="Usage: $0 --sdldir=path --arch=[armv6|armv7|i386|all] (--xcode-path=path --sdkver=major.minor --minver=major.minor)"

minver="3.0"
arch="all"
sdkver=`xcodebuild -showsdks | grep iphoneos | sed "s|.*iphoneos||"`
xcode_path=`xcode-select --print-path`
sdldir="$SDL2_IOS_HEADERS_PATH"

build_armv6=no
build_armv7=no
build_i386=no

while test x$1 != x; do
  case "$1" in
    -*=*) optarg=`echo $1 | sed "s,[-_a-zA-Z0-9]*=,,"` ;;
    *) optarg= ;;
  esac

  case "$1" in
    --sdldir=*) sdldir=$optarg ;;
    --sdkver=*) sdkver=$optarg ;;
    --minver=*) minver=$optarg ;;
    --xcode-path=*) xcode_path=$optarg ;;
    --arch=*) arch=$optarg ;;
    --help|--usage) die "$usage" ;;
    *) die "*** Error: Unknown option '$1'" ;;
  esac

  shift
done

case "$arch" in
  all) build_armv6=yes; build_armv7=yes; build_i386=yes ;;
  armv6) build_armv6=yes ;;
  armv7) build_armv7=yes ;;
  i386) build_i386=yes ;;
  *) die "Unkown architecture '$arch'" ;;
esac

if [ ! -f "$sdldir/SDL.h" ]; then
  die "Warning: SDL.h not found"
fi

builddir=$wd/build
mkdir -p "$builddir"

if test x$build_armv6 = xyes; then
  echo "Building armv6"
  make -f $wd/Makefile.ios SDK_VERSION=$sdkver MIN_VERSION=$minver ARCH=armv6 TARGET_OS=iPhoneOS XCODE_PATH=$xcode_path SDL2_INCLUDE_DIR=$sdldir SDL2_TTF_INCLUDE_DIR=. TARGET=$builddir/armv6.a > /dev/null
  make -f $wd/Makefile.ios clean > /dev/null
fi

if test x$build_armv7 = xyes; then
  echo "Building armv7"
  make -f $wd/Makefile.ios SDK_VERSION=$sdkver MIN_VERSION=$minver ARCH=armv7 TARGET_OS=iPhoneOS XCODE_PATH=$xcode_path SDL2_INCLUDE_DIR=$sdldir SDL2_TTF_INCLUDE_DIR=. TARGET=$builddir/armv7.a > /dev/null
  make -f $wd/Makefile.ios clean > /dev/null
fi

if test x$build_i386 = xyes; then
  echo "Building i386"
  make -f $wd/Makefile.ios SDK_VERSION=$sdkver MIN_VERSION=$minver ARCH=i386 TARGET_OS=iPhoneSimulator XCODE_PATH=$xcode_path SDL2_INCLUDE_DIR=$sdldir SDL2_TTF_INCLUDE_DIR=. TARGET=$builddir/i386.a > /dev/null
  make -f $wd/Makefile.ios clean > /dev/null
fi

lipo -create -o $wd/libSDLU.a $builddir/*.a
rm -rf $builddir

echo "Done. Created binary is $wd/libSDLU.a"

