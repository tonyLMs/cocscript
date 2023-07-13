#pragma once
#include <opencv2/opencv.hpp>
#include <Windows.h>
#include <cstdlib>
#include <fstream>
#include <QDebug>
#include <sstream>

bool Compare_Mat_Text(cv::Mat mat, QString text, bool fight_jiaozhun = false, bool is_black = true);

void Get_Mat_Number(cv::Mat mat, long(&arr)[3]);

void myShellExecute(LPCTSTR lpOperation, LPCTSTR lpFile, LPCTSTR lpParameters, INT nShowCmd);