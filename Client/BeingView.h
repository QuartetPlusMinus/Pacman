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
    BeingView(const Being &data, const char *imgPath):
            Being(data),
            s(new sf::Sprite)
    {
        auto texture = new sf::Texture;
        texture->loadFromFile(imgPath);
        s->setTexture(*texture);
    }

    void setData(const Being &data);

    sf::Sprite *getSprite();

private:
    sf::Sprite *s;

};

#endif //PACMAN_BEINGVIEW_H