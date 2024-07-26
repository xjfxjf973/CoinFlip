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

    //���ù̶���С
    setFixedSize(320, 588);
    //����ͼ��
    setWindowIcon(QIcon(":/res/Coin0001.png"));
    //���ñ���
    setWindowTitle("�����");

    //�˳���ťʵ��
    connect(ui->actionquit, &QAction::triggered, this, [=]() {
        this->close();
        });

    //׼����ʼ��ť����Ч
    QSound* startSound = new QSound(":/res/TapButtonSound.wav", this);


    //��ʼ��ť
    MyPushButton* startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width() * 0.5 - startBtn->width() * 0.5, this->height() * 0.7);

    //ʵ����ѡ��ؿ�����
    chooseScene = new ChooseLevelScene;

    //����ѡ��ؿ��ķ��ذ�ť���ź�
    connect(chooseScene, &ChooseLevelScene::chooseSceneBack, this, [=]() {
        QTimer::singleShot(200,this, [=]() {
            chooseScene->hide();
            //���ó���λ��
            this->setGeometry(chooseScene->geometry());
            this->show();//������ʾ������
            });

        });

    //��������¼���ִ����Ч
    connect(startBtn, &MyPushButton::clicked, this, [=]() {


        startBtn->zoom1(); //������Ծ
        startBtn->zoom2(); //������Ծ
        //���ſ�ʼ��Ч
        startSound->play();

        //���뵽ѡ��ؿ�������
        // ��ʱ����
        QTimer::singleShot(200, this, [=]() {
            //��������
            this->hide();
            //���ó���λ��
            chooseScene->setGeometry(this->geometry());
            //��ʾѡ��ؿ�����
            chooseScene->show();

            });


        });


}

//��дpainEvent�¼� ������ͼ
void MainScene::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0,this->width(),this->height(),pix);

    //������ͼ��
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width() * 0.5, pix.height() * 0.5);
    painter.drawPixmap(10, 30, pix.width(), pix.height(), pix);

}





MainScene::~MainScene()
{
    delete ui;
}
