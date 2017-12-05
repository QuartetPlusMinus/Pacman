//
// Created by viewsharp on 01.12.17.
//

#ifndef ONENIGHTPACMAN_BASEBEING_H
#define ONENIGHTPACMAN_BASEBEING_H

//#include "service.grpc.pb.h"
#include <string>
#include <generated/service.pb.h>

using namespace pacman_service;
using namespace std;

class BaseBeing : public Being {

public:

    BaseBeing(unsigned int x, unsigned int y) :
            speed(1) {
        set_direction(RIGHT);
        set_status(ALIVE);
        mutable_pos()->set_x(x);
        mutable_pos()->set_y(y);
    }

    void getBeing(Being *data);

    void step();

    int getSpeed() {
        return speed;
    }
private:

    int speed;

};

#endif //ONENIGHTPACMAN_BASEBEING_H
