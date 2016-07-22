lib_LTLIBRARIES = libSDLU.la
bin_SCRIPTS = sdlu-config

if CXX
cxx_sources =	src/cxx/SDLU_CButton.cxx		\
				src/cxx/SDLU_CComboBox.cxx		\
				src/cxx/SDLU_CIniHandler.cxx	\
				src/cxx/SDLU_CRenderer.cxx		\
				src/cxx/SDLU_CRWops.cxx         \
				src/cxx/SDLU_CSprite.cxx		\
				src/cxx/SDLU_CTexture.cxx		\
				src/cxx/SDLU_CTurtle.cxx		\
				src/cxx/SDLU_CWindow.cxx

libSDLU_la_LINK = $(CXXLINK)
else
cxx_sources =
libSDLU_la_LINK = $(LINK)
endif

libSDLU_la_SOURCES = ${cxx_sources}             					\
					 src/common/SDLU_common.c						\
					 src/common/SDLU_userdata.c						\
					 src/filedialog/SDLU_filedialog.c				\
					 src/filedialog/SDLU_filedialog_gtk.c			\
					 src/filedialog/SDLU_filedialog_win32.c			\
					 src/gl/SDLU_gl.c								\
					 src/gui/SDLU_button.c							\
					 src/gui/SDLU_combobox.c						\
					 src/ini/SDLU_ini.c								\
					 src/render/SDLU_pixels.c						\
					 src/render/SDLU_render.c						\
					 src/SDLU_collide.c								\
					 src/SDLU_create.c								\
					 src/SDLU_framerate.c							\
					 src/SDLU_math.c								\
					 src/sprite/SDLU_sprite.c						\
					 src/text/SDLU_ttf.c							\
					 src/turtle/SDLU_turtle.c

if FILEDIALOG_COCOA
libSDLU_la_SOURCES += src/filedialog/SDLU_filedialog_cocoa.m
endif

include_HEADERS = include/SDLU.h				\
				  include/SDLU_button.h			\
				  include/SDLU_collide.h		\
				  include/SDLU_combobox.h		\
				  include/SDLU_config.h			\
				  include/SDLU_create.h			\
				  include/SDLU_cxx.h			\
				  include/SDLU_defs.h			\
				  include/SDLU_features.h		\
				  include/SDLU_filedialog.h		\
				  include/SDLU_fps.h			\
				  include/SDLU_hints.h			\
				  include/SDLU_ini.h			\
				  include/SDLU_math.h			\
				  include/SDLU_opengl.h			\
				  include/SDLU_pixels.h			\
				  include/SDLU_render.h			\
				  include/SDLU_sprite.h			\
				  include/SDLU_text.h			\
				  include/SDLU_turtle.h

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = sdlu.pc

aclocaldir = $(datarootdir)/aclocal
aclocal_DATA = scripts/autotools/m4/sdlu.m4

ACLOCAL_AMFLAGS = -Iscripts/autotools/m4

EXTRA_DIST = scripts extras Android.mk ChangeLog CMakeLists.txt CONTRIBUTING \
			 COPYING Doxyfile README-android README-cmake README-configure \
			 README-cxx README-git README-ios README-raspberrypi README-windows \
			 sdlu-config.in sdlu.pc.in
