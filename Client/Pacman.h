//
// Created by viewsharp on 01.12.17.
//

#ifndef ONENIGHTPACMAN_PLAYER_H
#define ONENIGHTPACMAN_PLAYER_H

#include "BeingView.h"
#include <string>

using namespace pacman_service;
using namespace std;

class Pacman : public BeingView {

public:

    Pacman(const string &name, const Being &data):
            BeingView(data, 320, 0){
        this->name = name;
    }

    string name;

private:

};

#endif //ONENIGHTPACMAN_PLAYER_H
