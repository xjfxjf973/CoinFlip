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

    //ÖØÐ´painEventÊÂ¼þ »­±³¾°Í¼
    void paintEvent(QPaintEvent*);

    ChooseLevelScene* chooseScene = nullptr;



private:
    Ui::MainSceneClass *ui;
};
