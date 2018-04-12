//
// Created by viewsharp on 01.12.17.
//

#include "Ghost.h"

void Ghost::calcDirection(BaseBeing *pacman) {

//    timer = 50;
    int p_x = pacman->pos().x();
    int p_y = pacman->pos().y();
//    if (pacman->direction() == RIGHT) {
//        ++p_x;
//    } else if (pacman->direction() == LEFT) {
//        --p_x;
//    } else if (pacman->direction() == UP) {
//        --p_y;
//    } else {
//        ++p_y;
//    }
    int g_x = this->pos().x();
    int g_y = this->pos().y();

//    std::cout << "PACMAN_POS " << p_x << " " << p_y << std::endl;
//    std::cout << "GHOST_POS " << g_x << " " << g_y <<std::endl;

    dir_culcs[0] = (p_x - (g_x + 2)) * (p_x - (g_x + 2)) + (p_y - g_y) * (p_y - g_y);
    dir_culcs[1] = (p_x - g_x) * (p_x - g_x) + (p_y - (g_y + 2)) * (p_y - (g_y + 2));
    dir_culcs[2] = (p_x - (g_x - 2)) * (p_x - (g_x - 2)) + (p_y - g_y) * (p_y - g_y);
    dir_culcs[3] = (p_x - g_x) * (p_x - g_x) + (p_y - (g_y - 2)) * (p_y - (g_y - 2));
    dir_names[0] = RIGHT;
    dir_names[1] = DOWN;
    dir_names[2] = LEFT;
    dir_names[3] = UP;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4 - i - 1; j++) {
            if (dir_culcs[j] > dir_culcs[j + 1]) {
                std::swap(dir_culcs[j],dir_culcs[j + 1]);
                std::swap(dir_names[j], dir_names[j + 1]);
            }
        }
    }
//    std::cout << "_______________" << std::endl;
//    for (int i = 0; i < 4; ++i) {
//        std::cout << dir_names[i] << "---" << dir_culcs[i] << std::endl;
//    }
//    std::cout << "_______________" << std::endl;
}

void Ghost::changeTarget() {
    if (changeTargetTimer > 0) {
        --changeTargetTimer;
        return;
    }
    playerId = random() % playerCount;
    std::cout<<"PLAYER_ID "<<playerId<<std::endl;
    changeTargetTimer = 1000;
}

int Ghost::getPlayerId() {
    return playerId;
}

void Ghost::setNewDirection() {
    tryCount = 0;
    set_direction(newDirection);
}


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