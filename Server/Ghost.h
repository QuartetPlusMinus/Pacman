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

    void changeDirection(bool &frontB, bool &rightB, bool &backB, bool &leftB);

    Direction front ();

    Direction right();

    Direction left();

    Direction back();

private:
    int playerCount;
    int playerId;

};
#endif //ONENIGHTPACMAN_GHOST_H
