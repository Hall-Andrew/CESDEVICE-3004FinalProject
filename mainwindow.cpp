#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //resetDisplay();
    initializeDefaults();
    createMenu();
    setDefaultMenuSelections();
    ui->StackedWidget->setCurrentIndex(0);
    timer = new QTimer(this);
    UpdateFrequency(Frq_level);
    UpdateWaveform(Wf_level);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTimerDisplay);
}






MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createMenu(){
    ui->menuListWidget->addItem("Start A Session");
    ui->menuListWidget->addItem("View Previous Sessions");
    ui->FrequencyListWidget->addItem("0.5Hz");
    ui->FrequencyListWidget->addItem("77Hz");
    ui->FrequencyListWidget->addItem("100Hz");
    ui->WavelengthListWidget->addItem("Alpha");
    ui->WavelengthListWidget->addItem("Beta");
    ui->WavelengthListWidget->addItem("Gamma");
}

void MainWindow::setDefaultMenuSelections(){
    ui->menuListWidget->setCurrentRow(0);
    ui->FrequencyListWidget->setCurrentRow(0);
    ui->WavelengthListWidget->setCurrentRow(0);
}

void MainWindow::initializeDefaults(){
    onOffState = false;
    time = 0;
    lockState = false;
    contactState = false;
    powerState = 100;
    totalDuration = 0;
    Frq_level=0;
    Wf_level=0;
    amps.push_back(AMP_LVL_ONE);
    amps.push_back(AMP_LVL_TWO);
    amps.push_back(AMP_LVL_THREE);
    waveForm.push_back(alpha);
    waveForm.push_back(betta);
    waveForm.push_back(gamma);


}

/*
void MainWindow::resetDisplay()

{
    ui->TextView->setText("");
    QString timeString = time.toString("hh:mm:ss");
    QString powerString = QString::number(power);
    QString ampString = QString::number(amps);
    QString totalDurationString = QString::number(totalDuration);
    QString onOffStateString = QString::bool(onOffState);
  }


*/
void MainWindow::resetValues()
{
    time = 0;
    powerState = 100; //Need to read from Database
    //amps = 100;
    totalDuration = 0;
}


void MainWindow::on_OnOffButton_released()
{
    QString text = ui->TurnOnOffButton->text();
    if(text == "Turn On")
    {
         ui->TurnOnOffButton->setText("Turn Off");
         onOffState = true;
         resetValues();
    }
       else{
        ui->TurnOnOffButton->setText("Turn On");
        onOffState = false;
    }
   // resetDisplay();
}

void MainWindow::on_TimerButton_released()
{
      if (!timer->isActive()){
          timer->setInterval(1000);
          timer->start();
      }else
      {
          int seconds = time + 20;
          if(seconds > 60) seconds = 60;
          time = seconds;
      }
}

void MainWindow::on_UpButton_released()
{   if(ui->StackedWidget->currentIndex() == 0){
        int index = ui->menuListWidget->currentRow();
        int  newIndex = index - 1;
        if (newIndex<0)
            newIndex = 0;
        ui->menuListWidget->setCurrentRow(newIndex);
    }
    if(ui->StackedWidget->currentIndex() == 1){
        int index = ui->FrequencyListWidget->currentRow();
        int  newIndex = index - 1;
        if (newIndex<0)
            newIndex = 0;
        ui->FrequencyListWidget->setCurrentRow(newIndex);
    }
    if(ui->StackedWidget->currentIndex() == 2){
        int index = ui->WavelengthListWidget->currentRow();
        int  newIndex = index - 1;
        if (newIndex<0)
         newIndex = 0;
        ui->WavelengthListWidget->setCurrentRow(newIndex);
    }
    if(ui->StackedWidget->currentIndex() == 3){
        int currentAmp  = ui->ProgressBarWidget->value();
        int newAmp =  currentAmp + 50;
         ui->ProgressBarWidget->setValue(newAmp);
    }
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

  if(ui->StackedWidget->currentIndex() == 1){
    int index = ui->FrequencyListWidget->currentRow();
    int  newIndex = index + 1;
    if (newIndex >=  ui->FrequencyListWidget->count())
        return;
    ui->FrequencyListWidget->setCurrentRow(newIndex);
  }

  if(ui->StackedWidget->currentIndex() == 2){
    int index = ui->WavelengthListWidget->currentRow();
    int  newIndex = index + 1;
    if (newIndex >=  ui->WavelengthListWidget->count())
        return;
    ui->WavelengthListWidget->setCurrentRow(newIndex);
  }

  if(ui->StackedWidget->currentIndex() == 3){
      int currentAmp  = ui->ProgressBarWidget->value();
      int newAmp =  currentAmp - 100;
      if (newAmp < 0)
          newAmp = 0;
       ui->ProgressBarWidget->setValue(newAmp);
    }
}



void MainWindow::on_LockButton_released()
{

}

void MainWindow::on_ContactButton_released()
{

}

void MainWindow::on_EnterButton_released()
{
    int index = ui->StackedWidget->currentIndex();
    int nextIndex = index + 1 ;
    //I put a -1 here because I added Record_history to the stacked Widget, which messes up the conditional
        if (nextIndex< ui->StackedWidget->count()-1){
            ui->StackedWidget->setCurrentIndex(nextIndex);
    }

    if( ui->StackedWidget->currentIndex() == 3){
        QString text = ui->WavelengthListWidget->currentItem()->text();
        //waveForm=text;
        ui->WaveFormLabel->setText(text);
        time  = 20;
        QTime t = QTime(0,time);
        ui->TimeLabel->setText(t.toString());

    }
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
    }
}
//Buttons for record and record History. Record History could use a menu.
//Record isnt hooked up to any data atm see console/ Andrew
void MainWindow::on_Record_released()
{

        Record* rec=new Record(waveForm[Wf_level],amps[Frq_level],totalDuration,powerState);
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
