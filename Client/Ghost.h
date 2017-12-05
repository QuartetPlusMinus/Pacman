//
// Created by viewsharp on 01.12.17.
//

#ifndef ONENIGHTPACMAN_GHOST_H
#define ONENIGHTPACMAN_GHOST_H

#include "BeingView.h"

class Ghost: public BeingView {

public:

    explicit Ghost(const Being &data): BeingView(data, 0, 0) {}

};

#endif //ONENIGHTPACMAN_GHOST_H
