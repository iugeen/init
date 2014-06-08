/*
 * depthmap.h
 *
 *  Created on: Jun 3, 2014
 *      Author: imocanu
 */

#ifndef DEPTHMAP_H_
#define DEPTHMAP_H_

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

using namespace cv;
using namespace std;

namespace dmap
{

class depthmap
{
public:
	depthmap();
	virtual ~depthmap();
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
};

} /* namespace dmap */
#endif /* DEPTHMAP_H_ */
