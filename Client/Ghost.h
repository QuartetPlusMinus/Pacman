//
// Created by viewsharp on 01.12.17.
//

#ifndef ONENIGHTPACMAN_GHOST_H
#define ONENIGHTPACMAN_GHOST_H

#include "BeingView.h"

class Ghost: public BeingView {

public:

    Ghost(Being data): BeingView(data, "src/ghost.png") {}

};

#endif //ONENIGHTPACMAN_GHOST_H
