LOCAL_PATH := $(call my-dir)

### Android.mk
#
#	This file is used to build the Android port.
#	To build the Android port, refer to README-android

include $(CLEAR_VARS)

LOCAL_MODULE := SDLU

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include $(LOCAL_PATH)/src/common

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_C_INCLUDES)

LOCAL_SRC_FILES := $(subst $(LOCAL_PATH)/,, 					\
					$(LOCAL_PATH)/src/SDLU_create.c
					$(LOCAL_PATH)/src/gui/SDLU_button.c
					$(LOCAL_PATH)/src/gui/SDLU_combobox.c
					$(LOCAL_PATH)/src/SDLU_framerate.c
					$(LOCAL_PATH)/src/render/SDLU_pixels.c
					$(LOCAL_PATH)/src/render/SDLU_render.c
					$(LOCAL_PATH)/src/filedialog/SDLU_filedialog_dummy.c
					$(LOCAL_PATH)/src/text/SDLU_ttf.c
					$(LOCAL_PATH)/src/SDLU_collide.c
					$(LOCAL_PATH)/src/sprite/SDLU_sprite.c
					$(LOCAL_PATH)/src/common/SDLU_common.c
					$(LOCAL_PATH)/src/common/SDLU_userdata.c
					$(LOCAL_PATH)/src/turtle/SDLU_turtle.c
					$(LOCAL_PATH)/src/gl/SDLU_gl.c
					$(LOCAL_PATH)/src/ini/SDLU_ini.c
					$(LOCAL_PATH)/src/SDLU_math.c
					$(wildcard $(LOCAL_PATH)/src/*.cxx))

# comment this for a release build
DEBUG_FLAGS := -D_DEBUG

# Compiler flags
LOCAL_CFLAGS := $(DEBUG_FLAGS) -DFILEDIALOG_DUMMY

# Used libraries
LOCAL_SHARED_LIBRARIES := SDL2 SDL2_ttf

include $(BUILD_SHARED_LIBRARY)
