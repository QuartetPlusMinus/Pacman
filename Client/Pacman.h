//
// Created by viewsharp on 01.12.17.
//

#ifndef ONENIGHTPACMAN_PLAYER_H
#define ONENIGHTPACMAN_PLAYER_H
#include "service.grpc.pb.h"
#include <string>
using namespace pacman_service;
using namespace std;

class Pacman: public Being {

public:

    Pacman(string name, Being data) : name(name), Being(data){}
    string name;

private:

};

#endif //ONENIGHTPACMAN_PLAYER_H
