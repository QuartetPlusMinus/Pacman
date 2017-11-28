//
// Created by viewsharp on 28.11.17.
//

#ifndef CLIENT_PLAYER_H
#define CLIENT_PLAYER_H

#include <SFML/Graphics.hpp>

#include "service.grpc.pb.h"

using pacman_service::DirectionEnum;
using pacman_service::RIGHT;


class Player{

public:
    Player(): dir(RIGHT), idValue(0){

    }
    DirectionEnum dir;
    sf::Sprite sprite;

    int id() {
        return idValue;
    }
private:
    int idValue;
};

#endif //CLIENT_PLAYER_H
