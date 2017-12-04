//
// Created by viewsharp on 02.12.17.
//

#ifndef PACMAN_GAMEROOM_H
#define PACMAN_GAMEROOM_H

#include <chrono>

#include "service.grpc.pb.h"
#include "Pacman.h"
#include "Ghost.h"

using namespace std::chrono;

template<int PACMAN_COUNT, int GHOST_COUNT>
class GameRoom {

public:
    GameRoom() :
            clientInitCount(0),
            stepTime(16666667),
            time(steady_clock::now()),
            pacmans(),
            ghosts() {
        for (int i = 0; i < GHOST_COUNT; i++) {
            ghosts[i] = new Ghost(400 + 80 * i, 400);
        }
        for (int i = 0; i < PACMAN_COUNT; i++) {
            pacmans[i] = new Pacman(80 * i, 10);
        }
    }

    void getStartReply(StartReply *reply) {
        for (int i = 0; i < PACMAN_COUNT; i++) {
            BeingInit *data = reply->add_being();
            auto *being = new Being();
            pacmans[i]->getBeing(being);
            data->set_allocated_data(being);
            data->set_type(PACMAN);
        }
        for (int i = 0; i < GHOST_COUNT; i++) {
            BeingInit *data = reply->add_being();
            auto *being = new Being();
            ghosts[i]->getBeing(being);
            data->set_allocated_data(being);
            data->set_type(GHOST);
        }
    }

    void getIterationReply(IterationReply *reply) {
        for (int i = 0; i < PACMAN_COUNT; i++) {
            pacmans[i]->getBeing(reply->add_being());
        }
        for (int i = 0; i < GHOST_COUNT; i++) {
            ghosts[i]->getBeing(reply->add_being());
        }
    }

    void step() {
        if (steady_clock::now() - time > stepTime) {
            stepBody();
            time += stepTime;
        }
    }

    void setEvent(int id, Direction direction) {
        pacmans[id]->set_direction(direction);
    }

    int clientInitCount;

private:

    Pacman *pacmans[PACMAN_COUNT];
    Ghost *ghosts[GHOST_COUNT];
    steady_clock::time_point time;
    const nanoseconds stepTime;

    void stepBody() {
        for (int i = 0; i < PACMAN_COUNT; i++) {
            pacmans[i]->step();
        }
        for (int i = 0; i < GHOST_COUNT; i++) {
            ghosts[i]->step();
        }
    }

};

#endif //PACMAN_GAMEROOM_H
