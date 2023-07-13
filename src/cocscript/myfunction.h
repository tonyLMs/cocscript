#pragma once
#include "headfile.h"
#include "enum_sum.h"

QImage* QPixmap_To_Mat(QPixmap pix, cv::Mat& mat);

bool Is_jiaozhun_Area(QPoint jiaozhun_point, cv::Mat jiaozhun_png, int temp_x = -1, int temp_y = -1,int m = NORMAL);