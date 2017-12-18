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
//            pacmans[i].getBeing(data->mutable_data());
            *data->mutable_data() = pacmans[i];
            data->set_type(PACMAN);
            data->set_name(pacmans[i].name);
        }
        for (int i = 0; i < GHOST_COUNT; i++) {
            BeingInit *data = reply->add_being();
//            ghosts[i].getBeing(data->mutable_data());
            *data->mutable_data() = ghosts[i];
            data->set_type(GHOST);
        }
    }

    void getIterationReply(IterationReply *reply) {
        for (auto p: pacmans) {
            //pacmans[i].getBeing(reply->add_being());
            *reply->add_being() = p;
        }
        for (int i = 0; i < GHOST_COUNT; i++) {
            //ghosts[i].getBeing(reply->add_being());
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

    void start() {
        for (unsigned int i = 0; i < GHOST_COUNT; i++) {
            ghosts[i] = Ghost(320 + 32 * i, 416, pacmans.size());
        }
        Point *p;
        for (unsigned int j = 0; j < TileMap->length(); j++) {
            for (unsigned int i = 0; i < TileMap[j].length(); i++) {
                if (TileMap[j][i] == '.') {
                    p = new Point;
                    p->set_x(i);
                    p->set_y(j);
                    coins.push_back(*p);
                    delete p;
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
//
//    Pacman *pacmans[PACMAN_COUNT];
    Ghost ghosts[GHOST_COUNT];
    steady_clock::time_point time;
    const nanoseconds stepTime;
    vector<Point> coins;
    vector<Pacman> pacmans;


    void stepBody() {
        for (int i = 0; i < pacmans.size(); i++) {
            if (pacmans[i].tryCount) {
                if (!have_collision(pacmans[i], pacmans[i].newDirection)) {
                    pacmans[i].setNewDirection();
                } else {
                    pacmans[i].tryCount--;
                }
            }

            if (!have_collision(pacmans[i])) {
                pacmans[i].step();
            }
        }

        for (int i = 0; i < GHOST_COUNT; i++) {
            if (ghosts[i].pos().x() % 32 == 0 && ghosts[i].pos().y() % 32 == 0) {
                bool front = nextBlock(ghosts[i]) != 's';
                bool right = nextBlock(ghosts[i], ghosts[i].right()) != 's';
                bool back = nextBlock(ghosts[i], ghosts[i].back()) != 's';
                bool left = nextBlock(ghosts[i], ghosts[i].left()) != 's';
                if (left || right || !front) {
                    ghosts[i].changeDirection(front, right, back, left);
                }
            }

            if (!have_collision(ghosts[i])) {
                ghosts[i].step();
            }

//            cout << "x= " << pacmans[i].pos().x() << " y= " << pacmans[i].pos().y() << endl;
        }
    }

};

#endif //PACMAN_GAMEROOM_H
