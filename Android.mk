LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := SDLU

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include $(LOCAL_PATH)/src $(LOCAL_PATH)/external/freetype2/include $(LOCAL_PATH)/external/sdl_ttf

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include

LOCAL_SRC_FILES := $(subst $(LOCAL_PATH)/,, \
	$(wildcard $(LOCAL_PATH)/src/*.c) 	\
	$(LOCAL_PATH)/src/filedialog/SDLU_filedialog.c \
	$(LOCAL_PATH)/src/filesystem/SDLU_filesystem.c \
	$(LOCAL_PATH)/src/filesystem/SDLU_filesystem_dirent.c	\
	$(LOCAL_PATH)/external/sdl_ttf/SDL_ttf.c	\
	$(LOCAL_PATH)/external/freetype2/autofit.c	\
	$(LOCAL_PATH)/external/freetype2/ftbase.c		\
	$(LOCAL_PATH)/external/freetype2/ftbbox.c		\
	$(LOCAL_PATH)/external/freetype2/ftbdf.c		\
	$(LOCAL_PATH)/external/freetype2/ftbitmap.c	\
	$(LOCAL_PATH)/external/freetype2/ftcid.c		\
	$(LOCAL_PATH)/external/freetype2/ftdebug.c	\
	$(LOCAL_PATH)/external/freetype2/ftfstype.c	\
	$(LOCAL_PATH)/external/freetype2/ftgasp.c		\
	$(LOCAL_PATH)/external/freetype2/ftglyph.c	\
	$(LOCAL_PATH)/external/freetype2/ftgxval.c	\
	$(LOCAL_PATH)/external/freetype2/ftinit.c		\
	$(LOCAL_PATH)/external/freetype2/ftlcdfil.c	\
	$(LOCAL_PATH)/external/freetype2/ftmm.c			\
	$(LOCAL_PATH)/external/freetype2/ftotval.c	\
	$(LOCAL_PATH)/external/freetype2/ftpatent.c	\
	$(LOCAL_PATH)/external/freetype2/ftpfr.c		\
	$(LOCAL_PATH)/external/freetype2/ftstroke.c	\
	$(LOCAL_PATH)/external/freetype2/ftsynth.c	\
	$(LOCAL_PATH)/external/freetype2/ftsystem.c	\
	$(LOCAL_PATH)/external/freetype2/fttype1.c	\
	$(LOCAL_PATH)/external/freetype2/ftwinfnt.c	\
	$(LOCAL_PATH)/external/freetype2/ftxf86.c		\
	$(LOCAL_PATH)/external/freetype2/bdf.c			\
	$(LOCAL_PATH)/external/freetype2/ftbzip2.c	\
	$(LOCAL_PATH)/external/freetype2/ftcache.c	\
	$(LOCAL_PATH)/external/freetype2/cff.c			\
	$(LOCAL_PATH)/external/freetype2/type1cid.c	\
	$(LOCAL_PATH)/external/freetype2/ftgzip.c		\
	$(LOCAL_PATH)/external/freetype2/ftlzw.c		\
	$(LOCAL_PATH)/external/freetype2/pcf.c			\
	$(LOCAL_PATH)/external/freetype2/pfr.c			\
	$(LOCAL_PATH)/external/freetype2/psaux.c		\
	$(LOCAL_PATH)/external/freetype2/pshinter.c	\
	$(LOCAL_PATH)/external/freetype2/psmodule.c	\
	$(LOCAL_PATH)/external/freetype2/raster.c		\
	$(LOCAL_PATH)/external/freetype2/sfnt.c			\
	$(LOCAL_PATH)/external/freetype2/smooth.c		\
	$(LOCAL_PATH)/external/freetype2/apinames.c	\
	$(LOCAL_PATH)/external/freetype2/truetype.c	\
	$(LOCAL_PATH)/external/freetype2/type1.c		\
	$(LOCAL_PATH)/external/freetype2/type42.c		\
	$(LOCAL_PATH)/external/freetype2/winfnt.c)

# uncomment this for a debug build
# DEBUG_FLAGS := -D_DEBUG

# Compiler flags
LOCAL_CFLAGS := $(DEBUG_FLAGS) -DFILESYSTEM_DIRENT -DFT2_BUILD_LIBRARY

# Used libraries
LOCAL_SHARED_LIBRARIES := SDL2 SDL2_ttf

include $(BUILD_SHARED_LIBRARY)
