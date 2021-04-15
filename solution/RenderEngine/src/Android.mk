include $(call all-subdir-makefiles)

LOCAL_PATH := $(call my-dir)

###########################
#
# SRE shared library
#
###########################

include $(CLEAR_VARS)

LOCAL_MODULE := SRE

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../include

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_C_INCLUDES)

SEARCH_DIR = $(wildcard $1$2) $(foreach d, $(wildcard $1*), $(call SEARCH_DIR, $d/, $2))
ALL_SRC := $(call SEARCH_DIR, $(LOCAL_PATH)/, *.cpp)
ALL_SRC := $(filter %.cpp, $(ALL_SRC))

# LOCAL_SRC_FILES := $(ALL_SRC)

#traverse all the directory and subdirectory
define walk
  $(wildcard $(1)) $(foreach e, $(wildcard $(1)/*), $(call walk, $(e)))
endef

#find all the file recursively under jni/
ALLFILES = $(call walk, $(LOCAL_PATH))
FILE_LIST := $(filter %.cpp, $(ALLFILES))

LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)

# LOCAL_CFLAGS += -Wall
# LOCAL_CFLAGS += -DSRE_ANDROID

LOCAL_CPPFLAGS := -frtti -fexceptions -std=c++17
  
ifeq ($(NDK_DEBUG),1)
    cmd-strip :=
endif

LOCAL_SHARED_LIBRARIES := \
	SDL2 \
	SDL2_image
	
LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog

include $(BUILD_SHARED_LIBRARY)

###########################
#
# SRE static library
#
###########################

LOCAL_MODULE := SRE_static

LOCAL_MODULE_FILENAME := libSRE

include $(BUILD_STATIC_LIBRARY)

# $(call import-module,android/cpufeatures)
