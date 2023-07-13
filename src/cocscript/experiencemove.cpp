#include "cocscript.h"

void cocscript::two_experience()
{
	update_Text("\tNow it's an experience model\n");
	cv::waitKey(50);
	Left_Mouse_Event(QPoint(106, 871), QSize(0, 0));
	cv::waitKey(300);
	Left_Mouse_Event(QPoint(232, 519), QSize(0, 0));
	cv::waitKey(300);
	for (int i = 0; i < 2; i++)
	{
		Left_Mouse_Event(QPoint(580, 848), NORTH, 80, true);
		cv::waitKey(300);
	}
	while (!operator_Mouse(JINGJI.clone(), "jingji", 0.99, jiaozhun_empty, jiaozhun_empty, 0, 50))
	{
		Left_Mouse_Event(QPoint(556, 206), SOUTH, 500, true);
		cv::waitKey(500);
	}
	operator_Mouse(EXFIGHT.clone(), "fight", 0.9);
	cv::waitKey(3000);
	Left_Mouse_Event(QPoint(this->p_screen_size.width() / 2, this->p_screen_size.height() / 2), WEST, this->p_screen_size.width() / 4);
	cv::waitKey(200);
	Left_Mouse_Event(QPoint(this->p_screen_size.width() / 2, this->p_screen_size.height() / 4), SOUTH, this->p_screen_size.height() / 2);
	this->screen_pix = screen->grabWindow((WId)hq);
	QImage* del = QPixmap_To_Mat(this->screen_pix, this->mat);
	QPoint point = Find_SmallMat(ARCHERKING.clone(), this->mat,0.9);
	point.setX(point.x() + ARCHERKING.cols/2);
	point.setY(point.y() + ARCHERKING.rows/2);
	delete del;
	Left_Mouse_Event(point, QSize(0, 0));
	Left_Mouse_Event(QPoint(746, 110), QSize(0, 0));
	cv::waitKey(500);
	Left_Mouse_Event(point, QSize(0, 0));
	//while(Find_SmallMat())
	cv::waitKey(ui->spinBox_9->value());
	operator_Mouse(ENDFIGHT.clone(), "endfight", 0.9);
	operator_Mouse(FIGHTEXITYES.clone(), "exit", 0.9);
	operator_Mouse(GOHOME.clone(), "go home", 0.9);
	cv::waitKey(2500);
}