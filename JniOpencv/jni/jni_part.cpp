#include <jni.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <vector>

#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"


#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <android/log.h>

using namespace std;
using namespace cv;

extern "C"
{
JNIEXPORT
void JNICALL Java_org_opencv_samples_tutorial2_JniOpencvActivity_FindFeatures(JNIEnv*,
		jobject,
		jlong addrGray,
		jlong addrRgba);


JNIEXPORT
void JNICALL
Java_org_opencv_samples_tutorial2_JniOpencvActivity_InitStereoCamera(JNIEnv * env, jobject  obj);


JNIEXPORT
void JNICALL Java_org_opencv_samples_tutorial2_JniOpencvActivity_FindFeatures(JNIEnv*,
		jobject,
		jlong addrGray,
		jlong addrRgba)
{
	__android_log_write(ANDROID_LOG_VERBOSE, "Tag", "Error here");

	fprintf(stderr, "This message comes from C (JNI).\n");

	Mat& mGr  = *(Mat*)addrGray;
	Mat& mRgb = *(Mat*)addrRgba;
	vector<KeyPoint> v;

	FastFeatureDetector detector(50);
	detector.detect(mGr, v);

	for( unsigned int i = 0; i < v.size(); i++ )
	{
		const KeyPoint& kp = v[i];
		circle(mRgb, Point(kp.pt.x, kp.pt.y), 10, Scalar(255,0,0,255));
	}
}

JNIEXPORT
void JNICALL
Java_org_opencv_samples_tutorial2_JniOpencvActivity_InitStereoCamera(JNIEnv * env, jobject  obj)
{

	__android_log_print(ANDROID_LOG_INFO, "foo", "Error: %s", "sadfghjkhgfd");

//	    StereoCamera *sc = new StereoCamera();
//	    sc->opendevice(0);
//	    sc->opendevice(1);
//	    sc->checkCamerabase();
}


}


