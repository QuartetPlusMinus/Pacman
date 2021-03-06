//
// Created by viewsharp on 01.12.17.
//

#ifndef ONENIGHTPACMAN_PLAYER_H
#define ONENIGHTPACMAN_PLAYER_H

#include "BaseBeing.h"
#include <string>

using namespace pacman_service;
using namespace std;


class Pacman : public BaseBeing {

public:

    Pacman(unsigned int x, unsigned int y, string &name) :
            BaseBeing(x, y),
            tryCount(0),
            newDirection(this->direction()),
            coins(0) {
        set_health(4);
        this->name = name;
    }

    void setNewDirection();

    int tryCount;
    Direction newDirection;

    string name;

    int coins;

private:

};


#endif //ONENIGHTPACMAN_PLAYER_H
