//
// Created by viewsharp on 30.11.17.
//

#include "GameLoop.h"
#include "TileMap.h"
#include "Pacman.h"

void GameLoop::loop() {
//    window->clear(sf::Color::Yellow);

    ConnectRequest connectRequest;
    ConnectReply *connectReply;

    connectRequest.set_name(name);

    connectReply = connection->Connect(connectRequest);

    hex = connectReply->hex();
    cout<<"Connect to server. id_hex = "<<hex<<endl;

    delete connectReply;

    StartReply *startReply;
    StartRequest startRequest;
//    window->clear(sf::Color::Yellow);
    do {
        startReply = connection->Start(startRequest, hex);
        cout<<"Start: sleep = " << startReply->time() << endl;
        if (startReply->time() != 0) {
            usleep((useconds_t)startReply->time());
            delete  startReply;
        }
    } while (startReply->time() != 0);
    window = new RenderWindow(sf::VideoMode(800, 640), "SFML!");

    beings = new BeingView *[startReply->being_size()];
    beingCount = startReply->being_size();
    cout<<"bC = " << beingCount << endl;
    for (int i = 0; i < beingCount; i++) {
        const BeingInit *beingInit = &(startReply->being(i));
        switch(beingInit->type()) {
            case PACMAN:
                beings[i] = new Pacman(beingInit->name(), beingInit->data());
                cout << "Health" << beings[i]->health() << endl;
                cout << (((Pacman*)beings[i])->name) << endl;

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

    health = new Health();
    nicknames = new Text *[2];
    for (int i =0; i < 2; i++) {
        nicknames[i] = new Text();
        nicknames[i]->setFont(font);
        nicknames[i]->setString("lol");
        nicknames[i]->setCharacterSize(14);
        nicknames[i]->setColor(sf::Color::Red);
        cout << (((Pacman*)beings[i])->name) << endl;

    }

    while (window->isOpen()) {
        loopBody();
        window->setFramerateLimit(60);
    }
    delete[] health;
    for (int i =0; i < 2; i++) {
        delete[] nicknames[i];
    }
    delete[] nicknames;
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
//    // Declare and load a font
//    sf::Font font;
//    font.loadFromFile("src/pacfont.regular.ttf");
//// Create a text
//    sf::Text text("hello", font);
//    text.setCharacterSize(30);
//    text.setStyle(sf::Text::Bold);
//    text.setColor(sf::Color::Red);
//// Draw it
//    window->draw(text);

    // draw player health and nickname
    for (int i = 0; i < beings[id]->health(); ++i) {
        nicknames[i]->setPosition(beings[id]->pos().x()-16,beings[id]->pos().y()-16);
        window->draw(*nicknames[id]);
        window->draw(*health->getSprite());
        health->setPos(health->getImgX() + 32, health->getImgY());
    }
    health->setPos(800 - 32, health->getImgY());
    // draw friend health
    for (int i = 0; i < beings[1 - id]->health(); ++i) {
        window->draw(*health->getSprite());
        health->setPos(health->getImgX() - 32, health->getImgY());
    }
    health->setPos(0, health->getImgY());

    window->display();

    delete reply;
}