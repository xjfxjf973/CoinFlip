#include "mypushbutton.h"
#include <qdebug.h>
#include <qpropertyanimation.h>

//MyPushButton::MyPushButton(QWidget *parent)
//	: QPushButton(parent)
//{}

MyPushButton::MyPushButton(QString normalImg, QString pressImg) {
	this->normalImgPath = normalImg;
    this->pressImgPath = pressImg;

    QPixmap pix;
	bool ret = pix.load(normalImg);
	if (!ret) {
		qDebug() << "ͼƬ����ʧ��";
		return;
	}

	//����ͼƬ�̶���С
	this->setFixedSize(pix.width(), pix.height());
	//���ò�����ͼƬ��ʽ
	this->setStyleSheet("QPushButton{border:0px;}");
	//����ͼ��
	this->setIcon(pix);
	//����ͼ���С
	this->setIconSize(QSize(pix.width(), pix.height()));



}


void MyPushButton::zoom1()
{
    //������������
    QPropertyAnimation* animation1 = new QPropertyAnimation(this, "geometry");
    //����ʱ��������λ����
    animation1->setDuration(200);
    //������ʼλ��
    animation1->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
    //��������λ��
    animation1->setEndValue(QRect(this->x()+2, this->y() + 5, this->width(), this->height()));
    //���û������ߣ�QEasingCurve::OutBounce Ϊ����Ч��    
    animation1->setEasingCurve(QEasingCurve::OutBounce);
    //��ʼִ�ж���
    animation1->start();
}

void MyPushButton::zoom2()
{
    QPropertyAnimation* animation1 = new QPropertyAnimation(this, "geometry");
    animation1->setDuration(200);
    animation1->setStartValue(QRect(this->x()+2, this->y() + 5, this->width(), this->height()));
    animation1->setEndValue(QRect(this->x(), this->y(), this->width(), this->height()));
    animation1->setEasingCurve(QEasingCurve::OutBounce);
    animation1->start();
} 


//����¼�
void MyPushButton::mousePressEvent(QMouseEvent* e)
{
    if (this->pressImgPath != "") //ѡ��·����Ϊ�գ���ʾѡ��ͼƬ
    {
        QPixmap pixmap;
        bool ret = pixmap.load(pressImgPath);
        if (!ret)
        {
            qDebug() << pressImgPath << "����ͼƬʧ��!";
        }

        this->setFixedSize(pixmap.width(), pixmap.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(), pixmap.height()));
    }
    //��������ִ�а����¼�
    return QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent* e)
{
    if (this->normalImgPath != "") //ѡ��·����Ϊ�գ���ʾѡ��ͼƬ
    {
        QPixmap pixmap;
        bool ret = pixmap.load(normalImgPath);
        if (!ret)
        {
            qDebug() << normalImgPath << "����ͼƬʧ��!";
        }
        this->setFixedSize(pixmap.width(), pixmap.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(), pixmap.height()));
    }
    //��������ִ�� �ͷ��¼�
    return QPushButton::mouseReleaseEvent(e);
}




MyPushButton::~MyPushButton()
{}
