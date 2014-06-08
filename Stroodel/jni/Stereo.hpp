/*
 * Stereo.hpp
 *
 *  Created on: Jun 2, 2014
 *      Author: imocanu
 */

#ifndef STEREO_HPP_
#define STEREO_HPP_

#define USE_OPENCV

#include <jni.h>
#include <android/log.h>
#include <android/bitmap.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <unistd.h>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <stdlib.h>
#include <ctype.h>

#include <opencv/cv.h>
#include <opencv/cxmisc.h>
#include <opencv/cvaux.h>
#include <opencv/highgui.h>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/contrib/contrib.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "processing/libcam.h"

#define VERSION			1.0

using namespace cv;
using namespace std;

int ww = 320;
int hh = 240;
int fps = 60;
int skip_frames = 1;
int grab_timeout_ms = 1000;

string dev0 = "/dev/video1";
string dev1 = "/dev/video0";

#define  LOG_TAG    "stereo"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)


 Camera c(dev0.c_str(), ww, hh, fps);
 Camera c2(dev1.c_str(), ww, hh, fps);

 IplImage *l=cvCreateImage(cvSize(ww, hh), 8, 3);
 IplImage *r=cvCreateImage(cvSize(ww, hh), 8, 3);

 IplImage *lg=cvCreateImage(cvGetSize(l),IPL_DEPTH_8U,1);
 IplImage *rg=cvCreateImage(cvGetSize(r),IPL_DEPTH_8U,1);


 bool displayCorners = true;//true;
 const int maxScale = 2;
 const float squareSize = 1.f;  // Set this to your actual square size
 // ARRAY AND VECTOR STORAGE:

 vector<vector<Point2f> > imagePoints[2];
 vector<vector<Point3f> > objectPoints;
 Size imageSize;

 int i = 0, j = 0, k, nimages = 30;  // nr de perechi

 //imagePoints[0].resize(nimages);
 //imagePoints[1].resize(nimages);
 vector<IplImage*> goodImageList;

 bool useCalibrated=false;
 bool showRectified=true;
 bool isVerticalStereo  = true;

 Mat rmap[2][2];
 Rect validRoi[2];

 bool finalCalibrated  = true;
 bool startCalibration = true;

void init();

extern "C"
{
void Java_com_calibrate_CameraPreview_pixeltobmp(JNIEnv* env,jobject thiz, jobject bitmap1, jobject bitmap2);
jint Java_com_calibrate_CameraPreview_prepareCamera(JNIEnv* env,jobject thiz, jint videoid);
jint Java_com_calibrate_CameraPreview_prepareCameraWithBase(JNIEnv* env,jobject thiz, jint videoid, jint videobase);
void Java_com_calibrate_CameraPreview_processCamera(JNIEnv* env,jobject thiz);
void Java_com_calibrate_CameraPreview_stopCamera(JNIEnv* env,jobject thiz);
void Java_com_calibrate_CameraPreview_processRBCamera(JNIEnv* env,jobject thiz, jint lrmode);

//jintArray Java_com_calibrate_CameraPreview_getLeftImage(JNIEnv * env, jobject thiz);
//jintArray Java_com_calibrate_CameraPreview_getRightImage(JNIEnv * env, jobject thiz);
void      Java_com_calibrate_CameraPreview_getBitmap(JNIEnv* env,
													jobject thiz,
													jint width,
													jint height,
													jintArray bgra);

void Java_com_calibrate_CameraPreview_matBitmap(JNIEnv* env,jobject thiz, jobject bitmap1, jobject bitmap2);

}

#endif /* STEREO_HPP_ */
