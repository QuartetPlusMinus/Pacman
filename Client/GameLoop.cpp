//
// Created by viewsharp on 30.11.17.
//

#include "GameLoop.h"

void GameLoop::loop() {

    ConnectRequest connectRequest;
    ConnectReply *connectReply;

    connectRequest.set_name(name);

    connectReply = connection->Connect(connectRequest);

    hex = connectReply->hex();
    cout<<"Connect to server. id_hex = "<<hex<<endl;

    delete connectReply;

    StartReply *startReply;
    StartRequest startRequest;

    do {
        startReply = connection->Start(startRequest, hex);
        cout<<"Start: sleep = " << startReply->time() << endl;
        if (startReply->time() != 0) {
            usleep(startReply->time());
            delete  startReply;
        }
    } while (startReply->time() != 0);


    beings = new BeingView *[startReply->being_size()];
    beingCount = startReply->being_size();
    cout<<"bC = " << beingCount << endl;

    for (int i = 0; i < beingCount; i++) {
        BeingInit beingInit = startReply->being(i);
        switch(beingInit.type()) {
            case PACMAN:
                beings[i] = new Pacman(beingInit.name(), beingInit.data());
                break;
            case GHOST:
                beings[i] = new Ghost(beingInit.data());
                break;
        }
    }
    direction = beings[0]->direction();

    delete startReply;
    int qwer = 0;

    while (window->isOpen()) {
        auto begin = high_resolution_clock::now();
        cout << ++qwer << endl;
        loopBody();
        auto pause = begin - high_resolution_clock::now();
        if (pause.count() < 16666667)
            usleep(16667 - pause.count() / 1000);
    }
}

void GameLoop::loopBody () {


    sf::Event event;

    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        direction = UP;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        direction = RIGHT;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        direction = DOWN;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        direction = LEFT;
    }

    IterationReply *reply;
    IterationRequest request;

    request.set_direction(direction);
    reply = connection->Iteration(request, hex);

    window->clear();

    for (int i = 0; i < beingCount; i++) {


        beings[i]->setData(reply->being(i));
        window->draw(*beings[i]->getSprite());

    }

    window->display();

    delete reply;
}