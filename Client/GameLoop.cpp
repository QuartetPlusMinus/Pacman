//
// Created by viewsharp on 30.11.17.
//

#include "GameLoop.h"
#include "TileMap.h"

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
            usleep((useconds_t)startReply->time());
            delete  startReply;
        }
    } while (startReply->time() != 0); // CORE


    beings = new BeingView *[startReply->being_size()];
    beingCount = startReply->being_size();
    cout<<"bC = " << beingCount << endl;

    for (int i = 0; i < beingCount; i++) {
        const BeingInit *beingInit = &(startReply->being(i));
        switch(beingInit->type()) {
		// Read about `Factory` pattern
            case PACMAN:
                beings[i] = new Pacman(beingInit->name(), beingInit->data());
                break;
            case GHOST:
                beings[i] = new Ghost(beingInit->data());
                break;
            default:
                break;
        }
    }
    id = startReply->id();
    direction = beings[id]->direction();

    tMap = new TileMap(startReply, window);

    delete startReply;

    while (window->isOpen()) {
        loopBody();
        window->setFramerateLimit(60);
    }
}

void GameLoop::loopBody () {
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        }
    }

    if (wasd) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            direction = UP;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            direction = RIGHT;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            direction = DOWN;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            direction = LEFT;
        }
    } else {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            direction = UP;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            direction = RIGHT;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            direction = DOWN;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            direction = LEFT;
        }
    }

    IterationReply *reply;
    IterationRequest request;

    request.set_direction(direction);
    reply = connection->Iteration(request, hex);
    
    direction = reply->being(id).direction();

    window->clear();
    tMap->draw();

    for (int i = 0; i < beingCount; i++) {
        beings[i]->setData(reply->being(i));
        window->draw(*beings[i]->getSprite());
    }
    
    window->display();

    delete reply;
}
