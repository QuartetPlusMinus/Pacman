//
// Created by viewsharp on 02.12.17.
//

#ifndef PACMAN_BEINGVIEW_H
#define PACMAN_BEINGVIEW_H

//#include "service.grpc.pb.h"
#include "SFML/Graphics.hpp"
#include <string>
#include <generated/service.grpc.pb.h>

using namespace pacman_service;
using namespace std;

class BeingView: public Being {

public:
    explicit BeingView(const Being &data, int imgX = 0, int imgY = 0):
            Being(data),
            imgX(imgX),
            imgY(imgY),
            sprite(new sf::Sprite)
    {
        texture = new sf::Texture;
        texture->loadFromFile("src/img.png");
        sprite->setTexture(*texture);
    }
    ~BeingView() override {
        delete texture;
        delete sprite;
    }

    void setData(const Being &data);

    sf::Sprite *getSprite();

private:
    sf::Sprite *sprite;
    sf::Texture *texture;
    int imgX;
    int imgY;
    bool status;

};

#endif //PACMAN_BEINGVIEW_H