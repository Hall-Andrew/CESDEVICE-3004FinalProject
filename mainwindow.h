#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QTime>
#include <QTimer>
#include <QMainWindow>
#include <QWidget>
#include <QVector>
#include "record.h"

/*EDITED BY JULIEN NOV 21*/


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class record;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    bool onOffState;
    int time;
    bool lockState;
    bool contactState;
    double powerState;
    QString waveForm; //added waveform variable for record.
    float amps;
    int totalDuration;
    QTimer *timer;
    void resetDisplay();
    void createMenu();
    void resetValues();
    /*The two values which will take in the record. Currently buggy, as apparently record is 'incomplete'
     * record rec;
     * QVector<record> Record_History;
     *
     *
    */
     void setDefaultMenuSelections();



private slots:
    void on_OnOffButton_released();

    void on_TimerButton_released();

    void on_UpButton_released();

    void on_DownButton_released();

    void on_LockButton_released();

    void on_ContactButton_released();

    void on_EnterButton_released();

    void updateTimerDisplay();

    void on_BackButton_released();
//new buttons Nov 21
    void on_Record_released();

    void on_RecordHistory_released();

};
#endif // MAINWINDOW_H
