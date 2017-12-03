//
// Created by viewsharp on 02.12.17.
//

#ifndef PACMAN_GAMEROOM_H
#define PACMAN_GAMEROOM_H

#include "service.grpc.pb.h"
#include "Pacman.h"
#include "Ghost.h"

template <int PACMAN_COUNT, int GHOST_COUNT>
class GameRoom {

public:
    GameRoom(): clientInitCount(0) {
        for (int i = 0; i < GHOST_COUNT; i++) {
            ghosts[i] = new Ghost(400 + 80 * i, 400);
        }
        for (int i = 0; i < PACMAN_COUNT; i++) {
            pacmans[i] = new Pacman(80 * i, 10);
        }
    }

    void getStartReply(StartReply * reply) {
        for (int i = 0; i < PACMAN_COUNT; i++) {
            BeingInit *data = reply->add_being();
            Being *being = new Being();
            pacmans[i]->getBeing(being);
            data->set_allocated_data(being);
            data->set_type(PACMAN);
        }
        for (int i = 0; i < GHOST_COUNT; i++) {
            BeingInit *data = reply->add_being();
            Being *being = new Being();
            ghosts[i]->getBeing(being);
            data->set_allocated_data(being);
            data->set_type(PACMAN);
        }
    }

    void getIterationReply(IterationReply * reply) {
        for (int i = 0; i < PACMAN_COUNT; i++) {
            pacmans[i]->getBeing(reply->add_being());
        }
        for (int i = 0; i < GHOST_COUNT; i++) {
            ghosts[i]->getBeing(reply->add_being());
        }
    }

    void step() {
        for (int i = 0; i < PACMAN_COUNT; i++) {
            pacmans[i]->step();
        }
        for (int i = 0; i < GHOST_COUNT; i++) {
            ghosts[i]->step();
        }
    }

    void setEvent(int id, Direction direction) {
        pacmans[id]->set_direction(direction);
    }

    int clientInitCount;

private:

    Pacman *pacmans[PACMAN_COUNT];
    Ghost *ghosts[GHOST_COUNT];

};

#endif //PACMAN_GAMEROOM_H
