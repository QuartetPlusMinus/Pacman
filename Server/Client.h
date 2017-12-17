//
// Created by viewsharp on 02.12.17.
//

#ifndef PACMAN_CLIENT_H
#define PACMAN_CLIENT_H

#include "service.grpc.pb.h"
#include "GameRoom.h"

template<int GHOST_COUNT>
class Client {

public:
    Client() :
            name(""),
            id(-1),
            room(nullptr) {}

    explicit Client(const string &name, int id = -1) :
            id(id),
            room(nullptr) {
        this->name = name;
    }

    void setRoom(GameRoom<GHOST_COUNT> *room) {
        this->room = room;
        id = room->clientInitCount++;
    }

    void setEvent(Direction direction) {
        room->setEvent(id, direction);
    }

    GameRoom<GHOST_COUNT> *room;

    unsigned int getId() {
        if (id == -1)
            throw -1; // Нужен нормальны эксептион
        return (unsigned) id;
    }
    string name;

private:
    int id;

};

#endif //PACMAN_CLIENT_H
