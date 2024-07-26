#pragma once

#include <QMainWindow>
#include "playscene.h"

class ChooseLevelScene  : public QMainWindow
{
	Q_OBJECT

public:
	ChooseLevelScene(QWidget* parent = nullptr);
	~ChooseLevelScene();

	//重写painEvent事件 画背景图
	void paintEvent(QPaintEvent*);

	//游戏场景对象指针
	PlayScene* play = NULL;

signals:
	//写一个自定义信号，告诉主场景点击了返回
	void chooseSceneBack();


};
