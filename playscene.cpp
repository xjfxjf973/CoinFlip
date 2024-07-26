#include "playscene.h"
#include <qdebug.h>
#include <qmenubar.h>
#include <qmenu.h>
#include <qpainter.h>
#include "mypushbutton.h"
#include <qlabel.h>
#include "mycoin.h"
#include "dataconfig.h"
#include <qtimer.h>
#include <qpropertyanimation.h>
#include <QtMultimedia/QSound>

#pragma execution_character_set("utf-8") 

//PlayScene::PlayScene(QWidget *parent)
//	: QMainWindow(parent)
//{}

bool PlayScene::isWin = false;

PlayScene::PlayScene(int levelNum)
	//: QMainWindow(parent)
{
	this->levelIndex = levelNum;
	QString str = QString("进入了第 %1 关").arg(levelIndex);
	qDebug() << str;

	//初始化游戏场景
    //设置窗口固定大小
    this->setFixedSize(320, 588);
    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置标题
    this->setWindowTitle("翻金币");

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

    //翻金币音效
    QSound* flipSound = new QSound(":/res/ConFlipSound.wav", this);
    //胜利按钮音效
    QSound* winSound = new QSound(":/res/LevelWinSound.wav", this);
    //返回按钮音效
    QSound* backSound = new QSound(":/res/BackButtonSound.wav", this);


    //返回按钮
    MyPushButton* backBtn = new MyPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width(), this->height() - backBtn->height());

    //点击返回
    connect(backBtn, &MyPushButton::clicked, [=]() {
        backSound->play();
        qDebug() << "游戏场景中 点击了返回按钮";
        //告诉主场景我返回了，主场景监听返回按钮
        emit this->chooseSceneBack();

        });

    //当前关卡标题
    QLabel* label = new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("华文行楷");
    font.setPointSize(30);
    label->setFont(font);
    QString str2 = QString("Level: %1").arg(this->levelIndex);
    label->setText(str2);
    label->setGeometry(QRect(30, this->height() - 60, 140, 50)); //设置位置和大小

    //初始化二维数组
    dataConfig config;
    for (int i = 0; i < 4;i++)
    {
        for (int j = 0; j < 4; j++)
        {
            gameArray[i][j] = config.mData[this->levelIndex][i][j];
        }
    }

    //胜利图片显示
    QLabel* winLabel = new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0, 0, tmpPix.width(), tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move((this->width() - tmpPix.width()) * 0.5, -tmpPix.height());



    //创建金币的背景图片
    for (int i = 0; i < 4;i++)
    {
        for (int j = 0; j < 4; j++)
        {
            //绘制背景图片
            QPixmap pix = QPixmap(":/res/BoardNode(1).png");
            QLabel* label = new QLabel;
            label->setGeometry(0, 0, pix.width(), pix.height());
            label->setPixmap(pix);
            label->setParent(this);
            label->move(57 + i * 50, 200 + j * 50);

            //金币对象
            QString str;
            str = this->gameArray[i][j] == 1 ? ":/res/Coin0001.png" : ":/res/Coin0008.png";

            MyCoin* coin = new MyCoin(str);
            coin->setParent(label);
            coin->move(2, 3);

            coin->posX = i;
            coin->posY = j;
            coin->flag = this->gameArray[i][j];

            //将金币放入数组中进行维护
            coinBtn[i][j] = coin;

            //点击金币翻转
            connect(coin, &MyCoin::clicked, this, [=]() {
                flipSound->play();

                coin->changeFlag();
                //同步修改数组
                this->gameArray[coin->posX][coin->posY] = !this->gameArray[coin->posX][coin->posY];

                //翻转周围金币
                QTimer::singleShot(200, this, [=]() {
                    if (coin->posY - 1 >= 0)//
                    {
                        coinBtn[coin->posX][coin->posY - 1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY - 1] = !this->gameArray[coin->posX][coin->posY - 1];
                    }
                    if (coin->posY + 1 <= 3)//
                    {
                        coinBtn[coin->posX][coin->posY + 1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY + 1] = !this->gameArray[coin->posX][coin->posY + 1];
                    }
                    if (coin->posX - 1 >= 0)//
                    {
                        coinBtn[coin->posX - 1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX - 1][coin->posY] = !this->gameArray[coin->posX - 1][coin->posY];
                    }
                    if (coin->posX + 1 <= 3)//
                    {
                        coinBtn[coin->posX + 1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX + 1][coin->posY] = !this->gameArray[coin->posX + 1][coin->posY];
                    }

                    //判断是否胜利
                    this->isWin = true;
                    for (int i = 0; i < 4;i++)
                    {
                        for (int j = 0; j < 4; j++)
                        {
                            if (this->gameArray[i][j] == 0)
                            {
                                this->isWin = false;
                                break;
                            }
                        }
                    }

                    if (this->isWin == true)
                    {
                        qDebug() << "胜利";
                        winSound->play();
                        //移动胜利图片
                        QPropertyAnimation* animation1 = new QPropertyAnimation(winLabel, "geometry");
                        //设置动画持续时间
                        animation1->setDuration(1000);
                        //开始位置
                        animation1->setStartValue(QRect(winLabel->x(), winLabel->y(), winLabel->width(), winLabel->height()));
                        //结束位置
                        animation1->setEndValue(QRect(winLabel->x(), winLabel->y() + 180, winLabel->width(), winLabel->height()));
                        //设置缓和曲线
                        animation1->setEasingCurve(QEasingCurve::OutBounce);
                        //执行动画
                        animation1->start();
                    }

                    });


                });


        }
    }

}



//重写painEvent事件 画背景图
void PlayScene::paintEvent(QPaintEvent*) {
    //加载背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    //加载标题
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width() * 0.5, pix.height() * 0.5);
    painter.drawPixmap(10, 30, pix.width(), pix.height(), pix);

}



PlayScene::~PlayScene()
{}
