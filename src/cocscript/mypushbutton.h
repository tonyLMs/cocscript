#pragma once

#include <QPushButton>

class MyPushButton : public QPushButton
{
	Q_OBJECT

public:
	MyPushButton(QWidget* parent);
	~MyPushButton();
};