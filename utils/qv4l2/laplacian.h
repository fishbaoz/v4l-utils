#ifndef __LAPLACIAN_H__
#define __LAPLACIAN_H__

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <laplacian.h>

using namespace cv;
using namespace std;

void edgeEnhance(cv::Mat& srcImg, cv::Mat& dstImg);

#endif
