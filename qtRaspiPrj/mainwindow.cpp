///***************************** 
//pro1(PROGRAM1) : JOYSTICK
<라즈베리파이 GPIO 제어 >
조이스틱 result(초기값 0)입니다. 
좌(-1)우(+1)로 조정을 하면, 
조이스틱 중앙 버튼을 누르면 result :0으로 재설정 됩니다. 
<GUI>
화면상에서 변화된 result값이 출력이 되고, 
horizontal slider(범위 -30~+30)의 조정키 위치도 해당값으로 이동합니다. 

//pro2(PROGRAM2) : LED ON/OFF
<라즈베리파이 GPIO 제어 >
무한으로 wiringPiSetupGpio()모드에서, 5번핀에 연결된 
LED가 1초 단위로 무한 ON/OFF 합니다. 
<GUI>
ON일 경우, off 일경우 이미지 변경 
    
//pro3(PROGRAM3) : ELEVATOR
<라즈베리파이 GPIO 제어 >
0~9999까지의 값(목적지)을 keypad로 입력하면, 
FND에서 이전 출력한 숫자 값에서 COUNT UP 또는 COUNT DOWN을 하면서 
목적지에 도달합니다. 
<GUI>
목적지를 입력할 때, "YOUR DESTINATION : (목적지)" 출력
목적지에 도착했을 때, "ARRVIED : (목적지)"출력 
    
//pro4(PROGRAM4) : PWM LED
<GUI>
Horizontal slider (범위 0~255)의 키를 조정을 하면, 
LCD 숫자도 동일한 숫자를 출력을 하고, 
<라즈베리파이 GPIO 제어 >
동시에 라즈베리파이의 wiringPiSetupGpio()모드에서, 0번핀에 연결된
LED의 밝기가 조정됩니다. 
************************************///

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

//pwm led 밝기 조절 실행 
void MainWindow::pwmled(int num){
    softPwmWrite(PWM_PIN,num);
}

//pwm 초기 세팅 
void MainWindow::pwmledsetting(){
    wiringPiSetupGpio();
    pinMode(PWM_PIN, OUTPUT);
    softPwmCreate(PWM_PIN,0,255);
}

//pwm led off (종료)
void MainWindow::pwmled_terminate(){
    softPwmWrite(PWM_PIN,0);
}


//joystick 프로세스 실행 
void MainWindow::ExecuteProgram_pro1()
{

    //joystick 프로세스 생성
    pro1 = new QProcess(this);

    //시그널 슬롯 설정
    QObject::connect(pro1,  SIGNAL(readyReadStandardOutput()), this, SLOT(PrintMsg_pro1()));

    //지정한파일 실행
    pro1->start("qtPrj/joy1227");

    //프로세스 시작 확인 메세지
    if(pro1->waitForStarted() == false)
    {
        ui->textBrowser->insertPlainText("External Program Starting Error\n");
    }
    else
    {
        ui->textBrowser->insertPlainText("External Program Started\n");
    }


}

//joystick 프로세스가 보내는 메세지 출력 
void MainWindow::PrintMsg_pro1()
{
    QByteArray data;
    data = pro1->readAllStandardOutput();
    qDebug() << data;
    int num=0;

    //받은 메세지 중 특정값을 *구분자를 사용하여, 찾아낸다. 
    // 예를 들어, *number* 이런식으로 
    //split은 구분자를 기준으로 분리해서 list로 만들어준다 
    QList<QByteArray> arr= data.split('*');

    //arr 길이가 1개이하 이면, 전달받은 메세지에 내가 원하는 값이 들어있지 않음 
    if(arr.length()>1){

        //qDebug() <<arr[0];
        //printf("\n");
        //qDebug() <<arr[1];
        //qDebug() << "printmsg";
        bool ok;
        num = arr[1].toInt(&ok,10);//qbyte 형태이기 때문에, 숫자로 변환 필요 

        //printf("%d\n",num);
        qDebug() << "result: "<<num;
        if(num <= 30 && num >= -30){//horizontal slider의 범위 -30~+30안의 값일 경우, 
            ui->horizontalSlider_2->setValue(num); //해당위치로 slider의 키는 이동
        }

    }
    ui->textBrowser->insertPlainText(data); //전달받은 메세지를 출력 
    ui->textBrowser->moveCursor(QTextCursor::End);//커서 이동 
    data.clear();
}

//led on off 프로세스 실행 
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

//joystick 프로세스가 보내는 메세지 처리 
void MainWindow::PrintMsg_pro2()
{
    QByteArray data;
    data = pro2->readAllStandardOutput();
    QByteArray msg("ON");

    if(data.contains(msg)){//메세지가 on이면, 
        ui->label_7->setPixmap(img[1]);//led on 이미지 출력 

    }else {//off 이면, 
        ui->label_7->setPixmap(img[0]);//led off 이미지 출력 
    }


    ui->textBrowser_2->insertPlainText(data);
    ui->textBrowser_2->moveCursor(QTextCursor::End);
    data.clear();
}

//elevator 프로세스 실행 
void MainWindow::ExecuteProgram_pro3()
{
    pro3 = new QProcess(this);
    QObject::connect(pro3,  SIGNAL(readyReadStandardOutput()), this, SLOT(PrintMsg_pro3()));
    pro3->start("qtPrj/elevator1227");
    ui->textBrowser_3->insertPlainText("pro3 start");
}

//elevator 메세지 출력 
// 메세지 1: your destination 목적지 
// 메세지 2: arrived at 목적지 
void MainWindow::PrintMsg_pro3()
{
    QByteArray data;
    data = pro3->readAllStandardOutput();
    ui->textBrowser_3->insertPlainText(data);
    ui->textBrowser_3->moveCursor(QTextCursor::End);
    data.clear();
}

//joystick 프로세스 종료 
void MainWindow::pro1_terminate()
{
    pro1->terminate();
    ui->textBrowser->insertPlainText("pro1 terminate");

}

//LED ON OFF  프로세스 종료 
void MainWindow::pro2_terminate()
{
    pro2->terminate();
    ui->textBrowser_2->insertPlainText("pro2 terminate");

}

//ELEVATOR  프로세스 종료 
void MainWindow::pro3_terminate()
{
    pro3->terminate();
    ui->textBrowser_3->insertPlainText("pro3 terminate");

}
