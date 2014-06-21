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

#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>

// Point cloud library
#include <pcl/point_cloud.h>
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/passthrough.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/kdtree/kdtree_flann.h>

#include <cvblobslib/Blob.h>
#include <cvblobslib/BlobContour.h>
#include <cvblobslib/BlobLibraryConfiguration.h>
#include <cvblobslib/BlobOperators.h>
#include <cvblobslib/BlobProperties.h>
#include <cvblobslib/BlobResult.h>
#include <cvblobslib/ComponentLabeling.h>

typedef pcl::PointXYZI PointT;

#include "processing/libcam.h"

#define VERSION			1.0

using namespace cv;
using namespace std;
using namespace pcl;

int ww = 320;
int hh = 240;
int fps = 60;
int skip_frames = 1;
int grab_timeout_ms = 1000;

string dev0 = "/dev/video0";
string dev1 = "/dev/video1";

#define  LOG_TAG    "stereo"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)


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

void      Java_com_calibrate_CameraPreview_getBitmap(JNIEnv* env,
													jobject thiz,
													jint width,
													jint height,
													jintArray bgra);

void Java_com_calibrate_CameraPreview_matBitmap(JNIEnv* env,jobject thiz, jobject bitmap1, jobject bitmap2);

}

#endif /* STEREO_HPP_ */
