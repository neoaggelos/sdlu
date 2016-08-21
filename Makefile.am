noinst_LTLIBRARIES = libft.la libsdlttf.la
lib_LTLIBRARIES = libSDLU.la
bin_SCRIPTS = sdlu-config

extra_source_files= 
if FILEDIALOG_COCOA
extra_source_files += src/filedialog/SDLU_filedialog_cocoa.m
endif

if FILEDIALOG_WINDOWS
extra_source_files += src/filedialog/SDLU_filedialog_windows.c
endif

if FILEDIALOG_GTK
extra_source_files += src/filedialog/SDLU_filedialog_gtk.c
endif

if FILESYSTEM_WINDOWS
extra_source_files += src/filesystem/SDLU_filesystem_windows.c
endif

if FILESYSTEM_DIRENT
extra_source_files += src/filesystem/SDLU_filesystem_dirent.c
endif

libSDLU_la_LIBADD = libsdlttf.la
libSDLU_la_CFLAGS = -I$(srcdir)/external/sdl_ttf -I$(srcdir)/src -I$(srcdir)/include
libSDLU_la_OBJCFLAGS = $(libSDLU_la_CFLAGS)

libSDLU_la_SOURCES = 										\
		${extra_source_files}								\
		src/SDLU_common.c										\
		src/SDLU_userdata.c									\
		src/filedialog/SDLU_filedialog.c		\
  	src/filesystem/SDLU_filesystem.c		\
		src/SDLU_gl.c												\
		src/SDLU_button.c										\
		src/SDLU_combobox.c									\
		src/SDLU_ini.c											\
		src/SDLU_pixels.c										\
		src/SDLU_render.c										\
		src/SDLU_collide.c									\
		src/SDLU_create.c										\
		src/SDLU_framerate.c								\
		src/SDLU_math.c											\
		src/SDLU_sprite.c										\
		src/SDLU_ttf.c											\
		src/SDLU_turtle.c

include_HEADERS = 						\
		include/SDLU.h						\
		include/SDLU_button.h			\
		include/SDLU_collide.h		\
		include/SDLU_combobox.h		\
		include/SDLU_create.h			\
		include/SDLU_defs.h				\
		include/SDLU_filedialog.h	\
    include/SDLU_filesystem.h \
		include/SDLU_fps.h				\
		include/SDLU_hints.h			\
		include/SDLU_ini.h				\
		include/SDLU_math.h				\
		include/SDLU_opengl.h			\
		include/SDLU_pixels.h			\
		include/SDLU_render.h			\
		include/SDLU_sprite.h			\
		include/SDLU_text.h				\
		include/SDLU_turtle.h

# SDL2_ttf
libsdlttf_la_SOURCES = external/sdl_ttf/SDL_ttf.c
libsdlttf_la_LIBADD = libft.la
libsdlttf_la_CFLAGS = -I$(srcdir)/external/freetype2/include -DFT2_BUILD_LIBRARY

# freetype
if MACOSX_SYSTEM
ftmac_c=external/freetype2/ftmac.c
endif

libft_la_SOURCES =								\
		$(ftmac_c)										\
		external/freetype2/autofit.c	\
		external/freetype2/ftbase.c		\
		external/freetype2/ftbbox.c		\
		external/freetype2/ftbdf.c		\
		external/freetype2/ftbitmap.c	\
		external/freetype2/ftcid.c		\
		external/freetype2/ftdebug.c	\
		external/freetype2/ftfstype.c	\
		external/freetype2/ftgasp.c		\
		external/freetype2/ftglyph.c	\
		external/freetype2/ftgxval.c	\
		external/freetype2/ftinit.c		\
		external/freetype2/ftlcdfil.c	\
		external/freetype2/ftmm.c			\
		external/freetype2/ftotval.c	\
		external/freetype2/ftpatent.c	\
		external/freetype2/ftpfr.c		\
		external/freetype2/ftstroke.c	\
		external/freetype2/ftsynth.c	\
		external/freetype2/ftsystem.c	\
		external/freetype2/fttype1.c	\
		external/freetype2/ftwinfnt.c	\
		external/freetype2/ftxf86.c		\
		external/freetype2/bdf.c			\
		external/freetype2/ftbzip2.c	\
		external/freetype2/ftcache.c	\
		external/freetype2/cff.c			\
		external/freetype2/type1cid.c	\
		external/freetype2/ftgzip.c		\
		external/freetype2/ftlzw.c		\
		external/freetype2/pcf.c			\
		external/freetype2/pfr.c			\
		external/freetype2/psaux.c		\
		external/freetype2/pshinter.c	\
		external/freetype2/psmodule.c	\
		external/freetype2/raster.c		\
		external/freetype2/sfnt.c			\
		external/freetype2/smooth.c		\
		external/freetype2/apinames.c	\
		external/freetype2/truetype.c	\
		external/freetype2/type1.c		\
		external/freetype2/type42.c		\
		external/freetype2/winfnt.c

libft_la_CFLAGS=-I$(srcdir)/external/freetype2/include -DFT2_BUILD_LIBRARY

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = sdlu.pc

aclocaldir = $(datarootdir)/aclocal
aclocal_DATA = scripts/autotools/m4/sdlu.m4

ACLOCAL_AMFLAGS = -Iscripts/autotools/m4

EXTRA_DIST = \
	scripts Android.mk BUGS.txt ChangeLog CMakeLists.txt CONTRIBUTING.txt \
	COPYING.txt COPYING.uthash.txt Doxyfile INSTALL.txt Makefile.ios README.txt \
	README-git.txt sdlu-config.in sdlu.pc.in

