//
// Created by murt on 18.12.17.
//

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <iostream>


MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ButtonConnect_clicked()
{
    std::string host = ui->lineEditIP->text().toStdString();
    std::string name = ui->lineEditName->text().toStdString();
    ui->ButtonConnect->setText("Waiting ...");
}

