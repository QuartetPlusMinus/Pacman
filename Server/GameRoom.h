//
// Created by viewsharp on 02.12.17.
//

#ifndef PACMAN_GAMEROOM_H
#define PACMAN_GAMEROOM_H

#include <chrono>

#include "service.grpc.pb.h"
#include "Pacman.h"
#include "Ghost.h"
#include "MapManager.h"

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
        for (unsigned int i = 0; i < GHOST_COUNT; i++) {
            ghosts[i] = new Ghost(320 + 32 * i, 416);
        }
        for (unsigned int i = 0; i < PACMAN_COUNT; i++) {
            pacmans[i] = new Pacman(32 + 64 * i, 96);
        }
    }

    ~GameRoom() {
        delete[] ghosts;
        delete[] pacmans;
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

    void setEvent(int id, const Direction &direction) {
        //pacmans[id]->set_direction(direction);
        if (pacmans[id]->direction() != direction) {
                    pacmans[id]->newDirection = direction;
                    pacmans[id]->tryCount = 32;
            }
    }

    bool have_collision(BaseBeing *being) {
        return have_collision(being, being->direction());
    }

    bool have_collision(BaseBeing *being, const Direction &direction) {

        int y = being->pos().y();
        int x = being->pos().x();
        int i = x / 32 - 1;
        int j = y / 32 - 1;
        switch (direction) {
            case UP:
                if (y == 32)
                    return  true;
                if ((j < 0 && x % 32 == 0) || x % 32 != 0)
                    return true;
                if (y % 32 !=0)
                    return false;
                return (TileMap[j-1][i] == 's');
            case RIGHT:
                if ((i == MapManager::W - 1 && y % 32 == 0) || y % 32 != 0)
                    return true;
                if (x % 32 !=0)
                    return false;
                return (TileMap[j][i+1] == 's');
            case DOWN:
                if ((j == MapManager::H - 1 && x % 32 == 0) || x % 32 != 0)
                    return true;
                if (y % 32 !=0)
                    return false;
                return  (TileMap[j+1][i] == 's');
            case LEFT:
                if (x == 32)
                    return  true;
                if ((i < 0 && y % 32 == 0) || y % 32 != 0)
                    return true;
                if (x % 32 !=0)
                    return false;
                return (TileMap[j][i-1] == 's');
            default:
                break;
        }
        return true;

    }

    int clientInitCount;

private:

    Pacman *pacmans[PACMAN_COUNT];
    Ghost *ghosts[GHOST_COUNT];
    steady_clock::time_point time;
    const nanoseconds stepTime;

    void stepBody() {
        for (int i = 0; i < PACMAN_COUNT; i++) {
            if (pacmans[i]->tryCount) {
                if (!have_collision(pacmans[i], pacmans[i]->newDirection)) {
                    pacmans[i]->setNewDirection();
                }
                else {
                    pacmans[i]->tryCount--;
                }
            }

            if (!have_collision(pacmans[i])) {
                pacmans[i]->step();
                cout << "x= " << pacmans[i]->pos().x() << " y= "<< pacmans[i]->pos().y() << endl;
            }
        }
        for (int i = 0; i < GHOST_COUNT; i++) {
            if (!have_collision(ghosts[i])) {
                ghosts[i]->step();
            }
        }
    }

};

#endif //PACMAN_GAMEROOM_H
