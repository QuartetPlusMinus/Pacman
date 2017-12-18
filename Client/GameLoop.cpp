//
// Created by viewsharp on 30.11.17.
//

#include "GameLoop.h"

void GameLoop::loop(string name) {

    ConnectRequest connectRequest;
    ConnectReply *connectReply;

    connectRequest.set_name(name);

    connectReply = connection->Connect(connectRequest);

    hex = connectReply->hex();
    cout<<"Connect to server. id_hex = "<<hex<<endl;

    delete connectReply;

    StartReply *startReply;
    StartRequest startRequest;

    while (true) {
        startReply = connection->Start(startRequest, hex);
        cout<<"Start: sleep = " << startReply->time() << endl;
        if (startReply->time() == 0)
            break;
        usleep((useconds_t)startReply->time());
        delete  startReply;
    }

    beingCount = startReply->being_size();
    beings = new BeingView *[beingCount];

    Factory factory(font);

    for (int i = 0; i < beingCount; i++) {
        beings[i] = factory.make(startReply->being(i));
    }

    id = startReply->id();
    direction = beings[id]->direction();

    RenderWindow window(sf::VideoMode(800, 640), "Pacman");

    TileMap tMap(startReply, &window);

    delete startReply;
    
    while (window.isOpen()) {
        window.clear();
        tMap.draw();
        
        loopBody(window);
        
        window.display();
        window.setFramerateLimit(60);
    }
}

void GameLoop::loopBody (RenderWindow &window) {
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
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
    ((Pacman*)beings[id])->setSide(1);

    for (int i = 0; i < beingCount; i++) {
        beings[i]->setData(reply->being(i));
        beings[i]->draw(&window);
    }

    for (int i = 0; i < reply->coins_size(); i++) {
        coin.setPosition(reply->coins(i).x() * 32 + 40 ,reply->coins(i).y() * 32 + 40);
        window.draw(coin);
    }

    delete reply;
}
