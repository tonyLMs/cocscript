#include "cocscript.h"

void cocscript::two_Fight()
{
	cv::Mat open_search = BEGINFIGHT.clone();
	this->screen_pix = screen->grabWindow((WId)hq);
	QImage* del = QPixmap_To_Mat(this->screen_pix, this->mat);
	QPoint point = Find_SmallMat(open_search, this->mat);
	update_Text("\tNow it's a fight model\n");
	cv::waitKey(1000);
	if (point.x() == -1 && point.y() == -1)
	{
		update_Text("\tWait another 15 seconds before entering the game\n");
		keybd_event(0x11, 0, 0, 0);
		keybd_event('E', 0, 0, 0);
		keybd_event('E', 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x11, 0, KEYEVENTF_KEYUP, 0);
		cv::waitKey(15000);
		delete del;
		return;
	}

	//update_Text("\tNow is time to resize the screen\n");
	/*keybd_event(0x11, 0, 0, 0);
	mouse_event(MOUSEEVENTF_WHEEL, 0, 0, DWORD(-WHEEL_DELTA), 0);
	keybd_event(0x11, 0, KEYEVENTF_KEYUP, 0);*/

	bool is_next = false;
	cv::waitKey(1000);
	operator_Mouse(open_search, "begin fight");
	operator_Mouse(SEARCH.clone(), "search", "搜索对手", 0.9);

flag:
	if (is_next)
	{
		operator_Mouse(NEXT.clone(), "next", 0.9);
	}
	cv::waitKey(4000);
	cv::Mat t;
	int index = 0;
	do
	{
		this->screen_pix = screen->grabWindow((WId)hq);
		del = QPixmap_To_Mat(this->screen_pix, this->mat);
		point = Find_SmallMat(JUBAO.clone(), this->mat,0.2);
		t = this->mat.clone();
		
		if (point == QPoint(-1, -1))
		{
			update_Text("\twait more\n");
			cv::waitKey(4000);
		}

		index++;
		if (index == 3)
		{
			operator_Mouse(NEXT.clone(), "next", 0.9);
			index = 0;
		}
		delete del;

	} while (point == QPoint(-1, -1));

	cv::waitKey(500);
	//特殊区域数值，不要动
	cv::Mat digits_area(t, Rect(81, 162, 142, 152));
	long digits_arr[3];

	Get_Mat_Number(digits_area, digits_arr);

	update_Text(QString("\n/*-------------------------------------*/\n\tgold:\t%1\n\twater:\t%2\n\toil:\t%3\n/*-------------------------------------*/\n").arg(digits_arr[0]).arg(digits_arr[1]).arg(digits_arr[2]));
	cv::waitKey(500);

	//符合条件的对象
	if (digits_arr[0] >= ui->spinBox->value() * 10000 && digits_arr[1] >= ui->spinBox_2->value() * 10000 && digits_arr[2] >= ui->spinBox_3->value() * 1000)
	{
		is_next = false;
		update_Text("\tFind the objects that match the criteria!\n");
		cv::waitKey(2000);
		//左滑
		Left_Mouse_Event(QPoint(this->p_screen_size.width() / 2, this->p_screen_size.height() / 2), WEST, this->p_screen_size.width() / 4);
		cv::waitKey(500);
		Left_Mouse_Event(QPoint(this->p_screen_size.width() / 2, this->p_screen_size.height() / 4), SOUTH, this->p_screen_size.height() / 2);
		//下上半部分的兵

		cv::waitKey(5000);
		QPoint up_start(746, 110);
		QPoint up_left(73, 615);
		QPoint up_right(1342, 572);
		QPoint down_start(753, 783);
		QPoint down_left(72, 283);
		QPoint down_right(1439, 297);

		operator_Mouse(FIGHTBIGPERSON.clone(),"fight big person",0.8);
		Left_Mouse_Event(up_start, up_left, ui->spinBox_5->value() / 4, F_UP_LEFT);
		operator_Mouse(FIGHTPERSON.clone(), "fight person", 0.8);
		Left_Mouse_Event(up_start, up_left, ui->spinBox_6->value() / 4, F_UP_LEFT);
		operator_Mouse(FIGHTARCHER.clone(), "fight archer", 0.8);
		Left_Mouse_Event(up_start, up_left, ui->spinBox_7->value() / 4, F_UP_LEFT);

		if(operator_Mouse(PERSONKING.clone(), "fight person king", 0.8))
		{
			Left_Mouse_Event(QPoint(400, 376), QSize(0, 0));
		}
		if(operator_Mouse(ARCHERKING.clone(), "fight archer king", 0.8))
		{
			Left_Mouse_Event(QPoint(400, 376), QSize(0, 0));
		}
		if(operator_Mouse(HELPKING.clone(), "fight help king", 0.8))
		{
			Left_Mouse_Event(QPoint(400, 376), QSize(0, 0));
		}
		if (operator_Mouse(SHIELDKING.clone(), "shield king", 0.8))
		{
			Left_Mouse_Event(QPoint(400, 376), QSize(0, 0));
		}

		operator_Mouse(FIGHTBIGPERSON.clone(), "fight big person", 0.8);
		Left_Mouse_Event(up_start, up_right, ui->spinBox_5->value() / 4, F_UP_RIGHT);
		operator_Mouse(FIGHTPERSON.clone(), "fight person", 0.8);
		Left_Mouse_Event(up_start, up_right, ui->spinBox_6->value() / 4, F_UP_RIGHT);
		operator_Mouse(FIGHTARCHER.clone(), "fight archer", 0.8);
		Left_Mouse_Event(up_start, up_right, ui->spinBox_7->value() / 4, F_UP_RIGHT);
		Left_Mouse_Event(QPoint(this->p_screen_size.width() / 2, this->p_screen_size.height() / 4 * 3), NORTH, this->p_screen_size.height() / 2);
		operator_Mouse(FIGHTBIGPERSON.clone(), "fight big person", 0.8);
		Left_Mouse_Event(down_start, down_left, ui->spinBox_5->value() / 4, F_DOWN_LEFT);
		operator_Mouse(FIGHTPERSON.clone(), "fight person", 0.8);
		Left_Mouse_Event(down_start, down_left, ui->spinBox_6->value() / 4, F_DOWN_LEFT);
		operator_Mouse(FIGHTARCHER.clone(), "fight archer", 0.8);
		Left_Mouse_Event(down_start, down_left, ui->spinBox_7->value() / 4, F_DOWN_LEFT);
		operator_Mouse(FIGHTBIGPERSON.clone(), "fight big person", 0.8);
		Left_Mouse_Event(down_start, down_right, ui->spinBox_5->value() / 4, F_DOWN_RIGHT);
		operator_Mouse(FIGHTPERSON.clone(), "fight person", 0.8);
		Left_Mouse_Event(down_start, down_right, ui->spinBox_6->value() / 4, F_DOWN_RIGHT);
		operator_Mouse(FIGHTARCHER.clone(), "fight big archer", 0.8);
		Left_Mouse_Event(down_start, down_right, ui->spinBox_7->value() / 4, F_DOWN_RIGHT);


		if (operator_Mouse(FIGHTBIGPERSON.clone(), "fight big person", 0.8))
		{
			Left_Mouse_Event(down_start, down_right, ui->spinBox_5->value() / 4, F_DOWN_RIGHT);
		}
		if (operator_Mouse(FIGHTPERSON.clone(), "fight person", 0.8))
		{
			Left_Mouse_Event(down_start, down_right, ui->spinBox_6->value() / 4, F_DOWN_RIGHT);
		}
		if (operator_Mouse(FIGHTARCHER.clone(), "fight big archer", 0.8))
		{
			Left_Mouse_Event(down_start, down_right, ui->spinBox_7->value() / 4, F_DOWN_RIGHT);
		}

		//等待45秒
		cv::waitKey(45000);

		operator_Mouse(FIGHTEXIT.clone(), "exit",0.8);
		cv::waitKey(500);
		operator_Mouse(FIGHTEXITYES.clone(), "yes", 0.8);
		cv::waitKey(500);
		operator_Mouse(GOHOME.clone(), "gohome", 0.8);
		cv::waitKey(2000);
		Left_Mouse_Event(QPoint(72, 726), QSize(0, 0));
		cv::waitKey(500);
		cv::waitKey(500);
		operator_Mouse(TRAINRETURN.clone(), "train return", "一键训练");
		cv::waitKey(500);
		Left_Mouse_Event(QPoint(1469, 276), QSize(0, 0));
		cv::waitKey(500);
		operator_Mouse(TRAINCLOSE.clone(), "train close icon", 0.9);
	}
	else
	{
		index = 0;
		is_next = true;
		goto flag;
	}
}