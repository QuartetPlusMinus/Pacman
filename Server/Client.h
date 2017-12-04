//
// Created by viewsharp on 02.12.17.
//

#ifndef PACMAN_CLIENT_H
#define PACMAN_CLIENT_H

#include "service.grpc.pb.h"
#include "GameRoom.h"

template <int PACMAN_COUNT, int GHOST_COUNT>
class Client {

public:
    explicit Client(const string &name) :
            id(-1)
    {
        this->name = name;
    }

    void setRoom(GameRoom<PACMAN_COUNT, GHOST_COUNT> *room) {
        this->room = room;
        id = room->clientInitCount++;
    }

    void setEvent(Direction direction) {
        room->setEvent(id, direction);
    }

    GameRoom<PACMAN_COUNT, GHOST_COUNT> *room;

    unsigned int getId() {
        if (id == -1)
            throw -1; // Нужен нормальны эксептион
        return (unsigned)id;
    }

private:
    int id;
    string name;

};

#endif //PACMAN_CLIENT_H
