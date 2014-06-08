/*
 * Stereo.cpp
 *
 *  Created on: Jun 2, 2014
 *      Author: imocanu
 */

#include "Stereo.hpp"

void init()
{

}

extern "C"
{

JNIEXPORT jstring JNICALL Java_com_stroodel_MainActivity_stringFromJNI(JNIEnv *env, jobject obj);

JNIEXPORT jstring JNICALL Java_com_stroodel_MainActivity_stringFromJNI(JNIEnv *env, jobject obj)
{
	//LOGE("==TEST==");
	return env->NewStringUTF("Hello from C++ over JNI!");
}

void Java_com_calibrate_CameraPreview_pixeltobmp( JNIEnv* env,jobject thiz,jobject bitmap1, jobject bitmap2)
{
	//LOGE("= pixeltobmp =");
}

jint Java_com_calibrate_CameraPreview_prepareCamera(JNIEnv* env,jobject thiz, jint videoid)
{
	//LOGE("== prepareCamera ==");

    char system_call_buffer[50];
    sprintf(system_call_buffer,"su -c \"chmod 666 %s\"",  dev0.c_str());
    system(system_call_buffer);

    char system_call_bufferSecond[50];
    sprintf(system_call_bufferSecond,"su -c \"chmod 666 %s\"",  dev1.c_str());
    system(system_call_bufferSecond);
}

jint Java_com_calibrate_CameraPreview_prepareCameraWithBase( JNIEnv* env,jobject thiz, jint videoid, jint videobase){

	int ret;
	return Java_com_calibrate_CameraPreview_prepareCamera(env,thiz,videoid);

}

void Java_com_calibrate_CameraPreview_processCamera( JNIEnv* env,jobject thiz)
{
	//LOGE("== processCamera ==");

    if (!c.Update(&c2, 25, grab_timeout_ms))
    {
        printf("Failed to acquire images\n");
        exit(1);
    }

    c.toIplImage(l);
    c2.toIplImage(r);

}


void Java_com_calibrate_CameraPreview_stopCamera(JNIEnv* env,jobject thiz)
{

}

void Java_com_calibrate_CameraPreview_processRBCamera( JNIEnv* env,jobject thiz, jint lrmode)
{

}

JNIEXPORT
void JNICALL Java_com_calibrate_CameraPreview_getBitmap(JNIEnv* env, jobject thiz,
jint width, jint height, jintArray bgra)
{
    jint*  _bgra = env->GetIntArrayElements(bgra, 0);

    Mat mbgra(height, width, CV_8UC4, (unsigned char *)_bgra);

    Mat test(l);
    test.copyTo(mbgra);

//    cvSaveImage("/mnt/sdcard/left.jpg" , l);
//    cvSaveImage("/mnt/sdcard/right.jpg", r);
//
//    imwrite("/mnt/sdcard/test.jpg", test);
//    imwrite("/mnt/sdcard/mbgra.jpg", mbgra);

    env->ReleaseIntArrayElements(bgra, _bgra, 0);
}

///**restore java bitmap (from JNI data)*/  //
//JNIEXPORT jobject JNICALL Java_com_jni_bitmap_1operations_JniBitmapHolder_jniGetBitmapFromStoredBitmapData(JNIEnv * env, jobject obj, jobject handle)
//  {
////  JniBitmap* jniBitmap = (JniBitmap*) env->GetDirectBufferAddress(handle);
////  if (jniBitmap->_storedBitmapPixels == NULL)
////    {
////    LOGD("no bitmap data was stored. returning null...");
////    return NULL;
////    }
//  //
//  //creating a new bitmap to put the pixels into it - using Bitmap Bitmap.createBitmap (int width, int height, Bitmap.Config config) :
//  //
//  //LOGD("creating new bitmap...");
//  jclass bitmapCls = env->FindClass("android/graphics/Bitmap");
//  jmethodID createBitmapFunction = env->GetStaticMethodID(bitmapCls, "createBitmap", "(IILandroid/graphics/Bitmap$Config;)Landroid/graphics/Bitmap;");
//  jstring configName = env->NewStringUTF("ARGB_8888");
//  jclass bitmapConfigClass = env->FindClass("android/graphics/Bitmap$Config");
//  jmethodID valueOfBitmapConfigFunction = env->GetStaticMethodID(bitmapConfigClass, "valueOf", "(Ljava/lang/String;)Landroid/graphics/Bitmap$Config;");
//  jobject bitmapConfig = env->CallStaticObjectMethod(bitmapConfigClass, valueOfBitmapConfigFunction, configName);
//  jobject newBitmap = env->CallStaticObjectMethod(bitmapCls, createBitmapFunction, 320, 240, bitmapConfig);
//  //
//  // putting the pixels into the new bitmap:
//  //
//  int ret;
//  void* bitmapPixels;
//  if ((ret = AndroidBitmap_lockPixels(env, newBitmap, &bitmapPixels)) < 0)
//    {
//    LOGE("AndroidBitmap_lockPixels() failed ! error=%d", ret);
//    return NULL;
//    }
//  uint32_t* newBitmapPixels = (uint32_t*) bitmapPixels;
//  int pixelsCount = 320 * 240;
//  memcpy(newBitmapPixels, jniBitmap->_storedBitmapPixels, sizeof(uint32_t) * pixelsCount);
//  AndroidBitmap_unlockPixels(env, newBitmap);
//  //LOGD("returning the new bitmap");
//  return newBitmap;
//  }


JNIEXPORT
void Java_com_calibrate_CameraPreview_matBitmap(JNIEnv* env,
												jobject thiz,
												jobject bitmap1,
												jobject bitmap2)
{

	Mat srcLeft(l);
	Mat srcRight(r);
	bool needPremultiplyAlpha = true;

	AndroidBitmapInfo  info;
	void*              pixels;
	int                ret;
	int i;

	int width = ww;
	int height = hh;

	if ((ret = AndroidBitmap_getInfo(env, bitmap1, &info)) < 0)
	{
		LOGE("AndroidBitmap_getInfo() failed ! error=%d", ret);
	}

	if (info.format != ANDROID_BITMAP_FORMAT_RGBA_8888)
	{
		LOGE("Bitmap format is not RGBA_8888 !");
	}

	if ((ret = AndroidBitmap_lockPixels(env, bitmap1, &pixels)) < 0)
	{
		LOGE("AndroidBitmap_lockPixels() failed ! error=%d", ret);
	}

	Mat tmp(info.height, info.width, CV_8UC4, pixels);
	if(srcLeft.type() == CV_8UC1)
	{
		cvtColor(srcLeft, tmp, CV_GRAY2RGBA);
	}else if(srcLeft.type() == CV_8UC3)
	{
		cvtColor(srcLeft, tmp, CV_RGB2RGBA);
	}else if(srcLeft.type() == CV_8UC4)
	{
		if(needPremultiplyAlpha)
		{
			cvtColor(srcLeft, tmp, COLOR_RGBA2mRGBA);
		}
		else
		{
			srcLeft.copyTo(tmp);
		}
	}


	if ((ret = AndroidBitmap_getInfo(env, bitmap2, &info)) < 0)
	{
		LOGE("AndroidBitmap_getInfo() failed ! error=%d", ret);
	}

	if (info.format != ANDROID_BITMAP_FORMAT_RGBA_8888)
	{
		LOGE("Bitmap format is not RGBA_8888 !");
	}

	if ((ret = AndroidBitmap_lockPixels(env, bitmap2, &pixels)) < 0)
	{
		LOGE("AndroidBitmap_lockPixels() failed ! error=%d", ret);
	}

	Mat tmpSecond(info.height, info.width, CV_8UC4, pixels);
	if(srcRight.type() == CV_8UC1)
	{
		cvtColor(srcRight, tmpSecond, CV_GRAY2RGBA);
	}else if(srcRight.type() == CV_8UC3)
	{
		cvtColor(srcRight, tmpSecond, CV_RGB2RGBA);
	}else if(srcRight.type() == CV_8UC4)
	{
		if(needPremultiplyAlpha)
		{
			cvtColor(srcRight, tmpSecond, COLOR_RGBA2mRGBA);
		}
		else
		{
			srcRight.copyTo(tmpSecond);
		}
	}


	AndroidBitmap_unlockPixels(env, bitmap1);
	AndroidBitmap_unlockPixels(env, bitmap2);
}


}

