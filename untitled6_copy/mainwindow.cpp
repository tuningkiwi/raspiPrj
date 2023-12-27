#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QProcess>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // QProcess process;
    // QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    // env.insert("TMPDIR", "C:\\Qt\\program"); // Add an environment variable
    // process.setProcessEnvironment(env);
    // process.start("hello");
    connect(ui->pushButton, SIGNAL(clicked()),
            this, SLOT(ExecuteProgram_txtmsg()));

    connect(ui->pushButton_2, SIGNAL(clicked()),
            this, SLOT(ExecuteProgram_pro1()));

    connect(ui->pushButton_3, SIGNAL(clicked()),
            this, SLOT(ExecuteProgram_pro2()));

    connect(ui->pushButton_6, SIGNAL(clicked()),
            this, SLOT(txtmsg_kill()));

    connect(ui->pushButton_4, SIGNAL(clicked()),
            this, SLOT(pro1_kill()));

    connect(ui->pushButton_5, SIGNAL(clicked()),
            this, SLOT(pro2_kill()));



    // connect(ui->pushButton, SIGNAL(clicked()),
    //         this, SLOT(ExecuteProgram()));

    // QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    // env.insert("TMPDIR", "C:\\Qt\\program"); // Add an environment variable
    // process.setProcessEnvironment(env);
    // process.start("hello");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::PrintMsg()
{
    QByteArray data;
    data = textMsgProcess->readAllStandardOutput();
    //qDebug() << "printmsg";
    ui->textBrowser->insertPlainText(data);
    ui->textBrowser->moveCursor(QTextCursor::End);
    data.clear();
}

void MainWindow::ExecuteProgram_txtmsg()
{
    //QString path = "C:/Qt/test";
    qDebug() << "hello";

    //QString program = QString("C:/Qt/program/hello.exe");
    textMsgProcess = new QProcess(this);

    // QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    // env.insert("TMPDIR", "C:\\Qt\\program"); // Add an environment variable
    // textMsgProcess->setProcessEnvironment(env);
    // textMsgProcess->start("hello.exe");


    QObject::connect(textMsgProcess,  SIGNAL(readyReadStandardOutput()), this, SLOT(PrintMsg()));
    textMsgProcess->start("/home/pi/Work/qt/build-untitled8-Desktop-Release/untitled8");



    // QProcess process;
    // process.startCommand("del /s *.txt");
    // same as process.start("del", QStringList() << "/s" << "*.txt");


    /*answer */
    //textMsgProcess->start("D:\\work\\QTAPP\\qt1226\\build-untitled8-Desktop_Qt_6_6_1_MinGW_64_bit-Release\\release\\untitled8.exe");
    //(*textMsgProcess).start("C:\\Qt\\program\\hello.exe"); 실행안됨

    // QObject *parent;
    // ...
    //     QString program = "./path/to/Qt/examples/widgets/analogclock";
    // QStringList arguments;
    // arguments << "-style" << "fusion";

    // QProcess *myProcess = new QProcess(parent);
    // myProcess->start(program, arguments);

    if(textMsgProcess->waitForStarted() == false)
    {
        ui->textBrowser->insertPlainText("External Program Starting Error\n");
    }
    else
    {
        ui->textBrowser->insertPlainText("External Program Started\n");
    }


}


void MainWindow::ExecuteProgram_pro1()
{
    pro1 = new QProcess(this);
    pro1->start("/home/pi/Work/ras/gpio_out/led5");
    ui->textBrowser->insertPlainText("pro1 start");
}

void MainWindow::ExecuteProgram_pro2()
{
    pro2 = new QProcess(this);
    QObject::connect(pro2,  SIGNAL(readyReadStandardOutput()), this, SLOT(PrintMsg_pro2()));
    pro2->start("/home/pi/Work/ras/digit/elevator1221");
    ui->textBrowser->insertPlainText("pro2 start");
}

// void MainWindow::PrintMsg_pro2()
// {
//     QByteArray data;
//     data = textMsgProcess->readAllStandardOutput();
//     //qDebug() << "printmsg";
//     ui->textBrowser->insertPlainText(data);
//     ui->textBrowser->moveCursor(QTextCursor::End);
//     data.clear();
// }

void MainWindow::txtmsg_kill()
{
    textMsgProcess->terminate();
    ui->textBrowser->insertPlainText("txtmsg kill");

}


void MainWindow::pro1_kill()
{
    pro1->terminate();
    ui->textBrowser->insertPlainText("pro1 kill");

}


void MainWindow::pro2_kill()
{
    pro2->terminate();
    ui->textBrowser->insertPlainText("pro2 kill");

}
