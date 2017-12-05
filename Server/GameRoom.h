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
        for (int i = 0; i < GHOST_COUNT; i++) {
            ghosts[i] = new Ghost(400 + 32 * i, 400);
        }
        for (int i = 0; i < PACMAN_COUNT; i++) {
            pacmans[i] = new Pacman(64 * i + 66, 97);
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

    void setEvent(int id, Direction direction) {
        pacmans[id]->set_direction(direction);
    }

    bool have_collision(BaseBeing *being) {
        int x_left = being->pos().x();
        int x_right = x_left + tileSize;
        int y_top = being->pos().y();
        int y_bot = y_top + tileSize;

        switch (being->direction()) {
            case UP:
                for (int i = 0; i < MapManager::H; i++) {
                    for (int j = 0; j < MapManager::W; j++) {
                        if (TileMap[i][j] == 's') {
                            int x_left_t = (j + 1) * tileSize;
                            int x_rigt_t = (j + 2) * tileSize;
                            int y_bot_t = (i + 2) * tileSize;
                            if ((y_top - being->getSpeed() <= (i + 2) * tileSize) &&
                                ((x_left >= x_left_t && x_left <= x_rigt_t) ||
                                 (x_right >= x_left_t && x_right <= x_rigt_t))) {
                                return true;
                            }
                        }
                    }
                }
                if (being->pos().y() - being->getSpeed() > tileSize) {
                    return false;
                }
                return true;
                break;
            case RIGHT:
                for (int i = 0; i < MapManager::H; i++) {
                    for (int j = 0; j < MapManager::W; j++) {
                        if (TileMap[i][j] == 's') {
                            int x_left_t = (j + 1) * tileSize;
                            int y_top_t = (i + 1) * tileSize;
                            int y_bot_t = (i + 2) * tileSize;
                            if ((x_right + being->getSpeed() >= x_left_t) &&
                                ((y_top > y_top_t && y_top < y_bot_t) ||
                                 (y_bot > y_top_t && y_bot < y_bot_t))) {
                                return true;
                            }
                        }
                    }
                }
                if (being->pos().x() + being->getSpeed() < (MapManager::W) * tileSize) {
                    return false;
                }
                return true;
                break;
            case DOWN:
                for (int i = 0; i < MapManager::H; i++) {
                    for (int j = 0; j < MapManager::W; j++) {
                        if (TileMap[i][j] == 's') {
                            int x_left_t = (j + 1) * tileSize;
                            int x_right_t = (j + 2) * tileSize;
                            int y_top_t = (i + 1) * tileSize;
                            if ((y_bot + being->getSpeed() >= y_top_t) &&
                                ((x_left > x_left_t && x_left < x_right_t) ||
                                 (x_right > x_left_t && x_right < x_right_t))) {
                                return true;
                            }
                        }
                    }
                }
                if (being->pos().y() + being->getSpeed() < (MapManager::H) * tileSize) {
                    return false;
                }
                return true;
                break;
            case LEFT:
                for (int i = 0; i < MapManager::H; i++) {
                    for (int j = 0; j < MapManager::W; j++) {
                        if (TileMap[i][j] == 's') {
                            int x_right_t = (j + 2) * tileSize;
                            int y_top_t = (i + 1) * tileSize;
                            int y_bot_t = (i + 2) * tileSize;
                            if ((x_left - being->getSpeed() <= x_right_t) &&
                                ((y_top > y_top_t && y_top < y_bot_t) ||
                                 (y_bot > y_top_t && y_bot < y_bot_t))) {
                                return true;
                            }
                        }
                    }
                }
                if (being->pos().x() - being->getSpeed() > tileSize) {
                    return false;
                };
                return true;
                break;
            default:
                return true;
                break;
        }
    }

    int clientInitCount;

private:

    Pacman *pacmans[PACMAN_COUNT];
    Ghost *ghosts[GHOST_COUNT];
    steady_clock::time_point time;
    const nanoseconds stepTime;

    void stepBody() {
        for (int i = 0; i < PACMAN_COUNT; i++) {
            if (!have_collision(pacmans[i])) {
                pacmans[i]->step();
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
