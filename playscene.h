#pragma once

#include <QMainWindow>
#include "mycoin.h"

class PlayScene  : public QMainWindow
{
	Q_OBJECT

public:
	//PlayScene(QWidget *parent);
	~PlayScene();
	PlayScene(int levelNum);
	int levelIndex;//�ڲ��ĳ�Ա���� ��¼��ѡ�Ĺؿ�

	//��дpainEvent�¼� ������ͼ
	void paintEvent(QPaintEvent*);

	int gameArray[4][4];//����ؿ�����

	MyCoin *coinBtn[4][4]; //��Ұ�ť����

	static bool isWin; //�Ƿ�ʤ��


signals:
	void chooseSceneBack();


};

