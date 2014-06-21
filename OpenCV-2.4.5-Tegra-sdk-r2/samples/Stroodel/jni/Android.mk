LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
OPENCV_LIB_TYPE:=STATIC
include ../../sdk/native/jni/OpenCV.mk

LOCAL_MODULE    := stereo
LOCAL_SRC_FILES := Stereo.cpp processing/libcam.cpp \
                   cvblob/Blob.cpp \
                   cvblob/BlobContour.cpp \
                   cvblob/BlobOperators.cpp \
                   cvblob/BlobResult.cpp \
                   cvblob/ComponentLabeling.cpp 


LOCAL_LDLIBS  += -L$(BOOST_ANDROID_ROOT)/lib/ -L$(NDK_ROOT)/sources/cxx-stl/gnu-libstdc++/4.6/libs/armeabi-v7a  
LOCAL_LDLIBS  += -lstdc++ -lc -lm -llog -ldl -ljnigraphics #-landroid -lEGL -lGLESv2 #-lgnustl_static

LOCAL_STATIC_LIBRARIES += android_native_app_glue 

include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue) 

#LOCAL_LDLIBS += -L$(BOOST_ANDROID_ROOT)/lib/
#LOCAL_LDLIBS += -lboost_system-gcc-mt-1_53
#LOCAL_LDLIBS += -L$(NDK_ROOT)/sources/cxx-stl/gnu-libstdc++/4.6/libs/armeabi-v7a/libgnustl_static.a -lgnustl_static

#LOCAL_SHARED_LIBRARIES += libboost_system-gcc-mt-1_53

# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


#LOCAL_C_INCLUDES += $(NDK_ROOT)/boost/include/boost-1_53
#LOCAL_CFLAGS += -I$(NDK_ROOT)/boost/include/boost-1_53
#LOCAL_LDLIBS += -L$(NDK_ROOT)/boost/lib 
#LOCAL_LDLIBS    += -lstdc++ -lc -lm -llog -ldl -ljnigraphics -lboost_date_time-gcc-mt-1_53
#LOCAL_LDLIBS += -lboost_date_time-gcc-mt-1_53
#LOCAL_LDLIBS += -L$(NDK_ROOT)/build/boost-android/lib
#LOCAL_LDLIBS += -lboost_thread-gcc-mt-1_53
#LOCAL_STATIC_LIBRARIES += libboost_date_time-gcc-mt-1_53
#LOCAL_SHARED_LIBRARIES += libboost_date_time-gcc-mt-1_53
#LOCAL_C_INCLUDES += /boost/include/boost-1_53
#LOCAL_LDLIBS += -L/boost/lib 
#LOCAL_LDLIBS += -lboost_date_time-gcc-mt-1_53
#LOCAL_LDLIBS    += -lstdc++ -lc -lm -llog -ldl -ljnigraphics 
#LOCAL_SHARED_LIBRARIES += libboost_date_time-gcc-mt-1_53

#include $(BUILD_SHARED_LIBRARY)
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#LOCAL_PATH := $(call my-dir)
#
#include $(CLEAR_VARS)
#OPENCV_LIB_TYPE:=STATIC
#include ../../sdk/native/jni/OpenCV.mk
#
#LOCAL_MODULE    := stereo
#LOCAL_SRC_FILES := Stereo.cpp processing/libcam.cpp
#LOCAL_LDLIBS    += -lstdc++ -lc -lm -llog -ldl -ljnigraphics
#
#include $(BUILD_SHARED_LIBRARY)
#
#
#include $(CLEAR_VARS)
#LOCAL_MODULE := boost_date_time-gcc-mt-1_53
#LOCAL_SRC_FILES := /boost/lib/libboost_date_time-gcc-mt-1_53.a
#include $(PREBUILT_STATIC_LIBRARY)