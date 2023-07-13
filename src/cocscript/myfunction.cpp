#include "myfunction.h"

QImage* QPixmap_To_Mat(QPixmap pix, cv::Mat& mat)
{
	//QPixmap -> QImage
	QImage* qimage = new QImage(pix.toImage());
	//QImage -> Mat  bits() 获取第一个像素的指针
	mat = cv::Mat(qimage->height(), qimage->width(), CV_8UC4, qimage->bits(), qimage->bytesPerLine());
	cv::resize(mat, mat, Size(1700, 978));
	return qimage;
}

bool Is_jiaozhun_Area(QPoint jiaozhun_point, cv::Mat jiaozhun_png, int temp_x, int temp_y, int m)
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
		default:
			return false;
			break;
		}
	}
}