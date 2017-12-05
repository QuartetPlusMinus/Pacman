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
        int y = being->pos().y();
        int x = being->pos().x();
        switch (being->direction()) {
            case UP:
                y -= being->getSpeed();
                break;
            case RIGHT:
                x += being->getSpeed();
                break;
            case DOWN:
                y += being->getSpeed();
                break;
            case LEFT:
                x -= being->getSpeed();
                break;
            default:
                break;
        }
        int i = x / 32;
        int j = y / 32;
        if (j >= MapManager::H || i >= MapManager::W || j <= 0 || i <= 0 )
            return  true;
        if (!(y % 32) && (being->direction() == LEFT || being->direction() == RIGHT))
            return (TileMap[j-1][i-1] == 's' || TileMap[j-1][i] == 's');
        if (!(x % 32) && (being->direction() == UP || being->direction() == DOWN))
            return (TileMap[j-1][i-1] == 's' || TileMap[j][i-1] == 's');
        return (TileMap[j-1][i-1] == 's' || TileMap[j][i-1] == 's' || TileMap[j-1][i] == 's' || TileMap[j][i] == 's');

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
