//
// Created by viewsharp on 01.12.17.
//

#ifndef ONENIGHTPACMAN_BASEBEING_H
#define ONENIGHTPACMAN_BASEBEING_H
#include "service.grpc.pb.h"
#include <string>

using namespace pacman_service;
using namespace std;

class BaseBeing: public Being {

public:

    BaseBeing(): speed(1) {}

    void init(int id, int x, int y);

    void getBeing(Being *data);

    Being *getBeing();

    void step();

private:

    int speed;

};

#endif //ONENIGHTPACMAN_BASEBEING_H
