LOCAL_PATH := $(call my-dir)

###########################
#
# Classes shared library
#
###########################

include $(CLEAR_VARS)

LOCAL_MODULE := Classes

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_C_INCLUDES)

LOCAL_SRC_FILES := \
	$(subst $(LOCAL_PATH)/,, \
	$(wildcard $(LOCAL_PATH)/src/*.cpp))

LOCAL_CFLAGS += -Wall
 
ifeq ($(NDK_DEBUG),1)
    cmd-strip :=
endif

LOCAL_STATIC_LIBRARIES := cpufeatures

include $(BUILD_SHARED_LIBRARY)


###########################
#
# Classes static library
#
###########################

LOCAL_MODULE := Classes_static

LOCAL_MODULE_FILENAME := libClasses

include $(BUILD_STATIC_LIBRARY)

# $(call import-module,android/cpufeatures)
