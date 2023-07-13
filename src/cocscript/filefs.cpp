#include "cocscript.h"

void cocscript::mySave()
{
    QFile work_text_file(WORK_DIARY_PATH);
    if (!work_text_file.open(QIODevice::Append))
    {
        QMessageBox::warning(this, "warning", "Work diary opening failed!");
        this->work_text_temp += "Work diary opening failed!\n";
        ui->label_work->setText(work_text_temp);
    }
    else
    {
        update_Text("\tExit the program\n");
        work_text_file.write(this->work_text_temp.toStdString().data());
    }
    work_text_file.close();

    std::ofstream ofs;
    ofs.open("set.txt", std::ios::in | std::ios::trunc);
    if (ui->checkBox_donation->isChecked() == true)
    {
        ofs << "donation = true" << std::endl;
    }
    else
    {
        ofs << "donation = false" << std::endl;
    }
    if (ui->checkBox_fight->isChecked() == true)
    {
        ofs << "fight = true" << std::endl;
    }
    else
    {
        ofs << "fight = false" << std::endl;
    }
    if (ui->checkBox_fight_2->isChecked() == true)
    {
        ofs << "fight2 = true" << std::endl;
    }
    else
    {
        ofs << "fight2 = false" << std::endl;
    }
    if (ui->checkBox_3->isChecked() == true)
    {
        ofs << "army = true" << std::endl;
    }
    else
    {
        ofs << "army = false" << std::endl;
    }
    if (ui->checkBox_2->isChecked() == true)
    {
        ofs << "potion = true" << std::endl;
    }
    else
    {
        ofs << "potion = false" << std::endl;
    }
    if (ui->checkBox->isChecked() == true)
    {
        ofs << "machinery = true" << std::endl;
    }
    else
    {
        ofs << "machinery = false" << std::endl;
    }
    if (ui->checkBox_14->isChecked() == true)
    {
        ofs << "person = true" << std::endl;
    }
    else
    {
        ofs << "person = false" << std::endl;
    }
    if (ui->checkBox_12->isChecked() == true)
    {
        ofs << "archer = true" << std::endl;
    }
    else
    {
        ofs << "archer = false" << std::endl;
    }
    if (ui->checkBox_13->isChecked() == true)
    {
        ofs << "brontosaurus = true" << std::endl;
    }
    else
    {
        ofs << "brontosaurus = false" << std::endl;
    }
    if (ui->checkBox_15->isChecked() == true)
    {
        ofs << "iceperson = true" << std::endl;
    }
    else
    {
        ofs << "iceperson = false" << std::endl;
    }
    if (ui->checkBox_17->isChecked() == true)
    {
        ofs << "pig = true" << std::endl;
    }
    else
    {
        ofs << "pig = false" << std::endl;
    }
    if (ui->checkBox_16->isChecked() == true)
    {
        ofs << "valkyrie = true" << std::endl;
    }
    else
    {
        ofs << "valkyrie = false" << std::endl;
    }
    if (ui->checkBox_10->isChecked() == true)
    {
        ofs << "light = true" << std::endl;
    }
    else
    {
        ofs << "light = false" << std::endl;
    }
    if (ui->checkBox_4->isChecked() == true)
    {
        ofs << "kuangbao = true" << std::endl;
    }
    else
    {
        ofs << "kuangbao = false" << std::endl;
    }
    if (ui->checkBox_5->isChecked() == true)
    {
        ofs << "ice = true" << std::endl;
    }
    else
    {
        ofs << "ice = false" << std::endl;
    }
    if (ui->checkBox_6->isChecked() == true)
    {
        ofs << "car = true" << std::endl;
    }
    else
    {
        ofs << "car = false" << std::endl;
    }
    if (ui->checkBox_7->isChecked() == true)
    {
        ofs << "fly = true" << std::endl;
    }
    else
    {
        ofs << "fly = false" << std::endl;
    }
    if (ui->checkBox_8->isChecked() == true)
    {
        ofs << "ball = true" << std::endl;
    }
    else
    {
        ofs << "ball = false" << std::endl;
    }
    if (ui->checkBox_9->isChecked() == true)
    {
        ofs << "train = true" << std::endl;
    }
    else
    {
        ofs << "train = false" << std::endl;
    }
    if (ui->checkBox_11->isChecked() == true)
    {
        ofs << "wood = true" << std::endl;
    }
    else
    {
        ofs << "wood = false" << std::endl;
    }
    if (ui->checkBox_18->isChecked() == true)
    {
        ofs << "exarcher = true" << std::endl;
    }
    else
    {
        ofs << "exarcher = false" << std::endl;
    }
    ofs.close();

    ofs.open("fightset.txt", ios::trunc | ios::out);
    ofs << std::to_string(ui->spinBox->value()) << std::endl;
    ofs << std::to_string(ui->spinBox_2->value()) << std::endl;
    ofs << std::to_string(ui->spinBox_3->value()) << std::endl;
    ofs << std::to_string(ui->spinBox_4->value()) << std::endl;
    ofs << std::to_string(ui->spinBox_5->value()) << std::endl;
    ofs << std::to_string(ui->spinBox_6->value()) << std::endl;
    ofs << std::to_string(ui->spinBox_7->value()) << std::endl;
    ofs << std::to_string(ui->spinBox_8->value()) << std::endl;
    ofs << std::to_string(ui->spinBox_9->value()) << std::endl;
    ofs.close();
}

void cocscript::init_set()
{
    std::ifstream ifs;
    ifs.open("set.txt", std::ios::out);
    std::string buf;
    while (std::getline(ifs, buf))
    {
        if (buf == "donation = true")
        {
            ui->checkBox_donation->setChecked(true);
        }
        else if (buf == "fight = true")
        {
            ui->checkBox_fight->setChecked(true);
        }
        else if (buf == "fight2 = true")
        {
            ui->checkBox_fight_2->setChecked(true);
        }
        else if (buf == "army = true")
        {
            ui->checkBox_3->setChecked(true);
        }
        else if (buf == "potion = true")
        {
            ui->checkBox_2->setChecked(true);
        }
        else if (buf == "machinery = true")
        {
            ui->checkBox->setChecked(true);
        }
        else if (buf == "person = true")
        {
            ui->checkBox_14->setChecked(true);
        }
        else if (buf == "archer = true")
        {
            ui->checkBox_12->setChecked(true);
        }
        else if (buf == "brontosaurus = true")
        {
            ui->checkBox_13->setChecked(true);
        }
        else if (buf == "iceperson = true")
        {
            ui->checkBox_15->setChecked(true);
        }
        else if (buf == "pig = true")
        {
            ui->checkBox_17->setChecked(true);
        }
        else if (buf == "valkyrie = true")
        {
            ui->checkBox_16->setChecked(true);
        }
        else if (buf == "light = true")
        {
            ui->checkBox_10->setChecked(true);
        }
        else if (buf == "kuangbao = true")
        {
            ui->checkBox_4->setChecked(true);
        }
        else if (buf == "ice = true")
        {
            ui->checkBox_5->setChecked(true);
        }
        else if (buf == "car = true")
        {
            ui->checkBox_6->setChecked(true);
        }
        else if (buf == "fly = true")
        {
            ui->checkBox_7->setChecked(true);
        }
        else if (buf == "ball = true")
        {
            ui->checkBox_8->setChecked(true);
        }
        else if (buf == "train = true")
        {
            ui->checkBox_9->setChecked(true);
        }
        else if (buf == "wood = true")
        {
            ui->checkBox_11->setChecked(true);
        }
        else if (buf == "exarcher = true")
        {
            ui->checkBox_18->setChecked(true);
        }
	}
	ifs.close();

	ifs.open("fightset.txt", ios::in);
	std::getline(ifs, buf);
	ui->spinBox->setValue(atoi(buf.c_str()));
    std::getline(ifs, buf);
    ui->spinBox_2->setValue(atoi(buf.c_str()));
    std::getline(ifs, buf);
    ui->spinBox_3->setValue(atoi(buf.c_str()));
    std::getline(ifs, buf);
    ui->spinBox_4->setValue(atoi(buf.c_str()));
    std::getline(ifs, buf);
    ui->spinBox_5->setValue(atoi(buf.c_str()));
    std::getline(ifs, buf);
    ui->spinBox_6->setValue(atoi(buf.c_str()));
    std::getline(ifs, buf);
    ui->spinBox_7->setValue(atoi(buf.c_str()));
    std::getline(ifs, buf);
    ui->spinBox_8->setValue(atoi(buf.c_str()));
    std::getline(ifs, buf);
    ui->spinBox_9->setValue(atoi(buf.c_str()));
    ifs.close();
}