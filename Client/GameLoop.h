//
// Created by viewsharp on 30.11.17.
//

#ifndef ONENIGHTPACMAN_GAMELOOP_H
#define ONENIGHTPACMAN_GAMELOOP_H

#include <string>
//#include <chrono>
#include <unistd.h>
#include <SFML/Graphics.hpp>
#include <generated/service.pb.h>

#include "PlayerConnectionClient.h"
#include "BeingView.h"
#include "Pacman.h"
#include "Ghost.h"
#include "../cmake-build-debug/generated/service.pb.h"
#include "TileMap.h"

using namespace sf;
using namespace std;
using namespace pacman_service;

class GameLoop {

public:

    GameLoop(const string &host, const string &name, bool wasd) :
//    explicit GameLoop() :
            beings(nullptr),
            beingCount(0),
            direction(RIGHT),
            event(),
            tMap(nullptr),
            id(-1),
            wasd(wasd)
    {
//        cout << "Enter IP ..." << endl;
//        string host = "";
//        cin >> host;
//        if (host == "localhost") {
//            wasd = true;
//        }
//        else {
//            wasd = false;
//        }
//        string playerName;
//        cout << "Enter player name ..." << endl;
//        cin >> playerName;
        this->name = name;
        connection = new PlayerConnectionClient(host);
        if (!font.loadFromFile("src/pacfont.regular.ttf"))
        {
            cout << "Can't load fonts" << endl;
        }

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
    TileMap *tMap;
    Health *health;
    sf::Text **nicknames;
    sf::Font font;
    int id;
};

#endif //ONENIGHTPACMAN_GAMELOOP_H
