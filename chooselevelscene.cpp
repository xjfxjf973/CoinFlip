#include "chooselevelscene.h"
#include <qmenu.h>
#include <qmenubar.h>
#include <qpainter.h>
#include "mypushbutton.h"
#include <qdebug.h>
#include <qlabel.h>
#include <qtimer.h>
#include <QtMultimedia/QSound>

#pragma execution_character_set("utf-8") 

ChooseLevelScene::ChooseLevelScene(QWidget *parent)
	: QMainWindow(parent)
{
    //设置窗口固定大小
    this->setFixedSize(320, 588);
    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置标题
    this->setWindowTitle("选择关卡");

    //创建菜单栏
    QMenuBar* bar = this->menuBar();
    this->setMenuBar(bar);
    //创建开始菜单
    QMenu* startMenu = bar->addMenu("开始");
    //创建按钮菜单项
    QAction* quitAction = startMenu->addAction("退出");
    //点击退出 退出游戏
    connect(quitAction, &QAction::triggered, [=]() {
        this->close();
        });

    //选择关卡按钮音效
    QSound* chooseSound = new QSound(":/res/TapButtonSound.wav", this);
    //返回按钮音效
    QSound* backSound = new QSound(":/res/BackButtonSound.wav", this);


    //返回按钮
    MyPushButton* backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width(), this->height() - backBtn->height());

    //点击返回
    connect(backBtn, &MyPushButton::clicked, [=]() {
        //qDebug() << "点击了返回按钮";
        //告诉主场景我返回了，主场景监听返回按钮
        backSound->play();
        emit this->chooseSceneBack();

        });

    //创建选择关卡的按钮
    for (int i = 0; i < 20; i++)
    {
        MyPushButton* menuBtn = new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(25 + i % 4 * 70, 130 + i / 4 * 70);
        menuBtn->move(25 + i % 4 * 70, 130 + i / 4 * 70);

        //监听每个按钮的点击事件
        connect(menuBtn, &MyPushButton::clicked, this, [=]() {
            //播放音效
            chooseSound->play();

            QString str = QString("您选择的是第 %1 关").arg(i + 1);
            qDebug() << str;

            //进入到游戏场景
            this->hide();//隐藏选择场景
            play = new PlayScene(i + 1);
            play->setGeometry(this->geometry());
            play->show();

            //接收返回按钮
            connect(play, &PlayScene::chooseSceneBack, this, [=]() {
                QTimer::singleShot(200, this, [=]() {
                    this->setGeometry(play->geometry());
                    this->show();
                    PlayScene::isWin = false;
                    //使用删除而不是隐藏，节省内存
                    delete play;
                    play = nullptr;
                    });

                });

            });

        QLabel* label = new QLabel;
        label->setParent(menuBtn);
        label->setFixedSize(menuBtn->width(), menuBtn->height());
        // 创建字体对象并设置字体大小
        QFont font;
        font.setFamily("华文行楷");
        font.setPointSize(15); // 设置字体大小为 12
        label->setFont(font); // 应用字体到标签上
        label->setText(QString::number(i + 1));

        //设置label的对齐方式 水平居中和垂直居中
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    }



}



//重写painEvent事件 画背景图
void ChooseLevelScene::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    //加载标题
    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width() - pix.width()) * 0.5, 30, pix.width(), pix.height(), pix);

}



ChooseLevelScene::~ChooseLevelScene()
{}
