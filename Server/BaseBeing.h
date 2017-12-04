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

    BaseBeing(int x, int y) :
            speed(1) {
        set_direction(RIGHT);
        set_status(ALIVE);
        auto *pos = new Point();
        pos->set_x(x);
        pos->set_y(y);
        set_allocated_pos(pos);
    }

    void getBeing(Being *data);

    //Being *getBeing();

    void step();

private:

    int speed;

};

#endif //ONENIGHTPACMAN_BASEBEING_H
