#define USE_OPENCV

#include <iostream>
#include <opencv/cv.h>
#include <opencv/cxmisc.h>
#include <opencv/cvaux.h>
#include <opencv/highgui.h>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/contrib/contrib.hpp>

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

#include "libcam.h"

#define VERSION			1.0

using namespace cv;
using namespace std;


int main(int argc, char* argv[])
{
     char system_call_buffer[50];
     sprintf(system_call_buffer,"su -c \"chmod 666 %s\"",  dev0.c_str());
     system(system_call_buffer);

     char system_call_bufferSecond[50];
     sprintf(system_call_bufferSecond,"su -c \"chmod 666 %s\"",  dev1.c_str());
     system(system_call_bufferSecond);

     Camera c(dev0.c_str(), ww, hh, fps);
     Camera c2(dev1.c_str(), ww, hh, fps);

     IplImage *l=cvCreateImage(cvSize(ww, hh), 8, 3);
     IplImage *r=cvCreateImage(cvSize(ww, hh), 8, 3);

     IplImage *lg=cvCreateImage(cvGetSize(l),IPL_DEPTH_8U,1);
     IplImage *rg=cvCreateImage(cvGetSize(r),IPL_DEPTH_8U,1);

     Size boardSize;
     boardSize = Size(9, 6);

     bool displayCorners = true;//true;
     const int maxScale = 2;
     const float squareSize = 1.f;  // Set this to your actual square size
     // ARRAY AND VECTOR STORAGE:

     vector<vector<Point2f> > imagePoints[2];
     vector<vector<Point3f> > objectPoints;
     Size imageSize;

     int i = 0, j = 0, k, nimages = 30;  // nr de perechi

     imagePoints[0].resize(nimages);
     imagePoints[1].resize(nimages);
     vector<IplImage*> goodImageList;

     bool useCalibrated=false;
     bool showRectified=true;
     bool isVerticalStereo  = true;

     Mat rmap[2][2];
     Rect validRoi[2];

     bool finalCalibrated  = true;
     bool startCalibration = true;

     while(1)
     {
         if (!c.Update(&c2, 50, grab_timeout_ms))
         {
             printf("Failed to acquire images\n");
             break;
         }

         c.toIplImage(l);
         c2.toIplImage(r);

         skip_frames--;
         if (skip_frames < 0) skip_frames = 0;
         int wait = cvWaitKey(1) & 255;

         if( wait == 27 )
         {
             break;
         }
     }

    return 0;
}
