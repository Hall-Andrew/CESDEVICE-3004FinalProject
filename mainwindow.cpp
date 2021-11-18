#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    displayed = false;
    initUiElements();

}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initUiElements(){
    connect(ui->helloWorldButton,SIGNAL(pressed()),this,SLOT(printHelloWorld()));
}

void MainWindow::printHelloWorld(){
    QString text;
    if(displayed){
        text= " ";
        displayed = false;
    }else{
        displayed = true;
        text= "Hello World!";
    }
    ui->textLabel->setText(text);
}
