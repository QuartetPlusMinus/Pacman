//
// Created by viewsharp on 30.11.17.
//

#include "GameLoop.h"


void GameLoop::loop() {

    ConnectRequest connectRequest;
    ConnectReply *connectReply;

    connectRequest.set_name(name);
    connectReply = connection->Connect(connectRequest); //Connect


    id = connectReply->id();
    cout<<"Connect to server. id = "<<id<<endl;

    delete connectReply;

    StartReply *startReply;
    StartRequest startRequest;
    startRequest.set_id(id);

    do {
        startReply = connection->Start(startRequest, id);
        cout<<"Start: sleep = " << startReply->time() << endl;
        if (startReply->time() != 0) {
            usleep(startReply->time());
            delete  startReply;
        }
    } while (startReply->time() != 0);


    beings = new Being *[startReply->being_size()];
    for (int i = 0; i < startReply->being_size(); i++) {
        BeingInit beingInit = startReply->being(i);
        switch(beingInit.type()) {
            case PACMAN:
                cout<< beingInit.name() << &beingInit.data()<<endl;
                beings[i] = new Pacman(beingInit.name(), beingInit.data());
                break;
            case GHOST:
                beings[i] = new Ghost(beingInit.data());
                break;
        }
    }
    direction = beings[0]->direction();
    cout << "yepiii 2" << endl;

    delete startReply;
    int qwer = 0;
    while (true) {
        auto begin = high_resolution_clock::now();
        cout << ++qwer << endl;
        loopBody();
        auto pause = begin - high_resolution_clock::now();
        if (pause.count() < 16666667)
            usleep(16667 - pause.count() / 1000);
    }
}

void GameLoop::loopBody () {
    IterationReply *reply;
    IterationRequest request;

    request.set_direction(direction);
    request.set_id(id);

    reply = connection->Iteration(request);

    health = reply->health();
    //cout << "health = " << health << endl;

    for (int i = 0; i < reply->being_size(); i++) {
        Being current = reply->being(i);
        //cout<<"x = " <<current.pos().x() << "; y = " <<current.pos().x()<<endl;
    }

    delete reply;
}