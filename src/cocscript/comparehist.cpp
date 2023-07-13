#include "comparehist.h"

double compareHist(Mat src1, Mat src2)
{
	Mat hsv1, hsv2;
	cvtColor(src1, hsv1, COLOR_BGR2HSV);
	cvtColor(src2, hsv2, COLOR_BGR2HSV);

	int h_bins = 60; int s_bins = 64;
	int histSize[] = { h_bins, s_bins };
	float h_ranges[] = { 0, 180 };
	float s_ranges[] = { 0, 256 };
	const float* ranges[] = { h_ranges, s_ranges };
	int channels[] = { 0, 1 };
	//参数1 指针引用
	//参数2 数组中有几个图片
	//参数3 通道（0-1）
	//参数4 输出
	//参数5 计算的两个通道直方图
	//参数6 存放每个维度的直方图尺寸的数组。
	//参数7 通道像素的取值范围
	Mat hist1, hist2;
	calcHist(&hsv1, 1, channels, Mat(), hist1, 2, histSize, ranges, true, false);
	calcHist(&hsv2, 1, channels, Mat(), hist2, 2, histSize, ranges, true, false);

	//归一化
	normalize(hist1, hist1, 0, 1, NORM_MINMAX, -1, Mat());
	normalize(hist2, hist2, 0, 1, NORM_MINMAX, -1, Mat());

	double src1_src2 = compareHist(hist1, hist2, 0);
	return src1_src2;
}