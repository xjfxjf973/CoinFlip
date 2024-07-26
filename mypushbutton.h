#pragma once

#include <QPushButton>

class MyPushButton  : public QPushButton
{
	Q_OBJECT

public:
	//MyPushButton(QWidget *parent);
	//构造函数 正常显示图片路径，按下后显示的图片路径
	MyPushButton(QString normalImg, QString pressImg = "");
	
	//保存用户传入的路径
	QString normalImgPath;
	QString pressImgPath;

	//向下跳跃
	void zoom1();
	//向上跳跃
	void zoom2();

	void mousePressEvent(QMouseEvent* e);

	void mouseReleaseEvent(QMouseEvent* e);

	~MyPushButton();
};
