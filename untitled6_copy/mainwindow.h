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
    void ExecuteProgram_led20();
    void ExecuteProgram_led21();
    void led20kill();
    void led21kill();

    void PrintMsg();

private:
    Ui::MainWindow *ui;
    QProcess *textMsgProcess;
    QProcess *led20;
    QProcess *led21;

};
#endif // MAINWINDOW_H
