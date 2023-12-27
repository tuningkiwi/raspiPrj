//pro1(PROGRAM1) : JOYSTICK
//pro2(PROGRAM2) : LED ON/OFF
//pro3(PROGRAM3) : ELEVATOR
//pro4(PROGRAM4) : PWM LED

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QProcess>
#include <wiringPi.h>
#include <softPwm.h>
#include <QImage>
#include <stdlib.h>
#include <stdio.h>
#include <QList>

#define PWM_PIN 0

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    connect(ui->pushButton, SIGNAL(clicked()),
            this, SLOT(ExecuteProgram_pro1()));

    connect(ui->pushButton_2, SIGNAL(clicked()),
            this, SLOT(ExecuteProgram_pro2()));

    connect(ui->pushButton_3, SIGNAL(clicked()),
            this, SLOT(ExecuteProgram_pro3()));

    connect(ui->pushButton_6, SIGNAL(clicked()),
            this, SLOT(pro1_terminate()));

    connect(ui->pushButton_4, SIGNAL(clicked()),
            this, SLOT(pro2_terminate()));

    connect(ui->pushButton_5, SIGNAL(clicked()),
            this, SLOT(pro3_terminate()));


    connect(ui->pushButton_7,
                SIGNAL(clicked()),
                this, SLOT(pwmledsetting()));

    connect(ui->pushButton_8,
                SIGNAL(clicked()),
                this, SLOT(pwmled_terminate()));

    
    connect(ui->horizontalSlider,
            SIGNAL(valueChanged(int)),
            ui->lcdNumber,
            SLOT(display(int)));

    connect(ui->horizontalSlider,
            SIGNAL(valueChanged(int)),
            this, SLOT(pwmled(int)));

    img[0].load(":/image/ledoff.png");
    img[1].load(":/image/ledon.png");




}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::pwmled(int num){
    softPwmWrite(PWM_PIN,num);
    //delay(5);
}

void MainWindow::pwmledsetting(){
    wiringPiSetupGpio();
    pinMode(PWM_PIN, OUTPUT);
    softPwmCreate(PWM_PIN,0,255);
}


void MainWindow::pwmled_terminate(){
    softPwmWrite(PWM_PIN,0);
}


void MainWindow::ExecuteProgram_pro1()
{
    //QString path = "C:/Qt/test";
    //qDebug() << "hello";

    //QString program = QString("C:/Qt/program/hello.exe");
    pro1 = new QProcess(this);

    QObject::connect(pro1,  SIGNAL(readyReadStandardOutput()), this, SLOT(PrintMsg_pro1()));
    //pro1->start("/home/pi/Work/qt/build-untitled8-Desktop-Release/untitled8");
    //pro1->start("/home/pi/Work/qt/qtPrj/joy1227");
    pro1->start("qtPrj/joy1227");

    if(pro1->waitForStarted() == false)
    {
        ui->textBrowser->insertPlainText("External Program Starting Error\n");
    }
    else
    {
        ui->textBrowser->insertPlainText("External Program Started\n");
    }


}

void MainWindow::PrintMsg_pro1()
{
    QByteArray data;
    data = pro1->readAllStandardOutput();
    qDebug() << data;
    int num=0;
    QList<QByteArray> arr= data.split('*');
    if(arr.length()>1){

        //qDebug() <<arr[0];
        //printf("\n");
        //qDebug() <<arr[1];
    //qDebug() << "printmsg";
        bool ok;
        num = arr[1].toInt(&ok,10);

        //printf("%d\n",num);
        qDebug() << "result: "<<num;
        if(num <= 30 && num >= -30){
            ui->horizontalSlider_2->setValue(num);
        }

    }
    //bool ok;
    //int num = data.toInt(&ok,10);

    ui->textBrowser->insertPlainText(data);
    ui->textBrowser->moveCursor(QTextCursor::End);
    data.clear();
}


void MainWindow::ExecuteProgram_pro2()
{
    pro2 = new QProcess(this);
    QObject::connect(pro2,  SIGNAL(readyReadStandardOutput()), this, SLOT(PrintMsg_pro2()));

    pro2->start("qtPrj/led5");
    ui->textBrowser_2->insertPlainText("pro2 start");

    if(pro2->waitForStarted() == false)
    {
        ui->textBrowser_2->insertPlainText("External Program Starting Error\n");
    }
    else
    {
        ui->textBrowser_2->insertPlainText("External Program Started\n");
    }

}

void MainWindow::PrintMsg_pro2()
{
    QByteArray data;
    data = pro2->readAllStandardOutput();
    //qDebug() << "printmsg";
    QByteArray msg("ON");


    if(data.contains(msg)){
        ui->label_7->setPixmap(img[1]);

    }else {
        ui->label_7->setPixmap(img[0]);
    }


    ui->textBrowser_2->insertPlainText(data);
    ui->textBrowser_2->moveCursor(QTextCursor::End);
    data.clear();
}

void MainWindow::ExecuteProgram_pro3()
{
    pro3 = new QProcess(this);
    QObject::connect(pro3,  SIGNAL(readyReadStandardOutput()), this, SLOT(PrintMsg_pro3()));
    pro3->start("qtPrj/elevator1227");
    ui->textBrowser_3->insertPlainText("pro3 start");
}

void MainWindow::PrintMsg_pro3()
{
    QByteArray data;
    data = pro3->readAllStandardOutput();
    //qDebug() << "printmsg";
    ui->textBrowser_3->insertPlainText(data);
    ui->textBrowser_3->moveCursor(QTextCursor::End);
    data.clear();
}

void MainWindow::pro1_terminate()
{
    pro1->terminate();
    ui->textBrowser->insertPlainText("pro1 terminate");

}


void MainWindow::pro2_terminate()
{
    pro2->terminate();
    ui->textBrowser_2->insertPlainText("pro2 terminate");

}


void MainWindow::pro3_terminate()
{
    pro3->terminate();
    ui->textBrowser_3->insertPlainText("pro3 terminate");

}
