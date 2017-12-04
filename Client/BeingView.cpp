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
    s->setPosition(pos().x(), pos().y());
    return s;
}