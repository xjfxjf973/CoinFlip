#pragma once

#include <QPushButton>

class MyCoin  : public QPushButton
{
	Q_OBJECT

public:
	//MyCoin(QWidget *parent);
	MyCoin(QString btnImg);

	int posX; //x坐标
	int posY; //y坐标
	bool flag; //正反标志

	void changeFlag();//改变标志,执行翻转效果
	QTimer* timer1; //正面翻反面 定时器
	QTimer* timer2; //反面翻正面 定时器
	int min = 1; //最小图片
	int max = 8; //最大图片

	void mousePressEvent(QMouseEvent* e);


	~MyCoin();
};
