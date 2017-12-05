//
// Created by viewsharp on 03.12.17.
//

#ifndef PACMAN_MAPMANAGER_H
#define PACMAN_MAPMANAGER_H

#include <string>
#include <generated/service.pb.h>

using namespace std;
using namespace pacman_service;

const int tileSize = 32;

const std::string TileMap[] = {
        "T.....................t",
        "..s...sssssssssss......",
        ".......................",
        ".......................",
        ".......................",
        ".......................",
        ".......................",
        ".......................",
        ".......................",
        ".......................",
        ".......................",
        ".......................",
        ".......................",
        ".......................",
        ".......................",
        ".......................",
        ".......................",
        "B.....................b"
};

class MapManager {

public:

    static const int H = 18;
    static const int W = 23;

    static void getMap(StartReply *reply) {
        string *temp;
        for (int i = 0; i < H; i++) {
            temp = reply->add_map();
            *temp = TileMap[i];
        }
    }
};

#endif //PACMAN_MAPMANAGER_H
