//
// Created by viewsharp on 01.12.17.
//

#include "Pacman.h"

void Pacman::setNewDirection() {
    tryCount = 0;
    set_direction(newDirection);
}


void Pacman::getBeing(Being *data) {
    BaseBeing::getBeing(data);
    data->set_health(health());
}