if HAVE_OPENGLES2
GLES2_TESTS = testgles2
endif

if HAVE_OPENGL
GL_TESTS = testgl testrender2
endif

if HAVE_CXX
CXX_TESTS = testcxx
endif

noinst_PROGRAMS = testbutton testcollision testcolorkey testcombo testini testmath testmulticopy testrender testsprite testtext testturtle ${GLES2_TESTS} ${GL_TESTS} ${CXX_TESTS}

AM_CFLAGS = -DDATA_DIR=\"$(abs_srcdir)/data\"

testbutton_SOURCES      = common.c testbutton.c 
testcollision_SOURCES   = common.c testcollision.c 
testcolorkey_SOURCES    = common.c testcolorkey.c
testcombo_SOURCES		= common.c testcombo.c
testini_SOURCES         = common.c testini.c
testmath_SOURCES        = common.c testmath.c
testmulticopy_SOURCES   = common.c testmulticopy.c
testrender_SOURCES      = common.c testrender.c
testsprite_SOURCES      = common.c testsprite.c
testtext_SOURCES        = common.c testtext.c
testturtle_SOURCES		= common.c testturtle.c

if HAVE_OPENGL
testgl_SOURCES          = common.c testgl.c
testrender2_SOURCES     = common.c testrender2.c
endif

if HAVE_OPENGLES2
testgles2_SOURCES       = common.c testgles2.c
endif

if HAVE_CXX
testcxx_SOURCES         = common.c testcxx.cxx
endif

ACLOCAL_AMFLAGS = -I../scripts/autotools/m4
