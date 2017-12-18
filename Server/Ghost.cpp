//
// Created by viewsharp on 01.12.17.
//

#include "Ghost.h"

void Ghost::changeDirection(bool &frontB, bool &rightB, bool &backB, bool &leftB) {
    if (!(frontB || rightB || leftB )) {
        set_direction(back());
        return;
    }
    vector<Direction> dirVector;
    if (frontB)
        dirVector.push_back(direction());
    if (rightB)
        dirVector.push_back(right());
    if (leftB)
        dirVector.push_back(left());
    set_direction(dirVector[random()%dirVector.size()]);

}

Direction Ghost::front () {
    return direction();
}

Direction Ghost::right() {
    switch (direction()) {
        case UP:
            return RIGHT;
        case RIGHT:
            return DOWN;
        case DOWN:
            return LEFT;
        case LEFT:
            return UP;
        default:
            break;
    }
}

Direction Ghost::left() {
    switch (direction()) {
        case UP:
            return LEFT;
        case RIGHT:
            return UP;
        case DOWN:
            return RIGHT;
        case LEFT:
            return DOWN;
        default:
            break;
    }
}

Direction Ghost::back() {
    switch (direction()) {
        case UP:
            return DOWN;
        case RIGHT:
            return LEFT;
        case DOWN:
            return UP;
        case LEFT:
            return RIGHT;
        default:
            break;
    }
}