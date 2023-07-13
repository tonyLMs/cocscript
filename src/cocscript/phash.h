#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;


/************* 函数声明部分 start ************/

string p_hash(Mat src);    //计算图像的哈希字符串
int hamming(string str1, string str2);// 计算汉明距离
string str_to_hex(string s); // 字符串转16进制
int p_hash_hamming(Mat src1, Mat src2, bool is_open = true);

/************* 函数声明部分 end ************/