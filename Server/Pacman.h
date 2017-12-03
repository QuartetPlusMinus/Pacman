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

    Pacman (int x, int y): BaseBeing(x, y) {
        set_health(10);
    }

private:

};


#endif //ONENIGHTPACMAN_PLAYER_H
