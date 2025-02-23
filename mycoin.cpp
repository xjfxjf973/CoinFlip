#include "mycoin.h"
#include <qdebug.h>
#include <qtimer.h>
#include "playscene.h"
//#include <playscene.cpp>


//MyCoin::MyCoin(QWidget *parent)
//	: QPushButton(parent)
//{}

MyCoin::MyCoin(QString btnImg) {
	QPixmap pix;
	bool ret = pix.load(btnImg);
	if (!ret)
	{
		QString str = QString("图片 %1 加载失败").arg(btnImg);
		qDebug() << str;
		return;
	}
	this->setFixedSize(pix.width(), pix.height());
	this->setStyleSheet("QPushButton{border:0px;}");
	this->setIcon(pix);
	this->setIconSize(QSize(pix.width(), pix.height()));

	//初始化定时器
	timer1 = new QTimer(this);
	timer2 = new QTimer(this);

    //监听正面翻转的信号槽
    connect(timer1, &QTimer::timeout, [=]() {
        QPixmap pixmap;
        QString str = QString(":/res/Coin000%1.png").arg(this->min++);
        pixmap.load(str);
        this->setFixedSize(pixmap.width(), pixmap.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(), pixmap.height()));
        if (this->min > this->max) //如果大于最大值，重置最小值，并停止定时器
        {
            this->min = 1;
            timer1->stop();

        }
        });

    connect(timer2, &QTimer::timeout, [=]() {
        QPixmap pixmap;
        QString str = QString(":/res/Coin000%1.png").arg((this->max)--);
        pixmap.load(str);
        this->setFixedSize(pixmap.width(), pixmap.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(), pixmap.height()));
        if (this->max < this->min) //如果小于最小值，重置最大值，并停止定时器
        {
            this->max = 8;

            timer2->stop();
        }
        });




}

void MyCoin::changeFlag() {
	if (this->flag) //如果是正面，执行下列代码
	{
		timer1->start(30);

		this->flag = false;
	}
	else //反面执行下列代码
	{
		timer2->start(30);

		this->flag = true;
	}
}


void MyCoin::mousePressEvent(QMouseEvent* e)
{
    if (PlayScene::isWin)
    {
        return;
    }
    else
    {
        return QPushButton::mousePressEvent(e);
    }
}



MyCoin::~MyCoin()
{}
