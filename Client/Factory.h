//
// Created by viewsharp on 18.12.17.
//

#ifndef PACMAN_FACTORY_H
#define PACMAN_FACTORY_H

#include "BeingView.h"
#include "Pacman.h"
#include "Ghost.h"

class Factory {

public:
    Factory(sf::Font &nameFont):
            nameFont(nameFont){

    }

    BeingView *make(const BeingInit &data) {
        switch(data.type()) {
            case PACMAN:
                return new Pacman(data.name(), data.data(), nameFont);
            case GHOST:
                return new Ghost(data.data());
            default:
                break;
        }
    }

private:
    sf::Font nameFont;

};

#endif //PACMAN_FACTORY_H
