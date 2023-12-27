#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QPixmap>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();


private slots:
    void ExecuteProgram_pro1();
    void ExecuteProgram_pro2();
    void ExecuteProgram_pro3();
    void pro1_terminate();
    void pro2_terminate();
    void pro3_terminate();
    void pwmled_terminate();

    void PrintMsg_pro1();
    void PrintMsg_pro2();
    void PrintMsg_pro3();

    void pwmledsetting();
    void pwmled(int num);

private:
    Ui::MainWindow *ui;
    QProcess *pro1;
    QProcess *pro2;
    QProcess *pro3;
    QPixmap img[2];

};
#endif // MAINWINDOW_H
