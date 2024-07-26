#pragma once

#include <QPushButton>

class MyPushButton  : public QPushButton
{
	Q_OBJECT

public:
	//MyPushButton(QWidget *parent);
	//���캯�� ������ʾͼƬ·�������º���ʾ��ͼƬ·��
	MyPushButton(QString normalImg, QString pressImg = "");
	
	//�����û������·��
	QString normalImgPath;
	QString pressImgPath;

	//������Ծ
	void zoom1();
	//������Ծ
	void zoom2();

	void mousePressEvent(QMouseEvent* e);

	void mouseReleaseEvent(QMouseEvent* e);

	~MyPushButton();
};
