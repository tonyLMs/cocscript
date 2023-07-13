#pragma once

#include "headfile.h"
#include "neednum.h"
#include "enum_sum.h"

QT_BEGIN_NAMESPACE
namespace Ui { class cocscriptClass; };
QT_END_NAMESPACE

class cocscript : public QMainWindow
{
	Q_OBJECT

public:

	cocscript(QWidget* parent = nullptr);
	~cocscript();

	void paintEvent(QPaintEvent*);

	bool eventFilter(QObject* obj, QEvent* event);

	void mySave();

	QString getCurrentTime();

	//两个校准区域
	QPoint Find_SmallMat(cv::Mat icon, cv::Mat target, double w = 0.6, std::pair<cv::Mat, int> jiaozhun_mat = std::make_pair(cv::Mat(), NORMAL), std::pair<cv::Mat, int> jiaozhun_mat2 = std::make_pair(cv::Mat(), NORMAL), bool doublehelp = false, bool is_open_phash = true);

	//这个是正经ocr(先text)
	QPoint Find_SmallMat(cv::Mat icon, cv::Mat target, QString text, double w, bool fight_jiaozhun = false, bool is_black = true);

	//这个是为调用ocr的含校准区域的函数(先w)
	QPoint Find_SmallMat(cv::Mat icon, cv::Mat target, double w, QString text, std::pair<cv::Mat, int> jiaozhun_mat = std::make_pair(cv::Mat(), NORMAL));

	QPoint Find_SmallMat(cv::Mat icon, cv::Mat target, QPoint boundary, double w = 0.6);

	void Left_Mouse_Event(QPoint point_mouse, QSize icon_size, int add_x = 0, int add_y = 0);

	//左键鼠标滑动
	void Left_Mouse_Event(QPoint point_mouse, int way, int lenth);

	//新版修正
	void Left_Mouse_Event(QPoint point_mouse, int way, int lenth,bool);

	void Left_Mouse_Event(QPoint start_point, QPoint end_point, int num,FIGHT_WAY way);

	void Dark_Army_MouseEvent();

	void update_Text(QString str);

	void init_set();

	bool Is_Finish_Donation();

	bool Is_jiaozhun_Area(QPoint jiaozhun_point, cv::Mat jiaozhun_png, int temp_x, int temp_y, int m);

	/*----------------------------------here is operator----------------------------------------*/

	/*----------------------------------donation and fight and experience----------------------------------------*/

	bool operator_Mouse(cv::Mat icon, QString icon_name, double w = 0.6, std::pair<cv::Mat, int> jiaozhun_icon = std::make_pair(cv::Mat(), NORMAL), std::pair<cv::Mat, int> jiaozhun_icon2 = std::make_pair(cv::Mat(), NORMAL), int add_x = 0, int add_y = 0, bool doublehelp = false, bool is_open_phash = true);

	bool operator_Mouse(cv::Mat icon, QString icon_name, QString text, double w = 0.8, int add_x = 0, int add_y = 0, bool fight_jiaozhun = false, bool is_black = true);

	void donation(NeedNum& need_num);

	void one_FindAndOpenCoc();

	void two_Donation();

	void each_Donation(QCheckBox* checkbox, cv::Mat icon, QString icon_name, std::multimap<int, std::pair<std::string, int>>& map, int key);

	void two_Fight();

	void two_experience();

private:

	Ui::cocscriptClass* ui;

    QString work_text_temp;

    bool is_start_catch = false;

    HWND hq;

    QPixmap screen_pix;

    cv::Mat mat;

    QScreen* screen;

    int width_screen;
    int height_screen;

    //模拟器的左上角顶点
    int x;
	int y;

	std::pair<QPoint,QSize> lasttime;

	QSize p_screen_size;

	std::pair<cv::Mat, int> jiaozhun_empty;

	QTimer* qtimer;

	bool is_reboot = false;

	bool Have_Dark_Army = false;

	QPoint ex_fight;
};