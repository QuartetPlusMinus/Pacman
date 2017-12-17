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

    explicit Ghost(unsigned int x = 0, unsigned int y = 0, int playerCount = 0):
            BaseBeing(x,y),
            playerCount(playerCount) {
        if (playerCount != 0) {
            playerId = random() % playerCount;
        }
        else {
                playerId = -1;
        };
    }

    void changeDirection(bool &frontB, bool &rightB, bool &backB, bool &leftB) {
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
