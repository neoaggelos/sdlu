================================================================================
Building the tests using configure
================================================================================

Assuming the tests are in ~/sdlu/test:

    $ cd ~/sdlu/test
    $ ./configure; make

If configure cannot find the SDLU framework under Mac OS X:
(assuming the framework is in /Library/Frameworks)

    $ export SDLU_FRAMEWORK=/path/to/SDLU.framework
    $ ./configure; make

================================================================================
Building the tests using CMake
================================================================================

Assuming the tests are in ~/sdlu/test:

    $ cd ~/sdlu/test
    $ mkdir build && cd build
    $ cmake ..
    $ make

You can also use the CMake GUI.

================================================================================
Building the tests for Android
================================================================================

* Prepare an SDL2 android-project as explained in SDLU/INSTALL.txt.

* Add the files [testname.c, common.c, common.h] in "<PROJECT>/jni/src/". 

* Copy all files from "data/" in "<PROJECT>/assets/" (create folder if needed).

* Edit "<PROJECT>/jni/src/Android.mk" and replace YourSourceHere.c with
  testname.c and common.c

* Proceed with building the APK ('ndk-build' and 'ant debug')

================================================================================
Building the tests for iOS
================================================================================

* Build SDLU for iOS as explained in SDLU/INSTALL.txt

* Create a new SDL2 iOS project in Xcode (use the template that comes with the
  SDL2 source code)

* Add [testname.c, common.c, common.h] in the project

* Add libSDLU.a at the linker settings

* Proceed with building the application

================================================================================
Description of the tests
================================================================================

testbutton    : Simple example with buttons
testcollision : Collision detection between two rects
testcolorkey  : Simple example of loading textures with(out) a color-key
testcombo     : Simple combo box example
testfiledialog: Showcase how to create a simple open file dialog
testfilesystem: Simple program that lists contents of a directory
testgl        : Loads an OpenGL texture and blits it on the screen
testgles2     : Simple SDL2 + OpenGLES2 example
testini       : Shows how to use the ini file handling API
testmath      : Simple vector addition with SDLU math API
testmulticopy : Creates a tile-map from a single tile (uses RenderMultiCopy)
testrender    : Draws a circle and a filled polygon
testrender2   : Mixing pure OpenGL with the SDL2 Render API
testsprite    : Simple SDLU sprites example
testtext      : Shows off the text rendering API
testturtle    : Draws a rectangle using the turtle drawing API

