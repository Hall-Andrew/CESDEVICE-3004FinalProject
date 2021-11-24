#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <iostream>
#define powerTimeOut 30
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //resetDisplay();
    initializeDefaults();
    createMenu();
    ui->StackedWidget->setCurrentIndex(0);
    timer = new QTimer(this);
    powerTimer = new QTimer(this);
    UpdateFrequency(Frq_level);
    UpdateWaveform(Wf_level);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTimerDisplay);
    powerTimer->setInterval(powerTimeOut*1000);
    connect(powerTimer, &QTimer::timeout, this, &MainWindow::on_PowerTimerFired);
    connect(battery,SIGNAL(updateBatteryBar(int)),this,SLOT(updateBatteryLabel(int)));
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_PowerTimerFired(){
    cout<<"Entered function"<<endl;
   if(!timer->isActive()){
       turnDeviceOff();
   }else{
   }
}

void MainWindow::createMenu(){
    ui->menuListWidget->addItem("Start A Session");
    ui->menuListWidget->addItem("View Previous Sessions");

}

void MainWindow::setDefaultMenuSelections(){
    ui->menuListWidget->setCurrentRow(0);

}


void MainWindow::initializeDefaults(){
    onOffState = false;
    time = 0;
    lockState = false;
    paused = false;
    totalDuration = 0;
    Frq_level=0;
    Wf_level=0;
    amps.push_back(AMP_LVL_ONE);
    amps.push_back(AMP_LVL_TWO);
    amps.push_back(AMP_LVL_THREE);
    waveForm.push_back(alpha);
    waveForm.push_back(betta);
    waveForm.push_back(gamma);
    battery= new Battery();
}


void MainWindow::turnDeviceOn(){
    ui->StackedWidget->setCurrentIndex(1);
    setDefaultMenuSelections();
    resetPowerTimer();
    battery->startBatteryDrain();
}

void MainWindow:: turnDeviceOff(){
      ui->StackedWidget->setCurrentIndex(0);
      battery->stopBatteryDrain();
      powerTimer->stop();
}



void MainWindow::on_TimerButton_released()
{
    bool state = ui->ContactButton->isChecked();
      if (!timer->isActive()){
          timer->setInterval(1000);
          if(state){
          timer->start();
          }
      }else
      {
          int seconds = time + 20;
          if(seconds > 60) seconds = 60;
          time = seconds;
      }
      resetPowerTimer();
}

void MainWindow::on_UpButton_released()
{   if(ui->StackedWidget->currentIndex() == 0){
        int index = ui->menuListWidget->currentRow();
        int  newIndex = index - 1;
        if (newIndex<0)
            newIndex = 0;
        ui->menuListWidget->setCurrentRow(newIndex);
    }

    if(ui->StackedWidget->currentIndex() == 2){
        int currentAmp  = ui->ProgressBarWidget->value();
        int newAmp =  currentAmp + 50;
         ui->ProgressBarWidget->setValue(newAmp);
    }
      resetPowerTimer();
}


void MainWindow::on_DownButton_released()
{
  if(ui->StackedWidget->currentIndex() == 0){
    int index = ui->menuListWidget->currentRow();
    int  newIndex = index + 1;
    if (newIndex >=  ui->menuListWidget->count())
        return;
    ui->menuListWidget->setCurrentRow(newIndex);
  }



  if(ui->StackedWidget->currentIndex() == 2){
      int currentAmp  = ui->ProgressBarWidget->value();
      int newAmp =  currentAmp - 100;
      if (newAmp < 0)
          newAmp = 0;
       ui->ProgressBarWidget->setValue(newAmp);
    }

    resetPowerTimer();
}



void MainWindow::on_LockButton_released()
{
      resetPowerTimer();
}
/*
void MainWindow::on_Button_released()
{
      resetPowerTimer();
}
*/

void MainWindow::on_EnterButton_released()
{
    int index = ui->StackedWidget->currentIndex();
    if(index == 0)
        return;

    if( ui->StackedWidget->currentIndex() == 1){
       startSession();
       return;
    }

      resetPowerTimer();
}

void MainWindow::on_BackButton_released()
{
    int prevIndex;
    int index = ui->StackedWidget->currentIndex();
    //modified it so recordHisotry does not send you to the start screen.  If the index is 4 (record history), it'll send you back to start
    if (index>3)
    {
        prevIndex=0;
    }
    else
    {
        prevIndex = index - 1 ;
    }
      if (prevIndex >= 0){
          ui->StackedWidget->setCurrentIndex(prevIndex);
      }
}


void MainWindow::updateTimerDisplay()
{
    time = time - 1;
    QString timeString = QTime(0, time).toString();
    ui->TimeLabel->setText(timeString);
    if(time <= 0){
        timer->stop();
        resetPowerTimer();
    }
}
//Buttons for record and record History. Record History could use a menu.
//Record isnt hooked up to any data atm see console/ Andrew
void MainWindow::on_Record_released()
{

        Record* rec=new Record(waveForm[Wf_level],amps[Frq_level],totalDuration,battery->getBatteryPercentage());
        recordList.append(rec);

        cout<<"Amps: ";
        cout<<rec->getFrequency();
        cout<<" Duration: "<<rec->getDuration();
        cout<<" PowerState: ";
        cout<<rec->getPowerLevel()<<endl;


}
//switchs to page 4 of the stackedWidet and should create a page with all recording sessions
void MainWindow::on_RecordHistory_released()
{
    ui->StackedWidget->setCurrentIndex(4);
    ui->recordhistory->clear();
    for (int q=0; q<recordList.size(); q++)
    {
        ui->recordhistory->addItem("Session "+QString::number(q+1)+" "+recordList[q]->getRecord());
    }
}
//Functions to update the wavelenght and frequencies
void MainWindow:: UpdateFrequency(int level)
{
    ui->Frequncy->clear();
    QString dummy= QString::number(amps[level])+" Hz";
    ui->Frequncy->append(dummy);
}
void MainWindow:: UpdateWaveform(int level)
{
    ui->Waveform->clear();
    ui->Waveform->append(waveForm[level]);
}
void MainWindow::on_ChangeFrequency_released()
{
    if (Frq_level>=2)
    {
        Frq_level=0;
    }
    else
    {
       Frq_level++;
    }
    UpdateFrequency(Frq_level);
}

void MainWindow::on_ChangeWaveform_released()
{
    if (Wf_level>=2)
    {
        Wf_level=0;
    }
    else
    {
       Wf_level++;
    }
    UpdateWaveform(Wf_level);
}

void MainWindow::on_TurnOnOffButton_released()
{
    int index = ui->StackedWidget->currentIndex();
    if  (index == 0 ){
       turnDeviceOn();
    }else turnDeviceOff();

}


void MainWindow:: resetPowerTimer(){
    powerTimer->stop();
    powerTimer->setInterval(powerTimeOut*1000);
    powerTimer->start();
}


void MainWindow::on_OnOffButton_released(){

}
void MainWindow::startSession(){
    ui->StackedWidget->setCurrentIndex(2);
    // QString text = ui->WavelengthListWidget->currentItem()->text();
       //ui->WaveFormLabel->setText(text);
       time  = 20;
    resumeSession();


    //waveForm=text;
}

void MainWindow::on_ContactButton_released(){

}

void MainWindow::resumeSession(){
    QTime t = QTime(0,time);
    ui->TimeLabel->setText(t.toString());
 if(!ui->ContactButton->isChecked()){
     return;
 }
     powerTimer->stop();
}

void MainWindow::on_ContactButton_stateChanged(int arg1)
{
    bool state = ui->ContactButton->isChecked();
    if((timer->isActive()) && (!state)){
        timer->stop();
        paused = true;
    } else if (paused && state){
       resumeSession();
       timer->start();
    }

}

void MainWindow::updateBatteryLabel(int batteryPercentage){
    ui->batteryPercentageBar->setValue(batteryPercentage);
    on_batteryLevel_valueChanged(batteryPercentage);
}

void MainWindow::chargeBattery()
{
    // Charge the battery
    //battery->charge();

    // Get the new value
    //int newPercent = int(battery->getBatteryLevel());

    // Update the battery percentage bar
   //ui->batteryPercentageBar->setValue(newPercent);
}
