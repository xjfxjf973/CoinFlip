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
	QString str = QString("�����˵� %1 ��").arg(levelIndex);
	qDebug() << str;

	//��ʼ����Ϸ����
    //���ô��ڹ̶���С
    this->setFixedSize(320, 588);
    //����ͼ��
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //���ñ���
    this->setWindowTitle("�����");

    //�����˵���
    QMenuBar* bar = this->menuBar();
    this->setMenuBar(bar);
    //������ʼ�˵�
    QMenu* startMenu = bar->addMenu("��ʼ");
    //������ť�˵���
    QAction* quitAction = startMenu->addAction("�˳�");
    //����˳� �˳���Ϸ
    connect(quitAction, &QAction::triggered, [=]() {
        this->close();
        });

    //�������Ч
    QSound* flipSound = new QSound(":/res/ConFlipSound.wav", this);
    //ʤ����ť��Ч
    QSound* winSound = new QSound(":/res/LevelWinSound.wav", this);
    //���ذ�ť��Ч
    QSound* backSound = new QSound(":/res/BackButtonSound.wav", this);


    //���ذ�ť
    MyPushButton* backBtn = new MyPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width(), this->height() - backBtn->height());

    //�������
    connect(backBtn, &MyPushButton::clicked, [=]() {
        backSound->play();
        qDebug() << "��Ϸ������ ����˷��ذ�ť";
        //�����������ҷ����ˣ��������������ذ�ť
        emit this->chooseSceneBack();

        });

    //��ǰ�ؿ�����
    QLabel* label = new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("�����п�");
    font.setPointSize(30);
    label->setFont(font);
    QString str2 = QString("Level: %1").arg(this->levelIndex);
    label->setText(str2);
    label->setGeometry(QRect(30, this->height() - 60, 140, 50)); //����λ�úʹ�С

    //��ʼ����ά����
    dataConfig config;
    for (int i = 0; i < 4;i++)
    {
        for (int j = 0; j < 4; j++)
        {
            gameArray[i][j] = config.mData[this->levelIndex][i][j];
        }
    }

    //ʤ��ͼƬ��ʾ
    QLabel* winLabel = new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0, 0, tmpPix.width(), tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move((this->width() - tmpPix.width()) * 0.5, -tmpPix.height());



    //������ҵı���ͼƬ
    for (int i = 0; i < 4;i++)
    {
        for (int j = 0; j < 4; j++)
        {
            //���Ʊ���ͼƬ
            QPixmap pix = QPixmap(":/res/BoardNode(1).png");
            QLabel* label = new QLabel;
            label->setGeometry(0, 0, pix.width(), pix.height());
            label->setPixmap(pix);
            label->setParent(this);
            label->move(57 + i * 50, 200 + j * 50);

            //��Ҷ���
            QString str;
            str = this->gameArray[i][j] == 1 ? ":/res/Coin0001.png" : ":/res/Coin0008.png";

            MyCoin* coin = new MyCoin(str);
            coin->setParent(label);
            coin->move(2, 3);

            coin->posX = i;
            coin->posY = j;
            coin->flag = this->gameArray[i][j];

            //����ҷ��������н���ά��
            coinBtn[i][j] = coin;

            //�����ҷ�ת
            connect(coin, &MyCoin::clicked, this, [=]() {
                flipSound->play();

                coin->changeFlag();
                //ͬ���޸�����
                this->gameArray[coin->posX][coin->posY] = !this->gameArray[coin->posX][coin->posY];

                //��ת��Χ���
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

                    //�ж��Ƿ�ʤ��
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
                        qDebug() << "ʤ��";
                        winSound->play();
                        //�ƶ�ʤ��ͼƬ
                        QPropertyAnimation* animation1 = new QPropertyAnimation(winLabel, "geometry");
                        //���ö�������ʱ��
                        animation1->setDuration(1000);
                        //��ʼλ��
                        animation1->setStartValue(QRect(winLabel->x(), winLabel->y(), winLabel->width(), winLabel->height()));
                        //����λ��
                        animation1->setEndValue(QRect(winLabel->x(), winLabel->y() + 180, winLabel->width(), winLabel->height()));
                        //���û�������
                        animation1->setEasingCurve(QEasingCurve::OutBounce);
                        //ִ�ж���
                        animation1->start();
                    }

                    });


                });


        }
    }

}



//��дpainEvent�¼� ������ͼ
void PlayScene::paintEvent(QPaintEvent*) {
    //���ر���
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    //���ر���
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width() * 0.5, pix.height() * 0.5);
    painter.drawPixmap(10, 30, pix.width(), pix.height(), pix);

}



PlayScene::~PlayScene()
{}
