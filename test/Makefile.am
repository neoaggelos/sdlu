if HAVE_OPENGLES2
GLES2_TESTS = testgles2
endif

if HAVE_OPENGL
GL_TESTS = testgl testrender2
endif
noinst_PROGRAMS = testbutton testcolorkey testcombo testfiledialog testfilesystem testfont testini testrender testsprite testtext ${GLES2_TESTS} ${GL_TESTS}

AM_CFLAGS = -DDATA_DIR=\"$(abs_srcdir)/data\"

testbutton_SOURCES      = common.c testbutton.c 
testcolorkey_SOURCES    = common.c testcolorkey.c
testcombo_SOURCES		= common.c testcombo.c
testfiledialog_SOURCES  = common.c testfiledialog.c
testfilesystem_SOURCES	= common.c testfilesystem.c
testfont_SOURCES        = common.c testfont.c
testini_SOURCES         = common.c testini.c
testrender_SOURCES      = common.c testrender.c
testsprite_SOURCES      = common.c testsprite.c
testtext_SOURCES        = common.c testtext.c

if HAVE_OPENGL
testgl_SOURCES          = common.c testgl.c
testrender2_SOURCES     = common.c testrender2.c
endif

if HAVE_OPENGLES2
testgles2_SOURCES       = common.c testgles2.c
endif

ACLOCAL_AMFLAGS = -I../scripts/autotools/m4
