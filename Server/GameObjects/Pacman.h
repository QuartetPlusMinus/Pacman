//
// Created by viewsharp on 28.11.17.
//

#ifndef SERVER_PACMAN_H
#define SERVER_PACMAN_H

#include "MovingGameObject.h"

class Pacman: public MovingGameObject {
public:
    explicit Pacman(int x=0, int y=0): MovingGameObject(x, y, RIGHT)
    {}
};

#endif //SERVER_PACMAN_H
