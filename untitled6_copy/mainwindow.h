#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>


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
    void ExecuteProgram_txtmsg();
    void ExecuteProgram_pro1();
    void ExecuteProgram_pro2();
    void pro1_kill();
    void pro2_kill();
    void txtmsg_kill();

    void PrintMsg();
    // void PrintMsg_pro2();

private:
    Ui::MainWindow *ui;
    QProcess *textMsgProcess;
    QProcess *pro1;
    QProcess *pro2;

};
#endif // MAINWINDOW_H
