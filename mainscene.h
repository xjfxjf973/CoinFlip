#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_mainscene.h"
#include "chooselevelscene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainSceneClass; };
QT_END_NAMESPACE

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();

    //��дpainEvent�¼� ������ͼ
    void paintEvent(QPaintEvent*);

    ChooseLevelScene* chooseScene = nullptr;



private:
    Ui::MainSceneClass *ui;
};
