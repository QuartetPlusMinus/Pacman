//
// Created by viewsharp on 01.12.17.
//

#ifndef ONENIGHTPACMAN_PLAYER_H
#define ONENIGHTPACMAN_PLAYER_H
#include "BaseBeing.h"
#include <string>

using namespace pacman_service;
using namespace std;


class Player: public BaseBeing {

public:

    Player (string name): name(name){}

    string name;

private:

};


#endif //ONENIGHTPACMAN_PLAYER_H
