//
// Created by viewsharp on 02.12.17.
//

#include "BeingView.h"

void BeingView::setData(const Being &data) {
    mutable_pos()->set_x(data.pos().x());
    mutable_pos()->set_y(data.pos().y());
    set_status(data.status());
    set_direction(data.direction());
}

sf::Sprite *BeingView::getSprite() {

    static int count = 0;
    if (count < 90) {
        sprite->setTextureRect(sf::IntRect(imgX, imgY + (direction() * 32), 32, 32));
    } else if (count < 180) {
        sprite->setTextureRect(sf::IntRect(imgX + 32, imgY + (direction() * 32), 32, 32));
    } else {
        count = 0;
    }
    count++;

    sprite->setPosition(pos().x(), pos().y());
    return sprite;
}