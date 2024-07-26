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
    //���ô��ڹ̶���С
    this->setFixedSize(320, 588);
    //����ͼ��
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //���ñ���
    this->setWindowTitle("ѡ��ؿ�");

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

    //ѡ��ؿ���ť��Ч
    QSound* chooseSound = new QSound(":/res/TapButtonSound.wav", this);
    //���ذ�ť��Ч
    QSound* backSound = new QSound(":/res/BackButtonSound.wav", this);


    //���ذ�ť
    MyPushButton* backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width(), this->height() - backBtn->height());

    //�������
    connect(backBtn, &MyPushButton::clicked, [=]() {
        //qDebug() << "����˷��ذ�ť";
        //�����������ҷ����ˣ��������������ذ�ť
        backSound->play();
        emit this->chooseSceneBack();

        });

    //����ѡ��ؿ��İ�ť
    for (int i = 0; i < 20; i++)
    {
        MyPushButton* menuBtn = new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(25 + i % 4 * 70, 130 + i / 4 * 70);
        menuBtn->move(25 + i % 4 * 70, 130 + i / 4 * 70);

        //����ÿ����ť�ĵ���¼�
        connect(menuBtn, &MyPushButton::clicked, this, [=]() {
            //������Ч
            chooseSound->play();

            QString str = QString("��ѡ����ǵ� %1 ��").arg(i + 1);
            qDebug() << str;

            //���뵽��Ϸ����
            this->hide();//����ѡ�񳡾�
            play = new PlayScene(i + 1);
            play->setGeometry(this->geometry());
            play->show();

            //���շ��ذ�ť
            connect(play, &PlayScene::chooseSceneBack, this, [=]() {
                QTimer::singleShot(200, this, [=]() {
                    this->setGeometry(play->geometry());
                    this->show();
                    PlayScene::isWin = false;
                    //ʹ��ɾ�����������أ���ʡ�ڴ�
                    delete play;
                    play = nullptr;
                    });

                });

            });

        QLabel* label = new QLabel;
        label->setParent(menuBtn);
        label->setFixedSize(menuBtn->width(), menuBtn->height());
        // ��������������������С
        QFont font;
        font.setFamily("�����п�");
        font.setPointSize(15); // ���������СΪ 12
        label->setFont(font); // Ӧ�����嵽��ǩ��
        label->setText(QString::number(i + 1));

        //����label�Ķ��뷽ʽ ˮƽ���кʹ�ֱ����
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    }



}



//��дpainEvent�¼� ������ͼ
void ChooseLevelScene::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    //���ر���
    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width() - pix.width()) * 0.5, 30, pix.width(), pix.height(), pix);

}



ChooseLevelScene::~ChooseLevelScene()
{}
