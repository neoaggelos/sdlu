### This script is used to package SDLU snapshot tarballs

wd=`dirname $0`
wd=`cd $wd && echo $PWD`
wd=`cd $wd/../.. && echo $PWD`

rev=`git log --oneline | wc -l`
header="$wd/include/SDLU.h"
major=`grep "#define SDLU_VERSION_MAJOR" $header | sed "s,.*\([0-9]\).*,\1,"`
minor=`grep "#define SDLU_VERSION_MINOR" $header | sed "s,.*\([0-9]\).*,\1,"`
patch=`grep "#define SDLU_VERSION_PATCHLEVEL" $header | sed "s,.*\([0-9]\).*,\1,"`

echo "Packing SDLU version $major.$minor.$patch, revision $rev"

ARCHIVE=SDLU-$major.$minor.$patch-$rev
BUILDDIR=$wd/../$ARCHIVE

rm -f $wd/$ARCHIVE.tar.gz $wd/$ARCHIVE.zip

# Copy files
mkdir -p $BUILDDIR
cp -r $wd/* $BUILDDIR

cd $BUILDDIR && doxygen > /dev/null 2>> $wd/errlog
cd $BUILDDIR && rm -rf .git build .build test/build test/.build 2>> $wd/errlog

tar cvzf $wd/$ARCHIVE.tar.gz $BUILDDIR > /dev/null 2>> $wd/errlog
zip -r $wd/$ARCHIVE.zip $BUILDDIR > /dev/null 2>> $wd/errlog

rm -rf $BUILDDIR

echo "Done."
