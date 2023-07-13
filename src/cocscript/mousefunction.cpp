#include "cocscript.h"

bool cocscript::operator_Mouse(cv::Mat icon, QString icon_name, double w, std::pair<cv::Mat, int> jiaozhun_path_m, std::pair<cv::Mat, int> jiaozhun_path_m2, int add_x, int add_y, bool doublehelp, bool is_open_phash)
{
	this->screen_pix = screen->grabWindow((WId)hq);
	QImage* del = QPixmap_To_Mat(this->screen_pix, this->mat);
	QPoint point = Find_SmallMat(icon, this->mat, w, jiaozhun_path_m, jiaozhun_path_m2, doublehelp, is_open_phash);
	if (point.x() == -1 && point.y() == -1)
	{
		update_Text(QString("\tThe %1 was not found!\n").arg(icon_name));
		cv::waitKey(10);
		//update_Text("\tThe script is closed!\n");
		//this->is_start_catch = false;
		delete del;
		return false;
	}
	Left_Mouse_Event(point, QSize(icon.cols, icon.rows), add_x, add_y);
	update_Text(QString("\tThe %1 was found!\n").arg(icon_name));
	delete del;
	cv::waitKey(400);
	return true;
}

bool cocscript::operator_Mouse(cv::Mat icon, QString icon_name, QString text, double w, int add_x, int add_y,bool fight_jiaozhun, bool is_black)
{
	this->screen_pix = screen->grabWindow((WId)hq);
	QImage* del = QPixmap_To_Mat(this->screen_pix, this->mat);
	QPoint point = Find_SmallMat(icon, this->mat, text, w,fight_jiaozhun,is_black);
	if (point.x() == -1 && point.y() == -1)
	{
		update_Text(QString("\tThe %1 was not found!\n").arg(icon_name));
		cv::waitKey(10);
		delete del;
		return false;
	}
	Left_Mouse_Event(point, QSize(icon.cols, icon.rows), add_x, add_y);
	update_Text(QString("\tThe %1 was found!\n").arg(icon_name));
	delete del;
	cv::waitKey(1000);
	return true;
}

void cocscript::Left_Mouse_Event(QPoint point_mouse, QSize icon_size, int add_x, int add_y)
{
	RECT catch_rect;
	GetWindowRect(hq, &catch_rect);
	this->x = catch_rect.left;
	this->y = catch_rect.top;

	int now_x = this->x;
	int now_y = this->y;

	now_x += (point_mouse.x() + icon_size.width() / 2);
	now_y += (point_mouse.y() + icon_size.height() / 2);

	int width_abs = static_cast<unsigned short>((now_x + add_x) * 65535 / width_screen);
	int height_abs = static_cast<unsigned short>((now_y + add_y) * 65535 / height_screen);
	//左按下和左释放 相当于一次点击
	mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP | MOUSEEVENTF_MOVE, width_abs, height_abs, NULL, NULL);
}

void cocscript::Left_Mouse_Event(QPoint point_mouse, int way, int lenth)
{
	RECT catch_rect;
	GetWindowRect(hq, &catch_rect);
	this->x = catch_rect.left;
	this->y = catch_rect.top;
	int now_x = this->x;
	int now_y = this->y;
	now_x += point_mouse.x();
	now_y += point_mouse.y();
	int width_abs = static_cast<unsigned short>(now_x * 65535 / width_screen);
	int height_abs = static_cast<unsigned short>(now_y * 65535 / height_screen);
	int target_x = width_abs;
	int target_y = height_abs;

	switch (way)
	{
	case NORTH:
		target_y = static_cast<unsigned short>((now_y - lenth) * 65535 / width_screen);
		break;
	case SOUTH:
		target_y = static_cast<unsigned short>((now_y + lenth) * 65535 / width_screen);
		break;
	case WEST:
		target_x = static_cast<unsigned short>((now_x - lenth) * 65535 / width_screen);
		break;
	case EAST:
		target_x = static_cast<unsigned short>((now_x + lenth) * 65535 / width_screen);
		break;
	default:
		break;
	}
	mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_MOVE, width_abs, height_abs, NULL, NULL);
	Sleep(50);
	mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, target_x, target_y, NULL, NULL);
	Sleep(50);
	mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTUP | MOUSEEVENTF_MOVE, target_x, target_y, NULL, NULL);
	Sleep(50);
}

void cocscript::Left_Mouse_Event(QPoint point_mouse, int way, int lenth ,bool)
{
	RECT catch_rect;
	GetWindowRect(hq, &catch_rect);
	this->x = catch_rect.left;
	this->y = catch_rect.top;
	int now_x = this->x;
	int now_y = this->y;
	now_x += point_mouse.x();
	now_y += point_mouse.y();
	int width_abs = static_cast<unsigned short>(now_x * 65535 / width_screen);
	int height_abs = static_cast<unsigned short>(now_y * 65535 / height_screen);
	switch (way)
	{
	case NORTH:
		now_y -= lenth;
		break;
	case SOUTH:
		now_y += lenth;
		break;
	case WEST:
		now_x -= lenth;
		break;
	case EAST:
		now_x += lenth;
		break;
	default:
		break;
	}
	int target_x = static_cast<unsigned short>(now_x * 65535 / width_screen);
	int target_y = static_cast<unsigned short>(now_y * 65535 / width_screen);

	
	mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_MOVE, width_abs, height_abs, NULL, NULL);
	Sleep(50);
	mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, target_x, target_y, NULL, NULL);
	Sleep(50);
	mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTUP | MOUSEEVENTF_MOVE, target_x, target_y, NULL, NULL);
	Sleep(50);
}

void cocscript::Left_Mouse_Event(QPoint start_point, QPoint end_point, int num,FIGHT_WAY way)
{
	RECT catch_rect;
	GetWindowRect(hq, &catch_rect);
	this->x = catch_rect.left;
	this->y = catch_rect.top;
	int now_x = this->x;
	int now_y = this->y;
	int end_x = this->x;
	int end_y = this->y;
	now_x += start_point.x();
	now_y += start_point.y();
	end_x += end_point.x();
	end_y += end_point.y();
	double start_x = static_cast<unsigned short>(now_x * 65535 / width_screen);
	double start_y = static_cast<unsigned short>(now_y * 65535 / height_screen);
	double target_x = static_cast<unsigned short>(end_x * 65535 / width_screen);
	double target_y = static_cast<unsigned short>(end_y * 65535 / width_screen);
	//x y 分别的距离
	double len_x = abs(start_x - target_x);
	double len_y = abs(start_y - target_y);

	//单次增加的距离
	double s_x = len_x / (double)(num+1);
	double s_y = len_y / (double)(num+1);

	for (int i = 0; i < num; i++)
	{
		switch (way)
		{
		case F_UP_LEFT:
			start_x -= s_x;
			start_y += s_y * 2;
			break;
		case F_UP_RIGHT:
			start_x += s_x;
			start_y += s_y * 2;
			break;
		case F_DOWN_LEFT:
			start_x -= s_x*1.03;
			start_y -= s_y/1.3;
			break;
		case F_DOWN_RIGHT:
			start_x += s_x;
			start_y -= s_y/1.2;
			break;
		}
		mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP | MOUSEEVENTF_MOVE, start_x, start_y, NULL, NULL);
		cv::waitKey(ui->spinBox_4->value());
	}
}

void cocscript::Dark_Army_MouseEvent()
{
	if(Have_Dark_Army == true)
	{
		cv::waitKey(400);
		this->screen_pix = screen->grabWindow((WId)hq);
		QImage* del = QPixmap_To_Mat(this->screen_pix, this->mat);
		QPoint baoshi_point = Find_SmallMat(BAOSHI.clone(), this->mat);
		cv::Mat archer_icon = TRAINARCHER.clone();
		QPoint archer_point = Find_SmallMat(archer_icon, this->mat);
		Left_Mouse_Event(QPoint(baoshi_point.x(), archer_point.y() + archer_icon.rows + 10), WEST, baoshi_point.x() - archer_point.x());
		cv::waitKey(2000);
		delete del;
		this->Have_Dark_Army = false;
	}
	else
	{
		return;
	}
}