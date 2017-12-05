//
// Created by viewsharp on 01.12.17.
//

#include "BaseBeing.h"

void BaseBeing::getBeing(Being *data) {
    data->set_direction(direction());
    data->set_status(status());
    data->mutable_pos()->set_x(pos().x());
    data->mutable_pos()->set_y(pos().y());
}

//void BaseBeing::step() {
//    step(direction());
//}

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