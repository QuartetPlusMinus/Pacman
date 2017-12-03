//
// Created by viewsharp on 30.11.17.
//

#ifndef ONENIGHTPACMAN_GAMELOOP_H
#define ONENIGHTPACMAN_GAMELOOP_H

#include <string>
#include <chrono>
#include <unistd.h>
#include <SFML/Graphics.hpp>

#include "PlayerConnectionClient.h"
#include "service.grpc.pb.h"
#include "BeingView.h"
#include "Pacman.h"
#include "Ghost.h"

using namespace sf;
using namespace std;
using namespace pacman_service;
using chrono::high_resolution_clock;

class GameLoop {

public:

    GameLoop(PlayerConnectionClient *connection, string name) :
            connection(connection),
            name(name) {

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
    int health;

};

#endif //ONENIGHTPACMAN_GAMELOOP_H
