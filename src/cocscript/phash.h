#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;


/************* ������������ start ************/

string p_hash(Mat src);    //����ͼ��Ĺ�ϣ�ַ���
int hamming(string str1, string str2);// ���㺺������
string str_to_hex(string s); // �ַ���ת16����
int p_hash_hamming(Mat src1, Mat src2, bool is_open = true);

/************* ������������ end ************/