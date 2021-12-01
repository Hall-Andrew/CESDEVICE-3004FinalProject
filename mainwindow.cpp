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
    //makes edges of stackedwidget round
    const int radius = 10;

    QPainterPath path;
    path.addRoundedRect(ui->StackedWidget->rect(), radius, radius);
    QRegion mask = QRegion(path.toFillPolygon().toPolygon());
    ui->StackedWidget->setMask(mask);

    ui->StackedWidget->show();

    //resetDisplay();
    initializeDefaults();
    createMenu();
    ui->RecordHistory->setEnabled(false);
    ui->Record->setEnabled(false);
    ui->Record->setVisible(false);
    ui->BackButton->setEnabled(false);
    UpdateFrequency(Frq_level);
    ui->WaveformButton->setEnabled(false);
    ui->ChangeFrequency->setEnabled(false);
    UpdateWaveform(Wf_level);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTimerDisplay);
    connect(powerTimer, &QTimer::timeout, this, &MainWindow::on_PowerTimerFired);
    connect(contactTimer, &QTimer::timeout, this, &MainWindow::on_ContactTimerFired);
    connect(battery,SIGNAL(updateBatteryBar(int)),this,SLOT(onBatteryLevelChanged(int)));
    connect(battery,SIGNAL(shutDown()),this,SLOT(outOfPower()));
    connect(battery,SIGNAL(batteryMessage(QString)),this,SLOT(warningReciever(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_PowerTimerFired(){
    if(!timer->isActive()) {
        turnDeviceOff();
    }
}

void MainWindow::createMenu(){
    ui->menuListWidget->addItem("Start A Session");
    ui->StackedWidget->setCurrentIndex(0);
  //  ui->menuListWidget->addItem("View Previous Sessions");
}

void MainWindow::setDefaultMenuSelections(){
    ui->menuListWidget->setCurrentRow(0);
    ui->ContactExpireListWidget->setCurrentRow(0);
}

void MainWindow::initializeDefaults(){
    onOffState = false;
    time = 0;
    seconds = 0;
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
    ui->batteryPercentageBar->setValue(battery->getBatteryPercentage());
    ui->realisticPowerButton->setChecked(true);
    timer = new QTimer(this);
    powerTimer = new QTimer(this);
    contactTimer = new QTimer(this);
    powerTimer->setInterval(powerTimeOut*1000);
    displayClock = new CountDownClock(20);
    ui->lockedImage->setVisible(false);
}


void MainWindow::turnDeviceOn(){
    ui->StackedWidget->setCurrentIndex(1);
    ui->WaveformButton->setEnabled(true);
    ui->ChangeFrequency->setEnabled(true);
    setDefaultMenuSelections();
    resetPowerTimer();
    battery->startBatteryDrain();
    onOffState=true;
    ui->BackButton->setEnabled(true);
}

void MainWindow:: turnDeviceOff(){
      battery->stopBatteryDrain();
      powerTimer->stop();
      timer->stop();
      ui->StackedWidget->setCurrentIndex(0);
      ui->ContactButton->setCheckState(Qt::Unchecked);
      // Delete instance to go back to default setting
      delete displayClock;
      ui->WaveformButton->setEnabled(false);
      ui->ChangeFrequency->setEnabled(false);

      // Create new instance for when device is turned on
      displayClock = new CountDownClock(20);
      cout << totalDuration << endl;

      // Delete instance to go back to default setting
      delete displayClock;

      // Create new instance for when device is turned on
      displayClock = new CountDownClock(20);
      totalDuration = 0;
      onOffState=false;
      ui->BackButton->setEnabled(false);
      lockState=false;
      ui->lockedImage->setVisible(false);
}

void MainWindow::on_TimerButton_released()
{
    if(!lockState){
        time+=20;
        if(time>60){
            time = 20;
        }
        //Added for implementation of nicer looking timer, number input is "minute length" feel free to fix this if ive put in some other value /Andrew-
        displayClock->setMinutes(time);
        //displayClock->setSeconds(seconds);
        ui->timeLabel->display(displayClock->getDisplayNumbers());
    }
    resetPowerTimer();
}
void MainWindow::on_UpButton_released()
{
    if(ui->StackedWidget->currentIndex() == 0){
        int index = ui->menuListWidget->currentRow();
        int  newIndex = index - 1;
        if (newIndex<0)
            newIndex = 0;
        ui->menuListWidget->setCurrentRow(newIndex);
    }

    if(ui->StackedWidget->currentIndex() == 2 && !lockState){
        int currentAmp  = ui->ProgressBarWidget->value();
        int newAmp =  currentAmp + 50;
         ui->ProgressBarWidget->setValue(newAmp);
         if(ui->ContactButton->isChecked()){
             battery->setDrainMultiplier(newAmp);
         }
    }
    if (ui->StackedWidget->currentIndex()==3)
    {
        int index = ui->recordhistory->currentRow();
        cout<< index <<endl;
        int  newIndex = index - 1;
        if (newIndex<0)
            newIndex = ui->recordhistory->count()-1;
        ui->recordhistory->setCurrentRow(newIndex);

    }
    if (ui->StackedWidget->currentIndex()==6){
        int index = ui->ContactExpireListWidget->currentRow();
        cout<< index <<endl;
        int  newIndex = index - 1;
        if (newIndex<0)
            newIndex = ui->ContactExpireListWidget->count()-1;
        ui->ContactExpireListWidget->setCurrentRow(newIndex);
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
  if(ui->StackedWidget->currentIndex() == 2 && !lockState){
      int currentAmp  = ui->ProgressBarWidget->value();
      int newAmp =  currentAmp - 100;
      if (newAmp < 0)
          newAmp = 0;
      ui->ProgressBarWidget->setValue(newAmp);
      if(ui->ContactButton->isChecked()){
          battery->setDrainMultiplier(newAmp);
      }
  }
  if (ui->StackedWidget->currentIndex()==3){
      int index = ui->recordhistory->currentRow();
      cout<< index <<endl;
      int  newIndex = index + 1;
      if (newIndex<0)
          newIndex = 0;
      ui->recordhistory->setCurrentRow(newIndex);
  }
  if (ui->StackedWidget->currentIndex()==6){
     int index = ui->ContactExpireListWidget->currentRow();
     int  newIndex = index + 1;
     if (newIndex<0)
        newIndex = 0;
     ui->ContactExpireListWidget->setCurrentRow(newIndex);
  }
  resetPowerTimer();
}

void MainWindow::on_LockButton_released()
{
      if(!lockState){
          lockState=true;
          ui->lockedImage->setVisible(true);
      }else{
          lockState=false;
          ui->lockedImage->setVisible(false);
      }
      resetPowerTimer();
}

void MainWindow::on_EnterButton_released()
{
    int index = ui->StackedWidget->currentIndex();
    if(index == 0)
        return;
    if( ui->StackedWidget->currentIndex() == 1){
       startSession();
    }
    if (index == 3)
    {
        ui->StackedWidget->setCurrentIndex(5);
        ui->RecordingFull->clear();
        ui->RecordingFull->append("Session #"+QString::number(ui->recordhistory->currentRow()+1)+"\n");
        ui->RecordingFull->append(recordList[ui->recordhistory->currentRow()]->print());
    }
    if (index ==6)
    {
      if (ui->ContactExpireListWidget->currentRow()==0){
          on_Record_released();
      }
      ui->StackedWidget->setCurrentIndex(1);
      startSession();
    }
    resetPowerTimer();
}

void MainWindow::on_BackButton_released()
{
    cout<<ui->StackedWidget->currentIndex()<<endl;
    int prevIndex;
    int index = ui->StackedWidget->currentIndex();
    //modified it so recordHistory does not send you to the start screen.  If the index is 4 (record history), it'll send you back to start
    if (index>3 && index !=5)
    {
        prevIndex=0;
    }
    else{
        if(index == 5){
            prevIndex = index-2;
        }else{
            prevIndex = index - 1 ;
        }
    }
    if (prevIndex > 0){
          ui->StackedWidget->setCurrentIndex(prevIndex);
    }
     resetPowerTimer();
}

void MainWindow::updateTimerDisplay()
{
    // Duration only increases with each second the update timer updates
    totalDuration += 1;
    displayClock->countdown();//This should countdown each second properly
    ui->timeLabel->display(displayClock->getDisplayNumbers()); //This gets the proper number to be displayed from the class/ Andrew
    if(displayClock->isTimerFinished()){ //Literally yours but uses my stop boolean instead /Andrew
        timer->stop();
        resetPowerTimer();
    }
}

//Buttons for record and record History. Record History could use a menu.
void MainWindow::on_Record_released()
{
        if(ui->RecordHistory->isEnabled()==false){ui->RecordHistory->setEnabled(true);}
        // Total duration is stored as seconds, could change it to minutes but you have to change it here - Aaron
        Record* rec=new Record(waveForm[Wf_level],amps[Frq_level],totalDuration,ui->ProgressBarWidget->value(), dateInfo);
        recordList.append(rec);
}

//switchs to page 4 of the stackedWidet and should create a page with all recording sessions
void MainWindow::on_RecordHistory_released()
{
    ui->StackedWidget->setCurrentIndex(3);
    ui->recordhistory->clear();
    for (int q=0; q<recordList.size(); q++)
    {
        ui->recordhistory->addItem("Session "+QString::number(q+1)+" "+recordList[q]->getRecord());

    }
    int a=ui->recordhistory->count();
    ui->recordhistory->setCurrentRow(0);
    resetPowerTimer();
}

//Functions to update the wavelenght and frequencies
void MainWindow:: UpdateFrequency(int level)
{
    QString dummy="Freq: "+QString::number(amps[level])+" Hz";
    ui->frequencyLabel->setText(dummy);

}

void MainWindow:: UpdateWaveform(int level)
{
    ui->waveformLabel->setText("WaveForm: "+waveForm[level]);

}

void MainWindow::on_ChangeFrequency_released()
{
    if(!lockState){
        if (Frq_level>=2){
            Frq_level=0;
        }
        else{
           Frq_level++;
        }
        UpdateFrequency(Frq_level);
    }
    resetPowerTimer();
}

void MainWindow::on_WaveformButton_released()
{
    if(!lockState){
        if (Wf_level>=2){
            Wf_level=0;
        }
        else{
           Wf_level++;
        }
        UpdateWaveform(Wf_level);
    }
    resetPowerTimer();
}


void MainWindow::on_TurnOnOffButton_released()
{
    int index = ui->StackedWidget->currentIndex();
    if  (index == 0 && battery->hasPower()){
       turnDeviceOn();
    }else if(battery->hasPower()){
        turnDeviceOff();
    }
}


void MainWindow:: resetPowerTimer(){
    powerTimer->stop();
    powerTimer->setInterval(powerTimeOut*1000);
    powerTimer->start();
}

void MainWindow::startSession(){
    ui->StackedWidget->setCurrentIndex(2);
    time  = 20;
    totalDuration=0; //added to reset total duration when a session starts
    displayClock->setMinutes(time);
    resumeSession();
}

void MainWindow::on_ContactButton_released(){
    // should we even use this? i feel like the state change slot covers this
}

void MainWindow::resumeSession(){
    ui->timeLabel->display(displayClock->getDisplayNumbers());
    paused = false;
    if(!ui->ContactButton->isChecked()){
        return;
    }
    powerTimer->stop();
}

void MainWindow::on_ContactButton_stateChanged(int arg1)
{
    bool state = ui->ContactButton->isChecked();
    int index = ui->StackedWidget->currentIndex();
    bool ax = contactTimer->isActive();
    int remTime = contactTimer->remainingTime();
    if (!timer->isActive() && onOffState && index !=1 && !paused){
        timer->setInterval(1000);
        if(state){
            timer->start();
            battery->setDrainMultiplier(ui->ProgressBarWidget->value());
        }
        powerTimer->stop();
        ui->Record->setEnabled(true);
        ui->WaveformButton->setEnabled(false);
        ui->ChangeFrequency->setEnabled(false);
        dateInfo = therapyDateInfo.currentDateTime().toString();
    }else if((timer->isActive()) && (!state) && onOffState){
        timer->stop();
        paused = true;
        ui->Record->setEnabled(false);
        battery->resetPowerDraw();
        contactTimer->setInterval(5000);
        contactTimer->start();
        contactTimerFired = false;
        ui->WaveformButton->setEnabled(true);
        ui->ChangeFrequency->setEnabled(true);

    } else if (paused && state && onOffState && !contactTimerFired){
       resumeSession();
       contactTimer->stop();
       timer->start();
       battery->setDrainMultiplier(ui->ProgressBarWidget->value());
       ui->WaveformButton->setEnabled(false);
       ui->ChangeFrequency->setEnabled(false);
    }
}

void MainWindow::on_ContactTimerFired(){
    contactTimerFired = true;
    ui->StackedWidget->setCurrentIndex(6);
    contactTimer->stop();
}

void MainWindow::on_PowerSurgeButton_released()
{
    ui->centralwidget->setEnabled(false);
    ui->StackedWidget->setCurrentIndex(4);
    ui->SurgeLabel->setText("Power Surge Detected. Contact support. \n Device disabled.");
    battery->stopBatteryDrain();
}

void MainWindow::onBatteryLevelChanged(int batteryPercentage)
{
    ui->batteryPercentageBar->setValue(battery->getBatteryPercentage());
    // Change battery colour according to charge level
    if(batteryPercentage <= 10) {
        ui->batteryPercentageBar->setStyleSheet("selection-background-color: #FF0000; background-color: #FFF;");
    } else if(batteryPercentage <= 20) {
        // Yellow
        ui->batteryPercentageBar->setStyleSheet("selection-background-color: #ffff00; background-color: #FFF;");
    } else {
        // otherwise green
        ui->batteryPercentageBar->setStyleSheet("selection-background-color: #00b300; background-color: #FFF;");
    }
}

void MainWindow::chargeBattery()
{
    // Charge the battery
    battery->charge();
    // Update the battery percentage bar
    ui->batteryPercentageBar->setValue(battery->getBatteryPercentage());
}

void MainWindow::outOfPower(){
    turnDeviceOff();
}

void MainWindow::warningReciever(QString warning){
    ui->ErrorMessage->setText(warning);
}
//should finish a session
void MainWindow::on_FinishSesh_released()
{
    if(ui->ContactButton->isChecked()){
        timer->stop();
        totalDuration=time*60;
        time=0;
        ui->timeLabel->display(0.0);
        ui->StackedWidget->setCurrentIndex(6);
        battery->calcDrainSkipped(totalDuration);
        ui->batteryPercentageBar->setValue(battery->getBatteryPercentage());
        ui->ContactButton->setChecked(false);
    }
}

void MainWindow::on_ChargeButton_released()
{
    ui->ErrorMessage->clear();
    battery->charge();
}

void MainWindow::on_realisticPowerButton_released()
{
    battery->toggleRealism();
    if(ui->ContactButton->isChecked()){
       battery->setDrainMultiplier(ui->ProgressBarWidget->value());
    }
}

void MainWindow::on_realisticPowerButton_stateChanged(int){

}

void MainWindow::on_realisticPowerButton_clicked(){

}

