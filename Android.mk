LOCAL_PATH := $(call my-dir)

### Android.mk
#
#	This file is used to build the Android port.
#	To build the Android port, refer to README-android

include $(CLEAR_VARS)

LOCAL_MODULE := SDLU

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include $(LOCAL_PATH)/src/common

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_C_INCLUDES)

LOCAL_SRC_FILES := $(subst $(LOCAL_PATH)/,, 				\
					$(wildcard $(LOCAL_PATH)/src/*.c)		\

# comment this for a release build
DEBUG_FLAGS := -D_DEBUG

# Compiler flags
LOCAL_CFLAGS := $(DEBUG_FLAGS) -DFILEDIALOG_DUMMY

# Used libraries
LOCAL_SHARED_LIBRARIES := SDL2 SDL2_ttf

include $(BUILD_SHARED_LIBRARY)
