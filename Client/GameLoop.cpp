//
// Created by viewsharp on 30.11.17.
//

#include "GameLoop.h"


void GameLoop::loop() {

    ConnectRequest connectRequest;
    ConnectReply *connectReply;

    connectRequest.set_name(name);
    connectReply = connection->Connect(connectRequest);
    id = connectReply->id();
    delete connectReply;

    StartReply *startReply;
    StartRequest startRequest;
    startRequest.set_id(id);

    do {
        startReply = connection->Start(startRequest);
        if (startReply->time() != 0) {
            usleep(startReply->time());
        }
        delete  startReply;
    } while (startReply->time() != 0);

    cout << "yepiii" << endl;

    beings = new Being *[startReply->being_size()];
    for (int i = 0; i < startReply->being_size(); i++) {
        switch(startReply->being(i).type()) {
            case PACMAN:
                beings[i] = new Pacman(startReply->being(i).name(), startReply->being(i).data());
                break;
            case GHOST:
                beings[i] = new Ghost(startReply->being(i).data());
                break;
        }
        direction = beings[id]->direction();
    }

    delete startReply;

    while (true) {
        auto begin = high_resolution_clock::now();
        loopBody();
        auto pause = begin - high_resolution_clock::now();
        if (pause.count() < 17)
            usleep(16777 - pause.count() * 1000);
    }
}

void GameLoop::loopBody () {
    IterationReply *reply;
    IterationRequest request;

    request.set_direction(direction);
    request.set_id(id);

    reply = connection->Iteration(request);

    health = reply->health();

    for (int i = 0; i < reply->being_size(); i++) {
        Being current = reply->being(i);
    }

    delete reply;
}