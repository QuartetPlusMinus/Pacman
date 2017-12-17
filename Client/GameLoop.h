//
// Created by viewsharp on 30.11.17.
//

#ifndef ONENIGHTPACMAN_GAMELOOP_H
#define ONENIGHTPACMAN_GAMELOOP_H

#include <string>
#include <unistd.h>
#include <SFML/Graphics.hpp>
#include <generated/service.pb.h>

#include "PlayerConnectionClient.h"

#include "BeingView.h"
#include "TileMap.h"
#include "Pacman.h"
#include "Ghost.h"
#include "TileMap.h"

using namespace sf;
using namespace std;
using namespace pacman_service;

class GameLoop {

public:

    GameLoop(const string &host, const string &name, bool wasd) :
            connection(new PlayerConnectionClient(host)),
            wasd(wasd),
            beings(nullptr),
            beingCount(0),
            direction(RIGHT),
            event(),
            id(-1)
    {
        connection = new PlayerConnectionClient(host);
        if (!font.loadFromFile("src/pacfont.regular.ttf"))
        {
            cout << "Can't load fonts" << endl;
            throw "Ilnur";
        }

        loop(name);
    }


private:

    PlayerConnectionClient *connection;

    void loop(string name);

    void loopBody(RenderWindow &window);

    BeingView **beings;
    int beingCount;

    string hex;
    Direction direction;
    bool wasd;
    Event event;

    Font font;
    int id;
};

#endif //ONENIGHTPACMAN_GAMELOOP_H
