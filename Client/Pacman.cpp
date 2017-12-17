//
// Created by viewsharp on 01.12.17.
//

#include "Pacman.h"

sf::Sprite *Health::getSprite() {

    sprite->setPosition(imgX, imgY);
    return sprite;
}

void Pacman::draw(sf::RenderWindow *window) {
    BeingView::draw(window);
    
    for (int i = 0; i < health(); ++i) {
        window->draw(*healthView.getSprite());
        healthView.setPos(healthView.getImgX() + 32, healthView.getImgY());
    }
    healthView.setPos(800 - 32, healthView.getImgY());
    
    nickname.setPosition(pos().x(), pos().y());
    window->draw(nickname);
}
