#include <jni.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <vector>
#include "StereoCamera.h"

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

using namespace std;
using namespace cv;


StereoCamera::StereoCamera()
{
    for(int lr=0;lr<2;lr++){
        captures[lr] = 0;
        frames[lr] = 0;
        framesGray[lr] = 0;
    }
    ready = false;
}

StereoCamera::~StereoCamera()
{
    for(int lr=0;lr<2;lr++){
        cvReleaseImage(&frames[lr]);
        cvReleaseImage(&framesGray[lr]);
        cvReleaseCapture(&captures[lr]);
    }

}

int StereoCamera::setup(CvSize imageSize){
    this->imageSize = imageSize;

    captures[0] = cvCaptureFromCAM(1);
    captures[1] = cvCaptureFromCAM(2);

    if( captures[0] && captures[1]){

        for(int i=0;i<2;i++){
                cvSetCaptureProperty(captures[i] ,CV_CAP_PROP_FRAME_WIDTH,imageSize.width);
                cvSetCaptureProperty(captures[i] ,CV_CAP_PROP_FRAME_HEIGHT,imageSize.height);
        }


        ready = true;
        return RESULT_OK;
    }else{
        ready = false;
        return RESULT_FAIL;
    }

}

int StereoCamera::capture()
{
    frames[0] = cvQueryFrame(captures[0]);
    frames[1] = cvQueryFrame(captures[1]);
    return (captures[0] && captures[1]) ? RESULT_OK : RESULT_FAIL;
}

IplImage*  StereoCamera::getFramesGray(int lr)
{
    if(!frames[lr]) return 0;
    if(frames[lr]->depth == 1){
        framesGray[lr] = frames[lr];
        return frames[lr];
    }else{
        if(0 == framesGray[lr]) framesGray[lr] = cvCreateImage(cvGetSize(frames[lr]),IPL_DEPTH_8U,1);
        cvCvtColor(frames[lr],framesGray[lr],CV_BGR2GRAY);
        return framesGray[lr];
    }
}

int StereoCamera::checkCamerabase(void){
	struct stat st;
	int i;
	int start_from_4 = 1;
    static char            dev_name[16];

	/* if /dev/video[0-3] exist, camerabase=4, otherwise, camrerabase = 0 */
	for(i=0 ; i<4 ; i++){
		sprintf(dev_name,"/dev/video%d",i);
		if (-1 == stat (dev_name, &st)) {
			start_from_4 &= 0;
		}else{
			start_from_4 &= 1;
		}
	}

	if(start_from_4){
		return 4;
	}else{
		return 0;
	}
}

int StereoCamera::opendevice(int i)
{
	struct stat st;
	char system_call_buffer[100];
    static char            dev_name[16];
    static int             fd;

	sprintf(dev_name,"/dev/video%d",i);

	sprintf(system_call_buffer,"su -c \"chmod 666 %s\"",dev_name);

	int ret = system(system_call_buffer);


	ALOG("This message comes from C at line %d.", 222);
	__android_log_print(ANDROID_LOG_INFO, "foo", "Error: %s", ">>>>>>>>>>>>>>>>>>");


//	if (ret !=0) {
//		LOGE("Could not %s : %d, %s",system_call_buffer, errno, strerror (errno));
//		return ERROR_LOCAL;
//	}
//
//	if (-1 == stat (dev_name, &st)) {
//		LOGE("Cannot identify '%s': %d, %s", dev_name, errno, strerror (errno));
//		return ERROR_LOCAL;
//	}
//
//	if (!S_ISCHR (st.st_mode)) {
//		LOGE("%s is no device", dev_name);
//		return ERROR_LOCAL;
//	}
//
//	fd = -1;
//	fd = open (dev_name, O_RDWR | O_NONBLOCK, 0);
//
//	if (-1 == fd) {
//		LOGE("Cannot open '%s': %d, %s", dev_name, errno, strerror (errno));
//		return ERROR_LOCAL;
//	}
	return SUCCESS_LOCAL;
}
