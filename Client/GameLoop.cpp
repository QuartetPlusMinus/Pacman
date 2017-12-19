//
// Created by viewsharp on 30.11.17.
//

#include "GameLoop.h"

void GameLoop::loop(string name) {

    ConnectRequest connectRequest;
    connectRequest.set_name(name);

    auto connectReply = connection->Connect(connectRequest);

    connection->setHex(connectReply->hex());

    delete connectReply;
    

    StartReply *startReply;
    StartRequest startRequest;

    while (true) {
        startReply = connection->Start(startRequest);
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
        
        if (loopBody(window))
            break;
        
        window.display();
        window.setFramerateLimit(60);
    }

    EndRequest endRequest;
    auto endReply = connection->End(endRequest);
    cout << "points = " << endReply->points();

    sf::Text gameStatus;
    sf::Text gamePoints;

    gameStatus.setFont(font);
    gamePoints.setFont(font);
    gamePoints.setString("Your score  " + std::to_string(endReply->points()));
    gamePoints.setCharacterSize(50);
    gamePoints.setColor(sf::Color::Red);
    gamePoints.setPosition(200,300);

    if (endReply->status() == WIN) {
        gameStatus.setString("YOU WIN!");
    } else {
        gameStatus.setString("LOL, YOU LOSE");
    }
    delete endReply;
    gameStatus.setCharacterSize(50);
    gameStatus.setColor(sf::Color::Red);
    gameStatus.setPosition(200,200);

    window.clear();

    window.draw(gameStatus);
    window.draw(gamePoints);
    window.display();

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }
        }
        window.setFramerateLimit(60);
    }
}

bool GameLoop::loopBody (RenderWindow &window) {
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

    IterationRequest request;
    request.set_direction(direction);

    auto reply = connection->Iteration(request);
    
    direction = reply->being(id).direction();
    ((Pacman*)beings[id])->setSide(1);

    for (int i = 0; i < reply->coins_size(); i++) {
        coin.setPosition(reply->coins(i).x() * 32 + 40 ,reply->coins(i).y() * 32 + 40);
        window.draw(coin);
    }

    for (int i = 0; i < beingCount; i++) {
        beings[i]->setData(reply->being(i));
        beings[i]->draw(&window);
    }

    bool result = (reply->coins_size() == 0);

    delete reply;

    return result;
}
