#ifndef STEREOVISION_H
#define STEREOVISION_H

#include <opencv/cv.h>
#include <opencv/cxmisc.h>
#include <opencv/cvaux.h>
#include <opencv/highgui.h>

#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/contrib/contrib.hpp"

#include <stdio.h>
#include <vector>

#define RESULT_OK   0
#define RESULT_FAIL 1

using namespace cv;
using namespace std;

class StereoVision
{
private:
    //chesboard board corners X,Y, N = X*Y ,  number of corners = (number of cells - 1)
    int cornersX,cornersY,cornersN;
    int sampleCount;
    bool calibrationStarted;
    bool calibrationDone;

    CvSize imageSize;
    int imageWidth;
    int imageHeight;

    vector<CvPoint2D32f> ponintsTemp[2];
    vector<CvPoint3D32f> objectPoints;
    vector<CvPoint2D32f> points[2];
    vector<int> npoints;

public:
    StereoVision(int imageWidth,int imageHeight);
    ~StereoVision();

    //matrices resulting from calibration (used for cvRemap to rectify images)
    CvMat *mx1,*my1,*mx2,*my2;

    CvMat* imagesRectified[2];
    CvMat  *imageDepth,*imageDepthNormalized;

    void calibrationStart(int cornersX,int cornersY);
    int calibrationAddSample(IplImage* imageLeft,IplImage* imageRight);
    int calibrationEnd();

    int calibrationSave(const char* filename);
    int calibrationLoad(const char* filename);

    int stereoProcess(CvArr* imageSrcLeft,CvArr* imageSrcRight, IplImage* imageRgbLeft,IplImage* imageRgbRight);

    CvSize getImageSize(){return imageSize;}
    bool getCalibrationStarted(){return calibrationStarted;}
    bool getCalibrationDone(){return calibrationDone;}
    int getSampleCount(){return sampleCount;}

};

#endif // STEREOVISION_H
