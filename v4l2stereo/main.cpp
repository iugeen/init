/*
    v4l2stereo
    A command line utility for stereoscopic vision
    Copyright (C) 2010 Bob Mottram and Giacomo Spigler
    fuzzgun@gmail.com

    Requires packages:
        libgstreamer-plugins-base0.10-dev
        libgst-dev

    sudo apt-get install libcv2.1 libhighgui2.1 libcvaux2.1 libcv-dev libcvaux-dev libhighgui-dev libgstreamer-plugins-base0.10-dev libgst-dev

    For details of use see:

        http://sluggish.homelinux.net/wiki/Libv4l2cam

    For details of the ELAS dense stereo algorithm see:

        http://rainsoft.de/software/libelas.html

        @INPROCEEDINGS{Geiger10,
        author = {Andreas Geiger and Martin Roser and Raquel Urtasun},
        title = {Efficient Large-Scale Stereo Matching},
        booktitle = {Asian Conference on Computer Vision},
        year = {2010},
        month = {November},
        address = {Queenstown, New Zealand}
        }

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/* enable or disable gstreamer functionality */
//#define GSTREAMER

// ensure that openCV functions are defined within libcam
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
#include <omp.h>
#include <unistd.h>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <stdlib.h>
#include <ctype.h>

#include <cvblobs/Blob.h>
#include <cvblobs/BlobContour.h>
#include <cvblobs/BlobLibraryConfiguration.h>
#include <cvblobs/BlobOperators.h>
#include <cvblobs/BlobProperties.h>
#include <cvblobs/BlobResult.h>
#include <cvblobs/ComponentLabeling.h>

#include "libcam.h"
//#include "stereovision.h"

#define VERSION			1.054

using namespace cv;
using namespace std;

/*!
 * \brief expands a subregion of the given image with pixel interpolation.  It is assumed that the subregion has the same aspect as the original.
 * \param img colour image data
 * \param img_width width of the image
 * \param img_height height of the image
 * \param tx subregion top left x coordinate
 * \param ty subregion top left y coordinate
 * \param bx subregion bottom right x coordinate
 * \param by subregion bottom right y coordinate
 * \param expanded returned expanded image
 */

class WatershedSegmenter{
private:
    cv::Mat markers;
public:
    void setMarkers(cv::Mat& markerImage)
    {
        markerImage.convertTo(markers, CV_32S);
    }

    cv::Mat process(cv::Mat &image)
    {
        cv::watershed(image, markers);
        markers.convertTo(markers,CV_8U);
        return markers;
    }
};

int showDepthMap(IplImage *lg,IplImage *rg, String windowName,
                 int algorithm,
                 int preFilterCap,
                 int SADWindowSizeIn,
                 int minDisparity,
                 int numberOfDisparitiesIn,
                 int textureThreshold,
                 int uniquenessRatio,
                 int speckleWindowSize,
                 int speckleRange)
{

    //printf("preFilterCap: (%d) SADWindowSizeIn: (%d) \n", preFilterCap, SADWindowSizeIn);

    /// ====================== DEPTH MAP ============================ ///

    const char* intrinsic_filename = "/home/imocanu/Test_PHOTO/intrinsics.yml";
    const char* extrinsic_filename = "/home/imocanu/Test_PHOTO/extrinsics.yml";

    enum { STEREO_BM=0, STEREO_SGBM=1, STEREO_HH=2, STEREO_VAR=3 };
    int alg = algorithm; // STEREO_SGBM;
    int SADWindowSize = 0, numberOfDisparities = 0;
    bool no_display = false;
    float scale = 1.f;

    StereoBM bm;
    StereoSGBM sgbm;
    StereoVar var;

    Mat img1(lg);
    Mat img2(rg);

    if( scale != 1.f )
    {
        Mat temp1, temp2;
        int method = scale < 1 ? INTER_AREA : INTER_CUBIC;
        resize(img1, temp1, Size(), scale, scale, method);
        img1 = temp1;
        resize(img2, temp2, Size(), scale, scale, method);
        img2 = temp2;
    }

    Size img_size = img1.size();

    Rect roi1, roi2;
    Mat Q;

    if( true )
    {
        // reading intrinsic parameters
        FileStorage fs(intrinsic_filename, CV_STORAGE_READ);
        if(!fs.isOpened())
        {
            printf("Failed to open file %s\n", intrinsic_filename);
            return -1;
        }

        Mat M1, D1, M2, D2;
        fs["M1"] >> M1;
        fs["D1"] >> D1;
        fs["M2"] >> M2;
        fs["D2"] >> D2;

        M1 *= scale;
        M2 *= scale;

        fs.open(extrinsic_filename, CV_STORAGE_READ);
        if(!fs.isOpened())
        {
            printf("Failed to open file %s\n", extrinsic_filename);
            return -1;
        }

        Mat R, T, R1, P1, R2, P2;
        fs["R"] >> R;
        fs["T"] >> T;

        stereoRectify( M1, D1, M2, D2, img_size, R, T, R1, R2, P1, P2, Q, CALIB_ZERO_DISPARITY, -1, img_size, &roi1, &roi2 );

        Mat map11, map12, map21, map22;
        initUndistortRectifyMap(M1, D1, R1, P1, img_size, CV_16SC2, map11, map12);
        initUndistortRectifyMap(M2, D2, R2, P2, img_size, CV_16SC2, map21, map22);

        Mat img1r, img2r;
        remap(img1, img1r, map11, map12, INTER_LINEAR);
        remap(img2, img2r, map21, map22, INTER_LINEAR);

        //img1 = img1r;
        //img2 = img2r;
        //imshow("Left rectified", img1);
        //imshow("Right rectified", img2);
    }

    numberOfDisparities = numberOfDisparities > 0 ? numberOfDisparities : ((img_size.width/8) + 15) & -16;

///   === DEFAULT VALUES ===
//    preFilterType = StereoBM::PREFILTER_XSOBEL;
//    preFilterSize = 9;
//    preFilterCap = 31;
//    SADWindowSize = _SADWindowSize;
//    minDisparity = 0;
//    numDisparities = _numDisparities > 0 ? _numDisparities : 64;
//    textureThreshold = 10;
//    uniquenessRatio = 15;
//    speckleRange = speckleWindowSize = 0;
//    roi1 = roi2 = Rect(0,0,0,0);
//    disp12MaxDiff = -1;
//    dispType = CV_16S;

    bm.state->roi1 = roi1;
    bm.state->roi2 = roi2;
    bm.state->preFilterCap        = preFilterCap;
    bm.state->SADWindowSize       = SADWindowSizeIn;
    bm.state->minDisparity        = minDisparity;
    bm.state->numberOfDisparities = numberOfDisparities;
    bm.state->textureThreshold    = textureThreshold;
    bm.state->uniquenessRatio     = uniquenessRatio;
    bm.state->speckleWindowSize   = speckleWindowSize;
    bm.state->speckleRange        = speckleRange; // 32
    bm.state->disp12MaxDiff = 1;

//    bm.state->SADWindowSize = 9;
//    bm.state->numberOfDisparities = 112;
//    bm.state->preFilterSize = 5;
//    bm.state->preFilterCap = 61;
//    bm.state->minDisparity = -39;
//    bm.state->textureThreshold = 507;
//    bm.state->uniquenessRatio = 0;
//    bm.state->speckleWindowSize = 0;
//    bm.state->speckleRange = 8;
//    bm.state->disp12MaxDiff = 1;

    //    /// ORIGINAL PARAMETERS
    //    bm.state->roi1 = roi1;
    //    bm.state->roi2 = roi2;
    //    bm.state->preFilterCap = 31;
    //    bm.state->SADWindowSize = SADWindowSize > 0 ? SADWindowSize : 9;
    //    bm.state->minDisparity = 0;
    //    bm.state->numberOfDisparities = numberOfDisparities;
    //    bm.state->textureThreshold = 10;
    //    bm.state->uniquenessRatio = 15;
    //    bm.state->speckleWindowSize = 100;
    //    bm.state->speckleRange = 32;
    //    bm.state->disp12MaxDiff = 1;

    //    CvStereoBMState *BMState = cvCreateStereoBMState();
    //    BMState->preFilterSize=41;
    //    BMState->preFilterCap=31; *
    //    BMState->SADWindowSize=41;
    //    BMState->minDisparity=-64;
    //    BMState->numberOfDisparities=128;
    //    BMState->textureThreshold=10;
    //    BMState->uniquenessRatio=15;


    sgbm.preFilterCap = 63;
    sgbm.SADWindowSize = SADWindowSize > 0 ? SADWindowSize : 3;

    int cn = img1.channels();
//    sgbm.P1 = 8*cn*sgbm.SADWindowSize*sgbm.SADWindowSize;
//    sgbm.P2 = 32*cn*sgbm.SADWindowSize*sgbm.SADWindowSize;
//    sgbm.minDisparity = 0;
//    sgbm.numberOfDisparities = numberOfDisparities;
//    sgbm.uniquenessRatio = 10;
//    sgbm.speckleWindowSize = bm.state->speckleWindowSize;
//    sgbm.speckleRange = bm.state->speckleRange;
//    sgbm.disp12MaxDiff = 1;
//    sgbm.fullDP = alg == STEREO_HH;


    sgbm.SADWindowSize = 5;
    sgbm.numberOfDisparities = 192;
    sgbm.preFilterCap = 4;
    sgbm.minDisparity = -64;
    sgbm.uniquenessRatio = 1;
    sgbm.speckleWindowSize = 150;
    sgbm.speckleRange = 2;
    sgbm.disp12MaxDiff = 10;
    sgbm.fullDP = false;
    sgbm.P1 = 600;
    sgbm.P2 = 2400;

    var.levels = 3;                                 // ignored with USE_AUTO_PARAMS
    var.pyrScale = 0.5;                             // ignored with USE_AUTO_PARAMS
    var.nIt = 25;
    var.minDisp = -numberOfDisparities;
    var.maxDisp = 0;
    var.poly_n = 3;
    var.poly_sigma = 0.0;
    var.fi = 15.0f;
    var.lambda = 0.03f;
    var.penalization = var.PENALIZATION_TICHONOV;   // ignored with USE_AUTO_PARAMS
    var.cycle = var.CYCLE_V;                        // ignored with USE_AUTO_PARAMS
    var.flags = var.USE_SMART_ID | var.USE_AUTO_PARAMS | var.USE_INITIAL_DISPARITY | var.USE_MEDIAN_FILTERING ;

    Mat disp, disp8;
    //Mat img1p, img2p, dispp;
    //copyMakeBorder(img1, img1p, 0, 0, numberOfDisparities, 0, IPL_BORDER_REPLICATE);
    //copyMakeBorder(img2, img2p, 0, 0, numberOfDisparities, 0, IPL_BORDER_REPLICATE);

    //int64 t = getTickCount();
    if( alg == STEREO_BM )
        bm(img1, img2, disp);
    else if( alg == STEREO_VAR )
    {
        var(img1, img2, disp);
    }
    else if( alg == STEREO_SGBM || alg == STEREO_HH )
        sgbm(img1, img2, disp);
    //t = getTickCount() - t;
    //printf("Time elapsed: %fms\n", t*1000/getTickFrequency());

    //disp = dispp.colRange(numberOfDisparities, img1p.cols);
    Mat dst;

    if( alg != STEREO_VAR )
    {

        disp.convertTo(disp8, CV_8U, 255/(numberOfDisparities*16.));
        if( alg == STEREO_BM )
        {

            cv::Mat element(7,7,CV_8U,cv::Scalar(1));
            erode(disp8, dst, element);
            imshow("ERODE", dst);


            cv::Mat bg;
            cv::dilate(dst,bg,cv::Mat(),cv::Point(-1,-1),3);
            cv::threshold(bg,bg,1, 128,cv::THRESH_BINARY_INV);
            imshow("DILATE", bg);

        }
    }
    else
    {
        disp.convertTo(disp8, CV_8U);
    }
    if( !no_display )
    {
        imshow(windowName, disp8);
    }




/// FAKE COLOR DEPTH MAP
//    double min = 100;
//    double max = 255;
//    cv::minMaxIdx(disp8, &min, &max);
    cv::Mat adjMap, dest2, dest3;
//    // expand your range to 0..255. Similar to histEq();
//    disp8.convertTo(adjMap,CV_8UC1, 255 / (max-min), -min);
//    // this is great. It converts your grayscale image into a tone-mapped one,
//    // much more pleasing for the eye
//    // function is found in contrib module, so include contrib.hpp
//    // and link accordingly
//    cv::Mat falseColorsMap, res;
//    applyColorMap(adjMap, falseColorsMap, cv::COLORMAP_AUTUMN);
//    //cv::imshow("Out", falseColorsMap);
//    pyrMeanShiftFiltering( falseColorsMap, res, 10, 35, 3);
//    cv::imshow("MS alg", res);

    medianBlur(dst, dest2, 19);
    imshow("MEDIAN BLUR", dest2);

//    imwrite( "/home/imocanu/median.png", dest2);

    threshold(dest2, dest3, 100, 255,0 );

    imshow("BINARY MAP", dest3);

//    cv::Mat fg;
//    cv::erode(dest3,fg,cv::Mat(),cv::Point(-1,-1),2);
//    imshow("fg", fg);

    cv::Mat bg;
    cv::dilate(dest3,bg,cv::Mat(),cv::Point(-1,-1),3);
    cv::threshold(bg,bg,1, 128,cv::THRESH_BINARY_INV);
    imshow("bg", bg);

//    cv::Mat markers(dest3.size(),CV_8U,cv::Scalar(0));
//        markers= fg+bg;
//        imshow("markers", markers);

//        // Create watershed segmentation object
//           WatershedSegmenter segmenter;
//           segmenter.setMarkers(markers);

//           cv::Mat result = segmenter.process(img1);
//           result.convertTo(result,CV_8U);
//           imshow("final_result", result);


//    //imwrite( "/home/imocanu/colormap.png", falseColorsMap);


    Mat imgLeft = img1;
    Mat imgRight = img2;
    //-- And create the image in which we will save our disparities
    Mat imgDisparity16S = Mat( imgLeft.rows, imgLeft.cols, CV_16S );
    Mat imgDisparity8U = Mat( imgLeft.rows, imgLeft.cols, CV_8UC1 );

    if( !imgLeft.data || !imgRight.data )
    { std::cout<< " --(!) Error reading images " << std::endl; return -1; }

    //-- 2. Call the constructor for StereoBM
    int ndisparities = 16*5;   /**< Range of disparity */
    // int SADWindowSize = 21; /**< Size of the block window. Must be odd */

    StereoBM sbm( StereoBM::BASIC_PRESET,
                  ndisparities,  // ndisparities
                  21 );

    //-- 3. Calculate the disparity image
    sbm( imgLeft, imgRight, imgDisparity16S, CV_16S );

    //-- Check its extreme values
    double minVal; double maxVal;

    minMaxLoc( imgDisparity16S, &minVal, &maxVal );

    //printf("Min disp: %f Max value: %f \n", minVal, maxVal);

    //-- 4. Display it as a CV_8UC1 image
    imgDisparity16S.convertTo( imgDisparity8U, CV_8UC1, 255/(maxVal - minVal));

    namedWindow( "Disparity", WINDOW_NORMAL );
    imshow( "Disparity", imgDisparity8U );



//    IplImage *dispIpl = new IplImage(dest3);   //create an IplImage from Mat - imgDisparity8U

//    //Declare variables
//    CBlobResult blobs;
//    CBlob *currentBlob;
//    int minArea = 1000;


//    blobs = CBlobResult(dispIpl, NULL,0);  //get all blobs in the disparity map
//    blobs.Filter( blobs, B_EXCLUDE, CBlobGetArea(), B_LESS, minArea ); //filter blobs by area and remove all less than minArea

//    //Display blobs
//    IplImage *displayedImage = cvCreateImage(Size(320,240),8,3); //create image for outputting blobs
//    for (int i = 0; i < blobs.GetNumBlobs(); i++ )
//    {
//        currentBlob = blobs.GetBlob(i);
//        Scalar color( rand() &255, rand() &255, rand() &255 );
//        currentBlob->FillBlob( displayedImage, color);
//    }
//    Mat displayImage = displayedImage; //Convert to Mat for use in imshow()

//    if(alg == 1)
//    {
//        imshow("=========> Blobs", displayImage);
//    }

//    imshow( "BLOBS", displayImage );


    return 0;
}


int main(int argc, char* argv[])
{
    int ww = 320;
    int hh = 240;
    int fps = 60;
    int skip_frames = 400;
    int grab_timeout_ms = 1000;

    std::string dev0 = "/dev/video2";
    std::string dev1 = "/dev/video1";

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
    const float squareSize = 2.5f;  // Set this to your actual square size
    // ARRAY AND VECTOR STORAGE:

    vector<vector<Point2f> > imagePoints[2];
    vector<vector<Point3f> > objectPoints;
    Size imageSize;

    int i = 0, j = 0, k, nimages = 5;  // nr de perechi

    imagePoints[0].resize(nimages);
    imagePoints[1].resize(nimages);
    vector<IplImage*> goodImageList;

    bool useCalibrated=false;
    bool showRectified=true;
    bool isVerticalStereo  = true;

    Mat rmap[2][2];
    Rect validRoi[2];


    bool finalCalibrated  = false;
    bool startCalibration = false;

    system("rm /home/imocanu/Test_PHOTO/*.jpg");

    int preFilterCap  = 5;
    int SADWindowSize = 21;
    int minDisparity  = -100;
    int numberOfDisparities = 16;
    int textureThreshold  = 2;
    int uniquenessRatio = 6;
    int speckleWindowSize  = 100;
    int speckleRange = 32;

    Mat img1(lg);
    Mat img = img1;
    imshow("Filters", img);

    cvCreateTrackbar("preFilterCap","Filters",         &preFilterCap, 62,NULL);
    cvCreateTrackbar("SADWindowSize","Filters",        &SADWindowSize,255,NULL);
    cvCreateTrackbar("minDisparity","Filters",         &minDisparity, 100,NULL);
    cvCreateTrackbar("numberOfDisparities","Filters",  &numberOfDisparities, 256,NULL);
    cvCreateTrackbar("textureThreshold","Filters",     &textureThreshold, 32000,NULL);
    cvCreateTrackbar("uniquenessRatio","Filters",      &uniquenessRatio, 255,NULL);
    cvCreateTrackbar("speckleWindowSize","Filters",    &speckleWindowSize, 100,NULL);
    cvCreateTrackbar("speckleRange","Filters",         &speckleRange, 100,NULL);

    bool nextPicture = false;

    while(1)
    {
        if (!c.Update(&c2, 25, grab_timeout_ms))
        {
            printf("Failed to acquire images\n");
            break;
        }

        c.toIplImage(l);
        c2.toIplImage(r);

        cvCvtColor(l, lg, CV_BGR2GRAY);
        cvCvtColor(r, rg, CV_BGR2GRAY);

                 Mat img1(lg);
                 Mat img = img1;
                 imshow("Filters", img);


        //         Mat imgColorLeft(l);
        //         imwrite( "/home/imocanu/Test_PHOTO_l.jpg", imgColorLeft);
        //         Mat imgColorRight(r);
        //         imwrite( "/home/imocanu/Test_PHOTO_r.jpg", imgColorRight);

        if(i < nimages && startCalibration)
        {

//                for( k = 0; k < 2; k++ )
//                {
//                    //const string& filename = imagelist[i*2+k];

//                    Mat img;

//                    if(k == 0)
//                    {
//                        Mat img1(lg);
//                        img = img1;
//                        //imwrite( "/home/imocanu/lg.jpg", img );
//                    }
//                    else if(k == 1)
//                    {
//                        Mat img1(rg);
//                        img = img1;
//                        //imwrite( "/home/imocanu/rg.jpg", img );
//                    }

//                    if(img.empty())
//                    {
//                        break;
//                    }
//                    if( imageSize == Size() )
//                    {
//                        imageSize = img.size();
//                    }
//                    else if( img.size() != imageSize )
//                    {
//                        //cout << "The image " << filename << " has the size different from the first image size. Skipping the pair\n";
//                        break;
//                    }
//                    bool found = false;
//                    vector<Point2f>& corners = imagePoints[k][j];
//                    for( int scale = 1; scale <= maxScale; scale++ )
//                    {
//                        Mat timg;
//                        if( scale == 1 )
//                            timg = img;
//                        else
//                            resize(img, timg, Size(), scale, scale);

//                        found = findChessboardCorners(timg, boardSize, corners,
//                                                      CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_NORMALIZE_IMAGE);

//                        if( found )
//                        {
//                            if( scale > 1 )
//                            {
//                                Mat cornersMat(corners);
//                                cornersMat *= 1./scale;
//                            }
//                            break;
//                        }
//                    }
//                    if( displayCorners )
//                    {
//                        Mat cimg, cimg1;
//                        cvtColor(img, cimg, COLOR_GRAY2BGR);
//                        drawChessboardCorners(cimg, boardSize, corners, found);
//                        double sf = 320./MAX(img.rows, img.cols);
//                        resize(cimg, cimg1, Size(), sf, sf);
//                        imshow("corners", cimg1);
//                        char c = (char)waitKey(800);
//                        if( c == 'q' || c == 'Q' )
//                        { //Allow ESC to quit
//                            exit(-1);
//                        }
//                        else if( c == 27 )
//                        {
//                            nextPicture = true;
//                            printf(">> APASAT >>>\n");
//                        }
//                    }
//                    else
//                        putchar('.');

//                    if( !found )
//                    {
//                        break;
//                    }

//                    cornerSubPix(img, corners, Size(11,11), Size(-1,-1),
//                                 TermCriteria(CV_TERMCRIT_ITER+CV_TERMCRIT_EPS,
//                                              30, 0.01));
//                }

//            if( k == 2  && nextPicture)
//            {
//                Mat img;

//                std::string pathL, pathR;
//                std::string s = std::to_string(i);
//                pathL.append("/home/imocanu/Test_PHOTO/lg");
//                pathL.append(s);
//                pathL.append(".jpg");

//                pathR.append("/home/imocanu/Test_PHOTO/rg");
//                pathR.append(s);
//                pathR.append(".jpg");

//                Mat img1(lg);
//                img = img1;
//                imwrite( pathL , img );

//                Mat img2(rg);
//                img = img2;
//                imwrite( pathR , img );

//                goodImageList.push_back(lg);
//                goodImageList.push_back(rg);
//                printf("###############################################################################################################\n");
//                j++;
//                i++;
//                nextPicture = false;
//            }
            printf("good images .......... (%d) - total (%d) \n", j, i);
        }

        else
        {


//            ////             * Fundamental Matrix F
//            ////             * Camera Matrices left/right CM1 CM2
//            ////             * Distortion Coefficients for Camera left/right DIST1 DIST2
//            ////             * Rotation Matrix from cvStereoCalibrate R
//            ////             * translation vector from cvStereoCalibrate T
//            ////             * Reprojection Matrix Q from cvStereoRectify
//            ////             * rectified rotation matrix for left camera R1
//            ////             * rectified rotation matrix for right camera R2
//            ////             * projection equation matrix for left image P1
//            ////             * projection equation matrix for right image P1
//            ////             * undistorted pointlist for left image POINTS1
//            ////             * corresponding undistorted pointlist for right image POINTS2

//            if(finalCalibrated)
//            {
//                printf("====> %d pairs have been successfully detected.\n", j);
//                nimages = j;

//                imagePoints[0].resize(nimages);
//                imagePoints[1].resize(nimages);
//                objectPoints.resize(nimages);

//                for( i = 0; i < nimages; i++ )
//                {
//                    for( j = 0; j < boardSize.height; j++ )
//                        for( k = 0; k < boardSize.width; k++ )
//                            objectPoints[i].push_back(Point3f(j*squareSize, k*squareSize, 0));
//                }

//                cout << "Running stereo calibration ...\n";

//                Mat cameraMatrix[2], distCoeffs[2];
//                cameraMatrix[0] = Mat::eye(3, 3, CV_64F);
//                cameraMatrix[1] = Mat::eye(3, 3, CV_64F);
//                Mat R, T, E, F;
//                Mat iSize(lg);
//                imageSize = iSize.size();

//                double rms = stereoCalibrate(objectPoints, imagePoints[0], imagePoints[1],
//                        cameraMatrix[0], distCoeffs[0],
//                        cameraMatrix[1], distCoeffs[1],
//                        imageSize, R, T, E, F,
//                        TermCriteria(CV_TERMCRIT_ITER+CV_TERMCRIT_EPS, 100, 1e-5),
//                        CV_CALIB_FIX_ASPECT_RATIO +
//                        CV_CALIB_ZERO_TANGENT_DIST +
//                        CV_CALIB_SAME_FOCAL_LENGTH +
//                        CV_CALIB_RATIONAL_MODEL +
//                        CV_CALIB_FIX_K3 + CV_CALIB_FIX_K4 + CV_CALIB_FIX_K5);
//                cout << "done with RMS error=" << rms << endl;

//                // CALIBRATION QUALITY CHECK
//                // because the output fundamental matrix implicitly
//                // includes all the output information,
//                // we can check the quality of calibration using the
//                // epipolar geometry constraint: m2^t*F*m1=0
//                double err = 0;
//                int npoints = 0;
//                vector<Vec3f> lines[2];
//                for( i = 0; i < nimages; i++ )
//                {
//                    int npt = (int)imagePoints[0][i].size();
//                    Mat imgpt[2];
//                    for( k = 0; k < 2; k++ )
//                    {
//                        imgpt[k] = Mat(imagePoints[k][i]);
//                        undistortPoints(imgpt[k], imgpt[k], cameraMatrix[k], distCoeffs[k], Mat(), cameraMatrix[k]);
//                        computeCorrespondEpilines(imgpt[k], k+1, F, lines[k]);
//                    }
//                    for( j = 0; j < npt; j++ )
//                    {
//                        double errij = fabs(imagePoints[0][i][j].x*lines[1][j][0] +
//                                imagePoints[0][i][j].y*lines[1][j][1] + lines[1][j][2]) +
//                                fabs(imagePoints[1][i][j].x*lines[0][j][0] +
//                                imagePoints[1][i][j].y*lines[0][j][1] + lines[0][j][2]);
//                        err += errij;
//                    }
//                    npoints += npt;
//                }
//                cout << "average reprojection err = " <<  err/npoints << endl;


//                // save intrinsic parameters
//                FileStorage fs("intrinsics.yml", CV_STORAGE_WRITE);
//                if( fs.isOpened() )
//                {
//                    fs << "M1" << cameraMatrix[0] << "D1" << distCoeffs[0] <<
//                          "M2" << cameraMatrix[1] << "D2" << distCoeffs[1];
//                    fs.release();
//                }
//                else
//                    cout << "Error: can not save the intrinsic parameters\n";

//                system("cp intrinsics.yml /home/imocanu/Test_PHOTO");

//                Mat R1, R2, P1, P2, Q;
//                //Rect validRoi[2];

//                stereoRectify(cameraMatrix[0], distCoeffs[0],
//                        cameraMatrix[1], distCoeffs[1],
//                        imageSize, R, T, R1, R2, P1, P2, Q,
//                        CALIB_ZERO_DISPARITY, 1, imageSize, &validRoi[0], &validRoi[1]);

//                fs.open("extrinsics.yml", CV_STORAGE_WRITE);
//                if( fs.isOpened() )
//                {
//                    fs << "R" << R << "T" << T << "R1" << R1 << "R2" << R2 << "P1" << P1 << "P2" << P2 << "Q" << Q;
//                    fs.release();
//                }
//                else
//                    cout << "Error: can not save the intrinsic parameters\n";

//                system("cp extrinsics.yml /home/imocanu/Test_PHOTO");

//                // OpenCV can handle left-right
//                // or up-down camera arrangements
//                isVerticalStereo = fabs(P2.at<double>(1, 3)) > fabs(P2.at<double>(0, 3));

//                // COMPUTE AND DISPLAY RECTIFICATION
//                if( !showRectified )
//                {
//                    exit(1);
//                }

//                //    Mat rmap[2][2];
//                // IF BY CALIBRATED (BOUGUET'S METHOD)
//                if( useCalibrated )
//                {
//                    // we already computed everything
//                }
//                // OR ELSE HARTLEY'S METHOD
//                else
//                    // use intrinsic parameters of each camera, but
//                    // compute the rectification transformation directly
//                    // from the fundamental matrix
//                {
//                    vector<Point2f> allimgpt[2];
//                    for( k = 0; k < 2; k++ )
//                    {
//                        for( i = 0; i < nimages; i++ )
//                            std::copy(imagePoints[k][i].begin(), imagePoints[k][i].end(), back_inserter(allimgpt[k]));
//                    }
//                    F = findFundamentalMat(Mat(allimgpt[0]), Mat(allimgpt[1]), FM_8POINT, 0, 0);
//                    Mat H1, H2;
//                    stereoRectifyUncalibrated(Mat(allimgpt[0]), Mat(allimgpt[1]), F, imageSize, H1, H2, 3);

//                    R1 = cameraMatrix[0].inv()*H1*cameraMatrix[0];
//                    R2 = cameraMatrix[1].inv()*H2*cameraMatrix[1];
//                    P1 = cameraMatrix[0];
//                    P2 = cameraMatrix[1];
//                }

//                //Precompute maps for cv::remap()
//                initUndistortRectifyMap(cameraMatrix[0], distCoeffs[0], R1, P1, imageSize, CV_16SC2, rmap[0][0], rmap[0][1]);
//                initUndistortRectifyMap(cameraMatrix[1], distCoeffs[1], R2, P2, imageSize, CV_16SC2, rmap[1][0], rmap[1][1]);

//                finalCalibrated = false;
//            }

//            Mat canvas;
//            double sf;
//            int w, h;
//            if( !isVerticalStereo )
//            {
//                sf = 320./MAX(imageSize.width, imageSize.height);
//                w = cvRound(imageSize.width*sf);
//                h = cvRound(imageSize.height*sf);
//                canvas.create(h, w*2, CV_8UC3);
//            }
//            else
//            {
//                sf = 240./MAX(imageSize.width, imageSize.height);
//                w = cvRound(imageSize.width*sf);
//                h = cvRound(imageSize.height*sf);
//                canvas.create(h*2, w, CV_8UC3);
//            }

//            Mat rectifLeft;
//            Mat rectitRight;

//            for( k = 0; k < 2; k++ )
//            {
//                Mat rimg, cimg;

//                Mat img;
//                if(k == 0)
//                {
//                    Mat img1(lg);
//                    img = img1;
//                    rectifLeft = img1;
//                    cvShowImage("lg", lg);

//                }
//                else
//                {
//                    Mat img1(rg);
//                    img = img1;
//                    rectitRight = img1;
//                    cvShowImage("rg", rg);

//                }

//                remap(img, rimg, rmap[k][0], rmap[k][1], CV_INTER_LINEAR);
//                cvtColor(rimg, cimg, COLOR_GRAY2BGR);
//                Mat canvasPart = !isVerticalStereo ? canvas(Rect(w*k, 0, w, h)) : canvas(Rect(0, h*k, w, h));
//                resize(cimg, canvasPart, canvasPart.size(), 0, 0, CV_INTER_AREA);
//                if(k == 0)
//                {
//                    imshow("Part LEFT", canvasPart);
//                }
//                else
//                {
//                    imshow("Part RIGHT", canvasPart);
//                }
//                //                 if( useCalibrated )
//                //                 {
//                Rect vroi(cvRound(validRoi[k].x*sf), cvRound(validRoi[k].y*sf),
//                          cvRound(validRoi[k].width*sf), cvRound(validRoi[k].height*sf));
//                rectangle(canvasPart, vroi, Scalar(0,0,255), 3, 8);
//                //                 }
//            }

//            if( !isVerticalStereo )
//                for( j = 0; j < canvas.rows; j += 16 )
//                    line(canvas, Point(0, j), Point(canvas.cols, j), Scalar(0, 255, 0), 1, 8);
//            else
//                for( j = 0; j < canvas.cols; j += 16 )
//                    line(canvas, Point(j, 0), Point(j, canvas.rows), Scalar(0, 255, 0), 1, 8);


//            imshow("rectified", canvas);

                         showDepthMap(lg, rg, "STEREO BM", 0,
                                      preFilterCap,
                                      SADWindowSize,
                                      minDisparity,
                                      numberOfDisparities,
                                      textureThreshold,
                                      uniquenessRatio,
                                      speckleWindowSize,
                                      speckleRange);

//                         showDepthMap(lg, rg, "STEREO SGBM", 1,
//                                      preFilterCap,
//                                      SADWindowSize,
//                                      minDisparity,
//                                      numberOfDisparities,
//                                      textureThreshold,
//                                      uniquenessRatio,
//                                      speckleWindowSize,
//                                      speckleRange);


//            showDepthMap(lg, rg, "STEREO SGBM", 1, preFilterCap, SADWindowSize);
//            showDepthMap(lg, rg, "STEREO HH",   2, preFilterCap, SADWindowSize);
//            showDepthMap(lg, rg, "STEREO VAR",  3, preFilterCap, SADWindowSize);

        }
        skip_frames--;
        if (skip_frames < 0) skip_frames = 0;

        int wait = cvWaitKey(10) & 255;

        if( wait == 27 )
        {
            break;
        }
    }

    return 0;
}
