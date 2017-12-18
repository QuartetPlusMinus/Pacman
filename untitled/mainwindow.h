//
// Created by murt on 18.12.17.
//

#ifndef UNTITLED_MAINWINDOW_H
#define UNTITLED_MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_ButtonConnect_clicked();

private:
    Ui::MainWindow *ui;
};

#endif //UNTITLED_MAINWINDOW_H
