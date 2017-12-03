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
    Client(string name) :
            name(name) {}

    void setRoom(GameRoom<PACMAN_COUNT, GHOST_COUNT> *room) {
        this->room = room;
        id = room->clientInitCount++;
    }

    void setEvent(Direction direction) {
        cout<<"id = " << id << endl;
        room->setEvent(id, direction);
    }

    GameRoom<PACMAN_COUNT, GHOST_COUNT> *room;

    int getId() {
        return id;
    }

private:
    int id;
    string name;

};

#endif //PACMAN_CLIENT_H
