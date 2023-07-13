#include "cocscript.h"

void cocscript::one_FindAndOpenCoc()
{
	cv::Mat coc_icon = COC_ICON;

	this->screen_pix = screen->grabWindow((WId)hq);
	QImage * del = QPixmap_To_Mat(this->screen_pix,this->mat);

	cv::Mat last = this->mat.clone();
	QPoint point = Find_SmallMat(coc_icon, this->mat);

	if (point.x() == -1 && point.y() == -1)
	{
		update_Text("\tThe coc game was not found!\n");

		cv::waitKey(1000);
		update_Text("\tThe script is closed!\n");
		this->is_start_catch = false;
		delete del;
		return;
	}

	Left_Mouse_Event(point,QSize(91,85));

	update_Text("\tThe coc game was found!\n");
	delete del;

	cv::waitKey(1000);
	this->screen_pix = screen->grabWindow((WId)hq);
	del = QPixmap_To_Mat(this->screen_pix, this->mat);
	if (compareHist(last, this->mat) < 0.9)
	{
		update_Text("\tEntered the game!\n");
	}
	else
	{
		update_Text("\tFailed to enter the game\n");

		cv::waitKey(1000);
		update_Text("\tThe script is closed!\n");
		this->is_start_catch = false;

		delete del;
		return;
	}
	delete del;
}

void cocscript::two_Donation()
{
	NeedNum need_num;
	cv::Mat training = TRAINING_ICON.clone();
	this->screen_pix = screen->grabWindow((WId)hq);
	QImage* del = QPixmap_To_Mat(this->screen_pix, this->mat);
	QPoint point = Find_SmallMat(training, this->mat);
	update_Text("\tNow it's a donation model\n");
	cv::waitKey(1000);
	delete del;

	//先等20秒，没找到再等15秒
	if (point.x() == -1 && point.y() == -1)
	{
		update_Text("\tWait another 15 seconds before entering the game\n");
		keybd_event(0x11, 0, 0, 0);
		keybd_event('E', 0, 0, 0);
		keybd_event('E', 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x11, 0, KEYEVENTF_KEYUP, 0);
		cv::waitKey(15000);
		return;
	}

	operator_Mouse(DIALOG_OPEN.clone(), "dialog open icon");

	donation(need_num);
	cv::waitKey(1500);
	donation(need_num);

	operator_Mouse(DIALOG_CLOSE.clone(), "dialog close icon");

	if (need_num.army.empty() && need_num.potion.empty() && need_num.machinery.empty())
	{
		return;
	}

	operator_Mouse(TRAINING_ICON.clone(), "training icon");
	cv::waitKey(1000);
	if (!need_num.army.empty() && operator_Mouse(TRAINARMY.clone(), "train army", "训练部队", 0.85))
	{
		for (auto it = need_num.army.begin(); it != need_num.army.end(); it++)
		{
			if (it->second.first == "person")
			{
				for (int i = 0; i < it->second.second; i++)
				{
					operator_Mouse(TRAINPERSON.clone(), "train person");
				}
			}
			else if (it->second.first == "archer")
			{
				for (int i = 0; i < it->second.second; i++)
				{
					operator_Mouse(TRAINARCHER.clone(), "train archer");
				}
			}
			else if (it->second.first == "brontosaurus")
			{
				for (int i = 0; i < it->second.second; i++)
				{
					operator_Mouse(TRAINBRONTOSAURUS.clone(), "train brontosaurus");
				}
			}
			else if (it->second.first == "iceperson")
			{
				for (int i = 0; i < it->second.second; i++)
				{
					operator_Mouse(TRAINICEPERSON.clone(), "train iceperson");
				}
			}
			else if (it->second.first == "pig")
			{
				Dark_Army_MouseEvent();
				for (int i = 0; i < it->second.second; i++)
				{
					operator_Mouse(TRAINPIG.clone(), "train pig");
				}
			}
			else if (it->second.first == "valkyrie")
			{
				Dark_Army_MouseEvent();
				for (int i = 0; i < it->second.second; i++)
				{
					operator_Mouse(TRAINVALKYRIE.clone(), "train valkyrie");
				}
			}
		}
	}
	this->Have_Dark_Army = false;

	if (!need_num.potion.empty() && operator_Mouse(TRAINPOTION.clone(), "train potion", "配制法术", 0.9))
	{
		for (auto it = need_num.potion.begin(); it != need_num.potion.end(); it++)
		{
			if (it->second.first == "light")
			{
				for (int i = 0; i < it->second.second; i++)
				{
					operator_Mouse(TRAINLIGHT.clone(), "train light");
				}
			}
			else if (it->second.first == "kuangbao")
			{
				for (int i = 0; i < it->second.second; i++)
				{
					operator_Mouse(TRAINKUANGBAO.clone(), "train kuangbao");
				}
			}
			else if (it->second.first == "ice")
			{
				for (int i = 0; i < it->second.second; i++)
				{
					operator_Mouse(TRAINICE.clone(), "train ice");
				}
			}
		}
	}

	if (!need_num.machinery.empty() && operator_Mouse(TRAINMACHINERY.clone(), "train machinery", "建造攻城机器", 0.9))
	{
		for (auto it = need_num.machinery.begin(); it != need_num.machinery.end(); it++)
		{
			if (it->second.first == "car")
			{
				operator_Mouse(TRAINCAR.clone(), "train car");
			}
			else if (it->second.first == "fly")
			{
				operator_Mouse(TRAINFLY.clone(), "train fly");
			}
			else if (it->second.first == "ball")
			{
				operator_Mouse(TRAINBALL.clone(), "train ball");
			}
			else if (it->second.first == "train")
			{
				operator_Mouse(TRAINTRAIN.clone(), "train train");
			}
			else if (it->second.first == "wood")
			{
				operator_Mouse(TRAINWOOD.clone(), "train wood");
			}
		}

	}
	operator_Mouse(TRAINCLOSE.clone(), "train close icon", 0.9);
}

void cocscript::donation(NeedNum& need_num)
{
	//找到请求并点击

	if (operator_Mouse(QINGQIU, "reinforce", 0.85, std::make_pair(JIAOZHUN4.clone(), UP), std::make_pair(JIAOZHUN3.clone(), UPANDDOWN), 0, 0, true))
	{
		//捐兵模块
		if (ui->checkBox_3->isChecked())
		{
			each_Donation(ui->checkBox_14, GIVEPERSON.clone(), "person", need_num.army, 1);
			each_Donation(ui->checkBox_12, GIVEARCHER.clone(), "archer", need_num.army, 2);
			each_Donation(ui->checkBox_13, GIVEBRONTOSAURUS.clone(), "brontosaurus", need_num.army, 14);
			each_Donation(ui->checkBox_15, GIVEICEPERSON.clone(), "iceperson", need_num.army, 15);
			if (Is_Finish_Donation())
			{
				return;
			}
			each_Donation(ui->checkBox_17, GIVEPIG.clone(), "pig", need_num.army, 19);
			each_Donation(ui->checkBox_16, GIVEVALKYRIE.clone(), "valkyrie", need_num.army, 20);
			if (Is_Finish_Donation())
			{
				return;
			}
		}

		//捐药水模块
		if (ui->checkBox_2->isChecked())
		{
			each_Donation(ui->checkBox_10, GIVELIGHT.clone(), "light", need_num.potion, 1);
			each_Donation(ui->checkBox_4, GIVEKUANGBAO.clone(), "kuangbao", need_num.potion, 3);
			each_Donation(ui->checkBox_5, GIVEICE.clone(), "ice", need_num.potion, 5);
			this->screen_pix = screen->grabWindow((WId)hq);
			if (Is_Finish_Donation())
			{
				return;
			}
		}

		//捐车模块
		if (ui->checkBox->isChecked())
		{
			if (ui->checkBox_6->isChecked() && operator_Mouse(GIVECAR.clone(), "give car", 0.9, std::make_pair(JIAOZHUN.clone(), UP), std::make_pair(QINGQIU2.clone(), RIGHT), 0, 0, false, false))
			{
				need_num.machinery.insert(std::make_pair(1, std::make_pair("car", 1)));
			}
			else if (ui->checkBox_7->isChecked() && operator_Mouse(GIVEFLY.clone(), "give fly", 0.9, std::make_pair(JIAOZHUN.clone(), UP), std::make_pair(QINGQIU2.clone(), RIGHT), 0, 0, false, false))
			{
				need_num.machinery.insert(std::make_pair(2, std::make_pair("fly", 1)));
			}
			else if (ui->checkBox_8->isChecked() && operator_Mouse(GIVEBALL.clone(), "give ball", 0.9, std::make_pair(JIAOZHUN.clone(), UP), std::make_pair(QINGQIU2.clone(), RIGHT), 0, 0, false, false))
			{
				need_num.machinery.insert(std::make_pair(3,std::make_pair("ball", 1)));
			}
			else if (ui->checkBox_9->isChecked() && operator_Mouse(GIVETRAIN.clone(), "give train", 0.9, std::make_pair(JIAOZHUN.clone(), UP), std::make_pair(QINGQIU2.clone(), RIGHT), 0, 0, false, false))
			{
				need_num.machinery.insert(std::make_pair(4,std::make_pair("train", 1)));
			}
			else if (ui->checkBox_11->isChecked() && operator_Mouse(GIVEWOOD.clone(), "give wood", 0.9, std::make_pair(JIAOZHUN.clone(), UP), std::make_pair(QINGQIU2.clone(), RIGHT), 0, 0, false, false))
			{
				need_num.machinery.insert(std::make_pair(5,std::make_pair("wood", 1)));
			}
		}

		operator_Mouse(CLOSE.clone(), "close", 0.9);
	}
}

void cocscript::each_Donation(QCheckBox* checkbox, cv::Mat icon, QString icon_name, std::multimap<int,std::pair<std::string, int>>& map,int key)
{
	if (icon_name == "pig" || icon_name == "valkyrie")
	{
		this->Have_Dark_Army = true;
	}
	QString order = QString("give ") + icon_name;
	if (checkbox->isChecked() && operator_Mouse(icon, order, 0.8, std::make_pair(JIAOZHUN.clone(), UP), std::make_pair(QINGQIU2.clone(), RIGHT), 0, 0, false, false))
	{
		std::pair<int, std::pair<std::string, int>>temp;
		temp.second.first = icon_name.toStdString();
		temp.second.second = 1;
		while (checkbox->isChecked() && operator_Mouse(icon, order, 0.8, std::make_pair(JIAOZHUN.clone(), UP), std::make_pair(QINGQIU2.clone(), RIGHT), 0, 0, false, false))
		{
			temp.second.second++;
		}
		map.insert(temp);
	}
}