//
// Created by viewsharp on 01.12.17.
//

#include "BaseBeing.h"

void BaseBeing::step() {
    switch (direction()) {
        case UP:
            mutable_pos()->set_y(pos().y() - speed);
            break;
        case RIGHT:
            mutable_pos()->set_x(pos().x() + speed);
            break;
        case DOWN:
            mutable_pos()->set_y(pos().y() + speed);
            break;
        case LEFT:
            mutable_pos()->set_x(pos().x() - speed);
            break;
        default:
            break;
    }
}