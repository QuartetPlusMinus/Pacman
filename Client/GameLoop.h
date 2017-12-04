//
// Created by viewsharp on 30.11.17.
//

#ifndef ONENIGHTPACMAN_GAMELOOP_H
#define ONENIGHTPACMAN_GAMELOOP_H

#include <string>
#include <chrono>
#include <unistd.h>
#include <SFML/Graphics.hpp>
#include <generated/service.pb.h>

#include "PlayerConnectionClient.h"
//#include "service.grpc.pb.h"
#include "BeingView.h"
#include "Pacman.h"
#include "Ghost.h"

using namespace sf;
using namespace std;
using namespace pacman_service;

using chrono::steady_clock;

class GameLoop {

public:

    GameLoop(const string &host, const string &name, bool wasd) :
            connection(new PlayerConnectionClient(host)),
            name(name),
            wasd(wasd),
            beings(nullptr),
            beingCount(0),
            direction(RIGHT),
            event() 
    {
        this->window = new RenderWindow(sf::VideoMode(800, 800), "SFML!");

        sf::CircleShape MyCircle(10);
        MyCircle.setFillColor(sf::Color::Red);

        sf::Texture pacTexture;
        pacTexture.loadFromFile("src/pacimg.png");

        sf::Texture ghostTexture;
        ghostTexture.loadFromFile("src/ghost.png");

        this->connection = connection;
        this->name = name;
        loop();
    }


private:

    RenderWindow *window;
    PlayerConnectionClient *connection;

    void loop();

    void loopBody();

    BeingView **beings;
    int beingCount;

    string hex;
    string name;
    Direction direction;
    bool wasd;
    sf::Event event;

};

#endif //ONENIGHTPACMAN_GAMELOOP_H
