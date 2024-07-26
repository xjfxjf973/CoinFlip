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
		QString str = QString("ͼƬ %1 ����ʧ��").arg(btnImg);
		qDebug() << str;
		return;
	}
	this->setFixedSize(pix.width(), pix.height());
	this->setStyleSheet("QPushButton{border:0px;}");
	this->setIcon(pix);
	this->setIconSize(QSize(pix.width(), pix.height()));

	//��ʼ����ʱ��
	timer1 = new QTimer(this);
	timer2 = new QTimer(this);

    //�������淭ת���źŲ�
    connect(timer1, &QTimer::timeout, [=]() {
        QPixmap pixmap;
        QString str = QString(":/res/Coin000%1.png").arg(this->min++);
        pixmap.load(str);
        this->setFixedSize(pixmap.width(), pixmap.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(), pixmap.height()));
        if (this->min > this->max) //����������ֵ��������Сֵ����ֹͣ��ʱ��
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
        if (this->max < this->min) //���С����Сֵ���������ֵ����ֹͣ��ʱ��
        {
            this->max = 8;

            timer2->stop();
        }
        });




}

void MyCoin::changeFlag() {
	if (this->flag) //��������棬ִ�����д���
	{
		timer1->start(30);

		this->flag = false;
	}
	else //����ִ�����д���
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
