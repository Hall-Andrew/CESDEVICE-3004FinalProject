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
    ui->RecordHistory->setEnabled(false);
    UpdateFrequency(Frq_level);
    UpdateWaveform(Wf_level);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTimerDisplay);
    connect(powerTimer, &QTimer::timeout, this, &MainWindow::on_PowerTimerFired);
    connect(battery,SIGNAL(updateBatteryBar(int)),this,SLOT(onBatteryLevelChanged(int)));
    connect(battery,SIGNAL(shutDown()),this,SLOT(outOfPower()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_PowerTimerFired(){
    cout<<"Entered function"<<endl;
    if(!timer->isActive()) {
        turnDeviceOff();
    }else{
    }
}

void MainWindow::createMenu(){
    ui->menuListWidget->addItem("Start A Session");
    ui->StackedWidget->setCurrentIndex(0);
  //  ui->menuListWidget->addItem("View Previous Sessions");
}

void MainWindow::setDefaultMenuSelections(){
    ui->menuListWidget->setCurrentRow(0);
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
    timer = new QTimer(this);
    powerTimer = new QTimer(this);
    powerTimer->setInterval(powerTimeOut*1000);
    displayTimer = new CountDownClock(20);
}


void MainWindow::turnDeviceOn(){
    ui->StackedWidget->setCurrentIndex(1);
    setDefaultMenuSelections();
    resetPowerTimer();
    battery->startBatteryDrain();
}

void MainWindow:: turnDeviceOff(){
      battery->stopBatteryDrain();
      powerTimer->stop();
      ui->StackedWidget->setCurrentIndex(0);
      ui->ContactButton->setCheckState(Qt::Unchecked);

      cout << totalDuration << endl;

      // Delete instance to go back to default setting
      delete displayTimer;

      // Create new instance for when device is turned on
      displayTimer = new CountDownClock(20);
      totalDuration = 0;
}

void MainWindow::on_TimerButton_released()
{
    // The defaults can be changed here
    // open to interpretation
    if(time + 20 > 60) {
        time = 60;
        seconds = 0;
    } else {
        time = time + 20;
    }
    //Added for implementation of nicer looking timer, number input is "minute length" feel free to fix this if ive put in some other value /Andrew-
    displayTimer->setMinutes(time);
    displayTimer->setSeconds(seconds);
    ui->timeLabel->display(displayTimer->getDisplayNumbers());
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

    if(ui->StackedWidget->currentIndex() == 2){
        int currentAmp  = ui->ProgressBarWidget->value();
        int newAmp =  currentAmp + 50;
         ui->ProgressBarWidget->setValue(newAmp);
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
  if (ui->StackedWidget->currentIndex()==3)
  {
      int index = ui->recordhistory->currentRow();
      cout<< index <<endl;
      int  newIndex = index + 1;
      if (newIndex<0)
          newIndex = 0;
      ui->recordhistory->setCurrentRow(newIndex);


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
    if (index == 3)
    {
        ui->StackedWidget->setCurrentIndex(5);
        ui->RecordingFull->clear();
        ui->RecordingFull->append("Session #"+QString::number(ui->recordhistory->currentRow()+1)+"\n");
        ui->RecordingFull->append(recordList[ui->recordhistory->currentRow()]->print());
    }

      resetPowerTimer();
}

void MainWindow::on_BackButton_released()
{
    int prevIndex;
    int index = ui->StackedWidget->currentIndex();
    //modified it so recordHistory does not send you to the start screen.  If the index is 4 (record history), it'll send you back to start
    if (index>3)
    {
        prevIndex=0;
    }
    else
    {
        prevIndex = index - 1 ;
    }
      if (prevIndex > 0){
          ui->StackedWidget->setCurrentIndex(prevIndex);
      }
}


void MainWindow::updateTimerDisplay()
{
    if(seconds == 0) {
        time -= 1;
        seconds = 60;
    }else{
        seconds -= 1;
    }

    // Duration only increases with each second the update timer updates
    totalDuration += 1;

    displayTimer->countdown();//This should countdown each second properly

    QString timeString = QTime(0, time).toString();
    //ui->TimeLabel->setText(timeString); This is your old timer label Ive left cause its late at night and I dunno if my speed implementation is ok so you could theoretically revert/ Andrew

    ui->timeLabel->display(displayTimer->getDisplayNumbers()); //This gets the proper number to be displayed from the class/ Andrew

    //I didnt touch this either just commented it out/Andrew
    /*/
    if(time <= 0){
        timer->stop();
        resetPowerTimer();
    }
    /*/

    if(displayTimer->isTimerFinished()){ //Literally yours but uses my stop boolean instead /Andrew
        timer->stop();

        resetPowerTimer();
    }
}
//Buttons for record and record History. Record History could use a menu.
//Record isnt hooked up to any data atm see console/ Andrew
void MainWindow::on_Record_released()
{

        if(ui->RecordHistory->isEnabled()==false){ui->RecordHistory->setEnabled(true);}
        // Total duration is stored as seconds, could change it to minutes but you have to change it here - Aaron
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

    ui->StackedWidget->setCurrentIndex(3);
    ui->recordhistory->clear();
    for (int q=0; q<recordList.size(); q++)
    {
        ui->recordhistory->addItem("Session "+QString::number(q+1)+" "+recordList[q]->getRecord());

    }
    int a=ui->recordhistory->count();
    cout<<a<<endl;
    ui->recordhistory->setCurrentRow(0);
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
    // should we even use this? i feel like the state change slot covers this
}

void MainWindow::resumeSession(){
    ui->timeLabel->display(displayTimer->getDisplayNumbers());
    if(!ui->ContactButton->isChecked()){
        return;
    }
    powerTimer->stop();
}

void MainWindow::on_ContactButton_stateChanged(int arg1)
{
    bool state = ui->ContactButton->isChecked();
    if (!timer->isActive()){
        timer->setInterval(1000);
        if(state){
            cout << "Timer started" << endl;
            timer->start();
        }
    } else if((timer->isActive()) && (!state)){
        timer->stop();
        paused = true;
    } else if (paused && state){
       resumeSession();
       timer->start();
    }

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
