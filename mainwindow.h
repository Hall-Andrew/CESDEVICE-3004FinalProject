#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QTime>
#include <QMainWindow>
#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_OnOffButton_released();

    void on_TimerButton_released();

    void on_UpButton_released();

    void on_DownButton_released();

    void on_LockButton_released();

    void on_ContactButton_released();

    void on_EnterButton_released();



    void on_BackButton_released();

private:
    Ui::MainWindow *ui;
    bool onOffState;
    QTime time;
    bool lockState;
    bool contactState;
    double powerState;
    float amps;
    int totalDuration;
    void resetDisplay();
    void createMenu();
    void resetValues();

};
#endif // MAINWINDOW_H
