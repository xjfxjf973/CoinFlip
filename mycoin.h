#pragma once

#include <QPushButton>

class MyCoin  : public QPushButton
{
	Q_OBJECT

public:
	//MyCoin(QWidget *parent);
	MyCoin(QString btnImg);

	int posX; //x����
	int posY; //y����
	bool flag; //������־

	void changeFlag();//�ı��־,ִ�з�תЧ��
	QTimer* timer1; //���淭���� ��ʱ��
	QTimer* timer2; //���淭���� ��ʱ��
	int min = 1; //��СͼƬ
	int max = 8; //���ͼƬ

	void mousePressEvent(QMouseEvent* e);


	~MyCoin();
};
