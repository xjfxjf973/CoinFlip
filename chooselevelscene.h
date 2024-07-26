#pragma once

#include <QMainWindow>
#include "playscene.h"

class ChooseLevelScene  : public QMainWindow
{
	Q_OBJECT

public:
	ChooseLevelScene(QWidget* parent = nullptr);
	~ChooseLevelScene();

	//��дpainEvent�¼� ������ͼ
	void paintEvent(QPaintEvent*);

	//��Ϸ��������ָ��
	PlayScene* play = NULL;

signals:
	//дһ���Զ����źţ���������������˷���
	void chooseSceneBack();


};
