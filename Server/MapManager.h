//
// Created by viewsharp on 03.12.17.
//

#ifndef PACMAN_MAPMANAGER_H
#define PACMAN_MAPMANAGER_H

#include <string>
#include <generated/service.pb.h>

using namespace std;
using namespace pacman_service;

//const int tileSize = 32;

const std::string TileMap[] = {
        ".......................",
        ".s.sssss.sssss.sssss.s.",
        ".s...................s.",
        ".s.ssss.sssssss.ssss.s.",
        ".s.s...............s.s.",
        "...s.sssss.s.sssss.s...",
        ".s.......s.s.s.......s.",
        ".sssss.sss.s.sss.sssss.",
        ".s.......s.s.s.......s.",
        "...s.sssss.s.sssss.s...",
        ".s.s.......s.......s.s.",
        ".sss.ssss.sss.ssss.sss.",
        ".......s.......s.......",
        ".sssss.s.sssss.s.sssss.",
        "...........s...........",
        ".ss.s.ssss.s.ssss.s.ss.",
        ".ss.s.s.........s.s.ss.",
        "....s...sssssss...s...."
};

class MapManager {

public:

    static const int H = 18; // XXX: no hardcode
    static const int W = 23;

    static void getMap(StartReply *reply) {
        for (int i = 0; i < H; i++) {
            *reply->add_map() = TileMap[i];
        }
    }
};

#endif //PACMAN_MAPMANAGER_H
