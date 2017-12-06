//
// Created by viewsharp on 01.12.17.
//

#include "Pacman.h"
sf::Sprite *Health::getSprite() {
//    if (status) {
//    sprite->setTextureRect(sf::IntRect(imgX, imgY + (direction()*32), 32, 32));
//    } else {
//        sprite->setTextureRect(sf::IntRect(imgX+32, imgY, 32, 32));
//    }
//    status = !status;

    sprite->setPosition(imgX, imgY);
    return sprite;
}