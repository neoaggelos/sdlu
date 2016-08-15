LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := SDLU

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include $(LOCAL_PATH)/src

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_C_INCLUDES)

LOCAL_SRC_FILES := $(subst $(LOCAL_PATH)/,, \
	$(wildcard $(LOCAL_PATH)/src/*.c) 	\
	$(LOCAL_PATH)/src/filedialog/SDLU_filedialog.c \
	$(LOCAL_PATH)/src/filesystem/SDLU_filesystem.c \
	$(LOCAL_PATH)/src/filesystem/SDLU_filesystem_dirent.c)

# uncomment this for a debug build
# DEBUG_FLAGS := -D_DEBUG

# Compiler flags
LOCAL_CFLAGS := $(DEBUG_FLAGS) -DFILESYSTEM_DIRENT

# Used libraries
LOCAL_SHARED_LIBRARIES := SDL2 SDL2_ttf

include $(BUILD_SHARED_LIBRARY)
