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
	//����1 ָ������
	//����2 �������м���ͼƬ
	//����3 ͨ����0-1��
	//����4 ���
	//����5 ���������ͨ��ֱ��ͼ
	//����6 ���ÿ��ά�ȵ�ֱ��ͼ�ߴ�����顣
	//����7 ͨ�����ص�ȡֵ��Χ
	Mat hist1, hist2;
	calcHist(&hsv1, 1, channels, Mat(), hist1, 2, histSize, ranges, true, false);
	calcHist(&hsv2, 1, channels, Mat(), hist2, 2, histSize, ranges, true, false);

	//��һ��
	normalize(hist1, hist1, 0, 1, NORM_MINMAX, -1, Mat());
	normalize(hist2, hist2, 0, 1, NORM_MINMAX, -1, Mat());

	double src1_src2 = compareHist(hist1, hist2, 0);
	return src1_src2;
}