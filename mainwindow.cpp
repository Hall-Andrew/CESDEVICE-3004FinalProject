#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    onOffState = false;
    time = QTime(0,0);
    lockState = false;
    contactState = false;
    powerState = 100;
    amps = 0;
    totalDuration = 0;
    //resetDisplay();
    createMenu();

}






MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createMenu(){
    ui->menuListWidget->addItem("Start A Session");
    ui->menuListWidget->addItem("View Previous Sessions");


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
    time = QTime(0,0);
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

}

void MainWindow::on_UpButton_released()
{

}

void MainWindow::on_DownButton_released()
{

}

void MainWindow::on_LockButton_released()
{

}

void MainWindow::on_ContactButton_released()
{

}

void MainWindow::on_EnterButton_released()
{
    QListWidgetItem* item = ui->menuListWidget->currentItem();
   // qDebug()<<item->text();
}
