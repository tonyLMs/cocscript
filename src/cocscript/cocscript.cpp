#include "cocscript.h"

cocscript::cocscript(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::cocscriptClass())
{
    ui->setupUi(this);
    ui->scrollArea_work->installEventFilter(this);
    ui->scrollAreaWidgetContents_work->installEventFilter(this);
    ui->scrollArea_work->setStyleSheet("background:grey;");
    ui->tabWidget->setStyleSheet("background:grey;");
    ui->frame->setFrameStyle(QFrame::NoFrame);
    ui->frame->setStyleSheet("color:black");
    ui->tabWidget->setCurrentIndex(0);
    ui->stackedWidget->setCurrentIndex(0);
    this->setFixedSize(701, 503);
    this->width_screen = GetSystemMetrics(SM_CXSCREEN);
    this->height_screen = GetSystemMetrics(SM_CYSCREEN);
    this->lasttime = std::make_pair(QPoint(0, 0), QSize(0, 0));
    this->p_screen_size = QSize(1700, 978);
    this->jiaozhun_empty = std::make_pair(cv::Mat(), NORMAL);
	this->qtimer = new QTimer(this);

    connect(ui->btn_catch, &QPushButton::clicked, [=]()
        {
            flag2:
            if(this->is_start_catch == false)
            {
                update_Text("\tThe script is started!\n");

                hq = FindWindow(NULL, TEXT("BlueStacks")); //TEXT转化const char *到 LPCWSTR 找到窗口句柄

                if (get_window_title(hq).toStdString().size() == NULL)
                {
                    cv::waitKey(1000);
                    update_Text("\tBlueStacks are not captured!\n");

                    cv::waitKey(1000);
                    update_Text("\tThe script is closed!\n");
                }
                else //捕获窗口
                {
                    flag:
                    this->is_start_catch = true;
                    cv::waitKey(1000);
                    update_Text("\tBlueStacks are captured!\n");

                    cv::waitKey(1000);
                    //将hq窗口句柄转为QString输出
                    TCHAR szBuffer[256];
                    wsprintf(szBuffer, L"0x%08p", hq);
                    QString strHWND = QString::fromWCharArray(szBuffer);
                    this->work_text_temp += QString("BlueStacks' window handle is %1 \n").arg(strHWND);
                    ui->label_work->setText(work_text_temp);

                    //捕获屏幕截图到内存
                    screen = QGuiApplication::primaryScreen();
                    this->screen_pix = screen->grabWindow((WId)hq);

                    cv::waitKey(1000);
                    this->work_text_temp += QString("The screen's size is %1*%2\n").arg(this->screen_pix.width()).arg(this->screen_pix.height());
                    ui->label_work->setText(work_text_temp);


                    this->x = 0;
                    this->y = 0;

                    if (this->p_screen_size != QSize(this->screen_pix.width(), this->screen_pix.height()))
                    {
                        cv::waitKey(1000);
                        update_Text("\tThe window resizing is not a standard size and is being resized\n");
                        MoveWindow(hq, this->x, this->y, this->p_screen_size.width(), this->p_screen_size.height(), true);
                        goto flag;
                    }


                    SetWindowPos(hq, NULL, 0, 0, 0, 0, SWP_NOSIZE);

                    one_FindAndOpenCoc();

					if (ui->checkBox_donation->isChecked() || ui->checkBox_fight->isChecked()||ui->checkBox_fight_2->isChecked())
					{
						//进入游戏时间
						cv::waitKey(20000);
						while (this->is_start_catch)
						{
                            cv::Mat t;
							this->Have_Dark_Army = false;
							if (ui->checkBox_donation->isChecked())
							{
								two_Donation();
							}
                            else if (ui->checkBox_fight->isChecked())
                            {
                                Left_Mouse_Event(QPoint(72, 726), QSize(0, 0));
                                cv::waitKey(500);
                                this->screen_pix = screen->grabWindow((WId)hq);
                                QImage* del = QPixmap_To_Mat(this->screen_pix, this->mat);
                                cv::Mat t = this->mat.clone();
                                delete del;
								if (Find_SmallMat(FINISH.clone(), t, QPoint(1133, 402), 0.7) != QPoint(-1, -1) && Find_SmallMat(NOFINISH.clone(), t, QPoint(1133, 402), 0.7) == QPoint(-1, -1))
								{
                                    update_Text("\tThe army is trained\n");
                                    operator_Mouse(TRAINCLOSE.clone(), "train close icon", 0.9);
									two_Fight();
								}
								else
								{
									update_Text("\tThe army is not trained\n");
									operator_Mouse(TRAINCLOSE.clone(), "train close icon",0.9);
									update_Text("\tClose the coc game\n");
									Left_Mouse_Event(QPoint(1677, 959), QSize(0, 0));
									cv::waitKey(1000);
									//Left_Mouse_Event(QPoint(this->p_screen_size.width() / 3, this->p_screen_size.height() / 2), EAST, this->p_screen_size.width() /2 );
                                    Left_Mouse_Event(QPoint(1167, 344), QSize(0, 0));
                                    this->is_start_catch = false;
                                    cv::waitKey(ui->spinBox_8->value() * 60000);
									goto flag2;
								}
							}
							//刷经验模式
							else if (ui->checkBox_fight_2->isChecked())
							{
								if (ui->checkBox_18->isChecked() == false)
								{
									Left_Mouse_Event(QPoint(72, 726), QSize(0, 0));
									cv::waitKey(500);
									this->screen_pix = screen->grabWindow((WId)hq);
									QImage* del = QPixmap_To_Mat(this->screen_pix, this->mat);
									t = this->mat.clone();
									delete del;
								}
								if (ui->checkBox_18->isChecked() == false)
								{
									if (Find_SmallMat(ISARCHERKINGOK.clone(), t) != QPoint(-1, -1))
									{
										update_Text("\tThe archer king is trained\n");
										operator_Mouse(TRAINCLOSE.clone(), "train close icon", 0.9);
										two_experience();
									}
									else
									{
										update_Text("\tThe archer king is not trained\n");
									}
								}
								else
                                {
                                    two_experience();
                                }
							}
							if (!ui->checkBox_fight_2->isChecked())
							{
								cv::waitKey(10000);
							}
                        }
                    }
                    else
                    {
                        update_Text("\tNo mode selected,The script is closed!\n");
                        this->is_start_catch = false;
                    }
                }
            }
        });

    connect(ui->btn_close, &QPushButton::clicked, [=]()
        {
            if (this->is_start_catch == true)
            {
                update_Text("\tThe script is closed!\n");
                this->is_start_catch = false;
            }
        });

    connect(ui->btn_clean_data, &QPushButton::clicked, [=]()
        {
            if (QMessageBox::Yes == QMessageBox::question(this, "question", "Whether to clear the cache?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes))
            {
                QFile work_text_file(WORK_DIARY_PATH);
                work_text_file.open(QIODevice::WriteOnly);
                work_text_file.write(std::string().data());
                this->work_text_temp.clear();
                ui->label_work->setText(work_text_temp);
                work_text_file.close();
            }
        });

    connect(ui->btn_exit, &QPushButton::clicked, [=]()
        {
            if (QMessageBox::Yes == QMessageBox::question(this, "question", "Exit?", QMessageBox::Yes | QMessageBox::No, QMessageBox::No))
            {
                this->mySave();
                delete ui;
                exit(0);
            }
        });

    connect(ui->btn_set, &QPushButton::clicked, [=]()
        {
            if (this->is_start_catch == true)
            {
                QMessageBox::warning(this, "warning", "Please Close the script first!");
            }
            else
            {
                ui->stackedWidget->setCurrentIndex(1);
            }
        });

    connect(ui->btn_return, &QPushButton::clicked, [=]()
        {
            ui->stackedWidget->setCurrentIndex(0);
        });

    connect(ui->btn_return_2, &QPushButton::clicked, [=]()
        {
            ui->stackedWidget->setCurrentIndex(0);
        });

    connect(ui->btn_return_3, &QPushButton::clicked, [=]()
        {
            ui->stackedWidget->setCurrentIndex(0);
        });

    connect(ui->checkBox_donation, &QCheckBox::stateChanged, [=]()
        {
            if (ui->checkBox_donation->isChecked() == true)
            {
                ui->checkBox_fight->setChecked(false);
                ui->checkBox_fight_2->setChecked(false);
            }
        });

    connect(ui->checkBox_fight, &QCheckBox::stateChanged, [=]()
        {
            if (ui->checkBox_fight->isChecked() == true)
            {
                ui->checkBox_donation->setChecked(false);
                ui->checkBox_fight_2->setChecked(false);
            }
        });

    connect(ui->checkBox_fight_2, &QCheckBox::stateChanged, [=]()
        {
            if (ui->checkBox_fight_2->isChecked() == true)
            {
                ui->checkBox_donation->setChecked(false);
                ui->checkBox_fight->setChecked(false);
            }
        });

    init_set();
} 

cocscript::~cocscript()
{
    this->mySave();
    delete screen;
    delete ui;
}

void cocscript::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    QColor background;
    background.setRgb(54, 54, 54);
    painter.setBrush(background);
    painter.drawRect(rect());
}

bool cocscript::eventFilter(QObject* obj, QEvent* event) //封装好的事件过滤器 将滑动条滑倒最下端
{
    static int nHeight = 0;
    if (dynamic_cast<QScrollArea*>(obj) == ui->scrollArea_work)
    {
        if (event->type() == QEvent::Resize)
        {
            nHeight = ui->scrollArea_work->height();//记录滚动窗口高度
            return false;
        }
    }
    else if (dynamic_cast<QWidget*>(obj) == ui->scrollAreaWidgetContents_work)
    {
        if (event->type() == QEvent::Resize)
        {
            int nDif = ui->scrollAreaWidgetContents_work->height() - nHeight;
            if (nDif > 0)
            {
                //容器高度大于滚动区域，此时就需要滚动条
                QScrollBar* pVScrollBar = ui->scrollArea_work->verticalScrollBar();
                pVScrollBar->setMaximum(nDif);//设置最大值
                pVScrollBar->setValue(nDif);//将当前值设置成最大值
                return false;
            }
        }
    }
    return QWidget::eventFilter(obj, event);
}

QString cocscript::getCurrentTime()
{
    return QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
}

void cocscript::update_Text(QString str)
{
	this->work_text_temp += getCurrentTime();
	this->work_text_temp += str;
	ui->label_work->setText(this->work_text_temp);
}