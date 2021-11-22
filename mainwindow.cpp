#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    onOffState = false;
    time = 0;
    lockState = false;
    contactState = false;
    powerState = 100;
    amps = 0;
    totalDuration = 0;
    waveForm="";
    //resetDisplay();
    createMenu();
    ui->StackedWidget->setCurrentIndex(0);
    timer = new QTimer(this);
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
    amps = 100;
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
}}


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
        if (nextIndex< ui->StackedWidget->count()){
            ui->StackedWidget->setCurrentIndex(nextIndex);
    }

    if( ui->StackedWidget->currentIndex() == 3){
        QString text = ui->WavelengthListWidget->currentItem()->text();
        ui->WaveFormLabel->setText(text);
        time  = 20;
        QTime t = QTime(0,time);
        ui->TimeLabel->setText(t.toString());
    }


}

void MainWindow::on_BackButton_released()
{
    int index = ui->StackedWidget->currentIndex();
      int prevIndex = index - 1 ;
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
<<<<<<< HEAD

=======
//Buttons for record and record History. Record History could use a menu.
void MainWindow::on_Record_released()
{
    /*
    if (waveForm=="")
    {
        ui->ErrorMessage->append("Error! Can't make a record for session that does not exist");

    }
    else
      {
        record rec=new record(waveForm,amps,totalDuration,powerState);
        Rec_Hist.append(rec);
    }
    */
}

void MainWindow::on_RecordHistory_released()
{
    QString("foo");
   /* for (int q=0; q<Vec_Hist.size(); q++)
    {
        Vec_Hist[q].print();
    }*/
}
>>>>>>> c988d4ec25889d72b425a8873461311f398f6105
