//
// Created by viewsharp on 01.12.17.
//

#include "BaseBeing.h"

void BaseBeing::getBeing(Being *data) {
    data->set_direction(direction());
    data->set_status(status());
    auto point = new Point;
    point->set_x(pos().x());
    point->set_y(pos().y());
    data->set_allocated_pos(point);
}

void BaseBeing::step() {
    auto point = new Point();
    point->set_x(pos().x());
    point->set_y(pos().y());
    switch (direction()) {
        case UP:
            point->set_y(pos().y() - speed);
            break;
        case RIGHT:
            point->set_x(pos().x() + speed);
            break;
        case DOWN:
            point->set_y(pos().y() + speed);
            break;
        case LEFT:
            point->set_x(pos().x() - speed);
            break;
        default:
            break;
    }
    clear_pos();
    set_allocated_pos(point);
}