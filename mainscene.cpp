#include "mainscene.h"
#include <qpainter.h>
#include <mypushbutton.h>
#include <qdebug.h>
#include <qtimer.h>
#include <QtMultimedia/QSound>

#pragma execution_character_set("utf-8") 


MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainSceneClass())
{
    ui->setupUi(this);

    //设置固定大小
    setFixedSize(320, 588);
    //设置图标
    setWindowIcon(QIcon(":/res/Coin0001.png"));
    //设置标题
    setWindowTitle("翻金币");

    //退出按钮实现
    connect(ui->actionquit, &QAction::triggered, this, [=]() {
        this->close();
        });

    //准备开始按钮的音效
    QSound* startSound = new QSound(":/res/TapButtonSound.wav", this);


    //开始按钮
    MyPushButton* startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width() * 0.5 - startBtn->width() * 0.5, this->height() * 0.7);

    //实例化选择关卡场景
    chooseScene = new ChooseLevelScene;

    //监听选择关卡的返回按钮的信号
    connect(chooseScene, &ChooseLevelScene::chooseSceneBack, this, [=]() {
        QTimer::singleShot(200,this, [=]() {
            chooseScene->hide();
            //设置场景位置
            this->setGeometry(chooseScene->geometry());
            this->show();//重新显示主场景
            });

        });

    //监听点击事件，执行特效
    connect(startBtn, &MyPushButton::clicked, this, [=]() {


        startBtn->zoom1(); //向下跳跃
        startBtn->zoom2(); //向上跳跃
        //播放开始音效
        startSound->play();

        //进入到选择关卡场景中
        // 延时进入
        QTimer::singleShot(200, this, [=]() {
            //自身隐藏
            this->hide();
            //设置场景位置
            chooseScene->setGeometry(this->geometry());
            //显示选择关卡创建
            chooseScene->show();

            });


        });


}

//重写painEvent事件 画背景图
void MainScene::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0,this->width(),this->height(),pix);

    //画背景图标
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width() * 0.5, pix.height() * 0.5);
    painter.drawPixmap(10, 30, pix.width(), pix.height(), pix);

}





MainScene::~MainScene()
{
    delete ui;
}
