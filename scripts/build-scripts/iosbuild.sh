## iosbuild.sh: Build the iOS port

die() {
    echo "*** Error: $@"
    exit 1
}

if [ "x$SDL2_INCLUDE_DIR" == "x" ]; then
    die "\$SDL2_INCLUDE_DIR is not set, see README-ios"
fi

if [ "x$SDL2_TTF_INCLUDE_DIR" == "x" ]; then
    die "\$SDL2_TTF_INCLUDE_DIR is not set, see README-ios"
fi

wd=`dirname $0`
wd=`cd $wd && echo $PWD`
wd=`cd $wd/../.. && echo $PWD`

usage="Usage: ./scripts/build-scripts/iosbuild.sh [--architecture=arm|armv6|armv7|i386] [--sdk-version=major.minor] [--iphoneos-min-version=major.minor] [--xcode-path=PATH] [--sdl-prefix=PATH]

Available options:
--architecture: Choose the architecture to build [armv6, armv7, i386]
--sdk-version: Choose the version of the iOS SDK to use.
--iphoneos-min-version: The minimum iOS version that your application requires.
--xcode-path: Directory where Xcode is installed
"

iphoneos_min_version="3.0"
sdk_path=""
architecture="armv7"
xcode_path=`xcode-select --print-path`
dev_path=""
sdk_version=`xcodebuild -showsdks | grep iphoneos | sed "s|*iphoneos||"`

while test x$1 != x; do
    case "$1" in
        -*=*) optarg=`echo $1 | sed "s,[-_a-zA-Z0-9]*=,,"` ;;
        *) optarg= ;;
    esac

    case "$1" in
        --sdk-version=*)
            sdk_version=$optarg
            ;;
        --iphoneos-min-version=*)
            iphoneos_min_version=$optarg
            ;;
        --architecture=*)
            architecture=$optarg
            ;;
        --xcode-path=*)
            xcode_path=$optarg
            ;;
        --help|--usage)
            echo "$usage"
            exit 0
            ;;
        *)
            echo "*** Error: Unknown option '$1'"
            echo "$usage"
            exit 1
            ;;
    esac
done

case $architecture in
    armv6)
        CFLAGS="$CFLAGS -arch armv6"
        target="iPhoneOS"
        ;;
    armv7)
        CFLAGS="$CFLAGS -arch armv7"
        target="iPhoneOS"
        ;;
    i386)
        CFLAGS="$CFLAGS -arch i386"
        target="iPhoneSimulator"
        ;;
    *)
        echo "*** Error: architecture '$architecture' is not supported"
        exit 1
        ;;
esac

dev_path="$xcode_path/Platforms/$target.platform/Developer"
sdk_path="$dev_path/SDKs/$target$sdk_version.sdk"

export CC="$dev_path/usr/bin/llvm-gcc-4.2"
export CXX="$dev_path/usr/bin/llvm-g++-4.2"
export AR="$dev_path/usr/bin/ar"

export CFLAGS="$CFLAGS -pipe -g -02 -no-cpp-precomp -isysroot $sdk_path -miphoneos-min-version=$iphoneos_min_version -I/$sdk_path/usr/include"
export LIBS="$LIBS -isysroot $sdk_path -L/$sdk_path/usr/lib
-miphoneos-min-version=$iphoneos_min_version --static-libgcc"

builddir=$wd/build
mkdir -p "$builddir" && cd "$builddir"

../configure --disable-sdltest --disable-cxx --enable-debug --with-sysroot="$sdk_path" --disable-shared --enable-static --host=custom-apple-darwin
make -j3

echo "Done. You can find the binaries in \"$wd/build\"".

