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
#include "Pacman.h"
#include "Ghost.h"

using namespace sf;
using namespace std;
using namespace pacman_service;
using chrono::high_resolution_clock;

class GameLoop {

public:

    GameLoop(RenderWindow *window, PlayerConnectionClient *connection, string name):
    window (window),
    connection(connection),
    name(name) {
        this->window = window;
        this->connection = connection;
        this->name = name;
        loop();
    }


private:

    RenderWindow *window;
    PlayerConnectionClient *connection;

    void loop();

    void loopBody();

    int id;
    Being **beings;
    string name;
    Direction direction;
    int health;

};

#endif //ONENIGHTPACMAN_GAMELOOP_H
