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
            playerCount(playerCount),
            tryCount(0),
            newDirection(this->direction()) {
        if (playerCount != 0) {
            playerId = random() % playerCount;
        }
        else {
                playerId = -1;
        };
    }

    void changeDirection(bool &frontB, bool &rightB, bool &backB, bool &leftB);
    void setNewDirection();
    void calcDirection(BaseBeing* pacman);
    int getPlayerId();
    int tryCount;
    Direction newDirection;

    Direction front ();

    Direction right();

    Direction left();

    Direction back();
    int dir_culcs[4] = {1000000000, 1000000000, 1000000000, 1000000000};
    Direction dir_names[4] = {RIGHT, DOWN, LEFT, UP};
    int timer = 50;
    int changeTargetTimer = 300;
    void changeTarget();
private:
    int playerCount;
    int playerId;

};
#endif //ONENIGHTPACMAN_GHOST_H
