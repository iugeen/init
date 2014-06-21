/*
 * depthmap.cpp
 *
 *  Created on: Jun 3, 2014
 *      Author: imocanu
 */

#include "depthmap.h"

namespace dmap {

depthmap::depthmap() {
	// TODO Auto-generated constructor stub

}

depthmap::~depthmap() {
	// TODO Auto-generated destructor stub
}

int depthmap::showDepthMap(IplImage *lg,IplImage *rg, String windowName,
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

        img1 = img1r;
        img2 = img2r;
        //imshow("Left rectified", img1);
        //imshow("Right rectified", img2);
    }

    numberOfDisparities = numberOfDisparities > 0 ? numberOfDisparities : ((img_size.width/8) + 15) & -16;

    bm.state->roi1 = roi1;
    bm.state->roi2 = roi2;
    bm.state->preFilterCap = preFilterCap;
    bm.state->SADWindowSize = SADWindowSizeIn;
    bm.state->minDisparity = minDisparity;
    bm.state->numberOfDisparities = numberOfDisparities;
    bm.state->textureThreshold = textureThreshold;
    bm.state->uniquenessRatio = uniquenessRatio;
    bm.state->speckleWindowSize = speckleWindowSize;
    bm.state->speckleRange = 32;
    bm.state->disp12MaxDiff = 1;

    sgbm.preFilterCap = 63;
    sgbm.SADWindowSize = SADWindowSize > 0 ? SADWindowSize : 3;

    int cn = img1.channels();

    sgbm.P1 = 8*cn*sgbm.SADWindowSize*sgbm.SADWindowSize;
    sgbm.P2 = 32*cn*sgbm.SADWindowSize*sgbm.SADWindowSize;
    sgbm.minDisparity = 0;
    sgbm.numberOfDisparities = numberOfDisparities;
    sgbm.uniquenessRatio = 10;
    sgbm.speckleWindowSize = bm.state->speckleWindowSize;
    sgbm.speckleRange = bm.state->speckleRange;
    sgbm.disp12MaxDiff = 1;
    sgbm.fullDP = alg == STEREO_HH;

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

    if( alg == STEREO_BM )
        bm(img1, img2, disp);
    else if( alg == STEREO_VAR )
    {
        var(img1, img2, disp);
    }
    else if( alg == STEREO_SGBM || alg == STEREO_HH )
        sgbm(img1, img2, disp);
    if( alg != STEREO_VAR )
        disp.convertTo(disp8, CV_8U, 255/(numberOfDisparities*16.));
    else
        disp.convertTo(disp8, CV_8U);
    if( !no_display )
    {
        //imshow(windowName, disp8);
    }


    Mat imgLeft = img1;
    Mat imgRight = img2;
    Mat imgDisparity16S = Mat( imgLeft.rows, imgLeft.cols, CV_16S );
    Mat imgDisparity8U  = Mat( imgLeft.rows, imgLeft.cols, CV_8UC1 );

    if( !imgLeft.data || !imgRight.data )
    { std::cout<< " --(!) Error reading images " << std::endl; return -1; }

    //-- 2. Call the constructor for StereoBM
    int ndisparities = 16*5;   /**< Range of disparity */
   // int SADWindowSize = 21; /**< Size of the block window. Must be odd */

    StereoBM sbm( StereoBM::BASIC_PRESET,
                  ndisparities,
                  21 );

    //-- 3. Calculate the disparity image
    sbm( imgLeft, imgRight, imgDisparity16S, CV_16S );

    //-- Check its extreme values
    double minVal; double maxVal;

    minMaxLoc( imgDisparity16S, &minVal, &maxVal );

    imgDisparity16S.convertTo( imgDisparity8U, CV_8UC1, 255/(maxVal - minVal));

    //namedWindow( "Disparity", WINDOW_NORMAL );
    //imshow( "Disparity", imgDisparity8U );

    return 0;
}

} /* namespace dmap */
