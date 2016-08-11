lib_LTLIBRARIES = libSDLU.la
bin_SCRIPTS = sdlu-config

extra_source_files= 
if FILEDIALOG_COCOA
extra_source_files += src/filedialog/SDLU_filedialog_cocoa.m
endif

if FILEDIALOG_WIN
extra_source_files += src/filedialog/SDLU_filedialog_win32.c
endif

if FILEDIALOG_GTK
extra_source_files += src/filedialog/SDLU_filedialog_gtk.c
endif

if FILESYSTEM_WIN
extra_source_files += src/filesystem/SDLU_filesystem_win32.c
endif

if FILESYSTEM_DIRENT
extra_source_files += src/filesystem/SDLU_filesystem_dirent.c
endif



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
		include/SDLU_features.h		\
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

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = sdlu.pc

aclocaldir = $(datarootdir)/aclocal
aclocal_DATA = scripts/autotools/m4/sdlu.m4

ACLOCAL_AMFLAGS = -Iscripts/autotools/m4

# this needs to be updated
EXTRA_DIST = scripts extras Android.mk ChangeLog CMakeLists.txt CONTRIBUTING \
			 COPYING Doxyfile README-android README-cmake README-configure \
			 README-ios README-raspberrypi README-windows sdlu-config.in \
			 sdlu.pc.in
