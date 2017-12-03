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

    Pacman(string name, Being data) : name(name), BeingView(data, "src/pacimg.png") {}

    string name;

private:

};

#endif //ONENIGHTPACMAN_PLAYER_H