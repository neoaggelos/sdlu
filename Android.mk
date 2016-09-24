LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

# uncomment this if you build SDL2_ttf anyway
# SDL2_TTF := SDL2_ttf

# uncomment this if you build freetype2 anyway
# FREETYPE2 := freetype2

# uncomment this for a debug build
# DEBUG_FLAGS := -D_DEBUG

LOCAL_MODULE := SDLU

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include $(LOCAL_PATH)/src 

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include

# Compiler flags
LOCAL_CFLAGS := $(DEBUG_FLAGS) -DFILESYSTEM_DIRENT -DFILEDIALOG_DUMMY

LOCAL_SHARED_LIBRARIES := SDL2

LOCAL_SRC_FILES := \
	src/SDLU_button.c \
	src/SDLU_combobox.c \
	src/SDLU_common.c \
	src/SDLU_create.c \
	src/SDLU_framerate.c \
	src/SDLU_gl.c \
	src/SDLU_ini.c \
	src/SDLU_pixels.c \
	src/SDLU_render.c \
	src/SDLU_sprite.c \
	src/SDLU_ttf.c \
	src/SDLU_userdata.c \
	src/filedialog/SDLU_filedialog.c \
	src/filesystem/SDLU_filesystem.c \
	src/filesystem/SDLU_filesystem_dirent.c \
	
# we have to build our own SDL2_ttf
ifneq ($(SDL2_TTF),)
LOCAL_SRC_FILES +=	\
	external/sdl_ttf/SDL_ttf.c \

LOCAL_C_INCLUDES += $(LOCAL_PATH)/external/sdl_ttf
else
LOCAL_SHARED_LIBRARIES += $(SDL2_TTF)
endif

# we have to build our own freetype2
ifneq ($(SDL2_TTF)$(FREETYPE2),)

LOCAL_SRC_FILES += \
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

LOCAL_CFLAGS += -DFT2_BUILD_LIBRARY

LOCAL_C_INCLUDES += $(LOCAL_PATH)/external/freetype2/include
else
LOCAL_SHARED_LIBRARIES += $(FREETYPE2)
endif


include $(BUILD_SHARED_LIBRARY)
