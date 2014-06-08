LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
OPENCV_LIB_TYPE:=STATIC
include ../../sdk/native/jni/OpenCV.mk

LOCAL_MODULE    := stereo
LOCAL_SRC_FILES := Stereo.cpp processing/libcam.cpp
LOCAL_LDLIBS    += -lstdc++ -lc -lm -llog -ldl -ljnigraphics

include $(BUILD_SHARED_LIBRARY)
