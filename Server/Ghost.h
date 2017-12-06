//
// Created by viewsharp on 01.12.17.
//

#ifndef ONENIGHTPACMAN_GHOST_H
#define ONENIGHTPACMAN_GHOST_H

#include "BaseBeing.h"
#include <cstdlib>
#include <vector>

using namespace std;

class Ghost: public BaseBeing {

public:
    Ghost(unsigned int x, unsigned int y, int playerCount):
            BaseBeing(x,y),
            playerCount(playerCount),
            playerId(random() % playerCount) {}

    void changeDirection(bool dirs, ...) {
        bool* iter = &dirs;
        bool frontB = iter[(int)front()];
        bool rightB = iter[(int)right()];
        bool backB  = iter[(int)back()];
        bool leftB  = iter[(int)left()];
        if (!(frontB || rightB || leftB )) {
            cout << " back";
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

    Direction front () {
        return direction();
    }

    Direction right() {
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

    Direction left() {
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

    Direction back() {
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

private:
    int playerCount;
    int playerId;

};
#endif //ONENIGHTPACMAN_GHOST_H
