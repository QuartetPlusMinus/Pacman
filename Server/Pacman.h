//
// Created by viewsharp on 01.12.17.
//

#ifndef ONENIGHTPACMAN_PLAYER_H
#define ONENIGHTPACMAN_PLAYER_H
#include "BaseBeing.h"
#include <string>

using namespace pacman_service;
using namespace std;


class Pacman: public BaseBeing {

public:

    Pacman (unsigned int x, unsigned int y):
            BaseBeing(x, y),
            tryCount(0),
            newDirection(this->direction()){
        set_health(4);
    }

//    void tryStep();

    void getBeing(Being *data) override {
        data->set_health(health());
        data->set_direction(direction());
        data->set_status(status());
        data->mutable_pos()->set_x(pos().x());
        data->mutable_pos()->set_y(pos().y());
    }

    void setNewDirection();

    int tryCount;
    Direction newDirection;

private:

};


#endif //ONENIGHTPACMAN_PLAYER_H
