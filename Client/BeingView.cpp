//
// Created by viewsharp on 02.12.17.
//

#include "BeingView.h"

void BeingView::setData(const Being &data) {
    clear_pos();
    auto *pos = new Point();
    pos->set_x(data.pos().x());
    pos->set_y(data.pos().y());
    set_allocated_pos(pos);
    set_status(data.status());
    set_direction(data.direction());
}

sf::Sprite *BeingView::getSprite() {
//    if (status) {
    static int count = 0;
    if (count < 90) {
        sprite->setTextureRect(sf::IntRect(imgX, imgY + (direction() * 32), 32, 32));
    } else if (count < 180) {
        sprite->setTextureRect(sf::IntRect(imgX + 32, imgY + (direction() * 32), 32, 32));
    } else {
        count = 0;
    }
    count++;

//    } else {
//        sprite->setTextureRect(sf::IntRect(imgX+32, imgY, 32, 32));
//    }
//    status = !status;

    sprite->setPosition(pos().x(), pos().y());
    return sprite;
}