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

libSDLU_la_CFLAGS = -I$(srcdir)/src -I$(srcdir)/include
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
		src/SDLU_create.c										\
		src/SDLU_framerate.c								\
		src/SDLU_sprite.c										\
		src/SDLU_ttf.c

include_HEADERS = 						\
		include/SDLU.h						\
		include/SDLU_button.h			\
		include/SDLU_combobox.h		\
		include/SDLU_create.h			\
		include/SDLU_defs.h				\
		include/SDLU_filedialog.h	\
    include/SDLU_filesystem.h \
		include/SDLU_fps.h				\
		include/SDLU_hints.h			\
		include/SDLU_ini.h				\
		include/SDLU_opengl.h			\
		include/SDLU_pixels.h			\
		include/SDLU_render.h			\
		include/SDLU_sprite.h			\
		include/SDLU_text.h

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = sdlu.pc

aclocaldir = $(datarootdir)/aclocal
aclocal_DATA = scripts/autotools/m4/sdlu.m4

ACLOCAL_AMFLAGS = -Iscripts/autotools/m4

EXTRA_DIST = \
	scripts Android.mk BUGS.txt ChangeLog CMakeLists.txt CONTRIBUTING.txt \
	COPYING.txt COPYING.uthash.txt Doxyfile INSTALL.txt Makefile.ios README.txt \
	README-git.txt sdlu-config.in sdlu.pc.in

