//
// Created by viewsharp on 01.12.17.
//

#include "BaseBeing.h"

void BaseBeing::init(int id, int x, int y) {
    this->set_id(id);
    this->set_direction(RIGHT);
    this->set_status(ALIVE);
    auto point = new Point;
    point->set_x(x);
    point->set_y(y);
    this->set_allocated_pos(point);
}

Being *BaseBeing::getBeing() {
    Being *data;
    data->set_id(this->id());
    data->set_direction(this->direction());
    data->set_status(this->status());
    auto point = new Point;
    point->set_x(this->pos().x());
    point->set_y(this->pos().y());
    data->set_allocated_pos(point);
    return data;
}

void BaseBeing::getBeing(Being *data) {
    data->set_id(this->id());
    data->set_direction(this->direction());
    data->set_status(this->status());
    auto point = new Point;
    point->set_x(this->pos().x());
    point->set_y(this->pos().y());
    data->set_allocated_pos(point);
}

void BaseBeing::step() {
    Point *point = new Point();
    switch (this->direction()) {
        case UP:
            point->set_x(this->pos().x() - this->speed);
        case RIGHT:
            point->set_y(this->pos().y() + this->speed);
        case DOWN:
            point->set_x(this->pos().x() + this->speed);
        case LEFT:
            point->set_y(this->pos().y() - this->speed);
    }
    this->clear_pos();
    this->set_allocated_pos(point);
}