#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QTime>
#include <QTimer>
#include <QMainWindow>
#include <QWidget>
#include <QVector>
#include "record.h"
#define AMP_LVL_ONE .5
#define AMP_LVL_TWO 77
#define AMP_LVL_THREE 100
#define alpha "Alpha"
#define betta "Beta"
#define gamma "Gamma"


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
    int totalDuration;
    //these four set the waveform and frequency of the machine. The vectors have hard coded values defined above and we iterate through using Frq_level for Frequency and Wf_Level for waveform
    int Frq_level;
    int Wf_level;
    QVector<double> amps;
    QVector<QString> waveForm;
    // Slots used ^^: On_FrqButtonRealeased, On_WFButtonRealeased, updateFreq,updateWF
    QTimer *timer;
    QVector<Record*> recordList;
    void resetDisplay();
    void createMenu();
    void resetValues();
    void UpdateFrequency(int lvl);//takes in the new level and changes the frequency box
    void UpdateWaveform(int lvl);//^^ same thing
     void setDefaultMenuSelections();
     void initializeDefaults();



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

    void on_ChangeFrequency_released();
    void on_ChangeWaveform_released();
};
#endif // MAINWINDOW_H
