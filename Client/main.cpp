//
// Created by viewsharp on 01.12.17.
//

#include <string>
#include <iostream>

#include "PlayerConnectionClient.h"
#include "GameLoop.h"
#include <QApplication>
#include <QDesktopWidget>
#include "mainwindow.h"


using namespace std;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

//int main(int argc, char *argv[]) {
//    string host;
//
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//
////    switch (argc) {
////        case 1:
////            cout << "Error: not found player name" << endl;
////            return -1;
////        case 2:
////            host = "localhost";
////            break;
////        default:
////            host = argv[2];
////    }
////
////
////    try {
////        GameLoop game(host, argv[1], host == "localhost");
////    } catch (...) {
////        cout << "Error: server not found" << endl;
////    }
//    return a.exec();
////    return 0;
//}