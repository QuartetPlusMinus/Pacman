//
// Created by murt on 18.12.17.
//

#ifndef PACMAN_MAINWINDOW_H
#define PACMAN_MAINWINDOW_H

#include <QMainWindow>
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

private
    slots:
    void

    on_ButtonConnect_clicked();

private:
    Ui::MainWindow *ui;
};

#endif //PACMAN_MAINWINDOW_H
