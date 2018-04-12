//
// Created by viewsharp on 02.12.17.
//

#ifndef PACMAN_GAMEROOM_H
#define PACMAN_GAMEROOM_H

#include <chrono>
#include <vector>

#include "service.grpc.pb.h"
#include "Pacman.h"
#include "Ghost.h"
#include "MapManager.h"

using namespace std::chrono;

template<int GHOST_COUNT>
class GameRoom {

public:
    GameRoom() :
            clientInitCount(0),
            stepTime(16666667),
            time(steady_clock::now()) {}

    ~GameRoom() {
        delete[] ghosts;
    }

    void getStartReply(StartReply *reply) {
        for (int i = 0; i < pacmans.size(); i++) {
            BeingInit *data = reply->add_being();
            *data->mutable_data() = pacmans[i];
            data->set_type(PACMAN);
            data->set_name(pacmans[i].name);
        }
        for (int i = 0; i < GHOST_COUNT; i++) {
            BeingInit *data = reply->add_being();
            *data->mutable_data() = ghosts[i];
            data->set_type(GHOST);
        }
    }

    void getIterationReply(IterationReply *reply) {
        for (auto p: pacmans) {
            *reply->add_being() = p;
        }
        for (int i = 0; i < GHOST_COUNT; i++) {
            *reply->add_being() = ghosts[i];
        }
        for (auto c: coins) {
            *reply->add_coins() = c;
        }
    }

    void step() {
        if (steady_clock::now() - time > stepTime) {
            stepBody();
            time += stepTime;
        }
    }

    void setEvent(int id, const Direction &direction) {
        if (pacmans[id].direction() != direction) {
            pacmans[id].newDirection = direction;
            pacmans[id].tryCount = 32;
        }
    }

    int points(int id) {
        return pacmans[id].coins;
    }

    void start() {
        for (unsigned int i = 0; i < GHOST_COUNT; i++) {
            ghosts[i] = Ghost(320 + 32 * i, 416, pacmans.size());
        }
        Point *p;
//        for (unsigned int j = 0; j < MapManager::H; j++) {
//            for (unsigned int i = 0; i < MapManager::W; i++) {
        for (unsigned int j = 0; j < 5; j++) {
            for (unsigned int i = 0; i < 5; i++) {
                if (TileMap[j][i] == '.') {
                    Point p;
                    p.set_x(i);
                    p.set_y(j);
                    coins.push_back(p);
                }
            }
        }
    }

    void addPlayer(string name) {
        pacmans.push_back(Pacman(32 + 64 * pacmans.size(), 32, name));
    }

    char nextBlock(BaseBeing &being) {
        return nextBlock(being, being.direction());
    }

    char nextBlock(BaseBeing &being, const Direction &direction) {
        int i = being.pos().x() / 32 - 1;
        int j = being.pos().y() / 32 - 1;
        switch (direction) {
            case UP:
                if (j == 0)
                    return 's';
                return TileMap[j - 1][i];
            case RIGHT:
                if (i == MapManager::W - 1)
                    return 's';
                return TileMap[j][i + 1];
            case DOWN:
                if (j == MapManager::H - 1)
                    return 's';
                return TileMap[j + 1][i];
            case LEFT:
                if (i == 0)
                    return 's';
                return TileMap[j][i - 1];
            default:
                return 0;
        }
    }

    bool have_collision(BaseBeing &being) {
        return have_collision(being, being.direction());
    }

    bool have_collision(BaseBeing &being, const Direction &direction) {

        int y = being.pos().y();
        int x = being.pos().x();
        if (x % 32 == 0 && y % 32 == 0)
            return nextBlock(being, direction) == 's';
        if ((direction == UP || direction == DOWN) && (x % 32))
            return true;
        if ((direction == LEFT || direction == RIGHT) && (y % 32))
            return true;
        return false;

    }

    int clientInitCount;

private:

    Ghost ghosts[GHOST_COUNT];
    steady_clock::time_point time;
    const nanoseconds stepTime;
    vector<Pacman> pacmans;
    vector<Point> coins;

    void stepBody() {
        for (auto pacman = pacmans.begin(); pacman != pacmans.end(); pacman++) {
            if (pacman->tryCount) {
                if (!have_collision(*pacman, pacman->newDirection)) {
                    pacman->setNewDirection();
                } else {
                    pacman->tryCount--;
                }
            }

            for (int i = 0; i < GHOST_COUNT; ++i) {
                if (ghosts[i].pos().x() == pacman->pos().x() &&
                    ghosts[i].pos().y() == pacman->pos().y()) {
                    pacman->set_health(pacman->health() - 1);
                    std::cout << "---HEALTH----"<< pacman->health() << std::endl;
                }
            }

            if (pacman->pos().x() % 32 - 16 < 3 || pacman->pos().y() % 32 - 16 < 3) {

                for (auto coin = coins.begin(); coin != coins.end(); coin++) {
                    if ((48 + coin->x() * 32 - pacman->pos().x()) < 32 &&
                        (48 + coin->y() * 32 - pacman->pos().y()) < 32) {
                        coins.erase(coin);
                        pacman->coins++;
                        break;
                    }
                }
            }

            if (!have_collision(*pacman)) {
                pacman->step();
            }
        }

//        for (int i = 0; i < GHOST_COUNT; i++) {

        for (int i = 0; i < GHOST_COUNT; i++) {
//            ghosts[i].changeTarget();
            if (ghosts[i].pos().x() % 32 == 0 && ghosts[i].pos().y() % 32 == 0) {
                bool right = have_collision(ghosts[i], RIGHT);
                bool left = have_collision(ghosts[i], LEFT);
                bool top = have_collision(ghosts[i], UP);
                bool bottom = have_collision(ghosts[i], DOWN);
                if (!left && !right && top && bottom ||
                    left && right && !top && !bottom) {
                } else {
                    ghosts[i].calcDirection(&pacmans[ghosts[i].getPlayerId()]);
                    bool shortWay = true;
                    if (rand() % 10 >= 8) {
                        shortWay = false;
                    }
                    for (int dir = 0; dir < 4; ++dir) {
                        if (!have_collision(ghosts[i], ghosts[i].dir_names[dir])) {
                            if (!shortWay) {
                                shortWay = true;
                                continue;
                            }
                            ghosts[i].newDirection = ghosts[i].dir_names[dir];
                            ghosts[i].setNewDirection();
//                            std::cout << "SELECTED " << ghosts[i].dir_names[dir] << std::endl;
                            break;
                        }
                    }

                }
            }
//
            if (!have_collision(ghosts[i])) {
                ghosts[i].step();
            }
        }
    }

};

#endif //PACMAN_GAMEROOM_H
