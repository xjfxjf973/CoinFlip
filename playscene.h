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
	int levelIndex;//内部的成员函数 记录所选的关卡

	//重写painEvent事件 画背景图
	void paintEvent(QPaintEvent*);

	int gameArray[4][4];//保存关卡数据

	MyCoin *coinBtn[4][4]; //金币按钮数组

	static bool isWin; //是否胜利


signals:
	void chooseSceneBack();


};

