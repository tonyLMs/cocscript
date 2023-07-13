#pragma once

#include <opencv2/opencv.hpp>

using namespace cv;

//0~1 越接近1说明越相近
double compareHist(Mat src1, Mat src2);