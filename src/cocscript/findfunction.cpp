#include "cocscript.h"

QPoint cocscript::Find_SmallMat(cv::Mat icon, cv::Mat target, double w, std::pair<cv::Mat, int> jiaozhun_mat, std::pair<cv::Mat, int> jiaozhun_mat2, bool doublehelp, bool is_open_phash)
{
	int now_x = -1, now_y = -1;
	double s_max = 0;

	QPoint jiaozhun_point(-1, -1);
	QPoint jiaozhun_point2(-1, -1);

	//捐兵校准
	if (!jiaozhun_mat.first.empty())
	{
		jiaozhun_point = Find_SmallMat(jiaozhun_mat.first, target, 0.9);
	}

	if (!jiaozhun_mat2.first.empty())
	{
		jiaozhun_point2 = Find_SmallMat(jiaozhun_mat2.first, target, 0.9);
	}

	for (int x_temp = 0; x_temp < target.cols - icon.cols; x_temp += 10)
	{
		for (int y_temp = 0; y_temp < target.rows - icon.rows; y_temp += 10)
		{
			if (!jiaozhun_mat.first.empty() && Is_jiaozhun_Area(jiaozhun_point, jiaozhun_mat.first, x_temp, y_temp, jiaozhun_mat.second))
			{
				continue;
			}

			if (!jiaozhun_mat2.first.empty() && Is_jiaozhun_Area(jiaozhun_point2, jiaozhun_mat2.first, x_temp, y_temp, jiaozhun_mat2.second))
			{
				continue;
			}

			if (!doublehelp || (!(y_temp >= lasttime.first.y() - lasttime.second.height() / 4 && y_temp <= lasttime.first.y() + lasttime.second.height() / 4 && x_temp >= lasttime.first.x() - lasttime.second.width() / 4 && x_temp <= lasttime.first.x() + lasttime.second.width() / 4)))
			{
				cv::Mat temp(target, Rect(x_temp, y_temp, icon.cols, icon.rows));
				double s = compareHist(icon, temp);
				if ((s > s_max && s > w) || (s == 1 || p_hash_hamming(icon, temp, is_open_phash) == 0))
				{
					s_max = s;
					now_x = x_temp;
					now_y = y_temp;
					//利用文字识别加速
					if (doublehelp && Compare_Mat_Text(temp, "增援"))
					{
						goto flag;
					}
				}
			}

		}
	}
	flag:
	QPoint p(now_x, now_y);
	if (doublehelp)
	{
		this->lasttime.first = p;
		this->lasttime.second = QSize(icon.cols, icon.rows);
	}
	return p;
}

QPoint cocscript::Find_SmallMat(cv::Mat icon, cv::Mat target, QString text, double w,bool fight_jiaozhun,bool is_black)
{
	int now_x = -1, now_y = -1;

	for (int x_temp = 0; x_temp < target.cols - icon.cols; x_temp += 10)
	{
		for (int y_temp = 0; y_temp < target.rows - icon.rows; y_temp += 10)
		{
			cv::Mat temp(target, Rect(x_temp, y_temp, icon.cols, icon.rows));
			double s = compareHist(icon, temp);
			if (s > w && Compare_Mat_Text(temp, text, fight_jiaozhun,is_black))
			{
				now_x = x_temp;
				now_y = y_temp;
				goto flag;
			}
		}
	}
	flag:
	QPoint p(now_x, now_y);
	return p;
}

QPoint cocscript::Find_SmallMat(cv::Mat icon, cv::Mat target, double w, QString text, std::pair<cv::Mat, int> jiaozhun_mat)
{
	int now_x = -1, now_y = -1;
	double s_max = 0;

	QPoint jiaozhun_point(-1, -1);
	QPoint jiaozhun_point2(-1, -1);

	//捐兵校准
	if (!jiaozhun_mat.first.empty())
	{
		jiaozhun_point = Find_SmallMat(jiaozhun_mat.first, target, text, 0.8);
	}

	for (int x_temp = 0; x_temp < target.cols - icon.cols; x_temp += 10)
	{
		for (int y_temp = 0; y_temp < target.rows - icon.rows; y_temp += 10)
		{
			if (!jiaozhun_mat.first.empty() && Is_jiaozhun_Area(jiaozhun_point, jiaozhun_mat.first, x_temp, y_temp, jiaozhun_mat.second))
			{
				continue;
			}

			cv::Mat temp(target, Rect(x_temp, y_temp, icon.cols, icon.rows));
			double s = compareHist(icon, temp);
			if ((s > s_max && s > w) || (s == 1 || p_hash_hamming(icon, temp) == 0))
			{
				s_max = s;
				now_x = x_temp;
				now_y = y_temp;
			}

		}
	}
	QPoint p(now_x, now_y);
	return p;
}

QPoint cocscript::Find_SmallMat(cv::Mat icon, cv::Mat target, QPoint boundary, double w)
{
	int now_x = -1, now_y = -1;
	double s_max = 0;

	for (int x_temp = 0; x_temp < target.cols - icon.cols && x_temp < boundary.x(); x_temp += 10)
	{
		for (int y_temp = 0; y_temp < target.rows - icon.rows && y_temp < boundary.y(); y_temp += 10)
		{
			cv::Mat temp(target, Rect(x_temp, y_temp, icon.cols, icon.rows));
			double s = compareHist(icon, temp);
			if (s > w && s > s_max)
			{
				s_max = s;
				now_x = x_temp;
				now_y = y_temp;
			}
		}
	}

	return QPoint(now_x,now_y);
}

bool cocscript::Is_jiaozhun_Area(QPoint jiaozhun_point, cv::Mat jiaozhun_png, int temp_x, int temp_y, int m)
{
	if (temp_x == -1 || temp_y == -1)
	{
		return false;
	}
	else
	{
		switch (m)
		{
		case NORMAL:
			return false;
			break;
		case UP:
			if (temp_y >= jiaozhun_point.y())
			{
				return true;
			}
			else
			{
				return false;
			}
			break;
		case UPANDDOWN:
			if (temp_y >= jiaozhun_point.y() && temp_y <= jiaozhun_point.y() + jiaozhun_png.rows)
			{
				return true;
			}
			else
			{
				return false;
			}
			break;
		case RIGHT:
			if (temp_x <= jiaozhun_point.x() + jiaozhun_png.cols)
			{
				return true;
			}
			else
			{
				return false;
			}
			break;
		case RIGHT_LEFT:
			if (temp_x >= jiaozhun_point.x() + jiaozhun_png.cols)
			{
				return true;
			}
			else
			{
				return false;
			}
			break;
		default:
			return false;
			break;
		}
	}
}

bool cocscript::Is_Finish_Donation()
{
	QImage* del = QPixmap_To_Mat(this->screen_pix, this->mat);
	cv::Mat temp = this->mat.clone();
	delete del;
	if (Find_SmallMat(JIAOZHUN, temp, 0.9) == QPoint(-1, -1))
	{
		update_Text("\t\The donation has been finished!\n");
		return true;
	}
	else
	{
		return false;
	}
}