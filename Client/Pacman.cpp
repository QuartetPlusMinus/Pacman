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
    if (getSide() == 1) {
        healthView.setPos(0, healthView.getImgY());
        for (int i = 0; i < health(); ++i) {
            window->draw(*healthView.getSprite());
            healthView.setPos(healthView.getImgX() + 32, healthView.getImgY());
        }
    }
    else {
        healthView.setPos(768, healthView.getImgY());
        for (int i = 0; i < health(); ++i) {
            window->draw(*healthView.getSprite());
            healthView.setPos(healthView.getImgX() - 32, healthView.getImgY());
        }
    }

//    healthView.setPos(800 - 32, healthView.getImgY());
    
    nickname.setPosition(pos().x() - 16, pos().y() - 16);
    window->draw(nickname);
}
