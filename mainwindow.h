#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QTime>
#include <QTimer>
#include <QMainWindow>
#include <QWidget>
#include <QVector>
#include <time.h>
#include "record.h"
#include "battery.h"
#include "countdownclock.h"

#define AMP_LVL_ONE .5
#define AMP_LVL_TWO 77
#define AMP_LVL_THREE 100
#define alpha "Alpha"
#define betta "Beta"
#define gamma "Gamma"
/*
 * The main function of the program, acts as the recipient for signals and sends out the apporpriate response.
 *
 * Variables:
 *      bool onOffState: boolean which tracks if the device is "on" or "off
 *      bool contactTimerFired: boolean which tracks how long contact object has been active. Sets it to false if enough time has passed.
 *      int time: holds the value which is passed to countdownclock to set up the time.
 *      int seconds: holds the number of seconds required for totalDuration.
 *      QTimer* powerTimer: timer for the "time out" feature of the device.
 *      bool lockstate: tracks if the device is "locked"
 *      bool paused: tracks if the device is "paused"
 *      countDownClock displayClock: countdownCLock object which is the primary timer for sessions.
 *      int totalDuration: holds the value of the time elasped during a session.
 *      Battery* battery: battery object.
 *      int Frq_level: Holds a value which is meant to access a value in amps.
 *      int Wf_level: Holds a value which is meant to access a value in waveform
 *      QVector<double> amps: vector array which holds the defined values: AMP_LVL_ONE,AMP_LVL_TWO,AMP_LVL_THREE
 *      QVector<QString> waveForm: vector array which holds the deined stringvalues: alpha,betta,gamma
 *      QTimer *timer: timer object which holds the time that is being displayed by displayClock
 *      QVector<Record*> recordList:vector list which holds record objects, used to display session histories
 *      QTimer* contactTimer: timer which tracks how long it has been since the device had last been touched.
 *
 * Functions:
 *      resetDisplay(): resets the display to the default settings.
 *      createMenu():sets up the main menu for the device
 *      resetValues(): resets the values to their default settings
 *      UpdateFrequency(int lvl):Changes the Frq_level by the value of lvl, up to a maximum of two. Once the level has been changed, the value of the devices frequency changes to the corresponding
 *                              value in amps.
 *      UpdateWaveform(int lvl):Changes the Wf_level by the value of lvl, up to a maximum of two. Once the level has been changed, the value of the devices frequency changes to the corresponding
 *                              value in waveForm.
 *      setDefaultMenuSelections(): adds objects to the menu widget for the user to select.
 *      initializeDefaults(): sets the default values of the device.
 *      turnDeviceOff(): turns the device off. As in it sets the onOffState to false.
 *      turnDeviceOn(): turns the device on. As in it sets the onOffState to true.
 *      resetPowerTimer(): Resets the power timer to the starting time.
 *      startSession(): Changes the window to the session page and start the countdown session.
 *      resumeSession(): Starts or resumes (if contact is interuppted) a session.
 *      void chargeBattery(): Sets the battery life of the battery to 100.
 *
 * Signals:
 *      on_TimerButton_released(): increases the time variable by 20 until it reaches 60. After which, the timer will be set to 20.
 *      on_UpButton_released(): If there is a list widget currently active on the device, this button will move up the list by one.
 *      on_DownButton_released():If there is a list widget currently active on the device, this button will move down the list by one.
 *      on_LockButton_released(): toggles the lockstate boolean as well setting the lockimage to true.
 *      on_ContactButton_released(): toggles contactTimerFired to set contact to true. If time has been set and in the user is in the session widget, a session will begin.
 *      on_ContactTimerFired(): if the power timer ends, this changes contactTimerFired to true and ends contact.
 *      on_EnterButton_released(): 'enters" (as in activates differently depending on the page) a list item.
 *      updateTimerDisplay(): updates the timer display
 *      on_PowerTimerFired(): If PowerTimer runs out, then this function shuts off the device to simulate a time out.
 *      on_BackButton_released(): returns to the prior stackedWidget page.
 *      on_Record_released(): Creates a record object which is then added to recordList.
 *      on_RecordHistory_released(): Changes to the Record history page and allocated list items based on the values in recordList.
 *      on_ChangeFrequency_released(): changes Frq_lvl by 1 and then calls update_Frequency(Frq_lvl).
 *      on_ChangeWaveform_released(): changes Wf_lvl by 1 and then calls update_waveForm(Wf_lvl)
 *      on_TurnOnOffButton_released(): toggles the powerstate, as well as shutting off/turning on the device
 *      on_ContactButton_stateChanged(int arg1): Changes contact to true/false depedning on it's prior state. If on session page as well, this will set the button to true.
 *      onBatteryLevelChanged(int percentage): updates the battery life based on the percentage
 *      on_PowerSurgeButton_released(): simulates a powersurge, shutting off the device permanently.
 *      outOfPower(): turns the device off when battery returns empty.
 *      warningReciever(QString): outputs the warnings of the batteries.
 *      on_FinishSesh_released(): Ends the session as if the user sat there for the elapsed time.
 *      on_ChargeButton_released(): charges the battery.
 * */

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
    bool contactTimerFired;
    int time;
    int seconds;
    QTimer *powerTimer;
    bool lockState;
    bool paused;
    CountDownClock* displayClock;
    int totalDuration;
    Battery* battery;
    int Frq_level;
    int Wf_level;
    QVector<double> amps;
    QVector<QString> waveForm;
    QTimer *timer;
    QVector<Record*> recordList;
    QTimer* contactTimer;
    QDateTime therapyDateInfo;
    QString dateInfo;

    void resetDisplay();
    void createMenu();
    void resetValues();
    void UpdateFrequency(int lvl);
    void UpdateWaveform(int lvl);

    void setDefaultMenuSelections();
    void initializeDefaults();
    void turnDeviceOff();
    void turnDeviceOn();
    void resetPowerTimer();
    void startSession();
    void resumeSession();
    void chargeBattery();


private slots:
    void on_TimerButton_released();
    void on_UpButton_released();
    void on_DownButton_released();
    void on_LockButton_released();
    void on_ContactButton_released();
    void on_ContactTimerFired();
    void on_EnterButton_released();
    void updateTimerDisplay();
    void on_PowerTimerFired();
    void on_BackButton_released();
    void on_Record_released();
    void on_RecordHistory_released();
    void on_ChangeFrequency_released();
    void on_ChangeWaveform_released();
    void on_TurnOnOffButton_released();
    void on_ContactButton_stateChanged(int arg1);
    void onBatteryLevelChanged(int percentage);
    void on_PowerSurgeButton_released();
    void outOfPower();
    void warningReciever(QString);
    void on_FinishSesh_released();
    void on_ChargeButton_released();
    void on_realisticPowerButton_stateChanged(int arg1);
    void on_realisticPowerButton_clicked();
    void on_realisticPowerButton_released();
};
#endif // MAINWINDOW_H
